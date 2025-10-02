/***********************************************************************

	�_���A�L�����u�p�l������������Grop02�̎q�O���[�v

***********************************************************************/
#include	"CalibComm.h"
#include	"CalibUserMulti.h"
#include	"CalibInspectMultiNestStd.h"
#include	"CalibInspectMultiPlateStd.h"

CALIB_TYPE		CalibComm::m_CalibType;
LANGUAGE		CalibComm::m_Language;
CalibDataBuff	CalibComm::m_pData;
CALIB_DATA		CalibComm::m_ArmParaTxt;

/***********************************************************************

	�p�l����������
	�ɌĂԊ֐�

***********************************************************************/

int CalibComm::Init(CALIB_PARA* para, TCHAR*& path, int p_count, TCHAR*& mes, int m_count)
{
	int ret = 0;
	int lang = 0;
	int calmode = 0;

	CalibComm::m_Language = (LANGUAGE)para->Language;

	// DLL�̏�����
	ret = CalibSetPath("C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles");

	CalibComm::m_CalibType = (CALIB_TYPE)para->CalibType;
	switch (CalibComm::m_CalibType)
	{
		case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:
			ret |= CalibInspectMultiNestStd::InitSub(para);
			break;

		case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
			ret |= CalibUserMulti::InitSub(para);
			break;

		default:
			break;
	}

	// �Q�[�W�ݒ�̎擾
	ret |= CalibGetGaugeVal(&para->GaugePara);


	return (ret);
}


/***********************************************************************

	�J�n�{�^�����N���b�N���ꂽ�Ƃ���
	�ɌĂԊ֐�

***********************************************************************/
int CalibComm::Start(CALIB_PARA* para)
{
	int ret = 0;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];


	// ����f�[�^���o�b�t�@�ɓ��͉\�ɂ���
	if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::MEAS_IDLE)
	{
		HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::ALIGNMENT_REQ;
		while (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::ALIGNMENT_REQ)
		{
			Sleep(100);
			if (HwCtrl::m_VecStepSeq == VEC_STEP_SEQ::ALIGNMENT_ING)
			{
				break;
			}
		}
	}

	
	HwCtrl::Func09();	// �X�e�[�^�X�v��(���݂̃v���[�uID���m�肽��)
	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:
		ret |= CalibInspectMultiNestStd::StartSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
		ret |= CalibUserMulti::StartSub(para);
		break;

	default:
		break;
	}

	if (ret != 0)
	{
		goto exit;
	}

	// ����t���O�̏�����
	para->CalibInspectJudge = 0;
	// �Q�[�W�̒l�ݒ�
	CalibSetGaugeVal(para->GaugePara);

	// �������l�̎擾
	ret |= CalibGetThreshold(&para->ProbeCheckThreshold, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId);
	ret |= CalibGetThresholdCk(&para->InspectionThreshold);

	// �����p�����[�^�擾�E�ݒ�
	HwCtrl::GetArmParaV8(&CalibComm::m_ArmParaTxt, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId);
	CalibCalParaIn(&CalibComm::m_ArmParaTxt, HwCtrl::m_hVecCnt.m_Sts.m_iProbeId);

	// �f�[�^������
	CalibMesReset();
	CalibMesOutPath(path);
	CalibMesOutMesg(mesg1,mesg2);
	sprintf_s(mesg, 512, "%s\n%s", mesg1, mesg2);

	MultiByteToWideChar(CP_ACP, 0, path, -1, para->path, 128);
	MultiByteToWideChar(CP_ACP, 0, mesg, -1, para->mes, 256); 

exit:;
	return (ret);
}


/***********************************************************************

	�߂�{�^�����N���b�N���ꂽ�Ƃ���
	�ɌĂԊ֐�

***********************************************************************/
int CalibComm::Back(CALIB_PARA* para)
{
	int ret = 0;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];

	CalibMesBack();

	CalibMesOutPath(path);
	CalibMesOutMesg(mesg1, mesg2);
	sprintf_s(mesg, 512, "%s\n%s", mesg1, mesg2);
	MultiByteToWideChar(CP_ACP, 0, path, -1, para->path, 128);
	MultiByteToWideChar(CP_ACP, 0, mesg, -1, para->mes, 256);

	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:	

		break;

	case CALIB_TYPE::INSPECT_MULTI_GAUGE_PLATE_STD:

		break;

	case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:

		break;

	default:
		break;
	}



	return (ret);
}


/***********************************************************************

	���~�{�^�����N���b�N���ꂽ�Ƃ���
	�ɌĂԊ֐�

***********************************************************************/
int CalibComm::ReStart(CALIB_PARA* para)
{
	int ret = 0;
	char path[256];

	ret |= CalibEnd();

	CalibComm::m_CalibType = (CALIB_TYPE)para->CalibType;
	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:
		ret |= CalibInspectMultiNestStd::InitSub(para);
		break;

	case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
		ret |= CalibUserMulti::InitSub(para);
		break;

	default:
		break;
	}

	ret |= CalibGetGaugeVal(&para->GaugePara);


	return (ret);
}


/***********************************************************************

	���~�{�^�����N���b�N���ꂽ�Ƃ���
	�ɌĂԊ֐�

***********************************************************************/
int CalibComm::Close(CALIB_PARA* para)
{
	int ret = 0;

	ret |= CalibEnd();
	// �ʏ�V�[�P���X�ɂ��ǂ�
	HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
	while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::MEAS_IDLE)
	{
		Sleep(100);
	}
	////

	return (ret);
}



/***********************************************************************

	�`�悵�����摜�̃p�X���o��
	�ɌĂԊ֐�

***********************************************************************/
int CalibComm::GetDrawPath(TCHAR*& path, int count)
{
	int ret = 0;

	




	return (ret);
}



/***********************************************************************

	�\�����������b�Z�[�W�̕�������o��
	�ɌĂԊ֐�

***********************************************************************/
int CalibComm::GetMesString(TCHAR*& mes, int count)
{
	int ret = 0;






	return (ret);
}



/***********************************************************************

	�J�E���g�f�[�^������΃o�b�t�@�Ɋi�[��1��Ԃ�
	�ɌĂԊ֐�

***********************************************************************/
int CalibComm::CntDataInputThread(void)
{
	int ret = 0;
	int i = 0;

	VecCtEx2 CntData;
	i = HwCtrl::Func28(&CntData); // 2025.9.2 add eba 

	if ((CntData.button & 0x01) && (i == VEC_OK))
	{
		CalibComm::m_pData.PutData(CntData);
		ret = 1;
	}
	
	return (ret);
}



/***********************************************************************

	�J�E���g�f�[�^���L�����u�o�b�t�@�ɃC���v�b�g
	���肪�I�������A�L�����u

***********************************************************************/
int CalibComm::CntDataMesCallBack(CALIB_PARA* para)
{
	int ret = 0;
	int fg = 0;
	VecCtEx2 CntData;
	char path[256];
	char mesg[512], mesg1[256], mesg2[256];
	int result;

	CalibComm::m_pData.GetData(&CntData);

	// ����f�[�^�̃`�F�b�N
	if (CalibComm::m_CalibType == CALIB_TYPE::ALIGNMENT_MULTI_GAUGE)
	{
		fg = CalibUserMulti::CntDataMesCallBackSub2(para, &CntData);
		if(fg==0) CalibMesIn(&CntData);
	}
	else
	{
		CalibMesIn(&CntData);
	}

	CalibMesOutPath(path);
	CalibMesOutMesg(mesg1, mesg2);
	sprintf_s(mesg, 512, "%s\n%s", mesg1, mesg2);
	MultiByteToWideChar(CP_ACP, 0, path, -1, para->path, 128);
	MultiByteToWideChar(CP_ACP, 0, mesg, -1, para->mes, 256);
	
	int test = CalibMesCheck();
	if (test)
	{
		switch (CalibComm::m_CalibType)
		{
		case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:
			ret |= CalibInspectMultiNestStd::CntDataMesCallBackSub(para);
			break;

		case CALIB_TYPE::INSPECT_MULTI_GAUGE_PLATE_STD:
			ret |= CalibInspectMultiPlateStd::CntDataMesCallBackSub(para);
			break;

		case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
			ret |= CalibUserMulti::CntDataMesCallBackSub(para);
			break;

		default:
			break;
		}

	}

	return (ret);
}


/***********************************************************************

	�L�����u������������A�p�����[�^���A�[���ɓ]��
	�L�����u�A�_�����ʂ�C#�֓`�B

***********************************************************************/
int CalibComm::ParaOutCallBack(CALIB_PARA* para)
{
	int ret = 0;

	
	switch (CalibComm::m_CalibType)
	{
	case CALIB_TYPE::INSPECT_MULTI_GAUGE_NEST_STD:

		break;

	case CALIB_TYPE::ALIGNMENT_MULTI_GAUGE:
		
		ret = CalibUserMulti::ParaOutCallBackSub();

	default:
		break;
	}
	

	
	// �ʏ�V�[�P���X�ɂ��ǂ�
	HwCtrl::m_VecStepSeq = VEC_STEP_SEQ::MEAS_IDLE;
	while (HwCtrl::m_VecStepSeq != VEC_STEP_SEQ::MEAS_IDLE)
	{
		Sleep(100);
	}

	return (ret);
}


