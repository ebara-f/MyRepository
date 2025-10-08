/***********************************************************************

	始業前点検クラス

***********************************************************************/
#pragma once
#include    "HwCtrl.h"



class CalibInspectMultiPlateExt : public CalibComm
{
public:
	static int CntDataMesCallBackSub(CALIB_PARA* para);
	static int ParaOutCallBackSub(void);

};