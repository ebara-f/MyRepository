using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Security.Cryptography;
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
    /// ProbeSettingPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class ProbeSettingPanel : PanelBase // UserControl→PanelBaseへ変更(2025.7.28yori)
    {
        public ProbeSettingPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.ProbeSetting)
        {
            InitializeComponent();

            this.DataContext = model;

            // MainWindow.xaml.csから移動(2025.9.1yori)
            Status01 sts = new Status01();
            CSH.AppMain.UpDateData01(out sts);
            ViewModel.Name.Clear();
            ViewModel.Name.Insert(0, sts.pobe_name0);
            ViewModel.Name.Insert(1, sts.pobe_name1);
            ViewModel.Name.Insert(2, sts.pobe_name2);
            ViewModel.Name.Insert(3, sts.pobe_name3);
            ViewModel.Name.Insert(4, sts.pobe_name4);
            ViewModel.Name.Insert(5, sts.pobe_name5);
            ViewModel.Name.Insert(6, sts.pobe_name6);
            ViewModel.Name.Insert(7, sts.pobe_name7);
            ViewModel.Name.Insert(8, sts.pobe_name8);
            ViewModel.Name.Insert(9, sts.pobe_name9);
            ViewModel.Name.Insert(10, sts.pobe_name10);
            ViewModel.Name.Insert(11, sts.pobe_name11);
            ViewModel.Name.Insert(12, sts.pobe_name12);
            ViewModel.Name.Insert(13, sts.pobe_name13);
            ViewModel.Name.Insert(14, sts.pobe_name14);
            ViewModel.Name.Insert(15, sts.pobe_name15);
            ViewModel.Name.Insert(16, sts.pobe_name16);
            ViewModel.Name.Insert(17, sts.pobe_name17);
            ViewModel.Name.Insert(18, sts.pobe_name18); 
            ViewModel.Name.Insert(19, sts.pobe_name19);
            ViewModel.Name.Insert(20, sts.pobe_name20);
            ViewModel.NameIndex = sts.probe_id;
            if(sts.arm_model == "VAR800M" || sts.arm_model == "VAR800L") ProbeName.IsEnabled = false; // V8の場合、ComboBoxを選択できないよう無効化する。(2025.9.8yori)
            ViewModel.Id = sts.probe_id.ToString();
            ViewModel.Diameter = sts.dia.ToString("F2");
        }

        private ProbeSettingViewModel ViewModel
        {
            get => this.DataContext as ProbeSettingViewModel;
        }

        private void Click_DoneBtn(object sender, RoutedEventArgs e)
        {
            // プローブ設定画面からプローブ情報を取得し、アームへ送る。(2025.7.18yori)
            // CSH.Grp02.Cmd07関数に引数追加(2025.9.8yori)
            // スタイラスなしの場合は、直径=0mmに設定する。(2025.9.8yori)
            if (ViewModel.BallIndex == 0)
            {
                CSH.Grp02.Cmd07(int.Parse(ViewModel.Id), 0);
            }
            else
            {
                CSH.Grp02.Cmd07(int.Parse(ViewModel.Id), double.Parse(ViewModel.Diameter));
            }
            Parent.CurrentPanel = Panel.None; // プローブ設定画面非表示(2025.7.17yori) // Content = null;から変更(2025.8.16yori)

            // 下記の例は削除する予定(2025.7.17yori)
            /*
             * DEBUG: This code is example.
             */
            //ViewModel.BallIndex = ViewModel.BallIndex == 1 ? 0 : 1;
        }

        private void Click_CancelBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.None; // プローブ設定画面非表示(2025.7.17yori) // Content = null;から変更(2025.8.16yori)

            // 下記の例は削除する予定(2025.7.17yori)
            /*
             * DEBUG: This code is example.
             */
            //var diameter = double.Parse(ViewModel.Diameter) + 0.01;
            //ViewModel.Diameter = diameter.ToString("F2");
        }

        // 追加(2025.7.17yori)
        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            switch (ViewModel.BallIndex)
            { 
                case 0:
                    ViewModel.BallImage = "Image/VST28-0.1.PNG";
                    Dia.IsEnabled = false; // スタイラスなしの場合、ComboBoxを選択できないよう無効化する。(2025.9.8yori)
                    ViewModel.Diameter = "0.00"; // スタイラスなしの場合、直径=0.00mmと表示する。(2025.9.8yori)
                    break;
                case 1:
                    ViewModel.BallImage = "Image/BallProbe.PNG";
                    Dia.IsEnabled = true; // スタイラスありの場合、ComboBoxを選択できるよう有効化する。(2025.9.8yori)
                    break;
                default:
                    break;
            }
        }
    }
}
