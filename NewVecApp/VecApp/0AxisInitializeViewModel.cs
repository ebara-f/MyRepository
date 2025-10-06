// 追加(2025.10.2yori)
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VecApp
{
    public class _0AxisInitializeViewModel : INotifyPropertyChanged
    {
        private string _init0Image;
        public string Init0Image
        {
            get => _init0Image;
            set
            {
                if (_init0Image != value)
                {
                    _init0Image = value;
                    OnPropertyChanged(nameof(Init0Image));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string name) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
}
