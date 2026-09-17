/***********************************************************************

    C++ DLL からエクスポートした関数のC#ラッパー関数群
    CSH_Grp02.csをコピーして追加(2025.6.19yori)

***********************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace CSH
{
    public partial class Grp03
    {
        #region C/C++DLL-関数定義

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd01();

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd02();

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd03();

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd04(); // 追加(2025.7.3yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd05(); // 追加(2025.8.11yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd06(int scanmode); // 追加(2025.8.12yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd07(int sens); // 追加(2025.8.21yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd08(int power); // 追加(2025.8.21yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd09(int xpitch); // 追加(2025.8.21yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd10(in Status02 sts); // 追加(2025.8.23yori) // 引数追加(2026.8.7yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd11(ushort[] bright_slice); // 追加(2025.8.24yori) // 引数追加(2026.8.6yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd12(ushort[] sens_slice); // 追加(2025.8.24yori) // 引数追加(2026.8.6yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd13(int angle_mask_onoff, double angle); // 追加(2025.8.24yori) // 引数追加(2026.8.6yori) // 引数追加(2026.8.31yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd14(int twopeak); // 追加(2025.8.25yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd15(int edge); // 追加(2025.8.25yori) // 引数追加(2026.8.6yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd16(); // 追加(2025.8.27yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd17(); // 追加(2025.8.27yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd18(); // 追加(2025.11.11yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_ScannerAlignmentPanelFullCalStartBtn(); // 追加(2025.12.8yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_SetDistMaskEnable(bool maskfg); // 追加(2026.8.12yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_SetBrightSliceLevel(in Status02 sts); // 追加(2026.8.29yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_SetSensSliceLevel(in Status02 sts); // 追加(2026.8.29yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_SetBrightMaskSetting(in Status02 sts); // 追加(2026.9.2yori)

        #endregion

        /// <summary>
        /// Cmd01
        /// </summary>

        static public int Cmd01()
        {
            return CPX_Grp03_Cmd01();
        }

        /// <summary>
        /// Cmd02
        /// </summary>

        static public int Cmd02()
        {
            return CPX_Grp03_Cmd02();
        }

        /// <summary>
        /// Cmd03
        /// </summary>

        static public int Cmd03()
        {
            return CPX_Grp03_Cmd03();
        }

        /// <summary>
        /// Cmd04
        /// </summary>

        static public int Cmd04()
        {
            return CPX_Grp03_Cmd04(); // 追加(2025.7.3yori)
        }

        /// <summary>
        /// Cmd05
        /// 追加(2025.8.11yori)
        /// </summary>

        static public int Cmd05()
        {
            return CPX_Grp03_Cmd05();
        }

        /// <summary>
        /// Cmd06
        /// 追加(2025.8.12yori)
        /// </summary>

        static public int Cmd06(int scanmode)
        {
            return CPX_Grp03_Cmd06(scanmode);
        }

        /// <summary>
        /// Cmd07
        /// 追加(2025.8.21yori)
        /// </summary>

        static public int Cmd07(int sens)
        {
            return CPX_Grp03_Cmd07(sens);
        }

        /// <summary>
        /// Cmd08
        /// 追加(2025.8.21yori)
        /// </summary>

        static public int Cmd08(int power)
        {
            return CPX_Grp03_Cmd08(power);
        }

        /// <summary>
        /// Cmd09
        /// 追加(2025.8.21yori)
        /// </summary>

        static public int Cmd09(int xpitch)
        {
            return CPX_Grp03_Cmd09(xpitch);
        }

        /// <summary>
        /// Cmd10
        /// 追加(2025.8.23yori)
        /// 引数追加(2026.8.7yori)
        /// </summary>
        static public int Cmd10(in Status02 sts)
        {
            return CPX_Grp03_Cmd10(sts);
        }

        /// <summary>
        /// Cmd11
        /// 追加(2025.8.24yori)
        /// 引数追加(2026.8.6yori)
        /// </summary>
        static public int Cmd11(ushort[] bright_slice)
        {
            return CPX_Grp03_Cmd11(bright_slice);
        }

        /// <summary>
        /// Cmd12
        /// 追加(2025.8.24yori)
        /// 引数追加(2026.8.6yori)
        /// </summary>
        static public int Cmd12(ushort[] sens_slice)
        {
            return CPX_Grp03_Cmd12(sens_slice);
        }

        /// <summary>
        /// Cmd13
        /// 追加(2025.8.24yori)
        /// 引数追加(2026.8.6yori)
        /// 引数追加(2026.8.31yori)
        /// </summary>
        static public int Cmd13(int angle_mask_onoff, double angle)
        {
            return CPX_Grp03_Cmd13(angle_mask_onoff, angle);
        }

        /// <summary>
        /// Cmd14
        /// 追加(2025.8.25yori)
        /// </summary>
        static public int Cmd14(int twopeak)
        {
            return CPX_Grp03_Cmd14(twopeak);
        }

        /// <summary>
        /// Cmd15
        /// 追加(2025.8.25yori)
        /// 引数追加(2026.8.6yori)
        /// </summary>
        static public int Cmd15(int edge)
        {
            return CPX_Grp03_Cmd15(edge);
        }

        /// <summary>
        /// Cmd16
        /// 追加(2025.8.27yori)
        /// </summary>
        static public int Cmd16()
        {
            return CPX_Grp03_Cmd16();
        }

        /// <summary>
        /// Cmd17
        /// 追加(2025.8.27yori)
        /// </summary>
        static public int Cmd17()
        {
            return CPX_Grp03_Cmd17();
        }

        /// <summary>
        /// Cmd18
        /// 追加(2025.11.11yori)
        /// </summary>
        static public int Cmd18()
        {
            return CPX_Grp03_Cmd18();
        }

        /// <summary>
        /// ScannerAlignmentPanelFullCalStartBtn
        /// 追加(2025.11.11yori)
        /// </summary>
        static public int ScannerAlignmentPanelFullCalStartBtn()
        {
            return CPX_Grp03_ScannerAlignmentPanelFullCalStartBtn();
        }

        /// <summary>
        /// SetDistMaskEnable
        /// 追加(2026.8.12yori)
        /// </summary>
        static public int SetDistMaskEnable(bool maskfg)
        {
            return CPX_Grp03_SetDistMaskEnable(maskfg);
        }

        /// <summary>
        /// SetBrightSliceLevel
        /// 追加(2026.8.29yori)
        /// </summary>
        static public int SetBrightSliceLevel(in Status02 sts)
        {
            return CPX_Grp03_SetBrightSliceLevel(sts);
        }

        /// <summary>
        /// SetSensSliceLevel
        /// 追加(2026.8.29yori)
        /// </summary>
        static public int SetSensSliceLevel(in Status02 sts)
        {
            return CPX_Grp03_SetSensSliceLevel(sts);
        }

        /// <summary>
        /// SetBrightMaskSetting
        /// 追加(2026.9.29yori)
        /// </summary>
        static public int SetBrightMaskSetting(in Status02 sts)
        {
            return CPX_Grp03_SetBrightMaskSetting(sts);
        }
    }
}
