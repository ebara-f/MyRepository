// HsmsQue.cpp	�L���[
// ********************************************************
//  ���M�pQue�o�b�t�@ �i���M�݂̂Ɏg�p���Ă���)
//  32�̃}�W�b�NNO�����������Ŏg�p����Ă���̂Œ���
//   �������}�b�v��(�v���Z�X�ԋ��ʗ̈�)��ID�Ɠ����ԍ����g�p���邽�ߕύX�s��
//  ��M�͒��ڃ������}�b�v�h�t�@�C����ǂݏo��
// 
#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "QueTask.h"
#include "QueProc.h"
#include "QueMain.h"

extern HANDLE  hBoxMutex[];

bool g_bThreadBreak = false;

struct	t_QueForm {
			int		WriteIx;
			int		ReadIx;
			char	*QueAddr[QueMax];
};
typedef	struct t_QueForm	STR_QUE;

HANDLE		hQUETASK;
HANDLE		hProcSEMA[QueEntry];
STR_QUE*	m_Que;

//----------------------------------------------

UINT  QueThread(LPVOID pParm);
void QueThreadStart(void)
{
	ULONG	shThreadId;
	hQUETASK = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)QueThread,
								NULL,0,
								&shThreadId);
}
////////////////////////////////////////////////
// DESCRIPTION: Send Control(H<-T/B)
// Que�o�b�t�@�[�ɐςݍ���(0�`31) (t_MessForm)�f�[�^���������[�}�b�v�h�ŃA�v���ԒʐM�ɐςݍ���
//�@
// 2021.3.15 ���ӏ���
// ID�ɂ͂Q�킠��
//  Que�o�b�t�@�[��QueEntry�Œ�`����� ID�ԍ� �ƃ������[�}�b�v�h�ŃA�v���ԒʐM(Polyworks�j
//  ID�Ƃ͈قȂ�@�܂��A�������}�b�v�h�t�@�C������ID�Ƃ͖��֌W�ł���̂Œ��ӂ��K�v
//  �A�v���ԒʐM�͈�̃������Ńo�b�t�@�̈ʒu�����ƂȂ�̂݁@
//  ���̃\�[�X��@ID�����݂��Ă���悤�Ɍ��󂯂���@MesBoxBusyCheck(QNo)��RvText->TId�łȂ���΂Ȃ�Ȃ�
//�@QueTask.cpp �Œ�`����Ă��� #define COMM_MAX	32 ��(RvText->TId <= 32�����̐��l�ɂ�����B
//   ---> �}�W�b�NNo���g�p����Ă��邽�߁A����32�Œ�l�Ƃ��邱�ƁB
//�@�A�N�Z�X�̍�,WaitForSingleObject()���Ă��邪�@RvText�͖��֌W�H�H�H�H�H
//�@�@�Ƃ��낪�@SendMesBox()�Ńo�b�t�@�[�ɏ������݂̍� MesBox[0] = 1;�ƃ|�C���^���������݌��
//    �t���O���Z�b�g���Ă��邽�߂ɁA���葤�Ƌ����ɂ͂Ȃ��Ă��Ȃ��B�@LplRecvMesBox()�ƍ��킹�ĕύX���ɂ͒��ӂ��邱�ƁB

UINT  QueThread(LPVOID pParm)
{
	int		QNo;
	struct t_MessForm *RvText;

	for ( ; ; ) {

		if (g_bThreadBreak == true) break;

//>>[CHG:1006] 2010.12.7 yamade
//		Sleep(100);
		Sleep(10);
//<<[CHG:1006] 2010.12.7 yamade
		for (QNo = 1; QNo <= QueEntry; QNo++) {
			if(hBoxMutex[QNo-1]) WaitForSingleObject(hBoxMutex[QNo-1], INFINITE);	//[ADD:1006] 2010.12.7 yamade

			if (MesBoxBusyCheck(QNo) == 0) {
				RvText = (struct t_MessForm *)GetQue(QNo);
				if (RvText != NULL) {
					if (RvText->TId <= 32)
						SendMesBox(RvText->TId, RvText->Leng, RvText->Text);
					else {
						PutFreeBlock(RvText->TId-32, RvText->Text);					//  PutFreeBlock���e�s��
					}
					free(RvText);
				}
			}

			if(hBoxMutex[QNo-1]) ReleaseMutex(hBoxMutex[QNo-1]);	//[ADD:1006] 2010.12.7 yamade
		}

	}
	return 0;
}

void TerminateQueThread(void)
{

	g_bThreadBreak = true;

	// �X���b�h�̊�����ҋ@
	WaitForSingleObject(hQUETASK, INFINITE);

	// �n���h�������
	CloseHandle(hQUETASK);

	return;
}

//---------------------------------------------------------

// �L���[�̃C�j�V����
void InitialQue(void)
{
	int		i, j;
	SECURITY_ATTRIBUTES SecAtri;
	
	g_bThreadBreak = false;

	m_Que = new t_QueForm[QueEntry];
	for (i = 0; i < QueEntry; i++) {
		hProcSEMA[i] = CreateSemaphore(&SecAtri, 1, 1, NULL);
		m_Que[i].WriteIx = 0;
		m_Que[i].ReadIx  = 0;
		for (j = 0; j < QueMax; j++)
			m_Que[i].QueAddr[j] = 0;
	}
}

// �L���[�̃f���[�g
void DeleteQue(void)
{

	int		i;


	for (i = 0; i < QueEntry; i++) {
		for ( ; ; ) {
			if (m_Que[i].WriteIx != m_Que[i].ReadIx) {
				if (m_Que[i].ReadIx == QueMax-1) {
					m_Que[i].ReadIx = 0;
					free( m_Que[i].QueAddr[QueMax-1]);
				}
				else {
					m_Que[i].ReadIx++;
					free( m_Que[i].QueAddr[m_Que[i].ReadIx-1]);
				}
			}
			else
				break;
		}
	}

	if (m_Que != NULL) {
		delete[] m_Que;
	}

	//for (i = 0; i<QueEntry; i++)
	//{
	//	if (hBoxMutex[i] != NULL) {
	//		CloseHandle( hBoxMutex[i] );
	//	}
	//}

}

// �L���[�Ƀf�[�^(�|�C���^�[�����n�� char* (t_MessForm))������
// 2021.3.15 �߂�l 1�̎��̃o�O�C��
//   return ������������ 
// �߂�l 0 ����
//        1 QueID���w��ԍ��ȊO (��{�Ȃ� ���O�m�F�̂���)
//        2 �o�b�t�@�[�������ς��i�V�X�e���ُ�@�����~�̂���)
int PutQue(int QID, char* QAddr)
{
	int iSts = 0;														// �߂�l (����)

	if ((QID >= 1) && (QID <= QueEntry)) {
		WaitForSingleObject(hProcSEMA[QID-1], INFINITE);
		if (m_Que[QID-1].WriteIx == QueMax-1) {							// Buffer�̍Ō�܂œ��B
			if (m_Que[QID-1].ReadIx != 0) {								// �����ς��̔��f�@++WriteIx���ǂݏo���ɒǂ���
				m_Que[QID-1].QueAddr[QueMax-1] = QAddr;
				m_Que[QID-1].WriteIx = 0;								// �������݃J�E���^��擪�ɖ߂�
				iSts = 0;
			}
			else {
				iSts = 2;												// �v���I�G���[
			}
		}
		else {
			if (m_Que[QID-1].WriteIx+1 != m_Que[QID-1].ReadIx) {		// �����ς��̔��f�@++WriteIx���ǂݏo���ɒǂ���
				m_Que[QID-1].QueAddr[m_Que[QID-1].WriteIx] = QAddr;
				m_Que[QID-1].WriteIx++;									// �������݃J�E���^�����Z�b�g����
				iSts = 0;
			}
			else {
				iSts = 2;												// �v���I�G���[
			}
		}
		ReleaseSemaphore(hProcSEMA[QID - 1], 1, NULL);
		return iSts;
	}
	else {
		return 1;														//        1 QueID���w��ԍ��ȊO (��{�Ȃ� ���O�m�F�̂���)
	}
}

// �L���[����f�[�^���擾����(�|�C���^�[�@�߂� )
// �߂�l NULL�łȂ��@�����i�f�[�^�̃|�C���^) ���������̂���
//        NULL �f�[�^���Ȃ���������ID�̃G���[(���̂Ƃ��o�O����C��)
void* GetQue(int QID)
{
	void* ptRes = NULL;

	if ((QID >= 1) && (QID <= QueEntry)) {
		WaitForSingleObject(hProcSEMA[QID-1], INFINITE);
		if (m_Que[QID-1].WriteIx != m_Que[QID-1].ReadIx) {				// Reasd��Write�������ԍ��̓f�[�^�Ȃ����
			if (m_Que[QID-1].ReadIx == QueMax-1) {						// �o�b�t�@�[�܂�Ԃ�
				m_Que[QID-1].ReadIx = 0;
				ptRes = m_Que[QID-1].QueAddr[QueMax-1];
			}
			else {
				m_Que[QID-1].ReadIx++;
				ptRes = m_Que[QID-1].QueAddr[m_Que[QID-1].ReadIx-1];
			}
		}
		else {
			/* do nothing */
		}
		ReleaseSemaphore(hProcSEMA[QID - 1], 1, NULL);
		return ptRes;
	}
	else {
		return NULL;
	}
}
