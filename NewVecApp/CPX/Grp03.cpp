/***********************************************************************

    SubWinow3のコールバッククラス
    Grp02.cppをコピーして追加(2025.6.19yori)

***********************************************************************/

#include "Grp03.h"
#include "UsrMsg.h"
#include "CalibComm.h" // 追加(2025.12.8yori)



/***********************************************************************

    コマンド01
    追加(2025.6.24yori)

***********************************************************************/

int Grp03::Cmd01()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SCAN_START_REQ; // スキャンスタート

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド02
    追加(2025.6.24yori)

***********************************************************************/

int Grp03::Cmd02()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SCAN_STOP_REQ; // スキャンストップ

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド03
    追加(2025.7.2yori)

***********************************************************************/

int Grp03::Cmd03()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SENS_CHECK_REQ; // 感度チェック開始

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド04
    追加(2025.7.3yori)

***********************************************************************/

int Grp03::Cmd04()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::POINTER_CHECK_REQ; // ポインタ位置チェック開始

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド05
    追加(2025.8.11yori)

***********************************************************************/

int Grp03::Cmd05()
{
    int ret = 0;

    // PolyWorksから接続した場合、非接触設定メニューが閉じられたことをPolyWorks側に知らせる。(2025.9.3yori)
    if (HwCtrl::m_b_Button_ConnectFlag == false)
    {
        HwCtrl::AppCommandSend(APP_SEND_CMD::CLOSE_SCANNER_MEAS_FORM);
    }

    return (ret);
}



/***********************************************************************

    コマンド06
    追加(2025.8.12yori)

***********************************************************************/

int Grp03::Cmd06(int scanmode)
{
    int ret = 0;

    HwCtrl::Func61(scanmode); // スキャナ計測モード変更

    return (ret);
}



/***********************************************************************

    コマンド07
    追加(2025.8.21yori)

***********************************************************************/

int Grp03::Cmd07(int sens)
{
    int ret = 0;

    HwCtrl::Func62(sens); // 感度変更

    return (ret);
}



/***********************************************************************

    コマンド08
    追加(2025.8.21yori)

***********************************************************************/

int Grp03::Cmd08(int power)
{
    int ret = 0;

    HwCtrl::Func63(power); // ガイドレーザーパワーの設定

    return (ret);
}



/***********************************************************************

    コマンド09
    追加(2025.8.21yori)

***********************************************************************/

int Grp03::Cmd09(int pitch)
{
    int ret = 0;

    HwCtrl::Func64(pitch); // X点間補間モードの設定

    return (ret);
}



/***********************************************************************

    コマンド10
    追加(2025.8.23yori)
    引数追加に伴う変更(2026.8.7yori)

***********************************************************************/

int Grp03::Cmd10(STATUS02* sts)
{
    int ret = 0;
    int i, j, k; // 追加(2026.8.6yori)
    PulsZMask mask; // 追加(2026.8.6yori)

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 3; j++)
        {
            for (k = 0; k < 2; k++)
            {
                mask.use[i][j][k] = sts->dist_use[i][j][k];
                mask.data[i][j][k] = sts->dist_data[i][j][k];
            }
        }
    }

    HwCtrl::Func65(&mask); // 距離マスクの設定

    return (ret);
}



/***********************************************************************

    コマンド11
    追加(2025.8.24yori)
    引数追加(2026.8.5yori)

***********************************************************************/

int Grp03::Cmd11(unsigned short bright_slice[5])
{
    int ret = 0;

    HwCtrl::Func66(bright_slice); // 輝度スライスの設定

    return (ret);
}



/***********************************************************************

    コマンド12
    追加(2025.8.24yori)
    引数追加(2026.8.5yori)

***********************************************************************/

int Grp03::Cmd12(unsigned short sens_slice[5])
{
    int ret = 0;

    HwCtrl::Func67(sens_slice); // 感度スライスの設定

    return (ret);
}



/***********************************************************************

    コマンド13
    追加(2025.8.24yori)
    引数追加(2026.8.5yori)
    引数追加、INIファイルに角度マスク有効無効保存(2026.8.31yori)

***********************************************************************/

int Grp03::Cmd13(int angle_mask_onoff, double angle)
{
    int ret = 0;

    HwCtrl::WriteIniScanAngleMaskEnable(angle_mask_onoff);
    HwCtrl::Func68(angle); // 角度マスクの設定

    return (ret);
}



/***********************************************************************

    コマンド14
    追加(2025.8.25yori)

***********************************************************************/

int Grp03::Cmd14(int twopeak)
{
    int ret = 0;

    HwCtrl::Func69(twopeak); // 2ピークマスクの設定

    return (ret);
}



/***********************************************************************

    コマンド15
    追加(2025.8.25yori)
    引数追加(2026.8.5yori)

***********************************************************************/

int Grp03::Cmd15(int edge)
{
    int ret = 0;

    HwCtrl::Func70(edge); // エッジマスクの設定

    return (ret);
}



/***********************************************************************

    コマンド16
    追加(2025.8.27yori)

***********************************************************************/

int Grp03::Cmd16()
{
    int ret = 0;

    HwCtrl::Func71(); // スキャナをリセット

    return (ret);
}



/***********************************************************************

    コマンド17
    追加(2025.8.27yori)

***********************************************************************/

int Grp03::Cmd17()
{
    int ret = 0;

    HwCtrl::Func32(); // スキャナネットワーク設定

    return (ret);
}



/***********************************************************************

    コマンド18
    追加(2025.11.11yori)

***********************************************************************/

int Grp03::Cmd18()
{
    int ret = 0;

    HwCtrl::m_ScannerSettingCloseFlag = true;

    return (ret);
}



/***********************************************************************

    ScannerAlignmentPanelFullCalStartBtn
    追加(2025.12.8yori)

***********************************************************************/

int Grp03::ScannerAlignmentPanelFullCalStartBtn()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SCAN_START_REQ; // スキャンスタート
    HwCtrl::ScannerSetMeasType(TDS_MEASTYPE_CALIB_FULL);

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    SetDistMaskEnable
    2026.8.12yori)

***********************************************************************/

int Grp03::SetDistMaskEnable(bool* maskfg)
{
    int ret = 0;
    bool fg = maskfg; // 追加(2026.8.18yori)

    if (fg == true)
    {
        TdsVecSetZMaskEnable(TRUE);
    }
    else
    {
        TdsVecSetZMaskEnable(FALSE);
    }

    return (ret);
}



/***********************************************************************

    SetBrightSliceLevel
    追加(2025.8.29yori)

***********************************************************************/

int Grp03::SetBrightSliceLevel(STATUS02* sts)
{
    int ret = 0;

    // スタンダード、アドバンスの有効無効をINIファイルに保存
    HwCtrl::WriteIniBrightSliceEnable(sts->bright_slice_std_enable, sts->bright_slice_adv_enable);
    HwCtrl::Func66(sts->bright_slice); // 輝度スライスの設定

    return (ret);
}



/***********************************************************************

    SetSensSliceLevel
    追加(2025.8.29yori)

***********************************************************************/

int Grp03::SetSensSliceLevel(STATUS02* sts)
{
    int ret = 0;

    // スタンダード、アドバンスの有効無効をINIファイルに保存
    HwCtrl::WriteIniSensSliceEnable(sts->sens_slice_std_enable, sts->sens_slice_adv_enable);
    HwCtrl::Func67(sts->sens_slice); // 感度スライスの設定

    return (ret);
}



/***********************************************************************

    SetBrightMaskSetting
    追加(2026.9.2yori)

***********************************************************************/

int Grp03::SetBrightMaskSetting(STATUS02* sts)
{
    int ret = 0;

    // 輝度マスク設定をINIファイルに保存
    HwCtrl::WriteIniBrightMaskSetting(sts->bright_mask_select, sts->bright_mask_upper_limit, sts->bright_mask_lower_limit);
    HwCtrl::m_BrightMaskUpperLimit = sts->bright_mask_upper_limit;
    HwCtrl::m_BrightMaskLowerLimit = sts->bright_mask_lower_limit;

    return (ret);
}