using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace VecApp
{
    public class InspectionViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public ObservableCollection<string> ProbeName { get; set; } // 追加(2025.7.31yori) // pを大文字Pへ変更(2025.8.11yori)
        private int _probenameIndex; // 追加(2025.7.31yori)
        //private string _probeName; // 削除予定(2025.7.31yori)

        public InspectionViewModel() // 追加(2025.7.31yori)
        {
            ProbeName = new ObservableCollection<string> { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };
            ProbeNameIndex = 2;
        }

        // 追加(2025.7.31yori) 
        public int ProbeNameIndex
        {
            get => _probenameIndex;
            set
            {
                if (_probenameIndex != value)
                {
                    _probenameIndex = value;
                    OnPropertyChanged(nameof(ProbeNameIndex));
                }
            }
        }

        // 削除予定(2025.7.31yori)
        /*public string ProbeName
        {
            get => _probeName;
            set
            {
                if (_probeName != value)
                {
                    _probeName = value;
                    OnPropertyChanged(nameof(ProbeName));
                }
            }
        }*/

        private string _probeId;
        public string ProbeId
        {
            get => _probeId;
            set
            {
                if (_probeId != value)
                {
                    _probeId = value;
                    OnPropertyChanged(nameof(ProbeId));
                }
            }
        }

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

        private string _probeBallDiameter;
        public string ProbeBallDiameter
        {
            get => _probeBallDiameter;
            set
            {
                if (_probeBallDiameter != value)
                {
                    _probeBallDiameter = value;
                    OnPropertyChanged(nameof(ProbeBallDiameter));
                }
            }
        }

        // 追加(2025.11.14yori)
        private string _probeImage;
        public string ProbeImage
        {
            get => _probeImage;
            set
            {
                if (_probeImage != value)
                {
                    _probeImage = value;
                    OnPropertyChanged(nameof(ProbeImage));
                }
            }
        }

        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
