// LplQue_inner.h : LplQue �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//
//

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��
#include <locale.h>			//[ADD:kanamura]

/////////////////////////////////////////////////////////////////////////////
// CLplQueApp
// ���̃N���X�̓���̒�`�Ɋւ��Ă� LplQue.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CLplQueApp : public CWinApp
{
public:
	CLplQueApp();
	~CLplQueApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLplQueApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CLplQueApp)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

