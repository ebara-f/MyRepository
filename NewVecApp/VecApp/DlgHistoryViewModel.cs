using CSH;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using static System.Runtime.InteropServices.JavaScript.JSType;
using System.Windows.Media;

namespace VecApp
{
	/// <summary>
	/// Dlg01のViewModel
	/// </summary>
	public partial class DlgHistoryViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public DlgHistoryViewModel()
        {
            
        }

		private string _f;// = "History";
		public string TextHistory
        {
			get { return _f; }
			set
			{
				if (_f != value)
				{
					_f = value;
					OnPropertyChanged(nameof(TextHistory));
				}
			}
		}


        private void OnPropertyChanged(string name) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
}
