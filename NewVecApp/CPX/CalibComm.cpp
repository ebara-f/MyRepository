/***********************************************************************

	点検、キャリブパネルを処理するGrop02の子グループ

***********************************************************************/
#include	"CalibComm.h"
#include	"CalibUserMulti.h"
#include	"CalibInspectMultiNestStd.h"
#include	"CalibInspectMultiPlateStd.h"
#include	"CalibProbeBallStd.h"
#include	"CalibProbeBallExt.h"
#include	"CalibScannerMakeMatrix.h" // 追加(2025.12.4yori)
#include	"CalibScannerFull.h" // 追加(2025.12.5yori)

CALIB_TYPE		CalibComm::m_CalibType;
LANGUAGE		CalibComm::m_Language;
CalibDataBuff	CalibComm::m_pData;
CALIB_DATA		CalibComm::m_ArmParaTxt;

/***********************************************************************

	パネル初期化時
	に呼ぶ関数

***********************************************************************/

int CalibComm::Init(CALIB_MSEBOX* para, TCHAR*& path, int p_count, TCHAR*& mes, int m_count)
{
	int ret = 0;
	int lang = 0;
	int calmode = 0;

	CalibComm::m_Language = (LANGUAGE)para->Language;

	// DLLの初期化
	ret = CalibSetPath("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles");

	CalibComm::m_CalibType = (CALIB_TYPE)para->CalibType;
	switch (CalibComm::m_CalibType)
	{
		case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:
			ret |= CalibInspectMultiNestStd::InitSub(para);
			break;

		case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
			ret |= CalibUserMulti::InitSub(para);
			break;

		case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_STD:
			ret |= CalibProbeBallStd::InitSub(para);
			break;

		case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_EXT:
			ret |= CalibProbeBallExt::InitSub(para);
			break;

		default:
			break;
	}

	// ゲージ設定の取得
	ret |= CalibGetGaugeVal(&para->GaugePara);


	return (ret);
}


/***********************************************************************

	開始ボタンがクリックされたときに
	に呼ぶ関数

***********************************************************************/
int CalibComm::Start(CALIB_MSEBOX* para)
{
	int ret = 0;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];


	// 測定データをバッファに入力可能にする
	if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::MEAS_IDLE)
	{
		HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ALIGNMENT_REQ;
		while (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::ALIGNMENT_REQ)
		{
			Sleep(100);
			if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::ALIGNMENT_ING)
			{
				break;
			}
		}
	}

	// 判定フラグの初期化
	para->CalibInspectJudge = 0;
	para->CalibResultJudge = 0;
	// ゲージの値設定
	CalibSetGaugeVal(para->GaugePara);

	// しきい値の取得
	ret |= !CalibGetThreshold(&para->ProbeCheckThreshold, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId);
	ret |= !CalibGetThresholdCk(&para->InspectionThreshold);

	// V7は確認してはならない
	//if (HwCtrl::m_hVecCnt.m_Sts.m_iProbeId != para->CalibProbeId)
	//{
	//	goto exit;
	//}


	HwCtrl::Func09();	// ステータス要求(現在のプローブIDが知りたい)
	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:
		ret |= CalibInspectMultiNestStd::StartSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
		ret |= CalibUserMulti::StartSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_STD:
		ret |= CalibProbeBallStd::StartSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_EXT:
		ret |= CalibProbeBallExt::StartSub(para);
		break;

	default:
		break;
	}

	if (ret != 0)
	{
		goto exit;
	}

	// データ初期化
	CalibMesReset();
	CalibMesOutPath(path);
	CalibMesOutMesg(mesg1, mesg2);
	sprintf_s(mesg, 512, "%s\n%s", mesg1, mesg2);

	MultiByteToWideChar(CP_ACP, 0, path, -1, para->path, 128);
	MultiByteToWideChar(CP_ACP, 0, mesg, -1, para->mes, 256);

exit:;
	return (ret);
}


/***********************************************************************

	戻るボタンがクリックされたときに
	に呼ぶ関数

***********************************************************************/
int CalibComm::Back(CALIB_MSEBOX* para)
{
	int ret = 0;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];

	CalibMesBack();

	CalibMesOutPath(path);
	CalibMesOutMesg(mesg1, mesg2);
	sprintf_s(mesg, 512, "%s\n%s", mesg1, mesg2);
	MultiByteToWideChar(CP_ACP, 0, path, -1, para->path, 128);
	MultiByteToWideChar(CP_ACP, 0, mesg, -1, para->mes, 256);

	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:	

		break;

	case CALIB_TYPE::INSPECT_MULTI_GAUGE_PLATE_STD:

		break;

	case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:

		break;

	case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_STD:

		break;

	case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_EXT:

		break;
	default:
		break;
	}



	return (ret);
}


/***********************************************************************

	中止ボタンがクリックされたときに
	に呼ぶ関数

***********************************************************************/
int CalibComm::ReStart(CALIB_MSEBOX* para)
{
	int ret = 0;
	char path[256];

	ret |= CalibEnd();

	CalibComm::m_CalibType = (CALIB_TYPE)para->CalibType;
	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:
		ret |= CalibInspectMultiNestStd::InitSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
		ret |= CalibUserMulti::InitSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_STD:
		ret |= CalibProbeBallStd::InitSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_EXT:
		ret |= CalibProbeBallExt::InitSub(para);
		break;

	default:
		break;
	}

	ret |= CalibGetGaugeVal(&para->GaugePara);


	return (ret);
}


/***********************************************************************

	中止ボタンがクリックされたときに
	に呼ぶ関数

***********************************************************************/
int CalibComm::Close(CALIB_MSEBOX* para)
{
	int ret = 0;

	ret |= CalibEnd();
	// 通常シーケンスにもどす
	HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
	while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::MEAS_IDLE)
	{
		Sleep(100);
	}
	////

	return (ret);
}



/***********************************************************************

	描画したい画像のパスを出力
	に呼ぶ関数

***********************************************************************/
int CalibComm::GetDrawPath(TCHAR*& path, int count)
{
	int ret = 0;

	




	return (ret);
}



/***********************************************************************

	表示したいメッセージの文字列を出力
	に呼ぶ関数

***********************************************************************/
int CalibComm::GetMesString(TCHAR*& mes, int count)
{
	int ret = 0;






	return (ret);
}



/***********************************************************************

	カウントデータがあればバッファに格納し1を返す
	に呼ぶ関数

***********************************************************************/
int CalibComm::CntDataInputThread(void)
{
	int ret = 0;
	int i = 0;

	VecCtEx2 CntData;
	ret = HwCtrl::Func28(&CntData); // 2025.9.2 add eba 

	if (ret == 0)
	{
		if ((CntData.button & 0x01) && (ret == VEC_OK))
		{
			CalibComm::m_pData.PutData(CntData);
			ret = 1;
		}
	}
	else
	{
		ret = -1;
	}
	
	return (ret);
}



/***********************************************************************

	カウントデータをキャリブバッファにインプット
	測定が終わったら、キャリブ

***********************************************************************/
int CalibComm::CntDataMesCallBack(CALIB_MSEBOX* para)
{
	int ret = 0;
	int fg = 0;
	VecCtEx2 CntData;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];
	int result;

	CalibComm::m_pData.GetData(&CntData);

	CalibMesIn(&CntData);

	// 測定データのチェック
	if (CalibComm::m_CalibType == CALIB_TYPE::ALIGNMENT_MULTI_GAUGE)
	{
		fg = CalibUserMulti::CntDataMesCallBackSub2(para, &CntData);
	}

	CalibMesOutPath(path);
	CalibMesOutMesg(mesg1, mesg2);
	sprintf_s(mesg, 512, "%s\n%s", mesg1, mesg2);
	MultiByteToWideChar(CP_ACP, 0, path, -1, para->path, 128);
	MultiByteToWideChar(CP_ACP, 0, mesg, -1, para->mes, 256);
	
	int test = CalibMesCheck();
	if (test)
	{
		switch (CalibComm::m_CalibType)
		{
		case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:
			ret |= CalibInspectMultiNestStd::CntDataMesCallBackSub(para);
			break;

		case CALIB_TYPE::INSPECT_MULTI_GAUGE_PLATE_STD:
			ret |= CalibInspectMultiPlateStd::CntDataMesCallBackSub(para);
			break;

		case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
			ret |= CalibUserMulti::CntDataMesCallBackSub(para);
			break;

		case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_STD:
			ret |= CalibProbeBallStd::CntDataMesCallBackSub(para);
			break;

		case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_EXT:
			ret |= CalibProbeBallExt::CntDataMesCallBackSub(para);
			break;

		default:
			break;
		}

	}

	return (ret);
}



/***********************************************************************

	元に戻すボタン

***********************************************************************/
int CalibComm::ClickResoreBtn(CALIB_MSEBOX* para)
{
	int ret = 0;

	CalibComm::m_CalibType = (CALIB_TYPE)para->CalibType;
	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:
		
		break;

	case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
		
		break;

	case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_STD:
		ret |= CalibProbeBallStd::ClickResoreBtnSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_EXT:
		ret |= CalibProbeBallExt::ClickResoreBtnSub(para);
		break;

	default:
		break;
	}


	return (ret);
}



/***********************************************************************

	キャリブが成功したら、パラメータをアームに転送
	キャリブ、点検結果をC#へ伝達

***********************************************************************/
int CalibComm::ParaOutCallBack(CALIB_MSEBOX* para)
{
	int ret = 0;

	
	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:

		break;

	case CALIB_TYPE::INSPECT_MULTI_GAUGE_PLATE_STD:
		ret = CalibInspectMultiPlateStd::ParaOutCallBackSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
		ret = CalibUserMulti::ParaOutCallBackSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_STD:
		ret = CalibProbeBallStd::ParaOutCallBackSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_BALL_GAUGE_EXT:
		ret = CalibProbeBallExt::ParaOutCallBackSub(para);
		break;

	default:
		break;
	}
	

	
	// 通常シーケンスにもどす
	HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
	while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::MEAS_IDLE)
	{
		Sleep(100);
	}

	return (ret);
}



/***********************************************************************

	ScannerAlignmentPanel初期化時に呼ぶ関数
	2025.12.5yori

***********************************************************************/

void CalibComm::InitScanner(CALIB_SCANNER_MSEBOX* para, TCHAR*& path, int p_count, TCHAR*& mes, int m_count)
{
	int ret = 0;
	int lang = 0;
	int calmode = 0;

	CalibComm::m_Language = (LANGUAGE)para->Language;

	para->CalibType = HwCtrl::m_Type;
	CalibComm::m_CalibType = (CALIB_TYPE)para->CalibType;
	switch (CalibComm::m_CalibType)
	{
		case CALIB_TYPE::SCANNER_MAKE_MATRIX:
			CalibScannerMakeMatrix::InitSub(para);
			break;

		case CALIB_TYPE::SCANNER_FULL:
			CalibScannerFull::InitSub(para);
			break;

		default:
			break;
	}
}



/***********************************************************************

	ScannerAlignmentPanelの戻るボタンがクリックされたときに呼ぶ関数
	2025.12.11yori

***********************************************************************/
void CalibComm::BackScanner(CALIB_SCANNER_MSEBOX* para)
{
	wchar_t wc_path[256];
	wchar_t wc_msg[512];
	wchar_t wc_no[8];

	CalibComm::m_CalibType = (CALIB_TYPE)para->CalibType;
	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::SCANNER_MAKE_MATRIX:
		HwCtrl::m_ShotNo--;
		para->ShotNo = HwCtrl::m_ShotNo; // 追加(2025.16yori)
		swprintf(wc_no, 8, L"%d", HwCtrl::m_ShotNo + 1);
		GetPrivateProfileString(TEXT("IMAGE_V7"), wc_no, TEXT("\\calib\\MachineCheck\\V7\\Matrix_Plane_No1.png"), wc_path, 256, MACHINECHECK_TXT);
		if (CalibComm::m_Language == LANGUAGE::JAPANESE) GetPrivateProfileString(TEXT("MESSAGE_JPN"), wc_no, TEXT("[面]-[1点目]測定してください。"), wc_msg, 512, MACHINECHECK_TXT); // 日本語の場合(2025.12.14)
		if (CalibComm::m_Language == LANGUAGE::ENBLISH) GetPrivateProfileString(TEXT("MESSAGE_ENG"), wc_no, TEXT("[Plane]-[First]Please measure."), wc_msg, 512, MACHINECHECK_TXT); // 英語の場合(2025.12.14)
		break;

	case CALIB_TYPE::SCANNER_FULL:
		HwCtrl::m_ScanShotNo--;
		TdsVecSetShotNum(HwCtrl::m_ScanShotNo); // ショットNoを設定漏れのため、追加(2026.1.27yori)
		para->ScanShotNo = HwCtrl::m_ScanShotNo; // 追加(2025.16yori)
		swprintf(wc_no, 8, L"%d", HwCtrl::m_ScanShotNo + 1);
		GetPrivateProfileString(TEXT("IMAGE_V7"), wc_no, TEXT("\\calib\\calscn\\V7\\Shot1.png"), wc_path, 256, CALSCN_TXT);
		if (CalibComm::m_Language == LANGUAGE::JAPANESE) GetPrivateProfileString(TEXT("MESSAGE_JPN"), wc_no, TEXT("[面]-[基本姿勢]-[近]"), wc_msg, 512, CALSCN_TXT); // 日本語の場合(2025.12.14)
		if (CalibComm::m_Language == LANGUAGE::ENBLISH) GetPrivateProfileString(TEXT("MESSAGE_ENG"), wc_no, TEXT("[Plane]-[Normal]-[Near]"), wc_msg, 512, CALSCN_TXT); // 英語の場合(2025.12.14)
		break;

	default:
		break;
	}

	swprintf(para->path, 256, CALIB_PATH);
	swprintf(para->msg, 512, wc_msg);
	wcsncat_s(para->path, wc_path, sizeof(para->path));
}



/***********************************************************************

	ScannerAlignmentPanelの中止ボタンがクリックされたときに呼ぶ関数
	2025.12.11yori

***********************************************************************/
void CalibComm::ReStartScanner(CALIB_SCANNER_MSEBOX* para)
{
	CalibComm::m_CalibType = (CALIB_TYPE)para->CalibType;
	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::SCANNER_MAKE_MATRIX:
		CalibScannerMakeMatrix::InitSub(para);
		break;

	case CALIB_TYPE::SCANNER_FULL:
		CalibScannerFull::InitSub(para);
		break;

	default:
		break;
	}
}



/***********************************************************************

	非接触点検キャリブレーション画像のパスとメッセージ取得
	2025.12.9yori

***********************************************************************/
void CalibComm::ScanDataMesCallBack(CALIB_SCANNER_MSEBOX* para)
{
	wchar_t wc_path[256];
	wchar_t wc_msg[512];
	wchar_t wc_no[8];

	CalibComm::m_CalibType = (CALIB_TYPE)para->CalibType;
	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::SCANNER_MAKE_MATRIX:
		para->ShotNo = HwCtrl::m_ShotNo; // 追加(2025.12.16yori)
		if (HwCtrl::m_ShotNo == HwCtrl::m_ShotMax) para->ShotNo = 0; // 追加(2026.1.27yori)
		swprintf(wc_no, 8, L"%d", HwCtrl::m_ShotNo + 1);
		GetPrivateProfileString(TEXT("IMAGE_V7"), wc_no, TEXT("\\calib\\MachineCheck\\V7\\Matrix_Plane_No1.png"), wc_path, 256, MACHINECHECK_TXT);
		if (CalibComm::m_Language == LANGUAGE::JAPANESE) GetPrivateProfileString(TEXT("MESSAGE_JPN"), wc_no, TEXT("[面]-[1点目]測定してください。"), wc_msg, 512, MACHINECHECK_TXT); // 日本語の場合(2025.12.14)
		if (CalibComm::m_Language == LANGUAGE::ENBLISH) GetPrivateProfileString(TEXT("MESSAGE_ENG"), wc_no, TEXT("[Plane]-[First]Please measure."), wc_msg, 512, MACHINECHECK_TXT); // 英語の場合(2025.12.14)
		break;

	case CALIB_TYPE::SCANNER_FULL:
		para->ScanShotNo = HwCtrl::m_ScanShotNo; // 追加(2025.12.16yori)
		swprintf(wc_no, 8, L"%d", HwCtrl::m_ScanShotNo + 1);
		GetPrivateProfileString(TEXT("IMAGE_V7"), wc_no, TEXT("\\calib\\calscn\\V7\\Shot1.png"), wc_path, 256, CALSCN_TXT);
		if (CalibComm::m_Language == LANGUAGE::JAPANESE) GetPrivateProfileString(TEXT("MESSAGE_JPN"), wc_no, TEXT("[面]-[基本姿勢]-[近]"), wc_msg, 512, CALSCN_TXT); // 日本語の場合(2025.12.14)
		if (CalibComm::m_Language == LANGUAGE::ENBLISH) GetPrivateProfileString(TEXT("MESSAGE_ENG"), wc_no, TEXT("[Plane]-[Normal]-[Near]"), wc_msg, 512, CALSCN_TXT); // 英語の場合(2025.12.14)
		break;

	default:
		break;
	}

	swprintf(para->path, 256, CALIB_PATH);
	swprintf(para->msg, 512, wc_msg);
	wcsncat_s(para->path, wc_path, sizeof(para->path));
}



/***********************************************************************

	ScannerAlignmentPanelの閉じるボタンがクリックされたときに呼ぶ関数
	2025.12.11yori
	戻り値なしの関数へ変更(2025.12.17yori)

***********************************************************************/
void CalibComm::CloseScanner()
{
	int ret = 0;

	if (HwCtrl::m_ScannerAlignmentProbeFlag == true) // 有接触の場合(2025.12.17yori)
	{
		HwCtrl::m_ScannerAlignmentProbeFlag = false;

		// 有接触測定音OFFにして測定待機状態へ変更
		if (HwCtrl::Func12() == 0) HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
		while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::MEAS_IDLE)
		{
			Sleep(100);
		}
	}

	if (HwCtrl::m_ScannerAlignmentScannerFlag == true) // 非接触の場合(2025.12.17yori)
	{
		HwCtrl::m_ScannerAlignmentScannerFlag = false;
		HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::SCANNER_DISCONNECT_REQ; // スキャナ切断処理
		while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::SCANNER_DISCONNECT_REQ) // スキャナ切断処理状態になるまで待機
		{
			Sleep(100);
		}
		while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::SCANNER_DISCONNECT_CMP) // スキャナ切断処理完了状態になるまで待機
		{
			Sleep(100);
		}
		delete HwCtrl::m_ptCalibResult;

		// 有接触測定音OFFにして測定待機状態へ変更
		if (HwCtrl::Func12() == 0) HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
		while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::MEAS_IDLE)
		{
			Sleep(100);
		}
	}
}



/***********************************************************************

	非接触点検キャリブ結果コールバック関数
	2025.12.10yori

***********************************************************************/
void CalibComm::ScannerAlignmentPanelResultCallBack(CALIB_SCANNER_MSEBOX* para)
{
	para->dResult[0][0] = HwCtrl::m_ptCalibResult->dResult[0][0];
	para->dResult[0][1] = HwCtrl::m_ptCalibResult->dResult[0][1];
	para->dResult[0][2] = HwCtrl::m_ptCalibResult->dResult[0][2];
	para->dResult[1][0] = HwCtrl::m_ptCalibResult->dResult[1][0];
	para->dResult[1][1] = HwCtrl::m_ptCalibResult->dResult[1][1];
	para->dResult[1][2] = HwCtrl::m_ptCalibResult->dResult[1][2];
	para->dResult[2][0] = HwCtrl::m_ptCalibResult->dResult[2][0];
	para->dResult[2][1] = HwCtrl::m_ptCalibResult->dResult[2][1];
	para->dResult[2][2] = HwCtrl::m_ptCalibResult->dResult[2][2];
	para->dResult[3][0] = HwCtrl::m_ptCalibResult->dResult[3][0];
	para->dResult[3][1] = HwCtrl::m_ptCalibResult->dResult[3][1];
	para->dResult[3][2] = HwCtrl::m_ptCalibResult->dResult[3][2];
	para->maxmin[0] = HwCtrl::m_MaxMin[0];
	para->maxmin[1] = HwCtrl::m_MaxMin[1];
	para->maxmin[2] = HwCtrl::m_MaxMin[2];
	para->CalibResultJudge = HwCtrl::m_ScannerCalibResultJudge;
}