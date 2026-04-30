// DlgMI_ViewModel.cs追加(Dlg03_ViewModel.csをコピーして作成)(2026.4.14)
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Windows;
using System.Windows.Threading;

namespace VecApp
{
    public partial class DlgMI_ViewModel : ViewModel
    {
        public ObservableCollection<InitializeMarkViewModel> Marks { get; set; }

        private string _imageSource;

        private string _text;

        private Visibility _visibility;

        private int _x;

        private int _y;

        public DlgMI_ViewModel()
        {
            Marks = new ObservableCollection<InitializeMarkViewModel>
            {
                new InitializeMarkViewModel { Text = "⓪", Visibility = Visibility.Visible, X = 430, Y = 365 },
                new InitializeMarkViewModel { Text = "①", Visibility = Visibility.Visible, X = 500, Y = 315 },
                new InitializeMarkViewModel { Text = "②", Visibility = Visibility.Visible, X = 420, Y = 60 },
                new InitializeMarkViewModel { Text = "③", Visibility = Visibility.Visible, X = 305, Y = 30 },
                new InitializeMarkViewModel { Text = "④", Visibility = Visibility.Visible, X = 250, Y = 190 },
                new InitializeMarkViewModel { Text = "⑤", Visibility = Visibility.Visible, X = 340, Y = 245 },
                new InitializeMarkViewModel { Text = "⑥", Visibility = Visibility.Visible, X = 180, Y = 290 },
            };
        }

        public string ImageSource
        {
            get => _imageSource;
            set
            {
                if (_imageSource != value)
                {
                    _imageSource = value;
                    OnPropertyChanged(nameof(ImageSource));
                }
            }
        }

        public string Text
        {
            get => _text;
            set
            {
                if (_text != value)
                {
                    _text = value;
                    OnPropertyChanged(nameof(Text));
                }
            }
        }

        public Visibility Visibility
        {
            get => _visibility;
            set
            {
                if (_visibility != value)
                {
                    _visibility = value;
                    OnPropertyChanged(nameof(Visibility));
                }
            }
        }

        public int X
        {
            get => _x;
            set
            {
                if (_x != value)
                {
                    _x = value;
                    OnPropertyChanged(nameof(X));
                }
            }
        }

        public int Y
        {
            get => _y;
            set
            {
                if (_y != value)
                {
                    _y = value;
                    OnPropertyChanged(nameof(Y));
                }
            }
        }
    }
}
