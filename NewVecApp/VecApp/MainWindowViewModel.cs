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

        // ボタン1、2、3の有効無効を設定する。(2025.11.19yori)
        private bool _isBtnEnabled = true; // 初期状態は有効
        public bool IsBtnEnabled
        {
            get { return _isBtnEnabled; }
            set
            {
                if (_isBtnEnabled != value)
                {
                    _isBtnEnabled = value;
                    OnPropertyChanged(nameof(IsBtnEnabled));
                }
            }
        }

        // ボタン1、2、3の不透明度を設定する。(2025.11.19yori)
        private double _btnOpacity = 1.0; // デフォルトは不透明
        public double BtnOpacity
        {
            get => _btnOpacity;
            set
            {
                if (_btnOpacity != value)
                {
                    _btnOpacity = value;
                    OnPropertyChanged(nameof(BtnOpacity));
                }
            }
        }
    }
}
