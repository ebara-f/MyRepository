#pragma once

#include "LplQue.h"

//QueProc.h
//---------------------------------------------------------
#define MES_DATA_BUFF_SIZE 200000 //バッファサイズ修正(2021.11.16yori)
#define	MES_SIZE		sizeof(t_MessForm)
#define	MES_SIZE_CHECK 	MES_DATA_BUFF_SIZE

struct t_MessForm {
	short	TId;
	int		Leng;
	char	Text[MES_DATA_BUFF_SIZE]; //送信する構造体のサイズ(=196208バイト)より大きくした(2021.11.16yori)
};

// LplQue.h にて宣言
/*
void	__stdcall LplInitialIFCommon(void);
void	__stdcall LplInitialIFCommonEx(int TblNo);//[ADD]- kanamura
int		__stdcall LplSendMesBox(int TID, int Leng, char SBuf[]);
int		__stdcall LplRecvMesBox(int TId, char RBuf[]);
char*	__stdcall LplCreateCommonArea(char CName[], int CSize);
void	__stdcall LplTerminateALL();							// 2025.4.11
*/

int __stdcall LplSendMesBox2(int TId, int Leng, char SBuf[]);	// 2021.4.15
int __stdcall LplSendMesBoxBuffferEmpty(int TId);				// 2021.4.15

void   QueProcAppInit(void);
void   QueClose(void);

void QueBusy(void);
void QueReady(void);
int	MesBoxBusyCheck(int TId);
int SendMesBox(int TId, int Leng, char SBuf[]);

void PutFreeBlock(int QId, char Buf[]);
void InitialIFCommon(char TblName[]);//2011/6/15

