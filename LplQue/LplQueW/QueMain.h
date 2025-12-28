#pragma once

//QueMain.h
#define QUE_MAX		128
#define QUEID_MAX	16 //8

//>>[MOV:1006] 2010.12.7
//#define QueEntry	64//32
#define QueEntry	32 //kanamura
#define QueMax		2048 //64 2007/6/13 // 512Ç©ÇÁïœçX(2025.12.28yori)
//<<[MOV:1006] 2010.12.7
//---------------------------------------------------------

//<-í«â¡(2021.11.24yori)
#ifdef QUE_MAIN
	HANDLE hSEMAQUE;
#else
	extern HANDLE hSEMAQUE;
#endif
//->í«â¡(2021.11.24yori)

void AppInit(void);
void AppClose(void); //í«â¡(2022.1.26yori)

void LogFileDelete(char PathName[], char ExtID[], int Days);
void LogFileCheckDelete(int SysDate[], int FileDate[], char FileName[], char LogPath[], int Days); //H16 1.20
void TimeBinary(char tim[]);
void GetLogFileName(char LFName[]);
void LogDayTimeSet(char dt[]); //H15 8.5

void __stdcall QueLogWrite(int QueId, int SendRecv, int DtLen, char WBuf[]);
