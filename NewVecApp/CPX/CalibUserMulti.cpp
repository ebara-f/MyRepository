/***********************************************************************

    始業前点検クラス

***********************************************************************/
#include    "CalibComm.h"
#include	"CalibUserMulti.h"



int CalibUserMulti::InitSub(CALIB_MSEBOX* para)
{
	int ret = 0;


	switch (CalibComm::m_Language)
	{
	case LANGUAGE::JAPANESE:
		ret |= CalibInit(0, CALIB_MODE_USER);
		wcscpy_s(para->mes, 256, _T("ユーザーキャリブレーションをはじめます"));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\light_ja.png"));
		break;

	case LANGUAGE::ENBLISH:
		ret |= CalibInit(1, CALIB_MODE_USER);
		wcscpy_s(para->mes, 256, _T("Start User Calibration."));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\light_en.png"));
		break;

	default:
		wcscpy_s(para->mes, 256, _T("Unexpected events."));
		wcscpy_s(para->path, 128, _T(""));
		ret = 1;
		break;
	}


	return (ret);

}


int CalibUserMulti::StartSub(CALIB_MSEBOX* para)
{
	int ret = 0;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];


	
	
	if (HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 2 ||
		HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 1)
	{
		HwCtrl::m_hVecCnt.VecCmd_ChangeProbe(1); // PS=1へ強制変更
	}
	else
	{
		para->MesString = 230;
		ret = 1;
	}
	
	return (ret);
}



int CalibUserMulti::CntDataMesCallBackSub(CALIB_MSEBOX* para)
{
	int ret = 0;

	VecCtEx2 CntData;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];

	int result;
	if (!CalibCalParaOut(&result, &CalibComm::m_ArmParaTxt, 1))	// 試しにPSIDは１
	{
		para->CalibInspectJudge = 1;	// NG
		ret = 1;
	}
	else
	{
		para->CalibInspectJudge = 0;	// OK
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



int CalibUserMulti::CntDataMesCallBackSub2(CALIB_MSEBOX* para, VecCtEx2* data)
{
	int ret = 0;
	double radius;
	double height;
	double err;
	
	para->MesString = 0;
	if (CalibMesPosChk(data, &radius, &height) == 0)
	{	
		para->MesString = 231;
		ret |= 1;
	}

	if (CalibMesErrChk(data, &err) == 0)
	{
		if (ret == 1)
		{
			para->MesString = 232;
		}
		else
		{
			para->MesString = 233;
		}
		ret |= 1;
	}

	return (ret);
}




int CalibUserMulti::ParaOutCallBackSub(CALIB_MSEBOX* para)
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