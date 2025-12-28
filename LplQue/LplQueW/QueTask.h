#pragma once

// QueTask.h	ÉLÉÖÅ[

void InitialQue(void);
void DeleteQue(void);
int PutQue(int QID, char* QAddr);
void* GetQue(int QID);
void QueThreadStart(void);
void TerminateQueThread(void);
void GetQueCount(int QID,int* pWCnt,int* pRCnt);
