/***********************************************************************

    関数名 : [IT HD03]  pgt_it_funcs.h

    機  能 : ＩＴライブラリ用ヘッダファイル

    PGT IT Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.07.08

***********************************************************************/



#ifndef PGT_IT_FUNCS_H
#define PGT_IT_FUNCS_H



#include    "pgt_it_struct.h"



#ifdef __cplusplus
extern "C"{
#endif



/*----- [Axx] 2D Curve and Line --------------------------------------*/

extern  long  pgtIT_IntCrvLin2D(
                double[2],
                PGT_CURVP, PGT_LINE,
                long*, PGT_INTPNT**, long*
        );

extern  long  pgtIT_LineLRFlag(
                double[2],
                PGT_PNT, PGT_LINE,
                long*, double*, double*
        );

extern  long  pgtIT_CLbisrch2D(
                double[2],
                PGT_LINE, PGT_CURVP, double, double,
                PGT_INTPNT*, long*
        );

extern  long  pgtIT_IntCrvPoly(
                double[2],
                PGT_CURVP, PGT_POLYLINEP,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntCirLin2D(
                double[2],
                PGT_CIRCLE, PGT_LINE,
                long*, double[2], double[2], PGT_PNT[2]
        );

extern  long  pgtIT_IntElpLin2D(
                double[2],
                PGT_ELLIPSE, PGT_LINE,
                long*, double[2], double[2], PGT_PNT[2]
        );

extern  long  pgtIT_IntCirCir2D(
                double[2],
                PGT_CIRCLE, PGT_CIRCLE,
                long*, double[2], double[2], PGT_PNT[2]
        );

extern  long  pgtIT_IntElpElp2D(
                double[2],
                PGT_ELLIPSE, PGT_ELLIPSE,
                long*, double[4], double[4], PGT_PNT[4]
        );

extern  long  pgtIT_IntElpCir2D(
                double[2],
                PGT_ELLIPSE, PGT_CIRCLE,
                long*, double[4], double[4], PGT_PNT[4]
        );

extern  long  pgtIT_IntLinPol2D(
                double[2],
                PGT_LINE, PGT_POLYLINEP,
                long*, double**, double**, PGT_PNT**
        );

extern  long  pgtIT_IntCirPol2D(
                double[2],
                PGT_CIRCLE, PGT_POLYLINEP,
                long*, double**, double**, PGT_PNT**
        );

extern  long  pgtIT_IntElpPol2D(
                double[2],
                PGT_ELLIPSE, PGT_POLYLINEP,
                long*, double**, double**, PGT_PNT**
        );

extern  long  pgtIT_IntRayTri(
                double[2],
                double[3], double[3], PGT_TRIANGLE,
                long*, double*, PGT_PNT*
        );

extern  long  pgtIT_IntRayPln(
                double[2],
                double[3], double[3], PGT_PLANE,
                long*, double*, PGT_PNT*
        );

extern  long  pgtIT_IntRayCyl(
                double[2],
                double[3], double[3], PGT_CYLINDER,
                long*, double[2], PGT_PNT[2]
        );

extern  long  pgtIT_IntRayCylSolid(
                double[2],
                double[3], double[3], PGT_CYLINDER,
                long*, double[2], PGT_PNT[2]
        );

extern  long  pgtIT_IntRayCon(
                double[2],
                double[3], double[3], PGT_CONE,
                long*, double[2], PGT_PNT[2]
        );

extern  long  pgtIT_IntRayConSolid(
                double[2],
                double[3], double[3], PGT_CONE,
                long*, double[2], PGT_PNT[2]
        );

extern  long  pgtIT_IntRaySph(
                double[2],
                double[3], double[3], PGT_SPHERE,
                long*, double[2], PGT_PNT[2]
        );

extern  long  pgtIT_IntPlnPln(
                double[2],
                PGT_PLANE, PGT_PLANE,
                long*, PGT_LINE*
        );

extern  long  pgtIT_IntPlnPlnPln(
                double[2],
                PGT_PLANE, PGT_PLANE, PGT_PLANE,
                long*, PGT_PNT*
        );

extern  long  pgtIT_IntTriPln(
                double[2],
                PGT_TRIANGLE, PGT_PLANE,
                long*, PGT_LINE*
        );

extern  long  pgtIT_IntCylPln(
                double[2],
                PGT_CYLINDER, PGT_PLANE,
                long*, long*, PGT_ELLIPSE*, PGT_CIRCLE*, long*, PGT_LINE[2]
        );

extern  long  pgtIT_IntCirPln(
                double[2],
                PGT_CIRCLE, PGT_PLANE,
                long*, double[2], PGT_PNT[2]
        );

extern  long  pgtIT_IntElpPln(
                double[2],
                PGT_ELLIPSE, PGT_PLANE,
                long*, double[2], PGT_PNT[2]
        );

extern  long  pgtIT_SolveQuadratic(
                double,
                double, double, double,
                long*, double[2]
        );



/*----- [Bxx] Surface and Line ---------------------------------------*/

extern  long  pgtIT_IntSrfLin(
                double[2], 
                PGT_SURFP, PGT_LINE,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntSrfLinR(
                double[2], 
                PGT_SURFP, PGT_LINE, PGT_PNT,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntSrfLinRUV(
                double[2], 
                PGT_SURFP, PGT_LINE, double, double,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntPchLin(
                double[2], 
                PGT_SURFP, double, double, double, double, PGT_LINE,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_ApproachIntSL(
                double[2], 
                PGT_PNT, PGT_SURFP, PGT_LINE,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*,
                double*
        );

extern  long  pgtIT_ApproachIntSLRUV(
                double[2], 
                PGT_SURFP, PGT_LINE, double, double,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*,
                double*
        );


/*----- New Algorithm -----*/

extern  long  pgtIT_IntLineSurf(
                double[2], double,
                PGT_LINE, PGT_SURFP,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntLineSurfR(
                double[2], double,
                PGT_LINE, PGT_SURFP, double, double,
                long*, PGT_INTPNT*
        );

extern  long  pgtIT_BoxCheckLinSrf(
                double[2], 
                PGT_LINE, PGT_SURFP,
                long*
        );

extern  long  pgtIT_IntLinePatch(
                double[2], double,
                PGT_LINE, PGT_SURFP, double, double, double, double,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_UVStep(
                double[2], 
                PGT_VEC, PGT_VEC, PGT_VEC, double, double,
                double*, double*
        );



/*----- [Cxx] Plane and Curve ----------------------------------------*/

extern  long  pgtIT_IntPlnCrv(
                double[2], 
                PGT_PLANE, PGT_CURVP,
                long*, PGT_INTPNT**, long*
        );

extern  long  pgtIT_IntPlnCrvR(
                double[2], 
                PGT_PLANE, PGT_CURVP, PGT_PNT,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntPlnCrvRT(
                double[2], 
                PGT_PLANE, PGT_CURVP, double,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_ApproachIntPC(
                double[2], 
                PGT_PNT, PGT_PLANE, PGT_CURVP,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*,
                double*
        );

extern  long  pgtIT_ApproachIntPCRT(
                double[2], 
                PGT_PLANE, PGT_CURVP, double,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*,
                double*
        );

extern  long  pgtIT_BiSearchIntPC(
                double[2], 
                PGT_PLANE, PGT_CURVP,
                long*, PGT_INTPNT[2]
        );

extern  long  pgtIT_CvExtremeToPlane(
                double[2], 
                PGT_PLANE, PGT_CURVP,
                long*, PGT_PNT*, double*
        );

extern  long  pgtIT_CvIntsecToPlane(
                double[2], 
                PGT_PLANE, PGT_CURVP, double, double,
                long*, PGT_INTPNT*
        );



/*----- [Dxx] Surface and Curve --------------------------------------*/

extern  long  pgtIT_IntSrfCrv(
                double[2], 
                PGT_SURFP, PGT_CURVP,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntSrfCrvR(
                double[2], 
                PGT_SURFP, PGT_CURVP, PGT_PNT,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntSrfCrvRT(
                double[2], 
                PGT_SURFP, PGT_CURVP, double,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntSrfCrvRUV(
                double[2], 
                PGT_SURFP, PGT_CURVP, double, double,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntPchSeg(
                double[2], 
                PGT_SURFP, double, double, double, double,
                PGT_CURVP, double, double,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntSubPchSeg(
                double[2],
                PGT_SURFP, PGT_CURVP, long, long,
                long*, PGT_INTPNT[]
        );

extern  long  pgtIT_BoxCheckSrfCrv(
                double[2], 
                PGT_SURFP, PGT_CURVP,
                long*, PGT_BOX*, PGT_BOX*
        );

extern  long  pgtIT_ApproachIntSC(
                double[2], double,
                PGT_PNT, PGT_SURFP, PGT_CURVP,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*,
                double*
        );

extern  long  pgtIT_ApproachIntSCRT(
                double[2], 
                PGT_SURFP, PGT_CURVP, double,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*,
                double*
        );

extern  long  pgtIT_ApproachIntSCRUV(
                double[2], 
                PGT_SURFP, PGT_CURVP, double, double,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*,
                double*
        );

extern  long  pgtIT_DivSurf4(
                double[2], 
                PGT_SURFP,
                PGT_SURFP*, PGT_SURFP*, PGT_SURFP*, PGT_SURFP*
        );

extern  long  pgtIT_DivCurv2(
                double[2], 
                PGT_CURVP,
                PGT_CURVP*, PGT_CURVP*
        );

extern  long  pgtIT_BiSearchIntSC(
                double[2], 
                PGT_SURFP, PGT_CURVP,
                long*, PGT_INTPNT[2]
        );

extern  long  pgtIT_CvExtremeToSurf(
                double[2], 
                PGT_SURFP, PGT_CURVP,
                long*, PGT_PNT*, double*
        );

extern  long  pgtIT_CvIntsecToSurf(
                double[2], 
                PGT_SURFP, PGT_CURVP, double, double,
                long*, PGT_INTPNT*
        );



/*----- [Exx] Curve and Curve ----------------------------------------*/

extern  long  pgtIT_IntCrvCrv(
                double[2], 
                PGT_CURVP, PGT_CURVP,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntCrvCrvFIT(
                double[2], double,
                PGT_CURVP, PGT_CURVP,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntCrvSelf(
                double[2], 
                PGT_CURVP,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntCrvSelfFIT(
                double[2], double,
                PGT_CURVP,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntCrvCrvR(
                double[2], 
                PGT_CURVP, PGT_CURVP, PGT_PNT,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntSegSegFIT(
                double[2], double,
                PGT_CURVP, double, double,
                PGT_CURVP, double, double,
                PGT_FLEXINTPNTSP
        );

extern  long  pgtIT_IntSubSegSegFIT(
                double[2], double,
                PGT_CURVP, double, double,
                PGT_CURVP, double, double,
                long,
                PGT_FLEXINTPNTSP
        );

extern  long  pgtIT_BoxCheckCrvCrvFIT(
                double[2], double,
                PGT_CURVP, PGT_CURVP,
                long*, PGT_BOX*, PGT_BOX*
        );

extern  long  pgtIT_BoxCheckSegSegFIT(
                double[2], double,
                PGT_CURVP, double, double, PGT_CURVP, double, double,
                long*, PGT_BOX*, PGT_BOX*
        );

extern  long  pgtIT_ApproachIntCC(
                double[2],
                PGT_PNT, PGT_CURVP, PGT_CURVP,
                PGT_PNT*, double*,
                PGT_PNT*, double*,
                double*
        );

extern  long  pgtIT_ApproachIntCCR(
                double[2],
                PGT_CURVP, PGT_CURVP, double, double,
                PGT_PNT*, double*,
                PGT_PNT*, double*,
                double*
        );

extern  long  pgtIT_AllocFlexIntpnts(
                long, long, long,
                PGT_FLEXINTPNTSP*
        );

extern  long  pgtIT_FreeFlexIntpnts(
                PGT_FLEXINTPNTSP*
        );

extern  long  pgtIT_AddIntpntToFlex(
                PGT_FLEXINTPNTSP, PGT_INTPNT
        );



/*----- [Fxx] Curve and Line -----------------------------------------*/

extern  long  pgtIT_IntCrvLin(
                double[2],
                PGT_CURVP, PGT_LINE,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntCrvLinFIT(
                double[2], double,
                PGT_CURVP, PGT_LINE,
                long*, PGT_INTPNT**
        );



/*----- [Gxx] Surface and Surface ------------------------------------*/

extern  long  pgtIT_IntSrfSrf(
                double[2],
                PGT_SURFP, PGT_SURFP,
                long*, PGT_INTCRV**
        );

extern  long  pgtIT_IntPchPch(
                double[2], 
                PGT_SURFP, double, double, double, double,
                PGT_SURFP, double, double, double, double,
                long*, PGT_INTSEG**
        );

extern  long  pgtIT_IntSubPchPch(
                double[2],
                PGT_SURFP, PGT_SURFP, long, long,
                long*, PGT_INTSEG[]
        );

extern  long  pgtIT_CalIntSegPT(
                double[2],
                PGT_SURFP, PGT_SURFP,
                long*, PGT_INTSEG*
        );

extern  long  pgtIT_IntBoundEdgSrf(
                double[2],
                PGT_SURFP, PGT_SURFP,
                long*, 
                PGT_PNT*, double*, double*, double*, double*
        );

extern  long  pgtIT_SetIntPnts4(
                double[2],
                PGT_SURFP, PGT_SURFP, 
                PGT_PNT, double, double, double, double,
                PGT_PNT, double, double, double, double,
                PGT_PNT[4], PGT_PNT[4], PGT_PNT[4]
        );

extern  long  pgtIT_DirOfIntSeg(
                double[2],
                PGT_SURFP, double, double,
                PGT_SURFP, double, double,
                PGT_VEC*, long*
        );

extern  long  pgtIT_BezPos4(
                double[3], double[3], double[3], double[3], double,
                PGT_PNT*
        );

extern  long  pgtIT_ApproachIntSS(
                double[2],
                PGT_PNT, PGT_SURFP, PGT_SURFP,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*, double*,
                double*
        );

extern  long  pgtIT_JoinIntSeg(
                double[2], double, double,
                long, PGT_INTSEG[],
                long*, PGT_INTCRV**
        );

extern  long  pgtIT_CreIntSegChain(
                double[2], double, double, 
                long, PGT_INTSEG[],
                long*, PGT_INTCHAINP**
        );

extern  long  pgtIT_MkCrvFromChain(
                double[2],
                PGT_INTCHAINP,
                PGT_CURVP*, PGT_CURVP*, PGT_CURVP*
        );


extern  long  pgtIT_BoxCheckSrfSrf(
                double[2], 
                PGT_SURFP, PGT_SURFP,
                long*, PGT_BOX*, PGT_BOX*
        );

extern  long  pgtIT_DivSurf2(
                double[2], 
                PGT_SURFP,
                PGT_SURFP*, PGT_SURFP*
        );

extern  long  pgtIT_AllocIntChain(
                long,
                PGT_INTCHAINP*
        );

extern  long  pgtIT_FreeIntChain(
                PGT_INTCHAINP*
        );




/*----- One Intersection Curve -----*/

extern  long  pgtIT_IntSrfSrfWithRefPnt(
                double[2], double,
                PGT_SURFP, PGT_SURFP, PGT_PNT,
                long*, PGT_CURVP*
        );

extern  long  pgtIT_CalStepLength(
                double[2],
                PGT_SURFP, PGT_SURFP,
                double*
        );

extern  long  pgtIT_ShiftPntToSfIntsec(
                double[2], double,
                PGT_PNT, PGT_SURFP, PGT_SURFP,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*, double*,
                long*
        );

extern  long  pgtIT_CalIntPntsChain(
                double[2], double,
                PGT_PNT, PGT_VEC, double,
                PGT_SURFP, PGT_SURFP,
                long*, PGT_PNT**, PGT_PNT**, PGT_PNT**
        );


/*----- Expand Intersection Curve -----*/

extern  long  pgtIT_ExpandIntsecCurv(
                double[2], double,
                PGT_SURFP, PGT_SURFP, PGT_CURVP, long,
                PGT_CURVP*
        );

extern  long  pgtIT_CurvFromPassPnts(
                double[2], double,
                long, PGT_PNT[],
                PGT_CURVP*
        );

extern  long  pgtIT_CurvFromPassPntsAPRX(
                double[2], double,
                long, PGT_PNT[],
                PGT_CURVP*
        );

extern  long  pgtIT_CurvFromPassPntsPLSF(
                double[2], double, double,
                PGT_PLANE, PGT_SURFP,
                long, PGT_PNT[],
                PGT_CURVP*, PGT_CURVP*, PGT_CURVP*
        );

extern  long  pgtIT_CurvFromPassPntsSFSF(
                double[2], double, double,
                PGT_SURFP, PGT_SURFP,
                PGT_ITPASSPNTSP,
                PGT_CURVP*, PGT_CURVP*, PGT_CURVP*
        );

extern  long  pgtIT_AllocPassPnts(
                long,
                PGT_ITPASSPNTSP*
        );

extern  long  pgtIT_FreePassPnts(
                PGT_ITPASSPNTSP*
        );

extern  long  pgtIT_FindSegToDividePLSF(
                double[2], double,
                PGT_SURFP, 
                PGT_ITPASSPNTSP, PGT_CURVP,
                long*
        );

extern  long  pgtIT_FindSegToDivideSFSF(
                double[2], double,
                PGT_SURFP, PGT_SURFP, 
                PGT_ITPASSPNTSP, PGT_CURVP,
                long*
        );

extern  long  pgtIT_UpdatePassPntsPLSF(
                double[2], double,
                PGT_PLANE, PGT_SURFP, 
                PGT_ITPASSPNTSP, PGT_CURVP,
                PGT_ITPASSPNTSP*
        );

extern  long  pgtIT_UpdatePassPntsSFSF(
                double[2], double,
                PGT_SURFP, PGT_SURFP, 
                PGT_ITPASSPNTSP, PGT_CURVP,
                PGT_ITPASSPNTSP*
        );

extern  long  pgtIT_MkXYZCurvFromPassPnts(
                double[2],
                PGT_ITPASSPNTSP,
                PGT_CURVP*
        );

extern  long  pgtIT_MkUVCurvFromPassPnts(
                double[2],
                PGT_ITPASSPNTSP,
                PGT_CURVP*, PGT_CURVP*
        );




/*----- [Jxx] Surface and Plane --------------------------------------*/

extern  long  pgtIT_IntPlaneSurf(
                double[2], double,
                PGT_PLANE, PGT_SURFP,
                long*,  PGT_CURVP**, PGT_CURVP**, PGT_CURVP**
        );

extern  long  pgtIT_FindInitIntposPLSF(
                double[2], double,
                PGT_PLANE, PGT_SURFP,
                long*,  PGT_ITINITPOS**
        );

extern  long  pgtIT_ShiftPntToSfIntsecPLSF(
                double[2], double,
                PGT_PNT,
                PGT_PLANE, PGT_SURFP,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*, double*,
                long*
        );

extern  long  pgtIT_RemInitIntsecPosPLSF(
                double[2], double,
                PGT_CURVP,
                long,  PGT_ITINITPOS[]
        );

extern  long  pgtIT_FindBoundCvOnPlane(
                double[2], double,
                PGT_PLANE, PGT_SURFP,
                long*, PGT_CURVP**, PGT_CURVP**, PGT_CURVP**
        );

extern  long  pgtIT_CalStepLengthPLSF(
                double[2],
                PGT_SURFP,
                double*
        );

extern  long  pgtIT_GetStartIntsecPos(
                long,  PGT_ITINITPOS[],
                long*, long*
        );

extern  long  pgtIT_CalIntPntsChainPLSF(
                double[2], double,
                PGT_PNT, PGT_VEC, PGT_PNT, double,
                PGT_PLANE, PGT_SURFP,
                long*, long*, long*, PGT_PNT**
        );

extern  long  pgtIT_FindIntsecCvEnd(
                double[2], double,
                double, PGT_PNT, PGT_PNT, PGT_PNT,
                long*, PGT_PNT*
        );

extern  long  pgtIT_MoveXYZPosAlongDir(
                double[2],
                PGT_SURFP, double, double,
                PGT_VEC, 
                long*, PGT_PNT*
        );

extern  long  pgtIT_TurnBeforeSaddlePLSF(
                double[2], double,
                double, PGT_PLANE, PGT_SURFP,
                PGT_PNT, PGT_VEC, 
                long*, PGT_PNT*, PGT_VEC*, double*, double*
        );

extern  long  pgtIT_VerifyPassPntsDegen(
                double[2], double,
                long, PGT_PNT[],
                long*
        );

extern  long  pgtIT_VerifyPassPntsDegen2(
                double[2], double,
                PGT_ITPASSPNTSP,
                long*
        );



/*----- [Kxx] Surface and Surface (Again) ----------------------------*/

extern  long  pgtIT_IntSurfSurf(
                double[2], double,
                PGT_SURFP, PGT_SURFP,
                long*,  PGT_CURVP**, PGT_CURVP**, PGT_CURVP**
        );

extern  long  pgtIT_FindInitIntposSFSF(
                double[2], double,
                PGT_SURFP, PGT_SURFP,
                long*,  PGT_ITINITPOS**
        );

extern  long  pgtIT_FindInitIntposSFSF2(
                double[2], double,
                PGT_SURFP, PGT_SURFP,
                long*,  PGT_ITINITPOS**
        );

extern  long  pgtIT_FindInitIntposPCHPCH(
                double[2], double,
                long, long,
                PGT_SURFP, PGT_SURFP,
                PGT_FLEXPNTSP
        );

extern  long  pgtIT_CalStepLengthSFSF(
                double[2],
                PGT_SURFP, PGT_SURFP,
                double*
        );

extern  long  pgtIT_CalIntPntsChainSFSF(
                double[2], double,
                PGT_PNT, PGT_VEC, PGT_PNT, double,
                PGT_SURFP, PGT_SURFP,
                long*, long*, PGT_ITPASSPNTSP*
        );

extern  long  pgtIT_RemTinySegInPassPnts(
                PGT_ITPASSPNTSP, double,
                PGT_ITPASSPNTSP*
        );

extern  long  pgtIT_SplitPassPntsAtFoldPosUV(
                double[2], double,
                PGT_ITPASSPNTSP,
                long*, PGT_ITPASSPNTSP**
        );

extern  long  pgtIT_ShiftPntToSfIntsecSFSF(
                double[2], double,
                PGT_PNT,
                PGT_SURFP, PGT_SURFP,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*, double*,
                long*
        );

extern  long  pgtIT_ShiftPntToSfIntsecSFSF2(
                double[2], double,
                PGT_PNT,
                PGT_SURFP, PGT_SURFP,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*, double*,
                long*
        );

extern  long  pgtIT_ShiftPntToSfIntsecSFSFR(
                double[2], double,
                PGT_PNT,
                PGT_SURFP, double, double, PGT_SURFP, double, double,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*, double*,
                long*
        );

extern  long  pgtIT_ShiftPntToSfIntsecSFSFR2(
                double[2], double,
                PGT_PNT,
                PGT_SURFP, double, double, PGT_SURFP, double, double,
                PGT_PNT*, double*, double*,
                PGT_PNT*, double*, double*,
                long*
        );

extern  long  pgtIT_RemInitIntsecPosSFSF(
                double[2], double,
                PGT_CURVP,
                long,  PGT_ITINITPOS[]
        );

extern  long  pgtIT_TurnBeforeSaddleSFSF(
                double[2], double,
                double, long, PGT_SURFP, PGT_SURFP,
                PGT_PNT, PGT_VEC, 
                long*, PGT_PNT*, PGT_VEC*, 
                double*, double*, double*, double*
        );



/*----- [Lxx] Surface and Curve (Again) ------------------------------*/

extern  long  pgtIT_IntCurvSurf(
                double[2], double,
                PGT_CURVP, PGT_SURFP,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_IntCurvSurf2(
                double[2], double,
                PGT_CURVP, PGT_SURFP,
                long*, PGT_INTPNT**
        );

extern  long  pgtIT_FindInitIntposCVSF(
                double[2], double,
                PGT_CURVP, PGT_SURFP,
                long*, PGT_PNT**
        );

extern  long  pgtIT_FindInitIntposCVSF2(
                double[2], double,
                PGT_CURVP, PGT_SURFP,
                long*, PGT_PNT**
        );

extern  long  pgtIT_FindInitIntposSEGPCH(
                double[2], double,
                long, long,
                PGT_CURVP, PGT_SURFP,
                PGT_FLEXPNTSP
        );

extern  long  pgtIT_ShiftPntToSfIntsecCVSF(
                double[2], double,
                PGT_PNT,
                PGT_CURVP, PGT_SURFP,
                PGT_PNT*, double*,
                PGT_PNT*, double*, double*,
                long*
        );



extern  long  pgtIT_IntTsfLin();
extern  long  pgtIT_IntTsfPln();
extern  long  pgtIT_IntTsfTsf();



/*----- [Lxx] Polyline Loops -----------------------------------------*/

extern  long  pgtIT_CalLoopIntsec(
                double[2],
                PGT_POLYLINEP, PGT_POLYLINEP,
                long*, PGT_POLYLINEP**
        );

extern  long  pgtIT_CalLoopUnion(
                double[2],
                PGT_POLYLINEP, PGT_POLYLINEP,
                long*, PGT_POLYLINEP**
        );

extern  long  pgtIT_CalLoopSubtract(
                double[2],
                PGT_POLYLINEP, PGT_POLYLINEP,
                long*, PGT_POLYLINEP**
        );

extern  long  pgtIT_MkLoopCounterclockwise(
                double[2],
                PGT_POLYLINEP, 
                PGT_POLYLINEP*
        );

extern  long  pgtIT_IntsecOnLoopLoop(
                double[2],
                PGT_POLYLINEP, PGT_POLYLINEP,
                long*, double**, double**, PGT_PNT**
        );

extern  long  pgtIT_VerifyCrossing(
                double[2],
                PGT_POLYLINEP, double, PGT_POLYLINEP,
                long*
        );

extern  long  pgtIT_MkLoopIntoFragments(
                double[2],
                PGT_POLYLINEP, long, double[],
                long*, PGT_POLYLINEP**
        );

extern  long  pgtIT_IsPolyWithinLoop(
                double[2],
                PGT_POLYLINEP, PGT_POLYLINEP,
                long*
        );

extern  long  pgtIT_JoinPolyFragsUNION(
                double[2],
                long, PGT_POLYFRAG[], long, PGT_POLYFRAG[],
                long*, PGT_POLYLINEP**
        );

extern  long  pgtIT_JoinPolyFragsSUBTRACT(
                double[2],
                long, PGT_POLYFRAG[], long, PGT_POLYFRAG[],
                long*, PGT_POLYLINEP**
        );

extern  long  pgtIT_JoinPolyFragsINTSEC(
                double[2],
                long, PGT_POLYFRAG[], long, PGT_POLYFRAG[],
                long*, PGT_POLYLINEP**
        );

extern  long  pgtIT_CorrectInOutFlag(
                long, PGT_POLYFRAG[]
        );



/*----- End of File --------------------------------------------------*/



#ifdef __cplusplus
}
#endif



#endif
