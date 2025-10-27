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
    /// ProbeInputPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class ProbeInputPanel : PanelBase
    {
        public ProbeInputPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.ProbeInput)
        {
            InitializeComponent();
            this.DataContext = model;
            //// 追加(2025.10.24yori)
            Status01 sts = new Status01();
            CSH.AppMain.UpDateData01(out sts);
            if (sts.probe_id == 0) ViewModel.Name = sts.pobe_name0;
            if (sts.probe_id == 1) ViewModel.Name = sts.pobe_name1;
            if (sts.probe_id == 2) ViewModel.Name = sts.pobe_name2;
            if (sts.probe_id == 3) ViewModel.Name = sts.pobe_name3;
            if (sts.probe_id == 4) ViewModel.Name = sts.pobe_name4;
            if (sts.probe_id == 5) ViewModel.Name = sts.pobe_name5;
            if (sts.probe_id == 6) ViewModel.Name = sts.pobe_name6;
            if (sts.probe_id == 7) ViewModel.Name = sts.pobe_name7;
            if (sts.probe_id == 8) ViewModel.Name = sts.pobe_name8;
            if (sts.probe_id == 9) ViewModel.Name = sts.pobe_name9;
            if (sts.probe_id == 10) ViewModel.Name = sts.pobe_name10;
            if (sts.probe_id == 11) ViewModel.Name = sts.pobe_name11;
            if (sts.probe_id == 12) ViewModel.Name = sts.pobe_name12;
            if (sts.probe_id == 13) ViewModel.Name = sts.pobe_name13;
            if (sts.probe_id == 14) ViewModel.Name = sts.pobe_name14;
            if (sts.probe_id == 15) ViewModel.Name = sts.pobe_name15;
            if (sts.probe_id == 16) ViewModel.Name = sts.pobe_name16;
            if (sts.probe_id == 17) ViewModel.Name = sts.pobe_name17;
            if (sts.probe_id == 18) ViewModel.Name = sts.pobe_name18;
            if (sts.probe_id == 19) ViewModel.Name = sts.pobe_name19;
            if (sts.probe_id == 20) ViewModel.Name = sts.pobe_name20;
            ViewModel.Id = sts.probe_id.ToString();
            ViewModel.ProbeAngle = sts.stylus_angle[sts.probe_id].ToString("F2");
            ViewModel.BallDiameter = sts.dia.ToString("F2");
            ////
        }

        private ProbeInputViewModel ViewModel
        {
            get => this.DataContext as ProbeInputViewModel;
        }

        private void Click_StartBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CancelBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.None; // プローブ登録画面非表示(2025.10.24yori)
        }

        // 追加(2025.10.27yori)
        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            switch (this.ViewModel.BallIndex)
            {
                case 0:
                    this.ViewModel.ImageSource = "Image/standardProbeV7.PNG";
                    break;
                case 1:
                    this.ViewModel.ImageSource = "Image/VPR81.PNG";
                    break;
                case 2:
                    this.ViewModel.ImageSource = "Image/VPR103.PNG";
                    break;
                case 3:
                    this.ViewModel.ImageSource = "Image/VPR105.PNG";
                    break;
                default:
                    break;
            }
        }
    }
}
