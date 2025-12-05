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
    /// ContactInspectionPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class ContactInspectionPanel : PanelBase
    {
        public ContactInspectionPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.ContactInspection)
        {
            InitializeComponent();
            this.DataContext = model;

            // 初期化処理 2025.8.26 eba
            this.ViewModel.ImageVisibility = Visibility.Visible;
            this.ViewModel.GridVisibility = Visibility.Hidden;
            this.ViewModel.GridVisibility2 = Visibility.Hidden;
            this.ViewModel.GridVisibility3 = Visibility.Hidden;
            this.ViewModel.IsStartBtnEnabled = true;
            this.ViewModel.IsBackBtnEnabled = false;
            this.ViewModel.IsReStartBtnEnabled = false;
            this.ViewModel.IsSaveBtnEnabled = false;
            this.ViewModel.IsSettingBtnEnabled = true;
            this.ViewModel.SnapVisibility = Visibility.Hidden;
            this.ViewModel.GaugeLength = "0.000";
            this.ViewModel.IsTextBoxEnabled = true;

            // どのキャリブを立ち上げるのか引数で指定 2025.8.27 add eba
            //CalibMseBox calibPara = new CalibMseBox(); // 2025.9.3 add eba
            this.ViewModel.CalibMseBox.Language = 1;
            //this.ViewModel.CalibMseBox.CalibType = this.ViewModel.CalibStyleFg;
            string path;
            string mes;
            CSH.Grp02.ContactInspectionPanelInit(ref this.ViewModel.CalibMseBox, out path, 512, out mes, 1024);
            this.ViewModel.ImageSource = this.ViewModel.CalibMseBox.path;
            this.ViewModel.SubtitleText = this.ViewModel.CalibMseBox.mes;
            //this.ViewModel.GaugeLength = this.ViewModel.CalibMseBox.GaugePara.BallBarLen.ToString("F4");



        }


        private ContactInspectionViewModel ViewModel
        {
            get => this.DataContext as ContactInspectionViewModel;
        }


        public override void Terminate()
        {
            CSH.Grp02.ContactInspectionPanelTerminate(ref this.ViewModel.CalibMseBox);
           
        }

        public void MesCallBack()
        {
            CSH.Grp02.ContactInspectionPanelMesCallBack(ref this.ViewModel.CalibMseBox);
            this.ViewModel.ImageSource = this.ViewModel.CalibMseBox.path;
            this.ViewModel.SubtitleText = this.ViewModel.CalibMseBox.mes;

            UsrMessageBox.Show(this.ViewModel.CalibMseBox.MesString, "Information", MessageBoxButton.OK, MessageBoxImage.Information);
            this.ViewModel.CalibMseBox.MesString = 0;
        }

        public void ParaOutCallBack()
        {

            CSH.Grp02.ContactInspectionPanelParaOutCallBack(ref this.ViewModel.CalibMseBox);
            this.ViewModel.SubtitleText = VecApp.Properties.Resources.String265;

            switch ((CalibType)this.ViewModel.CalibMseBox.CalibType)
            {
                case CalibType.INSPECT_MULTI_GAUGE_NEST_STD:
                    this.ViewModel.ImageVisibility = Visibility.Hidden;
                    this.ViewModel.GridVisibility = Visibility.Visible;

                    this.ViewModel.XMaxMinValue = this.ViewModel.CalibMseBox.InspAndProbCkResult.pp[0].ToString("F3");
                    this.ViewModel.YMaxMinValue = this.ViewModel.CalibMseBox.InspAndProbCkResult.pp[1].ToString("F3");
                    this.ViewModel.ZMaxMinValue = this.ViewModel.CalibMseBox.InspAndProbCkResult.pp[2].ToString("F3");

                    this.ViewModel.XTwoSigmaValue = this.ViewModel.CalibMseBox.InspAndProbCkResult.sigma2[0].ToString("F3");
                    this.ViewModel.YTwoSigmaValue = this.ViewModel.CalibMseBox.InspAndProbCkResult.sigma2[1].ToString("F3");
                    this.ViewModel.ZTwoSigmaValue = this.ViewModel.CalibMseBox.InspAndProbCkResult.sigma2[2].ToString("F3");
                    this.ViewModel.DistanceTwoSigmaValue = this.ViewModel.CalibMseBox.InspAndProbCkResult.sigma2[3].ToString("F3");

                    this.ViewModel.FaceDistanceValue = this.ViewModel.CalibMseBox.InspAndProbCkResult.plate.ToString("F3");
                    this.ViewModel.MeasurementErrorValue = this.ViewModel.CalibMseBox.PlateErrVal.ToString("F3");

                    // OK・NG表示
                    if (this.ViewModel.CalibMseBox.CalibInspectJudge == 0)
                    {
                        this.ViewModel.ResultText = this.ViewModel.ToggleResultText();  // OK
                        this.ViewModel.ResultJudge = true;  // 背景色緑
                    }
                    else
                    {
                        this.ViewModel.ResultJudge = false; // 背景色赤
                    }

                    // 各結果の背景色変更
                    if (this.ViewModel.CalibMseBox.InspectionResultFg.pp[0] == 0)
                    {
                        this.ViewModel.XMaxMinJudge = true;
                    }
                    else
                    {
                        this.ViewModel.XMaxMinJudge = false;
                    }

                    if (this.ViewModel.CalibMseBox.InspectionResultFg.pp[1] == 0)
                    {
                        this.ViewModel.YMaxMinJudge = true;
                    }
                    else
                    {
                        this.ViewModel.YMaxMinJudge = false;
                    }

                    if (this.ViewModel.CalibMseBox.InspectionResultFg.pp[2] == 0)
                    {
                        this.ViewModel.ZMaxMinJudge = true;
                    }
                    else
                    {
                        this.ViewModel.ZMaxMinJudge = false;
                    }

                    if (this.ViewModel.CalibMseBox.InspectionResultFg.sigma2[0] == 0)
                    {
                        this.ViewModel.XTwoSigmaJudge = true;
                    }
                    else
                    {
                        this.ViewModel.XTwoSigmaJudge = false;
                    }

                    if (this.ViewModel.CalibMseBox.InspectionResultFg.sigma2[1] == 0)
                    {
                        this.ViewModel.YTwoSigmaJudge = true;
                    }
                    else
                    {
                        this.ViewModel.YTwoSigmaJudge = false;
                    }

                    if (this.ViewModel.CalibMseBox.InspectionResultFg.sigma2[2] == 0)
                    {
                        this.ViewModel.ZTwoSigmaJudge = true;
                    }
                    else
                    {
                        this.ViewModel.ZTwoSigmaJudge = false;
                    }

                    if (this.ViewModel.CalibMseBox.InspectionResultFg.sigma2[3] == 0)
                    {
                        this.ViewModel.DistanceTwoSigmaJudge = true;
                    }
                    else
                    {
                        this.ViewModel.DistanceTwoSigmaJudge = false;
                    }

                    if (this.ViewModel.CalibMseBox.InspectionResultFg.plate == 0)
                    {
                        this.ViewModel.MeasurementErrorJudge = true;
                    }
                    else
                    {
                        this.ViewModel.MeasurementErrorJudge = false;
                    }



                    // しきい値表示
                    this.ViewModel.ThresholdText =
                            "最大最小しきい値 : " +
                            this.ViewModel.CalibMseBox.InspectionThreshold.pp.ToString("F2") +
                            "\n" +
                            "2σしきい値 : " +
                            this.ViewModel.CalibMseBox.InspectionThreshold.sigma2.ToString("F2") +
                            "\n" +
                            "面間誤差しきい値 : " +
                            this.ViewModel.CalibMseBox.InspectionThreshold.plate.ToString("F2");

                    break;

                case CalibType.ALIGNMENT_MULTI_GAUGE:
                    this.ViewModel.ImageVisibility = Visibility.Hidden;
                    this.ViewModel.GridVisibility2 = Visibility.Visible;

                    // OK・NG表示
                    if (this.ViewModel.CalibMseBox.CalibResultJudge == 0)
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

                case CalibType.ALIGNMENT_BALL_GAUGE_STD:
                    this.ViewModel.ImageVisibility = Visibility.Hidden;
                    this.ViewModel.GridVisibility3 = Visibility.Visible;

                    this.ViewModel.CenterBefValue = this.ViewModel.CalibMseBox.InspAndProbCkResult.ri.ToString("F3");
                    this.ViewModel.DiaBefValue = this.ViewModel.CalibMseBox.InspAndProbCkResult.Ps.ToString("F3");
                    this.ViewModel.CenterAftValue = this.ViewModel.CalibMseBox.InspAndProbCkResult2.ri.ToString("F3");
                    this.ViewModel.DiaAftValue = this.ViewModel.CalibMseBox.InspAndProbCkResult2.Ps.ToString("F3");

                    // しきい値表示
                    this.ViewModel.ThresholdText3 =
                            "最大最小しきい値 : " +
                            this.ViewModel.CalibMseBox.InspectionThreshold.pp.ToString("F2") +
                            "\n" +
                            "2σしきい値 : " +
                            this.ViewModel.CalibMseBox.InspectionThreshold.sigma2.ToString("F2") +
                            "\n" +
                            "面間誤差しきい値 : " +
                            this.ViewModel.CalibMseBox.InspectionThreshold.plate.ToString("F2");

                    // 収束したかどうか
                    if (this.ViewModel.CalibMseBox.CalibResultJudge == 0)
                    {  
                        this.ViewModel.ResultText3 = VecApp.Properties.Resources.String266;
                    }
                    else
                    {
                        this.ViewModel.ResultText3 = VecApp.Properties.Resources.String267;
                    }

                    // 精度が改善したかどうか
                    if (this.ViewModel.CalibMseBox.CalibInspectJudge == 0)
                    {
                        this.ViewModel.ResultJudge3 = true;  // 背景色緑
                    }
                    else
                    {
                        this.ViewModel.ResultJudge3 = false; // 背景色黄色
                    }

                    break;

                default:
                    break;



            }
 


        }


        private void Click_StartBtn(object sender, RoutedEventArgs e)
        {
            switch ((CalibType)this.ViewModel.CalibMseBox.CalibType)
            {
                case CalibType.INSPECT_MULTI_GAUGE_NEST_STD:
                    break;

                case CalibType.ALIGNMENT_MULTI_GAUGE:
                    DlgBarLen dlg = new DlgBarLen();
                    bool? result = null;

                    dlg.ViewModel.Length = this.ViewModel.CalibMseBox.GaugePara.BallBarLen.ToString("F4");
                    result = dlg.ShowDialog();
                    if (result == true)
                    {
                        this.ViewModel.CalibMseBox.GaugePara.BallBarLen = Convert.ToDouble(dlg.ViewModel.Length);
                    }

                    break;

                case CalibType.ALIGNMENT_BALL_GAUGE_STD:
                    break;

                default:
                    break;
            }


            //this.ViewModel.CalibMseBox.GaugePara.BallBarLen = Convert.ToDouble(this.ViewModel.GaugeLength);

            CSH.Grp02.ContactInspectionPanelClickStart(ref this.ViewModel.CalibMseBox);

            if(this.ViewModel.CalibMseBox.MesString ==0)
            {
                this.ViewModel.IsStartBtnEnabled = false;
                this.ViewModel.IsBackBtnEnabled = true;
                this.ViewModel.IsReStartBtnEnabled = true;
                this.ViewModel.IsTextBoxEnabled = false;
                this.ViewModel.IsSettingBtnEnabled = false;
                this.ViewModel.ImageSource = this.ViewModel.CalibMseBox.path;
                this.ViewModel.SubtitleText = this.ViewModel.CalibMseBox.mes;
            }
            else
            {
                UsrMessageBox.Show(this.ViewModel.CalibMseBox.MesString, "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                this.ViewModel.CalibMseBox.MesString = 0;
            }

         
            //確認用(画像とテキストボックスの切り替え) アスタワン様サンプル
            //this.ViewModel.ImageVisibility = Visibility.Hidden;
            //this.ViewModel.GridVisibility = Visibility.Visible;
        }


        private void Click_BackBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.ContactInspectionPanelClickBack(ref this.ViewModel.CalibMseBox);
            this.ViewModel.ImageSource = this.ViewModel.CalibMseBox.path;
            this.ViewModel.SubtitleText = this.ViewModel.CalibMseBox.mes;

        }


        private void Click_FirstBackBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.ContactInspectionPanelClickReStart(ref this.ViewModel.CalibMseBox);
            this.ViewModel.IsStartBtnEnabled = true;
            this.ViewModel.IsBackBtnEnabled = false;
            this.ViewModel.IsReStartBtnEnabled = false;
            this.ViewModel.IsTextBoxEnabled = true;
            this.ViewModel.ImageSource = this.ViewModel.CalibMseBox.path;
            this.ViewModel.SubtitleText = this.ViewModel.CalibMseBox.mes;
            this.ViewModel.IsSettingBtnEnabled = true;

            //確認用(ResutTextのOK/NGの切り替え)　アスタワン様サンプル
            //this.ViewModel.ResultText = this.ViewModel.ToggleResultText();
        }


        private void Click_CloseBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.Inspection;
        }


        private void Click_HistoryBtn(object sender, RoutedEventArgs e)
        {

            DlgHistory dlg = new DlgHistory();
            bool? test = false;

            switch ((CalibType)this.ViewModel.CalibMseBox.CalibType)
            {
                case CalibType.INSPECT_MULTI_GAUGE_NEST_STD:

                    break;

                case CalibType.ALIGNMENT_MULTI_GAUGE:
                case CalibType.ALIGNMENT_BALL_GAUGE_STD:
                    dlg.SetHistoryText(this.ViewModel.CalibMseBox.CalibResultVal.ToString("F0"));

                    break;

                default:
                    break;
            }

            test = dlg.ShowDialog();
            

        }


        private void Click_SettingBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.Setting;
        }


        private void Click_SaveBtn(object sender, RoutedEventArgs e)
        {

        }


        private void Click_SnapBtn(object sender, RoutedEventArgs e)
        {

        }


        private void Click_HelpBtn(object sender, RoutedEventArgs e)
        {
            switch((CalibType)this.ViewModel.CalibMseBox.CalibType)
            {
                case CalibType.INSPECT_MULTI_GAUGE_NEST_STD:
                    this.ViewModel.ImageSource = "C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\chkpos_V8_Multi.png";
                    break;

                case CalibType.ALIGNMENT_MULTI_GAUGE:
                    this.ViewModel.ImageSource = "C:\\ProgramData\\Kosakalab\\Kosaka CMM\\Inifiles\\calib\\light_V8_Multi.png";
                    break;

                default:
                    break;
            }
                
        }


      


        private void Click_ProbeBtn(object sender, RoutedEventArgs e)
        {

        }


        private void Click_ContactBtn(object sender, RoutedEventArgs e)
        {

            CSH.Grp02.ContactInspectionPanelClickReStore(ref this.ViewModel.CalibMseBox);
        }
    }
}
