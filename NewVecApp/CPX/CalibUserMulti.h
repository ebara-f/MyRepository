/***********************************************************************

	�n�ƑO�_���N���X

***********************************************************************/
#pragma once
#include    "HwCtrl.h"



class CalibUserMulti : public CalibComm
{
public:
	static int InitSub(CALIB_MSEBOX* para);
	static int StartSub(CALIB_MSEBOX* para);
	static int CntDataMesCallBackSub(CALIB_MSEBOX* para);
	static int CntDataMesCallBackSub2(CALIB_MSEBOX* para, VecCtEx2* data);
	static int ParaOutCallBackSub(CALIB_MSEBOX* para);

};