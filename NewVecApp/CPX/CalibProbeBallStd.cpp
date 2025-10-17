/***********************************************************************

    �n�ƑO�_���N���X

***********************************************************************/
#include    "CalibComm.h"
#include	"CalibProbeBallStd.h"

CALIB_DATA CalibProbeBallStd::m_ArmParaTxtBackUp;

int CalibProbeBallStd::InitSub(CALIB_MSEBOX* para)
{
	int ret = 0;


	switch (CalibComm::m_Language)
	{
	case LANGUAGE::JAPANESE:
		ret |= CalibInit(0, CALIB_MODE_SIMPLE_BALL);
		wcscpy_s(para->mes, 256, _T("�v���[�u�L�����u���[�V�������͂��߂܂�"));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\probeCalib_ja.png"));
		break;

	case LANGUAGE::ENBLISH:
		ret |= CalibInit(1, CALIB_MODE_SIMPLE_BALL);
		wcscpy_s(para->mes, 256, _T("Start User Calibration."));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\probeCalib_en.png"));
		break;

	default:
		wcscpy_s(para->mes, 256, _T("Unexpected events."));
		wcscpy_s(para->path, 128, _T(""));
		ret = 1;
		break;
	}


	return (ret);

}


int CalibProbeBallStd::StartSub(CALIB_MSEBOX* para)
{
	int ret = 0;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];


	// �߂��悤�Ƀo�b�N�A�b�v
	CalibProbeBallStd::m_ArmParaTxtBackUp = CalibComm::m_ArmParaTxt;
	
	if (HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 2 ||
		HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 1)
	{
		HwCtrl::m_hVecCnt.VecCmd_ChangeProbe(2); // PS=2�֋����ύX
	}
	else
	{
		para->MesString = 230;
		ret = 1;
	}
	
	return (ret);
}



int CalibProbeBallStd::CntDataMesCallBackSub(CALIB_MSEBOX* para)
{
	int ret = 0;

	VecCtEx2 CntData;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];

	int result;
	if (!CalibCalParaOut(&result, &CalibComm::m_ArmParaTxt, 2))	// PSID��2
	{
		para->CalibInspectJudge = 1;
		ret = 1;
	}
	else
	{
		para->CalibInspectJudge = 0;
	}
	para->CalibResultVal = result;

	// �L�����u�O�_������
	CalibCheckBallResult(&para->InspAndProbCkResult);	// ri, Ps


	// �ʏ�V�[�P���X�ɂ��ǂ�
	HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ALIGNMENT_ING2;
	while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::ALIGNMENT_ING2)
	{
		Sleep(100);
	}

	return (ret);
}



int CalibProbeBallStd::ParaOutCallBackSub(CALIB_MSEBOX* para)
{
	int ret = 0;
	int no = 0;
	int i = 0;
	CALIB_PAPA data;


	// ���ʃp�����[�^�]��
	if (para->CalibInspectJudge == 0)	// // OK�Ȃ�
	{
		HwCtrl::SetArmParaV8(&CalibComm::m_ArmParaTxt, 2);
	}

	ret |= CalibEnd();

	

	OutDataNo(&no);
	for (i = 0; i < no; i++)
	{
		OutCntData(i+1, &data);
		GetXYZData(i+1, &data);
	}

	// �L�����u��_������
	CalibCheckBallResult(&para->InspAndProbCkResult2);	// ri, Ps


	return (ret);

}


int CalibProbeBallStd::ClickResoreBtnSub(CALIB_MSEBOX* para)
{
	int ret = 0;

	HwCtrl::SetArmParaV8(&CalibComm::m_ArmParaTxt, 2);
	

	return (ret);

}