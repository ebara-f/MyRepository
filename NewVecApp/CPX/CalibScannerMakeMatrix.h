/***********************************************************************

	非接触点検キャリブレーション座標系作成クラス
	2025.12.4yori

***********************************************************************/
#pragma once
#include    "HwCtrl.h"



class CalibScannerMakeMatrix : public CalibComm
{
public:
	static void InitSub(CALIB_SCANNER_MSEBOX* para);
};