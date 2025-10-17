// *****************************************************
// 
//
//  C++/CLI→C++変換(2025.5.15yori)
//*******************************************************
#pragma once

#include "Windows.h"

#include "common.h"
#include "CPX.h"	// 2025.9.12 add eba

//#include "../Lib/veccom/veccom.h"
#include <string> //追加(2025.5.15yori)
#include <array> //追加(2025.5.15yori)

//----------------------------------
// link Library
//----------------------------------
//#ifdef _WIN64
//#pragma comment(lib, "../Lib/veccom/veccom.lib")
//#endif

// ************************************************************
//  Inifileのパス
// ************************************************************
extern char InifileFullPath[];

#define SEMAPHORE_NAME2 L"VECCNT"					//セマフォの名前 VecCntのみ使用(2025.5.15yori)

using namespace std; //using namespace System→using namespace stdへ変更(2025.5.15yori)

#define MODEL_V8M	"VAR800M" // 追加(2025.6.10yori) // アーム型式へ変更(2025.9.26yori)
#define MODEL_V8L	"VAR800L" // 追加(2025.6.10yori) // アーム型式へ変更(2025.9.26yori)
#define MODEL_V8S	"VAR800S" // 追加(2025.9.29yori)
#define MODEL_V7S	"BK100S" // 追加(2025.6.10yori) // アーム型式へ変更(2025.9.26yori)
#define MODEL_V7SA	"BK100S-NC" // 追加 2025.7.2 eba add 仮これじゃダメ！ // アーム型式へ変更(2025.9.26yori)

// 定数定義
///////////////////////////////////////////////////////
// 軸数は7固定、ショートも7軸として処理が可能 (不要軸は初期化済みとして動作する)
const int MAX_AXIS = 7;

///////////////////////////////////////////////////////
// Enum定義
///////////////////////////////////////////////////////
//--------------------------------------
//VECCOMからの戻り値
// 関数によりこの戻り値ではないものがある
//--------------------------------------
//public、class削除(2025.5.15yori)
enum VEC_RET_CODE {
    RET_CODE__OK = VEC_OK,			//=0
    RET_CODE__STOP_WAIT = VEC_ER_STOP_WAT,	//=1
    RET_CODE__STOP_RESET = VEC_ER_STOP_RST,	//=2
    RET_CODE__STOP_BUFFER = VEC_ER_STOP_BUF,	//=3
    RET_CODE__STOP_OTHER = VEC_ER_STOP_OTR,	//=4
    RET_CODE__OPEN = VEC_ER_OPEN,		//=5
    RET_CODE__CLOSE = VEC_ER_CLSE,		//=6
    RET_CODE__TMOT = VEC_ER_TMOT,		//=7
    //(以下はVecCntオリジナル)
    RET_CODE__DO_NOT = -1,				//!< 実行不可
    RET_CODE__ARGMENT_ERROR = -2,				//!< 引数異常
    RET_CODE__UNKNOWN = -9				//!< 不明なエラー
};
//--------------------------------------
// Vectoronへの要求モード REQ_MODE -> VEC_MODE
//--------------------------------------
// public enum class REQ_MODE {
//public、class削除(2025.5.15yori)
enum VEC_MODE {
    VEC_MODE_PROBE = 1,	//!< 有接触モード
    VEC_MODE_LAZER_SCAN = 2,	//!< 非接触モード
    VEC_MODE_INITIALIZE = 3,	//!< イニシャライズモード
    VEC_MODE_TRACE = 4,	//!< トレースモード
    VEC_MODE_ARM_MOUSE = 5,	//!< アームマウスモード
    VEC_MODE_MAINTE = 6,	//!< メンテナンスモード
    VEC_MODE_ROUCH = 7,	//!< ラッチモード 
    VEC_MODE_RE_INIT = 8,	//!< 再イニシャライズモード
    VEC_MODE_UNKNOWN			// 初期状態
};

//public ref削除(2025.5.15yori)
struct ST_VEC_STATUS {

	VEC_MODE	m_enMode;	//!< 動作モード
	int			m_iInitFlg;	//!< イニシャライズ終了フラグ
	array<int, MAX_AXIS> m_iInitSts;	//!< 各軸のイニシャライズ状態 //array<int>^からarray<int, MAX_AXIS>へ変更(2025.5.15yori)
	int			m_iProbeId;	//!< プローブID
	double		m_dia;		//!< ポールプローブの直径
	int			m_iBeep;	//!< ビープ音のON/OFF(=0:OFF, =1:ON)
	int			m_iErrCode;
	string     m_Ver;		// ﾊﾞｰｼﾞｮﾝ情報 //String^→stringへ変更(2025.5.15yori)
	string     m_Area;		// エリアリミット情報 //String^→stringへ変更(2025.5.15yori)
	int  	   m_Warm;		// アーム内温度変化チェック(2025.6.4yori)
	double     m_Tmp[7];	// アーム内温度(2025.6.4yori)
	double     m_CalTmp[7];	// キャリブ温度(2025.6.4yori)
	int		   m_No0Fg;		// 0軸有無(2025.6.9yori)
	int		   m_INIT0_REQ_Fg;	// 0軸イニシャライズ要求フラグ(2025.6.10yori) // CVecCntのpublicから移動、bool→intへ変更(値が保持されないため)(2025.8.22yori)
	string     m_Model;	// 機種識別(2025.6.10yori) // CVecCntのpublicから移動(文字が保持されないため)、CPU基板のバージョン情報から取得するアーム型式(2025.8.20yori)
	char	   m_ArmModel[16];	// アーム型式(2025.6.16yori) // veccal.iniから取得するアーム型式(2025.8.20yori) // wchar_t→charへ変更(2025.8.30)
	char	   m_CntVer[32]; // カウンタバージョン(2025.6.16yori)
	char	   m_Address[32]; // IPアドレス(2025.6.18yori)
	char	   m_Subnet[32]; // サブネットマスク(2025.6.18yori)
	char	   m_Port[4]; // ポート番号(2025.6.18yori)

	VEC_MODE	m_GetMode;	//!< 動作モード(StatusRequestからの取得モード状態)
};

//public ref削除(2025.5.15yori)
class CVecCnt
{
protected:
	//Object^ m_Lock;						// 排他処理 従来の慣例よりMonitorクラスを使用する //Object^ m_Lock;コメントアウト(2025.5.15yori)
											// 現在競合の可能性は有接触でのサンプリング
											// 工夫次第では不要となる 2021.3.31現在は元のソフトを利用するため
											// 必ず処理を行う (MyForm.cppのバックグランドスレットでべクロトン情報を取得している)
											//  だだし、Open/Closeは例外であるためスレットが停止している状態で呼び出すこと
	HANDLE hSEMA_VECCNT;					//セマフォのハンドル(2025.5.15yori)
public:
	VEC_HANDLE	m_VecHandle;
	int			m_iConnectTimeOut;
	bool		m_connectflag;					//Vectoronと通信しているかどうか nakayama
	bool        m_VecInitflag;					//2021.3.12 初期化済み    (測定スレット確認のため)
	int         m_GetdataNo;					//2021.3.12 Vec_DataRequestEx()のデータ番号の複製 (スキャナーではIndexNo(Tag)の紐づけ用)
	const DWORD CHATTRING_INVALIDTIME = 300;	//2021.3.12 SW応答規制時間 標準 300ms
	ST_VEC_STATUS m_Sts;						// ベクトロン状態 //protectedへ移動(2025.5.15yori)
	VecProbeSettingIni* m_ProbeSetting;			// プローブ情報(2025.7.17yori)

protected:
	string hIniPath;						//String^→stringへ変更(2025.5.15yori)
	// char csIniPath[256];					// iniファイルパス default: C:\Kosakalab\VecApp\Inifiles   [veccom.ini]
	//ST_VEC_STATUS m_Sts;					// ベクトロン状態 //^削除、publicへ移動(2025.5.15yori)
	//VecDtEx* m_PosiData;					// ベクトロン取得データ位置情報 TdsData.hに同じ定義 noの型式のみ違う //使用していないため、コメントアウト(Detected memory leaks!対応)(2022.1.26yori)
			
public:
	CVecCnt();
	~CVecCnt();
	//!CVecCnt(); //コメントアウト(2025.5.15yori)

public:
	void VecSetIniPath(char* ptDir);
	int VecOpen(int time_out, char* ptDir);		// time_out defualt 100 [veccom.ini]のパス
	int VecClose();
	void SetVecStatus(VecSt* get_status);
	int VecCmd_GetVecStatus();
	int StdRecvCheck();
	// 以下 veccomm.dll 直接呼び出す関数 Lockつき
	int VecCmd_ReqVecBClr();
	int VecCmd_ChangeProbe(int probe_id);
	int VecCmd_ChangeDiameter(string dia); //String^→stringへ変更(2025.5.15yori)
	int VecCmd_ChangeMode(VEC_MODE req_mode);
	int VecCmd_ChangeBeep(char* beep);
	int VecCmd_ChangeBeepMeas(char* beep); //追加(2021.9.30yori)
	int VecCmd_ChangeNetwork(char* adress, char* subnet, char* port); //追加(2025.8.16yori)
	int VecCmd_GetVecVer();
	int VecCmd_GetArea();
	int VecCmd_ReqVecReStart();
	int VecCmd_ReqVecSeqReset();
	int VecCmd_Warm(); // 追加(2025.6.4yori)
	int VecCmd_Tmp(); // 追加(2025.6.4yori)
	int VecCmd_GetCntVer(); // 追加(2025.6.17yori)
	int VecCmd_GetCalTmp(); // 追加(2025.6.18yori)
	int VecCmd_GetNetwork(); // 追加(2025.6.18yori)
	
	int VecCmd_Test002(CALIB_DATA* para);	// 2025.9.12 add eba
	int VecCmd_Test004(CALIB_DATA* para);	// 2025.9.12 add eba
	int VecCmd_Test006(CALIB_DATA* para);	// 2025.9.12 add eba
	int VecCmd_Test008(CALIB_DATA* para);	// 2025.9.12 add eba
	int VecCmd_Test010(CALIB_DATA* para);	// 2025.10.6yori
	int VecCmd_Test012(CALIB_DATA* para);	// 2025.10.6yori
	int VecCmd_Test018(CALIB_DATA* para);	// 2025.10.6yori
	int VecCmd_Dprdc(CALIB_DATA* para);		// 2025.10.6yori
	int VecCmd_Dprdc2(CALIB_DATA* para);		// 2025.10.6yori
	int VecCmd_DprobeV8(CALIB_DATA* para, int psid);	// 2025.9.12 add eba
	int VecCmd_DprobeV8Ma(CALIB_DATA* para, int psid, int branch); // 2025.10.6yori
	int VecCmd_Dlevel(char* para); // 2025.10.7yori
	int VecCmd_Dcnt(char* para); // 2025.10.7yori
	int VecCmd_Dlim(char* para, int no); // 2025.10.7yori
	int VecCmd_Dserial(char* para); // 2025.10.7yori
	int VecCmd_Test003(CALIB_DATA* para);	// 2025.9.12 add eba
	int VecCmd_Test005(CALIB_DATA* para);	// 2025.9.12 add eba
	int VecCmd_Test007(CALIB_DATA* para);	// 2025.9.12 add eba
	int VecCmd_Test009(CALIB_DATA* para);	// 2025.9.12 add eba
	int VecCmd_SprobeV8(CALIB_DATA* para, int psid);	// 2025.9.12 add eba
	int VecCmd_SprobeV8Ma(CALIB_DATA* para, int psid, int branch); // 2025.10.10yori
	int VecCmd_Iso(void);	// 2025.9.12 add eba
	int VecCmd_Pc(CALIB_PAPA* para);	// 2025.10.17 add eba

	int VecFunc_DataRequestEx(VecDtEx* PosiData, int iDataSize);
	int VecFunc_CntRequestEx(VecCtEx2* CntData, int iDataSize); // 追加(2025.6.18yori)
	int VecFunc_SetProbeSettingIni(VecProbeSettingIni ProbeSetting[]); // 追加(2025.7.17yori)
	int VecFunc_GetProbeSettingIni(VecProbeSettingIni ProbeSetting[]); // 追加(2025.7.17yori)

	int VecSetScannerPara(double ofbx, double ofby, double ofbz, double ttbx, double ttby, double ttbz); // 追加(2021.8.25yori)
	int VecGetScannerPara(double *ofbx, double *ofby, double *ofbz, double *ttbx, double *ttby, double *ttbz); // 追加(2021.8.25yori)

	// 状態取得
	VEC_MODE VecSts_GetMode() { return m_Sts.m_enMode; }; //->→.へ変更(2025.5.15yori)
	int VecSts_GetProbeId() { return m_Sts.m_iProbeId; };		//!< プローブID //->→.へ変更(2025.5.15yori)
	double VecSts_GetProbeDia() { return m_Sts.m_dia; };		//!< ポールプローブの直径 //->→.へ変更(2025.5.15yori)
	array<int, MAX_AXIS> VecSts_InitSts() { return m_Sts.m_iInitSts; }; //array<int>^→array<int, MAX_AXIS>、//->→.へ変更(2025.5.15yori)
protected:
	void GetVecModeChar(VEC_MODE req_mode, char* pData);
};
