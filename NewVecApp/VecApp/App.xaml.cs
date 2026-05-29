using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Forms; // タスクトレイ対応(2026.5.19yori)

namespace VecApp
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : System.Windows.Application // Application→System.Windows.Application変更(2026.4.1yori)
    {
        private Mutex? mutex; // 多重起動防止のため、追加(2026.5.19yori)
        private NotifyIcon? notifyIcon; // タスクトレイ対応(2026.5.19yori)
        private MainWindow? mainWindow; // 追加(2026.5.19yori)

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            VecApp.Properties.Settings.Default.UICulture = "jp-JP";
            //VecApp.Properties.Settings.Default.Save();

            string cultureName = VecApp.Properties.Settings.Default.UICulture;
            if (string.IsNullOrEmpty(cultureName))
            {
                cultureName = "en-US"; // デフォルト 英語
            }

            Thread.CurrentThread.CurrentUICulture = new System.Globalization.CultureInfo(cultureName);
            Thread.CurrentThread.CurrentUICulture = new CultureInfo("en-US"); // 英語に変更(2025.12.14yori)

            //// 多重起動防止のため、追加(2026.5.15yori)
            bool createdNew;
            mutex = new Mutex(true, "K-CMM_Mutex", out createdNew);

            // 既に起動済み
            if (!createdNew)
            {
                System.Windows.MessageBox.Show(VecApp.Properties.Resources.String290,
                                VecApp.Properties.Resources.String291,
                                MessageBoxButton.OK,
                                MessageBoxImage.Information);

                Shutdown();
                return;
            }
            ////

            // tray 引数確認(2026.5.19yori)
            bool trayMode = e.Args.Any(arg => arg.Equals("tray", StringComparison.OrdinalIgnoreCase));
            CSH.AppMain.MainWindowStatus(trayMode); // C++にトレイモードの状態を渡す。(2026.5.20yori)

            // MainWindow生成(2026.5.20yori)
            mainWindow = new MainWindow();

            // trayモード(2026.5.20yori)
            if (trayMode)
            {
                CreateTrayIcon();

                // ウィンドウ非表示
                mainWindow.WindowState = WindowState.Minimized;
                mainWindow.ShowInTaskbar = false;
                mainWindow.Hide();
            }
            else
            {
                // 通常起動
                MainWindow = mainWindow;
                mainWindow.Show();
            }
        }


        // タスクトレイ生成(2026.5.20yori)
        private void CreateTrayIcon()
        {
            notifyIcon = new NotifyIcon();
            string iconPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "K-CMM.ico");
            notifyIcon.Icon = new System.Drawing.Icon(iconPath);
            notifyIcon.Visible = true;
            notifyIcon.Text = "K-CMM";

            // ダブルクリックで表示(通常使用しないため、コメントアウト)(2026.5.20yori)
            //notifyIcon.DoubleClick += (s, ev) =>
            //{
            //    if (mainWindow == null)
            //    {
            //        return;
            //    }

            //    mainWindow.Show();
            //    mainWindow.WindowState = WindowState.Normal;
            //    mainWindow.ShowInTaskbar = true;
            //    mainWindow.Activate();
            //};

            // 右クリックメニュー(2026.5.20yori)
            var menu = new ContextMenuStrip();
            // 表示(通常使用しないため、コメントアウト)
            //menu.Items.Add(VecApp.Properties.Resources.String120, null, (s, ev) =>
            //{
            //    if (mainWindow == null)
            //    {
            //        return;
            //    }

            //    mainWindow.Show();
            //    mainWindow.WindowState = WindowState.Normal;
            //    mainWindow.ShowInTaskbar = true;
            //    mainWindow.Activate();
            //});
            // 終了
            menu.Items.Add(VecApp.Properties.Resources.String292, null, (s, ev) =>
            {
                ExitApplication();
            });

            notifyIcon.ContextMenuStrip = menu;
        }

         // アプリ終了(2026.5.20yori)
        public void ExitApplication()
        {
            notifyIcon?.Dispose();
            notifyIcon = null;

            mutex?.ReleaseMutex();
            mutex?.Dispose();
            mutex = null;

            Shutdown();
        }

        // アプリ終了時(2026.5.20yori)
        protected override void OnExit(ExitEventArgs e)
        {
            notifyIcon?.Dispose();

            mutex?.ReleaseMutex();
            mutex?.Dispose();

            base.OnExit(e);
        }
    }
}