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

        // 0軸イニシャライズボタンの有効無効を設定する。(2025.11.19yori)
        private bool _isBtn04Enabled = true; // 初期状態は有効

        public bool IsBtn04Enabled
        {
            get { return _isBtn04Enabled; }
            set
            {
                if (_isBtn04Enabled != value)
                {
                    _isBtn04Enabled = value;
                    OnPropertyChanged(nameof(IsBtn04Enabled));
                }
            }
        }

        // 0軸イニシャライズボタンの不透明度を設定する。(2025.11.19yori)
        private double _btn04Opacity = 1.0; // デフォルトは不透明
        public double Btn04Opacity
        {
            get => _btn04Opacity;
            set
            {
                if (_btn04Opacity != value)
                {
                    _btn04Opacity = value;
                    OnPropertyChanged(nameof(Btn04Opacity));
                }
            }
        }
    }
}
