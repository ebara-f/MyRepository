//
//
//
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <io.h>
#include <sys/timeb.h>
#include <sys/types.h>	//H16 1.23
#include <sys/stat.h>	//H16 1.23

#define QUE_MAIN 1
#include "QueMain.h"
#include "QueProc.h"



//------------------------------------
HANDLE  hBoxMutex[QueEntry];	//[ADD:1006] 2010.12.7 yamade
int LogingFalg = 0;
int LoggindDay = 30;
int tDay;
char LogPath[256];
char LogBuf[1024];
//----------------------------------------------
// Initialize Queuing Table
//
void AppInit(void)
{

	int		i;
	WCHAR	wStrW[256] = { 0 };
	size_t	w_len = 0;


	hSEMAQUE = CreateSemaphore(NULL, 1, 1, NULL); // 追加(2021.11.24yori)

//>> [ADD:1006] 2010.12.7 yamade
	char buf[256]={0};
	for( i=0; i<QueEntry; i++ )
	{
		sprintf_s( buf, "LplQue_mutex%d", i );		// 2021.3.12 
		mbstowcs_s(&w_len, wStrW, strlen(buf), buf, _TRUNCATE);

		if ((hBoxMutex[i] = OpenMutex(MUTEX_ALL_ACCESS, FALSE, wStrW)) == NULL)
			hBoxMutex[i] = CreateMutex(NULL, FALSE, wStrW);
	}
//<< [ADD:1006] 2010.12.7 yamade


	QueProcAppInit();
}

//追加(2022.1.26yori)
void AppClose(void)
{
	QueClose();
}



//--------------------------------------------------------------------------------
// 履歴ファイルを削除（日付を見て）
//--------------------------------------------------------------------------------
void LogFileDelete(char PathName[], char ExtID[], int Days)
{
	//-----------------------------------------------------------------------
	char   Path[512];
	struct tm OrgTempTime;						// 2021.3.12
    struct tm *TempTime = &OrgTempTime;			// 2021.3.12
    time_t long_time;
    int    SysDate[3], FileDate[3];
    struct _finddata_t ffblk;
    int    FHandle, Rc;
	//-----------------------------------------------------------------------
	// strcpy(Path ,PathName);
	// strcat(Path, "\\");
	// strcat(Path, ExtID);
	strcpy_s(Path, PathName);	// 2021.3.12
	strcat_s(Path, "\\");		// 2021.3.12
	strcat_s(Path, ExtID);		// 2021.3.12
    //-----------------------------------------------------------------------
    time( &long_time );                /* long 整数として時刻を取得 */
    // TempTime = localtime( &long_time ); /* 現地時刻に変換 */
	localtime_s(TempTime,&long_time);		// 2021.3.12
	SysDate[0] = TempTime->tm_year+1900;
	SysDate[1] = TempTime->tm_mon+1;
	SysDate[2] = TempTime->tm_mday;
    //-----------------------------------------------------------------------
    FHandle = (int)_findfirst(Path,&ffblk);
    if (FHandle > 0) {
		//-------------------------------------------------------------------
        // TempTime = localtime( &ffblk.time_write ); /* 現地時刻に変換 */
		localtime_s(TempTime, &ffblk.time_write);		// 2021.3.12
		FileDate[0] = TempTime->tm_year+1900;
		FileDate[1] = TempTime->tm_mon+1;
		FileDate[2] = TempTime->tm_mday;
		LogFileCheckDelete(SysDate, FileDate, ffblk.name, PathName, Days); //H16 1.20
		for ( ; ; ) {
            Rc = _findnext(FHandle, &ffblk);
	        if (Rc != 0)
		        break;
			//-------------------------------------------------------------------
			// TempTime = localtime( &ffblk.time_write ); /* 現地時刻に変換 */
			localtime_s(TempTime, &ffblk.time_write);		// 2021.3.12
			FileDate[0] = TempTime->tm_year+1900;
			FileDate[1] = TempTime->tm_mon+1;
			FileDate[2] = TempTime->tm_mday;
			LogFileCheckDelete(SysDate, FileDate, ffblk.name, PathName, Days); //H16 1.20
		}
		_findclose(FHandle);
    }
}
//----------------------------------------------------------
// 履歴ファイルを検索（６０日たっている履歴ファイルを削除）
//--------------------------------------------------------------------------------
void LogFileCheckDelete(int SysDate[], int FileDate[], char FileName[], char LogPath[], int Days) //H16 1.20
{
	long FTime, STime;
	char DelFName[256];

	strcpy_s(DelFName, LogPath);	// 2021.3.12
	strcat_s(DelFName, "/");		// 2021.3.12
	strcat_s(DelFName, FileName);	// 2021.3.12
	STime = (SysDate[0]*12*30*24) + (SysDate[1]*30*24) + (SysDate[2]*24);
	FTime = (FileDate[0]*12*30*24) + (FileDate[1]*30*24) + (FileDate[2]*24);
	if((STime-FTime) > (24*Days))
		remove(DelFName);		// 削除
}
//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void __stdcall QueLogWrite(int QueId, int SendRecv, int DtLen, char WBuf[])
{
	char TBuf[64], LBuf[16];
	char FileName[255];
    FILE *pF;
	int i;
    //---------------------------------------------------------------------
	if (LogingFalg == 0)		// ロギングフラグＯｆｆ
		return;
    //---------------------------------------------------------------------
	TimeBinary(TBuf); //H16 1.20
	if (tDay != TBuf[2]) { //H16 1.20
		tDay = TBuf[2]; //H16 1.20
		LogFileDelete(LogPath, "*.log", LoggindDay);
	}
    //---------------------------------------------------------------------
	GetLogFileName(FileName);
	// if ((pF = fopen(FileName, "at")) != NULL) {
    if ((fopen_s(&pF,FileName, "at")) == 0) {			// 2021.3.12
		// ファイル書き込み;
		LogDayTimeSet(TBuf); //H15 8.5
		if (SendRecv == 0)
			sprintf_s(LogBuf, "%s Send QueID:%d Length:%d\n", TBuf, QueId, DtLen);		// 2021.3.12
		else
			sprintf_s(LogBuf, "%s Recv QueID:%d Length:%d\n", TBuf, QueId, DtLen);		// 2021.3.12
        fputs(LogBuf,pF);
		for (i = LogBuf[0] = 0; i < DtLen; i++) {
			if ((i != 0) && ((i % 16) == 0)) {
				// strcat(LogBuf, "\n");
				strcat_s(LogBuf, "\n");			// 2021.3.12
				fputs(LogBuf,pF);
				LogBuf[0] = 0;
			}
			sprintf_s(LBuf, "%02x ", WBuf[i] & 0x0ff);		// 2021.3.12
			strcat_s(LogBuf, LBuf);							// 2021.3.12
		}
		if ((i != 0) && ((i % 16)) != 0) {
			strcat_s(LogBuf, "\n");		// 2021.3.12
			fputs(LogBuf,pF);
		}
        fclose(pF);
	}
	else
		LogingFalg = 0;
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void TimeBinary(char tim[])
{
	char	tbuf[32];
	time_t	StartTM;		// 終点時間の取得バッファ
	struct tm Orgnewtime;					// 2021.3.12
    struct tm *newtime = &Orgnewtime;
	time_t	ltime;

	time(&StartTM);

	ltime = StartTM;
	if (ltime < 0)
		return;
    // newtime = localtime( &ltime );
	localtime_s(newtime,&ltime);	// 2021.3.12
    strftime( tbuf, 80, "%y%m%d%H%M%S", newtime);
	tim[0] = (tbuf[0] & 0x0f)*10+(tbuf[1] & 0x0f);
	tim[1] = (tbuf[2] & 0x0f)*10+(tbuf[3] & 0x0f);
	tim[2] = (tbuf[4] & 0x0f)*10+(tbuf[5] & 0x0f);
	tim[3] = (tbuf[6] & 0x0f)*10+(tbuf[7] & 0x0f);
	tim[4] = (tbuf[8] & 0x0f)*10+(tbuf[9] & 0x0f);
	tim[5] = (tbuf[10] & 0x0f)*10+(tbuf[11] & 0x0f);
}
//----------------------------------------------------------
//--------------------------------------------------------------------------------
void GetLogFileName(char LFName[])
{
	char		FName[32], Path[64];
	struct tm OrgTempTime;
    struct tm *TempTime = &OrgTempTime;
    time_t long_time;
    //-----------------------------------------------------------------------
    time( &long_time );                /* long 整数として時刻を取得 */
	localtime_s(TempTime,&long_time);			// 2021.3.12
	strcpy_s(Path, LogPath);	// 2021.3.12
	strcat_s(Path, "\\");		// 2021.3.12
	sprintf_s(FName, "%04d%02d%02d.log", TempTime->tm_year + 1900, TempTime->tm_mon + 1, TempTime->tm_mday);	// 2021.3.12
	strcpy_s(LFName, 254, Path);	// 2021.3.12
	strcat_s(LFName, 254, FName);	// 2021.3.12
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void LogDayTimeSet(char dt[]) //H15 8.5
{
	struct tm OrgTempTime;
    struct tm *TempTime = &OrgTempTime;
    time_t long_time;
    //-----------------------------------------------------------------------
    time( &long_time );                /* long 整数として時刻を取得 */
    // TempTime = localtime( &long_time ); /* 現地時刻に変換 */
	localtime_s(TempTime,&long_time);		// 2021.3.12
	// sprintf(dt,"%04d/%02d/%02d %02d:%02d:%02d ",
	//				TempTime->tm_year+1900,
	//				TempTime->tm_mon+1,
	//				TempTime->tm_mday,
	//				TempTime->tm_hour,
	//				TempTime->tm_min,
	//				TempTime->tm_sec);
	// buffer size 64byte 
	sprintf_s(dt, 63,"%04d/%02d/%02d %02d:%02d:%02d ",
		TempTime->tm_year + 1900,
		TempTime->tm_mon + 1,
		TempTime->tm_mday,
		TempTime->tm_hour,
		TempTime->tm_min,
		TempTime->tm_sec);		// 2021.3.12
}
