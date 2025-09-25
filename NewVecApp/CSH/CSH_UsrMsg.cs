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
    public partial class UsrMsg
    {
        public delegate void SM_CBFUNC(int msgID);

        #region C/C++DLL-関数定義
        [DllImport("CPX.dll")]
        public extern static void CPX_UsrMsg_SetCB(SM_CBFUNC cb);

        [DllImport("CPX.dll", CharSet = CharSet.Unicode)]
        public extern static int CPX_UsrMsg_GetMsg(int MsgID, ref StringBuilder sb, int str_count);

        #endregion
        /// <summary>
        /// コールバック関数のセット
        /// </summary>

        static public void SetCB(SM_CBFUNC cb)
        {
            CPX_UsrMsg_SetCB(cb);
        }
    }
}
