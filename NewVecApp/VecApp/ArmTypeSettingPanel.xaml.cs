using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using CSH;

namespace VecApp
{
    /// <summary>
    /// ArmTypeSettingPanel.xaml の相互作用ロジック
    /// </summary>
    public partial class ArmTypeSettingPanel : PanelBase
    {
        public ArmTypeSettingPanel(SubWindowBase parent, INotifyPropertyChanged model)
            : base(parent, Panel.ArmTypeSetting)
        {
            InitializeComponent();
            // 以降、ViewModel対応による追加
            this.DataContext = model;

            // 追加(2025.8.31yori)
            Status01 sts = new Status01();
            CSH.AppMain.UpDateData01(out sts);
            if (sts.arm_model == "VAR800M") ViewModel.ArmTypeIndex = 0;
            if (sts.arm_model == "VAR800L") ViewModel.ArmTypeIndex = 1;
            if (sts.arm_model == "BK100S") ViewModel.ArmTypeIndex = 2;
            if (sts.arm_model == "BK100S-NC") ViewModel.ArmTypeIndex = 3;
        }

        private void Click_DoneBtn(object sender, RoutedEventArgs e)
        {
            CSH.Grp02.Cmd10(ViewModel.ArmTypeItem); // 追加中(2025.9.1yori)
            Parent.CurrentPanel = Panel.None; // 追加(2025.8.30yori)
        }

        private void Click_CancelBtn(object sender, RoutedEventArgs e)
        {
            Parent.CurrentPanel = Panel.None; // 追加(2025.8.30yori)
        }

        private ArmTypeSettingViewModel ViewModel
        {
            get => this.DataContext as ArmTypeSettingViewModel;
        }

        // 追加(2025.8.30yori)
        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            switch (ViewModel.ArmTypeIndex)
            {
                case 0:
                    ViewModel.ArmTypeImage = "Image/init_machine10.PNG";
                    break;
                case 1:
                    ViewModel.ArmTypeImage = "Image/init_machine10.PNG";
                    break;
                case 2:
                    ViewModel.ArmTypeImage = "Image/BK100S.png";
                    break;
                case 3:
                    ViewModel.ArmTypeImage = "Image/BK100S-NC.PNG";
                    break;
                default:
                    break;
            }
        }
    }
}
