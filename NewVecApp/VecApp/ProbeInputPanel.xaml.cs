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
            if (sts.probe_id == 0) this.ViewModel.Name = sts.pobe_name0;
            if (sts.probe_id == 1) this.ViewModel.Name = sts.pobe_name1;
            if (sts.probe_id == 2) this.ViewModel.Name = sts.pobe_name2;
            if (sts.probe_id == 3) this.ViewModel.Name = sts.pobe_name3;
            if (sts.probe_id == 4) this.ViewModel.Name = sts.pobe_name4;
            if (sts.probe_id == 5) this.ViewModel.Name = sts.pobe_name5;
            if (sts.probe_id == 6) this.ViewModel.Name = sts.pobe_name6;
            if (sts.probe_id == 7) this.ViewModel.Name = sts.pobe_name7;
            if (sts.probe_id == 8) this.ViewModel.Name = sts.pobe_name8;
            if (sts.probe_id == 9) this.ViewModel.Name = sts.pobe_name9;
            if (sts.probe_id == 10) this.ViewModel.Name = sts.pobe_name10;
            if (sts.probe_id == 11) this.ViewModel.Name = sts.pobe_name11;
            if (sts.probe_id == 12) this.ViewModel.Name = sts.pobe_name12;
            if (sts.probe_id == 13) this.ViewModel.Name = sts.pobe_name13;
            if (sts.probe_id == 14) this.ViewModel.Name = sts.pobe_name14;
            if (sts.probe_id == 15) this.ViewModel.Name = sts.pobe_name15;
            if (sts.probe_id == 16) this.ViewModel.Name = sts.pobe_name16;
            if (sts.probe_id == 17) this.ViewModel.Name = sts.pobe_name17;
            if (sts.probe_id == 18) this.ViewModel.Name = sts.pobe_name18;
            if (sts.probe_id == 19) this.ViewModel.Name = sts.pobe_name19;
            if (sts.probe_id == 20) this.ViewModel.Name = sts.pobe_name20;
            this.ViewModel.Id = sts.probe_id.ToString();
            this.ViewModel.ProbeAngle = sts.stylus_angle[sts.probe_id].ToString("F2");
            this.ViewModel.BallDiameter = sts.dia.ToString("F2");
            ////
            //// プローブ種類画像追加(2025.10.31yori)
            switch (sts.pobe_type[sts.probe_id])
            {
                case 0:
                    this.ViewModel.ImageSource = "Image/taperProbeV7.PNG";
                    break;
                case 1:
                    this.ViewModel.ImageSource = "Image/standardProbeV7.PNG";
                    break;
                case 2:
                    this.ViewModel.ImageSource = "Image/VPR81.PNG";
                    break;
                case 3:
                    this.ViewModel.ImageSource = "Image/VPR103.PNG";
                    break;
                case 4:
                    this.ViewModel.ImageSource = "Image/VPR105.PNG";
                    break;
                default:
                    break;
            }
            this.ViewModel.BallIndex = sts.pobe_type[sts.probe_id];
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
            CSH.Grp02.ArmSetCancel(); // C++へキャンセルボタンが押されたことを通知(2026.2.6yori)
            Parent.CurrentPanel = Panel.None; // プローブ登録画面非表示(2025.10.24yori)
        }

        // 追加(2025.10.27yori)
        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            switch (this.ViewModel.BallIndex)
            {
                case 0:
                    this.ViewModel.ImageSource = "Image/taperProbeV7.PNG";
                    break;
                case 1:
                    this.ViewModel.ImageSource = "Image/standardProbeV7.PNG";
                    break;
                case 2:
                    this.ViewModel.ImageSource = "Image/VPR81.PNG";
                    break;
                case 3:
                    this.ViewModel.ImageSource = "Image/VPR103.PNG";
                    break;
                case 4:
                    this.ViewModel.ImageSource = "Image/VPR105.PNG";
                    break;
                default:
                    break;
            }
        }

        // プローブ登録ボタン(2025.10.31yori)
        private void Click_ResistBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.ProbeInputPanelProbeResist(int.Parse(this.ViewModel.Id), this.ViewModel.Name, this.ViewModel.BallIndex);
            Parent.CurrentPanel = Panel.None;
        }
    }
}