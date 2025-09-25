/***********************************************************************

    コマンド群を束ねるクラス
    Grp02.hをコピーして追加(2025.6.19yori)

***********************************************************************/

#pragma once

#include    "common.h"
#include    "CPX.h"
#include    "HwCtrl.h"



class Grp03
{
public:
    static int  Cmd01();
    static int  Cmd02();
    static int  Cmd03();
    static int  Cmd04(); // 追加(2025.7.3yori)
    static int  Cmd05(); // 追加(2025.8.11yori)
    static int  Cmd06(int scanmode); // 追加(2025.8.12yori)
    static int  Cmd07(int); // 追加(2025.8.21yori)
    static int  Cmd08(int power); // 追加(2025.8.21yori)
    static int  Cmd09(int pitch); // 追加(2025.8.21yori)
    static int  Cmd10(); // 追加(2025.8.23yori)
    static int  Cmd11(); // 追加(2025.8.24yori)
    static int  Cmd12(); // 追加(2025.8.24yori)
    static int  Cmd13(); // 追加(2025.8.24yori)
    static int  Cmd14(int twopeak); // 追加(2025.8.25yori)
    static int  Cmd15(); // 追加(2025.8.25yori)
    static int  Cmd16(); // 追加(2025.8.27yori)
    static int  Cmd17(); // 追加(2025.8.27yori)
};
