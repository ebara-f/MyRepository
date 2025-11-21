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

        // 接続ボタンの有効無効を設定する。(2025.11.20yori)
        private bool _isBtn01Enabled = true; // 初期状態は有効
        public bool IsBtn01Enabled
        {
            get { return _isBtn01Enabled; }
            set
            {
                if (_isBtn01Enabled != value)
                {
                    _isBtn01Enabled = value;
                    OnPropertyChanged(nameof(IsBtn01Enabled));
                }
            }
        }

        // 接続ボタンの不透明度を設定する。(2025.11.20yori)
        private double _btn01Opacity = 1.0; // デフォルトは不透明
        public double Btn01Opacity
        {
            get => _btn01Opacity;
            set
            {
                if (_btn01Opacity != value)
                {
                    _btn01Opacity = value;
                    OnPropertyChanged(nameof(Btn01Opacity));
                }
            }
        }

        // 切断ボタンの有効無効を設定する。(2025.11.20yori)
        private bool _isBtn02Enabled = true; // 初期状態は有効
        public bool IsBtn02Enabled
        {
            get { return _isBtn02Enabled; }
            set
            {
                if (_isBtn02Enabled != value)
                {
                    _isBtn02Enabled = value;
                    OnPropertyChanged(nameof(IsBtn02Enabled));
                }
            }
        }

        // 切断ボタンの不透明度を設定する。(2025.11.20yori)
        private double _btn02Opacity = 1.0; // デフォルトは不透明
        public double Btn02Opacity
        {
            get => _btn02Opacity;
            set
            {
                if (_btn02Opacity != value)
                {
                    _btn02Opacity = value;
                    OnPropertyChanged(nameof(Btn02Opacity));
                }
            }
        }

        // イニシャライズボタンの有効無効を設定する。(2025.11.20yori)
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

        // イニシャライズボタンの不透明度を設定する。(2025.11.20yori)
        private double _btn03Opacity = 1.0; // デフォルトは不透明
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

        // モード切替ボタンの不透明度を設定する。(2025.11.20yori)
        private double _btn05Opacity = 1.0; // デフォルトは不透明
        public double Btn05Opacity
        {
            get => _btn05Opacity;
            set
            {
                if (_btn05Opacity != value)
                {
                    _btn05Opacity = value;
                    OnPropertyChanged(nameof(Btn05Opacity));
                }
            }
        }

        // モード切替ボタンの有効無効を設定する。(2025.11.20yori)
        private bool _isBtn05Enabled = true; // 初期状態は有効

        public bool IsBtn05Enabled
        {
            get { return _isBtn05Enabled; }
            set
            {
                if (_isBtn05Enabled != value)
                {
                    _isBtn05Enabled = value;
                    OnPropertyChanged(nameof(IsBtn05Enabled)); // 誤記(IsBtn03Enabled)修正(2025.11.21yori)
                }
            }
        }
    }
}
