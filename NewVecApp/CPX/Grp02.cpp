/***********************************************************************

    SubWinow2のコールバッククラス

***********************************************************************/

#include "Grp02.h"
#include "UsrMsg.h" // "ErrMsg.h"→"UsrMsg.h"へ変更(2025.6.11yori)
//#include "ErrMsg.h"
#include "CalibComm.h"
#include "CalibSetting.h"



/***********************************************************************

    コマンド01

***********************************************************************/

int Grp02::Cmd01()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_SET_REQ; // プローブ情報要求(2025.6.11) // アーム設定要求(共通シーケンスへ変更)(2025.9.1)

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド02

***********************************************************************/

int Grp02::Cmd02()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ALIGNMENT_REQ; // 始業前点検(2025.6.11) 2025.8.27 mod eba

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);

    //if ( ErrMsg::CallBack != NULL ) {
    //    ErrMsg::CallBack( ErrMsg::ERR_HELLO );
    //}

    //return( 0 );
}



/***********************************************************************

    コマンド03

***********************************************************************/

int Grp02::Cmd03()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_MAKE_MATRIX_REQ; // 非接触点検キャリブ座標系作成(2025.12.2)
    HwCtrl::m_Type = int(CALIB_TYPE::SCANNER_MAKE_MATRIX);
    HwCtrl::m_ScannerAlignmentProbeFlag = true; // 追加(2025.12.17yori)
    HwCtrl::Func50(2,6); // ID=2,DIA=6へ強制変更(2026.1.1yori)

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド04

***********************************************************************/

int Grp02::Cmd04()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_SELFCHECK_REQ; // 有接触自己診断(2025.6.11)

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド05

***********************************************************************/

int Grp02::Cmd05()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_SET_REQ2; // アーム設定要求(2025.10.31)

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド06

***********************************************************************/

int Grp02::Cmd06()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_SET_REQ; // アーム設定要求(2025.6.11)

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド07
    追加(2025.7.18yori)
    引数追加(2025.9.8yori)

***********************************************************************/

int Grp02::Cmd07(int id, double dia)
{
    int ret = 0;

    ret = HwCtrl::Func50(id, dia); // プローブ設定画面から取得したプローブ情報をアームへ送る。(2025.9.1yori)

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE; // PROBE_SET_CMP→MEAS_IDLEへ変更(2025.9.1yori)

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド08
    追加(2025.8.9yori)

***********************************************************************/

int Grp02::Cmd08(int gaugetype)
{
    int ret = 0;

    HwCtrl::Func57(gaugetype); // ゲージ選択番号設定

    return (ret);
}



/***********************************************************************

    コマンド09
    追加(2025.8.16yori)

***********************************************************************/

int Grp02::Cmd09()
{
    int ret = 0;

    ret = HwCtrl::Func73(); // アームネットワーク設定(2025.8.28yori)

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    if(ret == 0) HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE; // 有接触測定待ち

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}




/***********************************************************************

    コマンド10
    追加(2025.8.31yori)

***********************************************************************/

int Grp02::Cmd10(const TCHAR* armtype)
{
    int ret = 0;

    ret = HwCtrl::Func74(armtype); // アーム型式設定(2025.9.1yori)

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    if (ret == 0) HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE; // 有接触測定待ち

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド11
    追加(2025.9.1ori)

***********************************************************************/

int Grp02::Cmd11()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE; // 有接触測定待ち

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    HwCtrl::AppCommandSend(APP_SEND_CMD::MENU_CLOSED); // 有接触設定メニューが閉じられたことをPolyWorks側に知らせる。

    return (ret);
}



/***********************************************************************

    コマンド12
    追加(2025.10.6yori)

***********************************************************************/

int Grp02::Cmd12()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_MaintModeFlag = true; // メンテナンスモードへ変更

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    コマンド13
    追加(2025.10.6yori)

***********************************************************************/

int Grp02::Cmd13()
{
    int ret = 0;

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    HwCtrl::m_MaintModeFlag = false; // 有接触モードへ変更

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    ContactSelfJudgmentPanelSavePara
    追加(2025.10.8yori)

***********************************************************************/

int Grp02::ContactSelfJudgmentPanelSavePara(const TCHAR* path)
{
    int ret = 0;

    HwCtrl::SavePara(path);

    return (ret);
}



/***********************************************************************

    ContactSelfJudgmentPanelRestorePara
    追加(2025.10.9yori)

***********************************************************************/

int Grp02::ContactSelfJudgmentPanelRestorePara(const TCHAR* path)
{
    int ret = 0;

    HwCtrl::RestorePara(path);

    return (ret);
}



/***********************************************************************

    ProbeInputPanelProbeResist
    追加(2025.10.31yori)

***********************************************************************/

int Grp02::ProbeInputPanelProbeResist(int id, const TCHAR* probename, int probetype)
{
    int ret = 0;

    HwCtrl::ProbeResit(id, probename, probetype);

    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

    if (ret == 0) HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE; // 有接触測定待ち

    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    return (ret);
}



/***********************************************************************

    ContactInspectionPanelInit
    2025.8.26 add eba

***********************************************************************/

int Grp02::ContactInspectionPanelInit(CALIB_MSEBOX* para, TCHAR*& path, int p_count, TCHAR*& mes, int m_count)
{
    int ret = 0;

    CalibComm::Init(para, path, p_count, mes, m_count);

    return (ret);
}



/***********************************************************************

    ContactInspectionPanelClickStart
    2025.8.26 add eba

***********************************************************************/

int Grp02::ContactInspectionPanelClickStart(CALIB_MSEBOX* para)
{
    int ret = 0;

    CalibComm::Start(para);

    return (ret);
}



/***********************************************************************

    ContactInspectionPanelClickBack
    2025.8.26 add eba

***********************************************************************/

int Grp02::ContactInspectionPanelClickBack(CALIB_MSEBOX* para)
{
    int ret = 0;

    CalibComm::Back(para);

    return (ret);
}



/***********************************************************************

    ContactInspectionPanelClickBack
    2025.8.26 add eba

***********************************************************************/

int Grp02::ContactInspectionPanelClickReStart(CALIB_MSEBOX* para)
{
    int ret = 0;

    CalibComm::ReStart(para);

    return (ret);
}


/***********************************************************************

    ContactInspectionPanelTerminate
    2025.8.26 add eba

***********************************************************************/

int Grp02::ContactInspectionPanelTerminate(CALIB_MSEBOX* para)
{
    int ret = 0;

    CalibComm::Close(para);

    return (ret);
}



/***********************************************************************

    ContactInspectionPanelMesCallBack
    2025.8.26 add eba

***********************************************************************/

int Grp02::ContactInspectionPanelMesCallBack(CALIB_MSEBOX* para)
{
    int ret = 0;

    CalibComm::CntDataMesCallBack(para);

    return (ret);
}



/***********************************************************************

    ContactInspectionPanelClickReStore
    2025.10.17 add eba

***********************************************************************/

int Grp02::ContactInspectionPanelClickReStore(CALIB_MSEBOX* para)
{
    int ret = 0;

    CalibComm::ClickResoreBtn(para);

    return (ret);
}


/***********************************************************************

    ContactInspectionPanelParaOutCallBack
    2025.8.26 add eba

***********************************************************************/

int Grp02::ContactInspectionPanelParaOutCallBack(CALIB_MSEBOX* para)
{
    int ret = 0;

    CalibComm::ParaOutCallBack(para);

    return (ret);
}



/***********************************************************************

    ContactInspectionPanelGetPath
    2025.8.26 add eba

***********************************************************************/

int Grp02::ContactInspectionPanelGetPath(TCHAR*& path, int count)
{
    int ret = 0;

    CalibComm::GetDrawPath(path, count);

    return (ret);
}



/***********************************************************************

    ContactInspectionPanelGetPath
    2025.8.26 add eba

***********************************************************************/

int Grp02::ContactInspectionPanelGetMes(TCHAR*& mes, int count)
{
    int ret = 0;

    CalibComm::GetMesString(mes, count);

    return (ret);
}



/***********************************************************************

    SettingPanelInit
    2025.9.24 add eba

***********************************************************************/

int Grp02::SettingPanelInit(CALIB_MSEBOX* para)
{
    int ret = 0;

    CalibSetting::Init(para);

    return (ret);
}



/***********************************************************************

    SettingPanelInit
    2025.9.24 add eba

***********************************************************************/

int Grp02::SettingPanelOkBtn(CALIB_MSEBOX* para)
{
    int ret = 0;

    CalibSetting::OkBtn(para);

    return (ret);
}



/***********************************************************************

    SettingPanelInit
    2025.9.24 add eba

***********************************************************************/

int Grp02::SettingPanelCancelBtn(CALIB_MSEBOX* para)
{
    int ret = 0;

    CalibSetting::CancelBtn(para);

    return (ret);
}



/***********************************************************************

    ScannerAlignmentPanelInit
    2025.12.3yori

***********************************************************************/

int Grp02::ScannerAlignmentPanelInit(CALIB_SCANNER_MSEBOX* para, TCHAR*& path, int p_count, TCHAR*& mes, int m_count)
{
    int ret = 0;

    CalibComm::InitScanner(para, path, p_count, mes, m_count);

    return (ret);
}



/***********************************************************************

    ScannerAlignmentPanelMesCallBack
    2025.12.3yori

***********************************************************************/

int Grp02::ScannerAlignmentPanelMesCallBack(CALIB_SCANNER_MSEBOX* para)
{
    int ret = 0;

    CalibComm::ScanDataMesCallBack(para);

    return (ret);
}



/***********************************************************************

    ScannerAlignmentPanelClickBack
    2025.12.12yori

***********************************************************************/

int Grp02::ScannerAlignmentPanelClickBack(CALIB_SCANNER_MSEBOX* para)
{
    int ret = 0;

    CalibComm::BackScanner(para);

    return (ret);
}



/***********************************************************************

    ScannerAlignmentPanelClickBack
    2025.12.12yori

***********************************************************************/

int Grp02::ScannerAlignmentPanelClickReStart(CALIB_SCANNER_MSEBOX* para)
{
    int ret = 0;

    CalibComm::ReStartScanner(para);

    return (ret);
}



/***********************************************************************

    ScannerAlignmentPanelTerminate
    2025.12.4yori

***********************************************************************/

int Grp02::ScannerAlignmentPanelTerminate()
{
    int ret = 0;

    CalibComm::CloseScanner();

    return (ret);
}



/***********************************************************************

    ScannerAlignmentPanelResultCallBack
    2025.12.9yori

***********************************************************************/

int Grp02::ScannerAlignmentPanelResultCallBack(CALIB_SCANNER_MSEBOX* para)
{
    int ret = 0;

    CalibComm::ScannerAlignmentPanelResultCallBack(para);

    return (ret);
}