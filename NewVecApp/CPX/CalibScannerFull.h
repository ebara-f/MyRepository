/***********************************************************************

	非接触フルキャリブレーションクラス
	2025.12.5yori

***********************************************************************/
#pragma once
#include    "HwCtrl.h"



class CalibScannerFull : public CalibComm
{
public:
	static void InitSub(CALIB_SCANNER_MSEBOX* para);
};