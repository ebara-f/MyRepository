// HsmsQue.cpp	キュー
// ********************************************************
//  送信用Queバッファ （送信のみに使用している)
//  32のマジックNOがあちこちで使用されているので注意
//   メモリマップど(プロセス間共通領域)のIDと同じ番号を使用するため変更不可
//  受信は直接メモリマップドファイルを読み出す
// 
#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "QueTask.h"
#include "QueProc.h"
#include "QueMain.h"

extern HANDLE  hBoxMutex[];

bool g_bThreadBreak = false;

struct	t_QueForm {
			int		WriteIx;
			int		ReadIx;
			char	*QueAddr[QueMax];
};
typedef	struct t_QueForm	STR_QUE;

HANDLE		hQUETASK;
HANDLE		hProcSEMA[QueEntry];
STR_QUE*	m_Que;

//----------------------------------------------

UINT  QueThread(LPVOID pParm);
void QueThreadStart(void)
{
	ULONG	shThreadId;
	hQUETASK = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)QueThread,
								NULL,0,
								&shThreadId);
}
////////////////////////////////////////////////
// DESCRIPTION: Send Control(H<-T/B)
// Queバッファーに積み込んだ(0～31) (t_MessForm)データをメモリーマップドでアプリ間通信に積み込む
//　
// 2021.3.15 注意書き
// IDには２種あり
//  QueバッファーはQueEntryで定義される ID番号 とメモリーマップドでアプリ間通信(Polyworks）
//  IDとは異なる　また、メモリマップドファイル名のIDとは無関係であるので注意が必要
//  アプリ間通信は一つのメモリでバッファの位置がことなるのみ　
//  このソース上　IDが混在しているように見受けられる　MesBoxBusyCheck(QNo)はRvText->TIdでなければならない
//　QueTask.cpp で定義されている #define COMM_MAX	32 と(RvText->TId <= 32がこの数値にあたる。
//   ---> マジックNoも使用されているため、当面32固定値とすること。
//　アクセスの際,WaitForSingleObject()しているが　RvTextは無関係？？？？？
//　　ところが　SendMesBox()でバッファーに書き込みの際 MesBox[0] = 1;とポインタを書き込み後に
//    フラグをセットしているために、相手側と競合にはなっていない。　LplRecvMesBox()と合わせて変更時には注意すること。

UINT  QueThread(LPVOID pParm)
{
	int		QNo;
	struct t_MessForm *RvText;

	for ( ; ; ) {

		if (g_bThreadBreak == true) break;

//>>[CHG:1006] 2010.12.7 yamade
//		Sleep(100);
		Sleep(10);
//<<[CHG:1006] 2010.12.7 yamade
		for (QNo = 1; QNo <= QueEntry; QNo++) {
			if(hBoxMutex[QNo-1]) WaitForSingleObject(hBoxMutex[QNo-1], INFINITE);	//[ADD:1006] 2010.12.7 yamade

			if (MesBoxBusyCheck(QNo) == 0) {
				RvText = (struct t_MessForm *)GetQue(QNo);
				if (RvText != NULL) {
					if (RvText->TId <= 32)
						SendMesBox(RvText->TId, RvText->Leng, RvText->Text);
					else {
						PutFreeBlock(RvText->TId-32, RvText->Text);					//  PutFreeBlock内容不明
					}
					free(RvText);
				}
			}

			if(hBoxMutex[QNo-1]) ReleaseMutex(hBoxMutex[QNo-1]);	//[ADD:1006] 2010.12.7 yamade
		}

	}
	return 0;
}

void TerminateQueThread(void)
{

	g_bThreadBreak = true;

	// スレッドの完了を待機
	WaitForSingleObject(hQUETASK, INFINITE);

	// ハンドルを閉じる
	CloseHandle(hQUETASK);

	return;
}

//---------------------------------------------------------

// キューのイニシャル
void InitialQue(void)
{
	int		i, j;
	SECURITY_ATTRIBUTES SecAtri;
	
	g_bThreadBreak = false;

	m_Que = new t_QueForm[QueEntry];
	for (i = 0; i < QueEntry; i++) {
		hProcSEMA[i] = CreateSemaphore(&SecAtri, 1, 1, NULL);
		m_Que[i].WriteIx = 0;
		m_Que[i].ReadIx  = 0;
		for (j = 0; j < QueMax; j++)
			m_Que[i].QueAddr[j] = 0;
	}
}

// キューのデリート
void DeleteQue(void)
{

	int		i;


	for (i = 0; i < QueEntry; i++) {
		for ( ; ; ) {
			if (m_Que[i].WriteIx != m_Que[i].ReadIx) {
				if (m_Que[i].ReadIx == QueMax-1) {
					m_Que[i].ReadIx = 0;
					free( m_Que[i].QueAddr[QueMax-1]);
				}
				else {
					m_Que[i].ReadIx++;
					free( m_Que[i].QueAddr[m_Que[i].ReadIx-1]);
				}
			}
			else
				break;
		}
	}

	if (m_Que != NULL) {
		delete[] m_Que;
	}

	//for (i = 0; i<QueEntry; i++)
	//{
	//	if (hBoxMutex[i] != NULL) {
	//		CloseHandle( hBoxMutex[i] );
	//	}
	//}

}

// キューにデータ(ポインター引き渡し char* (t_MessForm))を入れる
// 2021.3.15 戻り値 1の時のバグ修正
//   return を書き換える 
// 戻り値 0 成功
//        1 QueIDが指定番号以外 (基本なし 事前確認のこと)
//        2 バッファーがいっぱい（システム異常　動作停止のこと)
int PutQue(int QID, char* QAddr)
{
	int iSts = 0;														// 戻り値 (成功)

	if ((QID >= 1) && (QID <= QueEntry)) {
		WaitForSingleObject(hProcSEMA[QID-1], INFINITE);
		if (m_Que[QID-1].WriteIx == QueMax-1) {							// Bufferの最後まで到達
			if (m_Que[QID-1].ReadIx != 0) {								// いっぱいの判断　++WriteIxが読み出しに追いつく
				m_Que[QID-1].QueAddr[QueMax-1] = QAddr;
				m_Que[QID-1].WriteIx = 0;								// 書き込みカウンタを先頭に戻す
				iSts = 0;
			}
			else {
				iSts = 2;												// 致命的エラー
			}
		}
		else {
			if (m_Que[QID-1].WriteIx+1 != m_Que[QID-1].ReadIx) {		// いっぱいの判断　++WriteIxが読み出しに追いつく
				m_Que[QID-1].QueAddr[m_Que[QID-1].WriteIx] = QAddr;
				m_Que[QID-1].WriteIx++;									// 書き込みカウンタをリセットする
				iSts = 0;
			}
			else {
				iSts = 2;												// 致命的エラー
			}
		}
		ReleaseSemaphore(hProcSEMA[QID - 1], 1, NULL);
		return iSts;
	}
	else {
		return 1;														//        1 QueIDが指定番号以外 (基本なし 事前確認のこと)
	}
}

// キューからデータを取得する(ポインター　戻し )
// 戻り値 NULLでない　成功（データのポインタ) 処理後解放のこと
//        NULL データがないもしくはIDのエラー(このときバグあり修正)
void* GetQue(int QID)
{
	void* ptRes = NULL;

	if ((QID >= 1) && (QID <= QueEntry)) {
		WaitForSingleObject(hProcSEMA[QID-1], INFINITE);
		if (m_Que[QID-1].WriteIx != m_Que[QID-1].ReadIx) {				// ReasdとWriteが同じ番号はデータなし状態
			if (m_Que[QID-1].ReadIx == QueMax-1) {						// バッファー折り返し
				m_Que[QID-1].ReadIx = 0;
				ptRes = m_Que[QID-1].QueAddr[QueMax-1];
			}
			else {
				m_Que[QID-1].ReadIx++;
				ptRes = m_Que[QID-1].QueAddr[m_Que[QID-1].ReadIx-1];
			}
		}
		else {
			/* do nothing */
		}
		ReleaseSemaphore(hProcSEMA[QID - 1], 1, NULL);
		return ptRes;
	}
	else {
		return NULL;
	}
}
