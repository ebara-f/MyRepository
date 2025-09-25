// *****************************************************
// ���̃\�[�X��QUE�łȂ��̂Œ��ӁA�����܂ł��v���Z�X�ԋ��ʗ̈�� ��`�ł���.
//
// InitialIFCommon(char TblName[])�Ŋm�ۂ��邱�Ɓ@...EX()�͎g�p���Ȃ�
//  QueID�͂ǂꂩ�̃}�b�v�h�t�@�C���̈ꕔ���g�p����B
//
// �g�p��̒���:#define COMM_MAX 32 ���������Ń}�W�b�NNo���g�p����Ă���B
//              Que�̃C���f�b�N�X���ʐM�o�b�t�@�������ԍ����g�p���邽�߁A��`��
//              �ύX���Ȃ�����
//              QueID���ʐMID�������ԍ��ƂȂ��Ă��܂��Ă���B
//
//�@�@�@�@�@�@�@( �ȉ��A�ǋL 20250404 by �L�J���{ �n�� )�@
//              ���L�������}�b�s���O������^�C�v�w���
//              ���L�������ɂ�����|�C���^�ʒu�w��ɓ����ԍ����g���Ă��܂��Ă���B
//
// �ʐM�o�b�t�@�\��
//   �擪
// COMM_SIZE*COMM_MAX -- ���g�p
// MAX+MES_SIZE*32-- �ʐM�o�b�t�@ (1�f�[�^�݂̂̂����)
// FBK_SIZE*32    -- ���g�p
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



//�C���X�^���X�֐�
#pragma data_seg("QueUser")
LONG	instanceUserCnt = 0;			//DLL INITIAL CALL COUNT
#pragma data_seg()

#define COMM_MAX	32
#define COMM_SIZE	0x10			// **** 2021.3.21 S.Fukai ���g�p�ɂ��e�ʂ��኱�m�� *****
#define	FBK_SIZE	0x1000			// *** 2021.3.21 S.Fukai ���g�p **

#define	IFC_SIZE	COMM_SIZE*COMM_MAX+MES_SIZE*32+FBK_SIZE*32		// 32��QueID�ƍ��v������K�v���� 32�͌Œ�l�Ƃ���
#define	MES_TOP		COMM_SIZE*COMM_MAX								// ���ۂ̃o�b�t�@�ʒu (�g�p�͂����̂�)
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
// 2021.3.21 S.Fukai ���̊֐��͎g�p�����InitialIFCommon()�Ɠ���A�h���X���g�p���邱�ƂɂȂ�
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
// 2021.3.21 �������}�b�v�h�t�@�C���͂��̊֐��Ŋm�ۂ̂��� ....EX()�͎g�p�s��
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
// �v���Z�X�ԃf�[�^���M
// �߂�l0-����i�[�A1-�������m�ۂł���
//------------------------------------------------------------
int __stdcall LplSendMesBox(int TId, int Leng, char SBuf[])
{
	struct t_MessForm *MemAddr;


	if ((TId < 1) || (TId > 32))
		return 1;

	MemAddr = (struct t_MessForm *)malloc(Leng+16);
	if (MemAddr != NULL) {
		QueLogWrite(TId, 0, Leng, SBuf);
		MemAddr->TId  = TId;
		MemAddr->Leng = Leng;
		memcpy_s(MemAddr->Text, MES_SIZE_CHECK, SBuf, Leng);		// 2021.4.14
		PutQue(TId, (char *)&MemAddr->TId);
		return 0;
	}
	else
		return 1;

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
// Tid = 1�` 32�̂���
// 0�ȏオ����ǂݏo�� (0�̓o�b�t�@�ɏ������񂾂��f�[�^����0�̏ꍇ�j
// -1 �w��ID�ȊO���w��A��΂ɔ��������Ȃ�����
// -1 ���������m�ۂł��Ȃ�
// -3 �f�[�^�Ȃ�(��)
// ************************************************* �R�����g��t���� 2021.4.2
int	__stdcall LplRecvMesBox(int TId, char RBuf[])
{
char	*MesBox;
int		Len;

if ((TId < 1) || (TId > 32))
	return -1;
	if (hQueTbl == NULL)
		return -1;

	MesBox = _IFCom + MES_TOP + (TId-1)*MES_SIZE;
	if (MesBox[0] == 1) {
		int Len_H = (MesBox[1] << 16) & 0x0ff0000;
		int Len_M = (MesBox[2] <<  8) & 0x0000ff00;
		int Len_L = (MesBox[3]      ) & 0x000000ff;
		Len = Len_H | Len_M | Len_L;

		memcpy_s(RBuf, MES_SIZE_CHECK, &MesBox[4], Len);		// 2021.4.15
		MesBox[0] = 0;

		QueLogWrite(TId, 1, Len, RBuf);

		return Len;
	}

	return -3;
}

void 	PutFreeBlock(int QId, char Buf[])//�L���[�փt���[�u���b�N�𑗂�
{
	char	*MesBox;

	if ((QId < 1) || (QId > 32))
		return;
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
// �v���Z�X�ԋ��ʗ̈�̊m��
//		���ۂɖ{�֐�����������邩�͉����� By Geomlabo K.W. 2025.04.02 �L
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
//  ���̃V�X�e���ł�Vec����Polyworks�ւ̑���f�[�^�]���͂���Que��2�d�o�b�t�@�͕s�v
// �@���ڃ������}�b�v�h�t�@�C���ɏ������߂�悤�ɂ���B
// �@�߂�l 0 �������ݐ���
//          1 �󂫂Ȃ��i�������ݑ҂�)
//          2 �G���[
// 2021.4.15
// *********************************************************
int __stdcall LplSendMesBox2(int TId, int Leng, char SBuf[])
{

	WaitForSingleObject(hSEMAQUE, INFINITE); //�ǉ�(2021.11.24yori)

	char	*MesBox;

	if ((TId < 1) || (TId > 32))
	{
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //�ǉ�(2021.11.24yori)
		return 2;	// ��{�I�ɂ��̃G���[�͋A��Ȃ�
	}

	MesBox = _IFCom + MES_TOP + (TId-1)*MES_SIZE;
	if (MesBox[0] == 0)
	{
		MesBox[1] = (Leng >> 16) & 0x0ff;
		MesBox[2] = (Leng >>  8) & 0x0ff;
		MesBox[3] = Leng & 0x0ff;

		memcpy_s(&MesBox[4], MES_SIZE_CHECK, SBuf, Leng);	// 2021.4.14
		MesBox[0] = 1;

		ReleaseSemaphore(hSEMAQUE, 1, NULL); //�ǉ�(2021.11.24yori)
		return 0;		// ��������(copy)����
	}
	else
	{
		ReleaseSemaphore(hSEMAQUE, 1, NULL); //�ǉ�(2021.11.24yori)
		return 1;		// MesBox[0]��1�Ȃ̂œǂݏo����Ă��Ȃ�
	}
}

// *****************************************************
//   �o�b�t�@���󂩂ǂ����𔻒f
//   �߂�l 0 -- �o�b�t�@�͋�
//          1 -- �]���f�[�^����
// 2021.4.15
// ******************************************************
int __stdcall LplSendMesBoxBuffferEmpty(int TId)
{
	char	*MesBox;

	if ((TId < 1) || (TId > 32))	return 1;	// ��{�I�ɂ��̃G���[�͋A��Ȃ�

	MesBox = _IFCom + MES_TOP + (TId-1)*MES_SIZE;
	if (MesBox[0] == 0)
	{
		return 0;		// �������݉\
	}
	else {
		return 1;		// MesBox[0]��1�Ȃ̂ŏ������߂Ȃ�
	}
}

// *****************************************************
//   �e��̏I���������܂Ƃ߂čs��
//   LplQue���s�v�ɂȂ�^�C�~���O�Ŗ{�֐����Ăяo������
//�@�@( 20250411 by �L�J���{ �n�� )�@
// ******************************************************
void __stdcall LplTerminateALL()
{

	size_t	ifnm = 0;
	HANDLE	handle_FileMapping;
	CString	strName;

	/* �펞�L���[�������ݏ����X���b�h�̃n���h�����I�� */
	TerminateQueThread();

	/* �t�@�C���}�b�s���O�I�u�W�F�N�g�̃n���h�����I�� */
	for (ifnm = 0; ifnm < g_vNameFileMapping.size(); ifnm++) {
		strName = g_vNameFileMapping[ifnm];
		handle_FileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, strName.GetString());
		CloseHandle(handle_FileMapping);
	}

	return;
}

