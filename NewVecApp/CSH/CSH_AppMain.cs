/***********************************************************************

    C++ DLL からエクスポートした関数のC#ラッパー関数群

***********************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;


namespace CSH
{
    // ステータス更新用の構造体
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)] // 追加(2025.7.24yori) // CharSet.Unicode→CharSet.Ansiへ変更(2025.8.28yori)
    public struct Status01 // 文字化け調査中(2025.8.21yori)→C++側のwchar_t→charへ変更(2025.8.28yori)
    {
        public int mode;
        public int connect_fg;
        public int warm_fg;
        public int init_fg;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public int[] init_sts; // 各軸のイニシャライズ状態(2025.7.11yori)
        public int no0_fg; // 0軸有無(2025.7.15yori)
        public int probe_id; // プローブID(2025.6.11yori)
        public double dia; // スタイラス直径(2025.6.11yori)
        public double dia_meas; // 測定用スタイラス直径(2025.7.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name0; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name1; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name2; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name3; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name4; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name5; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name6; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name7; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name8; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name9; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name10; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name11; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name12; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name13; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name14; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name15; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name16; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name17; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name18; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name19; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string pobe_name20; // プローブ名称(2025.7.24yori)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 21)]
        public double[] stylus_angle; // スタイラス角度(2025.7.31yori)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 21)]
        public int[] pobe_type; // プローブ種類(2025.7.31yori)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public double[] tempature; // アーム内温度(2025.6.4yori)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public double[] cal_tempature; // キャリブ温度(2025.6.18yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string arm_model; // アーム型式(2025.6.16yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string address1; // IPアドレス(2025.6.18yori) // 4つに分割(2025.8.15yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string address2; // IPアドレス(2025.8.15yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string address3; // IPアドレス(2025.8.15yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string address4; // IPアドレス(2025.8.15yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string subnet1; // サブネットマスク(2025.6.18yori) // 4つに分割(2025.8.15yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string subnet2; // サブネットマスク(2025.8.15yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string subnet3; // サブネットマスク(2025.8.15yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string subnet4; // サブネットマスク(2025.8.15yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 4)]
        public string port; // ポート(2025.6.18yori)
    }

    // 有接触自己診断用の構造体(2025.9.1yori)
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct Status04
    {
        public uint btn; // ボタンの状態
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string firm_ver; // バージョン
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 9)]
        public int[] comm_check; // 通信チェック
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string cnt_ver; // カウンタバージョン
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 9)]
        public long[] cnt_data; // カウント値
        public int count_fg; // カウント値取得フラグ(2025.10.30yori)
    }

    // スキャナステータスの構造体(2025.6.19yori)
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)] // 追加(2025.8.11yori) // CharSet.Unicode→CharSet.Ansiへ変更(2025.8.14yori)
    public struct Status02
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string mode0_info; // 計測モード詳細(2025.8.10yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string mode1_info; // 計測モード詳細(2025.8.10yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string mode2_info; // 計測モード詳細(2025.8.10yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string mode3_info; // 計測モード詳細(2025.8.10yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string mode4_info; // 計測モード詳細(2025.8.10yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string mode5_info; // 計測モード詳細(2025.8.10yori)
        public int mode; // 計測モード(2025.6.20yori)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public double[] pitch; // 点間ピッチ間引き(2025.8.11yori)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
        public int[] sens_use; // 感度の有効無効(2025.6.23yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 50)]
        public string sens_name0; // 感度名称(2025.6.23yori)、char→stringへ変更(2025.8.14yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 50)]
        public string sens_name1; // 感度名称(2025.6.23yori)、char→stringへ変更(2025.8.14yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 50)]
        public string sens_name2; // 感度名称(2025.6.23yori)、char→stringへ変更(2025.8.14yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 50)]
        public string sens_name3; // 感度名称(2025.6.23yori)、char→stringへ変更(2025.8.14yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 50)]
        public string sens_name4; // 感度名称(2025.6.23yori)、char→stringへ変更(2025.8.14yori)
        public int sens; // 感度(2025.11.25yori)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6 * 3 * 2)]
        public int[] use; // 距離マスク使用の有無(1=使用する/0=使用しない)(2025.6.20yori)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6 * 3 * 2)]
        public double[] data; // マスク設定値(2025.6.20yori)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
        public ushort[] brightslice; //輝度スライス(2025.6.20yori)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
        public ushort[] sens_slice; //感度スライス(2025.6.20yori)
        public int power; // ガイドレーザーパワー(2025.6.23yori)
        public int xpitch_onoff; // 補間(2025.6.23yori)
        public double angle; // 角度マスク(2025.6.23yori)
        public int two_peak; // 2ピークマスク(2025.6.23yori)
        public int edge; // エッジマスク(2025.6.23yori)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3 * 6)]
        public int[] edge_default; // エッジマスク初期値(2025.8.27yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]  // 修正(2025.8.18yori)
        public string address1; // IPアドレス(2025.6.19yori) // 4つに分割(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string address2; // IPアドレス(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string address3; // IPアドレス(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string address4; // IPアドレス(2025.8.15yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string subnet1; // サブネットマスク(2025.6.19yori) // 4つに分割(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string subnet2; // サブネットマスク(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string subnet3; // サブネットマスク(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string subnet4; // サブネットマスク(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string gateway1; // デフォルトゲートウェイ(2025.6.19yori) // 4つに分割(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string gateway2; // デフォルトゲートウェイ(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string gateway3; // デフォルトゲートウェイ(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string gateway4; // デフォルトゲートウェイ(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string dns1; // DNSサーバー(2025.6.19yori) // 4つに分割(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string dns2; // DNSサーバー(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string dns3; // DNSサーバー(2025.8.17yori)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string dns4; // DNSサーバー(2025.8.17yori)
    }

    // しきい値の構造体(2025.8.1yori)
    public struct Threshold
    {
        // 始業前点検
        public double pp;
        public double sigma2;
        public double plate;
        public double pitch;
        public double maxmin;
        // プローブ点検
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public double[] pp_probe;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public double[] sigma2_probe;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public double[] plate_probe;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public double[] ri_probe;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public double[] ps_probe;
        // キャリブレーション
        public double dst_max;
        public double dst_min;
        public double height_max;
        public double height_min;
        public double error_max;
    }

    // 非接触自己診断用の構造体(2025.6.24yori)
    public struct Status03
    {
        // 感度チェック(2025.7.2yori)
        public int isensresult;
        public int ibasebright;
        public int iresultbright;
        public double dthreshold;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        // 非接触自己診断のSWチェック(2025.6.24yori)
        public int[] sw;
        // ラッチ通信チェック(2025.6.24yori)
        public int ilatchresult;
        public int isendlatchcount;
        public int irecvlatchcount;
        // ポインタ位置チェック(2025.7.4yori)
        public double avedit;
        // モーターチェック(2025.6.24yori)
        public int imotorresult;
        public int isensorplus;
        public int icontrollerplus;
        public int isensorminus;
        public int icontrollerminus;
        public int ibasemove;
        public int isensormoveplus;
        public int icontrollermoveplus;
        public int isensormoveminus;
        public int icontrollermoveminus;
    }

    // ゲージ設定の構造体(2025.8.7yori)
    public struct Gauge
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public char[] GageType;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public double[] Center_ScopePnt;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4 * 3)]
        public double[] Plane_ScopePnt;
        public double Plane_ScopeRad;
        public double Length_ScopeRad;
        public int Length_ScopeRad_Cnt;
        public double Center_Limit;
        public double Plane_Limit;
        public double Length_Limit;
        public double Only_Ball_Center_Limit; // 球ゲージのみで非接触始業前点検を実施するときの許容値(2025.8.9yori)
        public int Plane_MeasPnt_Limit;
        public int Length_MeasPnt_Limit;
        public int Kido_Base;
        public double Kido_Limit;

        public double Center_ScopeRad;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4 * 3)]
        public double[] Length_ScopePnt;
    }

    public partial class AppMain
    {
        #region C/C++DLL-関数定義

        [DllImport("CPX.dll")]
        public extern static int CPX_AppMain_Init();

        [DllImport("CPX.dll")]
        public extern static int CPX_AppMain_Term();

        [DllImport("CPX.dll")]
        public extern static int CPX_AppMain_SubWnd01();

        [DllImport("CPX.dll")]
        public extern static int CPX_AppMain_SubWnd02();

        [DllImport("CPX.dll")]
        public extern static int CPX_AppMain_SubWnd03();

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_UpDateData01(out Status01 sts);

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_UpDateData02(out Status02 sts); // 追加(2025.6.19yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_UpDateData03(out Status03 sts); // 追加(2025.6.24yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_UpDateData04(out Threshold th, int id); // 追加(2025.7.31yori) // 引数追加(2025.9.22yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_UpDateData05(out Gauge ga); // 追加(2025.8.7yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_UpDateData06(out Status04 sts); // 追加(2025.10.3yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_CountCheck(out Status04 sts); // 追加(2025.10.6yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_UpDateData01_Write(in Status01 sts); // 追加(2025.7.18yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_UpDateData02_Write(in Status02 sts); // 追加(2025.8.17yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_UpDateData04_Write(in Threshold th, int id); // 追加(2025.8.1yori) // 引数追加(2025.9.22yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_UpDateData05_Write(in Gauge ga); // 追加(2025.8.9yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_UpDateData04_Default(out Threshold th, int id); // 追加(2025.8.1yori) // 引数追加(2025.9.22yori)

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_AppMain_UpDateData05_Default(out Gauge ga); // 追加(2025.8.9yori)

        [DllImport("CPX.dll")]
        public extern static int CPX_AppMain_MesCallBack(); // 2025.9.2 add eba

        [DllImport("CPX.dll")]
        public extern static int CPX_AppMain_TestLplRecvMesBox(); // 追加(2025.12.28yori)

        #endregion

        /// <summary>
        /// 初期化処理
        /// </summary>

        static public int Init()
        {
            return CPX_AppMain_Init();
        }

        /// <summary>
        /// 終了処理
        /// </summary>

        static public int Term()
        {
            return CPX_AppMain_Term();
        }

        /// <summary>
        /// 終了処理
        /// </summary>

        static public int SubWnd01()
        {
            return CPX_AppMain_SubWnd01();
        }

        /// <summary>
        /// 終了処理
        /// </summary>

        static public int SubWnd02()
        {
            return CPX_AppMain_SubWnd02();
        }

        /// <summary>
        /// 終了処理
        /// </summary>

        static public int SubWnd03()
        {
            return CPX_AppMain_SubWnd03();
        }

        /// <summary>
        /// 終了処理
        /// </summary>

        static public int UpDateData01(out Status01 sts)
        {
            return CPX_AppMain_UpDateData01(out sts);
        }

        // 追加(2025.6.19yori)
        static public int UpDateData02(out Status02 sts)
        {
            return CPX_AppMain_UpDateData02(out sts);
        }

        // 追加(2025.6.24yori)
        static public int UpDateData03(out Status03 sts)
        {
            return CPX_AppMain_UpDateData03(out sts);
        }

        // 追加(2025.7.31yori)
        // 引数追加(2025.9.22yori)
        static public int UpDateData04(out Threshold th, int id)
        {
            return CPX_AppMain_UpDateData04(out th, id);
        }

        // 追加(2025.8.7yori)
        static public int UpDateData05(out Gauge ga)
        {
            return CPX_AppMain_UpDateData05(out ga);
        }

        // 追加(2025.10.3yori)
        static public int UpDateData06(out Status04 sts)
        {
            return CPX_AppMain_UpDateData06(out sts);
        }

        // 追加(2025.10.6yori)
        static public int CountCheck(out Status04 sts)
        {
            return CPX_AppMain_CountCheck(out sts);
        }

        // 追加(2025.7.18yori)
        static public int UpDateData01_Write(in Status01 sts)
        {
            return CPX_AppMain_UpDateData01_Write(in sts);
        }

        // 追加(2025.8.17yori)
        static public int UpDateData02_Write(in Status02 sts)
        {
            return CPX_AppMain_UpDateData02_Write(in sts);
        }

        // 追加(2025.8.1yori)
        // 引数追加(2025.9.22yori)
        static public int UpDateData04_Write(in Threshold th, int id)
        {
            return CPX_AppMain_UpDateData04_Write(in th, id);
        }

        // 追加(2025.8.9yori)
        static public int UpDateData05_Write(in Gauge ga)
        {
            return CPX_AppMain_UpDateData05_Write(in ga);
        }

        // 追加(2025.8.1yori)
        // 引数追加(2025.9.22yori)
        static public int UpDateData04_Default(out Threshold th, int id)
        {
            return CPX_AppMain_UpDateData04_Default(out th, id);
        }

        // 追加(2025.8.9yori)
        static public int UpDateData05_Default(out Gauge ga)
        {
            return CPX_AppMain_UpDateData05_Default(out ga);
        }

        // 2025.9.2 add eba
        static public int MesCallBack()
        {
            return CPX_AppMain_MesCallBack();
        }

        // 追加(2025.12.28yori)
        static public int TestLplRecvMesBox()
        {
            return CPX_AppMain_TestLplRecvMesBox();
        }
    }
}
