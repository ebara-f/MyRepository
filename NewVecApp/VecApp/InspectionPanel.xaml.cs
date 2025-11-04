using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
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
using System.IO; // 追加(2025.9.24yori)

namespace VecApp
{
    /// <summary>
    /// InspectionPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class InspectionPanel : PanelBase
    {
        public InspectionPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.Inspection)
        {
            InitializeComponent();
            this.DataContext = model;

            // MainWindow.xaml.csから移動(2025.9.24yori)
            Status01 sts = new Status01();
            CSH.AppMain.UpDateData01(out sts);
            ViewModel.ProbeName.Clear();
            ViewModel.ProbeName.Insert(0, sts.pobe_name0);
            ViewModel.ProbeName.Insert(1, sts.pobe_name1);
            ViewModel.ProbeName.Insert(2, sts.pobe_name2);
            ViewModel.ProbeName.Insert(3, sts.pobe_name3);
            ViewModel.ProbeName.Insert(4, sts.pobe_name4);
            ViewModel.ProbeName.Insert(5, sts.pobe_name5);
            ViewModel.ProbeName.Insert(6, sts.pobe_name6);
            ViewModel.ProbeName.Insert(7, sts.pobe_name7);
            ViewModel.ProbeName.Insert(8, sts.pobe_name8);
            ViewModel.ProbeName.Insert(9, sts.pobe_name9);
            ViewModel.ProbeName.Insert(10, sts.pobe_name10);
            ViewModel.ProbeName.Insert(11, sts.pobe_name11);
            ViewModel.ProbeName.Insert(12, sts.pobe_name12);
            ViewModel.ProbeName.Insert(13, sts.pobe_name13);
            ViewModel.ProbeName.Insert(14, sts.pobe_name14);
            ViewModel.ProbeName.Insert(15, sts.pobe_name15);
            ViewModel.ProbeName.Insert(16, sts.pobe_name16);
            ViewModel.ProbeName.Insert(17, sts.pobe_name17);
            ViewModel.ProbeName.Insert(18, sts.pobe_name18);
            ViewModel.ProbeName.Insert(19, sts.pobe_name19);
            ViewModel.ProbeName.Insert(20, sts.pobe_name20);
            ViewModel.ProbeNameIndex = sts.probe_id;
            if (sts.arm_model == "VAR800M" || sts.arm_model == "VAR800L") ProbeName.IsEnabled = false; // V8の場合、ComboBoxを選択できないよう無効化する。
            ViewModel.ProbeId = sts.probe_id.ToString();
            ViewModel.ProbeAngle = sts.stylus_angle[sts.probe_id].ToString("F2");
            ViewModel.ProbeBallDiameter = sts.dia.ToString("F2");
        }

        private InspectionViewModel ViewModel
        {
            get => this.DataContext as InspectionViewModel;
        }

        private void Click_MultiGaugeBtn01(object sender, RoutedEventArgs e)
        {
            (Parent as SubWindow2).ContactInspectionValue.CalibMseBox.CalibProbeId = 2;// 2025.10.20. test add eba
            (Parent as SubWindow2).ContactInspectionValue.CalibMseBox.CalibProbeBranch = 0;// 2025.10.20. test add eba
            (Parent as SubWindow2).ContactInspectionValue.CalibMseBox.CalibType = 5; // 2025.10.6. test add eba
            Parent.CurrentPanel = Panel.ContactInspection; // 追加(2025.7.31yori)
        }

        private void Click_MultiGaugeBtn02(object sender, RoutedEventArgs e)
        {
            //(Parent as SubWindow2).ContactInspectionValue.CalibMseBox.CalibType = 1; // 2025.8.27. add eba
            (Parent as SubWindow2).ContactInspectionValue.CalibMseBox.CalibType = 4; // 2025.8.27. add eba
            Parent.CurrentPanel = Panel.ContactInspection; // 追加(2025.7.31yori)
        }

        private void Click_MultiGaugeBtn03(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.ContactInspection; // 追加(2025.7.31yori)
        }

        private void Click_BallBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.ContactInspection; // 追加(2025.7.31yori)
        }

        private void Click_ThresholdSettingBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.ThresholdSetting;
        }

        private void Click_GaugeSettingBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.GaugeSetting;
        }

        private void Click_HelpBtn(object sender, RoutedEventArgs e)
        {
            // ヘルプボタンで取扱説明書のPDFを開く(2025.9.24yori)
            string pdfFilePath = "C:\\ProgramData\\Kosakalab\\Kosaka CMM\\doc\\RM-1401-06-JP.pdf"; // ここに実際のファイルパスを入力

            if (File.Exists(pdfFilePath))
            {
                Process.Start(new ProcessStartInfo(pdfFilePath) { UseShellExecute = true });// PDFファイルを開く
            }
            else
            {
                MessageBox.Show("指定されたPDFファイルが見つかりません。", "ファイルが見つかりません", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void Click_CloseBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.None; // 追加(2025.7.31yori)
        }
    }
}
