//-----------------------------------------------------------------------------
//�P�D�L���[����֐�
//  �v���Z�X�Ԃ̃f�[�^�ʐM�֐����L��܂��B
//
//DLL��            :LplQue.dll
//LIB��            :LplQue.lib
//�w�b�_�[�t�@�C�� :LplQue.h
//
//-------------------------------------------
//  �v���Z�X�ԃf�[�^�ʐM�֐�
//-------------------------------------------
//
//			�֐���	            		�� �e
//	LplInitialIFCommon			�v���Z�X�ԋ��L�f�[�^�Ǘ��̈�̏�����
//	LplInitialIFCommonEx		�v���Z�X�ԋ��L�f�[�^�Ǘ��̈�̏�����(�ԍ��w���)
//	LplSendMesBox	        	���v���Z�X�ւ̃f�[�^���M
//	LplRecvMesBox	        	���v���Z�X����̃f�[�^��M
//	LplCreateCommonArea			�v���Z�X�ԋ��ʗ̈�̊m��
//
//	LplSendMesBox2			    ���v���Z�X�ւ̃f�[�^���M(�L���[����݂����Ȃ����[�h)
//	LplSendMesBoxBuffferEmpty	�o�b�t�@���󂩂ǂ����𔻒f
//	LplTerminateALL	            �v���Z�X�ԋ��L�f�[�^�Ǘ��̈�̏I������
//
//-----------------------------------------------------------------------------
extern void		__stdcall LplInitialIFCommon(void);
extern void		__stdcall LplInitialIFCommonEx(int TblNo);
extern int		__stdcall LplSendMesBox(int TID, int Leng, char SBuf[]);
extern int		__stdcall LplRecvMesBox(int TId, char RBuf[]);
extern char*	__stdcall LplCreateCommonArea(char CName[], int CSize);

extern int 		__stdcall LplSendMesBox2(int TId, int Leng, char SBuf[]);	// 2021.4.15
extern int 		__stdcall LplSendMesBoxBuffferEmpty(int TId);				// 2021.4.15

extern void	    __stdcall LplTerminateALL();                                // 2025.4.11
