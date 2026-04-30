using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
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
using System.Windows.Shapes;
using CSH;

namespace VecApp
{
    /// <summary>
    /// DlgMI.xaml の相互作用ロジック
    /// </summary>
    public partial class DlgMI : Window
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
        public IntPtr m_hWnd;       // ウィンドウハンドル

        /// <summary>
        /// Closeを許可するか(falseの間は Closeが要求されてもHideに置換2026.4.14yori)
        /// </summary>
        public bool m_AllowClose { get; set; } = false;

        /// <summary>
        /// 非同期処理や長時間実行される処理を「キャンセル可能」にする仕組みを提供するクラス(2026.4.14yori)
        /// </summary>
        private CancellationTokenSource m_CTS;

        private int limitfg = 0; // 追加(2026.4.17yori)

        public DlgMI()
        {
            InitializeComponent();

            // ウィンドウズハンドルの取得
            m_hWnd = new WindowInteropHelper(this).EnsureHandle();

            this.DataContext = new DlgMI_ViewModel(); // 追加(2026.4.12yori)

            //// 追加(2026.4.14yori)
            this.ViewModel.ImageSource = "Image/init_V7.png";

            this.ViewModel.Marks[0].X = 420;
            this.ViewModel.Marks[0].Y = 365;
            this.ViewModel.Marks[1].X = 490;
            this.ViewModel.Marks[1].Y = 315;
            this.ViewModel.Marks[2].X = 410;
            this.ViewModel.Marks[2].Y = 60;
            this.ViewModel.Marks[3].X = 295;
            this.ViewModel.Marks[3].Y = 30;
            this.ViewModel.Marks[4].X = 240;
            this.ViewModel.Marks[4].Y = 190;
            this.ViewModel.Marks[5].X = 330;
            this.ViewModel.Marks[5].Y = 245;
            this.ViewModel.Marks[6].X = 170;
            this.ViewModel.Marks[6].Y = 290;

            this.ViewModel.Marks[0].Visibility = Visibility.Hidden;
            this.ViewModel.Marks[1].Visibility = Visibility.Hidden;
            this.ViewModel.Marks[2].Visibility = Visibility.Hidden;
            this.ViewModel.Marks[3].Visibility = Visibility.Hidden;
            this.ViewModel.Marks[4].Visibility = Visibility.Hidden;
            this.ViewModel.Marks[5].Visibility = Visibility.Hidden;
            this.ViewModel.Marks[6].Visibility = Visibility.Hidden;
            ////
        }

        public DlgMI_ViewModel ViewModel // 追加(2026.4.14yori)
        {
            get => this.DataContext as DlgMI_ViewModel;
        }

        /// <summary>
        /// ×ボタン（Close）やアプリ終了時の終了処理(2026.4.14yori)
        /// </summary>
        private void Terminate(object sender, CancelEventArgs e)
        {
            if (m_AllowClose == true)
            {
                Cancel();
                Dispose();
            }
            else
            {
                e.Cancel = true;    // 閉じさせない
                Cancel();           // バックグラウンド停止
                this.Hide();        // 画面の非表示
            }
        }

        /// <summary>
        /// 現在の処理のキャンセル(2026.4.14yori)
        /// </summary>
        public void Cancel()
        {
            try
            {
                if (m_CTS != null) m_CTS.Cancel();
            }
            catch
            {
                // 何もしない
            }
        }

        /// <summary>
        /// 解放処理(2026.4.14yori)
        /// </summary>
        public void Dispose()
        {
            if (m_CTS != null)
            {
                m_CTS.Cancel();
                m_CTS.Dispose();
                m_CTS = null;
            }
        }

        // 関節リミットアラーム画面表示(2026.4.19yori)
        public void JointLimitAlarmShow()
        {
            CSH.AppMain.JointLimitAlarm(out limitfg);
            // No.1関節
            if ((limitfg & 2) == 2)
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.Marks[1].Visibility = Visibility.Visible;
                });
            }
            else
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.Marks[1].Visibility = Visibility.Hidden;
                });
            }

            // No.3関節
            if ((limitfg & 8) == 8)
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.Marks[3].Visibility = Visibility.Visible;
                });
            }
            else
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.Marks[3].Visibility = Visibility.Hidden;
                });
            }

            // No.4関節
            if ((limitfg & 16) == 16)
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.Marks[4].Visibility = Visibility.Visible;
                });
            }
            else
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.Marks[4].Visibility = Visibility.Hidden;
                });
            }

            // No.5関節
            if ((limitfg & 32) == 32)
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.Marks[5].Visibility = Visibility.Visible;
                });
            }
            else
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.Marks[5].Visibility = Visibility.Hidden;
                });
            }

            // No.6関節
            if ((limitfg & 64) == 64)
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.Marks[6].Visibility = Visibility.Visible;
                });
            }
            else
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.Marks[6].Visibility = Visibility.Hidden;
                });
            }
        }
    }
}
