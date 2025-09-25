using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
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
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            VecApp.Properties.Settings.Default.UICulture = "jp-JP"; //
            //VecApp.Properties.Settings.Default.Save();

            string cultureName = VecApp.Properties.Settings.Default.UICulture;
            if (string.IsNullOrEmpty(cultureName))
            {
                cultureName = "en-US"; // デフォルト 英語
            }

            Thread.CurrentThread.CurrentUICulture = new System.Globalization.CultureInfo(cultureName);


            //Thread.CurrentThread.CurrentUICulture = new CultureInfo("en-US"); //英語に変更
            base.OnStartup(e);
        }
    }
}
