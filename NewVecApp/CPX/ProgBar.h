/***********************************************************************

    エラー管理

***********************************************************************/

#pragma once

#include    <string>
#include    "common.h"
#include    "CPX.h"



class ProgBar
{
public:
    static PGB_CBFUNC1 CallBackShow;
    static void SetCB1( PGB_CBFUNC1 );

    static PGB_CBFUNC2 CallBackHide;
    static void SetCB2(PGB_CBFUNC2 );

public:
    //
};
