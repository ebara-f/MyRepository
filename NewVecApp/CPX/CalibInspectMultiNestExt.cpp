/***********************************************************************

    始業前点検クラス

***********************************************************************/
#include    "CalibComm.h"
#include	"CalibInspectMultiNestExt.h"



int CalibInspectMultiNestExt::InitSub(CALIB_PARA* para)
{
	int ret = 0;
	

	switch (CalibComm::m_Language)
	{
	case LANGUAGE::JAPANESE:
		ret |= CalibInit(0, CALIB_MODE_PROBE_CHECK_EXT);
		wcscpy_s(para->mes, 256, _T("Extプローブ点検をはじめます"));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\probe_ja.png"));
		break;

	case LANGUAGE::ENBLISH:
		ret |= CalibInit(1, CALIB_MODE_PROBE_CHECK_EXT);
		wcscpy_s(para->mes, 256, _T("Start Probe Inspection."));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\probe_en.png"));
		break;

	default:
		wcscpy_s(para->mes, 256, _T("Unexpected events."));
		wcscpy_s(para->path, 128, _T(""));
		ret = 1;
		break;
	}


	return (ret);

}


int CalibInspectMultiNestExt::StartSub(CALIB_PARA* para)
{
	int ret = 0;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];




	if (HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 2 ||
		HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 1)
	{
		para->MesString = 258;
		ret = 1;
	}

	return (ret);
}


int CalibInspectMultiNestExt::CntDataMesCallBackSub(CALIB_PARA* para)
{
	int ret = 0;
	int i = 0;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];

	ret = CalibCheckResult(&para->InspAndProbCkResult);
	ret |= CalibEnd();

	for (i = 0; i < 3; i++)
	{
		if (para->ProbeCheckThreshold.pp < para->InspAndProbCkResult.pp[i])
		{
			para->ProbeCheckResultFg.pp[i] = 1;
			para->CalibInspectJudge |= 1;
		}

	}
	
	/*for (i = 0; i < 4; i++)
	{
		if (para->InspectionThreshold.sigma2 < para->InspAndProbCkResult.sigma2[i])
		{
			para->InspectionResultFg.sigma2[i] = 1;
			para->CalibInspectJudge |= 1;
		}
	}*/

	CalibComm::m_CalibType = CALIB_TYPE::INSPECT_MULTI_GAUGE_PLATE_STD;

	switch (CalibComm::m_Language)
	{
	case LANGUAGE::JAPANESE:
		ret |= CalibInit(0, CALIB_MODE_PLATE_EXT);
		break;

	case LANGUAGE::ENBLISH:
		ret |= CalibInit(1, CALIB_MODE_PLATE_EXT);
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
