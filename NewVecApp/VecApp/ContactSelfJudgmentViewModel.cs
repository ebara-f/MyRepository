using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;

namespace VecApp
{
    public class ContactSelfJudgmentViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public ContactSelfJudgmentViewModel()
        {
            ImageSource = "Image/selfchk_ja.png"; // 1-1-1.pngから変更(2025.10.2yori)
        }

        private Visibility _imageVisibility = Visibility.Visible;
        public Visibility ImageVisibility
        {
            get => _imageVisibility;
            set
            {
                if (_imageVisibility != value)
                {
                    _imageVisibility = value;
                    OnPropertyChanged(nameof(ImageVisibility));
                }
            }
        }

        private Visibility _gridVisibility = Visibility.Hidden;
        public Visibility GridVisibility
        {
            get => _gridVisibility;
            set
            {
                if (_gridVisibility != value)
                {
                    _gridVisibility = value;
                    OnPropertyChanged(nameof(GridVisibility));
                }
            }
        }

        // 追加(2025.10.3yori)
        private Visibility _gridVisibility2 = Visibility.Hidden;
        public Visibility GridVisibility2
        {
            get => _gridVisibility2;
            set
            {
                if (_gridVisibility2 != value)
                {
                    _gridVisibility2 = value;
                    OnPropertyChanged(nameof(GridVisibility2));
                }
            }
        }

        // トリガボタンの状態(2025.10.3yori)
        private string _triggerButtonStatus;
        public string TriggerButtonStatus
        {
            get => _triggerButtonStatus;
            set
            {
                if (_triggerButtonStatus != value)
                {
                    _triggerButtonStatus = value;
                    OnPropertyChanged(nameof(TriggerButtonStatus));
                }
            }
        }

        // トリガボタンの結果(2025.10.3yori)
        private string _triggerButtonResult;
        public string TriggerButtonResult
        {
            get => _triggerButtonResult;
            set
            {
                if (_triggerButtonResult != value)
                {
                    _triggerButtonResult = value;
                    OnPropertyChanged(nameof(TriggerButtonResult));
                }
            }
        }

        // キャンセルボタンの状態(2025.10.3yori)
        private string _cancelButtonStatus;
        public string CancelButtonStatus
        {
            get => _cancelButtonStatus;
            set
            {
                if (_cancelButtonStatus != value)
                {
                    _cancelButtonStatus = value;
                    OnPropertyChanged(nameof(CancelButtonStatus));
                }
            }
        }

        // キャンセルボタンの結果(2025.10.3yori)
        private string _cancelButtonResult;
        public string CancelButtonResult
        {
            get => _cancelButtonResult;
            set
            {
                if (_cancelButtonResult != value)
                {
                    _cancelButtonResult = value;
                    OnPropertyChanged(nameof(CancelButtonResult));
                }
            }
        }

        // 実行ボタンの状態(2025.10.3yori)
        private string _execButtonStatus;
        public string ExecButtonStatus
        {
            get => _execButtonStatus;
            set
            {
                if (_execButtonStatus != value)
                {
                    _execButtonStatus = value;
                    OnPropertyChanged(nameof(ExecButtonStatus));
                }
            }
        }

        // 実行ボタンの結果(2025.10.3yori)
        private string _execButtonResult;
        public string ExecButtonResult
        {
            get => _execButtonResult;
            set
            {
                if (_execButtonStatus != value)
                {
                    _execButtonResult = value;
                    OnPropertyChanged(nameof(ExecButtonResult));
                }
            }
        }

        // アームロックボタンの状態(2025.10.3yori)
        private string _lockButtonStatus;
        public string LockButtonStatus
        {
            get => _lockButtonStatus;
            set
            {
                if (_lockButtonStatus != value)
                {
                    _lockButtonStatus = value;
                    OnPropertyChanged(nameof(LockButtonStatus));
                }
            }
        }

        // アームロックボタンの結果(2025.10.3yori)
        private string _lockButtonResult;
        public string LockButtonResult
        {
            get => _lockButtonResult;
            set
            {
                if (_lockButtonResult != value)
                {
                    _lockButtonResult = value;
                    OnPropertyChanged(nameof(LockButtonResult));
                }
            }
        }

        private string _subtitleText;
        public string SubtitleText
        {
            get => _subtitleText;
            set
            {
                if (_subtitleText != value)
                {
                    _subtitleText = value;
                    OnPropertyChanged(nameof(SubtitleText));
                }
            }
        }

        private string _imageSource;
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

        // トリガボタンの結果の色(2025.10.3yori)
        private Brush _backgroundColor1;
        public Brush BackgroundColor1
        {
            get { return _backgroundColor1; }
            set
            {
                if (_backgroundColor1 != value)
                {
                    _backgroundColor1 = value;
                    OnPropertyChanged(nameof(BackgroundColor1));
                }
            }
        }

        // キャンセルボタンの結果の色(2025.10.3yori)
        private Brush _backgroundColor2;
        public Brush BackgroundColor2
        {
            get { return _backgroundColor2; }
            set
            {
                if (_backgroundColor2 != value)
                {
                    _backgroundColor2 = value;
                    OnPropertyChanged(nameof(BackgroundColor2));
                }
            }
        }

        // 実行ボタンの結果の色(2025.10.3yori)
        private Brush _backgroundColor3;
        public Brush BackgroundColor3
        {
            get { return _backgroundColor3; }
            set
            {
                if (_backgroundColor3 != value)
                {
                    _backgroundColor3 = value;
                    OnPropertyChanged(nameof(BackgroundColor3));
                }
            }
        }

        // アームロックボタンの結果の色(2025.10.3yori)
        private Brush _backgroundColor4;
        public Brush BackgroundColor4
        {
            get { return _backgroundColor4; }
            set
            {
                if (_backgroundColor4 != value)
                {
                    _backgroundColor4 = value;
                    OnPropertyChanged(nameof(BackgroundColor4));
                }
            }
        }

        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
