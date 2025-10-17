/***********************************************************************

	始業前点検クラス

***********************************************************************/
#pragma once
#include    "HwCtrl.h"



class CalibInspectMultiNestExt : public CalibComm
{
public:
	static int InitSub(CALIB_MSEBOX* para);
	static int StartSub(CALIB_MSEBOX* para);
	static int CntDataMesCallBackSub(CALIB_MSEBOX* para);
	//static int ParaOutCallBackSub(void);

};