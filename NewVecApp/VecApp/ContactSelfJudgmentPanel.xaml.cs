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
using Microsoft.Win32;
using System.IO; // 追加(2025.10.7yori)

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
            //// 追加(2025.10.6yori)
            this.ViewModel.ImageVisibility = Visibility.Visible; // 有接触自己診断
            this.ViewModel.GridVisibility = Visibility.Hidden; // ボタン
            this.ViewModel.GridVisibility2 = Visibility.Hidden; // ファームウェアVer.
            this.ViewModel.GridVisibility3 = Visibility.Hidden; // 通信チェック、カウンタVer.
            this.ViewModel.GridVisibility4 = Visibility.Hidden; // カウントチェック1、2
            this.ViewModel.GridVisibility5 = Visibility.Hidden; // ZXスケール
            this.ViewModel.GridVisibility6 = Visibility.Hidden; // 温度センサ
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String253;
            ////
        }

        private void Click_ParamSaveBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.Cmd13(); // 有接触モードへ変更(2025.10.6yori)

            var dialog = new SaveFileDialog
            {
                Title = VecApp.Properties.Resources.String258,
                Filter = "VECTORON files (*.V8)|*.V8|"
            };

            if (dialog.ShowDialog() == true)
            {
            }

            CSH.Grp02.ContactSelfJudgmentPanelSavePara(); // パラメータ保存(2025.10.6yori)
        }
        private void Click_ParamRestoreBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.Cmd13(); // 有接触モードへ変更(2025.10.6yori)
        }
        private void Click_SaveBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.Cmd13(); // 有接触モードへ変更(2025.10.6yori)
        }
        private void Click_CloseBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.Cmd13(); // 有接触モードへ変更(2025.10.6yori)
            Parent.CurrentPanel = Panel.None; // 追加(2025.9.25yori)
        }

        // ボタン(2025.10.6yori)
        private void Click_SwitchBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.Cmd13(); // 有接触モードへ変更
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
            CSH.Grp02.Cmd13(); // 有接触モードへ変更
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
            CSH.Grp02.Cmd13(); // 有接触モードへ変更
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
            CSH.Grp02.Cmd13(); // 有接触モードへ変更
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
            CSH.Grp02.Cmd13(); // 有接触モードへ変更
            this.ViewModel.ImageVisibility = Visibility.Hidden; // 有接触自己診断
            this.ViewModel.GridVisibility = Visibility.Hidden; // ボタン
            this.ViewModel.GridVisibility2 = Visibility.Hidden; // ファームウェアVer.
            this.ViewModel.GridVisibility3 = Visibility.Hidden; // 通信チェック、カウンタVer.
            this.ViewModel.GridVisibility4 = Visibility.Visible; // カウントチェック1、2
            this.ViewModel.GridVisibility5 = Visibility.Hidden; // ZXスケール
            this.ViewModel.GridVisibility6 = Visibility.Hidden; // 温度センサ
            this.ViewModel.BackgroundColor1 = Brushes.LightPink;
            this.ViewModel.BackgroundColor2 = Brushes.LightPink;
            this.ViewModel.BackgroundColor3 = Brushes.LightPink;
            this.ViewModel.BackgroundColor4 = Brushes.LightPink;
            this.ViewModel.BackgroundColor5 = Brushes.LightPink;
            this.ViewModel.BackgroundColor6 = Brushes.LightPink;
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String245;
            this.ViewModel.Item = JudgeItems.Count1;
            // 0軸有無を取得(2025.10.6yori)
            Status01 sts1 = new Status01();
            CSH.AppMain.UpDateData01(out sts1);
            // カウント値の最初の値を取得(2025.10.6yori)
            Status04 sts4 = new Status04();
            CSH.AppMain.UpDateData06(out sts4);
            this.ViewModel.Count[0] = sts4.cnt_data[0];
            this.ViewModel.Count[1] = sts4.cnt_data[1];
            this.ViewModel.Count[2] = sts4.cnt_data[2];
            this.ViewModel.Count[3] = sts4.cnt_data[3];
            this.ViewModel.Count[4] = sts4.cnt_data[4];
            this.ViewModel.Count[5] = sts4.cnt_data[5];
            this.ViewModel.Count[6] = sts4.cnt_data[6];
            if (sts1.no0_fg == 0)
            {
                this.ViewModel.CounterNo0Count = "―";
                this.ViewModel.CounterNo0Result = "―";
                this.ViewModel.BackgroundColor0 = Brushes.White;
            }
            else if(sts1.no0_fg != 0)
            {
                this.ViewModel.BackgroundColor0 = Brushes.LightPink;
                this.ViewModel.CounterNo0Result = "NG";
            }
            this.ViewModel.CounterNo1Result = "NG";
            this.ViewModel.CounterNo2Result = "NG";
            this.ViewModel.CounterNo3Result = "NG";
            this.ViewModel.CounterNo4Result = "NG";
            this.ViewModel.CounterNo5Result = "NG";
            this.ViewModel.CounterNo6Result = "NG";
        }

        // カウントチェック2(2025.10.6yori)
        private void Click_CountCheck2Btn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.Cmd12(); // メンテナンスモードへ変更
            this.ViewModel.ImageVisibility = Visibility.Hidden; // 有接触自己診断
            this.ViewModel.GridVisibility = Visibility.Hidden; // ボタン
            this.ViewModel.GridVisibility2 = Visibility.Hidden; // ファームウェアVer.
            this.ViewModel.GridVisibility3 = Visibility.Hidden; // 通信チェック、カウンタVer.
            this.ViewModel.GridVisibility4 = Visibility.Visible; // カウントチェック1、2
            this.ViewModel.GridVisibility5 = Visibility.Hidden; // ZXスケール
            this.ViewModel.GridVisibility6 = Visibility.Hidden; // 温度センサ
            this.ViewModel.BackgroundColor1 = Brushes.LightPink;
            this.ViewModel.BackgroundColor2 = Brushes.LightPink;
            this.ViewModel.BackgroundColor3 = Brushes.LightPink;
            this.ViewModel.BackgroundColor4 = Brushes.LightPink;
            this.ViewModel.BackgroundColor5 = Brushes.LightPink;
            this.ViewModel.BackgroundColor6 = Brushes.LightPink;
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String246;
            this.ViewModel.Item = JudgeItems.Count2;
            // 0軸有無を取得
            Status01 sts1 = new Status01();
            CSH.AppMain.UpDateData01(out sts1);
            if (sts1.no0_fg == 0)
            {
                this.ViewModel.CounterNo0Count = "―";
                this.ViewModel.CounterNo0Result = "―";
                this.ViewModel.BackgroundColor0 = Brushes.White;
            }
            else if (sts1.no0_fg != 0)
            {
                this.ViewModel.BackgroundColor0 = Brushes.LightPink;
                this.ViewModel.CounterNo0Result = "NG";
            }
            this.ViewModel.CounterNo1Result = "NG";
            this.ViewModel.CounterNo2Result = "NG";
            this.ViewModel.CounterNo3Result = "NG";
            this.ViewModel.CounterNo4Result = "NG";
            this.ViewModel.CounterNo5Result = "NG";
            this.ViewModel.CounterNo6Result = "NG";
        }

        // ZXスケール(2025.10.6yori)
        private void Click_ZXScaleAxisBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.Cmd13(); // 有接触モードへ変更
            this.ViewModel.ImageVisibility = Visibility.Hidden; // 有接触自己診断
            this.ViewModel.GridVisibility = Visibility.Hidden; // ボタン
            this.ViewModel.GridVisibility2 = Visibility.Hidden; // ファームウェアVer.
            this.ViewModel.GridVisibility3 = Visibility.Hidden; // 通信チェック、カウンタVer.
            this.ViewModel.GridVisibility4 = Visibility.Hidden; // カウントチェック1、2
            this.ViewModel.GridVisibility5 = Visibility.Visible; // ZXスケール
            this.ViewModel.GridVisibility6 = Visibility.Hidden; // 温度センサ
            this.ViewModel.CounterNo8Judge = "NG";
            this.ViewModel.CounterNo9Judge = "NG";
            this.ViewModel.BackgroundColor0 = Brushes.LightPink;
            this.ViewModel.BackgroundColor1 = Brushes.LightPink;
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String247;
            this.ViewModel.Item = JudgeItems.ZXScale;
            // カウント値の最初の値を取得(2025.10.6yori)
            Status04 sts4 = new Status04();
            CSH.AppMain.UpDateData06(out sts4);
            this.ViewModel.Count[7] = sts4.cnt_data[7];
            this.ViewModel.Count[8] = sts4.cnt_data[8];
        }

        // 温度センサ(2025.10.5yori)
        private void Click_TemperatureSensorBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.Cmd13(); // 有接触モードへ変更
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
            Status01 sts1 = new Status01();
            Status04 sts4 = new Status04();
            Application.Current.Dispatcher.Invoke(() =>
            {
                switch (this.ViewModel.Item) // 追加(2025.10.4yori)
                { 
                    case JudgeItems.Button: // 追加(2025.10.6yori)                        
                        CSH.AppMain.UpDateData06(out sts4);
                        if ((sts4.btn & 0x02) != 0x02)
                        {
                            this.ViewModel.TriggerButtonStatus = "OFF";
                        }
                        if ((sts4.btn & 0x02) == 0x02)
                        {
                            this.ViewModel.TriggerButtonStatus = "ON";
                            this.ViewModel.TriggerButtonResult = "OK";
                            this.ViewModel.BackgroundColor0 = Brushes.LightGreen;
                        }
                        if ((sts4.btn & 0x04) != 0x04)
                        {
                            this.ViewModel.CancelButtonStatus = "OFF";
                        }
                        if ((sts4.btn & 0x04) == 0x04)
                        {
                            this.ViewModel.CancelButtonStatus = "ON";
                            this.ViewModel.CancelButtonResult = "OK";
                            this.ViewModel.BackgroundColor1 = Brushes.LightGreen;
                        }
                        if ((sts4.btn & 0x08) != 0x08)
                        {
                            this.ViewModel.LockButtonStatus = "OFF";
                        }
                        if ((sts4.btn & 0x08) == 0x08)
                        {
                            this.ViewModel.LockButtonStatus = "ON";
                            this.ViewModel.LockButtonResult = "OK";
                            this.ViewModel.BackgroundColor3 = Brushes.LightGreen;
                        }
                        if ((sts4.btn & 0x10) != 0x10)
                        {
                            this.ViewModel.ExecButtonStatus = "OFF";
                        }
                        if ((sts4.btn & 0x10) == 0x10)
                        {
                            this.ViewModel.ExecButtonStatus = "ON";
                            this.ViewModel.ExecButtonResult = "OK";
                            this.ViewModel.BackgroundColor2 = Brushes.LightGreen;
                        }
                        break;

                    case JudgeItems.FirmVer: // ファームウェアVer.(2025.10.4yori)
                        CSH.AppMain.UpDateData06(out sts4);
                        this.ViewModel.FirmVer = sts4.firm_ver;
                        break;

                    case JudgeItems.Cummunication: // 通信チェック(2025.10.6yori)
                        CSH.AppMain.UpDateData06(out sts4);
                        if (sts4.comm_check[0] == 0)
                        {
                            this.ViewModel.CounterNo0Result = "OK";
                            this.ViewModel.BackgroundColor0 = Brushes.LightGreen;
                        }
                        if (sts4.comm_check[0] != 0)
                        {
                            this.ViewModel.CounterNo0Result = "NG";
                            this.ViewModel.BackgroundColor0 = Brushes.LightPink;
                        }
                        if (sts4.comm_check[1] == 0)
                        {
                            this.ViewModel.CounterNo1Result = "OK";
                            this.ViewModel.BackgroundColor1 = Brushes.LightGreen;
                        }
                        if (sts4.comm_check[1] != 0)
                        {
                            this.ViewModel.CounterNo1Result = "NG";
                            this.ViewModel.BackgroundColor1 = Brushes.LightPink;
                        }
                        if (sts4.comm_check[2] == 0)
                        {
                            this.ViewModel.CounterNo2Result = "OK";
                            this.ViewModel.BackgroundColor2 = Brushes.LightGreen;
                        }
                        if (sts4.comm_check[2] != 0)
                        {
                            this.ViewModel.CounterNo2Result = "NG";
                            this.ViewModel.BackgroundColor2 = Brushes.LightPink;
                        }
                        if (sts4.comm_check[3] == 0)
                        {
                            this.ViewModel.CounterNo3Result = "OK";
                            this.ViewModel.BackgroundColor3 = Brushes.LightGreen;
                        }
                        if (sts4.comm_check[3] != 0)
                        {
                            this.ViewModel.CounterNo3Result = "NG";
                            this.ViewModel.BackgroundColor3 = Brushes.LightPink;
                        }
                        if (sts4.comm_check[4] == 0)
                        {
                            this.ViewModel.CounterNo4Result = "OK";
                            this.ViewModel.BackgroundColor4 = Brushes.LightGreen;
                        }
                        if (sts4.comm_check[4] != 0)
                        {
                            this.ViewModel.CounterNo4Result = "NG";
                            this.ViewModel.BackgroundColor4 = Brushes.LightPink;
                        }
                        if (sts4.comm_check[5] == 0)
                        {
                            this.ViewModel.CounterNo5Result = "OK";
                            this.ViewModel.BackgroundColor5 = Brushes.LightGreen;
                        }
                        if (sts4.comm_check[5] != 0)
                        {
                            this.ViewModel.CounterNo5Result = "NG";
                            this.ViewModel.BackgroundColor5 = Brushes.LightPink;
                        }
                        if (sts4.comm_check[6] == 0)
                        {
                            this.ViewModel.CounterNo6Result = "OK";
                            this.ViewModel.BackgroundColor6 = Brushes.LightGreen;
                        }
                        if (sts4.comm_check[6] != 0)
                        {
                            this.ViewModel.CounterNo6Result = "NG";
                            this.ViewModel.BackgroundColor6 = Brushes.LightPink;
                        }
                        break;

                    case JudgeItems.CounterVer: // カウンタVer.(2025.10.4yori)
                        CSH.AppMain.UpDateData06(out sts4);
                        this.ViewModel.CounterNo0Result = sts4.cnt_ver.Substring(0, 1);
                        this.ViewModel.CounterNo1Result = sts4.cnt_ver.Substring(2, 1);
                        this.ViewModel.CounterNo2Result = sts4.cnt_ver.Substring(4, 1);
                        this.ViewModel.CounterNo3Result = sts4.cnt_ver.Substring(6, 1);
                        this.ViewModel.CounterNo4Result = sts4.cnt_ver.Substring(8, 1);
                        this.ViewModel.CounterNo5Result = sts4.cnt_ver.Substring(10, 1);
                        this.ViewModel.CounterNo6Result = sts4.cnt_ver.Substring(12, 1);
                        break;

                    case JudgeItems.Count1: // カウントチェック1(2025.10.6yori)
                        CSH.AppMain.UpDateData01(out sts1);
                        CSH.AppMain.CountCheck(out sts4);
                        this.ViewModel.CounterNo0Count = sts4.cnt_data[0].ToString();
                        this.ViewModel.CounterNo1Count = sts4.cnt_data[1].ToString();
                        this.ViewModel.CounterNo2Count = sts4.cnt_data[2].ToString();
                        this.ViewModel.CounterNo3Count = sts4.cnt_data[3].ToString();
                        this.ViewModel.CounterNo4Count = sts4.cnt_data[4].ToString();
                        this.ViewModel.CounterNo5Count = sts4.cnt_data[5].ToString();
                        this.ViewModel.CounterNo6Count = sts4.cnt_data[6].ToString();
                        if (sts1.no0_fg == 0)
                        {
                            this.ViewModel.CounterNo0Count = "―";
                        }
                        else if (sts1.no0_fg == 1 && Math.Abs(sts4.cnt_data[0] - this.ViewModel.Count[0]) > 1000)
                        {
                            this.ViewModel.CounterNo0Result = "OK";
                            this.ViewModel.BackgroundColor0 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[1] - this.ViewModel.Count[1]) > 1000)
                        {
                            this.ViewModel.CounterNo1Result = "OK";
                            this.ViewModel.BackgroundColor1 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[2] - this.ViewModel.Count[2]) > 1000)
                        {
                            this.ViewModel.CounterNo2Result = "OK";
                            this.ViewModel.BackgroundColor2 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[3] - this.ViewModel.Count[3]) > 1000)
                        {
                            this.ViewModel.CounterNo3Result = "OK";
                            this.ViewModel.BackgroundColor3 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[4] - this.ViewModel.Count[4]) > 1000)
                        {
                            this.ViewModel.CounterNo4Result = "OK";
                            this.ViewModel.BackgroundColor4 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[5] - this.ViewModel.Count[5]) > 1000)
                        {
                            this.ViewModel.CounterNo5Result = "OK";
                            this.ViewModel.BackgroundColor5 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[6] - this.ViewModel.Count[6]) > 1000)
                        {
                            this.ViewModel.CounterNo6Result = "OK";
                            this.ViewModel.BackgroundColor6 = Brushes.LightGreen;
                        }
                        break;

                    case JudgeItems.Count2: // カウントチェック1(2025.10.6yori)
                        CSH.AppMain.UpDateData01(out sts1);
                        CSH.AppMain.CountCheck(out sts4);
                        this.ViewModel.CounterNo0Count = sts4.cnt_data[0].ToString();
                        this.ViewModel.CounterNo1Count = sts4.cnt_data[1].ToString();
                        this.ViewModel.CounterNo2Count = sts4.cnt_data[2].ToString();
                        this.ViewModel.CounterNo3Count = sts4.cnt_data[3].ToString();
                        this.ViewModel.CounterNo4Count = sts4.cnt_data[4].ToString();
                        this.ViewModel.CounterNo5Count = sts4.cnt_data[5].ToString();
                        this.ViewModel.CounterNo6Count = sts4.cnt_data[6].ToString();
                        if (sts1.no0_fg == 0)
                        {
                            this.ViewModel.CounterNo0Count = "―";
                        }
                        else if (sts1.no0_fg == 1 && Math.Abs(sts4.cnt_data[0]) <= 60)
                        {
                            this.ViewModel.CounterNo0Result = "OK";
                            this.ViewModel.BackgroundColor0 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[1]) <= 60)
                        {
                            this.ViewModel.CounterNo1Result = "OK";
                            this.ViewModel.BackgroundColor1 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[2]) <= 60)
                        {
                            this.ViewModel.CounterNo2Result = "OK";
                            this.ViewModel.BackgroundColor2 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[3]) <= 60)
                        {
                            this.ViewModel.CounterNo3Result = "OK";
                            this.ViewModel.BackgroundColor3 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[4]) <= 60)
                        {
                            this.ViewModel.CounterNo4Result = "OK";
                            this.ViewModel.BackgroundColor4 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[5]) <= 60)
                        {
                            this.ViewModel.CounterNo5Result = "OK";
                            this.ViewModel.BackgroundColor5 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[6]) <= 60)
                        {
                            this.ViewModel.CounterNo6Result = "OK";
                            this.ViewModel.BackgroundColor6 = Brushes.LightGreen;
                        }
                        break;

                    case JudgeItems.ZXScale: // カウントチェック1(2025.10.6yori)
                        CSH.AppMain.CountCheck(out sts4);
                        this.ViewModel.CounterNo8Count = sts4.cnt_data[7].ToString();
                        this.ViewModel.CounterNo9Count = sts4.cnt_data[8].ToString();
                        if (Math.Abs(sts4.cnt_data[7] - this.ViewModel.Count[7]) > 1000)
                        {
                            this.ViewModel.CounterNo8Judge = "OK";
                            this.ViewModel.BackgroundColor0 = Brushes.LightGreen;
                        }
                        if (Math.Abs(sts4.cnt_data[8] - this.ViewModel.Count[8]) > 1000)
                        {
                            this.ViewModel.CounterNo9Judge = "OK";
                            this.ViewModel.BackgroundColor0 = Brushes.LightGreen;
                        }
                        CSH.AppMain.UpDateData06(out sts4);
                        this.ViewModel.CounterNo8Ver = sts4.cnt_ver.Substring(14, 1);
                        this.ViewModel.CounterNo9Ver = sts4.cnt_ver.Substring(16, 1);
                        break;

                    case JudgeItems.Temp: // 温度センサー(2025.10.6yori)
                        CSH.AppMain.UpDateData01(out sts1);
                        this.ViewModel.ArmTempA = sts1.tempature[0].ToString("F1");
                        this.ViewModel.ArmTempB = sts1.tempature[3].ToString("F1");
                        this.ViewModel.ArmTempC = sts1.tempature[6].ToString("F1");
                        this.ViewModel.CalTempA = sts1.cal_tempature[0].ToString("F1");
                        this.ViewModel.CalTempB = sts1.cal_tempature[3].ToString("F1");
                        this.ViewModel.CalTempC = sts1.cal_tempature[6].ToString("F1");
                        break;

                    default:
                        break;
                }
            });
        }
    }
}
