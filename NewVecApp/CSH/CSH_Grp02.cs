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
using System.Runtime.CompilerServices;

namespace CSH
{
    // キャリブレーション関連のデータ受け渡し要構造体 2025.9.3 eba
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct CalibGauge
    {
        public double StylusDia;

        public double BallBarLen;
        public double PlateLen;
        public double BallDia;
        double PitchBarLen;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6/*CALIB_GAUGE_LEN_V8*/)]
        public double[] BallBarLenV8;

        public double AreaRFar;
        public double AreaRNear;
        public double AreaZHigh;
        public double AreaZLow;
        public double ErrMax;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct CalibResult
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public double[] pp;       // MAX-MIN
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public double[] sigma2;   // 2σ
        public double plate;       // 面間距離
        public double pitch;       // ピッチゲージ距離
        //double Cmax[3];		// xyz max center position err(2018.3.10追加)
        //double Cmin[3];		// xyz min center position err(2018.3.10追加)
        public double Ps;          // diamter max size err(2018.3.10追加)
        public double Pf;          // form err(reseve)(2018.3.10追加)
        public double Ld;          // Ldia(2021.6.30追加)
        public double ri;          // 距離誤差(2018.3.12追加)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4 * 50)]
        public double[] cxyzd;/*[4][50]*/  //各球で測定した球中心座標値、直径(2022.4.21追加)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public double[] ave;      //球中心座標値、直径の平均値(2022.4.21追加)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public double[] sdevp;    //球中心座標値X、Y、Z の母集団標準偏差(2022.4.21追加)
        public double sqrtdevsq;   //球直径D の偏差平方和の平方根(2022.4.21追加)
        public double maxmin;		//ダミー点からの各球中心までの距離の最大－最小(2022.4.21追加)
    }


    // プローブ点検しきい値
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct CalibJudge
    {
        
        public double pp;   
        public double sigma2;
        public double plate;
        public double ld;
        public double pf;
        public double ps;
        public double ri;
        public double pl;
        public double psi;

    }

    // 始業前点検閾値
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct CalibJudgeCk
    {
        public double pp;
        public double sigma2;
        public double plate;
        public double pitch;
        public double maxmin;

    }

    // プローブ点検判定フラグ
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct CalibJudgeFg
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public int [] pp;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public int [] sigma2;
        public int plate;
        public int ld;
        public int pf;
        public int ps;
        public int ri;
        public int pl;
        public int psi;

    }

    // 始業前点検判定フラグ
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct CalibJudgeCkFg
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public int [] pp;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public int [] sigma2;
        public int plate;
        public int pitch;
        public int maxmin;

    }


    // キャリブデータの位置、ボールから離れたかのチェックを知らせるフラグ 2025.9.24 add eba
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct CalibPosErrFg
    {
        public int user_pos_err;
        public int user_ball_err;

    }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct CalibPara
    {
        public CalibGauge GaugePara;

        public CalibResult InspAndProbCkResult;
        public CalibJudge   ProbeCheckThreshold;
        public CalibJudgeCk InspectionThreshold;
        public CalibJudgeFg ProbeCheckResultFg;
        public CalibJudgeCkFg InspectionResultFg;

        public double PlateErrVal;
        public int CalibInspectJudge;
        public int CalibResultVal;

        public int Language;
        public int CalibType;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string path;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 512)]
        public string mes;

        public　int MesString;  // 2025.9.21 add eba 仮
    }

    public enum CalibType
    {
        UNKNOWN = 0,
        INSPECT_MULTI_GAUGE_NEST_STD,
        INSPECT_MULTI_GAUGE_PLATE_STD,
        INSPECT_BALL_GAUGE,
        ALIGNMENT_MULTI_GAUGE,
        ALIGNMENT_BALL_GAUGE_STD,

        END
    }


    public partial class Grp02
    {
        #region C/C++DLL-関数定義

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp02_Cmd01();

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp02_Cmd02();

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp02_Cmd03();

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp02_Cmd04();

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp02_Cmd05();

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp02_Cmd06();

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp02_Cmd07(int id, double dia); // 追加(2025.7.18yori) // 引数追加(2025.9.8yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp02_Cmd08(int gaugetype); // 追加(2025.8.9yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp02_Cmd09(); // 追加(2025.8.16yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_Cmd10(string armtype); // 追加(2025.8.31yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp02_Cmd11(); // 追加(2025.9.1yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp02_Cmd12(); // 追加(2025.10.6yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_Grp02_Cmd13(); // 追加(2025.10.6yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_ContactSelfJudgmentPanelSavePara(string path); // 追加(2025.10.8yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_ContactSelfJudgmentPanelRestorePara(string path); // 追加(2025.10.9yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_ContactInspectionPanelInit(ref CalibPara para, ref StringBuilder sb_p, int p_count, ref StringBuilder sb_m, int m_count); // 2025.8.26 add eba

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_ContactInspectionPanelClickStart(ref CalibPara para); // 2025.8.26 add eba

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_ContactInspectionPanelClickBack(ref CalibPara para); // 2025.9.22 add eba

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_ContactInspectionPanelClickReStart(ref CalibPara para); // 2025.8.26 add eba

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_ContactInspectionPanelTerminate(ref CalibPara para); // 2025.8.26 add eba

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_ContactInspectionPanelMesCallBack(ref CalibPara para); // 2025.9.2 add eba

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_ContactInspectionPanelParaOutCallBack(ref CalibPara para); // 2025.9.10 add eba

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_SettingPanelInit(ref CalibPara para);  // 2025.9.24 add eba

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_SettingPanelOkBtn(ref CalibPara para);  // 2025.9.25 add eba

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_Grp02_SettingPanelCancelBtn(ref CalibPara para);  // 2025.9.25 add eba
        #endregion

        /// <summary>
        /// Cmd01
        /// プローブ情報要求
        /// </summary>

        static public int Cmd01()
        {
            return CPX_Grp02_Cmd01();
        }

        /// <summary>
        /// Cmd02
        /// </summary>

        static public int Cmd02()
        {
            return CPX_Grp02_Cmd02();
        }

        /// <summary>
        /// Cmd03
        /// </summary>

        static public int Cmd03()
        {
            return CPX_Grp02_Cmd03();
        }


        /// <summary>
        /// Cmd04
        /// </summary>

        static public int Cmd04()
        {
            return CPX_Grp02_Cmd04();
        }


        /// <summary>
        /// Cmd05
        /// </summary>

        static public int Cmd05()
        {
            return CPX_Grp02_Cmd05();
        }


        /// <summary>
        /// Cmd06
        /// </summary>

        static public int Cmd06()
        {
            return CPX_Grp02_Cmd06();
        }

        /// <summary>
        /// Cmd07
        /// </summary>

        static public int Cmd07(int id, double dia)
        {
            return CPX_Grp02_Cmd07(id, dia);
        }

        /// <summary>
        /// Cmd08
        /// </summary>

        static public int Cmd08(int gaugetype)
        {
            return CPX_Grp02_Cmd08(gaugetype);
        }

        /// <summary>
        /// Cmd09
        /// </summary>

        static public int Cmd09()
        {
            return CPX_Grp02_Cmd09();
        }

        /// <summary>
        /// Cmd10
        /// 追加(2025.8.31yori)
        /// </summary>

        static public int Cmd10(string armtype)
        {
            return CPX_Grp02_Cmd10(armtype);
        }

        /// <summary>
        /// Cmd11
        /// 追加(2025.9.1yori)
        /// </summary>

        static public int Cmd11()
        {
            return CPX_Grp02_Cmd11();
        }

        /// <summary>
        /// Cmd12
        /// 追加(2025.10.6yori)
        /// </summary>

        static public int Cmd12()
        {
            return CPX_Grp02_Cmd12();
        }

        /// <summary>
        /// Cmd13
        /// 追加(2025.10.6yori)
        /// </summary>

        static public int Cmd13()
        {
            return CPX_Grp02_Cmd13();
        }

        /// <summary>
        /// アームパラメータ保存(2025.10.8yori)
        /// </summary>

        static public int ContactSelfJudgmentPanelSavePara(string path)
        {
            return CPX_Grp02_ContactSelfJudgmentPanelSavePara(path);
        }

        /// <summary>
        /// アームパラメータ復元(2025.10.9yori)
        /// </summary>

        static public int ContactSelfJudgmentPanelRestorePara(string path)
        {
            return CPX_Grp02_ContactSelfJudgmentPanelRestorePara(path);
        }

        /// <summary>
        /// キャリブレーション画面のイニシャル処理 2025.8.26 add eba
        /// </summary>

        static public int ContactInspectionPanelInit(ref CalibPara para, out string path, int p_count, out string mes, int m_count)
        {
            int rc;
            StringBuilder sb_p = null;
            StringBuilder sb_m = null;

            path = null;
            mes = null;

            // コマンドからの出力（文字列）を受け取るためのStringBuilderの生成
            if (p_count > 0)
            {
                sb_p = new StringBuilder(p_count);
            }
            if (m_count > 0)
            {
                sb_m = new StringBuilder(m_count);
            }

            rc = CPX_Grp02_ContactInspectionPanelInit(ref para, ref sb_p, p_count, ref sb_m, m_count);

            if(rc==0)
            {
                // コマンドからの出力（文字列）の抽出
                if (p_count > 0)
                {
                    path = sb_p.ToString();
                }
                if (m_count > 0)
                {
                    mes = sb_m.ToString();
                }
            }
            
            return rc;
        }

        /// <summary>
        /// 開始ボタンクリック 2025.8.26 add eba
        /// </summary>
        static public int ContactInspectionPanelClickStart(ref CalibPara para)
        {
            return CPX_Grp02_ContactInspectionPanelClickStart(ref para);
        }

        /// <summary>
        /// キャリブレーション画面のターミナル処理 2025.8.26 add eba
        /// </summary>

        static public int ContactInspectionPanelTerminate(ref CalibPara para)
        {
            return CPX_Grp02_ContactInspectionPanelTerminate(ref para);
        }

        /// <summary>
        /// 戻るボタンクリック2025.8.26 add eba
        /// </summary>
        static public int ContactInspectionPanelClickBack(ref CalibPara para)
        {
            return CPX_Grp02_ContactInspectionPanelClickBack(ref para);
        }

        /// <summary>
        /// 初めに戻るボタンクリック2025.8.26 add eba
        /// </summary>
        static public int ContactInspectionPanelClickReStart(ref CalibPara para)
        {
            return CPX_Grp02_ContactInspectionPanelClickReStart(ref para);
        }


        /// <summary>
        /// データが入力された時のコールバック関数(データ入力処理) 2025.8.26 add eba
        /// </summary>
        static public int ContactInspectionPanelMesCallBack(ref CalibPara para)
        {
            return CPX_Grp02_ContactInspectionPanelMesCallBack(ref para);
        }


        /// <summary>
        /// データの入力が完了した時のコールバック関数(結果処理) 2025.8.26 add eba
        /// </summary>
        static public int ContactInspectionPanelParaOutCallBack(ref CalibPara para)
        {
            return CPX_Grp02_ContactInspectionPanelParaOutCallBack(ref para);
        }


        /// <summary>
        /// 
        /// </summary>
        static public int SettingPanelInit(ref CalibPara para)
        {
            return CPX_Grp02_SettingPanelInit(ref para);
        }


        /// <summary>
        /// 
        /// </summary>
        static public int SettingPanelOkBtn(ref CalibPara para)
        {
            return CPX_Grp02_SettingPanelOkBtn(ref para);
        }


        /// <summary>
        /// 
        /// </summary>
        static public int SettingPanelCancelBtn(ref CalibPara para)
        {
            return CPX_Grp02_SettingPanelCancelBtn(ref para);
        }

    }
}
