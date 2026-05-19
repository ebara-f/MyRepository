using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Drawing; // タスクトレイ対応(2026.4.19yori)
using System.Globalization;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;

namespace VecApp
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : System.Windows.Application // Application→System.Windows.Application変更(2026.4.1yori)
    {   
        private Mutex _mutex; // 多重起動防止のため、追加(2026.5.15yori)

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

            //// 多重起動防止のため、追加(2026.5.15yori)
            const string mutexName = "K-CMM_Mutex";
            bool createdNew;
            _mutex = new Mutex(true, mutexName, out createdNew);

            // 既に起動済み
            if (!createdNew)
            {
                MessageBox.Show(VecApp.Properties.Resources.String290,
                                VecApp.Properties.Resources.String291,
                                MessageBoxButton.OK,
                                MessageBoxImage.Information);

                Shutdown();
                return;
            }
            ////

            base.OnStartup(e);

            // メイン画面表示(多重起動防止に伴う追記2026.5.15)
            MainWindow mainWindow = new MainWindow();
            mainWindow.Show();
        }

        // 多重起動防止のため、追加(2026.5.15yori)
        protected override void OnExit(ExitEventArgs e)
        {
            _mutex?.ReleaseMutex();
            _mutex?.Dispose();

            base.OnExit(e);
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