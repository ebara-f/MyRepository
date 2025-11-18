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
    public partial class ProgBar
    {
        public delegate void PGB_CBFUNC1(int id);
        public delegate void PGB_CBFUNC2();

        #region C/C++DLL-関数定義
        [DllImport("CPX.dll")]
        public extern static void CPX_ProgBar_SetCB1(PGB_CBFUNC1 cb);
        [DllImport("CPX.dll")] 
        public extern static void CPX_ProgBar_SetCB2(PGB_CBFUNC2 cb);
        #endregion
        /// <summary>
        /// コールバック関数のセット
        /// </summary>

        static public void SetCB1(PGB_CBFUNC1 cb)
        {
            CPX_ProgBar_SetCB1(cb);
        }

        static public void SetCB2(PGB_CBFUNC2 cb)
        {
            CPX_ProgBar_SetCB2(cb);
        }

    }
}
