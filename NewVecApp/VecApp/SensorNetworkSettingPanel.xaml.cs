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
    /// SensorNetworkSettingPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class SensorNetworkSettingPanel : PanelBase
    {
        public SensorNetworkSettingPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.SensorNetworkSetting)
        {
            InitializeComponent();
            // 以降、ViewModel対応による追加
            this.DataContext = model;

            // iniファイルから取得した値をTextBoxへ入力(2025.8.27yori)
            Status02 sts = new Status02();
            CSH.AppMain.UpDateData02(out sts);
            ViewModel.IPAdress1 = int.Parse(sts.address1);
            ViewModel.IPAdress2 = int.Parse(sts.address2);
            ViewModel.IPAdress3 = int.Parse(sts.address3);
            ViewModel.IPAdress4 = int.Parse(sts.address4);
            ViewModel.SubnetMask1 = int.Parse(sts.subnet1);
            ViewModel.SubnetMask2 = int.Parse(sts.subnet2);
            ViewModel.SubnetMask3 = int.Parse(sts.subnet3);
            ViewModel.SubnetMask4 = int.Parse(sts.subnet4);
            ViewModel.DefaultGateway1 = int.Parse(sts.gateway1);
            ViewModel.DefaultGateway2 = int.Parse(sts.gateway2);
            ViewModel.DefaultGateway3 = int.Parse(sts.gateway3);
            ViewModel.DefaultGateway4 = int.Parse(sts.gateway4);
        }

        private SensorNetworkSettingViewModel ViewModel
        {
            get => this.DataContext as SensorNetworkSettingViewModel;
        }

        private void Click_InitialSettingBtn(object sender, RoutedEventArgs e)
        {
            // 初期設定ボタンをクリックした場合の値をTextBoxへ入力(2025.8.17yori)
            ViewModel.IPAdress1 = 192;
            ViewModel.IPAdress2 = 168;
            ViewModel.IPAdress3 = 10;
            ViewModel.IPAdress4 = 200;
            ViewModel.SubnetMask1 = 255;
            ViewModel.SubnetMask2 = 255;
            ViewModel.SubnetMask3 = 255;
            ViewModel.SubnetMask4 = 0;
            ViewModel.DefaultGateway1 = 192;
            ViewModel.DefaultGateway2 = 168;
            ViewModel.DefaultGateway3 = 10;
            ViewModel.DefaultGateway4 = 1;
        }

        private void Click_DoneBtn(object sender, RoutedEventArgs e)
        {
            // スキャナネットワーク設定画面からネットワーク情報を取得し、スキャナへ送る。(2025.8.17yori)
            Status02 sts = new Status02();
            sts.address1 = ViewModel.IPAdress1.ToString();
            sts.address2 = ViewModel.IPAdress2.ToString();
            sts.address3 = ViewModel.IPAdress3.ToString();
            sts.address4 = ViewModel.IPAdress4.ToString();
            sts.subnet1 = ViewModel.SubnetMask1.ToString();
            sts.subnet2 = ViewModel.SubnetMask2.ToString();
            sts.subnet3 = ViewModel.SubnetMask3.ToString();
            sts.subnet4 = ViewModel.SubnetMask4.ToString();
            sts.gateway1 = ViewModel.DefaultGateway1.ToString();
            sts.gateway2 = ViewModel.DefaultGateway2.ToString();
            sts.gateway3 = ViewModel.DefaultGateway3.ToString();
            sts.gateway4 = ViewModel.DefaultGateway4.ToString();
            CSH.AppMain.UpDateData02_Write(in sts);
            CSH.Grp03.Cmd17(); // 追加(2025.8.27yori)
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
