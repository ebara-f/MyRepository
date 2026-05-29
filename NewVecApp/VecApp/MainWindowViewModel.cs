using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Windows;
using System.Windows.Input;

namespace VecApp
{
    /// <summary>
    /// MainWindowのViewModel
    /// </summary>
    public class MainWindowViewModel : ViewModel
    {
        public CSH.Status01 Sts01;

        public int MODE
        {
            get { return Sts01.mode; }
            set
            {
                if (Sts01.mode != value)
                {
                    Sts01.mode = value;
                    OnPropertyChanged("MODE");
                }
            }
        }

        public int CON_FG
        {
            get { return Sts01.connect_fg; }
            set
            {
                if (Sts01.connect_fg != value)
                {
                    Sts01.connect_fg = value;
                    OnPropertyChanged("CON_FG");
                }
            }
        }

        public int WARM_FG
        {
            get { return Sts01.warm_fg; }
            set
            {
                if (Sts01.warm_fg != value)
                {
                    Sts01.warm_fg = value;
                    OnPropertyChanged("WARM_FG");
                }
            }
        }

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

        public double TMP0
        {
            get { return Sts01.tempature[0]; }
            set
            {
                if (Sts01.tempature[0] != value)
                {
                    Sts01.tempature[0] = value;
                    OnPropertyChanged("TMP0");
                }
            }
        }

        public double TMP1
        {
            get { return Sts01.tempature[1]; }
            set
            {
                if (Sts01.tempature[1] != value)
                {
                    Sts01.tempature[1] = value;
                    OnPropertyChanged("TMP1");
                }
            }
        }

        public double TMP2
        {
            get { return Sts01.tempature[2]; }
            set
            {
                if (Sts01.tempature[2] != value)
                {
                    Sts01.tempature[2] = value;
                    OnPropertyChanged("TMP2");
                }
            }
        }

        public double TMP3
        {
            get { return Sts01.tempature[3]; }
            set
            {
                if (Sts01.tempature[3] != value)
                {
                    Sts01.tempature[3] = value;
                    OnPropertyChanged("TMP3");
                }
            }
        }

        public double TMP4
        {
            get { return Sts01.tempature[4]; }
            set
            {
                if (Sts01.tempature[4] != value)
                {
                    Sts01.tempature[4] = value;
                    OnPropertyChanged("TMP4");
                }
            }
        }

        public double TMP5
        {
            get { return Sts01.tempature[5]; }
            set
            {
                if (Sts01.tempature[5] != value)
                {
                    Sts01.tempature[5] = value;
                    OnPropertyChanged("TMP5");
                }
            }
        }

        public double TMP6
        {
            get { return Sts01.tempature[6]; }
            set
            {
                if (Sts01.tempature[6] != value)
                {
                    Sts01.tempature[6] = value;
                    OnPropertyChanged("TMP6");
                }
            }
        }

        // プロパティ
        private double _a = 0;
        public double A
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

        private string _b = "";
        public string B
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

        /// <summary>
        /// コンストラクタ
        /// </summary>
        public MainWindowViewModel()
		{
            Sts01 = new CSH.Status01();
            Sts01.tempature = new double[7];

        }

        // ボタン1の有効無効を設定する。(2026.2.13yori)
        // 有効(2026.5.14yori)
        private bool _isBtn01Enabled = true;
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

        // ボタン2の有効無効を設定する。(2026.5.14yori)
        private bool _isBtn02Enabled = false; // true→false(2026.5.28yori)
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

        // ボタン3の有効無効を設定する。(2026.5.14yori)
        private bool _isBtn03Enabled = false;
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

        // ボタン4の有効無効を設定する。(2026.5.28yori)
        private bool _isBtn04Enabled = true;
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

        // ボタン1の不透明度を設定する。上記より分離した。(2026.2.13yori)
        // _btn01Opacity = 0.25→1.0(2026.5.14yori)
        private double _btn01Opacity = 1.0;
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

        // ボタン2の不透明度を設定する。(2026.5.14yori)
        private double _btn02Opacity = 0.25; // 1.0→0.25(2026.5.28yori)
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

        // ボタン3の不透明度を設定する。(2026.5.14yori)
        private double _btn03Opacity = 0.25;
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

        // ボタン4の不透明度を設定する。(2026.5.28yori)
        private double _btn04Opacity = 1.0;
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
