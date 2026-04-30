using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Globalization;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
////起動時に非表示＋トレイ常駐するためのコードをコメントアウト(2026.4.6yori)
//using System.Windows.Forms; // 追加(2026.4.1yori)
//using System.Drawing; // 追加(2026.4.1yori)
//using System.IO; // 追加(2026.4.1yori)
////

namespace VecApp
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : System.Windows.Application // Application→System.Windows.Application変更(2026.4.1yori)
    {
        //private NotifyIcon _notifyIcon; // 追加(2026.4.1yori) // コメントアウト(2026.4.6yori)

        protected override void OnStartup(StartupEventArgs e)
        {
            VecApp.Properties.Settings.Default.UICulture = "jp-JP";
            //VecApp.Properties.Settings.Default.Save();

            string cultureName = VecApp.Properties.Settings.Default.UICulture;
            if (string.IsNullOrEmpty(cultureName))
            {
                cultureName = "en-US"; // デフォルト 英語
            }

            Thread.CurrentThread.CurrentUICulture = new System.Globalization.CultureInfo(cultureName);


            Thread.CurrentThread.CurrentUICulture = new CultureInfo("en-US"); // 英語に変更(2025.12.14yori)
            base.OnStartup(e);

            //// 起動時に非表示＋トレイ常駐(2026.4.2yori)
            //// コメントアウト(2026.4.6yori)
            //ShutdownMode = ShutdownMode.OnExplicitShutdown;

            //var mainWindow = new MainWindow();
            //// MainWindow表示しない！

            //_notifyIcon = new NotifyIcon();
            //string path = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "K-CMM.ico");
            //_notifyIcon.Icon = new System.Drawing.Icon(path);
            //_notifyIcon.Visible = true;
            //_notifyIcon.Text = "K-CMM";

            //// ダブルクリックで表示
            //// コメントアウト(ダブルクリックで表示しない。)
            ////_notifyIcon.DoubleClick += (s, args) =>
            ////{
            ////    mainWindow.Show();
            ////    mainWindow.WindowState = WindowState.Normal;
            ////    mainWindow.Activate();
            ////};

            //// メニュー
            //var menu = new ContextMenuStrip();

            //menu.Items.Add(VecApp.Properties.Resources.String120, null, (s, e2) =>
            //{
            //    mainWindow.Show();
            //    mainWindow.WindowState = WindowState.Normal;
            //    mainWindow.Activate();
            //});

            //menu.Items.Add(VecApp.Properties.Resources.String64, null, (s, e2) =>
            //{
            //    ExitApplication();
            //});

            //_notifyIcon.ContextMenuStrip = menu;
            ////
        }

        // アプリケーション終了(2026.4.2yori)
        // コメントアウト(2026.4.6yori)
        //public void ExitApplication()
        //{
        //    if (_notifyIcon != null)
        //    {
        //        _notifyIcon.Visible = false;
        //        _notifyIcon.Dispose();
        //        _notifyIcon = null;
        //    }

        //    Shutdown();
        //}
    }
}