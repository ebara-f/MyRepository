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
	public partial class DlgBarLen : Window
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
		public DlgBarLen()
		{
			InitializeComponent();
			this.DataContext = new DlgBarLen_ViewModel();

			// ウィンドウズハンドルの取得
			m_hWnd = new WindowInteropHelper(this).EnsureHandle();
		}
        public DlgBarLen_ViewModel ViewModel
        {
            get => this.DataContext as DlgBarLen_ViewModel;
        }

        /// <summary>
        /// 終了処理
        /// </summary>
        protected virtual void Terminate(object sender, System.ComponentModel.CancelEventArgs e)
		{
			// 終了処理
		}

		private void Button_Click_OK(object sender, RoutedEventArgs e)
        {
            DialogResult = true; // ShowDialog()がtrueを返す
            Close();
        }

		private void Button_Click_Cancel(object sender, RoutedEventArgs e)
		{
            DialogResult = false; // ShowDialog()がtrueを返す
            Close();
        }

        /*private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {

        }*/
    }
}
