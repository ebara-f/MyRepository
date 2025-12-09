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
            this.ViewModel.GridVisibility = Visibility.Hidden;
            this.ViewModel.GridVisibility2 = Visibility.Hidden;
            this.ViewModel.GridVisibility3 = Visibility.Hidden;
            this.ViewModel.IsStartBtnEnabled = true;
            this.ViewModel.IsBackBtnEnabled = false;
            this.ViewModel.IsReStartBtnEnabled = false;
            this.ViewModel.IsTextBoxEnabled = true;
        }

        private ScannerAlignmentViewModel ViewModel
        {
            get => this.DataContext as ScannerAlignmentViewModel;
        }

        // 画面の初期設定
        public void ScannerAlignmentPanelSetup()
        {
            this.ViewModel.CalibScannerMseBox.Language = 1; // 日本語
            string path;
            string mes;
            CSH.Grp02.ScannerAlignmentPanelInit(ref this.ViewModel.CalibScannerMseBox, out path, 512, out mes, 1024);
            this.ViewModel.ImageSource = this.ViewModel.CalibScannerMseBox.path;
            this.ViewModel.SubtitleText = this.ViewModel.CalibScannerMseBox.msg;
            this.ViewModel.StartButtonText = VecApp.Properties.Resources.String273; // フルキャリ開始(2025.12.8yori)
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

                    //SetHistoryText(this.ViewModel.CalibMseBox.CalibResultVal.ToString("F0"));

                    break;

                default:
                    break;
            }
        }

        // フルキャリ開始ボタン
        private void Click_FullCalStartBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp03.ScannerAlignmentPanelFullCalStartBtn(); // スキャンスタート(2025.12.8yori)
        }

        private void Click_BackBtn(object sender, RoutedEventArgs e)
        {
            //CSH.Grp02.ScannerAlignmentPanelClickBack(ref this.ViewModel.CalibMseBox);
            this.ViewModel.ImageSource = this.ViewModel.CalibScannerMseBox.path;
            this.ViewModel.SubtitleText = this.ViewModel.CalibScannerMseBox.msg;

        }


        private void Click_FirstBackBtn(object sender, RoutedEventArgs e)
        {
            //CSH.Grp02.ScannerAlignmentPanelClickReStart(ref this.ViewModel.CalibMseBox);
            this.ViewModel.IsStartBtnEnabled = true;
            this.ViewModel.IsBackBtnEnabled = false;
            this.ViewModel.IsReStartBtnEnabled = false;
            this.ViewModel.IsTextBoxEnabled = true;
            this.ViewModel.ImageSource = this.ViewModel.CalibScannerMseBox.path;
            this.ViewModel.SubtitleText = this.ViewModel.CalibScannerMseBox.msg;

            //確認用(ResutTextのOK/NGの切り替え)　アスタワン様サンプル
            //this.ViewModel.ResultText = this.ViewModel.ToggleResultText();
        }

        // 中止ボタン
        private void Click_CancelBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp03.Cmd02(); // スキャンストップ(2025.12.5yori)
        }

        private void Click_CloseBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.Inspection;
        }


        private void Click_HistoryBtn(object sender, RoutedEventArgs e)
        {

            DlgHistory dlg = new DlgHistory();
            bool? test = false;

            //switch ((CalibType)this.ViewModel.CalibMseBox.CalibType)
            //{
            //    case CalibType.INSPECT_MULTI_GAUGE_NEST_STD:

            //        break;

            //    case CalibType.ALIGNMENT_MULTI_GAUGE:
            //    case CalibType.ALIGNMENT_BALL_GAUGE_STD:
            //        dlg.SetHistoryText(this.ViewModel.CalibMseBox.CalibResultVal.ToString("F0"));

            //        break;

            //    default:
            //        break;
            //}

            test = dlg.ShowDialog();
            

        }

        private void Click_ProbeBtn(object sender, RoutedEventArgs e)
        {

        }
    }
}
