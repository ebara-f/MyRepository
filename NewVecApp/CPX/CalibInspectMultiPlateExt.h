/***********************************************************************

	�n�ƑO�_���N���X

***********************************************************************/
#pragma once
#include    "HwCtrl.h"



class CalibInspectMultiPlateExt : public CalibComm
{
public:
	static int CntDataMesCallBackSub(CALIB_MSEBOX* para);
	static int ParaOutCallBackSub(void);

};