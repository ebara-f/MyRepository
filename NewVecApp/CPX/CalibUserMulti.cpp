/***********************************************************************

    �n�ƑO�_���N���X

***********************************************************************/
#include    "CalibComm.h"
#include	"CalibUserMulti.h"



int CalibUserMulti::InitSub(CALIB_PARA* para)
{
	int ret = 0;


	switch (CalibComm::m_Language)
	{
	case LANGUAGE::JAPANESE:
		ret |= CalibInit(0, CALIB_MODE_USER);
		wcscpy_s(para->mes, 256, _T("���[�U�[�L�����u���[�V�������͂��߂܂�"));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\light_ja.png"));
		break;

	case LANGUAGE::ENBLISH:
		ret |= CalibInit(1, CALIB_MODE_USER);
		wcscpy_s(para->mes, 256, _T("Start User Calibration."));
		wcscpy_s(para->path, 128, _T("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\light_en.png"));
		break;

	default:
		wcscpy_s(para->mes, 256, _T("Unexpected events."));
		wcscpy_s(para->path, 128, _T(""));
		ret = 1;
		break;
	}


	return (ret);

}


int CalibUserMulti::StartSub(CALIB_PARA* para)
{
	int ret = 0;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];


	
	
	if (HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 2 ||
		HwCtrl::m_hVecCnt.m_Sts.m_iProbeId == 1)
	{
		// PS=1�֋����ύX
	}
	else
	{
		para->MesString = 1;	// 2025.9.21 ��
		ret = 1;
	}
	
	return (ret);
}



int CalibUserMulti::CntDataMesCallBackSub(CALIB_PARA* para)
{
	int ret = 0;

	VecCtEx2 CntData;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];

	int result;
	if (!CalibCalParaOut(&result, &CalibComm::m_ArmParaTxt, 1))	// ������PSID�͂P
	{
		ret = 1;
	}


	// �ʏ�V�[�P���X�ɂ��ǂ�
	HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
	while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::MEAS_IDLE)
	{
		Sleep(100);
		//if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::ALIGNMENT_ING2)
		//{
		//	break;
		//}
	}

	return (ret);
}



int CalibUserMulti::CntDataMesCallBackSub2(CALIB_PARA* para, VecCtEx2* data)
{
	int ret = 0;
	double radius;
	double height;
	double err;
	if (CalibMesPosChk(data, &radius, &height) == 0)
	{
		
		para->DataCheckFg.user_pos_err = 1;
		ret |= 1;
	}

	if (CalibMesErrChk(data, &err) == 0)
	{
		para->DataCheckFg.user_ball_err = 1;
		ret |= 2;
	}

	return (ret);
}




int CalibUserMulti::ParaOutCallBackSub(void)
{
	int ret = 0;

	// ���ʃp�����[�^�]��
	HwCtrl::SetArmParaV8(&CalibComm::m_ArmParaTxt, 2);
	ret |= CalibEnd();



	return (ret);

}