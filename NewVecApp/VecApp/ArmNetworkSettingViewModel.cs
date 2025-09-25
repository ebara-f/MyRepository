using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VecApp
{
    public class ArmNetworkSettingViewModel : INotifyPropertyChanged
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

        private int _portNumber;
        public int PortNumber
        {
            get => _portNumber;
            set
            {
                if (_portNumber != value)
                {
                    _portNumber = value;
                    OnPropertyChanged(nameof(PortNumber));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
