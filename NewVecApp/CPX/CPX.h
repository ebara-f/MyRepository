/***********************************************************************

    C++ DLL からエクスポートする関数群
    これらの関数を呼び出すC#ラッパー関数を別途作成する

***********************************************************************/

#pragma once

#define WIN32_LEAN_AND_MEAN  // Windows ヘッダーからほとんど使用されていない部分を除外
// Windows ヘッダー ファイル
#include <windows.h>
#include <tchar.h>
 //// 追加(2025.5.15yori)
//#include "VecCnt.h"
//#include "common.h"
#include "Error_Defin.h"
////

//#include "AppMain.h"

#ifdef CPX_EXPORTS
#define CPX_DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"{
#endif

typedef void (*ER_CBFUNC)( int );
typedef void (*SM_CBFUNC)( int );

// ステータス更新用の構造体
// 有接触ステータス更新用の構造体(2025.9.1yori)
typedef struct Status01
{
    int mode;
    int connect_fg;
    int warm_fg;
    int init_fg;
    int init_sts[7]; // 追加(2025.7.11yori)
    int no0_fg; // 0軸有無(2025.7.15yori)
    int probe_id; // プローブID(2025.6.11yori)
    double dia; // スタイラス直径(2025.6.11yori)
    double dia_meas; // スタイラス直径(2025.7.17yori)
    char probe_name[21][32]; // プローブ名称(2025.7.24yori) // wchar_t→charへ変更(2025.8.28yori)
    double stylus_angle[21]; // スタイラス角度(2025.7.31yori)
    int probe_type[21]; // プローブ種類(2025.10.31yori)
    double tempature[7]; // アーム内温度(2025.6.4yori)
    double cal_tempature[7]; // キャリブ温度(2025.6.18yori)
    char arm_model[16]; // アーム型式(2025.6.16yori)
    char address[4][8]; // IPアドレス(2025.6.18yori) // 4つに分割(2025.8.15yori)
    char subnet[4][8]; // サブネットマスク(2025.6.18yori) // 4つに分割(2025.8.15yori)
    char port[4]; // サブネットマスク(2025.6.18yori)

} STATUS01;

// 有接触自己診断用の構造体(2025.9.1yori)
typedef struct Status04
{
    unsigned int btn; // ボタンの状態
    char firm_ver[32]; // アーム型式
    int comm_check[9]; // 通信チェック
    char cnt_ver[32]; // カウンタバージョン
    long long cnt_data[9]; // カウント値
    int  count_fg; // カウント値取得フラグ(2025.10.30yori)

} STATUS04;

// 非接触ステータス更新用の構造体(2025.6.18yori)
typedef struct Status02
{
    char mode_info[6][32]; // 計測モード詳細(2025.8.10yori)、wchar_t→charへ変更(2025.8.14yori)
    int mode; // 計測モード(2025.6.20yori)
    double pitch[10]; // 点間ピッチ間引き(2025.8.11yori)
    int sens_use[5]; // 感度の有効無効(2025.6.23yori)
    char sens_name[5][50]; // 感度名称(2025.6.23yori)
    int	dist_use[6][3][2]; // 距離マスク使用の有無(1=使用する/0=使用しない)(2025.6.20yori)
    double dist_data[6][3][2]; // 距離マスク設定値(2025.6.20yori)
    unsigned short brightslice[5]; // 輝度スライス(2025.6.20yori)
    unsigned short sens_slice[5]; // 感度スライス(2025.6.20yori)
    int power; // ガイドレーザーパワー(2025.6.23yori)
    int xpitch_onoff; // 補間(2025.6.23yori)
    double angle; // 角度マスク(2025.6.23yori)
    int two_peak; // 2ピークマスク(2025.6.23yori)
    int edge; // エッジマスク(2025.6.23yori)
    int edge_default[3][6]; // エッジマスク初期値(2025.8.27yori)
    char address[4][8]; // 4つに分割(2025.8.17yori)
    char subnet[4][8]; // 4つに分割(2025.8.17yori)
    char gateway[4][8]; // 4つに分割(2025.8.17yori)
    char dns[4][8]; // 4つに分割(2025.8.17yori)

} STATUS02;

// 非接触自己診断用の構造体(2025.6.24yori)
typedef struct Status03
{
    // 感度チェック(2025.7.2yori)
    int isensresult;
    int ibasebright;
    int iresultbright;
    double dthreshold;
    // 非接触自己診断のSWチェック(2025.6.24yori)
    int sw[2];
    // ラッチ通信チェック(2025.6.24yori)
    int ilatchresult;
    int isendlatchcount;
    int irecvlatchcount;
    // ポインタ位置チェック(2025.7.4yori)
    double avedit;
    // モーターチェック(2025.6.24yori)
    int imotorresult;
    int isensorplus;
    int icontrollerplus;
    int isensorminus;
    int icontrollerminus;
    int ibasemove;
    int isensormoveplus;
    int icontrollermoveplus;
    int isensormoveminus;
    int icontrollermoveminus;

} STATUS03;

// しきい値の構造体(2025.8.1yori)
typedef struct Threshold
{
    double pp;
    double sigma2;
    double plate;
    double pitch;
    double maxmin;

    double pp_probe[20];
    double sigma2_probe[20];
    double plate_probe[20];
    double ri_probe[20];
    double ps_probe[20];

    double dst_max;
    double dst_min;
    double height_max;
    double height_min;
    double error_max;

} THRESHOLD;

// ゲージ設定の構造体(2025.8.7yori)
typedef struct Gauge
{
    char GageType[16];

    double Center_ScopePnt[3];
    double Plane_ScopePnt[4][3];
    double Plane_ScopeRad;
    double Length_ScopeRad;
    int Length_ScopeRad_Cnt;
    double Center_Limit;
    double Plane_Limit;
    double Length_Limit;
    double Only_Ball_Center_Limit; // 球ゲージのみで非接触始業前点検を実施するときの許容値(2025.8.9yori)
    int Plane_MeasPnt_Limit;
    int Length_MeasPnt_Limit;
    int Kido_Base;
    double Kido_Limit;

    double Center_ScopeRad;
    double Length_ScopePnt[4][3];

} GAUGE;


// プローブ点検判定フラグ
typedef struct
{
    int pp[4];
    int sigma2[4];
    int plate;
    int ld;
    int pf;
    int ps;
    int ri;
    int pl;
    int psi;

} CALIB_JUDGE_FG;

// 始業前点検判定フラグ
typedef struct
{
    int pp[4];
    int sigma2[4];
    int plate;
    int pitch;
    int maxmin;

} CALIB_JUDGE_CK_FG;


// キャリブデータの位置、ボールから離れたかのチェックを知らせるフラグ 2025.9.24 add eba
typedef struct
{
    int user_pos_err;
    int user_ball_err;

    
} CALIB_POS_ERR_FG;


// キャリブレーション関連のデータ受け渡し要構造体 2025.9.3 eba
typedef struct CalibSettingParamter
{
    CALIB_GAUGE     GaugePara;

    CALIB_RESULT    InspAndProbCkResult;   // 始業前とプローブ点検両方の結果が入る(2025.9.22 memo eba)
    CALIB_RESULT    InspAndProbCkResult2;   // 定数変更後の点検結果を入れる 2025.10.17 add eba
    CALIB_JUDGE     ProbeCheckThreshold;
    CALIB_JUDGE_CK  InspectionThreshold;
    CALIB_JUDGE_FG      ProbeCheckResultFg;
    CALIB_JUDGE_CK_FG  InspectionResultFg;

    double PlateErrVal;
    int CalibInspectJudge;  // 結果が改善したか、もしくはしきい値以内か否か
    int CalibResultJudge;   // 収束したか否か  
    int CalibResultVal;

    int Language;
    int CalibType;
    int CalibProbeId;
    int CalibProbeBranch;

    TCHAR   path[256];
    TCHAR   mes[512];

    int MesString;  // 2025.9.21 add eba 仮

} CALIB_MSEBOX;


CPX_DECLSPEC void WINAPI CPX_ErrMsg_SetCB( ER_CBFUNC );
CPX_DECLSPEC int  WINAPI CPX_ErrMsg_GetMsg( int, TCHAR*&, int );

CPX_DECLSPEC void WINAPI CPX_UsrMsg_SetCB( SM_CBFUNC );

CPX_DECLSPEC int  WINAPI CPX_AppMain_Init();
CPX_DECLSPEC int  WINAPI CPX_AppMain_Term();
CPX_DECLSPEC int  WINAPI CPX_AppMain_SubWnd01();        // 2025.4.24 eba add
CPX_DECLSPEC int  WINAPI CPX_AppMain_SubWnd02();        // 2025.4.24 eba add
CPX_DECLSPEC int  WINAPI CPX_AppMain_SubWnd03();        // 2025.4.24 eba add
CPX_DECLSPEC int  WINAPI CPX_AppMain_UpDateData01(STATUS01*);    // 2025.5.28 eba add
CPX_DECLSPEC int  WINAPI CPX_AppMain_UpDateData02(STATUS02*);    // 2025.6.19 yori
CPX_DECLSPEC int  WINAPI CPX_AppMain_UpDateData03(STATUS03*);    // 2025.6.24 yori
CPX_DECLSPEC int  WINAPI CPX_AppMain_UpDateData04(THRESHOLD*, int); // 2025.7.31 yori // int追加(2025.9.22yori)
CPX_DECLSPEC int  WINAPI CPX_AppMain_UpDateData05(GAUGE*);    // 2025.8.7 yori
CPX_DECLSPEC int  WINAPI CPX_AppMain_UpDateData06(STATUS04*); // 追加(2025.10.3yori)
CPX_DECLSPEC int  WINAPI CPX_AppMain_CountCheck(STATUS04*); // 追加(2025.10.6yori)
CPX_DECLSPEC int  WINAPI CPX_AppMain_UpDateData01_Write(STATUS01*); // 2025.7.18 yori
CPX_DECLSPEC int  WINAPI CPX_AppMain_UpDateData02_Write(STATUS02*); // 2025.8.25 yori
CPX_DECLSPEC int  WINAPI CPX_AppMain_UpDateData04_Write(THRESHOLD*, int); // 2025.8.1 yori // int追加(2025.9.22yori)
CPX_DECLSPEC int  WINAPI CPX_AppMain_UpDateData05_Write(GAUGE*); // 2025.8.9 yori
CPX_DECLSPEC int  WINAPI CPX_AppMain_UpDateData04_Default(THRESHOLD*, int); // 2025.8.1 yori // int追加(2025.9.22yori)
CPX_DECLSPEC int  WINAPI CPX_AppMain_UpDateData05_Default(GAUGE*); // 2025.8.1 yori
CPX_DECLSPEC int  WINAPI CPX_AppMain_MesCallBack(); // 2025.9.2 add eba

CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd01();
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd02( int, double, const TCHAR* );
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd03( int, double, const TCHAR*, int*, double*, TCHAR*&, int );
CPX_DECLSPEC int  WINAPI CPX_Grp01_CmdXX(double* , TCHAR*& , int );  // 2025.5.22 add eba test
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd04(); // 追加(2025.6.9yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd05(); // 追加(2025.6.9yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd06(); // 追加(2025.6.9yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd07(); // 追加(2025.6.9yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd08(); // 追加(2025.7.15yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd09(); // 追加(2025.7.18yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd10(); // 追加(2025.7.18yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd11(); // 追加(2025.7.25yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd12(); // 追加(2025.7.30yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd13(); // 追加(2025.7.30yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd14(); // 追加(2025.7.31yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd15(); // 追加(2025.7.31yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_Cmd16(); // 追加(2025.8.12yori)
CPX_DECLSPEC int  WINAPI CPX_Grp01_SensorConnectionPanelCancelButton(); // 追加(2025.10.28yori)

CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd01();
CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd02();
CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd03();
CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd04(); // 追加(2025.6.11yori)
CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd05(); // 追加(2025.6.11yori)
CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd06(); // 追加(2025.6.11yori)
CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd07(int id, double dia); // 追加(2025.7.18yori) // 引数追加(2025.9.8yori)
CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd08(int); // 追加(2025.8.9yori)
CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd09(); // 追加(2025.8.16yori)
CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd10(const TCHAR*); // 追加(2025.9.1yori)
CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd11(); // 追加(2025.9.1yori)
CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd12(); // 追加(2025.10.6yori)
CPX_DECLSPEC int  WINAPI CPX_Grp02_Cmd13(); // 追加(2025.10.6yori)
CPX_DECLSPEC int  WINAPI CPX_Grp02_ContactSelfJudgmentPanelSavePara(const TCHAR*); // 追加(2025.10.8yori)
CPX_DECLSPEC int  WINAPI CPX_Grp02_ContactSelfJudgmentPanelRestorePara(const TCHAR*); // 追加(2025.10.9yori)
CPX_DECLSPEC int  WINAPI CPX_Grp02_ProbeInputPanelProbeResist(int id, const TCHAR* probename, int probetype); // 追加(2025.10.31yori)

CPX_DECLSPEC int  WINAPI CPX_Grp02_ContactInspectionPanelInit(CALIB_MSEBOX* para, TCHAR*& path, int p_count, TCHAR*& mes, int m_count);
CPX_DECLSPEC int  WINAPI CPX_Grp02_ContactInspectionPanelClickStart(CALIB_MSEBOX* para);
CPX_DECLSPEC int  WINAPI CPX_Grp02_ContactInspectionPanelClickBack(CALIB_MSEBOX* para);
CPX_DECLSPEC int  WINAPI CPX_Grp02_ContactInspectionPanelClickReStart(CALIB_MSEBOX* para);
CPX_DECLSPEC int  WINAPI CPX_Grp02_ContactInspectionPanelTerminate(CALIB_MSEBOX* par);
CPX_DECLSPEC int  WINAPI CPX_Grp02_ContactInspectionPanelMesCallBack(CALIB_MSEBOX* para);
CPX_DECLSPEC int  WINAPI CPX_Grp02_ContactInspectionPanelClickReStore(CALIB_MSEBOX* para);
CPX_DECLSPEC int  WINAPI CPX_Grp02_ContactInspectionPanelParaOutCallBack(CALIB_MSEBOX* para);
CPX_DECLSPEC int  WINAPI CPX_Grp02_ContactInspectionPanelGetPath(TCHAR*&, int);
CPX_DECLSPEC int  WINAPI CPX_Grp02_ContactInspectionPanelGetMes(TCHAR*&, int);

CPX_DECLSPEC int  WINAPI CPX_Grp02_SettingPanelInit(CALIB_MSEBOX* para);
CPX_DECLSPEC int  WINAPI CPX_Grp02_SettingPanelOkBtn(CALIB_MSEBOX* para);
CPX_DECLSPEC int  WINAPI CPX_Grp02_SettingPanelCancelBtn(CALIB_MSEBOX* para);


CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd01(); // 追加(2025.6.24yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd02(); // 追加(2025.6.24yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd03(); // 追加(2025.6.24yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd04(); // 追加(2025.7.3yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd05(); // 追加(2025.8.11yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd06(int); // 追加(2025.8.12yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd07(int); // 追加(2025.8.21yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd08(int); // 追加(2025.8.21yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd09(int); // 追加(2025.8.21yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd10(); // 追加(2025.8.25yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd11(); // 追加(2025.8.25yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd12(); // 追加(2025.8.25yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd13(); // 追加(2025.8.25yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd14(int); // 追加(2025.8.25yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd15(); // 追加(2025.8.25yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd16(); // 追加(2025.8.27yori)
CPX_DECLSPEC int  WINAPI CPX_Grp03_Cmd17(); // 追加(2025.8.27yori)

#ifdef __cplusplus
}
#endif