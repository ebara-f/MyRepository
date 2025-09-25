//---------------------------------------------------------------------------
//!	TdsData�w�b�_�[�t�@�C��
//!	@date	20170315	�V�K�쐬
//!	@date	20170331	�{�����[���ő�l�̒l���C���A�G���[�R�[�h�ǉ�
//!	@date	20170519	TdsVecExecMakeMatrix�֐��̈�����ǉ��A�G���[�R�[�h�ǉ�
//!	@date	20170620	�G���[�R�[�h�ǉ�
//!	@date	20210107	ApiScan�P�x�}�X�N�@�\���Ǌ֐���ǉ�
//!	@date	20220525	���Ȑf�f���[�^�[�`�F�b�N�@�\�̔�����@�ύX�ɔ���SelfChkMotorResult�֕ϐ���ǉ�
//!	@date	20230831	ApiScan�}�X�N�@�\�����Ή�
//---------------------------------------------------------------------------
#if !defined(__TdsData_h)
#define __TdsData_h

#ifdef EXPORT_DLL
#define	DLL_API	// __declspec( dllexport )
#else
#define	DLL_API	__declspec( dllimport )
#endif

//---------------------------------------------------------------------------
// ��`
//---------------------------------------------------------------------------
//! �v�����[�h
#define		TDS_MEASMODE_A					( 0x00 )		//!< Fh
#define		TDS_MEASMODE_B					( 0x01 )		//!< F
#define		TDS_MEASMODE_C					( 0x02 )		//!< D
#define		TDS_MEASMODE_D					( 0x03 )		//!< C+
#define		TDS_MEASMODE_E					( 0x04 )		//!< E
#define		TDS_MEASMODE_F					( 0x05 )		//!< -

//! �v�����x
#define		TDS_SENSITIVITY_0				( 0x00 )		//!< �W��
#define		TDS_SENSITIVITY_1				( 0x01 )		//!< �W��+1 PULS-G�����g�p�̏ꍇ�ɑI���ł��܂�
#define		TDS_SENSITIVITY_2				( 0x02 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_SENSITIVITY_3				( 0x03 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_SENSITIVITY_4				( 0x04 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_SENSITIVITY_5				( 0x05 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_SENSITIVITY_6				( 0x06 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_SENSITIVITY_7				( 0x07 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_SENSITIVITY_8				( 0x08 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������

//! �v���ȈՊ��x
#define		TDS_SIMPLESENS_0				( 0x00 )		//!< Normal
#define		TDS_SIMPLESENS_1				( 0x01 )		//!< High ApiScan�����g�p�̏ꍇ�ɑI���ł��܂�
#define		TDS_SIMPLESENS_2				( 0x02 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_SIMPLESENS_3				( 0x03 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_SIMPLESENS_4				( 0x04 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������

//! ���[�U�[�p���[
#define		TDS_LASERPOWER_1				( 0x00 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_LASERPOWER_2				( 0x01 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_LASERPOWER_3				( 0x02 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_LASERPOWER_4				( 0x03 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_LASERPOWER_5				( 0x04 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_LASERPOWER_6				( 0x05 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������
#define		TDS_LASERPOWER_FREE				( 0x06 )		//!< �g���p�̂��ߑI�����Ȃ��ł�������

//! �K�C�h���[�U�[�p���[
#define		TDS_GUIDEPOWER_0				( 0x00 )		//!< �� ApiScan�����g�p�̏ꍇ�ɑI���ł��܂�
#define		TDS_GUIDEPOWER_1				( 0x01 )		//!< �� ApiScan�����g�p�̏ꍇ�ɑI���ł��܂�
#define		TDS_GUIDEPOWER_2				( 0x02 )		//!< �� ApiScan�����g�p�̏ꍇ�ɑI���ł��܂�

//! �v���^�C�v
#define		TDS_MEASTYPE_NORMAL				( 0x00 )		//!< �ʏ푪�胂�[�h
#define		TDS_MEASTYPE_MACHINE_CHECK		( 0x01 )		//!< �n�ƑO�_�����[�h
#define		TDS_MEASTYPE_SELF_CHECK_SENS	( 0x02 )		//!< ���Ȑf�f���x�`�F�b�N���[�h
#define		TDS_MEASTYPE_CALIB_USER			( 0x03 )		//!< ���[�U�[�L�����u���[�V�������[�h
#define		TDS_MEASTYPE_CALIB_FULL			( 0x04 )		//!< �t���L�����u���[�V�������[�h
#define		TDS_MEASTYPE_CALIB_SPH_CHECK	( 0x05 )		//!< ���m�F�v�����[�h
#define		TDS_MEASTYPE_CALIB_PLN_CHECK	( 0x06 )		//!< �ʊm�F�v�����[�h
#define		TDS_MEASTYPE_CALIB_SPH_RECHECK	( 0x07 )		//!< ���m�F�v���Čv�Z
#define		TDS_MEASTYPE_CALIB_MAKE_OFB		( 0x08 )		//!< OFB�쐬���[�h(���g�p)
#define		TDS_MEASTYPE_CALIB_MAKE_TTB		( 0x09 )		//!< TTB�쐬���[�h(���g�p)

//! X�_�ԕ�ԃ��[�h
#define		TDS_INTERPOLATIONX_NONE			( 0x00 )		//!< X�_�ԕ�ԂȂ�
#define		TDS_INTERPOLATIONX_NINE			( 0x01 )		//!< X�_�ԕ�Ԃ��� ������� ApiScan�����g�p�̏ꍇ�ɑI���ł��܂�

//! �V�X�e���{�����[���ݒ�
#define		TDS_SYSTEMVOLUME_OFF			( 0x00 )		//!< �{�����[��OFF
#define		TDS_SYSTEMVOLUME_ON				( 0x01 )		//!< �{�����[��ON

//! �V�X�e���{�����[���ݒ艺�����
#define		TDS_SYSTEMVOLUME_MIN			( 0x00 )		//!< �{�����[���ŏ��l
#define		TDS_SYSTEMVOLUME_MAX			( 0xFF )		//!< �{�����[���ő�l

//! ���̑�
#define		TDS_NODATA						( 999999.0 )	//!< �_�f�[�^����

//! 2�s�[�N�}�X�N�ݒ�
#define		TDS_2PEAK_MASK_ENABLE			( 0x00 )		//!< �}�X�N�L��(�f�[�^������)
#define		TDS_2PEAK_MASK_DISABLE_WIDTH	( 0x01 )		//!< �}�X�N���� �g�`�����L�����̃f�[�^���擾
#define		TDS_2PEAK_MASK_DISABLE_NEAR		( 0x02 )		//!< �}�X�N���� ����(Z)���߂����̃f�[�^���擾

//---------------------------------------------------------------------------
// �\���̒�`
//---------------------------------------------------------------------------
// PulsData
typedef struct										//! 1�_���̃X�L���i�f�[�^���i�[���邽�߂̍\����
{
	int				lineNo ;						//!< �A�[���̂h�c
	int				measID ;						//!< �v����ʁi1=�ʏ�v���^0���_�~�[�v���j
	int				dataDisable[2];					//!< �v���f�[�^�̗L��=0/����=1
													//	[0] �����}�X�N�Ŗ������A1 �ƂȂ�
													//	[1] �P�x�}�X�N�Ŗ������A1 �ƂȂ�i���ݖ��g�p�j
													//	�����f�[�^�̏ꍇ�A������ 1 �ƂȂ�
	double			dataX ;							//!< X (999999.0 �̎��A�����f�[�^)
	double			dataY ;							//!< Y (999999.0 �̎��A�����f�[�^)
	double			dataZ ;							//!< Z (999999.0 �̎��A�����f�[�^)
	int				dataR ;							//!< �P�x
	int				dataS ;							//!< ���x
	int				dataLd;							//!< LD�h���C�u�d���l
}PulsData;

// PulsZMask
typedef struct										//! �����}�X�N�̐ݒ�l���i�[���邽�߂̍\����
{
	int				use[6][3][2];					//!< �}�X�N�g�p�̗L���i1=�g�p����^0=�g�p���Ȃ��j
	double			data[6][3][2];					//!< �}�X�N�ݒ�l
													//!< �f�[�^�z��̈Ӗ�	[�v�����[�h][XYZ][�ő�l/�ŏ��l]
													//!<	[�v�����[�h]	= 0�`�AA(Fh)�AB�AC�AD(C+)�AE�AF
													//!<	[XYZ]			= 0(X)�A1(Y)�A2(Z)
													//!<	[�ő�l/�ŏ��l]	= 0(�ő�l)�A1(�ŏ��l)
}PulsZMask;

// VecRet
typedef	struct										//! �x�N�g�����f�[�^���i�[���邽�߂̍\����
{
	int				no1;							//!< �f�[�^�v���ɑ΂��Ă̗v�����ꂽ���C���i���o�[
	int				no2;							//!< �f�[�^�v���A�X�e�[�^�X�v���ɑ΂��Ă̍ŐV�̃��C���i���o�[
	int				no3;							//!< �X�e�[�^�X�v���ɑ΂��Ă̍ŌÂ̗��p�\�ȃ��C���i���o�[
	double			xyz[3];							//!< �f�[�^�v���ɑ΂��Ă�XYZ
	double			ijk[3];							//!< �f�[�^�v���ɑ΂��Ă�IJK
	double			ijk2[3];						//!< �f�[�^�v���ɑ΂��Ă�I2J2K2
	int				error;							//!< �G���[�R�[�h �i���y�[�W�Q�Ɓj
	int				button;							//!< ����{�^���̏�� (ON:1 OFF:0)
	int				scan;							//!< �����ԁi�A�C�h����:0 �X�L������:1 ���̑�:2�j
	double			angle[7];						//!< �e���̊p�x([0]:7�� [1]�`[6]:1�`6��)
}VecRet;

// VecCtEx
typedef struct										//! ���W�n�쐬����1�_���̃x�N�g�����f�[�^���i�[���邽�߂̍\����
{
     int			no;								//!< �A�[�����C��No ��
     double			xyz[3];							//!< XYZ���W(mm)
     double			ijk[3];							//!< �A�[��1�����IJK(�P�ʃx�N�g��) ��
     double			ijk2[3];						//!< �A�[��7�����I2J2K2(�P�ʃx�N�g��) ��
     unsigned int	button;							//!< ����{�^���̏�� ON(=1)�AOFF(=0) ��
     long			cnt[9];							//!< �p�����[�^��
     int			er_code[9];						//!< �G���[�R�[�h��
     double			angle[7];						//!< �e���̊p�x(�x) ��
} VecCtEx;

// MakeMtxInfo
typedef struct										//! ���W�n�쐬�Ɋւ�������i�[����\����
{
     int			iPlnShotNum;					//!< ���ʑ��萔(�_�~�[����܂�)
     int			iAxisShotNum;					//!< �����萔(�_�~�[����܂�)
     int			iOriginShotNum;					//!< ���_�����萔
     int			iShotMax;						//!< ���萔(��L�̑��a)
} MakeMtxInfo;

// MakeMtxResult
typedef struct										//! ���W�n�쐬���ʂ��i�[����\����
{
     double			dMatrix[4][4];					//!< ���W�ϊ��}�g���N�X
     double			dSphere[3];						//!< ���̒��S���W {x,y,z}
} MakeMtxResult;

// CalibInfo
typedef struct										//! �L�����u���[�V�����Z�o���ʂ��i�[����\����
{
     int			iUserCalibShotNum;				//!< ���[�U�[�L�����u���[�V�����̃V���b�g��
     int			iFullCalibShotNum;				//!< �t���L�����u���[�V�����̃V���b�g��
     int			iFullCalibCalcuShotNum;			//!< �t���L�����u���[�V�����̌v�Z���s�ɕK�v�ȃV���b�g��
     int			iPlnCheckShotNum;				//!< �ʊm�F�v���̃V���b�g��
     int			iSphCheckShotNum;				//!< ���m�F�v���̃V���b�g��
     int			iMakeOfbShotNum;				//!< OFB�쐬�v���̃V���b�g��(���g�p)
     int			iMakeTtbShotNum;				//!< TTB�쐬�v���̃V���b�g��(���g�p)
} CalibInfo;

// SensorParam
typedef struct										//! �Z���T�p�����[�^���i�[����\����
{
     double			dSensorOffset[3];				//!< �Z���T�I�t�Z�b�g�lX,Y,Z (mm)
     double			dSensorTilt[3];					//!< �Z���T�`���g�lX,Y,Z (�x)
} SensorParam;

// ArmParam
typedef struct										//! �A�[���p�����[�^���i�[����\����
{
     double			dArmAddOffset[3];				//!< �A�[���I�t�Z�b�g���Z�lX,Y,Z (mm)
     double			dArmAddTilt[3];					//!< �A�[���`���g���Z�lX,Y,Z (�x)
} ArmParam;

// alibResult
typedef struct										//! �L�����u���[�V�����Z�o���ʂ��i�[����\����
{
     SensorParam	tSensorParam;					//!< �Z���T�p�����[�^
     ArmParam		tArmParam;						//!< �A�[���p�����[�^
     double			dResult[4][3];					//!< 4�����S���W����(�ʊm�F�v���̏ꍇ�͖ʖ@���x�N�g��)
} CalibResult;

// ChkScnInfo
typedef struct										//! �n�ƑO�_���Ɋւ�������i�[����\����
{
     int			iChkScnShotNum;					//!< �n�ƑO�_���̃V���b�g��

} ChkScnInfo;

// ChkScnResult
typedef struct										//! �n�ƑO�_���̌��ʂ��i�[���邽�߂̍\����
{
     short			sResult;						//!< OK(=1)�ANG(=0)
     double			dSph[4][4];						//!< 4�V���b�g���ꂼ��̋��d�S�Ƌ����a(mm)
     double			dSphMaxMin[3][2];				//!< ���d�S4�V���b�g����XYZ�̍ő�l�ƍŏ��l(mm)
     double			dPlnHeight[4];					//!< 4�V���b�g���ꂼ��̖ʍ���(mm)
     double			dPlnLength;						//!< �ʊԋ�����l(mm)
     double			dPlnLenDifference;				//!< �ʊԋ����덷�l(mm)
     int			iAverageR[4];					//!< 4�V���b�g���ꂼ��̕��ϋP�x
     int			iCheckBright;					//!< �P�x�`�F�b�N���� OK(=1)�ANG(=0)

} ChkScnResult;

// SelfChkLatchResult
typedef struct										//! ���Ȑf�f�̃��b�`�ʐM�`�F�b�N�̌��ʂ��i�[����\����
{
     int			iResult;						//!< OK(=1)�ANG(=0)
     int			iSendLatchCount;				//!< ���M�������b�`�M���̐�
     int			iRecvLatchCount;				//!< ��M�������b�`�M���̐�

} SelfChkLatchResult;

// SelfChkMotorResult
typedef struct										//! ���Ȑf�f�̃��[�^�[�`�F�b�N�̌��ʂ��i�[����\����
{
    int			iResult;						//!< OK(=1)�ANG(=0)
    int			iSensorPlus;					//!< ���[�^�[���v���X�����ֈړ������ۂ̃Z���T�p���X��
    int			iControllerPlus;				//!< ���[�^�[���v���X�����ֈړ������ۂ̃R���g���[���p���X��
    int			iSensorMinus;					//!< ���[�^�[���}�C�i�X�����ֈړ������ۂ̃Z���T�p���X��
    int			iControllerMinus;				//!< ���[�^�[���}�C�i�X�����ֈړ������ۂ̃R���g���[���p���X��
    int			iBaseMove;						//!< ���[�^�[�ړ��ʊ�l (ApiScan�̏ꍇ200�APULS-G�̏ꍇ100)
    int			iSensorMovePlus;				//!< ���[�^�[���v���X�����ֈړ������ۂ̃Z���T�ړ���
    int			iControllerMovePlus;			//!< ���[�^�[���v���X�����ֈړ������ۂ̃R���g���[���ړ���
    int			iSensorMoveMinus;				//!< ���[�^�[���}�C�i�X�����ֈړ������ۂ̃Z���T�ړ���
    int			iControllerMoveMinus;			//!< ���[�^�[���}�C�i�X�����ֈړ������ۂ̃R���g���[���ړ���

} SelfChkMotorResult;

// SelfChkSensResult
typedef struct										//! ���Ȑf�f�̊��x�`�F�b�N�̌��ʂ��i�[����\����
{
     int			iResult;						//!< OK(=1)�ANG(=0)
     int			iBaseBright;					//!< ��P�x
     int			iResultBright;					//!< ���ϋP�x(���茋��)
     double			dThreshold;						//!< ���e�l(%)

} SelfChkSensResult;

// VecGaugeIni
typedef struct										//! �Q�[�W������i�[����\���� (vecgauge.ini�t�@�C���̃p�����[�^)
{
     int			iGaugeType;						//!< �}���`�Q�[�W�I��ԍ�
     char			szGaugeName[256];				//!< �}���`�Q�[�W�^��
     double			dSphDiameter;					//!< �}���`�Q�[�W���a(mm)
     double			dPlnLengthPnt[4][3];			//!< �}���`�Q�[�W�ʊԋ����p�̓_�Q���o�|�C���g(mm)(�}���`�Q�[�W���ʂ̊e�ʂ�XYZ���W)
} VecGaugeIni;

// SensorSettingIni
typedef struct										//! �n�ƑO�_���̐ݒ���i�[����\���̂ł��BSensorSetting.ini�t�@�C���̃p�����[�^�ł��B
{
     double			dCenterScopePnt[3];				//!< �����S���W (mm) (0,0,0�Œ�)
     double			dPlaneScopePnt[4][3];			//!< �ʍ����p�̓_�Q���o�|�C���g(mm)
     double			dPlaneScopeRad;					//!< �ʍ����p�̓_�Q���o�����a(mm)
     double			dLengthScopeRad;				//!< �ʊԋ����p�̓_�Q���o�����a(mm)
     int			iLengthScopeRadCnt;				//!< �ʊԋ����p�̓_�Q���o����
     double			dCenterLimit;					//!< �����S���W ���苖�e�l
     double			dPlaneHeightLimit;				//!< �ʍ��� ���苖�e�l
     double			dPlaneLengthLimit;				//!< �ʊԋ��� ���苖�e�l
     int			iPlaneHeightMeasPntMin;			//!< �ʍ������莞�̓_�������l
     int			iPlaneLengthMeasPntMin;			//!< �ʊԋ������莞�̓_�������l
     int			iBrightBase;					//!< �}���`�Q�[�W���莞�̊�P�x
     double			dBrightLimit;					//!< �P�x�`�F�b�N�̔��苖�e�l (��Ƃ���80%�̏ꍇ��0.8��ݒ�)
} SensorSettingIni;


//---------------------------------------------------------------------------
// �G���[�R�[�h��`
//---------------------------------------------------------------------------
#define		TDS_ERR_NONE					( 0 )	// ����
#define		TDS_ERR_PARAMETER				( 1 )	// �p�����[�^�G���[
#define		TDS_ERR_SCANNER_CONTROL			( 2 )	// �X�L���i����G���[
#define		TDS_ERR_GET_POINT_DATA			( 3 )	// �X�L���i�_�Q�f�[�^�擾�G���[
#define		TDS_ERR_NOT_INITIALIZE			( 4 )	// ���������G���[

#define		TDS_ERR_CALIB_SHOT_DATA_HALF	( 10 )	// �_�Q���G���[(�_�Q�������ȉ�)
#define		TDS_ERR_CALIB_SHOT_AXIS			( 11 )	// ���W�n�G���[
#define		TDS_ERR_CALIB_SHOT_NEAR			( 12 )	// �v���������߂�����
#define		TDS_ERR_CALIB_SHOT_FAR			( 13 )	// �v����������������
#define		TDS_ERR_CALIB_SHOT_NO_DATA		( 14 )	// �_�Q�擾���s
#define		TDS_ERR_CALIB_SHOT_1AXIS		( 15 )	// 1���p�x�G���[
#define		TDS_ERR_CALIB_SHOT_7AXIS		( 16 )	// 7���p�x�G���[
#define		TDS_ERR_CALIB_SHOT_DATA_LACK	( 17 )	// �_�Q�����G���[
#define		TDS_ERR_CALIB_SHOT_MAKE_SPH		( 18 )	// ���쐬���s
#define		TDS_ERR_CALIB_SHOT_2AXIS		( 19 )	// 2���p�x�G���[

#define		TDS_ERR_CALIB_SHOT_MAKE_PLN		( 20 )	// �ʍ쐬���s

#define		TDS_ERR_CALIB_CALCULATE			( 30 )	// �L�����u���[�V�����l�쐬���s
#define		TDS_ERR_CALIB_NO_CHANGE			( 31 )	// �L�����u���[�V�����l�ύX�Ȃ�
#define		TDS_ERR_CALIB_CHANGE_OVER		( 32 )	// �L�����u���[�V�����l�ω��ʃI�[�o�[�G���[
//#define	TDS_ERR_HOLDER_CHANGE_OVER		( 33 )	// �z���_�萔�l�ω��ʃI�[�o�[�G���[ ->��ʃA�v���ɂă`�F�b�N���Ă�������(�z���_�萔�ω��ʃI�[�o�[�G���[�̏ꍇ�ł��L�����u�l�͕ۑ�����d�l�ł�)
#define		TDS_ERR_CALIB_CALC_SHOT			( 34 )	// �L�����u���[�V�����v�Z�����s����V���b�gNo�łȂ�

#define		TDS_ERR_MACHINECHECK_DATA_LACK	( 40 )	// �n�ƑO�_�� �ʌv���_���G���[(���e�l�ݒ�������Ȃ�)
#define		TDS_ERR_MACHINECHECK_FILE_OUT	( 41 )	// �n�ƑO�_�� ���ʃ��O�t�@�C���o�͎��s

#define		TDS_ERR_DATA_ALLOC				( 50 )	// �_�Q�f�[�^�p�������m�ێ��s
#define		TDS_ERR_DATA_LINE_NO			( 51 )	// ���C��No�ُ�

#define		TDS_ERR_MAKE_MTX_PLN			( 60 )	// ���W�n�쐬 �ʍ쐬���s
#define		TDS_ERR_MAKE_MTX_AXS			( 61 )	// ���W�n�쐬 ���쐬���s
#define		TDS_ERR_MAKE_MTX_OGN			( 62 )	// ���W�n�쐬 ���_�쐬���s

#define		TDS_ERR_SELF_CHK_LATCH_START	( 70 )	// ���Ȑf�f ���Ƀ��b�`���M���J�n����Ă���

//---------------------------------------------------------------------------
// �֐���`
//---------------------------------------------------------------------------
extern "C"
{
//===========================================================================
//	�������֐�
//===========================================================================

//---------------------------------------------------------------------------
//!	INI�t�@�C�����o�͂���t�H���_�[�̃p�X��ݒ肵�܂��B
//  
//!	@param	szPath		(IN)		�t�H���_�[�p�X
//  
//!			�������֐����R�[������O�Ɏg�p���Ă��������B
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecSetIniFilePath( char* szPath );

//---------------------------------------------------------------------------
//!	INI�t�@�C�����o�͂���t�H���_�[�̃p�X���擾���܂��B
//  
//!	@param	szPath		(OUT)		�t�H���_�[�p�X
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetIniFilePath( char* szPath );

//---------------------------------------------------------------------------
//!	���O�t�@�C�����o�͂���t�H���_�[�̃p�X��ݒ肵�܂��B
//  
//!	@param	szPath		(IN)		�t�H���_�[�p�X
//  
//!			�������֐����R�[������O�Ɏg�p���Ă��������B
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecSetLogFilePath( char* szPath );

//---------------------------------------------------------------------------
//!	���O�t�@�C�����o�͂���t�H���_�[�̃p�X���擾���܂��B
//  
//!	@param	szPath		(OUT)		�t�H���_�[�p�X
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetLogFilePath( char* szPath );

//---------------------------------------------------------------------------
//!	�������֐�
//  
//!	@return	�ُ폈��(LAN�ڑ����s)(=0)�A ���폈��(�X�L���i�[�ڑ��悠��)(=1)�A ���폈��(�X�L���i�[�ڑ���Ȃ�)(=2)
//---------------------------------------------------------------------------
DLL_API int WINAPI TdsVecMeasInit();

//---------------------------------------------------------------------------
//!	�I���p�֐�
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecMeasExit();

//---------------------------------------------------------------------------
//! ���C�u�����փX�L���i�R���g���[����IP�A�h���X��ݒ肵�܂��B
//  
//! @param dwAdrs	(IN) �R���g���[����IP�A�h���X(HEX)
//
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecSetControllerAddress( DWORD dwAdrs );

//---------------------------------------------------------------------------
//! �R���g���[���̃l�b�g���[�N�ݒ��ύX���܂��B
//  
//! @param	dwAdrs		(IN)	IP�A�h���X(HEX)
//! @param	dwMask		(IN)	�T�u�l�b�g�}�X�N(HEX)
//! @param	dwGateway	(IN)	Gateway�A�h���X(HEX)
//! @param	dwDNS		(IN)	DNS�T�[�o�[�A�h���X(HEX)
//
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecConfigControllerAddressSetting( DWORD dwAdrs, DWORD dwMask, DWORD dwGateway,  DWORD dwDNS );

//---------------------------------------------------------------------------
//! �x�N�g�����t�@�[���̃o�[�W������ݒ肵�܂��B
//  
//! @param	iVersion	(IN)	�x�N�g�����t�@�[���̃o�[�W����
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecSetArmVersion( int iVersion );


//===========================================================================
//	�v���ݒ�֐�
//===========================================================================
//---------------------------------------------------------------------------
//!	�v�����[�h��ύX���܂��B
//  
//!	@param	iMode		(IN)	�ݒ肷��v�����[�h
//
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecChangeMode( int iMode );

//---------------------------------------------------------------------------
//! ���݂̌v�����[�h�̃|�C���g���Ɠ_�ԃs�b�`���擾���܂��B
//  
//! @param	piXnum		(OUT)	1���C���̃|�C���g�����i�[����ϐ��̃|�C���^
//! @param	pdXPitch	(OUT)	�_�ԃs�b�`(mm)���i�[����ϐ��̃|�C���^
//  
//! @return	 	���݂̌v�����[�h(0�`5)
//---------------------------------------------------------------------------
DLL_API int WINAPI TdsVecGetMode( int* piXnum, double* pdXPitch );

//---------------------------------------------------------------------------
//! �v�����x��ύX���܂��B
//  
//! @param	iSens	(IN)	�ݒ肷��v�����x
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecChangeSens( int iSens );

//---------------------------------------------------------------------------
//! �v���ȈՊ��x��ύX���܂��B
//  
//! @param	iSimpleSens	(IN)	�ݒ肷��v���ȈՊ��x
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
 DLL_API BOOL WINAPI TdsVecChangeSimpleSens( int iSimpleSens );

//---------------------------------------------------------------------------
//! �����}�X�N�p�����[�^�̐ݒ���s���܂��B
//  
//! @param	iSn		(IN)	�X�L���i�ԍ�(=0)
//! @param	ptZMask	(IN)	�����}�X�N�p�����[�^�\���̂̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecZMaskSet( int iSn, PulsZMask* ptZMask );

//---------------------------------------------------------------------------
//! �����}�X�N�p�����[�^�̎擾���s���܂��B
//  
//! @param	iSn		(IN)	�X�L���i�ԍ�(=0)
//! @param	ptZMask	(OUT)	�����}�X�N�p�����[�^���i�[����\���̂̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecZMaskGet( int iSn, PulsZMask* ptZMask );

//---------------------------------------------------------------------------
//! �����}�X�N�̗L��/������ݒ肵�܂��B
//  
//! @param	 bEnable	(IN)	�����}�X�N�L��(=TRUE)�A����(=FALSE)
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecSetZMaskEnable( BOOL bEnable );	

//---------------------------------------------------------------------------
//! �����}�X�N�̗L��/�������擾���܂��B
//  
//! @param	 bEnable	(OUT)	�����}�X�N�L��(=TRUE)�A����(=FALSE)
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetZMaskEnable( BOOL* pbEnable );	

//---------------------------------------------------------------------------
//! �v���^�C�v��ݒ肵�܂��B
//  
//! @param	iMeasType	(IN)	�ݒ肷��v���^�C�v
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecSetMeasType( int iMeasType );

//---------------------------------------------------------------------------
//! �v���^�C�v���擾���܂��B
//  
//! @param	piMeasType	(OUT)	�v���^�C�v���i�[����ϐ��ւ̃|�C���^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetMeasType( int* piMeasType );

//---------------------------------------------------------------------------
//! �K�C�h���[�U�[�̃p���[��ݒ肵�܂��B
//  
//! @param	iGuideLaserPow	(IN)	�ݒ肷��K�C�h���[�U�[�p���[
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecSetGuideLaserPower( int iGuideLaserPow );

//---------------------------------------------------------------------------
//! �K�C�h���[�U�[�̃p���[���擾���܂��B
//  
//! @param	piGuideLaserPow	(OUT)	�K�C�h���[�U�[�p���[���i�[����ϐ��ւ̃|�C���^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetGuideLaserPower( int* piGuideLaserPow );

//---------------------------------------------------------------------------
//! X�_�ԕ�ԃ��[�h��ݒ肵�܂��B
//  
//! @param	iInterpolation	(IN)	�ݒ肷��X�_�ԕ�ԃ��[�h
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecSetInterpolationX( int iInterpolation );

//---------------------------------------------------------------------------
//! X�_�ԕ�ԃ��[�h���擾���܂��B
//  
//! @param	piInterpolation	(OUT)	X�_�ԕ�ԃ��[�h���i�[����ϐ��ւ̃|�C���^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetInterpolationX( int* piInterpolation );

//---------------------------------------------------------------------------
//! �V�X�e���{�����[����ݒ肵�܂��B
//  
//! @param	iSetting	(IN)	�V�X�e���{�����[���ݒ�
//! @param	iVolume		(IN)	�X�s�[�J����
//  
//! @return		 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecSetSystemVolume( int iSetting, int iVolume );


//===========================================================================
//	�v���֐�
//===========================================================================
//---------------------------------------------------------------------------
//! �_�~�[�X�L�������J�n���܂��B
//  
//! @param	iSn	(IN)	�X�L���i�ԍ�(=0)
//! @param	iSw	(IN)	�G���[����(=0) 
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecDummyScanStart( int iSn, int iSw = 0 );

//---------------------------------------------------------------------------
//! �X�L�������J�n���܂��B
//  
//! @param	iSn	(IN)	�X�L���i�ԍ�(=0)
//! @param	iSw	(IN)	�G���[����(=0)
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecScanStart( int iSn, int iSw = 0 );

//---------------------------------------------------------------------------
//! �X�L�������I�����܂��B
//  
//! @param	iSn	(IN)	�X�L���i�ԍ�(=0)
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecScanStop( int iSn );

//---------------------------------------------------------------------------
//! ���Z�b�g�������s���܂��B
//  
//! @param	iSn	(IN)	�X�L���i�ԍ�(=0)
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
 DLL_API BOOL WINAPI TdsVecMeasReset( int iSn );

//---------------------------------------------------------------------------
//! �x�N�g�����̍ŏ���1�_�����C�u�����֐ݒ肵�܂��B
//  
//! @param	ptVecData	(IN)	�x�N�g�����f�[�^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVec1stPnt( VecRet* ptVecData );

//---------------------------------------------------------------------------
//! �w�肵�����C��No�̃X�L���i�f�[�^�����݂��邩�₢���킹�܂��B
//  
//! @param	iLineNo	(IN)	���C��No
//  
//! @return	 �X�L���i�f�[�^�̑��݃X�e�[�^�X
//!			 ����(��萔�f�[�^��������Ԃ�����������LAN�؂�G���[�Ƃ���)(=-3)
//!			 ����(���̃��C�������݂��邽�߁A���C�������G���[)(=-2)
//!			 ����(�f�[�^��M�҂�)(=-1)
//!			 ����(�A����M���̉\������)(=0)
//!			 ����(���̃��C�������݂��邽�ߎ�M�������Ă�����)(=1)
//---------------------------------------------------------------------------
DLL_API int WINAPI TdsIsLineExist( int iLineNo );

//---------------------------------------------------------------------------
//! �x�N�g�����̎���1�_�����C�u�����֐ݒ肵�A1���C�����̃X�L���i�f�[�^���擾���܂��B
//  
//! @param	ptVecData	(IN)	�x�N�g�����f�[�^�\���̂̃|�C���^
//! @param	ptPulsData	(OUT)	�X�L���i�f�[�^���i�[����\���̂̃|�C���^
//! @param	iBuffNum	(IN)	�f�[�^�o�b�t�@�ő吔
//! @param	piDataNum	(OUT)	�i�[�����f�[�^�����i�[����ϐ��̃|�C���^
//  
//! @return	 	�_��
//---------------------------------------------------------------------------
DLL_API int WINAPI TdsVecAndMeas( VecRet* ptVecData, PulsData* ptPulsData, int iBuffNum, int* piDataNum );

//---------------------------------------------------------------------------
//! 1���C�����̃X�L���i���[�J���f�[�^���擾���܂��B
//  
//! @param	iLineNo		(IN)	�擾����f�[�^�̃��C��No
//! @param	ptPulsData	(OUT)	�X�L���i�f�[�^���i�[����\���̂̃|�C���^
//! @param	iBuffNum	(IN)	�f�[�^�o�b�t�@�ő吔
//! @param	piDataNum	(OUT)	�i�[�����f�[�^�����i�[����ϐ��̃|�C���^
//  
//! @return	 	�_��
//---------------------------------------------------------------------------
DLL_API int WINAPI TdsVecGetLocalData( int iLineNo, PulsData* ptPulsData, int iBuffNum, int* piDataNum );


//===========================================================================
//	���̑��X�L���i����֐�
//===========================================================================
//---------------------------------------------------------------------------
//! �X�L���i�ւ̓d��������ON���܂��B
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecScannerPowerOn();

//---------------------------------------------------------------------------
//! �X�L���i�ւ̓d��������OFF���܂��B
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecScannerPowerOff();

//---------------------------------------------------------------------------
//! �R���g���[���̃f�[�^�o�b�t�@���N���A���܂��B
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecBufferClear();


//===========================================================================
//	���擾�֐�
//===========================================================================
//---------------------------------------------------------------------------
//! �X�L���i���T�u�t�@�[���E�F�A�ŋN�����Ă��Ȃ����m�F���܂��B
//  
//! @param	pbSensorFirm	(OUT)	�Z���T�T�u�t�@�[���N�������i�[����ϐ��̃|�C���^
//! @param	pbSensorFpga	(OUT)	�Z���T�T�uFPGA�N�������i�[����ϐ��̃|�C���^
//! @param	pbCtrlFirm		(OUT)	�R���g���[���T�u�t�@�[���N�������i�[����ϐ��̃|�C���^
//! @param	pbCtrlFpga		(OUT)	�R���g���[���T�uFPGA�N�������i�[����ϐ��̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecIsSubFirmware( BOOL* pbSensorFirm, BOOL* pbSensorFpga, BOOL* pbCtrlFirm, BOOL* pbCtrlFpga );

//---------------------------------------------------------------------------
//! �Z���TROM�p�����[�^�̓ǂݍ��ݏ�Ԃ��擾���܂��B
//  
//! @return	 	�p�����[�^�ǂݍ��݃X�e�[�^�X
//				�ǂݍ��ݎ��s(=-1)�A���ǂݍ���(=-0)�A�ǂݍ��ݐ���(=1)�A�ǂݍ��ݒ�(=2)
//---------------------------------------------------------------------------
DLL_API int WINAPI TdsVecGetEepromReadFlg();

//---------------------------------------------------------------------------
//! �v�����[�h�̗L��/�������A���[�h���̂��擾���܂��B
//  
//! @param	iUse	(OUT)	�v�����[�h�̗L��(=1)/����(=0)
//! 						��) iUse[ 4 ] = 1		E���[�h���L��
//! @param	szName	(OUT)	���[�h���� (�ő�50����)
//! 						[�v�����[�hNo][�v�����[�h���̕���]
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetAllModeName( int iUse[ 6 ], char szName[ 6 ][ 50 ] );

//---------------------------------------------------------------------------
//! �v�����x�̗L��/���������擾���܂��B
//  
//! @param	iUse	(OUT)	�v�����x�̗L��(=1)/����(=0)
//! 						��) iUse[ 1 ] = 1		���x1(�W��+1)���L��
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetAllSens( int iUse[ 9 ] );

//---------------------------------------------------------------------------
//! �v���ȈՊ��x�̗L��/�������A���̂��擾���܂��B
//  
//! @param	iUse	(OUT)	�v���ȈՊ��x�̗L��(=1)/����(=0)
//! 						��) iUse[ 1 ] = 1		�ȈՊ��x1(High)���L��
//! @param	szName	(OUT)	�ȈՊ��x���� (�ő�50����)
//! 						[�ȈՊ��xNo][�ȈՊ��x���̕���]
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetAllSimpleSensName( int iUse[ 5 ], char szName[ 5 ][ 50 ] );

//---------------------------------------------------------------------------
//! �X�L���i�̃X�e�[�^�X���擾���܂��B
//  
//! @param	pbExist		(OUT)	�X�L���i�ڑ��X�e�[�^�X���i�[����ϐ��̃|�C���^
//! 							�X�L���i�ڑ�����(=TRUE)�A�ڑ�����(=FALSE)
//! @param	pbConnect	(OUT)	�X�L���i�ڑ���X�e�[�^�X���i�[����ϐ��̃|�C���^
//! 							�ڑ���x�N�g����(=TRUE)�A�g�@���j�b�g(=FALSE)
//! @param	pbWarmup	(OUT)	�g�@�X�e�[�^�X���i�[����ϐ��̃|�C���^
//! 							�g�@����(=TRUE)�A�g�@��(=FALSE)
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecScannerStatus( BOOL* pbExist, BOOL* pbConnect, BOOL* pbWarmup );

//---------------------------------------------------------------------------
//! �Z���T�X�C�b�`1�̏���Ԃ��܂��B
//  
//! @return	 	ON(=1)�AOFF�܂��̓N���A�����܂�(=0)
//---------------------------------------------------------------------------
DLL_API int WINAPI TdsSw1Get();

//---------------------------------------------------------------------------
//! �Z���T�X�C�b�`2�̏���Ԃ��܂��B
//  
//! @return	 	ON(=1)�AOFF�܂��̓N���A�����܂�(=0)
//---------------------------------------------------------------------------
DLL_API int WINAPI TdsSw2Get();

//---------------------------------------------------------------------------
//! �Z���T�X�C�b�`3�̏���Ԃ��܂��B
//  
//! @return	 	ON(=1)�AOFF�܂��̓N���A�����܂�(=0)
//---------------------------------------------------------------------------
DLL_API int WINAPI TdsSw3Get();

//---------------------------------------------------------------------------
//! �Z���T�X�C�b�`4�̏���Ԃ��܂��B
//  
//! @return	 	ON(=1)�AOFF�܂��̓N���A�����܂�(=0)
//---------------------------------------------------------------------------
DLL_API int WINAPI TdsSw4Get();

//---------------------------------------------------------------------------
//! �R���g���[���̃f�[�^�o�b�t�@�̏�Ԃ��擾���܂��B
//  
//! @param	pbFull	(OUT)	�o�b�t�@�t���X�e�[�^�X���i�[����ϐ��̃|�C���^
//! 						�o�b�t�@�t��(=TRUE)�A�o�b�t�@�󂫂���(=FALSE)
//! @param	pbEmpty	(OUT)	�o�b�t�@�G���v�e�B�X�e�[�^�X���i�[����ϐ��̃|�C���^
//! 						�o�b�t�@����ɂȂ���(=TRUE)�A�o�b�t�@�փf�[�^����(=FALSE)
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecBufferStatus( BOOL* pbFull, BOOL* pbEmpty );

//---------------------------------------------------------------------------
//! �Z���T�̉��x���擾���܂��B
//  
//! @param	pdTemp	(OUT)	���x���i�[����ϐ��̃|�C���^
//  
//! @return	 	���폈��(=0)�A�ُ폈��(=0�ȊO)
//---------------------------------------------------------------------------
DLL_API int WINAPI TdsVecGetTemperature( double* pdTemp );

//---------------------------------------------------------------------------
//! �Z���T�̃o�[�W���������擾���܂��B
//  
//! @param	pszSerial	(OUT)	�Z���T�V���A���ԍ� (12����)
//! @param	pszFirmware	(OUT)	�Z���T�t�@�[���E�F�A�̃o�[�W����(4����)
//! @param	pszFPGA		(OUT)	�Z���TFPGA�̃o�[�W����(4����)
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecGetSensorVersion( char* pszSerial, char* pszFirmware, char* pszFPGA );

//---------------------------------------------------------------------------
//! �R���g���[���̃o�[�W���������擾���܂��B
//  
//! @param	pszSerial	(OUT)	���i����(10����)
//! @param	pszFirmware	(OUT)	�R���g���[���t�@�[���E�F�A�̃o�[�W����(�ő�32����)
//! @param	pszMacID	(OUT)	MAC-ID�̃��x��(19����)
//! @param	pszFPGA		(OUT)	�R���g���[��FPGA�̃o�[�W����(22����)
//! @param	pszAvr32	(OUT)	AVR32�̃o�[�W����(42����)
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecGetControllerVersion( char* pszName, char* pszFirmware,  char* pszMacID, char* pszFPGA, char* pszAvr32 );

//---------------------------------------------------------------------------
//! �G���[�R�[�h��Ԃ��܂��B
//  
//! @return	 	�G���[�R�[�h
//---------------------------------------------------------------------------
DLL_API int WINAPI TdsVecErrorCode();


//===========================================================================
//	���W�n�쐬��p�֐�
//===========================================================================
//---------------------------------------------------------------------------
//! ���W�n�쐬�̎��s�ɕK�v�ȏ����擾���܂��B
//  
//! @param	ptInfo	(OUT)	���W�n�쐬�̏����i�[����\���̂̃|�C���^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetMakeMatrixInfo( MakeMtxInfo* ptInfo );

//---------------------------------------------------------------------------
//! ���W�n�쐬���̃A�[���_�f�[�^��ݒ肵�܂��B
//  
//! @param	iShotNo		(IN)	���W�n�쐬�̃V���b�gNo (0�`)
//! @param	ptVecCtEx	(IN)	�A�[���_�f�[�^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecSetMakeMatrixData( int iShotNo, VecCtEx* ptVecCtEx );

//---------------------------------------------------------------------------
//! ���W�n�쐬�̌��ʎZ�o�����s���܂��B
// 
//!	@param	dProbBall	(IN)	�ڐG���{�[���v���[�u�̒��a
//! @param	ptResult	(OUT) 	���W�n�쐬���ʂ��i�[����\���̂̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecExecMakeMatrix( double dProbBall, MakeMtxResult* ptResult );

//---------------------------------------------------------------------------
//! ���W�n��ݒ肵�܂��B
//  
//! @param	pdMtx[4][4]	(IN) 	���W�n���i�[�����z��
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecSetMatrix( double pdMtx[4][4] );

//---------------------------------------------------------------------------
//! ���W�n���擾���܂��B
//  
//! @param	ptMtx[4][4]	(OUT) 	���W�n���i�[����z��
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetMatrix( double pdMtx[4][4] );

//---------------------------------------------------------------------------
//! �n�ƑO�_���Ŏg�p���鋅�̒��S���W��ݒ肵�܂��B
//  
//! @param	pdSph[3]	(IN) 	�����S���W���i�[�����z��
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecSetSphCod( double pdSph[3] );

//---------------------------------------------------------------------------
//! �n�ƑO�_���Ŏg�p���鋅�̒��S���W���擾���܂��B
//  
//! @param	pdSph[3]	(OUT) 	�����S���W���i�[����z��
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetSphCod( double pdSph[3] );


//===========================================================================
//	�L�����u���[�V�����A�n�ƑO�_�����ʊ֐�
//===========================================================================
//---------------------------------------------------------------------------
//! �L�����u���[�V�����܂��͎n�ƑO�_�����s���ꍇ�̌��݂̃V���b�gNo��ݒ肵�܂��B
//  
//! @param	iShotNo	(IN)	�V���b�g�ԍ�
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecSetShotNum( int iShotNo );

//---------------------------------------------------------------------------
//! �L�����u���[�V�����܂��͎n�ƑO�_���̑��肵���_�Q�f�[�^���������ݒ肳�ꂽ�����m�F���܂��B
//  
//! @param	iShotNo	(IN)	�V���b�g�ԍ�
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecCheckCalibData( int iShotNo );


//===========================================================================
//	�L�����u���[�V������p�֐�
//===========================================================================
//---------------------------------------------------------------------------
//! �L�����u���[�V�����̎��s�ɕK�v�ȏ����擾���܂��B
//  
//! @param	ptInfo	(OUT)	�L�����u���[�V�����̏����i�[����\���̂̃|�C���^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetCalibInfo( CalibInfo* ptInfo );

//---------------------------------------------------------------------------
//! �L�����u���[�V�����e�V���b�g�̃f�[�^��OK/NG������s��/�s��Ȃ��t���O��ݒ肵�܂��B
//  
//! @param	bDataCheck	(IN)	�f�[�^��OK/NG������s��/�s��Ȃ��t���O
//!								������s��(=TRUE)�A������s��Ȃ�(=FALSE)
//---------------------------------------------------------------------------
//DLL_API void WINAPI TdsVecSetDataCheckFlag( BOOL bDataCheck );

//---------------------------------------------------------------------------
//! �L�����u���[�V�����e�V���b�g�̃f�[�^��OK/NG������s��/�s��Ȃ��t���O���擾���܂��B
//  
//! @param	pbDataCheck	(OUT)	�f�[�^��OK/NG������s��/�s��Ȃ��t���O���i�[����ϐ��̃|�C���^
//!								������s��(=TRUE)�A������s��Ȃ�(=FALSE)
//---------------------------------------------------------------------------
//DLL_API void WINAPI TdsVecGetDataCheckFlag( BOOL* pbDataCheck );

//---------------------------------------------------------------------------
//! �L�����u���[�V�����v�Z���Ƀp�����[�^�e�[�u���̒������s��/�s��Ȃ��t���O��ݒ肵�܂��B
//  
//! @param	bZtableAdj	(IN)	�p�����[�^�e�[�u���̒������s��/�s��Ȃ��t���O
//!								�������s��(=TRUE)�A�������s��Ȃ�(=FALSE)
//---------------------------------------------------------------------------
//DLL_API void WINAPI TdsVecSetZTableAdjFlag( BOOL bZtableAdj );

//---------------------------------------------------------------------------
//! �L�����u���[�V�����v�Z���Ƀp�����[�^�e�[�u���̒������s��/�s��Ȃ��t���O���擾���܂��B
//  
//! @param	bZtableAdj	(OUT)	�p�����[�^�e�[�u���̒������s��/�s��Ȃ��t���O���i�[����ϐ��̃|�C���^
//!								�������s��(=TRUE)�A�������s��Ȃ�(=FALSE)
//---------------------------------------------------------------------------
//DLL_API void WINAPI TdsVecGetZTableAdjFlag( BOOL* pbZtableAdj );

//---------------------------------------------------------------------------
//! �L�����u���[�V�����̌v�Z�����s���܂��B
//  
//! @param	ptResult	(OUT) 	�L�����u���[�V�������ʂ��i�[����\���̂̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecExecCalibCalcu( CalibResult* ptResult );

//---------------------------------------------------------------------------
//! �Z���T�L�����u���[�V�����p�����[�^��ݒ肵�܂��B
//  
//! @param	ptParam	(IN) 	�L�����u���[�V�����l���i�[����\���̂̃|�C���^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecSetSensorCalibParam( SensorParam* ptParam );

//---------------------------------------------------------------------------
//! �Z���T�L�����u���[�V�����p�����[�^���擾���܂��B
//  
//! @param  ptParam	(OUT) 	�L�����u���[�V�����l���i�[����\���̂̃|�C���^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetSensorCalibParam( SensorParam* ptParam );

//---------------------------------------------------------------------------
//! �L�����u���[�V�����p�����[�^�̕ω��ʂ̏����ݒ肵�܂��B
//  
//! @param  dLimit[2]	(IN) 	�L�����u���[�V�����p�����[�^�̕ω��ʏ��
//!		          [0]	(IN) 	   �Z���T�`���g�ω��ʏ��(�x)
//!		          [1]	(IN) 	   �Z���T�I�t�Z�b�g�ω��ʏ��(mm)
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecSetCalibParamChangeLimit( double dLimit[2] );

//---------------------------------------------------------------------------
//! �L�����u���[�V�����p�����[�^�̕ω��ʂ̏�����擾���܂��B
//  
//! @param  dLimit[2]	(OUT) 	�L�����u���[�V�����p�����[�^�̕ω��ʏ��
//!		          [0]	(OUT) 	   �Z���T�`���g�ω��ʏ��(�x)
//!		          [1]	(OUT) 	   �Z���T�I�t�Z�b�g�ω��ʏ��(mm)
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetCalibParamChangeLimit( double dLimit[2] );


//===========================================================================
//	�n�ƑO�_����p�֐�
//===========================================================================
//---------------------------------------------------------------------------
//! �n�ƑO�_�������擾���܂��B
//  
//! @param  ptInfo	(OUT)	�n�ƑO�_���̏����i�[����\���̂̃|�C���^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecGetChkScnInfo( ChkScnInfo* ptInfo );

//---------------------------------------------------------------------------
//! �ʊԋ�����l���t�@�C������ǂݍ��݁A���C�u�����֐ݒ肷��ƂƂ��ɒl���擾���܂��B
//  
//! @param  pdLength	(OUT)	�ʊԋ�����l(mm)���i�[����ϐ��̃|�C���^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecReadChkScnLengthBase( double* pdLength );

//---------------------------------------------------------------------------
//! �ʊԋ�����l�����C�u�����֐ݒ肵�A�t�@�C���֏������݂܂��B
//  
//! @param  dLength	(IN)	�ʊԋ�����l(mm)
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecWriteChkScnLengthBase( double dLength );

//---------------------------------------------------------------------------
//! �n�ƑO�_���̌v�Z�����s���܂��B
//  
//! @param  ptResult	(OUT) 	�n�ƑO�_�����ʂ��i�[����\���̂̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecExecChkScnCalcu( ChkScnResult* ptResult );

//---------------------------------------------------------------------------
//! �n�ƑO�_�����ʃt�@�C�����o�͂��܂��B
//  
//! @param  szFileName	(IN)	�t�@�C�����Ɗg���q���܂ސ�΃p�X
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecFileOutputCheckScnResult( char* szFileName);

//===========================================================================
//	���Ȑf�f��p�֐�
//===========================================================================
//---------------------------------------------------------------------------
//! ���Ȑf�f�̃��b�`�ʐM�`�F�b�N���[�h���J�n���܂��B
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecStartSelfChkLatchMode();

//---------------------------------------------------------------------------
//! ���Ȑf�f�̃��b�`�ʐM�`�F�b�N���[�h���I�����܂��B
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecStopSelfChkLatchMode();

//---------------------------------------------------------------------------
//! ���Ȑf�f�Ń��b�`����M�����ꍇ�Ƀ��C�u�����֎�M��ʒm���܂��B
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecLatchReceive();

//---------------------------------------------------------------------------
//! ���Ȑf�f�̃��b�`�ʐM�`�F�b�N�̌��ʎZ�o�����s���܂��B
//  
//! @param  ptResult	(OUT) 	���b�`�ʐM�`�F�b�N�̌��ʂ��i�[����\���̂̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecExecSelfChkLatch( SelfChkLatchResult* ptResult );

//---------------------------------------------------------------------------
//! ���Ȑf�f�̃��[�^�[�`�F�b�N�̌��ʎZ�o�����s���܂��B
//  
//! @param  ptResult	(OUT) 	���[�^�[�`�F�b�N�̌��ʂ��i�[����\���̂̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecExecSelfChkMotor( SelfChkMotorResult* ptResult );

//---------------------------------------------------------------------------
//! ���Ȑf�f��LED�`�F�b�N���J�n���܂��B
//  
//! @param  bLedOnOff	(IN)	LED��S�_��(=TRUE)�ALED��S����(=FALSE)
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecStartSelfChkLed( BOOL bLedOnOff );

//---------------------------------------------------------------------------
//! ���Ȑf�f��LED�`�F�b�N���I�����܂��B
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecStopSelfChkLed();

//---------------------------------------------------------------------------
//! ���Ȑf�f�̊��x�`�F�b�N���J�n���܂��B
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecStartSelfChkSens();

//---------------------------------------------------------------------------
//! ���Ȑf�f�̊��x�`�F�b�N���I�����܂��B
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecStopSelfChkSens();

//---------------------------------------------------------------------------
//! ���Ȑf�f�̊��x�`�F�b�N�̌��ʎZ�o�����s���܂��B
//  
//! @param  ptResult	(OUT) 	���x�`�F�b�N�̌��ʂ��i�[����\���̂̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecExecSelfChkSens( SelfChkSensResult* ptResult );


//===========================================================================
//	�Q�[�W�ݒ��p�֐�
//===========================================================================
//---------------------------------------------------------------------------
//! �Q�[�W��p�����[�^��ǂݍ��݁A���C�u�����֐ݒ肷��ƂƂ��ɒl���擾���܂��B
//  
//! @param  ptParam	(OUT)	�Q�[�W��p�����[�^���i�[����\���̂̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecReadVecGaugeIni( VecGaugeIni* ptParam );

//---------------------------------------------------------------------------
//! �n�ƑO�_���ݒ�p�����[�^��ǂݍ��݁A���C�u�����֐ݒ肷��ƂƂ��ɒl���擾���܂��B
//  
//! @param  ptParam	(OUT)	�n�ƑO�_���ݒ�p�����[�^���i�[����\���̂̃|�C���^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecReadSSettingIni( SensorSettingIni* ptParam );

//---------------------------------------------------------------------------
//! �n�ƑO�_���ݒ�p�����[�^�����C�u�����֐ݒ肵�A�t�@�C���֏������݂܂��B
//  
//! @param  ptParam	(IN)	�n�ƑO�_���ݒ�p�����[�^���i�[�����\���̂̃|�C���^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecWriteSSettingIni( SensorSettingIni* ptParam );

//---------------------------------------------------------------------------
//! �n�ƑO�_���ݒ�p�����[�^�����������܂��B
//  
//! @param  ptParam	(OUT)	�n�ƑO�_���ݒ�p�����[�^���i�[����\���̂̃|�C���^
//---------------------------------------------------------------------------
DLL_API void WINAPI TdsVecClearSSettingIni( SensorSettingIni* ptParam );


//===========================================================================
//	���̑��֐�
//===========================================================================
//---------------------------------------------------------------------------
//! �o�͂������O�t�@�C�����폜���܂��B
//  
//! @param	iFileNum	(IN)	�c���t�@�C����
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecDeleteErrorLogFile( int iFileNum );

//===========================================================================
//	ApiScan�P�x�}�X�N�@�\���Ǌ֐�
//===========================================================================
//---------------------------------------------------------------------------
//! �ʏ푪�莞�̋P�x�X���C�X�p�����[�^��ݒ肵�܂��B
//  
//! @param	iSimpleSens	(IN)	�P�x�X���C�X��ݒ肷��v���ȈՊ��x�ԍ�
//! @param	usVal		(IN)	�ݒ肷��P�x�X���C�X
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecSetBrightSliceLevel( int iSimpleSens, unsigned short usVal );

//---------------------------------------------------------------------------
//! �ʏ푪�莞�̋P�x�X���C�X�p�����[�^���擾���܂��B
//  
//! @param	iSimpleSens	(IN)	�擾����P�x�X���C�X�̌v���ȈՊ��x�ԍ�
//! @param	pusVal		(OUT)	�擾����P�x�X���C�X�ւ̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecGetBrightSliceLevel( int iSimpleSens, unsigned short* pusVal );

//---------------------------------------------------------------------------
//! �ʏ푪�莞�̊p�x�}�X�N�p�����[�^��ݒ肵�܂��B
//  
//! @param	dThreshold	(IN)	�ݒ肷��p�x�}�X�N臒l(�x)
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecSetAngleMask( double dThreshold );

//---------------------------------------------------------------------------
//! �ʏ푪�莞�̊p�x�}�X�N�p�����[�^���擾���܂��B
//  
//! @param	pdThreshold	(OUT)	�擾����p�x�}�X�N臒l(�x)�ւ̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecGetAngleMask( double* pdThreshold );

//---------------------------------------------------------------------------
//! �ʏ푪�莞�̊��x�ݒ�X���C�X�p�����[�^��ݒ肵�܂��B
//  
//! @param	iSimpleSens	(IN)	���x�ݒ�X���C�X��ݒ肷��v���ȈՊ��x�ԍ�
//! @param	usVal		(IN)	�ݒ肷�銴�x�ݒ�X���C�X
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecSetDataMinSliceLevel( int iSimpleSens, unsigned short usVal );

//---------------------------------------------------------------------------
//! �ʏ푪�莞�̊��x�ݒ�X���C�X�p�����[�^���擾���܂��B
//  
//! @param	iSimpleSens	(IN)	�擾���銴�x�ݒ�X���C�X�̌v���ȈՊ��x�ԍ�
//! @param	pusVal		(OUT)	�擾���銴�x�ݒ�X���C�X�ւ̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecGetDataMinSliceLevel( int iSimpleSens, unsigned short* pusVal );


//===========================================================================
//	ApiScan�}�X�N�@�\�����֐�
//===========================================================================
//---------------------------------------------------------------------------
//! �ʏ푪�莞��2�s�[�N�}�X�N�p�����[�^��ݒ肵�܂��B
//  
//! @param	iMaskType		(IN)	�ݒ肷��2�s�[�N�}�X�N�ݒ�(0:�}�X�N�L��(�f�[�^������)�A1:�}�X�N���� �g�`�����L�����̃f�[�^���擾�A2:�}�X�N���� ����(Z)���߂����̃f�[�^���擾)
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecSet2PeakMask( int iMaskType );

//---------------------------------------------------------------------------
//! �ʏ푪�莞��2�s�[�N�}�X�N�p�����[�^���擾���܂��B
//  
//! @param	piMaskType		(OUT)	�擾����2�s�[�N�}�X�N�ݒ�ւ̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecGet2PeakMask( int* piMaskType );

//---------------------------------------------------------------------------
//! �ʏ푪�莞�̃G�b�W�}�X�N�p�����[�^��ݒ肵�܂��B
//  
//! @param	iDisableNum		(IN)	�ݒ肷��G�b�W�}�X�N�_�� (0�`6)
//! @param	iEdgeSearchNum	(IN)	�ݒ肷��G�b�W�Ɣ��f���钆��_�� (1�`5)
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecSetEdgeMask( int iDisableNum, int iEdgeSearchNum );

//---------------------------------------------------------------------------
//! �ʏ푪�莞�̃G�b�W�}�X�N�p�����[�^���擾���܂��B
//  
//! @param	piDisableNum	(OUT)	�擾����G�b�W�}�X�N�_���ւ̃|�C���^
//! @param	piEdgeSearchNum	(OUT)	�擾����G�b�W�Ɣ��f���钆��_���ւ̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecGetEdgeMask( int* piDisableNum, int* piEdgeSearchNum );

//---------------------------------------------------------------------------
//! �G�b�W�}�X�N�p�����[�^�̏����l���擾���܂��B
//  
//! @param	iSimpleSens		(IN)	�擾����G�b�W�}�X�N�p�����[�^�̌v���ȈՊ��x�ԍ�
//! @param	iMode			(IN)	�擾����G�b�W�}�X�N�p�����[�^�̌v�����[�h
//! @param	piDisableNum	(OUT)	�擾����G�b�W�}�X�N�_�������l�ւ̃|�C���^
//! @param	piEdgeSearchNum	(OUT)	�擾����G�b�W�Ɣ��f���钆��_�������l�ւ̃|�C���^
//  
//! @return	 	���폈��(=TRUE)�A�ُ폈��(=FALSE)
//---------------------------------------------------------------------------
DLL_API BOOL WINAPI TdsVecGetEdgeMaskDefault( int iSimpleSens, int iMode, int* piDisableNum, int* piEdgeSearchNum );

}	// extern "C"

#endif // !defined(__TdsData_h)
