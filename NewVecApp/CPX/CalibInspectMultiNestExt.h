/***********************************************************************

	�n�ƑO�_���N���X

***********************************************************************/
#pragma once
#include    "HwCtrl.h"



class CalibInspectMultiNestExt : public CalibComm
{
public:
	static int InitSub(CALIB_PARA* para);
	static int StartSub(CALIB_PARA* para);
	static int CntDataMesCallBackSub(CALIB_PARA* para);
	//static int ParaOutCallBackSub(void);

};