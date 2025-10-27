using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace VecApp
{
    /// <summary>
    /// Class for Marks in InitializePanel
    /// </summary>
    public class InitializeMarkViewModel : INotifyPropertyChanged
    {
        private string _text;

        private Visibility _visibility;

        private int _x;

        private int _y;

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

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

    /// <summary>
    /// Class for Labels in InitializePanel
    /// </summary>
    public class InitializeLabelViewModel : INotifyPropertyChanged
    {
        private string _text;

        private Visibility _visibility;

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

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

    /// <summary>
    /// Class for InitializePanel
    /// </summary>
    public class InitializeViewModel : INotifyPropertyChanged
    {
        public ObservableCollection<InitializeMarkViewModel> Marks { get; set; }

        public ObservableCollection<InitializeLabelViewModel> Labels { get; set; }

        private string _imageSource;

        private string _slideStatusText;

        private int _slideSwitch;

        public InitializeViewModel()
        {
            Marks = new ObservableCollection<InitializeMarkViewModel>
            {
                new InitializeMarkViewModel { Text = "⓪", Visibility = Visibility.Visible, X = 470, Y = 200 }, // 追加(2025.7.16yori)
                new InitializeMarkViewModel { Text = "①", Visibility = Visibility.Hidden, X = 450, Y = 160 }, // Visible→Hiddenへ変更(2025.7.16yori)
                new InitializeMarkViewModel { Text = "②", Visibility = Visibility.Hidden, X = 395, Y = 30 }, // Visible→Hiddenへ変更(2025.7.16yori)
                new InitializeMarkViewModel { Text = "③", Visibility = Visibility.Hidden, X = 310, Y = 0 }, // Visible→Hiddenへ変更(2025.7.16yori)
                new InitializeMarkViewModel { Text = "④", Visibility = Visibility.Hidden, X = 330, Y = 100 }, // Visible→Hiddenへ変更(2025.7.16yori)
                new InitializeMarkViewModel { Text = "⑤", Visibility = Visibility.Hidden, X = 230, Y = 140 }, // Visible→Hiddenへ変更(2025.7.16yori)
                new InitializeMarkViewModel { Text = "⑥", Visibility = Visibility.Hidden, X = 340, Y = 160 }, // Visible→Hiddenへ変更(2025.7.16yori)
            };

            Labels = new ObservableCollection<InitializeLabelViewModel>
            {
                new InitializeLabelViewModel { Text = "0", Visibility = Visibility.Hidden }, // 追加(2025.7.16yori)
                new InitializeLabelViewModel { Text = "1", Visibility = Visibility.Hidden }, // Visible→Hiddenへ変更(2025.7.16yori)
                new InitializeLabelViewModel { Text = "2", Visibility = Visibility.Hidden }, // Visible→Hiddenへ変更(2025.7.16yori)
                new InitializeLabelViewModel { Text = "3", Visibility = Visibility.Hidden }, // Visible→Hiddenへ変更(2025.7.16yori)
                new InitializeLabelViewModel { Text = "4", Visibility = Visibility.Hidden }, // Visible→Hiddenへ変更(2025.7.16yori)
                new InitializeLabelViewModel { Text = "5", Visibility = Visibility.Hidden }, // Visible→Hiddenへ変更(2025.7.16yori)
                new InitializeLabelViewModel { Text = "6", Visibility = Visibility.Hidden }, // Visible→Hiddenへ変更(2025.7.16yori)
            };

            ImageSource = ""; // 初期画像はハード側判別する。(Image/init_machine10.PNG削除)(2025.7.16yori)
            SlideSwitch = true; // 初期値はオン(2025.7.30yori)
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

        public bool SlideSwitch
        {
            get => _SlideSwitch == 1;
            set
            {
                if (value)
                {
                    _SlideSwitch = 1;
                    _SlideText = "オン";
                }
                else
                {
                    _SlideSwitch = 0;
                    _SlideText = "オフ";
                }
            }
        }

        public int _SlideSwitch
        {
            get => _slideSwitch;
            set
            {
                if (_slideSwitch != value)
                {
                    _slideSwitch = value;
                    OnPropertyChanged(nameof(_SlideSwitch));
                }
            }
        }

        public string _SlideText
        {
            get => _slideStatusText;
            set
            {
                if (_slideStatusText != value)
                {
                    _slideStatusText = value;
                    OnPropertyChanged(nameof(_SlideText));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
