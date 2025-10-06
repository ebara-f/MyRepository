using CSH;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using static System.Runtime.InteropServices.JavaScript.JSType;
using System.Windows.Media;

namespace VecApp
{
    public class ContactInspectionViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public ContactInspectionViewModel()
        {
            ImageSource = "Image/1-1-1.png";
        }

        private Visibility _imageVisibility = Visibility.Visible;
        public Visibility ImageVisibility
        {
            get => _imageVisibility;
            set
            {
                if (_imageVisibility != value)
                {
                    _imageVisibility = value;
                    OnPropertyChanged(nameof(ImageVisibility));
                }
            }
        }

        private Visibility _gridVisibility = Visibility.Hidden;
        public Visibility GridVisibility
        {
            get => _gridVisibility;
            set
            {
                if (_gridVisibility != value)
                {
                    _gridVisibility = value;
                    OnPropertyChanged(nameof(GridVisibility));
                }
            }
        }

        // 2025.10.6 add eba
        private Visibility _gridVisibility2 = Visibility.Hidden;
        public Visibility GridVisibility2
        {
            get => _gridVisibility2;
            set
            {
                if (_gridVisibility2 != value)
                {
                    _gridVisibility2 = value;
                    OnPropertyChanged(nameof(GridVisibility2));
                }
            }
        }

        // 2025.10.6 add eba
        private Visibility _gridVisibility3 = Visibility.Hidden;
        public Visibility GridVisibility3
        {
            get => _gridVisibility3;
            set
            {
                if (_gridVisibility3 != value)
                {
                    _gridVisibility3 = value;
                    OnPropertyChanged(nameof(GridVisibility3));
                }
            }
        }


        // 2025.9.22 add eba
        private Visibility _snapVisibility = Visibility.Hidden;
        public Visibility SnapVisibility
        {
            get => _snapVisibility;
            set
            {
                if (_snapVisibility != value)
                {
                    _snapVisibility = value;
                    OnPropertyChanged(nameof(SnapVisibility));
                }
            }
        }

        private string _xMaxMinValue;
        public string XMaxMinValue
        {
            get => _xMaxMinValue;
            set
            {
                if (_xMaxMinValue != value)
                {
                    _xMaxMinValue = value;
                    OnPropertyChanged(nameof(XMaxMinValue));
                }
            }
        }

        private string _xTwoSigmaValue;
        public string XTwoSigmaValue
        {
            get => _xTwoSigmaValue;
            set
            {
                if (_xTwoSigmaValue != value)
                {
                    _xTwoSigmaValue = value;
                    OnPropertyChanged(nameof(XTwoSigmaValue));
                }
            }
        }

        private string _yMaxMinValue;
        public string YMaxMinValue
        {
            get => _yMaxMinValue;
            set
            {
                if (_yMaxMinValue != value)
                {
                    _yMaxMinValue = value;
                    OnPropertyChanged(nameof(YMaxMinValue));
                }
            }
        }

        private string _yTwoSigmaValue;
        public string YTwoSigmaValue
        {
            get => _yTwoSigmaValue;
            set
            {
                if (_yTwoSigmaValue != value)
                {
                    _yTwoSigmaValue = value;
                    OnPropertyChanged(nameof(YTwoSigmaValue));
                }
            }
        }

        private string _zMaxMinValue;
        public string ZMaxMinValue
        {
            get => _zMaxMinValue;
            set
            {
                if (_zMaxMinValue != value)
                {
                    _zMaxMinValue = value;
                    OnPropertyChanged(nameof(ZMaxMinValue));
                }
            }
        }

        private string _zTwoSigmaValue;
        public string ZTwoSigmaValue
        {
            get => _zTwoSigmaValue;
            set
            {
                if (_zTwoSigmaValue != value)
                {
                    _zTwoSigmaValue = value;
                    OnPropertyChanged(nameof(ZTwoSigmaValue));
                }
            }
        }

        private string _distanceTwoSigmaValue;
        public string DistanceTwoSigmaValue
        {
            get => _distanceTwoSigmaValue;
            set
            {
                if (_distanceTwoSigmaValue != value)
                {
                    _distanceTwoSigmaValue = value;
                    OnPropertyChanged(nameof(DistanceTwoSigmaValue));
                }
            }
        }

        private string _faceDistanceValue;
        public string FaceDistanceValue
        {
            get => _faceDistanceValue;
            set
            {
                if (_faceDistanceValue != value)
                {
                    _faceDistanceValue = value;
                    OnPropertyChanged(nameof(FaceDistanceValue));
                }
            }
        }

        private string _measurementErrorValue;
        public string MeasurementErrorValue
        {
            get => _measurementErrorValue;
            set
            {
                if (_measurementErrorValue != value)
                {
                    _measurementErrorValue = value;
                    OnPropertyChanged(nameof(MeasurementErrorValue));
                }
            }
        }

        private string _thresholdText;
        public string ThresholdText
        {
            get => _thresholdText;
            set
            {
                if (_thresholdText != value)
                {
                    _thresholdText = value;
                    OnPropertyChanged(nameof(ThresholdText));
                }
            }
        }

        private string _historyText;
        public string HistoryText
        {
            get => _historyText;
            set
            {
                if (_historyText != value)
                {
                    _historyText = value;
                    OnPropertyChanged(nameof(HistoryText));
                }
            }
        }

        private string _subtitleText;
        public string SubtitleText
        {
            get => _subtitleText;
            set
            {
                if (_subtitleText != value)
                {
                    _subtitleText = value;
                    OnPropertyChanged(nameof(SubtitleText));
                }
            }
        }

        private string _resultText = "NG";
        public string ResultText
        {
            get => _resultText;
            set
            {
                if (_resultText != value)
                {
                    _resultText = value;
                    OnPropertyChanged(nameof(ResultText));
                }
            }
        }

        public string ToggleResultText()
        {
            if (ResultText == "OK")
            {
                ResultText = "NG";
            }
            else
            {
                ResultText = "OK";
            }

            return ResultText;
        }

        // 2025.10.6 add eba
        private string _resultText2 = "NG";
        public string ResultText2
        {
            get => _resultText2;
            set
            {
                if (_resultText2 != value)
                {
                    _resultText2 = value;
                    OnPropertyChanged(nameof(ResultText2));
                }
            }
        }


        private bool _xMaxMinJudge = true;
        public bool XMaxMinJudge
        {
            get => _xMaxMinJudge;
            set
            {
                if (_xMaxMinJudge != value)
                {
                    _xMaxMinJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(XMaxMinBackground));
                }
            }
        }
        public Brush XMaxMinBackground => XMaxMinJudge ? Brushes.White : Brushes.LightPink;


        private bool _xTwoSigmaJudge = true;
        public bool XTwoSigmaJudge
        {
            get => _xTwoSigmaJudge;
            set
            {
                if (_xTwoSigmaJudge != value)
                {
                    _xTwoSigmaJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(XTwoSigmaBackground));
                }
            }
        }
        public Brush XTwoSigmaBackground => XTwoSigmaJudge ? Brushes.White : Brushes.LightPink;


        private bool _yMaxMinJudge = true;
        public bool YMaxMinJudge
        {
            get => _yMaxMinJudge;
            set
            {
                if (_yMaxMinJudge != value)
                {
                    _yMaxMinJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(YMaxMinBackground));
                }
            }
        }
        public Brush YMaxMinBackground => YMaxMinJudge ? Brushes.White : Brushes.LightPink;


        private bool _yTwoSigmaJudge = true;
        public bool YTwoSigmaJudge
        {
            get => _yTwoSigmaJudge;
            set
            {
                if (_yTwoSigmaJudge != value)
                {
                    _yTwoSigmaJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(YTwoSigmaBackground));
                }
            }
        }
        public Brush YTwoSigmaBackground => YTwoSigmaJudge ? Brushes.White : Brushes.LightPink;


        private bool _zMaxMinJudge = true;
        public bool ZMaxMinJudge
        {
            get => _zMaxMinJudge;
            set
            {
                if (_zMaxMinJudge != value)
                {
                    _zMaxMinJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(ZMaxMinBackground));
                }
            }
        }
        public Brush ZMaxMinBackground => ZMaxMinJudge ? Brushes.White : Brushes.LightPink;


        private bool _zTwoSigmaJudge = true;
        public bool ZTwoSigmaJudge
        {
            get => _zTwoSigmaJudge;
            set
            {
                if (_zTwoSigmaJudge != value)
                {
                    _zTwoSigmaJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(ZTwoSigmaBackground));
                }
            }
        }
        public Brush ZTwoSigmaBackground => ZTwoSigmaJudge ? Brushes.White : Brushes.LightPink;


        private bool _distanceTwoSigmaJudge = true;
        public bool DistanceTwoSigmaJudge
        {
            get => _distanceTwoSigmaJudge;
            set
            {
                if (_distanceTwoSigmaJudge != value)
                {
                    _distanceTwoSigmaJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(DistanceTwoSigmaBackground));
                }
            }
        }
        public Brush DistanceTwoSigmaBackground => DistanceTwoSigmaJudge ? Brushes.White : Brushes.LightPink;

        private bool _measurementErrorJudge = true;
        public bool MeasurementErrorJudge
        {
            get => _measurementErrorJudge;
            set
            {
                if (_measurementErrorJudge != value)
                {
                    _measurementErrorJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(MeasurementErrorJudge));
                }
            }
        }
        public Brush MeasurementErrorBackground => MeasurementErrorJudge ? Brushes.White : Brushes.LightPink;

        private bool _resultJudge = true;
        public bool ResultJudge
        {
            get => _resultJudge;
            set
            {
                if (_resultJudge != value)
                {
                    _resultJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(ResultBackground));
                }
            }
        }
        public Brush ResultBackground => ResultJudge ? Brushes.LightGreen : Brushes.LightPink;

        private bool _resultJudge2 = true;
        public bool ResultJudge2
        {
            get => _resultJudge2;
            set
            {
                if (_resultJudge2 != value)
                {
                    _resultJudge2 = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(ResultBackground2));
                }
            }
        }
        public Brush ResultBackground2 => ResultJudge2 ? Brushes.LightGreen : Brushes.LightPink;



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

        // TextBoxの有効無効を設定する。 2025.9.2 add eba
        private bool _isTextBoxEnabled = false; // 初期状態は無効

        public bool IsTextBoxEnabled
        {
            get { return _isTextBoxEnabled; }
            set
            {
                if (_isTextBoxEnabled != value)
                {
                    _isTextBoxEnabled = value;
                    OnPropertyChanged(nameof(IsTextBoxEnabled));
                }
            }
        }

        // ゲージ長さ 2025.9.2 add eba
        private string _gaugeLength;
        public string GaugeLength
        {
            get => _gaugeLength;
            set
            {
                if (_gaugeLength != value)
                {
                    _gaugeLength = value;
                    OnPropertyChanged(nameof(GaugeLength));
                }
            }
        }

        // 開始ボタンの有効無効を設定する。 2025.9.2 add eba
        private bool _isStartBtnEnabled = true; // 初期状態は有効

        public bool IsStartBtnEnabled
        {
            get { return _isStartBtnEnabled; }
            set
            {
                if (_isStartBtnEnabled != value)
                {
                    _isStartBtnEnabled = value;
                    OnPropertyChanged(nameof(IsStartBtnEnabled));
                }
            }
        }

        // 戻るボタンの有効無効を設定する。 2025.9.2 add eba
        private bool _isBackBtnEnabled = true; // 初期状態は有効

        public bool IsBackBtnEnabled
        {
            get { return _isBackBtnEnabled; }
            set
            {
                if (_isBackBtnEnabled != value)
                {
                    _isBackBtnEnabled = value;
                    OnPropertyChanged(nameof(IsBackBtnEnabled));
                }
            }
        }

        // 初めに戻るボタンの有効無効を設定する。 2025.9.2 add eba
        private bool _isReStartBtnEnabled = true; // 初期状態は有効

        public bool IsReStartBtnEnabled
        {
            get { return _isReStartBtnEnabled; }
            set
            {
                if (_isReStartBtnEnabled != value)
                {
                    _isReStartBtnEnabled = value;
                    OnPropertyChanged(nameof(IsReStartBtnEnabled));
                }
            }
        }

        // 結果保存ボタンの有効無効を設定する。 2025.9.2 add eba
        private bool _isSaveBtnEnabled = true; // 初期状態は有効

        public bool IsSaveBtnEnabled
        {
            get { return _isSaveBtnEnabled; }
            set
            {
                if (_isSaveBtnEnabled != value)
                {
                    _isSaveBtnEnabled = value;
                    OnPropertyChanged(nameof(IsSaveBtnEnabled));
                }
            }
        }

        // 設定ボタンの有効無効を設定する。 2025.9.2 add eba
        private bool _isSettingBtnEnabled = true; // 初期状態は有効

        public bool IsSettingBtnEnabled
        {
            get { return _isSettingBtnEnabled; }
            set
            {
                if (_isSettingBtnEnabled != value)
                {
                    _isSettingBtnEnabled = value;
                    OnPropertyChanged(nameof(IsSettingBtnEnabled));
                }
            }
        }

        private void OnPropertyChanged(string name) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));

        // Viewと関連付かない変数 2025.8.26 add eba
        public int CalibStyleFg = 0;

        public CalibPara CalibPara = new CalibPara(); // 2025.9.3 add eba
    }
}
