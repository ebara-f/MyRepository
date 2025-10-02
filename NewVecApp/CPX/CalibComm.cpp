/***********************************************************************

	点検、キャリブパネルを処理するGrop02の子グループ

***********************************************************************/
#include	"CalibComm.h"
#include	"CalibUserMulti.h"
#include	"CalibInspectMultiNestStd.h"
#include	"CalibInspectMultiPlateStd.h"

CALIB_TYPE		CalibComm::m_CalibType;
LANGUAGE		CalibComm::m_Language;
CalibDataBuff	CalibComm::m_pData;
CALIB_DATA		CalibComm::m_ArmParaTxt;

/***********************************************************************

	パネル初期化時
	に呼ぶ関数

***********************************************************************/

int CalibComm::Init(CALIB_PARA* para, TCHAR*& path, int p_count, TCHAR*& mes, int m_count)
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
int CalibComm::Start(CALIB_PARA* para)
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

	
	HwCtrl::Func09();	// ステータス要求(現在のプローブIDが知りたい)
	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:
		ret |= CalibInspectMultiNestStd::StartSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
		ret |= CalibUserMulti::StartSub(para);
		break;

	default:
		break;
	}

	if (ret != 0)
	{
		goto exit;
	}

	// 判定フラグの初期化
	para->CalibInspectJudge = 0;
	// ゲージの値設定
	CalibSetGaugeVal(para->GaugePara);

	// しきい値の取得
	ret |= CalibGetThreshold(&para->ProbeCheckThreshold, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId);
	ret |= CalibGetThresholdCk(&para->InspectionThreshold);

	// 初期パラメータ取得・設定
	HwCtrl::GetArmParaV8(&CalibComm::m_ArmParaTxt, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId);
	CalibCalParaIn(&CalibComm::m_ArmParaTxt, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId);

	// データ初期化
	CalibMesReset();
	CalibMesOutPath(path);
	CalibMesOutMesg(mesg1,mesg2);
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
int CalibComm::Back(CALIB_PARA* para)
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

	default:
		break;
	}



	return (ret);
}


/***********************************************************************

	中止ボタンがクリックされたときに
	に呼ぶ関数

***********************************************************************/
int CalibComm::ReStart(CALIB_PARA* para)
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
int CalibComm::Close(CALIB_PARA* para)
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
	i = HwCtrl::Func28(&CntData); // 2025.9.2 add eba 

	if ((CntData.button & 0x01) && (i == VEC_OK))
	{
		CalibComm::m_pData.PutData(CntData);
		ret = 1;
	}
	
	return (ret);
}



/***********************************************************************

	カウントデータをキャリブバッファにインプット
	測定が終わったら、キャリブ

***********************************************************************/
int CalibComm::CntDataMesCallBack(CALIB_PARA* para)
{
	int ret = 0;
	int fg = 0;
	VecCtEx2 CntData;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];
	int result;

	CalibComm::m_pData.GetData(&CntData);

	// 測定データのチェック
	if (CalibComm::m_CalibType == CALIB_TYPE::ALIGNMENT_MULTI_GAUGE)
	{
		fg = CalibUserMulti::CntDataMesCallBackSub2(para, &CntData);
		if(fg==0) CalibMesIn(&CntData);
	}
	else
	{
		CalibMesIn(&CntData);
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

		default:
			break;
		}

	}

	return (ret);
}


/***********************************************************************

	キャリブが成功したら、パラメータをアームに転送
	キャリブ、点検結果をC#へ伝達

***********************************************************************/
int CalibComm::ParaOutCallBack(CALIB_PARA* para)
{
	int ret = 0;

	
	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:

		break;

	case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
		
		ret = CalibUserMulti::ParaOutCallBackSub();

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


