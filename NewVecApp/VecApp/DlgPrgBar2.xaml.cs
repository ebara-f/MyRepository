using System;
using System.Collections.Generic;
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

namespace VecApp
{
    /// <summary>
    /// DlgPrgBar2.xaml の相互作用ロジック
    /// </summary>
    public partial class DlgPrgBar2 : Window
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

		public DlgPrgBar2_ViewModel vm;

        /// <summary>
        /// メンバー変数
        /// </summary>
        public IntPtr	m_hWnd;		// ウィンドウハンドル

		/// <summary>
		/// 初期化処理
		/// </summary>
        public DlgPrgBar2()
        {
            InitializeComponent();
            this.DataContext = vm = new DlgPrgBar2_ViewModel(this);

            vm.StartProc();

			// ウィンドウズハンドルの取得
			m_hWnd = new WindowInteropHelper(this).EnsureHandle();
        }

		/// <summary>
		/// 終了処理
		/// </summary>
		protected virtual void Terminate(object sender, System.ComponentModel.CancelEventArgs e)
		{
			// 終了処理
		}

		/// <summary>
		/// ボタンClick時の処理(Btn01)
		/// </summary>
		private void Button_Click_Btn01(object sender, RoutedEventArgs e)
		{
			Cmd_Btn01();
		}

		/// <summary>
		/// ボタンClick時の処理(Btn01)
		/// </summary>
		public void Cmd_Btn01()
		{
			this.Hide();
		}
	}
}
