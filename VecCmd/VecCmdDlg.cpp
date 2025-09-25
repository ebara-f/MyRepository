
// VecCmdDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "VecCmd.h"
#include "VecCmdDlg.h"
#include "afxdialogex.h"

#include "LplQue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVecCmdDlg ダイアログ



CVecCmdDlg::CVecCmdDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VECCMD_DIALOG, pParent)
	, m_CmdID(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVecCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CmdID, m_CmdID);
}

BEGIN_MESSAGE_MAP(CVecCmdDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Send, &CVecCmdDlg::OnBnClickedSend)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CVecCmdDlg メッセージ ハンドラー

BOOL CVecCmdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	int		yes_existF;

	LplQue_IsExist( &yes_existF );

	if ( yes_existF != 1 ) {
        AfxMessageBox( _T("VecAppを起動してください") );
	}

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CVecCmdDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CVecCmdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CVecCmdDlg::OnBnClickedSend()
{
	int		frc,yes_existF;

	UpdateData( TRUE );
	
	LplQue_IsExist( &yes_existF );

	if ( yes_existF == 1 ) {
		frc = LplQue_PutCmdID( m_CmdID );
		if ( frc != 0 ) {
			AfxMessageBox( _T("コマンドの書込みに失敗しました") );
		}
	}
	else {
		AfxMessageBox( _T("共有メモリがオープンになっていません") );
	}
}



void CVecCmdDlg::OnClose()
{
	CDialogEx::OnClose();
}
