using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
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
    /// DlgMsg.xaml の相互作用ロジック
    /// </summary>
    public partial class DlgMsg : Window
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
        public IntPtr m_hWnd;		// ウィンドウハンドル

        public DlgMsg()
        {
            InitializeComponent();

            // ウィンドウズハンドルの取得
            m_hWnd = new WindowInteropHelper(this).EnsureHandle();
        }

        /// <summary>
        /// ボタンClick時の処理
        /// </summary>
        private void Click_CloseBtn(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
