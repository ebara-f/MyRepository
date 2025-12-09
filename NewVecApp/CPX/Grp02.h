/***********************************************************************

    コマンド群を束ねるクラス

***********************************************************************/

#pragma once
#include    "common.h"
#include    "CPX.h"
#include    "HwCtrl.h" // 追加(2025.6.11yori)



class Grp02
{
public:
    static int  Cmd01();
    static int  Cmd02();
    static int  Cmd03();
    static int  Cmd04(); // 追加(2025.6.11yori)
    static int  Cmd05(); // 追加(2025.6.11yori)
    static int  Cmd06(); // 追加(2025.6.11yori)
    static int  Cmd07(int id, double dia); // 追加(2025.7.18yori) // 引数追加(2025.9.8yori)
    static int  Cmd08(int gaugetype); // 追加(2025.8.9yori)
    static int  Cmd09(); // 追加(2025.8.16yori)
    static int  Cmd10(const TCHAR* armtype); // 追加(2025.8.31yori)
    static int  Cmd11(); // 追加(2025.9.1yori)
    static int  Cmd12(); // 追加(2025.10.6yori)
    static int  Cmd13(); // 追加(2025.10.6yori)
    static int  ContactSelfJudgmentPanelSavePara(const TCHAR* path); // 追加(2025.10.8yori)
    static int  ContactSelfJudgmentPanelRestorePara(const TCHAR* path); // 追加(2025.10.9yori)
    static int  ProbeInputPanelProbeResist(int id, const TCHAR* probename, int probetype); // 追加(2025.10.31yori)

    static int  ContactInspectionPanelInit(CALIB_MSEBOX* para, TCHAR*& path, int p_count, TCHAR*& mes, int m_count);  // 2025.8.26 add eba
    static int  ContactInspectionPanelClickStart(CALIB_MSEBOX* para);         // 2025.8.26 add eba
    static int  ContactInspectionPanelClickBack(CALIB_MSEBOX* para);          // 2025.8.26 add eba
    static int  ContactInspectionPanelClickReStart(CALIB_MSEBOX* para);     // 2025.8.26 add eba
    static int  ContactInspectionPanelTerminate(CALIB_MSEBOX* para);     // 2025.8.28 add eba
    static int  ContactInspectionPanelMesCallBack(CALIB_MSEBOX* para);    // 2025.9.2 add eba
    static int  ContactInspectionPanelParaOutCallBack(CALIB_MSEBOX* para);    // 2025.9.10 add eba
    static int  ContactInspectionPanelClickReStore(CALIB_MSEBOX* para); // 2025.10.17 add eba
    static int  ContactInspectionPanelGetPath(TCHAR*& path, int count);     // 2025.9.1 add eba
    static int  ContactInspectionPanelGetMes(TCHAR*& mes, int count);     // 2025.9.1 add eba

    static int  SettingPanelInit(CALIB_MSEBOX* para); // 2025.9.25 add eba
    static int  SettingPanelOkBtn(CALIB_MSEBOX* para); // 2025.9.25 add eba
    static int  SettingPanelCancelBtn(CALIB_MSEBOX* para); // 2025.9.25 add eba

    static int  ScannerAlignmentPanelMesCallBack(CALIB_SCANNER_MSEBOX* para); // 追加(2025.12.3yori)
    static int  ScannerAlignmentPanelInit(CALIB_SCANNER_MSEBOX* para, TCHAR*& path, int p_count, TCHAR*& mes, int m_count); // 追加(2025.12.4yori)
    static int  ScannerAlignmentPanelTerminate(); // 追加(2025.12.4yori)
    static int  ScannerAlignmentPanelResultCallBack(CALIB_SCANNER_MSEBOX* mes); // 追加(2025.12.9yori)
};
