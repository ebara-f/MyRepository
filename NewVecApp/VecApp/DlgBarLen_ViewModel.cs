using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Windows.Threading;

namespace VecApp
{
	/// <summary>
	/// DlgBarLenのViewModel
	/// </summary>
	public partial class DlgBarLen_ViewModel : INotifyPropertyChanged
    {
		private string _length;
		public string Length
		{
            get => _length;
			set
			{
				if (_length != value)
				{
					_length = value;
					OnPropertyChanged(nameof(Length));
				}
			}
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
