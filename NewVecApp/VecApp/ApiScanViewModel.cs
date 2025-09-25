using OxyPlot;
using OxyPlot.Annotations;
using OxyPlot.Axes;
using OxyPlot.Series;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using VecApp.Properties;

namespace VecApp
{
    public class ApiScanViewModel : INotifyPropertyChanged
    {

        public ObservableCollection<string> ApiScanItems1 { get; set; }
        public ObservableCollection<string> ApiScanItems2 { get; set; }

        public ObservableCollection<TreeItem> TreeItems { get; set; }

        public ApiScanViewModel()
        {
            ApiScanItems1 = new ObservableCollection<string> { "E  : 50mm-0.062mm-85Hz" }; // "D :100mm-0.125mm-77Hz"から変更(2025.8.27yori)
            ApiScanItems2 = new ObservableCollection<string> { "1/1", "1/2", "1/3", "1/4", "1/5", "1/6", "1/7", "1/8", "1/9", "1/10"};
            ApiScanIndex1 = 0;
            ApiScanIndex2 = 0;
            IsSensorParameterVisible = Visibility.Collapsed;

            TreeItems = CreateTreeItems();
        }

        private Visibility _isSensorParameterVisible = Visibility.Collapsed;
        public Visibility IsSensorParameterVisible
        {
            get => _isSensorParameterVisible;
            set
            {
                if (_isSensorParameterVisible != value)
                {
                    _isSensorParameterVisible = value;
                    OnPropertyChanged(nameof(IsSensorParameterVisible));
                }
            }
        }

        private int _apiScanIndex1;
        public int ApiScanIndex1
        {
            get => _apiScanIndex1;
            set
            {
                if (_apiScanIndex1 != value)
                {
                    _apiScanIndex1 = value;
                    OnPropertyChanged(nameof(ApiScanIndex1));
                }
            }
        }

        private int _apiScanIndex2;
        public int ApiScanIndex2
        {
            get => _apiScanIndex2;
            set
            {
                if (_apiScanIndex2 != value)
                {
                    _apiScanIndex2 = value;
                    OnPropertyChanged(nameof(ApiScanIndex2));
                }
            }
        }

        private string _apiScanText;
        public string ApiScanText
        {
            get => _apiScanText;
            set
            {
                if (_apiScanText != value)
                {
                    _apiScanText = value;
                    OnPropertyChanged(nameof(ApiScanText));
                }
            }
        }

        //// 追加(2025.9.3yori)
        // Buttonの有効無効を設定する。
        private bool _isButtonEnabled = false; // 初期状態は無効

        public bool IsButtonEnabled
        {
            get { return _isButtonEnabled; }
            set
            {
                if (_isButtonEnabled != value)
                {
                    _isButtonEnabled = value;
                    OnPropertyChanged(nameof(IsButtonEnabled));
                }
            }
        }
        ////

        private ObservableCollection<TreeItem> CreateTreeItems()
        {
            var items = new ObservableCollection<TreeItem>();

            var parent1 = new TreeItem { Name = Resources.String121 };

            parent1.Children.Add(new TreeItem
            {
                UIType = "Sensitivity",
                Options = new ObservableCollection<string> { Resources.String145, Resources.String146 }, // "Low"削除(2025.8.21yori)
                SelectedOption = Resources.String145,
                OptionIndex1 = 0 // 追加(2025.8.21yori)
            });
            items.Add(parent1);

            var parent2 = new TreeItem
            {
                Name = Resources.String122,
                UIType = "LuminosityMask",
                Options2 = new ObservableCollection<string> { Resources.String123, Resources.String124, Resources.String125, Resources.String126 },
                SelectedOption2 = Resources.String125
            };
            parent2.Children.Add(new TreeItem
            {
                UIType = "LuminosityMask2",
                SlideSwitchValue9 = 0,
                SlideText9 = Resources.String143,
                InputText32 = "0",
                InputText33 = "0",
                PlotModel1 = CreatePlotModel1(),
                PlotModel2 = CreatePlotModel2(),
            });
            items.Add(parent2);

            var parent3 = new TreeItem
            {
                Name = Resources.String127,
                UIType = "DistanceMask1",
                SlideSwitchValue = 0,
                SlideText = Resources.String143,
            };
            parent3.Children.Add(new TreeItem
            {
                XName = "X",
                YName = "Y",
                ZName = "Z",
                UIType = "DistanceMask2",
                InputText1 = "0.0", // 追加(2025.8.22yori)
                InputText2 = "0.0", // 追加(2025.8.22yori)
                InputText3 = "0.0", // 追加(2025.8.22yori)
                InputText4 = "0.0", // 追加(2025.8.22yori)
                InputText5 = "0.0", // 追加(2025.8.22yori)
                InputText6 = "0.0", // 追加(2025.8.22yori)
            });
            items.Add(parent3);

            var parent4 = new TreeItem { Name = Resources.String128 };
            parent4.Children.Add(new TreeItem {
                UIType = "PointCloudCorrection",
                SlideSwitchValue1 = 0,
                SlideText1 = Resources.String143,
                SlideSwitchValue2 = 0,
                SlideText2 = Resources.String143,
                SlideSwitchValue3 = 0,
                SlideText3 = Resources.String143,
                SlideSwitchValue4 = 0,
                SlideText4 = Resources.String143,
                SlideSwitchValue5 = 0,
                SlideText5 = Resources.String143,
                SlideSwitchValue6 = 0,
                SlideText6 = Resources.String143,
            });
            items.Add(parent4);

            var parent5 = new TreeItem { Name = Resources.String129 };
            parent5.Children.Add(new TreeItem
            {
                UIType = "LuminanceSlice",
                IsChecked7 = true,
            });
            items.Add(parent5);

            var parent6 = new TreeItem { Name = Resources.String130 };
            parent6.Children.Add(new TreeItem
            {
                UIType = "SensitivitySlice",
                IsChecked9 = true,
            });
            items.Add(parent6);

            var parent7 = new TreeItem { Name = Resources.String131 };
            parent7.Children.Add(new TreeItem
            {
                UIType = "GuideLaserPower",
                Options3 = new ObservableCollection<string> { Resources.String132, Resources.String133, Resources.String134 },
                SelectedOption3 = Resources.String134,
                OptionIndex3 = 2 // 追加(2025.8.21yori)
            });
            items.Add(parent7);

            var parent8 = new TreeItem { Name = Resources.String135 };
            parent8.Children.Add(new TreeItem
            {
                UIType = "Interpolation",
                SlideSwitchValue7 = 0,
                SlideText7 = Resources.String143,
            });
            items.Add(parent8);

            var parent9 = new TreeItem { Name = Resources.String136 };
            parent9.Children.Add(new TreeItem
            {
                UIType = "AngleMask",
                SlideSwitchValue8 = 0,
                SlideText8 = Resources.String143,
            });
            items.Add(parent9);

            var parent10 = new TreeItem { Name = Resources.String137 };
            parent10.Children.Add(new TreeItem
            {
                UIType = "TwoPeakMask",
                Options4 = new ObservableCollection<string> { Resources.String138, Resources.String139, Resources.String140 }, // 波形幅広、近距離追加(2025.8.25yori)
                SelectedOption4 = Resources.String138,
                ImageSource = "Image/Invalid data.png",   //画像表示確認用(ファイルのパスは仮) // 画像変更(2025.8.25yori)
                OptionIndex4 = 0 // 追加(2025.8.25yori)
            });
            items.Add(parent10);

            var parent11 = new TreeItem { Name = Resources.String141 };
            parent11.Children.Add(new TreeItem
            {
                UIType = "EdgeMask",
                InputText26 = "3", // 追加(2025.8.25yori)
            });
            items.Add(parent11);

            var parent12 = new TreeItem { Name = Resources.String142 };
            parent12.Children.Add(new TreeItem
            {
                UIType = "Memo",
            });
            items.Add(parent12);

            return items;
        }

        public static RectangleAnnotation Rect { get; private set; }

        private PlotModel CreatePlotModel1()
        {
            var model = new PlotModel
            {
                PlotMargins = new OxyThickness(0),
                Padding = new OxyThickness(0)
            };

            //X軸
            model.Axes.Add(new LinearAxis
            {
                Position = AxisPosition.Bottom,
                Minimum = 0,
                Maximum = 65535,
                IsAxisVisible = false
            });

            //Y軸
            model.Axes.Add(new LinearAxis
            {
                Position = AxisPosition.Left,
                Minimum = 0,
                Maximum = 1,
                IsAxisVisible = false
            });

            // 青で全面塗りつぶす矩形
            Rect = new RectangleAnnotation
            {
                MinimumX = 0,
                MaximumX = 0,
                MinimumY = 0,
                MaximumY = 1,
                Fill = OxyColors.CornflowerBlue,
            };

            model.Annotations.Add(Rect);

            return model;
        }


        public static StemSeries BarSeries { get; set; }
        public static List<DataPoint> AllPoints; //データ保持用

        private PlotModel CreatePlotModel2()
        {
            var model = new PlotModel();

            // X軸
            model.Axes.Add(new LinearAxis
            {
                Position = AxisPosition.Bottom,
                Minimum = 0,
                Maximum = 65535,
                IsAxisVisible = false
            });

            // Y軸
            model.Axes.Add(new LinearAxis
            {
                Position = AxisPosition.Left,
                Minimum = 0,
                Maximum = 1,
                IsAxisVisible = false
            });

            // 棒グラフ
            BarSeries = new StemSeries
            {
                Color = OxyColors.CornflowerBlue,
                StrokeThickness = 2
            };

            //サンプルデータ
            var random = new Random();
            AllPoints = new List<DataPoint>();
            for (int i = 0; i < 300; i++)
            {
                double x = i * 300;             
                double y = random.NextDouble();
                AllPoints.Add(new DataPoint(x, y));
            }

            model.Series.Add(BarSeries);

            return model;
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

    public class TreeItem : INotifyPropertyChanged
    {
        public string Name { get; set; }

        // 表示タイプ（テンプレート選択用）
        public string UIType { get; set; }

        public ObservableCollection<TreeItem> Children { get; set; } = new ObservableCollection<TreeItem>();

        // 感度
        public ObservableCollection<string> Options { get; set; }
        public string SelectedOption { get; set; }

        // 追加(2025.8.21yori)
        private int _optionIndex1;
        public int OptionIndex1
        {
            get => _optionIndex1;
            set
            {
                if (_optionIndex1 != value)
                {
                    _optionIndex1 = value;
                    OnPropertyChanged(nameof(OptionIndex1));
                }
            }
        }

        //輝度マスク
        public ObservableCollection<string> Options2 { get; set; }
        public string SelectedOption2 { get; set; }

        //距離マスク
        public string XName { get; set; }
        public string YName { get; set; }
        public string ZName { get; set; }
        private string _slideStatusText;

        private int _slideSwitch;

        public bool SlideSwitch
        {
            get => SlideSwitchValue == 1;
            set
            {
                if (value)
                {
                    SlideSwitchValue = 1;
                    SlideText = Resources.String144;
                }
                else
                {
                    SlideSwitchValue = 0;
                    SlideText = Resources.String143;
                }
            }
        }

        public int SlideSwitchValue
        {
            get => _slideSwitch;
            set
            {
                if (_slideSwitch != value)
                {
                    _slideSwitch = value;
                    OnPropertyChanged(nameof(SlideSwitchValue));
                }
            }
        }

        public string SlideText
        {
            get => _slideStatusText;
            set
            {
                if (_slideStatusText != value)
                {
                    _slideStatusText = value;
                    OnPropertyChanged(nameof(SlideText));
                }
            }
        }

        private bool _isChecked1;
        public bool IsChecked1
        {
            get => _isChecked1;
            set
            {
                if (_isChecked1 != value)
                {
                    _isChecked1 = value;
                    OnPropertyChanged(nameof(IsChecked1));
                }
            }
        }

        private bool _isChecked2;
        public bool IsChecked2
        {
            get => _isChecked2;
            set
            {
                if (_isChecked2 != value)
                {
                    _isChecked2 = value;
                    OnPropertyChanged(nameof(IsChecked2));
                }
            }
        }

        private bool _isChecked3;
        public bool IsChecked3
        {
            get => _isChecked3;
            set
            {
                if (_isChecked3 != value)
                {
                    _isChecked3 = value;
                    OnPropertyChanged(nameof(IsChecked3));
                }
            }
        }

        private bool _isChecked4;
        public bool IsChecked4
        {
            get => _isChecked4;
            set
            {
                if (_isChecked4 != value)
                {
                    _isChecked4 = value;
                    OnPropertyChanged(nameof(IsChecked4));
                }
            }
        }

        private bool _isChecked5;
        public bool IsChecked5
        {
            get => _isChecked5;
            set
            {
                if (_isChecked5 != value)
                {
                    _isChecked5 = value;
                    OnPropertyChanged(nameof(IsChecked5));
                }
            }
        }

        private bool _isChecked6;
        public bool IsChecked6
        {
            get => _isChecked6;
            set
            {
                if (_isChecked6 != value)
                {
                    _isChecked6 = value;
                    OnPropertyChanged(nameof(IsChecked6));
                }
            }
        }

        private string _inputText1;
        public string InputText1
        {
            get => _inputText1;
            set
            {
                if (_inputText1 != value)
                {
                    _inputText1 = value;
                    OnPropertyChanged(nameof(InputText1));
                }
            }
        }

        private string _inputText2;
        public string InputText2
        {
            get => _inputText2;
            set
            {
                if (_inputText2 != value)
                {
                    _inputText2 = value;
                    OnPropertyChanged(nameof(InputText2));
                }
            }
        }

        private string _inputText3;
        public string InputText3
        {
            get => _inputText3;
            set
            {
                if (_inputText3 != value)
                {
                    _inputText3 = value;
                    OnPropertyChanged(nameof(InputText3));
                }
            }
        }

        private string _inputText4;
        public string InputText4
        {
            get => _inputText4;
            set
            {
                if (_inputText4 != value)
                {
                    _inputText4 = value;
                    OnPropertyChanged(nameof(InputText4));
                }
            }
        }

        private string _inputText5;
        public string InputText5
        {
            get => _inputText5;
            set
            {
                if (_inputText5 != value)
                {
                    _inputText5 = value;
                    OnPropertyChanged(nameof(InputText5));
                }
            }
        }

        private string _inputText6;
        public string InputText6
        {
            get => _inputText6;
            set
            {
                if (_inputText6 != value)
                {
                    _inputText6 = value;
                    OnPropertyChanged(nameof(InputText6));
                }
            }
        }

        //// 追加(2025.8.26yori)
        // CheckBoxの有効無効を設定する。
        private bool _isCheckBoxEnabled = false; // 初期状態は無効

        public bool IsCheckBoxEnabled
        {
            get { return _isCheckBoxEnabled; }
            set
            {
                if (_isCheckBoxEnabled != value)
                {
                    _isCheckBoxEnabled = value;
                    OnPropertyChanged(nameof(IsCheckBoxEnabled));
                }
            }
        }
        ////

        //点群補正/フィルタ
        private int _slideSwitch1;
        private string _slideStatusText1;

        public bool SlideSwitch1
        {
            get => SlideSwitchValue1 == 1;
            set
            {
                if (value)
                {
                    SlideSwitchValue1 = 1;
                    SlideText1 = Resources.String144;
                }
                else
                {
                    SlideSwitchValue1 = 0;
                    SlideText1 = Resources.String143;
                }
            }
        }

        public int SlideSwitchValue1
        {
            get => _slideSwitch1;
            set
            {
                if (_slideSwitch1 != value)
                {
                    _slideSwitch1 = value;
                    OnPropertyChanged(nameof(SlideSwitchValue1));
                }
            }
        }

        public string SlideText1
        {
            get => _slideStatusText1;
            set
            {
                if (_slideStatusText1 != value)
                {
                    _slideStatusText1 = value;
                    OnPropertyChanged(nameof(SlideText1));
                }
            }
        }

        private int _slideSwitch2;
        private string _slideStatusText2;

        public bool SlideSwitch2
        {
            get => SlideSwitchValue2 == 1;
            set
            {
                if (value)
                {
                    SlideSwitchValue2 = 1;
                    SlideText2 = Resources.String144;
                }
                else
                {
                    SlideSwitchValue2 = 0;
                    SlideText2 = Resources.String143;
                }
            }
        }

        public int SlideSwitchValue2
        {
            get => _slideSwitch2;
            set
            {
                if (_slideSwitch2 != value)
                {
                    _slideSwitch2 = value;
                    OnPropertyChanged(nameof(SlideSwitchValue2));
                }
            }
        }

        public string SlideText2
        {
            get => _slideStatusText2;
            set
            {
                if (_slideStatusText2 != value)
                {
                    _slideStatusText2 = value;
                    OnPropertyChanged(nameof(SlideText2));
                }
            }
        }

        private int _slideSwitch3;
        private string _slideStatusText3;

        public bool SlideSwitch3
        {
            get => SlideSwitchValue3 == 1;
            set
            {
                if (value)
                {
                    SlideSwitchValue3 = 1;
                    SlideText3 = Resources.String144;
                }
                else
                {
                    SlideSwitchValue3 = 0;
                    SlideText3 = Resources.String143;
                }
            }
        }

        public int SlideSwitchValue3
        {
            get => _slideSwitch3;
            set
            {
                if (_slideSwitch3 != value)
                {
                    _slideSwitch3 = value;
                    OnPropertyChanged(nameof(SlideSwitchValue3));
                }
            }
        }

        public string SlideText3
        {
            get => _slideStatusText3;
            set
            {
                if (_slideStatusText3 != value)
                {
                    _slideStatusText3 = value;
                    OnPropertyChanged(nameof(SlideText3));
                }
            }
        }

        private int _slideSwitch4;
        private string _slideStatusText4;

        public bool SlideSwitch4
        {
            get => SlideSwitchValue4 == 1;
            set
            {
                if (value)
                {
                    SlideSwitchValue4 = 1;
                    SlideText4 = Resources.String144;
                }
                else
                {
                    SlideSwitchValue4 = 0;
                    SlideText4 = Resources.String143;
                }
            }
        }

        public int SlideSwitchValue4
        {
            get => _slideSwitch4;
            set
            {
                if (_slideSwitch4 != value)
                {
                    _slideSwitch4 = value;
                    OnPropertyChanged(nameof(SlideSwitchValue4));
                }
            }
        }

        public string SlideText4
        {
            get => _slideStatusText4;
            set
            {
                if (_slideStatusText4 != value)
                {
                    _slideStatusText4 = value;
                    OnPropertyChanged(nameof(SlideText4));
                }
            }
        }

        private int _slideSwitch5;
        private string _slideStatusText5;

        public bool SlideSwitch5
        {
            get => SlideSwitchValue5 == 1;
            set
            {
                if (value)
                {
                    SlideSwitchValue5 = 1;
                    SlideText5 = Resources.String144;
                }
                else
                {
                    SlideSwitchValue5 = 0;
                    SlideText5 = Resources.String143;
                }
            }
        }

        public int SlideSwitchValue5
        {
            get => _slideSwitch5;
            set
            {
                if (_slideSwitch5 != value)
                {
                    _slideSwitch5 = value;
                    OnPropertyChanged(nameof(SlideSwitchValue5));
                }
            }
        }

        public string SlideText5
        {
            get => _slideStatusText5;
            set
            {
                if (_slideStatusText5 != value)
                {
                    _slideStatusText5 = value;
                    OnPropertyChanged(nameof(SlideText5));
                }
            }
        }

        private int _slideSwitch6;
        private string _slideStatusText6;

        public bool SlideSwitch6
        {
            get => SlideSwitchValue6 == 1;
            set
            {
                if (value)
                {
                    SlideSwitchValue6 = 1;
                    SlideText6 = Resources.String144;
                }
                else
                {
                    SlideSwitchValue6 = 0;
                    SlideText6 = Resources.String143;
                }
            }
        }

        public int SlideSwitchValue6
        {
            get => _slideSwitch6;
            set
            {
                if (_slideSwitch6 != value)
                {
                    _slideSwitch6 = value;
                    OnPropertyChanged(nameof(SlideSwitchValue6));
                }
            }
        }

        public string SlideText6
        {
            get => _slideStatusText6;
            set
            {
                if (_slideStatusText6 != value)
                {
                    _slideStatusText6 = value;
                    OnPropertyChanged(nameof(SlideText6));
                }
            }
        }

        private string _inputText7;
        public string InputText7
        {
            get => _inputText7;
            set
            {
                if (_inputText7 != value)
                {
                    _inputText7 = value;
                    OnPropertyChanged(nameof(InputText7));
                }
            }
        }

        private string _inputText8;
        public string InputText8
        {
            get => _inputText8;
            set
            {
                if (_inputText8 != value)
                {
                    _inputText8 = value;
                    OnPropertyChanged(nameof(InputText8));
                }
            }
        }

        private string _inputText9;
        public string InputText9
        {
            get => _inputText9;
            set
            {
                if (_inputText9 != value)
                {
                    _inputText9 = value;
                    OnPropertyChanged(nameof(InputText9));
                }
            }
        }

        private string _inputText10;
        public string InputText10
        {
            get => _inputText10;
            set
            {
                if (_inputText10 != value)
                {
                    _inputText10 = value;
                    OnPropertyChanged(nameof(InputText10));
                }
            }
        }

        private string _inputText11;
        public string InputText11
        {
            get => _inputText11;
            set
            {
                if (_inputText11 != value)
                {
                    _inputText11 = value;
                    OnPropertyChanged(nameof(InputText11));
                }
            }
        }

        //輝度スライス
        private string _inputText12;
        public string InputText12
        {
            get => _inputText12;
            set
            {
                if (_inputText12 != value)
                {
                    _inputText12 = value;
                    OnPropertyChanged(nameof(InputText12));
                }
            }
        }

        private string _inputText13;
        public string InputText13
        {
            get => _inputText13;
            set
            {
                if (_inputText13 != value)
                {
                    _inputText13 = value;
                    OnPropertyChanged(nameof(InputText13));
                }
            }
        }

        private string _inputText14;
        public string InputText14
        {
            get => _inputText14;
            set
            {
                if (_inputText14 != value)
                {
                    _inputText14 = value;
                    OnPropertyChanged(nameof(InputText14));
                }
            }
        }

        private string _inputText15;
        public string InputText15
        {
            get => _inputText15;
            set
            {
                if (_inputText15 != value)
                {
                    _inputText15 = value;
                    OnPropertyChanged(nameof(InputText15));
                }
            }
        }

        private string _inputText16;
        public string InputText16
        {
            get => _inputText16;
            set
            {
                if (_inputText16 != value)
                {
                    _inputText16 = value;
                    OnPropertyChanged(nameof(InputText16));
                }
            }
        }

        private string _inputText17;
        public string InputText17
        {
            get => _inputText17;
            set
            {
                if (_inputText17 != value)
                {
                    _inputText17 = value;
                    OnPropertyChanged(nameof(InputText17));
                }
            }
        }

        private bool _isChecked7;
        public bool IsChecked7
        {
            get => _isChecked7;
            set
            {
                if (_isChecked7 != value)
                {
                    _isChecked7 = value;
                    OnPropertyChanged(nameof(IsChecked7));
                }
            }
        }

        private bool _isChecked8;
        public bool IsChecked8
        {
            get => _isChecked8;
            set
            {
                if (_isChecked8 != value)
                {
                    _isChecked8 = value;
                    OnPropertyChanged(nameof(IsChecked8));
                }
            }
        }

        //感度スライス
        private string _inputText18;
        public string InputText18
        {
            get => _inputText18;
            set
            {
                if (_inputText18 != value)
                {
                    _inputText18 = value;
                    OnPropertyChanged(nameof(InputText18));
                }
            }
        }

        private string _inputText19;
        public string InputText19
        {
            get => _inputText19;
            set
            {
                if (_inputText19 != value)
                {
                    _inputText19 = value;
                    OnPropertyChanged(nameof(InputText19));
                }
            }
        }

        private string _inputText20;
        public string InputText20
        {
            get => _inputText20;
            set
            {
                if (_inputText20 != value)
                {
                    _inputText20 = value;
                    OnPropertyChanged(nameof(InputText20));
                }
            }
        }

        private string _inputText21;
        public string InputText21
        {
            get => _inputText21;
            set
            {
                if (_inputText21 != value)
                {
                    _inputText21 = value;
                    OnPropertyChanged(nameof(InputText21));
                }
            }
        }

        private string _inputText22;
        public string InputText22
        {
            get => _inputText22;
            set
            {
                if (_inputText22 != value)
                {
                    _inputText22 = value;
                    OnPropertyChanged(nameof(InputText22));
                }
            }
        }

        private string _inputText23;
        public string InputText23
        {
            get => _inputText23;
            set
            {
                if (_inputText23 != value)
                {
                    _inputText23 = value;
                    OnPropertyChanged(nameof(InputText23));
                }
            }
        }

        private string _inputText24;
        public string InputText24
        {
            get => _inputText24;
            set
            {
                if (_inputText24 != value)
                {
                    _inputText24 = value;
                    OnPropertyChanged(nameof(InputText24));
                }
            }
        }

        private bool _isChecked9;
        public bool IsChecked9
        {
            get => _isChecked9;
            set
            {
                if (_isChecked9 != value)
                {
                    _isChecked9 = value;
                    OnPropertyChanged(nameof(IsChecked9));
                }
            }
        }

        private bool _isChecked10;
        public bool IsChecked10
        {
            get => _isChecked10;
            set
            {
                if (_isChecked10 != value)
                {
                    _isChecked10 = value;
                    OnPropertyChanged(nameof(IsChecked10));
                }
            }
        }

        //ガイドレーザーパワー
        public ObservableCollection<string> Options3 { get; set; }
        public string SelectedOption3 { get; set; }

        private int _optionIndex3;
        public int OptionIndex3
        {
            get => _optionIndex3;
            set
            {
                if (_optionIndex3 != value)
                {
                    _optionIndex3 = value;
                    OnPropertyChanged(nameof(OptionIndex3));
                }
            }
        }

        //補間(Xピッチ)
        private int _slideSwitch7;
        private string _slideStatusText7;

        public bool SlideSwitch7
        {
            get => SlideSwitchValue7 == 1;
            set
            {
                if (value)
                {
                    SlideSwitchValue7 = 1;
                    SlideText7 = Resources.String144;
                }
                else
                {
                    SlideSwitchValue7 = 0;
                    SlideText7 = Resources.String143;
                }
            }
        }

        public int SlideSwitchValue7
        {
            get => _slideSwitch7;
            set
            {
                if (_slideSwitch7 != value)
                {
                    _slideSwitch7 = value;
                    OnPropertyChanged(nameof(SlideSwitchValue7));
                }
            }
        }

        public string SlideText7
        {
            get => _slideStatusText7;
            set
            {
                if (_slideStatusText7 != value)
                {
                    _slideStatusText7 = value;
                    OnPropertyChanged(nameof(SlideText7));
                }
            }
        }

        //角度マスク
        private int _slideSwitch8;
        private string _slideStatusText8;

        public bool SlideSwitch8
        {
            get => SlideSwitchValue8 == 1;
            set
            {
                if (value)
                {
                    SlideSwitchValue8 = 1;
                    SlideText8 = Resources.String144;
                }
                else
                {
                    SlideSwitchValue8 = 0;
                    SlideText8 = Resources.String143;
                }
            }
        }

        public int SlideSwitchValue8
        {
            get => _slideSwitch8;
            set
            {
                if (_slideSwitch8 != value)
                {
                    _slideSwitch8 = value;
                    OnPropertyChanged(nameof(SlideSwitchValue8));
                }
            }
        }

        public string SlideText8
        {
            get => _slideStatusText8;
            set
            {
                if (_slideStatusText8 != value)
                {
                    _slideStatusText8 = value;
                    OnPropertyChanged(nameof(SlideText8));
                }
            }
        }

        private string _inputText25;
        public string InputText25
        {
            get => _inputText25;
            set
            {
                if (_inputText25 != value)
                {
                    _inputText25 = value;
                    OnPropertyChanged(nameof(InputText25));
                }
            }
        }

        //2ピークマスク
        public ObservableCollection<string> Options4 { get; set; }
        public string SelectedOption4 { get; set; }

        private string _imageSource;
        public string ImageSource
        {
            get => _imageSource;
            set
            {
                if (_imageSource != value)
                {
                    _imageSource = value;
                    OnPropertyChanged(nameof(ImageSource));
                }
            }
        }

        // 追加(2025.8.25yori)
        private int _optionIndex4;
        public int OptionIndex4
        {
            get => _optionIndex4;
            set
            {
                if (_optionIndex4 != value)
                {
                    _optionIndex4 = value;
                    OnPropertyChanged(nameof(OptionIndex4));
                }
            }
        }

        //エッジマスク
        private string _inputText26;
        public string InputText26
        {
            get => _inputText26;
            set
            {
                if (_inputText26 != value)
                {
                    _inputText26 = value;
                    OnPropertyChanged(nameof(InputText26));
                }
            }
        }

        //メモ
        private string _inputText27;
        public string InputText27
        {
            get => _inputText27;
            set
            {
                if (_inputText27 != value)
                {
                    _inputText27 = value;
                    OnPropertyChanged(nameof(InputText27));
                }
            }
        }

        //輝度マスク
        private string _inputText28;
        public string InputText28
        {
            get => _inputText28;
            set
            {
                if (_inputText28 != value)
                {
                    _inputText28 = value;
                    OnPropertyChanged(nameof(InputText28));
                }
            }
        }

        private string _inputText29;
        public string InputText29
        {
            get => _inputText29;
            set
            {
                if (_inputText29 != value)
                {
                    _inputText29 = value;
                    OnPropertyChanged(nameof(InputText29));
                }
            }
        }

        private string _inputText30;
        public string InputText30
        {
            get => _inputText30;
            set
            {
                if (_inputText30 != value)
                {
                    _inputText30 = value;
                    OnPropertyChanged(nameof(InputText30));
                }
            }
        }

        private string _inputText31;
        public string InputText31
        {
            get => _inputText31;
            set
            {
                if (_inputText31 != value)
                {
                    _inputText31 = value;
                    OnPropertyChanged(nameof(InputText31));
                }
            }
        }

        private string _inputText32;
        public string InputText32
        {
            get => _inputText32;
            set
            {
                if (_inputText32 != value)
                {
                    _inputText32 = value;
                    OnPropertyChanged(nameof(InputText32));
                    if (int.TryParse(value, out int num))
                    {
                        if (SlideSwitchValue10 != num)
                            SlideSwitchValue10 = num;
                    }
                }
            }
        }

        private string _inputText33;
        public string InputText33
        {
            get => _inputText33;
            set
            {
                if (_inputText33 != value)
                {
                    _inputText33 = value;
                    OnPropertyChanged(nameof(InputText33));
                    if (int.TryParse(value, out int num))
                    {
                        if (SlideSwitchValue11 != num)
                            SlideSwitchValue11 = num;
                    }
                }
            }
        }

        private string _inputText34;
        public string InputText34
        {
            get => _inputText34;
            set
            {
                if (_inputText34 != value)
                {
                    _inputText34 = value;
                    OnPropertyChanged(nameof(InputText34));
                    InputText32 = value;
                }
            }
        }

        private string _inputText35;
        public string InputText35
        {
            get => _inputText35;
            set
            {
                if (_inputText35 != value)
                {
                    _inputText35 = value;
                    OnPropertyChanged(nameof(InputText35));
                    InputText33 = value;
                }
            }
        }

        private string _inputText36;
        public string InputText36
        {
            get => _inputText36;
            set
            {
                if (_inputText36 != value)
                {
                    _inputText36 = value;
                    OnPropertyChanged(nameof(InputText36));
                }
            }
        }

        private string _inputText37;
        public string InputText37
        {
            get => _inputText37;
            set
            {
                if (_inputText37 != value)
                {
                    _inputText37 = value;
                    OnPropertyChanged(nameof(InputText37));
                }
            }
        }

        private string _inputText38;
        public string InputText38
        {
            get => _inputText38;
            set
            {
                if (_inputText38 != value)
                {
                    _inputText38 = value;
                    OnPropertyChanged(nameof(InputText38));
                }
            }
        }

        private string _inputText39;
        public string InputText39
        {
            get => _inputText39;
            set
            {
                if (_inputText39 != value)
                {
                    _inputText39 = value;
                    OnPropertyChanged(nameof(InputText39));
                }
            }
        }

        private string _inputText40;
        public string InputText40
        {
            get => _inputText40;
            set
            {
                if (_inputText40 != value)
                {
                    _inputText40 = value;
                    OnPropertyChanged(nameof(InputText40));
                }
            }
        }

        private int _slideSwitch9;
        private string _slideStatusText9;

        public bool SlideSwitch9
        {
            get => SlideSwitchValue9 == 1;
            set
            {
                if (value)
                {
                    SlideSwitchValue9 = 1;
                    SlideText9 = Resources.String144;
                }
                else
                {
                    SlideSwitchValue9 = 0;
                    SlideText9 = Resources.String143;
                }
            }
        }

        public int SlideSwitchValue9
        {
            get => _slideSwitch9;
            set
            {
                if (_slideSwitch9 != value)
                {
                    _slideSwitch9 = value;
                    OnPropertyChanged(nameof(SlideSwitchValue9));
                }
            }
        }

        public string SlideText9
        {
            get => _slideStatusText9;
            set
            {
                if (_slideStatusText9 != value)
                {
                    _slideStatusText9 = value;
                    OnPropertyChanged(nameof(SlideText9));
                }
            }
        }

        private int _slideSwitch10;
        public int SlideSwitchValue10
        {
            get => _slideSwitch10;
            set
            {
                if (_slideSwitch10 != value)
                {
                    _slideSwitch10 = value;
                    OnPropertyChanged(nameof(SlideSwitchValue10));
                    InputText32 = value.ToString();
                    UpdatePlotRange();
                }
            }
        }

        private int _slideSwitch11;
        public int SlideSwitchValue11
        {
            get => _slideSwitch11;
            set
            {
                if (_slideSwitch11 != value)
                {
                    _slideSwitch11 = value;
                    OnPropertyChanged(nameof(SlideSwitchValue11));
                    InputText33 = value.ToString();
                    UpdatePlotRange();
                }
            }
        }

        private PlotModel _plotModel1;
        public PlotModel PlotModel1
        {
            get => _plotModel1;
            set
            {
                _plotModel1 = value;
                OnPropertyChanged(nameof(PlotModel1));
            }
        }

        private PlotModel _plotModel2;
        public PlotModel PlotModel2
        {
            get => _plotModel2;
            set
            {
                _plotModel2 = value;
                OnPropertyChanged(nameof(PlotModel2));
            }
        }

        private void UpdatePlotRange()
        {
            double min = Math.Min(SlideSwitchValue10, SlideSwitchValue11);
            double max = Math.Max(SlideSwitchValue10, SlideSwitchValue11);

            // PlotModel1 の範囲を更新
            if (ApiScanViewModel.Rect != null)
            {
                ApiScanViewModel.Rect.MinimumX = min;
                ApiScanViewModel.Rect.MaximumX = max;
                PlotModel1.InvalidatePlot(false);
            }

            // PlotModel2 の範囲を更新
            if (ApiScanViewModel.BarSeries != null)
            {
                ApiScanViewModel.BarSeries.Points.Clear();
                ApiScanViewModel.BarSeries.Points.AddRange(ApiScanViewModel.AllPoints.Where(p => p.X >= min && p.X <= max));

                PlotModel2.InvalidatePlot(true);
            }

        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
