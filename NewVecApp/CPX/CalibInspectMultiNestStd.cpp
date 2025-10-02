/***********************************************************************

    始業前点検クラス

***********************************************************************/
#include    "CalibComm.h"
#include	"CalibInspectMultiNestStd.h"



int CalibInspectMultiNestStd::InitSub(CALIB_PARA* para)
{
	int ret = 0;
	

	switch (CalibComm::m_Language)
	{
	case LANGUAGE::JAPANESE:
		ret |= CalibInit(0, CALIB_MODE_CHECK);
		wcscpy_s(para->mes, 256, _T("始業前点検をはじめます"));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\check_ja.png"));
		break;

	case LANGUAGE::ENBLISH:
		ret |= CalibInit(1, CALIB_MODE_CHECK);
		wcscpy_s(para->mes, 256, _T("Start Machine Inspection."));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\check_en.png"));
		break;

	default:
		wcscpy_s(para->mes, 256, _T("Unexpected events."));
		wcscpy_s(para->path, 128, _T(""));
		ret = 1;
		break;
	}


	return (ret);

}


int CalibInspectMultiNestStd::StartSub(CALIB_PARA* para)
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
		para->MesString = 230;	// 2025.10.1 add eba
		ret = 1;
	}

	return (ret);
}


int CalibInspectMultiNestStd::CntDataMesCallBackSub(CALIB_PARA* para)
{
	int ret = 0;
	int i = 0;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];
	//CALIB_RESULT result;
	//CALIB_JUDGE judge;

	ret = CalibCheckResult(&para->InspAndProbCkResult);
	ret |= CalibEnd();

	for (i = 0; i < 3; i++)
	{
		//para->IncpectionResult.pp[i] = result.pp[i];
		//para->IncpectionResult.sigma2[i] = result.sigma2[i];

		if (para->InspectionThreshold.pp < para->InspAndProbCkResult.pp[i])
		{
			para->InspectionResultFg.pp[i] = 1;
			para->CalibInspectJudge |= 1;
		}

	}
	
	for (i = 0; i < 4; i++)
	{
		if (para->InspectionThreshold.sigma2 < para->InspAndProbCkResult.sigma2[i])
		{
			para->InspectionResultFg.sigma2[i] = 1;
			para->CalibInspectJudge |= 1;
		}
	}

	CalibComm::m_CalibType = CALIB_TYPE::INSPECT_MULTI_GAUGE_PLATE_STD;

	switch (CalibComm::m_Language)
	{
	case LANGUAGE::JAPANESE:
		ret |= CalibInit(0, CALIB_MODE_PLATE);
		break;

	case LANGUAGE::ENBLISH:
		ret |= CalibInit(1, CALIB_MODE_PLATE);
		break;

	default:
		ret = 1;
		break;
	}

	// バッファリセット
	CalibMesReset();
	
	// データ初期化
	CalibMesReset();
	CalibMesOutPath(path);
	CalibMesOutMesg(mesg1, mesg2);
	sprintf_s(mesg, 512, "%s\n%s", mesg1, mesg2);

	MultiByteToWideChar(CP_ACP, 0, path, -1, para->path, 128);
	MultiByteToWideChar(CP_ACP, 0, mesg, -1, para->mes, 256);

	return (ret);
}
