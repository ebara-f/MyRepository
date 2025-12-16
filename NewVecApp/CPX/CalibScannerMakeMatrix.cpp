/***********************************************************************

    非接触点検キャリブレーション座標系作成クラス
	2025.12.4yori

***********************************************************************/
#include    "CalibComm.h"
#include	"CalibScannerMakeMatrix.h"



void CalibScannerMakeMatrix::InitSub(CALIB_SCANNER_MSEBOX* para)
{
	// 画面表示設定
	switch (CalibComm::m_Language)
	{
	case LANGUAGE::JAPANESE:
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\MachineCheck\\V7\\Matrix_Plane_No1.png"));
		wcscpy_s(para->msg, 256, _T("[面]-[1点目]測定してください。"));
		break;

	case LANGUAGE::ENBLISH:
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\MachineCheck\\V7\\Matrix_Plane_No1.png"));
		wcscpy_s(para->msg, 256, _T("[Plane]-[First]Please measure."));
		break;

	default:
		wcscpy_s(para->path, 128, _T(""));
		wcscpy_s(para->msg, 256, _T("Unexpected events."));
		break;
	}

	// プローブID設定
	if (HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 2 ||
		HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 1)
	{
		HwCtrl::m_hVecCnt.VecCmd_ChangeProbe(2); // PS=2へ強制変更
	}
	else
	{
		para->MesString = 230;
	}

	// 有接触測定音ON
	HwCtrl::Func13();

	// 座標系作成のショット数を取得
	MakeMtxInfo ptinfo;
	TdsVecGetMakeMatrixInfo(&ptinfo);
	HwCtrl::m_ShotMax = ptinfo.iShotMax;

	//  座標系作成のショット数初期化(2025.12.11yori)
	HwCtrl::m_ShotNo = 0;
}