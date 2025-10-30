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
    /// SettingPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class SettingPanel : PanelBase
    {
        public SettingPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.Setting)
        {
            InitializeComponent();
            this.DataContext = model;

            CSH.Grp02.SettingPanelInit(ref this.ViewModel.CalibMseBox);
            this.ViewModel.BallStylusDiameter = this.ViewModel.CalibMseBox.GaugePara.StylusDia.ToString("F3");
            this.ViewModel.Distance = this.ViewModel.CalibMseBox.GaugePara.PlateLen.ToString("F3"); ;
            this.ViewModel.BallGaugeDiameter = this.ViewModel.CalibMseBox.GaugePara.BallDia.ToString("F3");
            this.ViewModel.BallDiameter = this.ViewModel.CalibMseBox.GaugePara.ErrMax.ToString("F3"); ;
        }

        private SettingViewModel ViewModel
        {
            get => this.DataContext as SettingViewModel;
        }

        private void Click_DoneBtn(object sender, RoutedEventArgs e)
        {
            this.ViewModel.CalibMseBox.GaugePara.StylusDia = Convert.ToDouble(this.ViewModel.BallStylusDiameter);
            this.ViewModel.CalibMseBox.GaugePara.PlateLen = Convert.ToDouble(this.ViewModel.Distance);
            this.ViewModel.CalibMseBox.GaugePara.BallDia = Convert.ToDouble(this.ViewModel.BallGaugeDiameter);
            this.ViewModel.CalibMseBox.GaugePara.ErrMax = Convert.ToDouble(this.ViewModel.BallDiameter);

            CSH.Grp02.SettingPanelOkBtn(ref this.ViewModel.CalibMseBox);

            Parent.CurrentPanel = Panel.ContactInspection;
        }
        private void Click_CancelBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.SettingPanelCancelBtn(ref this.ViewModel.CalibMseBox);
            Parent.CurrentPanel = Panel.ContactInspection;
        }
    }
}
