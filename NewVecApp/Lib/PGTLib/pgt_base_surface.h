/***********************************************************************

    関数名 : [BASE HD04]  pgt_base_surface.h

    機  能 : ＢＡＳＥライブラリ用ヘッダファイル
             曲面の構造体

    PGT BASE Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_BASE_SURFACE_H
#define PGT_BASE_SURFACE_H



#include    "pgt_base_types.h"




/*--------------------------------------------------------------------*/
/*  Plane                                                             */
/*  note : (1) p(u,v) = origin + u * u_vec + v * v_vec                */
/*         (2) v_vec is perpendicular to u_vec                        */
/*         (3) |u_vec| = |v_vec| = |n_vec| = 1.0                      */
/*         (4) ubgn < uend, vbgn < vend                               */
/*--------------------------------------------------------------------*/

typedef struct  _pgt_plane {
    PGT_SFTYPE  sftype;                 /* PGT_SFTYPE_PLANE           */
    int         revflg;                 /* if ON surf dir is reversed */
    double      origin[3];              /* origin                     */
    double      u_vec[3];               /* 1st vector                 */
    double      v_vec[3];               /* 2nd vector                 */
    double      n_vec[3];               /* Normal vector              */
    double      ubgn;                   /* u start boundary           */
    double      uend;                   /* u end   boundary           */
    double      vbgn;                   /* v start boundary           */
    double      vend;                   /* v end   boundary           */

} PGT_PLANE, *PGT_PLANEP;


#define     pgt_PLN_SFTYPE(p)           ( (p)->sftype )
#define     pgt_PLN_REVFLG(p)           ( (p)->revflg )

#define     pgt_PLN_ORIGIN(p,i)         ( (p)->origin[(i)] )
#define     pgt_PLN_U_VEC(p,i)          ( (p)->u_vec[(i)] )
#define     pgt_PLN_V_VEC(p,i)          ( (p)->v_vec[(i)] )
#define     pgt_PLN_N_VEC(p,i)          ( (p)->n_vec[(i)] )
#define     pgt_PLN_UBGN(p)             ( (p)->ubgn )
#define     pgt_PLN_UEND(p)             ( (p)->uend )
#define     pgt_PLN_VBGN(p)             ( (p)->vbgn )
#define     pgt_PLN_VEND(p)             ( (p)->vend )




/*--------------------------------------------------------------------*/
/*  Cylinder                                                          */
/*  note : (1) p(u,v) = origin +                                      */
/*                      + rad * ( cos(u) * u_vec + sin(u) * v_vec )   */
/*                      + v * n_vec                                   */
/*         (2) v_vec is perpendicular to u_vec                        */
/*         (3) |u_vec| = |v_vec| = |n_vec| = 1.0                      */
/*         (4) Angle is measured from u_vec to v_vec                  */
/*         (5) bgnang < endang, botheight < topheight                 */
/*--------------------------------------------------------------------*/

typedef struct  _pgt_cylinder {
    PGT_SFTYPE  sftype;                 /* PGT_SFTYPE_CYLINDER        */
    int         revflg;                 /* if ON surf dir is reversed */
    double      origin[3];              /* Origin of bottom plane     */
    double      u_vec[3];               /* Vect to define bottom plane*/
    double      v_vec[3];               /* Vect to define bottom plane*/
    double      n_vec[3];               /* Vector of rotation axis    */
    double      rad;                    /* radius                     */
    double      bgnang;                 /* start angle ( radian )     */
    double      endang;                 /* end   angle ( radian )     */
    double      botheight;              /* start height               */
    double      topheight;              /* end   height               */

} PGT_CYLINDER, *PGT_CYLINDERP;


#define     pgt_CYL_SFTYPE(p)           ( (p)->sftype )
#define     pgt_CYL_REVFLG(p)           ( (p)->revflg )

#define     pgt_CYL_ORIGIN(p,i)         ( (p)->origin[(i)] )
#define     pgt_CYL_U_VEC(p,i)          ( (p)->u_vec[(i)] )
#define     pgt_CYL_V_VEC(p,i)          ( (p)->v_vec[(i)] )
#define     pgt_CYL_N_VEC(p,i)          ( (p)->n_vec[(i)] )
#define     pgt_CYL_RAD(p)              ( (p)->rad )
#define     pgt_CYL_BGNANG(p)           ( (p)->bgnang )
#define     pgt_CYL_ENDANG(p)           ( (p)->endang )
#define     pgt_CYL_BOTHEIGHT(p)        ( (p)->botheight )
#define     pgt_CYL_TOPHEIGHT(p)        ( (p)->topheight )




/*--------------------------------------------------------------------*/
/*  Cone                                                              */
/*  note : (1) p(u,v) = origin                                        */
/*                      + ( baserad - v * tan(apxang) ) *             */
/*                               ( cos(u) * u_vec + sin(u) * v_vec )  */
/*                      + v * n_vec                                   */
/*         (2) v_vec is perpendicular to u_vec                        */
/*         (3) |u_vec| = |v_vec| = |n_vec| = 1.0                      */
/*         (4) height is measured from origin                         */
/*         (5) Radius decreases along axis sign of apxang is positive */
/*         (6) Angle is measured from u_vec to v_vec                  */
/*         (7) bgnang < endang, bgnheight < endheight                 */
/*--------------------------------------------------------------------*/

typedef struct  _pgt_cone {
    PGT_SFTYPE  sftype;                 /* PGT_SFTYPE_CONE            */
    int         revflg;                 /* if ON surf dir is reversed */
    double      origin[3];              /* Apex point of cone         */
    double      u_vec[3];               /* 1st vector                 */
    double      v_vec[3];               /* 2nd vector                 */
    double      n_vec[3];               /* Vector of rotation axis    */
    double      apxang;                 /* angle between axis and     */
                                        /* mother line  (radian)      */
    double      baserad;                /* base radius                */
    double      bgnang;                 /* start angle  ( radian )    */
    double      endang;                 /* end   angle  ( radian )    */
    double      bgnheight;              /* start height               */
    double      endheight;              /* end   height               */

} PGT_CONE, *PGT_CONEP;


#define     pgt_CON_SFTYPE(p)           ( (p)->sftype      )
#define     pgt_CON_REVFLG(p)           ( (p)->revflg      )

#define     pgt_CON_ORIGIN(p,i)         ( (p)->origin[(i)] )
#define     pgt_CON_U_VEC(p,i)          ( (p)->u_vec[(i)]  )
#define     pgt_CON_V_VEC(p,i)          ( (p)->v_vec[(i)]  )
#define     pgt_CON_N_VEC(p,i)          ( (p)->n_vec[(i)]  )
#define     pgt_CON_APXANG(p)           ( (p)->apxang      )
#define     pgt_CON_BASERAD(p)          ( (p)->baserad     )
#define     pgt_CON_BGNANG(p)           ( (p)->bgnang      )
#define     pgt_CON_ENDANG(p)           ( (p)->endang      )
#define     pgt_CON_BGNHEIGHT(p)        ( (p)->bgnheight   )
#define     pgt_CON_ENDHEIGHT(p)        ( (p)->endheight   )




/*--------------------------------------------------------------------*/
/*  Sphere                                                            */
/*  note : (1) p(u,v) = origin +                                      */
/*                  + rad * cos(v) * ( cos(u)*u_vec + sin(u)*v_vec )  */
/*                  + rad * sin(v) * n_vec                            */
/*         (2) v_vec is perpendicular to u_vec                        */
/*         (3) |u_vec| = |v_vec| = |n_vec| = 1.0                      */
/*         (4) bgnang and endang is angle of revolution around n_vec  */
/*         (4) bgnang and endang are measured from u_vec to v_vec     */
/*         (5) bgnangR < endangR  bgnangN < endangN                   */
/*         (6) bgnangN and endangN are measured from u_vec to n_vec   */
/*         (7) - PI/2 <= bgnangN < endangN <= PI/2                    */
/*--------------------------------------------------------------------*/

typedef struct  _pgt_sphere {
    PGT_SFTYPE  sftype;                 /* PGT_SFTYPE_SPHERE          */
    int         revflg;                 /* if ON surf dir is reversed */
    double      origin[3];              /* center                     */
    double      u_vec[3];               /* 1st vector                 */
    double      v_vec[3];               /* 2nd vector                 */
    double      n_vec[3];               /* 3rd vector                 */
    double      rad;                    /* radius                     */
    double      bgnangR;                /* start angle  ( radian )    */
    double      endangR;                /* end   angle  ( radian )    */
    double      bgnangN;                /* start angle  ( radian )    */
    double      endangN;                /* end   angle  ( radian )    */

} PGT_SPHERE, *PGT_SPHEREP;


#define     pgt_SPH_SFTYPE(p)           ( (p)->sftype      )
#define     pgt_SPH_REVFLG(p)           ( (p)->revflg      )

#define     pgt_SPH_ORIGIN(p,i)         ( (p)->origin[(i)] )
#define     pgt_SPH_U_VEC(p,i)          ( (p)->u_vec[(i)]  )
#define     pgt_SPH_V_VEC(p,i)          ( (p)->v_vec[(i)]  )
#define     pgt_SPH_N_VEC(p,i)          ( (p)->n_vec[(i)]  )
#define     pgt_SPH_RAD(p)              ( (p)->rad         )
#define     pgt_SPH_BGNANGR(p)          ( (p)->bgnangR     )
#define     pgt_SPH_ENDANGR(p)          ( (p)->endangR     )
#define     pgt_SPH_BGNANGN(p)          ( (p)->bgnangN     )
#define     pgt_SPH_ENDANGN(p)          ( (p)->endangN     )




/*--------------------------------------------------------------------*/
/*  Torus                                                             */
/*  note : (1) p(u,v) = origin                                        */
/*                      + ( majrad + minrad * cos(v) )                */
/*                             * ( cos(u) * u_vec + sin(u) * v_vec )  */
/*                      + minrad * sin(v) * n_vec                     */
/*         (2) v_vec is perpendicular to u_vec                        */
/*         (3) |u_vec| = |v_vec| = |n_vec| = 1.0                      */
/*         (4) bgnangMJ, endangMJ are revolution angle around n_vec   */
/*         (4) bgnangMJ, endangMJ are measured from u_vec to v_vec    */
/*         (5) bgnangMJ < endangMJ  bgnangMN < endangMN               */
/*         (6) bgnangMN, endangMN are measured from u_vec to n_vec    */
/*--------------------------------------------------------------------*/

typedef struct  _pgt_torus {
    PGT_SFTYPE  sftype;                 /* PGT_SFTYPE_TORUS           */
    int         revflg;                 /* if ON surf dir is reversed */
    double      origin[3];              /* center                     */
    double      u_vec[3];               /* 1st vector                 */
    double      v_vec[3];               /* 2nd vector                 */
    double      n_vec[3];               /* 3rd vector                 */
    double      majrad;                 /* major radius               */
    double      minrad;                 /* minor radius               */
    double      bgnangMJ;               /* start angle (major)(radian)*/
    double      endangMJ;               /* end   angle (major)(radian)*/
    double      bgnangMN;               /* start angle (minor)(radian)*/
    double      endangMN;               /* end   angle (minor)(radian)*/

} PGT_TORUS, *PGT_TORUSP;


#define     pgt_TRS_SFTYPE(p)           ( (p)->sftype      )
#define     pgt_TRS_REVFLG(p)           ( (p)->revflg      )

#define     pgt_TRS_ORIGIN(p,i)         ( (p)->origin[(i)] )
#define     pgt_TRS_U_VEC(p,i)          ( (p)->u_vec[(i)]  )
#define     pgt_TRS_V_VEC(p,i)          ( (p)->v_vec[(i)]  )
#define     pgt_TRS_N_VEC(p,i)          ( (p)->n_vec[(i)]  )
#define     pgt_TRS_MAJRAD(p)           ( (p)->majrad      )
#define     pgt_TRS_MINRAD(p)           ( (p)->minrad      )
#define     pgt_TRS_BGNANGMJ(p)         ( (p)->bgnangMJ    )
#define     pgt_TRS_ENDANGMJ(p)         ( (p)->endangMJ    )
#define     pgt_TRS_BGNANGMN(p)         ( (p)->bgnangMN    )
#define     pgt_TRS_ENDANGMN(p)         ( (p)->endangMN    )




/*--------------------------------------------------------------------*/
/*     Polynomial Type Surface                                        */
/*--------------------------------------------------------------------*/

/*----- Coefficients of Polynomial Surface Segments ------------------*/

typedef  struct _pgt_sfcoef {
    double      cod[4];                 /* for  xw, yw, zw, w         */

} PGT_SFCOEF, *PGT_SFCOEFP;



/*----- Segments of Polynomial Surface -------------------------------*/

typedef  struct _pgt_plsfpch {
    double      ubgn;                   /* u start parameter          */
    double      uend;                   /* u end   parameter          */
    double      vbgn;                   /* v start parameter          */
    double      vend;                   /* v end   parameter          */
    PGT_SFCOEF* coef;                   /* coefficents                */
    void*       pdummy;                 /* padding                    */

} PGT_PLSFPCH, *PGT_PLSFPCHP;



/*----- Polynomial Surface -------------------------------------------*/

typedef  struct _pgt_plsurf {
    long            useg;               /* u no. of u-patches         */
    long            vseg;               /* v no. of v-patches         */
    long            udeg;               /* u degree (order-1)         */
    long            vdeg;               /* v degree (order-1)         */
    long            uratflg;            /* u rat flag 0:none 1:yes    */
    long            vratflg;            /* v rat flag 0:none 1:yes    */
    PGT_PLSFPCH*    pch;                /* patch                      */
    void*           pdummy;             /* padding                    */

} PGT_PLSURF, *PGT_PLSURFP;


#define  pgt_PLSFUSEG(P)         ( (P)->useg    )
#define  pgt_PLSFVSEG(P)         ( (P)->vseg    )
#define  pgt_PLSFUDEG(P)         ( (P)->udeg    )
#define  pgt_PLSFVDEG(P)         ( (P)->vdeg    )
#define  pgt_PLSFURATFLG(P)      ( (P)->uratflg )
#define  pgt_PLSFVRATFLG(P)      ( (P)->vratflg )

#define  pgt_PLSFUBGN(P,SU,SV)   ( (P)->pch[(SV)*((P)->useg)+(SU)].ubgn )
#define  pgt_PLSFUEND(P,SU,SV)   ( (P)->pch[(SV)*((P)->useg)+(SU)].uend )
#define  pgt_PLSFVBGN(P,SU,SV)   ( (P)->pch[(SV)*((P)->useg)+(SU)].vbgn )
#define  pgt_PLSFVEND(P,SU,SV)   ( (P)->pch[(SV)*((P)->useg)+(SU)].vend )

#define  pgt_PLSFCOEF(P,SU,SV,DU,DV,K)  \
             ((P)->pch[(SV)*((P)->useg)+(SU)]. \
                 coef[(DU)*((P)->vdeg+1)+(DV)].cod[(K)])


#define  pgt_PLSFPCHP(P)         ( (P)->pch )




/*--------------------------------------------------------------------*/
/*     Work Area for de Boor Cox                                      */
/*--------------------------------------------------------------------*/

/*----- Coordinates (ordinaly) ---------------------------------------*/

typedef  struct _pgt_sfdbrpt {
    double      cod[3];                 /* coordinates (ordinaly)     */

} PGT_SFDBRPT, *PGT_SFDBRPTP;



/*----- Coordinates (homogeneous) ------------------------------------*/

typedef  struct _pgt_sfdbrqt {
    double      cod[4];                 /* coordinates (homogeneous)  */

} PGT_SFDBRQT, *PGT_SFDBRQTP;



/*----- Work Area for de Boor Cox ------------------------------------*/

typedef  struct _pgt_sfdeboor {
    long                uord;           /* u order (private)          */
    long                vord;           /* v order (private)          */
    long                ucpnt;          /* no. of u ctrl pnt (private)*/
    long                vcpnt;          /* no. of v ctrl pnt (private)*/
    double*             ubfuncX;        /* u BS func : [ucpnt][uord]  */
    double*             vbfuncX;        /* v BS func : [vcpnt][vord]  */
    double*             ubfuncD;        /* u BS func : [ucpnt][uord]  */
    double*             vbfuncD;        /* v BS func : [vcpnt][vord]  */
    PGT_SFDBRPT*        pt;             /* ordinaly cod :[uord][vord] */
    PGT_SFDBRQT*        qt;             /* homogen  cod :[uord][vord] */

} PGT_SFDEBOOR, *PGT_SFDEBOORP;


#define     pgt_DBRUORD(P)          ( (P)->uord    )
#define     pgt_DBRVORD(P)          ( (P)->vord    )
#define     pgt_DBRUCPNT(p)         ( (p)->ucpnt   )
#define     pgt_DBRVCPNT(p)         ( (p)->vcpnt   )

#define     pgt_UBFUNCXP(P)         ( (P)->ubfuncX )
#define     pgt_VBFUNCXP(P)         ( (P)->vbfuncX )
#define     pgt_UBFUNCDP(P)         ( (P)->ubfuncD )
#define     pgt_VBFUNCDP(P)         ( (P)->vbfuncD )
#define     pgt_SFDBRPTP(P)         ( (P)->pt      )
#define     pgt_SFDBRQTP(P)         ( (P)->qt      )

#define     pgt_UBFUNCX(p,n,m)      ( (p)->ubfuncX[(pgt_DBRUORD(p))*(n)+(m)] )
#define     pgt_VBFUNCX(p,n,m)      ( (p)->vbfuncX[(pgt_DBRVORD(p))*(n)+(m)] )
#define     pgt_UBFUNCD(p,n,m)      ( (p)->ubfuncD[(pgt_DBRUORD(p))*(n)+(m)] )
#define     pgt_VBFUNCD(p,n,m)      ( (p)->vbfuncD[(pgt_DBRVORD(p))*(n)+(m)] )
#define     pgt_SFDBRPT(p,u,v,k)    ( (p)->pt[(pgt_DBRVORD(p))*(u)+(v)]. \
                                                            cod[(k)] )
#define     pgt_SFDBRQT(p,u,v,k)    ( (p)->qt[(pgt_DBRVORD(p))*(u)+(v)]. \
                                                            cod[(k)] )



/*--------------------------------------------------------------------*/
/*     New NURBS Surface                                              */
/*--------------------------------------------------------------------*/

/*----- Control Points -----------------------------------------------*/

typedef  struct _pgt_sfcpnt {
    double      cod[4];                 /* coordinates (homogeneous)  */

}  PGT_SFCPNT, *PGT_SFCPNTP;



/*----- Knots --------------------------------------------------------*/

typedef     double      PGT_SFKNOT;
typedef     double*     PGT_SFKNOTP;



/*----- Surface Geometry ---------------------------------------------*/

typedef  union _pgt_sfgeom {
    PGT_PLANE*          pln;            /* plane                      */
    PGT_CYLINDER*       cyl;            /* cylinder                   */
    PGT_CONE*           con;            /* cone                       */
    PGT_SPHERE*         sph;            /* sphere                     */
    PGT_TORUS*          tor;            /* torus                      */
    long*               all;            /* general                    */

} PGT_SFGEOM;                           /*                            */



/*----- NURBS Surface ------------------------------------------------*/

typedef  struct  _pgt_surf {

    /*----- Basic Memer -----*/
    PGT_SFTYPE          sftype;         /* type    0:general          */
    int                 dummy;          /* padding                    */
    PGT_CLSFLG          uclsflg;        /* u closed flag -1:unknown   */
    PGT_CLSFLG          vclsflg;        /* v closed flag -1:unknown   */
    PGT_POLFLG          upolflg;        /* u pole flag   -1:unknown   */
    PGT_POLFLG          vpolflg;        /* v pole flag   -1:unknown   */
    PGT_RATFLG          uratflg;        /* U rational flag -1:unknown */
    PGT_RATFLG          vratflg;        /* V rational flag -1:unknown */

    long                uord;           /* u order                    */
    long                vord;           /* v order                    */
    long                ucpnt;          /* u no. of control points    */
    long                vcpnt;          /* v no. of control points    */
    PGT_SFKNOT*         uknot;          /* u knots                    */
    PGT_SFKNOT*         vknot;          /* v knots                    */
    PGT_SFCPNT*         cpnt;           /* control points             */
    void*               pdummy;         /* padding                    */

    /*----- Work Area for Calculation -----*/
    PGT_SFDEBOOR*       sfdeboor;       /* work area for deBoorCox    */
    PGT_PLSURF*         plsurf;         /* polynomial expression      */

    /*----- Extension : Boundary Curve -----*/
    PGT_CURVP           u0bndcv;        /* boundary curve at u0       */
    PGT_CURVP           u1bndcv;        /* boundary curve at u1       */
    PGT_CURVP           v0bndcv;        /* boundary curve at v0       */
    PGT_CURVP           v1bndcv;        /* boundary curve at v1       */

    /*----- Extension : Analytic Expression -----*/
    PGT_SFGEOM          sfgeom;         /* analytic   expression      */
	void*				pdummy2;		/* padding                    */

    /*----- Extension : For Application -----*/
	long				userID;			/* user ID                    */
    long                usrflg;         /* user flag                  */
    long                lay_no;         /* layer no.                  */
    long                icolor;         /* color char[4] r.g.b.a      */

    /*----- Extension : For Cal. of Closest Position -----*/
    double              ukept;          /* kept u for iteration call  */
    double              vkept;          /* kept v for iteration call  */
    double              duds;           /* coef.  du/ds -1.0:not set  */
    double              dvds;           /* coef.  dv/ds -1.0:not set  */

    long                calarcF;        /* if ON arctic is calculated */
    long                calsemF;        /* if ON seam   is calculated */
    double              uarc_limit[2];  /* pole u start/end parameter */
    double              varc_limit[2];  /* pole v start/end parameter */
    double              usem_limit[2];  /* seam u start/end parameter */
    double              vsem_limit[2];  /* seam v start/end parameter */

    struct _pgt_surf*   refsurf0;       /* surf. #0 (reference only)  */
    struct _pgt_surf*   refsurf1;       /* surf. #1 (reference only)  */

}  PGT_SURF, *PGT_SURFP;


/*----- for General Users -----*/
#define  pgt_UORD(p)            ( (p)->uord )
#define  pgt_VORD(p)            ( (p)->vord )
#define  pgt_UCPNT(p)           ( (p)->ucpnt )
#define  pgt_VCPNT(p)           ( (p)->vcpnt )
#define  pgt_SFCPNT(p,u,v,k)    ( (p)->cpnt[(pgt_UCPNT(p))*(v)+(u)].cod[(k)] )
#define  pgt_UKNOT(p,j)         ( (p)->uknot[(j)] )
#define  pgt_VKNOT(p,j)         ( (p)->vknot[(j)] )
#define  pgt_UBGN(p)            ( (p)->uknot[pgt_UORD(p)-1] )
#define  pgt_UEND(p)            ( (p)->uknot[pgt_UCPNT(p)] )
#define  pgt_VBGN(p)            ( (p)->vknot[pgt_VORD(p)-1] )
#define  pgt_VEND(p)            ( (p)->vknot[pgt_VCPNT(p)] )

#define  pgt_SFTYPE(p)          ( (p)->sftype  )
#define  pgt_UCLSFLG(p)         ( (p)->uclsflg )
#define  pgt_VCLSFLG(p)         ( (p)->vclsflg )
#define  pgt_UPOLFLG(p)         ( (p)->upolflg )
#define  pgt_VPOLFLG(p)         ( (p)->vpolflg )
#define  pgt_URATFLG(p)         ( (p)->uratflg )
#define  pgt_VRATFLG(p)         ( (p)->vratflg )

/*----- for Library Developer -----*/
#define  pgt_SFCPNTP(p)         ( (p)->cpnt   )
#define  pgt_UKNOTP(p)          ( (p)->uknot  )
#define  pgt_VKNOTP(p)          ( (p)->vknot  )
#define  pgt_SFDEBOORP(p)       ( (p)->sfdeboor )
#define  pgt_PLSURFP(p)         ( (p)->plsurf )
#define  pgt_SFGEOM(p)          ( (p)->sfgeom )

#define  pgt_U0BNDCVP(p)        ( (p)->u0bndcv )
#define  pgt_U1BNDCVP(p)        ( (p)->u1bndcv )
#define  pgt_V0BNDCVP(p)        ( (p)->v0bndcv )
#define  pgt_V1BNDCVP(p)        ( (p)->v1bndcv )

#define  pgt_SFGMALLP(p)        ( (p)->sfgeom.all )
#define  pgt_SFGMPLNP(p)        ( (p)->sfgeom.pln )
#define  pgt_SFGMCYLP(p)        ( (p)->sfgeom.cyl )
#define  pgt_SFGMCONP(p)        ( (p)->sfgeom.con )
#define  pgt_SFGMSPHP(p)        ( (p)->sfgeom.sph )
#define  pgt_SFGMTORP(p)        ( (p)->sfgeom.tor )

#define  pgt_SFUSERID(P)        ( (P)->userID )
#define  pgt_SFUSRFLG(P)        ( (P)->usrflg )
#define  pgt_SFLAYNO(P)         ( (P)->lay_no )
#define  pgt_SFICOLOR(P)        ( (P)->icolor )

#define  pgt_UKEPT(p)           ( (p)->ukept )
#define  pgt_VKEPT(p)           ( (p)->vkept )
#define  pgt_DUDS(p)            ( (p)->duds )
#define  pgt_DVDS(p)            ( (p)->dvds )

#define  pgt_CALARCF(p)         ( (p)->calarcF )
#define  pgt_CALSEMF(p)         ( (p)->calsemF )
#define  pgt_UARCLIMIT(p,k)     ( (p)->uarc_limit[k] )
#define  pgt_VARCLIMIT(p,k)     ( (p)->varc_limit[k] )
#define  pgt_USEMLIMIT(p,k)     ( (p)->usem_limit[k] )
#define  pgt_VSEMLIMIT(p,k)     ( (p)->vsem_limit[k] )

#define  pgt_REFSURF0(p)        ( (p)->refsurf0 )
#define  pgt_REFSURF1(p)        ( (p)->refsurf1 )




/*--------------------------------------------------------------------*/
/*     Trimmed Surface                                                */
/*--------------------------------------------------------------------*/


/**********************************************************************/
/*  Note !                                                            */
/*                                                                    */
/*  Edge Direction                                                    */
/*  Edge direction is same as the Loop.  Underlying UV Curve has same */
/*  direction as the Edge.                                            */
/*                                                                    */
/*  Front and Back                                                    */
/*  Direction of trimmed surface is Pu x Pv of base surface.          */
/*                                                                    */
/*  Domain                                                            */
/*  When a man walks on base surface along loop domain is on left     */
/*  side of the man. First loop must be outer loop of the domain.     */
/*                                                                    */
/*  Edge on degenerate xyz curve                                      */
/*  In case that underlying xyz curve degenerates  degen flag is set  */
/*  to ON.  And xyz point may be set instead of the xyz curve.        */
/*                                                                    */
/*  Underlying Curve/Polyline                                         */
/*  Underlying curves and polylines belong to parent trimmed surface. */
/*  Utility functions for trimmed surface can free these geometry.    */
/*                                                                    */
/**********************************************************************/


/*----- Trimming Edge ------------------------------------------------*/

typedef     void*   PGT_ENTITYP;        /* for any other entities     */



typedef  struct _pgt_trimed {

    /*----- Basic Member -----*/
    long            trimedID;           /* trim edge ID (coedgeID)    */
    long            brepedID;           /* sub  edge ID (brep shell)  */
    PGT_CURVP       uvcurv;             /* 2D curve (z=0)             */
    PGT_POLYLINEP   uvpoly;             /* 2D polyline ( z = 0 )      */

    /*----- Extension -----*/
    long            userID;             /* user ID   (for application)*/
    long            usrflg;             /* user flag (for application)*/
    long            usrflgA;            /* user flag                  */
    long            usrflgB;            /* user flag                  */

    long            lay_no;             /* layer no.                  */
    long            icolor;             /* color char[4] r.g.b.a      */

    PGT_ENTITYP     userCE;             /* user coedge   entity       */
    PGT_ENTITYP     userED;             /* user edge     entity       */
    PGT_ENTITYP     userUV;             /* user uv  curv entity       */
    PGT_ENTITYP     userCV;             /* user xyz curv entity       */
    PGT_ENTITYP     userVT0;            /* user vertex entity         */
    PGT_ENTITYP     userVT1;            /* user vertxe entity         */

    PGT_PNT         vt_pos0;            /* user start vertex position */
    PGT_PNT         vt_pos1;            /* user end   vertex position */

    /*----- XYZ Curve -----*/
    long            revflg;             /* reversed flag              */
                                        /* -1:unknown 0:fwd 1:backward*/
    long            dgnflg;             /* degenerate flag for xyzcurv*/
                                        /* -1:?? 0:none 1:degenerate  */
    PGT_CURVP       xyzcurv;            /* 3D curve                   */
    PGT_POLYLINEP   xyzpoly;            /* 3D polyline                */
    PGT_PNT         xyzpnt;             /* degenerate position        */

    /*----- Boundary condition -----*/
    long            bndflg;             /* boundary position          */
                                        /*  1:at u0  2:u1  3:v0  4:v1 */
    long            bndprt;             /* boundary length            */
                                        /* -1:?? 0:none 1:part 2:full */
} PGT_TRIMED, *PGT_TRIMEDP;


#define     pgt_TREDTHISID(P)       ( (P)->trimedID )
#define     pgt_TREDBREPID(P)       ( (P)->brepedID )
#define     pgt_TREDUVCURV(P)       ( (P)->uvcurv  )
#define     pgt_TREDUVPOLY(P)       ( (P)->uvpoly  )

#define     pgt_TREDUSERID(P)       ( (P)->userID  )
#define     pgt_TREDUSRFLG(P)       ( (P)->usrflg  )
#define     pgt_TREDUSRFLGA(P)      ( (P)->usrflgA )
#define     pgt_TREDUSRFLGB(P)      ( (P)->usrflgB )

#define     pgt_TREDLAYNO(P)        ( (P)->lay_no  )
#define     pgt_TREDICOLOR(P)       ( (P)->icolor  )

#define     pgt_TREDUSERCE(P)       ( (P)->userCE  )
#define     pgt_TREDUSERED(P)       ( (P)->userED  )
#define     pgt_TREDUSERUV(P)       ( (P)->userUV  )
#define     pgt_TREDUSERCV(P)       ( (P)->userCV  )
#define     pgt_TREDUSERVT0(P)      ( (P)->userVT0 )
#define     pgt_TREDUSERVT1(P)      ( (P)->userVT1 )

#define     pgt_TREDVTPOS0(P)       ( (P)->vt_pos0 )
#define     pgt_TREDVTPOS1(P)       ( (P)->vt_pos1 )

#define     pgt_TREDREVFLG(P)       ( (P)->revflg  )
#define     pgt_TRED3DCURV(P)       ( (P)->xyzcurv )
#define     pgt_TRED3DPOLY(P)       ( (P)->xyzpoly )

#define     pgt_TREDDGNFLG(P)       ( (P)->dgnflg  )
#define     pgt_TREDXYZPNT(P)       ( (P)->xyzpnt  )

#define     pgt_TREDBNDFLG(P)       ( (P)->bndflg  )
#define     pgt_TREDBNDPRT(P)       ( (P)->bndprt  )



/*----- Trimming Loop ------------------------------------------------*/

typedef  struct _pgt_trimlp {

    /*----- Basic Member -----*/
    long            trimlpID;           /* user ID                    */
    long            idummy;             /* padding                    */

    /*----- Extension -----*/
    long            userID;             /* user ID   (for application)*/
    long            usrflg;             /* user flag (for application)*/
    long            usrflgA;            /* user flag                  */
    long            usrflgB;            /* user flag                  */

    PGT_POLYLINEP   cls_uvpoly;         /* 2D closed polyline ( z=0 ) */
    PGT_POLYLINEP   cls_xyzpoly;        /* 3D closed polyline         */

    PGT_ENTITYP     userLP;             /* user loop entity           */
    void*           pdummy;             /* (reference only)           */

    /*----- Underlying Edges -----*/
    long            max_size;           /* max size of this array     */
    long            num_trimED;         /* no. of trimming edges      */
    PGT_TRIMEDP*    ary_trimED;         /* trimming edges             */
    void*           pdummy2;            /* padding                    */

} PGT_TRIMLP, *PGT_TRIMLPP;


#define     pgt_TRLPTHISID(P)       ( (P)->trimlpID )

#define     pgt_TRLPUSERID(P)       ( (P)->userID  )
#define     pgt_TRLPUSRFLG(P)       ( (P)->usrflg  )
#define     pgt_TRLPUSRFLGA(P)      ( (P)->usrflgA )
#define     pgt_TRLPUSRFLGB(P)      ( (P)->usrflgB )


#define     pgt_TRLP2DPOLY(P)       ( (P)->cls_uvpoly )
#define     pgt_TRLP3DPOLY(P)       ( (P)->cls_xyzpoly )

#define     pgt_TRLPUSERLP(P)       ( (P)->userLP )

#define     pgt_TRLPMAXSIZE(P)      ( (P)->max_size )
#define     pgt_TRLPNEDGE(P)        ( (P)->num_trimED )
#define     pgt_TRLPEDARY(P)        ( (P)->ary_trimED )
#define     pgt_TRLPEDGE(P,N)       ( (P)->ary_trimED[(N)] )



/*----- Trimmed Surface ----------------------------------------------*/

typedef  struct  _pgt_trimsf {

    /*----- Basic Member -----*/
    long            trimsfID;           /* user ID                    */
    long            idummy;             /* padding                    */
    PGT_SURFP       baseSF;             /* underlying surface         */
    void*           pdummy;             /* padding                    */

    /*----- Extension -----*/
    long            userID;             /* user ID   (for application)*/
    long            usrflg;             /* user flag (for application)*/
    long            usrflgA;            /* user flag                  */
    long            usrflgB;            /* user flag                  */

    long            dirflg;             /* direction flag  -1:unknown */
    long            idummy2;            /* 0:forward  1:reversed      */
    long            untrimF;            /* if ON surf is untrimmed    */
    long            fboundF;            /* if ON surf is full bounded */

    long            lay_no;             /* layer no.                  */
    long            icolor;             /* color uchar[4] r.g.b.a     */

    PGT_ENTITYP     userFC;             /* user face entity           */
    PGT_ENTITYP     userSF;             /* user surf entity           */

    /*----- Underlying Loops -----*/
    long            max_size;           /* max size of this array     */
    long            num_trimLP;         /* no. of trimming loops      */
    PGT_TRIMLPP*    ary_trimLP;         /* trimming loops             */
    void*           pdummy2;            /* padding                    */

} PGT_TRIMSF, *PGT_TRIMSFP;


#define     pgt_TRSFTHISID(P)       ( (P)->trimsfID )
#define     pgt_TRSFBASESF(P)       ( (P)->baseSF   )

#define     pgt_TRSFUSERID(P)       ( (P)->userID   )
#define     pgt_TRSFUSRFLG(P)       ( (P)->usrflg   )
#define     pgt_TRSFUSRFLGA(P)      ( (P)->usrflgA  )
#define     pgt_TRSFUSRFLGB(P)      ( (P)->usrflgB  )

#define     pgt_TRSFDIRFLG(P)       ( (P)->dirflg   )
#define     pgt_TRSFUNTRIMF(P)		( (P)->untrimF  )
#define     pgt_TRSFFBOUNDF(P)		( (P)->fboundF  )

#define     pgt_TRSFLAYNO(P)        ( (P)->lay_no   )
#define     pgt_TRSFICOLOR(P)       ( (P)->icolor   )

#define     pgt_TRSFUSERFC(P)       ( (P)->userFC   )
#define     pgt_TRSFUSERSF(P)       ( (P)->userSF   )

#define     pgt_TRSFMAXSIZE(P)      ( (P)->max_size )
#define     pgt_TRSFNLOOP(P)        ( (P)->num_trimLP )
#define     pgt_TRSFLPARY(P)        ( (P)->ary_trimLP )
#define     pgt_TRSFLOOP(P,N)       ( (P)->ary_trimLP[(N)] )



/*--------------------------------------------------------------------*/
/*     Flex Array of NURBS Surfaces                                   */
/*--------------------------------------------------------------------*/

/*----- Element Surface ----------------------------------------------*/

typedef  struct _pgt_elmsurf {
    PGT_SURFP       surf;               /* surface (don't free)       */
    void*           pdummy;             /* padding                    */
    long            surfID;             /* surface ID                 */
    long            userF;              /* user flag                  */

} PGT_ELMSURF, *PGT_ELMSURFP;



/*----- Flex Array of Surfaces ----------------------------------------*/

typedef  struct _pgt_flexsurfs {
    long            max_size;           /* max_size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_elmsurf;        /* no. of valid surfaces      */
    long            idummy;             /* padding                    */
    PGT_ELMSURF*    ary_elmsurf;        /* surfaces                   */
    void*           pdummy;             /* padding                    */

} PGT_FLEXSURFS, *PGT_FLEXSURFSP;



/*--------------------------------------------------------------------*/
/*     Flex Array of Trimmed Surfaces                                 */
/*--------------------------------------------------------------------*/

/*----- Element Trimmed Surface --------------------------------------*/

typedef  struct _pgt_elmtsrf {
    PGT_TRIMSFP     trimSF;             /* trimmed surf (don't free)  */
    void*           pdummy;             /* padding                    */
    long            trimsfID;           /* trimmed surface ID         */
    long            userF;              /* user flag                  */

} PGT_ELMTSRF, *PGT_ELMTSRFP;



/*----- Flex Array of Surfaces ----------------------------------------*/

typedef  struct _pgt_flextsrfs {
    long            max_size;           /* max_size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_elmtsrf;        /* no. of valid surfaces      */
    long            idummy;             /* padding                    */
    PGT_ELMTSRF*    ary_elmtsrf;        /* trimmed surfaces           */
    void*           pdummy;             /* padding                    */

} PGT_FLEXTSRFS, *PGT_FLEXTSRFSP;




/*--------------------------------------------------------------------*/
/*     End of File                                                    */
/*--------------------------------------------------------------------*/



#endif
