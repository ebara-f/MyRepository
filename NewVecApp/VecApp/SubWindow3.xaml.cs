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
using CSH;

namespace VecApp
{
    /// <summary>
    /// SubWindow3.xaml の相互作用ロジック
    /// </summary>
    public partial class SubWindow3 : SubWindowBase
    {
        // 2025.09.04  Modify by GeomLab
        // MainWindow から終了させるときだけ true にする
        public bool m_AllowClose { get; set; } = false;

        /// <summary>
        /// メンバー変数
        /// </summary>
        //public IntPtr m_hWnd;		// ウィンドウハンドル // 削除予定(2025.7.28yori)

        public ApiScanViewModel ApiScanValue = new ApiScanViewModel();

        public NonContactSelfJudgmentViewModel NonContactSelfJudgmentValue = new NonContactSelfJudgmentViewModel();

        public SensorNetworkSettingViewModel SensorNetworkSettingValue = new SensorNetworkSettingViewModel();

        public SubWindow3()
        {
            InitializeComponent();

            // ウィンドウズハンドルの取得
            //m_hWnd = new WindowInteropHelper(this).EnsureHandle(); // 削除予定(2025.7.28yori)
        }

        private void Click_Btn01(object sender, RoutedEventArgs e)
        {
            this.CurrentPanel = Panel.ApiScan;
        }

        private void Click_Btn02(object sender, RoutedEventArgs e)
        {
            // C++で実装した処理を実行
            CSH.Grp03.Cmd04();  // 追加(2025.7.3yori)

            this.CurrentPanel = Panel.NonContactSelfJudgment;
        }

        private void Click_Btn03(object sender, RoutedEventArgs e)
        {
            this.CurrentPanel = Panel.SensorNetworkSetting;
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
                        case Panel.ApiScan:
                            MainContent.Content = new ApiScanPanel(this, ApiScanValue);
                            break;
                        case Panel.NonContactSelfJudgment:
                            MainContent.Content = new NonContactSelfJudgmentPanel(this, NonContactSelfJudgmentValue);
                            break;
                        case Panel.SensorNetworkSetting:
                            MainContent.Content = new SensorNetworkSettingPanel(this, SensorNetworkSettingValue);
                            break;
                        default:
                            Debug.Assert(false);
                            return;
                    }
                }
            }
        }

        // 閉じるボタンをクリックしたときの処理(2025.8.12yori)
        private void Terminate(object sender, System.ComponentModel.CancelEventArgs e)
        {
            CSH.Grp03.Cmd05(); // 追加(2025.9.3yori)

            // 2025.09.04  Modify by GeomLab
            if (m_AllowClose == false)
            {
                e.Cancel = true;
                this.CurrentPanel = Panel.None;
                this.Hide();
            }
        }
    }
}
