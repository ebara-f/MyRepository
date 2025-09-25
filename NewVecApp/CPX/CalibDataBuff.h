/***********************************************************************

	�J�E���g�f�[�^���i�[����֐�
	2025.9.2 eba
	�g���K�[�{�^�����������f�[�^�����������PutData�֐���
	�߂�l���P�Ƃ��AAppMain���̃��[�J�[�X���b�h�Ń��b�Z�[�W��
	C#�֑��M���ACalibComm��UpDateData�֐����R�[���o�b�N�����邵����

***********************************************************************/

#pragma once
#include <mutex>
#include "HwCtrl.h"

#define CALIBDATABUFF_BUFF_SIZE	0x000F

// �b��Ō���ꂽ�͈͂ł��̍\���̂��g��
// �p���X�̖��O�ƃo�b�e�B���O����炵���̂Ńv���W�F�N�g���ŃO���[�o���Ɏg���Ȃ�
/*typedef struct
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

} VecCtEx;*/


class CalibDataBuff
{
public :
	CalibDataBuff(void);
	virtual ~CalibDataBuff(void);

private :
	VecCtEx2 m_pCntData[CALIBDATABUFF_BUFF_SIZE];

	int m_PtrR;
	int m_PtrW;
	int m_Len;

	std::mutex m_Mutex; // �r������p�~���[�e�b�N�X

public:
	int InitBuff();
	int PutData(VecCtEx2 data);
	int GetData(VecCtEx2* data);
	int DelData(void);
	int LenData(void);

};