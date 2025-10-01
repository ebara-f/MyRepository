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

            // MainWindow.xaml.csから移動(2025.8.21yori)
            Status02 sts = new Status02();
            CSH.AppMain.UpDateData02(out sts);

            // 計測モード(2025.8.11yori)
            ViewModel.ApiScanItems1.Clear();
            ViewModel.ApiScanItems1.Insert(0, sts.mode0_info);
            ViewModel.ApiScanItems1.Insert(1, sts.mode1_info);
            ViewModel.ApiScanItems1.Insert(2, sts.mode2_info);
            ViewModel.ApiScanItems1.Insert(3, sts.mode3_info);
            ViewModel.ApiScanItems1.Insert(4, sts.mode4_info);
            ViewModel.ApiScanItems1.Insert(5, sts.mode5_info);
            ViewModel.ApiScanIndex1 = sts.mode;

            // 感度(2025.8.18yori)
            var Item1 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "Sensitivity");
            if (Item1?.Options != null)
            {
                Item1.Options.Clear();
                if (sts.sens_use[0] == 1) Item1.Options.Insert(0, sts.sens_name0);
                if (sts.sens_use[1] == 1) Item1.Options.Insert(1, sts.sens_name1);
                if (sts.sens_use[2] == 1) Item1.Options.Insert(2, sts.sens_name2);
                if (sts.sens_use[3] == 1) Item1.Options.Insert(3, sts.sens_name3);
                if (sts.sens_use[4] == 1) Item1.Options.Insert(4, sts.sens_name4);
                Item1.SelectedOption = "Normal";
            }

            // 距離マスク(2025.8.22yori) // Item4→Item3へ変更(ViewModelの番号と合わせる。)(2025.8.26yori)
            var Item3 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "DistanceMask2");
            if (Item3?.IsChecked1 != null) // 追加(2025.8.26yori)
            {
                switch (sts.mode)
                {
                    case 0:
                        if (sts.use[0] == 1) Item3.IsChecked1 = true;
                        if (sts.use[1] == 1) Item3.IsChecked2 = true;
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
            var parent3 = ViewModel.TreeItems.FirstOrDefault(x => x.UIType == "DistanceMask1");
            if (parent3?.SlideSwitchValue != null) // 追加(2025.8.26yori)
            {
                if (parent3.SlideSwitchValue == 0)
                {
                    Item3.IsCheckBoxEnabled = false; // 距離マスクがOFFなら各(左右遠近)CheckBoxを無効にする。(2025.8.26yori)
                }
            }

            // 輝度スライス(2025.8.23yori)
            var Item5 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminanceSlice");
            if (Item5?.InputText12 != null) // 追加(2025.8.26yori)
            {
                // スタンダード
                Item5.InputText12 = "24528";
                Item5.InputText13 = "24528";
                Item5.InputText14 = "24528";
                // アドバンス
                Item5.InputText15 = sts.brightslice[0].ToString();
                Item5.InputText16 = sts.brightslice[1].ToString();
                Item5.InputText17 = sts.brightslice[2].ToString();
            }

            // 感度スライス(2025.8.23yori)
            var Item6 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "SensitivitySlice");
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
            var Item7 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "GuideLaserPower");
            if (Item7?.Options3 != null)
            {
                Item7.Options3.Clear();
                Item7.Options3.Insert(0, "低");
                Item7.Options3.Insert(1, "中");
                Item7.Options3.Insert(2, "高");
                Item7.OptionIndex3 = sts.power;
            }

            // 角度マスク(2025.8.24yori)
            var Item9 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "AngleMask");
            if (Item9?.InputText25 != null) // 追加(2025.8.26yori)
            {
                Item9.InputText25 = sts.angle.ToString("F1");
            }

            // 2ピークマスク(2028.8.25yori)
            var Item10 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "TwoPeakMask");
            if (Item10?.OptionIndex4 != null) // 追加(2025.8.26yori)
            {
                Item10.OptionIndex4 = sts.two_peak;
            }

            // エッジマスク(2028.8.25yori)
            var Item11 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "EdgeMask");
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
            if (SartStopButton.Content.ToString() == "スタート")
            {
                Status02 sts = new Status02();
                CSH.AppMain.UpDateData02(out sts); // 追加(2025.8.25yori)

                // 画面からスキャナパラメータ取得し、スキャナに設定する。

                // 感度(2025.8.26yori)
                // スキャナへの変更はComboBox変更時に行う。(2025.9.4yori)

                // 距離マスク(2025.8.23yori)
                var parent3 = ViewModel.TreeItems.FirstOrDefault(x => x.UIType == "DistanceMask1");
                if (parent3?.SlideSwitchValue != null) // 追加(2025.8.26yori)
                {
                    if (parent3.SlideSwitchValue == 1) // 距離マスクがオンの場合
                    {
                        // Item4→Item3へ変更(ViewModelの番号と合わせる。)(2025.8.26yori)
                        var Item3 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "DistanceMask2");
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
                            CSH.AppMain.UpDateData02_Write(in sts);
                            CSH.Grp03.Cmd10();
                        }
                    }
                }

                // 輝度スライス(2025.8.24yori)
                var Item5 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminanceSlice");
                if (Item5?.InputText15 != null) // 追加(2025.8.26yori)
                {
                    sts.brightslice[0] = ushort.Parse(Item5.InputText15);
                    sts.brightslice[1] = ushort.Parse(Item5.InputText16);
                    sts.brightslice[2] = ushort.Parse(Item5.InputText17);
                    CSH.AppMain.UpDateData02_Write(in sts);
                    if (Item5.IsChecked8 == true) CSH.Grp03.Cmd11();
                }

                // 感度スライス(2025.8.24yori)
                var Item6 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "SensitivitySlice");
                if (Item6?.InputText21 != null) // 追加(2025.8.26yori)
                {
                    sts.sens_slice[0] = ushort.Parse(Item6.InputText21);
                    sts.sens_slice[1] = ushort.Parse(Item6.InputText22);
                    sts.sens_slice[2] = ushort.Parse(Item6.InputText23);
                    CSH.AppMain.UpDateData02_Write(in sts);
                    if (Item6.IsChecked10 == true) CSH.Grp03.Cmd12();
                }

                // 角度マスク(2025.8.24yori)
                var Item9 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "AngleMask");
                if (Item9?.InputText25 != null) // 追加(2025.8.26yori)
                {
                    sts.angle = double.Parse(Item9.InputText25);
                    CSH.AppMain.UpDateData02_Write(in sts);
                    if (Item9.SlideSwitchValue8 == 1) CSH.Grp03.Cmd13();
                }

                // エッジマスク(2028.8.25yori)
                var Item11 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "EdgeMask");
                if (Item11?.InputText26 != null) // 追加(2025.8.26yori)
                {
                    sts.edge = int.Parse(Item11.InputText26);
                    CSH.AppMain.UpDateData02_Write(in sts);
                    CSH.Grp03.Cmd15();
                }
                
                CSH.Grp03.Cmd01(); // スキャンスタート
                SartStopButton.Content = "ストップ";
                ScanMode.IsEnabled = false; // 計測モードComboBox無効
                Pitch.IsEnabled = false; // 点間ピッチComboBox無効
            }
            else
            {
                CSH.Grp03.Cmd02(); // スキャンストップ
                SartStopButton.Content = "スタート";
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
            MessageBoxResult result;
            result = MessageBox.Show("パラメータを初期化しますか？", "BeakMater Plug-in SoftWare(beta)", MessageBoxButton.YesNo, MessageBoxImage.Information);
            switch (result)
            {
                case MessageBoxResult.Yes:
                    // スキャナパラメータを初期値へ設定する。(2025.8.26yori)
                    // 感度
                    var Item = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "Sensitivity");
                    if (Item?.OptionIndex1 != null)
                    {
                        Item.OptionIndex1 = 0; // 感度をNormalに表示
                    }
                    
                    // 距離マスク
                    var parent3 = ViewModel.TreeItems.FirstOrDefault(x => x.UIType == "DistanceMask1");
                    if (parent3?.SlideSwitchValue != null)
                    {
                        parent3.SlideSwitchValue = 0;
                    }
                    var Item3 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "DistanceMask2");
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
                    var Item5 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "LuminanceSlice");
                    if (Item5?.InputText15 != null)
                    {
                        // アドバンス
                        Item5.InputText15 = "24528";
                        Item5.InputText16 = "24528";
                        Item5.InputText17 = "24528";
                    }

                    // 感度スライス
                    var Item6 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "SensitivitySlice");
                    if (Item6?.InputText21 != null)
                    {
                        // アドバンス
                        Item6.InputText21 = "3276";
                        Item6.InputText22 = "1200";
                        Item6.InputText23 = "3276";
                    }

                    // ガイドレーザーパワー
                    var Item7 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "GuideLaserPower");
                    if (Item7?.Options3 != null)
                    {
                        Item7.OptionIndex3 = 1; // ガイドレーザーパワーを中に表示
                    }

                    // 補間(Xピッチ)
                    var Item8 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "Interpolation");
                    if (Item8?.Options3 != null)
                    {
                        Item8.SlideSwitchValue7 = 0;
                    }

                    // 角度マスク
                    var Item9 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "AngleMask");
                    if (Item9?.InputText25 != null)
                    {
                        Item9.InputText25 = "70.0";
                    }

                    // 2ピークマスク
                    var Item10 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "TwoPeakMask");
                    if (Item10?.OptionIndex4 != null)
                    {
                        Item10.OptionIndex4 = 0; // 2ピークマスクをデータ無効に表示
                    }

                    // エッジマスク
                    var Item11 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "EdgeMask");
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
            Parent.CurrentPanel = Panel.None; // 追加(2025.8.21yori)
        }

        private void SlideSwitch_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (sender is Slider slider && slider.DataContext is TreeItem treeItem)
            {
                if (treeItem.SlideSwitch)
                {
                    treeItem.SlideSwitch = true;
                    // 距離マスクがONなら各(左右遠近)CheckBoxを有効にする。(2025.8.26yori)
                    var Item3 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "DistanceMask2");
                    if (Item3?.IsCheckBoxEnabled != null)
                    {
                        Item3.IsCheckBoxEnabled = true;
                    }
                }
                else
                {
                    treeItem.SlideSwitch = false;
                    // 距離マスクがOFFなら各(左右遠近)CheckBoxを無効にする。(2025.8.26yori)
                    var Item3 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "DistanceMask2");
                    if (Item3?.IsCheckBoxEnabled != null)
                    {
                        Item3.IsCheckBoxEnabled = false;
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
                }
                else
                {
                    treeItem.SlideSwitch7 = false;
                    CSH.Grp03.Cmd09(treeItem.SlideSwitchValue7); // スキャナへの変更はSlider切替時に行う。(2025.9.4yori)
                }

                if (treeItem.SlideSwitch8)
                {
                    treeItem.SlideSwitch8 = true;
                }
                else
                {
                    treeItem.SlideSwitch8 = false;
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
            // エッジマスク点数は計測モードによって異なるため、画面表示を変更する。(2028.8.27yori)
            Status02 sts = new Status02();
            CSH.AppMain.UpDateData02(out sts);
            var Item11 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "EdgeMask");
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
            //ViewModel.ApiScanText = sts.pitch[ViewModel.ApiScanIndex2].ToString("F3");
        }

        // 感度を変更する。(2025.8.21yori)
        private void ComboBox_SelectionChanged_Sens(object sender, SelectionChangedEventArgs e)
        {
            var Item1 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "Sensitivity");
            if (Item1?.OptionIndex1 != null)
            {
                CSH.Grp03.Cmd07(Item1.OptionIndex1);
            }
            // エッジマスク点数は感度によって異なるため、画面表示を変更する。(2028.8.27yori)
            Status02 sts = new Status02();
            CSH.AppMain.UpDateData02(out sts);
            var Item11 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "EdgeMask");
            if (Item11?.InputText26 != null)
            {
                Item11.InputText26 = sts.edge.ToString();
            }
        }

        // ガイドレーザーパワーを変更する。(2025.8.21yori)
        private void ComboBox_SelectionChanged_Guide(object sender, SelectionChangedEventArgs e)
        {
            // スキャナへの変更はComboBox変更時に行う。(2025.9.4yori)
            var Item7 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "GuideLaserPower");
            if (Item7?.OptionIndex3 != null)
            {
                CSH.Grp03.Cmd08(Item7.OptionIndex3);
            }
        }

        // 2ピークマスクを変更する。(2025.8.25yori)
        private void ComboBox_SelectionChanged_TwoPeak(object sender, SelectionChangedEventArgs e)
        {
            var Item10 = ViewModel.TreeItems.SelectMany(x => x.Children).FirstOrDefault(x => x.UIType == "TwoPeakMask");
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
    }
}