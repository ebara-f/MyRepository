using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Security.AccessControl;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace VecApp
{
    public class ArmTypeSettingViewModel : INotifyPropertyChanged
    {
        public ObservableCollection<string> ArmTypeItems { get; set; }
        public ArmTypeSettingViewModel()
        {
            ArmTypeItems = new ObservableCollection<string> { "VAR700M", "VAR700L", "VAR800M", "VAR800L", "BK100S", "BK100-NC" }; // "VAR700M", "VAR700L", "VAR700LT", "VAR600", "VAR600MII"削除、"BK100S", "BK100NC"追加(2025.8.30yori) // "VAR700M", "VAR700L"追加(2025.11.1yori)
            ArmTypeIndex = 0;
            ArmTypeItem = "VAR700M"; // 追加(2025.9.1yori) // "VAR800M"から変更(2025.11.1yori)
            ArmTypeImage = "Image/init_V7.PNG"; //画像変更(他の画像と共通で使用する)(2025.8.30yori) // init_machine10.pngから変更(2025.11.1yori)
        }

        private int _armTypeIndex;
        public int ArmTypeIndex
        {
            get => _armTypeIndex;
            set
            {
                if (_armTypeIndex != value)
                {
                    _armTypeIndex = value;
                    OnPropertyChanged(nameof(ArmTypeIndex));
                }
            }
        }

        // 追加(2025.9.1yori)
        private string _armTypeItem;
        public string ArmTypeItem
        {
            get => _armTypeItem;
            set
            {
                if (_armTypeItem != value)
                {
                    _armTypeItem = value;
                    OnPropertyChanged(nameof(ArmTypeItem));
                }
            }
        }

        private string  _armTypeImage;
        public string ArmTypeImage
        {
            get => _armTypeImage;
            set
            {
                if (_armTypeImage != value)
                {
                    _armTypeImage = value;
                    OnPropertyChanged(nameof(ArmTypeImage));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
