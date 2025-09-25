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
    public partial class ErrMsg
    {
        public delegate void ER_CBFUNC(int msgID);

        #region C/C++DLL-関数定義
        [DllImport("CPX.dll")]
        public extern static void CPX_ErrMsg_SetCB(ER_CBFUNC cb);

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_ErrMsg_GetMsg(int MsgID, ref StringBuilder sb, int str_count);

        #endregion
        /// <summary>
        /// コールバック関数のセット
        /// </summary>

        static public void SetCB(ER_CBFUNC cb)
        {
            CPX_ErrMsg_SetCB(cb);
        }

        /// <summary>
        /// メッセージの取得
        /// </summary>
        /// <param name="MsgID">メッセージID</param>
        /// <param name="Str">文字列</param>
        /// <param name="Str_count">文字列バッファ数</param>

        static public int GetMsg(
            int MsgID, ref string Str, int Str_count)
        {
            int rc;
            StringBuilder sb = null;

            // コマンドからの出力（文字列）を受け取るためのStringBuilderの生成
            if (Str_count > 0)
            {
                sb = new StringBuilder(Str_count);
            }

            // メッセージの取得
            rc = CPX_ErrMsg_GetMsg(MsgID, ref sb, Str_count );
            if (rc != 0)
            {
                return rc;
            }

            // コマンドからの出力（文字列）の抽出
            if (Str_count > 0)
            {
                Str = sb.ToString();
            }

            return 0;
        }
    }
}
