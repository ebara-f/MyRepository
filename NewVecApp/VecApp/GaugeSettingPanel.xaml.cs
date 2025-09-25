using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Security.Cryptography;
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
using CSH;

namespace VecApp
{
    /// <summary>
    /// GaugeSettingPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class GaugeSettingPanel : PanelBase
    {
        public GaugeSettingPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.GaugeSetting)
        {
            InitializeComponent();
            this.DataContext = model;

            // ゲージ設定の初期値表示(2025.8.7yori)
            Gauge ga = new Gauge();
            CSH.AppMain.UpDateData05(out ga);
            // パラメータ
            ViewModel.CenterScopePntX = ga.Center_ScopePnt[0].ToString("F2");
            ViewModel.CenterScopePntY = ga.Center_ScopePnt[1].ToString("F2");
            ViewModel.CenterScopePntZ = ga.Center_ScopePnt[0].ToString("F2");
            ViewModel.CenterScopePntRad = ga.Center_ScopeRad.ToString("F2");
            ViewModel.PlaneScopePnt00 = ga.Plane_ScopePnt[0].ToString("F2");
            ViewModel.PlaneScopePnt01 = ga.Plane_ScopePnt[1].ToString("F2");
            ViewModel.PlaneScopePnt02 = ga.Plane_ScopePnt[2].ToString("F2");
            ViewModel.PlaneScopePnt10 = ga.Plane_ScopePnt[3].ToString("F2");
            ViewModel.PlaneScopePnt11 = ga.Plane_ScopePnt[4].ToString("F2");
            ViewModel.PlaneScopePnt12 = ga.Plane_ScopePnt[5].ToString("F2");
            ViewModel.PlaneScopePnt20 = ga.Plane_ScopePnt[6].ToString("F2");
            ViewModel.PlaneScopePnt21 = ga.Plane_ScopePnt[7].ToString("F2");
            ViewModel.PlaneScopePnt22 = ga.Plane_ScopePnt[8].ToString("F2");
            ViewModel.PlaneScopePnt30 = ga.Plane_ScopePnt[9].ToString("F2");
            ViewModel.PlaneScopePnt31 = ga.Plane_ScopePnt[10].ToString("F2");
            ViewModel.PlaneScopePnt32 = ga.Plane_ScopePnt[11].ToString("F2");
            ViewModel.PlaneScopeRad = ga.Plane_ScopeRad.ToString("F2");
            ViewModel.LengthScopePnt00 = ga.Length_ScopePnt[0].ToString("F2");
            ViewModel.LengthScopePnt01 = ga.Length_ScopePnt[1].ToString("F2");
            ViewModel.LengthScopePnt02 = ga.Length_ScopePnt[2].ToString("F2");
            ViewModel.LengthScopePnt10 = ga.Length_ScopePnt[3].ToString("F2");
            ViewModel.LengthScopePnt11 = ga.Length_ScopePnt[4].ToString("F2");
            ViewModel.LengthScopePnt12 = ga.Length_ScopePnt[5].ToString("F2");
            ViewModel.LengthScopePnt20 = ga.Length_ScopePnt[6].ToString("F2");
            ViewModel.LengthScopePnt21 = ga.Length_ScopePnt[7].ToString("F2");
            ViewModel.LengthScopePnt22 = ga.Length_ScopePnt[8].ToString("F2");
            ViewModel.LengthScopePnt30 = ga.Length_ScopePnt[9].ToString("F2");
            ViewModel.LengthScopePnt31 = ga.Length_ScopePnt[10].ToString("F2");
            ViewModel.LengthScopePnt32 = ga.Length_ScopePnt[11].ToString("F2");
            ViewModel.LengthScopeRad = ga.Length_ScopeRad.ToString("F2");
            ViewModel.LengthScopeRadCnt = ga.Length_ScopeRad_Cnt.ToString();
            // 制限
            ViewModel.CenterLimit = ga.Center_Limit.ToString("F2");
            ViewModel.PlaneLimit = ga.Plane_Limit.ToString("F2");
            ViewModel.LengthLimit = ga.Length_Limit.ToString("F2");
            ViewModel.OnlyBallCenterLimit = ga.Only_Ball_Center_Limit.ToString("F2"); // 新たにscancheckball.iniを作成し、値を取得(2025.8.10yori)
            ViewModel.PlaneMeasPntLimit = ga.Plane_MeasPnt_Limit.ToString();
            ViewModel.LengthMeasPntLimit = ga.Length_MeasPnt_Limit.ToString();
            ViewModel.KidoBase = ga.Kido_Base.ToString();
            ViewModel.KidoLimit = ga.Kido_Limit.ToString("F2");
            // ゲージタイプの初期値をVAC46に設定(2025.8.9yori)
            ViewModel.GaugeIndex = 2;
        }

        private GaugeSettingViewModel ViewModel
        {
            get => this.DataContext as GaugeSettingViewModel;
        }

        private void Click_InitialSettingBtn(object sender, RoutedEventArgs e)
        {
            Gauge ga = new Gauge();
            CSH.AppMain.UpDateData05_Default(out ga);
            // 制限値のみ初期設定(2025.8.9yori)
            ViewModel.CenterLimit = ga.Center_Limit.ToString("F2");
            ViewModel.PlaneLimit = ga.Plane_Limit.ToString("F2");
            ViewModel.LengthLimit = ga.Length_Limit.ToString("F2");
            ViewModel.OnlyBallCenterLimit = "0.18";
            ViewModel.PlaneMeasPntLimit = ga.Plane_MeasPnt_Limit.ToString();
            ViewModel.LengthMeasPntLimit = ga.Length_MeasPnt_Limit.ToString();
            ViewModel.KidoBase = ga.Kido_Base.ToString();
            ViewModel.KidoLimit = ga.Kido_Limit.ToString("F2");
        }
        private void Click_DoneBtn(object sender, RoutedEventArgs e)
        {
            // ゲージ設定画面からゲージ設定値情報を取得し、iniファイルへ送る。(2025.8.9yori)
            Gauge ga = new Gauge();
            ga.Center_Limit = double.Parse(ViewModel.CenterLimit);
            ga.Plane_Limit = double.Parse(ViewModel.PlaneLimit);
            ga.Length_Limit = double.Parse(ViewModel.LengthLimit);
            ga.Only_Ball_Center_Limit = double.Parse(ViewModel.OnlyBallCenterLimit);
            ga.Plane_MeasPnt_Limit = int.Parse(ViewModel.PlaneMeasPntLimit);
            ga.Length_MeasPnt_Limit = int.Parse(ViewModel.LengthMeasPntLimit);
            ga.Kido_Base = int.Parse(ViewModel.KidoBase);
            ga.Kido_Limit = double.Parse(ViewModel.KidoLimit);
            CSH.AppMain.UpDateData05_Write(in ga);

            Parent.CurrentPanel = Panel.Inspection; // 追加(2025.7.31yori)
        }
        private void Click_CancelBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.Inspection; // 追加(2025.7.31yori)
        }

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            CSH.Grp02.Cmd08(ViewModel.GaugeIndex); // vecgauge.iniのGageType=値を変更する。(2025.8.9yori)
            Gauge ga = new Gauge();
            CSH.AppMain.UpDateData05(out ga);
            // GageType=値に応じてvecgauge.iniの値を切り替える。(2025.8.9yori)
            ViewModel.CenterScopePntRad = ga.Center_ScopeRad.ToString("F2");
            ViewModel.LengthScopePnt00 = ga.Length_ScopePnt[0].ToString("F2");
            ViewModel.LengthScopePnt01 = ga.Length_ScopePnt[1].ToString("F2");
            ViewModel.LengthScopePnt02 = ga.Length_ScopePnt[2].ToString("F2");
            ViewModel.LengthScopePnt10 = ga.Length_ScopePnt[3].ToString("F2");
            ViewModel.LengthScopePnt11 = ga.Length_ScopePnt[4].ToString("F2");
            ViewModel.LengthScopePnt12 = ga.Length_ScopePnt[5].ToString("F2");
            ViewModel.LengthScopePnt20 = ga.Length_ScopePnt[6].ToString("F2");
            ViewModel.LengthScopePnt21 = ga.Length_ScopePnt[7].ToString("F2");
            ViewModel.LengthScopePnt22 = ga.Length_ScopePnt[8].ToString("F2");
            ViewModel.LengthScopePnt30 = ga.Length_ScopePnt[9].ToString("F2");
            ViewModel.LengthScopePnt31 = ga.Length_ScopePnt[10].ToString("F2");
            ViewModel.LengthScopePnt32 = ga.Length_ScopePnt[11].ToString("F2");

            switch (ViewModel.GaugeIndex) // ゲージ画像を切り替える。(2025.9.23yori)
            {
                case 0:
                    // VAC26は使用していないため、表示しない。(2025.9.24yori)
                    break;
                case 1:
                    ViewModel.ImageSource = "Image/VAC39.png";
                    break;
                case 2:
                    ViewModel.ImageSource = "Image/VAC46.png";
                    break;
                default:
                    break;
            }
        }
    }
}