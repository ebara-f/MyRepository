/***********************************************************************

    SubWinow1のコールバッククラス

***********************************************************************/

#include "Grp01.h"
#include "UsrMsg.h"



/***********************************************************************

    コマンド01

***********************************************************************/

int Grp01::Cmd01()
{
    int ret = 0;

    HwCtrl::m_b_Button_ConnectFlag = true; // アプリ側から接続を行った。(2025.6.10yori)

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);
    if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::START ||
        HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::FINISH ||
        HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::DISCONNECT_CMP)    // 2025.7.2 eba chg // DISCONNECT_CMP追加(2025.9.2yori)
    {
        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
    }
    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド02

***********************************************************************/

int Grp01::Cmd02(
    int             A,          // i 入力パラメータ(A)
    double          B,          // i 入力パラメータ(B)
    const TCHAR*    C           // i 入力パラメータ(C)
)
{
    return( 0 );
}



/***********************************************************************

    コマンド03

***********************************************************************/

int Grp01::Cmd03(
    int             A,          // i 入力パラメータ(A)
    double          B,          // i 入力パラメータ(B)
    const TCHAR*    C,          // i 入力パラメータ(C)
    int*            pD,         // o 出力パラメータ(D)
    double*         pE,         // o 出力パラメータ(E)
    TCHAR*&         pF,         // i 入力パラメータ(F)
    int             F_count     // i 入力パラメータ(F_count)
)
{
    *pD = A * 2;
    *pE = B * 3.0;

    if ( F_count > 0 ) {
        int len = (int)_tcslen(C);
        for ( int ii=0; ii<len; ii++ ) {
            pF[ii] = C[len-1-ii];
        }
        pF[len] = 0;
    }

    return( 0 );
}



/***********************************************************************

    コマンドXX
    C#メイン画面に測定器のステータスを渡す
    追加(2025.5.22 eba)
    テスト版
***********************************************************************/

int Grp01::CmdXX(double* pA, TCHAR*& pB, int B_count)
{
    *pA = 999.999;
    wcscpy_s(pB, B_count, _T("TEST___________"));

    return (0);
}



/***********************************************************************

    コマンド04
    追加(2025.6.9yori)

***********************************************************************/

int Grp01::Cmd04()
{
    int ret = 0;
    static int dmy = 0;
    // 2025.7.4 eba del
    //HwCtrl::m_b_Button_ConnectFlag = false; // アプリ側から切断を行った。(2025.6.10yori)
    //ret = HwCtrl::Func04(); // 有接触切断

    // 2025.7.2 eba chg
    //WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE); // コールバック関数UsrMsg::CallBackが戻ってこないため、一時的にコメントアウト、後で調査(2025.8.21yori)
    if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::CONNECT_CMP ||
        HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::MEAS_IDLE ||
        HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::INITIALIZE_CMP || // 2025.9.30 add eba
        HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::SCANNER_DISCONNECT_CMP) // 追加(2025.12.18yori)
    {
        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::DISCONNECT_REQ;
    }
    else
    {
        dmy = 1;
    }
    //ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL); // コールバック関数UsrMsg::CallBackが戻ってこないため、一時的にコメントアウト、後で調査(2025.8.21yori)

    return (ret);
}



/***********************************************************************

    コマンド05
    追加(2025.6.9yori)

***********************************************************************/

int Grp01::Cmd05()
{
    int ret = 0;
    
    //WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE); // コールバック関数UsrMsg::CallBackが戻ってこないため、一時的にコメントアウト、後で調査(2025.8.21yori)

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE_REQ; // イニシャライズモードへ変更

    //ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL); // コールバック関数UsrMsg::CallBackが戻ってこないため、一時的にコメントアウト、後で調査(2025.8.21yori)

    return (ret);
}



/***********************************************************************

    コマンド06
    追加(2025.6.9yori)

***********************************************************************/

int Grp01::Cmd06()
{
    int ret = 0;

    HwCtrl::m_hVecCnt.m_Sts.m_INIT0_REQ_Fg = 1; // 追加(2025.6.10yori) // true→1へ変更、m_Sts追加(2025.8.22yori)

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE0_REQ; // 0軸イニシャライズモードへ変更

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド07
    追加(2025.6.9yori)

***********************************************************************/

int Grp01::Cmd07()
{
    int ret = 0;

    //WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE); // 一時的にコメントアウト、後で調査(2025.8.21yori)
    // アーム型式場合分け追加(2025.10.27yori)
    if (HwCtrl::m_hVecCnt.m_Sts.m_Model == "VAR800M" || HwCtrl::m_hVecCnt.m_Sts.m_Model == "VAR800L")
    {
        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE0_REQ; // 有接触から非接触へ切り替える // SCANNER_INIT_REQ→INITIALIZE0_REQへ変更(2025.9.2yori)
        HwCtrl::m_ScannerConnectBtnFg = true; // 接続完了ボタンが押された。(2025.9.2yori)
    }
    if(HwCtrl::m_hVecCnt.m_Sts.m_Model == "VAR700M" || HwCtrl::m_hVecCnt.m_Sts.m_Model == "VAR700L" || HwCtrl::m_hVecCnt.m_Sts.m_Model == "VAR600M") // VAR600M追加(2026.1.3yori)
    {
        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_INIT_ING;
    }

    //ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL); // 一時的にコメントアウト、後で調査(2025.8.21yori)

    return (ret);
}



/***********************************************************************

    コマンド08
    追加(2025.7.15yori)

***********************************************************************/

int Grp01::Cmd08()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE_CAN; // イニシャライズキャンセル(2025.10.28yori)

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド09
    追加(2025.7.18yori)

***********************************************************************/

int Grp01::Cmd09()
{
    int ret = 0;

    //WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE); // 一時的にコメントアウト、後で調査(2025.9.2yori)

    HwCtrl::m_ArmWarmUpMonitorFlag = true; // 暖機監視オン

    //ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL); // 一時的にコメントアウト、後で調査(2025.9.2yori)

    return (ret);
}



/***********************************************************************

    コマンド10
    追加(2025.7.18yori)

***********************************************************************/

int Grp01::Cmd10()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_ArmWarmUpMonitorFlag = false; // 暖機監視オフ

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド11
    追加(2025.7.25yori)

***********************************************************************/

int Grp01::Cmd11()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE0_CMP; // 0軸イニシャライズモード終了

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド12
    追加(2025.7.30yori)

***********************************************************************/

int Grp01::Cmd12()
{
    int ret = 0;

    //WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE); // 一時的にコメントアウト、後で調査(2025.9.2yori)

    HwCtrl::m_ScannerWarmUpMonitorFlag = true; // 暖機監視オフ

    //ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL); // 一時的にコメントアウト、後で調査(2025.9.2yori)

    return (ret);
}



/***********************************************************************

    コマンド13
    追加(2025.7.30yori)

***********************************************************************/

int Grp01::Cmd13()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_ScannerWarmUpMonitorFlag = false; // 暖機監視オン

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL); 

    return (ret);
}



/***********************************************************************

    コマンド14
    追加(2025.7.31yori)

***********************************************************************/

int Grp01::Cmd14()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_WARMUP_CMP; // アーム温度監視終了

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド15
    追加(2025.7.31yori)

***********************************************************************/

int Grp01::Cmd15()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_WARMUP_CMP; // スキャナ温度監視終了 // SCANNER_INIT_CMP→SCANNER_WARMUP_CMPへ変更(2025.8.22yori)

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド16
    追加(2025.8.12yori)

***********************************************************************/

int Grp01::Cmd16()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MODE_SW_REQ; // モード切替

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}


/***********************************************************************

    SensorConnectionPanelCancelButton
    追加(2025.10.28yori)

***********************************************************************/

int Grp01::SensorConnectionPanelCancelButton()
{
    int ret = 0;

    if (HwCtrl::m_b_Button_ConnectFlag == false)
    {
        UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Close); // SubWindow1を閉じる。

        if (HwCtrl::m_ScannerAlignmentProbeFlag == false)  // PolyWorksから接続し、通常測定の場合(2025.12.17yori)
        {
            HwCtrl::AppCommandSend(APP_SEND_CMD::SCANNER_CONNECT_CANCEL);// PolyWorks側にスキャナ接続キャンセルを知らせる。
                                                                         // →PolyWorks側からスキャナとアームの切断が通知される。
        }
        else // PolyWorksから接続し、非接触点検キャリブの場合(2025.12.17yori)
        {
            UsrMsg::CallBack(UsrMsg::WM_MainWnd_Btn02); // 有接触設定メニュー表示
            UsrMsg::CallBack(UsrMsg::WM_ScannerAlignmentPanel_Show); // アライメント画面表示
            UsrMsg::CallBack(UsrMsg::WM_ScannerAlignmentPanel_Setup); // アライメント画面の初期設定
            HwCtrl::m_ScannerAlignmentProbeFlag = false;
        }
    }
    else // アプリから接続した場合、キャンセルボタンでスキャナ切断処理を行う。(2025.12.18yori)
    {
        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_DISCONNECT_REQ; // スキャナ切断処理
        while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::SCANNER_DISCONNECT_REQ) // スキャナ切断処理状態になるまで待機
        {
            Sleep(100);
        }
        while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::SCANNER_DISCONNECT_CMP) // スキャナ切断処理完了状態になるまで待機
        {
            Sleep(100);
        }
    }

    return (ret);
}