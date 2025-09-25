using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using CSH;

namespace VecApp
{
    public class ThresholdSettingViewModel : INotifyPropertyChanged
    {
        // TextBoxの有効無効を設定する。(2025.8.6yori)
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

        // TextBoxの有効無効を設定する。(2025.9.22yori)
        private bool _isTextBoxEnabled2 = true; // 初期状態は有効

        public bool IsTextBoxEnabled2
        {
            get { return _isTextBoxEnabled2; }
            set
            {
                if (_isTextBoxEnabled2 != value)
                {
                    _isTextBoxEnabled2 = value;
                    OnPropertyChanged(nameof(IsTextBoxEnabled2));
                }
            }
        }

        // 始業前点検
        private string _preCheckMaxMinThreshold;
        public string PreCheckMaxMinThreshold
        {
            get => _preCheckMaxMinThreshold;
            set
            {
                if (_preCheckMaxMinThreshold != value)
                {
                    _preCheckMaxMinThreshold = value;
                    OnPropertyChanged(nameof(PreCheckMaxMinThreshold));
                }
            }
        }

        private string _preCheckTwoSigmaThreshold;
        public string PreCheckTwoSigmaThreshold
        {
            get => _preCheckTwoSigmaThreshold;
            set
            {
                if (_preCheckTwoSigmaThreshold != value)
                {
                    _preCheckTwoSigmaThreshold = value;
                    OnPropertyChanged(nameof(PreCheckTwoSigmaThreshold));
                }
            }
        }

        private string _preCheckDistanceThreshold;
        public string PreCheckDistanceThreshold
        {
            get => _preCheckDistanceThreshold;
            set
            {
                if (_preCheckDistanceThreshold != value)
                {
                    _preCheckDistanceThreshold = value;
                    OnPropertyChanged(nameof(PreCheckDistanceThreshold));
                }
            }
        }

        // プローブ点検
        private string _probeCheckMaxMinThreshold;
        public string ProbeCheckMaxMinThreshold
        {
            get => _probeCheckMaxMinThreshold;
            set
            {
                if (_probeCheckMaxMinThreshold != value)
                {
                    _probeCheckMaxMinThreshold = value;
                    OnPropertyChanged(nameof(ProbeCheckMaxMinThreshold));
                }
            }
        }

        private string _probeCheckTwoSigmaThreshold;
        public string ProbeCheckTwoSigmaThreshold
        {
            get => _probeCheckTwoSigmaThreshold;
            set
            {
                if (_probeCheckTwoSigmaThreshold != value)
                {
                    _probeCheckTwoSigmaThreshold = value;
                    OnPropertyChanged(nameof(ProbeCheckTwoSigmaThreshold));
                }
            }
        }

        private string _probeCheckDistanceThreshold;
        public string ProbeCheckDistanceThreshold
        {
            get => _probeCheckDistanceThreshold;
            set
            {
                if (_probeCheckDistanceThreshold != value)
                {
                    _probeCheckDistanceThreshold = value;
                    OnPropertyChanged(nameof(ProbeCheckDistanceThreshold));
                }
            }
        }

        private string _probeCheckBallCenter;
        public string ProbeCheckBallCenter
        {
            get => _probeCheckBallCenter;
            set
            {
                if (_probeCheckBallCenter != value)
                {
                    _probeCheckBallCenter = value;
                    OnPropertyChanged(nameof(ProbeCheckBallCenter));
                }
            }
        }

        private string _probeCheckBallDiameter;
        public string ProbeCheckBallDiameter
        {
            get => _probeCheckBallDiameter;
            set
            {
                if (_probeCheckBallDiameter != value)
                {
                    _probeCheckBallDiameter = value;
                    OnPropertyChanged(nameof(ProbeCheckBallDiameter));
                }
            }
        }

        public ObservableCollection<string> ProbeCheckId { get; set; } // 追加(2025.7.31yori)
        private int _probecheckidIndex; // 追加(2025.7.31yori)

        public int ProbeCheckIdIndex
        {
            get => _probecheckidIndex;
            set
            {
                if (_probecheckidIndex != value)
                {
                    _probecheckidIndex = value;
                    OnPropertyChanged(nameof(ProbeCheckIdIndex));
                }
            }
        }

        // 削除予定(2025.8.1yori)
        //private string _probeCheckId;
        /*public string ProbeCheckId
        {
            get => _probeCheckId;
            set
            {
                if (_probeCheckId != value)
                {
                    _probeCheckId = value;
                    OnPropertyChanged(nameof(ProbeCheckId));
                }
            }
        }*/

        // キャリブレーション
        private string _gaugeDistanceMax;
        public string GaugeDistanceMax
        {
            get => _gaugeDistanceMax;
            set
            {
                if (_gaugeDistanceMax != value)
                {
                    _gaugeDistanceMax = value;
                    OnPropertyChanged(nameof(GaugeDistanceMax));
                }
            }
        }

        private string _gaugeDistanceMin;
        public string GaugeDistanceMin
        {
            get => _gaugeDistanceMin;
            set
            {
                if (_gaugeDistanceMin != value)
                {
                    _gaugeDistanceMin = value;
                    OnPropertyChanged(nameof(GaugeDistanceMin));
                }
            }
        }

        private string _gaugeHeightMax;
        public string GaugeHeightMax
        {
            get => _gaugeHeightMax;
            set
            {
                if (_gaugeHeightMax != value)
                {
                    _gaugeHeightMax = value;
                    OnPropertyChanged(nameof(GaugeHeightMax));
                }
            }
        }

        private string _gaugeHeightMin;
        public string GaugeHeightMin
        {
            get => _gaugeHeightMin;
            set
            {
                if (_gaugeHeightMin != value)
                {
                    _gaugeHeightMin = value;
                    OnPropertyChanged(nameof(GaugeHeightMin));
                }
            }
        }

        private string _calibrationTolerance;
        public string CalibrationTolerance
        {
            get => _calibrationTolerance;
            set
            {
                if (_calibrationTolerance != value)
                {
                    _calibrationTolerance = value;
                    OnPropertyChanged(nameof(CalibrationTolerance));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        private void OnPropertyChanged(string name) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
}
