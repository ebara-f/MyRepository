/***********************************************************************

    アプリのメイン処理を担うクラス

***********************************************************************/

#include <thread>
#include "AppMain.h"
//// 下記へ変更(2025.4.30)
// #include "LplQue.h"を削除
// 追加のインクルードディレクトリ(C/C++)「.;..\..\NewLplQue;%(AdditionalIncludeDirectories)」を削除
// 追加のライブラリディレクトリ(Debug、リンカー)「..\..\NewLplQue\lib64_dbg\$(PlatformToolset)\;%(AdditionalLibraryDirectories)」を削除
// 追加のライブラリディレクトリ(Release、リンカー)「..\..\NewLplQue\lib64\$(PlatformToolset)\;%(AdditionalLibraryDirectories)」を削除
// 追加の依存ファイルからLplQue.lib削除
// ビルド後のイベントの変更前
// xcopy /D /Y /I $(OutDir)$(TargetName).dll ..\_exec\$(Configuration)\
// xcopy /D /Y /I ..\..\NewLplQue\lib64_dbg\$(PlatformToolset)\LplQue.dll ..\_exec\$(Configuration)\
// xcopy /D /Y /I $(OutDir)$(TargetName).dll ..\_exec\$(Configuration)\
// xcopy /D /Y /I ..\..\NewLplQue\lib64\$(PlatformToolset)\LplQue.dll ..\_exec\$(Configuration)\
// ビルド後のイベントの変更後
// xcopy /D /Y /I $(OutDir)$(TargetName).dll ..\_exec\$(Configuration)\
// xcopy /D /Y /I ..\..\LplQue\Lib64_dbg\LplQue.dll ..\_exec\$(Configuration)\
// xcopy /D /Y /I $(OutDir)$(TargetName).dll ..\_exec\$(Configuration)\
// xcopy /D /Y /I ..\..\LplQue\Lib64\LplQue.dll ..\_exec\$(Configuration)\
////
#include "UsrMsg.h"
#include "UsrMsgBox.h"  // 2025.11.12 add eba
#include "ProgBar.h"  // 2025.11.18 add eba
#include "CalibComm.h"
#include "PowerPlanRAII.h" // 追加(2025.12..27yori)

//// 追加(2025.5.15yori)
//------------------------------
// APP間コマンド（Plugin側のソースコード内のAPP_CMDと一致させること）
//------------------------------
enum APP_CMD {
    UNKNOWN = 0,
    CONNECT,						//通信接続
    DISCONNECT,						//通信切断
    SCAN_START,						//スキャンスタート（おそらく非接触の時に使っていたコマンド。消して問題ないと思います。）
    SCAN_STOP,						//スキャンストップ（おそらく非接触の時に使っていたコマンド。消して問題ないと思います。）
    ORIGIN_REQ,						//おそらく非接触の時に使っていたコマンド。消して問題ないと思います。
    ORIGIN_RSP,						//おそらく非接触の時に使っていたコマンド。消して問題ないと思います。
    HOME_REQ,						//おそらく非接触の時に使っていたコマンド。消して問題ないと思います。
    HOME_RSP,						//おそらく非接触の時に使っていたコマンド。消して問題ないと思います。
    INITIALIZE,						//初期化スタート
    OPEN_MENUDIALOG,				//メニューダイアログの表示を要求
    PROBE_PROPETY_REQUEST,			//プローブのIDとスタイラス直径の要求
    SCANNER_INITIALIZE,				//スキャナの接続と初期化(2021.5.18yori)
    SCANNER_DISCONNECT,				//スキャナの切断(2021.5.18yori)
    VEC_HEAD_TYPE_PROBE,			//Inspectorのプローブのアイコンをクリックした場合(2021.5.19)
    VEC_HEAD_TYPE_SCANNER,			//Inspectorのスキャナのアイコンをクリックした場合(2021.5.19)
    INITIALIZE_STATUS,				//イニシャライズ状態確認(2021.9.21yori)
    OPEN_SCANNER_MEAS_DIALOG,		//スキャナ測定ダイアログ表示(2021.10.2yori)
    NONCONTACT_SCAN_START = 100,	//非接触スキャンスタート
    NONCONTACT_STOP = 101,			//非接触スキャンストップ
    END
};
////



/***********************************************************************

    スタティック変数

***********************************************************************/

HANDLE    AppMain::m_hThread      = NULL;
bool      AppMain::m_ThreadBreak  = false;



/***********************************************************************

    初期化処理

***********************************************************************/

int AppMain::Init()
{
    DisablePowerThrottlingIgnoreTimerResolution(); // 電力スロットリングを無効化(タイマー精度)(2025.12.26yori)
    //DisableAllPowerThrottling(); // 電力スロットリングを無効化(CPU処理速度、タイマー精度)→上記をコメントアウトしてこれを実行してもEhモードは遅延する。(2025.12.27yori)
    timeBeginPeriod(1); // 追加(2025.12.27yori)
    //SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS); // 優先度：高(2025.12.27yori)
    //int     frc,yes_existF; // 現行のLplQueを使用するため、コメントアウト(2025.5.15yori)

    m_ThreadBreak = false;

    LplInitialIFCommon(); // 追加(2025.5.15yori) // 終了時に「例外がスローされました」のメッセージが表示される(2025.5.15yori)
    HwCtrl::hSEMA = CreateSemaphore(NULL, 1, 1, SEMAPHORE_NAME); //追加(2025.5.15yori)
    HwCtrl::hSEMA_VSEQ = CreateSemaphore(NULL, 1, 1, SEMAPHORE_VEC_STEP_SEQ_NAME); // 2025.5.27 add eba

    // Vecシーケンス初期化 2025.5.27 add eba
    WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);
    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::START;
    ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

    // 共有メモリの作成
    // 現行のLplQueを使用するため、コメントアウト(2025.5.15yori)
    /*
    LplQue_IsExist( &yes_existF );

    if ( yes_existF != 1 ) {
        unsigned long  DataSize = 10000000;

        frc = LplQue_Create( DataSize );
        if ( frc != 0 ) {
            return( 1 );
        }
    }
    */

    // スレッド開始
    std::thread  Thread( &AppMain::ThreadProc );
    m_hThread  = Thread.native_handle();
    Thread.detach();

    return( 0 );
}



/***********************************************************************

    終了処理

***********************************************************************/

int AppMain::Term()
{
    m_ThreadBreak = true;
    CloseHandle(HwCtrl::hSEMA); //追加(2025.5.15yori)
    CloseHandle(HwCtrl::hSEMA_VSEQ);    // 2025.5.27 add eba
    LplTerminateALL(); // 追加(2025.5.15yori)
    // 現行のLplQueを使用するため、コメントアウト(2025.5.15yori)
    //LplQue_Delete();
    timeEndPeriod(1); // 追加(2025.12.27yori)

    return( 0 );
}


/***********************************************************************
    2025.4.24 eba
    SubWindow01が開く前の処理
    memo：関数名は処理したい名前に変えてもよいと思う
***********************************************************************/

int AppMain::Grp01()
{
    // add code 

    return(0);
}


/***********************************************************************
    2025.4.24 eba
    SubWindow02が開く前の処理
    memo：関数名は処理したい名前に変えてもよいと思う
***********************************************************************/

int AppMain::Grp02()
{
    // add code 

    return(0);
}


/***********************************************************************
    2025.4.24 eba
    SubWindow03が開く前の処理
    memo：関数名は処理したい名前に変えてもよいと思う
***********************************************************************/

int AppMain::Grp03()
{
    // add code 

    return(0);
}


/***********************************************************************
    2025.5.28 eba
    HardWareのステータス変更情報の取得
    
***********************************************************************/

int AppMain::UpDateData01(STATUS01* sts)
{
    int i = 0;
    int j = 0; // 追加(2025.2.24yori)
    int ret = 0; // 追加(2025.6.4yori)
    wchar_t probe_name[21][32], stylus_angle[21][32], probe_type[21][32]; // 追加(2025.8.28yori) // プローブ種類追加(2025.10.31yori)

    // ステータスチェック(2025.6.4yori)
    ret = HwCtrl::Func09();
    if (ret == 0)
    {
        sts->mode = HwCtrl::m_hVecCnt.m_Sts.m_GetMode; // モード(2025.6.4yori)
        sts->connect_fg = HwCtrl::m_hVecCnt.m_connectflag; // 接続状態(2025.6.4yori)
        sts->init_fg = HwCtrl::m_hVecCnt.m_Sts.m_iInitFlg; // イニシャライズ終了フラグ(2025.6.4yori)
        for (i = 0; i < 7; i++)
        {
            sts->init_sts[i] = HwCtrl::m_hVecCnt.m_Sts.m_iInitSts[i]; // 各軸のイニシャライズ状態(2025.7.11yori)
        }
        sts->no0_fg = HwCtrl::m_hVecCnt.m_Sts.m_No0Fg; // 0軸有無(2025.7.15yori)
        sts->probe_id = HwCtrl::m_hVecCnt.m_Sts.m_iProbeId; // プローブID(2025.6.11yori)
        sts->dia = HwCtrl::m_hVecCnt.m_Sts.m_dia; // スタイラス直径(2025.6.11yori)
    }
 
    // アーム暖機、温度変化チェック(2025.6.4yori)
    ret = HwCtrl::Func22();
    if (ret == 0)
    {
        sts->warm_fg = HwCtrl::m_hVecCnt.m_Sts.m_Warm;
    }

    // プローブ情報取得(2025.7.24yori)
    // Func52へ引数追加に伴う変更(2025.8.28yori)
    HwCtrl::Func52(probe_name, stylus_angle, probe_type);

    for (int i = 0; i < 21; i++)
    {
        // wcstombs_s を使って変換(2025.8.28yori)
        size_t converted = 0; // 変換されたバイト数を格納する変数
        errno_t err; // エラーコードを格納する変数
        err = wcstombs_s(&converted, sts->probe_name[i], sizeof(sts->probe_name[i]), probe_name[i], _TRUNCATE);

        sts->stylus_angle[i] = _wtof(stylus_angle[i]);
        sts->probe_type[i] = _wtoi(probe_type[i]); // プローブ種類(2025.10.31yori)
    }

    // アーム内温度取得(2025.6.4yori)
    ret = HwCtrl::Func24();
    if (ret == 0)
    {
        for (i = 0; i < 7; i++)
        {
            sts->tempature[i] = HwCtrl::m_hVecCnt.m_Sts.m_Tmp[i];
        }
    }

    // キャリブ温度取得(2025.6.18yori)
    ret = HwCtrl::Func30();
    if (ret == 0)
    {
        for (i = 0; i < 7; i++)
        {
            sts->cal_tempature[i] = HwCtrl::m_hVecCnt.m_Sts.m_CalTmp[i];
        }
    }

    //// アーム型式取得(2025.6.16yori)
    HwCtrl::Func26();
    strcpy_s(sts->arm_model, 16, HwCtrl::m_hVecCnt.m_Sts.m_ArmModel); //sprintf_s→strcpy_sへ変更(2025.8.30yori)

    //// ネットワーク設定取得(2025.6.18yori)
    char adress[4][8], subnet[4][8], port[4]; // IPアドレス、サブネットマスクを4つに分割(2025.8.15yori)
//    ret = HwCtrl::Func31(adress, subnet, port); // 2025.9.30 この関数バグあり、メモリ壊しています！！！！ memo eba
    if (ret == 0)
    {
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 8; j++)
            {
                sts->address[i][j] = adress[i][j];
                sts->subnet[i][j] = subnet[i][j];
            }
 
            sts->port[i] = port[i];
        }
    }

    return(0);
}

/***********************************************************************

    2025.9.1 yori
    有接触自己診断のステータス変更情報の取得

***********************************************************************/

int AppMain::UpDateData06(STATUS04* sts)
{
    int ret = 0;
    int i = 0;

    // ボタンチェック
    // 通信チェック
    VecDtEx data;
    ret = HwCtrl::Func05(&data);
    if (ret == 0)
    {
        sts->btn = data.button;
        for (i = 0; i < 9; i++)
        {
            sts->comm_check[i] = data.er_code[i];
        }
    }

    // ファームウェアバージョン
    strcpy_s(sts->firm_ver, 32, HwCtrl::m_hVecCnt.m_Sts.m_Ver.c_str());

    // カウンタバージョン
    ret = HwCtrl::Func27();
    if (ret == 0)
    {
        strcpy_s(sts->cnt_ver, sizeof(sts->cnt_ver), HwCtrl::m_hVecCnt.m_Sts.m_CntVer);
    }

    // カウントチェック1は、CountCheckを使用する。(2025.10.6yori)
    // カウントチェック2は、CountCheckを使用する。(2025.10.6yori)

    return(0);
}

/***********************************************************************

    2025.10.6 yori
    カウントチェック1、2

***********************************************************************/

int AppMain::CountCheck(STATUS04* sts)
{
    int ret = 0;
    int i = 0;

    VecCtEx2 cntdata;
    ret = HwCtrl::Func28(&cntdata);
    if (ret == 0 && (cntdata.no == -1 || cntdata.no >= 0)) // cntdata.noの条件追加、cntdata.no=-858993460が取得される場合がある。(2025.10.30yori)
    {
        for (i = 0; i < 9; i++)
        {
            sts->cnt_data[i] = cntdata.cnt[i];
        }
        sts->count_fg = 1; // カウント値を正常に取得できた場合(2025.10.30yori)
    }
    else
    {
        sts->count_fg = 0; // カウント値を正常に取得できなかった場合(2025.10.30yori)
    }

    return(0);
}

/***********************************************************************

    2025.6.19 yori
    HardWare(スキャナ)のステータス変更情報の取得

***********************************************************************/

int AppMain::UpDateData02(STATUS02* sts)
{
    BOOL fg = FALSE;
    wchar_t mode[6][32]; // 追加(2025.8.10yori)
    int i, j, k; // 追加(2025.8.11yori)

    // TDSLibarary.iniから計測モード情報取得(2025.8.10yori)
    HwCtrl::Func59(mode);
    for (i = 0; i < 6; i++)
    {
        // wcstombs_s を使って変換(2025.8.28yori)
        size_t converted_chars = 0; // 変換されたバイト数を格納する変数
        errno_t err; // エラーコードを格納する変数
        err = wcstombs_s(&converted_chars, sts->mode_info[i], sizeof(sts->mode_info[i]), mode[i], _TRUNCATE);
    }

    // 計測モード取得
    sts->mode = HwCtrl::Func34();

    // 点間ピッチ間引き(2025.8.11yori)
    for (i = 0; i < 10; i++)
    {
        sts->pitch[i] = HwCtrl::m_dXPitch * ( i + 1 );
    }

    // 感度取得
    HwCtrl::Func35(sts->sens_use, sts->sens_name);
    HwCtrl::GetIniScanSens(&sts->sens); // 現在の感度取得(2025.11.25yori)

    // 距離マスク取得
    fg = HwCtrl::Func36();
    if (fg == TRUE)
    {
        for (i = 0; i < 6; i++)
        {
            for (j = 0; j < 3; j++)
            {
                for (k = 0; k < 2; k++)
                {
                    sts->dist_use[i][j][k] = HwCtrl::m_ptZMask->use[i][j][k];
                    sts->dist_data[i][j][k] = HwCtrl::m_ptZMask->data[i][j][k];
                }
            }
        }
    }
    delete HwCtrl::m_ptZMask;

    // 輝度スライス取得(2025.6.20yori)
    fg = HwCtrl::Func37(sts->brightslice); // 修正(2025.8.25yori)

    // 感度スライス取得(2025.6.20yori)
    fg = HwCtrl::Func38(sts->sens_slice); // 修正(2025.8.25yori)

    // ガイドレーザーパワー取得(2025.6.23yori)
    HwCtrl::Func39(&sts->power);

    // 補間設定取得(2025.6.23yori)
    HwCtrl::Func40(&sts->xpitch_onoff);

    // 角度マスク設定値取得(2025.6.23yori)
    HwCtrl::Func41(&sts->angle);

    // 2ピークマスク設定値取得(2025.6.23yori)
    HwCtrl::Func42(&sts->two_peak);

    // エッジマスク設定値取得(2025.6.23yori)
    int serch_mask = 0;
    HwCtrl::Func43(&sts->edge, &serch_mask);

    // エッジマスク初期値取得(2025.8.27yori)
    int serch_mask_default[3][6];
    HwCtrl::Func72(sts->edge_default, serch_mask_default);

    // スキャナネットワーク設定取得(2025.6.20yori)
    HwCtrl::Func33(sts->address, sts->subnet, sts->gateway, sts->dns);
    
    return(0);
}

/***********************************************************************

    HardWare(アーム)のステータス変更情報(C#→C++)
    ApplicationからHardWare(アーム)へ書き込むための情報取得
    2025.7.18yori

***********************************************************************/

int AppMain::UpDateData01_Write(STATUS01* sts)
{
    char s_para[32]; // 追加(2025.8.15yori)

    // アームのIPアドレス(2025.8.15yori)
    // スペース追加(2025.8.15yori)
    strcpy_s(s_para, &sts->address[0][0]);
    strcat_s(s_para, " ");
    strcat_s(s_para, &sts->address[1][0]);
    strcat_s(s_para, " ");
    strcat_s(s_para, &sts->address[2][0]);
    strcat_s(s_para, " ");
    strcat_s(s_para, &sts->address[3][0]);
    strcpy_s(HwCtrl::m_hVecCnt.m_Sts.m_Address, sizeof(HwCtrl::m_hVecCnt.m_Sts.m_Address), s_para);

    // アームのサブネットマスク(2025.8.15yori)
    // スペース追加(2025.8.15yori)
    strcpy_s(s_para, &sts->subnet[0][0]);
    strcat_s(s_para, " ");
    strcat_s(s_para, &sts->subnet[1][0]);
    strcat_s(s_para, " ");
    strcat_s(s_para, &sts->subnet[2][0]);
    strcat_s(s_para, " ");
    strcat_s(s_para, &sts->subnet[3][0]);
    strcpy_s(HwCtrl::m_hVecCnt.m_Sts.m_Subnet, sizeof(HwCtrl::m_hVecCnt.m_Sts.m_Subnet), s_para); // m_Address→m_Subnetへ修正(2025.8.28yori)

    // アームのポート(2025.8.15yori)
    strcpy_s(HwCtrl::m_hVecCnt.m_Sts.m_Port, sizeof(HwCtrl::m_hVecCnt.m_Sts.m_Port), sts->port);

    return(0);
}

/***********************************************************************

    HardWare(スキャナ)のステータス変更情報(C#→C++)
    ApplicationからHardWare(スキャナ)へ書き込むための情報取得
    2025.8.17yori

***********************************************************************/

int AppMain::UpDateData02_Write(STATUS02* sts)
{
    int i, j, k;
    HwCtrl::m_ptZMask = new PulsZMask;

    // 距離マスク(2025.8.25yori)
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 3; j++)
        {
            for (k = 0; k < 2; k++)
            {
                HwCtrl::m_ptZMask->use[i][j][k] = sts->dist_use[i][j][k];
                HwCtrl::m_ptZMask->data[i][j][k] = sts->dist_data[i][j][k];
            }
        }
    }

    // 輝度、感度スライス(2025.8.25yori)
    for (i = 0; i < 5; i++)
    {
        HwCtrl::m_BrightSlice[i] = sts->brightslice[i];
        HwCtrl::m_SensSlice[i] = sts->sens_slice[i];
    }

    // 角度マスク(2025.8.25yori)
    HwCtrl::m_Angle = sts->angle;

    // エッジマスク(2025.8.25yori)
    HwCtrl::m_Edge = sts->edge;

    // スキャナのIPアドレス(2025.8.27yori)
    HwCtrl::m_Address = (unsigned int)(atoi(sts->address[0]) << 24) + (unsigned int)(atoi(sts->address[1]) << 16) + (unsigned int)(atoi(sts->address[2]) << 8) + (unsigned int)atoi(sts->address[3]);
    // スキャナのサブネットマスク(2025.8.27yori)
    HwCtrl::m_Subnet = (unsigned int)(atoi(sts->subnet[0]) << 24) + (unsigned int)(atoi(sts->subnet[1]) << 16) + (unsigned int)(atoi(sts->subnet[2]) << 8) + (unsigned int)atoi(sts->subnet[3]);
    // スキャナのデフォルトゲートウェイ(2025.8.27yori)
    HwCtrl::m_Gateway = (unsigned int)(atoi(sts->gateway[0]) << 24) + (unsigned int)(atoi(sts->gateway[1]) << 16) + (unsigned int)(atoi(sts->gateway[2]) << 8) + (unsigned int)atoi(sts->gateway[3]);

    return(0);
}


/***********************************************************************

    2025.6.24 yori
    非接触自己診断のステータス変更情報の取得

***********************************************************************/

int AppMain::UpDateData03(STATUS03* sts)
{
    BOOL fg = FALSE;

    // 感度チェック(2025.7.2)
    HwCtrl::Func49();
    sts->isensresult = HwCtrl::m_ptSensResult->iResult;
    sts->ibasebright = HwCtrl::m_ptSensResult->iBaseBright;
    sts->iresultbright = HwCtrl::m_ptSensResult->iResultBright;
    sts->dthreshold = HwCtrl::m_ptSensResult->dThreshold;
    delete HwCtrl::m_ptSensResult;

    // SWチェック(2025.6.24yori)
    HwCtrl::Func44(sts->sw);

    // ラッチ通信チェック作成中(2025.6.24yori)
    HwCtrl::Func45();
    sts->ilatchresult = HwCtrl::m_ptLatchResult->iResult;
    sts->isendlatchcount = HwCtrl::m_ptLatchResult->iSendLatchCount;
    sts->irecvlatchcount = HwCtrl::m_ptLatchResult->iRecvLatchCount;
    delete HwCtrl::m_ptLatchResult;

    // ポインタ位置チェック(2025.7.4yori)
    sts->avedit = HwCtrl::m_PointerCheckScanData;

    // モーターチェック(2025.6.24yori)
    HwCtrl::Func46();
    sts->imotorresult = HwCtrl::m_ptMotorResult->iResult;
    sts->isensorplus = HwCtrl::m_ptMotorResult->iSensorPlus;
    sts->icontrollerplus = HwCtrl::m_ptMotorResult->iControllerPlus;
    sts->isensorminus = HwCtrl::m_ptMotorResult->iSensorMinus;
    sts->icontrollerminus = HwCtrl::m_ptMotorResult->iControllerMinus;
    delete HwCtrl::m_ptMotorResult;

    // LEDチェック
    HwCtrl::Func47();

    return(0);
}

/***********************************************************************

    2025.7.31 yori
    しきい値取得
    すべてのID→指定IDのしきい値取得へ変更(2025.9.22yori)

***********************************************************************/

int AppMain::UpDateData04(THRESHOLD* th, int id)
{
    CALIB_JUDGE_CK judge_ck;
    CALIB_JUDGE judge[20];
    CALIB_GAUGE gauge;

    HwCtrl::Func54(&judge_ck, judge, &gauge, id);

    // 始業前点検
    th->pp = judge_ck.pp;
    th->sigma2 = judge_ck.sigma2;
    th->plate = judge_ck.plate;
    th->pitch = judge_ck.pitch;
    th->maxmin = judge_ck.maxmin;

    // プローブ点検
    th->pp_probe[id] = judge[id].pp;
    th->sigma2_probe[id] = judge[id].sigma2;
    th->plate_probe[id] = judge[id].plate;
    th->ri_probe[id] = judge[id].ri;
    th->ps_probe[id] = judge[id].ps;

    // キャリブレーション
    th->dst_max = gauge.AreaRFar;
    th->dst_min = gauge.AreaRNear;
    th->height_max = gauge.AreaZHigh;
    th->height_min = gauge.AreaZLow;
    th->error_max = gauge.ErrMax;

    return(0);
}

/***********************************************************************

    2025.8.7 yori
    ゲージ設定値取得

***********************************************************************/

int AppMain::UpDateData05(GAUGE* ga)
{
    VecGaugeIni vecini;
    SensorSettingIni sensini;
    double scanchkball; // 非接触球のみの点検しきい値追加(2025.8.10)

    HwCtrl::Func56(&vecini, &sensini, &scanchkball);
    memcpy(ga->GageType, vecini.szGaugeName, sizeof(ga->GageType));
    ga->Center_ScopePnt[0] = sensini.dCenterScopePnt[0];
    ga->Center_ScopePnt[1] = sensini.dCenterScopePnt[1];
    ga->Center_ScopePnt[2] = sensini.dCenterScopePnt[2];
    ga->Center_ScopeRad = vecini.dSphDiameter;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ga->Plane_ScopePnt[i][j] = sensini.dPlaneScopePnt[i][j];
        }
    }
    ga->Plane_ScopeRad = sensini.dPlaneScopeRad;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ga->Length_ScopePnt[i][j] = vecini.dPlnLengthPnt[i][j];
        }
    }
    ga->Length_ScopeRad = sensini.dLengthScopeRad;
    ga->Length_ScopeRad_Cnt = sensini.iLengthScopeRadCnt;
    ga->Center_Limit = sensini.dCenterLimit;
    ga->Plane_Limit = sensini.dPlaneHeightLimit;
    ga->Length_Limit = sensini.dPlaneLengthLimit;
    ga->Only_Ball_Center_Limit = scanchkball; // 非接触球のみの点検しきい値追加(2025.8.10)
    ga->Plane_MeasPnt_Limit = sensini.iPlaneHeightMeasPntMin;
    ga->Length_MeasPnt_Limit = sensini.iPlaneLengthMeasPntMin;
    ga->Kido_Base = sensini.iBrightBase;
    ga->Kido_Limit = sensini.dBrightLimit;

    return(0);
}

/***********************************************************************

    veccal.ini変更情報(C#→C++)
    Applicationからiniファイルへ書き込むための情報取得
    2025.8.1yori
    すべてのID→指定IDのしきい値書き込みへ変更(2025.9.22yori)

***********************************************************************/

int AppMain::UpDateData04_Write(THRESHOLD* th, int id)
{
    CALIB_JUDGE_CK judge_ck;
    CALIB_JUDGE judge_write[20]; // 追加(2025.9.8yori)
    CALIB_JUDGE judge_read[20]; // 追加(2025.9.22yori)
    CALIB_GAUGE gauge_write;
    CALIB_GAUGE gauge_read;

    // アプリ側で表示していない値はiniファイルの値を使用する。
    CalibGetGaugeVal(&gauge_read);
    CalibGetThreshold(&judge_read[id], id); // 追加(2025.9.22yori)

    // 始業前点検
    judge_ck.pp = th->pp;
    judge_ck.sigma2 = th->sigma2;
    judge_ck.plate = th->plate;
    judge_ck.pitch = th->pitch;
    judge_ck.maxmin = th->maxmin;

    // プローブ点検(2025.9.8yori)
    judge_write[id].pp = th->pp_probe[id];
    judge_write[id].sigma2 = th->sigma2_probe[id];
    judge_write[id].plate = th->plate_probe[id];
    judge_write[id].ri = th->ri_probe[id];
    judge_write[id].ps = th->ps_probe[id];
    judge_write[id].ld = judge_read[id].ld; // 追加(2025.9.22yori)
    judge_write[id].pf = judge_read[id].pf; // 追加(2025.9.22yori)
    judge_write[id].pl = judge_read[id].pl; // 追加(2025.9.22yori)
    judge_write[id].psi = judge_read[id].psi; // 追加(2025.9.22yori)


    // キャリブレーション
    gauge_write.StylusDia = gauge_read.StylusDia;
    gauge_write.BallBarLen = gauge_read.BallBarLen;
    gauge_write.PlateLen = gauge_read.PlateLen;
    gauge_write.BallDia = gauge_read.BallDia;
    gauge_write.PitchBarLen = gauge_read.PitchBarLen;
    for (int i = 0; i < 6; i++)
    {
        gauge_write.BallBarLenV8[i] = gauge_read.BallBarLenV8[i];
    }
    gauge_write.AreaRFar = th->dst_max;
    gauge_write.AreaRNear = th->dst_min;
    gauge_write.AreaZHigh = th->height_max;
    gauge_write.AreaZLow = th->height_min;
    gauge_write.ErrMax = th->error_max;

    CalibSetThresholdCk(judge_ck);
    CalibSetThreshold(judge_write[id], id); // プローブ点検のしきい値(2025.9.8yori)
    CalibSetGaugeVal(gauge_write);

    return(0);
}

/***********************************************************************

    SensorSetting.ini変更情報(C#→C++)
    Applicationからiniファイルへ書き込むための情報取得
    2025.8.9yori

***********************************************************************/

int AppMain::UpDateData05_Write(GAUGE* ga)
{
    SensorSettingIni sensini_wite;
    SensorSettingIni sensini_read;

    TdsVecReadSSettingIni(&sensini_read); // アプリ側で表示していない値はiniファイルの値を使用する。
    sensini_wite.dCenterScopePnt[0] = sensini_read.dCenterScopePnt[0];
    sensini_wite.dCenterScopePnt[1] = sensini_read.dCenterScopePnt[1];
    sensini_wite.dCenterScopePnt[2] = sensini_read.dCenterScopePnt[2];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sensini_wite.dPlaneScopePnt[i][j] = sensini_read.dPlaneScopePnt[i][j];
        }
    }
    sensini_wite.dPlaneScopeRad = sensini_read.dPlaneScopeRad;
    sensini_wite.dLengthScopeRad = sensini_read.dLengthScopeRad;
    sensini_wite.iLengthScopeRadCnt = sensini_read.iLengthScopeRadCnt;

    sensini_wite.dCenterLimit= ga->Center_Limit;
    sensini_wite.dPlaneHeightLimit = ga->Plane_Limit;
    sensini_wite.dPlaneLengthLimit = ga->Length_Limit;
    sensini_wite.iPlaneHeightMeasPntMin = ga->Plane_MeasPnt_Limit;
    sensini_wite.iPlaneLengthMeasPntMin = ga->Length_MeasPnt_Limit;
    sensini_wite.iBrightBase = ga->Kido_Base;
    sensini_wite.dBrightLimit = ga->Kido_Limit;

    TdsVecWriteSSettingIni(&sensini_wite);
    HwCtrl::Func58(ga->Only_Ball_Center_Limit); // 追加(2025.8.10yori)

    return(0);
}

/***********************************************************************

    2025.8.1 yori
    しきい値の初期値取得
    すべてのID→指定IDの初期値取得へ変更(2025.9.22yori)

***********************************************************************/

int AppMain::UpDateData04_Default(THRESHOLD* th, int id)
{
    CALIB_JUDGE_CK judge_ck;
    CALIB_JUDGE judge[20];

    HwCtrl::Func55(&judge_ck, judge, id);

    // 始業前点検
    th->pp = judge_ck.pp;
    th->sigma2 = judge_ck.sigma2;
    th->plate = judge_ck.plate;
    th->pitch = judge_ck.pitch;
    th->maxmin = judge_ck.maxmin;

    // プローブ点検
    th->pp_probe[id] = judge[id].pp;
    th->sigma2_probe[id] = judge[id].sigma2;
    th->plate_probe[id] = judge[id].plate;
    th->ri_probe[id] = judge[id].ri;
    th->ps_probe[id] = judge[id].ps;

    return(0);
}

/***********************************************************************

    2025.8.9 yori
    ゲージ設定の初期値(SensorSetting.iniのみ)取得

***********************************************************************/

int AppMain::UpDateData05_Default(GAUGE* ga)
{
    SensorSettingIni sensini;

    TdsVecClearSSettingIni(&sensini);

    ga->Center_ScopePnt[0] = sensini.dCenterScopePnt[0];
    ga->Center_ScopePnt[1] = sensini.dCenterScopePnt[1];
    ga->Center_ScopePnt[2] = sensini.dCenterScopePnt[2];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ga->Plane_ScopePnt[i][j] = sensini.dPlaneScopePnt[i][j];
        }
    }
    ga->Plane_ScopeRad = sensini.dPlaneScopeRad;
    ga->Length_ScopeRad = sensini.dLengthScopeRad;
    ga->Length_ScopeRad_Cnt = sensini.iLengthScopeRadCnt;
    ga->Center_Limit = sensini.dCenterLimit;
    ga->Plane_Limit = sensini.dPlaneHeightLimit;
    ga->Length_Limit = sensini.dPlaneLengthLimit;
    ga->Plane_MeasPnt_Limit = sensini.iPlaneHeightMeasPntMin;
    ga->Length_MeasPnt_Limit = sensini.iPlaneLengthMeasPntMin;
    ga->Kido_Base = sensini.iBrightBase;
    ga->Kido_Limit = sensini.dBrightLimit;

    return(0);
}

/***********************************************************************

    2025.9.2 eba
    キャリブデータが入力された時に返ってくるコールバック関数

***********************************************************************/

int AppMain::ContactInspectionPanelMesCallBack()
{
   // CalibComm::CntDataMesCallBack();

    return(0);
}

/***********************************************************************

    電力スロットリングを無効化(CPU処理速度)
    2025.12.26yori

***********************************************************************/
void AppMain::DisablePowerThrottling()
{
    PROCESS_POWER_THROTTLING_STATE state = {};
    state.Version = PROCESS_POWER_THROTTLING_CURRENT_VERSION;

    // 電力スロットリングを無効化
    state.ControlMask = PROCESS_POWER_THROTTLING_EXECUTION_SPEED;
    state.StateMask = 0; // ← 無効化

    BOOL result = SetProcessInformation(
        GetCurrentProcess(),
        ProcessPowerThrottling,
        &state,
        sizeof(state)
    );

    if (!result)
    {
        DWORD err = GetLastError();
        // エラーハンドリング（必要なら）
    }
}


/***********************************************************************

    電力スロットリングを無効化(タイマー精度)
    2025.12.26yori

***********************************************************************/
void AppMain::DisablePowerThrottlingIgnoreTimerResolution()
{
    PROCESS_POWER_THROTTLING_STATE state = {};
    state.Version = PROCESS_POWER_THROTTLING_CURRENT_VERSION;

    // 対象を指定（IGNORE_TIMER_RESOLUTION を管理対象にする）
    state.ControlMask = PROCESS_POWER_THROTTLING_IGNORE_TIMER_RESOLUTION;

    // StateMask を 0 にする → フラグを無効化（OFFにする）
    state.StateMask = 0;

    BOOL result = SetProcessInformation(
        GetCurrentProcess(),
        ProcessPowerThrottling,
        &state,
        sizeof(state)
    );

    if (!result)
    {
        DWORD err = GetLastError();
        // エラーハンドリング（必要なら）
    }
}

/***********************************************************************

    全電力スロットリングも含めて完全に無効化(CPU処理速度、タイマー精度)
    2025.12.26yori

***********************************************************************/
void AppMain::DisableAllPowerThrottling()
{
    PROCESS_POWER_THROTTLING_STATE state = {};
    state.Version = PROCESS_POWER_THROTTLING_CURRENT_VERSION;

    // 全フラグを管理対象に設定
    state.ControlMask =
        PROCESS_POWER_THROTTLING_EXECUTION_SPEED |
        PROCESS_POWER_THROTTLING_IGNORE_TIMER_RESOLUTION;

    // すべてOFFにする
    state.StateMask = 0;

    BOOL result = SetProcessInformation(
        GetCurrentProcess(),
        ProcessPowerThrottling,
        &state,
        sizeof(state)
    );

    if (!result)
    {
        DWORD err = GetLastError();
        // エラーハンドリング（必要なら）
    }
}



/***********************************************************************
    
    共有メモリ受信テスト関数
    2025.12.28yori

***********************************************************************/

int AppMain::TestLplRecvMesBox()
{
    int		iRec = 0;
    char	buff[1024] = { 0 };
    iRec = HwCtrl::AppCommandRecv(buff);

    return(0);
}



/***********************************************************************

    スレッド処理
    PolyWorksからのメッセージ受信
    PolyWorksへ有接触データ送信

***********************************************************************/

void AppMain::ThreadProc()
{
    //int     CmdID, ExistF; // 未使用のためコメントアウト
    
    //// 追加(2025.5.15yori)
    int     cmd_no;
    int		iRec = 0;
    int		tid = QUE_NUM::COMMAND;
    char	buff[1024] = { 0 };
    int     ret = 0;
    int     slp_tm = 100;   // 2025.7.4 eba add default100ms
    BOOL    warmup_fg = FALSE; // 追加(2025.7.29yori)
    ////
    VecDtEx PosiData; // 下記から移動(2025.9.8yori)
    PosiData.pbid_chg_fg = 0;  // 追加(2025.9.8yori)
    size_t converted = 0; // 追加(2025.9.26yori)
    errno_t err; // 追加(2025.9.26yori)
    wchar_t armtype[16]; // 追加(2025.9.26yori)
    char model[16];// 追加(2025.9.26yori)
    int resultMsg = 0;
    VecCtEx VecData; // スキャナ側のベクトロンデータ(スキャナデータ変換用データ)(2025.12.2yori)
    //int w_cnt = 0; // デバッグ(2025.12.28yori)
    //int r_cnt = 0; // デバッグ2025.12.28yori)
    //char text[256]; // デバッグ(2026.1.12yori) 

    while( 1 )
    {
        //LplGetQueCount(NONCONTACT_DATA, &w_cnt, &r_cnt); // デバッグ(2025.12.28yori)
        //sprintf_s(text, 256, "LplGetQueCount:w_cnt %d r_cnt %d\n", w_cnt, r_cnt); // デバッグ(2025.12.28yori)
        //OutputDebugStringA(text); // デバッグ(2025.12.27yori)

        if ( m_ThreadBreak == true ) {
            m_ThreadBreak = false;
            break;
        }

        WaitForSingleObject(HwCtrl::hSEMA_VSEQ, INFINITE);

        //// 追加(2025.5.15yori)
        // PolyWorksからのメッセージ受信
        iRec = HwCtrl::AppCommandRecv(buff);
        if (iRec > 0) {
            cmd_no = buff[0];
            switch (cmd_no) {
            case APP_CMD::CONNECT:
                if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::START ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::DISCONNECT_CMP || // DISCONNECT_CMPは切断完了のため追加(2025.11.17yori)
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::FINISH) // 切断後に接続できるようDISCONNECT_CMP→FINISHへ変更(2025.11.7yori)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
                    HwCtrl::m_b_Button_ConnectFlag = false; // ポリ側から接続を行った 2025.7.4 eba add // true→falseへ修正(2025.7.18yori)
                }
                break;

            case APP_CMD::INITIALIZE:
                if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::CONNECT_CMP ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::MEAS_IDLE)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE_REQ;
                }
                break;

            case APP_CMD::OPEN_MENUDIALOG: // 有接触設定メニュー表示(2025.7.18yori)
                if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::CONNECT_CMP ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::MEAS_IDLE)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::OPEN_MENUDIALOG_REQ;
                }
                break;

            case APP_CMD::PROBE_PROPETY_REQUEST: // 追加(2025.7.18yori)
                if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::CONNECT_CMP ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::MEAS_IDLE)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::PROBE_PROPETY_REQ;
                }
                break;

            case APP_CMD::DISCONNECT:
                if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::CONNECT_CMP ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::MEAS_IDLE ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::SCANNER_SCAN_STOP_CMP ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::SCANNER_INIT_CMP ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::SCANNER_DISCONNECT_CMP) // SCANNER_DISCONNECT_CMP追加(2025.9.3yori)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::DISCONNECT_REQ;
                }
                break;

            case APP_CMD::SCANNER_INITIALIZE:
                if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::CONNECT_CMP ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::MEAS_IDLE ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::SCANNER_SCAN_STOP_CMP)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_INIT_REQ;
                }
                break;

            case APP_CMD::VEC_HEAD_TYPE_PROBE: // 追加(2025.11.7yori)
                // 何もしない。処理が必要な場合は、追加する。(2025.11.7yori)
                break;

            case APP_CMD::VEC_HEAD_TYPE_SCANNER: // 追加(2025.11.7yori)
                // 何もしない。処理が必要な場合は、追加する。(2025.11.7yori)
                break;

            case APP_CMD::NONCONTACT_SCAN_START:
                if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::SCANNER_INIT_CMP ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::SCANNER_SCAN_STOP_CMP ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::SCANNER_SCAN_MEAS_IDEL) // SCANNER_SCAN_MEAS_IDEL追加(2025.11.6yori)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SCAN_START_REQ;
                }
                break;

            case APP_CMD::NONCONTACT_STOP:
                if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::SCANNER_SCAN_MEAS_IDEL)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SCAN_STOP_REQ;
                }
                break;

            case APP_CMD::OPEN_SCANNER_MEAS_DIALOG: // PolyWorksの設定ボタンが押され、非接触設定メニューを表示する。(2025.9.3yori)
                if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::SCANNER_INIT_CMP ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::SCANNER_SCAN_MEAS_IDEL ||
                    HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::SCANNER_SCAN_STOP_CMP)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::OPEN_SCANNER_MEAS_DIALOG_REQ;
                }
                break;

            case APP_CMD::SCANNER_DISCONNECT: // スキャナ切断処理(2025.9.3yori)
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_DISCONNECT_REQ;
                break;

            default:
                break;
            }
        }
       
        switch (HwCtrl::m_VecStepSeq)
        {
        case VEC_STEP_SEQ::START:
            slp_tm = 100;
            break;
        case VEC_STEP_SEQ::CONNECT_REQ:
            //ProgBar::CallBackShow(1);   // test eba // コメントアウト(2025.11.19yori)
            ret = HwCtrl::Func01(); // 有接触接続
            if (ret == 0)
            {
                //ProgBar::CallBackHide();     // test eba // コメントアウト(2025.11.19yori)

                // 接続時にファームウェアからアーム型式を自動変更する。(2025.9.29yori)
                if (HwCtrl::m_hVecCnt.m_Sts.m_Model == "VAR800S") strcpy_s(model, 16, "BK100S"); // VAR800Sは、BK100Sで点検、キャリブを行う。(2025.9.29yori)
                else strcpy_s(model, 16, HwCtrl::m_hVecCnt.m_Sts.m_Model.c_str());
                err = mbstowcs_s(&converted, armtype, 16, model, _TRUNCATE);
                ret = HwCtrl::Func74(armtype);
                ret = HwCtrl::Func08(); // 有接触モードへ変更
                ret = HwCtrl::Func75(); // 関節リミットビープ音のON(2025.9.1yori)
                ret = HwCtrl::Func05(&PosiData); // 接続時にプローブID変更フラグ初期値取得のため、追加(2025.10.2)
                if (HwCtrl::Func09() == 0 && HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 0) // 有接触モードでID=0(非接触)の場合、非接触モードへ切り替える前のプローブIDへ戻す。(2025.12.20yori)
                {
                    HwCtrl::Func50(HwCtrl::m_ProbeIdBeforeScanner, HwCtrl::m_hVecCnt.m_Sts.m_dia);
                }

                if (HwCtrl::m_hVecCnt.m_Sts.m_Warm != 0) // 温度が正常ではない場合(2025.11.11yori)
                {
                    //if(HwCtrl::m_ArmWarmUpMonitorFlag) HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_WARMUP_REQ; // 暖機処理を無視するため、コメントアウト、後でコーディング(2025.11.11yori)
                }

                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_CMP; // 追加(2025.11.10yori)
                if (!HwCtrl::m_b_Button_ConnectFlag)
                {
                    HwCtrl::AppCommandSend(APP_SEND_CMD::CONNECT_SUCCESS); // 接続に成功したことをPolyWorks側に知らせる(2025.6.9yori)
                    //UsrMsg::CallBack(UsrMsg::WM_MainWnd_OtherApp_Connected); // C#側にPolyWorks側から接続したことを知らせる。(2025.11.19yori) // アプリ単体動作は作成中のため、最初から接続、設定ボタンを押せないようにする。(2025.12.26yori)
                }
            }
            else
            {
                if (!HwCtrl::m_b_Button_ConnectFlag) HwCtrl::AppCommandSend(APP_SEND_CMD::CONNECT_FAILURE); // 接続に失敗したことをPolyWorks側に知らせる(2025.6.9yori)
                
                // 接続エラー
                ProgBar::CallBackHide();     // test eba
                resultMsg = UsrMsgBox::CallBack(269, 268, 0, 16);
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::START;
            }
            break;

        case VEC_STEP_SEQ::CONNECT_CMP:
            ret = HwCtrl::Func05(&PosiData);    //ret = HwCtrl::Func09(); 2025.11.12 mod eba
            if (ret == 0)
            {
                UsrMsg::CallBack(UsrMsg::WM_UpdateData1); // C#側にステータス更新要求を送る 2025.7.2 add eba
                if (HwCtrl::m_hVecCnt.m_VecInitflag)   // 初期化が完了していたら
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE_CMP; // イニシャライズ画面は出さず測定準備完了へ
                }
            }
            else
            {
                // 通信エラー
                resultMsg = UsrMsgBox::CallBack(270, 268, 4, 16);
                HwCtrl::Func04(); // 有接触切断
                if (resultMsg == 6)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
                }
                else
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
                }
            }
            break;

        case VEC_STEP_SEQ::ARM_WARMUP_REQ: // アーム温度監視要求(2025.7.16yori)
            if (HwCtrl::m_hVecCnt.m_Sts.m_Warm == 3 || HwCtrl::m_hVecCnt.m_Sts.m_Warm == 4 ) UsrMsg::CallBack(UsrMsg::WM_DlgPrgBar1_Show); // 3:暖機未完了、4:暖気スキップ禁止の場合のみプログレスバー表示(2025.9.8yori)
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_WARMUP_ING;
            break;

        case VEC_STEP_SEQ::ARM_WARMUP_ING: // アーム温度監視中(2025.7.17yori)
            if (HwCtrl::m_hVecCnt.m_Sts.m_Warm == 0 ||  // 0:正常
                HwCtrl::m_hVecCnt.m_Sts.m_Warm == 1 ||  // 1:温度勾配警告
                HwCtrl::m_hVecCnt.m_Sts.m_Warm == 2)    // 2:温度補正不可能
            {
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_WARMUP_CMP;
            }
            break;

        case VEC_STEP_SEQ::ARM_WARMUP_CMP: // アーム温度監視終了(2025.7.16yori)
            UsrMsg::CallBack(UsrMsg::WM_DlgPrgBar1_Close); // プログレスバー非表示(2025.7.17yori)
            if (HwCtrl::m_hVecCnt.m_VecInitflag) // 初期化が完了していたら
            {
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE_CMP;
            }
            else
            {
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_CMP;
            }
            break;

        case VEC_STEP_SEQ::INITIALIZE_REQ:
            ret = HwCtrl::Func09(); // ステータスチェック(2025.11.11yori)
            if (!HwCtrl::m_b_Button_ConnectFlag && HwCtrl::m_hVecCnt.m_VecInitflag) // PolyWorksから接続かつ初期化が完了していた場合
            {
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE_CMP;
            }
            else
            {
                ret = HwCtrl::Func07(); // イニシャライズモードへ変更
                if (ret == 0)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE_ING;
                    if (!HwCtrl::m_b_Button_ConnectFlag) UsrMsg::CallBack(UsrMsg::WM_MainWnd_Btn01); // 接続メニュー表示(2025.6.5yori)
                    if (!HwCtrl::m_b_Button_ConnectFlag) UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Btn03); // C#側にイニシャライズ画面表示要求を出す 2025.5.28 add eba
                    if (!HwCtrl::m_b_Button_ConnectFlag) UsrMsg::CallBack(UsrMsg::WM_InitPanel_Setup); // イニシャライズ画面の初期設定(2025.11.12yori)
                }
                else
                {
                    // 通信エラー
                    resultMsg = UsrMsgBox::CallBack(270, 268, 4, 16);
                    if (resultMsg == 6)
                    {
                        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
                    }
                    else
                    {
                        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
                    }
                }
            }

            break;

        case VEC_STEP_SEQ::INITIALIZE_ING:
            ret = HwCtrl::Func09(); // ステータスチェック
            if (ret == 0 && HwCtrl::m_hVecCnt.m_VecInitflag) // 初期化が完了したら
            {
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE_CMP;
            }
            else
            {
                // 終わるまで繰り返す
                UsrMsg::CallBack(UsrMsg::WM_InitPanel_Update); // 追加(2025.7.11yori)
            }
            break;

        case VEC_STEP_SEQ::INITIALIZE_CMP:
            ret = HwCtrl::Func08();   // 有接触モードへ変更
            if (ret == 0)
            {
                if (!HwCtrl::m_b_Button_ConnectFlag) // アプリから接続した場合は、下記を実行しない。(2025.6.10yori)
                {
                    ret = HwCtrl::Func10();   // PolyWorksへイニシャライズ完了通知
                    ret = HwCtrl::Func12();   // 測定音OFF
                    UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Close); // SubWindow1閉じる 2025.6.5yori
                }
                else
                {
                    UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Panel_Hide); // イニシャライズ画面非表示(2025.7.14yori)
                }

                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
            }
            else
            {
                // 通信エラー
                resultMsg = UsrMsgBox::CallBack(270, 268, 4, 16);
                if (resultMsg == 6)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
                }
                else
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
                }
            }   
            break;

        case VEC_STEP_SEQ::INITIALIZE_CAN: // イニシャライズをキャンセルした場合(2025.10.28yori)
            if (!HwCtrl::m_b_Button_ConnectFlag) // アプリから接続していない場合
            {
                HwCtrl::AppCommandSend(APP_SEND_CMD::UNEXPECTED_DISCONNECION); // PolyWorksを切断状態する。
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::DISCONNECT_REQ;
                UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Close); // SubWindow1閉じる 2025.6.5yori
            }
            else
            {
                ret = HwCtrl::Func08(); // 有接触モードへ変更
                if (ret == 0)
                {
                    UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Panel_Hide); // イニシャライズ画面非表示
                }
                else
                {
                    // 通信エラー
                    resultMsg = UsrMsgBox::CallBack(270, 268, 4, 16);
                    if (resultMsg == 6)
                    {
                        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
                    }
                    else
                    {
                        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
                    }
                }
            }
            break;

        case VEC_STEP_SEQ::INITIALIZE0_REQ: // 0軸イニシャライズ要求(2025.6.9yori)
            ret = HwCtrl::Func25(); // 0軸イニシャライズモードへ変更
            if (ret == 0)
            {
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE0_ING;
                if (!HwCtrl::m_b_Button_ConnectFlag) UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Btn04); // 0軸イニシャライズ画面表示(2025.7.25yori)
                UsrMsg::CallBack(UsrMsg::WM_Init0Panel_Setup); // イニシャライズ画像表示(2025.10.2yori)
            }
            else
            {
                // 通信エラー
                resultMsg = UsrMsgBox::CallBack(270, 268, 4, 16);
                if (resultMsg == 6)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
                }
                else
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
                }
            }
            break;

        case VEC_STEP_SEQ::INITIALIZE0_ING: // 0軸イニシャライズ中(2025.6.9yori)
            ret = HwCtrl::Func09(); // ステータスチェック
            if (ret == 0)
            {
                if (HwCtrl::m_hVecCnt.m_VecInitflag)     // 初期化が完了していたら
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE0_CMP;
                    if (!HwCtrl::m_b_Button_ConnectFlag) // アプリから接続した場合は、SubWindow1閉じない。(2025.6.10yori)
                    {
                        UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Close); // SubWindow1閉じる(2025.6.10yori)
                    }
                }
                else
                {
                    // 終わるまで繰り返す
                }
            }
            else
            {
                // 通信エラー
                resultMsg = UsrMsgBox::CallBack(270, 268, 4, 16);
                if (resultMsg == 6)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
                }
                else
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
                }
            }
            break;

        case VEC_STEP_SEQ::INITIALIZE0_CMP: // 0軸イニシャライズ完了(2025.6.9yori)
            if (HwCtrl::m_ScannerConnectBtnFg == false) // スキャナ接続完了ボタンが押されてなければ有接触モードへ変更する。(2025.9.2yori)
            {
                ret = HwCtrl::Func08(); // 有接触モードへ変更
                if (ret == 0)
                {
                    if (!HwCtrl::m_b_Button_ConnectFlag) // アプリから接続した場合は、下記を実行しない。(2025.7.25yori)
                    {
                        UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Close); // SubWindow1を閉じる
                    }
                    else
                    {
                        UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Panel_Hide); // 0軸イニシャライズ画面非表示(2025.7.25yori)
                    }

                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
                }
                else
                {
                    // 通信エラー
                    resultMsg = UsrMsgBox::CallBack(270, 268, 4, 16);
                    if (resultMsg == 6)
                    {
                        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
                    }
                    else
                    {
                        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
                    }
                }
            }
            else // スキャナ接続完了ボタンが押されていれば非接触モードへ変更する。(2025.9.2yori)
            {
                ret = HwCtrl::Func08(); // 有接触モードへ変更(メモ：イニシャライズモードから非接触モードへ移行できないようだ。)(2025.9.2yori)
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_INIT_ING;
                HwCtrl::m_ScannerConnectBtnFg = false;
            }
            break;

        case VEC_STEP_SEQ::MODE_SW_REQ: // モード切替(2025.8.12yori)
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MODE_SW_ING;
            break;

        case VEC_STEP_SEQ::MODE_SW_ING: // モード切替中(2025.8.12yori)
            break;

        case VEC_STEP_SEQ::MODE_SW_CMP: // モード切替終了(2025.8.12yori)
            break;

        case VEC_STEP_SEQ::OPEN_MENUDIALOG_REQ: // 有接触設定メニュー表示(2025.7.18yori)
            UsrMsg::CallBack(UsrMsg::WM_MainWnd_Btn02);
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_SET_ING;
            break;

        // PolyWorksへスタイラス直径を送り、表示する。(2025.7.18yori)
        // PolyWorksからイニシャライズ完了後に要求される。(2025.11.12yori)
        case VEC_STEP_SEQ::PROBE_PROPETY_REQ:
            ret = HwCtrl::Func51();
            if (ret == 0)
            {
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
            }
            else
            {
                // C#へ通信エラーメッセージは保留(通信コマンドでは無いため)2025.11.12 eba memo
            }
            break;

        case VEC_STEP_SEQ::SCANNER_SET_REQ: // スキャナパラメータ設定(2025.8.10yori)
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SET_ING;
            break;

        case VEC_STEP_SEQ::SCANNER_SET_ING: // スキャナパラメータ設定中(2025.8.10yori)
            break;

        case VEC_STEP_SEQ::SCANNER_SET_CMP: // スキャナパラメータ設定完了(2025.8.10yori)
            break;

        case VEC_STEP_SEQ::ALIGNMENT_REQ: // アライメント(2025.6.11yori)
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ALIGNMENT_ING;
            break;

        case VEC_STEP_SEQ::ALIGNMENT_ING: // データ取り込み、計算シーケンス中(2025.6.11yori)
            ret = CalibComm::CntDataInputThread();
            if (ret == 1) UsrMsg::CallBack(UsrMsg::WM_ContactInspectionPanel_MesCallBack);
            else if (ret == -1)
            {
                // 通信エラー
                resultMsg = UsrMsgBox::CallBack(270, 268, 4, 16);
                if (resultMsg == 6)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
                }
                else
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
                }
            }
            break;

        case VEC_STEP_SEQ::ALIGNMENT_ING2: // データと転送、表示シーケンス中 2025.9.10 add eba
            UsrMsg::CallBack(UsrMsg::WM_ContactInspectionPanel_ParaOutCallBack);
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ALIGNMENT_ING;
            break;

        case VEC_STEP_SEQ::ALIGNMENT_CMP: // アライメント終了(2025.6.11yori)
            //HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
            break;

        case VEC_STEP_SEQ::SCANNER_MAKE_MATRIX_REQ: // 非接触点検キャリブ座標系作成要求(2025.12.5yori)
            UsrMsg::CallBack(UsrMsg::WM_ScannerAlignmentPanel_Show);
            UsrMsg::CallBack(UsrMsg::WM_ScannerAlignmentPanel_Setup);
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_MAKE_MATRIX_ING;
            break;

        case VEC_STEP_SEQ::SCANNER_MAKE_MATRIX_ING: // 非接触点検キャリブ座標系作成(2025.12.8yori)
            ret = HwCtrl::Func05(&PosiData);
            if ((ret == 0) && (PosiData.button & 0x01) == 0x01 && (PosiData.no != -1) && (HwCtrl::m_hVecCnt.m_GetdataNo != 0)) // SW1(トリガボタンを押した場合)
            {
                HwCtrl::ConvertVecCtExTranceData(&PosiData, &VecData); // 構造体の内容が異なるため変換が必要
                TdsVecSetMakeMatrixData(HwCtrl::m_ShotNo, &VecData);
                HwCtrl::m_ShotNo++;
                UsrMsg::CallBack(UsrMsg::WM_ScannerAlignmentPanel_MesCallBack);
                if (HwCtrl::m_ShotNo == HwCtrl::m_ShotMax)
                {
                    MakeMtxResult Result;
                    TdsVecExecMakeMatrix(HwCtrl::m_hVecCnt.VecSts_GetProbeDia(), &Result);	// 座標系作成を実行
                    TdsVecSetMatrix(Result.dMatrix); // マトリクスを設定
                    TdsVecSetSphCod(Result.dSphere); // 球座標を設定
                    UsrMsg::CallBack(UsrMsg::WM_SubWnd02_Close);
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_INIT_REQ;
                    HwCtrl::m_ShotNo = 0;
                    HwCtrl::m_ScannerAlignmentScannerFlag = true; // 追加(2025.12.18yori)
                }
            }
            break;

        case VEC_STEP_SEQ::ARM_SELFCHECK_REQ: // 有接触自己診断(2025.6.11yori)
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_SELFCHECK_ING;
            break;

        case VEC_STEP_SEQ::ARM_SELFCHECK_ING: // 有接触自己診断中(2025.6.11yori)
            if (HwCtrl::m_MaintModeFlag == true) // 追加(2025.10.6yori)
            {
                ret = HwCtrl::Func29(); //メンテナンスモードへ変更
                if (ret == 0)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_SELFCHECK_ING2;
                }
                else
                {
                    // 通信エラー
                    resultMsg = UsrMsgBox::CallBack(270, 268, 4, 16);
                    if (resultMsg == 6)
                    {
                        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
                    }
                    else
                    {
                        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
                    }
                }
                
            }
            UsrMsg::CallBack(UsrMsg::WM_ContactSelfJudgmentPanel_Update); // C#側に有接触自己診断更新要求(2025.10.3yori)
            break;

        case VEC_STEP_SEQ::ARM_SELFCHECK_ING2: // 有接触自己診断のカウントチェック2(2025.10.6yori)
            if (HwCtrl::m_MaintModeFlag == false)
            {
                ret = HwCtrl::Func08(); // 有接触モードへ変更
                if (ret == 0)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_SELFCHECK_ING;
                }
                else
                {
                    // 通信エラー
                    resultMsg = UsrMsgBox::CallBack(270, 268, 4, 16);
                    if (resultMsg == 6)
                    {
                        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
                    }
                    else
                    {
                        HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
                    }
                }
            }
            UsrMsg::CallBack(UsrMsg::WM_ContactSelfJudgmentPanel_Update); // C#側に有接触自己診断更新要求
            break;

        case VEC_STEP_SEQ::ARM_SELFCHECK_CMP: // 有接触自己診断終了(2025.6.11yori)
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
            break;

        case VEC_STEP_SEQ::ARM_SET_REQ: // アーム設定要求(2025.9.1yori)
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ARM_SET_ING;
            break;

        case VEC_STEP_SEQ::ARM_SET_REQ2: // アーム設定要求(2025.10.31yori)
            // 何もしない。
            break;

        case VEC_STEP_SEQ::ARM_SET_ING: // アーム設定中(2025.9.1yori)
            //// IDの変更があった場合、C#側にステータス更新要求を送る。(2025.9.8yori)
            HwCtrl::pbid_chg_old_fg = PosiData.pbid_chg_fg;
            ret = HwCtrl::Func05(&PosiData);
            if(PosiData.pbid_chg_fg != HwCtrl::pbid_chg_old_fg) UsrMsg::CallBack(UsrMsg::WM_UpdateData1);
            ////
            break;

        case VEC_STEP_SEQ::MEAS_IDLE:
            HwCtrl::pbid_chg_old_fg = PosiData.pbid_chg_fg; // 追加(2025.10.2yori)
            ret = HwCtrl::Func05(&PosiData);
            // 測定中に異常があった場合のエラー処理をちゃんとすること 2025.5.27 memo eba
            if (ret == 0)
            {
                // アプリから接続した場合は、PolyWorksへデータ送信しない。(2025.6.10yori)
                if (HwCtrl::m_b_Button_ConnectFlag == false) // FullMoonのテスト環境の場合はif文をコメントアウトする。(2025.12.22yori)
                {
                    // PolyWorksへデータ送信
                    if (HwCtrl::m_hVecCnt.m_Sts.m_enMode == VEC_MODE_PROBE && HwCtrl::m_hVecCnt.m_VecInitflag == true)
                    {
                        HwCtrl::Func11(PosiData);
                    }

                    // プローブID変更があった場合(2025.10.2yori)
                    if (PosiData.pbid_chg_fg != HwCtrl::pbid_chg_old_fg)
                    {
                        ret = HwCtrl::Func09();
                        if (ret == 0 && HwCtrl::m_hVecCnt.m_Sts.m_No0Fg == 1 && HwCtrl::m_hVecCnt.m_Sts.m_iProbeId != 0) // No.0関節の有無確認、スキャナ(ID=0)はここでイニシャライズしない。
                        {
                            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::INITIALIZE0_REQ; // 0軸イニシャライズ要求(2025.10.2yori)
                            UsrMsg::CallBack(UsrMsg::WM_MainWnd_Btn01); // 接続メニュー表示
                        }
                    }
                }
            }
            else
            {
                // 通信エラー
                resultMsg = UsrMsgBox::CallBack(270, 268, 4, 16);
                HwCtrl::Func04(); // 有接触切断
                if (resultMsg == 6)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::CONNECT_REQ;
                }
                else
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
                }
            }
            break;

        case VEC_STEP_SEQ::SCANNER_INIT_REQ:
            UsrMsg::CallBack(UsrMsg::WM_MainWnd_Btn01); // 接続メニュー表示(2025.9.2yori)
            UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Btn05); // スキャナ接続画面表示(2025.9.2yori)
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_CONNECT_BTN_ONOFF;
            break;

        case VEC_STEP_SEQ::SCANNER_CONNECT_BTN_ONOFF: // スキャナ接続完了ボタン待ち(2025.9.2yori)
            Sleep(100);
            break;

        case VEC_STEP_SEQ::SCANNER_INIT_ING:
            UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Close); // VEC_STEP_SEQ::SCANNER_WARMUP_CMPから移動、接続完了ボタンを押したら、SubWindwow1を閉じる。(2025.11.25yori)
            //UsrMsg::CallBack(UsrMsg::WM_DlgPrgBar2_Show); // VEC_STEP_SEQ::SCANNER_INIT_REQから移動(2025.9.2yori) // 一時的にコメントアウト、後で調査(2025.10.27yori)
            if (HwCtrl::Func09() == 0) HwCtrl::m_ProbeIdBeforeScanner = HwCtrl::m_hVecCnt.m_Sts.m_iProbeId; // 非接触モードへ変更する前のプローブID取得(2025.11.20yori)
            ret = HwCtrl::Func14(); // ID0→非接触モードへ変更→スキャナ電源ON→接続→初期化
            if (ret == ERROR_CODE::ERROR_CODE_NONE) // ここで初期化が終わったかチェック
            {
                //UsrMsg::CallBack(UsrMsg::WM_DlgPrgBar2_Close); // プログレスバーHIDE 2025.5.27 mwmo eba // 一時的にコメントアウト、後で調査(2025.10.27yori)
                if (HwCtrl::m_ScannerWarmUpMonitorFlag) // 暖機待ち処理追加(2025.7.30yori)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_WARMUP_ING;
                    UsrMsg::CallBack(UsrMsg::WM_DlgPrgBar3_Show); // 暖機監視プログレスバー表示(2025.7.29yori)
                }
                else
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_INIT_CMP;
                    UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Close); // SubWindow1非表示(2025.8.22yori)
                    UsrMsg::CallBack(UsrMsg::WM_MainWnd_Btn03); // SubWindow3表示(2025.8.22yori)
                }
            }
            else
            {
                UsrMsgBox::CallBack(271, 268, 0, 16); // エラーメッセージ表示
                if (HwCtrl::m_ScannerAlignmentScannerFlag) // 非接触点検キャリブレーションの場合(2026.1.23yori)
                {
                    HwCtrl::Func08(); // 有接触モードへ変更
                    HwCtrl::Func12(); // 有接触測定音OFF
                    UsrMsg::CallBack(UsrMsg::WM_MainWnd_Btn02); // 有接触設定メニュー表示
                    UsrMsg::CallBack(UsrMsg::WM_ScannerAlignmentPanel_Show); // アライメント画面表示
                    UsrMsg::CallBack(UsrMsg::WM_ScannerAlignmentPanel_Setup); // アライメント画面の初期設定
                    HwCtrl::m_ScannerAlignmentScannerFlag = false;
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_MAKE_MATRIX_ING;
                }
                else if (HwCtrl::m_b_Button_ConnectFlag == false) // 非接触点検キャリブレーションではない場合(2026.1.23yori)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
                    HwCtrl::AppCommandSend(APP_SEND_CMD::SCANNER_CONNECT_CANCEL);// PolyWorks側にスキャナ接続キャンセルを知らせる。→PolyWorks側からスキャナとアームの切断が通知される。(2026.1.3yori)
                }
            }
            break;

        case VEC_STEP_SEQ::SCANNER_WARMUP_ING:
            HwCtrl::Func53(&warmup_fg);
            if (warmup_fg == TRUE)
            {
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_WARMUP_CMP;
            }
            break;

        case VEC_STEP_SEQ::SCANNER_WARMUP_CMP: // 暖機監視終了(2025.8.22yori)
            UsrMsg::CallBack(UsrMsg::WM_DlgPrgBar3_Close); // 暖機監視プログレスバー非表示(2025.7.29yori) // VEC_STEP_SEQ::SCANNER_WARMUP_INGから移動(2025.8.22yori)
            //UsrMsg::CallBack(UsrMsg::WM_SubWnd01_Close); // SubWindow1非表示(2025.6.10yori) // VEC_STEP_SEQ::SCANNER_INIT_CMPから移動し、修正(2025.8.21yori) // コメントアウト(2025.11.25yori)
            if (HwCtrl::m_b_Button_ConnectFlag &&                   // アプリから接続した場合は、SubWindow3を表示する。(2025.6.10yori) // VEC_STEP_SEQ::SCANNER_INIT_CMPから移動し、修正(2025.8.21yori)
                HwCtrl::m_ScannerAlignmentScannerFlag == false)     // 点検キャリブレーションではない場合(2025.12.18yori)
            {
                UsrMsg::CallBack(UsrMsg::WM_MainWnd_Btn03); // 非接触設定メニュー表示
            }
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_INIT_CMP;
            break;

        case VEC_STEP_SEQ::SCANNER_INIT_CMP:
            if (HwCtrl::m_ScannerAlignmentScannerFlag) // 非接触点検キャリブレーションの場合(2025.12.8yori)
            {
                HwCtrl::m_ScannerAlignmentProbeFlag = false; // 追加(2025.12.18yori)
                HwCtrl::m_Type = int(CALIB_TYPE::SCANNER_FULL);
                UsrMsg::CallBack(UsrMsg::WM_MainWnd_Btn02);
                UsrMsg::CallBack(UsrMsg::WM_ScannerAlignmentPanel_Show);
                UsrMsg::CallBack(UsrMsg::WM_ScannerAlignmentPanel_Setup);
            }
            else if (HwCtrl::m_b_Button_ConnectFlag == false) // 非接触点検キャリブレーションではない場合(2026.1.20yori)
            {
                HwCtrl::AppCommandSend(APP_SEND_CMD::SCANNER_INITIALIZE_SUCCESS); // 追加(2026.1.9yori)
            }
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SCAN_MEAS_IDEL;
            Sleep(100);
            break;

        case VEC_STEP_SEQ::SCANNER_SCAN_START_REQ:

            ////// test only 2026.01.12 t.kanamura
            //for (int i = 0; i < 11; i++) {
            //    HwCtrl::gDistHist[i] = 0;
            //}

            HwCtrl::m_PointerCheckLineNo = 1; // 追加(2025.7.4yori)
            HwCtrl::m_ScanShotOldNo = HwCtrl::m_ScanShotNo; // 追加(2025.12.6yori)
            HwCtrl::Func18(); // スキャン(Thread2)開始
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SCAN_START_CMP;
            break;

        case VEC_STEP_SEQ::SCANNER_SCAN_START_CMP:
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SCAN_MEAS_IDEL;
            break;

        case VEC_STEP_SEQ::SCANNER_SCAN_MEAS_IDEL:
            // PolyWorksから接続かつ非接触設定メニューの閉じるボタンを押した場合(2025.11.11yori)
            if (HwCtrl::m_b_Button_ConnectFlag == false && HwCtrl::m_ScannerSettingCloseFlag == true)
            {
                UsrMsg::CallBack(UsrMsg::WM_SubWnd03_Close); // SubWindow3非表示(2025.11.11yori)
                HwCtrl::m_ScannerSettingCloseFlag = false;
            }

            if (HwCtrl::m_ScannerAlignmentScannerFlag) // 非接触点検キャリブレーションの場合(2025.12.5yori)
            {
                if (HwCtrl::m_ScanShotNo != HwCtrl::m_ScanShotOldNo)
                {
                    HwCtrl::m_ScanShotOldNo = HwCtrl::m_ScanShotNo;
                    UsrMsg::CallBack(UsrMsg::WM_ScannerAlignmentPanel_MesCallBack);
                }

                if (HwCtrl::CalcFg) HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_ALIGNMENT_REQ; // 計算中(2025.12.10yori)

                if (HwCtrl::EndFg) // 全ての点検、キャリブデータを取得した場合(2025.12.8yori)
                {
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SCAN_STOP_REQ;
                    UsrMsg::CallBack(UsrMsg::WM_ScannerAlignmentPanel_ReultCallBack);
                    HwCtrl::EndFg = false; // 追加(2025.12.17yori)
                }
            }
            Sleep(100);
            break;

        case VEC_STEP_SEQ::SCANNER_SCAN_STOP_REQ:
            HwCtrl::Func20(); // スキャン停止
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SCAN_STOP_CMP;
            //sprintf_s(text, 256, "m_Afterdist2:%.9f\n", HwCtrl::m_Afterdist2); // デバッグ(2026.1.12yori)
            //OutputDebugStringA(text); // デバッグ(2026.1.12yori)
            //HwCtrl::m_Afterdist2 = 0.0; // デバッグ(2026.1.12yori)
            break;
        case VEC_STEP_SEQ::SCANNER_SCAN_STOP_CMP: // SCANNER_SCAN_MEAS_IDELから移動(2025.12.8yori)
            Sleep(100);
            break;
        
        case VEC_STEP_SEQ::OPEN_SCANNER_MEAS_DIALOG_REQ: // PolyWorksの設定ボタンが押され、非接触設定メニューを表示する。(2025.9.3yori)
            UsrMsg::CallBack(UsrMsg::WM_MainWnd_Btn03); // SubWindow3表示
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SCAN_MEAS_IDEL;
            break;

        case VEC_STEP_SEQ::SCANNER_DISCONNECT_REQ: // スキャナ切断処理(2025.9.3yori)
            HwCtrl::Func76(); // スキャナ終了前のモード取得→スキャナ電源OFF→スキャナ終了処理→スキャナ測定音ON
            HwCtrl::Func08(); //有接触モードへ変更
            if(HwCtrl::Func09() == 0) HwCtrl::Func50(HwCtrl::m_ProbeIdBeforeScanner, HwCtrl::m_hVecCnt.m_Sts.m_dia); // 非接触モードへ切り替える前のプローブIDへ戻す。(2025.11.20yori)
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_DISCONNECT_CMP;
            break;

        case VEC_STEP_SEQ::SCANNER_DISCONNECT_CMP: // スキャナ切断処理完了(2025.9.3yori)
            Sleep(100);
            break;

        case VEC_STEP_SEQ::SCANNER_ALIGNMENT_REQ: // 非接触点検キャリブ要求(2025.12.5yori)
            ProgBar::CallBackShow(2); // 計算中のプログレスバー表示(2025.12.10yori)
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_ALIGNMENT_ING;
            break;

        case VEC_STEP_SEQ::SCANNER_ALIGNMENT_ING: // 非接触点検キャリブ(2025.12.5yori)
            if (!HwCtrl::CalcFg) // 計算が終了した場合(2025.12.10yori)
            {
                ProgBar::CallBackHide();
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_SCAN_MEAS_IDEL;
            }
            Sleep(100);
            break;

        case VEC_STEP_SEQ::SENS_CHECK_REQ: // 感度チェック(2025.7.2yori)
            HwCtrl::Func49(); // 感度チェック開始
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SENS_CHECK_ING;
            break;

        case VEC_STEP_SEQ::SENS_CHECK_ING: // 感度チェック中(2025.7.2yori)
            break;

        case VEC_STEP_SEQ::SENS_CHECK_CMP: // 感度チェック完了(2025.7.2yori)
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
            break;

        // ポインタ位置チェック作成中のため、コメントアウト(2025.9.3yori)
        //case VEC_STEP_SEQ::POINTER_CHECK_REQ: // ポインタ位置チェック(2025.7.3yori)
        //    HwCtrl::m_PointerCheckFg = true;
        //    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::POINTER_CHECK_ING;
        //    break;

        //case VEC_STEP_SEQ::POINTER_CHECK_ING: // ポインタ位置チェック中(2025.7.3yori)
        //    break;

        //case VEC_STEP_SEQ::POINTER_CHECK_CMP: // ポインタ位置チェック完了(2025.7.3yori)
        //    HwCtrl::m_PointerCheckFg = false;
        //    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
        //    break;

        case VEC_STEP_SEQ::DISCONNECT_REQ:
            if (HwCtrl::m_hVecCnt.m_connectflag == true) // 接続している場合を追加、PolyWorksを再起動したときに再接続できるようにする。(2025.12.31yori)
            {
                ret = HwCtrl::Func08();   // 有接触モードへ変更
                ret |= HwCtrl::Func13(); // 有接触測定音ON
                ret |= HwCtrl::Func04(); // 有接触切断
                if (ret == 0)
                {
                    if (!HwCtrl::m_b_Button_ConnectFlag)
                    {
                        HwCtrl::AppCommandSend(APP_SEND_CMD::DISCONNECT_SUCCESS); // 切断に成功したことをPolyWorks側に知らせる(2025.6.9yori)
                        //UsrMsg::CallBack(UsrMsg::WM_MainWnd_OtherApp_Disconnected); // C#側にPolyWorks側から切断したことを知らせる。(2025.11.19yori) // アプリ単体動作は作成中のため、最初から接続、設定ボタンを押せないようにする。(2025.12.26yori)
                    }
                    HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::DISCONNECT_CMP;
                }
                else
                {
                    if (!HwCtrl::m_b_Button_ConnectFlag) HwCtrl::AppCommandSend(APP_SEND_CMD::DISCONNECT_FAILURE); // 切断に失敗したことをPolyWorks側に知らせる(2025.6.9yori)
                }
            }
            else
            {
                HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;
            }
            break;

        case VEC_STEP_SEQ::DISCONNECT_CMP:
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::FINISH;    // 2025.7.2 eba add
            break;

        default:
            HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::START;    // 2025.7.2 eba add
            slp_tm = 100;
            break;
        }

        ReleaseSemaphore(HwCtrl::hSEMA_VSEQ, 1, NULL);

        Sleep(slp_tm);
    }
}
