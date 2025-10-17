/***********************************************************************

	点検、キャリブパネルを処理するGrop02の子グループ

***********************************************************************/
#pragma once

class CalibSetting : public CalibComm
{

protected:
	
public:
	static int Init(CALIB_MSEBOX* para);
	static int OkBtn(CALIB_MSEBOX* para);
	static int CancelBtn(CALIB_MSEBOX* para);



	

};
