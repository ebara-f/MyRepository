/***********************************************************************

	�n�ƑO�_���N���X

***********************************************************************/
#pragma once
#include    "HwCtrl.h"



class CalibInspectMultiPlateStd : public CalibComm
{
public:
	static int CntDataMesCallBackSub(CALIB_PARA* para);
	static int ParaOutCallBackSub(void);

};