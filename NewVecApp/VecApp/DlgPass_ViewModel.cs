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
	/// DlgPassのViewModel
	/// </summary>
	public partial class DlgPass_ViewModel : INotifyPropertyChanged
    {
		private string _pass;
		public string Pass
		{
            get => _pass;
			set
			{
				if (_pass != value)
				{
					_pass = value;
					OnPropertyChanged(nameof(Pass));
				}
			}
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
