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
        public ProbeInputViewModel()
        {
            BallItems = new ObservableCollection<string> { Resources.String214, Resources.String215, Resources.String216, Resources.String217 };
            BallIndex = 0;
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
