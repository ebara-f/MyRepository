/***********************************************************************

    関数名 : [SF HD04]  pgt_sf_struct.h

    機  能 : ＳＦライブラリ用ヘッダファイル
             構造体の定義

    PGT SF Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.06.07

***********************************************************************/



#ifndef PGT_SF_STRUCT_H
#define PGT_SF_STRUCT_H



#include    "pgt_base.h"



/*--------------------------------------------------------------------*/
/*     Conversion Table                                               */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_cnvtab {
    double          ss_geom;            /* parameter ( chord length ) */
    double          tt_parm;            /* parameter ( general )      */
    double          length;             /* segment length             */

} PGT_CNVTAB, *PGT_CNVTABP;




/*--------------------------------------------------------------------*/
/*     Curve Mesh                                                     */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_cvpt {
    double          tpar;               /* parameter value            */
    double          spar;               /* normalized arc length parm */
    double          orgpnt[3];          /* meshing point              */
    double          offpnt[3];          /* meshing point    (offset)  */
    double          uv_pos[2];          /* meshing uv_point (offset)  */
    long            divflg;             /* division flag              */
    long            newflg;             /* new element flag           */

} PGT_CVPT, *PGT_CVPTP;


typedef  struct _pgt_cvmesh {
    long            npnt;               /* no. of meshing points      */
    long            idummy;             /* padding                    */
    PGT_CVPT*       cvpt;               /* points                     */
    void*           pdummy;             /* padding                    */

} PGT_CVMESH, *PGT_CVMESHP;


#define     pgt_CVMNPNT(p)          ( (p)->npnt )
#define     pgt_CVMCVPT(p)          ( (p)->cvpt )

#define     pgt_CVMTPAR(p,i)        ( (p)->cvpt[(i)].tpar )
#define     pgt_CVMORGPNT(p,i,k)    ( (p)->cvpt[(i)].orgpnt[(k)] )
#define     pgt_CVMOFFPNT(p,i,k)    ( (p)->cvpt[(i)].offpnt[(k)] )
#define     pgt_CVMUVPOS(p,i,k)     ( (p)->cvpt[(i)].uv_pos[(k)] )
#define     pgt_CVMDIVFLG(p,i)      ( (p)->cvpt[(i)].divflg )
#define     pgt_CVMNEWFLG(p,i)      ( (p)->cvpt[(i)].newflg )




/*--------------------------------------------------------------------*/
/*     Surface Mesh                                                   */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_sfpt {

    /*----- on Original Surf. ----------------------------------------*/
    double          upar;               /* u parameter                */
    double          vpar;               /* v parameter                */
    double          orgpnt[3];          /* meshing point              */
    double          orgvec[3];          /* normal dir on mesh pnt     */

    /*----- on Offset Surf. ------------------------------------------*/
    double          offupar;            /* u parameter                */
    double          offvpar;            /* v parameter                */
    double          offpnt[3];          /* meshing point (offset)     */

    /*----- Extension ------------------------------------------------*/
    double          dist;               /* distance                   */
    long            divflg;             /* division flag              */
    long            newflg;             /* new element flag           */
    long            invalidF;           /* invalid flag               */
    long            type;               /* point type                 */

} PGT_SFPT, *PGT_SFPTP;


typedef  struct _pgt_sfmesh {
    long            upnt;               /* no. of u meshing points    */
    long            vpnt;               /* no. of v meshing points    */
    long            upol;               /* pole flag                  */
    long            vpol;               /* 0:none 1:at u0 2:u1 3:both */
    PGT_SFPT*       sfpt;               /* points                     */
    void*           pdummy;             /* padding                    */

} PGT_SFMESH, *PGT_SFMESHP;


#define     pgt_SFMUPNT(p)      ( (p)->upnt )
#define     pgt_SFMVPNT(p)      ( (p)->vpnt )
#define     pgt_SFMUPOL(p)      ( (p)->upol )
#define     pgt_SFMVPOL(p)      ( (p)->vpol )
#define     pgt_SFMSFPT(p)      ( (p)->sfpt )

#define     pgt_SFMUPAR(p,iu,iv) \
                ( (p)->sfpt[((p)->upnt)*(iv)+(iu)].upar )
#define     pgt_SFMVPAR(p,iu,iv) \
                ( (p)->sfpt[((p)->upnt)*(iv)+(iu)].vpar )
#define     pgt_SFMORGPNT(p,iu,iv,k) \
                ( (p)->sfpt[((p)->upnt)*(iv)+(iu)].orgpnt[(k)] )
#define     pgt_SFMORGVEC(p,iu,iv,k) \
                ( (p)->sfpt[((p)->upnt)*(iv)+(iu)].orgvec[(k)] )

#define     pgt_SFMOFFUPAR(p,iu,iv)  \
                ( (p)->sfpt[((p)->upnt)*(iv)+(iu)].offupar )
#define     pgt_SFMOFFVPAR(p,iu,iv)  \
                ( (p)->sfpt[((p)->upnt)*(iv)+(iu)].offvpar )
#define     pgt_SFMOFFPNT(p,iu,iv,k) \
                ( (p)->sfpt[((p)->upnt)*(iv)+(iu)].offpnt[(k)] )

#define     pgt_SFMDIST(p,iu,iv)   \
                ( (p)->sfpt[((p)->upnt)*(iv)+(iu)].dist )
#define     pgt_SFMDIVFLG(p,iu,iv)   \
                ( (p)->sfpt[((p)->upnt)*(iv)+(iu)].divflg )
#define     pgt_SFMNEWFLG(p,iu,iv)   \
                ( (p)->sfpt[((p)->upnt)*(iv)+(iu)].newflg )
#define     pgt_SFMINVALIDF(p,iu,iv)   \
                ( (p)->sfpt[((p)->upnt)*(iv)+(iu)].invalidF )
#define     pgt_SFMTYPE(p,iu,iv)   \
                ( (p)->sfpt[((p)->upnt)*(iv)+(iu)].type )




/*--------------------------------------------------------------------*/
/*     Ladder Structure                                               */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_subsec {
    double          ratio;              /* blending ratio 0-1         */
    double          swp_pos0[3];        /* position on guide curve 0  */
    double          swp_pos1[3];        /* position on guide curve 1  */
    PGT_CODSYS      locsys;             /* local coordinate system    */
    PGT_CURVP       wld_seccrv;         /* section curve in world sys.*/
    void*           pdummy;             /* padding                    */
    
} PGT_SUBSEC, *PGT_SUBSECP;


typedef  struct _pgt_step {

    /*----- Section Curve --------------------------------------------*/
    PGT_CURVP       org_seccrv;         /* original section curve     */
    PGT_CURVP       apx_seccrv;         /* approx.  section curve     */
    PGT_CURVP       loc_seccrv;         /* local    section curve     */
    void*           pdummy;             /* padding                    */
    double          swp_pos0[3];        /* position on guide curve 0  */
    double          swp_pos1[3];        /* position on guide curve 1  */
    PGT_CODSYS      locsys;             /* local coordinate system    */

    /*----- Guid Curve -----------------------------------------------*/
    double          swp_tbgn0;          /* start parm. on guide crv 0 */
    double          swp_tend0;          /* end   parm. on guide crv 0 */
    double          swp_tbgn1;          /* start parm. on guide crv 1 */
    double          swp_tend1;          /* end   parm. on guide crv 1 */
    PGT_CURVP       apx_swpcrv0;        /* approx. guide curve 0      */
    PGT_CURVP       apx_swpcrv1;        /* approx. guide curve 1      */

    /*----- Middle Section Curves ------------------------------------*/
    long            num_subsec;         /* no. of sub section curves  */
    long            idummy;             /* padding                    */
    PGT_SUBSEC*     ary_subsec;         /* sub section curves         */
    void*           pdummy2;            /* padding                    */

} PGT_STEP, *PGT_STEPP;


typedef  struct _pgt_ladder {
    PGT_CURVP       org_swpcrv0;        /* guide curve 0              */
    PGT_CURVP       org_swpcrv1;        /* guide curve 1              */
    long            num_step;           /* no. of steps               */
    long            idummy;             /* padding                    */
    PGT_STEP*       ary_step;           /* steps                      */
    void*           pdummy;             /* padding                    */

} PGT_LADDER, *PGT_LADDERP;




/*--------------------------------------------------------------------*/
/*     Boundary Frame                                                 */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_frame {

    /*----- General Info. --------------------------------------------*/
    long            type;               /* 0:general                  */
    long            idummy;             /* 1:one guide 2:two guides   */
    double          apex[3];            /* apex if type = 1,2         */

    /*----- Sweep Curve ----------------------------------------------*/
    PGT_CURVP       swp_curv0;          /* sweep curve  0             */
    PGT_CURVP       swp_curv1;          /* sweep curve  1             */

    /*----- Section Curve --------------------------------------------*/
    PGT_CURVP       sec_curvL;          /* section curve L            */
    PGT_CURVP       sec_curvR;          /* section curve R            */
    double          swp_posL0[3];       /* start pos. of sec. L       */
    double          swp_posL1[3];       /* end   pos. of sec. L       */
    double          swp_posR0[3];       /* start pos. of sec. R       */
    double          swp_posR1[3];       /* end   pos. of sec. R       */
    PGT_CODSYS      locsysL;            /* local coord. system L      */
    PGT_CODSYS      locsysR;            /* local coord. system R      */

    /*----- Middle Section Curves ------------------------------------*/
    long            num_subsec;         /* no. of sub sections        */
    long            idummy2;            /* padding                    */
    PGT_SUBSEC*     ary_subsec;         /* ary of sub sections        */
    void*           pdummy;             /* padding                    */

} PGT_FRAME, *PGT_FRAMEP;




/*--------------------------------------------------------------------*/
/*     Radial Frame ( Surfs in N Sided Boundary )                     */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_nsideelm {
    PGT_CURVP       bond_curv;          /* original boundary curve    */
    PGT_POLYLINEP   bond_poly;          /* points on boundary         */

    double          bond_leng;          /* length of boundary         */

    PGT_PNT         pos0;               /* start  pos.                */
    PGT_PNT         pos1;               /* end    pos.                */
    PGT_PNT         posM;               /* middle pos.                */
    PGT_PNT         posC;               /* interpolated center pos.   */

    PGT_VEC         dir0;               /* start  dir. (unit)         */
    PGT_VEC         dir1;               /* end    dir. (unit)         */

    PGT_VEC         cros_dir0;          /* start  cross dir. (unit)   */
    PGT_VEC         cros_dir1;          /* end    cross dir. (unit)   */
    PGT_VEC         cros_dirM;          /* middle cross dir. (unit)   */
    PGT_VEC         cros_dirC;          /* center cross dir. (unit)   */

    PGT_CURVP       splt_curv0;         /* front  curve               */
    PGT_CURVP       splt_curv1;         /* rear   curve               */
    PGT_CURVP       radi_curv;          /* radial curve               */
    void*           pdummy;             /* padding                    */

} PGT_NSIDEELM, *PGT_NSIDEELMP;


typedef  struct _pgt_nsidefrm {
    long            nside;              /* no. of boundaries          */
    long            idummy;             /* padding                    */
    PGT_PLANE       base_plane;         /* base plane                 */
    PGT_PNT         cent_pos;           /* center pos.                */
    PGT_NSIDEELM*   elm;                /* side elements              */
    void*           pdummy;             /* padding                    */

} PGT_NSIDEFRM, *PGT_NSIDEFRMP;




/*--------------------------------------------------------------------*/
/*     Curve Chain                                                    */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_cvelem {
    PGT_CURVP       curv;               /* curve                      */
    void*           pdummy;             /* padding                    */
    long            revflg;             /* if ON crv will be reversed */
    long            idummy;             /* padding                    */
    PGT_PNT         term_posS;          /* start term. of curve       */
    PGT_PNT         term_posE;          /* end   term. of curve       */

} PGT_CVELEM, *PGT_CVELEMP;


typedef  struct _pgt_cvchain {
    long            max_size;           /* max size of elements      */
    long            num_elem;           /* no. of elements           */
    long            clsflg;             /* if ON chain is closed     */
    long            idummy;             /* padding                   */
    PGT_CVELEM*     ary_elem;           /* array of element curves   */
    void*           pdummy;             /* padding                   */

} PGT_CVCHAIN, *PGT_CVCHAINP;




/*----- End of File --------------------------------------------------*/



#endif
