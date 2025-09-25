
// VecCmdDlg.h : ヘッダー ファイル
//

#pragma once


// CVecCmdDlg ダイアログ
class CVecCmdDlg : public CDialogEx
{
// コンストラクション
public:
	CVecCmdDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VECCMD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_CmdID;
	afx_msg void OnBnClickedSend();
	afx_msg void OnClose();
};
