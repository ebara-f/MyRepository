// SubWindow1_ViewModel.csをもとに作成(2026.6.3yori)
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
    /// SubWindow2のViewModel
    /// </summary>
    public partial class SubWindow2_ViewModel : ViewModel
    {
        /// <summary>
        /// コンストラクタ
        /// </summary>
        public SubWindow2_ViewModel()
		{
		}

        // キャリブレーションボタンの有効無効を設定する。(2026.6.3yori)
        private bool _isBtn03Enabled = true; // 初期状態は有効
        public bool IsBtn03Enabled
        {
            get { return _isBtn03Enabled; }
            set
            {
                if (_isBtn03Enabled != value)
                {
                    _isBtn03Enabled = value;
                    OnPropertyChanged(nameof(IsBtn03Enabled));
                }
            }
        }

        // キャリブレーションボタンの不透明度を設定する。(2026.6.3yori)
        private double _btn03Opacity = 1.0; // 初期状態を不透明(1.0)
        public double Btn03Opacity
        {
            get => _btn03Opacity;
            set
            {
                if (_btn03Opacity != value)
                {
                    _btn03Opacity = value;
                    OnPropertyChanged(nameof(Btn03Opacity));
                }
            }
        }
    }
}
