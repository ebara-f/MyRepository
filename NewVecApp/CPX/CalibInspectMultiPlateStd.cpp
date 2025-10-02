/***********************************************************************

    始業前点検クラス

***********************************************************************/
#include    "CalibComm.h"
#include	"CalibInspectMultiPlateStd.h"



int CalibInspectMultiPlateStd::CntDataMesCallBackSub(CALIB_PARA* para)
{
	int ret = 0;
	int i = 0;
	CALIB_RESULT result;
	CALIB_JUDGE judge;
	double err = 0.0;

	ret |= CalibPltCheckResult(&result);
	ret |= CalibGetThreshold(&judge, 2);

	para->PlateErrVal = result.plate - para->GaugePara.PlateLen;
	para->InspAndProbCkResult.plate = result.plate;
	if (para->InspectionThreshold.plate < abs(para->PlateErrVal))
	{
		para->InspectionResultFg.plate = 1;
		para->CalibInspectJudge |= 1;
	}

	// 通常シーケンスにもどす
	HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ALIGNMENT_ING2;
	while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::ALIGNMENT_ING2)
	{
		Sleep(100);
	}
	////

	return (ret);
}


int CalibInspectMultiPlateStd::ParaOutCallBackSub(void)
{
	int ret = 0;

	ret |= CalibEnd();

	return (ret);

}