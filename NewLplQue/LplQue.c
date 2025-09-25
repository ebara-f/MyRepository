/***********************************************************************

    共有メモリを介したデータ授受機能

***********************************************************************/


#include    <windows.h>
#include    <stdio.h>
#include    <conio.h>
#include    "LplQue.h"



/***********************************************************************

    DLLメイン関数

***********************************************************************/

BOOL APIENTRY DllMain(
    HMODULE         hModule,     
    DWORD           ul_reason_for_call,
    LPVOID          lpReserved
)
{
    switch ( ul_reason_for_call )
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}



/***********************************************************************

    グローバル変数・定数

***********************************************************************/

#define CMD_POOL   ( "LplQue_CmdPool"  )
#define DATA_POOL  ( "LplQue_DataPool" )



/***********************************************************************

    データヘッダー 構造体

***********************************************************************/

typedef  struct lplque_datahead {
    unsigned long   DataPoolSize;   // データプールサイズ
    unsigned long   DataSize;       // データサイズ
} LPLQUE_DATAHEAD;



/***********************************************************************

    コマンドプール・データプールの存在の確認

***********************************************************************/

void WINAPI LplQue_IsExist(
    int*            yes_existFp         // o 1:存在する 0:存在しない
)
{
    int             yes_existF;
    HANDLE          hCmdPool,hDataPool;

    /*----- 出力変数の初期化 -----*/
    *yes_existFp = -1;

    hCmdPool = OpenFileMappingA(
                    FILE_MAP_ALL_ACCESS,
                    FALSE,
                    CMD_POOL
    );

    hDataPool = OpenFileMappingA(
                    FILE_MAP_ALL_ACCESS,
                    FALSE,
                    DATA_POOL
    );

    if ( hCmdPool != NULL  &&  hDataPool != NULL ) {
        yes_existF = 1;
    }
    else {
        yes_existF = 0;
    }

    /*----- 出力変数のセット -----*/
    *yes_existFp = yes_existF;
}



/***********************************************************************

    コマンドプール・データプールの作成

***********************************************************************/

int WINAPI LplQue_Create(
    unsigned long   DataPoolSize        // i データプールのサイズ
)
{
    /*----- Declare and Initialize -----------------------------------*/
    char*           errmsg = NULL;      /* error message              */
    long            rc  = 0;            /* return code                */
    long            frc = 0;            /* function return code       */

    long              yes_existF;
    unsigned long     DataPoolSizeN,CmdPoolSize;
    LPLQUE_DATAHEAD*  pDataHead;


    HANDLE            hCmdPool  = NULL;
    HANDLE            hDataPool = NULL;
    long*             pCmdPool  = NULL;
    char*             pDataPool = NULL;


    /*----- 入力引数チェック -----*/
    if ( DataPoolSize < 0 ) {
        rc = 1;
        goto ERR;
    }

    /*----- 既にファイルマッピングオブジェクトが存在しないか確認 -----*/
    LplQue_IsExist( &yes_existF );
    if ( yes_existF == 1 ) {
        rc = 2;
        goto ERR;
    }


    /*----------------------------------------------------------------*/
    /*     コマンドプール                                             */
    /*----------------------------------------------------------------*/

    /*----- ファイルマッピングオブジェクトの作成 -----*/
    CmdPoolSize = sizeof( long );

    hCmdPool = CreateFileMappingA(
                    INVALID_HANDLE_VALUE,
                    NULL,
                    PAGE_READWRITE,
                    0,
                    CmdPoolSize,
                    CMD_POOL
    );
    if ( hCmdPool == NULL ) {
        rc = 3;
        goto ERR;
    }

    /*----- メモリマッピング -----*/
    pCmdPool = (long*)MapViewOfFile(
                    hCmdPool,
                    FILE_MAP_ALL_ACCESS,
                    0,
                    0,
                    0
    );
    if ( pCmdPool == NULL ) {
        rc = 4;
        goto ERR;
    }

    /*----- 初期化 -----*/
    *pCmdPool = 0;    // 未セットを表す初期化値


    /*----------------------------------------------------------------*/
    /*     データプール                                               */
    /*----------------------------------------------------------------*/

    /*----- ファイルマッピングオブジェクトの作成 -----*/
    DataPoolSizeN =  DataPoolSize;
    DataPoolSizeN += sizeof( unsigned long );  // データプールサイズの変数分
    DataPoolSizeN += sizeof( unsigned long );  // データサイズの変数分

    hDataPool = CreateFileMappingA(
                    INVALID_HANDLE_VALUE,
                    NULL,
                    PAGE_READWRITE,
                    0,
                    DataPoolSizeN,  // 注意！
                    DATA_POOL
    );
    if ( hDataPool == NULL ) {
        rc = 5;
        goto ERR;
    }

    /*----- メモリマッピング -----*/
    pDataPool = (char*)MapViewOfFile(
                    hDataPool,
                    FILE_MAP_ALL_ACCESS,
                    0,
                    0,
                    0
    );
    if ( pDataPool == NULL ) {
        rc = 6;
        goto ERR;
    }

    /*----- 初期化 -----*/
    pDataHead = (LPLQUE_DATAHEAD*)pDataPool;
    pDataHead->DataPoolSize = DataPoolSizeN;
    pDataHead->DataSize = 0;


    /*----- メモリアンマッピング -----*/
    UnmapViewOfFile( pCmdPool  );
    pCmdPool = NULL;

    UnmapViewOfFile( pDataPool );
    pDataPool = NULL;

    /*----- Notice. -----*/
    hCmdPool  = NULL;
    hDataPool = NULL;


    goto OWARI;
    /*----- Error Message --------------------------------------------*/
ERR:
    switch( rc ){
        case 1 :
            errmsg = "DataPoolSize < 0 ";
            break;
        case 2 :
            errmsg = "already exist file mappinng object. ";
            break;
        case 3 : case 5 :
            errmsg = "err in CreateFileMappingA(). ";
            break;
        case 4 : case 6 :
            errmsg = "err in MapViewOfFile(). ";
            break;
        default:
            errmsg = "unknown error";
            break;
    }

    // エラーログなどのエラー管理はここで

    /*----- Closing and Return ---------------------------------------*/
OWARI:
    /*----- 終了処理 -----*/
    if ( pCmdPool  != NULL )  UnmapViewOfFile( pCmdPool  );
    if ( pDataPool != NULL )  UnmapViewOfFile( pDataPool );
    if ( hCmdPool  != NULL )  CloseHandle( hCmdPool  );
    if ( pDataPool != NULL )  CloseHandle( pDataPool );

    /*----- Terminate -----*/
    return( rc );
}



/***********************************************************************

    コマンドプール・データプールの破棄

***********************************************************************/

void WINAPI LplQue_Delete()
{
    HANDLE          hCmdPool,hDataPool;

    hCmdPool = OpenFileMappingA(
                    FILE_MAP_ALL_ACCESS,
                    FALSE,
                    CMD_POOL
    );
    if ( hCmdPool != NULL ) {
        CloseHandle( hCmdPool  );
    }

    hDataPool = OpenFileMappingA(
                    FILE_MAP_ALL_ACCESS,
                    FALSE,
                    DATA_POOL
    );
    if ( hDataPool != NULL ) {
        CloseHandle( hDataPool  );
    }
}



/***********************************************************************

    コマンドIDのセット

***********************************************************************/

int WINAPI LplQue_PutCmdID(
    int             CmdID               // i コマンドID
)
{
    /*----- Declare and Initialize -----------------------------------*/
    char*           errmsg = NULL;      /* error message              */
    long            rc  = 0;            /* return code                */
    long            frc = 0;            /* function return code       */

    HANDLE          hCmdPool;

    long*           pCmdPool = NULL;


    /*----- ファイルマッピングオブジェクトの取得 -----*/
    hCmdPool = OpenFileMappingA(
                    FILE_MAP_ALL_ACCESS,
                    FALSE,
                    CMD_POOL
    );
    if ( hCmdPool == NULL ) {
        rc = 1;
        goto ERR;
    }

    /*----- メモリマッピング -----*/
    pCmdPool = (long*)MapViewOfFile(
                    hCmdPool,
                    FILE_MAP_ALL_ACCESS,
                    0,
                    0,
                    0
    );
    if ( pCmdPool == NULL ) {
        rc = 2;
        goto ERR;
    }

    /*----- コマンドIDのセット -----*/
    *pCmdPool = CmdID;

    /*----- メモリアンマッピング -----*/
    UnmapViewOfFile( pCmdPool );
    pCmdPool = NULL;


    goto OWARI;
    /*----- Error Message --------------------------------------------*/
ERR:
    switch( rc ){
        case 1 :
            errmsg = "err in OpenFileMappingA(). ";
            break;
        case 2 :
            errmsg = "err in MapViewOfFile(). ";
            break;
        default:
            errmsg = "unknown error";
            break;
    }

    // エラーログなどのエラー管理はここで

    /*----- Closing and Return ---------------------------------------*/
OWARI:
    /*----- 終了処理 -----*/
    if ( pCmdPool != NULL )  UnmapViewOfFile( pCmdPool  );

    /*----- Terminate -----*/
    return( rc );
}



/***********************************************************************

    コマンドIDの取得

***********************************************************************/

int WINAPI LplQue_GetCmdID(
    int*            CmdIDp              // o コマンドID
)
{
    /*----- Declare and Initialize -----------------------------------*/
    char*           errmsg = NULL;      /* error message              */
    long            rc  = 0;            /* return code                */
    long            frc = 0;            /* function return code       */

    HANDLE          hCmdPool;

    long*           pCmdPool = NULL;


    /*----- ファイルマッピングオブジェクトの取得 -----*/
    hCmdPool = OpenFileMappingA(
                    FILE_MAP_ALL_ACCESS,
                    FALSE,
                    CMD_POOL
    );
    if ( hCmdPool == NULL ) {
        rc = 1;
        goto ERR;
    }

    /*----- メモリマッピング -----*/
    pCmdPool = (long*)MapViewOfFile(
                    hCmdPool,
                    FILE_MAP_ALL_ACCESS,
                    0,
                    0,
                    0
    );
    if ( pCmdPool == NULL ) {
        rc = 2;
        goto ERR;
    }

    /*----- コマンドIDの取得 -----*/
    *CmdIDp = *pCmdPool;

    /*----- メモリアンマッピング -----*/
    UnmapViewOfFile( pCmdPool );
    pCmdPool = NULL;


    goto OWARI;
    /*----- Error Message --------------------------------------------*/
ERR:
    switch( rc ){
        case 1 :
            errmsg = "err in OpenFileMappingA(). ";
            break;
        case 2 :
            errmsg = "err in MapViewOfFile(). ";
            break;
        default:
            errmsg = "unknown error";
            break;
    }

    // エラーログなどのエラー管理はここで

    /*----- Closing and Return ---------------------------------------*/
OWARI:
    /*----- 終了処理 -----*/
    if ( pCmdPool != NULL )  UnmapViewOfFile( pCmdPool  );

    /*----- Terminate -----*/
    return( rc );
}



/***********************************************************************

    データのセット

***********************************************************************/

int WINAPI LplQue_PutData(
    unsigned long   DataSize,           // i データサイズ
    char            Data[]              // i データ
)
{
    /*----- Declare and Initialize -----------------------------------*/
    char*           errmsg = NULL;      /* error message              */
    long            rc  = 0;            /* return code                */
    long            frc = 0;            /* function return code       */

    unsigned long     DataPoolSize,ii;
    LPLQUE_DATAHEAD*  pDataHead;
    HANDLE            hDataPool;
    char*             pData;

    char*             pDataPool = NULL;


    /*----- チェック -----*/
    if ( DataSize < 1  ||  Data == NULL ) {
        rc = 1;
        goto ERR;
    }

    frc = LplQue_GetDataPoolSize( &DataPoolSize );
    if ( frc != 0 ) {
        rc = 2;
        goto ERR;
    }

    if ( DataSize > DataPoolSize ) {
        rc = 3;
        goto ERR;
    }

    /*----- ファイルマッピングオブジェクトの取得 -----*/
    hDataPool = OpenFileMappingA(
                    FILE_MAP_ALL_ACCESS,
                    FALSE,
                    DATA_POOL
    );
    if ( hDataPool == NULL ) {
        rc = 4;
        goto ERR;
    }

    /*----- メモリマッピング -----*/
    pDataPool = (char*)MapViewOfFile(
                    hDataPool,
                    FILE_MAP_ALL_ACCESS,
                    0,
                    0,
                    0
    );
    if ( pDataPool == NULL ) {
        rc = 5;
        goto ERR;
    }

    /*----- データの書き込み -----*/
    pDataHead = (LPLQUE_DATAHEAD*)pDataPool;
    pDataHead->DataSize = DataSize;

    pData = pDataPool;
    for ( ii=0; ii<sizeof(LPLQUE_DATAHEAD); ii++ ) {
        pData ++;
    }

    memcpy( pData, Data, DataSize );

    /*----- メモリアンマッピング -----*/
    UnmapViewOfFile( pDataPool );
    pDataPool = NULL;

    goto OWARI;
    /*----- Error Message --------------------------------------------*/
ERR:
    switch( rc ){
        case 1 :
            errmsg = "No input data ? ";
            break;
        case 2 :
            errmsg = "err in MsgBox_GetDataPoolSize(). ";
            break;
        case 3 :
            errmsg = "data size is too lerge. ";
            break;
        case 4 :
            errmsg = "err in OpenFileMappingA(). ";
            break;
        case 5 :
            errmsg = "err in MapViewOfFile(). ";
            break;
        default:
            errmsg = "unknown error";
            break;
    }

    // エラーログなどのエラー管理はここで

    /*----- Closing and Return ---------------------------------------*/
OWARI:
    /*----- 終了処理 -----*/
    if ( pDataPool != NULL )  UnmapViewOfFile( pDataPool  );

    /*----- Terminate -----*/
    return( rc );
}



/***********************************************************************

    データ領域最大サイズの取得

***********************************************************************/

int WINAPI LplQue_GetDataPoolSize(
    unsigned long* DataPoolSizep        // o データプールサイズ
)
{
    /*----- Declare and Initialize -----------------------------------*/
    char*           errmsg = NULL;      /* error message              */
    long            rc  = 0;            /* return code                */
    long            frc = 0;            /* function return code       */

    HANDLE            hDataPool;
    LPLQUE_DATAHEAD*  pDataHead;

    char*             pDataPool = NULL;


    /*----- ファイルマッピングオブジェクトの取得 -----*/
    hDataPool = OpenFileMappingA(
                    FILE_MAP_ALL_ACCESS,
                    FALSE,
                    DATA_POOL
    );
    if ( hDataPool == NULL ) {
        rc = 1;
        goto ERR;
    }

    /*----- メモリマッピング -----*/
    pDataPool = (char*)MapViewOfFile(
                    hDataPool,
                    FILE_MAP_ALL_ACCESS,
                    0,
                    0,
                    0
    );
    if ( pDataPool == NULL ) {
        rc = 2;
        goto ERR;
    }

    /*----- データ領域最大サイズの取得 -----*/
    pDataHead = (LPLQUE_DATAHEAD*)pDataPool;
    *DataPoolSizep = pDataHead->DataPoolSize;

    /*----- メモリアンマッピング -----*/
    UnmapViewOfFile( pDataPool );
    pDataPool = NULL;


    goto OWARI;
    /*----- Error Message --------------------------------------------*/
ERR:
    switch( rc ){
        case 1 :
            errmsg = "err in OpenFileMappingA(). ";
            break;
        case 2 :
            errmsg = "err in MapViewOfFile(). ";
            break;
        default:
            errmsg = "unknown error";
            break;
    }

    // エラーログなどのエラー管理はここで

    /*----- Closing and Return ---------------------------------------*/
OWARI:
    /*----- 終了処理 -----*/
    if ( pDataPool != NULL )  UnmapViewOfFile( pDataPool  );

    /*----- Terminate -----*/
    return( rc );
}



/***********************************************************************

    データサイズの取得

***********************************************************************/

int WINAPI LplQue_GetDataSize(
    unsigned long* DataSizep            // o データサイズ
)
{
    /*----- Declare and Initialize -----------------------------------*/
    char*           errmsg = NULL;      /* error message              */
    long            rc  = 0;            /* return code                */
    long            frc = 0;            /* function return code       */

    HANDLE            hDataPool;
    LPLQUE_DATAHEAD*  pDataHead;

    char*             pDataPool = NULL;


    /*----- ファイルマッピングオブジェクトの取得 -----*/
    hDataPool = OpenFileMappingA(
                    FILE_MAP_ALL_ACCESS,
                    FALSE,
                    DATA_POOL
    );
    if ( hDataPool == NULL ) {
        rc = 1;
        goto ERR;
    }

    /*----- メモリマッピング -----*/
    pDataPool = (char*)MapViewOfFile(
                    hDataPool,
                    FILE_MAP_ALL_ACCESS,
                    0,
                    0,
                    0
    );
    if ( pDataPool == NULL ) {
        rc = 2;
        goto ERR;
    }

    /*----- データ領域最大サイズの取得 -----*/
    pDataHead = (LPLQUE_DATAHEAD*)pDataPool;
    *DataSizep = pDataHead->DataSize;

    /*----- メモリアンマッピング -----*/
    UnmapViewOfFile( pDataPool );
    pDataPool = NULL;


    goto OWARI;
    /*----- Error Message --------------------------------------------*/
ERR:
    switch( rc ){
        case 1 :
            errmsg = "err in OpenFileMappingA(). ";
            break;
        case 2 :
            errmsg = "err in MapViewOfFile(). ";
            break;
        default:
            errmsg = "unknown error";
            break;
    }

    // エラーログなどのエラー管理はここで

    /*----- Closing and Return ---------------------------------------*/
OWARI:
    /*----- 終了処理 -----*/
    if ( pDataPool != NULL )  UnmapViewOfFile( pDataPool  );

    /*----- Terminate -----*/
    return( rc );
}



/***********************************************************************

    データの取得
    データを格納する領域は呼び出し側で確保しておくこと

***********************************************************************/

int WINAPI LplQue_GetData(
    unsigned long*  DataSizep,          // o データサイズ
    char            Data[]              // o データ
)
{
    /*----- Declare and Initialize -----------------------------------*/
    char*           errmsg = NULL;      /* error message              */
    long            rc  = 0;            /* return code                */
    long            frc = 0;            /* function return code       */

    unsigned long     ii;
    LPLQUE_DATAHEAD*  pDataHead;
    HANDLE            hDataPool;
    char*             pData;

    char*             pDataPool = NULL;

    /*----- チェック -----*/
    if ( Data == NULL ) {
        rc = 1;
        goto ERR;
    }

    /*----- ファイルマッピングオブジェクトの取得 -----*/
    hDataPool = OpenFileMappingA(
                    FILE_MAP_ALL_ACCESS,
                    FALSE,
                    DATA_POOL
    );
    if ( hDataPool == NULL ) {
        rc = 2;
        goto ERR;
    }

    /*----- メモリマッピング -----*/
    pDataPool = (char*)MapViewOfFile(
                    hDataPool,
                    FILE_MAP_ALL_ACCESS,
                    0,
                    0,
                    0
    );
    if ( pDataPool == NULL ) {
        rc = 3;
        goto ERR;
    }

    pDataHead = (LPLQUE_DATAHEAD*)pDataPool;
    *DataSizep = pDataHead->DataSize;

    if ( *DataSizep > 0 ) {
        pData = pDataPool;
        for ( ii=0; ii<sizeof(LPLQUE_DATAHEAD); ii++ ) {
            pData ++;
        }

        memcpy( Data, pData, *DataSizep );
    }
    else {
        *DataSizep = 0;
    }

    /*----- メモリアンマッピング -----*/
    UnmapViewOfFile( pDataPool );
    pDataPool = NULL;

    goto OWARI;
    /*----- Error Message --------------------------------------------*/
ERR:
    switch( rc ){
        case 1 :
            errmsg = "No input Data ? ";
            break;
        case 2 :
            errmsg = "err in OpenFileMappingA(). ";
            break;
        case 3 :
            errmsg = "err in MapViewOfFile(). ";
            break;
        default:
            errmsg = "unknown error";
            break;
    }

    // エラーログなどのエラー管理はここで

    /*----- Closing and Return ---------------------------------------*/
OWARI:
    /*----- 終了処理 -----*/
    if ( pDataPool != NULL )  UnmapViewOfFile( pDataPool  );

    /*----- Terminate -----*/
    return( rc );
}
