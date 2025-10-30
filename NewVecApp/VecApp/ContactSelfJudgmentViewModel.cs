using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using static VecApp.ContactSelfJudgmentViewModel;

namespace VecApp
{
    // 自己診断項目(2025.10.5yori)
    public enum JudgeItems
    {
        Button,
        FirmVer,
        Cummunication,
        CounterVer,
        Count1,
        Count2,
        ZXScale,
        Temp
    }

    public class ContactSelfJudgmentViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public long[] Count { get; set; } // カウンタ値(2025.10.6yori)

        public ContactSelfJudgmentViewModel()
        {
            ImageSource = "Image/selfchk_ja.png"; // 1-1-1.pngから変更(2025.10.2yori)
            Count = new long[] { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // カウンタ初期値(2025.10.6yori)
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

        // 追加(2025.10.4yori)
        private Visibility _gridVisibility3 = Visibility.Hidden;
        public Visibility GridVisibility3
        {
            get => _gridVisibility3;
            set
            {
                if (_gridVisibility3 != value)
                {
                    _gridVisibility3 = value;
                    OnPropertyChanged(nameof(GridVisibility3));
                }
            }
        }

        // 追加(2025.10.5yori)
        private Visibility _gridVisibility4 = Visibility.Hidden;
        public Visibility GridVisibility4
        {
            get => _gridVisibility4;
            set
            {
                if (_gridVisibility4 != value)
                {
                    _gridVisibility4 = value;
                    OnPropertyChanged(nameof(GridVisibility4));
                }
            }
        }

        // 追加(2025.10.5yori)
        private Visibility _gridVisibility5 = Visibility.Hidden;
        public Visibility GridVisibility5
        {
            get => _gridVisibility5;
            set
            {
                if (_gridVisibility5 != value)
                {
                    _gridVisibility5 = value;
                    OnPropertyChanged(nameof(GridVisibility5));
                }
            }
        }

        // 追加(2025.10.5yori)
        private Visibility _gridVisibility6 = Visibility.Hidden;
        public Visibility GridVisibility6
        {
            get => _gridVisibility6;
            set
            {
                if (_gridVisibility6 != value)
                {
                    _gridVisibility6 = value;
                    OnPropertyChanged(nameof(GridVisibility6));
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

        // 結果の色0(2025.10.4yori)
        private Brush _backgroundColor0;
        public Brush BackgroundColor0
        {
            get { return _backgroundColor0; }
            set
            {
                if (_backgroundColor0 != value)
                {
                    _backgroundColor0 = value;
                    OnPropertyChanged(nameof(BackgroundColor0));
                }
            }
        }

        // 結果の色1(2025.10.4yori)
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

        // 結果の色2(2025.10.4yori)
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

        // 結果の色3(2025.10.4yori)
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

        // 結果の色4(2025.10.4yori)
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

        // 結果の色5(2025.10.4yori)
        private Brush _backgroundColor5;
        public Brush BackgroundColor5
        {
            get { return _backgroundColor5; }
            set
            {
                if (_backgroundColor5 != value)
                {
                    _backgroundColor5 = value;
                    OnPropertyChanged(nameof(BackgroundColor5));
                }
            }
        }

        // 結果の色6(2025.10.4yori)
        private Brush _backgroundColor6;
        public Brush BackgroundColor6
        {
            get { return _backgroundColor6; }
            set
            {
                if (_backgroundColor6 != value)
                {
                    _backgroundColor6 = value;
                    OnPropertyChanged(nameof(BackgroundColor6));
                }
            }
        }

        // 診断項目(2025.10.4yori)
        private JudgeItems _item;
        public JudgeItems Item
        {
            get => _item;
            set
            {
                if (_item != value)
                {
                    _item = value;
                    OnPropertyChanged(nameof(Item));
                }
            }
        }

        // ファームウェアバージョン(2025.10.4yori)
        private string _firmVer;
        public string FirmVer
        {
            get => _firmVer;
            set
            {
                if (_firmVer != value)
                {
                    _firmVer = value;
                    OnPropertyChanged(nameof(FirmVer));
                }
            }
        }

        // カウンタNo.0の結果(2025.10.4yori)
        private string _counterNo0Result;
        public string CounterNo0Result
        {
            get => _counterNo0Result;
            set
            {
                if (_counterNo0Result != value)
                {
                    _counterNo0Result = value;
                    OnPropertyChanged(nameof(CounterNo0Result));
                }
            }
        }

        // カウンタNo.1の結果(2025.10.4yori)
        private string _counterNo1Result;
        public string CounterNo1Result
        {
            get => _counterNo1Result;
            set
            {
                if (_counterNo1Result != value)
                {
                    _counterNo1Result = value;
                    OnPropertyChanged(nameof(CounterNo1Result));
                }
            }
        }

        // カウンタNo.2の結果(2025.10.4yori)
        private string _counterNo2Result;
        public string CounterNo2Result
        {
            get => _counterNo2Result;
            set
            {
                if (_counterNo2Result != value)
                {
                    _counterNo2Result = value;
                    OnPropertyChanged(nameof(CounterNo2Result));
                }
            }
        }

        // カウンタNo.3の結果(2025.10.4yori)
        private string _counterNo3Result;
        public string CounterNo3Result
        {
            get => _counterNo3Result;
            set
            {
                if (_counterNo3Result != value)
                {
                    _counterNo3Result = value;
                    OnPropertyChanged(nameof(CounterNo3Result));
                }
            }
        }

        // カウンタNo.4の結果(2025.10.4yori)
        private string _counterNo4Result;
        public string CounterNo4Result
        {
            get => _counterNo4Result;
            set
            {
                if (_counterNo4Result != value)
                {
                    _counterNo4Result = value;
                    OnPropertyChanged(nameof(CounterNo4Result));
                }
            }
        }

        // カウンタNo.5の結果(2025.10.4yori)
        private string _counterNo5Result;
        public string CounterNo5Result
        {
            get => _counterNo5Result;
            set
            {
                if (_counterNo5Result != value)
                {
                    _counterNo5Result = value;
                    OnPropertyChanged(nameof(CounterNo5Result));
                }
            }
        }

        // カウンタNo.6の結果(2025.10.4yori)
        private string _counterNo6Result;
        public string CounterNo6Result
        {
            get => _counterNo6Result;
            set
            {
                if (_counterNo6Result != value)
                {
                    _counterNo6Result = value;
                    OnPropertyChanged(nameof(CounterNo6Result));
                }
            }
        }

        // カウンタNo.8の判定(2025.10.5yori)
        private string _counterNo8Judge;
        public string CounterNo8Judge
        {
            get => _counterNo8Judge;
            set
            {
                if (_counterNo8Judge != value)
                {
                    _counterNo8Judge = value;
                    OnPropertyChanged(nameof(CounterNo8Judge));
                }
            }
        }

        // カウンタNo.9の判定(2025.10.6yori)
        private string _counterNo9Judge;
        public string CounterNo9Judge
        {
            get => _counterNo9Judge;
            set
            {
                if (_counterNo9Judge != value)
                {
                    _counterNo9Judge = value;
                    OnPropertyChanged(nameof(CounterNo9Judge));
                }
            }
        }

        // カウンタNo.8のVer.(2025.10.6yori)
        private string _counterNo8Ver;
        public string CounterNo8Ver
        {
            get => _counterNo8Ver;
            set
            {
                if (_counterNo8Ver != value)
                {
                    _counterNo8Ver = value;
                    OnPropertyChanged(nameof(CounterNo8Ver));
                }
            }
        }

        // カウンタNo.9のVer.(2025.10.6yori)
        private string _counterNo9Ver;
        public string CounterNo9Ver
        {
            get => _counterNo9Ver;
            set
            {
                if (_counterNo9Ver != value)
                {
                    _counterNo9Ver = value;
                    OnPropertyChanged(nameof(CounterNo9Ver));
                }
            }
        }

        // カウンタ診断項目(2025.10.4yori)
        private string _counterItem;
        public string CounterItem
        {
            get => _counterItem;
            set
            {
                if (_counterItem != value)
                {
                    _counterItem = value;
                    OnPropertyChanged(nameof(CounterItem));
                }
            }
        }

        // No.0カウント値(2025.10.4yori)
        private string _counterNo0Count;
        public string CounterNo0Count
        {
            get => _counterNo0Count;
            set
            {
                if (_counterNo0Count != value)
                {
                    _counterNo0Count = value;
                    OnPropertyChanged(nameof(CounterNo0Count));
                }
            }
        }

        // No.1カウント値(2025.10.4yori)
        private string _counterNo1Count;
        public string CounterNo1Count
        {
            get => _counterNo1Count;
            set
            {
                if (_counterNo1Count != value)
                {
                    _counterNo1Count = value;
                    OnPropertyChanged(nameof(CounterNo1Count));
                }
            }
        }

        // No.2カウント値(2025.10.4yori)
        private string _counterNo2Count;
        public string CounterNo2Count
        {
            get => _counterNo2Count;
            set
            {
                if (_counterNo2Count != value)
                {
                    _counterNo2Count = value;
                    OnPropertyChanged(nameof(CounterNo2Count));
                }
            }
        }

        // No.3カウント値(2025.10.4yori)
        private string _counterNo3Count;
        public string CounterNo3Count
        {
            get => _counterNo3Count;
            set
            {
                if (_counterNo3Count != value)
                {
                    _counterNo3Count = value;
                    OnPropertyChanged(nameof(CounterNo3Count));
                }
            }
        }

        // No.4カウント値(2025.10.4yori)
        private string _counterNo4Count;
        public string CounterNo4Count
        {
            get => _counterNo4Count;
            set
            {
                if (_counterNo4Count != value)
                {
                    _counterNo4Count = value;
                    OnPropertyChanged(nameof(CounterNo4Count));
                }
            }
        }

        // No.5カウント値(2025.10.4yori)
        private string _counterNo5Count;
        public string CounterNo5Count
        {
            get => _counterNo5Count;
            set
            {
                if (_counterNo5Count != value)
                {
                    _counterNo5Count = value;
                    OnPropertyChanged(nameof(CounterNo5Count));
                }
            }
        }

        // No.6カウント値(2025.10.4yori)
        private string _counterNo6Count;
        public string CounterNo6Count
        {
            get => _counterNo6Count;
            set
            {
                if (_counterNo6Count != value)
                {
                    _counterNo6Count = value;
                    OnPropertyChanged(nameof(CounterNo6Count));
                }
            }
        }

        // No.8カウント値(2025.10.5yori)
        private string _counterNo8Count;
        public string CounterNo8Count
        {
            get => _counterNo8Count;
            set
            {
                if (_counterNo8Count != value)
                {
                    _counterNo8Count = value;
                    OnPropertyChanged(nameof(CounterNo8Count));
                }
            }
        }

        // No.8カウント値(2025.10.5yori)
        private string _counterNo9Count;
        public string CounterNo9Count
        {
            get => _counterNo9Count;
            set
            {
                if (_counterNo9Count != value)
                {
                    _counterNo9Count = value;
                    OnPropertyChanged(nameof(CounterNo9Count));
                }
            }
        }

        // アーム内温度A(2025.10.5yori)
        private string _armTempA;
        public string ArmTempA
        {
            get => _armTempA;
            set
            {
                if (_armTempA != value)
                {
                    _armTempA = value;
                    OnPropertyChanged(nameof(ArmTempA));
                }
            }
        }

        // アーム内温度B(2025.10.5yori)
        private string _armTempB;
        public string ArmTempB
        {
            get => _armTempB;
            set
            {
                if (_armTempB != value)
                {
                    _armTempB = value;
                    OnPropertyChanged(nameof(ArmTempB));
                }
            }
        }

        // アーム内温度C(2025.10.5yori)
        private string _armTempC;
        public string ArmTempC
        {
            get => _armTempC;
            set
            {
                if (_armTempC != value)
                {
                    _armTempC = value;
                    OnPropertyChanged(nameof(ArmTempC));
                }
            }
        }

        // 校正時温度A(2025.10.5yori)
        private string _calTempA;
        public string CalTempA
        {
            get => _calTempA;
            set
            {
                if (_calTempA != value)
                {
                    _calTempA = value;
                    OnPropertyChanged(nameof(CalTempA));
                }
            }
        }

        // 校正時温度B(2025.10.5yori)
        private string _calTempB;
        public string CalTempB
        {
            get => _calTempB;
            set
            {
                if (_calTempB != value)
                {
                    _calTempB = value;
                    OnPropertyChanged(nameof(CalTempB));
                }
            }
        }

        // 校正時温度C(2025.10.5yori)
        private string _calTempC;
        public string CalTempC
        {
            get => _calTempC;
            set
            {
                if (_calTempC != value)
                {
                    _calTempC = value;
                    OnPropertyChanged(nameof(CalTempC));
                }
            }
        }

        protected void OnPropertyChanged(string propertyName) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
