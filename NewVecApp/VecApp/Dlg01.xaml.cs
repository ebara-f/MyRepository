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
	/// Dlg01.xaml の相互作用ロジック
	/// </summary>
	public partial class Dlg01 : Window
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
		public Dlg01()
		{
			InitializeComponent();
			this.DataContext = new Dlg01_ViewModel();

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
		/// ボタンClick時の処理(Btn02)
		/// </summary>
		private void Button_Click_Btn02(object sender, RoutedEventArgs e)
		{
			Cmd_Btn02();
		}

		/// <summary>
		/// ボタンClick時の処理(Btn03)
		/// </summary>
		private void Button_Click_Btn03(object sender, RoutedEventArgs e)
		{
			Cmd_Btn03();
		}

		/// <summary>
		/// ボタンClick時の処理(Btn01)
		/// </summary>
		public void Cmd_Btn01()
		{
		    // データ更新
			ValA.GetBindingExpression(TextBox.TextProperty).UpdateSource();
			ValB.GetBindingExpression(TextBox.TextProperty).UpdateSource();
			ValC.GetBindingExpression(TextBox.TextProperty).UpdateSource();

			Dlg01_ViewModel vm = (Dlg01_ViewModel)this.DataContext;

			int    A = vm.A;
			double B = vm.B;
			string C = vm.C;

			/*----- exec command -----*/
			int rc = CSH.Grp01.Cmd02(A, B, C);
			if (rc != 0)
			{
 				MessageBox.Show(
					"コマンド実行エラー",
					"Dlg01",
					MessageBoxButton.OK,
					MessageBoxImage.Error
				);
				goto FIN;
			}

			/*----- close dialog -----*/
		FIN:;
			this.Hide();
		}

		/// <summary>
		/// ボタンClick時の処理(Btn02)
		/// </summary>
		public void Cmd_Btn02()
		{
			this.Hide();
		}

		/// <summary>
		/// ボタンClick時の処理(Btn03)
		/// </summary>
		public void Cmd_Btn03()
		{
		    // データ更新
			ValA.GetBindingExpression(TextBox.TextProperty).UpdateSource();
			ValB.GetBindingExpression(TextBox.TextProperty).UpdateSource();
			ValC.GetBindingExpression(TextBox.TextProperty).UpdateSource();

			Dlg01_ViewModel vm = (Dlg01_ViewModel)this.DataContext;

			int    A = vm.A;
			double B = vm.B;
			string C = vm.C;

			int	   D;
			double E;

			string	F = null;
			int		F_count = 512;

			/*----- exec command -----*/
			int rc = CSH.Grp01.Cmd03(
							A, B, C,
                            out D, out E, ref F, F_count
				);
			if (rc != 0)
			{
 				MessageBox.Show(
					"コマンド実行エラー",
					"Dlg01",
					MessageBoxButton.OK,
					MessageBoxImage.Error
				);
			}

			if ( rc == 0)
			{
				vm.D = D;
				vm.E = E;
				vm.F = F;
			}

		    // 表示更新
			ValD.GetBindingExpression(TextBox.TextProperty).UpdateTarget();
			ValE.GetBindingExpression(TextBox.TextProperty).UpdateTarget();
			ValF.GetBindingExpression(TextBox.TextProperty).UpdateTarget();
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
					"Dlg01",
					MessageBoxButton.OK,
					MessageBoxImage.Information
				);
			}
		}
	}
}
