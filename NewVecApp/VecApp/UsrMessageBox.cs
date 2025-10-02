using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

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
                    text = VecApp.Properties.Resources.String232;
                    break;

                default:
                    text = "NO Message";
                    break;


            }

            return MessageBox.Show(text, caption, button, icon);

        }









    }
}
