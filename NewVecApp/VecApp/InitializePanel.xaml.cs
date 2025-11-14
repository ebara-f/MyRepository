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
using Application = System.Windows.Application;

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

            // イニシャライズ画面の初期設定(2025.10.27yori)
            // ここは一度だけ呼び出されるため、再イニシャライズする場合はInitPanelSetup()を呼び出す。(2025.11.12yori)
            Status01 sts = new Status01();
            CSH.AppMain.UpDateData01(out sts);
            if ((sts.arm_model == "VAR800M" || sts.arm_model == "VAR800L") && sts.no0_fg == 0) // 0軸が無い場合は、0軸無しの画像へ変更し、0番を表示しない。
            {
                this.ViewModel.ImageSource = "Image/init_machine10.PNG";

                // new InitializeMarkViewModel...から変更(2025.11.12yori)
                this.ViewModel.Marks[0].X = 430;
                this.ViewModel.Marks[0].Y = 365;
                this.ViewModel.Marks[1].X = 530;
                this.ViewModel.Marks[1].Y = 350;
                this.ViewModel.Marks[2].X = 415;
                this.ViewModel.Marks[2].Y = 70;
                this.ViewModel.Marks[3].X = 285;
                this.ViewModel.Marks[3].Y = 30;
                this.ViewModel.Marks[4].X = 190;
                this.ViewModel.Marks[4].Y = 220;
                this.ViewModel.Marks[5].X = 320;
                this.ViewModel.Marks[5].Y = 275;
                this.ViewModel.Marks[6].X = 145;
                this.ViewModel.Marks[6].Y = 320;

                this.ViewModel.ImageSource = "Image/init_machine10.PNG";
                this.ViewModel.Marks[0].Visibility = Visibility.Hidden;
                this.ViewModel.Marks[1].Visibility = Visibility.Visible;
                this.ViewModel.Marks[2].Visibility = Visibility.Visible;
                this.ViewModel.Marks[3].Visibility = Visibility.Visible;
                this.ViewModel.Marks[4].Visibility = Visibility.Visible;
                this.ViewModel.Marks[5].Visibility = Visibility.Visible;
                this.ViewModel.Marks[6].Visibility = Visibility.Visible;
                this.ViewModel.Labels[0].Visibility = Visibility.Hidden;
                this.ViewModel.Labels[1].Visibility = Visibility.Visible;
                this.ViewModel.Labels[2].Visibility = Visibility.Visible;
                this.ViewModel.Labels[3].Visibility = Visibility.Visible;
                this.ViewModel.Labels[4].Visibility = Visibility.Visible;
                this.ViewModel.Labels[5].Visibility = Visibility.Visible;
                this.ViewModel.Labels[6].Visibility = Visibility.Visible;
            }

            if ((sts.arm_model == "VAR800M" || sts.arm_model == "VAR800L") && sts.no0_fg == 1) // 0軸が有る場合は、0軸有りの画像へ変更し、0番を表示する。
            {
                this.ViewModel.ImageSource = "Image/init_V8+VPR81.PNG";

                // new InitializeMarkViewModel...から変更(2025.11.12yori)
                this.ViewModel.Marks[0].X = 430;
                this.ViewModel.Marks[0].Y = 365;
                this.ViewModel.Marks[1].X = 530;
                this.ViewModel.Marks[1].Y = 350;
                this.ViewModel.Marks[2].X = 415;
                this.ViewModel.Marks[2].Y = 70;
                this.ViewModel.Marks[3].X = 285;
                this.ViewModel.Marks[3].Y = 30;
                this.ViewModel.Marks[4].X = 190;
                this.ViewModel.Marks[4].Y = 220;
                this.ViewModel.Marks[5].X = 320;
                this.ViewModel.Marks[5].Y = 275;
                this.ViewModel.Marks[6].X = 145;
                this.ViewModel.Marks[6].Y = 320;

                this.ViewModel.Marks[0].Visibility = Visibility.Visible;
                this.ViewModel.Marks[1].Visibility = Visibility.Visible;
                this.ViewModel.Marks[2].Visibility = Visibility.Visible;
                this.ViewModel.Marks[3].Visibility = Visibility.Visible;
                this.ViewModel.Marks[4].Visibility = Visibility.Visible;
                this.ViewModel.Marks[5].Visibility = Visibility.Visible;
                this.ViewModel.Marks[6].Visibility = Visibility.Visible;
                this.ViewModel.Labels[0].Visibility = Visibility.Visible;
                this.ViewModel.Labels[1].Visibility = Visibility.Visible;
                this.ViewModel.Labels[2].Visibility = Visibility.Visible;
                this.ViewModel.Labels[3].Visibility = Visibility.Visible;
                this.ViewModel.Labels[4].Visibility = Visibility.Visible;
                this.ViewModel.Labels[5].Visibility = Visibility.Visible;
                this.ViewModel.Labels[6].Visibility = Visibility.Visible;
            }

            if (sts.arm_model == "VAR700M" || sts.arm_model == "VAR700L")
            {
                this.ViewModel.ImageSource = "Image/init_V7.png";

                // new InitializeMarkViewModel...から変更(2025.11.12yori)
                this.ViewModel.Marks[0].X = 430;
                this.ViewModel.Marks[0].Y = 365;
                this.ViewModel.Marks[1].X = 500;
                this.ViewModel.Marks[1].Y = 315;
                this.ViewModel.Marks[2].X = 420;
                this.ViewModel.Marks[2].Y = 60;
                this.ViewModel.Marks[3].X = 305;
                this.ViewModel.Marks[3].Y = 30;
                this.ViewModel.Marks[4].X = 250;
                this.ViewModel.Marks[4].Y = 190;
                this.ViewModel.Marks[5].X = 340;
                this.ViewModel.Marks[5].Y = 245;
                this.ViewModel.Marks[6].X = 180;
                this.ViewModel.Marks[6].Y = 290;

                this.ViewModel.Marks[0].Visibility = Visibility.Visible;
                this.ViewModel.Marks[1].Visibility = Visibility.Visible;
                this.ViewModel.Marks[2].Visibility = Visibility.Visible;
                this.ViewModel.Marks[3].Visibility = Visibility.Visible;
                this.ViewModel.Marks[4].Visibility = Visibility.Visible;
                this.ViewModel.Marks[5].Visibility = Visibility.Visible;
                this.ViewModel.Marks[6].Visibility = Visibility.Visible;
                this.ViewModel.Labels[0].Visibility = Visibility.Visible;
                this.ViewModel.Labels[1].Visibility = Visibility.Visible;
                this.ViewModel.Labels[2].Visibility = Visibility.Visible;
                this.ViewModel.Labels[3].Visibility = Visibility.Visible;
                this.ViewModel.Labels[4].Visibility = Visibility.Visible;
                this.ViewModel.Labels[5].Visibility = Visibility.Visible;
                this.ViewModel.Labels[6].Visibility = Visibility.Visible;
            }

            this.ViewModel.SlideSwitch = false; // 後でコーディングするため、暖機処理待ちオフ(2025.11.11yori)
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

        // イニシャライズ画面の初期設定(2025.7.15yori) // MainWindow.xaml.csのInitPanelSetupから移動(2025.11.12yori)
        public void InitPanelSetup()
        {
            Status01 sts = new Status01();
            CSH.AppMain.UpDateData01(out sts);
            if ((sts.arm_model == "VAR800M" || sts.arm_model == "VAR800L") && sts.no0_fg == 0) // 0軸が無い場合は、0軸無しの画像へ変更し、0番を表示しない。
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.ImageSource = "Image/init_machine10.PNG";

                    this.ViewModel.Marks[0].X = 430;
                    this.ViewModel.Marks[0].Y = 365;
                    this.ViewModel.Marks[1].X = 530;
                    this.ViewModel.Marks[1].Y = 350;
                    this.ViewModel.Marks[2].X = 415;
                    this.ViewModel.Marks[2].Y = 70;
                    this.ViewModel.Marks[3].X = 285;
                    this.ViewModel.Marks[3].Y = 30;
                    this.ViewModel.Marks[4].X = 190;
                    this.ViewModel.Marks[4].Y = 220;
                    this.ViewModel.Marks[5].X = 320;
                    this.ViewModel.Marks[5].Y = 275;
                    this.ViewModel.Marks[6].X = 145;
                    this.ViewModel.Marks[6].Y = 320;

                    this.ViewModel.Marks[0].Visibility = Visibility.Hidden;
                    this.ViewModel.Marks[1].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[2].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[3].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[4].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[5].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[6].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[0].Visibility = Visibility.Hidden;
                    this.ViewModel.Labels[1].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[2].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[3].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[4].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[5].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[6].Visibility = Visibility.Visible;
                });
            }

            if ((sts.arm_model == "VAR800M" || sts.arm_model == "VAR800L") && sts.no0_fg == 1) // 0軸が有る場合は、0軸有りの画像へ変更し、0番を表示する。
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.ImageSource = "Image/init_V8+VPR81.PNG";

                    this.ViewModel.Marks[0].X = 430;
                    this.ViewModel.Marks[0].Y = 365;
                    this.ViewModel.Marks[1].X = 530;
                    this.ViewModel.Marks[1].Y = 350;
                    this.ViewModel.Marks[2].X = 415;
                    this.ViewModel.Marks[2].Y = 70;
                    this.ViewModel.Marks[3].X = 285;
                    this.ViewModel.Marks[3].Y = 30;
                    this.ViewModel.Marks[4].X = 190;
                    this.ViewModel.Marks[4].Y = 220;
                    this.ViewModel.Marks[5].X = 320;
                    this.ViewModel.Marks[5].Y = 275;
                    this.ViewModel.Marks[6].X = 145;
                    this.ViewModel.Marks[6].Y = 320;

                    this.ViewModel.Marks[0].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[1].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[2].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[3].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[4].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[5].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[6].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[0].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[1].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[2].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[3].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[4].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[5].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[6].Visibility = Visibility.Visible;
                });
            }

            if (sts.arm_model == "VAR700M" || sts.arm_model == "VAR700L")
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    this.ViewModel.ImageSource = "Image/init_V7.png";

                    this.ViewModel.Marks[0].X = 430;
                    this.ViewModel.Marks[0].Y = 365;
                    this.ViewModel.Marks[1].X = 500;
                    this.ViewModel.Marks[1].Y = 315;
                    this.ViewModel.Marks[2].X = 420;
                    this.ViewModel.Marks[2].Y = 60;
                    this.ViewModel.Marks[3].X = 305;
                    this.ViewModel.Marks[3].Y = 30;
                    this.ViewModel.Marks[4].X = 250;
                    this.ViewModel.Marks[4].Y = 190;
                    this.ViewModel.Marks[5].X = 340;
                    this.ViewModel.Marks[5].Y = 245;
                    this.ViewModel.Marks[6].X = 180;
                    this.ViewModel.Marks[6].Y = 290;

                    this.ViewModel.Marks[0].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[1].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[2].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[3].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[4].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[5].Visibility = Visibility.Visible;
                    this.ViewModel.Marks[6].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[0].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[1].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[2].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[3].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[4].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[5].Visibility = Visibility.Visible;
                    this.ViewModel.Labels[6].Visibility = Visibility.Visible;
                });
            }
        }

        // イニシャライズ画面の更新(2025.7.14yori) // MainWindow.xaml.csから移動(2025.10.27yori)
        public void InitPanelUpdate()
        {
            Status01 sts = new Status01();
            CSH.AppMain.UpDateData01(out sts);
            for (int i = 0; i < 7; i++) // i = 1→0へ変更(2025.7.15yori)
            {
                if (sts.init_sts[i] == 1)
                {
                    switch (i)
                    {
                        case 0:
                            Application.Current.Dispatcher.Invoke(() =>
                            {
                                this.ViewModel.Marks[0].Visibility = Visibility.Hidden;
                                this.ViewModel.Labels[0].Visibility = Visibility.Hidden;
                            });
                            break;
                        case 1:
                            Application.Current.Dispatcher.Invoke(() =>
                            {
                                this.ViewModel.Marks[1].Visibility = Visibility.Hidden;
                                this.ViewModel.Labels[1].Visibility = Visibility.Hidden;
                            });
                            break;
                        case 2:
                            Application.Current.Dispatcher.Invoke(() =>
                            {
                                this.ViewModel.Marks[2].Visibility = Visibility.Hidden;
                                this.ViewModel.Labels[2].Visibility = Visibility.Hidden;
                            });
                            break;
                        case 3:
                            Application.Current.Dispatcher.Invoke(() =>
                            {
                                this.ViewModel.Marks[3].Visibility = Visibility.Hidden;
                                this.ViewModel.Labels[3].Visibility = Visibility.Hidden;
                            });
                            break;
                        case 4:
                            Application.Current.Dispatcher.Invoke(() =>
                            {
                                this.ViewModel.Marks[4].Visibility = Visibility.Hidden;
                                this.ViewModel.Labels[4].Visibility = Visibility.Hidden;
                            });
                            break;
                        case 5:
                            Application.Current.Dispatcher.Invoke(() =>
                            {
                                this.ViewModel.Marks[5].Visibility = Visibility.Hidden;
                                this.ViewModel.Labels[5].Visibility = Visibility.Hidden;
                            });
                            break;
                        case 6:
                            Application.Current.Dispatcher.Invoke(() =>
                            {
                                this.ViewModel.Marks[6].Visibility = Visibility.Hidden;
                                this.ViewModel.Labels[6].Visibility = Visibility.Hidden;
                            });
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}
