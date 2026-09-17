/***********************************************************************

    関数名 : [PLUS HD02]  pgt_plus_struct.h

    機  能 : ＰＬＵＳライブラリ用ヘッダファイル
             構造体の定義

    PGT PLUS Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_PLUS_STRUCT_H
#define PGT_PLUS_STRUCT_H



#include    "pgt_base.h"




/*--------------------------------------------------------------------*/
/*     BEZIER curve (degree = 3)                                      */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_bzseg4 {
    PGT_PNT     dpnt[4];                /* definition points          */
    double      arcleng;                /* arc length                 */
    double      tbgn;                   /* start parameter            */
    double      tend;                   /* end   parameter            */

} PGT_BZSEG4, *PGT_BZSEG4P;             /* x,y,z,w                    */



typedef  struct _pgt_bzcurv4 {
    long            nseg;               /* no. of segments            */
    long            idummy;             /* padding                    */
    PGT_BZSEG4*     seg;                /* array of segments          */
    void*           pdummy;             /* padding                    */

} PGT_BZCURV4, *PGT_BZCURV4P;


#define  pgt_BZCVNSEG4(p)        ( (p)->nseg )
#define  pgt_BZCVCOD4(p,n,m,k)   ( (p)->seg[(n)].dpnt[(m)].veccod[(k)] )
#define  pgt_BZCVARC4(p,n)       ( (p)->seg[(n)].arcleng )
#define  pgt_BZCVTBGN4(p,n)      ( (p)->seg[(n)].tbgn )
#define  pgt_BZCVTEND4(p,n)      ( (p)->seg[(n)].tend )




/*--------------------------------------------------------------------*/
/*     BEZIER surface (degree = 3)                                    */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_bzpch4 {
    double      ubgn;                   /* u start parameter          */
    double      uend;                   /* u end   parameter          */
    double      vbgn;                   /* v start parameter          */
    double      vend;                   /* v end   parameter          */
    PGT_PNT     defpnt[4][4];           /* definition points          */

} PGT_BZPCH4, *PGT_BZPCH4P;


typedef  struct _pgt_bzsurf4 {
    long            useg;               /* u no. of patches           */
    long            vseg;               /* v no. of patches           */
    PGT_BZPCH4*     pch;                /* array of patches           */
    void*           pdummy;             /* padding                    */

} PGT_BZSURF4, *PGT_BZSURF4P;


#define  pgt_BZSFUSEG4(p)        ( (p)->useg )
#define  pgt_BZSFVSEG4(p)        ( (p)->vseg )
#define  pgt_BZSFUBGN4(p,ua,va)  ( (p)->pch[((p)->useg)*(va)+(ua)].ubgn )
#define  pgt_BZSFUEND4(p,ua,va)  ( (p)->pch[((p)->useg)*(va)+(ua)].uend )
#define  pgt_BZSFVBGN4(p,ua,va)  ( (p)->pch[((p)->useg)*(va)+(ua)].vbgn )
#define  pgt_BZSFVEND4(p,ua,va)  ( (p)->pch[((p)->useg)*(va)+(ua)].vend )
#define  pgt_BZSFCOD4(p,ua,va,ub,vb,k)  \
        ( (p)->pch[((p)->useg)*(va)+(ua)].defpnt[(ub)][(vb)].veccod[(k)] )




/*--------------------------------------------------------------------*/
/*     Smooth Spline (Fairing Points)                                 */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_fairpnt {
    double      cod[3];                 /* passing points             */
    double      tpar;                   /* parameter position         */
    double      rho;                    /* adjusted curvature         */
    double      acc_area;               /* accumulated curvature area */

} PGT_FAIRPNT, *PGT_FAIRPNTP;


typedef  struct _pgt_chkseg {
    double      tbgn;                   /* start param. of this seg.  */
    double      tend;                   /* end   param. of this seg.  */
    long        ok_flag;                /* this seg. check has done   */
    long        npnt;                   /* no. of check points        */
    PGT_PNT*    ary_pnts;               /* check points               */
    double*     ary_tpar;               /* parameter on check points  */

} PGT_CHKSEG, *PGT_CHKSEGP;




/*--------------------------------------------------------------------*/
/*     end of file                                                    */
/*--------------------------------------------------------------------*/



#endif
