/***********************************************************************

    エラー管理

***********************************************************************/

#pragma once

#include    <string>
#include    "common.h"
#include    "CPX.h"



class UsrMsgBox
{
public:
    static UMB_CBFUNC CallBack;
    static void SetCB( UMB_CBFUNC );

public:
    //
};
