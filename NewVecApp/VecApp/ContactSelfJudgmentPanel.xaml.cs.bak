using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
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
    /// ContactSelfJudgmentPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class ContactSelfJudgmentPanel : PanelBase
    {
        public ContactSelfJudgmentPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.ContactSelfJudgment)
        {
            InitializeComponent();
            this.DataContext = model;
        }


        private void Click_ParamSaveBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_ParamRestoreBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_SaveBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CloseBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_SwitchBtn(object sender, RoutedEventArgs e)
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
        private void Click_FirmwareVerBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CommunicationCheckBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CounterVerBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CountCheck1Btn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CountCheck2Btn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_ZXScaleAxisBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_TemperatureSensorBtn(object sender, RoutedEventArgs e)
        {

        }

        private ContactSelfJudgmentViewModel ViewModel
        {
            get => this.DataContext as ContactSelfJudgmentViewModel;
        }
    }
}
