/***********************************************************************

    C++ DLL からエクスポートした関数のC#ラッパー関数群

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
    public partial class Grp01
    {
        #region C/C++DLL-関数定義
        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd01();

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp01_Cmd02(int A, double B, string C);

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp01_Cmd03(int A, double B, string C, out int D, out double E, ref StringBuilder sb, int str_count);

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd04(); //追加(2025.4.28yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp01_CmdXX(out double A, ref StringBuilder sb, int str_count); //2025.5.22 add eba test

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd05(); //追加(2025.6.9yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd06(); //追加(2025.6.9yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd07(); //追加(2025.6.9yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd08(); //追加(2025.6.11yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd09(); //追加(2025.7.18yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd10(); //追加(2025.7.19yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd11(); //追加(2025.7.25yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd12(); //追加(2025.7.30yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd13(); //追加(2025.7.30yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd14(); //追加(2025.7.31yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd15(); //追加(2025.7.31yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp01_Cmd16(); //追加(2025.8.12yori)

        #endregion

        /// <summary>
        /// Cmd01
        /// </summary>

        static public int Cmd01()
        {
            return CPX_Grp01_Cmd01();
        }

        /// <summary>
        /// Cmd02
        /// </summary>
        /// <param name="A">入力パラメータA</param>
        /// <param name="B">入力パラメータB</param>
        /// <param name="C">入力パラメータC</param>
        /// <param name="D">出力パラメータD</param>

        static public int Cmd02(int A, double B, string C)
        {
            return CPX_Grp01_Cmd02(A, B, C);
        }

        /// <summary>
        /// Cmd03
        /// </summary>
        /// <param name="A">入力パラメータA</param>
        /// <param name="B">入力パラメータB</param>
        /// <param name="C">入力パラメータC</param>
        /// <param name="D">出力パラメータD</param>
        /// <param name="E">出力パラメータE</param>
        /// <param name="F">出力パラメータF</param>
        /// <param name="F_count">出力パラメータF_count</param>

        static public int Cmd03(
            int A, double B, string C,
            out int D, out double E, ref string F, int F_count)
        {
            int rc;
            StringBuilder sb = null;

            // コマンドからの出力（文字列）を受け取るためのStringBuilderの生成
            if (F_count > 0)
            {
                sb = new StringBuilder(F_count);
            }

            // コマンドの実行
            rc = CPX_Grp01_Cmd03(A, B, C, out D, out E, ref sb, F_count );
            if (rc != 0)
            {
                return rc;
            }

            // コマンドからの出力（文字列）の抽出
            if (F_count > 0)
            {
                F = sb.ToString();
            }

            return 0;
        }

        /// <summary>
        /// Cmd04
        /// 追加(2025.4.28yori)
        /// </summary>

        static public int Cmd04()
        {
            return CPX_Grp01_Cmd04();
        }

        /// <summary>
        /// Cmd23
        /// 測定機のステータスをC#側に渡す
        /// 2025.5.22 add eba test
        /// </summary>

        static public int CmdXX(out double A, ref string B, int B_count)
        {
            int rc;
            StringBuilder sb = null;

            // コマンドからの出力（文字列）を受け取るためのStringBuilderの生成
            if (B_count > 0)
            {
                sb = new StringBuilder(B_count);
            }
            rc = CPX_Grp01_CmdXX(out A, ref sb, B_count);
            if (rc != 0)
            {
                return rc;
            }

            if (B_count > 0)
            {
                B = sb.ToString();
            }

            return 0;
        }

        /// <summary>
        /// Cmd05
        /// 追加(2025.6.9yori)
        /// </summary>

        static public int Cmd05()
        {
            return CPX_Grp01_Cmd05();
        }

        /// <summary>
        /// Cmd06
        /// 追加(2025.6.9yori)
        /// </summary>

        static public int Cmd06()
        {
            return CPX_Grp01_Cmd06();
        }

        /// <summary>
        /// Cmd07
        /// 追加(2025.6.9yori)
        /// </summary>

        static public int Cmd07()
        {
            return CPX_Grp01_Cmd07();
        }

        /// <summary>
        /// Cmd08
        /// 追加(2025.6.9yori)
        /// </summary>

        static public int Cmd08()
        {
            return CPX_Grp01_Cmd08();
        }

        /// <summary>
        /// Cmd09
        /// 追加(2025.7.18yori)
        /// </summary>

        static public int Cmd09()
        {
            return CPX_Grp01_Cmd09();
        }

        /// <summary>
        /// Cmd10
        /// 追加(2025.7.18yori)
        /// </summary>

        static public int Cmd10()
        {
            return CPX_Grp01_Cmd10();
        }

        /// <summary>
        /// Cmd11
        /// 追加(2025.7.25yori)
        /// </summary>

        static public int Cmd11()
        {
            return CPX_Grp01_Cmd11();
        }

        /// <summary>
        /// Cmd12
        /// 追加(2025.7.30yori)
        /// </summary>

        static public int Cmd12()
        {
            return CPX_Grp01_Cmd12();
        }

        /// <summary>
        /// Cmd13
        /// 追加(2025.7.30yori)
        /// </summary>

        static public int Cmd13()
        {
            return CPX_Grp01_Cmd13();
        }

        /// <summary>
        /// Cmd14
        /// 追加(2025.7.31yori)
        /// </summary>

        static public int Cmd14()
        {
            return CPX_Grp01_Cmd14();
        }

        /// <summary>
        /// Cmd15
        /// 追加(2025.7.31yori)
        /// </summary>

        static public int Cmd15()
        {
            return CPX_Grp01_Cmd15();
        }

        /// <summary>
        /// Cmd16
        /// 追加(2025.8.12yori)
        /// </summary>

        static public int Cmd16()
        {
            return CPX_Grp01_Cmd16();
        }
    }
}
