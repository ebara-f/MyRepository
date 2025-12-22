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
using CSH;

namespace VecApp
{
    /// <summary>
    /// ArmNetworkSettingPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class ArmNetworkSettingPanel : PanelBase
    {
        public ArmNetworkSettingPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.ArmNetworkSetting)
        {
            InitializeComponent();
            // 以降、ViewModel対応による追加
            this.DataContext = model;

            // MainWindow.xaml.csから移動(2025.8.27yori)
            Status01 sts = new Status01();
            CSH.AppMain.UpDateData01(out sts);
            ViewModel.IPAdress1 = int.Parse(sts.address1);
            ViewModel.IPAdress2 = int.Parse(sts.address2);
            ViewModel.IPAdress3 = int.Parse(sts.address3);
            ViewModel.IPAdress4 = int.Parse(sts.address4);
            ViewModel.SubnetMask1 = int.Parse(sts.subnet1);
            ViewModel.SubnetMask2 = int.Parse(sts.subnet2);
            ViewModel.SubnetMask3 = int.Parse(sts.subnet3);
            ViewModel.SubnetMask4 = int.Parse(sts.subnet4);
            ViewModel.PortNumber = int.Parse(sts.port);
        }

        private ArmNetworkSettingViewModel ViewModel
        {
            get => this.DataContext as ArmNetworkSettingViewModel;
        }

        private void Click_InitialSettingBtn(object sender, RoutedEventArgs e)
        {
            // 初期設定ボタンをクリックした場合の値をTextBoxへ入力(2025.8.16yori)
            ViewModel.IPAdress1 = 192;
            ViewModel.IPAdress2 = 168;
            ViewModel.IPAdress3 = 10;
            ViewModel.IPAdress4 = 10;
            ViewModel.SubnetMask1 = 255;
            ViewModel.SubnetMask2 = 255;
            ViewModel.SubnetMask3 = 255;
            ViewModel.SubnetMask4 = 0;
            ViewModel.PortNumber = 23;
        }

        private void Click_DoneBtn(object sender, RoutedEventArgs e)
        {
            // アームネットワーク設定画面からネットワーク情報を取得し、アームへ送る。(2025.8.16yori)
            Status01 sts = new Status01();
            sts.address1 = ViewModel.IPAdress1.ToString();
            sts.address2 = ViewModel.IPAdress2.ToString();
            sts.address3 = ViewModel.IPAdress3.ToString();
            sts.address4 = ViewModel.IPAdress4.ToString();
            sts.subnet1 = ViewModel.SubnetMask1.ToString();
            sts.subnet2 = ViewModel.SubnetMask2.ToString();
            sts.subnet3 = ViewModel.SubnetMask3.ToString();
            sts.subnet4 = ViewModel.SubnetMask4.ToString();
            sts.port = ViewModel.PortNumber.ToString();
            CSH.AppMain.UpDateData01_Write(in sts);
            CSH.Grp02.Cmd09();
            // メッセージボックスを表示する。(2025.8.28yori)
            // 多言語対応による変更(2025.12.22yori)
            MessageBox.Show(VecApp.Properties.Resources.String69, "Beak Master Plug-in SoftWare(beta)", MessageBoxButton.OK, MessageBoxImage.Information);
            Parent.CurrentPanel = Panel.None;
        }

        private void Click_CancelBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.None; // 追加(2025.8.16yori)
        }
    }
}
