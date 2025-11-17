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

namespace VecApp
{
    /// <summary>
    /// ContactPropertyPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class ContactPropertyPanel : PanelBase
    {
        public ContactPropertyPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.ContactProperty)
        {
            InitializeComponent();
            this.DataContext = model;
        }
        private ContactPropertyViewModel ViewModel
        {
            get => this.DataContext as ContactPropertyViewModel;
        }

        private void Click_NetworkBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_ProbeBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_ArmTypeBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_InspectionBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.ProbeInput;
        }
        private void Click_CalibrationgBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.ContactInspection;
        }
        private void Click_ProbeRegistrationBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CloseBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.None; // 追加(2025.11.14yori)
        }
        private void Click_ContactBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_SelfJudgmentBtn(object sender, RoutedEventArgs e)
        {

        }
    }
}
