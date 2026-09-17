/***********************************************************************

    関数名 : [IT HD04]  pgt_it_struct.h

    機  能 : ＩＴライブラリ用ヘッダファイル
             構造体の定義

    PGT IT Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_IT_STRUCT_H
#define PGT_IT_STRUCT_H



#include    "pgt_base.h"



/*----- Intersection Point -------------------------------------------*/

typedef  struct _pgt_intpnt {

    /*----- Basic Membere -----*/
    PGT_PNT         pnt;                /* intersection point         */
    double          self_tpar;          /* t parameter on itself      */
    double          self_upar;          /* u parameter on itself      */
    double          self_vpar;          /* v parameter on itself      */
    double          opos_tpar;          /* t parameter on oposite     */
    double          opos_upar;          /* u parameter on oposite     */
    double          opos_vpar;          /* v parameter on oposite     */

    /*----- Extension -----*/
    long            dupflg;             /* if ON point is duplicated  */
    long            idummy;             /* padding                    */

} PGT_INTPNT, *PGT_INTPNTP;




/*----- Intersection Curve -------------------------------------------*/

typedef  struct _pgt_intcrv {
    PGT_CURVP       xyzcurv;            /* xyz intsec curve           */
    PGT_CURVP       uvcurv0;            /* uv  intsec curve on sf0    */
    PGT_CURVP       uvcurv1;            /* uv  intsec curve on sf1    */
    void*           pdummy;             /* padding                    */
    long            dgnflg;             /* degenerate flag            */
    long            idummy;             /*  (0:none, 1:degenerate)    */
    PGT_PNT         dgnpos;             /* position of degenerated cv */

} PGT_INTCRV, *PGT_INTCRVP;




/*----- Intersection Segment -----------------------------------------*/

typedef  struct _pgt_intseg {

    /*----- Passing Points -------------------------------------------*/
    PGT_PNT         xyzpnts[4];         /* xyz passing points         */
    PGT_PNT         uvpnts0[4];         /* uv  passing points on sf0  */
    PGT_PNT         uvpnts1[4];         /* uv  passing points on sf1  */

    /*----- Interpolation Curve --------------------------------------*/
    PGT_CURVP       xyzcurv;            /* xyz intsec curve           */
    PGT_CURVP       uvcurv0;            /* uv  intsec curve on sf0    */
    PGT_CURVP       uvcurv1;            /* uv  intsec curve on sf1    */
    void*           pdummy;             /* padding                    */

    /*----- Support Info. --------------------------------------------*/
    long            useflg;             /* used flag                  */
    long            revflg;             /* reversed flag              */

} PGT_INTSEG, *PGT_INTSEGP;



typedef  struct _pgt_intchain {
    long            num_intseg;         /* no. of segments            */
    long            idummy;             /* padding                    */
    PGT_INTSEG*     ary_intseg;         /* array of intsec segments   */
    void*           pdummy;             /* padding                    */

} PGT_INTCHAIN, *PGT_INTCHAINP;




/*----- Closest Points between Curves --------------------------------*/

typedef  struct _pgt_clspnt {
    PGT_PNT         pos1;               /* closest point on curve 1   */
    PGT_PNT         pos2;               /* closest point on curve 2   */
    double          t1;                 /* closest param pos. on cv1  */
    double          t2;                 /* closest param pos. on cv2  */
    long            cond1;              /* point condition on curve1  */
    long            cond2;              /* point condition on curve2  */
                                        /*  (0:at mid  1:bgn 2:end)   */
    double          dist;               /* dist between given curves  */

} PGT_CLSPNT, *PGT_CLSPNTP;




/*----- Polyline Fragment --------------------------------------------*/

typedef  struct _pgt_polyfrag {
    PGT_POLYLINEP   poly;               /* polyline (reference only)  */
    void*           pdummy;             /* padding                    */
    long            inoutF;             /* inout flag -1:unknown      */
    long            idummy;             /* 0:inside 1:outside 2:both  */
    PGT_PNT         pntS;               /* start position             */
    PGT_PNT         pntE;               /* end   position             */
    long            useflg;             /* use flag                   */
    long            revflg;             /* reversed flag              */

} PGT_POLYFRAG, *PGT_POLYFRAGP;




/*----- Closest Points between Curves --------------------------------*/

typedef  struct _pgt_itinitpos {
    PGT_PNT         xyzpos;             /* xyz pos                    */
    PGT_PNT         uvpos0;             /* uv pos on surf #0          */
    PGT_PNT         uvpos1;             /* uv pos on surf #1          */
    long            useflg;             /* used flag                  */
    long            idummy;             /* 0:none 1:as start 2:close  */

} PGT_ITINITPOS, *PGT_ITINITPOSP;




/*----- Flex Intpnts -------------------------------------------------*/

typedef  struct _pgt_flexintpnts {
    long            max_size;           /* max_size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_intpnt;         /* no. of valid points        */
    long            idummy;             /* padding                    */
    PGT_INTPNT*     ary_intpnt;         /* points                     */
    void*           pdummy;             /* padding                    */

} PGT_FLEXINTPNTS, *PGT_FLEXINTPNTSP;



/*----- Passing Points -----------------------------------------------*/

typedef  struct _pgt_itelmpnt {
    double          xyz_tpar;           /* t param on curve           */
    PGT_PNT         xyz_pos;            /* xyz pos.                   */
    PGT_PNT         uv_pos0;            /* uv pos. on suuf #0         */
    PGT_PNT         uv_pos1;            /* uv pos. on suuf #1         */
    long            NG_approxF;         /* approximation flag         */
    long            idummy;             /* padding                    */

} PGT_ITELMPNT, *PGT_ITELMPNTP;


typedef  struct _pgt_itpasspnts {
    long            num_elmpnt;         /* no. of element points      */
    long            idummy;             /* padding                    */
    PGT_ITELMPNT*   ary_elmpnt;         /* element points             */
    void*           pdummy;             /* padding                    */

} PGT_ITPASSPNTS, *PGT_ITPASSPNTSP;




/*----- End of File --------------------------------------------------*/



#endif
