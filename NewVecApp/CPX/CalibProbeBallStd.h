/***********************************************************************

	始業前点検クラス

***********************************************************************/
#pragma once
#include    "HwCtrl.h"



class CalibProbeBallStd : public CalibComm
{
public:
	static CALIB_DATA		m_ArmParaTxtBackUp;

	static int InitSub(CALIB_MSEBOX* para);
	static int StartSub(CALIB_MSEBOX* para);
	static int CntDataMesCallBackSub(CALIB_MSEBOX* para);
	static int CntDataMesCallBackSub2(CALIB_MSEBOX* para, VecCtEx2* data);
	static int ParaOutCallBackSub(CALIB_MSEBOX* para);
	static int ClickResoreBtnSub(CALIB_MSEBOX* para);



};