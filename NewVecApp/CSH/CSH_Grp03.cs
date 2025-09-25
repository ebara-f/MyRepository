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
        public extern static int CPX_Grp03_Cmd10(); // 追加(2025.8.23yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd11(); // 追加(2025.8.24yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd12(); // 追加(2025.8.24yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd13(); // 追加(2025.8.24yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd14(int twopeak); // 追加(2025.8.25yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd15(); // 追加(2025.8.25yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd16(); // 追加(2025.8.27yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp03_Cmd17(); // 追加(2025.8.27yori)

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
        /// </summary>
        static public int Cmd10()
        {
            return CPX_Grp03_Cmd10();
        }

        /// <summary>
        /// Cmd11
        /// 追加(2025.8.24yori)
        /// </summary>
        static public int Cmd11()
        {
            return CPX_Grp03_Cmd11();
        }

        /// <summary>
        /// Cmd12
        /// 追加(2025.8.24yori)
        /// </summary>
        static public int Cmd12()
        {
            return CPX_Grp03_Cmd12();
        }

        /// <summary>
        /// Cmd13
        /// 追加(2025.8.24yori)
        /// </summary>
        static public int Cmd13()
        {
            return CPX_Grp03_Cmd13();
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
        /// </summary>
        static public int Cmd15()
        {
            return CPX_Grp03_Cmd15();
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
    }
}
