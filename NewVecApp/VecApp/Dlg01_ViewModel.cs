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
	/// Dlg01のViewModel
	/// </summary>
	public partial class Dlg01_ViewModel : ViewModel
	{
		// プロパティ
		private int _a = 0;
		public int A
		{
			get { return _a; }
			set
			{
				if (_a != value)
				{
					_a = value;
					OnPropertyChanged("A");
				}
			}
		}

		private double _b = 0.0;
		public double B
		{
			get { return _b; }
			set
			{
				if (_b != value)
				{
					_b = value;
					OnPropertyChanged("B");
				}
			}
		}

		private string _c = "";
		public string C
		{
			get { return _c; }
			set
			{
				if (_c != value)
				{
					_c = value;
					OnPropertyChanged("C");
				}
			}
		}

		private int _d = 0;
		public int D
		{
			get { return _d; }
			set
			{
				if (_d != value)
				{
					_d = value;
					OnPropertyChanged("D");
				}
			}
		}

		private double _e = 0.0;
		public double E
		{
			get { return _e; }
			set
			{
				if (_e != value)
				{
					_e = value;
					OnPropertyChanged("E");
				}
			}
		}

		private string _f = "";
		public string F
		{
			get { return _f; }
			set
			{
				if (_f != value)
				{
					_f = value;
					OnPropertyChanged("F");
				}
			}
		}

		/// <summary>
		/// コンストラクタ
		/// </summary>
		public Dlg01_ViewModel()
		{
		}
	}
}
