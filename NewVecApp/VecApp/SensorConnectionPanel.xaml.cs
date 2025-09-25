using System;
using System.Collections.Generic;
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
using System.ComponentModel;

namespace VecApp
{
    /// <summary>
    /// SensorConnectionPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class SensorConnectionPanel : PanelBase
    {
        public SensorConnectionPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.SensorConnection)
        {
            InitializeComponent();
            this.DataContext = model; // 追加(2025.8.12)
            SlideSwitch.Value = 1; // 初期値はオン(2025.7.30yori)
        }

        private void Click_ConnectDoneBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp01.Cmd07();  // 有接触から非接触へ切り替える(2025.7.29yori)
        }

        private void SlideSwitch_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (SlideSwitch.Value == 1)
            {
                SlideStatusText.Text = "オン";
                CSH.Grp01.Cmd12();  // 暖機監視オン(2025.7.30yori)
            }
            else
            {
                SlideStatusText.Text = "オフ";
                CSH.Grp01.Cmd13();  // 暖機監視オフ(2025.7.30yori)
            }
        }

        // キャンセルボタンをクリックした場合(2025.7.30)
        private void Click_ConnectCancelBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.None; // Content = null;から変更(2025.8.12yori)
        }
    }
}
