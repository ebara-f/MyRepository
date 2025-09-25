using System;
using System.Collections.Generic;
using System.Data;
using System.Diagnostics;
using System.IO.MemoryMappedFiles;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace VecApp
{
	/// <summary>
	/// DlgPass.xaml の相互作用ロジック
	/// </summary>
	public partial class DlgPass : Window
	{
		#region 最大化・最小化・閉じるボタンの非表示設定

		[DllImport("user32.dll", SetLastError = true)]
		private static extern int GetWindowLong(IntPtr hWnd, int nIndex);

		[DllImport("user32.dll")]
		private static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

		private void Window_Loaded(object sender, RoutedEventArgs e)
		{
			const int GWL_STYLE = -16;
			const int WS_SYSMENU = 0x80000;

			// SYSMENUを非表示にする
			var hwnd = new WindowInteropHelper((Window)sender).Handle;
			SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SYSMENU);
		}

		#endregion

        /// <summary>
        /// メンバー変数
        /// </summary>
        public IntPtr	m_hWnd;		// ウィンドウハンドル

		/// <summary>
		/// 初期化処理
		/// </summary>
		public DlgPass()
		{
			InitializeComponent();
			this.DataContext = new DlgPass_ViewModel();

			// ウィンドウズハンドルの取得
			m_hWnd = new WindowInteropHelper(this).EnsureHandle();
		}
        private DlgPass_ViewModel ViewModel
        {
            get => this.DataContext as DlgPass_ViewModel;
        }

        /// <summary>
        /// 終了処理
        /// </summary>
        protected virtual void Terminate(object sender, System.ComponentModel.CancelEventArgs e)
		{
			// 終了処理
		}

		/// <summary>
		/// コールバック関数（C++側からコールされる関数）
		/// </summary>
		public static void ShowErr(int msgID)
		{
		    int     rc;
			string	msg = null;
			int		msg_count = 512;

			rc = CSH.ErrMsg.GetMsg( msgID, ref msg, msg_count );
			if ( rc == 0 )
			{
 				MessageBox.Show(
					msg,
					"DlgPass",
					MessageBoxButton.OK,
					MessageBoxImage.Information
				);
			}
		}
		private void Button_Click_OK(object sender, RoutedEventArgs e)
        {
			if (ViewModel.Pass == "kosaka")
			{
				DialogResult = true;
			}
			else
			{
                DialogResult = false;
            }
			
			this.Hide();
        }

		private void Button_Click_Cancel(object sender, RoutedEventArgs e)
		{
            DialogResult = false;
            this.Hide();
		}

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            this.Visibility = Visibility.Collapsed;
        }
    }
}
