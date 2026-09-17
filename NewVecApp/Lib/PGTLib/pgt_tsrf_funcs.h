/***********************************************************************

    ä÷êîñº : [TSRF HD03]  pgt_tsrf_funcs.h

    ã@  î\ : ÇsÇrÇqÇeÉâÉCÉuÉâÉäópÉwÉbÉ_ÉtÉ@ÉCÉã

    PGT TSRF Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_TSRF_FUNCS_H
#define PGT_TSRF_FUNCS_H



#include    "pgt_tsrf_struct.h"



#ifdef __cplusplus
extern "C"{
#endif



/*--------------------------------------------------------------------*/
/*     Utilities for Trimmed Surface                                  */
/*--------------------------------------------------------------------*/


/*----- [Axx] Trim Surface Operation ---------------------------------*/

extern  long  pgtTS_AttachUVCurv(
                    double[2], double,
                    PGT_TRIMSFP
        );

extern  long  pgtTS_AttachXYZCurv(
                    double[2], double,
                    PGT_TRIMSFP
        );

extern  long  pgtTS_AttachUVPoly(
                    double[2],  double,
                    PGT_TRIMSFP
        );

extern  long  pgtTS_UVAreaInTrimSF(
                    double[2],
                    PGT_TRIMSFP,
                    double*
        );

extern  long  pgtTS_ReverseBaseSF(
                    double[2], double,
                    PGT_TRIMSFP, double
        );

extern  long  pgtTS_PntsInTrimSF(
                    double[2],
                    PGT_TRIMSFP, double,
                    long*, PGT_PNT**, PGT_PNT**
        );

extern  long  pgtTS_PntsInTrimSF2(
                    double[2],
                    PGT_TRIMSFP, double,
                    long*, PGT_PNT**, PGT_PNT**
        );

extern  long  pgtTS_AttachUVPoly2(
                    double[2],
                    PGT_TRIMSFP
        );

extern  long  pgtTS_IsPntInTrimSF(
                    double[2],
                    PGT_TRIMSFP, double, double,
                    long*
        );

extern  long  pgtTS_IsPntInTrimSF2(
                    double[2],
                    PGT_TRIMSFP, double, double,
                    long*
        );

extern  long  pgtTS_AttachUVPoly3(
                    double[2], double,
                    PGT_TRIMSFP
        );

extern  long  pgtTS_PntsOnTrimLP(
                    double[2],
                    PGT_TRIMSFP, double,
                    long*, PGT_PNT**, PGT_PNT**
        );

extern  long  pgtTS_MMBoxForTrimLP(
                    double[2],
                    PGT_TRIMLPP,
                    double[3], double[3]
        );

extern  long  pgtTS_UVAreaForTrimLP(
                    double[2],
                    PGT_TRIMLPP,
                    double*
        );

extern  long  pgtTS_ClsUVPolyFromTrimLP(
                    double[2],
                    PGT_TRIMLPP,
                    PGT_POLYLINEP*
        );

extern  long  pgtTS_ClsXYZPolyFromTrimLP(
                    double[2],
                    PGT_TRIMLPP,
                    PGT_POLYLINEP*
        );

extern  long  pgtTS_UVMMBoxForTrimLP(
                    double[2],
                    PGT_TRIMLPP,
                    double[2], double[2]
        );

extern  long  pgtTS_SplitEdgeAtPole(
                    double[2], double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_MergeEdgeAtPole(
                    double[2],
                    PGT_TRIMSFP,
                    PGT_TRIMSFP
        );

extern  long  pgtTS_SetDegenFlag(
                    double[2], double,
                    PGT_TRIMSFP
        );

extern  long  pgtTS_AttachUVPolyCvFit(
                    double[2],  double, double,
                    PGT_TRIMSFP
        );

extern  long  pgtTS_AttachUVPolyCvFit2(
                    double[2],  double, double,
                    PGT_TRIMSFP
        );

extern  long  pgtTS_AttachUVPolyLoop(
                    double[2],
                    PGT_TRIMSFP
        );

extern  long  pgtTS_AttachUVPolyLoopPOLE(
                    double[2], double, double,
                    PGT_TRIMSFP
        );

extern  long  pgtTS_AttachUVPolyLoopPOLE2(
                    double[2], double,
                    PGT_TRIMSFP
        );

extern  long  pgtTS_AttachUVPolyLoopPOLE_R(
                    double[2], double, double,
                    PGT_TRIMSFP
        );

extern  long  pgtTS_IsTrimSFOnSeam(
                    double[2],
                    PGT_TRIMSFP,
                    long*, long*,
                    double*, double*, double*, double*
        );

extern  long  pgtTS_AttachUVCurvDGN(
                    double[2], double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_DetachUVCurv(
                    PGT_TRIMSFP
        );

extern  long  pgtTS_DetachXYZCurv(
                    PGT_TRIMSFP
        );

extern  long  pgtTS_DetachUVPolylines(
                    PGT_TRIMSFP
        );

extern  long  pgtTS_IsTrimSFFullBound(
                    double[2], double,
                    PGT_TRIMSFP,
                    long*
        );

extern  long  pgtTS_AreCurvsSame(
                    double[2], double,
                    PGT_CURVP, PGT_CURVP,
                    long*
        );

extern  long  pgtTS_IsCurvOnBaseOne(
                    double[2], double,
                    PGT_CURVP, PGT_CURVP,
                    long*, long*
        );

extern  long  pgtTS_ConvGeomIntoBezier(
                    double[2],
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_CleanUVPoly(
                    double[2],
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*, long*
        );




/*----- [Bxx] File I/O -----------------------------------------------*/

/*----- Ascii -----*/
extern  long  pgtTS_WriteTrimSF(
                    char[], PGT_TRIMSFP
        );

extern  long  pgtTS_WriteTrimSFFP(
                    FILE*, PGT_TRIMSFP
        );

extern  long  pgtTS_ReadTrimSF(
                    char[],
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_ReadTrimSFFP(
                    FILE*,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_WriteTrimSFArray(
                    char[], long, PGT_TRIMSFP[]
        );

extern  long  pgtTS_ReadTrimSFArray(
                    char[],
                    long*, PGT_TRIMSFP**
        );


/*----- Binary -----*/

extern  long  pgtTS_WriteTrimSFBIN(
                    char[], PGT_TRIMSFP
        );

extern  long  pgtTS_WriteTrimSFBINFP(
                    FILE*, PGT_TRIMSFP
        );

extern  long  pgtTS_ReadTrimSFBIN(
                    char[],
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_ReadTrimSFBINFP(
                    FILE*,
                    PGT_TRIMSFP*
        );



/*----- [Cxx] Basic Operation ----------------------------------------*/

extern  long  pgtTS_CopyTrimSF(
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_CopyTrimSFADJ(
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_ReverseTrimSF(
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_MoveTrimSF(
                    double[2],
                    PGT_TRIMSFP, double[4][4],
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_NormalizeTrimSF(
                    double[2],
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_NormalizeTrimSFGEOM(
                    double[2],
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_VerifyFullBound(
                    double[2],
                    PGT_TRIMSFP,
                    long*
        );

extern  long  pgtTS_RemoveTrimLP(
                    PGT_TRIMSFP, long, long[],
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_CopyTrimLP(
                    PGT_TRIMLPP,
                    PGT_TRIMLPP*
        );

extern  long  pgtTS_RemUVElements(
                    PGT_TRIMSFP
        );

extern  long  pgtTS_CopyTrimED(
                    PGT_TRIMEDP,
                    PGT_TRIMEDP*
        );

extern  long  pgtTS_SurfIntoTrimSF(
                    double[2],
                    PGT_SURFP, long,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_FindEdgeWithPolyline(
                    PGT_TRIMSFP,
                    long*
        );

extern  long  pgtTS_BrkEdgeWithPolyline(
                    double[],
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_ShiftTrimSF(
                    double[2],
                    PGT_TRIMSFP, double[3],
                    PGT_TRIMSFP*
        );



/*----- [Dxx] Split Trimmed Surface ----------------------------------*/

extern  long  pgtTS_SplitTrimSF(
                    double[2],
                    PGT_TRIMSFP, long, double,
                    long*, PGT_TRIMSFP**
        );

extern  long  pgtTS_IsSplitPosOnSurf(
                    double[2],
                    PGT_TRIMSFP, long, double,
                    long*
        );

extern  long  pgtTS_SplitLoops(
                    double[2],
                    PGT_TRIMSFP, long, double,
                    long*, long*, PGT_TSLOOPP*
        );

extern  long  pgtTS_Brk3DCrvWithUVCrv(
                    double[2],
                    PGT_CURVP, long, long, PGT_CURVP[], PGT_SURFP,
                    long*, PGT_CURVP**
        );

extern  long  pgtTS_MakeEdgeGroup(
                    double[2],
                    PGT_TRIMSFP, long, double, PGT_TSLOOPP,
                    PGT_TSLOOPP*, PGT_TSLOOPP*
        );

extern  long  pgtTS_CreTSLoops(
                    double[2],
                    PGT_TRIMSFP, long, double, long, PGT_TSLOOPP,
                    long*, PGT_TSLOOPP**
        );

extern  long  pgtTS_SetEndPoints(
                    double[2],
                    PGT_TRIMSFP, long, double,
                    PGT_TSLOOPP
        );

extern  long  pgtTS_StartEdge(
                    PGT_TSLOOPP,
                    long*
        );

extern  long  pgtTS_NextEdge(
                    PGT_TSLOOPP, long,
                    long*
        );

extern  long  pgtTS_GetCopyOfEdge(
                    PGT_TSLOOPP, long,
                    PGT_TSEDGE*
        );

extern  long  pgtTS_NextEdgeOnBound(
                    double[2],
                    PGT_TRIMSFP, long, double, long,
                    PGT_TSLOOPP, long,
                    PGT_TSEDGE*, long*
        );

extern  long  pgtTS_CreTrimSurfs(
                    double[2],
                    PGT_TRIMSFP, long, double, long, long, PGT_TSLOOPP[],
                    long*, PGT_TRIMSFP**
        );

extern  long  pgtTS_ClsUVPolyFromLoop(
                    double[2],
                    long, PGT_TSLOOPP[],
                    long*, PGT_POLYLINEP**
        );

extern  long  pgtTS_MakeLoopGroup(
                    double[2],
                    long, PGT_POLYLINEP[],
                    long*, PGT_TSGROUPP**
        );

extern  long  pgtTS_LoopsIntoTrimSurf(
                    double[2],
                    PGT_TRIMSFP, long, double, long,
                    long, PGT_TSLOOPP[], PGT_TSGROUPP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_AllocTSLoop(
                    long,
                    PGT_TSLOOPP*
        );

extern  long  pgtTS_FreeTSLoop(
                    PGT_TSLOOPP*
        );

extern  long  pgtTS_AllocTSGroup(
                    long,
                    PGT_TSGROUPP*
        );

extern  long  pgtTS_FreeTSGroup(
                    PGT_TSGROUPP*
        );



/*----- [Exx] Smooth Trimmed Surface ---------------------------------*/

extern  long  pgtTS_SmoothTrimSF(
                    double[2],
                    PGT_TRIMSFP, long,
                    PGT_TRIMSFP*
        );



/*----- [Fxx] Make Base Surface Tight --------------------------------*/

extern  long  pgtTS_MkBaseSfTight(
                    double[2], double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_MkBaseSfTight3D(
                    double[2],
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_IsTrimSFOnTorus(
                    double[2], double,
                    PGT_TRIMSFP,
                    long*
        );

extern  long  pgtTS_IsTrimSFOnPseudoTorus(
                    double[2], double,
                    PGT_TRIMSFP,
                    long*
        );

extern  long  pgtTS_MakeTrimSFOnTorusTight(
                    double[2], double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_MakeTrimSFOnPseudoTorusTight(
                    double[2], double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_IsTrimSFOnSphere(
                    double[2], double,
                    PGT_TRIMSFP,
                    long*
        );

extern  long  pgtTS_MakeTrimSFOnSphereTight(
                    double[2], double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );



/*----- [Gxx] Align Trim Loop in TrimSF ------------------------------*/

extern  long  pgtTS_AlignTrimLP(
                    double[2], double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_AlignTrimLPWithUVC(
                    double[2], double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_DecideTrimLPDir(
                    double[2], double,
                    PGT_TRIMLPP, PGT_SURFP,
                    long*
        );

extern  long  pgtTS_DecideTrimLPDirWithUVC(
                    double[2], double,
                    PGT_TRIMLPP, PGT_SURFP,
                    long*
        );

extern  long  pgtTS_ReverseTrimLP(
                    PGT_TRIMLPP,
                    PGT_TRIMLPP*
        );




/*----- [Hxx] Intersection -------------------------------------------*/

extern  long  pgtTS_IntLineTrimSF(
                    double[2], double,
                    PGT_LINE, PGT_TRIMSFP,
                    long*, PGT_INTPNT**
        );

extern  long  pgtTS_IntLineTrimSF2(
                    double[2], double,
                    PGT_LINE, PGT_TRIMSFP,
                    long*, PGT_INTPNT**
        );

extern  long  pgtTS_IntLineTrimSFR(
                    double[2], double,
                    PGT_LINE, PGT_TRIMSFP, double, double,
                    long*, PGT_INTPNT*
        );

extern  long  pgtTS_IntLineTrimSFR2(
                    double[2], double,
                    PGT_LINE, PGT_TRIMSFP, double, double,
                    long*, PGT_INTPNT*
        );

extern  long  pgtTS_IntPlaneTrimSF(
                    double[2], double, double,
                    PGT_PLANE, PGT_TRIMSFP,
                    long*, PGT_CURVP**
        );

extern  long  pgtTS_IntPlaneTrimSFRPT(
                    double[2], double,
                    PGT_PLANE, PGT_TRIMSFP,
                    long*, PGT_CURVP**
        );

extern  long  pgtTS_DelUVCurvOnTrimLP(
                    double[2], double,
                    PGT_TRIMSFP,
                    long, PGT_TSINTCRVP[],
                    long*, PGT_TSINTCRVP**
        );

extern  long  pgtTS_GetUVCurvWithinTrimLP(
                    double[2], double,
                    PGT_TRIMSFP,
                    long, PGT_TSINTCRVP[],
                    long*, PGT_CURVP**
        );

extern  long  pgtTS_InitTrimSFToSliceRPT(
                    double[2], double, double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_AllocTSIntcrv(
                    PGT_TSINTCRVP*
        );

extern  long  pgtTS_FreeTSIntcrv(
                    PGT_TSINTCRVP*
        );

extern  long  pgtTS_AddIntsecToTSIntcrv(
                    PGT_TSINTCRVP, PGT_TSINTSEC
        );


/*----- TrimSF and TrimSF -----*/

extern  long  pgtTS_IntTrimSFTrimSF(
                    double[2], double, double,
                    PGT_TRIMSFP, PGT_TRIMSFP,
                    long*, PGT_CURVP**
        );

extern  long  pgtTS_IntTrimSFTrimSFRPT(
                    double[2], double, double,
                    PGT_TRIMSFP, PGT_TRIMSFP,
                    long*, PGT_CURVP**
        );

extern  long  pgtTS_IntTrimSFTrimSFRPT2(
                    double[2], double, double,
                    PGT_TRIMSFP, PGT_TRIMSFP,
                    long*, PGT_CURVP**
        );

extern  long  pgtTS_InitTrimSFForIntsecCv(
                    double[2], double, double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_InitTrimSFForIntsecCv2(
                    double[2], double, double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_DelXYZCurvOnTrimLP(
                    double[2], double,
                    PGT_TRIMSFP,
                    long, PGT_TSINTCRVP[],
                    long*, PGT_TSINTCRVP**
        );

extern  long  pgtTS_GetXYZCurvWithinTrimLP(
                    double[2], double,
                    PGT_TRIMSFP,
                    long, PGT_TSINTCRVP[],
                    long*, PGT_TSINTCRVP**
        );

extern  long  pgtTS_RemDupXYZCurv(
                    double[2], double,
                    long, PGT_CURVP[],
                    long*, PGT_CURVP**
        );




/*----- [Ixx] Adjust Trim Edge Terminals -----------------------------*/

extern  long  pgtTS_AdjTrimEDTerms(
                    double[2],
                    PGT_TRIMSFP
        );

extern  long  pgtTS_AdjTrimEDTerms2(
                    double[2],
                    PGT_TRIMSFP
        );

extern  long  pgtTS_AdjGapBetweenTrimED(
                    double[2],
                    PGT_SURFP,
                    PGT_TRIMLPP
        );

extern  long  pgtTS_AdjGapBetweenTrimED2(
                    double[2],
                    PGT_SURFP,
                    PGT_TRIMLPP
        );

extern  long  pgtTS_AddEdgeOnPole(
                    double[2],
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_HealTrimEDTerms(
                    double[2],
                    PGT_TRIMLPP
        );

extern  long  pgtTS_HealTrimEDTermsUV(
                    double[2],
                    PGT_TRIMLPP
        );




/*----- [Jxx] Split Non G2 Edges -------------------------------------*/

extern  long  pgtTS_SplitNonG2TrimED(
                    double[2], double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );




/*----- [Kxx] Remove Tiny Edge and Patch -----------------------------*/

extern  long  pgtTS_RemTinyEdgePatch(
                    double[2], double, double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_RemTinyEdgePatchINS(
                    double[2], double, double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );




/*----- [Lxx] Remove Degenerate Edge String --------------------------*/

extern  long  pgtTS_RemDegenEdStrInTrimSF(
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );

extern  long  pgtTS_RemDegenEdStrInTrimLP(
                    PGT_TRIMLPP,
                    PGT_TRIMLPP*
        );




/*----- [Mxx] Split Periodic TrimSF ----------------------------------*/

/*----- Alloc / Free / Copy -----*/

extern  long  pgtTS_AllocTSFragVT(
                    PGT_TSFRAGVTP*
        );

extern  long  pgtTS_AllocTSFragED(
                    PGT_TSFRAGEDP*
        );

extern  long  pgtTS_AllocTSFragLP(
                    long,
                    PGT_TSFRAGLPP*
        );

extern  long  pgtTS_AllocTSFragGR(
                    long,
                    PGT_TSFRAGGRP*
        );

extern  long  pgtTS_FreeTSFragVT(
                    PGT_TSFRAGVTP*
        );

extern  long  pgtTS_FreeTSFragED(
                    PGT_TSFRAGEDP*
        );

extern  long  pgtTS_FreeTSFragLP(
                    PGT_TSFRAGLPP*
        );

extern  long  pgtTS_FreeTSFragGR(
                    PGT_TSFRAGGRP*
        );

extern  long  pgtTS_CopyTSFragED(
                    PGT_TSFRAGEDP,
                    PGT_TSFRAGEDP*
        );

extern  long  pgtTS_CopyTSFragLP(
                    PGT_TSFRAGLPP,
                    PGT_TSFRAGLPP*
        );

/*----- Is TrimSF Periodic ? -----*/

extern  long  pgtTS_IsTrimSFPeriodic(
                    double[2], double,
                    PGT_TRIMSFP,
                    long*
        );

extern  long  pgtTS_Arctic(
                    double[2],
                    PGT_SURFP, double,
                    long*, long*, double[2], double[2]
        );

extern  long  pgtTS_CkSeam(
                    double[2],
                    PGT_SURFP, double,
                    long*, long*, double[2], double[2]
        );

extern  long  pgtTS_GetInitUVPolyFromTrimLP(
                    double[2],
                    PGT_SURFP, long, long,
                    PGT_TRIMLPP,
                    long*, PGT_POLYLINEP**
        );

extern  long  pgtTS_GetInitUVPolyFromTrimLPTRS(
                    double[2],
                    PGT_SURFP, PGT_PNT, PGT_VEC,
                    PGT_TRIMLPP,
                    long*, PGT_POLYLINEP**
        );

extern  long  pgtTS_CalUVMMBoxWithSeam(
                    long,
                    double, double, double, double,
                    long, long, double[2], double[2],
                    long, long, double[2], double[2],
                    long, PGT_POLYLINEP[],
                    long*, long*, double*, double*
        );

/*----- Split Periodic TrimSF -----*/

extern  long  pgtTS_SplitPeriodicTrimSF(
                    double[2], double, double,
                    PGT_TRIMSFP, long,
                    long*, PGT_TRIMSFP**
        );

extern  long  pgtTS_SplitPeriodicTrimSF_DBG(
                    double[2], double, double,
                    PGT_TRIMSFP, long, long,
                    long*, PGT_TSFRAGEDP**
        );

extern  long  pgtTS_IsTrimSFClosedSolid(
                    double[2], double,
                    PGT_TRIMSFP,
                    long*
        );

extern  long  pgtTS_FindSlitInBack(
                    double[2],
                    PGT_TRIMSFP,
                    long*, long*, double*, double*
        );

extern  long  pgtTS_FindSeamPosToSplit(
                    double[2], double,
                    PGT_TRIMSFP,
                    long, long, double, double,
                    long*, long*, 
                    double*, double*, double*, double*
        );

extern  long  pgtTS_ClassifyTrimLP(
                    double[2],
                    double, double, double, double,
                    long, long, double[2], double[2],
                    long, long, double[2], double[2],
                    long, PGT_POLYLINEP[],
                    long*
        );

extern  long  pgtTS_ClassifyTrimLP2(
                    double[2],
                    double, double, double, double,
                    long, long, double[2], double[2],
                    long, long, double[2], double[2],
                    long, PGT_POLYLINEP[],
                    long*, PGT_POLYLINEP*
        );

extern  long  pgtTS_SeamNotOnOuterLP(
                    double[2],
                    long,
                    double, double, double, double,
                    long, long, double[2], double[2],
                    long, long, double[2], double[2],
                    long, PGT_POLYLINEP[],
                    long*, double*
        );

extern  long  pgtTS_RotateBaseSF(
                    double[2], double,
                    PGT_SURFP, 
                    long, long, double, double,
                    PGT_SURFP*
        );

extern  long  pgtTS_SeamLine(
                    double[2],
                    PGT_SURFP, long, long,
                    long*, long*,
                    PGT_CURVP**, PGT_CURVP**,
                    PGT_CURVP**, PGT_CURVP**
        );

extern  long  pgtTS_SetIntcrvFromTrimED(
                    PGT_TRIMSFP,
                    long*, PGT_TSINTCRVP**
        );

extern  long  pgtTS_SetIntcrvFromSeamLine(
                    PGT_SURFP,
                    long, PGT_CURVP[], PGT_CURVP[],
                    long, PGT_CURVP[], PGT_CURVP[],
                    long*, PGT_TSINTCRVP**
        );

extern  long  pgtTS_MkFragmentEdgesFromTrimCV(
                    double[2], double, double,
                    PGT_SURFP,
                    long, PGT_TSINTCRVP[],
                    long, PGT_CURVP[], long, PGT_CURVP[],
                    long*, PGT_TSFRAGEDP**
        );

extern  long  pgtTS_MkFragmentEdgesFromSeamCV(
                    double[2], double,
                    PGT_SURFP,
                    long, PGT_TSINTCRVP[],
                    long, PGT_TSFRAGEDP[],
                    long*, PGT_TSFRAGEDP**
        );

extern  long  pgtTS_GatherFragmentEdges(
                    double[2],
                    long, PGT_TSFRAGEDP[],
                    long, PGT_TSFRAGEDP[],
                    long*, PGT_TSFRAGEDP**
        );

extern  long  pgtTS_MkFragmentLoops(
                    double[2], double,
                    PGT_SURFP,
                    long, PGT_TSFRAGEDP[],
                    long*, PGT_TSFRAGLPP**
        );

extern  long  pgtTS_MkFragmentLoops_DBG(
                    double[2], double,
                    PGT_SURFP,
                    long, PGT_TSFRAGEDP[]
        );

extern  long  pgtTS_CreFragVT(
                    double[2],
                    PGT_SURFP,
                    long, PGT_TSFRAGEDP[],
                    long*, PGT_TSFRAGVTP**
        );

extern  long  pgtTS_MergeFragVT(
                    double[2], double, double,
                    PGT_SURFP,
                    long, PGT_TSFRAGEDP[],
                    long, PGT_TSFRAGVTP[],
                    long*, PGT_TSFRAGVTP**
        );

extern  long  pgtTS_MergeFragVTInXYZ(
                    double[2], double,
                    long, PGT_TSFRAGEDP[],
                    long, PGT_TSFRAGVTP[],
                    long*, PGT_TSFRAGVTP**
        );

extern  long  pgtTS_MakeFragmentLoopGroups(
                    double[2],
                    long, PGT_TSFRAGLPP[],
                    long*, PGT_TSFRAGGRP**
        );

extern  long  pgtTS_MakeTrimSFFromFragGR(
                    double[2],
                    PGT_SURFP,
                    PGT_TSFRAGGRP,
                    PGT_TRIMSFP*
        );


/*----- Rotate Base Sphere Surf -----*/

extern  long  pgtTS_RotateSphere(
                    double[2], double,
                    PGT_TRIMSFP,
                    PGT_SURFP*, long*
        );



/*----- [Nxx] Is trimLP like Sliver ? --------------------------------*/

extern  long  pgtTS_IsTrimLPLikeSliver(
                    double[2], double,
                    PGT_TRIMLPP,
                    long*
        );

extern  long  pgtTS_EdgeTabForTrimLP(
                    double[2], double,
                    PGT_TRIMLPP,
                    PGT_TSBREDTABP*
        );

extern  long  pgtTS_VtexTabForTrimSF(
                    double[2],
                    PGT_TSBREDTABP,
                    PGT_TSBRVTTABP*
        );

extern  long  pgtTS_MergeVtexForTrimSF(
                    double[2], double,
                    PGT_TSBREDTABP, PGT_TSBRVTTABP,
                    PGT_TSBRVTTABP*
        );

extern  long  pgtTS_SplitEdgeForTrimSF(
                    double[2], double,
                    PGT_TSBREDTABP, PGT_TSBRVTTABP,
                    PGT_TSBREDTABP*
        );


extern  long  pgtTS_SplitPosOnEDCurv(
                    double[2], double,
                    PGT_CURVP, long, PGT_ELMPNT[],
                    long, long[],
                    long*, long**, double**
        );

extern  long  pgtTS_SplitEdge(
                    double[2],
                    long, PGT_CURVP, long, long,
                    long, long*, double*,
                    long*, PGT_TSEDCURV**
        );

extern  long  pgtTS_FindPairEdge(
                    double[2], double,
                    PGT_TSBREDTABP,
                    long*
        );

extern  long  pgtTS_GetVTVtex(
                    PGT_TSBRVTTABP, long,
                    PGT_TSBRVTEXP*
        );

extern  long  pgtTS_AllocBREdgeTab(
                    long,
                    PGT_TSBREDTABP*
        );

extern  long  pgtTS_FreeBREdgeTab(
                    PGT_TSBREDTABP*
        );

extern  long  pgtTS_AllocBREdge(
                    PGT_TSBREDGEP*
        );

extern  long  pgtTS_FreeBREdge(
                    PGT_TSBREDGEP*
        );

extern  long  pgtTS_AllocBRVtexTab(
                    long,
                    PGT_TSBRVTTABP*
        );

extern  long  pgtTS_FreeBRVtexTab(
                    PGT_TSBRVTTABP*
        );

extern  long  pgtTS_AllocBRVtex(
                    PGT_TSBRVTEXP*
        );

extern  long  pgtTS_FreeBRVtex(
                    PGT_TSBRVTEXP*
        );




/*----- [Oxx] Concate G2 Edges ---------------------------------------*/

extern  long  pgtTS_ConcatG2Edges(
                    double[2], double,
                    PGT_TRIMSFP,
                    PGT_TRIMSFP*
        );




/*----- [Pxx] Make TrimSF from BaseSF and Curves ---------------------*/

extern  long  pgtTS_MakeTrimSFFromSfAndCvs(
                    double[2], double,
                    PGT_SURFP, long, PGT_CURVP[],
                    PGT_TRIMSFP*
        );



/*----- End of File --------------------------------------------------*/



#ifdef __cplusplus
}
#endif



#endif
