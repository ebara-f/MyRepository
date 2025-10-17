/***********************************************************************

	点検、キャリブパネルを処理するGrop02の子グループ

***********************************************************************/
#pragma once

#include	"common.h"
#include	"CPX.h"
#include	"Grp02.h"
#include	"CalibDataBuff.h"


// 2025.8.27 add eba
enum class CALIB_TYPE
{
	UNKNOWN = 0,
	INSPECT_MULTI_GAUGE_NEST_STD,
	INSPECT_MULTI_GAUGE_PLATE_STD,
	INSPECT_BALL_GAUGE,
	ALIGNMENT_MULTI_GAUGE,
	ALIGNMENT_BALL_GAUGE_STD,



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


};
