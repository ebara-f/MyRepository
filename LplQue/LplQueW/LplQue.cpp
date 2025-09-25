// LplQue.cpp : DLL 用の初期化処理の定義を行います。
//

#include "stdafx.h"
#include "LplQue_inner.h"
#include "QueMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HANDLE  hBoxMutex[];
//
//	メモ!
//
//		この DLL が MFC DLL に対して動的にリンクされる場合、
//		MFC 内で呼び出されるこの DLL からエクスポートされた
//		どの関数も関数の最初に追加される AFX_MANAGE_STATE 
//		マクロを含んでいなければなりません。
//
//		例:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 通常関数の本体はこの位置にあります
//		}
//
//		このマクロが各関数に含まれていること、MFC 内の
//		どの呼び出しより優先することは非常に重要です。
//		これは関数内の最初のステートメントでなければな
//		らないことを意味します、コンストラクタが MFC 
//		DLL 内への呼び出しを行う可能性があるので、オブ
//		ジェクト変数の宣言よりも前でなければなりません。
//
//		詳細については MFC テクニカル ノート 33 および
//		58 を参照してください。
//

/////////////////////////////////////////////////////////////////////////////
// CLplQueApp

BEGIN_MESSAGE_MAP(CLplQueApp, CWinApp)
	//{{AFX_MSG_MAP(CLplQueApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLplQueApp の構築

CLplQueApp::CLplQueApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance の中の重要な初期化処理をすべて記述してください。
	setlocale(LC_ALL, "japanese");//[ADD]-kanamura
	AppInit();
}
CLplQueApp::~CLplQueApp()
{
	int i;
	//------------------------------

//>>[ADD:1006] 2010.12.7 yamade
	for( i=0; i<QueEntry; i++ )
	{
		if (hBoxMutex[i] != NULL) {
			CloseHandle( hBoxMutex[i] );
			hBoxMutex[i] = NULL;
		}
	}
//<<[ADD:1006] 2010.12.7 yamade

	//<-追加(20211124yori)
	if (hSEMAQUE != NULL)
	{
		CloseHandle(hSEMAQUE);
		hSEMAQUE = NULL;
	}
	//->追加(20211124yori)

	AppClose(); //追加(Detected memory leaks!対応)(2022.1.26yori)
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CLplQueApp オブジェクト

CLplQueApp theApp;
