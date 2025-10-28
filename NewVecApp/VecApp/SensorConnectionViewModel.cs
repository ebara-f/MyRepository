// 追加(2025.10.28yori)
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VecApp
{
    public class SensorConnectionViewModel : INotifyPropertyChanged
    {
        private string _connectScannerImage;
        public string ConnectScannerImage
        {
            get => _connectScannerImage;
            set
            {
                if (_connectScannerImage != value)
                {
                    _connectScannerImage = value;
                    OnPropertyChanged(nameof(ConnectScannerImage));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string name) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
}
