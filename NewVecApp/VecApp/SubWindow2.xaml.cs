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
using System.Runtime.InteropServices;
using CSH;

namespace VecApp
{
    /// <summary>
    /// SubWindow2.xaml の相互作用ロジック
    /// </summary>
    public partial class SubWindow2 : SubWindowBase
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
            //SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SYSMENU);   // 2025.4.22 eba del
        }

        #endregion

        // 2025.09.04  Modify by GeomLab
        // MainWindow から終了させるときだけ true にする
        public bool m_AllowClose { get; set; } = false;

        /// <summary>
        /// メンバー変数
        /// </summary>
        //public IntPtr m_hWnd;		// ウィンドウハンドル // 削除予定(2025.7.28yori)

        public ProbeSettingViewModel ProbeSettingValue = new ProbeSettingViewModel();

        public SettingViewModel SettingValue = new SettingViewModel();

        public InspectionViewModel InspectionValue = new InspectionViewModel();

        public ThresholdSettingViewModel ThresholdValue = new ThresholdSettingViewModel();

        public GaugeSettingViewModel GaugeValue = new GaugeSettingViewModel();

        public ContactPropertyViewModel ContactPropertyValue = new ContactPropertyViewModel();

        public ContactInspectionViewModel ContactInspectionValue = new ContactInspectionViewModel();

        public ProbeInputViewModel ProbeInputValue = new ProbeInputViewModel();

        public ContactSelfJudgmentViewModel ContactSelfJudgmentValue = new ContactSelfJudgmentViewModel();

        public ArmTypeSettingViewModel ArmTypeSettingValue = new ArmTypeSettingViewModel();

        public ArmNetworkSettingViewModel ArmNetworkSettingValue = new ArmNetworkSettingViewModel();

        public SubWindow2()
        {
            InitializeComponent();
        }

        public void Cmd01() // 追加(2025.6.11yori)
        {

        }

        private void Click_Btn01(object sender, RoutedEventArgs e)
        {
            // C++で実装した処理を実行
            CSH.Grp02.Cmd01();  // 追加(2025.6.11yori)

            this.CurrentPanel = Panel.ProbeSetting;
        }

        private void Click_Btn02(object sender, RoutedEventArgs e)
        {
            // C++で実装した処理を実行
            CSH.Grp02.Cmd02();  // 追加(2025.6.11yori)

            this.CurrentPanel = Panel.Inspection;
        }

        private void Click_Btn03(object sender, RoutedEventArgs e)
        {
            // C++で実装した処理を実行
            CSH.Grp02.Cmd03();  // 追加(2025.6.11yori)

            this.CurrentPanel = Panel.ContactProperty;
        }

        private void Click_Btn04(object sender, RoutedEventArgs e)
        {
            // C++で実装した処理を実行
            CSH.Grp02.Cmd04();  // 追加(2025.6.11yori)

            this.CurrentPanel = Panel.ContactSelfJudgment;
        }

        private void Click_Btn05(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.Cmd05();  // 追加(2025.10.31yori)
            this.CurrentPanel = Panel.ArmTypeSetting;
        }

        private void Click_Btn06(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.Cmd06();  // 追加(2025.8.15yori)
            this.CurrentPanel = Panel.ArmNetworkSetting;
        }

        // プローブ登録(2025.10.24yori)
        private void Click_Btn07(object sender, RoutedEventArgs e)
        {
            this.CurrentPanel = Panel.ProbeInput;
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
                        case Panel.ProbeSetting:
                            MainContent.Content = new ProbeSettingPanel(this, ProbeSettingValue);
                            break;
                        case Panel.Inspection:
                            MainContent.Content = new InspectionPanel(this, InspectionValue);
                            break;
                        case Panel.ThresholdSetting:
                            MainContent.Content = new ThresholdSettingPanel(this, ThresholdValue);
                            break;
                        case Panel.GaugeSetting:
                            MainContent.Content = new GaugeSettingPanel(this, GaugeValue);
                            break;
                        case Panel.ContactProperty:
                            MainContent.Content = new ContactPropertyPanel(this, ContactPropertyValue);
                            break;
                        case Panel.ContactInspection:
                            MainContent.Content = new ContactInspectionPanel(this, ContactInspectionValue);
                            break;
                        case Panel.ProbeInput:
                            MainContent.Content = new ProbeInputPanel(this, ProbeInputValue);
                            break;
                        case Panel.Setting:
                            MainContent.Content = new SettingPanel(this, SettingValue);
                            break;
                        case Panel.ContactSelfJudgment:
                            MainContent.Content = new ContactSelfJudgmentPanel(this, ContactSelfJudgmentValue);
                            break;
                        case Panel.ArmTypeSetting:
                            MainContent.Content = new ArmTypeSettingPanel(this, ArmTypeSettingValue);
                            break;
                        case Panel.ArmNetworkSetting:
                            MainContent.Content = new ArmNetworkSettingPanel(this, ArmNetworkSettingValue);
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
            // 2025.09.04  Modify by GeomLab
            if ( m_AllowClose == false ) {
                CSH.Grp02.Cmd11();  // 追加(2025.9.1yori)
                e.Cancel = true;
                this.CurrentPanel = Panel.None;
                this.Hide();
            }
        }
    }
}
