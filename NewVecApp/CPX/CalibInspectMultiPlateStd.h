/***********************************************************************

	始業前点検クラス

***********************************************************************/
#pragma once
#include    "HwCtrl.h"



class CalibInspectMultiPlateStd : public CalibComm
{
public:
	static int CntDataMesCallBackSub(CALIB_MSEBOX* para);
	static int ParaOutCallBackSub(CALIB_MSEBOX* para);

};