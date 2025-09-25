#pragma once

#include <string> //追加(2025.5.15yori)
#include <list> //追加(2025.5.15yori)
#include <array> //追加(2025.5.15yori)
#include "Windows.h"
#include "../Lib/veccom/veccom.h"
//----------------------------------
// link Library
//----------------------------------
#ifdef _WIN64
#pragma comment(lib, "../Lib/veccom/veccom.lib")
#endif

#include "../Lib/PSControl/TdsData.h"	// 2025.9.3 eba
#pragma comment(lib, "../Lib/PSControl/PSControl.lib")	// 2025.9.3 eba

#include "../Lib/VecCalib/VecCalPolyPgin.h" // 2025.9.3 eba
#pragma comment(lib, "../Lib/VecCalib/VecCalPolyPgin.lib") // 2025.9.3 eba


using namespace std; //using namespace System→using namespace stdへ変更(2025.5.15yori)

///////////////////////////////////////////////////////
// Enum定義
//          2021.3.4 非接触測定スレットシーケンスNoの定義 S.FUKAI
///////////////////////////////////////////////////////

// 2025.9.1 add eba
enum class LANGUAGE
{
	UNKNOWN = 0,
	JAPANESE,
	ENBLISH,
	CHINESE,



	END
};


//-----------------------------------
// Vec間処理のステップ定義(有接触)
//-----------------------------------
//public削除(2025.5.15yori)
/*enum class VEC_STEP {
	UNKNOWN = 0,
	SET_UP,
	INITIALIZE,
	IDLE,
	DATA_REQUEST,
	PAUSE,
	DOWN,
	_END
};*/
enum class VEC_STEP_SEQ {	// 2025.5.23 作成 eba
	UNKNOWN = 0,
	START,
	CONNECT_REQ,
	CONNECT_CMP,
	ARM_WARMUP_REQ, // 追加(2025.7.17yori)
	ARM_WARMUP_ING, // 追加(2025.7.16yori)
	ARM_WARMUP_CMP, // 追加(2025.7.16yori)
	ARM_WARMUP_OFF, // 追加(2025.7.18yori)
	INITIALIZE_REQ,
	INITIALIZE_ING,
	INITIALIZE_CMP,
	INITIALIZE0_REQ, // 追加(2025.6.9yori)
	INITIALIZE0_ING, // 追加(2025.6.9yori)
	INITIALIZE0_CMP, // 追加(2025.6.9yori)
	MODE_SW_REQ, // 追加(2025.8.12yori)
	MODE_SW_ING, // 追加(2025.8.12yori)
	MODE_SW_CMP, // 追加(2025.8.12yori)
	MEAS_IDLE,
	OPEN_MENUDIALOG_REQ, // 追加(2025.7.18yori)
	PROBE_PROPETY_REQ, // 追加(2025.7.18yori)
	DISCONNECT_REQ,
	DISCONNECT_CMP,
	SCANNER_INIT_REQ,
	SCANNER_INIT_ING,
	SCANNER_INIT_CMP,
	SCANNER_CONNECT_BTN_ONOFF, // 追加(2025.9.2yori)
	SCANNER_WARMUP_ING, // 追加(2025.7.29yori)
	SCANNER_WARMUP_CMP, // 追加(2025.8.22yori)
	SCANNER_SCAN_START_REQ,
	SCANNER_SCAN_START_CMP,
	SCANNER_SCAN_MEAS_IDEL,
	SCANNER_SCAN_STOP_REQ,
	SCANNER_SCAN_STOP_CMP,
	SCANNER_DISCONNECT_REQ, // 追加(2025.9.3yori)
	SCANNER_DISCONNECT_CMP, // 追加(2025.9.3yori)
	OPEN_SCANNER_MEAS_DIALOG_REQ, // 追加(2025.9.3yori)
	PROBE_SET_REQ,	// 追加(2025.6.11yori)
	PROBE_SET_ING,	// 追加(2025.6.11yori)
	PROBE_SET_CMP,	// 追加(2025.6.11yori)
	SCANNER_SET_REQ, // 追加(2025.8.10yori)
	SCANNER_SET_ING, // 追加(2025.8.10yori)
	SCANNER_SET_CMP, // 追加(2025.8.10yori)
	//INSPECTION_REQ,	// 追加(2025.6.11yori)
	//INSPECTION_ING,	// 追加(2025.6.11yori)
	//INSPECTION_CMP,	// 追加(2025.6.11yori)
	ALIGNMENT_REQ,	// 追加(2025.6.11yori) 2025.8.27 del eba
	ALIGNMENT_ING,	// 追加(2025.6.11yori) 2025.8.27 del eba
	ALIGNMENT_ING2,	// 結果転送(アームへ)、結果表示(C#へ)シーケンス 2025.9.10 add eba
	ALIGNMENT_CMP,	// 追加(2025.6.11yori) 2025.8.27 del eba
	ARM_SELFCHECK_REQ,	// 追加(2025.6.11yori)
	ARM_SELFCHECK_ING,	// 追加(2025.6.11yori)
	ARM_SELFCHECK_CMP,	// 追加(2025.6.11yori)
	// アーム設定は下記のシーケンスで共通で使用できるよう整理中(2025.9.1yori)
	ARM_SET_REQ,	// 追加(2025.9.1yori)
	ARM_SET_ING,	// 追加(2025.9.1yori)
	SENS_CHECK_REQ,	// 追加(2025.7.2yori)
	SENS_CHECK_ING,	// 追加(2025.7.2yori)
	SENS_CHECK_CMP,	// 追加(2025.7.2yori)
	POINTER_CHECK_REQ,	// 追加(2025.7.3yori)
	POINTER_CHECK_ING,	// 追加(2025.7.3yori)
	POINTER_CHECK_CMP,	// 追加(2025.7.3yori)
	FINISH
};

//-------------------------------------------
// Queの番号(Plugin側と合わせること)
//-------------------------------------------
enum QUE_NUM {
	UNKNOWN_QUE = 0,
	MEASUREMENT_DATA,
	DUMMY_DATA,
	COMMAND,
	SEND_COMMAND,
	NONCONTACT_DATA = 15,
	END_QUE
};

//-------------------------------------------
// 送信コマンド(Plugin側と合わせること)(有接触)
//-------------------------------------------
enum APP_SEND_CMD {
	UNKNOWN_REC_CMD = 0,
	CONNECT_SUCCESS,
	CONNECT_FAILURE,
	DISCONNECT_SUCCESS,
	DISCONNECT_FAILURE,
	MENU_CLOSED,
	SEND_PROBE_PROPETY,
	UNEXPECTED_DISCONNECION,
	ARM_INITIALIZE_ON, //追加(2021.9.21yori)
	ARM_INITIALIZE_OFF, //追加(2021.9.21yori)
	SCANNER_CONNECT, //追加(2021.10.1yori)
	SCANNER_INITIALIZE_SUCCESS, //追加(2021.10.1yori)
	SCANNER_INITIALIZE_FAILURE, //追加(2021.10.1yori)
	CLOSE_SCANNER_MEAS_FORM,	//スキャナ測定ダイアログ表示(2021.11.18yori)
	SCANNER_CONNECT_CANCEL, //追加(2022.2.14yori)
	END_REC_CMD
};

//-----------------------------------
// 非接触測定スレットシーケンス(SEQUENCE)Noの定義
// 2021.3.4  S.FUKAI
// MyForm_ConnectScanner.h→common.hへ移動(2025.5.15yori)
//-----------------------------------
enum NCON_MEAS_SEQ {
	IDEL = 0,					// 0　- TREAD起動
	START,						// 1  - TREAD起動完了
	DUMMY_START,				// 2  - ダミースキャン開始
	DUMMY_MEAS_TOP,				// 3  - ダミースキャン先頭データ取得
	DUMMY_MEAS,					// 4  - ダミースキャン中
	MAIN_START,					// 5  - メイン(サンプリング）スキャン開始
	MAIN_START_TOP,				// 6  - メイン(サンプリング）先頭データ取得
	MAIN_MEAS,					// 7  - メイン(サンプリング）スキャン中
	MAIN_END,					// 7  - メイン(サンプリング）スキャン終了->ダミースキャンへ
	MS_ERROR,					// 8  - error 停止（終了)
	BREAK,						// 9  - 中断
	FINISH						// 10  - スレット終了
};

///////////////////////////////////////////////////////
// 構造体定義
///////////////////////////////////////////////////////
//public ref削除(2025.5.15yori)
//struct ST_SYSTEM {
	//VEC_STEP m_enVecStep; //^削除(2025.5.15yori)
	
	//下記、コメントアウト(2025.5.15yori)
	//ST_SYSTEM() {
	//	m_enVecStep = gcnew VEC_STEP;
	//}
//};

//----------------------------------
//! 
//----------------------------------
//[SerializableAttribute] //コメントアウト(2025.5.15yori)
//public ref削除(2025.5.15yori)
struct ST_PROBE {
	string	m_hName;		//!< 名称 //String^→stringへ変更(2025.5.15yori)
	int		m_iId;			//!< ID
	double	m_dDeg;			//!< 角度
	double  m_dBallRadius;	//!< ボール半径	

	ST_PROBE(){
		m_hName			= ""; //gcnew String()削除(2025.5.15yori)
		m_iId			= 0;
		m_dDeg			= 0.0;
		m_dBallRadius	= 0.0;
	}
};

//----------------------------------
//! 
//----------------------------------
//[SerializableAttribute] //コメントアウト(2025.5.15yori)
//public ref削除(2025.5.15yori)
struct ST_PROBE_LIST {
	list<ST_PROBE> m_hList; //List→listへ変更、^削除(2025.5.15yori)
		
	ST_PROBE_LIST(){
		m_hList = list<ST_PROBE>(); //gcnew List、^削除(2025.5.15yori)
	}
	~ST_PROBE_LIST(){
		//for(int k = 0; m_hList->Count; k++){
		//	m_hList->RemoveAt(k);
		//}
		m_hList.clear(); //上記から変更(2025.5.15yori)
	}
};

//----------------------------------
//! 
//----------------------------------
//[SerializableAttribute] //コメントアウト(2025.5.15yori)
//public ref削除(2025.5.15yori)
struct ST_ARM {
	string m_hName; //String^→stringへ変更(2025.5.15yori)
	string m_hImageFile; //String^→stringへ変更(2025.5.15yori)
	ST_ARM(){
		m_hName		 = ""; //gcnew String()削除(2025.5.15yori)
		m_hImageFile = ""; //gcnew String()削除(2025.5.15yori)
	}
};

//----------------------------------
//! 
//----------------------------------
//[SerializableAttribute] //コメントアウト(2025.5.15yori)
//public ref削除(2025.5.15yori)
struct ST_ARM_LIST {
	list<ST_ARM> m_hList; //List→listへ変更、^削除(2025.5.15yori)
		
	ST_ARM_LIST(){
		m_hList = list<ST_ARM>(); //gcnew List、^削除(2025.5.15yori)
	}
	~ST_ARM_LIST(){
		//for(int k = 0; m_hList->Count; k++){
		//	m_hList->RemoveAt(k);
		//}		
		m_hList.clear(); //上記から変更(2025.5.15yori)	
	}
};

//----------------------------------
//! 
//----------------------------------
//[SerializableAttribute] //コメントアウト(2025.5.15yori)
//public ref削除(2025.5.15yori)
struct ST_STARTUP_ITEM {
	string m_hText; //String^→stringへ変更(2025.5.15yori)
	double	m_dMax_Min;
	double  m_d2Sigma;
	int		m_iJudgement;

	ST_STARTUP_ITEM(){
		m_hText		 = "No Data"; //gcnew String()削除(2025.5.15yori)
		m_dMax_Min	 = 0.0;
		m_d2Sigma	 = 0.0;
		m_iJudgement = 0;
	}
};

//----------------------------------
//! 
//----------------------------------
//[SerializableAttribute] //コメントアウト(2025.5.15yori)
//public ref削除(2025.5.15yori)
struct ST_STARTUP_RESULT {
	array<ST_STARTUP_ITEM, 4>	m_hList;			//!< 各要素のリスト(X,Y,Z,および距離) //array<ST_STARTUP_ITEM^>^からarray<ST_STARTUP_ITEM, 4>へ変更(2025.5.15yori)
	double						m_dPlaneDist;		//!< 面間距離
	double						m_dMasureMargin;	//!< 測定誤差
	int							m_iMarginJudge;		//!< 測定誤差の判定(=0:NG,=1:OK）
		
	//コメントアウト(2025.5.15yori)
	/*
	ST_STARTUP_RESULT(){
		m_hList = gcnew array<ST_STARTUP_ITEM^>(4);
	}
	*/
};

//----------------------------------
//! PolyWorksへデータ送信用
//----------------------------------
//public削除(2025.5.15yori)
struct SEND_PROBE_PROPERTY {
	char cmd_no[1];	//コマンドNo
	int ps_id;		//プローブID
	double dia;		//スタイラス直径
};
