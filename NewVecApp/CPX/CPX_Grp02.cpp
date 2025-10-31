/***********************************************************************

    C++ DLL からエクスポートする関数群
    これらの関数を呼び出すC#ラッパー関数を別に作成する

***********************************************************************/

#include "common.h"
#include "CPX.h"
#include "Grp02.h"



/***********************************************************************

    Cmd01

***********************************************************************/

int WINAPI CPX_Grp02_Cmd01()
{
    int     rc;
    
    rc = Grp02::Cmd01();

    return( rc );
}



/***********************************************************************

    Cmd02

***********************************************************************/

int WINAPI CPX_Grp02_Cmd02()
{
    int     rc;
    
    rc = Grp02::Cmd02();

    return( rc );
}



/***********************************************************************

    Cmd03

***********************************************************************/

int WINAPI CPX_Grp02_Cmd03()
{
    int     rc;
    
    rc = Grp02::Cmd03();

    return( rc );
}



/***********************************************************************

    Cmd04

***********************************************************************/

int WINAPI CPX_Grp02_Cmd04()
{
    int     rc;

    rc = Grp02::Cmd04();

    return(rc);
}



/***********************************************************************

    Cmd05

***********************************************************************/

int WINAPI CPX_Grp02_Cmd05()
{
    int     rc;

    rc = Grp02::Cmd05();

    return(rc);
}



/***********************************************************************

    Cmd06

***********************************************************************/

int WINAPI CPX_Grp02_Cmd06()
{
    int     rc;

    rc = Grp02::Cmd06();

    return(rc);
}



/***********************************************************************

    Cmd07
    追加(2025.7.17yori)
    引数追加(2025.9.8yori)

***********************************************************************/

int WINAPI CPX_Grp02_Cmd07(int id, double dia)
{
    int     rc;

    rc = Grp02::Cmd07(id, dia);

    return(rc);
}



/***********************************************************************

    Cmd08
    追加(2025.8.9yori)

***********************************************************************/

int WINAPI CPX_Grp02_Cmd08(int gaugetype)
{
    int     rc;

    rc = Grp02::Cmd08(gaugetype);

    return(rc);
}



/***********************************************************************

    Cmd09
    追加(2025.8.16yori)

***********************************************************************/

int WINAPI CPX_Grp02_Cmd09()
{
    int     rc;

    rc = Grp02::Cmd09();

    return(rc);
}



/***********************************************************************

    Cmd10
    追加(2025.9.1yori)

***********************************************************************/

int WINAPI CPX_Grp02_Cmd10(const TCHAR* armtype)
{
    int     rc;

    rc = Grp02::Cmd10(armtype);

    return(rc);
}



/***********************************************************************

    Cmd11
    追加(2025.9.1yori)

***********************************************************************/

int WINAPI CPX_Grp02_Cmd11()
{
    int     rc;

    rc = Grp02::Cmd11();

    return(rc);
}



/***********************************************************************

    Cmd12
    追加(2025.10.6yori)

***********************************************************************/

int WINAPI CPX_Grp02_Cmd12()
{
    int     rc;

    rc = Grp02::Cmd12();

    return(rc);
}



/***********************************************************************

    Cmd13
    追加(2025.10.6yori)

***********************************************************************/

int WINAPI CPX_Grp02_Cmd13()
{
    int     rc;

    rc = Grp02::Cmd13();

    return(rc);
}



/***********************************************************************

    ContactSelfJudgmentPanelSavePara
    追加(2025.10.8yori)

***********************************************************************/

int WINAPI CPX_Grp02_ContactSelfJudgmentPanelSavePara(const TCHAR* path)
{
    int     rc;

    rc = Grp02::ContactSelfJudgmentPanelSavePara(path);

    return(rc);
}



/***********************************************************************

    ContactSelfJudgmentPanelRestorePara
    追加(2025.10.8yori)

***********************************************************************/

int WINAPI CPX_Grp02_ContactSelfJudgmentPanelRestorePara(const TCHAR* path)
{
    int     rc;

    rc = Grp02::ContactSelfJudgmentPanelRestorePara(path);

    return(rc);
}



/***********************************************************************

    CPX_Grp02_ProbeInputPanelProbeResist
    追加(2025.10.31yori)

***********************************************************************/

int WINAPI CPX_Grp02_ProbeInputPanelProbeResist(int id, const TCHAR* probename, int probetype)
{
    int     rc;

    rc = Grp02::ProbeInputPanelProbeResist(id, probename, probetype);

    return(rc);
}



/***********************************************************************

    CPX_Grp02_ContactInspectionPanelInit
    2025.8.26 add eba

***********************************************************************/

int WINAPI CPX_Grp02_ContactInspectionPanelInit(CALIB_MSEBOX* para, TCHAR*& path, int p_count, TCHAR*& mes, int m_count)
{
    int     rc;

    rc = Grp02::ContactInspectionPanelInit(para, path, p_count, mes, m_count);

    return(rc);
}



/***********************************************************************

    CPX_Grp02_ContactInspectionPanelClickStart
    2025.8.26 add eba

***********************************************************************/

int WINAPI CPX_Grp02_ContactInspectionPanelClickStart(CALIB_MSEBOX* para)
{
    int     rc;

    rc = Grp02::ContactInspectionPanelClickStart(para);

    return(rc);
}



/***********************************************************************

    CPX_Grp02_ContactInspectionPanelClickBack
    2025.8.26 add eba

***********************************************************************/

int WINAPI CPX_Grp02_ContactInspectionPanelClickBack(CALIB_MSEBOX* para)
{
    int     rc;

    rc = Grp02::ContactInspectionPanelClickBack(para);

    return(rc);
}



/***********************************************************************

    CPX_Grp02_ContactInspectionPanelClickReStart
    2025.8.26 add eba

***********************************************************************/

int WINAPI CPX_Grp02_ContactInspectionPanelClickReStart(CALIB_MSEBOX* para)
{
    int     rc;

    rc = Grp02::ContactInspectionPanelClickReStart(para);

    return(rc);
}


/***********************************************************************

    CPX_Grp02_ContactInspectionPanelMesCallBack
    2025.8.28 add eba

***********************************************************************/

int WINAPI CPX_Grp02_ContactInspectionPanelMesCallBack(CALIB_MSEBOX* para)
{
    int     rc;

    rc = Grp02::ContactInspectionPanelMesCallBack(para);

    return(rc);
}


/***********************************************************************

    CPX_Grp02_ContactInspectionPanelClickReStore
    2025.8.28 add eba

***********************************************************************/

int WINAPI CPX_Grp02_ContactInspectionPanelClickReStore(CALIB_MSEBOX* para)
{
    int     rc;

    rc = Grp02::ContactInspectionPanelClickReStore(para);

    return(rc);
}


/***********************************************************************

    CPX_Grp02_ContactInspectionPanelParaOutCallBack
    2025.8.28 add eba

***********************************************************************/

int WINAPI CPX_Grp02_ContactInspectionPanelParaOutCallBack(CALIB_MSEBOX* para)
{
    int     rc;

    rc = Grp02::ContactInspectionPanelParaOutCallBack(para);

    return(rc);
}


/***********************************************************************

    CPX_Grp02_ContactInspectionPanelTerminate
    2025.8.28 add eba

***********************************************************************/

int WINAPI CPX_Grp02_ContactInspectionPanelTerminate(CALIB_MSEBOX* para)
{
    int     rc;

    rc = Grp02::ContactInspectionPanelTerminate(para);

    return(rc);
}

/***********************************************************************

    CPX_Grp02_ContactInspectionPanelGetPath
    2025.9.1 add eba

***********************************************************************/

int WINAPI CPX_Grp02_ContactInspectionPanelGetPath(TCHAR*& path, int count)
{
    int     rc=0;

    return(rc);
}


/***********************************************************************

    CPX_Grp02_ContactInspectionPanelGetPath
    2025.9.1 add eba

***********************************************************************/

int WINAPI CPX_Grp02_ContactInspectionPanelGetMes(TCHAR*& mes, int count)
{
    int     rc=0;

    return(rc);
}


/***********************************************************************

    CPX_Grp02_SettingPanelInit
    2025.9.24 add eba

***********************************************************************/

int WINAPI CPX_Grp02_SettingPanelInit(CALIB_MSEBOX* para)
{
    int     rc;

    rc = Grp02::SettingPanelInit(para);

    return(rc);
}


/***********************************************************************

    CPX_Grp02_SettingPanelOkBtn
    2025.9.25 add eba

***********************************************************************/

int WINAPI CPX_Grp02_SettingPanelOkBtn(CALIB_MSEBOX* para)
{
    int     rc;

    rc = Grp02::SettingPanelOkBtn(para);

    return(rc);
}


/***********************************************************************

    CPX_Grp02_SettingPanelCancelBtn
    2025.9.25 add eba

***********************************************************************/

int WINAPI CPX_Grp02_SettingPanelCancelBtn(CALIB_MSEBOX* para)
{
    int     rc;

    rc = Grp02::SettingPanelCancelBtn(para);

    return(rc);
}
