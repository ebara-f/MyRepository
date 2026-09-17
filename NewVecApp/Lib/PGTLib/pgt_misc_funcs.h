/***********************************************************************

    ä÷êîñº : [MISC HD03]  pgt_misc_funcs.h

    ã@  î\ : ÇlÇhÇrÇbÉâÉCÉuÉâÉäópÉwÉbÉ_ÉtÉ@ÉCÉã

    PGT MISC Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2023.11.23
    Modified  : Yojiro Mandachi    / GeomLab        2024.06.19
    Modified  : Hiroyuki Kitazawa  / GeomLab        2025.08.09

***********************************************************************/



#ifndef PGT_MISC_FUNCS_H
#define PGT_MISC_FUNCS_H



#include    "pgt_base_point.h"
#include    "pgt_base_curve.h"
#include    "pgt_base_surface.h"
#include    "pgt_misc_struct.h"



#ifdef __cplusplus
extern "C"{
#endif



/*----- A : Min Max Box ----------------------------------------------*/

extern  long  pgtSC_MMBoxForPnts(
                double, long, PGT_PNT[],
                PGT_BOX*
        );

extern  long  pgtSC_MMBoxForElmPnts(
                double, long, PGT_ELMPNT[],
                PGT_BOX*
        );

extern  long  pgtSC_MMBoxForLine(
                double, PGT_LINE,
                PGT_BOX*
        );

extern  long  pgtSC_MMBoxForLine2D(
                double, PGT_LINE,
                PGT_BOX*
        );

extern  long  pgtSC_MMBoxForLinePT(
                double, double[3], double[3],
                double[3], double[3]
        );

extern  long  pgtSC_MMBoxForPolyline(
                double, PGT_POLYLINEP,
                PGT_BOX*
        );

extern  long  pgtSC_MMBoxForCircle2D(
                double, PGT_CIRCLE,
                PGT_BOX*
        );

extern  long  pgtSC_MMBoxForTriangle(
                double, PGT_TRIANGLE,
                PGT_BOX*
        );

extern  long  pgtSC_MMBoxForTris(
                double, long, PGT_TRIANGLE[],
                PGT_BOX*
        );

extern  long  pgtSC_IntPntBox(
                double[3], PGT_BOX,
                long*
        );

extern  long  pgtSC_IntPntBox2D(
                double[3], double[3], double[3],
                long*
        );

extern  long  pgtSC_IntBoxBox(
                PGT_BOX, PGT_BOX,
                long*
        );

extern  long  pgtSC_IntBoxBox2D(
                double[3], double[3], double[3], double[3],
                long*
        );

extern  long  pgtSC_IntBoxBoxPT(
                double[3], double[3], double[3], double[3],
                long*
        );

extern  long  pgtSC_IntLinBox(
                double[2],
                PGT_LINE, PGT_BOX,
                long*
        );

extern  long  pgtSC_IntRayBox2D(
                double[2],
                PGT_LINE, PGT_BOX,
                long*
        );

extern  long  pgtSC_IsPntOnLeft2D(
                double[2],
                PGT_PNT, PGT_LINE,
                long*, long*
        );

extern  long  pgtSC_ExpandBox(
                double, PGT_BOX,
                PGT_BOX*
        );

extern  long  pgtSC_ExpandBoxPT(
                double, double[3], double[3],
                double[3], double[3]
        );

extern  long  pgtSC_IsBoxDegenerate(
                PGT_BOX, double,
                long*
        );

extern  long  pgtSC_BoxCenter(
                PGT_BOX,
                double[3]
        );

extern  long  pgtSC_BoxBoxAND(
                PGT_BOX, PGT_BOX,
                long*, PGT_BOX*
        );

extern  long  pgtSC_BoxSize(
                PGT_BOX,
                double*, double*, double*
        );



/*----- B : Line / Polyline ------------------------------------------*/

extern  long  pgtSC_LinVect(
                double[2],
                PGT_LINE, double,
                PGT_PNT*, PGT_VEC*
        );

extern  long  pgtSC_IntLinLin(
                double[2],
                PGT_LINE, PGT_LINE,
                long*, PGT_PNT*, double*, PGT_PNT*, double*, double*
              );

extern  long  pgtSC_IntLinLin2D(
                double[2],
                PGT_LINE, PGT_LINE,
                long*, double[2], double[2], PGT_PNT[2]
        );

extern  long  pgtSC_IntLinLinPT(
                double[2], double,
                double[3], double[3], double[3], double[3],
                long*, double[2], double[2], double[2][3]
        );

extern  long  pgtSC_IntLinRay2D(
                double[2],
                PGT_LINE, PGT_LINE,
                long*, double[2], double[2], PGT_PNT[2]
        );

extern  long  pgtSC_ClsPntOnLine(
                double[2],
                PGT_PNT, PGT_LINE,
                PGT_PNT*, double*, double*
        );

extern  long  pgtSC_ClsPntOnLine2D(
                double[2],
                double[3], PGT_LINE,
                double[3], double*, double*
        );

extern  long  pgtSC_ClsPntOnLinePT(
                double[2],
                double[3], double[3], double[3],
                double*, double[3], double*
        );

extern  long  pgtSC_ClsPntToPolyline(
                double[2],
                PGT_PNT, PGT_POLYLINEP,
                PGT_PNT*, double*, double*
        );

extern  long  pgtSC_IntPolyPoly(
                double[2], double,
                PGT_POLYLINEP, PGT_POLYLINEP,
                long*, double**, double**, PGT_PNT**
        );

extern  long  pgtSC_IntPolySelf(
                double[2], double,
                PGT_POLYLINEP,
                long*, double**, double**, PGT_PNT**
        );

extern  long  pgtSC_PolyLoopArea2D(
                double[2],
                PGT_POLYLINEP,
                double*
        );

extern  long  pgtSC_IsPntInPolyLoop(
                double[2],
                double, double, PGT_POLYLINEP,
                long*, long*, long*
        );

extern  long  pgtSC_IsPntInPolyLoopOVERLAP(
                double[2], double,
                double, double, PGT_POLYLINEP,
                long*
        );

extern  long  pgtSC_IntLoopLoop(
                double[2],
                PGT_POLYLINEP, PGT_POLYLINEP,
                long*
        );

extern  long  pgtSC_IsPolyAWithinB(
                double[2],
                PGT_POLYLINEP, PGT_POLYLINEP,
                long*
        );

extern  long  pgtSC_IsPolyAWithinBOVERLAP(
                double[2], double,
                PGT_POLYLINEP, PGT_POLYLINEP,
                long*
        );

extern  long  pgtSC_PolyVect(
                double[2],
                PGT_POLYLINEP, double,
                PGT_PNT*, PGT_VEC*
        );

extern  long  pgtSC_PolyLengthFull(
                PGT_POLYLINEP,
                double*
        );

extern  long  pgtSC_GapPolyPoly(
                double[2],
                PGT_POLYLINEP, PGT_POLYLINEP,
                double*, double*, double*
        );

extern  long  pgtSC_GapLineLinePT(
                double[2],
                double[3], double[3], double[3], double[3],
                double*, double*, double*
        );



/*----- C : Circle / Ellipse -----------------------------------------*/

extern  long  pgtSC_CirVect(
                double[2],
                PGT_CIRCLE, double,
                PGT_PNT*, PGT_VEC*
        );

extern  long  pgtSC_ClsPntToCircle(
                double[2],
                PGT_PNT, PGT_CIRCLE,
                PGT_PNT*, double*, double*
        );

extern  long  pgtSC_ClsPntOnCircle2D(
                double[2],
                double[3], PGT_CIRCLE,
                double[3], double*, double*, long*
        );

extern  long  pgtSC_IntCirCir2D(
                double[2],
                PGT_CIRCLE, PGT_CIRCLE,
                long*, double[2], double[2], PGT_PNT[2]
        );

extern  long  pgtSC_IntCirLin2D(
                double[2],
                PGT_CIRCLE, PGT_LINE,
                long*, double[2], double[2], PGT_PNT[2]
        );

extern  long  pgtSC_IntCirRay2D(
                double[2],
                PGT_CIRCLE, PGT_LINE,
                long*, double[2], double[2], PGT_PNT[2]
        );

extern  long  pgtSC_ElpVect(
                double[2],
                PGT_ELLIPSE, double,
                PGT_PNT*, PGT_VEC*
        );

extern  long  pgtSC_ClsPntToEllipse(
                double[2],
                PGT_PNT, PGT_ELLIPSE,
                PGT_PNT*, double*, double*
        );



/*----- D : Plane ----------------------------------------------------*/

extern  long  pgtSC_PlaneOnTriangle(
                double[2],
                double[3], double[3], double[3],
                PGT_PLANE*
        );

extern  long  pgtSC_ClsPntOnPlane(
                double[2],
                double[3], PGT_PLANE,
                double[3], double*, double*, double*
        );

extern  long  pgtSC_IntLinePlanePT(
                double[2],
                double[3], double[3], PGT_PLANE,
                double[3], double*, double*, double*, long*
        );

extern  long  pgtSC_IntLinePlane(
                double[2],
                PGT_LINE, PGT_PLANE,
                PGT_PNT*, double*, double*, double*, long*
        );

extern  long  pgtSC_IntPlanePlane(
                double[2],
                PGT_PLANE, PGT_PLANE,
                long*, PGT_LINE*
        );

extern  long  pgtSC_IntPlanePlanePT(
                double[2],
                double[3], double[3], double[3], double[3],
                long*, double[3], double[3]
        );

extern  long  pgtSC_IntPolyPlane(
                double[2], double,
                PGT_POLYLINEP, PGT_PLANE,
                long*, double**, PGT_PNT**
        );

extern  long  pgtSC_PlnVect(
                double[2],
                PGT_PLANE, double, double,
                PGT_PNT*, PGT_VEC*
        );

extern  long  pgtSC_PlaneOnPnts(
                double[2],
                long, PGT_PNT[],
                PGT_PLANE*
        );

extern  long  pgtSC_PntsGravityCenter(
                long, PGT_PNT[],
                double[3]
        );

extern  long  pgtSC_PntsPrincipalAxis(
                double[2],
                long, PGT_PNT[],
                double[3], double[3], double[3]
        );

extern  long  pgtSC_NormalDirOnPnts(
                double[2],
                long, PGT_PNT[],
                PGT_PNT*, PGT_VEC*, long*
        );



/*----- E : Triangle -------------------------------------------------*/

extern  long  pgtSC_InterfBetTriangles(
                double[2], double,
                double[3], double[3], double[3],
                double[3], double[3], double[3],
                long*
        );

extern  long  pgtSC_InterfBetTriangles2(
                double[2],
                double[3], double[3], double[3],
                double[3], double[3], double[3],
                long*, double[3]
        );

extern  long  pgtSC_IsPntInTriangle(
                double[2],
                double[3], double[3], double[3], double[3],
                long*
        );

extern  long  pgtSC_IsPntInTriangle2D(
                double[2],
                double[3], double[3], double[3], double[3],
                long*, long*
        );

extern  long  pgtSC_IsPntOnTriangleEdge(
                double[2],
                double[3], double[3], double[3], double[3],
                long*
        );

extern  long  pgtSC_IsPntNearTriangle(
                double[2], double,
                double[3], double[3], double[3], double[3],
                long*
        );

extern  long  pgtSC_TriMeshFromPolys(
                long, PGT_POLYLINEP[],
                long*, PGT_TRIANGLE**
        );

extern  long  pgtSC_ExpandTriangle(
                double[2],
                double, double[3], double[3], double[3],
                double[3], double[3], double[3]
        );

extern  long  pgtSC_IntTriLin(
                double[2],
                PGT_TRIANGLE, PGT_LINE,
                long*, PGT_PNT*, double*, long*
        );

extern  long  pgtSC_IntTriRay(
                double[2],
                PGT_TRIANGLE, PGT_PNT, PGT_VEC,
                long*, long*, PGT_PNT*
        );

extern  long  pgtSC_IntTriTri(
                double[2],
                PGT_TRIANGLE, PGT_TRIANGLE,
                long*, PGT_PNT*, PGT_PNT*
        );

extern  long  pgtSC_TriGravityCenter(
                double[3], double[3], double[3],
                double[3]
        );

extern  long  pgtSC_TriInnerCircle(
                double[2],
                double[3], double[3], double[3],
                double[3], double*
        );

extern  long  pgtSC_TriOuterCircle(
                double[2],
                double[3], double[3], double[3],
                double[3], double*
        );

extern  long  pgtSC_TriArea(
                double[3], double[3], double[3],
                double*
        );

extern  long  pgtSC_IntTriBox(
                double[2],
                PGT_TRIANGLE, PGT_BOX,
                long*
        );

extern  long  pgtSC_IntTriBox2(
                double[2],
                PGT_TRIANGLE, PGT_BOX, PGT_PLANE,
                long*
        );

extern  long  pgtSC_NonInterfBetTriangles(
                double[2], double,
                double[3], double[3], double[3],
                double[3], double[3], double[3],
                long*
        );

extern  long  pgtSC_ClsPntToTriangle(
                double[2],
                PGT_PNT, PGT_TRIANGLE,
                PGT_PNT*, double*, long*, long*, long*
        );

extern  long  pgtSC_ClsPntToTriangleBND(
                double[2], double,
                PGT_PNT, PGT_TRIANGLE,
                PGT_PNT*, double*, long*
        );

extern  long  pgtSC_IsTriangleDegenerate(
                double[2], double,
                PGT_PNT, PGT_PNT, PGT_PNT,
                long*
        );

extern  long  pgtSC_PntsOnTriangle(
                double[2],
                PGT_TRIANGLE, double,
                long*, PGT_PNT**
        );



/*----- F : Points Tree ----------------------------------------------*/

extern  long  pgtSC_CrePntsTree(
                double[2],
                long, PGT_ELMPNT[],
                PGT_PNTSTREEP*
        );

extern  long  pgtSC_GrowPntsTree(
                double[2],
                long, PGT_ELMPNT[], PGT_BOX,
                PGT_PTNODEP
        );

extern  long  pgtSC_AllocPntsTree(
                PGT_PNTSTREEP*
        );

extern  long  pgtSC_FreePntsTree(
                PGT_PNTSTREEP*
        );

extern  long  pgtSC_AllocPntsTreeNode(
                PGT_PTNODEP*
        );

extern  long  pgtSC_FreePntsTreeNode(
                PGT_PTNODEP*
        );

extern  long  pgtSC_GetPntsFromTree(
                double[2],
                PGT_PNTSTREEP, PGT_BOX,
                long*, PGT_ELMPNT**
        );

extern  long  pgtSC_GetPntsOnBranch(
                PGT_PTNODEP,
                long*, PGT_ELMPNT**
        );

extern  long  pgtSC_GetPntsFromTreeFLEX(
                double[2],
                PGT_PNTSTREEP, PGT_BOX,
                PGT_FLEXPNTSP
        );

extern  long  pgtSC_GetPntsOnBranchFLEX(
                PGT_PTNODEP,
                PGT_FLEXPNTSP
        );

extern  long  pgtSC_AllocFlexPnts(
                long, long, long,
                PGT_FLEXPNTSP*
        );

extern  long  pgtSC_FreeFlexPnts(
                PGT_FLEXPNTSP*
        );

extern  long  pgtSC_AddPntToFlex(
                PGT_FLEXPNTSP, PGT_ELMPNT
        );

extern  long  pgtSC_ThinPntsCloud(
                double[2], double,
                long, PGT_ELMPNT[],
                long*, PGT_ELMPNT**
        );

extern  long  pgtSC_ThinPntsCloudCENT(
                double[2], double,
                long, PGT_ELMPNT[],
                long*, PGT_ELMPNT**
        );

extern  long  pgtSC_DecimatePoints(
                double[2], double,
                long, PGT_PNT[],
                long*, PGT_PNT**
        );

extern  long  pgtSC_CreNodeAsLeafTHIN(
                long, PGT_ELMPNT[], PGT_BOX,
                PGT_PTNODEP
        );

extern  long  pgtSC_CreNodeAsBranchTHIN(
                double,
                long, PGT_ELMPNT[], PGT_BOX,
                PGT_PTNODEP
        );

extern  long  pgtSC_GetPntsOnBranchTHIN(
                PGT_PTNODEP,
                long*, PGT_ELMPNT**
        );

extern  long  pgtSC_GetPntsOnBranchTHIN2(
                PGT_PTNODEP,
                long*, PGT_ELMPNT**
        );

extern  long  pgtSC_SortElmPntBySortF(
                long, PGT_ELMPNT[]
        );

extern  long  pgtSC_AnalyzePoints(
                double[2],
                long, PGT_PNT[],
                PGT_BOX*, double*, double*
        );

extern  long  pgtSC_AveDistAmongPnts(
                double[2],
                double, long, PGT_PNT[],
                long*, double*, double*
        );



/*----- G : Triangle Tree --------------------------------------------*/

extern  long  pgtSC_CreTrisTree(
                double[2],
                long, PGT_TRIANGLE[],
                PGT_TRISTREEP*
        );

extern  long  pgtSC_GrowTrisTree(
                double[2],
                long, PGT_TRIANGLE[], PGT_BOX,
                PGT_TRISTREEP
        );

extern  long  pgtSC_CreNodeAsLeaf(
                double[2],
                long, PGT_TRIANGLE[], PGT_BOX,
                PGT_TRISTREEP
        );

extern  long  pgtSC_CreNodeAsBranch(
                double[2],
                long, PGT_TRIANGLE[], PGT_BOX,
                PGT_TRISTREEP
        );

extern  long  pgtSC_AllocTrisTree(
                long, PGT_TRISTREEP*
        );

extern  long  pgtSC_FreeTrisTree(
                PGT_TRISTREEP*
        );

extern  long  pgtSC_GetBoxInterfTris(
                double[2],
                PGT_TRISTREEP, PGT_BOX,
                long*, PGT_TRIANGLE**
        );

extern  long  pgtSC_GetBoxInterfTrisFLEX(
                double[2],
                PGT_TRISTREEP, PGT_BOX,
                PGT_FLEXTRISP
        );

extern  long  pgtSC_GetBoxInterfTris2(
                double[2],
                PGT_TRISTREEP, PGT_BOX, long, PGT_PLANEP*,
                PGT_FLEXTRISP
        );

extern  long  pgtSC_GetTrisOnBranch(
                PGT_TRISTREEP,
                long*, PGT_TRIANGLE**
        );

extern  long  pgtSC_GetTrisOnBranchFLEX(
                PGT_TRISTREEP,
                PGT_FLEXTRISP
        );

extern  long  pgtSC_GetTrisOnBranch2(
                PGT_TRISTREEP,
                PGT_FLEXTRISP
        );

extern  long  pgtSC_AllocFlexTris(
                long, long, long,
                PGT_FLEXTRISP*
        );

extern  long  pgtSC_FreeFlexTris(
                PGT_FLEXTRISP*
        );

extern  long  pgtSC_AddTriToFlex(
                PGT_FLEXTRISP, PGT_TRIANGLE
        );



/*----- Domain -------------------------------------------------------*/

extern  long  pgtSC_AllocPolyDM(
                long, 
                PGT_POLYDMP*
        );

extern  long  pgtSC_FreePolyDM(
                PGT_POLYDMP*
        );

extern  long  pgtSC_CopyPolyDM(
                PGT_POLYDMP,
                PGT_POLYDMP*
        );

extern  long  pgtSC_FindPolyDMs(
                double[2],
                long, PGT_POLYLINEP[],
                long*, PGT_POLYDMP**
        );

extern  long  pgtSC_FindPolyDMsOVERLAP(
                double[2], double,
                long, PGT_POLYLINEP[],
                long*, PGT_POLYDMP**
        );

extern  long  pgtSC_IsPntInPolyDM(
                double[2],
                PGT_POLYDMP, double, double,
                long*
        );

extern  long  pgtSC_IsPntInPolyDMs(
                double[2],
                long, PGT_POLYDMP[], double, double,
                long*
        );



/*----- Bit Array ----------------------------------------------------*/

extern  long  pgtSC_IsBitON(
                PGT_BITARYP, PGT_LONG8,
                long*
        );

extern  long  pgtSC_SetBitON(
                PGT_LONG8, PGT_BITARYP
        );

extern  long  pgtSC_SetBitONALL(
                PGT_BITARYP
        );

extern  long  pgtSC_SetBitOFFALL(
                PGT_BITARYP
        );

extern  long  pgtSC_AllocBitArray(
                PGT_LONG8,
                PGT_BITARYP*
        );

extern  long  pgtSC_FreeBitArray(
                PGT_BITARYP*
        );



/*----- T Part Boolean -----------------------------------------------*/

extern  long  pgtSC_UniteTPartAandB(
                double[2],
                PGT_TPART, PGT_TPART,
                long*, PGT_TPART[2]
        );

extern  long  pgtSC_SubtractTPartBfromA(
                double[2],
                PGT_TPART, PGT_TPART,
                long*, PGT_TPART[2]
        );

extern  long  pgtSC_IntersectTPartAandB(
                double[2],
                PGT_TPART, PGT_TPART,
                long*, PGT_TPART*
        );

extern  long  pgtSC_UniteTPartsMULT(
                double[2],
                long, PGT_TPART[],
                long*, PGT_TPART**
        );

extern  long  pgtSC_SubtractTPartsMULT(
                double[2],
                long, PGT_TPART[], long, PGT_TPART[],
                long*, PGT_TPART**
        );

extern  long  pgtSC_IntersectTPartsMULT(
                double[2],
                long, PGT_TPART[], long, PGT_TPART[],
                long*, PGT_TPART**
        );

extern  long  pgtSC_AllocFlexTParts(
                long, long, long,
                PGT_FLEXTPRSP*
        );

extern  long  pgtSC_FreeFlexTParts(
                PGT_FLEXTPRSP*
        );

extern  long  pgtSC_AddTPartToFlex(
                PGT_FLEXTPRSP, PGT_TPART
        );



/*----- H : Read/Write -----------------------------------------------*/

extern  long  pgtSC_ReadRecordFP(
                FILE*, long,
                char[], long*
        );

extern  long  pgtSC_WriteLine(
                char[],
                PGT_LINE
        );

extern  long  pgtSC_ReadLine(
                char[],
                PGT_LINE*
        );

extern  long  pgtSC_WriteLineFP(
                FILE*,
                PGT_LINE
        );

extern  long  pgtSC_ReadLineFP(
                FILE*,
                PGT_LINE*
        );

extern  long  pgtSC_WriteCircle(
                char[],
                PGT_CIRCLE
        );

extern  long  pgtSC_ReadCircle(
                char[],
                PGT_CIRCLE*
        );

extern  long  pgtSC_WriteCircleFP(
                FILE*,
                PGT_CIRCLE
        );

extern  long  pgtSC_ReadCircleFP(
                FILE*,
                PGT_CIRCLE*
        );

extern  long  pgtSC_WriteEllipse(
                char[],
                PGT_ELLIPSE
        );

extern  long  pgtSC_ReadEllipse(
                char[],
                PGT_ELLIPSE*
        );

extern  long  pgtSC_WriteEllipseFP(
                FILE*,
                PGT_ELLIPSE
        );

extern  long  pgtSC_ReadEllipseFP(
                FILE*,
                PGT_ELLIPSE*
        );

extern  long  pgtSC_WriteParabolaFP(
                FILE*,
                PGT_PARABOLA
        );

extern  long  pgtSC_ReadParabolaFP(
                FILE*,
                PGT_PARABOLA*
        );

extern  long  pgtSC_WriteHyperbolaFP(
                FILE*,
                PGT_HYPERBOLA
        );

extern  long  pgtSC_ReadHyperbolaFP(
                FILE*,
                PGT_HYPERBOLA*
        );

extern  long  pgtSC_WritePlane(
                char*, PGT_PLANE
        );

extern  long  pgtSC_ReadPlane(
                char*,
                PGT_PLANE*
        );

extern  long  pgtSC_WritePlaneFP(
                FILE*, PGT_PLANE
        );

extern  long  pgtSC_ReadPlaneFP(
                FILE*,
                PGT_PLANE*
        );

extern  long  pgtSC_WritePnts(
                char[], long, PGT_PNT[]
        );

extern  long  pgtSC_ReadPnts(
                char[],
                long*, PGT_PNT**
        );

extern  long  pgtSC_WriteBox(
                char[], PGT_BOX
        );

extern  long  pgtSC_ReadBox(
                char[],
                PGT_BOX*
        );

extern  long  pgtSC_WriteCodSys(
                char[], PGT_CODSYS
        );

extern  long  pgtSC_WriteCodSysFP(
                FILE*, PGT_CODSYS
        );

extern  long  pgtSC_ReadCodSys(
                char[],
                PGT_CODSYS*
        );

extern  long  pgtSC_ReadCodSysFP(
                FILE*,
                PGT_CODSYS*
        );



/*----- I :  Others --------------------------------------------------*/

extern  long  pgtSC_MovePnt(
                PGT_PNT, double[4][4],
                PGT_PNT*
        );

extern  long  pgtSC_MoveVec(
                PGT_VEC, double[4][4],
                PGT_VEC*
        );

extern  long  pgtSC_MoveCodSys(
                PGT_CODSYS, double[4][4],
                PGT_CODSYS*
        );

extern  long  pgtSC_MoveTriangle(
                PGT_TRIANGLE, double[4][4],
                PGT_TRIANGLE*
        );

extern  long  pgtSC_AllocFlexInts(
                long, long, long,
                PGT_FLEXINTSP*
        );

extern  long  pgtSC_FreeFlexInts(
                PGT_FLEXINTSP*
        );

extern  long  pgtSC_AddIntToFlex(
                PGT_FLEXINTSP, long
        );

extern  long  pgtSC_AllocFlexFlts(
                long, long, long,
                PGT_FLEXFLTSP*
        );

extern  long  pgtSC_FreeFlexFlts(
                PGT_FLEXFLTSP*
        );

extern  long  pgtSC_AddFltToFlex(
                PGT_FLEXFLTSP, float
        );

extern  long  pgtSC_AllocFlexDbls(
                long, long, long,
                PGT_FLEXDBLSP*
        );

extern  long  pgtSC_FreeFlexDbls(
                PGT_FLEXDBLSP*
        );

extern  long  pgtSC_AddDblToFlex(
                PGT_FLEXDBLSP, double
        );

extern  long  pgtSC_AllocFlexPtrs(
                long, long, long,
                PGT_FLEXPTRSP*
        );

extern  long  pgtSC_FreeFlexPtrs(
                PGT_FLEXPTRSP*
        );

extern  long  pgtSC_AddPtrToFlex(
                PGT_FLEXPTRSP, void*
        );

extern  long  pgtSC_CalFitMatrixForPntsPair(
                double[2], double,
                long, PGT_PNT[], PGT_PNT[], long,
                double[4][4]
        );



/*----- J :  Set and Get Color ---------------------------------------*/

extern  long  pgtSC_SetRGBIntoICOLOR(
                long, long, long,
                long*
        );

extern  long  pgtSC_GetRGBFromICOLOR(
                long,
                long*, long*, long*, long*
        );



/*----- K : Elements Tree --------------------------------------------*/


extern  long  pgtSC_CreElmsTree(
                    double[2],
                    long, PGT_ELEMENT[],
                    PGT_ELMSTREEP*
        );

extern  long  pgtSC_GrowElmsTree(
                    double[2],
                    long, PGT_ELEMENT[], PGT_BOX,
                    PGT_ELMSTREEP
        );

extern  long  pgtSC_ElmsNodeAsLeaf(
                    double[2],
                    long, PGT_ELEMENT[], PGT_BOX,
                    PGT_ELMSTREEP
        );

extern  long  pgtSC_ElmsNodeAsBranch(
                    double[2],
                    long, PGT_ELEMENT[], PGT_BOX,
                    PGT_ELMSTREEP
        );

extern  long  pgtSC_AllocElmsTree(
                    long,
                    PGT_ELMSTREEP*
        );

extern  long  pgtSC_FreeElmsTree(
                    PGT_ELMSTREEP*
        );

extern  long  pgtSC_GetBoxInterfElms(
                    double[2],
                    PGT_ELMSTREEP, PGT_BOX,
                    long*, PGT_ELEMENT**
        );

extern  long  pgtSC_GetElmsOnBranch(
                    PGT_ELMSTREEP,
                    long*, PGT_ELEMENT**
        );

extern  long  pgtSC_GetBoxInterfElmsFLEX(
                    double[2],
                    PGT_ELMSTREEP, PGT_BOX,
                    PGT_FLEXELMSP
        );

extern  long  pgtSC_GetElmsOnBranchFLEX(
                    PGT_ELMSTREEP,
                    PGT_FLEXELMSP
        );

extern  long  pgtSC_AllocFlexElms(
                    long, long, long,
                    PGT_FLEXELMSP*
        );

extern  long  pgtSC_FreeFlexElms(
                    PGT_FLEXELMSP*
        );

extern  long  pgtSC_AddElmToFlex(
                    PGT_FLEXELMSP, PGT_ELEMENT
        );



/*----- Complex Number -----------------------------------------------*/

extern  long  pgtSC_ComplexAbs(
                    PGT_COMPLEX,
                    double*
        );

extern  long  pgtSC_ComplexAdd(
                    PGT_COMPLEX, PGT_COMPLEX,
                    PGT_COMPLEX*
        );

extern  long  pgtSC_ComplexSub(
                    PGT_COMPLEX, PGT_COMPLEX,
                    PGT_COMPLEX*
        );

extern  long  pgtSC_ComplexMul(
                    PGT_COMPLEX, PGT_COMPLEX,
                    PGT_COMPLEX*
        );

extern  long  pgtSC_ComplexDiv(
                    PGT_COMPLEX, PGT_COMPLEX,
                    PGT_COMPLEX*
        );

extern  long  pgtSC_ComplexPow(
                    PGT_COMPLEX, double,
                    PGT_COMPLEX*
        );



/*----- Equation Solver ----------------------------------------------*/

extern  long  pgtSC_SolveQuadratic(
                    double,
                    double, double, double,
                    long*, double[2]
        );

extern  long  pgtSC_SolveQuadratic2(
                    double,
                    double, double, double,
                    long*, PGT_COMPLEX[2]
        );

extern  long  pgtSC_SolveQuadratic3(
                    double,
                    PGT_COMPLEX, PGT_COMPLEX, PGT_COMPLEX,
                    long*, double[2]
        );

extern  long  pgtSC_SolveCubic(
                    double,
                    double, double, double, double,
                    long*, double[3]
        );

extern  long  pgtSC_SolveCubic2(
                    double,
                    double, double, double, double,
                    long*, PGT_COMPLEX[3]
        );

extern  long  pgtSC_SolveQuartic(
                    double,
                    double, double, double, double, double,
                    long*, double[4]
        );




/*----- End of File --------------------------------------------------*/



#ifdef __cplusplus
}
#endif



#endif
