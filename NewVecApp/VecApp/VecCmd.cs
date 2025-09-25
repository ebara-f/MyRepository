using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VecApp
{
    /// <summary>
	/// コマンド一覧
	/// </summary>
    static class VecCmd
    {
        public const int None = 0;              // 指示なし

        public const int MainWnd_Close = 1;     // MainWindowを閉じる
        public const int MainWnd_Btn01 = 2;     // MainWindowのボタン01を押す
        public const int MainWnd_Btn02 = 3;     // MainWindowのボタン02を押す
        public const int MainWnd_Btn03 = 4;     // MainWindowのボタン03を押す

        public const int Dlg01_Close   = 5;     // Dialog01を閉じる
        public const int Dlg01_Btn01   = 6;     // Dialog01のボタン01を押す
        public const int Dlg01_Btn02   = 7;     // Dialog01のボタン02を押す
        public const int Dlg01_Btn03   = 8;     // Dialog01のボタン03を押す

        public const int Dlg02_Close   = 9;     // Dialog02を閉じる
        public const int Dlg02_Btn01   = 10;    // Dialog02のボタン01を押す

        public const int Dlg03_Close   = 11;     // Dialog03を閉じる
    }
}
