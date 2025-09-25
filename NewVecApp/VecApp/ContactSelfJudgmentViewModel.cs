using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace VecApp
{
    public class ContactSelfJudgmentViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public ContactSelfJudgmentViewModel()
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

        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
