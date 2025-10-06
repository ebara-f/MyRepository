using System;
using System.Collections.Generic;
using System.ComponentModel; // 追加(2025.7.28yori)
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
    /// _0AxisInitializePanel.xaml の相互作用ロジック
    /// </summary>
    public partial class _0AxisInitializePanel : PanelBase // UserControl→PanelBaseへ変更(2025.7.28yori)
    {
        public _0AxisInitializePanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel._0AxisInitialize)
        {
            InitializeComponent();
            this.DataContext = model; // 追加(2025.10.2yori)
        }

        private void Click_CancelBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp01.Cmd11();  // イニシャライズをキャンセルする場合は、有接触モードへ切り替える。(2025.7.25yori)
            Parent.CurrentPanel = Panel.None; // Content = null;から変更(2025.8.12yori)
        }
    }
}
