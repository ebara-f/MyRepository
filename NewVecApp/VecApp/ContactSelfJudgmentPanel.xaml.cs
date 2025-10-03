using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using CSH;

namespace VecApp
{
    /// <summary>
    /// ContactSelfJudgmentPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class ContactSelfJudgmentPanel : PanelBase
    {
        public ContactSelfJudgmentPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.ContactSelfJudgment)
        {
            InitializeComponent();
            this.DataContext = model;
            //// 追加(2025.10.3yori)
            this.ViewModel.TriggerButtonStatus = "OFF";
            this.ViewModel.CancelButtonStatus = "OFF";
            this.ViewModel.ExecButtonStatus = "OFF";
            this.ViewModel.LockButtonStatus = "OFF";
            this.ViewModel.TriggerButtonResult = "NG";
            this.ViewModel.CancelButtonResult = "NG";
            this.ViewModel.ExecButtonResult = "NG";
            this.ViewModel.LockButtonResult = "NG";
            this.ViewModel.BackgroundColor1 = Brushes.LightPink;
            this.ViewModel.BackgroundColor2 = Brushes.LightPink;
            this.ViewModel.BackgroundColor3 = Brushes.LightPink;
            this.ViewModel.BackgroundColor4 = Brushes.LightPink;
            this.ViewModel.BackgroundColor4 = Brushes.LightPink;
            this.ViewModel.BackgroundColor4 = Brushes.LightPink;
            this.ViewModel.SubtitleText = "";
            ////
        }


        private void Click_ParamSaveBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_ParamRestoreBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_SaveBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CloseBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.None; // 追加(2025.9.25yori)
        }
        private void Click_SwitchBtn(object sender, RoutedEventArgs e)
        {
            // 表示画面切替(2025.10.3yori)
            this.ViewModel.ImageVisibility = Visibility.Hidden;
            this.ViewModel.GridVisibility = Visibility.Visible;
            this.ViewModel.GridVisibility2 = Visibility.Hidden;
            this.ViewModel.SubtitleText = "各ボタンを押してください。";
        }
        private void Click_FirmwareVerBtn(object sender, RoutedEventArgs e)
        {
            // 表示画面切替(2025.10.3yori)
            this.ViewModel.ImageVisibility = Visibility.Hidden;
            this.ViewModel.GridVisibility = Visibility.Hidden;
            this.ViewModel.GridVisibility2 = Visibility.Visible;
        }
        private void Click_CommunicationCheckBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CounterVerBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CountCheck1Btn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CountCheck2Btn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_ZXScaleAxisBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_TemperatureSensorBtn(object sender, RoutedEventArgs e)
        {

        }

        private ContactSelfJudgmentViewModel ViewModel
        {
            get => this.DataContext as ContactSelfJudgmentViewModel;
        }

        // 画面更新(2025.10.3yori)
        public void PanelUpdate()
        {
            Status04 sts = new Status04();
            CSH.AppMain.UpDateData06(out sts);
            Application.Current.Dispatcher.Invoke(() =>
            {
                if ((sts.btn & 0x02) != 0x02)
                {
                    ViewModel.TriggerButtonStatus = "OFF";
                }
                if ((sts.btn & 0x02) == 0x02)
                {
                    ViewModel.TriggerButtonStatus = "ON";
                    ViewModel.TriggerButtonResult = "OK";
                    ViewModel.BackgroundColor1 = Brushes.LightGreen;
                }
                if ((sts.btn & 0x04) != 0x04)
                {
                    ViewModel.CancelButtonStatus = "OFF";
                }
                if ((sts.btn & 0x04) == 0x04)
                {
                    ViewModel.CancelButtonStatus = "ON";
                    ViewModel.CancelButtonResult = "OK";
                    ViewModel.BackgroundColor2 = Brushes.LightGreen;
                }
                if ((sts.btn & 0x08) != 0x08)
                {
                    ViewModel.LockButtonStatus = "OFF";
                }
                if ((sts.btn & 0x08) == 0x08)
                {
                    ViewModel.LockButtonStatus = "ON";
                    ViewModel.LockButtonResult = "OK";
                    ViewModel.BackgroundColor4 = Brushes.LightGreen;
                }
                if ((sts.btn & 0x10) != 0x10)
                {
                    ViewModel.ExecButtonStatus = "OFF";
                }
                if ((sts.btn & 0x10) == 0x10)
                {
                    ViewModel.ExecButtonStatus = "ON";
                    ViewModel.ExecButtonResult = "OK";
                    ViewModel.BackgroundColor3 = Brushes.LightGreen;
                }
            });
        }
    }
}
