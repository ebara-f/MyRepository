#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef LPLQUE_EXPORTS
#define LPLQUE_DECLSPEC __declspec(dllexport)
#else
#define LPLQUE_DECLSPEC __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"{
#endif

LPLQUE_DECLSPEC void WINAPI LplQue_IsExist( int* );
LPLQUE_DECLSPEC int  WINAPI LplQue_Create( unsigned long );
LPLQUE_DECLSPEC void WINAPI LplQue_Delete();
LPLQUE_DECLSPEC int  WINAPI LplQue_PutCmdID( int );
LPLQUE_DECLSPEC int  WINAPI LplQue_GetCmdID( int* );
LPLQUE_DECLSPEC int  WINAPI LplQue_PutData( unsigned long, char[] );
LPLQUE_DECLSPEC int  WINAPI LplQue_GetDataPoolSize( unsigned long* );
LPLQUE_DECLSPEC int  WINAPI LplQue_GetDataSize( unsigned long* );
LPLQUE_DECLSPEC int  WINAPI LplQue_GetData( unsigned long*, char[] );

#ifdef __cplusplus
}
#endif




