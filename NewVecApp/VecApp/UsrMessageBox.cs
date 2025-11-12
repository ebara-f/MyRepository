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

            // 最前面に表示するために
            // 一時的な透明ウィンドウを作成
            var topmostWindow = new Window
            {
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
            topmostWindow.Show();

            return (int)MessageBox.Show(topmostWindow, text, caption, (MessageBoxButton)button, (MessageBoxImage)icon);

        }







    }
}
