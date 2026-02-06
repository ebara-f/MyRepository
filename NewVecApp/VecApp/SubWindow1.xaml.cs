using System;
using System.Collections.Generic;
using System.Linq;
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
using System.Diagnostics;
using System.ComponentModel;
using CSH;
using System.Runtime.InteropServices; // 追加(2026.2.6yori)

namespace VecApp
{
    /// <summary>
    /// SubWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class SubWindow1 : SubWindowBase
    {
        // 2025.09.04  Modify by GeomLab
        // MainWindow から終了させるときだけ true にする
        public bool m_AllowClose { get; set; } = false;

        /// <summary>
        /// メンバー変数
        /// </summary>
        //public IntPtr m_hWnd;		// ウィンドウハンドル // 削除予定(2025.7.28yori)

        public InitializeViewModel InitializeValue = new InitializeViewModel();

        public SensorConnectionViewModel SensorConnectionValue = new SensorConnectionViewModel(); // 変更(2025.10.28yori)

        public _0AxisInitializeViewModel _0AxisInitializeValue = new _0AxisInitializeViewModel(); // 変更(2025.10.2yori)

        //// ×ボタンを非表示にするたの追加コード(2026.2.6yori)
        [DllImport("user32.dll")]
        private static extern int GetWindowLong(IntPtr hWnd, int nIndex);

        [DllImport("user32.dll")]
        private static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

        private const int GWL_STYLE = -16;
        private const int WS_SYSMENU = 0x00080000; // システムメニュー（×ボタン含む）
        ////

        public SubWindow1()
        {
            InitializeComponent();
            this.DataContext = new SubWindow1_ViewModel(); // コメントアウト(2025.8.12yori) // コメントアウト解除(2025.11.19yori)

            // ウィンドウズハンドルの取得
            //m_hWnd = new WindowInteropHelper(this).EnsureHandle(); // 削除予定(2025.7.28yori)

            // ×ボタンを非表示にする。(2026.2.6yori)
            HideCloseButton();

            // Beak Masterで0軸イニシャライズは不要なため、無効化(2025.12.18yori)
            SubWindow1_ViewModel vm = (SubWindow1_ViewModel)DataContext;
            vm.IsBtn04Enabled = false;
            vm.Btn04Opacity = 0.25;
        }

        /// <summary>
        /// ×ボタンクリックでCloseしない終了処理
        /// 2025.5.23 add eba
        /// </summary>
        protected virtual void Terminate(object sender, System.ComponentModel.CancelEventArgs e)
        {
            // 2025.09.04  Modify by GeomLab
            if ( m_AllowClose == false ) {
                e.Cancel = true;
                this.CurrentPanel = Panel.None; // 再度、SubWindowを表示したときに前に表示していた画面を表示しないようにする。(2025.8.12yori)
                this.Hide();
            }
        }

        // 接続
        private void Click_Btn01(object sender, RoutedEventArgs e)
        {
            // C++で実装した処理を実行
            CSH.Grp01.Cmd01();  // 追加(2025.4.28yori)

            // this.CurrentPanel = Panel.Initialize; // ここではイニシャライズを実施しない。(2025.7.30yori)

            // 0軸イニシャライズボタン有効無効の機種場合分け追加(2025.11.19yori)
            // V8対応のときに追加する。(2025.12.18yoriyori)
            //Status01 sts = new Status01();
            //CSH.AppMain.UpDateData01(out sts);
            //SubWindow1_ViewModel vm = (SubWindow1_ViewModel)DataContext;
            //if (sts.arm_model == "VAR800M" || sts.arm_model == "VAR800L")
            //{
            //    vm.IsBtn04Enabled = true;
            //    vm.Btn04Opacity = 1.0;
            //}
            //else
            //{
            //    vm.IsBtn04Enabled = false;
            //    vm.Btn04Opacity = 0.25;
            //}
        }

        // 切断
        private void Click_Btn02(object sender, RoutedEventArgs e)
        {
            // C++で実装した処理を実行
            CSH.Grp01.Cmd04();  // 追加(2025.4.28yori)
            // 0軸イニシャライズボタンの状態をでデフォルトに戻す。(2025.11.19yori)
            // V8対応のときに追加する。(2025.12.18yori)
            //SubWindow1_ViewModel vm = (SubWindow1_ViewModel)DataContext;
            //vm.IsBtn04Enabled = true;
            //vm.Btn04Opacity = 1.0;
        }

        // イニシャライズ
        private void Click_Btn03(object sender, RoutedEventArgs e)
        {
            // C++で実装した処理を実行
            CSH.Grp01.Cmd05();  // 追加(2025.6.9yori)

            this.CurrentPanel = Panel.Initialize;
        }

        // 0軸イニシャライズ
        private void Click_Btn04(object sender, RoutedEventArgs e)
        {
            // 機種場合分け追加(2025.11.19yori)
            Status01 sts = new Status01();
            CSH.AppMain.UpDateData01(out sts);
            if (sts.arm_model == "VAR800M" || sts.arm_model == "VAR800L")
            {
                CSH.Grp01.Cmd06();  // 追加(2025.6.9yori)
                this.CurrentPanel = Panel._0AxisInitialize;
            }
        }

        // モード切替
        private void Click_Btn05(object sender, RoutedEventArgs e)
        {
            CSH.Grp01.Cmd16();  // 追加(2025.8.12yori)
            this.CurrentPanel = Panel.SensorConnection;
        }

        public void Cmd03()
        {
            Status01 sts = new Status01(); //追加(2025.6.6yori)

            CSH.AppMain.UpDateData01(out sts);  // テスト(2025.6.6yori)

            // Sub1データ更新
            //ValA.GetBindingExpression(TextBox.TextProperty).UpdateSource();

            // 削除予定(2025.7.28yori)
            //SubWindow1_ViewModel vm = (SubWindow1_ViewModel)DataContext;
            //vm.Visible = true;
            //vm.INIT_FG = sts.init_fg; // 追加(2025.6.6yori)

            // Sub1表示更新
            //ValA.GetBindingExpression(TextBox.TextProperty).UpdateTarget();
        }

        public override Panel CurrentPanel
        {
            get => MainContent.Content == null ? Panel.None : (MainContent.Content as PanelBase).Type;
            set
            {
                if (MainContent.Content == null || (MainContent.Content as PanelBase).Type != value)
                {
                    if (MainContent.Content != null)
                    {
                        (MainContent.Content as PanelBase).Terminate();
                    }
                    switch (value)
                    {
                        case Panel.None:
                            MainContent.Content = null;
                            break;
                        case Panel.Initialize:
                            MainContent.Content = new InitializePanel(this, InitializeValue);
                            break;
                        case Panel.SensorConnection:
                            MainContent.Content = new SensorConnectionPanel(this, SensorConnectionValue);
                            break;
                        case Panel._0AxisInitialize:
                            MainContent.Content = new _0AxisInitializePanel(this, _0AxisInitializeValue);
                            break;
                        default:
                            Debug.Assert(false);
                            return;
                    }
                }
            }
        }

        // ×ボタンを消す処理を追加(2026.2.6yori)
        private void HideCloseButton()
        {
            IntPtr hWnd = new WindowInteropHelper(this).EnsureHandle();

            int style = GetWindowLong(hWnd, GWL_STYLE);
            style &= ~WS_SYSMENU; // システムメニューを外す
            SetWindowLong(hWnd, GWL_STYLE, style);
        }
    }
}
