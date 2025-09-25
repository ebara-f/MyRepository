/***********************************************************************

    コマンド群を束ねるクラス

***********************************************************************/

#pragma once

#include    "common.h"
#include    "CPX.h"
#include    "HwCtrl.h"


class Grp01
{
public:
    static int  Cmd01();
    static int  Cmd02( int, double, const TCHAR* );
    static int  Cmd03( int, double, const TCHAR*, int*, double*, TCHAR*&, int );

    static int  CmdXX(double* pA, TCHAR*& pB, int B_count);
    static int  Cmd04(); // 追加(2025.6.9yori)
    static int  Cmd05(); // 追加(2025.6.9yori)
    static int  Cmd06(); // 追加(2025.6.9yori)
    static int  Cmd07(); // 追加(2025.6.9yori)
    static int  Cmd08(); // 追加(2025.7.15yori)
    static int  Cmd09(); // 追加(2025.7.18yori)
    static int  Cmd10(); // 追加(2025.7.18yori)
    static int  Cmd11(); // 追加(2025.7.25yori)
    static int  Cmd12(); // 追加(2025.7.30yori)
    static int  Cmd13(); // 追加(2025.7.30yori)
    static int  Cmd14(); // 追加(2025.7.31yori)
    static int  Cmd15(); // 追加(2025.7.30yori)
    static int  Cmd16(); // 追加(2025.8.12yori)
};
