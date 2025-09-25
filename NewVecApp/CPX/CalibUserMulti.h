/***********************************************************************

	始業前点検クラス

***********************************************************************/
#pragma once
#include    "HwCtrl.h"



class CalibUserMulti : public CalibComm
{
public:
	static int InitSub(CALIB_PARA* para);
	static int StartSub(CALIB_PARA* para);
	static int CntDataMesCallBackSub(CALIB_PARA* para);
	static int CntDataMesCallBackSub2(CALIB_PARA* para, VecCtEx2* data);
	static int ParaOutCallBackSub(void);

};