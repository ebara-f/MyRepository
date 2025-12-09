/***********************************************************************

    C++ DLL からエクスポートする関数群
    これらの関数を呼び出すC#ラッパー関数を別途作成する

***********************************************************************/

#include "common.h"
#include "CPX.h"
#include "AppMain.h"



/***********************************************************************

    初期化処理

***********************************************************************/

int WINAPI CPX_AppMain_Init()
{
    int     rc;
    
    rc = AppMain::Init();

    return( rc );
}



/***********************************************************************

    終了処理

***********************************************************************/

int WINAPI CPX_AppMain_Term()
{
    int     rc;
    
    rc = AppMain::Term();

    return( rc );
}



int WINAPI CPX_AppMain_SubWnd01()
{
    int     rc;

    rc = AppMain::Grp01();

    return(rc);
}



int WINAPI CPX_AppMain_SubWnd02()
{
    int     rc;

    rc = AppMain::Grp02();

    return(rc);
}



int WINAPI CPX_AppMain_SubWnd03()
{
    int     rc;

    rc = AppMain::Grp03();

    return(rc);
}



int WINAPI CPX_AppMain_UpDateData01(STATUS01* sts)
{
    int     rc;

    rc = AppMain::UpDateData01(sts);

    return(rc);
}



// 追加(2025.6.19yori)
int WINAPI CPX_AppMain_UpDateData02(STATUS02* sts)
{
    int     rc;

    rc = AppMain::UpDateData02(sts);

    return(rc);
}



// 追加(2025.6.24yori)
int WINAPI CPX_AppMain_UpDateData03(STATUS03* sts)
{
    int     rc;

    rc = AppMain::UpDateData03(sts);

    return(rc);
}



// 追加(2025.7.31yori)
// 引数追加(2025.9.22yori)
int WINAPI CPX_AppMain_UpDateData04(THRESHOLD* th, int id)
{
    int     rc;

    rc = AppMain::UpDateData04(th, id);

    return(rc);
}



// 追加(2025.8.7yori)
int WINAPI CPX_AppMain_UpDateData05(GAUGE* ga)
{
    int     rc;

    rc = AppMain::UpDateData05(ga);

    return(rc);
}



// 追加(2025.10.3yori)
int WINAPI CPX_AppMain_UpDateData06(STATUS04* sts)
{
    int     rc;

    rc = AppMain::UpDateData06(sts);

    return(rc);
}



// 追加(2025.10.6yori)
int WINAPI CPX_AppMain_CountCheck(STATUS04* sts)
{
    int     rc;

    rc = AppMain::CountCheck(sts);

    return(rc);
}



// 追加(2025.7.18yori)
int WINAPI CPX_AppMain_UpDateData01_Write(STATUS01* sts)
{
    int     rc;

    rc = AppMain::UpDateData01_Write(sts);

    return(rc);
}



// 追加(2025.8.25yori)
int WINAPI CPX_AppMain_UpDateData02_Write(STATUS02* sts)
{
    int     rc;

    rc = AppMain::UpDateData02_Write(sts);

    return(rc);
}



// 追加(2025.8.1yori)
// 引数追加(2025.9.22yori)
int WINAPI CPX_AppMain_UpDateData04_Write(THRESHOLD* th, int id)
{
    int     rc;

    rc = AppMain::UpDateData04_Write(th, id);

    return(rc);
}



// 追加(2025.8.9yori)
int WINAPI CPX_AppMain_UpDateData05_Write(GAUGE* ga)
{
    int     rc;

    rc = AppMain::UpDateData05_Write(ga);

    return(rc);
}



// 追加(2025.8.1yori)
// 引数追加(2025.9.22yori)
int WINAPI CPX_AppMain_UpDateData04_Default(THRESHOLD* th, int id)
{
    int     rc;

    rc = AppMain::UpDateData04_Default(th, id);

    return(rc);
}



// 追加(2025.8.9yori)
int WINAPI CPX_AppMain_UpDateData05_Default(GAUGE* ga)
{
    int     rc;

    rc = AppMain::UpDateData05_Default(ga);

    return(rc);
}



// 追加(2025.8.9yori)
int WINAPI CPX_AppMain_MesCallBack()
{
    int     rc;

    rc = AppMain::ContactInspectionPanelMesCallBack();

    return(rc);
}