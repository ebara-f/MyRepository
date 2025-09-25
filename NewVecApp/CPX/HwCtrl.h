/***********************************************************************

    コマンド群を束ねるクラス

***********************************************************************/

#pragma once

#include    <string>
#include    "common.h"
#include    "CPX.h"
//// 追加(2025.5.15yori)
#include "../Lib/LplQue/LplQue.h" 
#pragma comment(lib, "../Lib/LplQue/LplQue.lib")
//#include "../Lib/PSControl/TdsData.h" // ->2025.9.3 commonへ移動 eba
//#pragma comment(lib, "../Lib/PSControl/PSControl.lib")    // ->2025.9.3 commonへ移動 eba
// PSControl.dllとTdsLibrary.dllはリリース版を配置すること
// デバッグ版を配置すると、「このアプリケーションのサイド バイ サイド構成が正しくないため、アプリケーションを開始できませんでした。」
#include "SharedMemory.h"
////
//#include "../Lib/VecCalib/VecCalPolyPgin.h" // 追加(2025.7.31yori) ->2025.9.3 commonへ移動 eba
//#pragma comment(lib, "../Lib/VecCalib/VecCalib.lib") // 追加(2025.7.31yori) ->2025.9.3 commonへ移動 eba
#include "VecCnt.h"

#define SEMAPHORE_VEC_STEP_SEQ_NAME	L"SEMAPHORE_VEC_STEP_SEQ"	// 2025.5.27 add eba

class HwCtrl
{
public:
    static int  Func01(); // 変更(2025.5.15yori)
    static int  Func02( int, double, const TCHAR* );
    static int  Func03( int, double, const TCHAR*, int*, double*, TCHAR*&, int );
    //// 追加(2025.5.15yori)
    static int  Func04();
    static int  Func05( VecDtEx* );
    static int  Func06( VEC_MODE* );
    static int  Func07();
    static int  Func08();
    static int  Func09();
    static int  Func10();
    static int  Func11(VecDtEx vecdata);
    static int  Func12();
    static int  Func13();
    static int  Func14();
    static int  Func15();
    static int  Func16();
    static int  Func17();
    static void  Func18();
    //static void  Func19(); // コメントアウト(2025.5.15yori)
    static void  Func20();
    static void  Func21();
    static int Func22(); // 追加(2025.6.4yori)
    static int Func23(double* pA, TCHAR*& pB, int B_count);
    static int Func24(); // 追加(2025.6.4yori)
    static int Func25(); // 追加(2025.6.9yori)
    static int Func26(); // 追加(2025.6.12yori)
    static int Func27(); // 追加(2025.6.17yori)
    static int Func28( VecCtEx2*); // 追加(2025.6.18yori)
    static int Func29(); // 追加(2025.6.18yori)
    static int Func30(); // 追加(2025.6.18yori)
    static int Func31(char adress[4][8], char subnet[4][8], char port[4]); // 追加(2025.6.18yori) // 引数追加(2025.8.15yori)
    static BOOL Func32(); // 追加(2025.6.19yori)
    static void Func33(char adress[4][8], char subnet[4][8], char gateway[4][8], char dns[4][8]); // 追加(2025.6.19yori) // 引数を2次元配列へ変更(2025.8.17yori)
    static int Func34(); // 追加(2025.6.20yori)
    static void Func35(int[5], char[5][50]); // 追加(2025.6.23yori)
    static BOOL Func36(); // 追加(2025.6.20yori)
    static BOOL Func37(unsigned short val[5]); // 追加(2025.6.20yori)
    static BOOL Func38(unsigned short val[5]); // 追加(2025.6.20yori)
    static void Func39(int*); // 追加(2025.6.23yori)
    static void Func40(int*); // 追加(2025.6.23yori)
    static void Func41(double*); // 追加(2025.6.23yori)
    static void Func42(int*); // 追加(2025.6.23yori)
    static void Func43(int*, int*); // 追加(2025.6.23yori)
    static void Func44(int*); // 追加(2025.6.24yori)
    static void Func45(); // 追加(2025.6.24yori)
    static void Func46(); // 追加(2025.6.24yori)
    static void Func47(); // 追加(2025.6.25yori)
    static BOOL Func48(int); // 追加(2025.7.2yori)
    static BOOL Func49(); // 追加(2025.7.2yori)
    static int  Func50(int id, double dia); // 追加(2025.7.18yori) // 引数追加(2025.9.8yori)
    static int  Func51(); // 追加(2025.7.18yori)
    static void Func52(wchar_t probe_name[21][32], wchar_t stylus_angle[21][32]); // 追加(2025.7.22yori) // 引数追加(2025.8.28yori)
    static BOOL Func53(BOOL*); // 追加(2025.7.29yori)
    static int  Func54(CALIB_JUDGE_CK* th, CALIB_JUDGE th2[20], CALIB_GAUGE* gauge, int id); // 追加(2025.8.1yori)  // 引数追加(2025.9.22yori)
    static int  Func55(CALIB_JUDGE_CK* th, CALIB_JUDGE th2[20], int id); // 追加(2025.8.1yori) // 引数追加(2025.9.22yori)
    static BOOL  Func56(VecGaugeIni* ga1, SensorSettingIni* ga2, double* scanchkball); // 追加(2025.8.7yori) // 非接触球のみの点検しきい値追加(2025.8.10yori)
    static void Func57(int gagetype); // 追加(2025.8.5yori)
    static void Func58(double scanchkball); // 追加(2025.8.10yori)
    static void Func59(wchar_t mode[6][32]); // 追加(2025.8.10yori)
    static void  Func60(); // 追加(2025.8.12yori)
    static BOOL Func61(int scanmode); // 追加(2025.8.5yori)
    static BOOL Func62(int sens); // 追加(2025.8.21yori)
    static BOOL Func63(int power); // 追加(2025.8.21yori)
    static BOOL Func64(int pitch); // 追加(2025.8.21yori)
    static BOOL Func65(); // 追加(2025.8.23yori)
    static BOOL Func66(); // 追加(2025.8.24yori)
    static BOOL Func67(); // 追加(2025.8.24yori)
    static BOOL Func68(); // 追加(2025.8.24yori)
    static BOOL Func69(int twopeak); // 追加(2025.8.25yori)
    static BOOL Func70(); // 追加(2025.8.25yori)
    static BOOL Func71(); // 追加(2025.8.27yori)
    static BOOL Func72(int edge_default[3][6], int serch_mask_default[3][6]); // 追加(2025.8.27yori)
    static int Func73(); // 追加(2025.8.28yori)
    static int Func74(const TCHAR* armmodel); // 追加(2025.8.31yori)
    static int Func75(); // 追加(2025.9.1yori)
    static BOOL Func76(); // 追加(2025.9.3yori)
    static CVecCnt m_hVecCnt;

    static int pbid_chg_old_fg; // プローブID の変更があったことを知らせる一つ前のフラグ(2025.9.8yori)

    static bool	m_b_Button_ConnectFlag;	// 有接触接続ボタン判定フラグ(2025.6.10yori)
    static bool	m_ArmWarmUpMonitorFlag; // 有接触暖機監視フラグ(2025.7.18yori)
    static bool	m_ScannerWarmUpMonitorFlag; // 非接触暖機監視フラグ(2025.7.30yori)
    static bool	m_ScannerWarmUpMonitorCancelFlag; // 非接触暖機監視キャンセルフラグ(2025.8.22yori)
    static bool m_ScannerConnectBtnFg; // スキャナ暖機完了ボタンフラグ(2025.9.2yori)

    static HANDLE m_hGetScanDataThread;
    static void GetScanDataThread_new(); // スキャンデータ取得レッド
    static bool m_bGetThreadStopFlag; // スキャンデータ取得スレッド停止フラグ

    static HANDLE hSEMA; // セマフォのハンドル(共有メモリアクセス時のスレッド間バッティング防止用)    // ほんに全部セマフォ取る必要ある？？ 2025.5.28 memo eba
    static HANDLE hSEMA_VSEQ; // アームの動作シーケンス制御用 2025.5.27 add eba

    static int AppCommandRecv(char* RBuf);    // 2025.5.28 add eba
    static int AppCommandSend(APP_SEND_CMD cmd);
    static int SendPolyworksMessage(int TID, int Leng, char SBuf[]);

    static int iScannerConnect; //スキャナ接続有無
    static Status* ptstatus; // データの状態
    static OneLineData2* ptlinedata2025; // ラインデータの格納先 // ptlinedata2→ptlinedata2025へ変更(2025.5.15yori)
    static int m_iXSize; // スキャン幅 スレット起動時にセットされる
    static double m_dXPitch; // ピッチ
    static bool m_bmeasfg;
    static NCON_MEAS_SEQ  m_ScanDataStepCounter;    // 測定サンプリングスレッドのシーケンスカウンタ
    static DWORD m_StepStartTime;                   // ステップ開始時間
    static bool m_bSwSts;                           // スイッチ状態
    static bool m_bOldSwSts;                        // 前回のスイッチ状態
    static DWORD m_SwTime;                          // 検出時間
    static DWORD m_OldSwTime;                       // 前回の検出時間
    static int m_LineNo;                            // 取得ライン番号
    static int m_iSn;                               // スキャナNo等 0でのみ使用
    static int m_iSw;
    static int m_ScanShotNo;                        // ショットNo
    static bool m_bReadThreadStopFlag;		        //読出しスレッド停止フラグ
    static bool EndFg;
    static const double INVALID_CHECK;              // 無効値判断値 (無効値は999999.0 floatデータのため
    static unsigned short m_BrightSlice[5];         // 輝度スライス(2025.8.25yori)
    static unsigned short m_SensSlice[5];           // 感度スライス(2025.8.25yori)
    static double m_Angle;                          // 角度マスク(2025.8.25yori)
    static int m_Edge;                              // エッジマスク(2025.8.25yori)
    static DWORD m_Address;                         // スキャナのIPアドレス(2025.6.18yori)
    static DWORD m_Subnet;                          // スキャナのサブネットマスク(2025.6.18yori)
    static DWORD m_Gateway;                         // スキャナのデフォルトゲートウェイ(2025.6.18yori)
    static DWORD m_DNS;                             // スキャナのDNSサーバー(2025.6.18yori)
    static PulsZMask* m_ptZMask;                    // 距離マスク(2025.6.20yori)
    static SelfChkLatchResult* m_ptLatchResult;     // ラッチ通信チェック(2025.6.24yori)
    static SelfChkMotorResult* m_ptMotorResult;     // モーターチェック(2025.6.24yori)
    static SelfChkSensResult* m_ptSensResult;       // 感度チェック(2025.7.2yori)
    static bool m_PointerCheckFg;                   // ポインタ位置チェックフラグ(2025.7.3yori)
    static double m_PointerCheckScanData;           // ポインタ位置チェック用データ(2025.7.3yori)
    static int m_PointerCheckLineNo;                // ポインタ位置チェック用ライン数(2025.7.4yori)

    static int GetVecDataEx(VecDtEx* PosiData);
    static int GetMeasTopData();
    static int DataSamplingandTransfer(bool transFg, int* pErrorCode);
    static int OneDataSamplingandTransfer(bool transFg, int* pErrorCode);
    //static bool GetandStoreScannerLineData(const VecRet* pVecData, bool tranceFg); // コメントアウト(2025.5.15yori)
    static bool GetandSendScannerLineData(const VecRet* pVecData, bool tranceFg);
    static void ConvertVecTranceData(const VecDtEx* pGetData, VecRet* pVecData); // 構造体の内容がことなるため変換が必要
    static void SetTds1stPosition(const VecDtEx* pGetData);
    static int TriggerButtonAndMeasDataStatusTransfer(bool buttonfg, bool measdatafg);
    static void Memory_ResetCounter();
    //static bool SendOneLineData(); // コメントアウト(2025.5.15yori)
    static int SendLineDataCheck2(int index);
    static void FileOutput(); // Debug用、スキャンデータファイル出力(2025.8.5yori)

    // 非接触点検、キャリブ用関数
    static void CalibCheckAndCalcu(CalibResult* ptCalibResultt, ChkScnResult* ptChkResult);
    static void MaxCalcu43(double data[4][3], int index, double* max);
    static void MinCalcu43(double data[4][3], int index, double* min); 
    static void MaxCalcu4(double data[4], double* max);
    static void MinCalcu4(double data[4], double* min);
    //


    // 有接触点検、キャリブ用関数
    static int GetArmParaV8(CALIB_DATA* para, int psid); 
    static int SetArmParaV8(CALIB_DATA* para, int psid);
    //
    
     
    // シーケンス制御関数
    static VEC_STEP_SEQ m_VecStepSeq;    // 2025.5.27 add eba
};
