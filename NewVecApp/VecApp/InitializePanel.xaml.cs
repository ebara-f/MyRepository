using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
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
using static System.Net.Mime.MediaTypeNames;

namespace VecApp
{
    /// <summary>
    /// InitializePanel.xaml の相互作用ロジック
    /// </summary>
    public partial class InitializePanel : PanelBase // UserControl→PanelBaseへ変更(2025.7.28yori)
    {
        public InitializePanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.Initialize)
        {
            InitializeComponent();
            this.DataContext = model;

            // 機種による関節No位置を場合分け(2025.10.24yori)
            Status01 sts = new Status01();
            CSH.AppMain.UpDateData01(out sts);
            if (sts.arm_model == "VAR800M" || sts.arm_model == "VAR800L")
            {
                this.ViewModel.Marks = new ObservableCollection<InitializeMarkViewModel>
                {
                    new InitializeMarkViewModel { Text = "⓪", Visibility = Visibility.Hidden, X = 470, Y = 200 },
                    new InitializeMarkViewModel { Text = "①", Visibility = Visibility.Hidden, X = 450, Y = 160 },
                    new InitializeMarkViewModel { Text = "②", Visibility = Visibility.Hidden, X = 395, Y = 30 },
                    new InitializeMarkViewModel { Text = "③", Visibility = Visibility.Hidden, X = 310, Y = 0 },
                    new InitializeMarkViewModel { Text = "④", Visibility = Visibility.Hidden, X = 330, Y = 100 },
                    new InitializeMarkViewModel { Text = "⑤", Visibility = Visibility.Hidden, X = 230, Y = 140 },
                    new InitializeMarkViewModel { Text = "⑥", Visibility = Visibility.Hidden, X = 340, Y = 160 },
                };
            }
            if (sts.arm_model == "VAR700M" || sts.arm_model == "VAR700L")
            {
                this.ViewModel.Marks = new ObservableCollection<InitializeMarkViewModel>
                {
                    new InitializeMarkViewModel { Text = "⓪", Visibility = Visibility.Hidden, X = 380, Y = 190 },
                    new InitializeMarkViewModel { Text = "①", Visibility = Visibility.Hidden, X = 440, Y = 150 },
                    new InitializeMarkViewModel { Text = "②", Visibility = Visibility.Hidden, X = 400, Y = 20 },
                    new InitializeMarkViewModel { Text = "③", Visibility = Visibility.Hidden, X = 315, Y = 0 },
                    new InitializeMarkViewModel { Text = "④", Visibility = Visibility.Hidden, X = 290, Y = 80 },
                    new InitializeMarkViewModel { Text = "⑤", Visibility = Visibility.Hidden, X = 355, Y = 120 },
                    new InitializeMarkViewModel { Text = "⑥", Visibility = Visibility.Hidden, X = 250, Y = 140 },
                };
            }
        }

        private InitializeViewModel ViewModel
        {
            get => this.DataContext as InitializeViewModel;
        }

        private void SlideSwitch_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (this.ViewModel.SlideSwitch)
            {
                this.ViewModel.SlideSwitch = true;
                CSH.Grp01.Cmd09();  // 暖機監視オン(2025.7.16yori)
            }
            else
            {
                this.ViewModel.SlideSwitch = false;
                CSH.Grp01.Cmd10();  // 暖機監視オフ(2025.7.16yori)
            }
        }

        private void Click_CancelBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp01.Cmd08();  // イニシャライズをキャンセルする場合は、有接触モードへ切り替える。(2025.7.16yori)
            Parent.CurrentPanel = Panel.None; // Content = null;から変更(2025.8.12yori)

            // 下記の例は削除する予定(2025.7.16yori)
            /*
             * DEBUG: This code is example.
             */
            //for (var i = 0; i < this.ViewModel.Marks.Count; ++i)
            //{
            //    if (this.ViewModel.Marks[i].Visibility == Visibility.Visible)
            //    {
            //        this.ViewModel.Marks[i].Visibility = Visibility.Hidden;
            //        this.ViewModel.Labels[i].Visibility = Visibility.Hidden;
            //        break;
            //    }
            //}
            /*
             * DEBUG: This code is example.
             */
            var close = true;
            for (var i = 0; i < this.ViewModel.Marks.Count; ++i)
            {
                if (this.ViewModel.Marks[i].Visibility == Visibility.Visible)
                {
                    this.ViewModel.Marks[i].Visibility = Visibility.Hidden;
                    this.ViewModel.Labels[i].Visibility = Visibility.Hidden;
                    close = false;
                    break;
                }
            }
            if (close)
            {
                for (var i = 0; i < this.ViewModel.Marks.Count; ++i)
                {
                    this.ViewModel.Marks[i].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[i].Visibility = Visibility.Visible;
                }
                this.Parent.CurrentPanel = Panel.None;
            }
        }
    }
}
