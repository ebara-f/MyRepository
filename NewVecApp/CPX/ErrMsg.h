/***********************************************************************

    エラー管理

***********************************************************************/

#pragma once

#include    <string>
#include    "common.h"
#include    "CPX.h"



class ErrMsg
{
public:
    static ER_CBFUNC CallBack;
    static void SetCB( ER_CBFUNC );

public:
    const static int ERR_MORNING = 1;   /* おはようございます         */
    const static int ERR_HELLO   = 2;   /* こんにちは                 */
    const static int ERR_EVENING = 3;   /* こんばんは                 */

public:
    static int  GetMsg( int, TCHAR*&, int );
};
