// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ VECCOM_EXPORTS
// �V���{���ŃR���p�C������܂��B���̃V���{���́A���� DLL ���g���v���W�F�N�g�Œ�`���邱�Ƃ͂ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// VECCOM_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B
#pragma once

#ifdef VECCOM_EXPORTS
#define VECCOM_API __declspec(dllexport)
#else
#define VECCOM_API __declspec(dllimport)
#endif

////////////////////////////////////////////////////////////
// Error Code
#define VEC_OK				0
#define VEC_ER_STOP_WAT		1
#define VEC_ER_STOP_RST		2
#define VEC_ER_STOP_BUF		3
#define VEC_ER_STOP_OTR		4
#define	VEC_ER_OPEN			5
#define	VEC_ER_CLSE			6
#define VEC_ER_TMOT			7

#ifndef SOH
#define SOH				(char)0x01
#endif
#ifndef STX
#define STX				(char)0x02
#endif
#ifndef EOT
#define EOT				(char)0x04
#endif
#ifndef ENQ
#define ENQ				(char)0x05
#endif
#ifndef ACK
#define ACK				(char)0x06
#endif
#ifndef BS
#define BS				(char)0x08
#endif
#ifndef TAB
#define TAB				(char)0x09
#endif
#ifndef LF
#define LF				(char)0x0a
#endif
#ifndef CR
#define CR				(char)0x0d
#endif
#ifndef DC1
#define DC1				(char)0x11
#endif
#ifndef NAK
#define NAK				(char)0x15
#endif
#ifndef ESC
#define ESC				(char)0x1b
#endif
#ifndef SP
#define SP				(char)0x20
#endif

#define			GposLen		50
#define			GetCntLen		86
#define			GposV8Len	59	// 2021.11.25 �X�V
#define			GetCntV8Len	95	// 2021.11.25 �X�V


typedef unsigned int VEC_HANDLE;

typedef struct
{
	long	no;

	double	xyz[3];
	double	ijk[3];
	double	ijk2[3];
	
	unsigned int	button;

	int		er_code[9];	// 2008.1.29

} VecDt;


typedef struct	// 2012.8.27
{
	long	no;

	double	xyz[3];
	double	ijk[3];
	double	ijk2[3];
	
	unsigned int	button;

	int		er_code[9];

	double	angle[7];	////

	int		pbid_chg_fg;	// 1�ŕύX�L(2021.6.10)

	int		some_err_fg;	// !=0�ŃG���[�L(2021.11.25)

} VecDtEx;


typedef struct
{
	long	no;

	double	xyz[3];
	double	ijk[3];
	double	ijk2[3];
	
	unsigned int	button;
	
	long	cnt[9];

	int		er_code[9];	// 2008.1.29

} VecCt;


typedef struct
{
	long	no;

	double	xyz[3];
	double	ijk[3];
	double	ijk2[3];
	
	unsigned int	button;
	
	long	cnt[9];

	int		er_code[9];

	double	angle[7];	////

	int		pbid_chg_fg;	// 1�ŕύX�L(2021.6.10)

	int		some_err_fg;	// !=0�ŃG���[�L(2021.11.25)

} VecCtEx2; // TdsData.h�œ����\���̂���`����Ă��邽�߁AVecCtEx�� VecCtEx2�֕ύX(2025.6.9yori)


typedef struct
{
	int		mode;
	unsigned int	init;
	int		ps_id;
	double	dia;
	int		beep;
	char 	EnErFg;	// �G���R�[�_�s�ǌ��m�t���O
	char 	CnErFg;	// �J�E���^��̏ጟ�m�t���O
	char 	HsErFg;	// �A�[�����z���s�ǌ��m
	unsigned long 	PowLog;	// �ʓd���ԃ��M���O�@�\(2021.8.11 unsigned�ɕύX)
	char 	LimFg;	// �֐߃��~�b�g���\���@�\
	char PsNo0Fg;	// No.0���ɃG���R�[�_���t���Ă��邩���f����ׂ̃t���O 2022.5.16

} VecSt;


// 2008.9.10
typedef struct
{
	double 	maxmin_x;
	double 	maxmin_y;
	double 	maxmin_z;
	double 	sigma2_x;
	double 	sigma2_y;
	double 	sigma2_z;
	double 	sigma2_r;
	double	menkangosa;
	double	menkanjig;
	short	judge;	// 1<-OK, 0<-NG
	char	ver;
} VecResult;


// 2021.6.11
// ApiScanTdsArm.ini�̃p�����[�^�i�[�p
typedef struct{
	double	No0[3];	// �Z���T�[�`���g�p�����[�^��l ��{�Œ�l
	double	No1[3];	// �Z���T�[�I�t�Z�b�g�p�����[�^��l ��{�Œ�l
	double	No2[3];	// �Z���T�[�`���g�p�����[�^(��)
	double	No3[3];	// �Z���T�[�I�t�Z�b�g�p�����[�^(��)

} VecTdsArmIni;



// 2021.6.11
// ProbeSetting.ini�̃p�����[�^�i�[�p
typedef struct{
	int		OffsetProbeUseFlag;					// �v���[�u�o�^�t���O(1:�o�^�ρA0:���o�^)
	double	OffsetProbeTipAngle;					// �v���[�u��[�Ȃ���p�x
	double	OffsetProbeIjk2RotationAngle;		// IJK2��]�p�x
	int		OffsetProbeTouchFlag;				// �^�b�`���t���O(0:�ʏ�@1:�^�b�`��)
	double	OffsetProbeBallDiameterCalib;		// �{�[�����a�i�_��/�L�����u�p�j
	double	OffsetProbeBallDiameterMeas;			// �{�[�����a�i����p�j
	int		OffsetProbeTyp;						// �v���[�u�^�C�v
													// 0:�e�[�p
													// 1:�X�^���_�[�h
													// 2:�G�N�X�e���V����
													// 3:�X�g���[�g
													// 4:�^�b�`(V7/V8�͖���)
	int		OffsetProbeCalibStatus;				// �L�����u�X�e�[�^�X(0:�����{�@1:���{�ς�)
	double	OffsetProbeBallDiameterMeasBackup;	// �{�[�����a�i����p�j���o�b�N�A�b�v�p
	char	OffsetProbeCode[16];				// �v���[�u���i�R�[�h(���p�p������)	// 2021.10.21(32->16�ύX)

} VecProbeSettingIni;



VECCOM_API int Vec_Open(VEC_HANDLE *pvecHandle, int tmout, char *dir);	// �����ǉ�(2018.6.5yori)
VECCOM_API int Vec_ReOpen(VEC_HANDLE* pvecHandle, int tmout);
VECCOM_API int Vec_Close(VEC_HANDLE vecHandle);
VECCOM_API int Vec_DataRequest(VEC_HANDLE vecHandle, int bufSize, VecDt *vecData, int *dataNo);
VECCOM_API int Vec_CntRequest(VEC_HANDLE vecHandle, int bufSize, VecCt *vecCntData, int *dataNo);
VECCOM_API int Vec_StatusRequest(VEC_HANDLE vecHandle, VecSt *vecStatus);
VECCOM_API int Vec_CmdTrans(VEC_HANDLE vecHandle, char *cmd, char *para, int paraNo);
VECCOM_API int Vec_CmdReceive(VEC_HANDLE vecHandle, char *cmd, char *para, int *paraNo);
VECCOM_API int Vec_SetPulsProbe(VEC_HANDLE vecHandle, double ofbx, double ofby, double ofbz, double ttbx, double ttby, double ttbz);
VECCOM_API int Vec_GetPulsProbe(VEC_HANDLE vecHandle, double *ofbx, double *ofby, double *ofbz, double *ttbx, double *ttby, double *ttbz);
VECCOM_API int Vec_WriteMemory(VEC_HANDLE vecHandle);
VECCOM_API int Vec_SetIpAddress(VEC_HANDLE vecHandle, DWORD dwAdrs);
VECCOM_API int Vec_SetNetworkAddress(VEC_HANDLE vecHandle, DWORD dwAdrs, DWORD dwMask, WORD wPort);
// 2012.8.27
VECCOM_API int Vec_DataRequestEx(VEC_HANDLE vecHandle, int bufSize, VecDtEx *vecData, int *dataNo);
VECCOM_API int Vec_CntRequestEx(VEC_HANDLE vecHandle, int bufSize, VecCtEx2 *vecCntData, int *dataNo); // TdsData.h�œ����\���̂���`����Ă��邽�߁AVecCtEx�� VecCtEx2�֕ύX(2025.6.9yori)
// 2021.6.11
// ApiScanTdsArm.ini�̃p�����[�^����M�֐�
VECCOM_API int Vec_SetTdsArmIni (VEC_HANDLE vecHandle, VecTdsArmIni vecTdsArmIni);
VECCOM_API int Vec_GetTdsArmIni (VEC_HANDLE vecHandle, VecTdsArmIni *vecTdsArmIni);
// 2021.6.11
// ProbeSetting.ini�̃p�����[�^����M�֐�
VECCOM_API int Vec_SetProbeSettingIni (VEC_HANDLE vecHandle, VecProbeSettingIni vecProbeSettingIni[]);	// 17-19�͎}�Ԏd�l�ɕύX�B�g�p���Ȃ�(2022.1.13)
VECCOM_API int Vec_GetProbeSettingIni (VEC_HANDLE vecHandle, VecProbeSettingIni vecProbeSettingIni[]);

VECCOM_API int Vec_SetProbeSettingIniManual (VEC_HANDLE vecHandle, int  id/*(=17,18,19)*/, VecProbeSettingIni vecProbeSettingIni[]);	// �}��0-14�����
VECCOM_API int Vec_GetProbeSettingIniManual (VEC_HANDLE vecHandle, int  id/*(=17,18,19)*/, VecProbeSettingIni vecProbeSettingIni[]);	// �}��0-14�����
// 2021.7.16
VECCOM_API int Vec_DataRequestV8(VEC_HANDLE vecHandle, int bufSize, VecDtEx *vecData, int *dataNo);
VECCOM_API int Vec_CntRequestV8(VEC_HANDLE vecHandle, int bufSize, VecCtEx2 *vecCntData, int *dataNo); // TdsData.h�œ����\���̂���`����Ă��邽�߁AVecCtEx�� VecCtEx2�֕ύX(2025.6.9yori)
// 2021.8.11
VECCOM_API int Vec_StatusRequestV8(VEC_HANDLE vecHandle, VecSt *vecStatus);

