/***********************************************************************

    始業前点検クラス

***********************************************************************/
#include    "CalibComm.h"
#include	"CalibProbeBallStd.h"

CALIB_DATA CalibProbeBallStd::m_ArmParaTxtBackUp;

int CalibProbeBallStd::InitSub(CALIB_MSEBOX* para)
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


int CalibProbeBallStd::StartSub(CALIB_MSEBOX* para)
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
	
	// 初期パラメータ取得・設定
	HwCtrl::GetArmParaV8(&CalibComm::m_ArmParaTxt, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId, 0);
	CalibCalParaIn(&CalibComm::m_ArmParaTxt, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId);
	// 戻すようにバックアップ
	CalibProbeBallStd::m_ArmParaTxtBackUp = CalibComm::m_ArmParaTxt;


	return (ret);
}



int CalibProbeBallStd::CntDataMesCallBackSub(CALIB_MSEBOX* para)
{
	int ret = 0;

	VecCtEx2 CntData;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];

	int result;
	if (!CalibCalParaOut(&result, &CalibComm::m_ArmParaTxt, 2))	// PSIDは2
	{
		para->CalibResultJudge = 1;
		ret = 1;
	}
	else
	{
		para->CalibResultJudge = 0;
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



int CalibProbeBallStd::ParaOutCallBackSub(CALIB_MSEBOX* para)
{
	int ret = 0;
	int no = 0;
	int i = 0;
	CALIB_PAPA data;


	// 結果パラメータ転送
	if (para->CalibResultJudge == 0)	// // OKなら
	{
		HwCtrl::SetArmParaV8(&CalibComm::m_ArmParaTxt, 2, 0);
		HwCtrl::WriteParaISO();
	}

	OutDataNo(&no);
	for (i = 0; i < no; i++)
	{
		OutCntData(i + 1, &data);
		HwCtrl::VecCmd_Pc(&data);
		GetXYZData(i + 1, &data);
	}

	// キャリブ後点検結果
	CalibCheckBallResult(&para->InspAndProbCkResult2);	// ri, Ps

	if (para->InspAndProbCkResult.ri < para->InspAndProbCkResult2.ri)
	{
		para->CalibInspectJudge = 1;
	}
	if (para->InspAndProbCkResult.Ps < para->InspAndProbCkResult2.Ps)
	{
		para->CalibInspectJudge = 1;
	}


	ret |= CalibEnd();


	return (ret);

}


int CalibProbeBallStd::ClickResoreBtnSub(CALIB_MSEBOX* para)
{
	int ret = 0;

	HwCtrl::SetArmParaV8(&CalibProbeBallStd::m_ArmParaTxtBackUp, 2, 0);
	HwCtrl::WriteParaISO();

	return (ret);

}