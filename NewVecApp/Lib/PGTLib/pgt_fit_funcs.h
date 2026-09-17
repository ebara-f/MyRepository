/***********************************************************************

    関数名 : [FIT HD03]  pgt_fit_funcs.h

    機  能 : ＦＩＴライブラリ用ヘッダファイル

    PGT FIT Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Yojiro Mandachi    / GeomLab        2025.06.13

***********************************************************************/



#ifndef PGT_FIT_FUNCS_H
#define PGT_FIT_FUNCS_H



#include    "pgt_fit_struct.h"



#ifdef __cplusplus
extern "C"{
#endif



/*----- A : Polyline on Curve ----------------------------------------*/

extern  long  pgtFT_PolylineOnCurv(
                double[2],
                PGT_CURVP, long,
                PGT_POLYLINEP*
        );

extern  long  pgtFT_PolylineOnCurvAdj(
                double[2],
                PGT_CURVP, long,
                PGT_POLYLINEP*
        );

extern  long  pgtFT_ApproxCurvByPoly(
                double[2], double,
                PGT_CURVP,
                PGT_POLYLINEP*
        );

extern  long  pgtFT_ApproxCurvByPoly2(
                double[2],
                double, PGT_CURVP,
                PGT_POLYLINEP*
        );

extern  long  pgtFT_ApproxCurvByPolyMIN(
                double[2], double, double, double,
                PGT_CURVP,
                PGT_POLYLINEP*
        );

extern  long  pgtFT_PolylineOnCurvBySeg(
                double[2],
                PGT_CURVP, long,
                PGT_POLYLINEP*
        );

extern  long  pgtFT_PolylineOnCurvBySegLeng(
                double[2],
                PGT_CURVP, double,
                PGT_POLYLINEP*
        );


/*----- B : Make Polyline Smooth -------------------------------------*/

extern  long  pgtFT_SmoothPolyline(
                double[2], double,
                PGT_POLYLINEP, long,
                PGT_POLYLINEP*
        );

extern  long  pgtFT_AmplitudeOnPoly(
                double[2],
                PGT_POLYLINEP,
                double*
        );

extern  long  pgtFT_DividePoly(
                PGT_POLYLINEP, long,
                long*, PGT_POLYLINEP**
        );

extern  long  pgtFT_DigitCurve(
                double[2],
                PGT_CURVP, long,
                PGT_FTDIGIT[]
        );

extern  long  pgtFT_CurvatureOnPnts(
                double[2],
                long, PGT_FTDIGIT[]
        );

extern  long  pgtFT_SamplingPos(
                double[2],
                long, long, PGT_FTDIGIT[],
                double[]
        );

extern  long  pgtFT_CrePolyline(
                double[2],
                PGT_CURVP, long, double[],
                PGT_POLYLINEP*
        );

extern  long  pgtFT_ConcatPolylines(
                double[2],
                long, PGT_POLYLINEP[],
                PGT_POLYLINEP*
        );

extern  long  pgtFT_RemTinySegInPoly(
                double[2],
                PGT_POLYLINEP,
                PGT_POLYLINEP*
        );

extern  long  pgtFT_RemDegenSeg(
                double[2], double,
                PGT_CURVP,
                PGT_CURVP*, long*
        );

extern  long  pgtFT_SmoothPolyEasy(
                double[2],
                PGT_POLYLINEP,
                PGT_POLYLINEP*
        );

extern  long  pgtFT_SmoothPolyWithFold(
                double[2], double,
                PGT_POLYLINEP, double, long,
                PGT_POLYLINEP*
        );

extern  long  pgtFT_SmoothPolyEasyWithFold(
                double[2],
                PGT_POLYLINEP, double,
                PGT_POLYLINEP*
        );




/*----- C : Make Surface G1 Smooth -----------------------------------*/

extern  long  pgtFT_MakeSurfG1(
                double[2],
                PGT_SURFP,
                PGT_SURFP*
        );

extern  long  pgtFT_RaiseOrderTo4(
                double[2],
                PGT_SURFP,
                PGT_SURFP*
        );

extern  long  pgtFT_FindG0Knots(
                PGT_SURFP,
                long*, long*, double**, double**
        );

extern  long  pgtFT_AdjG1CPntsAtCross(
                double[2],
                PGT_SURFP, long, long, double[], double[],
                PGT_SURFP*
        );

extern  long  pgtFT_AdjG1CPnts(
                double[2],
                PGT_SURFP, long, long, double[],
                PGT_SURFP*
        );

extern  long  pgtFT_AdjG1CPntsAtSeam(
                double[2],
                PGT_SURFP, long,
                PGT_SURFP*
        );


/*----- Clean Pole -----*/

extern  long  pgtFT_CleanSfPole(
                double[2],
                PGT_SURFP,
                PGT_SURFP*
        );

extern  long  pgtFT_CleanSfPole2(
                double[2], double,
                PGT_SURFP,
                PGT_SURFP*
        );




/*----- D : Make Surface G2 Smooth -----------------------------------*/

extern  long  pgtFT_MakeSurfG2(
                double[2],
                PGT_SURFP,
                PGT_SURFP*
        );


extern  long  pgtFT_FindNonG2Knots(
                double[2],
                PGT_SURFP,
                long*, long*, double**, double**
        );

extern  long  pgtFT_FindNonG1Knots(
                double[2],
                PGT_SURFP,
                long*, long*, double**, double**
        );

extern  long  pgtFT_FindBezKnots(
                double[2],
                PGT_SURFP,
                long*, long*, double**, double**
        );




/*----- E : Fit Curve Terminal ---------------------------------------*/

extern  long  pgtFT_FitCvTerm(
                double[2],
                PGT_CURVP, long, PGT_PNT,
                PGT_CURVP*
        );

extern  long  pgtFT_FitCvTermByShearing(
                double[2],
                PGT_CURVP, long, PGT_PNT,
                PGT_CURVP*
        );

extern  long  pgtFT_FitCvTermUV(
                double[2],
                PGT_CURVP, long, PGT_PNT,
                PGT_CURVP*
        );

extern  long  pgtFT_SetSideFlag(
                double[2],
                PGT_CURVP, PGT_PNT,
                long*
        );

extern  long  pgtFT_DisplacementVec(
                double[2],
                PGT_CURVP, long, PGT_PNT,
                PGT_VEC*, PGT_VEC*, long*
        );

extern  long  pgtFT_FindSegment(
                double[2],
                PGT_CURVP, long, long, double,
                double*, double*
        );

extern  long  pgtFT_CopyPartCv(
                double[2],
                PGT_CURVP, double, double,
                PGT_CURVP*
        );

extern  long  pgtFT_AdjTermSegment(
                double[2],
                PGT_CURVP, long, PGT_PNT,
                PGT_CURVP*
        );



/*----- F : Make Curve G1 Smooth -------------------------------------*/

extern  long  pgtFT_MakeCurvG1(
                double[2],
                PGT_CURVP,
                PGT_CURVP*
        );

extern  long  pgtFT_MakeCurvG1AtSeam(
                double[2],
                PGT_CURVP,
                PGT_CURVP*
        );



/*----- G : Relax Curve under Manifold Edge --------------------------*/

extern  long  pgtFT_RelaxCurvOnTwoSurfs(
                double[2],
                PGT_CURVP, PGT_SURFP, PGT_SURFP,
                PGT_CURVP*
        );

extern  long  pgtFT_SamplePosOnCurv(
                double[2],
                PGT_CURVP,
                long*, PGT_PNT**, double**
        );

extern  long  pgtFT_RelaxCurvPnts(
                double[2],
                long, PGT_PNT[], PGT_SURFP, PGT_SURFP,
                PGT_PNT**
        );

extern  long  pgtFT_RelaxVects(
                double[2],
                long, PGT_PNT[], PGT_PNT[],
                PGT_VEC**
        );

extern  long  pgtFT_RelaxVectsForCvCpnts(
                double[2],
                PGT_CURVP, long, double[], PGT_VEC[],
                long*, PGT_VEC**
        );



/*----- H : Relax Curve To Fit Base Surf -----------------------------*/

extern  long  pgtFT_RelaxCurvToFitSf(
                double[2], double,
                PGT_CURVP, PGT_SURFP,
                PGT_CURVP*
        );

extern  long  pgtFT_RelaxCvPnts(
                double[2], double,
                long, PGT_PNT[], PGT_SURFP,
                PGT_VEC**
        );

extern  long  pgtFT_GapBetweenCvSf(
                double[2],
                PGT_CURVP, PGT_SURFP,
                double*, PGT_PNT*, PGT_PNT*
        );



/*----- I : Relax Surface To Fit Curve -------------------------------*/

extern  long  pgtFT_RelaxSurfToFitCv(
                double[2], double,
                PGT_SURFP, PGT_CURVP,
                PGT_SURFP*
        );

extern  long  pgtFT_RelaxSurfToFitPnts(
                double[2], double,
                PGT_SURFP, long, PGT_PNT[],
                PGT_SURFP*
        );

extern  long  pgtFT_RelaxSfPnts(
                double[2], double,
                long, PGT_PNT[], PGT_SURFP,
                long*, PGT_PNT**, PGT_PNT**, double**, double**
        );

extern  long  pgtFT_RelaxVectsForSfCpnts(
                double[2],
                PGT_SURFP, long, double[], double[], PGT_VEC[],
                long*, long*, PGT_VEC**
        );



/*----- J : Make Curve and Surface G2 by Knot Removeal ---------------*/

extern  long  pgtFT_G2CurvByKnotRemoval(
                double[2],
                PGT_CURVP, long,
                PGT_CURVP*, double*
        );

extern  long  pgtFT_G2SurfByKnotRemoval(
                double[2],
                PGT_SURFP, long,
                PGT_SURFP*, double*
        );

extern  long  pgtFT_ErrorBetCurvs(
                double[2],
                PGT_CURVP, PGT_CURVP, long,
                double*, PGT_PNT*, PGT_PNT*
        );

extern  long  pgtFT_ErrorBetSurfs(
                double[2],
                PGT_SURFP, PGT_SURFP, long,
                double*, PGT_PNT*, PGT_PNT*
        );



/*----- K : Fit Surfaces to Large One --------------------------------*/

extern  long  pgtFT_FitSurfsToLargeOne(
                double[2], double,
                long, PGT_SURFP,
                long*, PGT_SURFP**,
                double*, PGT_PNT*, PGT_PNT*
        );

extern  long  pgtFT_SetApproxSurf(
                double[2], double,
                long, long, double, double,
                PGT_SURFP, double, double, double, double,
                PGT_SFNODEP,
                double*, PGT_PNT*, PGT_PNT*
        );

extern  long  pgtFT_GetApproxPartSf(
                double[2],
                PGT_SURFP, double, double, double, double,
                PGT_SURFP*
        );

extern  long  pgtFT_CheckApproxPartSf(
                double[2], double,
                PGT_SURFP, double, double, double, double,
                PGT_SURFP,
                long*,
                double*, PGT_PNT*, PGT_PNT*
        );

extern  long  pgtFT_GetAllApproxSurfs(
                PGT_SFNODEP,
                long*, PGT_SURFP**
        );

extern  long  pgtFT_AllocSfNode(
                PGT_SFNODEP*
        );

extern  long  pgtFT_FreeSfNode(
                PGT_SFNODEP*
        );

extern  long  pgtFT_AdjSfBoundToFitNext(
                double[2], double,
                long, PGT_SURFP[]
        );

extern  long  pgtFT_AdjSfBoundToFitNextUV(
                double[2], double,
                long, PGT_SURFP[]
        );



/*----- L : Fit Line / Circle Terminal -------------------------------*/

extern  long  pgtFT_FitLineTerm(
                    double[2],
                    PGT_LINE, long, PGT_PNT,
                    PGT_LINE*
        );

extern  long  pgtFT_FitCircleTerm(
                    double[2],
                    PGT_CIRCLE, long, PGT_PNT,
                    PGT_CIRCLE*
        );



/*----- M : Approx Curve / Surface -----------------------------------*/

extern  long  pgtFT_ApproxCurv(
                double[2], double,
                PGT_CURVP,
                PGT_CURVP*, double*
        );

extern  long  pgtFT_ApproxSegCurv(
                double[2], double,
                PGT_CURVP,
                PGT_CURVP*, double*
        );

extern  long  pgtFT_ApproxSegment(
                double[2],
                PGT_CURVP, long,
                PGT_CURVP*, double*
        );

extern  long  pgtFT_ApproxCurvHOMO(
                double[2], double,
                PGT_CURVP, long,
                PGT_CURVP*, double*
        );

extern  long  pgtFT_ApproxSurfHOMO(
                double[2], double,
                PGT_SURFP,
                PGT_SURFP*, double*
        );



/*----- N : Least Squares Fitting ------------------------------------*/

extern  long  pgtFT_FitCircleToPnts(
                double[2],
                long, PGT_PNT[],
                PGT_CIRCLE*
        );

extern  long  pgtFT_FitCircleToPntsUV(
                double[2],
                long, PGT_PNT[],
                PGT_PNT*, double*
        );

extern  long  pgtFT_FitEllipseToPnts(
                double[2],
                long, PGT_PNT[],
                PGT_ELLIPSE*
        );

extern  long  pgtFT_FitEllipseToPntsUV(
                double[2],
                long, PGT_PNT[],
                PGT_PNT*, double*, double*, double*
        );

extern  long  pgtFT_FitSphereToPnts(
                double[2],
                long, PGT_PNT[],
                PGT_SPHERE*
        );

extern  long  pgtFT_FitQuadSurfToPnts(
                double[2],
                long, PGT_PNT[],
                PGT_SURFP*
        );

extern  long  pgtFT_FitPolySurfToPnts(
                double[2],
                long, PGT_PNT[], long,
                PGT_SURFP*
        );




/*----- End of File --------------------------------------------------*/



#ifdef __cplusplus
}
#endif



#endif
