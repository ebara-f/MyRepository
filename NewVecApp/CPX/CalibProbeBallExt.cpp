/***********************************************************************

    始業前点検クラス

***********************************************************************/
#include    "CalibComm.h"
#include	"CalibProbeBallExt.h"

CALIB_DATA CalibProbeBallExt::m_ArmParaTxtBackUp;

int CalibProbeBallExt::InitSub(CALIB_MSEBOX* para)
{
	int ret = 0;


	switch (CalibComm::m_Language)
	{
	case LANGUAGE::JAPANESE:
		ret |= CalibInit(0, CALIB_MODE_SIMPLE_BALL_EXT);
		wcscpy_s(para->mes, 256, _T("プローブキャリブレーションをはじめます"));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\probeCalib_ja.png"));
		break;

	case LANGUAGE::ENBLISH:
		ret |= CalibInit(1, CALIB_MODE_SIMPLE_BALL_EXT);
		wcscpy_s(para->mes, 256, _T("Start User Calibration."));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\probeCalib_en.png"));
		break;

	default:
		wcscpy_s(para->mes, 256, _T("Unexpected events."));
		wcscpy_s(para->path, 128, _T(""));
		ret = 1;
		break;
	}


	return (ret);

}


int CalibProbeBallExt::StartSub(CALIB_MSEBOX* para)
{
	int ret = 0;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];
	
	if (HwCtrl::m_hVecCnt.m_Sts.m_iProbeId != 17 ||
		HwCtrl::m_hVecCnt.m_Sts.m_iProbeId != 18 ||
		HwCtrl::m_hVecCnt.m_Sts.m_iProbeId != 19)
	{
		
	}
	else
	{
		para->MesString = 230;
		ret = 1;
	}
	
	// 初期パラメータ取得・設定
	HwCtrl::GetArmParaV8(&CalibComm::m_ArmParaTxt, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId, para->CalibProbeBranch);
	CalibCalParaInEx(&CalibComm::m_ArmParaTxt, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId, para->CalibProbeBranch);
	// 戻すようにバックアップ
	CalibProbeBallExt::m_ArmParaTxtBackUp = CalibComm::m_ArmParaTxt;

	return (ret);
}



int CalibProbeBallExt::CntDataMesCallBackSub(CALIB_MSEBOX* para)
{
	int ret = 0;

	VecCtEx2 CntData;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];

	int result;
	if (!CalibCalParaOutEx(&result, &CalibComm::m_ArmParaTxt, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId, para->CalibProbeBranch))	// 指定の枝番
	{
		para->CalibInspectJudge = 1;
		ret = 1;
	}
	else
	{
		para->CalibInspectJudge = 0;
	}
	para->CalibResultVal = result;

	// キャリブ前点検結果
	CalibCheckBallResult(&para->InspAndProbCkResult);	// ri, Ps


	// 通常シーケンスにもどす
	HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ALIGNMENT_ING2;
	while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::ALIGNMENT_ING2)
	{
		Sleep(100);
	}

	return (ret);
}



int CalibProbeBallExt::ParaOutCallBackSub(CALIB_MSEBOX* para)
{
	int ret = 0;
	int no = 0;
	int i = 0;
	CALIB_PAPA data;


	// 結果パラメータ転送
	if (para->CalibInspectJudge == 0)	// // OKなら
	{
		HwCtrl::SetArmParaV8(&CalibComm::m_ArmParaTxt, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId, para->CalibProbeBranch);
	}

	ret |= CalibEnd();

	

	OutDataNo(&no);
	for (i = 0; i < no; i++)
	{
		OutCntData(i+1, &data);
		GetXYZData(i+1, &data);
	}

	// キャリブ後点検結果
	CalibCheckBallResult(&para->InspAndProbCkResult2);	// ri, Ps


	return (ret);

}


int CalibProbeBallExt::ClickResoreBtnSub(CALIB_MSEBOX* para)
{
	int ret = 0;

	HwCtrl::SetArmParaV8(&CalibProbeBallExt::m_ArmParaTxtBackUp, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId, para->CalibProbeBranch);
	

	return (ret);

}