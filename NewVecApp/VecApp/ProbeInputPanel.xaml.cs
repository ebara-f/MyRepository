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
    /// ProbeInputPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class ProbeInputPanel : PanelBase
    {
        public ProbeInputPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.ProbeInput)
        {
            InitializeComponent();
            // 以降、ViewModel対応による追加(2025.7.29yori)
            this.DataContext = model;
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
            Parent.CurrentPanel = Panel.ContactProperty;
        }
    }
}
