/***********************************************************************

	点検、キャリブパネルを処理するGrop02の子グループ

***********************************************************************/
#pragma once

#include	"common.h"
#include	"CPX.h"
#include	"Grp02.h"
#include	"CalibDataBuff.h"

#define CALIB_PATH L"C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles" // 追加(2025.12.4yori)
#define MACHINECHECK_INI L"C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\MachineCheck\\MachineCheck.txt" // 追加(2025.12.4yori)
#define CALSCN_INI L"C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\calscn\\calscn.txt" // 追加(2025.12.8yori)

// 2025.8.27 add eba
enum class CALIB_TYPE
{
	UNKNOWN = 0,
	INSPECT_MULTI_GAUGE_NEST_STD,
	INSPECT_MULTI_GAUGE_PLATE_STD,
	INSPECT_BALL_GAUGE,
	ALIGNMENT_MULTI_GAUGE,
	ALIGNMENT_BALL_GAUGE_STD,			// CALIB_MODE_SIMPLE_BALL
	ALIGNMENT_BALL_GAUGE_EXT,			// CALIB_MODE_SIMPLE_BALL_EXT
	ALIGNMENT_MULTI_GAUGE_NEST_STD,		// CALIB_MODE_PROBE
	ALIGNMENT_MULTI_GAUGE_NEST_EXT,		// CALIB_MODE_PROBE_EXT
	PROBEINSPECT_MULTI_GAUGE_NEST_STD,	// CALIB_MODE_PROBE_CHECK
	PROBEINSPECT_MULTI_GAUGE_NEST_EXT,	// CALIB_MODE_PROBE_CHECK_EXT
	// PROBEINSPECTのBALLはない 2025.10.31 memo eba
	SCANNER_MAKE_MATRIX,				// 非接触点検キャリブレーションの座標系作成(2025.12.5yori)
	SCANNER_FULL,						// 非接触フルキャリブレーション(2025.12.5yori)

	END
};


class CalibComm : public Grp02
{

protected:
	static CALIB_TYPE		m_CalibType;
	//static CALIB_TYPE		m_CalibType2;
	static LANGUAGE			m_Language;
	static CalibDataBuff	m_pData;
	static CALIB_DATA		m_ArmParaTxt;
public:
	static int Init(CALIB_MSEBOX* para, TCHAR*& path, int p_count, TCHAR*& mes, int m_count);
	static int Start(CALIB_MSEBOX* para);
	static int Back(CALIB_MSEBOX* para);
	static int ReStart(CALIB_MSEBOX* para);
	static int Close(CALIB_MSEBOX* para);
	static int GetDrawPath(TCHAR*& path, int count);
	static int GetMesString(TCHAR*& mes, int count);
	static int CntDataInputThread(void);
	static int CntDataMesCallBack(CALIB_MSEBOX* para);
	static int ClickResoreBtn(CALIB_MSEBOX* para);
	static int ParaOutCallBack(CALIB_MSEBOX* para);

	// 非接触関連
	static void InitScanner(CALIB_SCANNER_MSEBOX* para, TCHAR*& path, int p_count, TCHAR*& mes, int m_count); // 追加(2025.12.4yori)
	static void ScanDataMesCallBack(CALIB_SCANNER_MSEBOX* para); // 追加(2025.12.4yori)
	static int CloseScanner(); // 追加(2025.12.4yori)
};