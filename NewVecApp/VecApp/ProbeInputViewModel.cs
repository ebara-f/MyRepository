using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VecApp.Properties;

namespace VecApp
{
    public class ProbeInputViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public ObservableCollection<string> BallItems { get; set; }
        public ObservableCollection<string> GaugeItems { get; set; } // 追加(2025.10.27yori)
        public ProbeInputViewModel()
        {
            BallItems = new ObservableCollection<string> { Resources.String264, Resources.String214, Resources.String215, Resources.String216, Resources.String217 }; // テーパ追加(2025.10.31yori)
            GaugeItems = new ObservableCollection<string> { Resources.String61, Resources.String62 };
            BallIndex = 0;
            GaugeIndex = 0; // 追加(2025.10.27yori)
            ImageSource = "";
        }

        private string _name;
        public string Name
        {
            get => _name;
            set
            {
                if (_name != value)
                {
                    _name = value;
                    OnPropertyChanged(nameof(Name));
                }
            }
        }

        private string _id;
        public string Id
        {
            get => _id;
            set
            {
                if (_id != value)
                {
                    _id = value;
                    OnPropertyChanged(nameof(Id));
                }
            }
        }

        // 追加(2025.10.27yori)
        private string _probeAngle;
        public string ProbeAngle
        {
            get => _probeAngle;
            set
            {
                if (_probeAngle != value)
                {
                    _probeAngle = value;
                    OnPropertyChanged(nameof(ProbeAngle));
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

        private int _ballIndex;
        public int BallIndex
        {
            get => _ballIndex;
            set
            {
                if (_ballIndex != value)
                {
                    _ballIndex = value;
                    OnPropertyChanged(nameof(BallIndex));
                }
            }
        }

        // 追加(2025.10.27yori)
        private int _gaugeIndex;
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

        private void OnPropertyChanged(string name) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
}
