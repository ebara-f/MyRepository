/***********************************************************************

    関数名 : [PLUS HD03]  pgt_plus_funcs.h

    機  能 : ＰＬＵＳライブラリ用ヘッダファイル
             関数プロトタイプ宣言

    PGT PLUS Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2023.01.03

***********************************************************************/



#ifndef PGT_PLUS_FUNCS_H
#define PGT_PLUS_FUNCS_H



#include    "pgt_base.h"



#ifdef __cplusplus
extern "C"{
#endif



/*--------------------------------------------------------------------*/
/*     PLUS NC Axx : Closest Point on Curve                           */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_ClsPntToCrv(
                double[2],
                PGT_CURVP, PGT_PNT,
                PGT_PNT*, double*, double*, long*
        );

extern  long  pgtNC_ClsPntToCrvR(
                double[2],
                PGT_CURVP, PGT_PNT, double,
                PGT_PNT*, double*, double*, long*
        );

extern  long  pgtNC_BiSearch(
                double[2],
                PGT_CURVP, PGT_PNT, double, double, double, double,
                PGT_PNT*, double*, double*
        );

extern  long  pgtNC_DotSign(
                double[2],
                PGT_CURVP, PGT_PNT, double,
                PGT_PNT*, double*, long*
        );

extern  long  pgtNC_CvDegen(
                double[2],
                PGT_CURVP,
                long*
        );

extern  long  pgtNC_CvDegenSEG(
                double[2], double,
                PGT_CURVP,
                long*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Bxx : Extreme Position on Curve                        */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_CvExtremePos(
                double[2],
                PGT_CURVP, PGT_VEC,
                PGT_PNT*, double*, long*
        );

extern  long  pgtNC_CvExtremePosR(
                double[2],
                PGT_CURVP, PGT_VEC, double,
                PGT_PNT*, double*, long*
        );

extern  long  pgtNC_ApPosVecDist(
                double[2],
                PGT_CURVP, double, double[3], double[3],
                PGT_PNT*, double*, long*
        );

extern  long  pgtNC_SegExtremePos(
                double[2],
                double[3], double[3], PGT_CURVP, double, double,
                PGT_PNT*, double*, double*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Cxx : BEZIER Curve                                     */
/*--------------------------------------------------------------------*/

/*----- Bezier Curve -------------------------------------------------*/
extern  long  pgtNC_AllocBZCurv4(
                long, long,
                PGT_BZCURV4P*
        );

extern  long  pgtNC_FreeBZCurv4(
                PGT_BZCURV4P*
        );

extern  long  pgtNC_CurvFromBZ4(
                double[2],
                PGT_BZCURV4P,
                PGT_CURVP*
        );

extern  long  pgtNC_BZCurvFromNB4(
                double[2],
                PGT_CURVP,
                PGT_BZCURV4P*
        );

extern  long  pgtNC_IsCurvBezType(
                PGT_CURVP,
                long*
        );

extern  long  pgtNC_AdjBezParamCV(
                double[2],
                PGT_CURVP,
                PGT_CURVP*
        );

extern  long  pgtNC_ReparamCv(
                double[2],
                PGT_CURVP,
                PGT_CURVP*
        );


/*----- CAP Special --------------------------------------------------*/
extern  long  pgtNC_BZCurvFromCAP(
                long, double[],
                PGT_BZCURV4P*
        );

extern  long  pgtNC_BZCurvToCAP(
                PGT_BZCURV4P,
                long*, double**
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Dxx : Create Spline from Passing Points                */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_MkCurvFromPassN(
                double[2],
                long, PGT_PNT[],
                PGT_CURVP*
        );

extern  long  pgtNC_MkCurvFromPassF(
                double[2],
                long, PGT_PNT[], PGT_VEC, PGT_VEC,
                PGT_CURVP*
        );

extern  long  pgtNC_CPntFromPassN(
                double[2],
                long, PGT_PNT[], double[],
                PGT_CURVP*
        );

extern  long  pgtNC_CPntFromPassF(
                double[2],
                long, PGT_PNT[], double[], PGT_VEC, PGT_VEC,
                PGT_CURVP*
        );

extern  long  pgtNC_MkCurvFromPassT(
                double[2],
                long, long, double[],
                PGT_PNT[], double[],
                PGT_CURVP*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Exx : Expand Curve                                     */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_ExpandCv(
                double[2],
                PGT_CURVP, long, double,
                PGT_CURVP*, double*
        );

extern  long  pgtNC_ExpandCv2(
                double[2],
                PGT_CURVP, long, long, double, double,
                PGT_CURVP*
        );

extern  long  pgtNC_ExpandCvTangent(
                double[2],
                PGT_CURVP, long, double,
                PGT_CURVP*
        );

extern  long  pgtNC_ExpandCvTangent2(
                double[2],
                PGT_CURVP, long, long, double, double,
                PGT_CURVP*
        );

extern  long  pgtNC_ExpandCvByLeng(
                double[2],
                PGT_CURVP, long, double,
                PGT_CURVP*, double*, double*
        );

extern  long  pgtNC_ExpandCvWithSegment(
                double[2],
                PGT_CURVP, long, double,
                PGT_CURVP*
        );

extern  long  pgtNC_ExpandCvWithSegment2(
                double[2],
                PGT_CURVP, long, long, double, double,
                PGT_CURVP*
        );

extern  long  pgtNC_ExpandCvWithSegment3(
                double[2],
                PGT_CURVP, long, long, double, double,
                PGT_CURVP*
        );

extern  long  pgtNC_ExpandCvWithSegmentARC(
                double[2],
                PGT_CURVP, long, double,
                PGT_CURVP*
        );

extern  long  pgtNC_ExpandCvWithSegmentARC2(
                double[2],
                PGT_CURVP, long, long, double, double,
                PGT_CURVP*
        );

extern  long  pgtNC_IsCurvCircle(
                double[2], double,
                PGT_CURVP,
                long*, PGT_CIRCLE*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Fxx : Fitting Curve                                    */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_FitCurvToPnts(
                double[2], double,
                long, PGT_PNT[],
                PGT_CURVP*, double*
        );

extern  long  pgtNC_ParamOnPnts(
                double[2],
                long, PGT_PNT[],
                double**
        );

extern  long  pgtNC_MkFitCurv(
                double[2], double,
                long, PGT_PNT[], double[],
                PGT_CURVP*, double*
        );

extern  long  pgtNC_CurvatOnPnts(
                double[2],
                long, PGT_FAIRPNT[]
        );

extern  long  pgtNC_FlatKnotsOnFairPnts(
                double[2],
                long, long, PGT_FAIRPNT[],
                long*, double**
        );

extern  long  pgtNC_MkCurvByLSQ(
                double[2],
                long, PGT_PNT[], double[], long, double[], long,
                PGT_CURVP*
        );

extern  long  pgtNC_MkCurvByLSQWithFreeTerm(
                double[2],
                long, PGT_PNT[], double[], long, double[], long,
                PGT_CURVP*
        );

extern  long  pgtNC_CalCtrlPnts(
                double[2],
                long, PGT_PNT[], double[],
                long, long, double[],
                PGT_PNT[]
        );

extern  long  pgtNC_EvalFairCurv(
                double[2],
                long, PGT_PNT[], double[], PGT_CURVP,
                double*
        );

extern  long  pgtNC_CvAbsFittol(
                long, PGT_PNT[], double,
                double*
        );

extern  long  pgtNC_FitCurvToPnts2(
                double[2], double,
                long, PGT_PNT[], long, long,
                PGT_CURVP*, double*
        );

extern  long  pgtNC_FitCurvToPnts2F(
                double[2], double,
                long, PGT_PNT[], long, long,
                PGT_CURVP*, double*
        );

extern  long  pgtNC_MkFitCurv2(
                double[2], double,
                long, PGT_PNT[], double[], long, long,
                PGT_CURVP*, double*
        );

extern  long  pgtNC_MkFitCurv2F(
                double[2], double,
                long, PGT_PNT[], double[], long, long,
                PGT_CURVP*, double*
        );

extern  long  pgtNC_EvalFairCurv2(
                double[2], double,
                long, PGT_PNT[], double[], PGT_CURVP,
                long, double[],
                long*, long**, double*
        );

extern  long  pgtNC_FitCurvToPnts3(
                double[2], double,
                long, long, PGT_PNT[], long, long[],
                PGT_CURVP*, double*
        );

extern  long  pgtNC_MkFitCurv3(
                double[2], double,
                long, long, PGT_PNT[], double[], long, long[],
                PGT_CURVP*, double*
        );

extern  long  pgtNC_EvalFairCurv3(
                double[2], double,
                PGT_CURVP, long, PGT_CHKSEG[],
                long*, double*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Gxx : Gap between Two Curves                           */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_GapBetweenTwoCurvs(
                double[2],
                PGT_CURVP, PGT_CURVP, long,
                double*, PGT_PNT*, PGT_PNT*
        );

extern  long  pgtNC_AreCurvsSame(
                double[2], double,
                PGT_CURVP, PGT_CURVP,
                long*
        );

extern  long  pgtNC_IsCurvOnBaseOne(
                double[2], double,
                PGT_CURVP, PGT_CURVP,
                long*, long*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Hxx : Remove Tiny Segments                             */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_RemTinySegs(
                double[2], double,
                PGT_CURVP,
                PGT_CURVP*, long*
        );

extern  long  pgtNC_RemCvExcessKnots(
                PGT_CURVP,
                PGT_CURVP*
        );

extern  long  pgtNC_ClampCvKnots(
                double,
                PGT_CURVP,
                PGT_CURVP*
        );

extern  long  pgtNC_IsCurvClamped(
                double,
                PGT_CURVP,
                long*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Ixx : Gap between Two Polylines                        */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_ArePolylinesSame(
                double[2],
                PGT_POLYLINEP, PGT_POLYLINEP,
                long*
        );

extern  long  pgtNC_ArePolylinesSameGEOM(
                double[2], double,
                PGT_POLYLINEP, PGT_POLYLINEP,
                long*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Jxx : Create Arc from Terminals                        */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_MkArcCurv(
                double[2],
                PGT_PNT, PGT_PNT, PGT_VEC, PGT_VEC,
                PGT_CURVP*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Kxx : Create Curve Chain                               */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_MakeOneChain(
                double[2],
                long, PGT_CURVP[],
                PGT_CURVP[], long*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Lxx : Conic into NURBS                                 */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_CurvFromLine(
                double[2],
                PGT_LINE,
                PGT_CURVP*
        );

extern  long  pgtNC_CurvFromCircle(
                double[2],
                PGT_CIRCLE,
                PGT_CURVP*
        );

extern  long  pgtNC_CurvFromEllipse(
                double[2], double,
                PGT_ELLIPSE,
                PGT_CURVP*
        );

extern  long  pgtNC_CurvFromEllipse2(
                double[2],
                PGT_ELLIPSE,
                PGT_CURVP*
        );

extern  long  pgtNC_CurvFromParabola(
                double[2], double,
                PGT_PARABOLA,
                PGT_CURVP*
        );

extern  long  pgtNC_CurvFromHyperbola(
                double[2], double,
                PGT_HYPERBOLA,
                PGT_CURVP*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Mxx : T-paramerer from Length                          */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_CvTparFromLeng(
                double[2], double,
                PGT_CURVP, double,
                double*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NF Axx : Closest Point on Surface                         */
/*--------------------------------------------------------------------*/

/*----- Closest Point (By Projection Vector) -------------------------*/
extern  long  pgtNF_ClsPntToSrf(
                double[2],
                PGT_SURFP, PGT_PNT,
                PGT_PNT*, double*, double*, double*, long*
        );

extern  long  pgtNF_ClsPntToSrfR(
                double[2],
                PGT_SURFP, PGT_PNT, double, double,
                PGT_PNT*, double*, double*, double*, long*
        );

extern  long  pgtNF_PrtSf0(
                double[2],
                PGT_SURFP, double, double, double, double,
                PGT_SURFP*
        );

extern  long  pgtNF_BrkSf0(
                double[2],
                PGT_SURFP, long, double,
                PGT_SURFP*, PGT_SURFP*
        );

extern  long  pgtNF_StatPt(
                double[2],
                PGT_SURFP, PGT_PNT,
                PGT_PNT*, double*, double*, double*
        );

extern  long  pgtNF_StatPt2(
                double[2],
                PGT_SURFP, PGT_PNT,
                PGT_PNT*, double*, double*, double*
        );

extern  long  pgtNF_StatPt_COIL(
                double[2],
                PGT_SURFP, PGT_PNT,
                PGT_PNT*, double*, double*, double*
        );

extern  long  pgtNF_StatPtIso(
                double[2],
                PGT_SURFP, PGT_PNT,
                PGT_PNT*, double*, double*, double*
        );

extern  long  pgtNF_UVStep(
                double[2],
                PGT_VEC, PGT_VEC, PGT_VEC, double, double,
                double*, double*
        );

extern  long  pgtNF_EdgeCv(
                double[2],
                PGT_SURFP, long,
                PGT_CURVP*, long*
        );


/*----- Closest Point 2 (By Isoparametric Curve) ---------------------*/
extern  long  pgtNF_ClsPntToSrfIso(
                double[2],
                PGT_SURFP, PGT_PNT,
                PGT_PNT*, double*, double*, double*, long*
        );

extern  long  pgtNF_ClsPntToSrfIsoR(
                double[2],
                PGT_SURFP, PGT_PNT, double, double,
                PGT_PNT*, double*, double*, double*, long*
        );


/*----- Closest Point 3 (for BEZIER Type Suface) ---------------------*/
extern  long  pgtNF_ClsPntToSrfBD(
                double[2],
                PGT_SURFP, PGT_PNT,
                PGT_PNT*, double*, double*, double*, long*
        );

extern  long  pgtNF_ClsPntToSrfBDR(
                double[2],
                PGT_SURFP, PGT_PNT, double, double,
                PGT_PNT*, double*, double*, double*, long*
        );

extern  long  pgtNF_OnMidBound(
                double[2],
                PGT_SURFP, double, double, double, double,
                double*, double*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NF Bxx : Extreme Position on Surface                      */
/*--------------------------------------------------------------------*/

extern  long  pgtNF_SfExtremePos(
                double[2],
                PGT_SURFP, PGT_VEC,
                PGT_PNT*, double*, double*, long*
        );

extern  long  pgtNF_SfExtremePosR(
                double[2],
                PGT_SURFP, PGT_VEC, double, double,
                PGT_PNT*, double*, double*, long*
        );

extern  long  pgtNF_ExtremeRough(
                double[2],
                PGT_SURFP, PGT_VEC,
                PGT_PNT*, double*, double*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NF Cxx : BEZIER Surface                                   */
/*--------------------------------------------------------------------*/

/*----- Bezier Surface -----------------------------------------------*/
extern  long  pgtNF_AllocBZSurf4(
                long, long, long, long,
                PGT_BZSURF4P*
        );

extern  long  pgtNF_FreeBZSurf4(
                PGT_BZSURF4P*
        );

extern  long  pgtNF_SurfFromBZ4(
                PGT_BZSURF4P,
                PGT_SURFP*
        );

extern  long  pgtNF_BZSurfFromNB4(
                double[2],
                PGT_SURFP,
                PGT_BZSURF4P*
        );

extern  long  pgtNF_IsSurfBezType(
                PGT_SURFP,
                long*
        );

extern  long  pgtNF_AdjBezParamSF(
                double[2],
                PGT_SURFP,
                PGT_SURFP*
        );

extern  long  pgtNF_ReparamSf(
                double[2],
                PGT_SURFP,
                PGT_SURFP*
        );


/*----- CAP Special --------------------------------------------------*/
extern  long  pgtNF_BZSurfFromCAP(
                long, long, double[],
                PGT_BZSURF4P*
        );

extern  long  pgtNF_BZSurfToCAP(
                PGT_BZSURF4P,
                long*, long*, double**
        );



/*--------------------------------------------------------------------*/
/*     PLUS NF Dxx : Create Surface from Passing Points               */
/*--------------------------------------------------------------------*/

extern  long  pgtNF_MkSurfFromPassN(
                double[2],
                long, long, PGT_PNT[],
                PGT_SURFP*
        );

extern  long  pgtNF_MkSurfFromPassF(
                double[2],
                long, long, PGT_PNT[], long, PGT_VEC[], PGT_VEC[],
                PGT_SURFP*
        );

extern  long  pgtNF_ChkSfPassPnts(
                double[2],
                long, long, PGT_PNT[],
                long*, long*, long*
        );

extern  long  pgtNF_SwapSfPassPnts(
                long, long, PGT_PNT[],
                long*, long*, PGT_PNT**
        );

extern  long  pgtNF_MkSurfWithVTan(
                double[2],
                long, long, PGT_PNT[], PGT_VEC[], PGT_VEC[],
                PGT_SURFP*
        );

extern  long  pgtNF_SfCpntFromPassN(
                double[2],
                long, long, PGT_PNT[], double[], double[],
                PGT_SURFP*
        );

extern  long  pgtNF_MkSurfFromPassUV(
                double[2],
                long, long, long, long, double[], double[],
                PGT_PNT[], double[], double[],
                PGT_SURFP*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NF Exx : Expand Surface                                   */
/*--------------------------------------------------------------------*/

extern  long  pgtNF_ExpandSf(
                double[2],
                PGT_SURFP, long, long, double, double,
                PGT_SURFP*, double*, double*
        );

extern  long  pgtNF_ExpandSf2(
                double[2],
                PGT_SURFP,
                long, long, long, long,
                double, double, double, double,
                PGT_SURFP*
        );

extern  long  pgtNF_ExpandSfTangent(
                double[2],
                PGT_SURFP, long, long, double, double,
                PGT_SURFP*
        );

extern  long  pgtNF_ExpandSfTangent2(
                double[2],
                PGT_SURFP,
                long, long, long, long,
                double, double, double, double,
                PGT_SURFP*
        );

extern  long  pgtNF_ExpandSfByLeng(
                double[2],
                PGT_SURFP, long, long, double,
                PGT_SURFP*, double*, double*, double*, double*
        );

extern  long  pgtNF_ExpandSfWithPatch(
                double[2],
                PGT_SURFP, long, long, double, double,
                PGT_SURFP*
        );

extern  long  pgtNF_ExpandSfWithPatch2(
                double[2],
                PGT_SURFP,
                long, long, long, long,
                double, double, double, double,
                PGT_SURFP*
        );

extern  long  pgtNF_ExpandSfWithPatch3(
                double[2],
                PGT_SURFP,
                long, long, long, long,
                double, double, double, double,
                PGT_SURFP*
        );

extern  long  pgtNF_ExpandSfWithPatchARC(
                double[2],
                PGT_SURFP, long, long, double, double,
                PGT_SURFP*
        );

extern  long  pgtNF_ExpandSfWithPatchARC2(
                double[2],
                PGT_SURFP,
                long, long, long, long,
                double, double, double, double,
                PGT_SURFP*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NF Fxx : Fitting Surface                                  */
/*--------------------------------------------------------------------*/

extern  long  pgtNF_FitSurfToPnts(
                double[2], double,
                long, long, PGT_PNT[],
                PGT_SURFP*, double*
        );

extern  long  pgtNF_ParamOnPnts(
                double[2],
                long, long, PGT_PNT[],
                double**, double**
        );

extern  long  pgtNF_MkFitSurf(
                double[2], double,
                long, long, PGT_PNT[], double[], double[],
                PGT_SURFP*, double*
        );

extern  long  pgtNF_FairPntsTab(
                double[2],
                long, PGT_POLYLINEP[], double[],
                long*, PGT_FAIRPNT**
        );

extern  long  pgtNF_FitCurvs(
                double[2], double,
                long, PGT_POLYLINEP[], long, PGT_FAIRPNT[],
                PGT_CURVP[], double*
        );

extern  long  pgtNF_EvalFairSurf(
                double[2],
                long, long, PGT_PNT[], double[], double[], PGT_SURFP,
                double*
        );

extern  long  pgtNF_SfAbsFittol(
                long, long, PGT_PNT[], double,
                double*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NF Gxx : Remove Tiny Patch                                */
/*--------------------------------------------------------------------*/

extern  long  pgtNF_RemovePatchStrip(
                    double[2], double,
                    PGT_SURFP,
                    PGT_SURFP*
        );

extern  long  pgtNF_RemPatches(
                    PGT_SURFP, long, double,
                    PGT_SURFP*
        );

extern  long  pgtNF_IsSurfDegen(
                    double[2], double,
                    PGT_SURFP,
                    long*, long*
        );

extern  long  pgtNF_RemSfExcessKnots(
                    PGT_SURFP,
                    PGT_SURFP*
        );



/*--------------------------------------------------------------------*/
/*     PLUS NC Hxx : Conic into/from NURBS                            */
/*--------------------------------------------------------------------*/

/*----- from Analytical Expression -----*/

extern  long  pgtNF_CreRevoluteSurf(
                    double[2],
                    PGT_CURVP, PGT_LINE, double, double,
                    PGT_SURFP*
        );

extern  long  pgtNF_SurfFromPlane(
                    double[2],
                    PGT_PLANE,
                    PGT_SURFP*
        );

extern  long  pgtNF_SurfFromCylinder(
                    double[2],
                    PGT_CYLINDER,
                    PGT_SURFP*
        );

extern  long  pgtNF_SurfFromCone(
                    double[2],
                    PGT_CONE,
                    PGT_SURFP*
        );

extern  long  pgtNF_SurfFromSphere(
                    double[2],
                    PGT_SPHERE,
                    PGT_SURFP*
        );

extern  long  pgtNF_SurfFromTorus(
                    double[2],
                    PGT_TORUS,
                    PGT_SURFP*
        );

extern  long  pgtNF_SurfFromPseudoTorus(
                    double[2],
                    PGT_CIRCLE, PGT_PNT, PGT_VEC,
                    PGT_SURFP*
        );


/*----- into Analytical Expression -----*/

extern  long  pgtNF_IsSurfPlane(
                    double[2], double,
                    PGT_SURFP,
                    long*, PGT_PLANE*
        );

extern  long  pgtNF_IsSurfCylinder(
                    double[2], double,
                    PGT_SURFP,
                    long*, PGT_CYLINDER*
        );

extern  long  pgtNF_IsSurfCylinderPart(
                    double[2], double,
                    PGT_SURFP,
                    long*, PGT_CYLINDER*
        );

extern  long  pgtNF_IsSurfCone(
                    double[2], double,
                    PGT_SURFP,
                    long*, PGT_CONE*
        );

extern  long  pgtNF_IsSurfSphere(
                    double[2], double,
                    PGT_SURFP,
                    long*, PGT_SPHERE*
        );

extern  long  pgtNF_IsSurfSpherePart(
                    double[2], double,
                    PGT_SURFP,
                    long*, PGT_SPHERE*
        );

extern  long  pgtNF_IsSurfTorus(
                    double[2], double,
                    PGT_SURFP,
                    long*, PGT_TORUS*
        );

extern  long  pgtNF_IsSurfTorus2(
                    double[2], double,
                    PGT_SURFP,
                    long*, PGT_TORUS*, long*
        );

extern  long  pgtNF_IsSurfPseudoTorus(
                    double[2], double,
                    PGT_SURFP,
                    long*, PGT_CIRCLE*, PGT_PNT*, PGT_VEC*
        );



/*----- End of File --------------------------------------------------*/



#ifdef __cplusplus
}
#endif



#endif
