using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace VecApp
{
    /// <summary>
    /// Windowメッセージ ユーティリティ
    /// </summary>
    static class UsrMsg
    {
        /// <summary>
        /// メッセージ送信関数
        /// </summary>
        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, IntPtr wParam, IntPtr lParam);

        [DllImport("user32.dll")]
        public static extern int PostMessage(IntPtr hWnd, int Msg, IntPtr wParam, IntPtr lParam);

        
        /// <summary>
        /// メッセージ送信関数
        /// </summary>
        unsafe public static void SendMsg(IntPtr hWnd, int Msg)
        {
            SendMessage( hWnd, Msg, 0, 0 );
        }

        unsafe public static void PostMsg(IntPtr hWnd, int Msg)
        {
            PostMessage( hWnd, Msg, 0, 0 );
        }

        /// <summary>
        /// ユーザーメッセージ一覧
        /// </summary>
        public const int WM_USER = 0x0400;

        public const int WM_MainWnd_Close = WM_USER + 1;
        public const int WM_MainWnd_Btn01 = WM_USER + 2;
        public const int WM_MainWnd_Btn02 = WM_USER + 3;
        public const int WM_MainWnd_Btn03 = WM_USER + 4;

        public const int WM_Dlg01_Close   = WM_USER + 5;
        public const int WM_Dlg01_Btn01   = WM_USER + 6;
        public const int WM_Dlg01_Btn02   = WM_USER + 7;
        public const int WM_Dlg01_Btn03   = WM_USER + 8;

        public const int WM_Dlg02_Close   = WM_USER + 9;
        public const int WM_Dlg02_Btn01   = WM_USER + 10;

        public const int WM_Dlg03_Close   = WM_USER + 11;

        public const int WM_UpdateData1 = WM_USER + 12;   // 2025.5.22 add eba

        public const int WM_SubWnd01_Close = WM_USER + 13;  // 2025.6.3 add eba
        public const int WM_SubWnd01_Btn01 = WM_USER + 14;  // 2025.6.3 add eba
        public const int WM_SubWnd01_Btn02 = WM_USER + 15;  // 2025.6.3 add eba
        public const int WM_SubWnd01_Btn03 = WM_USER + 16;  // 2025.6.3 add eba
        public const int WM_SubWnd01_Btn04 = WM_USER + 17;  // 2025.6.3 add eba
        public const int WM_SubWnd01_Btn05 = WM_USER + 18;  // 2025.6.3 add eba

        public const int WM_SubWnd02_Close = WM_USER + 19;  // 2025.6.11 add yori
        public const int WM_SubWnd02_Btn01 = WM_USER + 20;  // 2025.6.11 add yori
        public const int WM_SubWnd02_Btn02 = WM_USER + 21;  // 2025.6.11 add yori
        public const int WM_SubWnd02_Btn03 = WM_USER + 22;  // 2025.6.11 add yori
        public const int WM_SubWnd02_Btn04 = WM_USER + 23;  // 2025.6.11 add yori
        public const int WM_SubWnd02_Btn05 = WM_USER + 24;  // 2025.6.11 add yori
        public const int WM_SubWnd02_Btn06 = WM_USER + 25;  // 2025.6.11 add yori

        public const int WM_InitPanel_Update = WM_USER + 26;   // 2025.7.11 add yori
        public const int WM_SubWnd01_Panel_Hide = WM_USER + 27;   // 名称変更(2025.7.25yori)
        public const int WM_InitPanel_Setup = WM_USER + 28;   // 2025.7.11 add yori

        public const int WM_DlgPrgBar1_Show = WM_USER + 29;   // 追加(2025.7.17yori)
        public const int WM_DlgPrgBar1_Close = WM_USER + 30;   // 追加(2025.7.17yori)
        public const int WM_DlgPrgBar2_Show = WM_USER + 31;   // 追加(2025.7.30yori)
        public const int WM_DlgPrgBar2_Close = WM_USER + 32;   // 追加(2025.7.30yori)
        public const int WM_DlgPrgBar3_Show = WM_USER + 33;   // 追加(2025.7.31yori)
        public const int WM_DlgPrgBar3_Close = WM_USER + 34;   // 追加(2025.7.31yori)

        public const int WM_SubWnd03_Close = WM_USER + 35;  // 追加(2025.8.10yori)
        public const int WM_SubWnd03_Btn01 = WM_USER + 36;  // 追加(2025.8.10yori)
        public const int WM_SubWnd03_Btn02 = WM_USER + 37;  // 追加(2025.8.10yori)
        public const int WM_SubWnd03_Btn03 = WM_USER + 38;  // 追加(2025.8.10yori)

        public const int WM_ContactInspectionPanel_MesCallBack = WM_USER + 39;  // 2025.9.2 add eba
        public const int WM_ContactInspectionPanel_ParaOutCallBack = WM_USER + 40;  // 2025.9.2 add eba

        public const int WM_Init0Panel_Setup = WM_USER + 41; // 追加(2025.10.2yori)
        public const int WM_ContactSelfJudgmentPanel_Update = WM_USER + 42; // 追加(2025.10.3yori)

        public static int WM_MainWnd_OtherApp_Connected = WM_USER + 43; // 他アプリ(PolyWorks)から接続した場合(2025.11.19yori)
        public static int WM_MainWnd_OtherApp_Disconnected = WM_USER + 44; // 他アプリ(PolyWorks)から切断した場合(2025.11.19yori)
    }
}
