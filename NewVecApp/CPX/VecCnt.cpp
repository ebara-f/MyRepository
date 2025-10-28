// **************************************************
// veccom.dll アクセス関数群
//
// IP関係の設定ファイルはパス指定 InifileFullPath[] 
// Vec_CmdTrans()コマンド転送とVec_CmdReceive()はペアーで使用すること
// また、その間には通信不可です。以下の関数群ではStdRecvCheck()でVec_CmdReceive()を行っている
//
// 2021.3.31
// C++/CLI→C++変換(2025.5.15yori)
// **********************************************
//#include "stdafx.h" //コメントアウト(2025.5.15yori)
//#include <atlstr.h> //マネージ型の変換が面倒だ //コメントアウト(2025.5.15yori)
// CStirng のために定義している最終的には検討が必要

#include "VecCnt.h"

//using namespace System::Threading; //コメントアウト(2024.4.8yori)

// ************************************************************
//  Inifileのパス
// ************************************************************
//char InifileFullPath[] = "C:\\Kosakalab\\VecApp\\Inifiles";
char InifileFullPath[] = "C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles"; //パスの変更(2021.11.9yori)

CVecCnt::CVecCnt()
{
	//m_Lock = gcnew Object;		// 排他処理を行う //コメントアウト(2025.5.15yori)

	////this->削除(2025.5.15yori)
	m_VecHandle = NULL;
	m_iConnectTimeOut = 100;
	m_connectflag = false;				//Vectoronと通信しているかどうか nakayama
	m_VecInitflag = false;				// 2021.3.12 初期化済み    (測定スレット確認のため)
	m_GetdataNo = 0;					// 2021.3.12 Vec_DataRequestEx()のデータ番号の複製 (スキャナーではIndexNo(Tag)の紐づけ用)
	////

	//m_Sts = gcnew ST_VEC_STATUS;					//	ベクトロン状態 //コメントアウト(2025.5.15yori)

	//m_Sts->m_iInitSts = gcnew array<int>(MAX_AXIS); //コメントアウト(2025.5.15yori)
	for (int k = 0; k< MAX_AXIS; k++) {
		m_Sts.m_iInitSts[k] = 0;		//=0:未初期化
	}

	//各変数の初期値セット
	m_Sts.m_enMode   = VEC_MODE::VEC_MODE_UNKNOWN; //->→.へ変更(2025.5.15yori)
	m_Sts.m_iInitFlg = 0; //->→.へ変更(2025.5.15yori)
	m_Sts.m_iProbeId = 0; //->→.へ変更(2025.5.15yori)
	m_Sts.m_dia      = 0; //->→.へ変更(2025.5.15yori)
	m_Sts.m_iBeep    = 0; //->→.へ変更(2025.5.15yori)

	m_Sts.m_Ver      = "";		// バージョン情報 //->→.へ変更、gcnew String()削除(2025.5.15yori)
	m_Sts.m_Area     = "";		// エリアリミット情報  //->→.へ変更、gcnew String()削除(2025.5.15yori)
	memset(m_Sts.m_ArmModel, NULL, sizeof(m_Sts.m_ArmModel)); // 追加(2025.6.16yori)

	// ベクトロン取得データ位置情報
	//m_PosiData = new VecDtEx;			// 1データのみ確保 //使用していないため、コメントアウト(Detected memory leaks!対応)(2022.1.26yorri)

	hIniPath = ""; //gcnew String()削除(2025.5.15yori)
	hSEMA_VECCNT = CreateSemaphore(NULL, 1, 1, SEMAPHORE_NAME2); //追加(2025.5.15yori)
	m_Sts.m_Model = ""; // 追加(2025.6.10) // m_Modelにm_Sts.追加(2025.8.20yori)
	m_Sts.m_INIT0_REQ_Fg = 0; // 追加(2025.6.10) // false→0へ変更、m_Sts追加(2025.8.22yori)
	memset(m_Sts.m_CntVer, NULL, sizeof(m_Sts.m_CntVer)); // 追加(2025.6.16yori)
	memset(m_Sts.m_Tmp, 0, sizeof(m_Sts.m_Tmp)); // 追加(2025.6.18yori)
	memset(m_Sts.m_CalTmp, 0, sizeof(m_Sts.m_CalTmp)); // 追加(2025.6.18yori)
	memset(m_Sts.m_Address, NULL, sizeof(m_Sts.m_Address)); // 追加(2025.6.18yori)
	memset(m_Sts.m_Subnet, NULL, sizeof(m_Sts.m_Subnet)); // 追加(2025.6.18yori)
	memset(m_Sts.m_Port, NULL, sizeof(m_Sts.m_Port)); // 追加(2025.6.18yori)
}

CVecCnt::~CVecCnt()
{
	//delete m_PosiData; //使用していないため、コメントアウト(Detected memory leaks!対応)(2022.1.26yorri)
	//this->!CVecCnt(); //コメントアウト(2025.5.15yori)
	CloseHandle(hSEMA_VECCNT); // 追加(2021.6.11yori)
}
//-------------------------------
//! @fn ファイナライザ
//-------------------------------
////コメントアウト(2025.5.15yori)
/*
CVecCnt::!CVecCnt()
{

}
*/
//

void CVecCnt::VecSetIniPath(char* ptDir)
{
	hIniPath = string(ptDir);  //gcnew String()→stringへ変更(2025.5.15yori)
	
}

// *********************************************************
//  Open 関数 引数の char *dirはIp設定ファイル[veccom.ini]のパスを指定する
//       引数追加は 2018.6.5 (2018.6.5yori)
//  NULLは不可
//  2021.3.31
// ************************************************************
int CVecCnt::VecOpen(int time_out, char* ptDir)
{
	int ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
	m_iConnectTimeOut = time_out; //this->削除(2025.5.15yori)
	VEC_HANDLE temp_vec_handle;
	//まだ接続していなければ接続を開始する
	if (m_connectflag == false) //this->削除(2025.5.15yori)
	{
		/*
		if (ptDir != NULL) hIniPath = gcnew String(ptDir);
		CString strtmp(hIniPath);									//マネージ型の変換が面倒だ
		char* ptChar = (char*)strtmp.GetBuffer(0);
		ret_code = Vec_Open(&temp_vec_handle, time_out, ptChar);
		*/
		ret_code = Vec_Open(&temp_vec_handle, time_out, InifileFullPath); //上記だとveccom.iniファイルが生成されないため、直接パスを入力(2021.11.19yori)

		m_VecHandle = temp_vec_handle; //this->削除(2025.5.15yori)
		//接続が成功したらフラグをtrueにする
		if (ret_code == 0)
		{
			m_connectflag = true; //this->削除(2025.5.15yori)
		}
		else {
			ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;		// エラー
		}
	}
	else
	{	//すでに接続していた場合はOKを返す
		ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
	}

	return(ret_code);
}

int CVecCnt::VecClose()
{
	int ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;
	//接続している場合のみ切断コマンドを送信する
	if (m_connectflag == true) //this->削除(2025.5.15yori)
	{
		if (m_VecHandle != 0) //this->削除(2025.5.15yori)
		{
			ret_code = Vec_Close(m_VecHandle); //this->削除(2025.5.15yori)
			//切断が成功したらフラグをfalseにする
			if (ret_code == 0)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;	
				m_connectflag = false; //this->削除(2025.5.15yori)
			} 
		}
	}
	return(ret_code);
}

void CVecCnt::SetVecStatus(VecSt* get_status)
{
	//各軸の初期化状態の格納 (初期化画面用)
	for (int k = 0; k < MAX_AXIS; k++) {
		int onoff = get_status->init & (0x01 << k);
		onoff = (onoff >> k) & 0x01;

		m_Sts.m_iInitSts[k] = onoff; //->→.変更(2025.5.15yori)
	}
	//初期化完了フラグを格納（中身は0～7bitを使用？）
	m_Sts.m_iInitFlg = get_status->init; //->→.変更(2025.5.15yori)

	// 0軸有無フラグを格納(2025.6.10yori)
	m_Sts.m_No0Fg = (int)(get_status->PsNo0Fg);

	// 2021.3.15 初期化済み検証
	// bit7-リザーブ(7) No6軸(6) No5軸(5) No4軸(4) No3軸(3) No2軸(2) No1軸(1) No7軸(0) 
	// 軸数が7軸以外は処理が必要
	// m_Modelにm_Sts.追加(2025.8.20yori)
	// m_INIT0_REQ_Fgの型をbool→intへ変更、m_Sts(2025.8.22yori)
	if ((m_Sts.m_Model == MODEL_V8M || m_Sts.m_Model == MODEL_V8L || m_Sts.m_Model == MODEL_V8S) && m_Sts.m_No0Fg == 1 && m_Sts.m_INIT0_REQ_Fg == 1) // V8かつNo.0関節のみイニシャライズを行う場合(2025.6.10yori) // V8をS/M/Lに分割(2025.9.29yori)
	{
		if (m_Sts.m_iInitFlg == 127)
		{
			m_VecInitflag = true;
			m_Sts.m_INIT0_REQ_Fg = 0;
		}
		else
		{
			m_VecInitflag = false;
		}
	}
	if ((m_Sts.m_Model == MODEL_V8M || m_Sts.m_Model == MODEL_V8L || m_Sts.m_Model == MODEL_V8S) && m_Sts.m_No0Fg == 1 && m_Sts.m_INIT0_REQ_Fg == 0) // V8かつNo.0-6全部イニシャライズを行う場合　2025.7.2 eba add // V8をS/M/Lに分割(2025.9.29yori)
	{
		if (m_Sts.m_iInitFlg == 0x7F)
		{
			m_VecInitflag = true;
		}
		else
		{
			m_VecInitflag = false;
		}
	}
	else if ((m_Sts.m_Model == MODEL_V8M || m_Sts.m_Model == MODEL_V8L || m_Sts.m_Model == MODEL_V8S) && m_Sts.m_No0Fg == 0 && m_Sts.m_INIT0_REQ_Fg == 0) // V8かつNo.0関節が無い場合(2025.6.10yori) // V8をS/M/Lに分割(2025.9.29yori)
	{
		if (m_Sts.m_iInitFlg == 126) m_VecInitflag = true;
		else                         m_VecInitflag = false;
	}
	else if (m_Sts.m_Model == MODEL_V7S)	// 2025.7.2 eba chg
	{
		if (m_Sts.m_iInitFlg == 127) m_VecInitflag = true; // V7Sは、関節が無いNo.0,4はイニシャライズ完了済みとしている。(2024.6.10yori) //->→.変更(2025.5.15yori)
		else                         m_VecInitflag = false;
	}

	//プローブIDを格納
	m_Sts.m_iProbeId = get_status->ps_id; //->→.変更(2025.5.15yori)
	//スタイラスの直径を格納
	m_Sts.m_dia = get_status->dia; //->→.変更(2025.5.15yori)

	m_Sts.m_GetMode = (VEC_MODE)get_status->mode;	//!< 動作モード(StatusRequestからの取得モード状態) //->→.変更(2025.5.15yori)

}

//----------------------------------------
//! @func ステータス要求
//----------------------------------------
//! @return なし 
//----------------------------------------
int CVecCnt::VecCmd_GetVecStatus()
{
	VecSt	vecStatus;
	int		ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;
	
	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可 //this->削除(2025.5.15yori)
	
	//Monitor::Enter(m_Lock);			//ロック //コメントアウト、下記追加(2025.5.15yori)
	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	// 機種識別追加(2025.6.10)
	// m>Modelにm_Sts.追加(2025.8.20yori)
	if (m_Sts.m_Model == MODEL_V8M || m_Sts.m_Model == MODEL_V8L || m_Sts.m_Model == MODEL_V8S) // V8をS/M/Lに分割(2025.9.29yori)
	{
		ret_code = Vec_StatusRequestV8(m_VecHandle, &vecStatus);
	}
	else
	{
		ret_code = Vec_StatusRequest(m_VecHandle, &vecStatus); //this->削除(2025.5.15yori)
	}

	if(ret_code == (int)VEC_RET_CODE::RET_CODE__OK)
	{
		SetVecStatus(&vecStatus); //this->削除(2025.5.15yori)
	}

	//Monitor::Exit(m_Lock);			//Unlock //コメントアウト、下記追加(2025.5.15yori)
	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

// **************************************************
//  以下の戻り値をいちいち代入していのはデバックのため
// ****************************************************

// ********************************************
// 戻り値チェック関数
//  Vec_CmdReceive()の戻り値自身は通常trueになる、
//  戻りパラメータをチェックする必要あり(ACK)
//  Lock状態で呼び出されます。
// *********************************************
int CVecCnt::StdRecvCheck()
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可

	char  cRecvCmd[32] = { 0 };		// 先頭のみ使用
	char  cRecvData[32] = { 0 };	// この関数群では使用しない
	int   recv_count = 0;			// 戻りパラメータはないため０が返る

	int	  ret_code_recv;

	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, cRecvData, &recv_count); //this->削除(2025.5.15yori)

	if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_recv;
	}
	else {
		if (cRecvCmd[0] == ACK) ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
		else                    ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
	}

	return ret_code;
}
//----------------------------------------
//! @func Vectoron内測定データバッファクリア要求
//----------------------------------------
//! @return int : ※関数の戻り値一覧を参照のこと 
// 2021.3.26 戻り値ではなく cRecvCmdデータ確認する。
//   正常終了は ACK( 0x06 )が返る
//      それ以外は VEC_RET_CODE::RET_CODE__UNKNOWNを取り合えず戻します。
//----------------------------------------
int CVecCnt::VecCmd_ReqVecBClr()
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可

	int   ret_code_send;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可 //this->削除(2025.5.15yori)

	//Monitor::Enter(m_Lock);			//ロック //コメントアウト、下記追加(2025.5.15yori)
	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	ret_code_send = Vec_CmdTrans(m_VecHandle, "BCLR", NULL, 0); //this->削除(2025.5.15yori)
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK) 
		ret_code = ret_code_send;
	else
		ret_code = StdRecvCheck();		// Standerd Recve (Ack Check)

	//Monitor::Exit(m_Lock);			//Unlock //コメントアウト、下記追加(2025.5.15yori)
	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);
	return ret_code;
}

//----------------------------------------
//! @func プローブID変更要求
//----------------------------------------
//! @return int :  
//----------------------------------------
int CVecCnt::VecCmd_ChangeProbe(int probe_id)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可

	char	cSendData[32] = { 0 };
	int		ret_code_send;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可 //this->削除(2025.5.15yori)

	//Monitor::Enter(m_Lock);			//ロック //コメントアウト、下記追加(2025.5.15yori)
	//WaitForSingleObject(hSEMA_VECCNT, INFINITE); 2025.10.1 del eba

	sprintf_s(cSendData, 32, "%d", probe_id);

	ret_code_send = Vec_CmdTrans(m_VecHandle, "CPROBE", cSendData, 1); //this->削除(2025.5.15yori)
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
		ret_code = ret_code_send;
	else
		ret_code = StdRecvCheck();		// Standerd Recve (Ack Check)

	//Monitor::Exit(m_Lock);			//Unlock //コメントアウト、下記追加(2025.5.15yori)
	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL); 2025.10.1 del eba

	return ret_code;
}

//----------------------------------------
//! @func スタイラス直径変更要求
//----------------------------------------
//! @return int :  
//----------------------------------------
int CVecCnt::VecCmd_ChangeDiameter(string dia) //String^→stringへ変更(2025.5.15yori)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可

	char	cSendData[32] = { 0 };
	int		ret_code_send;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可 //this->削除(2025.5.15yori)

	//String --> char* 変換
	//CString strtmp(dia);									//マネージ型の変換が面倒だ //コメントアウト(2025.5.15yori)
	//char* pSendData = (char*)strtmp.GetBuffer(0); //コメントアウト(2025.5.15yori)

	//Monitor::Enter(m_Lock);			//ロック //コメントアウト、下記追加(2025.5.15yori)
	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	strcpy_s(cSendData, 32, dia.c_str()); //pSendData→dia.c_str()へ変更(2025.5.15yori)
	ret_code_send = Vec_CmdTrans(m_VecHandle, "DIA", cSendData, 1); //this->削除(2025.5.15yori)
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
		ret_code = ret_code_send;
	else
		ret_code = StdRecvCheck();		// Standerd Recve (Ack Check)

	//Monitor::Exit(m_Lock);			//Unlock //コメントアウト、下記追加(2025.5.15yori)
	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

//----------------------------------------
//! @func モード変更要求
//----------------------------------------
//! @return int :  
// 2021.3.26 戻り値ではなく cRecvCmdデータ確認する。
//   正常終了は ACK( 0x06 )が返る
//      それ以外は VEC_RET_CODE::RET_CODE__UNKNOWNを取り合えず戻します。
// 要注意：現状に設定されているモードを再切替するおとNAKが返る
//         2021.4.8現状のモード取得がSCANのみとなってしまう
//         NACは無視することにする
//
//----------------------------------------
int CVecCnt::VecCmd_ChangeMode(VEC_MODE req_mode)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可
	char  cSendData[5] = { 0 };
	int   ret_code_send;

	m_Sts.m_enMode = VEC_MODE::VEC_MODE_UNKNOWN;		// modeデータを一旦無効にする //->→.へ変更(2025.5.15yori)

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可 //this->削除(2025.5.15yori)

	//Monitor::Enter(m_Lock);			//ロック //コメントアウト、下記追加(2025.5.15yori)
	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	// 現在のモードを確認する。 うまく読みださない 2021.4.8
	{
		// ret_code_send = VecCmd_GetVecStatus();
		// if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
		// {
		//	ret_code = ret_code_send;
		// 	goto job_exit;
		// }
		// if (m_Sts->m_GetMode == req_mode)	// 同じモードは切換えない
		// {
		//	ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
		//	goto job_exit;
		// }
	}
	// モードを切り返る
	{
		GetVecModeChar(req_mode, cSendData);

		ret_code_send = Vec_CmdTrans(m_VecHandle, "MODE", cSendData, 1); //this->削除(2025.5.15yori)
		if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_send;
		}
		else
		{
			ret_code = StdRecvCheck();		// Standerd Recve (Ack Check)
			// 2021.4.8  戻り値判断無視 if (ret_code == (int)VEC_RET_CODE::RET_CODE__OK)
			ret_code = (int)VEC_RET_CODE::RET_CODE__OK;		// 強制設定
			m_Sts.m_enMode = req_mode;						// mode の記憶 //->→.へ変更(2025.5.15yori)
		}
	}

	// job_exit:
	//Monitor::Exit(m_Lock);			//Unlock //コメントアウト、下記追加(2025.5.15yori)
	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



//----------------------------------------
//! @func 指定したVECのモードから送信するコードを取得
//! @param [in]  req_mode : 指定VECモード(Enum)
//! @param [out] pData : 取得した送信コード
//! @return なし 
//----------------------------------------
void CVecCnt::GetVecModeChar(VEC_MODE req_mode, char* pData)
{
	switch (req_mode) {
	case VEC_MODE::VEC_MODE_PROBE:			pData[0] = '1'; break;//= 1(有接触モード)
	case VEC_MODE::VEC_MODE_LAZER_SCAN:		pData[0] = '2'; break;//= 2(非接触モード)	
	case VEC_MODE::VEC_MODE_INITIALIZE:		pData[0] = '3'; break;//= 3(イニシャライズモード)
	case VEC_MODE::VEC_MODE_TRACE:			pData[0] = '4'; break;//= 4(トレースモード)
	case VEC_MODE::VEC_MODE_ARM_MOUSE:		pData[0] = '5'; break;//= 5(アームマウスモード)
	case VEC_MODE::VEC_MODE_MAINTE:			pData[0] = '6'; break;//= 6(メンテナンス)
	case VEC_MODE::VEC_MODE_ROUCH:			pData[0] = '7'; break;//= 7(ラッチ）
	case VEC_MODE::VEC_MODE_RE_INIT:		pData[0] = '8'; break;//= 8(再9イニシャル）
	default:								pData[0] = '0';	break;//無効なコード
	}
}



//----------------------------------------
//! @func ビープ音変更要求
//----------------------------------------
//! @return int :  
//----------------------------------------
// 2021.3.6 bug修正 S.Fukai
//  "ON" :関節リミット音がon データが取れない
//  "OFF":ビープ音off データが取れる
//  "CAL":        off データが取れる

int CVecCnt::VecCmd_ChangeBeep(char* beep)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可
	char	cSendData[32] = { 0 };
	int		ret_code_send;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可 //this->削除(2025.5.15yori)
																		
	//Monitor::Enter(m_Lock);			//ロック //コメントアウト、下記追加(2025.5.15yori)
	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	strcpy_s(cSendData, 32, beep);
	ret_code_send = Vec_CmdTrans(m_VecHandle, "BEEP", cSendData, 1); //this->削除(2025.5.15yori)
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
		ret_code = ret_code_send;
	else
		ret_code = StdRecvCheck();		// Standerd Recve (Ack Check)

	//Monitor::Exit(m_Lock);			//Unlock //コメントアウト、下記追加(2025.5.15yori)
	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

//----------------------------------------
//! @func VectoronのVerを要求
//----------------------------------------
//! @return int :  
// VERはm_Sts->m_Verに文字列格納
//----------------------------------------
int CVecCnt::VecCmd_GetVecVer()
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可

	char	cRecvCmd[32] = { 0 };
	char	cRecvData[32] = { 0 };
	int		recv_count = 0;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可 //this->削除(2025.5.15yori)

	//Monitor::Enter(m_Lock);			//ロック //コメントアウト、下記追加(2025.5.15yori)
	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	ret_code_send = Vec_CmdTrans(m_VecHandle, "VER", NULL, 0); //this->削除(2025.5.15yori)
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, cRecvData, &recv_count); //this->削除(2025.5.15yori)
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else 
		{
			if (cRecvCmd[0] == ACK && recv_count == 1)
			{
				m_Sts.m_Ver = string(cRecvData); // バージョン情報 //->→.、gcnew String()→stringへ変更(2025.5.15yori)

				// バージョン情報から機種を識別する。(2025.6.10yori)
				// m_Modelにm_Sts.追加(2025.8.20yori) // #defineをアーム型式へ変更(2025.9.26yori)
				if ((m_Sts.m_Ver.substr(0, 2) == "V8") && (m_Sts.m_Ver.substr(13, 1) == "M"))
				{
					m_Sts.m_Model = MODEL_V8M;
				}
				if ((m_Sts.m_Ver.substr(0, 2) == "V8") && (m_Sts.m_Ver.substr(13, 1) == "L"))
				{
					m_Sts.m_Model = MODEL_V8L;
				}
				if ((m_Sts.m_Ver.substr(0, 2) == "V8") && (m_Sts.m_Ver.substr(13, 1) == "S")) // 追加(2025.9.29yori)
				{
					m_Sts.m_Model = MODEL_V8S;
				}
				if ((m_Sts.m_Ver.substr(0, 2) == "V7") && (m_Sts.m_Ver.substr(13, 1) == "S"))
				{
					m_Sts.m_Model = MODEL_V7S;
				}
				if ((m_Sts.m_Ver.substr(0, 2) == "V7") && (m_Sts.m_Ver.substr(13, 2) == "sa"))
				{
					m_Sts.m_Model = MODEL_V7SA;
				}

				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//Monitor::Exit(m_Lock);			//Unlock //コメントアウト、下記追加(2025.5.15yori)
	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

//----------------------------------------
//! @func エリアリミット情報の設定値取得
//----------------------------------------
//! @return int :  
//----------------------------------------
int CVecCnt::VecCmd_GetArea()
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可

	char	cRecvCmd[32] = { 0 };
	char	cRecvData[32] = { 0 };
	int		recv_count = 0;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可 //this->削除(2025.5.15yori)

	//Monitor::Enter(m_Lock);			//ロック //コメントアウト、下記追加(2025.5.15yori)
	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	ret_code_send = Vec_CmdTrans(m_VecHandle, "DAREA", NULL, 0); //this->削除(2025.5.15yori)
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, cRecvData, &recv_count); //this->削除(2025.5.15yori)
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK && recv_count == 1)
			{
				m_Sts.m_Area = string(cRecvData);		// エリア情報  //->→.、gcnew String()→stringへ変更(2025.5.15yori)
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//Monitor::Exit(m_Lock);			//Unlock //コメントアウト、下記追加(2025.5.15yori)
	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

//----------------------------------------
//! @func 測定再開確認
//----------------------------------------
//! @return int : ※関数の戻り値一覧を参照のこと 
//----------------------------------------
int CVecCnt::VecCmd_ReqVecReStart()
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可

	int   ret_code_send;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可 //this->削除(2025.5.15yori)

	//Monitor::Enter(m_Lock);			//ロック //コメントアウト、下記追加(2025.5.15yori)
	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	ret_code_send = Vec_CmdTrans(m_VecHandle, "RESTART", NULL, 0); //this->削除(2025.5.15yori)
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
		ret_code = ret_code_send;
	else
		ret_code = StdRecvCheck();		// Standerd Recve (Ack Check)

	//Monitor::Exit(m_Lock);			//Unlock //コメントアウト、下記追加(2025.5.15yori)
	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

//----------------------------------------
//! @func シーケンス番号のリセット (1にセットする)
//----------------------------------------
//! @return int : ※関数の戻り値一覧を参照のこと 
// 2021.3.26 戻り値ではなく cRecvCmdデータ確認する。
//   正常終了は ACK( 0x06 )が返る
//      それ以外は VEC_RET_CODE::RET_CODE__UNKNOWNを取り合えず戻します。
//----------------------------------------
int CVecCnt::VecCmd_ReqVecSeqReset()
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可

	char  cSendData[32] = { 0 };
	int   ret_code_send;

	
	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可 //this->削除(2025.5.15yori)

	//Monitor::Enter(m_Lock);			//ロック //コメントアウト、下記追加(2025.5.15yori)
	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	// cSendData[0] = '1';			// start data no
	cSendData[0] = '0';			// start data no
	ret_code_send = Vec_CmdTrans(m_VecHandle, "SEQ", cSendData, 1); //this->削除(2025.5.15yori)
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
		ret_code = ret_code_send;
	else
		ret_code = StdRecvCheck();		// Standerd Recve (Ack Check)

	//Monitor::Exit(m_Lock);			//Unlock //コメントアウト、下記追加(2025.5.15yori)
	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

/////////////////////////////////////////////////////////////////
// アーム暖機、温度変化チェック
// 2025.6.4yori
/////////////////////////////////////////////////////////////////
int CVecCnt::VecCmd_Warm()
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT; // 実行不可

	char	cRecvCmd[32] = { 0 };
	char	cRecvData[32] = { 0 };
	int		recv_count = 0;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT; // 実行不可

	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	ret_code_send = Vec_CmdTrans(m_VecHandle, "WARM", NULL, 0);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, cRecvData, &recv_count);
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK && recv_count == 1)
			{
				m_Sts.m_Warm = stoi(string(cRecvData));
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

/////////////////////////////////////////////////////////////////
// アーム内温度取得
// 2025.6.4yori
/////////////////////////////////////////////////////////////////
int CVecCnt::VecCmd_Tmp()
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT; // 実行不可

	char	cRecvCmd[32] = { 0 };
	char	cRecvData[32] = { 0 };
	int		recv_count = 0;
	int		ret_code_send;
	int		ret_code_recv;
	int		i;
	char	no[4];

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT; // 実行不可

	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	for (i = 0; i < 7; i++)
	{
		memset(no, NULL, 4);
		sprintf_s(no, "%d", i);
		ret_code_send = Vec_CmdTrans(m_VecHandle, "TMP", no, 1);
		if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_send;
		}
		else
		{
			ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, cRecvData, &recv_count);
			if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
			{
				ret_code = ret_code_recv;
			}
			else
			{
				if (cRecvCmd[0] == ACK && recv_count == 1)
				{
					m_Sts.m_Tmp[i] = stod(string(cRecvData));
					ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
				}
				else
				{
					ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
				}
			}
		}
	}

	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

/////////////////////////////////////////////////////////////////
// カウンタバージョン取得
// 2025.6.17yori
/////////////////////////////////////////////////////////////////
int CVecCnt::VecCmd_GetCntVer()
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT; // 実行不可

	char	cRecvCmd[32] = { 0 };
	char	cRecvData[32] = { 0 };
	int		recv_count = 0;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT; // 実行不可

	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	ret_code_send = Vec_CmdTrans(m_VecHandle, "CNTVER", NULL, 0);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, cRecvData, &recv_count);
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK && recv_count == 9)
			{
				strcpy_s(m_Sts.m_CntVer, sizeof(m_Sts.m_CntVer), cRecvData);

				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

/////////////////////////////////////////////////////////////////
// キャリブ時の温度取得
// 2025.6.18yori
/////////////////////////////////////////////////////////////////
int CVecCnt::VecCmd_GetCalTmp()
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT; // 実行不可

	char	cRecvCmd[32] = { 0 };
	char	cRecvData[32] = { 0 };
	int		recv_count = 0;
	int		ret_code_send;
	int		ret_code_recv;
	int		i;
	char	no[4];

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT; // 実行不可

	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	for (i = 0; i < 7; i++)
	{
		memset(no, NULL, 4);
		sprintf_s(no, "%d", i);
		ret_code_send = Vec_CmdTrans(m_VecHandle, "DCTMP", no, 1);
		if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_send;
		}
		else
		{
			ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, cRecvData, &recv_count);
			if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
			{
				ret_code = ret_code_recv;
			}
			else
			{
				if (cRecvCmd[0] == ACK && recv_count == 1)
				{
					m_Sts.m_CalTmp[i] = stod(string(cRecvData));
					ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
				}
				else
				{
					ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
				}
			}
		}
	}

	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

/////////////////////////////////////////////////////////////////
// ネットワーク設定取得
// 2025.6.18yori
/////////////////////////////////////////////////////////////////
int CVecCnt::VecCmd_GetNetwork()
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT; // 実行不可

	char	cRecvCmd[32] = { 0 };
	char	cRecvData[32] = { 0 };
	int		recv_count = 0;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT; // 実行不可

	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	// IPアドレス取得
	ret_code_send = Vec_CmdTrans(m_VecHandle, "DIP", NULL, 0);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
		ReleaseSemaphore(hSEMA_VECCNT, 1, NULL); // 追加(2025.8.19yori)
		return ret_code; // 追加(2025.8.16yori)
	}
	else
	{
		ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, cRecvData, &recv_count);
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
			ReleaseSemaphore(hSEMA_VECCNT, 1, NULL); // 追加(2025.8.19yori)
			return ret_code; // 追加(2025.8.16yori)
		}
		else
		{
			if (cRecvCmd[0] == ACK && recv_count == 4)
			{
				strcpy_s(m_Sts.m_Address, sizeof(m_Sts.m_Address), cRecvData);
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
				ReleaseSemaphore(hSEMA_VECCNT, 1, NULL); // 追加(2025.8.19yori)
				return ret_code; // 追加(2025.8.16yori)
			}
		}
	}

	// サブネットマスク取得
	ret_code_send = Vec_CmdTrans(m_VecHandle, "DSNET", NULL, 0);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
		ReleaseSemaphore(hSEMA_VECCNT, 1, NULL); // 追加(2025.8.19yori)
		return ret_code; // 追加(2025.8.16yori)
	}
	else
	{
		ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, cRecvData, &recv_count);
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
			ReleaseSemaphore(hSEMA_VECCNT, 1, NULL); // 追加(2025.8.19yori)
			return ret_code; // 追加(2025.8.16yori)
		}
		else
		{
			if (cRecvCmd[0] == ACK && recv_count == 4)
			{
				strcpy_s(m_Sts.m_Subnet, sizeof(m_Sts.m_Subnet), cRecvData);
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
				ReleaseSemaphore(hSEMA_VECCNT, 1, NULL); // 追加(2025.8.19yori)
				return ret_code; // 追加(2025.8.16yori)
			}
		}
	}

	// ポート番号取得
	ret_code_send = Vec_CmdTrans(m_VecHandle, "DPORT", NULL, 0);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
		ReleaseSemaphore(hSEMA_VECCNT, 1, NULL); // 追加(2025.8.19yori)
		return ret_code; // 追加(2025.8.16yori)
	}
	else
	{
		ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, cRecvData, &recv_count);
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
			ReleaseSemaphore(hSEMA_VECCNT, 1, NULL); // 追加(2025.8.19yori)
			return ret_code; // 追加(2025.8.16yori)
		}
		else
		{
			if (cRecvCmd[0] == ACK && recv_count == 1)
			{
				strcpy_s(m_Sts.m_Port, sizeof(m_Sts.m_Subnet), cRecvData);
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
				ReleaseSemaphore(hSEMA_VECCNT, 1, NULL); // 追加(2025.8.19yori)
				return ret_code; // 追加(2025.8.16yori)
			}
		}
	}

	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL); 

	return ret_code;
}

/////////////////////////////////////////////////////////////////
// Vec 測定データ取得
//    hStDataEx->m_iSize = 1 固定、取得データは１個のみ 2021.3.5 現在
//    戻り値処理注意
//    ・非接触ではスキャナーとデータが同期されるため、データが無い時には VEC_OK(0)以外が返される
//    ・接触式では、data_noに取得データ数を確認　-1　（トリガーSWによるデータが無い）
//      しかし、現在の座標点が取得される。（リアルタイム表示用）  
//
// ijk[2] *= -1;  Z軸データのみ極性変更必要 (スキャナーのヘッドが点方向になってしまう）
// 　スキャンデータへは引き渡し構造体が違うため、最終的には変換が必要
//
//  バッファサイズは読み出しのデータポイント数　スキャナーでは1とすること
////////////////////////////////////////////////////////////////
int CVecCnt::VecFunc_DataRequestEx(VecDtEx* PosiData,int iDataSize)
{
	// VecDtEx* m_PosiData;						// ベクトロン取得データ位置情報

	int data_no = 0;
	int ret;
	// 間違い int isize = sizeof(VecDtEx);

	// 機種識別追加(2025.6.16)
	// m_Modelにm_Sts.追加(2025.8.20yori)
	if (m_Sts.m_Model == MODEL_V8M || m_Sts.m_Model == MODEL_V8L || m_Sts.m_Model == MODEL_V8S) // V8をS/M/Lに分割(2025.9.29yori)
	{
		ret = Vec_DataRequestV8(m_VecHandle, iDataSize, PosiData, &data_no);
	}
	else
	{
		ret = Vec_DataRequestEx(m_VecHandle, iDataSize, PosiData, &data_no);
	}

	//	PosiData->ijk[2] *= -1;				// 大元のソースはijk[2]の極性を変更していたが 
	//PosiData->ijk[0] *= -1;				//  [0] Xの極性変更が正解と思われる 2021.4.20 →極性変更不要(2021.5.21yori)
	m_GetdataNo = data_no;					// 2021.3.5 Vec_DataRequestEx()の有接点動作用 //this->削除(2025.5.15yori)

	return(ret);
}

/////////////////////////////////////////////////////////////////
// 測定データとカウント値の取得
// 2025.6.18yori
/////////////////////////////////////////////////////////////////
int CVecCnt::VecFunc_CntRequestEx(VecCtEx2* CntData, int iDataSize)
{

	int data_no = 0;
	int ret;

	// 機種識別追加(2025.6.16)
	// m_Modelにm_Sts.追加(2025.8.20yori)
	if (m_Sts.m_Model == MODEL_V8M || m_Sts.m_Model == MODEL_V8L || m_Sts.m_Model == MODEL_V8S) // V8をS/M/Lに分割(2025.9.29yori)
	{
		ret = Vec_CntRequestV8(m_VecHandle, iDataSize, CntData, &data_no);
	}
	else
	{
		ret = Vec_CntRequestEx(m_VecHandle, iDataSize, CntData, &data_no);
	}

	m_GetdataNo = data_no;

	return(ret);
}

/////////////////////////////////////////////////////////////////
// プローブ情報設定
// 2025.7.17yori
/////////////////////////////////////////////////////////////////
int CVecCnt::VecFunc_SetProbeSettingIni(VecProbeSettingIni ProbeSetting[20])
{
	int ret;

	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	ret = Vec_SetProbeSettingIni(m_VecHandle, ProbeSetting);

	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret;
}

/////////////////////////////////////////////////////////////////
// プローブ情報取得
// 2025.7.17yori
/////////////////////////////////////////////////////////////////
int CVecCnt::VecFunc_GetProbeSettingIni(VecProbeSettingIni ProbeSetting[20])
{
	int ret;

	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	ret = Vec_GetProbeSettingIni(m_VecHandle, ProbeSetting);

	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);


	return ret;
}

/////////////////////////////////////////////////////////////////
// アーム内スキャナパラメータ設定
// 2021.8.25yori
/////////////////////////////////////////////////////////////////
int CVecCnt::VecSetScannerPara(double ofbx, double ofby, double ofbz, double ttbx, double ttby, double ttbz)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT; // 実行不可

	int   ret_code_send;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;// 実行不可 //this->削除(2025.5.15yori)

	//Monitor::Enter(m_Lock); // ロック //コメントアウト、下記追加(2025.5.15yori)
	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	ret_code_send = Vec_SetPulsProbe(m_VecHandle, ofbx, ofby, ofbz, ttbx, ttby, ttbz); //this->削除(2025.5.15yori)
	ret_code = ret_code_send;

	//Monitor::Exit(m_Lock); // Unlock //コメントアウト、下記追加(2025.5.15yori)
	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

/////////////////////////////////////////////////////////////////
// アーム内スキャナパラメータ取得
// 2021.8.25yori
/////////////////////////////////////////////////////////////////
int CVecCnt::VecGetScannerPara(double *ofbx, double *ofby, double *ofbz, double *ttbx, double *ttby, double *ttbz)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT; // 実行不可

	int   ret_code_send;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;// 実行不可 //this->削除(2025.5.15yori)

	//Monitor::Enter(m_Lock); // ロック //コメントアウト、下記追加(2025.5.15yori)
	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	ret_code_send = Vec_GetPulsProbe(m_VecHandle, ofbx, ofby, ofbz, ttbx, ttby, ttbz); //this->削除(2025.5.15yori)
	ret_code = ret_code_send;

	//Monitor::Exit(m_Lock); // Unlock //コメントアウト、下記追加(2025.5.15yori)
	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}

/////////////////////////////////////////////////////////////////
// 有接触測定音のON、OFF切換設定(トリガー音のON/OFF)
// 2021.9.30yori
/////////////////////////////////////////////////////////////////
int CVecCnt::VecCmd_ChangeBeepMeas(char* beep)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可
	char	cSendData[32] = { 0 };
	int		ret_code_send;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可 //this->削除(2025.5.15yori)

	//Monitor::Enter(m_Lock);			//ロック //コメントアウト、下記追加(2025.5.15yori)
	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	strcpy_s(cSendData, 32, beep);
	ret_code_send = Vec_CmdTrans(m_VecHandle, "BEPTRG", cSendData, 1); //this->削除(2025.5.15yori)
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
		ret_code = ret_code_send;
	else
		ret_code = StdRecvCheck();		// Standerd Recve (Ack Check)

	//Monitor::Exit(m_Lock);			//Unlock //コメントアウト、下記追加(2025.5.15yori)
	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}


/////////////////////////////////////////////////////////////////
// アームのネットワーク設定変更
// 2025.8.16yori
/////////////////////////////////////////////////////////////////
int CVecCnt::VecCmd_ChangeNetwork(char* adress, char* subnet, char* port)
{
	int		ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可
	char	cSendData[32] = { 0 };
	int		ret_code_send;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;	//実行不可

	WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	// IPアドレス
	strcpy_s(cSendData, 32, adress);
	ret_code_send = Vec_CmdTrans(m_VecHandle, "SIP", cSendData, 4);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
		return ret_code;
	}
	else
	{
		ret_code = StdRecvCheck();
		if (ret_code != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			return ret_code;
		}
	}

	// サブネットマスク
	strcpy_s(cSendData, 32, subnet);
	ret_code_send = Vec_CmdTrans(m_VecHandle, "SSNET", cSendData, 4);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
		return ret_code;
	}
	else
	{
		ret_code = StdRecvCheck();
		if (ret_code != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			return ret_code;
		}
	}

	// ポート
	strcpy_s(cSendData, 32, port);
	ret_code_send = Vec_CmdTrans(m_VecHandle, "SPORT", cSendData, 1);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
		return ret_code;
	}
	else
	{
		ret_code = StdRecvCheck();
		if (ret_code != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			return ret_code;
		}
	}

	ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	TEST@002
	2025.9.12 add eba

***********************************************************************/
int CVecCnt::VecCmd_Test002(CALIB_DATA* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	sprintf_s(para->test002.cmd, sizeof(para->test002.cmd), "%s", "TEST@002B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test002.cmd, NULL, 0);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para->test002.para, &para->test002.no);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}


/***********************************************************************

	TEST@004
	2025.9.12 add eba

***********************************************************************/
int CVecCnt::VecCmd_Test004(CALIB_DATA* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	sprintf_s(para->test004.cmd, sizeof(para->test004.cmd), "%s", "TEST@004B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test004.cmd, NULL, 0);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para->test004.para, &para->test004.no);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}


/***********************************************************************

	TEST@006
	2025.9.12 add eba

***********************************************************************/
int CVecCnt::VecCmd_Test006(CALIB_DATA* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	sprintf_s(para->test006.cmd, sizeof(para->test006.cmd), "%s", "TEST@006B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test006.cmd, NULL, 0);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para->test006.para, &para->test006.no);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{	
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}


/***********************************************************************

	TEST@008
	2025.9.12 add eba

***********************************************************************/
int CVecCnt::VecCmd_Test008(CALIB_DATA* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	sprintf_s(para->test008.cmd, sizeof(para->test008.cmd), "%s", "TEST@008B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test008.cmd, NULL, 0);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para->test008.para, &para->test008.no);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	TEST@010
	2025.10.6yori

***********************************************************************/
int CVecCnt::VecCmd_Test010(CALIB_DATA* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	sprintf_s(para->test010.cmd, sizeof(para->test010.cmd), "%s", "TEST@010B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test010.cmd, NULL, 0);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para->test010.para, &para->test010.no);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	TEST@012
	2025.10.6yori

***********************************************************************/
int CVecCnt::VecCmd_Test012(CALIB_DATA* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	sprintf_s(para->test012.cmd, sizeof(para->test012.cmd), "%s", "TEST@012B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test012.cmd, NULL, 0);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para->test012.para, &para->test012.no);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	TEST@018
	2025.10.6yori

***********************************************************************/
int CVecCnt::VecCmd_Test018(CALIB_DATA* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	sprintf_s(para->test018.cmd, sizeof(para->test018.cmd), "%s", "TEST@018B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test018.cmd, NULL, 0);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para->test018.para, &para->test018.no);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	DPRDC
	2025.10.6yori

***********************************************************************/
int CVecCnt::VecCmd_Dprdc(CALIB_DATA* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	sprintf_s(para->sprdc.cmd, sizeof(para->sprdc.cmd), "%s", "DPRDC");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->sprdc.cmd, NULL, 0);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para->sprdc.para, &para->sprdc.no);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	DPRDC2
	2025.10.6yori

***********************************************************************/
int CVecCnt::VecCmd_Dprdc2(CALIB_DATA* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	sprintf_s(para->sprdc2.cmd, sizeof(para->sprdc2.cmd), "%s", "DPRDC2");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->sprdc2.cmd, NULL, 0);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para->sprdc2.para, &para->sprdc2.no);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	DPROBEV8
	2025.9.12 add eba

***********************************************************************/
int CVecCnt::VecCmd_DprobeV8(CALIB_DATA* para, int psid)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	sprintf_s(para->sprobe.cmd, sizeof(para->sprobe.cmd), "%s", "DPROBEV8");
	sprintf_s(para->sprobe.para, sizeof(para->sprobe.para), "%d", psid);
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->sprobe.cmd, para->sprobe.para, 1);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para->sprobe.para, &para->sprobe.no);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	DPROBEV8MA
	2025.10.6yori

***********************************************************************/
int CVecCnt::VecCmd_DprobeV8Ma(CALIB_DATA* para, int psid, int branch)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	char	cbranch[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	sprintf_s(para->sprobe.cmd, sizeof(para->sprobe.cmd), "%s", "DPROBEV8MA");
	sprintf_s(para->sprobe.para, sizeof(para->sprobe.para), "%d", psid);
	sprintf_s(cbranch, sizeof(cbranch), " %d", branch);
	strcat_s(para->sprobe.para, sizeof(para->sprobe.para), cbranch);
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->sprobe.cmd, para->sprobe.para, 2);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para->sprobe.para, &para->sprobe.no);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	DLEVEL
	2025.10.7yori

***********************************************************************/
int CVecCnt::VecCmd_Dlevel(char* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		recv_count = 0;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	ret_code_send = Vec_CmdTrans(m_VecHandle, "DLEVEL", NULL, 0);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para, &recv_count);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	DCNT
	2025.10.7yori

***********************************************************************/
int CVecCnt::VecCmd_Dcnt(char* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		recv_count = 0;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	ret_code_send = Vec_CmdTrans(m_VecHandle, "DCNT", NULL, 0);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para, &recv_count);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	DLIM
	2025.10.7yori

***********************************************************************/
int CVecCnt::VecCmd_Dlim(char* para, int no)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	char	cSendData[32] = { 0 };
	int		recv_count = 0;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo
	sprintf_s(cSendData, sizeof(cSendData), "%d", no);
	ret_code_send = Vec_CmdTrans(m_VecHandle, "DLIM", cSendData, 1);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para, &recv_count);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	DSERIAL
	2025.10.7yori

***********************************************************************/
int CVecCnt::VecCmd_Dserial(char* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		recv_count = 0;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);	// veccom.dll内で排他処理してるので不要ではないか？2025.9.12 eba memo

	ret_code_send = Vec_CmdTrans(m_VecHandle, "DSERIAL", NULL, 0);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para, &recv_count);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	TEST@003B
	2025.9.12 add eba

***********************************************************************/
int CVecCnt::VecCmd_Test003(CALIB_DATA* para)
{
	int		ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(para->test002.cmd, sizeof(para->test002.cmd), "%s", "TEST@003B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test002.cmd, para->test002.para, para->test002.no);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	TEST@005B
	2025.9.12 add eba

***********************************************************************/
int CVecCnt::VecCmd_Test005(CALIB_DATA* para)
{
	int		ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(para->test004.cmd, sizeof(para->test004.cmd), "%s", "TEST@005B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test004.cmd, para->test004.para, para->test004.no);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}


/***********************************************************************

	TEST@007B
	2025.9.12 add eba

***********************************************************************/
int CVecCnt::VecCmd_Test007(CALIB_DATA* para)
{
	int		ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(para->test006.cmd, sizeof(para->test006.cmd), "%s", "TEST@007B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test006.cmd, para->test006.para, para->test006.no);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}


/***********************************************************************

	TEST@009B
	2025.9.12 add eba

***********************************************************************/
int CVecCnt::VecCmd_Test009(CALIB_DATA* para)
{
	int		ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(para->test008.cmd, sizeof(para->test008.cmd), "%s", "TEST@009B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test008.cmd, para->test008.para, para->test008.no);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	TEST@011B
	2025.10.16yori

***********************************************************************/
int CVecCnt::VecCmd_Test011(CALIB_DATA* para)
{
	int		ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(para->test010.cmd, sizeof(para->test010.cmd), "%s", "TEST@011B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test010.cmd, para->test010.para, para->test010.no);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	TEST@013B
	2025.10.16yori

***********************************************************************/
int CVecCnt::VecCmd_Test013(CALIB_DATA* para)
{
	int		ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(para->test012.cmd, sizeof(para->test012.cmd), "%s", "TEST@013B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test012.cmd, para->test012.para, para->test012.no);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	TEST@019B
	2025.10.16yori

***********************************************************************/
int CVecCnt::VecCmd_Test019(CALIB_DATA* para)
{
	int		ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(para->test018.cmd, sizeof(para->test018.cmd), "%s", "TEST@019B");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->test018.cmd, para->test018.para, para->test018.no);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	SPRDC
	2025.10.17yori

***********************************************************************/
int CVecCnt::VecCmd_Sprdc(CALIB_DATA* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cSendData[64] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(cSendData, sizeof(cSendData), "%s", para->sprdc.para);
	ret_code_send = Vec_CmdTrans(m_VecHandle, "SPRDC", cSendData, para->sprdc.no);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	SPRDC2
	2025.10.17yori

***********************************************************************/
int CVecCnt::VecCmd_Sprdc2(CALIB_DATA* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cSendData[64] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(cSendData, sizeof(cSendData), "%s", para->sprdc2.para);
	ret_code_send = Vec_CmdTrans(m_VecHandle, "SPRDC2", cSendData, para->sprdc2.no);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	SPROBEV8
	2025.9.12 add eba

***********************************************************************/
int CVecCnt::VecCmd_SprobeV8(CALIB_DATA* para, int psid)
{
	int		ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(para->sprobe.cmd, sizeof(para->sprobe.cmd), "%s", "SPROBEV8");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->sprobe.cmd, para->sprobe.para, para->sprobe.no);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}


/***********************************************************************

	SPROBE
	2025.10.22 add eba
	V7用プローブ定数設定コマンド
***********************************************************************/
int CVecCnt::VecCmd_Sprobe(int psid)
{
	int		ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;
	int		ret_code_send;
	int		ret_code_recv;
	char	cmd[16];
	char	para[256];

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(cmd, sizeof(cmd), "%s", "SPROBE");
	
	if (psid < 0 || 19 < psid)
	{
		return (int)VEC_RET_CODE::RET_CODE__ARGMENT_ERROR;
	}
	sprintf_s(cmd, sizeof(cmd), "%d", psid);
	
	ret_code_send = Vec_CmdTrans(m_VecHandle, cmd, para, 1);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	SPROBEV8MA
	2025.10.20yori

***********************************************************************/
int CVecCnt::VecCmd_SprobeV8Ma(CALIB_DATA* para, int psid, int branch)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cPsId[8] = { 0 };
	char	cBranch[8] = { 0 };
	char	cSendData[sizeof(cPsId) + sizeof(cBranch) + sizeof(para->sprobe.para)];
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(para->sprobe.cmd, sizeof(para->sprobe.cmd), "%s", "SPROBEV8MA");
	sprintf_s(cPsId, sizeof(cPsId), "%d", psid);
	sprintf_s(cBranch, sizeof(cBranch), " %d ", branch);
	sprintf_s(cSendData, sizeof(cSendData), " %s", cPsId);
	strcat_s(cSendData, sizeof(cSendData), cBranch);
	strcat_s(cSendData, sizeof(cSendData), para->sprobe.para);
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->sprobe.cmd, cSendData, para->sprobe.no);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	SLEVEL
	2025.10.17yori

***********************************************************************/
int CVecCnt::VecCmd_Slevel(char* para, int psid)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cSendData[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(cSendData, sizeof(cSendData), "%d ", psid);
	strcat_s(cSendData, sizeof(cSendData), para);
	ret_code_send = Vec_CmdTrans(m_VecHandle, "SLEVEL", cSendData, 2);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	MCNT
	2025.10.17yori

***********************************************************************/
int CVecCnt::VecCmd_Mcnt(char* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cSendData[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(cSendData, sizeof(cSendData), "%s", para);
	ret_code_send = Vec_CmdTrans(m_VecHandle, "MCNT", cSendData, 9);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	SLIM
	2025.10.14yori

***********************************************************************/
int CVecCnt::VecCmd_Slim(char* para, int no)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cSendData[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(cSendData, sizeof(cSendData), "%d ", no);
	strcat_s(cSendData, sizeof(cSendData), para);
	ret_code_send = Vec_CmdTrans(m_VecHandle, "SLIM", cSendData, 3);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	SSERIAL
	2025.10.14yori

***********************************************************************/
int CVecCnt::VecCmd_Sserial(char* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cSendData[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(cSendData, sizeof(cSendData), "%s", para);
	ret_code_send = Vec_CmdTrans(m_VecHandle, "SSERIAL", cSendData, 1);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}



/***********************************************************************

	TEST@ISO
	2025.9.12 add eba

***********************************************************************/
int CVecCnt::VecCmd_Iso(void)
{
	int		ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	ret_code_send = Vec_CmdTrans(m_VecHandle, "TEST@ISO", NULL, 0);
	ret_code_recv = StdRecvCheck();
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		ret_code = ret_code_recv;
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}


/***********************************************************************

	PC
	2025.10.127add eba

***********************************************************************/
int CVecCnt::VecCmd_Pc(CALIB_PAPA* para)
{
	int	  ret_code = (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	char	cRecvCmd[32] = { 0 };
	int		ret_code_send;
	int		ret_code_recv;

	if (m_VecHandle == NULL) return (int)VEC_RET_CODE::RET_CODE__DO_NOT;

	//WaitForSingleObject(hSEMA_VECCNT, INFINITE);

	sprintf_s(para->cmd, sizeof(para->cmd), "%s", "PC");
	ret_code_send = Vec_CmdTrans(m_VecHandle, para->cmd, para->para, 9);
	ret_code_recv = Vec_CmdReceive(m_VecHandle, cRecvCmd, para->para_in, &para->no);
	if (ret_code_send != (int)VEC_RET_CODE::RET_CODE__OK)
	{
		ret_code = ret_code_send;
	}
	else
	{
		if (ret_code_recv != (int)VEC_RET_CODE::RET_CODE__OK)
		{
			ret_code = ret_code_recv;
		}
		else
		{
			if (cRecvCmd[0] == ACK)
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__OK;
			}
			else
			{
				ret_code = (int)VEC_RET_CODE::RET_CODE__UNKNOWN;
			}
		}
	}

	//ReleaseSemaphore(hSEMA_VECCNT, 1, NULL);

	return ret_code;
}
