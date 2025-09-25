using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VecApp
{
    public class SensorNetworkSettingViewModel : INotifyPropertyChanged
    {
        //// 追加(2025.8.17yori)
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

        private int _ipAdress1;
        public int IPAdress1
        {
            get => _ipAdress1;
            set
            {
                if (_ipAdress1 != value)
                {
                    _ipAdress1 = value;
                    OnPropertyChanged(nameof(IPAdress1));
                }
            }
        }

        private int _ipAdress2;
        public int IPAdress2
        {
            get => _ipAdress2;
            set
            {
                if (_ipAdress2 != value)
                {
                    _ipAdress2 = value;
                    OnPropertyChanged(nameof(IPAdress2));
                }
            }
        }

        private int _ipAdress3;
        public int IPAdress3
        {
            get => _ipAdress3;
            set
            {
                if (_ipAdress3 != value)
                {
                    _ipAdress3 = value;
                    OnPropertyChanged(nameof(IPAdress3));
                }
            }
        }

        private int _ipAdress4;
        public int IPAdress4
        {
            get => _ipAdress4;
            set
            {
                if (_ipAdress4 != value)
                {
                    _ipAdress4 = value;
                    OnPropertyChanged(nameof(IPAdress4));
                }
            }
        }

        private int _subnetMask1;
        public int SubnetMask1
        {
            get => _subnetMask1;
            set
            {
                if (_subnetMask1 != value)
                {
                    _subnetMask1 = value;
                    OnPropertyChanged(nameof(SubnetMask1));
                }
            }
        }

        private int _subnetMask2;
        public int SubnetMask2
        {
            get => _subnetMask2;
            set
            {
                if (_subnetMask2 != value)
                {
                    _subnetMask2 = value;
                    OnPropertyChanged(nameof(SubnetMask2));
                }
            }
        }

        private int _subnetMask3;
        public int SubnetMask3
        {
            get => _subnetMask3;
            set
            {
                if (_subnetMask3 != value)
                {
                    _subnetMask3 = value;
                    OnPropertyChanged(nameof(SubnetMask3));
                }
            }
        }

        private int _subnetMask4;
        public int SubnetMask4
        {
            get => _subnetMask4;
            set
            {
                if (_subnetMask4 != value)
                {
                    _subnetMask4 = value;
                    OnPropertyChanged(nameof(SubnetMask4));
                }
            }
        }

        private int _defaultGateway1;
        public int DefaultGateway1
        {
            get => _defaultGateway1;
            set
            {
                if (_defaultGateway1 != value)
                {
                    _defaultGateway1 = value;
                    OnPropertyChanged(nameof(DefaultGateway1));
                }
            }
        }

        private int _defaultGateway2;
        public int DefaultGateway2
        {
            get => _defaultGateway2;
            set
            {
                if (_defaultGateway2 != value)
                {
                    _defaultGateway2 = value;
                    OnPropertyChanged(nameof(DefaultGateway2));
                }
            }
        }

        private int _defaultGateway3;
        public int DefaultGateway3
        {
            get => _defaultGateway3;
            set
            {
                if (_defaultGateway3 != value)
                {
                    _defaultGateway3 = value;
                    OnPropertyChanged(nameof(DefaultGateway3));
                }
            }
        }

        private int _defaultGateway4;
        public int DefaultGateway4
        {
            get => _defaultGateway4;
            set
            {
                if (_defaultGateway4 != value)
                {
                    _defaultGateway4 = value;
                    OnPropertyChanged(nameof(DefaultGateway4));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
