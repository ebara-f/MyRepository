/***********************************************************************

    始業前点検クラス

***********************************************************************/
#include    "CalibComm.h"
#include	"CalibProbeBallStd.h"



int CalibProbeBallStd::InitSub(CALIB_PARA* para)
{
	int ret = 0;


	switch (CalibComm::m_Language)
	{
	case LANGUAGE::JAPANESE:
		ret |= CalibInit(0, CALIB_MODE_SIMPLE_BALL);
		wcscpy_s(para->mes, 256, _T("プローブキャリブレーションをはじめます"));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\probeCalib_ja.png"));
		break;

	case LANGUAGE::ENBLISH:
		ret |= CalibInit(1, CALIB_MODE_SIMPLE_BALL);
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


int CalibProbeBallStd::StartSub(CALIB_PARA* para)
{
	int ret = 0;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];


	
	
	if (HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 2 ||
		HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 1)
	{
		HwCtrl::m_hVecCnt.VecCmd_ChangeProbe(2); // PS=2へ強制変更
	}
	else
	{
		para->MesString = 230;
		ret = 1;
	}
	
	return (ret);
}



int CalibProbeBallStd::CntDataMesCallBackSub(CALIB_PARA* para)
{
	int ret = 0;

	VecCtEx2 CntData;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];

	int result;
	if (!CalibCalParaOut(&result, &CalibComm::m_ArmParaTxt, 2))	// PSIDは2
	{
		para->CalibInspectJudge = 1;
		ret = 1;
	}
	else
	{
		para->CalibInspectJudge = 0;
	}
	para->CalibResultVal = result;


	// 通常シーケンスにもどす
	HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ALIGNMENT_ING2;
	while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::ALIGNMENT_ING2)
	{
		Sleep(100);
	}

	return (ret);
}



int CalibProbeBallStd::ParaOutCallBackSub(CALIB_PARA* para)
{
	int ret = 0;

	// 結果パラメータ転送
	if (para->CalibInspectJudge == 0)	// // OKなら
	{
		HwCtrl::SetArmParaV8(&CalibComm::m_ArmParaTxt, 1);
	}

	ret |= CalibEnd();



	return (ret);

}