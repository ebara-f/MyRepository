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

        // ボタン(2025.10.5yori)
        private void Click_SwitchBtn(object sender, RoutedEventArgs e)
        {
            this.ViewModel.ImageVisibility = Visibility.Hidden; // 有接触自己診断
            this.ViewModel.GridVisibility = Visibility.Visible; // ボタン
            this.ViewModel.GridVisibility2 = Visibility.Hidden; // ファームウェアVer.
            this.ViewModel.GridVisibility3 = Visibility.Hidden; // 通信チェック、カウンタVer.
            this.ViewModel.GridVisibility4 = Visibility.Hidden; // カウントチェック1、2
            this.ViewModel.GridVisibility5 = Visibility.Hidden; // ZXスケール
            this.ViewModel.GridVisibility6 = Visibility.Hidden; // 温度センサ
            this.ViewModel.TriggerButtonStatus = "OFF";
            this.ViewModel.CancelButtonStatus = "OFF";
            this.ViewModel.ExecButtonStatus = "OFF";
            this.ViewModel.LockButtonStatus = "OFF";
            this.ViewModel.TriggerButtonResult = "NG";
            this.ViewModel.CancelButtonResult = "NG";
            this.ViewModel.ExecButtonResult = "NG";
            this.ViewModel.LockButtonResult = "NG";
            this.ViewModel.BackgroundColor0 = Brushes.LightPink;
            this.ViewModel.BackgroundColor1 = Brushes.LightPink;
            this.ViewModel.BackgroundColor2 = Brushes.LightPink;
            this.ViewModel.BackgroundColor3 = Brushes.LightPink;
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String241;
            this.ViewModel.Item = JudgeItems.Button;
        }

        // ファームウェアVer.(2025.10.5yori)
        private void Click_FirmwareVerBtn(object sender, RoutedEventArgs e)
        {
            this.ViewModel.ImageVisibility = Visibility.Hidden; // 有接触自己診断
            this.ViewModel.GridVisibility = Visibility.Hidden; // ボタン
            this.ViewModel.GridVisibility2 = Visibility.Visible; // ファームウェアVer.
            this.ViewModel.GridVisibility3 = Visibility.Hidden; // 通信チェック、カウンタVer.
            this.ViewModel.GridVisibility4 = Visibility.Hidden; // カウントチェック1、2
            this.ViewModel.GridVisibility5 = Visibility.Hidden; // ZXスケール
            this.ViewModel.GridVisibility6 = Visibility.Hidden; // 温度センサ
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String242;
            this.ViewModel.Item = JudgeItems.FirmVer;
        }

        // 通信チェック(2025.10.5yori)
        private void Click_CommunicationCheckBtn(object sender, RoutedEventArgs e)
        {
            this.ViewModel.ImageVisibility = Visibility.Hidden; // 有接触自己診断
            this.ViewModel.GridVisibility = Visibility.Hidden; // ボタン
            this.ViewModel.GridVisibility2 = Visibility.Hidden; // ファームウェアVer.
            this.ViewModel.GridVisibility3 = Visibility.Visible; // 通信チェック、カウンタVer.
            this.ViewModel.GridVisibility4 = Visibility.Hidden; // カウントチェック1、2
            this.ViewModel.GridVisibility5 = Visibility.Hidden; // ZXスケール
            this.ViewModel.GridVisibility6 = Visibility.Hidden; // 温度センサ
            this.ViewModel.BackgroundColor0 = Brushes.LightPink;
            this.ViewModel.BackgroundColor1 = Brushes.LightPink;
            this.ViewModel.BackgroundColor2 = Brushes.LightPink;
            this.ViewModel.BackgroundColor3 = Brushes.LightPink;
            this.ViewModel.BackgroundColor4 = Brushes.LightPink;
            this.ViewModel.BackgroundColor5 = Brushes.LightPink;
            this.ViewModel.BackgroundColor6 = Brushes.LightPink;
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String244;
            this.ViewModel.CounterItem = VecApp.Properties.Resources.String236;
            this.ViewModel.Item = JudgeItems.Cummunication;
        }

        // カウンタVer.(2025.10.5yori)
        private void Click_CounterVerBtn(object sender, RoutedEventArgs e)
        {
            this.ViewModel.ImageVisibility = Visibility.Hidden; // 有接触自己診断
            this.ViewModel.GridVisibility = Visibility.Hidden; // ボタン
            this.ViewModel.GridVisibility2 = Visibility.Hidden; // ファームウェアVer.
            this.ViewModel.GridVisibility3 = Visibility.Visible; // 通信チェック、カウンタVer.
            this.ViewModel.GridVisibility4 = Visibility.Hidden; // カウントチェック1、2
            this.ViewModel.GridVisibility5 = Visibility.Hidden; // ZXスケール
            this.ViewModel.GridVisibility6 = Visibility.Hidden; // 温度センサ
            this.ViewModel.BackgroundColor0 = Brushes.White;
            this.ViewModel.BackgroundColor1 = Brushes.White;
            this.ViewModel.BackgroundColor2 = Brushes.White;
            this.ViewModel.BackgroundColor3 = Brushes.White;
            this.ViewModel.BackgroundColor4 = Brushes.White;
            this.ViewModel.BackgroundColor5 = Brushes.White;
            this.ViewModel.BackgroundColor6 = Brushes.White;
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String242;
            this.ViewModel.CounterItem = "Ver.";
            this.ViewModel.Item = JudgeItems.CounterVer;
        }

        // カウントチェック1(2025.10.5yori)
        private void Click_CountCheck1Btn(object sender, RoutedEventArgs e)
        {
            this.ViewModel.ImageVisibility = Visibility.Hidden; // 有接触自己診断
            this.ViewModel.GridVisibility = Visibility.Hidden; // ボタン
            this.ViewModel.GridVisibility2 = Visibility.Hidden; // ファームウェアVer.
            this.ViewModel.GridVisibility3 = Visibility.Hidden; // 通信チェック、カウンタVer.
            this.ViewModel.GridVisibility4 = Visibility.Visible; // カウントチェック1、2
            this.ViewModel.GridVisibility5 = Visibility.Hidden; // ZXスケール
            this.ViewModel.GridVisibility6 = Visibility.Hidden; // 温度センサ
            this.ViewModel.BackgroundColor0 = Brushes.LightPink;
            this.ViewModel.BackgroundColor1 = Brushes.LightPink;
            this.ViewModel.BackgroundColor2 = Brushes.LightPink;
            this.ViewModel.BackgroundColor3 = Brushes.LightPink;
            this.ViewModel.BackgroundColor4 = Brushes.LightPink;
            this.ViewModel.BackgroundColor5 = Brushes.LightPink;
            this.ViewModel.BackgroundColor6 = Brushes.LightPink;
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String245;
            this.ViewModel.Item = JudgeItems.Count1;
        }

        // カウントチェック2(2025.10.5yori)
        private void Click_CountCheck2Btn(object sender, RoutedEventArgs e)
        {
            this.ViewModel.ImageVisibility = Visibility.Hidden; // 有接触自己診断
            this.ViewModel.GridVisibility = Visibility.Hidden; // ボタン
            this.ViewModel.GridVisibility2 = Visibility.Hidden; // ファームウェアVer.
            this.ViewModel.GridVisibility3 = Visibility.Hidden; // 通信チェック、カウンタVer.
            this.ViewModel.GridVisibility4 = Visibility.Visible; // カウントチェック1、2
            this.ViewModel.GridVisibility5 = Visibility.Hidden; // ZXスケール
            this.ViewModel.GridVisibility6 = Visibility.Hidden; // 温度センサ
            this.ViewModel.BackgroundColor0 = Brushes.LightPink;
            this.ViewModel.BackgroundColor1 = Brushes.LightPink;
            this.ViewModel.BackgroundColor2 = Brushes.LightPink;
            this.ViewModel.BackgroundColor3 = Brushes.LightPink;
            this.ViewModel.BackgroundColor4 = Brushes.LightPink;
            this.ViewModel.BackgroundColor5 = Brushes.LightPink;
            this.ViewModel.BackgroundColor6 = Brushes.LightPink;
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String246;
            this.ViewModel.Item = JudgeItems.Count2;
        }

        // ZXスケール(2025.10.5yori)
        private void Click_ZXScaleAxisBtn(object sender, RoutedEventArgs e)
        {
            this.ViewModel.ImageVisibility = Visibility.Hidden; // 有接触自己診断
            this.ViewModel.GridVisibility = Visibility.Hidden; // ボタン
            this.ViewModel.GridVisibility2 = Visibility.Hidden; // ファームウェアVer.
            this.ViewModel.GridVisibility3 = Visibility.Hidden; // 通信チェック、カウンタVer.
            this.ViewModel.GridVisibility4 = Visibility.Hidden; // カウントチェック1、2
            this.ViewModel.GridVisibility5 = Visibility.Visible; // ZXスケール
            this.ViewModel.GridVisibility6 = Visibility.Hidden; // 温度センサ
            this.ViewModel.BackgroundColor0 = Brushes.LightPink;
            this.ViewModel.BackgroundColor1 = Brushes.LightPink;
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String247;
            this.ViewModel.Item = JudgeItems.ZXScale;
        }

        // 温度センサ(2025.10.5yori)
        private void Click_TemperatureSensorBtn(object sender, RoutedEventArgs e)
        {
            this.ViewModel.ImageVisibility = Visibility.Hidden; // 有接触自己診断
            this.ViewModel.GridVisibility = Visibility.Hidden; // ボタン
            this.ViewModel.GridVisibility2 = Visibility.Hidden; // ファームウェアVer.
            this.ViewModel.GridVisibility3 = Visibility.Hidden; // 通信チェック、カウンタVer.
            this.ViewModel.GridVisibility4 = Visibility.Hidden; // カウントチェック1、2
            this.ViewModel.GridVisibility5 = Visibility.Hidden; // ZXスケール
            this.ViewModel.GridVisibility6 = Visibility.Visible; // 温度センサ
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String248;
            this.ViewModel.Item = JudgeItems.Temp;
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
                switch (this.ViewModel.Item) // 追加(2025.10.4yori)
                { 
                    case JudgeItems.Button: // 追加(2025.10.6yori)
                        if ((sts.btn & 0x02) != 0x02)
                        {
                            this.ViewModel.TriggerButtonStatus = "OFF";
                        }
                        if ((sts.btn & 0x02) == 0x02)
                        {
                            this.ViewModel.TriggerButtonStatus = "ON";
                            this.ViewModel.TriggerButtonResult = "OK";
                            this.ViewModel.BackgroundColor0 = Brushes.LightGreen;
                        }
                        if ((sts.btn & 0x04) != 0x04)
                        {
                            this.ViewModel.CancelButtonStatus = "OFF";
                        }
                        if ((sts.btn & 0x04) == 0x04)
                        {
                            this.ViewModel.CancelButtonStatus = "ON";
                            this.ViewModel.CancelButtonResult = "OK";
                            this.ViewModel.BackgroundColor1 = Brushes.LightGreen;
                        }
                        if ((sts.btn & 0x08) != 0x08)
                        {
                            this.ViewModel.LockButtonStatus = "OFF";
                        }
                        if ((sts.btn & 0x08) == 0x08)
                        {
                            this.ViewModel.LockButtonStatus = "ON";
                            this.ViewModel.LockButtonResult = "OK";
                            this.ViewModel.BackgroundColor3 = Brushes.LightGreen;
                        }
                        if ((sts.btn & 0x10) != 0x10)
                        {
                            this.ViewModel.ExecButtonStatus = "OFF";
                        }
                        if ((sts.btn & 0x10) == 0x10)
                        {
                            this.ViewModel.ExecButtonStatus = "ON";
                            this.ViewModel.ExecButtonResult = "OK";
                            this.ViewModel.BackgroundColor2 = Brushes.LightGreen;
                        }
                        break;

                    case JudgeItems.FirmVer: // ファームウェアVer.(2025.10.4yori)
                        this.ViewModel.FirmVer = sts.firm_ver;
                        break;

                    case JudgeItems.Cummunication: // 通信チェック(2025.10.6yori)
                        if (sts.comm_check[0] == 0)
                        {
                            this.ViewModel.CounterNo0Result = "OK";
                            this.ViewModel.BackgroundColor0 = Brushes.LightGreen;
                        }
                        if (sts.comm_check[0] != 0)
                        {
                            this.ViewModel.CounterNo0Result = "NG";
                            this.ViewModel.BackgroundColor0 = Brushes.LightPink;
                        }
                        if (sts.comm_check[1] == 0)
                        {
                            this.ViewModel.CounterNo1Result = "OK";
                            this.ViewModel.BackgroundColor1 = Brushes.LightGreen;
                        }
                        if (sts.comm_check[1] != 0)
                        {
                            this.ViewModel.CounterNo1Result = "NG";
                            this.ViewModel.BackgroundColor1 = Brushes.LightPink;
                        }
                        if (sts.comm_check[2] == 0)
                        {
                            this.ViewModel.CounterNo2Result = "OK";
                            this.ViewModel.BackgroundColor2 = Brushes.LightGreen;
                        }
                        if (sts.comm_check[2] != 0)
                        {
                            this.ViewModel.CounterNo2Result = "NG";
                            this.ViewModel.BackgroundColor2 = Brushes.LightPink;
                        }
                        if (sts.comm_check[3] == 0)
                        {
                            this.ViewModel.CounterNo3Result = "OK";
                            this.ViewModel.BackgroundColor3 = Brushes.LightGreen;
                        }
                        if (sts.comm_check[3] != 0)
                        {
                            this.ViewModel.CounterNo3Result = "NG";
                            this.ViewModel.BackgroundColor3 = Brushes.LightPink;
                        }
                        if (sts.comm_check[4] == 0)
                        {
                            this.ViewModel.CounterNo4Result = "OK";
                            this.ViewModel.BackgroundColor4 = Brushes.LightGreen;
                        }
                        if (sts.comm_check[4] != 0)
                        {
                            this.ViewModel.CounterNo4Result = "NG";
                            this.ViewModel.BackgroundColor4 = Brushes.LightPink;
                        }
                        if (sts.comm_check[5] == 0)
                        {
                            this.ViewModel.CounterNo5Result = "OK";
                            this.ViewModel.BackgroundColor5 = Brushes.LightGreen;
                        }
                        if (sts.comm_check[5] != 0)
                        {
                            this.ViewModel.CounterNo5Result = "NG";
                            this.ViewModel.BackgroundColor5 = Brushes.LightPink;
                        }
                        if (sts.comm_check[6] == 0)
                        {
                            this.ViewModel.CounterNo6Result = "OK";
                            this.ViewModel.BackgroundColor6 = Brushes.LightGreen;
                        }
                        if (sts.comm_check[6] != 0)
                        {
                            this.ViewModel.CounterNo6Result = "NG";
                            this.ViewModel.BackgroundColor6 = Brushes.LightPink;
                        }
                        break;

                    case JudgeItems.CounterVer: // カウンタVer.(2025.10.4yori)
                        this.ViewModel.CounterNo0Result = sts.cnt_ver.Substring(0, 1);
                        this.ViewModel.CounterNo1Result = sts.cnt_ver.Substring(2, 1);
                        this.ViewModel.CounterNo2Result = sts.cnt_ver.Substring(4, 1);
                        this.ViewModel.CounterNo3Result = sts.cnt_ver.Substring(6, 1);
                        this.ViewModel.CounterNo4Result = sts.cnt_ver.Substring(8, 1);
                        this.ViewModel.CounterNo5Result = sts.cnt_ver.Substring(10, 1);
                        this.ViewModel.CounterNo6Result = sts.cnt_ver.Substring(12, 1);
                        break;

                    case JudgeItems.Count1: // カウントチェック1(2025.10.6yori)
                        this.ViewModel.CounterNo0Count = sts.cnt_data[0].ToString();
                        this.ViewModel.CounterNo1Count = sts.cnt_data[1].ToString();
                        this.ViewModel.CounterNo2Count = sts.cnt_data[2].ToString();
                        this.ViewModel.CounterNo3Count = sts.cnt_data[3].ToString();
                        this.ViewModel.CounterNo4Count = sts.cnt_data[4].ToString();
                        this.ViewModel.CounterNo5Count = sts.cnt_data[5].ToString();
                        this.ViewModel.CounterNo6Count = sts.cnt_data[6].ToString();
                        break;

                    default:
                        break;
                }
            });
        }
    }
}
