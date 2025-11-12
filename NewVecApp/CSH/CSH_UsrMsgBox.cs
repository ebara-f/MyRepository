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
    public partial class UsrMsgBox
    {
        public delegate int UMB_CBFUNC(int msgID, int capID, int button, int icon);

        #region C/C++DLL-関数定義
        [DllImport("CPX.dll")]
        public extern static void CPX_UsrMsgBox_SetCB(UMB_CBFUNC cb);
        #endregion
        /// <summary>
        /// コールバック関数のセット
        /// </summary>

        static public void SetCB(UMB_CBFUNC cb)
        {
            CPX_UsrMsgBox_SetCB(cb);
        }

    }
}
