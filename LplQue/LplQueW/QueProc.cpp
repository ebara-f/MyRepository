// *****************************************************
// このソースはQUEでないので注意、あくまでもプロセス間共通領域の 定義であり.
//
// InitialIFCommon(char TblName[])で確保すること　...EX()は使用しない
//  QueIDはどれかのマップドファイルの一部を使用する。
//
// 使用上の注意:#define COMM_MAX 32 あちこちでマジックNoが使用されている。
//              Queのインデックスも通信バッファも同じ番号を使用するため、定義を
//              変更しないこと
//              QueIDも通信IDも同じ番号となってしまっている。
//
//　　　　　　　( 以下、追記 20250404 by キカラボ 渡辺 )　
//              共有メモリマッピング文字列タイプ指定と
//              共有メモリにおけるポインタ位置指定に同じ番号を使ってしまっている。
//
// 通信バッファ構成
//   先頭
// COMM_SIZE*COMM_MAX -- 未使用
// MAX+MES_SIZE*32-- 通信バッファ (1データのみのやり取り)
// FBK_SIZE*32    -- 未使用
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <vector>
#include "QueProc.h"
#include "QueTask.h"
#include "QueMain.h"



HANDLE	hQueTbl;
char*	_IFCom;
std::vector<CString>	g_vNameFileMapping;



//インスタンス関数
#pragma data_seg("QueUser")
LONG	instanceUserCnt = 0;			//DLL INITIAL CALL COUNT
#pragma data_seg()

#define COMM_MAX	32
#define COMM_SIZE	0x10			// **** 2021.3.21 S.Fukai 未使用につき容量を若干確保 *****
#define	FBK_SIZE	0x1000			// *** 2021.3.21 S.Fukai 未使用 **

#define	IFC_SIZE	COMM_SIZE*COMM_MAX+MES_SIZE*32+FBK_SIZE*32		// 32はQueIDと合致させる必要あり 32は固定値とする
#define	MES_TOP		COMM_SIZE*COMM_MAX								// 実際のバッファ位置 (使用はここのみ)
#define	FBK_TOP		COMM_SIZE*COMM_MAX+MES_SIZE*32



//----------------------------------------------
// Initialize Queuing Table
//
void QueProcAppInit(void)
{
	hQueTbl   = NULL;
	_IFCom = NULL;
	g_vNameFileMapping.clear();

	//-------------------------------
	InitialQue();
	QueThreadStart();
}
//---------------------------------------------------------
//---------------------------------------------------------
void  __stdcall LplInitialIFCommon(void)
{

	InitialIFCommon("_IF_COMMON");//2011/6/15
}
//---------------------------------------------------------
//---------------------------------------------------------
// 2021.3.21 S.Fukai この関数は使用するなInitialIFCommon()と同一アドレスを使用することになる
//
void  __stdcall LplInitialIFCommonEx(int TblNo)
{
	char TblName[64];
	//---------------------------------------
	// sprintf(TblName, "_IF_COMMON_%d", TblNo);//2011/6/15
	sprintf_s(TblName, "_IF_COMMON_%d", TblNo);		// 2021.3.12
	InitialIFCommon(TblName);//2011/6/15
}
//---------------------------------------------------------
//2011/6/15
//---------------------------------------------------------
// 2021.3.21 メモリマップドファイルはこの関数で確保のこと ....EX()は使用不可
//
void InitialIFCommon(char TblName[])
{
	WCHAR	wStrW[256] = { 0 };
	size_t	w_len = 0;
	int		N;
	

	HANDLE hMap;


	mbstowcs_s(&w_len, wStrW, strlen(TblName), TblName, _TRUNCATE);

	hQueTbl = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, wStrW);
	if (hQueTbl == NULL) {
#ifdef  _WIN64
		hMap = CreateFileMapping((HANDLE)INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, IFC_SIZE, wStrW);
#else
		hMap = CreateFileMapping((HANDLE)0xffffffff, 0, PAGE_READWRITE, 0, IFC_SIZE, wStrW);
#endif
		if (hMap != INVALID_HANDLE_VALUE) {

			g_vNameFileMapping.push_back(CString(wStrW));

			hQueTbl = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, wStrW);
			if (hQueTbl != NULL) {

				if (_IFCom != NULL) {
					UnmapViewOfFile(_IFCom);
					_IFCom = NULL;
				}

				_IFCom = (char *)MapViewOfFile(hQueTbl, FILE_MAP_ALL_ACCESS, 0, 0, 0);
				for (N = 0; N < IFC_SIZE; N++)
					_IFCom[N] = 0;

				FlushViewOfFile(_IFCom, 0);
				instanceUserCnt++;

			}
			CloseHandle(hMap);
		
		}
	}
	else {

		if (_IFCom != NULL) {
			UnmapViewOfFile(_IFCom);
			_IFCom = NULL;
		}

		_IFCom = (char *)MapViewOfFile(hQueTbl, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		instanceUserCnt++;

	}
}



//---------------------------------------------------------------------
void QueClose(void)
{
	BOOL	rc;

	if (hQueTbl != NULL) {
		rc = UnmapViewOfFile(_IFCom);
		rc = CloseHandle(hQueTbl);
	}
	DeleteQue();
}
//------------------------------------------------------------
// プロセス間データ送信
// 戻り値0-正常格納、1-メモリ確保できず
//------------------------------------------------------------
int __stdcall LplSendMesBox(int TId, int Leng, char SBuf[])
{
	struct t_MessForm *MemAddr;

	WaitForSingleObject(hSEMAQUE, INFINITE); //追加(2025.12.27yori)

	if ((TId < 1) || (TId > 32))
	{
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2025.12.27yori)
		return 1;
	}

	MemAddr = (struct t_MessForm *)malloc(Leng+16);
	if (MemAddr != NULL) {
		QueLogWrite(TId, 0, Leng, SBuf);
		MemAddr->TId  = TId;
		MemAddr->Leng = Leng;
		memcpy_s(MemAddr->Text, MES_SIZE_CHECK, SBuf, Leng);		// 2021.4.14
		PutQue(TId, (char *)&MemAddr->TId);
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2025.12.27yori)
		return 0;
	}
	else
	{
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2025.12.27yori)
		return 1;
	}
}
//---------------------------------------------------
int MesBoxBusyCheck(int TId)
{
	char	*MesBox;
	if (_IFCom != NULL) {
		MesBox = _IFCom + MES_TOP + (TId-1)*MES_SIZE;
		return MesBox[0];
	}
	return 1;
}
int SendMesBox(int TId, int Leng, char SBuf[])
{
	char	*MesBox;

	if ((TId < 1) || (TId > 32))
		return 1;

	MesBox = _IFCom + MES_TOP + (TId-1)*MES_SIZE;
	if (MesBox[0] == 0) {
		MesBox[1] = (Leng >> 16) & 0x0ff;
		MesBox[2] = (Leng >>  8) & 0x0ff;
		MesBox[3] =  Leng & 0x0ff;

		memcpy_s(&MesBox[4], MES_SIZE_CHECK, SBuf, Leng);	// 2021.4.14
		MesBox[0] = 1;

		return 0;
	}

	return 1;
}


// ***********************************************
// Tid = 1～ 32のこと
// 0以上が正常読み出し (0はバッファに書き込んだがデータ長が0の場合）
// -1 指定ID以外を指定、絶対に発せさせないこと
// -1 メモリが確保できない
// -3 データなし(空)
// ************************************************* コメントを付ける 2021.4.2
int	__stdcall LplRecvMesBox(int TId, char RBuf[])
{
	char	*MesBox;
	int		Len;

	WaitForSingleObject(hSEMAQUE, INFINITE); //追加(2025.12.27yori)

	if ((TId < 1) || (TId > 32)) {
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2025.12.27yori)
		return -1;
	}
	if (hQueTbl == NULL) {
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2025.12.27yori)
		return -1;
	}

	MesBox = _IFCom + MES_TOP + (TId-1)*MES_SIZE;
	if (MesBox[0] == 1) {
		int Len_H = (MesBox[1] << 16) & 0x0ff0000;
		int Len_M = (MesBox[2] <<  8) & 0x0000ff00;
		int Len_L = (MesBox[3]      ) & 0x000000ff;
		Len = Len_H | Len_M | Len_L;

		memcpy_s(RBuf, MES_SIZE_CHECK, &MesBox[4], Len);		// 2021.4.15
		MesBox[0] = 0;

		QueLogWrite(TId, 1, Len, RBuf);
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2025.12.27yori)
		return Len;
	}
	ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2025.12.27yori)
	return -3;
}

void 	PutFreeBlock(int QId, char Buf[])//キューへフリーブロックを送る
{
	char	*MesBox;

	WaitForSingleObject(hSEMAQUE, INFINITE); //追加(2025.12.27yori)

	if ((QId < 1) || (QId > 32)) {
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2025.12.27yori)
		return;
	}
	MesBox = _IFCom + FBK_TOP + (QId-1)*FBK_SIZE;
	QueBusy();
	if (MesBox[0] == 0) {
		memcpy(&MesBox[4], &Buf[3], FBK_SIZE-3);
		MesBox[1] = Buf[0];
		MesBox[2] = Buf[1];
		MesBox[3] = Buf[2];
		MesBox[0] = 1;
		QueReady();
	}
	QueReady();
	ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2025.12.27yori)
}
void QueBusy(void)
{
	WCHAR	wStrW[256] = { 0 };
	size_t	w_len = 0;
	HANDLE	hIOSema;
	char	buf[256] = { 0 };


	// sprintf(buf, "_IFCOM_SEMA");
	sprintf_s(buf, "_IFCOM_SEMA");		// 2021.3.12
	mbstowcs_s(&w_len, wStrW, strlen(buf), buf, _TRUNCATE);

	for (;;) {

		hIOSema = CreateMutex(NULL, TRUE, wStrW);
		if (hIOSema == NULL) {
			if (GetLastError() != ERROR_ALREADY_EXISTS)
				return;
		}
		else {
			CloseHandle(hIOSema);
			return;
		}
		Sleep(10);
	}
}
void QueReady(void)
{
	WCHAR	wStrW[256] = { 0 };
	size_t	w_len = 0;
	HANDLE	hIOSema;
	char	buf[256] = { 0 };


	// sprintf(buf, "_IFCOM_SEMA");
	sprintf_s(buf, "_IFCOM_SEMA");		// 2021.3.12
	mbstowcs_s(&w_len, wStrW, strlen(buf), buf, _TRUNCATE);

	hIOSema = OpenMutex(MUTEX_ALL_ACCESS, FALSE, wStrW);
	if (hIOSema != NULL) {
		ReleaseMutex(hIOSema);
		CloseHandle(hIOSema);
	}
}

//---------------------------------------------------------
// プロセス間共通領域の確保
//		実際に本関数が発動されるかは怪しい By Geomlabo K.W. 2025.04.02 記
//---------------------------------------------------------
char*  __stdcall LplCreateCommonArea(char CName[], int CSize)
{
	char	TblName[32];
	int		N;
	char	*_CommArea;
	HANDLE	hProcMap;
	//LPTSTR	hProcQueTbl;

	HANDLE	hProcQueTbl;
	WCHAR	wStrW[256] = { 0 };
	size_t	w_len = 0;

	// strcpy(TblName, CName);
	strcpy_s(TblName, CName);	// 2021.3.12

	mbstowcs_s(&w_len, wStrW, strlen(TblName), TblName, _TRUNCATE);

	hProcQueTbl = (char *)OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, wStrW);
	if (hProcQueTbl == NULL) {
#ifdef  _WIN64
		hProcMap = CreateFileMapping((HANDLE)INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, CSize, wStrW);
#else
		hProcMap = CreateFileMapping((HANDLE)0xffffffff, 0, PAGE_READWRITE, 0, CSize, wStrW);
#endif
		if (hProcMap != INVALID_HANDLE_VALUE) {

			g_vNameFileMapping.push_back(CString(wStrW));

			hProcQueTbl = (char *)OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, wStrW);
			if (hProcQueTbl != NULL) {
				//_CommArea = (char *)MapViewOfFile(hQueTbl, FILE_MAP_ALL_ACCESS, 0, 0, 0);
				_CommArea = (char *)MapViewOfFile(hQueTbl, FILE_MAP_ALL_ACCESS, 0, 0, CSize);//kanamura
				for (N = 0; N < CSize; N++)
					_CommArea[N] = 0;
				FlushViewOfFile(_CommArea, 0);
				CloseHandle(hProcMap);
				return _CommArea;
			}
			CloseHandle(hProcMap);
			return NULL;
		}
		return NULL;
	}
	else {
		//return (char *)MapViewOfFile(hProcQueTbl, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		return (char *)MapViewOfFile(hProcQueTbl, FILE_MAP_ALL_ACCESS, 0, 0, CSize);//kanamura
	}
}

// ********************************************************
//  このシステムではVecからPolyworksへの測定データ転送はこのQueの2重バッファは不要
// 　直接メモリマップドファイルに書き込めるようにする。
// 　戻り値 0 書き込み成功
//          1 空きなし（書き込み待ち)
//          2 エラー
// 2021.4.15
// *********************************************************
int __stdcall LplSendMesBox2(int TId, int Leng, char SBuf[])
{

	WaitForSingleObject(hSEMAQUE, INFINITE); //追加(2021.11.24yori)

	char	*MesBox;

	if ((TId < 1) || (TId > 32))
	{
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2021.11.24yori)
		return 2;	// 基本的にこのエラーは帰らない
	}

	MesBox = _IFCom + MES_TOP + (TId-1)*MES_SIZE;
	if (MesBox[0] == 0)
	{
		MesBox[1] = (Leng >> 16) & 0x0ff;
		MesBox[2] = (Leng >>  8) & 0x0ff;
		MesBox[3] = Leng & 0x0ff;

		memcpy_s(&MesBox[4], MES_SIZE_CHECK, SBuf, Leng);	// 2021.4.14
		MesBox[0] = 1;

		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2021.11.24yori)
		return 0;		// 書き込み(copy)完了
	}
	else
	{
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2021.11.24yori)
		return 1;		// MesBox[0]が1なので読み出されていない
	}
}

// *****************************************************
//   バッファが空かどうかを判断
//   戻り値 0 -- バッファは空
//          1 -- 転送データあり
// 2021.4.15
// ******************************************************
int __stdcall LplSendMesBoxBuffferEmpty(int TId)
{
	char	*MesBox;

	WaitForSingleObject(hSEMAQUE, INFINITE); //追加(2025.12.27yori)

	if ((TId < 1) || (TId > 32)) {
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2025.12.27yori)
		return 1;	// 基本的にこのエラーは帰らない
	}

	MesBox = _IFCom + MES_TOP + (TId-1)*MES_SIZE;
	if (MesBox[0] == 0)
	{
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2025.12.27yori)
		return 0;		// 書き込み可能
	}
	else {
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //追加(2025.12.27yori)
		return 1;		// MesBox[0]が1なので書き込めない
	}
}

// *****************************************************
//   各種の終了処理をまとめて行う
//   LplQueが不要になるタイミングで本関数を呼び出すこと
//　　( 20250411 by キカラボ 渡辺 )　
// ******************************************************
void __stdcall LplTerminateALL()
{

	size_t	ifnm = 0;
	HANDLE	handle_FileMapping;
	CString	strName;

	/* 常時キュー書き込み処理スレッドのハンドルを終了 */
	TerminateQueThread();

	/* ファイルマッピングオブジェクトのハンドルを終了 */
	for (ifnm = 0; ifnm < g_vNameFileMapping.size(); ifnm++) {
		strName = g_vNameFileMapping[ifnm];
		handle_FileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, strName.GetString());
		CloseHandle(handle_FileMapping);
	}

	return;
}

// 追加(2025.12.28yori)
void __stdcall LplGetQueCount(int TId, int* pWCnt, int* pRCnt)
{
	GetQueCount(TId, &*pWCnt, &*pRCnt);
}

