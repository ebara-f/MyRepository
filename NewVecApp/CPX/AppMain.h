/***********************************************************************

    アプリのメイン処理を担うクラス

***********************************************************************/

#pragma once

#include    "common.h"
#include    "CPX.h"
#include    "HwCtrl.h" // 追加(2025.5.15yori)

class AppMain
{
public:
    static HANDLE  m_hThread;
    static bool    m_ThreadBreak;

public:
    static int  Init();
    static int  Term();
    static int  Grp01();
    static int  Grp02();
    static int  Grp03();
    static int  UpDateData01(STATUS01* sts);
    static int  UpDateData02(STATUS02* sts); // スキャナ用で追加(2025.6.19yori)
    static int  UpDateData03(STATUS03* sts); // 非接触自己診断用で追加(2025.6.24yori)
    static int  UpDateData04(THRESHOLD* th, int id); // しきい値用で追加(2025.7.31yori)  // id追加(2025.9.22yori)
    static int  UpDateData05(GAUGE* ga); // ゲージ用で追加(2025.7.31yori)
    static int  UpDateData06(STATUS04* sts); // 有接触自己診断用で追加(2025.9.1yori)
    static int  UpDateData01_Write(STATUS01* sts); // 追加(2025.7.18yori)
    static int  UpDateData02_Write(STATUS02* sts); // 追加(2025.8.17yori)
    static int  UpDateData04_Write(THRESHOLD* sts, int id); // 追加(2025.8.1yori) // id追加(2025.9.22yori)
    static int  UpDateData05_Write(GAUGE* ga); // 追加(2025.8.9yori)
    static int  UpDateData04_Default(THRESHOLD* sts, int id); // 追加(2025.8.1yori) // id追加(2025.9.22yori)
    static int  UpDateData05_Default(GAUGE* ga); // 追加(2025.8.9yori)
    static int  ContactInspectionPanelMesCallBack(); // 2025.9.2 add eba

    static void ThreadProc();
};


