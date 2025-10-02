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
using System.Windows.Media.Media3D;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace VecApp
{
    /// <summary>
    /// NonContactSelfJudgmentPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class NonContactSelfJudgmentPanel : PanelBase
    {
        public NonContactSelfJudgmentPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.NonContactSelfJudgment)
        {
            InitializeComponent();
            this.DataContext = model;
        }

        private NonContactSelfJudgmentViewModel ViewModel
        {
            get => this.DataContext as NonContactSelfJudgmentViewModel;
        }

        private void Click_HistoryBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_AllLightsOnBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_AllLightsOffBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_StopBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_SaveBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CloseBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.None; // 追加(2025.9.26yori)
        }

        private void Click_SensitivityBtn(object sender, RoutedEventArgs e)
        {
            //確認用(画像とテキストボックスの切り替え)
            if (this.ViewModel.ImageVisibility == Visibility.Visible)
            {
                this.ViewModel.ImageVisibility = Visibility.Hidden;
                this.ViewModel.GridVisibility = Visibility.Visible;
            }
            else
            {
                this.ViewModel.ImageVisibility = Visibility.Visible;
                this.ViewModel.GridVisibility = Visibility.Hidden;
            }
        }
        private void Click_SensorBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_LatchBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_PointerBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_MotorBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_LEDBtn(object sender, RoutedEventArgs e)
        {

        }
    }
}
