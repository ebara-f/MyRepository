/***********************************************************************

    非接触フルキャリブレーションクラス
	2025.12.5yori

***********************************************************************/
#include    "CalibComm.h"
#include	"CalibScannerFull.h"



void CalibScannerFull::InitSub(CALIB_SCANNER_MSEBOX* para)
{
	// 画面表示設定
	switch (CalibComm::m_Language)
	{
	case LANGUAGE::JAPANESE:
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\calscn\\V7\\Shot1.png"));
		wcscpy_s(para->msg, 256, _T("[面]-[基本姿勢]-[近]"));
		break;

	case LANGUAGE::ENBLISH:
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\calscn\\V7\\Shot1.png"));
		wcscpy_s(para->msg, 256, _T("[Plane]-[Normal]-[Near]"));
		break;

	default:
		wcscpy_s(para->path, 128, _T(""));
		wcscpy_s(para->msg, 256, _T("Unexpected events."));
		break;
	}
}