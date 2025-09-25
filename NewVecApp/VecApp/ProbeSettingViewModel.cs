using System;
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
    /// <summary>
    /// Class for ProbeSetting
    /// </summary>
    public class ProbeSettingViewModel : INotifyPropertyChanged
    {
        public ObservableCollection<string> Name { get; set; } // 追加(2025.7.22yori)
        private int _nameIndex; // 追加(2025.7.22yori)
        //private string _name; // 削除予定(2025.7.22yori)

        private string _id;

        private int _ballIndex;

        private string _ballImage;

        public ObservableCollection<string> BallItems { get; set; }

        private string _diameter;

        private string _probeImage;

        public ProbeSettingViewModel()
        {
            BallItems = new ObservableCollection<string> { Resources.String212, Resources.String213 };
            Name = new ObservableCollection<string> { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }; // 追加(2025.7.24yori)
            NameIndex = 2;  // 追加(2025.7.22yori)
            //Name = "標準プローブ"; // 削除予定(2025.7.22yori)
            Id = ""; // 初期値は空白(2025.7.17yori)
            Diameter = ""; // 初期値は空白(2025.7.17yori)
            BallIndex = 1;
            BallImage = "Image/BallProbe.PNG";
            ProbeImage = "Image/standardProbeV8.PNG";
        }

        // 追加(2025.7.22yori) 
        public int NameIndex
        {
            get => _nameIndex;
            set
            {
                if (_nameIndex != value)
                {
                    _nameIndex = value;
                    OnPropertyChanged(nameof(NameIndex));
                }
            }
        }

        // 削除予定(2025.7.22yori)
        /*public string Name
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
        */

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

        public string BallImage
        {
            get => _ballImage;
            set
            {
                if (_ballImage != value)
                {
                    _ballImage = value;
                    OnPropertyChanged(nameof(BallImage));
                }
            }
        }

        public string Diameter
        {
            get => _diameter;
            set
            {
                if (_diameter != value)
                {
                    _diameter = value;
                    OnPropertyChanged(nameof(Diameter));
                }
            }
        }

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

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
