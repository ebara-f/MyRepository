using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using CSH;

namespace VecApp
{
    /// <summary>
    /// ThresholdSettingPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class ThresholdSettingPanel : PanelBase
    {
        private DlgPass m_DlgPass = null; // 追加(2025.8.6yori)

        public ThresholdSettingPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.ThresholdSetting)
        {
            InitializeComponent();
            this.DataContext = model;

            // しきい値設定の初期値表示(2025.8.6yori)
            Threshold th = new Threshold();
            ViewModel.ProbeCheckIdIndex = 2;
            CSH.AppMain.UpDateData04(out th, ViewModel.ProbeCheckIdIndex); // 引数追加追加(2025.9.22yori)
            ViewModel.PreCheckMaxMinThreshold = th.pp.ToString("F2");
            ViewModel.PreCheckTwoSigmaThreshold = th.sigma2.ToString("F2");
            ViewModel.PreCheckDistanceThreshold = th.plate.ToString("F2");
            ViewModel.ProbeCheckMaxMinThreshold = th.pp_probe[ViewModel.ProbeCheckIdIndex].ToString("F2"); // 2→ViewModel.ProbeCheckIdIndex(2025.9.22yori)
            ViewModel.ProbeCheckTwoSigmaThreshold = th.sigma2_probe[ViewModel.ProbeCheckIdIndex].ToString("F2"); // 2→ViewModel.ProbeCheckIdIndex(2025.9.22yori)
            ViewModel.ProbeCheckDistanceThreshold = th.plate_probe[ViewModel.ProbeCheckIdIndex].ToString("F2"); // 2→ViewModel.ProbeCheckIdIndex(2025.9.22yori)
            ViewModel.ProbeCheckBallCenter = th.ri_probe[ViewModel.ProbeCheckIdIndex].ToString("F2"); // 2→ViewModel.ProbeCheckIdIndex(2025.9.22yori)
            ViewModel.ProbeCheckBallDiameter = th.ps_probe[ViewModel.ProbeCheckIdIndex].ToString("F2"); // 2→ViewModel.ProbeCheckIdIndex(2025.9.22yori)
            ViewModel.ProbeCheckId = new ObservableCollection<string> { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19" };
            ViewModel.GaugeDistanceMax = th.dst_max.ToString("F0");
            ViewModel.GaugeDistanceMin = th.dst_min.ToString("F0");
            ViewModel.GaugeHeightMax = th.height_max.ToString("F0");
            ViewModel.GaugeHeightMin = th.height_min.ToString("F0");
            ViewModel.CalibrationTolerance = th.error_max.ToString("F2");
            ViewModel.IsTextBoxEnabled = false; // キャリブレーションのテキストボックス無効(2025.8.6yori)
            ViewModel.IsTextBoxEnabled2 = true; // プローブ点検のテキストボックス無効(2025.9.22yori)
        }

        private ThresholdSettingViewModel ViewModel
        {
            get => this.DataContext as ThresholdSettingViewModel;
        }

        // 始業前点検の初期値ボタン(2025.8.1yori)
        private void Click_InitialValueBtn1(object sender, RoutedEventArgs e)
        {
            Threshold th = new Threshold();
            CSH.AppMain.UpDateData04_Default(out th, ViewModel.ProbeCheckIdIndex); // 引数追加(2025.9.22yori)
            ViewModel.PreCheckMaxMinThreshold = th.pp.ToString("F2");
            ViewModel.PreCheckTwoSigmaThreshold = th.sigma2.ToString("F2");
            ViewModel.PreCheckDistanceThreshold = th.plate.ToString("F2");
        }

        // プローブ点検の初期値ボタン(2025.8.1yori)
        private void Click_InitialValueBtn2(object sender, RoutedEventArgs e)
        {
            Threshold th = new Threshold();
            CSH.AppMain.UpDateData04_Default(out th, ViewModel.ProbeCheckIdIndex); // 引数追加(2025.9.22yori)
            ViewModel.ProbeCheckMaxMinThreshold = th.pp_probe[ViewModel.ProbeCheckIdIndex].ToString("F2");
            ViewModel.ProbeCheckTwoSigmaThreshold = th.sigma2_probe[ViewModel.ProbeCheckIdIndex].ToString("F2");
            ViewModel.ProbeCheckDistanceThreshold = th.plate_probe[ViewModel.ProbeCheckIdIndex].ToString("F2");
            ViewModel.ProbeCheckBallCenter = th.ri_probe[ViewModel.ProbeCheckIdIndex].ToString("F2");
            ViewModel.ProbeCheckBallDiameter = th.ps_probe[ViewModel.ProbeCheckIdIndex].ToString("F2");
        }

        private void Click_PasswordBtn(object sender, RoutedEventArgs e)
        {
            // パスワード入力ダイアログ表示(2025.8.6yori)
            m_DlgPass = new DlgPass();
            if (m_DlgPass.IsVisible == false)
            {
                m_DlgPass.Owner = Application.Current.MainWindow;
                m_DlgPass.WindowStartupLocation = WindowStartupLocation.CenterOwner;

                // モーダルダイアログとして表示
                if(m_DlgPass.ShowDialog() == true)
                {
                    ViewModel.IsTextBoxEnabled = true;
                }

                // Window のアクティブ化
                UIPlus.ForceActive(m_DlgPass.m_hWnd);
            }
        }
        private void Click_DoneBtn(object sender, RoutedEventArgs e)
        {
            // しきい値設定画面からしきい値情報を取得し、iniファイルへ送る。(2025.8.1yori)
            Threshold th = new Threshold();
            th.pp_probe = new double[20];
            th.sigma2_probe = new double[20];
            th.plate_probe = new double[20];
            th.ri_probe = new double[20];
            th.ps_probe = new double[20];
            // 始業前点検
            th.pp = double.Parse(ViewModel.PreCheckMaxMinThreshold);
            th.sigma2 = double.Parse(ViewModel.PreCheckTwoSigmaThreshold);
            th.plate = double.Parse(ViewModel.PreCheckDistanceThreshold);
            // プローブ点検(2025.9.8yori)
            // 選択されたIDのみ、しきい値変更(2025.9.22yori)
            th.pp_probe[ViewModel.ProbeCheckIdIndex] = double.Parse(ViewModel.ProbeCheckMaxMinThreshold);
            th.sigma2_probe[ViewModel.ProbeCheckIdIndex] = double.Parse(ViewModel.ProbeCheckTwoSigmaThreshold);
            th.plate_probe[ViewModel.ProbeCheckIdIndex] = double.Parse(ViewModel.ProbeCheckDistanceThreshold);
            th.ri_probe[ViewModel.ProbeCheckIdIndex] = double.Parse(ViewModel.ProbeCheckBallCenter);
            th.ps_probe[ViewModel.ProbeCheckIdIndex] = double.Parse(ViewModel.ProbeCheckBallDiameter);
            // キャリブレーション
            th.dst_max = double.Parse(ViewModel.GaugeDistanceMax);
            th.dst_min = double.Parse(ViewModel.GaugeDistanceMin);
            th.height_max = double.Parse(ViewModel.GaugeHeightMax);
            th.height_min = double.Parse(ViewModel.GaugeHeightMin);
            th.error_max = double.Parse(ViewModel.CalibrationTolerance);

            CSH.AppMain.UpDateData04_Write(in th, ViewModel.ProbeCheckIdIndex); // 引数追加(2025.9.22yori)
            Parent.CurrentPanel = Panel.Inspection; // 追加(2025.7.31yori)
        }

        private void Click_CancelBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.Inspection;
        }

        // 追加(2025.8.1yori)
        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Threshold th = new Threshold();
            CSH.AppMain.UpDateData04(out th, ViewModel.ProbeCheckIdIndex); // 引数追加追加(2025.9.22yori)
            ViewModel.ProbeCheckMaxMinThreshold = th.pp_probe[ViewModel.ProbeCheckIdIndex].ToString("F2");
            ViewModel.ProbeCheckTwoSigmaThreshold = th.sigma2_probe[ViewModel.ProbeCheckIdIndex].ToString("F2");
            ViewModel.ProbeCheckDistanceThreshold = th.plate_probe[ViewModel.ProbeCheckIdIndex].ToString("F2");
            ViewModel.ProbeCheckBallCenter = th.ri_probe[ViewModel.ProbeCheckIdIndex].ToString("F2");
            ViewModel.ProbeCheckBallDiameter = th.ps_probe[ViewModel.ProbeCheckIdIndex].ToString("F2");

            if (ViewModel.ProbeCheckIdIndex == 0) // ID=0(スキャナ)の場合は、プローブ点検が無いため、無効化(2025.9.22yori)
            {
                ViewModel.IsTextBoxEnabled2 = false;
            }
            else
            {  
                ViewModel.IsTextBoxEnabled2 = true;
            }
        }
    }
}
