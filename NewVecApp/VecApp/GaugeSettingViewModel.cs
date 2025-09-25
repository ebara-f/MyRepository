using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VecApp
{
    public class GaugeSettingViewModel : INotifyPropertyChanged
    {
        //// 追加(2025.8.7yori)
        // TextBoxの有効無効を設定する。
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

        // パラメータの球中心
        private string _centerScopePntX;
        public string CenterScopePntX
        {
            get => _centerScopePntX;
            set
            {
                if (_centerScopePntX != value)
                {
                    _centerScopePntX = value;
                    OnPropertyChanged(nameof(CenterScopePntX));
                }
            }
        }

        private string _centerScopePntY;
        public string CenterScopePntY
        {
            get => _centerScopePntY;
            set
            {
                if (_centerScopePntY != value)
                {
                    _centerScopePntY = value;
                    OnPropertyChanged(nameof(CenterScopePntY));
                }
            }
        }

        private string _centerScopePntZ;
        public string CenterScopePntZ
        {
            get => _centerScopePntZ;
            set
            {
                if (_centerScopePntZ != value)
                {
                    _centerScopePntZ = value;
                    OnPropertyChanged(nameof(CenterScopePntZ));
                }
            }
        }

        private string _centerScopePntRad;
        public string CenterScopePntRad
        {
            get => _centerScopePntRad;
            set
            {
                if (_centerScopePntRad != value)
                {
                    _centerScopePntRad = value;
                    OnPropertyChanged(nameof(CenterScopePntRad));
                }
            }
        }

        // パラメータの面高さ
        private string _planeScopePnt00;
        public string PlaneScopePnt00
        {
            get => _planeScopePnt00;
            set
            {
                if (_planeScopePnt00 != value)
                {
                    _planeScopePnt00 = value;
                    OnPropertyChanged(nameof(PlaneScopePnt00));
                }
            }
        }

        private string _planeScopePnt01;
        public string PlaneScopePnt01
        {
            get => _planeScopePnt01;
            set
            {
                if (_planeScopePnt01 != value)
                {
                    _planeScopePnt01 = value;
                    OnPropertyChanged(nameof(PlaneScopePnt01));
                }
            }
        }

        private string _planeScopePnt02;
        public string PlaneScopePnt02
        {
            get => _planeScopePnt02;
            set
            {
                if (_planeScopePnt02 != value)
                {
                    _planeScopePnt02 = value;
                    OnPropertyChanged(nameof(PlaneScopePnt02));
                }
            }
        }

        private string _planeScopePnt10;
        public string PlaneScopePnt10
        {
            get => _planeScopePnt10;
            set
            {
                if (_planeScopePnt10 != value)
                {
                    _planeScopePnt10 = value;
                    OnPropertyChanged(nameof(PlaneScopePnt10));
                }
            }
        }

        private string _planeScopePnt11;
        public string PlaneScopePnt11
        {
            get => _planeScopePnt11;
            set
            {
                if (_planeScopePnt11 != value)
                {
                    _planeScopePnt11 = value;
                    OnPropertyChanged(nameof(PlaneScopePnt11));
                }
            }
        }

        private string _planeScopePnt12;
        public string PlaneScopePnt12
        {
            get => _planeScopePnt12;
            set
            {
                if (_planeScopePnt12 != value)
                {
                    _planeScopePnt12 = value;
                    OnPropertyChanged(nameof(PlaneScopePnt12));
                }
            }
        }

        private string _planeScopePnt20;
        public string PlaneScopePnt20
        {
            get => _planeScopePnt20;
            set
            {
                if (_planeScopePnt20 != value)
                {
                    _planeScopePnt20 = value;
                    OnPropertyChanged(nameof(PlaneScopePnt20));
                }
            }
        }

        private string _planeScopePnt21;
        public string PlaneScopePnt21
        {
            get => _planeScopePnt21;
            set
            {
                if (_planeScopePnt21 != value)
                {
                    _planeScopePnt21 = value;
                    OnPropertyChanged(nameof(PlaneScopePnt21));
                }
            }
        }

        private string _planeScopePnt22;
        public string PlaneScopePnt22
        {
            get => _planeScopePnt22;
            set
            {
                if (_planeScopePnt22 != value)
                {
                    _planeScopePnt22 = value;
                    OnPropertyChanged(nameof(PlaneScopePnt22));
                }
            }
        }

        private string _planeScopePnt30;
        public string PlaneScopePnt30
        {
            get => _planeScopePnt30;
            set
            {
                if (_planeScopePnt30 != value)
                {
                    _planeScopePnt30 = value;
                    OnPropertyChanged(nameof(PlaneScopePnt30));
                }
            }
        }

        private string _planeScopePnt31;
        public string PlaneScopePnt31
        {
            get => _planeScopePnt31;
            set
            {
                if (_planeScopePnt31 != value)
                {
                    _planeScopePnt31 = value;
                    OnPropertyChanged(nameof(PlaneScopePnt31));
                }
            }
        }

        private string _planeScopePnt32;
        public string PlaneScopePnt32
        {
            get => _planeScopePnt32;
            set
            {
                if (_planeScopePnt32 != value)
                {
                    _planeScopePnt32 = value;
                    OnPropertyChanged(nameof(PlaneScopePnt32));
                }
            }
        }

        private string _planeScopeRad;
        public string PlaneScopeRad
        {
            get => _planeScopeRad;
            set
            {
                if (_planeScopeRad != value)
                {
                    _planeScopeRad = value;
                    OnPropertyChanged(nameof(PlaneScopeRad));
                }
            }
        }

        // パラメータの面間距離
        private string _lengthScopePnt00;
        public string LengthScopePnt00
        {
            get => _lengthScopePnt00;
            set
            {
                if (_lengthScopePnt00 != value)
                {
                    _lengthScopePnt00 = value;
                    OnPropertyChanged(nameof(LengthScopePnt00));
                }
            }
        }

        private string _lengthScopePnt01;
        public string LengthScopePnt01
        {
            get => _lengthScopePnt01;
            set
            {
                if (_lengthScopePnt01 != value)
                {
                    _lengthScopePnt01 = value;
                    OnPropertyChanged(nameof(LengthScopePnt01));
                }
            }
        }

        private string _lengthScopePnt02;
        public string LengthScopePnt02
        {
            get => _lengthScopePnt02;
            set
            {
                if (_lengthScopePnt02 != value)
                {
                    _lengthScopePnt02 = value;
                    OnPropertyChanged(nameof(LengthScopePnt02));
                }
            }
        }

        private string _lengthScopePnt10;
        public string LengthScopePnt10
        {
            get => _lengthScopePnt10;
            set
            {
                if (_lengthScopePnt10 != value)
                {
                    _lengthScopePnt10 = value;
                    OnPropertyChanged(nameof(LengthScopePnt10));
                }
            }
        }

        private string _lengthScopePnt11;
        public string LengthScopePnt11
        {
            get => _lengthScopePnt11;
            set
            {
                if (_lengthScopePnt11 != value)
                {
                    _lengthScopePnt11 = value;
                    OnPropertyChanged(nameof(LengthScopePnt11));
                }
            }
        }

        private string _lengthScopePnt12;
        public string LengthScopePnt12
        {
            get => _lengthScopePnt12;
            set
            {
                if (_lengthScopePnt12 != value)
                {
                    _lengthScopePnt12 = value;
                    OnPropertyChanged(nameof(LengthScopePnt12));
                }
            }
        }

        private string _lengthScopePnt20;
        public string LengthScopePnt20
        {
            get => _lengthScopePnt20;
            set
            {
                if (_lengthScopePnt20 != value)
                {
                    _lengthScopePnt20 = value;
                    OnPropertyChanged(nameof(LengthScopePnt20));
                }
            }
        }

        private string _lengthScopePnt21;
        public string LengthScopePnt21
        {
            get => _lengthScopePnt21;
            set
            {
                if (_lengthScopePnt21 != value)
                {
                    _lengthScopePnt21 = value;
                    OnPropertyChanged(nameof(LengthScopePnt21));
                }
            }
        }

        private string _lengthScopePnt22;
        public string LengthScopePnt22
        {
            get => _lengthScopePnt22;
            set
            {
                if (_lengthScopePnt22 != value)
                {
                    _lengthScopePnt22 = value;
                    OnPropertyChanged(nameof(LengthScopePnt22));
                }
            }
        }

        private string _lengthScopePnt30;
        public string LengthScopePnt30
        {
            get => _lengthScopePnt30;
            set
            {
                if (_lengthScopePnt30 != value)
                {
                    _lengthScopePnt30 = value;
                    OnPropertyChanged(nameof(LengthScopePnt30));
                }
            }
        }

        private string _lengthScopePnt31;
        public string LengthScopePnt31
        {
            get => _lengthScopePnt31;
            set
            {
                if (_lengthScopePnt31 != value)
                {
                    _lengthScopePnt31 = value;
                    OnPropertyChanged(nameof(LengthScopePnt31));
                }
            }
        }

        private string _lengthScopePnt32;
        public string LengthScopePnt32
        {
            get => _lengthScopePnt32;
            set
            {
                if (_lengthScopePnt32 != value)
                {
                    _lengthScopePnt32 = value;
                    OnPropertyChanged(nameof(LengthScopePnt32));
                }
            }
        }

        private string _lengthScopeRad;
        public string LengthScopeRad
        {
            get => _lengthScopeRad;
            set
            {
                if (_lengthScopeRad != value)
                {
                    _lengthScopeRad = value;
                    OnPropertyChanged(nameof(LengthScopeRad));
                }
            }
        }

        private string _lengthScopeRadCnt;
        public string LengthScopeRadCnt
        {
            get => _lengthScopeRadCnt;
            set
            {
                if (_lengthScopeRadCnt != value)
                {
                    _lengthScopeRadCnt = value;
                    OnPropertyChanged(nameof(LengthScopeRadCnt));
                }
            }
        }

        // 制限の許容値
        private string _centerLimit;
        public string CenterLimit
        {
            get => _centerLimit;
            set
            {
                if (_centerLimit != value)
                {
                    _centerLimit = value;
                    OnPropertyChanged(nameof(CenterLimit));
                }
            }
        }

        private string _planeLimit;
        public string PlaneLimit
        {
            get => _planeLimit;
            set
            {
                if (_planeLimit != value)
                {
                    _planeLimit = value;
                    OnPropertyChanged(nameof(PlaneLimit));
                }
            }
        }

        private string _lengthLimit;
        public string LengthLimit
        {
            get => _lengthLimit;
            set
            {
                if (_lengthLimit != value)
                {
                    _lengthLimit = value;
                    OnPropertyChanged(nameof(LengthLimit));
                }
            }
        }

        private string _onlyBallCenterLimit;
        public string OnlyBallCenterLimit
        {
            get => _onlyBallCenterLimit;
            set
            {
                if (_onlyBallCenterLimit != value)
                {
                    _onlyBallCenterLimit = value;
                    OnPropertyChanged(nameof(OnlyBallCenterLimit));
                }
            }
        }

        private string _planeMeasPntLimit;
        public string PlaneMeasPntLimit
        {
            get => _planeMeasPntLimit;
            set
            {
                if (_planeMeasPntLimit != value)
                {
                    _planeMeasPntLimit = value;
                    OnPropertyChanged(nameof(PlaneMeasPntLimit));
                }
            }
        }

        private string _lengthMeasPntLimit;
        public string LengthMeasPntLimit
        {
            get => _lengthMeasPntLimit;
            set
            {
                if (_lengthMeasPntLimit != value)
                {
                    _lengthMeasPntLimit = value;
                    OnPropertyChanged(nameof(LengthMeasPntLimit));
                }
            }
        }

        private string _kidoBase;
        public string KidoBase
        {
            get => _kidoBase;
            set
            {
                if (_kidoBase != value)
                {
                    _kidoBase = value;
                    OnPropertyChanged(nameof(KidoBase));
                }
            }
        }

        private string _kidoLimit;
        public string KidoLimit
        {
            get => _kidoLimit;
            set
            {
                if (_kidoLimit != value)
                {
                    _kidoLimit = value;
                    OnPropertyChanged(nameof(KidoBase));
                }
            }
        }
        ////

        private int _gaugeIndex; // 追加(2025.8.9yori)
        public int GaugeIndex
        {
            get => _gaugeIndex;
            set
            {
                if (_gaugeIndex != value)
                {
                    _gaugeIndex = value;
                    OnPropertyChanged(nameof(GaugeIndex));
                }
            }
        }

        //外部画像ファイル追加
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

        public GaugeSettingViewModel()
        {
            ImageSource = "Image/VAC46.png"; //確認用の画像パス
        }

        public event PropertyChangedEventHandler PropertyChanged;
        private void OnPropertyChanged(string name) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
}
