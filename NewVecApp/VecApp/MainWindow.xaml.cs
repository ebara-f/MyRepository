using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Linq;
using System.Linq.Expressions;
using System.Net;
using System.Printing;
using System.Reflection.Metadata;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using CSH;


namespace VecApp
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		#region 最大化・最小化・閉じるボタンの非表示設定

		[DllImport("user32.dll", SetLastError = true)]
		private static extern int GetWindowLong(IntPtr hWnd, int nIndex);

		[DllImport("user32.dll")]
		private static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

        private void Window_Loaded(object sender, RoutedEventArgs e)
		{
            const int GWL_STYLE = -16;
            const int WS_SYSMENU = 0x00080000;

            //SYSMENUを非表示にする
            var hwnd = new WindowInteropHelper((Window)sender).Handle;
            //SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SYSMENU); // 2025.4.22 eba del // 最小化、閉じるボタン有効にするため、コメントアウト(2025.11.19yori)
        }

        #endregion

        /// <summary>
        /// メンバー変数
        /// </summary>
        private static IntPtr	m_hWnd;		// ウィンドウハンドル
		private HwndSourceHook	m_Hook;

		private Dlg01 m_Dlg01 = null;
		private Dlg02 m_Dlg02 = null;
		private Dlg03 m_Dlg03 = null;
        private SubWindow1 m_SubWnd01 = null;   // 2025.4.23 eba add
        private SubWindow2 m_SubWnd02 = null;   // 2025.4.23 eba add
        private SubWindow3 m_SubWnd03 = null;   // 2025.4.23 eba add
        private DlgPrgBar1 m_DlgPrgBar1 = null;	// 2025.5.30 add eba // プログレスバー追加のため番号追加(2025.7.30yori)
        private DlgPrgBar2 m_DlgPrgBar2 = null;	// 追加(2025.7.30yori)
        private DlgPrgBar3 m_DlgPrgBar3 = null;	// 追加(2025.7.31yori)
        private static PrgressBar m_PrgressBar = null;  // 2025.11.14 add eba

        // スタイルを変更するためのインデックス(2025.11.19yori)
        private const int GWL_STYLE = -16;

        /// <summary>
        /// 初期化処理
        /// </summary>
        public MainWindow()
		{
			InitializeComponent();

            // メインウィンドウ起動時に最小化する。(2025.11.19yori)
            this.WindowState = System.Windows.WindowState.Minimized;

            this.DataContext = new MainWindowViewModel();

			// ウィンドウズハンドルの取得
			m_hWnd = new WindowInteropHelper(this).EnsureHandle();

			// メッセージループをフックする関数を登録
			HwndSource source = HwndSource.FromHwnd(m_hWnd);
			m_Hook = new HwndSourceHook(WndProc);
			source.AddHook( m_Hook );

			// 独自の初期化処理 -> C++で実装した処理を実行
			int rc = CSH.AppMain.Init();
			if (rc != 0) {
 				MessageBox.Show(
					"初期化に失敗しました",
					"AppMain",
					MessageBoxButton.OK,
					MessageBoxImage.Error
				);
			}

			// ダイアログの作成
			//m_Dlg01 = new Dlg01();
			//m_Dlg02 = new Dlg02();
			//m_Dlg03 = new Dlg03();
            m_SubWnd01 = new SubWindow1();  // 2025.4.23 eba add
            m_SubWnd02 = new SubWindow2();  // 2025.4.23 eba add
            m_SubWnd03 = new SubWindow3();  // 2025.4.23 eba add
            // m_DlgPrgBar1,2も3と同じように改良しないとプロセスがこのってしまう(後で必ずやる必要あり) 2025.9.10 eba memo
            m_DlgPrgBar1 = new DlgPrgBar1(); // プログレスバー追加のため番号追加(2025.7.30yori)
            //m_DlgPrgBar2 = new DlgPrgBar2(); // 追加(2025.7.30yori)
            //
            m_DlgPrgBar3 = new DlgPrgBar3(); // 追加(2025.7.31yori) 2025.8.29 これがあるとプロセスが残る
            m_PrgressBar = new PrgressBar(); // 2025.11.14 add eba

            // コールバック関数のセット
            CSH.ErrMsg.SetCB( ShowErr );  // エラー表示
			CSH.UsrMsg.SetCB( SendMsg );  // Windowsメッセージ送信
            CSH.UsrMsgBox.SetCB(UsrMessageBox.ShowCallBack);  // エラーダイアログ表示
            CSH.ProgBar.SetCB1(PrgressBarShiwTopMost);  // プログレスバーShow
            CSH.ProgBar.SetCB2(PrgressBarHide);  // プログレスバーHide
        }

        private void MainWindow_SourceInitialized(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// 終了処理
        /// </summary>
        protected virtual void Terminate(object sender, System.ComponentModel.CancelEventArgs e)
		{
			// メッセージループをフックする関数を解除
			HwndSource source = HwndSource.FromHwnd(m_hWnd);
			source.RemoveHook( m_Hook );

			// 独自の終了処理
			CSH.AppMain.Term();

			//if ( m_Dlg01 != null )  m_Dlg01.Close();
			//if ( m_Dlg02 != null )  m_Dlg02.Close();
			//if ( m_Dlg03 != null )  m_Dlg03.Close();
            
            if ( m_SubWnd01 != null ) {             // 2025.4.23 eba add
                m_SubWnd01.m_AllowClose = true;     // 2025.09.04  Modify by GeomLab
                m_SubWnd01.Close();
            }
            if ( m_SubWnd02 != null ) {             // 2025.4.23 eba add
                m_SubWnd02.m_AllowClose = true;     // 2025.09.04  Modify by GeomLab
                m_SubWnd02.Close();
            }
            if ( m_SubWnd03 != null ) {             // 2025.4.23 eba add
                m_SubWnd03.m_AllowClose = true;     // 2025.09.04  Modify by GeomLab
                m_SubWnd03.Close();
            }

            if (m_DlgPrgBar1 != null)
            {           
                m_DlgPrgBar1.m_AllowClose = true;   // 2025.10.2 add eba
                m_DlgPrgBar1.Dispose();
                m_DlgPrgBar1.Close();
            }

            if (m_DlgPrgBar2 != null)
            {           
                m_DlgPrgBar2.m_AllowClose = true;   // 2025.10.2 add eba
                m_DlgPrgBar2.Dispose();
                m_DlgPrgBar2.Close();
            }

            if ( m_DlgPrgBar3 != null ) 
            {
                m_DlgPrgBar3.m_AllowClose = true;   // 2025.09.04  Modify by GeomLab
                m_DlgPrgBar3.Dispose();
                m_DlgPrgBar3.Close();
            }

            if (m_PrgressBar != null)   // 2025.11.14 add eba
            {
                m_PrgressBar.m_AllowClose = true;
                m_PrgressBar.Dispose();
                m_PrgressBar.Close();
            }

        }

        // メッセージループを記述したメソッド
        private IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            if (msg == UsrMsg.WM_MainWnd_Close)
            {
                Close();
            }
            else if (msg == UsrMsg.WM_MainWnd_Btn01)
            {
                //CmdDlg01();		// 2025.4.23 eba del
                CmdSubWnd01();  // 2025.4.23 eba add
            }
            else if (msg == UsrMsg.WM_MainWnd_Btn02)
            {
                //CmdDlg02();		// 2025.4.23 eba del
                CmdSubWnd02();  // 2025.4.23 eba add
            }
            else if (msg == UsrMsg.WM_MainWnd_Btn03)
            {
                //CmdDlg03();		// 2025.4.23 eba del
                 CmdSubWnd03();  // 2025.4.23 eba add
            }
            else if (msg == UsrMsg.WM_Dlg01_Close)
            {
                if (m_Dlg01 != null) m_Dlg01.Hide();
            }
            else if (msg == UsrMsg.WM_Dlg01_Btn01)
            {
                if (m_Dlg01 != null) m_Dlg01.Cmd_Btn01();
            }
            else if (msg == UsrMsg.WM_Dlg01_Btn02)
            {
                if (m_Dlg01 != null) m_Dlg01.Cmd_Btn02();
            }
            else if (msg == UsrMsg.WM_Dlg01_Btn03)
            {
                if (m_Dlg01 != null) m_Dlg01.Cmd_Btn03();
            }
            else if (msg == UsrMsg.WM_Dlg02_Close)
            {
                if (m_Dlg02 != null) m_Dlg02.Hide();
            }
            else if (msg == UsrMsg.WM_Dlg02_Btn01)
            {
                if (m_Dlg02 != null) m_Dlg02.Hide();
            }
            else if (msg == UsrMsg.WM_Dlg03_Close)
            {
                if (m_Dlg03 != null) m_Dlg03.Hide();
            }
            //else if (msg == UsrMsg.WM_Dlg03_Close)    // 2025.09.04 修正 by GeomLab
            //{                                         // 重複？不要？
            //    if (m_Dlg03 != null) m_Dlg03.Hide();
            //}
            else if (msg == UsrMsg.WM_UpdateData1)
            {
                UpdateData01();	// 2025.5.22 add eba test
            }
            else if (msg == UsrMsg.WM_SubWnd01_Btn03)
            {
                m_SubWnd01.CurrentPanel = Panel.Initialize; // イニシャライズ画面表示(2025.7.18yori) // 変更(2025.7.28yori)
            }
            else if (msg == UsrMsg.WM_SubWnd01_Btn04)
            {
                m_SubWnd01.CurrentPanel = Panel._0AxisInitialize; // 0軸イニシャライズ画面表示(2025.7.25yori) // 変更(2025.7.28yori)
            }
            else if (msg == UsrMsg.WM_SubWnd01_Btn05)
            {
                // SubWindow1のボタン無効化(2025.11.20yori)
                SubWindow1_ViewModel SubWnd01ViewModel = new SubWindow1_ViewModel();
                m_SubWnd01.DataContext = SubWnd01ViewModel;
                SubWnd01ViewModel.IsBtn01Enabled = false;
                SubWnd01ViewModel.IsBtn02Enabled = false;
                SubWnd01ViewModel.IsBtn03Enabled = false;
                SubWnd01ViewModel.IsBtn04Enabled = false;
                SubWnd01ViewModel.IsBtn05Enabled = false;
                SubWnd01ViewModel.Btn01Opacity = 0.25;
                SubWnd01ViewModel.Btn02Opacity = 0.25;
                SubWnd01ViewModel.Btn03Opacity = 0.25;
                SubWnd01ViewModel.Btn04Opacity = 0.25;
                SubWnd01ViewModel.Btn05Opacity = 0.25;
                m_SubWnd01.CurrentPanel = Panel.SensorConnection; // スキャナ接続手順画面表示(2025.9.2yori)
            }
            else if (msg == UsrMsg.WM_SubWnd01_Close)
            {
                if (m_SubWnd01 != null) m_SubWnd01.Hide(); // 追加(2025.6.5yori)
            }
            else if (msg == UsrMsg.WM_SubWnd02_Close)
            {
                if (m_SubWnd02 != null) m_SubWnd02.Hide(); // 追加(2025.12.2yori)
            }
            else if (msg == UsrMsg.WM_SubWnd03_Close)
            {
                if (m_SubWnd03 != null) // 追加(2025.11.11yori)
                {
                    CSH.Grp03.Cmd05();
                    m_SubWnd03.Hide(); 
                }
            }
            else if (msg == UsrMsg.WM_SubWnd02_Btn01)
            {

            }
            else if (msg == UsrMsg.WM_SubWnd02_Btn02)
            {

            }
            else if (msg == UsrMsg.WM_SubWnd02_Btn03)
            {
                m_SubWnd02.Cmd01();// 追加(2025.6.12yori)
            }
            else if (msg == UsrMsg.WM_SubWnd02_Btn04)
            {
                m_SubWnd02.Cmd01();// 追加(2025.6.16yori)
            }
            else if (msg == UsrMsg.WM_SubWnd02_Btn05)
            {
                m_SubWnd02.Cmd01();// 追加(2025.6.12yori)
            }
            else if (msg == UsrMsg.WM_SubWnd02_Btn06)
            {

            }
            else if (msg == UsrMsg.WM_InitPanel_Setup) // イニシャライズ画面の初期設定(2025.11.12yori)
            {
                // 現在表示されているPanelクラスを取得
                var Content = m_SubWnd01.MainContent.Content;

                // パネルが表示されており(非null)、表示されているパネルが目的のパネル(Panel.Initialize)が表示されているか確認
                if (Content != null && (Content as PanelBase).Type == Panel.Initialize)
                {
                     // ContentがInitializePanelであればキャストしてアクセスする
                     (Content as InitializePanel).InitPanelSetup();
                }
            }
            else if (msg == UsrMsg.WM_InitPanel_Update) // 変更(2025.10.27yori)
            {
                // 現在表示されているPanelクラスを取得
                var Content = m_SubWnd01.MainContent.Content;

                // パネルが表示されており(非null)、表示されているパネルが目的のパネル(Panel.Initialize)が表示されているか確認
                if (Content != null && (Content as PanelBase).Type == Panel.Initialize)
                {
                    // ContentがInitializePanelであればキャストしてアクセスする
                    (Content as InitializePanel).InitPanelUpdate();
                }
            }
            else if (msg == UsrMsg.WM_SubWnd01_Panel_Hide)
            {
                m_SubWnd01.MainContent.Content = null; // SubWnd01のパネル非表示(2025.7.25yori)
            }
            else if (msg == UsrMsg.WM_DlgPrgBar1_Show)
            {
                CmdDlgPrgBar1(); // プログレスバー1表示(2025.7.17yori)
            }
            else if (msg == UsrMsg.WM_DlgPrgBar1_Close)
            {
                m_DlgPrgBar1.Hide();// プログレスバー1非表示(2025.7.17yori)
                //m_DlgPrgBar1.Dispose();// プログレスバー1非表示(2025.7.17yori)
            }
            else if (msg == UsrMsg.WM_DlgPrgBar2_Show)
            {
                CmdDlgPrgBar2(); // プログレスバー2表示(2025.7.30yori)
            }
            else if (msg == UsrMsg.WM_DlgPrgBar2_Close)
            {
                m_DlgPrgBar2.Hide();// プログレスバー2非表示(2025.7.30yori)
            }
            else if (msg == UsrMsg.WM_DlgPrgBar3_Show)
            {
                CmdDlgPrgBar3(); // プログレスバー3表示(2025.7.31yori)
            }
            else if (msg == UsrMsg.WM_DlgPrgBar3_Close)
            {
                m_DlgPrgBar3.Hide();// プログレスバー3非表示(2025.7.31yori)
            }
            else if (msg == UsrMsg.WM_ContactInspectionPanel_MesCallBack)
            {
                // 現在表示されているPanelクラスを取得
                var Content = m_SubWnd02.MainContent.Content;

                // パネルが表示されており(非null)、表示されているパネルが目的のパネル(Panel.ContactInspection)が表示されているか確認
                if (Content != null && (Content as PanelBase).Type == Panel.ContactInspection)
                {
                    // ContentがContactInspectionPanelであればキャストしてアクセスする
                    (Content as ContactInspectionPanel).MesCallBack();
                }
            }
            else if (msg == UsrMsg.WM_ContactInspectionPanel_ParaOutCallBack)
            {
                // 現在表示されているPanelクラスを取得
                var Content = m_SubWnd02.MainContent.Content;

                // パネルが表示されており(非null)、表示されているパネルが目的のパネル(Panel.ContactInspection)が表示されているか確認
                if (Content != null && (Content as PanelBase).Type == Panel.ContactInspection)
                {
                    // ContentがContactInspectionPanelであればキャストしてアクセスする
                    (Content as ContactInspectionPanel).ParaOutCallBack();
                }
            }
            else if (msg == UsrMsg.WM_ScannerAlignmentPanel_MesCallBack) // 追加(2025.12.3yori)
            {
                // 現在表示されているPanelクラスを取得
                var Content = m_SubWnd02.MainContent.Content;

                // パネルが表示されており(非null)、表示されているパネルが目的のパネル(Panel.ScannerAlignment)が表示されているか確認
                if (Content != null && (Content as PanelBase).Type == Panel.ScannerAlignment)
                {
                    // ContentがScannerAlignmentPanelであればキャストしてアクセスする
                    (Content as ScannerAlignmentPanel).MesCallBack();
                }
            }
            else if (msg == UsrMsg.WM_ScannerAlignmentPanel_ResultCallBack) // 追加(2025.12.9yori)
            {
                // 現在表示されているPanelクラスを取得
                var Content = m_SubWnd02.MainContent.Content;

                // パネルが表示されており(非null)、表示されているパネルが目的のパネル(Panel.ScannerAlignment)が表示されているか確認
                if (Content != null && (Content as PanelBase).Type == Panel.ScannerAlignment)
                {
                    // ContentがScannerAlignmentPanelであればキャストしてアクセスする
                    (Content as ScannerAlignmentPanel).ResultCallBack();
                }
            }
            else if (msg == UsrMsg.WM_Init0Panel_Setup)
            {
                Init0PanelSetup(); // 追加(2025.10.2yori)
            }
            else if (msg == UsrMsg.WM_ContactSelfJudgmentPanel_Update) // 有接触自己診断画面更新(2025.10.3yori)
            {
                // 現在表示されているPanelクラスを取得
                var Content = m_SubWnd02.MainContent.Content;

                // パネルが表示されており(非null)、表示されているパネルが目的のパネル(Panel.ContactSelfJudgment)が表示されているか確認
                if (Content != null && (Content as PanelBase).Type == Panel.ContactSelfJudgment)
                {
                    // ContentがContactSelfJudgmentPanelであればキャストしてアクセスする
                    (Content as ContactSelfJudgmentPanel).PanelUpdate();
                }
            }
            else if (msg == UsrMsg.WM_MainWnd_OtherApp_Connected) // 追加(2025.11.19yori)
            {
                MainWindowViewModel vm = (MainWindowViewModel)this.DataContext;
                vm.IsBtnEnabled = false;
                vm.BtnOpacity = 0.25;
            }
            else if (msg == UsrMsg.WM_MainWnd_OtherApp_Disconnected) // 追加(2025.11.19yori)
            {
                MainWindowViewModel vm = (MainWindowViewModel)this.DataContext;
                vm.IsBtnEnabled = true;
                vm.BtnOpacity = 1.0;
            }
            else if (msg == UsrMsg.WM_ScannerAlignmentPanel_Show) // 追加(2025.12.5yori)
            {
                m_SubWnd02.CurrentPanel = Panel.ScannerAlignment; // スキャナアライメント画面表示
            }
            else if (msg == UsrMsg.WM_ScannerAlignmentPanel_Setup) // アライメント画面の初期設定(2025.12.5yori)
            {
                // 現在表示されているPanelクラスを取得
                var Content = m_SubWnd02.MainContent.Content;

                // パネルが表示されており(非null)、表示されているパネルが目的のパネル(Panel.Initialize)が表示されているか確認
                if (Content != null && (Content as PanelBase).Type == Panel.ScannerAlignment)
                {
                    // ContentがScannerAlignmentPanelであればキャストしてアクセスする
                    (Content as ScannerAlignmentPanel).ScannerAlignmentPanelSetup();
                }
            }

            return IntPtr.Zero;
        }

		/// <summary>
		/// ボタンClick時の処理(Btn01)
		/// </summary>
		private void Click_Btn01(object sender, RoutedEventArgs e)
		{
			// ダイアログ表示
			//CmdDlg01();	// 2025.4.23 eba del
			CmdSubWnd01();  // 2025.4.23 eba add
            m_SubWnd03.ApiScanValue.IsButtonEnabled = true; // アプリ側から接続した場合にスキャナのスタートとリセットボタンを押せるようにする。(2025.9.3yori)
            m_SubWnd03.ApiScanValue.ButtonOpacity = 1.0; // 追加(2025.11.20yori)

            //UpdateData1();	// 2025.5.22 test ebs
        }

		/// <summary>
		/// ボタンClick時の処理(Btn02)
		/// </summary>
		private void Click_Btn02(object sender, RoutedEventArgs e)
		{
            // ダイアログ表示
            //CmdDlg02();	// 2025.4.23 eba del
            CmdSubWnd02();  // 2025.4.23 eba add
        }

		/// <summary>
		/// ボタンClick時の処理(Btn03)
		/// </summary>
		private void Click_Btn03(object sender, RoutedEventArgs e)
		{
            // ダイアログ表示
            //CmdDlg03();	// 2025.4.23 eba del
            CmdSubWnd03();  // 2025.4.23 eba add
        }

		/// <summary>
		/// ボタンClick時の処理(Btn04)
		/// </summary>
		private void Click_Close(object sender, RoutedEventArgs e)
		{
			Close();
		}

        /// <summary>
        /// Dlg01の表示
        /// </summary>
        private void CmdDlg01()
		{
			if ( m_Dlg01.IsVisible == false ) {
				m_Dlg01.Owner = Application.Current.MainWindow;
				m_Dlg01.WindowStartupLocation = WindowStartupLocation.CenterOwner;

				Dlg01_ViewModel vm = (Dlg01_ViewModel)m_Dlg01.DataContext;
				vm.A = 123;
				vm.B = 9.99;
				vm.C = "abcdef";
				vm.D = -1;
				vm.E = 0.0;
				vm.F = "init";

				// モーダレスダイアログとして表示
				m_Dlg01.Show();

				// モーダルダイアログとして表示
				//m_Dlg01.ShowDialog();

				// Window のアクティブ化
				UIPlus.ForceActive( m_Dlg01.m_hWnd );
			}
		}

		/// <summary>
		/// Dlg02の表示
		/// </summary>
		private void CmdDlg02()
		{
			if ( m_Dlg02.IsVisible == false ) {
				m_Dlg02.Owner = Application.Current.MainWindow;
				m_Dlg02.WindowStartupLocation = WindowStartupLocation.CenterOwner;

				// モーダレスダイアログとして表示
				m_Dlg02.Show();

				// モーダルダイアログとして表示
				//m_Dlg02.ShowDialog();

				// Window のアクティブ化
				UIPlus.ForceActive( m_Dlg02.m_hWnd );
			}
		}

		/// <summary>
		/// Dlg03の表示
		/// </summary>
		private void CmdDlg03()
		{
			if ( m_Dlg03.IsVisible == false ) {
				m_Dlg03.Owner = Application.Current.MainWindow;
				m_Dlg03.WindowStartupLocation = WindowStartupLocation.CenterOwner;

				// モーダレスダイアログとして表示
				m_Dlg03.Show();

				// モーダルダイアログとして表示
				//m_Dlg03.ShowDialog();

				// Window のアクティブ化
				UIPlus.ForceActive( m_Dlg03.m_hWnd );
			}
		}

        /// <summary>
        /// SubWindow1の表示	2025.4.23 eba add
        /// </summary>
        private void CmdSubWnd01()
        {
            // 2025.09.04  Add by GeomLab 
            if ( m_SubWnd01 == null ) return;

			// C++側の処理
			CSH.AppMain.SubWnd01();

			// C#側の処理
            if (m_SubWnd01.IsVisible == false)
            {
                m_SubWnd01.Owner = Application.Current.MainWindow;
                m_SubWnd01.WindowStartupLocation = WindowStartupLocation.CenterOwner;

                // モーダレスダイアログとして表示
                m_SubWnd01.Show();

                // モーダルダイアログとして表示
                //m_SubWnd01.ShowDialog();

                // Window のアクティブ化
                //UIPlus.ForceActive(m_SubWnd01.hWnd); // m_hWnd→hWnd(2025.7.29yori)
                // SetForegroundWindowの代わりにTopmostを使用する。(2025.11.7yori)
                m_SubWnd01.Topmost = true;  // 一時的に最前面にする。
                m_SubWnd01.Activate();      // ウィンドウをアクティブ化
                m_SubWnd01.Topmost = false; // 元に戻す。
            }
        }

        /// <summary>
        /// SubWindow2の表示	2025.4.23 eba add
        /// </summary>
        private void CmdSubWnd02()
        {
            // 2025.09.04  Add by GeomLab 
            if ( m_SubWnd02 == null ) return;

            // C++側の処理
            CSH.AppMain.SubWnd02();

            // C#側の処理
            if (m_SubWnd02.IsVisible == false)
            {
                m_SubWnd02.Owner = Application.Current.MainWindow;
                m_SubWnd02.WindowStartupLocation = WindowStartupLocation.CenterOwner;

                // モーダレスダイアログとして表示
                m_SubWnd02.Show();

                // モーダルダイアログとして表示
                //m_SubWnd02.ShowDialog();

                // Window のアクティブ化
                //UIPlus.ForceActive(m_SubWnd02.hWnd); // m_hWnd→hWnd(2025.7.29yori)
                // 1.アプリ起動→2.PolyWorks起動→3.接続→4.SubWindowを起動すると、フリーズ状態(SetForegroundWindow関数が戻らない)となるため、
                // SetForegroundWindowの代わりにTopmostを使用する。(2025.11.7yori)
                m_SubWnd02.Topmost = true;  // 一時的に最前面にする。
                m_SubWnd02.Activate();      // ウィンドウをアクティブ化
                m_SubWnd02.Topmost = false; // 元に戻す。
            }
        }

        /// <summary>
        /// SubWindow3の表示	2025.4.23 eba add
        /// </summary>
        private void CmdSubWnd03()
        {
            // DEBUG
            //m_DlgPrgBar3.ShowAndStart(this);
            //return;

            // 2025.09.04  Add by GeomLab 
            if ( m_SubWnd03 == null ) return;

            // C++側の処理
            CSH.AppMain.SubWnd03();

            // C#側の処理
            if (m_SubWnd03.IsVisible == false)
            {
                m_SubWnd03.Owner = Application.Current.MainWindow;
                m_SubWnd03.WindowStartupLocation = WindowStartupLocation.CenterOwner;

                // モーダレスダイアログとして表示
                m_SubWnd03.Show();

                // モーダルダイアログとして表示
                //m_SubWnd03.ShowDialog();

                // Window のアクティブ化
                //UIPlus.ForceActive(m_SubWnd03.hWnd); // m_hWnd→hWnd(2025.7.29yori)
                // SetForegroundWindowの代わりにTopmostを使用する。(2025.11.7yori)
                m_SubWnd03.Topmost = true;  // 一時的に最前面にする。
                m_SubWnd03.Activate();      // ウィンドウをアクティブ化
                m_SubWnd03.Topmost = false; // 元に戻す。
            }
        }

        /// <summary>
        /// DlgPrgBar1の表示
        /// プログレスバー追加のため番号追加(2025.7.30yori)
        /// </summary>
        private void CmdDlgPrgBar1()
        {
            // 2025.09.04  Add by GeomLab 
            if ( m_DlgPrgBar1 == null ) return;

            if (m_DlgPrgBar1.IsVisible == false)
            {
                m_DlgPrgBar1.Owner = Application.Current.MainWindow;
                m_DlgPrgBar1.WindowStartupLocation = WindowStartupLocation.CenterOwner;

                // モーダレスダイアログとして表示
                m_DlgPrgBar1.Show();

                // モーダルダイアログとして表示
                //m_DlgPrgBar1.ShowDialog();

                // Window のアクティブ化
                UIPlus.ForceActive(m_DlgPrgBar1.m_hWnd);
            }
        }
        
        /// <summary>
        /// DlgPrgBar2の表示(2025.7.30yori)
        /// </summary>
        private void CmdDlgPrgBar2()
        {
            // 2025.09.04  Add by GeomLab 
            if ( m_DlgPrgBar2 == null ) return;

            if (m_DlgPrgBar2.IsVisible == false)
            {
                m_DlgPrgBar2.Owner = Application.Current.MainWindow;
                m_DlgPrgBar2.WindowStartupLocation = WindowStartupLocation.CenterOwner;

                // モーダレスダイアログとして表示
                m_DlgPrgBar2.Show();

                // モーダルダイアログとして表示
                //m_DlgPrgBar2.ShowDialog();

                // Window のアクティブ化
                UIPlus.ForceActive(m_DlgPrgBar2.m_hWnd);
            }
        }

        /// <summary>
        /// DlgPrgBar3の表示(2025.7.31yori)
        /// </summary>
        private void CmdDlgPrgBar3()
        {
            // 2025.09.04  Add by GeomLab 
            if ( m_DlgPrgBar3 == null ) return;

            if (m_DlgPrgBar3.IsVisible == false)
            {
                m_DlgPrgBar3.Owner = Application.Current.MainWindow;
                m_DlgPrgBar3.WindowStartupLocation = WindowStartupLocation.CenterOwner;

                // モーダレスダイアログとして表示
                m_DlgPrgBar3.Show();

                // モーダルダイアログとして表示
                //m_DlgPrgBar3.ShowDialog();

                // Window のアクティブ化
                //UIPlus.ForceActive(m_DlgPrgBar2.m_hWnd);
                UIPlus.ForceActive(m_DlgPrgBar3.m_hWnd);    // 2025.09.04 修正 by GeomLab
            }
        }


        /// <summary>
        /// DlgPrgBar1の表示
        /// プログレスバー追加のため番号追加(2025.7.30yori)
        /// </summary>
        private void CmdPrgressBar()
        {
            // 2025.09.04  Add by GeomLab 
            if (m_PrgressBar == null) return;

            if (m_PrgressBar.IsVisible == false)
            {
                m_PrgressBar.Owner = Application.Current.MainWindow;
                m_PrgressBar.WindowStartupLocation = WindowStartupLocation.CenterOwner;

                // モーダレスダイアログとして表示
                m_PrgressBar.Show();

                // モーダルダイアログとして表示
                //m_DlgPrgBar1.ShowDialog();

                // Window のアクティブ化
                UIPlus.ForceActive(m_PrgressBar.m_hWnd);
            }
        }

        /// <summary>
        /// App全体が使うデータの更新
        /// 主に測定機のステータス情報の更新
        /// </summary>
        private void UpdateData01()
        {
            //double Tmp1; // 未使用のため、削除予定(2025.8.30yori)
            //string sts1 = null; // 未使用のため、削除予定(2025.8.30yori)
            //int sts1_count = 256; // 未使用のため、削除予定(2025.8.30yori)

            Status01 sts = new Status01();
            sts.tempature = new double[7];

            //CSH.Grp01.CmdXX(out Tmp1, ref sts1, sts1_count);  // 2025.5.22 add eba test
            CSH.AppMain.UpDateData01(out sts);  // 2025.5.28 add eba test

            // 未使用のため、コメントアウト、削除予定(2025.11.19yori)
            //MainWindowViewModel vm = (MainWindowViewModel)this.DataContext;
            //vm.A = Tmp1;
            //vm.B = sts1;
            //vm.MODE = sts.mode;
            //vm.TMP1 = sts.tempature[0];
            // メイン表示更新
            //ValA.GetBindingExpression(TextBox.TextProperty).UpdateTarget();
            //ValB.GetBindingExpression(TextBox.TextProperty).UpdateTarget();

            // プローブ名称とID更新(2025.9.8yori)
            Application.Current.Dispatcher.Invoke(() => // AppMain.cppのスレッドからC#側のGUI操作を行う場合のコード
            {
                m_SubWnd02.ProbeSettingValue.NameIndex = sts.probe_id;
                m_SubWnd02.ProbeSettingValue.Id = sts.probe_id.ToString();
            });
        }

        /// <summary>
        /// 0軸イニシャライズ画面の初期設定(2025.10.2yori)
        /// </summary>
        private void Init0PanelSetup()
        {
            Status01 sts = new Status01();
            CSH.AppMain.UpDateData01(out sts);
            Application.Current.Dispatcher.Invoke(() =>
            {
                if ( sts.probe_id == 0 ) m_SubWnd01._0AxisInitializeValue.Init0Image = "Image/init_No0.PNG";
                if ( sts.probe_id > 2 && sts.probe_id < 20 ) m_SubWnd01._0AxisInitializeValue.Init0Image = "Image/init_VPR81.PNG";
            });
        }

        /// <summary>
        /// コールバック関数（C++側からコールされる関数）
        /// </summary>
        public static void ShowErr(int msgID)
		{
		    int     rc;
			string	msg = null;
			int		msg_count = 512;

			// IDからメッセージを取得
			rc = CSH.ErrMsg.GetMsg( msgID, ref msg, msg_count );
			if ( rc == 0 )
			{
 				MessageBox.Show(
					msg,
					"DlgMain",
					MessageBoxButton.OK,
					MessageBoxImage.Information
				);
			}
		}

		/// <summary>
		/// コールバック関数（C++側からコールされる関数）
		/// </summary>
		public static void SendMsg(int msgID)
		{
			if ( m_hWnd != IntPtr.Zero ) {
				UsrMsg.SendMsg( m_hWnd, msgID );
			}
		}


        /// <summary>
        /// DlgPrgBar1の表示
        /// プログレスバー追加のため番号追加(2025.7.30yori)
        /// </summary>
        public static void PrgressBarShiwTopMost(int id)
        {
            // 現在がUIスレッドでなければDispatcher経由で実行
            if (!Application.Current.Dispatcher.CheckAccess())
            {
                Application.Current.Dispatcher.Invoke(() => PrgressBarShiwTopMost(id));
            }

            if (m_PrgressBar == null) return;

            if (m_PrgressBar.IsVisible == false)
            {
                m_PrgressBar.SetId(id);

                m_PrgressBar.Owner = Application.Current.MainWindow;
                m_PrgressBar.WindowStartupLocation = WindowStartupLocation.CenterOwner;

                // モーダレスダイアログとして表示
                m_PrgressBar.Show();

                // モーダルダイアログとして表示
                //m_DlgPrgBar1.ShowDialog();

                // Window のアクティブ化
                UIPlus.ForceActive(m_PrgressBar.m_hWnd);
            }
        }

        /// <summary>
        /// DlgPrgBar1の表示
        /// プログレスバー追加のため番号追加(2025.7.30yori)
        /// </summary>
        public static void PrgressBarHide()
        {
            // 現在がUIスレッドでなければDispatcher経由で実行
            if (!Application.Current.Dispatcher.CheckAccess())
            {
                Application.Current.Dispatcher.Invoke(() => PrgressBarHide());
            }

            if (m_PrgressBar == null) return;

            if (m_PrgressBar.IsVisible == true)
            {
                m_PrgressBar.Hide();
            }
        }

    }
}
