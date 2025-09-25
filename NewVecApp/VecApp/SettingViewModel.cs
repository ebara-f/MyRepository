using CSH;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VecApp
{
    public class SettingViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private string _ballStylusDiameter;
        public string BallStylusDiameter
        {
            get => _ballStylusDiameter;
            set
            {
                if (_ballStylusDiameter != value)
                {
                    _ballStylusDiameter = value;
                    OnPropertyChanged(nameof(BallStylusDiameter));
                }
            }
        }

        private string _distance;
        public string Distance
        {
            get => _distance;
            set
            {
                if (_distance != value)
                {
                    _distance = value;
                    OnPropertyChanged(nameof(Distance));
                }
            }
        }

        private string _ballGaugeDiameter;
        public string BallGaugeDiameter
        {
            get => _ballGaugeDiameter;
            set
            {
                if (_ballGaugeDiameter != value)
                {
                    _ballGaugeDiameter = value;
                    OnPropertyChanged(nameof(BallGaugeDiameter));
                }
            }
        }

        private string _ballDiameter;
        public string BallDiameter
        {
            get => _ballDiameter;
            set
            {
                if (_ballDiameter != value)
                {
                    _ballDiameter = value;
                    OnPropertyChanged(nameof(BallDiameter));
                }
            }
        }

        private string _initialValue;
        public string InitialValue
        {
            get => _initialValue;
            set
            {
                if (_initialValue != value)
                {
                    _initialValue = value;
                    OnPropertyChanged(nameof(InitialValue));
                }
            }
        }

        private void OnPropertyChanged(string name) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));

        // Viewと関連付かない変数
        public CalibPara CalibPara = new CalibPara(); // 2025.9.24 add eba
    }
}
