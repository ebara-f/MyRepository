using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace VecApp
{
    public class UsrMessageBox
    {

        public static MessageBoxResult Show(int text_no, string caption, MessageBoxButton button, MessageBoxImage icon)
        {
            string text = "";
            switch(text_no)
            {
                case 0:
                    return 0;
                    //break;

                case 230:
                    text = VecApp.Properties.Resources.String230;
                    break;
                case 231:
                    text = VecApp.Properties.Resources.String231;
                    break;
                case 232:
                    text = VecApp.Properties.Resources.String232;
                    break;
                case 233:
                    text = VecApp.Properties.Resources.String233; // 232→233へ変更(2025.10.2yori)
                    break;

                default:
                    text = "NO Message";
                    break;


            }

            return MessageBox.Show(text, caption, button, icon);

        }

        public static int ShowCallBack(int msgID, int capID, int button, int icon)
        {
            string text = "";
            string caption = "";
            int result = 0; // = 0追加(2026.2.5yori)

            switch (msgID)
            {
                case 0:
                    return 0;
                //break;

                case 269:
                    text = VecApp.Properties.Resources.String269;
                    break;
                case 270:
                    text = VecApp.Properties.Resources.String270;
                    break;
                case 271: // スキャナ接続エラー追加(2026.1.3yori)
                    text = VecApp.Properties.Resources.String271;
                    break;
                case 279: // アーム通信エラー追加(2026.2.3yori)
                    text = VecApp.Properties.Resources.String279;
                    break;
                case 280: // 点群数エラー(2026.2.4yori)
                    text = VecApp.Properties.Resources.String280;
                    break;
                case 281: // 座標系エラー(2026.2.4yori)
                    text = VecApp.Properties.Resources.String281;
                    break;
                case 282: // 距離が近すぎます。(2026.2.4yori)
                    text = VecApp.Properties.Resources.String282;
                    break;
                case 283: // 距離が遠すぎます。(2026.2.4yori)
                    text = VecApp.Properties.Resources.String283;
                    break;
                case 284: // 点群取得失敗(2026.2.4yori)
                    text = VecApp.Properties.Resources.String284;
                    break;
                case 285: // No.1関節角度エラー(2026.2.4yori)
                    text = VecApp.Properties.Resources.String285;
                    break;
                case 286: // No.0関節角度エラー(2026.2.4yori)
                    text = VecApp.Properties.Resources.String286;
                    break;
                case 287: // 点群欠損エラー(2026.2.4yori)
                    text = VecApp.Properties.Resources.String287;
                    break;
                case 288: // 球作成失敗(2026.2.4yori)
                    text = VecApp.Properties.Resources.String288;
                    break;
                case 289: // No.2関節角度エラー(2026.2.4yori)
                    text = VecApp.Properties.Resources.String289;
                    break;

                default:
                    text = "NO Message";
                    break;
            }


            switch (capID)
            {
                case 0:
                    return 0;
                //    break;

                case 268:
                    caption = VecApp.Properties.Resources.String268;
                    break;

                default:
                    caption = "NO Message";
                    break;


            }

            // 現在がUIスレッドでなければDispatcher経由で実行
            if (!Application.Current.Dispatcher.CheckAccess())
            {
                return Application.Current.Dispatcher.Invoke(() =>
                    ShowCallBack(msgID, capID, button, icon));
            }

            // 今アクティブなWindowを親にして他のWindowを操作不可(2026.2.5yori)
            Window owner = Application.Current.Windows
                .OfType<Window>()
                .FirstOrDefault(w => w.IsActive)
                ?? Application.Current.MainWindow;

            // 最前面に表示するために
            // 一時的な透明ウィンドウを作成
            var topmostWindow = new Window
            {
                Owner = owner, // 追加(2026.2.5yori)
                Topmost = true,
                ShowInTaskbar = false,
                WindowStyle = WindowStyle.None,
                AllowsTransparency = true,
                Opacity = 0,
                Width = 1,
                Height = 1,
                Left = SystemParameters.WorkArea.Width / 2,
                Top = SystemParameters.WorkArea.Height / 2
            };
            //topmostWindow.Show(); // コメントアウト(2026.2.5yori)

            // Windowが表示されたタイミングで MessageBoxを出す。(2026.2.5yori)
            topmostWindow.Loaded += (_, __) =>
            {
                result = (int)MessageBox.Show(topmostWindow, text, caption, (MessageBoxButton)button, (MessageBoxImage)icon);

                topmostWindow.Close(); // MessageBox終了後に閉じる。(2026.2.5yori)
            };

            topmostWindow.ShowDialog(); // モーダル表示(2026.2.5yori)

            return (result);        
           
            //return (int)MessageBox.Show(text, caption, (MessageBoxButton)button, (MessageBoxImage)icon);
        }







    }
}
