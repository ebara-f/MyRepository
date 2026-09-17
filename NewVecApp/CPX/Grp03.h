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
    static int  Cmd10(STATUS02* sts); // 追加(2025.8.23yori) // 引数追加(2026.8.7yori)
    static int  Cmd11(unsigned short bright_slice[5]); // 追加(2025.8.24yori) // 引数追加(2026.8.5yori)
    static int  Cmd12(unsigned short sens_slice[5]); // 追加(2025.8.24yori) // 引数追加(2026.8.5yori)
    static int  Cmd13(int angle_mask_onoff, double angle); // 追加(2025.8.24yori) // 引数追加(2026.8.5yori) // 引数追加(2026.8.31yori)
    static int  Cmd14(int twopeak); // 追加(2025.8.25yori)
    static int  Cmd15(int edge); // 追加(2025.8.25yori) // 引数追加(2026.8.5yori)
    static int  Cmd16(); // 追加(2025.8.27yori)
    static int  Cmd17(); // 追加(2025.8.27yori)
    static int  Cmd18(); // 追加(2025.11.11yori)
    static int  ScannerAlignmentPanelFullCalStartBtn(); // フルキャリ開始(2025.12.8yori)
    static int  SetDistMaskEnable(bool* maskfg); // 距離マスクの有効/無効を設定(2026.8.12yori)
    static int  SetBrightSliceLevel(STATUS02* sts); // 輝度スライス設定(2026.8.29yori)
    static int  SetSensSliceLevel(STATUS02* sts); // 感度スライス設定(2026.8.29yori)
    static int  SetBrightMaskSetting(STATUS02* sts); // 輝度マスク設定(2026.9.2yori)
};