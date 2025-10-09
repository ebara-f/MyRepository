/***********************************************************************

    コマンド群を束ねるクラス

***********************************************************************/

#include "HwCtrl.h"
//// 追加(2025.5.15yori)
#include <thread>
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")
////

#include "UsrMsg.h"

/***********************************************************************

    スタティック変数(2025.5.15yori)

***********************************************************************/

CVecCnt         HwCtrl::m_hVecCnt;
int             HwCtrl::pbid_chg_old_fg = 0; // プローブID の変更があったことを知らせる一つ前のフラグ(2025.9.8yori)
HANDLE          HwCtrl::m_hGetScanDataThread = NULL;
bool            HwCtrl::m_bGetThreadStopFlag = true;
HANDLE          HwCtrl::hSEMA = NULL;
HANDLE          HwCtrl::hSEMA_VSEQ = NULL;
int             HwCtrl::iScannerConnect = 0;
Status*         HwCtrl::ptstatus; 
OneLineData2*   HwCtrl::ptlinedata2025 = NULL;
int             HwCtrl::m_iXSize = 0;
double          HwCtrl::m_dXPitch = 0.0;
bool            HwCtrl::m_bmeasfg = false;
NCON_MEAS_SEQ   HwCtrl::m_ScanDataStepCounter;
DWORD           HwCtrl::m_StepStartTime;
bool            HwCtrl::m_bSwSts = false;
bool            HwCtrl::m_bOldSwSts = false;
DWORD           HwCtrl::m_SwTime;
DWORD           HwCtrl::m_OldSwTime;
int             HwCtrl::m_LineNo = 0;
int             HwCtrl::m_iSn = 0;
int             HwCtrl::m_iSw = 0;
int             HwCtrl::m_ScanShotNo = 0;
bool            HwCtrl::m_bReadThreadStopFlag = true;
bool            HwCtrl::EndFg = false;
const double    HwCtrl::INVALID_CHECK = 999998.0;
VEC_STEP_SEQ    HwCtrl::m_VecStepSeq;
bool            HwCtrl::m_b_Button_ConnectFlag = false; // 追加(2025.6.10yori)
bool	        HwCtrl::m_ArmWarmUpMonitorFlag = true; // 追加(2025.7.18yori)
bool	        HwCtrl::m_ScannerWarmUpMonitorFlag = true; // 追加(2025.7.30yori)
bool	        HwCtrl::m_ScannerWarmUpMonitorCancelFlag = false; // 追加(2025.8.22yori)
bool            HwCtrl::m_ScannerConnectBtnFg = false; // 追加(2025.9.2yori)
bool            HwCtrl::m_MaintModeFlag = false; // 追加(2025.10.6yori)
unsigned short  HwCtrl::m_BrightSlice[5] = { 0x5FD0, 0x5FD0, 0x5FD0, 0x5FD0, 0x5FD0 }; // 輝度スライス(2025.8.25yori)
unsigned short  HwCtrl::m_SensSlice[5] = { 0x0CCC, 0x04B0, 0x0CCC, 0x0CCC, 0x0CCC }; // 感度スライス(2025.8.25yori)
double          HwCtrl::m_Angle = 70.0; // 角度マスク(2025.8.25yori)
int             HwCtrl::m_Edge = 3; // エッジマスク(2025.8.25yori)
DWORD           HwCtrl::m_Address = 0xC0A801C8; // スキャナのIPアドレス初期値「192.168.10.200(0xC0A80AC8)」、一時的にIPアドレスを「192.168.1.200(0xC0A801C8)」へ変更(2025.6.19yori)
DWORD           HwCtrl::m_Subnet = 0xFFFFFF00; // スキャナのサブネットマスク初期値「255.255.255.0」(2025.6.19yori)
DWORD           HwCtrl::m_Gateway = 0xC0A80A01; // スキャナのデフォルトゲートウェイ初期値「192.168.10.1」(2025.6.19yori)
DWORD           HwCtrl::m_DNS = 0x00000000; // スキャナのDNSサーバー初期値「0.0.0.0」(2025.6.23yori)
PulsZMask*      HwCtrl::m_ptZMask = NULL; // 距離マスク(2025.6.20yori)
SelfChkLatchResult* HwCtrl::m_ptLatchResult = NULL; // ラッチ通信チェック(2025.6.24yori)
SelfChkMotorResult* HwCtrl::m_ptMotorResult = NULL; // モーターチェック(2025.6.24yori)
SelfChkSensResult* HwCtrl::m_ptSensResult = NULL; // モーターチェック(2025.6.24yori)
bool            HwCtrl::m_PointerCheckFg = false; // ポインタ位置チェック(2025.7.3yori)
double          HwCtrl::m_PointerCheckScanData = 0; // ポインタ位置チェック用データ(2025.7.4yori)
int             HwCtrl::m_PointerCheckLineNo = 1; // ポインタ位置チェック用ライン数(2025.7.4yori)



/***********************************************************************

    コマンド01
    有接触接続
    変更(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func01()
{
    int ret = 0;

    // VECTORONと接続開始
    ret = HwCtrl::m_hVecCnt.VecOpen(20000, NULL);

    // 機種を識別するため、バージョン取得する。(2025.6.10yori)
    ret = HwCtrl::m_hVecCnt.VecCmd_GetVecVer();

    // アプリ単体でVECTORONと接続する場合もあるため、
    // PolyWorksへのコマンド送信はここでは行わない(2025.6.6yori)

    UsrMsg::CallBack(UsrMsg::WM_UpdateData1); // C#側に結果を知らせる(テスト2025.5.22 eba)

    return ret;
}



/***********************************************************************

    コマンド02

***********************************************************************/

int HwCtrl::Func02(
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

int HwCtrl::Func03(
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

    コマンド04
    有接触切断
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func04()
{
    int ret = 0;

    // VECTORONと切断
    ret = m_hVecCnt.VecClose();

    // アプリ単体でVECTORONと接続する場合もあるため、
    // PolyWorksへのコマンド送信はここでは行わない(2025.6.9yori)

    return ret;
}



/***********************************************************************

    コマンド05
    有接触データ要求
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func05(VecDtEx* vecdata)
{
    int ret = 0;

    ret = m_hVecCnt.VecFunc_DataRequestEx(vecdata, 1);

    return ret;
}



/***********************************************************************

    コマンド06
    モード取得
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func06(VEC_MODE* mode)
{
    int ret = 0;
    ret = m_hVecCnt.VecCmd_GetVecStatus();
    *mode = m_hVecCnt.m_Sts.m_GetMode;
    return ret;
}



/***********************************************************************

    コマンド07
    イニシャライズモードへ変更
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func07()
{
    int ret = 0;

    ret = m_hVecCnt.VecCmd_ChangeMode(VEC_MODE::VEC_MODE_RE_INIT);
    //ret = m_hVecCnt.VecCmd_ChangeMode(VEC_MODE::VEC_MODE_INITIALIZE);   // 2025.6.20 test eba
    return ret;
}



/***********************************************************************

    コマンド08
    有接触モードへ変更
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func08()
{
    int ret = 0;

    ret = m_hVecCnt.VecCmd_ChangeMode(VEC_MODE::VEC_MODE_PROBE);

    return ret;
}



/***********************************************************************

    コマンド09
    ステータス要求
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func09()
{
    int ret = 0;

    ret = m_hVecCnt.VecCmd_GetVecStatus();

    return ret;
}



/***********************************************************************

    コマンド10
    PolyWorksへイニシャライズ完了通知
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func10()
{
    int ret = 0;
    
    AppCommandSend(APP_SEND_CMD::ARM_INITIALIZE_ON);

    return ret;
}



/***********************************************************************

    コマンド11
    有接触データ要求→ PolyWorksへ有接触データ送信
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func11(VecDtEx vecdata)
{
    int ret = 0;
    int ret_send = 1;
    VecDtEx PosiData = vecdata;

    //ret = Func05(&PosiData);

    //if (ret == 0) { // 正常にデータ取得した場合
        ret_send = SendPolyworksMessage((int)QUE_NUM::MEASUREMENT_DATA, sizeof(PosiData), ((char*)&PosiData));
        if (ret_send != 0)
        {
            //エラー処理は後でコーディング(2025.5.8)
        }
    //}

    return ret;
}



/***********************************************************************

    コマンド12
    有接触測定音OFF
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func12()
{
    int ret = 0;

    m_hVecCnt.VecCmd_ChangeBeepMeas("OFF"); // 有接触測定音OFF

    return ret;
}



/***********************************************************************

    コマンド13
    有接触測定音ON
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func13()
{
    int ret = 0;

    m_hVecCnt.VecCmd_ChangeBeepMeas("ON"); // 有接触測定音ON

    return ret;
}



/***********************************************************************

    コマンド14
    ID0→非接触モードへ変更→スキャナ電源ON→接続→初期化
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func14()
{
    int ret = 0;

    ERROR_CODE ErrorCode = ERROR_CODE::ERROR_CODE_NONE;

    m_hVecCnt.VecCmd_ChangeProbe(0);
    m_hVecCnt.VecCmd_ChangeMode(VEC_MODE::VEC_MODE_LAZER_SCAN);
    AppCommandSend(APP_SEND_CMD::SCANNER_CONNECT);

    ErrorCode = (ERROR_CODE)Func15(); // スキャナ接続と初期化

    if (ErrorCode != ERROR_CODE::ERROR_CODE_NONE)
    {
        // エラー処理は後でコーディング(2025.5.15yori)
    }
    else
    {
        if (iScannerConnect == 1) // スキャナの電源がONの場合
        {
            AppCommandSend(APP_SEND_CMD::SCANNER_INITIALIZE_SUCCESS);
        }
        else if (iScannerConnect == 2) // スキャナの電源がOFFの場合
        {
            TdsVecScannerPowerOn(); // スキャナへの供給電源をON
            ErrorCode = (ERROR_CODE)Func15(); // スキャナ接続と初期化

            if (ErrorCode == ERROR_CODE::ERROR_CODE_NONE)
            {
                if (iScannerConnect == 2) // スキャナの電源がOFFの場合
                {
                    // エラー処理は後でコーディング(2025.5.15yori)
                }
                else
                {
                    AppCommandSend(APP_SEND_CMD::SCANNER_INITIALIZE_SUCCESS);
                }
            }
            else
            {
                // エラー処理は後でコーディング(2025.5.15yori)
            }
        }
    }

    return (int)ErrorCode;
}



/***********************************************************************

    コマンド15
    スキャナ接続と初期化
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func15()
{
    BOOL bFg; // int retから変更(2025.7.30yori)
    ERROR_CODE ErrorCode = ERROR_CODE::ERROR_CODE_NONE;
    char address[4][8], subnet_dummy[4][8], gateway_dummy[4][8], dns_dummy[4][8]; // 追加(2025.8.28yori)
    DWORD d_address; // 追加(2025.8.28yori)

    // INIファイルを出力するフォルダーのパスを設定
    TdsVecSetIniFilePath("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles");

    // ログファイルを出力するフォルダーのパスを設定
    TdsVecSetLogFilePath("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Log");

    // IPアドレスをiniファイルから取得し、スキャナコントローラへ設定する。(2025.8.28yori)
    Func33(address, subnet_dummy, gateway_dummy, dns_dummy);
    d_address = (unsigned int)(atoi(address[0]) << 24) + (unsigned int)(atoi(address[1]) << 16) + (unsigned int)(atoi(address[2]) << 8) + (unsigned int)atoi(address[3]);
    TdsVecSetControllerAddress(d_address); //一時的にIPアドレスを「192.168.1.200(0xC0A801C8)」へ変更(2025.5.15yori) // iniファイルのIPアドレスを入力する。(2025.8.28yori)

    if (m_b_Button_ConnectFlag)
    {
        HwCtrl::Func60(); // スキャナ測定音ON(2025.8.12yori)
    }
    else
    {
        Func21(); // スキャナ測定音OFF、AppMain.cppから移動(2025.8.12yori)
    }

    iScannerConnect = TdsVecMeasInit();

    if (iScannerConnect == 1 )
    {
        bFg = TdsVecBufferClear(); // スキャナバッファクリア
        if ( bFg )
        {
            TdsVecChangeMode(TDS_MEASMODE_E);
            int     iXSize = 0;
            double	dXPitch = 0.0;
            int		iMeasMode = Func34(); // 変更(2025.8.12yori)
            TdsVecSetInterpolationX(TDS_INTERPOLATIONX_NONE); //補間なしに設定
        }
        else
        {
            ErrorCode = ERROR_CODE::ERROR_CODE_SCANBUFFER_CLEAR; // スキャナー側バッファがクリアーできない
        }

    }
    else
    {
        if (iScannerConnect == 0) // 追加(2025.7.30yori)
        {
            ErrorCode = ERROR_CODE::ERROR_CODE_SCANNER_INIT;
        }
        goto job_exit;
    }

    Func16(); // バッファクリア 

job_exit:
    
    return (int)ErrorCode;
}



/***********************************************************************

    コマンド16
    バッファデータのクリア
    シーケンスカウンタも1にすること
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func16()
{
    ERROR_CODE ErrorCode = ERROR_CODE::ERROR_CODE_NONE;

    // ベクトロン内の測定バッファをクリア
    int ret = m_hVecCnt.VecCmd_ReqVecBClr();
    if (ret != (int)VEC_RET_CODE::RET_CODE__OK)
    {
        ErrorCode = ERROR_CODE::ERROR_CODE_VECBUFFER_CLEAR; // べクロトン側バッファがクリアーできない
        goto job_exit;
    }
    else
    {
        VEC_MODE nowMode = m_hVecCnt.VecSts_GetMode(); // 現在のモードを返す 

        if ( nowMode == VEC_MODE::VEC_MODE_LAZER_SCAN )
        {
            BOOL bFg = TdsVecBufferClear(); // スキャナバッファクリア
            if (!bFg)
            {
                ErrorCode = ERROR_CODE::ERROR_CODE_SCANBUFFER_CLEAR; // スキャナー側バッファがクリアーできない
                goto job_exit;
            }
        }
    }

    ErrorCode = (ERROR_CODE)Func17(); // シーケンスカウンタを1にする

job_exit:

    return (int)ErrorCode;
}



/***********************************************************************

    コマンド17
    シーケンスカウンタをプリセット
    1にセットする
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func17()
{
    ERROR_CODE ErrorCode = ERROR_CODE::ERROR_CODE_NONE;

    int ret = m_hVecCnt.VecCmd_ReqVecSeqReset(); // 2021.03.30 S.Fukai data no clear(1)
                                                 // この作業を行わないとST_DATA_EXのnoが1から始まらない
    if (ret != (int)VEC_RET_CODE::RET_CODE__OK)
    {
        ErrorCode = ERROR_CODE::ERROR_CODE_SEQRESET; // シーケンスカウンタがリセットできない
    }
    return (int)ErrorCode;
}



/***********************************************************************

    コマンド18
    スキャン(Thread2)開始
    移植(2025.5.15yori)

***********************************************************************/

void HwCtrl::Func18()
{
    // 後でコーディング(2025.5.15yori)
    /*
    if (!Scan_Start_Check())
    {
        // 起動できる条件がそろわない 詳細エラーはScan_Start()で表示
        return;
    }
    */

    // スレッドが動いていない場合はスタートする
    // Thread2開始
    if ( m_bGetThreadStopFlag == true ) {
        m_ScanDataStepCounter = NCON_MEAS_SEQ::IDEL; // 0　- TREAD起動
        std::thread  Thread2(&HwCtrl::GetScanDataThread_new);
        m_hGetScanDataThread = Thread2.native_handle();
        Thread2.detach();
        m_bGetThreadStopFlag = false;
        while (m_ScanDataStepCounter == NCON_MEAS_SEQ::IDEL)
        {
            Sleep(10);	// 起動待ち
        }
    }
}



/***********************************************************************

    コマンド19
    PolyWorksへ非接触データ送信
    移植(2025.5.15yori)

    移植前のコメント
    データ読み出しスレッド
    GetScanDataThread_new()でVec&スキャナーから読み出しデータをptlinedata[]に積んでいるが
    そのデータをSendOneLineData()をQueにさらに積む
    2021.3.10

***********************************************************************/

//void HwCtrl::Func19()
//{
//    m_bReadThreadStopFlag = false;
//    int bRec = false;
//
//    while (m_bReadThreadStopFlag == false)
//    {
//        // Queに積みに行く
//        bRec = SendOneLineData();
//
//        //Queに積むことができなかった時は無視
//        if (bRec == false)
//        {
//            Sleep(10);
//        }
//
//        //スキャンスレッドが終了していたら
//        if (m_bGetThreadStopFlag == true)
//        {
//            if (ptstatus->readIx == ptstatus->writeIx)
//            {
//                //読み出すデータが無いので終了
//                m_bReadThreadStopFlag = true; // スレットを終了
//            }
//        }
//    }
//}



/***********************************************************************

    コマンド20
    スキャン停止
    移植(2025.5.15yori)

***********************************************************************/

void HwCtrl::Func20()
{
    if (m_bGetThreadStopFlag == true) return;					// 停止中は入らない
    if (m_ScanDataStepCounter == NCON_MEAS_SEQ::IDEL) return;	// Idel中は入らない

    //ダミースキャンが開始されるまで待機、ダミースキャンが開始される前に停止すると、ダミースキャンが停止しない(2022.3.25yori)
    int iMeasType = 0;
    TdsVecGetMeasType(&iMeasType);
    if (iMeasType == TDS_MEASTYPE_NORMAL && m_ScanDataStepCounter != NCON_MEAS_SEQ::MAIN_MEAS)
    {
        while (m_ScanDataStepCounter != NCON_MEAS_SEQ::DUMMY_MEAS)
        {
            Sleep(1);
        }
    }

    // スレッド終了フラグをONにする
    m_bGetThreadStopFlag = true;

    while (m_ScanDataStepCounter != NCON_MEAS_SEQ::FINISH)
    {
        Sleep(100); // スレッド終了待ち
    }
    
    //m_ScanDataStepCounter = NCON_MEAS_SEQ::IDEL; // コメントアウト(2025.5.15yori)
    
    Sleep(100);
}



/***********************************************************************

    コマンド21
    スキャナ測定音OFF
    移植(2025.5.15yori)

***********************************************************************/

void HwCtrl::Func21()
{
    WritePrivateProfileString(TEXT("Buzzer"), TEXT("0"), TEXT("0"), TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\TDSUser.ini"));
}



/***********************************************************************

    コマンド22
    アーム暖機、温度変化チェック
    追加(2025.6.4yori)

***********************************************************************/

int HwCtrl::Func22()
{
    int ret = 0;

    m_hVecCnt.VecCmd_Warm();

    return ret;
}


/***********************************************************************

    コマンド23
    C#メイン画面に測定器のステータスを渡す
    追加(2025.5.22 eba)
    テスト版
***********************************************************************/

int HwCtrl::Func23(double* pA, TCHAR*& pB, int B_count)
{
    *pA = 999.999;
    wcscpy_s(pB, B_count, _T("TEST___________"));

    return (0);
}


/***********************************************************************

    コマンド24
    アーム内温度取得
    追加(2025.6.4yori)

***********************************************************************/

int HwCtrl::Func24()
{
    int ret = 0;

    m_hVecCnt.VecCmd_Tmp();

    return ret;
}


/***********************************************************************

    コマンド25
    0軸イニシャライズモードへ変更
    追加(2025.6.9yori)

***********************************************************************/

int HwCtrl::Func25()
{
    int ret = 0;

    ret = m_hVecCnt.VecCmd_ChangeMode(VEC_MODE::VEC_MODE_INITIALIZE);

    return ret;
}


/***********************************************************************

    コマンド26
    アーム型式取得
    追加(2025.6.16yori)

***********************************************************************/

int HwCtrl::Func26()
{
    int ret = 0;

    ret = CalibSetPath("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles");
    ret |= CalibGetArmNo(m_hVecCnt.m_Sts.m_ArmModel, 16); // アーム型式は直接veccal.iniからではなく、VecCalib.dllから取得するように変更(2025.8.30yori)

    return ret;
}


/***********************************************************************

    コマンド27
    カウンタバージョン取得
    追加(2025.6.17yori)

***********************************************************************/

int HwCtrl::Func27()
{
    int ret = 0;

    ret = m_hVecCnt.VecCmd_GetCntVer();

    return ret;
}



/***********************************************************************

    コマンド28
    有接触カウント値要求
    追加(2025.5.15yori)

***********************************************************************/

int HwCtrl::Func28(VecCtEx2* veccntdata)
{
    int ret = 0;

    ret = m_hVecCnt.VecFunc_CntRequestEx(veccntdata, 1);

    return ret;
}



/***********************************************************************

    コマンド29
    メンテナンスモードへ変更
    追加(2025.6.18yori)

***********************************************************************/

int HwCtrl::Func29()
{
    int ret = 0;

    ret = m_hVecCnt.VecCmd_ChangeMode(VEC_MODE::VEC_MODE_MAINTE);

    return ret;
}



/***********************************************************************

    コマンド30
    アーム内温度取得
    追加(2025.6.18yori)

***********************************************************************/

int HwCtrl::Func30()
{
    int ret = 0;

    m_hVecCnt.VecCmd_GetCalTmp();

    return ret;
}



/***********************************************************************

    コマンド31
    アームネットワーク設定取得
    追加(2025.6.18yori)

***********************************************************************/

int HwCtrl::Func31(char address[4][8], char subnet[4][8], char port[4]) // 2025.9.30 この関数バグあり、メモリ壊しています！！！！ memo eba
{
    int ret = 0;
    int i = 0;
    int j = 0;
    int k = 0; // 追加(2025.8.20yori)

    // 初期化(2025.8.20yori)
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            address[i][j] = NULL;
            subnet[i][j] = NULL;
        }
        port[i] = NULL;
    }

    m_hVecCnt.VecCmd_GetNetwork();

    // IPアドレス、サブネットマスクを分割(2025.8.15yori)
    // IPアドレス
    for (i = 0; i < 4; i++)
    {
        while(m_hVecCnt.m_Sts.m_Address[k] != ' ')
        {
            if (m_hVecCnt.m_Sts.m_Address[k] == '\0') break;
            address[i][j] = m_hVecCnt.m_Sts.m_Address[k];
            j++;
            k++; // 追加(2025.8.20yori)
        }
        j = 0; // 追加(2025.8.20yori)
        k++; // 追加(2025.8.20yori)
    }

    // サブネットマスク
    j = 0;
    k = 0;
    for (i = 0; i < 4; i++)
    {
        while (m_hVecCnt.m_Sts.m_Subnet[k] != ' ')
        {
            if (m_hVecCnt.m_Sts.m_Subnet[k] == '\0') break;
            subnet[i][j] = m_hVecCnt.m_Sts.m_Subnet[k];
            j++;
            k++; // 追加(2025.8.20yori)
        }
        j = 0; // 追加(2025.8.20yori)
        k++; // 追加(2025.8.20yori)
    }

    // ポート
    for (i = 0; i < 4; i++)
    {
        port[i] = m_hVecCnt.m_Sts.m_Port[i];
    }

    return ret;
}



/***********************************************************************

    コマンド32
    スキャナネットワーク設定
    追加(2025.6.19yori)

***********************************************************************/

BOOL HwCtrl::Func32()
{
    BOOL fg = FALSE;
    unsigned char c;
    wchar_t net[4][8], s_para[32];

    fg = TdsVecConfigControllerAddressSetting(m_Address, m_Subnet, m_Gateway, m_DNS);

    // iniファイルにネットワーク情報を書き込む(2025.8.28yori)
    // IPアドレス
    memset(net, 0, sizeof(net));
    memset(s_para, 0, sizeof(s_para));
    c = (unsigned char)(m_Address & 0x000000ff);
    swprintf_s(net[3], 8, L"%d", c);
    m_Address = m_Address >> 8;
    c = (unsigned char)(m_Address & 0x000000ff);
    swprintf_s(net[2], 8, L"%d.", c);
    m_Address = m_Address >> 8;
    c = (unsigned char)(m_Address & 0x000000ff);
    swprintf_s(net[1], 8, L"%d.", c);
    m_Address = m_Address >> 8;
    c = (unsigned char)(m_Address & 0x000000ff);
    swprintf_s(net[0], 8, L"%d.", c);
    wcscpy_s(s_para, &net[0][0]);
    wcscat_s(s_para, &net[1][0]);
    wcscat_s(s_para, &net[2][0]);
    wcscat_s(s_para, &net[3][0]);
    WritePrivateProfileString(TEXT("Scanner"), TEXT("IP_Address"), s_para, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\networkset.ini"));

    // サブネットマスク
    memset(net, 0, sizeof(net));
    memset(s_para, 0, sizeof(s_para));
    c = (unsigned char)(m_Subnet & 0x000000ff);
    swprintf_s(net[3], 8, L"%d", c);
    m_Subnet = m_Subnet >> 8;
    c = (unsigned char)(m_Subnet & 0x000000ff);
    swprintf_s(net[2], 8, L"%d.", c);
    m_Subnet = m_Subnet >> 8;
    c = (unsigned char)(m_Subnet & 0x000000ff);
    swprintf_s(net[1], 8, L"%d.", c);
    m_Subnet = m_Subnet >> 8;
    c = (unsigned char)(m_Subnet & 0x000000ff);
    swprintf_s(net[0], 8, L"%d.", c);
    wcscpy_s(s_para, &net[0][0]);
    wcscat_s(s_para, &net[1][0]);
    wcscat_s(s_para, &net[2][0]);
    wcscat_s(s_para, &net[3][0]);
    WritePrivateProfileString(TEXT("Scanner"), TEXT("Subnet_Mask"), s_para, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\networkset.ini"));

    // デフォルトゲイトウェイ
    memset(net, 0, sizeof(net));
    memset(s_para, 0, sizeof(s_para));
    c = (unsigned char)(m_Gateway & 0x000000ff);
    swprintf_s(net[3], 8, L"%d", c);
    m_Gateway = m_Gateway >> 8;
    c = (unsigned char)(m_Gateway & 0x000000ff);
    swprintf_s(net[2], 8, L"%d.", c);
    m_Gateway = m_Gateway >> 8;
    c = (unsigned char)(m_Gateway & 0x000000ff);
    swprintf_s(net[1], 8, L"%d.", c);
    m_Gateway = m_Gateway >> 8;
    c = (unsigned char)(m_Gateway & 0x000000ff);
    swprintf_s(net[0], 8, L"%d.", c);
    wcscpy_s(s_para, &net[0][0]);
    wcscat_s(s_para, &net[1][0]);
    wcscat_s(s_para, &net[2][0]);
    wcscat_s(s_para, &net[3][0]);
    WritePrivateProfileString(TEXT("Scanner"), TEXT("Default_Gateway"), s_para, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\networkset.ini"));

    // DNSサーバー
    memset(net, 0, sizeof(net));
    memset(s_para, 0, sizeof(s_para));
    c = (unsigned char)(m_DNS & 0x000000ff);
    swprintf_s(net[3], 8, L"%d", c);
    m_DNS = m_DNS >> 8;
    c = (unsigned char)(m_DNS & 0x000000ff);
    swprintf_s(net[2], 8, L"%d.", c);
    m_DNS = m_DNS >> 8;
    c = (unsigned char)(m_DNS & 0x000000ff);
    swprintf_s(net[1], 8, L"%d.", c);
    m_DNS = m_DNS >> 8;
    c = (unsigned char)(m_DNS & 0x000000ff);
    swprintf_s(net[0], 8, L"%d.", c);
    wcscpy_s(s_para, &net[0][0]);
    wcscat_s(s_para, &net[1][0]);
    wcscat_s(s_para, &net[2][0]);
    wcscat_s(s_para, &net[3][0]);
    WritePrivateProfileString(TEXT("Scanner"), TEXT("DNS_Server"), s_para, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\networkset.ini"));

    return fg;
}



/***********************************************************************

    コマンド33
    スキャナネットワーク設定値取得
    追加(2025.6.19yori)
    引数を2次元配列へ変更(2025.8.17yori)
    iniファイルからネットワーク情報取得(2025.8.27yori)

***********************************************************************/

void HwCtrl::Func33(char address[4][8], char subnet[4][8], char gateway[4][8], char dns[4][8])
{
    int i = 0;
    int j = 0;
    int k = 0;
    int size = 32; // 追加(2025.8.28yori)
    char c_network[32]; // 追加(2025.8.29yori)
    wchar_t w_network[32];
    size_t converted = 0; // 追加(2025.8.29yori)
    errno_t err; // 追加(2025.8.29yori)
    memset(w_network, 0, sizeof(w_network));
    memset(c_network, 0, sizeof(c_network)); // 追加(2025.8.29yori)

    // IPアドレス
    GetPrivateProfileString(TEXT("Scanner"), TEXT("IP_Address"), TEXT("192.168.10.200"), w_network, size, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\networkset.ini"));
    err = wcstombs_s(&converted, c_network, 32, w_network, _TRUNCATE); // wcstombs_sを使ってwchar_tからcharへ変換(2025.8.29yori)
    for (i = 0; i < 4; i++)
    {
        while (c_network[k] != '.')
        {
            if (c_network[k] == '\0') break;
            address[i][j] = c_network[k];
            j++;
            k++;
        }
        j = 0;
        k++;
    }

    // サブネットマスク
    j = 0;
    k = 0;
    memset(w_network, 0, sizeof(w_network));
    memset(c_network, 0, sizeof(c_network)); // 追加(2025.8.29yori)
    GetPrivateProfileString(TEXT("Scanner"), TEXT("Subnet_Mask"), TEXT("255.255.255.0"), w_network, size, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\networkset.ini"));
    err = wcstombs_s(&converted, c_network, 32, w_network, _TRUNCATE); // wcstombs_sを使ってwchar_tからcharへ変換(2025.8.29yori)
    for (i = 0; i < 4; i++)
    {
        while (c_network[k] != '.')
        {
            if (c_network[k] == '\0') break;
            subnet[i][j] = c_network[k];
            j++;
            k++;
        }
        j = 0;
        k++;
    }

    // デフォルトゲイトウェイ
    j = 0;
    k = 0;
    memset(w_network, 0, sizeof(w_network));
    memset(c_network, 0, sizeof(c_network)); // 追加(2025.8.29yori)
    GetPrivateProfileString(TEXT("Scanner"), TEXT("Default_Gateway"), TEXT("192.168.10.1"), w_network, size, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\networkset.ini"));
    err = wcstombs_s(&converted, c_network, 32, w_network, _TRUNCATE); // wcstombs_sを使ってwchar_tからcharへ変換(2025.8.29yori)
    for (i = 0; i < 4; i++)
    {
        while (c_network[k] != '.')
        {
            if (c_network[k] == '\0') break;
            gateway[i][j] = c_network[k];
            j++;
            k++;
        }
        j = 0;
        k++;
    }

    // DNSサーバー
    j = 0;
    k = 0;
    memset(w_network, 0, sizeof(w_network));
    memset(c_network, 0, sizeof(c_network)); // 追加(2025.8.29yori)
    GetPrivateProfileString(TEXT("Scanner"), TEXT("DNS_Server"), TEXT("0.0.0.0"), w_network, size, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\networkset.ini"));
    err = wcstombs_s(&converted, c_network, 32, w_network, _TRUNCATE); // wcstombs_sを使ってwchar_tからcharへ変換(2025.8.29yori)
    for (i = 0; i < 4; i++)
    {
        while (c_network[k] != '.')
        {
            if (c_network[k] == '\0') break;
            dns[i][j] = c_network[k];
            j++;
            k++;
        }
        j = 0;
        k++;
    }
}



/***********************************************************************

    コマンド34
    スキャナ計測モード取得
    追加(2025.6.20yori)

***********************************************************************/

int HwCtrl::Func34()
{
    int i = 0;

    i = TdsVecGetMode(&m_iXSize, &m_dXPitch);

    return i;
}



/***********************************************************************

    コマンド35
    感度取得
    追加(2025.6.23yori)

***********************************************************************/

void HwCtrl::Func35(int use[5], char name[5][50])
{
    TdsVecGetAllSimpleSensName(use, name);
}



/***********************************************************************

    コマンド36
    距離マスクパラメータの取得
    追加(2025.6.20yori)

***********************************************************************/

BOOL HwCtrl::Func36()
{
    BOOL fg = FALSE;
    m_ptZMask = new PulsZMask;

    fg = TdsVecZMaskGet(0, m_ptZMask);

    return fg;
}



/***********************************************************************

    コマンド37
    輝度スライスパラメータ取得
    追加(2025.6.20yori)

***********************************************************************/

BOOL HwCtrl::Func37(unsigned short val[5])
{
    BOOL fg = FALSE;

    for (int i = 0; i < 5; i++)
    {
        fg = TdsVecGetBrightSliceLevel(i, &val[i]);
        if (fg == FALSE)
        {
            break;
        }
    }

    return fg;
}



/***********************************************************************

    コマンド38
    感度スライスパラメータ取得
    追加(2025.6.20yori)

***********************************************************************/

BOOL HwCtrl::Func38(unsigned short val[5])
{
    BOOL fg = FALSE;

    for (int i = 0; i < 5; i++)
    {
        fg = TdsVecGetDataMinSliceLevel(i, &val[i]);
        if (fg == FALSE)
        {
            break;
        }
    }

    return fg;
}



/***********************************************************************

    コマンド39
    ガイドレーザーパワー取得
    追加(2025.6.23yori)

***********************************************************************/

void HwCtrl::Func39(int* power)
{
    TdsVecGetGuideLaserPower(power);
}



/***********************************************************************

    コマンド40
    補間設定取得
    追加(2025.6.23yori)

***********************************************************************/

void HwCtrl::Func40(int* onoff)
{
    TdsVecGetInterpolationX(onoff);
}



/***********************************************************************

    コマンド41
    角度マスク設定値取得
    追加(2025.6.23yori)

***********************************************************************/

void HwCtrl::Func41(double* angle)
{
    TdsVecGetAngleMask(angle);
}



/***********************************************************************

    コマンド42
    2ピークマスク設定取得
    追加(2025.6.23yori)

***********************************************************************/

void HwCtrl::Func42(int* mask)
{
    TdsVecGet2PeakMask(mask); // 追加(2025.7.4yori)
}



/***********************************************************************

    コマンド43
    エッジマスク設定取得
    追加(2025.6.23yori)

***********************************************************************/

void HwCtrl::Func43(int* edge_point, int* search_point)
{
    TdsVecGetEdgeMask(edge_point, search_point);// 追加(2025.7.4yori)
}



/***********************************************************************

    コマンド44
    SWチェック
    追加(2025.6.24yori)

***********************************************************************/

void HwCtrl::Func44(int* sw)
{
    sw[0] = TdsSw1Get();
    sw[1] = TdsSw2Get();
}



/***********************************************************************

    コマンド45
    ラッチ通信チェック
    追加(2025.6.25yori)

***********************************************************************/

void HwCtrl::Func45()
{
    int ret = 0;
    int latch_count = 0;
    BOOL fg = FALSE;
    VecDtEx PosiData;
    m_ptLatchResult = new SelfChkLatchResult;
    ret = m_hVecCnt.VecCmd_ChangeMode(VEC_MODE::VEC_MODE_ROUCH);
    if (ret == 0)
    {
        fg = TdsVecStartSelfChkLatchMode();
        if (fg == TRUE)
        {
            while (1)
            {
                ret = Func05(&PosiData);
                if (m_hVecCnt.m_GetdataNo != 0)
                {
                    TdsVecLatchReceive();
                    latch_count++;
                    if (latch_count == 1) // 1回ラッチ受信したら、ストップする。
                    {
                        TdsVecStopSelfChkLatchMode();
                        TdsVecExecSelfChkLatch(m_ptLatchResult);
                        break;
                    }
                }
            }
        }
    }
    ret = m_hVecCnt.VecCmd_ChangeMode(VEC_MODE::VEC_MODE_LAZER_SCAN);
}



/***********************************************************************

    コマンド46
    モーターチェック
    追加(2025.6.24yori)

***********************************************************************/

void HwCtrl::Func46()
{
    m_ptMotorResult = new SelfChkMotorResult;
    TdsVecExecSelfChkMotor(m_ptMotorResult);
}



/***********************************************************************

    コマンド47
    LEDチェック
    追加(2025.6.25yori)

***********************************************************************/

void HwCtrl::Func47()
{
    TdsVecStartSelfChkLed(TRUE);
    TdsVecStartSelfChkLed(FALSE);
    TdsVecStopSelfChkLed();
}



/***********************************************************************

    コマンド48
    計測タイプ設定
    追加(2025.7.2yori)

***********************************************************************/

BOOL HwCtrl::Func48(int type)
{
    BOOL fg = FALSE;

    fg = TdsVecSetMeasType(type);

    return fg;
}



/***********************************************************************

    コマンド49
    感度チェック
    追加(2025.7.2yori)

***********************************************************************/

BOOL HwCtrl::Func49()
{
    BOOL fg = FALSE;

    fg = Func48(TDS_MEASTYPE_SELF_CHECK_SENS);
    if (fg == TRUE)
    {
        fg = TdsVecStartSelfChkSens();
        if (fg == TRUE)
        {
            return TRUE;
        }
    }

    return FALSE;
}



/***********************************************************************

    コマンド50
    プローブ情報設定
    追加(2025.7.18yori)
    引数追加(2025.9.8yori)

***********************************************************************/

int HwCtrl::Func50(int id, double dia)
{
    int ret = 0;

    if (m_hVecCnt.m_Sts.m_Model != "VAR800M" || m_hVecCnt.m_Sts.m_Model != "VAR800L") // m_Sts追加(2025.8.20yori) // V8をMとLに分割(2025.9.26yori)
    {
        ret = HwCtrl::m_hVecCnt.VecCmd_ChangeProbe(id);
    }

    ret |= HwCtrl::m_hVecCnt.VecCmd_ChangeDiameter(to_string(dia));

    return ret;
}



/***********************************************************************

    コマンド51
    プローブ情報をPolyWorksへ送信
    追加(2025.7.18yori)

***********************************************************************/

int HwCtrl::Func51()
{
    SEND_PROBE_PROPERTY probe_data;

    ERROR_CODE ErrorCode = ERROR_CODE::ERROR_CODE_NONE;

    int ret = HwCtrl::Func09(); // VECTORONの状態取得
    if (ret != VEC_RET_CODE::RET_CODE__OK)
    {
        return ERROR_CODE::ERROR_CODE_PROPETY; // プロパティ情報取得に失敗しました。
    }

    // 現在のプローブIDとスタイラス直径の情報をPolyWorksへ送信する。
    probe_data.ps_id = HwCtrl::m_hVecCnt.VecSts_GetProbeId();
    probe_data.dia = HwCtrl::m_hVecCnt.VecSts_GetProbeDia();

    probe_data.cmd_no[0] = (char)APP_SEND_CMD::SEND_PROBE_PROPETY & 0xff;
    ret = SendPolyworksMessage((int)QUE_NUM::SEND_COMMAND, sizeof(probe_data), ((char*)&probe_data));
    if (ret != 0)  ErrorCode = ERROR_CODE::ERROR_CODE_MEMORYMAPED_WRITE; // Polyworks転送バッファに書き込みできない(メモリマップドファイル)
    return  (int)ErrorCode;
}



/***********************************************************************

    コマンド52
    プローブ名称取得(2025.7.23yori)
    スタイラス角度取得(2025.7.31yori)
    引数追加(2025.8.28yori)

***********************************************************************/

void HwCtrl::Func52(wchar_t probe_name[21][32], wchar_t stylus_angle[21][32])
{
    for (int i = 0; i < 21; i++) // probeset.iniファイルからID=0～20までのプローブ情報取得(2025.7.24yori)
    {
        wchar_t id[8] = L"ID";
        wchar_t no[8];

        swprintf(no, 8, L"%d", i); // swprintfへ変更(2025.8.10yori)
        wcsncat_s(id, no, sizeof(id));

        GetPrivateProfileString(id, TEXT("name"), TEXT("スタンダードプローブ"), probe_name[i], 32, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\probeset.ini")); // ファイル名変更(2025.8.18yori)
        GetPrivateProfileString(id, TEXT("angle"), TEXT("0.0000"), stylus_angle[i], 32, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\probeset.ini")); // ファイル名変更(2025.8.18yori)
    }
}



/***********************************************************************

    コマンド53
    スキャナのステータス取得
    追加(2025.7.29yori)

***********************************************************************/

BOOL HwCtrl::Func53(BOOL* warmup)
{
    BOOL fg = FALSE;
    BOOL exist = FALSE;
    BOOL connect = FALSE;

    fg = TdsVecScannerStatus(&exist, &connect, warmup);

    return fg;
}



/***********************************************************************

    コマンド54
    しきい値取得
    追加(2025.8.1yori)
    すべてのID→指定IDの初期値取得へ変更(2025.9.22yori)

***********************************************************************/

int HwCtrl::Func54(CALIB_JUDGE_CK* th1, CALIB_JUDGE th2[20], CALIB_GAUGE* gauge, int id)
{
    int ret = 0;

    ret = CalibSetPath("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles");
    ret |= CalibInit(0, CALIB_MODE_CHECK); // 追加(2025.8.5yori)
    ret |= CalibGetThresholdCk(th1); // 始業前点検のしきい値
    if (id == 0) // スキャナの場合はプローブ点検が無いため、0.0を入れておく(i=0を入力するとスタック破壊となる。)(2025.9.8yori)
    {
        th2[id].pp = 0.0;
        th2[id].sigma2 = 0.0;
        th2[id].plate = 0.0;
        th2[id].ld = 0.0;
        th2[id].pf = 0.0;
        th2[id].ps = 0.0;
        th2[id].ri = 0.0;
        th2[id].pl = 0.0;
        th2[id].psi = 0.0;
    }
    else
    {
        ret |= CalibGetThreshold(&th2[id], id);
    }
    ret |= CalibGetGaugeVal(gauge); // キャリブレーションのしきい値
    ret |= CalibEnd();  // 2025.9.22 add eba

    return ret;
}



/***********************************************************************

    コマンド55
    しきい値の初期値取得
    追加(2025.8.1yori)
    すべてのID→指定IDの初期値取得へ変更(2025.9.22yori)

***********************************************************************/

int HwCtrl::Func55(CALIB_JUDGE_CK* th1, CALIB_JUDGE th2[20], int id)
{
    int ret = 0;

    ret = CalibGetThresholdCkDef(th1); // 始業前点検のしきい値の初期値
    if (id == 0) // スキャナの場合はプローブ点検が無いため、0.0を入れておく(id=0を入力するとスタック破壊となる。)(2025.9.8yori)
    {
        th2[0].pp = 0.0;
        th2[0].sigma2 = 0.0;
        th2[0].plate = 0.0;
        th2[0].ld = 0.0;
        th2[0].pf = 0.0;
        th2[0].ps = 0.0;
        th2[0].ri = 0.0;
        th2[0].pl = 0.0;
        th2[0].psi = 0.0;
    }
    else
    {
        ret |= CalibGetThresholdDef(&th2[id], id); // プローブ点検のしきい値の初期値
    }

    return ret;
}



/***********************************************************************

    コマンド56
    ゲージ設定取得
    追加(2025.8.7yori)

***********************************************************************/

BOOL HwCtrl::Func56(VecGaugeIni* ga1, SensorSettingIni* ga2, double* scanchkball)
{
    BOOL fg = FALSE;
    wchar_t th[8];

    TdsVecSetIniFilePath("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles");
    fg = TdsVecReadVecGaugeIni(ga1);
    TdsVecReadSSettingIni(ga2);
    // 非接触球のみの点検しきい値追加(2025.8.7yori)
    GetPrivateProfileString(TEXT("Limit"), TEXT("Center_Limit"), TEXT("0.18"), th, 8, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\scancheckball.ini"));
    WritePrivateProfileString(TEXT("Limit"), TEXT("Center_Limit"), th, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\scancheckball.ini"));
    *scanchkball = _wtof(th);

    return fg;
}



/***********************************************************************

    コマンド57
    ゲージ選択番号書き込み
    追加(2025.8.9yori)

***********************************************************************/

void HwCtrl::Func57(int gaugetype)
{
    wchar_t no[8];

    swprintf(no, 8, L"%d", gaugetype);

    WritePrivateProfileString(TEXT("Select"), TEXT("GageType"), no, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\vecgauge.ini"));
}



/***********************************************************************

    コマンド58
    非接触球のみの点検しきい値書き込み
    追加(2025.8.10yori)

***********************************************************************/

void HwCtrl::Func58(double scanchkball)
{
    wchar_t th[8];

    swprintf(th, 8, L"%.2f", scanchkball);

    WritePrivateProfileString(TEXT("Limit"), TEXT("Center_Limit"), th, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\scancheckball.ini"));
}



/***********************************************************************

    コマンド59
    非接触モード計測モード取得(2025.8.10yori)

***********************************************************************/

void HwCtrl::Func59(wchar_t mode[6][32])
{
    wchar_t no[6];

    for (int i = 0; i < 6; i++) // TdsLibrary.iniから計測モード取得(2025.8.10yori)
    {
        swprintf(no, 6, L"%d", i+2); // swprintfへ変更(2025.8.10yori)

        GetPrivateProfileString(TEXT("System"), no, TEXT("E  : 50mm-0.062mm-85Hz"), mode[i], 32, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\TDSLibrary.ini"));
    }
}



/***********************************************************************

    コマンド60
    スキャナ測定音ON
    移植(2025.8.12yori)

***********************************************************************/

void HwCtrl::Func60()
{
    WritePrivateProfileString(TEXT("Buzzer"), TEXT("0"), TEXT("1"), TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\TDSUser.ini"));
}



/***********************************************************************

    コマンド61
    スキャナ計測モード変更
    追加(2025.8.12yori)

***********************************************************************/

BOOL HwCtrl::Func61(int scanmode)
{
    BOOL fg = FALSE;

    fg = TdsVecChangeMode(scanmode);

    return fg;
}



/***********************************************************************

    コマンド62
    感度変更
    追加(2025.8.21yori)

***********************************************************************/

BOOL HwCtrl::Func62(int sens)
{
    BOOL fg = FALSE;

    fg = TdsVecChangeSimpleSens(sens);

    return fg;
}



/***********************************************************************

    コマンド63
    ガイドレーザーパワーの設定
    追加(2025.8.21yori)

***********************************************************************/

BOOL HwCtrl::Func63(int power)
{
    BOOL fg = FALSE;

    fg = TdsVecSetGuideLaserPower(power);

    return fg;
}



/***********************************************************************

    コマンド64
    X点間補間モードの設定
    追加(2025.8.21yori)

***********************************************************************/

BOOL HwCtrl::Func64(int pitch)
{
    BOOL fg = FALSE;

    fg = TdsVecSetInterpolationX(pitch);

    return fg;
}



/***********************************************************************

    コマンド65
    距離マスクの設定
    追加(2025.8.24yori)

***********************************************************************/

BOOL HwCtrl::Func65()
{
    BOOL fg = FALSE;

    fg = TdsVecZMaskSet(0, m_ptZMask);

    delete m_ptZMask;

    return fg;
}



/***********************************************************************

    コマンド66
    輝度スライスの設定
    追加(2025.8.25yori)

***********************************************************************/

BOOL HwCtrl::Func66()
{
    int i;
    BOOL fg = FALSE;
    
    for (i = 0; i < 5; i++)
    {
        fg = TdsVecSetBrightSliceLevel(i, m_BrightSlice[i]);
        fg |= TdsVecSetMeasType(TDS_MEASTYPE_NORMAL); // 追加(2025.8.26yori)
        if (fg == FALSE)
        {
            break;
        }
    }

    return fg;
}



/***********************************************************************

    コマンド67
    感度スライスの設定
    追加(2025.8.24yori)

***********************************************************************/

BOOL HwCtrl::Func67()
{
    int i;
    BOOL fg = FALSE;

    for (i = 0; i < 5; i++)
    {
        fg = TdsVecSetDataMinSliceLevel(i, m_SensSlice[i]);
        fg |= TdsVecSetMeasType(TDS_MEASTYPE_NORMAL); // 追加(2025.8.26yori)
        if (fg == FALSE)
        {
            break;
        }
    }

    return fg;
}



/***********************************************************************

    コマンド68
    角度マスクの設定
    追加(2025.8.25yori)

***********************************************************************/

BOOL HwCtrl::Func68()
{
    BOOL fg = FALSE;

    fg = TdsVecGetAngleMask(&m_Angle);

    return fg;
}



/***********************************************************************

    コマンド69
    2ピークマスクの設定
    追加(2025.8.25yori)

***********************************************************************/

BOOL HwCtrl::Func69(int twopeak)
{
    BOOL fg = FALSE;

    fg = TdsVecSet2PeakMask(twopeak);
    fg |= TdsVecSetMeasType(TDS_MEASTYPE_NORMAL); // 追加(2025.8.26yori)

    return fg;
}



/***********************************************************************

    コマンド70
    エッジマスクの設定
    追加(2025.8.25yori)

***********************************************************************/

BOOL HwCtrl::Func70()
{
    BOOL fg = FALSE;

    fg = TdsVecSetEdgeMask(m_Edge, 5); // エッジと判断する中空点数の初期値：5
    fg |= TdsVecSetMeasType(TDS_MEASTYPE_NORMAL); // 追加(2025.8.26yori)

    return fg;
}



/***********************************************************************

    コマンド71
    スキャナのリセット
    追加(2025.8.27yori)

***********************************************************************/

BOOL HwCtrl::Func71()
{
    BOOL fg = FALSE;

    fg = TdsVecMeasReset(0);

    return fg;
}



/***********************************************************************

    コマンド72
    エッジマスクパラメータの初期値を取得
    追加(2025.8.27yori)

***********************************************************************/

BOOL HwCtrl::Func72(int edge_default[3][6], int edge_serch_default[3][6])
{
    int i, j;
    BOOL fg = FALSE;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 6; j++)
        {
            fg |= TdsVecGetEdgeMaskDefault(i, j, &edge_default[i][j], &edge_serch_default[i][j]);
            if (fg == FALSE)
            {
                break;
            }
        }
    }

    return fg;
}



/***********************************************************************

    コマンド73
    アームネットワーク設定
    追加(2025.8.28yori)

***********************************************************************/

int HwCtrl::Func73()
{
    int ret = 0;
    int i; // 追加(2025.8.29yori)
    size_t len; // 追加(2025.8.29yori)
    wchar_t address[32]; // 追加(2025.8.29yori)
    size_t converted = 0; // 追加(2025.8.29yori)
    errno_t err; // 追加(2025.8.29yori)

    ret = m_hVecCnt.VecCmd_ChangeNetwork(m_hVecCnt.m_Sts.m_Address, m_hVecCnt.m_Sts.m_Subnet, m_hVecCnt.m_Sts.m_Port);

    // veccom.ini、networkset.iniにIPアドレスを書き込む(2025.8.29yori)
    len = strlen(m_hVecCnt.m_Sts.m_Address);
    for (i = 0; i < len; i++)
    {
        if (m_hVecCnt.m_Sts.m_Address[i] == ' ') m_hVecCnt.m_Sts.m_Address[i] = '.';
    }
    err = mbstowcs_s(&converted, address, 32, m_hVecCnt.m_Sts.m_Address, _TRUNCATE);

    WritePrivateProfileString(TEXT("LAN"), TEXT("VECADDR"), address, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\veccom.ini"));
    WritePrivateProfileString(TEXT("Arm"), TEXT("IP_Address"), address, TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\networkset.ini"));

    return ret;
}



/***********************************************************************

    コマンド74
    アーム型式設定
    追加(2025.8.31yori)

***********************************************************************/

int HwCtrl::Func74(const TCHAR* armmodel)
{
    int ret = 0;
    size_t converted = 0;
    errno_t err; 

    err = wcstombs_s(&converted, m_hVecCnt.m_Sts.m_ArmModel, sizeof(m_hVecCnt.m_Sts.m_ArmModel), armmodel, _TRUNCATE); // wchar_tからcharへ変換(2025.9.1yori)

    ret = CalibSetArmNo(m_hVecCnt.m_Sts.m_ArmModel, 16);

    return ret;
}



/***********************************************************************

    コマンド75
    関節リミットビープ音のON
    追加(2025.9.1yori)

***********************************************************************/

int HwCtrl::Func75()
{
    int ret = 0;

    ret = HwCtrl::m_hVecCnt.VecCmd_ChangeBeep("ON");

    return ret;
}



/***********************************************************************

    コマンド75
    スキャナ電源OFF→スキャナ終了処理→スキャナ測定音ON
    追加(2025.9.3yori)

***********************************************************************/

BOOL HwCtrl::Func76()
{
    BOOL fg = FALSE;

    fg = TdsVecScannerPowerOff();
    TdsVecMeasExit();
    fg |= WritePrivateProfileString(TEXT("Buzzer"), TEXT("0"), TEXT("1"), TEXT("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\TDSUser.ini"));

    return fg;
}



/***********************************************************************

    PolyWorksからコマンドを受信する
    送信するコマンド番号
    移植(2025.5.15yori)

***********************************************************************/

int HwCtrl::AppCommandRecv(char* RBuf)
{
    int		iRec = 0;
    int		tid = QUE_NUM::COMMAND;

    iRec = LplRecvMesBox(tid, RBuf);

    return iRec;
}



/***********************************************************************

    PolyWorksへコマンドを送信する
    送信するコマンド番号
    移植(2025.5.15yori)

***********************************************************************/

int HwCtrl::AppCommandSend(APP_SEND_CMD cmd)
{
    int  len;
    int  idx;
    int ret_send = 1;	// 正常に送信できたとき以外の数値(0)をあらかじめ入れておく
    char SBuf[10] = { 0 };

    //送信するデータをバッファに格納
    idx = 0;
    SBuf[idx++] = (char)cmd & 0xff;
    len = idx;

    ret_send = SendPolyworksMessage((int)QUE_NUM::SEND_COMMAND, len, SBuf);
    //データの送信に失敗したとき
    if (ret_send != 0)
    {
         //エラーメッセージ処理は後でコーディング(2025.4.30)
    }

    return ret_send;
}



/***********************************************************************

    LplSendMesBox == Queを使用せず直接バッファ書き込む
    戻り値 0-正常転送
           1- error およびタイムアウト 10s
    移植(2025.5.15yori)

***********************************************************************/

int HwCtrl::SendPolyworksMessage(int TID, int Leng, char SBuf[])
{
    int iCheckFg = 1;
    DWORD StartTime = timeGetTime();// 開始時間

    while (LplSendMesBoxBuffferEmpty(TID) != 0)
    {
        DWORD dwTime = timeGetTime() - StartTime;
        if (dwTime > 10000) goto job_exit;// time out
    }

    WaitForSingleObject(hSEMA, INFINITE);

    iCheckFg = LplSendMesBox2(TID, Leng, SBuf);// 直接バッファに書き込む

    ReleaseSemaphore(hSEMA, 1, NULL);

job_exit:

    return iCheckFg;
}



/***********************************************************************

    スレッド処理
    非接触データ取得
    移植(2025.5.15yori)

***********************************************************************/

void HwCtrl::GetScanDataThread_new()
{
    NCON_MEAS_SEQ  OldScanDataStepCounter = NCON_MEAS_SEQ::IDEL;		// 測定サンプリングスレット　シーケンスカウンタデバック用
    m_StepStartTime = timeGetTime();									// ステップ開始時間	
    m_bSwSts = false;												    // スイッチ状態
    m_bOldSwSts = false;												// 前回のスイッチ状態
    m_SwTime = m_StepStartTime;										    // 検出時間							
    m_OldSwTime = m_StepStartTime;										// 前回の検出時間

    DWORD startTimedt = 0;												// 時計データ　チャタリング監視用
    DWORD endTimedt = 0;

    double		dXPitch = 0.0;
    int			iMeasMode = Func34(); // 変更(20258.12yori)

    int res = 0;
    int ErrorCode = 0;

    int iSts = 0;
    int iMeasType = 0;
    bool ThredLoopFg = true;
    bool transfg = true;												// 追加(2021.8.17yori)
    BOOL shotNoFg = false;												// 追加(2021.8.23yori)
    bool endfg = true;													// 追加(2021.9.8yori)
    CalibResult CalibResult;											// 追加(2021.9.8yori)
    ChkScnResult ChkResult;
    BOOL fg = FALSE; // 追加(2025.7.2yori)

    while (ThredLoopFg)
    {
        switch ( m_ScanDataStepCounter ) {
        case NCON_MEAS_SEQ::IDEL:										// 0　- TREAD起動
            TdsVecGetMeasType(&iMeasType);
            if (iMeasType == TDS_MEASTYPE_CALIB_FULL || iMeasType == TDS_MEASTYPE_CALIB_USER || iMeasType == TDS_MEASTYPE_MACHINE_CHECK || iMeasType == TDS_MEASTYPE_SELF_CHECK_SENS)	// キャリブレーション、始業前点検の場合、「iMeasType ==」追加修正(2021.9.15yori) // 感度チェック追加(2025.7.2yori)
            {
                //shotNoFg = TdsVecSetShotNum(m_ScanShotNo);			// ショットNoを設定
            }
            else if (iMeasType != TDS_MEASTYPE_NORMAL)					// 測定タイプの通常計測モードでないとき再設定
            {
                if (!TdsVecSetMeasType(TDS_MEASTYPE_NORMAL))
                {
                    // ログ出力 
                    // スレット終了へ
                    OldScanDataStepCounter = m_ScanDataStepCounter;		// Old情報
                    m_ScanDataStepCounter = NCON_MEAS_SEQ::MS_ERROR;	// 8  - error 停止（終了)
                }
            }
            m_ScanDataStepCounter = NCON_MEAS_SEQ::START;
            m_StepStartTime = timeGetTime();						// ステップ開始時間	
            break;
        case NCON_MEAS_SEQ::START:										// 1  - TREAD起動完了
            if ( Func16() == (int)VEC_RET_CODE::RET_CODE__OK )		// 2021.3.26 バッファクリア
            {
                m_ScanDataStepCounter = NCON_MEAS_SEQ::DUMMY_START;
                m_StepStartTime = timeGetTime();						// ステップ開始時間	
            }
            else {
                OldScanDataStepCounter = m_ScanDataStepCounter;			// Old情報
                m_ScanDataStepCounter = NCON_MEAS_SEQ::MS_ERROR;		// 8  - error 停止（終了)
            }
            break;
        case NCON_MEAS_SEQ::DUMMY_START:								// 2  - ダミースキャン開始
            if (TdsVecDummyScanStart(m_iSn, m_iSw))
            {
                if (iMeasType == TDS_MEASTYPE_CALIB_FULL || iMeasType == TDS_MEASTYPE_CALIB_USER || iMeasType == TDS_MEASTYPE_MACHINE_CHECK)	// キャリブレーション、始業前点検の場合(2021.9.16yori)
                {
                    shotNoFg = TdsVecSetShotNum(m_ScanShotNo);				// ショットNoを設定(2021.8.23yori)
                }
                m_ScanDataStepCounter = NCON_MEAS_SEQ::DUMMY_MEAS_TOP;
                m_StepStartTime = timeGetTime();						// ステップ開始時間	
            }
            else
            {
                // ログ出力 
                OldScanDataStepCounter = m_ScanDataStepCounter;			// Old情報
                m_ScanDataStepCounter = NCON_MEAS_SEQ::MS_ERROR;		// 8  - error 停止（終了)
            }
            break;
        case NCON_MEAS_SEQ::DUMMY_MEAS_TOP:								// 3  - ダミースキャン先頭データ取得
            res = GetMeasTopData();
            if (res == 0)
            {
                ++m_LineNo;												// ライン番号は次から
                m_ScanDataStepCounter = NCON_MEAS_SEQ::DUMMY_MEAS;		// ダミースキャンへ
                m_StepStartTime = timeGetTime();						// ステプ開始時間
            }
            else {
                m_ScanDataStepCounter = NCON_MEAS_SEQ::BREAK;			// 中断
            }
            if (iMeasType == TDS_MEASTYPE_NORMAL)						//追加(2022.4.7yori)
            {
                if (m_b_Button_ConnectFlag == false)                    // アプリから接続した場合は、PolyWorksへデータを送信しない。(2025.7.3yori)
                {
                    TriggerButtonAndMeasDataStatusTransfer(true, false); //トリガボタンを押した。ダミースキャンデータ(2021.11.25yori)
                }
            }
            m_bmeasfg = false;
            break;
        case NCON_MEAS_SEQ::DUMMY_MEAS:
            if (iMeasType == TDS_MEASTYPE_NORMAL)						// 測定タイプで場合分け(2021.8.17yori)
            {
                transfg = true;
            }
            else
            {
                transfg = false;
            }
            res = DataSamplingandTransfer(transfg, &ErrorCode);
            switch (res)
            {
            case 0: // SW状態遷移
                if ( Func16() == (int)VEC_RET_CODE::RET_CODE__OK)	// 2021.3.26 バッファクリア
                {
                    m_ScanDataStepCounter = NCON_MEAS_SEQ::MAIN_START;
                    m_StepStartTime = timeGetTime();					// ステップ開始時間
                    //Memory_ResetCounter();				            // ダミースキャン終了後、writeIx=0、readIx=0(2021.9.16yori) // コメントアウト(2025.5.15yori)
                }
                else {
                    OldScanDataStepCounter = m_ScanDataStepCounter;		// Old情報
                    m_ScanDataStepCounter = NCON_MEAS_SEQ::MS_ERROR;	// 8  - error 停止（終了)
                }
                break;
            case 2:		// 中断
                m_ScanDataStepCounter = NCON_MEAS_SEQ::BREAK;			// 中断
                break;
            case 3:		// full 再測定
                m_ScanDataStepCounter = NCON_MEAS_SEQ::START;
                break;
            default:
            case -1:		// Error
                OldScanDataStepCounter = m_ScanDataStepCounter;			// Old情報
                m_ScanDataStepCounter = NCON_MEAS_SEQ::MS_ERROR;		// 8  - error 停止（終了)
                break;
            }
            break;
        case NCON_MEAS_SEQ::MAIN_START:									// 5  - メイン(サンプリング）スキャン開始
            if (TdsVecScanStart(m_iSn, m_iSw))
            {
                m_ScanDataStepCounter = NCON_MEAS_SEQ::MAIN_START_TOP;
                m_StepStartTime = timeGetTime();						// ステップ開始時間	
            }
            else {
                OldScanDataStepCounter = m_ScanDataStepCounter;			// Old情報
                m_ScanDataStepCounter = NCON_MEAS_SEQ::MS_ERROR;		// 8  - error 停止（終了)
            }
            break;
        case NCON_MEAS_SEQ::MAIN_START_TOP:								// 6  - メイン(サンプリング）先頭データ取得
            res = GetMeasTopData();
            if (res == 0)
            {
                ++m_LineNo;												// ライン番号は次から
                m_ScanDataStepCounter = NCON_MEAS_SEQ::MAIN_MEAS;		// 本スキャンへ
                m_StepStartTime = timeGetTime();						// ステップ開始時間
                if (iMeasType == TDS_MEASTYPE_NORMAL)					//追加(2022.4.7yori)
                {
                    if (m_b_Button_ConnectFlag == false)                // アプリから接続した場合は、PolyWorksへデータを送信しない。(2025.7.3yori)
                    {
                        TriggerButtonAndMeasDataStatusTransfer(true, true);	//トリガボタンを押した。測定スキャンデータ(2021.11.25yori)
                    }
                }
                m_bmeasfg = true;						                // 測定データ判定Fg追加(2021.6.11yori)
            }
            else
            {
                m_ScanDataStepCounter = NCON_MEAS_SEQ::BREAK;			// 中断
                m_bmeasfg = false;	                					// Fgを初期値へ戻す(2021.6.11yori)
            }
            break;
        case NCON_MEAS_SEQ::MAIN_MEAS:									// 7  - メイン(サンプリング）スキャン中(true)
            if (iMeasType == TDS_MEASTYPE_NORMAL)						// 測定タイプで場合分け(2021.8.17yori)
            {
                transfg = true;
            }
            else
            {
                transfg = false;
            }
            res = DataSamplingandTransfer(transfg, &ErrorCode);
            switch (res)
            {
            case 0:		// SW状態遷移 // case 3と分離(2021.9.6yori)
                if (iMeasType == TDS_MEASTYPE_CALIB_FULL || iMeasType == TDS_MEASTYPE_CALIB_USER || iMeasType == TDS_MEASTYPE_MACHINE_CHECK)	//キャリブレーション、始業前点検の場合(2021.9.15yori)
                {
                    CalibCheckAndCalcu(&CalibResult, &ChkResult);
                }

                if (iMeasType == TDS_MEASTYPE_SELF_CHECK_SENS) // 追加(2025.7.2yori)
                {
                    fg = TdsVecStopSelfChkSens();
                    if (fg == TRUE)
                    {
                        m_ptSensResult = new SelfChkSensResult;
                        TdsVecExecSelfChkSens(m_ptSensResult);
                        m_VecStepSeq = VEC_STEP_SEQ::SENS_CHECK_CMP;
                    }
                }

                // ポインタ位置チェック作成中のため、コメントアウト(2025.9.3yori)
                //if (iMeasType == TDS_MEASTYPE_NORMAL || m_PointerCheckFg == true) // ポインタ位置チェックの場合(2025.7.3yori)
                //{
                //    m_VecStepSeq = VEC_STEP_SEQ::POINTER_CHECK_CMP;
                //}

                if (iMeasType == TDS_MEASTYPE_NORMAL || EndFg == false) //通常計測モードまたは、キャリブレーション、始業前点検が終了していない場合(2021.9.15yori)
                {
                    if ( Func16() == (int)VEC_RET_CODE::RET_CODE__OK )	// bufferをクリアする
                    {
                        m_ScanDataStepCounter = NCON_MEAS_SEQ::MAIN_END;
                        m_StepStartTime = timeGetTime();					// ステップ開始時間
                    }
                    else
                    {
                        OldScanDataStepCounter = m_ScanDataStepCounter;		// Old情報
                        m_ScanDataStepCounter = NCON_MEAS_SEQ::MS_ERROR;	// 8  - error 停止（終了)
                    }
                }
                break;
            case 3:		// BUFFER FULL (一度停止させる->DUMMYSACANへ→再測定へ変更(2022.2.9yori))
                if ( Func16() == (int)VEC_RET_CODE::RET_CODE__OK)	    // bufferをクリアする
                {
                    m_ScanDataStepCounter = NCON_MEAS_SEQ::MAIN_START;	//MAIN_ENDから再測定へ変更(2022.2.9yori)
                    m_StepStartTime = timeGetTime();					// ステップ開始時間
                }
                else
                {
                    OldScanDataStepCounter = m_ScanDataStepCounter;		// Old情報
                    m_ScanDataStepCounter = NCON_MEAS_SEQ::MS_ERROR;	// 8  - error 停止（終了)
                }
                break;
            case 2:		// 中断
                m_ScanDataStepCounter = NCON_MEAS_SEQ::BREAK;			// 中断
                break;
            default:
            case -1:		// Error
                OldScanDataStepCounter = m_ScanDataStepCounter;			// Old情報
                m_ScanDataStepCounter = NCON_MEAS_SEQ::MS_ERROR;		// 10  - error 停止（終了)
                break;
            }
            break;
        case NCON_MEAS_SEQ::MAIN_END:									// 8  - メイン(サンプリング）スキャン終了->ダミースキャンへ
            // 転送バッファが完了するまで待ちを行うこと 2021.3.8
            m_ScanDataStepCounter = NCON_MEAS_SEQ::DUMMY_START;		    // ダミースキャンへ　ループ 
            m_StepStartTime = timeGetTime();						    // ステップ開始時間
            break;
        case NCON_MEAS_SEQ::MS_ERROR:									// 9  - error 停止（終了)
            // error処理 2021.3.8現在　エラー内容不確定
            m_ScanDataStepCounter = NCON_MEAS_SEQ::FINISH;
            break;
        case NCON_MEAS_SEQ::BREAK:										// 10  - 中断
            // 転送バッファーが完了するまで待ちたい
            m_ScanDataStepCounter = NCON_MEAS_SEQ::FINISH;
            break;
        case NCON_MEAS_SEQ::FINISH:										// 11  - スレット終了
            ThredLoopFg = false;
            break;
        }
        Sleep(1);
    }
}



/***********************************************************************

    べクロトン情報取得

    BOOL* bSWfg 現在のボタンの状態
    遷移作業は上位で判断する。

    戻り値 = 0  データなし(待ちのこと)
             1  データ取得 
             2  中断
             -1  Error  2021.3.6 不明

	 移植(2025.5.15yori)

***********************************************************************/

int HwCtrl::GetVecDataEx(VecDtEx* PosiData)
{
    int iRes = -1; // 不明エラーセット

    if (m_bGetThreadStopFlag == false)
    {
        int ires = m_hVecCnt.VecFunc_DataRequestEx(PosiData, 1); // 非接触と有接触モードでは動作が異なる スキャナはデータは1個のみとすること
                                                                 // 非接触でデータがある場合はVEC_OK(0)が返る
        
        // ボタンの監視
        {
            int button = PosiData->button & 0x0002;				// SW1を見る
            if (button != 0) m_bSwSts = true;					// ボタンが押された(極性を反転しないこと)
            else             m_bSwSts = false;
            m_SwTime = timeGetTime();							// 検出時間							
        }

        if (ires == VEC_OK)
        {
            if (m_hVecCnt.m_GetdataNo >= 1)
            {
                iRes = 1; // データあり 注意マニュアルにある戻り値で見てはいけない		
            }
            else {
                iRes = 0; // データなし
            }
        }
        else if (ires == (int)VEC_RET_CODE::RET_CODE__STOP_BUFFER)
        {
            // ベクトロン内部のバッファがいっぱいなのでクリアする
            ires = m_hVecCnt.VecCmd_ReqVecBClr();
            ires = m_hVecCnt.VecCmd_ReqVecReStart();

            if (ires != (int)VEC_RET_CODE::RET_CODE__OK) iRes = -1;		// 測定再開不可能なのでエラー状態へ移行
            else                                         iRes = 0;		// データなし
        }
    }
    else {
        iRes = 2; // 中断指示
    }

    return iRes;
}



/***********************************************************************

    トップデータ処理
    この関数は、スキャン開始後の先頭データチェック
    先頭のみ SetTds1stPosition()でスキャナーに先頭データを設定する必要がある
    次からは現在の情報をセットしてスキャナーデータを取得していく
    注意：先頭データはSWを無視する。
    戻り値 0:成功
           1
           2:中止
           -1:エラー
    移植(2025.5.15yori)

***********************************************************************/

int HwCtrl::GetMeasTopData()
{
    // 1. べクロトンデータの取得
    VecDtEx PosiData;
    bool VecGetLoopFg = true;
    int iVecSts = -1;
    bool bSwFg = false;
    while (VecGetLoopFg)
    {
        int res = GetVecDataEx(&PosiData);
        switch (res)
        {
        case 0:	Sleep(1);
            break;								// データなし
        case 1:									// データ取得
            m_LineNo = PosiData.no;				// 取得ライン番号
            SetTds1stPosition(&PosiData);		// 先頭データセット
            iVecSts = 0;
            VecGetLoopFg = false;
            break;
        case 2:				// 中止処理
        case 3:				// 中止処理
            iVecSts = 3;
            VecGetLoopFg = false;
            break;
        default:
            // ログ出力 
            iVecSts = -1;			// エラー処理 2021.3.6現在　エラーの取得不明のため処理の不明
            VecGetLoopFg = false;
            break;
        }
    }

    return iVecSts;
}



/***********************************************************************

    スキャナー先頭データセット
    ベクトロンデータとは構造体がことなるので変換する。
    2021.3.6現在確認は取っていないがこのタイミングでﾍﾞｸﾄﾛﾝデータ取得はNo = 1となっているはず。
    というか1になるように開始させるとこ
    2021.3.6
    移植(2025.5.15yori)

***********************************************************************/

void HwCtrl::SetTds1stPosition(const VecDtEx* pGetData)
{
    VecRet VecData; // スキャナー側のベクトロンデータ

    // 2021.3.6  hStDataEx->pGetData->no == 1 確認のこと
    ConvertVecTranceData(pGetData, &VecData); // 構造体の内容がことなるため変換が必要
    TdsVec1stPnt(&VecData);
}



/***********************************************************************

    べクロトン取得データをスキャナのベクトロン位置情報に変換
    違いがあるので注意
    べクロトン取得データ          VecDtEx* pGetData;
    スキャナのベクトロン位置情報 VecRet*	pVecData;			// ベクトロンのデータ
    移植(2025.5.15yori)

***********************************************************************/

void HwCtrl::ConvertVecTranceData(const VecDtEx* pGetData, VecRet* pVecData)
{

    pVecData->no1 = (int)pGetData->no;			// 型式違う !< データ要求に対しての要求されたラインナンバー
    pVecData->no2 = 0;							// 未使用 !< データ要求、ステータス要求に対しての最新のラインナンバー
    pVecData->no3 = 0;							// 未使用 !< ステータス要求に対しての最古の利用可能なラインナンバー
    for (int i = 0; i < 3; ++i)
    {
        pVecData->xyz[i] = pGetData->xyz[i];		// !< データ要求に対してのXYZ
        pVecData->ijk[i] = pGetData->ijk[i];		// !< データ要求に対してのIJK
        pVecData->ijk2[i] = pGetData->ijk2[i];		// !< データ要求に対してのI2J2K2
    }

    pVecData->error = 0;							// 未使用 !< エラーコード サイズ違いでコピーできない
    pVecData->button = 0;							// 未使用 !< 測定ボタンの状態 (ON:1 OFF:0)
    pVecData->scan = 0;								// 未使用 !< 測定状態（アイドル中:0 スキャン中:1 その他:2）
    for (int i = 0; i < 7; ++i)
    {
        pVecData->angle[i] = pGetData->angle[i];	// 配列サイズが違うので注意 !< 各軸の角度([0]:7軸 [1]～[6]:1～6軸)

    }
}

/***********************************************************************

    トリガーボタンステータス送信(2021.11.25)
    移植(2025.5.15yori)

***********************************************************************/

int HwCtrl::TriggerButtonAndMeasDataStatusTransfer(bool buttonfg, bool measdatafg)
{
    int iRecQue = 0;
    OneLineData2* ptlinedata2;
    int isize;

    ptlinedata2 = new OneLineData2;
    ptlinedata2->iDataNum_Rec = 0;
    ptlinedata2->iDataNum = 0;
    ptlinedata2->bButtonFg = buttonfg;
    ptlinedata2->bMeasDataFg = measdatafg;
    isize = sizeof(OneLineData2);
    iRecQue = LplSendMesBox2(NONCONTACT_DATA, isize, (char*)(ptlinedata2));
    while (iRecQue == 1) // PolyWorksが読み込むまで送信し続ける(2022.4.1yori)
    {
        iRecQue = LplSendMesBox2(NONCONTACT_DATA, isize, (char*)(ptlinedata2));
        if (iRecQue == 0)
        {
            break;
        }
        Sleep(1);
    }

    delete ptlinedata2; // 解放(2022.2.1yori)

    return iRecQue;
}



/***********************************************************************

    スキャン作業
    戻り値が複雑なため、実スキャン関数を別ループとする

    戻り値 = 0 SW状態遷移
             2 停止処理中止
            -1 error     ?????
    移植(2025.5.15yori)

***********************************************************************/

int HwCtrl::DataSamplingandTransfer(bool transFg, int* pErrorCode)
{
    bool bSwFg = false;
    int iSts = 0;
    bool bLoop = true;
    while (bLoop)											// スキャンループ
    {
        int res = OneDataSamplingandTransfer(transFg, pErrorCode);

        switch (res) {
        case 0:	// サンプリング中
            Sleep(1);
            break;
        case 1:	//SW = サンプリング Stop (スキャン停止は行われている)
            iSts = 0;									// SWによる状態遷移
            bLoop = false;										// スキャンループ停止
            break;
        case 2:	// 中止
            bLoop = false;										// スキャンループ停止
            iSts = 2;											// 中断
            break;
        case 3:	// BUFFERがFULL
            bLoop = false;										// スキャンループ停止
            iSts = 3;											// 中断
            break;
        default:
            // ログ出力
            bLoop = false;										// スキャンループ停止
            iSts = -1;											// エラー
            break;
        }
    }

    return iSts;
}


/***********************************************************************

    非接触でのスキャナ（ライン）データのの取得

    1.べクロトンデータの取得
　　　戻り：SWの遷移と中止あり
  　　チェックとして指定ライン番号でない場合は抜けエラーとする。
      エラー処理は後回し
    
    2.ラインデータチェック
  　  スキャナに指定ライン番号があるかをチェックする
    
    3.べクロトンデータ変換　＆　スキャナーデータの取得と転送バッファへの転送
    4.error 処理
    
    非接触の場合、べクロトンとスキャナはハードトリガで同期サンプリングされ、
    ライン番号が合致した状態でサンプリングされてくる
    
    引数
    bool transFg = true  -- polyworkバッファに転送
                   false -- 転送しない (dummyscan用)
    int* piLineNo 現在のライン番号
    bool* pbSwFg  現在のスイッチ状態
    
    戻り値：0 正常データ取得　（ライン番号の加算）iVecSt
            1 SW
            2 中止
            4 error  -2 ライン抜け
                     -1 通信バッファオーバフロー
                     詳細は*pErrorCodeで 通信以外は不明
    注意：ベクトロンi/f スキャナi/fのアクセスはスレット内で行うこと
    移植(2025.5.15yori)

***********************************************************************/

int HwCtrl::OneDataSamplingandTransfer(bool transFg, int* pErrorCode)
{
    char* cs;

    VecDtEx PosiData; // べクロトン 1座標データ (veccom.dllよりべクロトン本体より読み出し)
    VecRet VecData; // スキャナ側のベクトロンデータ (スキャナデータ変換用データ　同じ構造体でない)

    int iSts = -1;
    bool TranceSts = true;
    int line_no = 9999;

    // 1.べクロトンデータの取得
    bool VecGetLoopFg = true;
    int iVecSts = -1;
    while (VecGetLoopFg)
    {
        int res = GetVecDataEx(&PosiData);

        // sw状態監視 前回が離されている状態で押された場合は遷移する
        // swは戻り値を無視して検査する
        if (m_bSwSts == true && m_bOldSwSts == false)
        {
            DWORD tmp = m_SwTime - m_StepStartTime;								// 検出時間
            if ( m_hVecCnt.CHATTRING_INVALIDTIME < tmp)
            {
                iVecSts = 1;
                m_bOldSwSts = m_bSwSts;
                m_OldSwTime = m_SwTime;
                goto job_exit;													// 完了   4.error 処理へ
            }
            else {																// 未時間時間は変化させない
                m_bOldSwSts = m_bSwSts;
                m_OldSwTime = m_SwTime;
            }
        }
        else {
            m_bOldSwSts = m_bSwSts;
            m_OldSwTime = m_SwTime;
        }

        switch (res)
        {
        case 0:	Sleep(2);
            break;                                                              // データなし　状態監視ループ
        case 1:                                                                 // データ取得			
            line_no = (int)PosiData.no;
            iVecSts = 0;
            VecGetLoopFg = false;
            break;
        case 2:                                                                 // 中止処理
            iVecSts = 2;
            VecGetLoopFg = false;
            break;
        default:
            // ログ出力 
            iVecSts = -1;			// エラー処理 2021.3.6現在　エラーの取得不明のため処理の不明
            VecGetLoopFg = false;
            break;
        }
    }

    // 2.ラインデータチェック
    if (iVecSts == 0)
    {
        bool LineGetLoopFg = true;
        while (LineGetLoopFg)
        {
            if (m_bGetThreadStopFlag == true)
            {
                iVecSts = 2;	// 中断
                LineGetLoopFg = false;
            }
            else {
                int	res = TdsIsLineExist(m_LineNo); // 取得ライン番号確認
                switch (res)
                {
                case -2:	// 指定ラインなし　ライン抜けエラー
                    // MEMO : ライン抜けのエラー処理を行ってください
                    iVecSts = -2;	// Line抜けエラー
                    cs = Error_Defin::GetErrorString(ERROR_CODE::ERROR_CODE_LINENUMBERMISSION);
                    // エラーメッセージは後でコーディング(2025.5.15yori)
                    LineGetLoopFg = false;
                    break;
                case -1:	//データなし　受信待ち
                    Sleep(300);		// 要注意　データなし状態で3回サンプリングすると-3が発生
                    break;
                case 0:		// あり受信途中
                    Sleep(1);
                    break;
                case 1:		// あり受信完了
                    iVecSts = 0;
                    LineGetLoopFg = false;
                    break;
                default:	// Unknow error
                    //-3 データなしを3回続けると発生する。-4の可能性もあり発生後はLAN遮断される
                    iVecSts = -1;			// エラー処理 2021.3.6現在　エラーの取得不明のため処理の不明
                    //MessageBox::Show("OneDataSampling -3 error ", "error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    // 上記より戻り値とラインNoを明示的に表示(2022.1.17yori)
                    char buff[64] = "";
                    sprintf_s(buff, "Line Exist:%d LineNo:%d", res, m_LineNo); //「TdsIsLineExist」を変更」(2022.3.18yori)
                    // エラーメッセージは後でコーディング(2025.5.15yori)
                    LineGetLoopFg = false;
                    break;
                }
            }
        }
    }

    // 3.べクロトンデータ変換　＆　スキャナーデータの取得と転送バッファへの転送
    if (iVecSts == 0)
    {
        ++m_LineNo;
        ConvertVecTranceData(&PosiData, &VecData);						//構造体の内容がことなるため変換が必要

        TranceSts = GetandSendScannerLineData(&VecData, transFg);		// この関数内でScanerデータ取得あり transFg-trueでpolyworksにデータ転送 false dummyscan用
        if (!TranceSts)
        {
            // 1次バッファ ptstatus[] 256がいっぱいになっているときエラー表示 その先のQueがいっぱいかそのまた先のPolyworksメモリマップドファイルを読み出してもらいえない
            // 最終的には無視するか？
            // エラーメッセージは後でコーディング(2025.5.15yori)
            iVecSts = 3;		// バッファがいっぱいの場合中断とする　
        }
    }

job_exit:

    // 4.error 処理
    if (iVecSts == 0 && TranceSts == true)
    {
        *pErrorCode = 0;		// すべて成功
        iSts = 0;				// サンプリング処理継続
    }
    else {
        BOOL bRec = TdsVecScanStop(m_iSn);					// それ以外すべて　中断命令 
        if (iVecSts == 1)		// SW検出
        {
            *pErrorCode = 0;
            iSts = 1;			// SWによる状態遷移
        }
        else if (iVecSts == 2) //中止(2021.11.19yori)
        {
            iSts = 2;
        }
        else if (iVecSts == 3)
        {
            iSts = 3;		// fullCount 再測定とする
        }
        else {
            if (TranceSts == false)
            {
                *pErrorCode = -1;	// 通信バッファオーバーフロー
                iSts = 4;			// エラー状態
            }
            else {
                *pErrorCode = iVecSts;	// 2021.3.6現在エラーをすべて解析できない
                iSts = 4;				// エラー状態
            }
        }
    }

    return iSts;
}



/***********************************************************************

    スキャナーデータの取得
    VecRet* pVecData ベクトロン取得データ(変換済みデータ)
    bool tranceFg true polyworksデータ転送
                  false dummyscan

    従来関数を利用する。
    移植(2025.5.15yori)

***********************************************************************/

//bool HwCtrl::GetandStoreScannerLineData(const VecRet* pVecData, bool tranceFg)
//{
//    bool bCheckFg = true;
//    int index = 0; // 書込み先
//    int	iDataNum = 0;
//
//    WaitForSingleObject(hSEMA, INFINITE);
//
//    if (tranceFg == true)
//    {
//        // インデックスの計算
//        if (ptstatus->writeIx == MAX_LINEDATA - 1)
//        {
//            if (ptstatus->readIx != 0)
//            {
//                ptstatus->writeIx = 0;
//                index = MAX_LINEDATA - 1;
//            }
//            else
//            {
//                // 読出しが追い付かずに書込みできない場合の対処
//                bCheckFg = false;
//                goto job_exit;
//            }
//        }
//        else
//        {
//            if (ptstatus->writeIx + 1 != ptstatus->readIx)
//            {
//                index = ptstatus->writeIx;
//                ptstatus->writeIx++;
//            }
//            else
//            {
//                // 読出しが追い付かずに書込みできない場合の対処
//                bCheckFg = false;
//                goto job_exit;
//            }
//        }
//    }
//    else {
//        index = 0; // 先頭のみを使用する
//    }
//
//    ptlinedata2[index].tVecData = *pVecData; // ベクトロンデータのセット
//
//    // 計測データ取得 転送しない場合も計算を行う
//    // 最終的にはDummyでもどこかに値を表示するかもしれない
//    memset(ptlinedata2[index].tPulsData, 0, sizeof(PulsData) * 3500); //ゼロクリア追加(2021.11.15yori)
//    int	iRec = TdsVecAndMeas(&(ptlinedata2[index].tVecData), (ptlinedata2[index].tPulsData), m_iXSize, &iDataNum);
//    ptlinedata2[index].lineNo = (int)pVecData->no1;
//    ptlinedata2[index].iDataNum_Rec = iRec;
//    ptlinedata2[index].iDataNum = iDataNum;
//    ptlinedata2[index].bMeasDataFg = m_bmeasfg; //追加(2021.11.24yori)
//
//    if (tranceFg == true)
//    {
//        // バッファの残数を演算
//        int iRemainNo;
//        int itmp = ptstatus->writeIx - ptstatus->readIx;
//        if (itmp < 0) iRemainNo = MAX_LINEDATA + itmp;
//        else          iRemainNo = MAX_LINEDATA - itmp;
//        ptstatus->userate++;
//    }
//
//    bCheckFg = true;
//
//job_exit:
//
//    ReleaseSemaphore(hSEMA, 1, NULL);
//
//    if (!bCheckFg)
//    {
//
//    }
//
//    return bCheckFg;
//}


/***********************************************************************

    ベクトロンとスキャナデータを合成→1ラインデータ作成→PolyWorksへ1ライン送信
    追加(2025.5.15yori)

***********************************************************************/

bool HwCtrl::GetandSendScannerLineData(const VecRet* pVecData, bool tranceFg)
{
    bool bCheckFg = true;
    int	iDataNum = 0;
    int iRec = 0;
    int index = 0;
    int iRecQue = 0;

    ptlinedata2025 = new OneLineData2;

    WaitForSingleObject(hSEMA, INFINITE);

    ptlinedata2025->tVecData = *pVecData; // ベクトロンデータのセット

    memset(ptlinedata2025->tPulsData, 0, sizeof(PulsData) * 3500); // ゼロクリア追加(2021.11.15yori)

    // ポインタ位置チェック作成中のため、コメントアウト(2025.9.3yori)
    //if (m_PointerCheckFg == true && m_bmeasfg == true && m_PointerCheckLineNo == 1) // ポインタ位置チェックの場合は最初の1ライン目の測定データで評価する(2025.7.4yori)
    //{
    //    TdsVecGetLocalData(pVecData->no1, ptlinedata2025->tPulsData, m_iXSize, &iDataNum); // 1ライン分のスキャナローカルデータを取得
    //    for (int i = 0; i < iDataNum; i++) // 作成途中(2025.7.4yori)
    //    {
    //        m_PointerCheckScanData += ptlinedata2025->tPulsData[i].dataZ;
    //    }
    //    m_PointerCheckScanData = m_PointerCheckScanData / iDataNum; // 平均距離計算
    //    m_PointerCheckLineNo++;
    //}
    //else
    //{
        iRec = TdsVecAndMeas(&(ptlinedata2025->tVecData), (ptlinedata2025->tPulsData), m_iXSize, &iDataNum); // ベクトロンとスキャンデータ合成
        ptlinedata2025->lineNo = (int)pVecData->no1;
        ptlinedata2025->iDataNum_Rec = iRec;
        ptlinedata2025->iDataNum = iDataNum;
        ptlinedata2025->bMeasDataFg = m_bmeasfg;

        // デバッグ用(2025.8.5yori)
        //if (ptlinedata2025[index].bMeasDataFg == true) // 測定データのみ出力
        //{
        //    FileOutput();
        //}

        ptlinedata2025->iSendDataNo = SendLineDataCheck2(index); // 無効データ処理を行う(2021.12.1yori)
        // ダミースキャンは、レーザーが照射されている部分のみ座標値を取得される。(コメントアウト追加2025.5.15yori)
        // ダミースキャンは、奇数Noが有効な座標値、偶数Noが無効な座標値が取得される。(コメントアウト追加2025.5.15yori)
        if (ptlinedata2025->iSendDataNo != 0) // 有効データ数を構造体へ追加(2021.12.1yori)
        {
            int isize = sizeof(OneLineData2);  // 転送データ数(バイト)：196216 // sizeofで確認(2025.5.15yori)

            //iRecQue = LplSendMesBox2(NONCONTACT_DATA, isize, (char*)(ptlinedata2025));  // VECのijkを取得するため、OneLineData2を送信する(2021.5.27yori)
            if (m_b_Button_ConnectFlag == false)  // アプリから接続した場合は、PolyWorksへデータを送信しない。(2025.7.3yori)
            {
                iRecQue = LplSendMesBox(NONCONTACT_DATA, isize, (char*)(ptlinedata2025));  // (2025.5.15yori)
            }
            // Queに積めたかどうか
            if (iRecQue != 0)
            {
                // 0以外の戻りはない
            }

            bCheckFg = true;
        }
        else // すべて無効の場合はデータを積まないで戻る
        {
            //bCheckFg = false; // コメントアウト(2025.5.15yori)
        }
    //}

    ReleaseSemaphore(hSEMA, 1, NULL);

    delete ptlinedata2025;

    return bCheckFg;
}



/***********************************************************************
    
    キャリブレーションと始業前点検データのチェックと計算
    2021.9.6yori
    移植(2025.5.15yori)

***********************************************************************/

void HwCtrl::CalibCheckAndCalcu(CalibResult* ptCalibResult, ChkScnResult* ptChkResult)
{
    int ErrorCode = 0;
    double ofb_old[3] = { 0 }; //追加(2021.12.20yori)
    double ttb_old[3] = { 0 }; //追加(2021.12.20yori)
    double ofb[3] = { 0 };
    double ttb[3] = { 0 };
    int iMeasType = 0;
    double maxx = 0, maxy = 0, maxz = 0, minx = 0, miny = 0, minz = 0, maxh = 0, minh = 0;

    TdsVecGetMeasType(&iMeasType);

    if (iMeasType == TDS_MEASTYPE_CALIB_FULL) // フルキャリブレーションの場合(2021.8.18yori)
    {
        if (TdsVecCheckCalibData(m_ScanShotNo))
        {
            if (m_ScanShotNo == 14)
            {
                if (TdsVecExecCalibCalcu(ptCalibResult)) // デバッグ版では、「Debug Assertion Failed!」のメッセージが2回表示されるが、「無視」して問題ない。(2021.9.3yori)
                {
                    m_ScanShotNo++;
                }
                else
                {
                    ErrorCode = TdsVecErrorCode();
                    char* cs = Error_Defin::GetErrorString((ERROR_CODE)ErrorCode);
                    // エラーメッセージは後でコーディング(2025.5.15yori)
                }
            }
            else if (m_ScanShotNo == 16)
            {
                if (TdsVecExecCalibCalcu(ptCalibResult))
                {
                    // 最大値、最小値計算(2021.9.7.yori)
                    MaxCalcu43(ptCalibResult->dResult, 0, &maxx); // X最大値
                    MaxCalcu43(ptCalibResult->dResult, 1, &maxy); // Y最大値
                    MaxCalcu43(ptCalibResult->dResult, 2, &maxz); // Z最大値
                    MinCalcu43(ptCalibResult->dResult, 0, &minx); // X最小値
                    MinCalcu43(ptCalibResult->dResult, 1, &miny); // Y最小値
                    MinCalcu43(ptCalibResult->dResult, 2, &minz); // Z最小値
                    // キャリブレーション計算結果の保存、後でコーディング(2025.5.15yori)
                    // アームのスキャナパラメータを取得(2021.12.20yori)
                    m_hVecCnt.VecGetScannerPara(&ofb_old[0], &ofb_old[1], &ofb_old[2], &ttb_old[0], &ttb_old[1], &ttb_old[2]);
                    // アームのスキャナパラメータを書き込む(2021.8.25yori)
                    //現状のパラメータに計算されたパラメータを加算して書き込む(2021.12.20yori)
                    ofb[0] = ofb_old[0] + ptCalibResult->tArmParam.dArmAddOffset[0];
                    ofb[1] = ofb_old[1] + ptCalibResult->tArmParam.dArmAddOffset[1];
                    ofb[2] = ofb_old[2] + ptCalibResult->tArmParam.dArmAddOffset[2];
                    ttb[0] = ttb_old[0] + ptCalibResult->tArmParam.dArmAddTilt[0];
                    ttb[1] = ttb_old[1] + ptCalibResult->tArmParam.dArmAddTilt[1];
                    ttb[2] = ttb_old[2] + ptCalibResult->tArmParam.dArmAddTilt[2];
                    m_hVecCnt.VecSetScannerPara(ofb[0], ofb[1], ofb[2], ttb[0], ttb[1], ttb[2]);
                    m_ScanShotNo = 0;
                }
                else
                {
                    ErrorCode = TdsVecErrorCode();
                    char* cs = Error_Defin::GetErrorString((ERROR_CODE)ErrorCode);
                    // エラーメッセージは後でコーディング(2025.5.15yori)
                }

                m_ScanDataStepCounter = NCON_MEAS_SEQ::BREAK;			// 中断
                EndFg = true;
            }
            else
            {
                m_ScanShotNo++;
            }
        }
        else
        {
            ErrorCode = TdsVecErrorCode();
            char* cs = Error_Defin::GetErrorString((ERROR_CODE)ErrorCode);
            // エラーメッセージは後でコーディング(2025.5.15yori)
        }
    }
    else if (iMeasType == TDS_MEASTYPE_CALIB_USER) // ユーザーキャリブレーションの場合(2021.8.20yori)
    {
        if (TdsVecCheckCalibData(m_ScanShotNo))
        {
            if (m_ScanShotNo == 12)
            {
                if (TdsVecExecCalibCalcu(ptCalibResult))
                {
                    // 球中心座標値の最大値、最小値計算(2021.9.8.yori)
                    MaxCalcu43(ptCalibResult->dResult, 0, &maxx); // X最大値
                    MaxCalcu43(ptCalibResult->dResult, 1, &maxy); // Y最大値
                    MaxCalcu43(ptCalibResult->dResult, 2, &maxz); // Z最大値
                    MinCalcu43(ptCalibResult->dResult, 0, &minx); // X最小値
                    MinCalcu43(ptCalibResult->dResult, 1, &miny); // Y最小値
                    MinCalcu43(ptCalibResult->dResult, 2, &minz); // Z最小値
                    // キャリブレーション計算結果の保存は、後でコーディング(2025.5.15yori)
                    // アームのスキャナパラメータを取得(2021.8.25yori)
                    m_hVecCnt.VecGetScannerPara(&ofb_old[0], &ofb_old[1], &ofb_old[2], &ttb_old[0], &ttb_old[1], &ttb_old[2]);
                    //現状のパラメータに計算されたパラメータを加算して書き込む(2021.12.20yori)
                    ofb[0] = ofb_old[0] + ptCalibResult->tArmParam.dArmAddOffset[0];
                    ofb[1] = ofb_old[1] + ptCalibResult->tArmParam.dArmAddOffset[1];
                    ofb[2] = ofb_old[2] + ptCalibResult->tArmParam.dArmAddOffset[2];
                    ttb[0] = ttb_old[0];
                    ttb[1] = ttb_old[1];
                    ttb[2] = ttb_old[2];
                    m_hVecCnt.VecSetScannerPara(ofb[0], ofb[1], ofb[2], ttb[0], ttb[1], ttb[2]);
                    m_ScanShotNo = 0;
                }
                else
                {
                    ErrorCode = TdsVecErrorCode();
                    char* cs = Error_Defin::GetErrorString((ERROR_CODE)ErrorCode);
                    // エラーメッセージは後でコーディング(2025.5.15yori)
                }

                m_ScanDataStepCounter = NCON_MEAS_SEQ::BREAK;			// 中断
                EndFg = true;
            }
            else
            {
                m_ScanShotNo++;
            }
        }
        else
        {
            ErrorCode = TdsVecErrorCode();
            char* cs = Error_Defin::GetErrorString((ERROR_CODE)ErrorCode);
            // エラーメッセージは後でコーディング(2025.5.15yori)
        }
    }
    else if (iMeasType == TDS_MEASTYPE_MACHINE_CHECK) // 始業前点検の場合(2021.8.31yori)
    {
        if (TdsVecCheckCalibData(m_ScanShotNo))
        {
            if (m_ScanShotNo == 5)
            {
                if (TdsVecExecChkScnCalcu(ptChkResult))
                {
                    // 面高さの最大値、最小値計算(2021.9.8.yori)
                    MaxCalcu4(ptChkResult->dPlnHeight, &maxh); // 最大値
                    MinCalcu4(ptChkResult->dPlnHeight, &minh); // 最小値
                    // 始業前点検結果の保存は、後でコーディング(2025.5.15yori)
                    m_ScanShotNo = 0;
                }
                else
                {
                    ErrorCode = TdsVecErrorCode();
                    char* cs = Error_Defin::GetErrorString((ERROR_CODE)ErrorCode);
                    // エラーメッセージは後でコーディング(2025.5.15yori)
                }

                m_ScanDataStepCounter = NCON_MEAS_SEQ::BREAK;			// 中断
                EndFg = true;
            }
            else
            {
                m_ScanShotNo++;
            }
        }
        else
        {
            ErrorCode = TdsVecErrorCode();
            char* cs = Error_Defin::GetErrorString((ERROR_CODE)ErrorCode);
            // エラーメッセージは後でコーディング(2025.5.15yori)
        }
    }
}



/***********************************************************************

    最大値計算
    2021.9.8yori
    移植(2025.5.15yori)

***********************************************************************/

void HwCtrl::MaxCalcu43(double data[4][3], int index, double* max)
{
    int i;
    *max = data[0][index];
    for (i = 1; i < 4; i++)
    {
        if (data[i][index] > *max)
        {
            *max = data[i][index];
        }
    }
}

/***********************************************************************

    最小値計算
    2021.9.8yori
    移植(2025.5.15yori)

***********************************************************************/

void HwCtrl::MinCalcu43(double data[4][3], int index, double* min)
{
    int i;
    *min = data[0][index];
    for (i = 1; i < 4; i++)
    {
        if (data[i][index] < *min)
        {
            *min = data[i][index];
        }
    }
}

/***********************************************************************

    最大値計算
    2021.9.8yori
    移植(2025.5.15yori)

***********************************************************************/

void HwCtrl::MaxCalcu4(double data[4], double* max)
{
    int i;
    *max = data[0];
    for (i = 1; i < 4; i++)
    {
        if (data[i] > *max)
        {
            *max = data[i];
        }
    }
}



/***********************************************************************

    最小値計算
    2021.9.8yori
    移植(2025.5.15yori)

***********************************************************************/

void HwCtrl::MinCalcu4(double data[4], double* min)
{
    int i;
    *min = data[0];
    for (i = 1; i < 4; i++)
    {
        if (data[i] < *min)
        {
            *min = data[i];
        }
    }
}



/***********************************************************************

    スキャンは途中停止があるため先頭データ取得時にresetしておく
    移植(2025.5.15yori)

***********************************************************************/

void HwCtrl::Memory_ResetCounter()
{
    WaitForSingleObject(hSEMA, INFINITE);

    ptstatus->readIx = 0;
    ptstatus->writeIx = 0;
    ptstatus->userate = 0;

    ReleaseSemaphore(hSEMA, 1, NULL);
}



/***********************************************************************

    1ラインデータをPolyWorksへ転送
    直接メモリマップドファイルに転送する
    2021.3.10 無効データを削除する
    移植(2025.5.15yori)

***********************************************************************/

//bool HwCtrl::SendOneLineData()
//{
//    bool bCheckFg = true;
//    int index = 0; // 転送する取得データ番号
//    int before_readIx = 0;
//    int iRecQue = 0;
//
//    WaitForSingleObject(hSEMA, INFINITE);
//    
//    if (LplSendMesBoxBuffferEmpty(NONCONTACT_DATA) != 0)				// 2021.4.15
//    {
//        bCheckFg = true;	// 戻りはtrue
//        goto job_exit;		// バッファの空きがないため以下の作業をスキップする
//    }
//
//    if (ptstatus->readIx == ptstatus->writeIx)
//    {
//        bCheckFg = false;		//読み出すデータが無いときの処理
//        goto job_exit;
//    }
//
//    //読み出すデータがある
//    if (ptstatus->readIx == MAX_LINEDATA - 1)
//    {
//        before_readIx = ptstatus->readIx;
//        ptstatus->readIx = 0;
//        index = MAX_LINEDATA - 1;
//    }
//    else
//    {
//        before_readIx = ptstatus->readIx;
//        ptstatus->readIx++;
//        index = ptstatus->readIx - 1;
//    }
//
//    // 送信用バッファを確保する
//    int iXSize = ptlinedata2[index].iDataNum; // 変更(2021.5.27yori)
//    ptlinedata2[index].iSendDataNo = SendLineDataCheck2(index);								// 無効データ処理を行う(2021.12.1yori) 
//    if (ptlinedata2[index].iSendDataNo != 0)												// 有効データ数を構造体へ追加(2021.12.1yori)
//    {
//        int isize = sizeof(OneLineData2);													// 転送データ数(バイト)：190048→196208 // 変更(2021.11.16yori)
//
//        // この関数を実行する前にバッファが空どうかを確認する 
//        iRecQue = LplSendMesBox2(NONCONTACT_DATA, isize, (char*)(&ptlinedata2[index]));     // VECのijkを取得するため、OneLineData2を送信する(2021.5.27yori)
//                                                                                            // 全てのデータが無効データの場合のみ、上記の場合分けにより、送信しない(2021.5.27yori)
//        ptstatus->userate--;
//        //Queに積めたかどうか
//        if (iRecQue != 0)
//        {
//            // 0以外の戻りはない
//        }
//        bCheckFg = true;
//    }
//    else // すべて無効の場合はデータを積まないで戻る
//    {
//        bCheckFg = false;
//        ptstatus->userate--; //無効データもカウント(2021.9.16yori)
//    }
//
//job_exit:
//
//    ReleaseSemaphore(hSEMA, 1, NULL);
//
//    return bCheckFg;
//}



/***********************************************************************

    無効データの処理(レーザーが戻らない)
    index バッファptlinedata2[]位置 (チェック元)
    PulsData チェック後に積み出し (無効値を除く)
　  所得データを先頭詰めで差し替える(2021.12.1yori)
    999999.0が無効値 floatデータのため 999998.0(INVALID_CHECK)より大きい値を無効値とする
    戻り値 0：転送データなし その他：転送データ数
    移植(2025.5.15yori)

***********************************************************************/

int HwCtrl::SendLineDataCheck2(int index)
{
    int transferCnt = 0;
    
    int iXSize = ptlinedata2025[index].iDataNum; //スキャンデータ数

    for (int i = 0; i < iXSize; ++i)
    {
        if (ptlinedata2025[index].tPulsData[i].dataX < INVALID_CHECK &&
            ptlinedata2025[index].tPulsData[i].dataY < INVALID_CHECK &&
            ptlinedata2025[index].tPulsData[i].dataZ < INVALID_CHECK)
        {
            //有効データ
            ptlinedata2025[index].tPulsData[transferCnt++] = ptlinedata2025[index].tPulsData[i]; //先頭詰めにする
        }
    }

    return transferCnt;	// (transferCnt != 0) // 転送データあり
}



/***********************************************************************

    スキャンデータのファイル出力
    移植(2025.8.5yori)

***********************************************************************/
void HwCtrl::FileOutput()
{
    FILE* pf;
    char cPath[256] = { 0 }; // ファイルのパス
    char cData1[256] = { 0 }; // ラインNo, IJK
    char cData2[256] = { 0 }; // XYZ

    sprintf_s(cPath, "C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Log\\ScanLineData.txt"); // 書込むファイルのパス
    int index = 0, i = 0;

    if ((fopen_s(&pf, cPath, "a")) == 0)
    {
        sprintf_s(cData1, "LineNo%d,%f,%f,%f\n", m_LineNo, ptlinedata2025[index].tVecData.ijk[0], ptlinedata2025[index].tVecData.ijk[1], ptlinedata2025[index].tVecData.ijk[2]);
        fseek(pf, 0, SEEK_SET); // file先頭へ移動
        fputs((char*)&(cData1), pf); // fileへ書き込み
        memset(cData1, 0, sizeof(cData1)); // 配列をクリア

        int iScanDataNo = SendLineDataCheck2(index); // 無効データ処理を行う

        for (i = 0; i < iScanDataNo; i++)
        {
            sprintf_s(cData2, "%f,%f,%f\n", ptlinedata2025[index].tPulsData[i].dataX, ptlinedata2025[index].tPulsData[i].dataY, ptlinedata2025[index].tPulsData[i].dataZ);
            fputs((char*)&(cData2), pf); // fileへ書き込み
            memset(cData2, 0, sizeof(cData2)); //配列をクリア
        }

        fclose(pf); //ファイルを閉じる
    }
    else
    {
        // ファイルを開くことができなかった
    }
}



/***********************************************************************

    アームパラメータの取得(テキストデータ)
    2025.9.10 add eba

***********************************************************************/
int HwCtrl::GetArmParaV8(CALIB_DATA* para, int psid)
{
    int ret = 0;

    ret = HwCtrl::m_hVecCnt.VecCmd_Test002(para);
    ret |= HwCtrl::m_hVecCnt.VecCmd_Test004(para);
    ret |= HwCtrl::m_hVecCnt.VecCmd_Test006(para);
    ret |= HwCtrl::m_hVecCnt.VecCmd_Test008(para);
    ret |= HwCtrl::m_hVecCnt.VecCmd_DprobeV8(para, psid);

    return (ret);
}



/***********************************************************************

    アームパラメータの設定(テキストデータ)
    2025.9.10 add eba

***********************************************************************/
int HwCtrl::SetArmParaV8(CALIB_DATA* para, int psid)
{
    int ret = 0;

    ret = HwCtrl::m_hVecCnt.VecCmd_Test003(para);
    ret |= HwCtrl::m_hVecCnt.VecCmd_Test005(para);
    ret |= HwCtrl::m_hVecCnt.VecCmd_Test007(para);
    ret |= HwCtrl::m_hVecCnt.VecCmd_Test009(para);
    ret |= HwCtrl::m_hVecCnt.VecCmd_SprobeV8(para, psid);
    ret |= HwCtrl::m_hVecCnt.VecCmd_Iso();

    return (ret);
}



/***********************************************************************

    アームパラメータ保存
    2025.10.8yori)

***********************************************************************/
void HwCtrl::SavePara(const TCHAR* path)
{
    int ret = 0, psid = 0, branch = 0, no = 0, i = 0, j = 0, k = 0, l = 0 ;
    CALIB_DATA para;
    char para2[64] = { 0 };
    char test002[1024] = { 0 };
    char test004[1024] = { 0 };
    char test006[1024] = { 0 };
    char test008[512] = { 0 };
    char test010[1024] = { 0 };
    char test012[1024] = { 0 };
    char test018[128] = { 0 };
    char dprdc[512] = { 0 };
    char dprobe[20][512] = { 0 };
    char dprobema[3][15][512] = { 0 };
    char dlevel[64] = { 0 };
    char dcnt[32] = { 0 };
    char dlim[7][256] = { 0 };
    char dserial[32] = { 0 };
    char* token[40];
    char* context = NULL;

    // TEST@002
    ret = HwCtrl::m_hVecCnt.VecCmd_Test002(&para);
    // スペース区切りのパラメータを分割
    token[0] = strtok_s(para.test002.para, " ", &context);
    for (i = 1; i < 19; i++)
    {
        token[i] = strtok_s(NULL, " ", &context);
    }
    // パラメータ保存フォーマットへ変更
    sprintf_s(test002, "TEST@002\nARM1,");
    strcat_s(test002, sizeof(test002), token[0]);
    strcat_s(test002, sizeof(test002), ",ARM2,");
    strcat_s(test002, sizeof(test002), token[1]);
    strcat_s(test002, sizeof(test002), ",ARM3,");
    strcat_s(test002, sizeof(test002), token[2]);
    strcat_s(test002, sizeof(test002), "\nAB1,");
    strcat_s(test002, sizeof(test002), token[3]);
    strcat_s(test002, sizeof(test002), ",AO1,");
    strcat_s(test002, sizeof(test002), token[11]);
    strcat_s(test002, sizeof(test002), "\nAB2,");
    strcat_s(test002, sizeof(test002), token[4]);
    strcat_s(test002, sizeof(test002), ",AO2,");
    strcat_s(test002, sizeof(test002), token[12]);
    strcat_s(test002, sizeof(test002), "\nAB3,");
    strcat_s(test002, sizeof(test002), token[5]);
    strcat_s(test002, sizeof(test002), ",AO3,");
    strcat_s(test002, sizeof(test002), token[13]);
    strcat_s(test002, sizeof(test002), "\nAB4,");
    strcat_s(test002, sizeof(test002), token[6]);
    strcat_s(test002, sizeof(test002), ",AO4,");
    strcat_s(test002, sizeof(test002), token[14]);
    strcat_s(test002, sizeof(test002), "\nAB5,");
    strcat_s(test002, sizeof(test002), token[7]);
    strcat_s(test002, sizeof(test002), ",AO5,");
    strcat_s(test002, sizeof(test002), token[15]);
    strcat_s(test002, sizeof(test002), "\nAB6,");
    strcat_s(test002, sizeof(test002), token[8]);
    strcat_s(test002, sizeof(test002), ",AO6,");
    strcat_s(test002, sizeof(test002), token[16]);
    strcat_s(test002, sizeof(test002), "\nAB7,");
    strcat_s(test002, sizeof(test002), token[9]);
    strcat_s(test002, sizeof(test002), ",AO7,");
    strcat_s(test002, sizeof(test002), token[17]);
    strcat_s(test002, sizeof(test002), "\nAB8,");
    strcat_s(test002, sizeof(test002), token[10]);
    strcat_s(test002, sizeof(test002), ",AO8,");
    strcat_s(test002, sizeof(test002), token[18]);
    strcat_s(test002, sizeof(test002), "\n\n");

    // TEST@004
    ret |= HwCtrl::m_hVecCnt.VecCmd_Test004(&para);
    // スペース区切りのパラメータを分割
    token[0] = strtok_s(para.test004.para, " ", &context);
    for (i = 1; i < 27; i++)
    {
        token[i] = strtok_s(NULL, " ", &context);
    }
    // パラメータ保存フォーマットへ変更
    sprintf_s(test004, "TEST@004\nOF0X,");
    strcat_s(test004, sizeof(test004), token[0]);
    strcat_s(test004, sizeof(test004), ",OF0Y,");
    strcat_s(test004, sizeof(test004), token[1]);
    strcat_s(test004, sizeof(test004), ",OF0Z,");
    strcat_s(test004, sizeof(test004), token[2]);
    strcat_s(test004, sizeof(test004), "\nOF1X,");
    strcat_s(test004, sizeof(test004), token[3]);
    strcat_s(test004, sizeof(test004), ",OF1Y,");
    strcat_s(test004, sizeof(test004), token[4]);
    strcat_s(test004, sizeof(test004), ",OF1Z,");
    strcat_s(test004, sizeof(test004), token[5]);
    strcat_s(test004, sizeof(test004), "\nOF2X,");
    strcat_s(test004, sizeof(test004), token[6]);
    strcat_s(test004, sizeof(test004), ",OF2Y,");
    strcat_s(test004, sizeof(test004), token[7]);
    strcat_s(test004, sizeof(test004), ",OF2Z,");
    strcat_s(test004, sizeof(test004), token[8]);
    strcat_s(test004, sizeof(test004), "\nOF3X,");
    strcat_s(test004, sizeof(test004), token[9]);
    strcat_s(test004, sizeof(test004), ",OF3Y,");
    strcat_s(test004, sizeof(test004), token[10]);
    strcat_s(test004, sizeof(test004), ",OF3Z,");
    strcat_s(test004, sizeof(test004), token[11]);
    strcat_s(test004, sizeof(test004), "\nOF4X,");
    strcat_s(test004, sizeof(test004), token[12]);
    strcat_s(test004, sizeof(test004), ",OF4Y,");
    strcat_s(test004, sizeof(test004), token[13]);
    strcat_s(test004, sizeof(test004), ",OF4Z,");
    strcat_s(test004, sizeof(test004), token[14]);
    strcat_s(test004, sizeof(test004), "\nOF5X,");
    strcat_s(test004, sizeof(test004), token[15]);
    strcat_s(test004, sizeof(test004), ",OF5Y,");
    strcat_s(test004, sizeof(test004), token[16]);
    strcat_s(test004, sizeof(test004), ",OF5Z,");
    strcat_s(test004, sizeof(test004), token[17]);
    strcat_s(test004, sizeof(test004), "\nOF6X,");
    strcat_s(test004, sizeof(test004), token[18]);
    strcat_s(test004, sizeof(test004), ",OF6Y,");
    strcat_s(test004, sizeof(test004), token[19]);
    strcat_s(test004, sizeof(test004), ",OF6Z,");
    strcat_s(test004, sizeof(test004), token[20]);
    strcat_s(test004, sizeof(test004), "\nOF7X,");
    strcat_s(test004, sizeof(test004), token[21]);
    strcat_s(test004, sizeof(test004), ",OF7Y,");
    strcat_s(test004, sizeof(test004), token[22]);
    strcat_s(test004, sizeof(test004), ",OF7Z,");
    strcat_s(test004, sizeof(test004), token[23]);
    strcat_s(test004, sizeof(test004), "\nOF8X,");
    strcat_s(test004, sizeof(test004), token[24]);
    strcat_s(test004, sizeof(test004), ",OF8Y,");
    strcat_s(test004, sizeof(test004), token[25]);
    strcat_s(test004, sizeof(test004), ",OF8Z,");
    strcat_s(test004, sizeof(test004), token[26]);
    strcat_s(test004, sizeof(test004), "\n\n");

    // TEST@006
    ret |= HwCtrl::m_hVecCnt.VecCmd_Test006(&para);
    // スペース区切りのパラメータを分割
    token[0] = strtok_s(para.test006.para, " ", &context);
    for (i = 1; i < 27; i++)
    {
        token[i] = strtok_s(NULL, " ", &context);
    }
    // パラメータ保存フォーマットへ変更
    sprintf_s(test006, "TEST@006\nTT0X,");
    strcat_s(test006, sizeof(test006), token[0]);
    strcat_s(test006, sizeof(test006), ",TT0Y,");
    strcat_s(test006, sizeof(test006), token[1]);
    strcat_s(test006, sizeof(test006), ",TT0Z,");
    strcat_s(test006, sizeof(test006), token[2]);
    strcat_s(test006, sizeof(test006), "\nTT1X,");
    strcat_s(test006, sizeof(test006), token[3]);
    strcat_s(test006, sizeof(test006), ",TT1Y,");
    strcat_s(test006, sizeof(test006), token[4]);
    strcat_s(test006, sizeof(test006), ",TT1Z,");
    strcat_s(test006, sizeof(test006), token[5]);
    strcat_s(test006, sizeof(test006), "\nTT2X,");
    strcat_s(test006, sizeof(test006), token[6]);
    strcat_s(test006, sizeof(test006), ",TT2Y,");
    strcat_s(test006, sizeof(test006), token[7]);
    strcat_s(test006, sizeof(test006), ",TT2Z,");
    strcat_s(test006, sizeof(test006), token[8]);
    strcat_s(test006, sizeof(test006), "\nTT3X,");
    strcat_s(test006, sizeof(test006), token[9]);
    strcat_s(test006, sizeof(test006), ",TT3Y,");
    strcat_s(test006, sizeof(test006), token[10]);
    strcat_s(test006, sizeof(test006), ",TT3Z,");
    strcat_s(test006, sizeof(test006), token[11]);
    strcat_s(test006, sizeof(test006), "\nTT4X,");
    strcat_s(test006, sizeof(test006), token[12]);
    strcat_s(test006, sizeof(test006), ",TT4Y,");
    strcat_s(test006, sizeof(test006), token[13]);
    strcat_s(test006, sizeof(test006), ",TT4Z,");
    strcat_s(test006, sizeof(test006), token[14]);
    strcat_s(test006, sizeof(test006), "\nTT5X,");
    strcat_s(test006, sizeof(test006), token[15]);
    strcat_s(test006, sizeof(test006), ",TT5Y,");
    strcat_s(test006, sizeof(test006), token[16]);
    strcat_s(test006, sizeof(test006), ",TT5Z,");
    strcat_s(test006, sizeof(test006), token[17]);
    strcat_s(test006, sizeof(test006), "\nTT6X,");
    strcat_s(test006, sizeof(test006), token[18]);
    strcat_s(test006, sizeof(test006), ",TT6Y,");
    strcat_s(test006, sizeof(test006), token[19]);
    strcat_s(test006, sizeof(test006), ",TT6Z,");
    strcat_s(test006, sizeof(test006), token[20]);
    strcat_s(test006, sizeof(test006), "\nTT7X,");
    strcat_s(test006, sizeof(test006), token[21]);
    strcat_s(test006, sizeof(test006), ",TT7Y,");
    strcat_s(test006, sizeof(test006), token[22]);
    strcat_s(test006, sizeof(test006), ",TT7Z,");
    strcat_s(test006, sizeof(test006), token[23]);
    strcat_s(test006, sizeof(test006), "\nTT8X,");
    strcat_s(test006, sizeof(test006), token[24]);
    strcat_s(test006, sizeof(test006), ",TT8Y,");
    strcat_s(test006, sizeof(test006), token[25]);
    strcat_s(test006, sizeof(test006), ",TT8Z,");
    strcat_s(test006, sizeof(test006), token[26]);
    strcat_s(test006, sizeof(test006), "\n\n");

    // TEST@008
    ret |= HwCtrl::m_hVecCnt.VecCmd_Test008(&para);
    // スペース区切りのパラメータを分割
    token[0] = strtok_s(para.test008.para, " ", &context);
    for (i = 1; i < 14; i++)
    {
        token[i] = strtok_s(NULL, " ", &context);
    }
    // パラメータ保存フォーマットへ変更
    sprintf_s(test008, "TEST@008\nAB0,");
    strcat_s(test008, sizeof(test008), token[0]);
    strcat_s(test008, sizeof(test008), ",AO0,");
    strcat_s(test008, sizeof(test008), token[1]);
    strcat_s(test008, sizeof(test008), "\nOFAX,");
    strcat_s(test008, sizeof(test008), token[2]);
    strcat_s(test008, sizeof(test008), ",OFAY,");
    strcat_s(test008, sizeof(test008), token[3]);
    strcat_s(test008, sizeof(test008), ",OFAZ,");
    strcat_s(test008, sizeof(test008), token[4]);
    strcat_s(test008, sizeof(test008), "\nTTAX,");
    strcat_s(test008, sizeof(test008), token[5]);
    strcat_s(test008, sizeof(test008), ",TTAY,");
    strcat_s(test008, sizeof(test008), token[6]);
    strcat_s(test008, sizeof(test008), ",TTAZ,");
    strcat_s(test008, sizeof(test008), token[7]);
    strcat_s(test008, sizeof(test008), "\nOFBX,");
    strcat_s(test008, sizeof(test008), token[8]);
    strcat_s(test008, sizeof(test008), ",OFBY,");
    strcat_s(test008, sizeof(test008), token[9]);
    strcat_s(test008, sizeof(test008), ",OFBZ,");
    strcat_s(test008, sizeof(test008), token[10]);
    strcat_s(test008, sizeof(test008), "\nTTBX,");
    strcat_s(test008, sizeof(test008), token[11]);
    strcat_s(test008, sizeof(test008), ",TTBY,");
    strcat_s(test008, sizeof(test008), token[12]);
    strcat_s(test008, sizeof(test008), ",TTBZ,");
    strcat_s(test008, sizeof(test008), token[13]);
    strcat_s(test008, sizeof(test008), "\n\n");

    // TEST@010
    ret |= HwCtrl::m_hVecCnt.VecCmd_Test010(&para);
    // スペース区切りのパラメータを分割
    token[0] = strtok_s(para.test010.para, " ", &context);
    for (i = 1; i < 16; i++)
    {
        token[i] = strtok_s(NULL, " ", &context);
    }
    // パラメータ保存フォーマットへ変更
    sprintf_s(test010, "TEST@010\nNO.5 BASE HIGHT,");
    strcat_s(test010, sizeof(test010), token[0]);
    strcat_s(test010, sizeof(test010), "\nNO.5 0deg,");
    strcat_s(test010, sizeof(test010), token[1]);
    strcat_s(test010, sizeof(test010), "\nNO.5 45deg,");
    strcat_s(test010, sizeof(test010), token[2]);
    strcat_s(test010, sizeof(test010), "\nNO.5 90deg,");
    strcat_s(test010, sizeof(test010), token[3]);
    strcat_s(test010, sizeof(test010), "\nNO.5 135deg,");
    strcat_s(test010, sizeof(test010), token[4]);
    strcat_s(test010, sizeof(test010), "\nNO.5 180deg,");
    strcat_s(test010, sizeof(test010), token[5]);
    strcat_s(test010, sizeof(test010), "\nT5YR 0deg,");
    strcat_s(test010, sizeof(test010), token[6]);
    strcat_s(test010, sizeof(test010), "\nT5YR 45deg,");
    strcat_s(test010, sizeof(test010), token[7]);
    strcat_s(test010, sizeof(test010), "\nT5YR 90deg,");
    strcat_s(test010, sizeof(test010), token[8]);
    strcat_s(test010, sizeof(test010), "\nT5YR 135deg,");
    strcat_s(test010, sizeof(test010), token[9]);
    strcat_s(test010, sizeof(test010), "\nT5YR 180deg,");
    strcat_s(test010, sizeof(test010), token[10]);
    strcat_s(test010, sizeof(test010), "\nT5XR 0deg,");
    strcat_s(test010, sizeof(test010), token[11]);
    strcat_s(test010, sizeof(test010), "\nT5XR 45deg,");
    strcat_s(test010, sizeof(test010), token[12]);
    strcat_s(test010, sizeof(test010), "\nT5XR 90deg,");
    strcat_s(test010, sizeof(test010), token[13]);
    strcat_s(test010, sizeof(test010), "\nT5XR 135deg,");
    strcat_s(test010, sizeof(test010), token[14]);
    strcat_s(test010, sizeof(test010), "\nT5XR 180deg,");
    strcat_s(test010, sizeof(test010), token[15]);
    strcat_s(test010, sizeof(test010), "\n\n");

    // TEST@012
    ret |= HwCtrl::m_hVecCnt.VecCmd_Test012(&para);
    // スペース区切りのパラメータを分割
    token[0] = strtok_s(para.test012.para, " ", &context);
    for (i = 1; i < 38; i++)
    {
        token[i] = strtok_s(NULL, " ", &context);
    }
    // パラメータ保存フォーマットへ変更
    sprintf_s(test012, "TEST@012\nT3XR NO.5 -45deg,");
    strcat_s(test012, sizeof(test012), token[0]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.5 0deg,");
    strcat_s(test012, sizeof(test012), token[1]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.5 30deg,");
    strcat_s(test012, sizeof(test012), token[2]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.5 60deg,");
    strcat_s(test012, sizeof(test012), token[3]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.5 90deg,");
    strcat_s(test012, sizeof(test012), token[4]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.5 135deg,");
    strcat_s(test012, sizeof(test012), token[5]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.5 180deg,");
    strcat_s(test012, sizeof(test012), token[6]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.4 0deg,");
    strcat_s(test012, sizeof(test012), token[7]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.4 45deg,");
    strcat_s(test012, sizeof(test012), token[8]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.4 90deg,");
    strcat_s(test012, sizeof(test012), token[9]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.4 135deg,");
    strcat_s(test012, sizeof(test012), token[10]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.4 180deg,");
    strcat_s(test012, sizeof(test012), token[11]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.4 -45deg,");
    strcat_s(test012, sizeof(test012), token[12]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.4 -90deg,");
    strcat_s(test012, sizeof(test012), token[13]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.4 -135deg,");
    strcat_s(test012, sizeof(test012), token[14]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.3 0deg,");
    strcat_s(test012, sizeof(test012), token[15]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.3 30deg,");
    strcat_s(test012, sizeof(test012), token[16]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.3 60deg,");
    strcat_s(test012, sizeof(test012), token[17]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.3 90deg,");
    strcat_s(test012, sizeof(test012), token[18]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.3 120deg,");
    strcat_s(test012, sizeof(test012), token[19]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.3 150deg,");
    strcat_s(test012, sizeof(test012), token[20]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.3 180deg,");
    strcat_s(test012, sizeof(test012), token[21]);
    strcat_s(test012, sizeof(test012), "\nT3XR NO.3 -45deg,");
    strcat_s(test012, sizeof(test012), token[22]);
    strcat_s(test012, sizeof(test012), "\nT3ZR NO.4 0deg,");
    strcat_s(test012, sizeof(test012), token[23]);
    strcat_s(test012, sizeof(test012), "\nT3ZR NO.4 45deg,");
    strcat_s(test012, sizeof(test012), token[24]);
    strcat_s(test012, sizeof(test012), "\nT3ZR NO.4 90deg,");
    strcat_s(test012, sizeof(test012), token[25]);
    strcat_s(test012, sizeof(test012), "\nT3ZR NO.4 135deg,");
    strcat_s(test012, sizeof(test012), token[26]);
    strcat_s(test012, sizeof(test012), "\nT3ZR NO.4 180deg,");
    strcat_s(test012, sizeof(test012), token[27]);
    strcat_s(test012, sizeof(test012), "\nT3ZR NO.4 -45deg,");
    strcat_s(test012, sizeof(test012), token[28]);
    strcat_s(test012, sizeof(test012), "\nT3ZR NO.4 -90deg,");
    strcat_s(test012, sizeof(test012), token[29]);
    strcat_s(test012, sizeof(test012), "\nT3ZR NO.4 -135deg,");
    strcat_s(test012, sizeof(test012), token[30]);
    strcat_s(test012, sizeof(test012), "\nOF4Z NO.5 -45deg,");
    strcat_s(test012, sizeof(test012), token[31]);
    strcat_s(test012, sizeof(test012), "\nOF4Z NO.5 0deg,");
    strcat_s(test012, sizeof(test012), token[32]);
    strcat_s(test012, sizeof(test012), "\nOF4Z NO.5 30deg,");
    strcat_s(test012, sizeof(test012), token[33]);
    strcat_s(test012, sizeof(test012), "\nOF4Z NO.5 60deg,");
    strcat_s(test012, sizeof(test012), token[34]);
    strcat_s(test012, sizeof(test012), "\nOF4Z NO.5 90deg,");
    strcat_s(test012, sizeof(test012), token[35]);
    strcat_s(test012, sizeof(test012), "\nOF4Z NO.5 135deg,");
    strcat_s(test012, sizeof(test012), token[36]);
    strcat_s(test012, sizeof(test012), "\nOF4Z NO.5 180deg,");
    strcat_s(test012, sizeof(test012), token[37]);
    strcat_s(test012, sizeof(test012), "\n\n");

    // TEST@018
    ret |= HwCtrl::m_hVecCnt.VecCmd_Test018(&para);
    // スペース区切りのパラメータを分割
    token[0] = strtok_s(para.test018.para, " ", &context);
    token[1] = strtok_s(NULL, " ", &context);
    token[2] = strtok_s(NULL, " ", &context);
    // パラメータ保存フォーマットへ変更
    sprintf_s(test018, "TEST@018\nARM1 ADJUST,");
    strcat_s(test018, sizeof(test018), token[0]);
    strcat_s(test018, sizeof(test018), "\nARM2 ADJUST,");
    strcat_s(test018, sizeof(test018), token[1]);
    strcat_s(test018, sizeof(test018), "\nARM3 ADJUST,");
    strcat_s(test018, sizeof(test018), token[2]);
    strcat_s(test018, sizeof(test018), "\n\n");

    // DPRDC
    ret |= HwCtrl::m_hVecCnt.VecCmd_Dprdc(&para);
    ret |= HwCtrl::m_hVecCnt.VecCmd_Dprdc2(&para);
    // スペース区切りのパラメータを分割
    token[0] = strtok_s(para.sprdc.para, " ", &context);
    token[1] = strtok_s(NULL, " ", &context);
    token[2] = strtok_s(NULL, " ", &context);
    token[3] = strtok_s(NULL, " ", &context);
    token[4] = strtok_s(NULL, " ", &context);
    token[5] = strtok_s(NULL, " ", &context);
    token[6] = strtok_s(para.sprdc2.para, " ", &context);
    token[7] = strtok_s(NULL, " ", &context);
    token[8] = strtok_s(NULL, " ", &context);
    token[9] = strtok_s(NULL, " ", &context);
    token[10] = strtok_s(NULL, " ", &context);
    token[11] = strtok_s(NULL, " ", &context);
    // パラメータ保存フォーマットへ変更
    sprintf_s(dprdc, "DPRDC\nFLAG,");
    strcat_s(dprdc, sizeof(dprdc), token[0]);
    strcat_s(dprdc, sizeof(dprdc), "\nOFAO1,");
    strcat_s(dprdc, sizeof(dprdc), token[1]);
    strcat_s(dprdc, sizeof(dprdc), "\nOFAO2,");
    strcat_s(dprdc, sizeof(dprdc), token[2]);
    strcat_s(dprdc, sizeof(dprdc), "\nOFAO3,");
    strcat_s(dprdc, sizeof(dprdc), token[3]);
    strcat_s(dprdc, sizeof(dprdc), "\nOFAO4,");
    strcat_s(dprdc, sizeof(dprdc), token[4]);
    strcat_s(dprdc, sizeof(dprdc), "\nOFAO5,");
    strcat_s(dprdc, sizeof(dprdc), token[5]);
    strcat_s(dprdc, sizeof(dprdc), "\nOFAO6,");
    strcat_s(dprdc, sizeof(dprdc), token[7]);
    strcat_s(dprdc, sizeof(dprdc), "\nCALBAO1,");
    strcat_s(dprdc, sizeof(dprdc), token[8]);
    strcat_s(dprdc, sizeof(dprdc), "\nCALBAO2,");
    strcat_s(dprdc, sizeof(dprdc), token[9]);
    strcat_s(dprdc, sizeof(dprdc), "\nCALBAO3,");
    strcat_s(dprdc, sizeof(dprdc), token[8]);
    strcat_s(dprdc, sizeof(dprdc), "\nCALBAO4,");
    strcat_s(dprdc, sizeof(dprdc), token[9]);
    strcat_s(dprdc, sizeof(dprdc), "\nCALBAO5,");
    strcat_s(dprdc, sizeof(dprdc), token[10]);
    strcat_s(dprdc, sizeof(dprdc), "\nCALBAO6,");
    strcat_s(dprdc, sizeof(dprdc), token[11]);
    strcat_s(dprdc, sizeof(dprdc), "\n\n");

    // DPROBE
    // DPROBEの文字は、ファイル保存時に入力する。
    for (i = 0; i < 20; i++)
    {
        ret |= HwCtrl::m_hVecCnt.VecCmd_DprobeV8(&para, i);
        // スペース区切りのパラメータを分割
        token[0] = strtok_s(para.sprobe.para, " ", &context);
        for (j = 1; j < 19; j++)
        {
            token[j] = strtok_s(NULL, " ", &context);
        }
        // パラメータ保存フォーマットへ変更
        sprintf_s(dprobe[i], "ID%d\nAO0,", i);
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[0]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), "\nOFAX,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[1]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), ",OFAY,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[2]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), ",OFAZ,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[3]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), "\nTTAX,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[4]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), ",TTAY,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[5]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), ",TTAZ,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[6]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), "\nOFBX,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[7]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), ",OFBY,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[8]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), ",OFBZ,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[9]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), "\nTTBX,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[10]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), ",TTBY,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[11]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), ",TTBZ,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[12]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), "\nOF0X,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[13]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), ",OF0Y,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[14]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), ",OF0Z,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[15]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), "\nTT0X,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[16]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), ",TT0Y,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[17]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), ",TT0Z,");
        strcat_s(dprobe[i], sizeof(dprobe[i]), token[18]);
        strcat_s(dprobe[i], sizeof(dprobe[i]), "\n");
    }
    // 枝番のパラメータ
    for (i = 17; i < 20; i++)
    {
        for (k = 0; k < 15; k++)
        {
            ret |= HwCtrl::m_hVecCnt.VecCmd_DprobeV8Ma(&para, i, k);
            // スペース区切りのパラメータを分割
            token[0] = strtok_s(para.sprobe.para, " ", &context);
            for (j = 1; j < 19; j++)
            {
                token[j] = strtok_s(NULL, " ", &context);
            }
            // パラメータ保存フォーマットへ変更
            sprintf_s(dprobema[i-17][k], "ID%d-%d\nAO0,", i, k);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[0]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), "\nOFAX,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[1]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), ",OFAY,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[2]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), ",OFAZ,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[3]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), "\nTTAX,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[4]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), ",TTAY,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[5]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), ",TTAZ,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[6]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), "\nOFBX,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[7]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), ",OFBY,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[8]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), ",OFBZ,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[9]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), "\nTTBX,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[10]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), ",TTBY,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[11]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), ",TTBZ,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[12]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), "\nOF0X,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[13]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), ",OF0Y,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[14]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), ",OF0Z,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[15]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), "\nTT0X,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[16]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), ",TT0Y,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[17]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), ",TT0Z,");
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), token[18]);
            strcat_s(dprobema[i-17][k], sizeof(dprobema[i-17][k]), "\n");
        }
    }
    strcat_s(dprobema[2][14], sizeof(dprobema[2][14]), "\n");

    // DLEVEL
    ret |= HwCtrl::m_hVecCnt.VecCmd_Dlevel(para2);
    // パラメータ保存フォーマットへ変更
    sprintf_s(dlevel, "DLEVEL\nSWLV,");
    strcat_s(dlevel, sizeof(dlevel), para2);
    strcat_s(dlevel, sizeof(dlevel), "\n\n");
    memset(para2, 0, sizeof(para2)); // 初期化


    // DCNT
    ret |= HwCtrl::m_hVecCnt.VecCmd_Dcnt(para2);
    // パラメータ保存フォーマットへ変更
    sprintf_s(dcnt, "DCNT\nDIR,");
    strcat_s(dcnt, sizeof(dcnt), para2);
    strcat_s(dcnt, sizeof(dcnt), "\n\n");
    memset(para2, 0, sizeof(para2)); // 初期化

    // DLIM
    // DLIMの文字は、ファイル保存時に入力する。
    for (i = 0; i < 7; i++)
    {
        ret |= HwCtrl::m_hVecCnt.VecCmd_Dlim(para2, i);
        sprintf_s(dlim[i], sizeof(dlim[i]), "No.%d,", i);
        strcat_s(dlim[i], sizeof(dlim[i]), para2);
        strcat_s(dlim[i], sizeof(dlim[i]), "\n");
    }
    strcat_s(dlim[6], sizeof(dlim[6]), "\n");
    memset(para2, 0, sizeof(para2)); // 初期化
    
    // DSERIAL
    ret |= HwCtrl::m_hVecCnt.VecCmd_Dserial(para2);
    sprintf_s(dserial, "DSERIAL\nNo,");
    strcat_s(dserial, sizeof(dserial), para2);
    strcat_s(dserial, sizeof(dcnt), "\n");

    FILE* pf;
    char cPath[256] = { 0 }; // ファイルのパス
    size_t converted = 0;
    errno_t err;
    err = wcstombs_s(&converted, cPath, sizeof(cPath), path, _TRUNCATE); // wcstombs_sを使ってwchar_tからcharへ変換

    if ((fopen_s(&pf, cPath, "w")) == 0)
    {
        // ファイルへ書き込む
        fputs((char*)&(test002), pf);
        fputs((char*)&(test004), pf);
        fputs((char*)&(test006), pf);
        fputs((char*)&(test008), pf);
        fputs((char*)&(test010), pf);
        fputs((char*)&(test012), pf);
        fputs((char*)&(test018), pf);
        fputs((char*)&(dprdc), pf);
        fputs("DPROBE\n", pf);
        for (i = 0; i < 20; i++)
        {
            fputs(dprobe[i], pf);
        }
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 15; j++)
            {
                fputs(dprobema[i][j], pf);
            }
        }
        fputs((char*)&(dlevel), pf);
        fputs((char*)&(dcnt), pf);
        fputs("DLIM\n", pf);
        for (i = 0; i < 7; i++)
        {
            fputs(dlim[i], pf);
        }
        fputs((char*)&(dserial), pf);

        fclose(pf); //ファイルを閉じる
    }
    else
    {
        // ファイルを開くことができなかった
    }
}



/***********************************************************************

    アームパラメータ復元
    2025.10.9yori)

***********************************************************************/
void HwCtrl::RestorePara(const TCHAR* path)
{
    int i = 0;
    size_t len = 0;
    FILE* pf;
    char cPath[256] = { 0 }; // ファイルのパス
    size_t converted = 0;
    errno_t err;
    char line[1024]; // 1行を読み込むバッファ
    char* line2;
    char* para_name = NULL;
    char* para;
    char* token;
    char* context = NULL;
    char para2[64] = { 0 };
    char test002[1024] = { 0 };
    char test002_ab[256] = { 0 };
    char test002_ao[256] = { 0 };
    char test004[1024] = { 0 };
    char test006[1024] = { 0 };
    char test008[512] = { 0 };
    char test010[1024] = { 0 };
    char test012[1024] = { 0 };
    char test018[128] = { 0 };
    char dprdc[512] = { 0 };
    char dprobe[20][512] = { 0 };
    char dprobema[3][15][512] = { 0 };
    char dlevel[64] = { 0 };
    char dcnt[32] = { 0 };
    char dlim[7][256] = { 0 };
    char dserial[32] = { 0 };

    err = wcstombs_s(&converted, cPath, sizeof(cPath), path, _TRUNCATE); // wcstombs_sを使ってwchar_tからcharへ変換

    if ((fopen_s(&pf, cPath, "r")) == 0)
    {
        // TEST@002
        if (fgets(line, sizeof(line), pf) != NULL) // 1行を取得
        {
            if(strstr(line, "TEST@002")!= NULL)
            {
                // ARM1,2,3
                fgets(line, sizeof(line), pf); // 1行を取得
                line[strcspn(line, "\n")] = '\0'; // 改行を削除
                para_name = strtok_s(line, ",", &context);
                while (para_name != NULL)
                {
                    para = strtok_s(NULL, ",", &context);
                    strcat_s(test002, sizeof(test002), para);
                    strcat_s(test002, sizeof(test002), " ");
                    para_name = strtok_s(NULL, ",", &context);
                }
                // AB1,AO1
                fgets(line, sizeof(line), pf); // 1行を取得
                line[strcspn(line, "\n")] = '\0'; // 改行削除
                para_name = strtok_s(line, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ab, sizeof(test002_ab), para);
                strcat_s(test002_ab, sizeof(test002_ab), " ");
                para_name = strtok_s(NULL, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ao, sizeof(test002_ao), para);
                strcat_s(test002_ao, sizeof(test002_ao), " ");
                // AB2,AO2
                fgets(line, sizeof(line), pf); // 1行を取得
                line[strcspn(line, "\n")] = '\0'; // 改行を削除
                para_name = strtok_s(line, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ab, sizeof(test002_ab), para);
                strcat_s(test002_ab, sizeof(test002_ab), " ");
                para_name = strtok_s(NULL, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ao, sizeof(test002_ao), para);
                strcat_s(test002_ao, sizeof(test002_ao), " ");
                // AB3,AO3
                fgets(line, sizeof(line), pf); // 1行を取得
                line[strcspn(line, "\n")] = '\0'; // 改行を削除
                para_name = strtok_s(line, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ab, sizeof(test002_ab), para);
                strcat_s(test002_ab, sizeof(test002_ab), " ");
                para_name = strtok_s(NULL, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ao, sizeof(test002_ao), para);
                strcat_s(test002_ao, sizeof(test002_ao), " ");
                // AB4,AO4
                fgets(line, sizeof(line), pf); // 1行を取得
                line[strcspn(line, "\n")] = '\0'; // 改行を削除
                para_name = strtok_s(line, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ab, sizeof(test002_ab), para);
                strcat_s(test002_ab, sizeof(test002_ab), " ");
                para_name = strtok_s(NULL, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ao, sizeof(test002_ao), para);
                strcat_s(test002_ao, sizeof(test002_ao), " ");
                // AB5,AO5
                fgets(line, sizeof(line), pf); // 1行を取得
                line[strcspn(line, "\n")] = '\0'; // 改行を削除
                para_name = strtok_s(line, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ab, sizeof(test002_ab), para);
                strcat_s(test002_ab, sizeof(test002_ab), " ");
                para_name = strtok_s(NULL, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ao, sizeof(test002_ao), para);
                strcat_s(test002_ao, sizeof(test002_ao), " ");
                // AB6,AO6
                fgets(line, sizeof(line), pf); // 1行取得
                line[strcspn(line, "\n")] = '\0'; // 改行削除
                para_name = strtok_s(line, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ab, sizeof(test002_ab), para);
                strcat_s(test002_ab, sizeof(test002_ab), " ");
                para_name = strtok_s(NULL, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ao, sizeof(test002_ao), para);
                strcat_s(test002_ao, sizeof(test002_ao), " ");
                // AB7,AO7
                fgets(line, sizeof(line), pf); // 1行取得
                line[strcspn(line, "\n")] = '\0'; // 改行削除
                para_name = strtok_s(line, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ab, sizeof(test002_ab), para);
                strcat_s(test002_ab, sizeof(test002_ab), " ");
                para_name = strtok_s(NULL, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ao, sizeof(test002_ao), para);
                strcat_s(test002_ao, sizeof(test002_ao), " ");
                // AB8,AO8
                fgets(line, sizeof(line), pf); // 1行を取得
                line[strcspn(line, "\n")] = '\0'; // 改行を削除
                para_name = strtok_s(line, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ab, sizeof(test002_ab), para);
                para_name = strtok_s(NULL, ",", &context); // カンマまでのパラメータ名を取得
                para = strtok_s(NULL, ",", &context); // カンマまでのパラメータを取得
                strcat_s(test002_ao, sizeof(test002_ao), para);
                //ARM+AB+AO
                strcat_s(test002, sizeof(test002), test002_ab);
                strcat_s(test002, sizeof(test002), " ");
                strcat_s(test002, sizeof(test002), test002_ao);
            }
        }

        fgets(line, sizeof(line), pf); // 改行

        // TEST@004
        if (fgets(line, sizeof(line), pf) != NULL)
        {
            if (strstr(line, "TEST@004") != NULL)
            {
                for (i = 0; i < 10; i++)
                {
                    fgets(line, sizeof(line), pf);
                    line[strcspn(line, "\n")] = '\0'; // 改行を削除
                    para_name = strtok_s(line, ",", &context);
                    while (para_name != NULL)
                    {
                        para = strtok_s(NULL, ",", &context);
                        strcat_s(test004, sizeof(test004), para);
                        strcat_s(test004, sizeof(test004), " ");
                        para_name = strtok_s(NULL, ",", &context);
                    }
                }
                len = strlen(test004); // 文字列の長さを取得
                if (len > 0) test004[len - 1] = '\0'; // 末尾の文字を削除(ヌル文字を末尾に書き込む)
            }
        }

        fclose(pf); //ファイルを閉じる
    }
    else
    {
        // ファイルを開くことができなかった
    }

}