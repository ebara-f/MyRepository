/***********************************************************************

    関数名 : [UV HD02]  pgt_uv_struct.h

    機  能 : ＵＶライブラリ用ヘッダファイル
             構造体の定義

    PGT UV Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_UV_STRUCT_H
#define PGT_UV_STRUCT_H



#include    "pgt_base.h"




/*----- Passing Points -----------------------------------------------*/

typedef  struct _pgt_uvps {
    double          t;                  /* parameter value            */
    double          xyzcod[3];          /* xyz coord. on surface      */
    double          pcod[2];            /* point on surface           */
    double          dist;               /* distance                   */
    long            divseg;             /* no. of sub segs. (1 or 2)  */
    long            apxokf;             /* approximation OK flag      */
    long            semflg;             /* seam flag                  */
    long            semflgADJ;          /* seam flag adjusted         */
    long            polflg;             /* pole flag                  */
    long            ptinfo;             /* point on arctic circle     */
    long            polsme;             /* pole position in a seg.    */
    long            idummy;             /* padding                    */

} PGT_UVPS, *PGT_UVPSP;



typedef  struct _pgt_uvpasspnt {
    long            npnt;               /* no. of passing points      */
    long            idmy1;              /* padding                    */
    PGT_SURFP       surf;               /* base surface               */
    PGT_CURVP       curv;               /* curve on the surface       */
    long            upol;               /* u pole flag                */
    long            vpol;               /* v pole flag                */
    double          ulimt[2];           /* u arctic circle            */
    double          vlimt[2];           /* v arctic circle            */
    long            usem;               /* u seam flag                */
    long            vsem;               /* v seam flag                */
    double          ulimt2[2];          /* u seam area                */
    double          vlimt2[2];          /* v seam area                */

    PGT_UVPS*       ps;                 /* passing point              */
    void*           pdummy;             /* padding                    */

} PGT_UVPASSPNT, *PGT_UVPASSPNTP;




/*----- Segment Curve Chain ------------------------------------------*/

typedef  struct _pgt_uvsegelem {
    PGT_CURVP       xyz_curv;           /* xyz curve                  */
    PGT_CURVP       uv_curv;            /* uv  curve                  */

    long            orig_index;         /* index of orig. cv array    */
    long            whole_seamF;        /* whole curv on seam         */
    long            adj_doneF;          /* adjusted done flag         */
    long            idummy;             /* padding                    */

    PGT_PNT         uv_pos0;            /* start pos. of uv curve     */
    long            u_semtchF0;         /* start seam touch in u      */
    long            v_semtchF0;         /* start seam touch in v      */
    long            u_poltchF0;         /* start pole touch in u      */
    long            v_poltchF0;         /* start pole touch in v      */

    PGT_PNT         uv_pos1;            /* end   pos. of uv curve     */
    long            u_semtchF1;         /* end   seam touch in u      */
    long            v_semtchF1;         /* end   seam touch in v      */
    long            u_poltchF1;         /* end   pole touch in u      */
    long            v_poltchF1;         /* end   pole touch in v      */

                                        /* for seam flag              */
                                        /* 0:none 1:bgn 2:end         */
                                        /* for pole flag              */
                                        /* 0:none 1:bgn 2:end 3:both  */

} PGT_UVSEGELEM, *PGT_UVSEGELEMP;



typedef  struct _pgt_uvsegcrvs {
    long            max_size;           /* max size                   */
    long            idummy;             /* padding                    */
    long            num_curv;           /* no. of segments in this    */
    long            orig_ncrv;          /* no. of original xyz curvs  */
    double          ubgn;               /* u start parameter of surf. */
    double          uend;               /* u end   parameter of surf, */
    double          vbgn;               /* v start parameter of surf. */
    double          vend;               /* v end   parameter of surf. */
    PGT_UVSEGELEM*  cv;                 /* segment curve              */
    void*           pdummy;             /* padding                    */

} PGT_UVSEGCRVS, *PGT_UVSEGCRVSP;




/*----- Polyline Chain -----------------------------------------------*/

typedef  struct _pgt_uvpolyed {
    PGT_POLYLINEP   uv_poly;            /* uv polyline                */
    void*           pdummy;             /* padding                    */

    long            whole_seamF;        /* whole curv on seam         */
    long            adj_doneF;          /* adjusted done flag         */

    PGT_PNT         uv_pos0;            /* start pos. of uv curve     */
    long            u_semtchF0;         /* start seam touch in u      */
    long            v_semtchF0;         /* start seam toucj in v      */
    long            u_poltchF0;         /* start pole touch in u      */
    long            v_poltchF0;         /* start pole toucj in v      */

    PGT_PNT         uv_pos1;            /* end   pos. of uv curve     */
    long            u_semtchF1;         /* end   seam touch in u      */
    long            v_semtchF1;         /* end   seam touch in v      */
    long            u_poltchF1;         /* end   pole touch in u      */
    long            v_poltchF1;         /* end   pole touch in v      */

} PGT_UVPOLYED, *PGT_UVPOLYEDP;



typedef  struct _pgt_uvpolylp {
    long            num_poly;           /* no. of polylines           */
    long            idummy;             /* padding                    */

    double          ubgn;               /* u start parameter of surf. */
    double          uend;               /* u end   parameter of surf, */
    double          vbgn;               /* v start parameter of surf. */
    double          vend;               /* v end   parameter of surf. */
                                        /* 0:none 1:bgn 2:end 3:both  */
    PGT_UVPOLYED*   ed;                 /* edge polyline              */
    void*           pdummy;             /* padding                    */

} PGT_UVPOLYLP, *PGT_UVPOLYLPP;




/*----- End of File --------------------------------------------------*/



#endif
