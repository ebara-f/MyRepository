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


        private string _centerBefValue;
        public string CenterBefValue
        {
            get => _centerBefValue;
            set
            {
                if (_centerBefValue != value)
                {
                    _centerBefValue = value;
                    OnPropertyChanged(nameof(CenterBefValue));
                }
            }
        }

        private bool _centerBefJudge = true;
        public bool CenterBefJudge
        {
            get => _centerBefJudge;
            set
            {
                if (_centerBefJudge != value)
                {
                    _centerBefJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(CenterBefBackground));
                }
            }
        }
        public Brush CenterBefBackground => CenterBefJudge ? Brushes.White : Brushes.LightYellow;

        private string _centerAftValue;
        public string CenterAftValue
        {
            get => _centerAftValue;
            set
            {
                if (_centerAftValue != value)
                {
                    _centerAftValue = value;
                    OnPropertyChanged(nameof(CenterAftValue));
                }
            }
        }

        private bool _centerAftJudge = true;
        public bool CenterAftJudge
        {
            get => _centerAftJudge;
            set
            {
                if (_centerAftJudge != value)
                {
                    _centerAftJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(CenterAftBackground));
                }
            }
        }
        public Brush CenterAftBackground => CenterAftJudge ? Brushes.White : Brushes.LightYellow;


        private string _diaBefValue;
        public string DiaBefValue
        {
            get => _diaBefValue;
            set
            {
                if (_diaBefValue != value)
                {
                    _diaBefValue = value;
                    OnPropertyChanged(nameof(DiaBefValue));
                }
            }
        }

        private bool _diaBefJudge = true;
        public bool DiaBefJudge
        {
            get => _diaBefJudge;
            set
            {
                if (_diaBefJudge != value)
                {
                    _diaBefJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(DiaBefBackground));
                }
            }
        }
        public Brush DiaBefBackground => DiaBefJudge ? Brushes.White : Brushes.LightYellow;


        private string _diaAftValue;
        public string DiaAftValue
        {
            get => _diaAftValue;
            set
            {
                if (_diaAftValue != value)
                {
                    _diaAftValue = value;
                    OnPropertyChanged(nameof(DiaAftValue));
                }
            }
        }

        private bool _diaAftJudge = true;
        public bool DiaAftJudge
        {
            get => _diaAftJudge;
            set
            {
                if (_diaAftJudge != value)
                {
                    _diaAftJudge = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(DiaAftBackground));
                }
            }
        }
        public Brush DiaAftBackground => DiaAftJudge ? Brushes.White : Brushes.LightYellow;

        private string _thresholdText3;
        public string ThresholdText3
        {
            get => _thresholdText3;
            set
            {
                if (_thresholdText3 != value)
                {
                    _thresholdText3 = value;
                    OnPropertyChanged(nameof(ThresholdText3));
                }
            }
        }


        // 2025.10.7 add eba
        private string _resultText3 = "NG";
        public string ResultText3
        {
            get => _resultText3;
            set
            {
                if (_resultText3 != value)
                {
                    _resultText3 = value;
                    OnPropertyChanged(nameof(ResultText3));
                }
            }
        }

        private bool _resultJudge3 = true;
        public bool ResultJudge3
        {
            get => _resultJudge3;
            set
            {
                if (_resultJudge3 != value)
                {
                    _resultJudge3 = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(ResultBackground3));
                }
            }
        }
        public Brush ResultBackground3 => ResultJudge3 ? Brushes.LightGreen : Brushes.LightPink;

        /// <summary>
        /// ////////
        /// </summary>
        // 2025.10.7 add eba
        private Visibility _gridVisibility4 = Visibility.Hidden;
        public Visibility GridVisibility4
        {
            get => _gridVisibility4;
            set
            {
                if (_gridVisibility4 != value)
                {
                    _gridVisibility4 = value;
                    OnPropertyChanged(nameof(GridVisibility4));
                }
            }
        }


        private string _xMaxMixValue;
        public string XMaxMixValue
        {
            get => _xMaxMixValue;
            set
            {
                if (_xMaxMixValue != value)
                {
                    _xMaxMixValue = value;
                    OnPropertyChanged(nameof(XMaxMixValue));
                }
            }
        }

        private bool _xMaxMinJudge4 = true;
        public bool XMaxMinJudge4
        {
            get => _xMaxMinJudge4;
            set
            {
                if (_xMaxMinJudge4 != value)
                {
                    _xMaxMinJudge4 = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(XMaxMinground));
                }
            }
        }
        public Brush XMaxMinground => XMaxMinJudge4 ? Brushes.White : Brushes.LightYellow;


        private string _yMaxMixValue;
        public string YMaxMixValue
        {
            get => _yMaxMixValue;
            set
            {
                if (_yMaxMixValue != value)
                {
                    _yMaxMixValue = value;
                    OnPropertyChanged(nameof(YMaxMixValue));
                }
            }
        }

        private bool _yMaxMinJudge4 = true;
        public bool YMaxMinJudge4
        {
            get => _yMaxMinJudge4;
            set
            {
                if (_yMaxMinJudge4 != value)
                {
                    _yMaxMinJudge4 = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(YMaxMinground));
                }
            }
        }
        public Brush YMaxMinground => YMaxMinJudge4 ? Brushes.White : Brushes.LightYellow;


        private string _zMaxMixValue;
        public string ZMaxMixValue
        {
            get => _zMaxMixValue;
            set
            {
                if (_zMaxMixValue != value)
                {
                    _zMaxMixValue = value;
                    OnPropertyChanged(nameof(ZMaxMixValue));
                }
            }
        }

        private bool _zMaxMinJudge4 = true;
        public bool ZMaxMinJudge4
        {
            get => _zMaxMinJudge4;
            set
            {
                if (_zMaxMinJudge4 != value)
                {
                    _zMaxMinJudge4 = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(ZMaxMinground));
                }
            }
        }
        public Brush ZMaxMinground => ZMaxMinJudge4 ? Brushes.White : Brushes.LightYellow;

        private string _faceDistanceValue4;
        public string FaceDistanceValue4
        {
            get => _faceDistanceValue4;
            set
            {
                if (_faceDistanceValue4 != value)
                {
                    _faceDistanceValue4 = value;
                    OnPropertyChanged(nameof(FaceDistanceValue4));
                }
            }
        }

        private string _measurementErrorValue4;
        public string MeasurementErrorValue4
        {
            get => _measurementErrorValue4;
            set
            {
                if (_measurementErrorValue4 != value)
                {
                    _measurementErrorValue4 = value;
                    OnPropertyChanged(nameof(MeasurementErrorValue4));
                }
            }
        }

        private string _thresholdText4;
        public string ThresholdText4
        {
            get => _thresholdText4;
            set
            {
                if (_thresholdText4 != value)
                {
                    _thresholdText4 = value;
                    OnPropertyChanged(nameof(ThresholdText4));
                }
            }
        }

        private string _resultText4 = "NG";
        public string ResultText4
        {
            get => _resultText4;
            set
            {
                if (_resultText4 != value)
                {
                    _resultText4 = value;
                    OnPropertyChanged(nameof(ResultText4));
                }
            }
        }

        private bool _resultJudge4 = true;
        public bool ResultJudge4
        {
            get => _resultJudge4;
            set
            {
                if (_resultJudge4 != value)
                {
                    _resultJudge4 = value;
                    //OnPropertyChanged();
                    // 状態が変わったら色も変わる
                    OnPropertyChanged(nameof(ResultBackground4));
                }
            }
        }
        public Brush ResultBackground4 => ResultJudge4 ? Brushes.LightGreen : Brushes.LightPink;
















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

        private void OnPropertyChanged(string name) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));

        // Viewと関連付かない変数 2025.8.26 add eba
        public int CalibStyleFg = 0;

        public CalibPara CalibPara = new CalibPara(); // 2025.9.3 add eba
    }
}
