
// VecCmd.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CVecCmdApp:
// このクラスの実装については、VecCmd.cpp を参照してください
//

class CVecCmdApp : public CWinApp
{
public:
	CVecCmdApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CVecCmdApp theApp;
