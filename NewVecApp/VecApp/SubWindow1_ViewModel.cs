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
    /// SubWindow1のViewModel
    /// </summary>
    public partial class SubWindow1_ViewModel : ViewModel
    {
        public CSH.Status01 Sts01;

        public int INIT_FG
        {
            get { return Sts01.init_fg; }
            set
            {
                if (Sts01.init_fg != value)
                {
                    Sts01.init_fg = value;
                    OnPropertyChanged("INIT_FG");
                }
            }
        }

        public bool visible;
        public bool Visible
        {
            get { return visible; }
            set
            {
                if (visible != value)
                {
                    visible = value;
                    OnPropertyChanged("Visible");
                }
            }
        }
        /// <summary>
        /// コンストラクタ
        /// </summary>
        public SubWindow1_ViewModel()
		{
		}
	}
}
