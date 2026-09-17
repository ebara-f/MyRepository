/***********************************************************************

    関数名 : [BASE HD03]  pgt_base_curve.h

    機  能 : ＢＡＳＥライブラリ用ヘッダファイル
             曲線の構造体

    PGT BASE Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_BASE_CURVE_H
#define PGT_BASE_CURVE_H



#include    "pgt_base_types.h"



/*--------------------------------------------------------------------*/
/*  Line                                                              */
/*  NOTE : (1) p(t) = origin + t * dirvec                             */
/*            (2) tbgn < tend                                         */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_line {
    PGT_CVTYPE  cvtype;                 /* PGT_CVTYPE_LINE            */
    int         dummy;                  /* padding                    */
    double      origin[3];              /* origin                     */
    double      dirvec[3];              /* direction vector (unit)    */
    double      tbgn;                   /* start parameter            */
    double      tend;                   /* end   parameter            */

} PGT_LINE, *PGT_LINEP;


#define     pgt_LIN_CVTYPE(p)           ( (p)->cvtype )
#define     pgt_LIN_ORIGIN(p,i)         ( (p)->origin[(i)] )
#define     pgt_LIN_DIRVEC(p,i)         ( (p)->dirvec[(i)] )
#define     pgt_LIN_TBGN(p)             ( (p)->tbgn )
#define     pgt_LIN_TEND(p)             ( (p)->tend )




/*--------------------------------------------------------------------*/
/*  Circle                                                            */
/*  NOTE : (1) p(t) = origin + rad * ( cos(t)*u_vec + sin(t)*v_vec )  */
/*         (2) v_vec is perpendicular to u_vec.                       */
/*         (3) bgnang < endang.                                       */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_circle {
    PGT_CVTYPE  cvtype;                 /* PGT_CVTYPE_CIRCLE          */
    int         dummy;                  /* padding                    */
    double      origin[3];              /* center                     */
    double      u_vec[3];               /* u vector (unit)            */
    double      v_vec[3];               /* v vector (unit)            */
    double      rad;                    /* radius                     */
    double      bgnang;                 /* start angle (radian)       */
    double      endang;                 /* end   angle (radian)       */

} PGT_CIRCLE, *PGT_CIRCLEP;


#define     pgt_CIR_CVTYPE(p)           ( (p)->cvtype )
#define     pgt_CIR_ORIGIN(p,i)         ( (p)->origin[(i)] )
#define     pgt_CIR_U_VEC(p,i)          ( (p)->u_vec[(i)] )
#define     pgt_CIR_V_VEC(p,i)          ( (p)->v_vec[(i)] )
#define     pgt_CIR_RAD(p)              ( (p)->rad )
#define     pgt_CIR_BGNANG(p)           ( (p)->bgnang )
#define     pgt_CIR_ENDANG(p)           ( (p)->endang )




/*--------------------------------------------------------------------*/
/*  Ellipse                                                           */
/*  NOTE : (1) p(t) = origin + u_rad * cos(t) * u_vec                 */
/*                           + v_rad * sin(t) * v_vec                 */
/*         (2) v_vec is perpendicular to u_vec.                       */
/*         (3) bgnang < endang.                                       */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_ellipse {
    PGT_CVTYPE  cvtype;                 /* PGT_CVTYPE_ELLIPSE         */
    int         dummy;                  /* padding                    */
    double      origin[3];              /* center                     */
    double      u_vec[3];               /* u vector (unit)            */
    double      v_vec[3];               /* v vector (unit)            */
    double      u_rad;                  /* u radius                   */
    double      v_rad;                  /* v radius                   */
    double      bgnang;                 /* start angle (radian)       */
    double      endang;                 /* end   angle (radian)       */

} PGT_ELLIPSE, *PGT_ELLIPSEP;


#define     pgt_ELL_CVTYPE(p)           ( (p)->cvtype )
#define     pgt_ELL_ORIGIN(p,i)         ( (p)->origin[(i)] )
#define     pgt_ELL_U_VEC(p,i)          ( (p)->u_vec[(i)] )
#define     pgt_ELL_V_VEC(p,i)          ( (p)->v_vec[(i)] )
#define     pgt_ELL_U_RAD(p)            ( (p)->u_rad )
#define     pgt_ELL_V_RAD(p)            ( (p)->v_rad )
#define     pgt_ELL_BGNANG(p)           ( (p)->bgnang )
#define     pgt_ELL_ENDANG(p)           ( (p)->endang )




/*--------------------------------------------------------------------*/
/*  Parabola                                                          */
/*  NOTE : (1) p(t) = origin + t*u_vec + alpha*t*t*v_vec              */
/*         (2) tbgn < tend.                                           */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_parabola {
    PGT_CVTYPE  cvtype;                 /* PGT_CVTYPE_PARABOLA        */
    int         dummy;                  /* padding                    */
    double      origin[3];              /* origin                     */
    double      u_vec[3];               /* u vector (unit)            */
    double      v_vec[3];               /* v vector (unit)            */
    double      alpha;                  /* 1/4 focus                  */
    double      tbgn;                   /* start parameter            */
    double      tend;                   /* end   parameter            */

} PGT_PARABOLA, *PGT_PARABOLAP;


#define     pgt_PAR_CVTYPE(p)           ( (p)->cvtype )
#define     pgt_PAR_ORIGIN(p,i)         ( (p)->origin[(i)] )
#define     pgt_PAR_U_VEC(p,i)          ( (p)->u_vec[(i)] )
#define     pgt_PAR_V_VEC(p,i)          ( (p)->v_vec[(i)] )
#define     pgt_PAR_ALPHA(p)            ( (p)->alpha )
#define     pgt_PAR_TBGN(p)             ( (p)->tbgn )
#define     pgt_PAR_TEND(p)             ( (p)->tend )




/*--------------------------------------------------------------------*/
/*  Hyperbola                                                         */
/*  NOTE : (1) p(t) = origin + alpha * sec(t) * u_vec                 */
/*                           + beta * tan(t) * v_vec                  */
/*         (2) v_vec is perpendicular to u_vec.                       */
/*         (3) bgnang < endang.                                       */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_hyperbola {
    PGT_CVTYPE  cvtype;                 /* PGT_CVTYPE_HYPERBOLA       */
    int         dummy;                  /* padding                    */
    double      origin[3];              /* origin                     */
    double      u_vec[3];               /* u vector (unit)            */
    double      v_vec[3];               /* v vector (unit)            */
    double      alpha;                  /* x = alpha * sec( t )       */
    double      beta;                   /* y = beta  * tan( t )       */
    double      bgnang;                 /* start parameter            */
    double      endang;                 /* end   parameter            */

} PGT_HYPERBOLA, *PGT_HYPERBOLAP;


#define     pgt_HYP_CVTYPE(p)           ( (p)->cvtype )
#define     pgt_HYP_ORIGIN(p,i)         ( (p)->origin[(i)] )
#define     pgt_HYP_U_VEC(p,i)          ( (p)->u_vec[(i)] )
#define     pgt_HYP_V_VEC(p,i)          ( (p)->v_vec[(i)] )
#define     pgt_HYP_ALPHA(p)            ( (p)->alpha )
#define     pgt_HYP_BETA(p)             ( (p)->beta )
#define     pgt_HYP_BGNANG(p)           ( (p)->bgnang )
#define     pgt_HYP_ENDANG(p)           ( (p)->endang )




/*--------------------------------------------------------------------*/
/*     Polynomial type curve                                          */
/*--------------------------------------------------------------------*/

/*----- coefficients of polynomial curve segments --------------------*/

typedef  struct _pgt_cvcoef {
    double      cod[4];                 /* for (wx,wy,wz,w)           */

} PGT_CVCOEF, *PGT_CVCOEFP;



/*----- segments of polynomial curve ---------------------------------*/

typedef  struct _pgt_plcvseg {
    double      tbgn;                   /* start parameter            */
    double      tend;                   /* end   parameter            */
    PGT_CVCOEF* coef;                   /* coefficients               */
    void*       pdummy;                 /* padding                    */

} PGT_PLCVSEG, *PGT_PLCVSEGP;



/*----- polynomial curve ---------------------------------------------*/

typedef struct _pgt_plcurv {
    long            nseg;               /* no. of segments            */
    long            deg;                /* degree (order-1)           */
    long            ratflg;             /* rat. flag  0:none 1:yes    */
    long            idummy;             /* padding                    */
    PGT_PLCVSEG*    seg;                /* segments                   */
    void*           pdummy;             /* padding                    */

} PGT_PLCURV, *PGT_PLCURVP;


#define     pgt_PLCVNSEG(P)         ( (P)->nseg   )
#define     pgt_PLCVDEG(P)          ( (P)->deg    )
#define     pgt_PLCVRATFLG(P)       ( (P)->ratflg )

#define     pgt_PLCVTBGN(P,S)       ( (P)->seg[(S)].tbgn )
#define     pgt_PLCVTEND(P,S)       ( (P)->seg[(S)].tend )
#define     pgt_PLCVCOEF(P,S,D,K)   ( (P)->seg[(S)].coef[(D)].cod[(K)] )


#define     pgt_PLCVSEGP(P)         ( (P)->seg )




/*--------------------------------------------------------------------*/
/*     work area for de Boor Cox                                      */
/*--------------------------------------------------------------------*/

/*----- coordinates (ordinaly) ---------------------------------------*/

typedef  struct _pgt_cvdbrpt {
    double      cod[3];                 /* coordinates (ordinaly)     */

} PGT_CVDBRPT, *PGT_CVDBRPTP;



/*----- coordinates (homogeneous) ------------------------------------*/

typedef  struct _pgt_cvdbrqt {
    double      cod[4];                 /* coordinates (homogeneous)  */

} PGT_CVDBRQT, *PGT_CVDBRQTP;



/*----- work area for de Boor Cox ------------------------------------*/

typedef  struct _pgt_cvdeboor {
    long                mord;           /* order (private)            */
    long                ncpnt;          /* no. of ctrl pnt (private)  */
    double*             bfuncX;         /* BS func : [ncpnt][mord]    */
    double*             bfuncD;         /* BS func : [ncpnt][mord]    */
    PGT_CVDBRPT*        pt;             /* ordinaly points    : [mord]*/
    PGT_CVDBRQT*        qt;             /* homogeneous points : [mord]*/

} PGT_CVDEBOOR, *PGT_CVDEBOORP;


#define     pgt_DBRMORD(P)          ( (P)->mord  )
#define     pgt_DBRNCPNT(P)         ( (P)->ncpnt )
    
#define     pgt_CVBFUNCXP(P)        ( (P)->bfuncX )
#define     pgt_CVBFUNCDP(P)        ( (P)->bfuncD )
#define     pgt_CVDBRPTP(P)         ( (P)->pt     )
#define     pgt_CVDBRQTP(P)         ( (P)->qt     )

#define     pgt_CVBFUNCX(P,N,M)     ( (P)->bfuncX[(pgt_DBRMORD(P))*(N)+(M)] )
#define     pgt_CVBFUNCD(P,N,M)     ( (P)->bfuncD[(pgt_DBRMORD(P))*(N)+(M)] )
#define     pgt_CVDBRPT(P,M,K)      ( (P)->pt[(M)].cod[(K)] )
#define     pgt_CVDBRQT(P,M,K)      ( (P)->qt[(M)].cod[(K)] )




/*--------------------------------------------------------------------*/
/*     NURBS curve                                                    */
/*--------------------------------------------------------------------*/

/*----- control points -----------------------------------------------*/

typedef  struct _pgt_cvcpnt {
    double      cod[4];                 /* coordinates (homogeneous)  */

}  PGT_CVCPNT, *PGT_CVCPNTP;



/*----- knots --------------------------------------------------------*/

typedef     double      PGT_CVKNOT;
typedef     double*     PGT_CVKNOTP;



/*----- curve geometry -----------------------------------------------*/

typedef  union _pgt_cvgeom {
    PGT_LINE*           lin;            /* line                       */
    PGT_CIRCLE*         cir;            /* circle                     */
    PGT_ELLIPSE*        ell;            /* ellipse                    */
    PGT_PARABOLA*       par;            /* parabola                   */
    PGT_HYPERBOLA*      hyp;            /* hyperbola                  */
    long*               all;            /* general                    */

} PGT_CVGEOM;


/*----- NURBS curve --------------------------------------------------*/

typedef  struct  _pgt_curv {

    /*----- Basic Members -----*/
    PGT_CVTYPE          cvtype;         /* type    0:general          */
    PGT_CLSFLG          clsflg;         /* closed flag    -1:unknown  */
    PGT_PLNFLG          plnflg;         /* planar flag    -1:unknown  */
    PGT_RATFLG          ratflg;         /* rational flag  -1:unknown  */

    long                mord;           /* order                      */
    long                ncpnt;          /* no. of control points      */
    PGT_CVKNOT*         knot;           /* knots                      */
    PGT_CVCPNT*         cpnt;           /* control points             */

    /*----- Work Area for Calculation -----*/
    PGT_CVDEBOOR*       cvdeboor;       /* work area for deBoorCox    */
    PGT_PLCURV*         plcurv;         /* polynomial expression      */

    /*----- Extension -----*/
    PGT_CVGEOM          cvgeom;         /* analytic   expression      */
    void*               pdummy;         /* padding                    */

    long                userID;         /* user ID                    */
    long                usrflg;         /* user flag                  */
    long                lay_no;         /* layer no.                  */
    long                icolor;         /* color char[4] r.g.b.a      */
    long                dgn_pntF;       /* degen point flag           */
                                        /* ( IGES Only )              */
    long                idummy;         /* padding                    */

    double              kept_t;         /* kept t for iteration call  */
    double              dtds;           /* coefficient  dt/ds         */

} PGT_CURV, *PGT_CURVP;


/*----- for General Users -----*/
#define  pgt_MORD(P)            ( (P)->mord )
#define  pgt_NCPNT(P)           ( (P)->ncpnt )
#define  pgt_CVCPNT(P,N,K)      ( (P)->cpnt[(N)].cod[(K)] )
#define  pgt_CVKNOT(P,J)        ( (P)->knot[(J)] )
#define  pgt_BGN_PARAM(P)       ( (P)->knot[pgt_MORD(P)-1] )
#define  pgt_END_PARAM(P)       ( (P)->knot[pgt_NCPNT(P)] )
#define  pgt_TBGN(P)            ( (P)->knot[pgt_MORD(P)-1] )
#define  pgt_TEND(P)            ( (P)->knot[pgt_NCPNT(P)] )

#define  pgt_CVTYPE(P)          ( (P)->cvtype   )
#define  pgt_CLSFLG(P)          ( (P)->clsflg )
#define  pgt_PLNFLG(P)          ( (P)->plnflg )
#define  pgt_RATFLG(P)          ( (P)->ratflg )

/*----- for Library Developer -----*/
#define  pgt_CVCPNTP(P)         ( (P)->cpnt   )
#define  pgt_CVKNOTP(P)         ( (P)->knot   )
#define  pgt_CVDEBOORP(P)       ( (P)->cvdeboor )
#define  pgt_PLCURVP(P)         ( (P)->plcurv )
#define  pgt_CVGEOM(P)          ( (P)->cvgeom )

#define  pgt_CVGMALLP(P)        ( (P)->cvgeom.all )
#define  pgt_CVGMLINP(P)        ( (P)->cvgeom.lin )
#define  pgt_CVGMCIRP(P)        ( (P)->cvgeom.cir )
#define  pgt_CVGMELLP(P)        ( (P)->cvgeom.ell )
#define  pgt_CVGMPARP(P)        ( (P)->cvgeom.par )
#define  pgt_CVGMHYPP(P)        ( (P)->cvgeom.hyp )

#define  pgt_CVUSERID(P)        ( (P)->userID )
#define  pgt_CVUSRFLG(P)        ( (P)->usrflg )
#define  pgt_CVLAYNO(P)         ( (P)->lay_no )
#define  pgt_CVICOLOR(P)        ( (P)->icolor )
#define  pgt_CVDGNPNTF(P)       ( (P)->dgn_pntF )

#define  pgt_KEPTT(P)           ( (P)->kept_t )
#define  pgt_DTDS(P)            ( (P)->dtds )




/*--------------------------------------------------------------------*/
/*     Flex Array of NURBS Curves                                     */
/*--------------------------------------------------------------------*/

/*----- Element Curve ------------------------------------------------*/

typedef  struct _pgt_elmcurv {
    PGT_CURVP       curv;               /* curve (don't free)         */
    void*           pdummy;             /* padding                    */
    long            curvID;             /* curve ID                   */
    long            userF;              /* user flag                  */

} PGT_ELMCURV, *PGT_ELMCURVP;



/*----- Flex Array of Curves -----------------------------------------*/

typedef  struct _pgt_flexcurvs {
    long            max_size;           /* max_size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_elmcurv;        /* no. of valid curves        */
    long            idummy;             /* padding                    */
    PGT_ELMCURV*    ary_elmcurv;        /* curves                     */
    void*           pdummy;             /* padding                    */

} PGT_FLEXCURVS, *PGT_FLEXCURVSP;




/*--------------------------------------------------------------------*/
/*     Composite Curve                                                */
/*--------------------------------------------------------------------*/

/*----- Composite Segment --------------------------------------------*/

typedef  struct _pgt_compseg {

    /*----- Basic Members -----*/
    long            edgeID;             /* this segment ID            */
    PGT_CVTYPE      cvtype;             /* type                       */
    PGT_CURVP       curv;               /* curve                      */
    PGT_LINEP       line;               /* line                       */
    PGT_CIRCLEP     circle;             /* circle                     */
    PGT_ELLIPSEP    ellipse;            /* ellipse                    */
    PGT_PARABOLAP   parabola;           /* parabola                   */
    PGT_HYPERBOLAP  hyperbola;          /* hyperbola                  */

    double          seg_tbgn;           /* start parameter            */
    double          seg_tend;           /* end   parameter            */

    /*----- Extension -----*/
    long            ref_revflg;         /* if curv dir is reversed    */
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            icolor;             /* i color                    */

} PGT_COMPSEG, *PGT_COMPSEGP;


#define     pgt_CMPSEGID(P)         ( (P)->edgeID    )
#define     pgt_CMPSEGTYPE(P)       ( (P)->cvtype    )
#define     pgt_CMPSEGCURV(P)       ( (P)->curv      )
#define     pgt_CMPSEGLINE(P)       ( (P)->line      )
#define     pgt_CMPSEGCIRCLE(P)     ( (P)->circle    )
#define     pgt_CMPSEGELLIPSE(P)    ( (P)->ellipse   )
#define     pgt_CMPSEGPARABOLA(P)   ( (P)->parabola  )
#define     pgt_CMPSEGHYPERBOLA(P)  ( (P)->hyperbola )

#define     pgt_CMPSEGTBGN(P)       ( (P)->seg_tbgn  )
#define     pgt_CMPSEGTEND(P)       ( (P)->seg_tend  )

#define     pgt_CMPSEGREFREVFLG(P)  ( (P)->ref_revflg )
#define     pgt_CMPSEGUSERID(P)     ( (P)->userID     )
#define     pgt_CMPSEGUSEFLG(P)     ( (P)->useflg     )
#define     pgt_CMPSEGICOLOR(P)     ( (P)->icolor     )



/*----- Composite Curve ----------------------------------------------*/

typedef  struct _pgt_compcrv {

    /*----- Basic Members -----*/
    long            ccrvID;             /* this curve ID              */
    long            num_segment;        /* no. of segment             */
    PGT_COMPSEGP*   ary_segment;        /* segments                   */
    void*           pdummy;             /* padding                    */

    /*----- Extension -----*/
    long            clsflg;             /* closed flag                */
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            icolor;             /* color                      */

} PGT_COMPCRV, *PGT_COMPCRVP;


#define     pgt_CMPCRVID(P)         ( (P)->ccrvID      )
#define     pgt_CMPCRVNSEG(P)       ( (P)->num_segment )
#define     pgt_CMPCRVSEGARY(P)     ( (P)->ary_segment )
#define     pgt_CMPCRVSEG(P,N)      ( (P)->ary_segment[(N)] )

#define     pgt_CMPCRVCLSFLG(P)     ( (P)->clsflg )
#define     pgt_CMPCRVUSERID(P)     ( (P)->userID )
#define     pgt_CMPCRVUSEFLG(P)     ( (P)->useflg )
#define     pgt_CMPCRVICOLOR(P)     ( (P)->icolor )




/*--------------------------------------------------------------------*/
/*     end of file                                                    */
/*--------------------------------------------------------------------*/



#endif
