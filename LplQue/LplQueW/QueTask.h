#pragma once

// QueTask.h	�L���[

void InitialQue(void);
void DeleteQue(void);
int PutQue(int QID, char* QAddr);
void* GetQue(int QID);
void QueThreadStart(void);
void TerminateQueThread(void);
