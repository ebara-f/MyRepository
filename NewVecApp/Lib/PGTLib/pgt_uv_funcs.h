/***********************************************************************

    関数名 : [UV HD03]  pgt_uv.h

    機  能 : ＵＶライブラリ用ヘッダファイル

    PGT UV Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_UV_FUNCS_H
#define PGT_UV_FUNCS_H



#include "pgt_base.h"



#ifdef __cplusplus
extern "C"{
#endif



/*----- A : Create UV curve ------------------------------------------*/

extern  long  pgtUV_MkUVCurv(
                double[2], double,
                PGT_SURFP, PGT_CURVP, long,
                PGT_CURVP*, double*, long*, long*
        );

extern  long  pgtUV_MkUVCurvN(
                double[2], double,
                long, PGT_SURFP, PGT_CURVP, long,
                PGT_CURVP*, double*, long*, long*
        );



/*----- B : Create UV points -----------------------------------------*/

extern  long  pgtUV_MkUVPnts(
                double[2],
                PGT_SURFP, PGT_POLYLINEP,
                PGT_POLYLINEP*, PGT_POLYLINEP*, double*, long*, long*
        );

extern  long  pgtUV_MkUVPnts_COIL(
                double[2],
                PGT_SURFP, PGT_POLYLINEP,
                PGT_POLYLINEP*, PGT_POLYLINEP*, double*, long*, long*
        );

extern  long  pgtUV_MkUVPntsN(
                double[2],
                long, PGT_SURFP, PGT_POLYLINEP,
                PGT_POLYLINEP*, PGT_POLYLINEP*, double*, long*, long*
        );

extern  long  pgtUV_MkUVPntsNB(
                double[2],
                long, PGT_SURFP, long, PGT_POLYLINEP,
                PGT_POLYLINEP*, PGT_POLYLINEP*, double*, long*, long*
        );



/*----- C : UV curve -------------------------------------------------*/

extern  long  pgtUV_UVCrv0(
                double[2], double,
                PGT_SURFP, PGT_CURVP, 
                PGT_CURVP*, double*, long*, long*
        );

extern  long  pgtUV_UVCrv0VH(                   /* 2022.04.01 */
                double[2], double, double,
                PGT_SURFP, PGT_CURVP, 
                PGT_CURVP*, double*, long*, long*
        );

extern  long  pgtUV_UVCrvN(
                double[2], double,
                long, PGT_SURFP, PGT_CURVP, 
                PGT_CURVP*, double*, long*, long*
        );

extern  long  pgtUV_UVEdge(
                double[2], double,
                PGT_SURFP, PGT_CURVP, long,
                PGT_CURVP*
        );

extern  long  pgtUV_UVEdg2(
                double[2], double,
                PGT_SURFP, PGT_CURVP, long,
                PGT_CURVP*, double*
        );

extern  long  pgtUV_InvCTP(
                PGT_SURFP, PGT_CURVP,
                PGT_CURVP*
        );



/*----- D : Passing Points -------------------------------------------*/

extern  long  pgtUV_MkPass(
                double[2],
                PGT_SURFP, PGT_CURVP,
                PGT_UVPASSPNTP*, double*
        );

extern  long  pgtUV_MkPassN(
                double[2],
                long, PGT_SURFP, PGT_CURVP,
                PGT_UVPASSPNTP*, double*
        );

extern  long  pgtUV_MkPassVH(
                double[2],
                PGT_SURFP, PGT_CURVP,
                PGT_UVPASSPNTP*, double*, double*
        );

extern  long  pgtUV_CpPass(
                double[2],
                PGT_UVPASSPNTP,
                PGT_UVPASSPNTP*, double* 
        );

extern  long  pgtUV_CpPassVH(
                double[2],
                PGT_UVPASSPNTP,
                PGT_UVPASSPNTP*, double*, double* 
        );

extern  long  pgtUV_PtDetm(
                double[2],
                PGT_UVPASSPNTP,
                PGT_UVPASSPNTP*, long*, long*
        );

extern  long  pgtUV_Arctic(
                double[2],
                PGT_SURFP, double,
                long*, long*, double[2], double[2] 
        );

extern  long  pgtUV_ByPole(
                double, double, long, long, double[2], double[2],
                long*
        );

extern  long  pgtUV_CkSeam(
                double[2],
                PGT_SURFP, double,
                long*, long*, double[2], double[2]
        );

extern  long  pgtUV_BySeam(
                double, double, long, long, double[2], double[2],
                long*
        );

extern  long  pgtUV_AdjSem(
                PGT_UVPASSPNTP, long*
        );

extern  long  pgtUV_CnvTUV(
                double[2],
                long, double, PGT_CURVP, PGT_SURFP,
                double*, double*, double*
        );

extern  long  pgtUV_TUVTry(
                double[2],
                double, PGT_CURVP, PGT_SURFP, double, double, long,
                double*, double*
        );

extern  long  pgtUV_DeltUV(
                double[2],
                PGT_SURFP, double, double, PGT_PNT,
                double*, double*
        );

extern  long  pgtUV_DbgPas(
                PGT_UVPASSPNTP
        );

extern  long  pgtUV_AllocPassPnt(           /* 2022.04.01 */
                long, 
                PGT_UVPASSPNTP*
        );

extern  long  pgtUV_FreePassPnt(            /* 2022.04.01 */
                PGT_UVPASSPNTP*
        );


/*----- E : Cal. Control Points --------------------------------------*/

extern  long  pgtUV_MkNubs(
                PGT_UVPASSPNTP,
                PGT_CURVP*
        );

extern  long  pgtUV_MkNbs2(
                double[2],
                PGT_UVPASSPNTP, 
                PGT_CURVP*
        );

extern  long  pgtUV_MkCvSS(
                PGT_UVPASSPNTP, long, long,
                PGT_CURVP*
        );

extern  long  pgtUV_MkCvEE(
                PGT_UVPASSPNTP, long, long,
                PGT_CURVP*
        );

extern  long  pgtUV_MkCvOO(
                PGT_UVPASSPNTP, long, long,
                PGT_CURVP*
        );

extern  long  pgtUV_MkCvMM(
                PGT_UVPASSPNTP, long, long,
                PGT_CURVP*
        );

extern  long  pgtUV_MkCvSE(
                PGT_UVPASSPNTP, long, long,
                PGT_CURVP*
        );



/*----- F : Check UV curve -------------------------------------------*/

extern  long  pgtUV_ChkApx(
                double[2],
                PGT_CURVP, PGT_SURFP, PGT_UVPASSPNTP, PGT_CURVP, double,
                long*
        );

extern  long  pgtUV_ChkApxVH(               /* 2022.04.01 */
                double[2],
                PGT_CURVP, PGT_SURFP, PGT_UVPASSPNTP, PGT_CURVP, 
                double, double,
                long*
        );


/*----- G : Operate Original Curve -----------------------------------*/

extern  long  pgtUV_PrtCv1(
                double[2],
                PGT_CURVP, double, double,
                PGT_CURVP*
        );

extern  long  pgtUV_Concat(
                double[2],
                long, PGT_CURVP[],
                PGT_CURVP*
        );

extern  long  pgtUV_CvJoin(
                double[2],
                PGT_CURVP, PGT_CURVP,
                PGT_CURVP*
        );

extern  long  pgtUV_BkKnot(
                double[2],
                PGT_CURVP, long*, double**
        );

extern  long  pgtUV_LLCros(
                double[2],
                PGT_LINE, PGT_LINE, 
                PGT_PNT*, PGT_PNT*,double*, double*,double*
        );

extern  long  pgtUV_UVAlin(
                long, PGT_CURVP[], long[], PGT_SURFP
        );



/*----- H : Create UV curve and UV points ----------------------------*/

extern  long  pgtUV_MkUVCurvBD(
                double[2], double,
                PGT_SURFP, PGT_CURVP, long,
                long*, PGT_CURVP**,
                double*, long*, long*
        );

extern  long  pgtUV_AdjBezParam(
                double[2], 
                PGT_SURFP,
                PGT_SURFP*
        );

extern  long  pgtUV_BrkAtPatchBound(
                double[2], double,
                PGT_CURVP, long, long, double[], double[],
                long*, PGT_CURVP**
        );

extern  long  pgtUV_ChangeUVParam(
                PGT_CURVP, 
                long, long, double[], double[],
                double[], double[],
                PGT_CURVP*
        );

extern  long  pgtUV_IsSurfBezType(
                double[2], 
                PGT_SURFP,
                long*
        );

extern  long  pgtUV_MkUVCurvBDN(
                double[2], double,
                long,
                PGT_SURFP, PGT_CURVP, long,
                long*, PGT_CURVP**,
                double*, long*, long*
        );

extern  long  pgtUV_MkUVCurvN2(
                double[2], double,
                long, PGT_SURFP, PGT_CURVP, long,
                PGT_CURVP*, double*, long*, long*
        );

extern  long  pgtUV_MkUVCurvFragments(
                double[2], double,
                PGT_SURFP, PGT_CURVP, long,
                long*, PGT_CURVP**, long*, long*, long**, double*
        );

extern  long  pgtUV_BrkAtPatchBound2(
                double[2], double,
                PGT_CURVP, long, long, double[], double[],
                long*, PGT_CURVP**, long**
        );



/*----- J : Closest Point on UV Curve --------------------------------*/

extern  long  pgtUV_ClsPntToUVCurv(
                double[2],
                PGT_CURVP, PGT_SURFP, PGT_PNT,
                PGT_PNT*, PGT_PNT*, double*, double*, long*
        );

extern  long  pgtUV_ClsPntToUVCurvR(
                double[2],
                PGT_CURVP, PGT_SURFP, PGT_PNT, double,
                PGT_PNT*, PGT_PNT*, double*, double*, long*
        );

extern  long  pgtUV_DotSign(
                double[2],
                PGT_CURVP, PGT_SURFP, PGT_PNT, double,
                PGT_PNT*, PGT_PNT*, double*, long*
        );

extern  long  pgtUV_BiSearch(
                double[2],
                PGT_CURVP, PGT_SURFP, PGT_PNT, double, double, double, double,
                PGT_PNT*, PGT_PNT*, double*, double*
        );



/*----- K : Curve Length in XYZ Space --------------------------------*/

extern  long  pgtUV_CurvLength3D(
                double[2],
                PGT_CURVP, PGT_SURFP, double, double,
                double*
        );



/*----- L : Create UV Curves for a Loop ------------------------------*/

extern  long  pgtUV_MkUVCurvsForLoop(
                double[2], double,
                PGT_SURFP, long, PGT_CURVP[],
                long*, PGT_CURVP**
        );

extern  long  pgtUV_VerifyLoopChain(
                double[2], double,
                long, PGT_CURVP[],
                long*
        );

extern  long  pgtUV_VerifyBaseSurf(
                double[2],
                PGT_SURFP,
                long*, long*, long*, long*
        );

extern  long  pgtUV_DecomposeXYZCurvs(
                double[2],
                long, PGT_CURVP[], 
                PGT_UVSEGCRVSP*
        );

extern  long  pgtUV_SplitSegCurvsAtPole(
                double[2], double,
                PGT_SURFP, PGT_UVSEGCRVSP,
                PGT_UVSEGCRVSP*
        );

extern  long  pgtUV_CalUVCurvs(
                double[2], double,
                PGT_SURFP, PGT_UVSEGCRVSP
        );

extern  long  pgtUV_CalUVCurvsVH(               /* 2022.04.01 */
                double[2], double, double,
                PGT_SURFP, PGT_UVSEGCRVSP
        );

extern  long  pgtUV_AdjUVCurvsOnSeam(
                double[2],                      /* 2022.04.01 */
                PGT_UVSEGCRVSP
        );

extern  long  pgtUV_ComposeUVCurvs(
                double[2],
                PGT_UVSEGCRVSP,
                long*, PGT_CURVP**
        );

extern  long  pgtUV_AllocSegCurvs(
                long,
                PGT_UVSEGCRVSP*
        );

extern  long  pgtUV_FreeSegCurvs(
                PGT_UVSEGCRVSP*
        );

extern  long  pgtUV_RemDuplicateCPnts(
                double[2],
                PGT_CURVP,
                PGT_CURVP*
        );



/*----- M : Create UV Polylines for a Loop ---------------------------*/

extern  long  pgtUV_MkUVPolysForLoop(
                double[2], double,
                PGT_SURFP, long, PGT_POLYLINEP[],
                long*, PGT_POLYLINEP**
        );

extern  long  pgtUV_MkUVPolysForLoop_COIL(
                double[2], double,
                PGT_SURFP, long, PGT_POLYLINEP[],
                long*, PGT_POLYLINEP**
        );

extern  long  pgtUV_VerifyLoopPoly(
                double[2], double,
                long, PGT_POLYLINEP[],
                long*
        );

extern  long  pgtUV_CalUVPolys(
                double[2],
                PGT_SURFP, long, PGT_POLYLINEP[],
                PGT_UVPOLYLPP*
        );

extern  long  pgtUV_CalUVPolys_COIL(
                double[2],
                PGT_SURFP, long, PGT_POLYLINEP[],
                PGT_UVPOLYLPP*
        );

extern  long  pgtUV_AdjUVPolysOnSeam(
                double[2],                  /* 2022.04.01 */
                PGT_UVPOLYLPP
        );

extern  long  pgtUV_AllocPolyLp(
                long,
                PGT_UVPOLYLPP*
        );

extern  long  pgtUV_FreePolyLp(
                PGT_UVPOLYLPP*
        );



/*----- N : Approx UV Curve by Polyline ------------------------------*/

extern  long  pgtUV_ApproxUVCurvByPoly(
                double[2], double, double,
                PGT_CURVP, PGT_SURFP,
                PGT_POLYLINEP*
                );



/*----- O : Approx UV Curve by Polyline ------------------------------*/

extern  long  pgtUV_MkXYZCurvFromUV(
                double[2], double,
                PGT_SURFP, PGT_CURVP,
                                long*, PGT_CURVP*, PGT_PNT*
                );




/*----- End of File --------------------------------------------------*/



#ifdef __cplusplus
}
#endif



#endif
