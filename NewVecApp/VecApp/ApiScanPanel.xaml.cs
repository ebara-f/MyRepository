using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
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
    /// ApiScanPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class ApiScanPanel : PanelBase
    {
        public ApiScanPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.ApiScan)
        {
            InitializeComponent();
            // 以降、ViewModel対応による追加
            this.DataContext = model;

            // TreeViewItem.Expandedイベントを監視(2025.11.7yori)
            ApiScanTree.AddHandler(TreeViewItem.ExpandedEvent,
                new RoutedEventHandler(TreeViewItem_Expanded), true);

            // MainWindow.xaml.csから移動(2025.8.21yori)
            Status02 sts = new Status02();
            CSH.AppMain.UpDateData02(out sts);

            // 計測モード(2025.8.11yori)
            this.ViewModel.ApiScanItems1.Clear();
            this.ViewModel.ApiScanItems1.Insert(0, sts.mode0_info);
            this.ViewModel.ApiScanItems1.Insert(1, sts.mode1_info);
            this.ViewModel.ApiScanItems1.Insert(2, sts.mode2_info);
            this.ViewModel.ApiScanItems1.Insert(3, sts.mode3_info);
            this.ViewModel.ApiScanItems1.Insert(4, sts.mode4_info);
            this.ViewModel.ApiScanItems1.Insert(5, sts.mode5_info);
            this.ViewModel.ApiScanIndex1 = sts.mode;

            // 点間ピッチ(2025.11.6yori)
            this.ViewModel.ApiScanText = Math.Round(sts.pitch[0], 3, MidpointRounding.AwayFromZero).ToString("F3"); // 1/1 // 四捨五入されるようsts.pitch[0].ToString("F3")から修正(2026.1.28yori)

            // 感度(2025.8.18yori)
            var Item1 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "Sensitivity");
            if (Item1?.Options != null)
            {
                Item1.Options.Clear();
                if (sts.sens_use[0] == 1) Item1.Options.Insert(0, sts.sens_name0);
                if (sts.sens_use[1] == 1) Item1.Options.Insert(1, sts.sens_name1);
                if (sts.sens_use[2] == 1) Item1.Options.Insert(2, sts.sens_name2);
                if (sts.sens_use[3] == 1) Item1.Options.Insert(3, sts.sens_name3);
                if (sts.sens_use[4] == 1) Item1.Options.Insert(4, sts.sens_name4);
                Item1.OptionIndex1 = sts.sens; // Item1.SelectedOption = "Normal";からスキャナに設定されている感度を表示する。(2025.11.25yori)
            }

            // 輝度マスク(2026.9.2yori)
            var Item = this.ViewModel.TreeItems.FirstOrDefault(x => x.UIType == "LuminosityMask");
            if (Item?.OptionIndex2 != null)
            {
                Item.OptionIndex2 = sts.bright_mask_select;
                var Item0 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminosityMask2");
                if (Item0?.InputText32 != null)
                {
                    Item0.InputText32 = sts.bright_mask_upper_limit.ToString();
                }
                if (Item0?.InputText33 != null)
                {
                    Item0.InputText33 = sts.bright_mask_lower_limit.ToString();
                }
            }

            // 距離マスク(2025.8.22yori) // Item4→Item3へ変更(ViewModelの番号と合わせる。)(2025.8.26yori)
            var Item3 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "DistanceMask2");
            if (Item3?.IsChecked1 != null) // 追加(2025.8.26yori)
            {
                switch (sts.mode)
                {
                    case 0:
                        if (sts.use[0] == 1)
                        {
                            Item3.IsChecked1 = true;
                        }
                        else
                        {
                            //Item3.IsChecked1 = false;
                        }
                        if (sts.use[1] == 1)
                        {
                            Item3.IsChecked2 = true;
                        }
                        else
                        {
                            //Item3.IsChecked2 = false;
                        }
                        if (sts.use[2] == 1) Item3.IsChecked3 = true;
                        if (sts.use[3] == 1) Item3.IsChecked4 = true;
                        if (sts.use[4] == 1) Item3.IsChecked5 = true;
                        if (sts.use[5] == 1) Item3.IsChecked6 = true;
                        Item3.InputText1 = sts.data[0].ToString("F1");
                        Item3.InputText2 = sts.data[1].ToString("F1");
                        Item3.InputText3 = sts.data[2].ToString("F1");
                        Item3.InputText4 = sts.data[3].ToString("F1");
                        Item3.InputText5 = sts.data[4].ToString("F1");
                        Item3.InputText6 = sts.data[5].ToString("F1");
                        break;
                    case 1:
                        if (sts.use[6] == 1) Item3.IsChecked1 = true;
                        if (sts.use[7] == 1) Item3.IsChecked2 = true;
                        if (sts.use[8] == 1) Item3.IsChecked3 = true;
                        if (sts.use[9] == 1) Item3.IsChecked4 = true;
                        if (sts.use[10] == 1) Item3.IsChecked5 = true;
                        if (sts.use[11] == 1) Item3.IsChecked6 = true;
                        Item3.InputText1 = sts.data[6].ToString("F1");
                        Item3.InputText2 = sts.data[7].ToString("F1");
                        Item3.InputText3 = sts.data[8].ToString("F1");
                        Item3.InputText4 = sts.data[9].ToString("F1");
                        Item3.InputText5 = sts.data[10].ToString("F1");
                        Item3.InputText6 = sts.data[11].ToString("F1");
                        break;
                    case 2:
                        if (sts.use[12] == 1) Item3.IsChecked1 = true;
                        if (sts.use[13] == 1) Item3.IsChecked2 = true;
                        if (sts.use[14] == 1) Item3.IsChecked3 = true;
                        if (sts.use[15] == 1) Item3.IsChecked4 = true;
                        if (sts.use[16] == 1) Item3.IsChecked5 = true;
                        if (sts.use[17] == 1) Item3.IsChecked6 = true;
                        Item3.InputText1 = sts.data[12].ToString("F1");
                        Item3.InputText2 = sts.data[13].ToString("F1");
                        Item3.InputText3 = sts.data[14].ToString("F1");
                        Item3.InputText4 = sts.data[15].ToString("F1");
                        Item3.InputText5 = sts.data[16].ToString("F1");
                        Item3.InputText6 = sts.data[17].ToString("F1");
                        break;
                    case 3:
                        if (sts.use[18] == 1) Item3.IsChecked1 = true;
                        if (sts.use[19] == 1) Item3.IsChecked2 = true;
                        if (sts.use[20] == 1) Item3.IsChecked3 = true;
                        if (sts.use[21] == 1) Item3.IsChecked4 = true;
                        if (sts.use[22] == 1) Item3.IsChecked5 = true;
                        if (sts.use[23] == 1) Item3.IsChecked6 = true;
                        Item3.InputText1 = sts.data[18].ToString("F1");
                        Item3.InputText2 = sts.data[19].ToString("F1");
                        Item3.InputText3 = sts.data[20].ToString("F1");
                        Item3.InputText4 = sts.data[21].ToString("F1");
                        Item3.InputText5 = sts.data[22].ToString("F1");
                        Item3.InputText6 = sts.data[23].ToString("F1");
                        break;
                    case 4:
                        if (sts.use[24] == 1) Item3.IsChecked1 = true;
                        if (sts.use[25] == 1) Item3.IsChecked2 = true;
                        if (sts.use[26] == 1) Item3.IsChecked3 = true;
                        if (sts.use[27] == 1) Item3.IsChecked4 = true;
                        if (sts.use[28] == 1) Item3.IsChecked5 = true;
                        if (sts.use[29] == 1) Item3.IsChecked6 = true;
                        Item3.InputText1 = sts.data[24].ToString("F1");
                        Item3.InputText2 = sts.data[25].ToString("F1");
                        Item3.InputText3 = sts.data[26].ToString("F1");
                        Item3.InputText4 = sts.data[27].ToString("F1");
                        Item3.InputText5 = sts.data[28].ToString("F1");
                        Item3.InputText6 = sts.data[29].ToString("F1");
                        break;
                    case 5:
                        if (sts.use[30] == 1) Item3.IsChecked1 = true;
                        if (sts.use[31] == 1) Item3.IsChecked2 = true;
                        if (sts.use[32] == 1) Item3.IsChecked3 = true;
                        if (sts.use[33] == 1) Item3.IsChecked4 = true;
                        if (sts.use[34] == 1) Item3.IsChecked5 = true;
                        if (sts.use[35] == 1) Item3.IsChecked6 = true;
                        Item3.InputText1 = sts.data[30].ToString("F1");
                        Item3.InputText2 = sts.data[31].ToString("F1");
                        Item3.InputText3 = sts.data[32].ToString("F1");
                        Item3.InputText4 = sts.data[33].ToString("F1");
                        Item3.InputText5 = sts.data[34].ToString("F1");
                        Item3.InputText6 = sts.data[35].ToString("F1");
                        break;
                    default:
                        break;
                }
            }
            var parent3 = this.ViewModel.TreeItems.FirstOrDefault(x => x.UIType == "DistanceMask1");
            if (parent3?.SlideSwitchValue != null) // 追加(2025.8.26yori)
            {
                parent3.SlideSwitchValue = sts.dist_onoff; // 追加(2025.8.30yori)
                if (parent3.SlideSwitchValue == 0)
                {
                    // 距離マスクがOFFなら各(左右遠近)CheckBoxを無効にする。(2025.8.26yori)
                    // CheckBoxを識別する。(2026.8.6yori)
                    Item3.IsCheckBox1Enabled = false;
                    Item3.IsCheckBox2Enabled = false;
                    Item3.IsCheckBox5Enabled = false;
                    Item3.IsCheckBox6Enabled = false;
                }
            }

            // 輝度スライス(2025.8.23yori)
            var Item5 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminanceSlice");           
            // スタンダードのラジオボタンの有効無効を設定する。(2026.8.29yori)
            if (Item5?.IsChecked7 != null)
            {
                if (sts.bright_slice_std_enable == 1)
                {
                    Item5.IsChecked7 = true;
                }
                else
                {
                    Item5.IsChecked7 = false;
                }
            }
            // アドバンスのラジオボタンの有効無効を設定する。(2026.8.29yori)
            if (Item5?.IsChecked8 != null)
            {
                if (sts.bright_slice_adv_enable == 1)
                {
                    Item5.IsChecked8 = true;
                }
                else
                {
                    Item5.IsChecked8 = false;
                }
            }
            if (Item5?.InputText12 != null) // 追加(2025.8.26yori)
            {
                // スタンダード
                Item5.InputText12 = "24528";
                Item5.InputText13 = "24528";
                Item5.InputText14 = "24528";
                // アドバンス
                Item5.InputText15 = sts.bright_slice[0].ToString();
                Item5.InputText16 = sts.bright_slice[1].ToString();
                Item5.InputText17 = sts.bright_slice[2].ToString();
            }

            // 感度スライス(2025.8.23yori)
            var Item6 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "SensitivitySlice");
            // スタンダードのラジオボタンの有効無効を設定する。(2026.8.29yori)
            if (Item5?.IsChecked9 != null)
            {
                if (sts.bright_slice_std_enable == 1)
                {
                    Item5.IsChecked9 = true;
                }
                else
                {
                    Item5.IsChecked9 = false;
                }
            }
            // アドバンスのラジオボタンの有効無効を設定する。(2026.8.29yori)
            if (Item5?.IsChecked10 != null)
            {
                if (sts.bright_slice_adv_enable == 1)
                {
                    Item5.IsChecked10 = true;
                }
                else
                {
                    Item5.IsChecked10 = false;
                }
            }
            if (Item6?.InputText18 != null) // 追加(2025.8.26yori)
            {
                // スタンダード
                Item6.InputText18 = "3276";
                Item6.InputText19 = "1200";
                Item6.InputText20 = "3276";
                // アドバンス
                Item6.InputText21 = sts.sens_slice[0].ToString();
                Item6.InputText22 = sts.sens_slice[1].ToString();
                Item6.InputText23 = sts.sens_slice[2].ToString();
            }

            // ガイドレーザーパワー(2025.8.21yori) // Item3→Item7へ変更(ViewModelの番号と合わせる。)(2025.8.26yori)
            var Item7 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "GuideLaserPower");
            if (Item7?.Options3 != null)
            {
                Item7.Options3.Clear();
                Item7.Options3.Insert(0, VecApp.Properties.Resources.String132); // 変更(2025.12.18yori)
                Item7.Options3.Insert(1, VecApp.Properties.Resources.String133); // 変更(2025.12.18yori)
                Item7.Options3.Insert(2, VecApp.Properties.Resources.String134); // 変更(2025.12.18yori)
                Item7.OptionIndex3 = sts.power;
            }

            // 補間(Xピッチ)(2025.11.21yori)
            var Item8 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "Interpolation");
            if (Item8?.SlideText7 != null)
            {
                // スキャナに設定されている補間を表示する。(2025.11.25yori)
                if (sts.xpitch_onoff == 0) Item8.SlideSwitch7 = false;
                if (sts.xpitch_onoff == 1) Item8.SlideSwitch7 = true;
            }

            // 角度マスク(2025.8.24yori)
            var Item9 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "AngleMask");
            if (Item9?.SlideSwitchValue8 != null) // 追加(2025.8.31yori)
            {
                Item9.SlideSwitchValue8 = sts.angle_mask_onoff;
                if (Item9.SlideSwitchValue8 == 1)
                {
                    Item9.IsAngleMaskEnabled = true;
                    Item9.SlideText8 = VecApp.Properties.Resources.String144;
                }
                else
                {
                    Item9.IsAngleMaskEnabled = false;
                    Item9.SlideText8 = VecApp.Properties.Resources.String143;
                }
            }
            if (Item9?.InputText25 != null) // 追加(2025.8.26yori)
            {
                Item9.InputText25 = sts.angle_mask_deg.ToString("F1"); // angle→angle_mask_deg(2026.8.6yori)
            }

            // 2ピークマスク(2028.8.25yori)
            var Item10 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "TwoPeakMask");
            if (Item10?.OptionIndex4 != null) // 追加(2025.8.26yori)
            {
                Item10.OptionIndex4 = sts.two_peak;
            }

            // エッジマスク(2028.8.25yori)
            var Item11 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "EdgeMask");
            if (Item11?.InputText26 != null) // 追加(2025.8.26yori)
            {
                Item11.InputText26 = sts.edge.ToString();
            }
        }

        private ApiScanViewModel ViewModel
        {
            get => this.DataContext as ApiScanViewModel;
        }

        private void Click_SensorParameterBtn(object sender, RoutedEventArgs e)
        {
            // ボタンをクリック毎にスキャナパラメータ詳細画面の表示、非表示を切り替える。(2025.8.13yori)
            if (this.ViewModel.IsSensorParameterVisible == Visibility.Visible)
            {
                this.ViewModel.IsSensorParameterVisible = Visibility.Collapsed;
            }
            else
            {
                this.ViewModel.IsSensorParameterVisible = Visibility.Visible;
            }
        }

        private void Click_StartBtn(object sender, RoutedEventArgs e)
        {
            // ボタンの名前を切り替えと、スキャンとストップを行う。(2025.8.12yori)
            // 多言語対応による変更(2025.12.22yori)
            if (SartStopButton.Content.ToString() == VecApp.Properties.Resources.String114)
            {
                Status02 sts = new Status02();
                CSH.AppMain.UpDateData02(out sts); // 追加(2025.8.25yori)

                // 画面からスキャナパラメータ取得し、スキャナに設定する。

                // 感度(2025.8.26yori)
                // スキャナへの変更はComboBox変更時に行う。(2025.9.4yori)

                // 距離マスク(2025.8.23yori)
                var parent3 = this.ViewModel.TreeItems.FirstOrDefault(x => x.UIType == "DistanceMask1");
                if (parent3?.SlideSwitchValue != null) // 追加(2025.8.26yori)
                {
                    if (parent3.SlideSwitchValue == 1) // 距離マスクがオンの場合
                    {
                        // Item4→Item3へ変更(ViewModelの番号と合わせる。)(2025.8.26yori)
                        var Item3 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "DistanceMask2");
                        if (Item3?.IsChecked1 != null) // 追加(2025.8.26yori)
                        {
                            switch (sts.mode)
                            {
                                case 0:
                                    if (Item3.IsChecked1 == true) sts.use[0] = 1;
                                    if (Item3.IsChecked2 == true) sts.use[1] = 1;
                                    if (Item3.IsChecked3 == true) sts.use[2] = 1;
                                    if (Item3.IsChecked4 == true) sts.use[3] = 1;
                                    if (Item3.IsChecked5 == true) sts.use[4] = 1;
                                    if (Item3.IsChecked6 == true) sts.use[5] = 1;
                                    sts.data[0] = double.Parse(Item3.InputText1);
                                    sts.data[1] = double.Parse(Item3.InputText2);
                                    sts.data[2] = double.Parse(Item3.InputText3);
                                    sts.data[3] = double.Parse(Item3.InputText4);
                                    sts.data[4] = double.Parse(Item3.InputText5);
                                    sts.data[5] = double.Parse(Item3.InputText6);
                                    break;
                                case 1:
                                    if (Item3.IsChecked1 == true) sts.use[6] = 1;
                                    if (Item3.IsChecked2 == true) sts.use[7] = 1;
                                    if (Item3.IsChecked3 == true) sts.use[8] = 1;
                                    if (Item3.IsChecked4 == true) sts.use[9] = 1;
                                    if (Item3.IsChecked5 == true) sts.use[10] = 1;
                                    if (Item3.IsChecked6 == true) sts.use[11] = 1;
                                    sts.data[6] = double.Parse(Item3.InputText1);
                                    sts.data[7] = double.Parse(Item3.InputText2);
                                    sts.data[8] = double.Parse(Item3.InputText3);
                                    sts.data[9] = double.Parse(Item3.InputText4);
                                    sts.data[10] = double.Parse(Item3.InputText5);
                                    sts.data[11] = double.Parse(Item3.InputText6);
                                    break;
                                case 2:
                                    if (Item3.IsChecked1 == true) sts.use[12] = 1;
                                    if (Item3.IsChecked2 == true) sts.use[13] = 1;
                                    if (Item3.IsChecked3 == true) sts.use[14] = 1;
                                    if (Item3.IsChecked4 == true) sts.use[15] = 1;
                                    if (Item3.IsChecked5 == true) sts.use[16] = 1;
                                    if (Item3.IsChecked6 == true) sts.use[17] = 1;
                                    sts.data[12] = double.Parse(Item3.InputText1);
                                    sts.data[13] = double.Parse(Item3.InputText2);
                                    sts.data[14] = double.Parse(Item3.InputText3);
                                    sts.data[15] = double.Parse(Item3.InputText4);
                                    sts.data[16] = double.Parse(Item3.InputText5);
                                    sts.data[17] = double.Parse(Item3.InputText6);
                                    break;
                                case 3:
                                    if (Item3.IsChecked1 == true) sts.use[18] = 1;
                                    if (Item3.IsChecked2 == true) sts.use[19] = 1;
                                    if (Item3.IsChecked3 == true) sts.use[20] = 1;
                                    if (Item3.IsChecked4 == true) sts.use[21] = 1;
                                    if (Item3.IsChecked5 == true) sts.use[22] = 1;
                                    if (Item3.IsChecked6 == true) sts.use[23] = 1;
                                    sts.data[18] = double.Parse(Item3.InputText1);
                                    sts.data[19] = double.Parse(Item3.InputText2);
                                    sts.data[20] = double.Parse(Item3.InputText3);
                                    sts.data[21] = double.Parse(Item3.InputText4);
                                    sts.data[22] = double.Parse(Item3.InputText5);
                                    sts.data[23] = double.Parse(Item3.InputText6);
                                    break;
                                case 4:
                                    if (Item3.IsChecked1 == true) sts.use[24] = 1;
                                    if (Item3.IsChecked2 == true) sts.use[25] = 1;
                                    if (Item3.IsChecked3 == true) sts.use[26] = 1;
                                    if (Item3.IsChecked4 == true) sts.use[27] = 1;
                                    if (Item3.IsChecked5 == true) sts.use[28] = 1;
                                    if (Item3.IsChecked6 == true) sts.use[29] = 1;
                                    sts.data[24] = double.Parse(Item3.InputText1);
                                    sts.data[25] = double.Parse(Item3.InputText2);
                                    sts.data[26] = double.Parse(Item3.InputText3);
                                    sts.data[27] = double.Parse(Item3.InputText4);
                                    sts.data[28] = double.Parse(Item3.InputText5);
                                    sts.data[29] = double.Parse(Item3.InputText6);
                                    break;
                                case 5:
                                    if (Item3.IsChecked1 == true) sts.use[30] = 1;
                                    if (Item3.IsChecked2 == true) sts.use[31] = 1;
                                    if (Item3.IsChecked3 == true) sts.use[32] = 1;
                                    if (Item3.IsChecked4 == true) sts.use[33] = 1;
                                    if (Item3.IsChecked5 == true) sts.use[34] = 1;
                                    if (Item3.IsChecked6 == true) sts.use[35] = 1;
                                    sts.data[30] = double.Parse(Item3.InputText1);
                                    sts.data[31] = double.Parse(Item3.InputText2);
                                    sts.data[32] = double.Parse(Item3.InputText3);
                                    sts.data[33] = double.Parse(Item3.InputText4);
                                    sts.data[34] = double.Parse(Item3.InputText5);
                                    sts.data[35] = double.Parse(Item3.InputText6);
                                    break;
                                default:
                                    break;
                            }

                            CSH.Grp03.Cmd10(in sts); // 引数追加に伴う変更(2026.8.7yori)
                        }
                    }
                }

                // 輝度スライス(2025.8.24yori)
                var Item5 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminanceSlice");
                if (Item5?.InputText15 != null) // 追加(2025.8.26yori)
                {
                    sts.bright_slice[0] = ushort.Parse(Item5.InputText15);
                    sts.bright_slice[1] = ushort.Parse(Item5.InputText16);
                    sts.bright_slice[2] = ushort.Parse(Item5.InputText17);
                    if (Item5.IsChecked8 == true)
                    {
                        CSH.Grp03.Cmd11(sts.bright_slice); // 引数追加に伴う変更(2026.8.6yori)
                    }
                }

                // 感度スライス(2025.8.24yori)
                var Item6 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "SensitivitySlice");
                if (Item6?.InputText21 != null) // 追加(2025.8.26yori)
                {
                    sts.sens_slice[0] = ushort.Parse(Item6.InputText21);
                    sts.sens_slice[1] = ushort.Parse(Item6.InputText22);
                    sts.sens_slice[2] = ushort.Parse(Item6.InputText23);
                    if (Item6.IsChecked10 == true)
                    {
                        CSH.Grp03.Cmd12(sts.sens_slice); // 引数追加に伴う変更(2026.8.6yori)
                    }
                }

                // 角度マスク(2025.8.24yori)
                var Item9 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "AngleMask");
                if (Item9?.InputText25 != null) // 追加(2025.8.26yori)
                {
                    if (Item9.SlideSwitchValue8 == 1)
                    {
                        CSH.Grp03.Cmd13(Item9.SlideSwitchValue8, double.Parse(Item9.InputText25)); // 引数追加に伴う変更(2026.8.6yori) // 引数追加(2026.8.31yori)
                    }
                }

                // エッジマスク(2028.8.25yori)
                var Item11 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "EdgeMask");
                if (Item11?.InputText26 != null) // 追加(2025.8.26yori)
                {
                    CSH.Grp03.Cmd15(int.Parse(Item11.InputText26)); // 引数追加に伴う変更(2026.8.6yori)
                }
                
                CSH.Grp03.Cmd01(); // スキャンスタート
                SartStopButton.Content = VecApp.Properties.Resources.String278; // 多言語対応による変更(2025.12.22yori)
                ScanMode.IsEnabled = false; // 計測モードComboBox無効
                Pitch.IsEnabled = false; // 点間ピッチComboBox無効
            }
            else
            {
                CSH.Grp03.Cmd02(); // スキャンストップ
                SartStopButton.Content = VecApp.Properties.Resources.String114; // 多言語対応による変更(2025.12.22yori)
                ScanMode.IsEnabled = true; // ComboBox有効
                Pitch.IsEnabled = true; // 点間ピッチComboBox有効
            }
        }
        private void Click_ResetBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp03.Cmd16(); // スキャナのリセット(2025.8.27yori)
        }
        private void Click_ColorMapBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_AutoMeshingBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_SaveBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_ParameterInitializationBtn(object sender, RoutedEventArgs e)
        {
            // メッセージボックスを表示する。(2025.8.26yori)
            // 多言語対応による変更(2025.12.22yori)
            // タイトルバーの(beta)削除(2026.1.13yori)
            MessageBoxResult result;
            result = MessageBox.Show(VecApp.Properties.Resources.String195, "Beak Master Plug-in SoftWare", MessageBoxButton.YesNo, MessageBoxImage.Information);
            switch (result)
            {
                case MessageBoxResult.Yes:
                    // スキャナパラメータを初期値へ設定する。(2025.8.26yori)
                    // 感度
                    var Item = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "Sensitivity");
                    if (Item?.OptionIndex1 != null)
                    {
                        Item.OptionIndex1 = 0; // 感度をNormalに表示
                    }
                    
                    // 距離マスク
                    var parent3 = this.ViewModel.TreeItems.FirstOrDefault(x => x.UIType == "DistanceMask1");
                    if (parent3?.SlideSwitchValue != null)
                    {
                        parent3.SlideSwitchValue = 0;
                    }
                    var Item3 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "DistanceMask2");
                    if (Item3?.IsChecked1 != null)
                    {
                        Item3.IsChecked1 = false;
                        Item3.IsChecked2 = false;
                        Item3.IsChecked3 = false;
                        Item3.IsChecked4 = false;
                        Item3.IsChecked5 = false;
                        Item3.IsChecked6 = false;
                        Item3.InputText1 = "0.0";
                        Item3.InputText2 = "0.0";
                        Item3.InputText3 = "0.0";
                        Item3.InputText4 = "0.0";
                        Item3.InputText5 = "0.0";
                        Item3.InputText6 = "0.0";
                    }

                    // 輝度スライス
                    var Item5 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminanceSlice");
                    if (Item5?.InputText15 != null)
                    {
                        // アドバンス
                        Item5.InputText15 = "24528";
                        Item5.InputText16 = "24528";
                        Item5.InputText17 = "24528";
                    }

                    // 感度スライス
                    var Item6 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "SensitivitySlice");
                    if (Item6?.InputText21 != null)
                    {
                        // アドバンス
                        Item6.InputText21 = "3276";
                        Item6.InputText22 = "1200";
                        Item6.InputText23 = "3276";
                    }

                    // ガイドレーザーパワー
                    var Item7 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "GuideLaserPower");
                    if (Item7?.Options3 != null)
                    {
                        Item7.OptionIndex3 = 1; // ガイドレーザーパワーを中に表示
                    }

                    // 補間(Xピッチ)
                    var Item8 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "Interpolation");
                    if (Item8?.SlideText7 != null) // 誤記(Options3)修正(2025.11.21yori)
                    {
                        Item8.SlideSwitchValue7 = 0;
                    }

                    // 角度マスク
                    var Item9 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "AngleMask");
                    if (Item9?.InputText25 != null)
                    {
                        Item9.InputText25 = "70.0";
                    }

                    // 2ピークマスク
                    var Item10 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "TwoPeakMask");
                    if (Item10?.OptionIndex4 != null)
                    {
                        Item10.OptionIndex4 = 0; // 2ピークマスクをデータ無効に表示
                    }

                    // エッジマスク
                    var Item11 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "EdgeMask");
                    if (Item11?.InputText26 != null)
                    {
                        Status02 sts = new Status02();
                        CSH.AppMain.UpDateData02(out sts);
                        Item11.InputText26 = sts.edge_default[sts.mode].ToString(); // デフォルトはNormalで現在の計測モードのエッジマスク点数を取得する。(2025.8.27yori)
                    }

                    break;
                case MessageBoxResult.No:
                    break;
            }
        }
        private void Click_DisplayBtn(object sender, RoutedEventArgs e)
        {

        }
        private void Click_CloseBtn(object sender, RoutedEventArgs e)
        {
            Status02 sts = new Status02(); // 追加(2026.8.6yori)
            CSH.AppMain.UpDateData02(out sts); // 追加(2026.8.7yori)

            // 輝度マスク(2026.9.2yori)
            var Item = this.ViewModel.TreeItems.FirstOrDefault(x => x.UIType == "LuminosityMask");
            if (Item?.OptionIndex2 != null)
            {
                switch (Item.OptionIndex2)
                {
                    case 0: // なし
                        var Item0 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminosityMask2");
                        if (Item0?.InputText32 != null)
                        {
                            sts.bright_mask_upper_limit = 65535;
                        }
                        if (Item0?.InputText33 != null)
                        {
                            sts.bright_mask_lower_limit = 0;
                        }
                        sts.bright_mask_select = 0;
                        CSH.Grp03.SetBrightMaskSetting(sts);
                        break;
                    case 1: // 手動
                        var Item1 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminosityMask2");
                        if (Item1?.InputText32 != null)
                        {
                            sts.bright_mask_upper_limit = int.Parse(Item1.InputText32);
                        }
                        if (Item1?.InputText33 != null)
                        {
                            sts.bright_mask_lower_limit = int.Parse(Item1.InputText33);
                        }
                        sts.bright_mask_select = 1;
                        CSH.Grp03.SetBrightMaskSetting(sts);
                        break;
                    case 2: // 自動(1パッチ毎)
                        var Item2 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminosityMask2");
                        if (Item2?.InputText32 != null)
                        {
                            sts.bright_mask_upper_limit = int.Parse(Item2.InputText32);
                        }
                        if (Item2?.InputText33 != null)
                        {
                            sts.bright_mask_lower_limit = int.Parse(Item2.InputText33);
                        }
                        sts.bright_mask_select = 2;
                        CSH.Grp03.SetBrightMaskSetting(sts);
                        break;
                    case 3: // 自動(スタート毎)
                        var Item3 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminosityMask2");
                        if (Item3?.InputText32 != null)
                        {
                            sts.bright_mask_upper_limit = int.Parse(Item3.InputText32);
                        }
                        if (Item3?.InputText33 != null)
                        {
                            sts.bright_mask_lower_limit = int.Parse(Item3.InputText33);
                        }
                        sts.bright_mask_select = 3;
                        CSH.Grp03.SetBrightMaskSetting(sts);
                        break;
                    default:
                        break;
                }
            }

            // 距離マスク(2026.8.8yori)
            var parent3 = this.ViewModel.TreeItems.FirstOrDefault(x => x.UIType == "DistanceMask1");
            if (parent3?.SlideSwitchValue != null)
            {
                if (parent3.SlideSwitchValue == 1) // 距離マスクがオンの場合
                {
                    var Item3 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "DistanceMask2");
                    if (Item3?.IsChecked1 != null)
                    {
                        switch (sts.mode)
                        {
                            case 0:
                                if (Item3.IsChecked1 == true)
                                {
                                    sts.use[0] = 1;
                                }
                                else
                                {
                                    sts.use[0] = 0;
                                }
                                if (Item3.IsChecked2 == true)
                                {
                                    sts.use[1] = 1;
                                }
                                else
                                {
                                    sts.use[1] = 0;
                                }
                                if (Item3.IsChecked3 == true)
                                {
                                    sts.use[2] = 1;
                                }
                                else
                                {
                                    sts.use[2] = 0;
                                }
                                if (Item3.IsChecked4 == true)
                                {
                                    sts.use[3] = 1;
                                }
                                else
                                {
                                    sts.use[3] = 0;
                                }
                                if (Item3.IsChecked5 == true)
                                {
                                    sts.use[4] = 1;
                                }
                                else
                                {
                                    sts.use[4] = 0;
                                }
                                if (Item3.IsChecked6 == true)
                                {
                                    sts.use[5] = 1;
                                }
                                else
                                {
                                    sts.use[5] = 0;
                                }
                                sts.data[0] = double.Parse(Item3.InputText1);
                                sts.data[1] = double.Parse(Item3.InputText2);
                                sts.data[2] = double.Parse(Item3.InputText3);
                                sts.data[3] = double.Parse(Item3.InputText4);
                                sts.data[4] = double.Parse(Item3.InputText5);
                                sts.data[5] = double.Parse(Item3.InputText6);
                                break;
                            case 1:
                                if (Item3.IsChecked1 == true)
                                {
                                    sts.use[6] = 1;
                                }
                                else
                                {
                                    sts.use[6] = 0;
                                }
                                if (Item3.IsChecked2 == true)
                                {
                                    sts.use[7] = 1;
                                }
                                else
                                {
                                    sts.use[7] = 0;
                                }
                                if (Item3.IsChecked3 == true)
                                {
                                    sts.use[8] = 1;
                                }
                                else
                                {
                                    sts.use[8] = 0;
                                }
                                if (Item3.IsChecked4 == true)
                                {
                                    sts.use[9] = 1;
                                }
                                else
                                {
                                    sts.use[9] = 0;
                                }
                                if (Item3.IsChecked5 == true)
                                {
                                    sts.use[10] = 1;
                                }
                                else
                                {
                                    sts.use[10] = 0;
                                }
                                if (Item3.IsChecked6 == true)
                                {
                                    sts.use[11] = 1;
                                }
                                else
                                {
                                    sts.use[11] = 0;
                                }
                                sts.data[6] = double.Parse(Item3.InputText1);
                                sts.data[7] = double.Parse(Item3.InputText2);
                                sts.data[8] = double.Parse(Item3.InputText3);
                                sts.data[9] = double.Parse(Item3.InputText4);
                                sts.data[10] = double.Parse(Item3.InputText5);
                                sts.data[11] = double.Parse(Item3.InputText6);
                                break;
                            case 2:
                                if (Item3.IsChecked1 == true)
                                {
                                    sts.use[12] = 1;
                                }
                                else
                                {
                                    sts.use[12] = 0;
                                }
                                if (Item3.IsChecked2 == true)
                                {
                                    sts.use[13] = 1;
                                }
                                else
                                {
                                    sts.use[13] = 0;
                                }
                                if (Item3.IsChecked3 == true)
                                {
                                    sts.use[14] = 1;
                                }
                                else
                                {
                                    sts.use[14] = 0;
                                }
                                if (Item3.IsChecked4 == true)
                                {
                                    sts.use[15] = 1;
                                }
                                else
                                {
                                    sts.use[15] = 0;
                                }
                                if (Item3.IsChecked5 == true)
                                {
                                    sts.use[16] = 1;
                                }
                                else
                                {
                                    sts.use[16] = 0;
                                }
                                if (Item3.IsChecked6 == true)
                                {
                                    sts.use[17] = 1;
                                }
                                else
                                {
                                    sts.use[17] = 0;
                                }
                                sts.data[12] = double.Parse(Item3.InputText1);
                                sts.data[13] = double.Parse(Item3.InputText2);
                                sts.data[14] = double.Parse(Item3.InputText3);
                                sts.data[15] = double.Parse(Item3.InputText4);
                                sts.data[16] = double.Parse(Item3.InputText5);
                                sts.data[17] = double.Parse(Item3.InputText6);
                                break;
                            case 3:
                                if (Item3.IsChecked1 == true)
                                {
                                    sts.use[18] = 1;
                                }
                                else
                                {
                                    sts.use[18] = 0;
                                }
                                if (Item3.IsChecked2 == true)
                                {
                                    sts.use[19] = 1;
                                }
                                else
                                {
                                    sts.use[19] = 0;
                                }
                                if (Item3.IsChecked3 == true)
                                {
                                    sts.use[20] = 1;
                                }
                                else
                                {
                                    sts.use[20] = 0;
                                }
                                if (Item3.IsChecked4 == true)
                                {
                                    sts.use[21] = 1;
                                }
                                else
                                {
                                    sts.use[21] = 0;
                                }
                                if (Item3.IsChecked5 == true)
                                {
                                    sts.use[22] = 1;
                                }
                                else
                                {
                                    sts.use[22] = 0;
                                }
                                if (Item3.IsChecked6 == true)
                                {
                                    sts.use[23] = 1;
                                }
                                else
                                {
                                    sts.use[23] = 0;
                                }
                                sts.data[18] = double.Parse(Item3.InputText1);
                                sts.data[19] = double.Parse(Item3.InputText2);
                                sts.data[20] = double.Parse(Item3.InputText3);
                                sts.data[21] = double.Parse(Item3.InputText4);
                                sts.data[22] = double.Parse(Item3.InputText5);
                                sts.data[23] = double.Parse(Item3.InputText6);
                                break;
                            case 4:
                                if (Item3.IsChecked1 == true)
                                {
                                    sts.use[24] = 1;
                                }
                                else
                                {
                                    sts.use[24] = 0;
                                }
                                if (Item3.IsChecked2 == true)
                                {
                                    sts.use[25] = 1;
                                }
                                else
                                {
                                    sts.use[25] = 0;
                                }
                                if (Item3.IsChecked3 == true)
                                {
                                    sts.use[26] = 1;
                                }
                                else
                                {
                                    sts.use[26] = 0;
                                }
                                if (Item3.IsChecked4 == true)
                                {
                                    sts.use[27] = 1;
                                }
                                else
                                {
                                    sts.use[27] = 0;
                                }
                                if (Item3.IsChecked5 == true)
                                {
                                    sts.use[28] = 1;
                                }
                                else
                                {
                                    sts.use[28] = 0;
                                }
                                if (Item3.IsChecked6 == true)
                                {
                                    sts.use[29] = 1;
                                }
                                else
                                {
                                    sts.use[29] = 0;
                                }
                                sts.data[24] = double.Parse(Item3.InputText1);
                                sts.data[25] = double.Parse(Item3.InputText2);
                                sts.data[26] = double.Parse(Item3.InputText3);
                                sts.data[27] = double.Parse(Item3.InputText4);
                                sts.data[28] = double.Parse(Item3.InputText5);
                                sts.data[29] = double.Parse(Item3.InputText6);
                                break;
                            case 5:
                                if (Item3.IsChecked1 == true)
                                {
                                    sts.use[30] = 1;
                                }
                                else
                                {
                                    sts.use[30] = 0;
                                }
                                if (Item3.IsChecked2 == true)
                                {
                                    sts.use[31] = 1;
                                }
                                else
                                {
                                    sts.use[31] = 0;
                                }
                                if (Item3.IsChecked3 == true)
                                {
                                    sts.use[32] = 1;
                                }
                                else
                                {
                                    sts.use[32] = 0;
                                }
                                if (Item3.IsChecked4 == true)
                                {
                                    sts.use[33] = 1;
                                }
                                else
                                {
                                    sts.use[33] = 0;
                                }
                                if (Item3.IsChecked5 == true)
                                {
                                    sts.use[34] = 1;
                                }
                                else
                                {
                                    sts.use[34] = 0;
                                }
                                if (Item3.IsChecked6 == true)
                                {
                                    sts.use[35] = 1;
                                }
                                else
                                {
                                    sts.use[35] = 0;
                                }
                                sts.data[30] = double.Parse(Item3.InputText1);
                                sts.data[31] = double.Parse(Item3.InputText2);
                                sts.data[32] = double.Parse(Item3.InputText3);
                                sts.data[33] = double.Parse(Item3.InputText4);
                                sts.data[34] = double.Parse(Item3.InputText5);
                                sts.data[35] = double.Parse(Item3.InputText6);
                                break;
                            default:
                                break;
                        }

                        CSH.Grp03.Cmd10(in sts);
                        CSH.Grp03.SetDistMaskEnable(true); // 追加(2026.8.12yori)
                    }
                }
                else // 距離マスクがOFFの場合
                {
                    CSH.Grp03.SetDistMaskEnable(false);
                }
            }

            // 輝度スライス(2026.8.6yori)
            var Item5 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminanceSlice");
            if (Item5?.InputText15 != null)
            {
                // 標準(2026.8.27yori)
                if (Item5.IsChecked7 == true)
                {
                    sts.bright_slice_std_enable = 1; // 追加(2026.8.29yori)
                    sts.bright_slice_adv_enable = 0; // 追加(2026.8.29yori)
                    sts.bright_slice[0] = ushort.Parse(Item5.InputText12);
                    sts.bright_slice[1] = ushort.Parse(Item5.InputText13);
                    sts.bright_slice[2] = ushort.Parse(Item5.InputText14);
                    CSH.Grp03.SetBrightSliceLevel(sts); // 引数を構造体へ変更(2026.8.29yori)
                }

                // アドバンス
                if (Item5.IsChecked8 == true)
                {
                    sts.bright_slice_std_enable = 0; // 追加(2026.8.29yori)
                    sts.bright_slice_adv_enable = 1; // 追加(2026.8.29yori)
                    sts.bright_slice[0] = ushort.Parse(Item5.InputText15);
                    sts.bright_slice[1] = ushort.Parse(Item5.InputText16);
                    sts.bright_slice[2] = ushort.Parse(Item5.InputText17);
                    CSH.Grp03.SetBrightSliceLevel(sts); // 引数を構造体へ変更(2026.8.29yori)
                }
            }

            // 感度スライス(2026.8.6yori)
            var Item6 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "SensitivitySlice");
            if (Item6?.InputText21 != null)
            {
                // 標準(2026.8.27yori)
                if (Item6.IsChecked9 == true)
                {
                    sts.sens_slice_std_enable = 1; // 追加(2026.8.29yori)
                    sts.sens_slice_adv_enable = 0; // 追加(2026.8.29yori)
                    sts.sens_slice[0] = ushort.Parse(Item6.InputText18);
                    sts.sens_slice[1] = ushort.Parse(Item6.InputText19);
                    sts.sens_slice[2] = ushort.Parse(Item6.InputText20);
                    CSH.Grp03.SetSensSliceLevel(sts); // 引数を構造体へ変更(2026.8.29yori)
                }

                // アドバンス
                if (Item6.IsChecked10 == true)
                {
                    sts.sens_slice_std_enable = 0; // 追加(2026.8.29yori)
                    sts.sens_slice_adv_enable = 1; // 追加(2026.8.29yori)
                    sts.sens_slice[0] = ushort.Parse(Item6.InputText21);
                    sts.sens_slice[1] = ushort.Parse(Item6.InputText22);
                    sts.sens_slice[2] = ushort.Parse(Item6.InputText23);
                    CSH.Grp03.SetSensSliceLevel(sts); // 引数を構造体へ変更(2026.8.29yori)
                }
            }

            // 角度マスク(2026.8.6yori)
            var Item9 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "AngleMask");
            if (Item9?.InputText25 != null)
            {
                if (Item9.SlideSwitchValue8 == 1)
                {
                    CSH.Grp03.Cmd13(Item9.SlideSwitchValue8, double.Parse(Item9.InputText25)); // 引数追加(2026.8.31yori)
                }
                else
                {
                    CSH.Grp03.Cmd13(Item9.SlideSwitchValue8, 90.0); // 追加(2026.8.31yori)
                }
            }

            // エッジマスク(2026.8.6yori)
            var Item11 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "EdgeMask");
            if (Item11?.InputText26 != null)
            {
                CSH.Grp03.Cmd15(int.Parse(Item11.InputText26));
            }

            Parent.CurrentPanel = Panel.None; // 追加(2025.8.21yori)
            CSH.Grp03.Cmd18(); // SubWindow3非表示(2025.11.11yori)
        }

        private void SlideSwitch_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (sender is Slider slider && slider.DataContext is TreeItem treeItem)
            {
                if (treeItem.SlideSwitch)
                {
                    treeItem.SlideSwitch = true;
                    // 距離マスクがONなら各(左右遠近)CheckBoxを有効にする。(2025.8.26yori)
                    // CheckBoxを識別する。(2026.8.6yori)
                    var Item3 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "DistanceMask2");
                    if (Item3?.IsCheckBox1Enabled != null)
                    {
                        Item3.IsCheckBox1Enabled = true;
                    }
                    if (Item3?.IsCheckBox2Enabled != null)
                    {
                        Item3.IsCheckBox2Enabled = true;
                    }
                    if (Item3?.IsCheckBox5Enabled != null)
                    {
                        Item3.IsCheckBox5Enabled = true;
                    }
                    if (Item3?.IsCheckBox6Enabled != null)
                    {
                        Item3.IsCheckBox6Enabled = true;
                    }
                    if (Item3?.IsText1Enabled != null) // 追加(2026.8.12yori)
                    {
                        Item3.IsText1Enabled = true;
                    }
                    if (Item3?.IsText2Enabled != null) // 追加(2026.8.12yori)
                    {
                        Item3.IsText2Enabled = true;
                    }
                    if (Item3?.IsText5Enabled != null) // 追加(2026.8.12yori)
                    {
                        Item3.IsText5Enabled = true;
                    }
                    if (Item3?.IsText6Enabled != null) // 追加(2026.8.12yori)
                    {
                        Item3.IsText6Enabled = true;
                    }
                }
                else
                {
                    treeItem.SlideSwitch = false;
                    // 距離マスクがOFFなら各(左右遠近)CheckBoxを無効にする。(2025.8.26yori)
                    // CheckBoxを識別する。(2026.8.6yori)
                    var Item3 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "DistanceMask2");
                    if (Item3?.IsCheckBox1Enabled != null)
                    {
                        Item3.IsCheckBox1Enabled = false;
                    }
                    if (Item3?.IsCheckBox2Enabled != null)
                    {
                        Item3.IsCheckBox2Enabled = false;
                    }
                    if (Item3?.IsCheckBox5Enabled != null)
                    {
                        Item3.IsCheckBox5Enabled = false;
                    }
                    if (Item3?.IsCheckBox6Enabled != null)
                    {
                        Item3.IsCheckBox6Enabled = false;
                    }
                    if (Item3?.IsText1Enabled != null) // 追加(2026.8.12yori)
                    {
                        Item3.IsText1Enabled = false;
                    }
                    if (Item3?.IsText2Enabled != null) // 追加(2026.8.12yori)
                    {
                        Item3.IsText2Enabled = false;
                    }
                    if (Item3?.IsText5Enabled != null) // 追加(2026.8.12yori)
                    {
                        Item3.IsText5Enabled = false;
                    }
                    if (Item3?.IsText6Enabled != null) // 追加(2026.8.12yori)
                    {
                        Item3.IsText6Enabled = false;
                    }
                }

                if (treeItem.SlideSwitch1)
                {
                    treeItem.SlideSwitch1 = true;
                }
                else
                {
                    treeItem.SlideSwitch1 = false;
                }

                if (treeItem.SlideSwitch2)
                {
                    treeItem.SlideSwitch2 = true;
                }
                else
                {
                    treeItem.SlideSwitch2 = false;
                }

                if (treeItem.SlideSwitch3)
                {
                    treeItem.SlideSwitch3 = true;
                }
                else
                {
                    treeItem.SlideSwitch3 = false;
                }

                if (treeItem.SlideSwitch4)
                {
                    treeItem.SlideSwitch4 = true;
                }
                else
                {
                    treeItem.SlideSwitch4 = false;
                }

                if (treeItem.SlideSwitch5)
                {
                    treeItem.SlideSwitch5 = true;
                }
                else
                {
                    treeItem.SlideSwitch5 = false;
                }

                if (treeItem.SlideSwitch6)
                {
                    treeItem.SlideSwitch6 = true;
                }
                else
                {
                    treeItem.SlideSwitch6 = false;
                }

                // 補間(Xピッチ)
                if (treeItem.SlideSwitch7)
                {
                    treeItem.SlideSwitch7 = true;
                    CSH.Grp03.Cmd09(treeItem.SlideSwitchValue7); // スキャナへの変更はSlider切替時に行う。(2025.9.4yori)
                    // 点間ピッチを画面表示する。(2025.11.6yori)
                    Status02 sts = new Status02();
                    CSH.AppMain.UpDateData02(out sts);
                    this.ViewModel.ApiScanText = Math.Round(sts.pitch[0], 3, MidpointRounding.AwayFromZero).ToString("F3"); // 四捨五入されるようsts.pitch[0].ToString("F3")から修正(2026.1.28yori)
                }
                else
                {
                    treeItem.SlideSwitch7 = false;
                    CSH.Grp03.Cmd09(treeItem.SlideSwitchValue7); // スキャナへの変更はSlider切替時に行う。(2025.9.4yori)
                    // 点間ピッチを画面表示する。(2025.11.6yori)
                    Status02 sts = new Status02();
                    CSH.AppMain.UpDateData02(out sts);
                    this.ViewModel.ApiScanText = Math.Round(sts.pitch[0], 3, MidpointRounding.AwayFromZero).ToString("F3"); // 四捨五入されるようsts.pitch[0].ToString("F3")から修正(2026.1.28yori)
                }

                // 角度マスク
                if (treeItem.SlideSwitch8)
                {
                    treeItem.SlideSwitch8 = true;
                    // 角度マスクONの場合、TextBoxを編集できるよう有効化する。(2026.8.31yori)
                    var Item9 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "AngleMask");
                    if (Item9?.InputText25 != null)
                    {
                        Item9.IsAngleMaskEnabled = true;
                    }
                }
                else
                {
                    treeItem.SlideSwitch8 = false;
                    // 角度マスクOFFの場合、TextBoxを編集できないよう無効化する。(2026.8.6yori)
                    var Item9 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "AngleMask");
                    if (Item9?.InputText25 != null)
                    {
                        Item9.IsAngleMaskEnabled = false;
                    }
                }

                if (treeItem.SlideSwitch9)
                {
                    treeItem.SlideSwitch9 = true;
                }
                else
                {
                    treeItem.SlideSwitch9 = false;
                }
            }
        }

        // スキャナ計測モードを変更する。(2025.8.12yori)
        private void ComboBox_SelectionChanged_Mode(object sender, SelectionChangedEventArgs e)
        {
            CSH.Grp03.Cmd06(ViewModel.ApiScanIndex1);
            Status02 sts = new Status02();
            CSH.AppMain.UpDateData02(out sts);
            // 点間ピッチは計測モードによって異なるため、画面表示を変更する。(2025.11.6yori)
            this.ViewModel.ApiScanText = Math.Round(sts.pitch[0], 3, MidpointRounding.AwayFromZero).ToString("F3"); // 四捨五入されるようsts.pitch[0].ToString("F3")から修正(2026.1.28yori)
            // 距離マスクは計測モードによって異なるため、画面表示を変更する。(2026.8.8yori)
            var Item3 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "DistanceMask2");
            if (Item3?.IsChecked1 != null)
            {
                switch (sts.mode)
                {
                    case 0:
                        if (sts.use[0] == 1)
                        {
                            Item3.IsChecked1 = true;
                        }
                        else
                        {
                            Item3.IsChecked1 = false;
                        }
                        if (sts.use[1] == 1)
                        {
                            Item3.IsChecked2 = true;
                        }
                        else
                        {
                            Item3.IsChecked2 = false;
                        }
                        if (sts.use[2] == 1)
                        {
                            Item3.IsChecked3 = true;
                        }
                        else
                        {
                            Item3.IsChecked3 = false;
                        }
                        if (sts.use[3] == 1)
                        {
                            Item3.IsChecked4 = true;
                        }
                        else
                        {
                            Item3.IsChecked4 = false;
                        }
                        if (sts.use[4] == 1)
                        {
                            Item3.IsChecked5 = true;
                        }
                        else
                        {
                            Item3.IsChecked5 = false;
                        }
                        if (sts.use[5] == 1)
                        {
                            Item3.IsChecked6 = true;
                        }
                        else
                        {
                            Item3.IsChecked6 = false;
                        }
                        Item3.InputText1 = sts.data[0].ToString("F1");
                        Item3.InputText2 = sts.data[1].ToString("F1");
                        Item3.InputText3 = sts.data[2].ToString("F1");
                        Item3.InputText4 = sts.data[3].ToString("F1");
                        Item3.InputText5 = sts.data[4].ToString("F1");
                        Item3.InputText6 = sts.data[5].ToString("F1");
                        break;
                    case 1:
                        if (sts.use[6] == 1)
                        {
                            Item3.IsChecked1 = true;
                        }
                        else
                        {
                            Item3.IsChecked1 = false;
                        }
                        if (sts.use[7] == 1)
                        {
                            Item3.IsChecked2 = true;
                        }
                        else
                        {
                            Item3.IsChecked2 = false;
                        }
                        if (sts.use[8] == 1)
                        {
                            Item3.IsChecked3 = true;
                        }
                        else
                        {
                            Item3.IsChecked3 = false;
                        }
                        if (sts.use[9] == 1)
                        {
                            Item3.IsChecked4 = true;
                        }
                        else
                        {
                            Item3.IsChecked4 = false;
                        }
                        if (sts.use[10] == 1)
                        {
                            Item3.IsChecked5 = true;
                        }
                        else
                        {
                            Item3.IsChecked5 = false;
                        }
                        if (sts.use[11] == 1)
                        {
                            Item3.IsChecked6 = true;
                        }
                        else
                        {
                            Item3.IsChecked6 = false;
                        }
                        Item3.InputText1 = sts.data[6].ToString("F1");
                        Item3.InputText2 = sts.data[7].ToString("F1");
                        Item3.InputText3 = sts.data[8].ToString("F1");
                        Item3.InputText4 = sts.data[9].ToString("F1");
                        Item3.InputText5 = sts.data[10].ToString("F1");
                        Item3.InputText6 = sts.data[11].ToString("F1");
                        break;
                    case 2:
                        if (sts.use[12] == 1)
                        {
                            Item3.IsChecked1 = true;
                        }
                        else
                        {
                            Item3.IsChecked1 = false;
                        }
                        if (sts.use[13] == 1)
                        {
                            Item3.IsChecked2 = true;
                        }
                        else
                        {
                            Item3.IsChecked2 = false;
                        }
                        if (sts.use[14] == 1)
                        {
                            Item3.IsChecked3 = true;
                        }
                        else
                        {
                            Item3.IsChecked3 = false;
                        }
                        if (sts.use[15] == 1)
                        {
                            Item3.IsChecked4 = true;
                        }
                        else
                        {
                            Item3.IsChecked4 = false;
                        }
                        if (sts.use[16] == 1)
                        {
                            Item3.IsChecked5 = true;
                        }
                        else
                        {
                            Item3.IsChecked5 = false;
                        }
                        if (sts.use[17] == 1)
                        {
                            Item3.IsChecked6 = true;
                        }
                        else
                        {
                            Item3.IsChecked6 = false;
                        }
                        Item3.InputText1 = sts.data[12].ToString("F1");
                        Item3.InputText2 = sts.data[13].ToString("F1");
                        Item3.InputText3 = sts.data[14].ToString("F1");
                        Item3.InputText4 = sts.data[15].ToString("F1");
                        Item3.InputText5 = sts.data[16].ToString("F1");
                        Item3.InputText6 = sts.data[17].ToString("F1");
                        break;
                    case 3:
                        if (sts.use[18] == 1)
                        {
                            Item3.IsChecked1 = true;
                        }
                        else
                        {
                            Item3.IsChecked1 = false;
                        }
                        if (sts.use[19] == 1)
                        {
                            Item3.IsChecked2 = true;
                        }
                        else
                        {
                            Item3.IsChecked2 = false;
                        }
                        if (sts.use[20] == 1)
                        {
                            Item3.IsChecked3 = true;
                        }
                        else
                        {
                            Item3.IsChecked3 = false;
                        }
                        if (sts.use[21] == 1)
                        {
                            Item3.IsChecked4 = true;
                        }
                        else
                        {
                            Item3.IsChecked4 = false;
                        }
                        if (sts.use[22] == 1)
                        {
                            Item3.IsChecked5 = true;
                        }
                        else
                        {
                            Item3.IsChecked5 = false;
                        }
                        if (sts.use[23] == 1)
                        {
                            Item3.IsChecked6 = true;
                        }
                        else
                        {
                            Item3.IsChecked6 = false;
                        }
                        Item3.InputText1 = sts.data[18].ToString("F1");
                        Item3.InputText2 = sts.data[19].ToString("F1");
                        Item3.InputText3 = sts.data[20].ToString("F1");
                        Item3.InputText4 = sts.data[21].ToString("F1");
                        Item3.InputText5 = sts.data[22].ToString("F1");
                        Item3.InputText6 = sts.data[23].ToString("F1");
                        break;
                    case 4:
                        if (sts.use[24] == 1)
                        {
                            Item3.IsChecked1 = true;
                        }
                        else
                        {
                            Item3.IsChecked1 = false;
                        }
                        if (sts.use[25] == 1)
                        {
                            Item3.IsChecked2 = true;
                        }
                        else
                        {
                            Item3.IsChecked2 = false;
                        }
                        if (sts.use[26] == 1)
                        {
                            Item3.IsChecked3 = true;
                        }
                        else
                        {
                            Item3.IsChecked3 = false;
                        }
                        if (sts.use[27] == 1)
                        {
                            Item3.IsChecked4 = true;
                        }
                        else
                        {
                            Item3.IsChecked4 = false;
                        }
                        if (sts.use[28] == 1)
                        {
                            Item3.IsChecked5 = true;
                        }
                        else
                        {
                            Item3.IsChecked5 = false;
                        }
                        if (sts.use[29] == 1)
                        {
                            Item3.IsChecked6 = true;
                        }
                        else
                        {
                            Item3.IsChecked6 = false;
                        }
                        Item3.InputText1 = sts.data[24].ToString("F1");
                        Item3.InputText2 = sts.data[25].ToString("F1");
                        Item3.InputText3 = sts.data[26].ToString("F1");
                        Item3.InputText4 = sts.data[27].ToString("F1");
                        Item3.InputText5 = sts.data[28].ToString("F1");
                        Item3.InputText6 = sts.data[29].ToString("F1");
                        break;
                    case 5:
                        if (sts.use[30] == 1)
                        {
                            Item3.IsChecked1 = true;
                        }
                        else
                        {
                            Item3.IsChecked1 = false;
                        }
                        if (sts.use[31] == 1)
                        {
                            Item3.IsChecked2 = true;
                        }
                        else
                        {
                            Item3.IsChecked2 = false;
                        }
                        if (sts.use[32] == 1)
                        {
                            Item3.IsChecked3 = true;
                        }
                        else
                        {
                            Item3.IsChecked3 = false;
                        }
                        if (sts.use[33] == 1)
                        {
                            Item3.IsChecked4 = true;
                        }
                        else
                        {
                            Item3.IsChecked4 = false;
                        }
                        if (sts.use[34] == 1)
                        {
                            Item3.IsChecked5 = true;
                        }
                        else
                        {
                            Item3.IsChecked5 = false;
                        }
                        if (sts.use[35] == 1)
                        {
                            Item3.IsChecked6 = true;
                        }
                        else
                        {
                            Item3.IsChecked6 = false;
                        }
                        Item3.InputText1 = sts.data[30].ToString("F1");
                        Item3.InputText2 = sts.data[31].ToString("F1");
                        Item3.InputText3 = sts.data[32].ToString("F1");
                        Item3.InputText4 = sts.data[33].ToString("F1");
                        Item3.InputText5 = sts.data[34].ToString("F1");
                        Item3.InputText6 = sts.data[35].ToString("F1");
                        break;
                    default:
                        break;
                }
            }
            // エッジマスク点数は計測モードによって異なるため、画面表示を変更する。(2025.8.27yori)
            var Item11 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "EdgeMask");
            if (Item11?.InputText26 != null)
            {
                Item11.InputText26 = sts.edge.ToString();
            }
        }

        // 点間ピッチの値を切り替える。(2025.8.11yori)
        private void ComboBox_SelectionChanged_Pitch(object sender, SelectionChangedEventArgs e)
        {
            Status02 sts = new Status02();
            CSH.AppMain.UpDateData02(out sts);
            //this.ViewModel.ApiScanText = sts.pitch[this.ViewModel.ApiScanIndex2].ToString("F3");
        }

        // 感度を変更する。(2025.8.21yori)
        private void ComboBox_SelectionChanged_Sens(object sender, SelectionChangedEventArgs e)
        {
            var Item1 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "Sensitivity");
            if (Item1?.OptionIndex1 != null)
            {
                CSH.Grp03.Cmd07(Item1.OptionIndex1);
            }
            // エッジマスク点数は感度によって異なるため、画面表示を変更する。(2028.8.27yori)
            Status02 sts = new Status02();
            CSH.AppMain.UpDateData02(out sts);
            var Item11 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "EdgeMask");
            if (Item11?.InputText26 != null)
            {
                Item11.InputText26 = sts.edge.ToString();
            }
        }

        // 輝度マスクを変更する。(2026.9.1yori)
        private void ComboBox_SelectionChanged_LuminosityMask(object sender, SelectionChangedEventArgs e)
        {
            var Item = this.ViewModel.TreeItems.FirstOrDefault(x => x.UIType == "LuminosityMask");
            if (Item?.OptionIndex2 != null)
            {
                switch (Item.OptionIndex2)
                {
                    case 0: // なし
                        var Item0 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminosityMask2");
                        if (Item0?.TextBlock1Opacity != null)
                        {
                            Item0.TextBlock1Opacity = 0.25;
                        }
                        if (Item0?.TextBlock2Opacity != null)
                        {
                            Item0.TextBlock2Opacity = 0.25;
                        }
                        if (Item0?.IsTextBox1Enabled != null)
                        {
                            Item0.IsTextBox1Enabled = false;
                        }
                        if (Item0?.IsSliderEnabled != null)
                        {
                            Item0.IsSliderEnabled = false;
                        }
                        if (Item0?.PlotView1Opacity != null)
                        {
                            Item0.PlotView1Opacity = 0.25;
                        }
                        break;
                    case 1: // 手動
                        var Item1 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminosityMask2");
                        if (Item1?.TextBlock1Opacity != null)
                        {
                            Item1.TextBlock1Opacity = 0.25;
                        }
                        if (Item1?.TextBlock2Opacity != null)
                        {
                            Item1.TextBlock2Opacity = 1.0;
                        }
                        if (Item1?.IsTextBox1Enabled != null)
                        {
                            Item1.IsTextBox1Enabled = false;
                        }
                        if (Item1?.IsSliderEnabled != null)
                        {
                            Item1.IsSliderEnabled = true;
                        }
                        if (Item1?.PlotView1Opacity != null)
                        {
                            Item1.PlotView1Opacity = 1.0;
                        }
                        break;
                    case 2: // 自動(1パッチ毎)
                        var Item2 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminosityMask2");
                        if (Item2?.TextBlock1Opacity != null)
                        {
                            Item2.TextBlock1Opacity = 1.0;
                        }
                        if (Item2?.TextBlock2Opacity != null)
                        {
                            Item2.TextBlock2Opacity = 1.0;
                        }
                        if (Item2?.IsTextBox1Enabled != null)
                        {
                            Item2.IsTextBox1Enabled = true;
                        }
                        if (Item2?.IsSliderEnabled != null)
                        {
                            Item2.IsSliderEnabled = true;
                        }
                        if (Item2?.PlotView1Opacity != null)
                        {
                            Item2.PlotView1Opacity = 1.0;
                        }
                        break;
                    case 3: // 自動(スタート毎)
                        var Item3 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminosityMask2");
                        if (Item3?.TextBlock1Opacity != null)
                        {
                            Item3.TextBlock1Opacity = 1.0;
                        }
                        if (Item3?.TextBlock2Opacity != null)
                        {
                            Item3.TextBlock2Opacity = 1.0;
                        }
                        if (Item3?.IsTextBox1Enabled != null)
                        {
                            Item3.IsTextBox1Enabled = true;
                        }
                        if (Item3?.IsSliderEnabled != null)
                        {
                            Item3.IsSliderEnabled = true;
                        }
                        if (Item3?.PlotView1Opacity != null)
                        {
                            Item3.PlotView1Opacity = 1.0;
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        // ガイドレーザーパワーを変更する。(2025.8.21yori)
        private void ComboBox_SelectionChanged_Guide(object sender, SelectionChangedEventArgs e)
        {
            // スキャナへの変更はComboBox変更時に行う。(2025.9.4yori)
            var Item7 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "GuideLaserPower");
            if (Item7?.OptionIndex3 != null)
            {
                CSH.Grp03.Cmd08(Item7.OptionIndex3);
            }
        }

        // 2ピークマスクを変更する。(2025.8.25yori)
        private void ComboBox_SelectionChanged_TwoPeak(object sender, SelectionChangedEventArgs e)
        {
            var Item10 = this.ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "TwoPeakMask");
            if (Item10?.OptionIndex4 != null) // 追加(2025.8.26yori)
            {
                switch (Item10.OptionIndex4)
                {
                    case 0:
                        Item10.ImageSource = "Image/Invalid data.png";
                        break;
                    case 1:
                        Item10.ImageSource = "Image/Valid data Wide waveform.png";
                        break;
                    case 2:
                        Item10.ImageSource = "Image/Valid data Near distance.png";
                        break;
                    default:
                        break;
                }
                CSH.Grp03.Cmd14(Item10.OptionIndex4);
            }
        }

        // ツリーの展開を無効化(2025.11.7yori)
        private void TreeViewItem_Expanded(object sender, RoutedEventArgs e)
        {
            // 展開されたアイテムを取得
            if (e.OriginalSource is TreeViewItem item)
            {
                // バインドされているデータ
                if (item.DataContext is TreeItem treeItem)
                {
                    // 特定のアイテムの展開を無効化
                    if (//treeItem.Name == VecApp.Properties.Resources.String122 ||   // 輝度マスク有効(2026.8.13yori)
                        //treeItem.Name == VecApp.Properties.Resources.String127 ||   // 距離マスク有効(2026.8.6yori)
                        //treeItem.Name == VecApp.Properties.Resources.String128 ||   // 点群補正/フィルタ有効(2026.8.6yori)
                        //treeItem.Name == VecApp.Properties.Resources.String129 ||   // 輝度スライス有効(2026.8.6yori)
                        //treeItem.Name == VecApp.Properties.Resources.String130 ||   // 感度スライス有効(2026.8.6yori)
                        //treeItem.Name == VecApp.Properties.Resources.String136 ||   // 角度マスク有効(2026.8.6yori)
                        //treeItem.Name == VecApp.Properties.Resources.String137 ||   // 2ピークマスク有効(2026.8.6yori)
                        //treeItem.Name == VecApp.Properties.Resources.String141 ||   // エッジマスク有効(2026.8.6yori)
                        treeItem.Name == VecApp.Properties.Resources.String142)     // メモ
                    {
                        // 展開をキャンセル
                        item.IsExpanded = false;

                        // イベントを処理済みに設定
                        e.Handled = true;
                    }
                }
            }
        }

        // エッジマスク点数は、整数の0～6のみ入力可能にする。(2026.8.31yori)
        private void TextBox_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            e.Handled = !e.Text.All(c => c >= '0' && c <= '6');
        }
    }
}