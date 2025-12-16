// 追加(2025.12.7yori)
using CSH;
using Microsoft.VisualBasic;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
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

namespace VecApp
{
    /// <summary>
    /// ScannerAlignmentPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class ScannerAlignmentPanel : PanelBase
    {
        public ScannerAlignmentPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.ScannerAlignment)
        {
            InitializeComponent();
            this.DataContext = model;

            // 初期化処理
            this.ViewModel.ImageVisibility = Visibility.Visible;
            this.ViewModel.GridVisibility2 = Visibility.Hidden;
            this.ViewModel.GridVisibility3 = Visibility.Hidden;
            this.ViewModel.IsFullCalStartBtnEnabled = false; // 変更(2025.12.16yori)
            this.ViewModel.FullCalStartButtonOpacity = 0.25; // 追加(2025.12.16yori)
            this.ViewModel.IsBackBtnEnabled = false; // 変更(2025.12.16yori)
            this.ViewModel.BackButtonOpacity = 0.25; // 追加(2025.12.16yori)
            this.ViewModel.IsStopBtnEnabled = false; // 変更(2025.12.16yori)
            this.ViewModel.StopButtonOpacity = 0.25; // 追加(2025.12.16yori)
        }

        private ScannerAlignmentViewModel ViewModel
        {
            get => this.DataContext as ScannerAlignmentViewModel;
        }

        // 画面の初期設定
        public void ScannerAlignmentPanelSetup()
        {
            this.ViewModel.CalibScannerMseBox.Language = 2; // 英語(2025.12.14yori)
            string path;
            string mes;
            CSH.Grp02.ScannerAlignmentPanelInit(ref this.ViewModel.CalibScannerMseBox, out path, 512, out mes, 1024);
            this.ViewModel.ImageSource = this.ViewModel.CalibScannerMseBox.path;
            this.ViewModel.SubtitleText = this.ViewModel.CalibScannerMseBox.msg;
            switch ((CalibType)this.ViewModel.CalibScannerMseBox.CalibType) // 追加(2025.12.16yori)
            {
                case CalibType.SCANNER_MAKE_MATRIX:
                    this.ViewModel.IsFullCalStartBtnEnabled = false;
                    this.ViewModel.FullCalStartButtonOpacity = 0.25;
                    break;
                case CalibType.SCANNER_FULL:
                    this.ViewModel.IsFullCalStartBtnEnabled = true;
                    this.ViewModel.FullCalStartButtonOpacity = 1.0;
                    break;
                default:
                    break;
            }
            this.ViewModel.IsBackBtnEnabled = false;
            this.ViewModel.BackButtonOpacity = 0.25;
            this.ViewModel.IsStopBtnEnabled = false;
            this.ViewModel.StopButtonOpacity = 0.25;
        }

        public override void Terminate()
        {
            CSH.Grp02.ScannerAlignmentPanelTerminate();           
        }

        // 点検キャリブ画像切り替え(2025.12.5yori)
        public void MesCallBack()
        {
            CSH.Grp02.ScannerAlignmentPanelMesCallBack(ref this.ViewModel.CalibScannerMseBox);
            this.ViewModel.ImageSource = this.ViewModel.CalibScannerMseBox.path;
            this.ViewModel.SubtitleText = this.ViewModel.CalibScannerMseBox.msg;
            if (this.ViewModel.CalibScannerMseBox.ShotNo != 0 || this.ViewModel.CalibScannerMseBox.ScanShotNo != 0)// 追加(2025.12.16yori)
            {
                this.ViewModel.IsBackBtnEnabled = true;
                this.ViewModel.BackButtonOpacity = 1.0;
                this.ViewModel.IsStopBtnEnabled = true;
                this.ViewModel.StopButtonOpacity = 1.0;
            }
            //UsrMessageBox.Show(this.ViewModel.CalibMseBox.MesString, "Information", MessageBoxButton.OK, MessageBoxImage.Information);
            //this.ViewModel.CalibMseBox.MesString = 0;
        }

        // 結果表示(2025.12.9yori)
        public void ResultCallBack()
        {
            CSH.Grp02.ScannerAlignmentPanelResultCallBack(ref this.ViewModel.CalibScannerMseBox);
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String265;

            switch ((CalibType)this.ViewModel.CalibScannerMseBox.CalibType)
            {
                case CalibType.SCANNER_FULL:
                    this.ViewModel.ImageVisibility = Visibility.Hidden;
                    this.ViewModel.GridVisibility2 = Visibility.Visible;

                    // OK・NG表示
                    if (this.ViewModel.CalibScannerMseBox.CalibResultJudge == 0)
                    {
                        this.ViewModel.ResultText2 = "OK";
                        this.ViewModel.ResultJudge2 = true;  // 背景色緑
                    }
                    else
                    {
                        this.ViewModel.ResultText2 = "NG";
                        this.ViewModel.ResultJudge2 = false; // 背景色赤
                    }

                    break;

                default:
                    break;
            }
            // ボタンの状態変更(2025.12.16yori)
            this.ViewModel.IsFullCalStartBtnEnabled = true;
            this.ViewModel.FullCalStartButtonOpacity = 1.0;
            this.ViewModel.IsBackBtnEnabled = false;
            this.ViewModel.BackButtonOpacity = 0.25;
            this.ViewModel.IsStopBtnEnabled = false;
            this.ViewModel.StopButtonOpacity = 0.25;
        }

        // フルキャリ開始ボタン
        private void Click_FullCalStartBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp03.ScannerAlignmentPanelFullCalStartBtn(); // スキャンスタート(2025.12.8yori)
            this.ViewModel.IsFullCalStartBtnEnabled = false; // 追加(2025.12.16yori)
            this.ViewModel.FullCalStartButtonOpacity = 0.25; // 追加(2025.12.16yori)
        }

        // 戻るボタン
        private void Click_BackBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.ScannerAlignmentPanelClickBack(ref this.ViewModel.CalibScannerMseBox); // 追加(2025.12.12yori)
            this.ViewModel.ImageSource = this.ViewModel.CalibScannerMseBox.path;
            this.ViewModel.SubtitleText = this.ViewModel.CalibScannerMseBox.msg;
            if (this.ViewModel.CalibScannerMseBox.ShotNo == 0 && this.ViewModel.CalibScannerMseBox.ScanShotNo == 0)// 追加(2025.12.16yori)
            {
                this.ViewModel.IsBackBtnEnabled = false;
                this.ViewModel.BackButtonOpacity = 0.25;
                this.ViewModel.IsStopBtnEnabled = false;
                this.ViewModel.StopButtonOpacity = 0.25;
            }
        }

        // 中止ボタン(2025.12.16yori)
        private void Click_StopBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.ScannerAlignmentPanelClickReStart(ref this.ViewModel.CalibScannerMseBox);
            this.ViewModel.ImageSource = this.ViewModel.CalibScannerMseBox.path;
            this.ViewModel.SubtitleText = this.ViewModel.CalibScannerMseBox.msg;
            switch ((CalibType)this.ViewModel.CalibScannerMseBox.CalibType)
            {
                case CalibType.SCANNER_FULL:
                    CSH.Grp03.Cmd02(); // スキャンストップ
                    break;

                default:
                    break;
            }
            this.ViewModel.IsBackBtnEnabled = false;
            this.ViewModel.BackButtonOpacity = 0.25;
            this.ViewModel.IsStopBtnEnabled = false;
            this.ViewModel.StopButtonOpacity = 0.25;
        }

        private void Click_CloseBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.Inspection;
        }


        private void Click_HistoryBtn(object sender, RoutedEventArgs e)
        {

            DlgHistory dlg = new DlgHistory();
            bool? test = false;

            switch ((CalibType)this.ViewModel.CalibScannerMseBox.CalibType)
            {
                case CalibType.SCANNER_FULL:
                    dlg.SetHistoryText("[" + VecApp.Properties.Resources.String62 + "1] = " +
                                       this.ViewModel.CalibScannerMseBox.dResult[0].ToString("F3") + " " +
                                       this.ViewModel.CalibScannerMseBox.dResult[1].ToString("F3") + " " +
                                       this.ViewModel.CalibScannerMseBox.dResult[2].ToString("F3") + "\n" +
                                       "[" + VecApp.Properties.Resources.String62 + "2] = " +
                                       this.ViewModel.CalibScannerMseBox.dResult[3].ToString("F3") + " " +
                                       this.ViewModel.CalibScannerMseBox.dResult[4].ToString("F3") + " " +
                                       this.ViewModel.CalibScannerMseBox.dResult[5].ToString("F3") + "\n" +
                                       "[" + VecApp.Properties.Resources.String62 + "3] = " +
                                       this.ViewModel.CalibScannerMseBox.dResult[6].ToString("F3") + " " +
                                       this.ViewModel.CalibScannerMseBox.dResult[7].ToString("F3") + " " +
                                       this.ViewModel.CalibScannerMseBox.dResult[8].ToString("F3") + "\n" +
                                       "[" + VecApp.Properties.Resources.String62 + "4] = " +
                                       this.ViewModel.CalibScannerMseBox.dResult[9].ToString("F3") + " " +
                                       this.ViewModel.CalibScannerMseBox.dResult[10].ToString("F3") + " " +
                                       this.ViewModel.CalibScannerMseBox.dResult[11].ToString("F3") + "\n" +
                                       "[" + VecApp.Properties.Resources.String78 + "] = " +
                                       this.ViewModel.CalibScannerMseBox.maxmin[0].ToString("F3") + " " +
                                       this.ViewModel.CalibScannerMseBox.maxmin[1].ToString("F3") + " " +
                                       this.ViewModel.CalibScannerMseBox.maxmin[2].ToString("F3") + "\n");
                    break;

                default:
                    break;
            }

            test = dlg.ShowDialog();
        }


        // ユーザーキャリ開始ボタン
        private void Click_UserCalStartBtn(object sender, RoutedEventArgs e)
        {

        }
    }
}
