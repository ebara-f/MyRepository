/***********************************************************************

    メッセージ一覧

***********************************************************************/

#pragma once

#include    <string>
#include    "common.h"
#include    "CPX.h"



class UsrMsg
{
public:
    static SM_CBFUNC CallBack;
    static void SetCB( SM_CBFUNC );

public:
    const static int WM_MainWnd_Close = WM_USER + 1;
    const static int WM_MainWnd_Btn01 = WM_USER + 2;
    const static int WM_MainWnd_Btn02 = WM_USER + 3;
    const static int WM_MainWnd_Btn03 = WM_USER + 4;

    const static int WM_Dlg01_Close   = WM_USER + 5;
    const static int WM_Dlg01_Btn01   = WM_USER + 6;
    const static int WM_Dlg01_Btn02   = WM_USER + 7;
    const static int WM_Dlg01_Btn03   = WM_USER + 8;

    const static int WM_Dlg02_Close   = WM_USER + 9;
    const static int WM_Dlg02_Btn01   = WM_USER + 10;

    const static int WM_Dlg03_Close   = WM_USER + 11;

    const static int WM_UpdateData1 = WM_USER + 12;   // 2025.5.22 add eba

    const static int WM_SubWnd01_Close = WM_USER + 13;  // 定数(仮名)で追加(2025.6.4yori)
    const static int WM_SubWnd01_Btn01 = WM_USER + 14;  // 定数(仮名)で追加(2025.6.4yori)
    const static int WM_SubWnd01_Btn02 = WM_USER + 15;  // 定数(仮名)で追加(2025.6.4yori)
    const static int WM_SubWnd01_Btn03 = WM_USER + 16;  // 定数(仮名)で追加(2025.6.4yori)
    const static int WM_SubWnd01_Btn04 = WM_USER + 17;  // 定数(仮名)で追加(2025.6.4yori)
    const static int WM_SubWnd01_Btn05 = WM_USER + 18;  // 定数(仮名)で追加(2025.6.4yori)

    const static int WM_SubWnd02_Close = WM_USER + 19;  // 追加(2025.6.11yori)
    const static int WM_SubWnd02_Btn01 = WM_USER + 20;  // 追加(2025.6.11yori)
    const static int WM_SubWnd02_Btn02 = WM_USER + 21;  // 追加(2025.6.11yori)
    const static int WM_SubWnd02_Btn03 = WM_USER + 22;  // 追加(2025.6.11yori)
    const static int WM_SubWnd02_Btn04 = WM_USER + 23;  // 追加(2025.6.11yori)
    const static int WM_SubWnd02_Btn05 = WM_USER + 24;  // 追加(2025.6.11yori)
    const static int WM_SubWnd02_Btn06 = WM_USER + 25;  // 追加(2025.6.12yori)

    const static int WM_InitPanel_Update = WM_USER + 26;   // 追加(2025.7.11yori)
    const static int WM_SubWnd01_Panel_Hide = WM_USER + 27;   // 名称変更(2025.7.25yori)
    const static int WM_InitPanel_Setup = WM_USER + 28;   // 追加(2025.7.14yori)

    const static int WM_DlgPrgBar1_Show = WM_USER + 29;   // 追加(2025.7.17yori)
    const static int WM_DlgPrgBar1_Close = WM_USER + 30;   // 追加(2025.7.17yori)
    const static int WM_DlgPrgBar2_Show = WM_USER + 31;   // 追加(2025.7.30yori)
    const static int WM_DlgPrgBar2_Close = WM_USER + 32;   // 追加(2025.7.30yori)
    const static int WM_DlgPrgBar3_Show = WM_USER + 33;   // 追加(2025.7.31yori)
    const static int WM_DlgPrgBar3_Close = WM_USER + 34;   // 追加(2025.7.31yori)

    const static int WM_SubWnd03_Close = WM_USER + 35;  // 追加(2025.8.10yori)
    const static int WM_SubWnd03_Btn01 = WM_USER + 36;  // 追加(2025.8.10yori)
    const static int WM_SubWnd03_Btn02 = WM_USER + 37;  // 追加(2025.8.10yori)
    const static int WM_SubWnd03_Btn03 = WM_USER + 38;  // 追加(2025.8.10yori)

    const static int WM_ContactInspectionPanel_MesCallBack = WM_USER + 39;  // 2025.9.2 add eba
    const static int WM_ContactInspectionPanel_ParaOutCallBack = WM_USER + 40;  // 2025.9.2 add eba
};
