/***********************************************************************

    関数名 : [BASE HD05]  pgt_base_funcs.h

    機  能 : ＢＡＳＥライブラリ用ヘッダファイル
             関数プロトタイプ宣言

    PGT BASE Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2025.08.09

***********************************************************************/



#ifndef PGT_BASE_FUNCS_H
#define PGT_BASE_FUNCS_H



#include    "pgt_base_point.h"
#include    "pgt_base_curve.h"
#include    "pgt_base_surface.h"



#ifdef __cplusplus
extern "C"{
#endif



/*--------------------------------------------------------------------*/
/*     BASE PT Axx : Points(Polyline)                                 */
/*--------------------------------------------------------------------*/

/*----- PT Axx : Alloc, Free, Copy -----------------------------------*/

extern  long  pgtNC_AllocPolyline(
                long, 
                PGT_POLYLINEP*
        );

extern  long  pgtNC_FreePolyline(
                PGT_POLYLINEP*
        );

extern  long  pgtNC_CopyPolyline(
                PGT_POLYLINEP,
                PGT_POLYLINEP*
        );

extern  long  pgtNC_ReversePolyline(
                PGT_POLYLINEP,
                PGT_POLYLINEP*
        );

extern  long  pgtNC_AllocFlexPolys(
                long, long, long,
                PGT_FLEXPOLYSP*
        );

extern  long  pgtNC_FreeFlexPolys(
                PGT_FLEXPOLYSP*
        );

extern  long  pgtNC_AddPolyToFlex(
                PGT_FLEXPOLYSP, PGT_ELMPOLY
        );

extern  long  pgtNC_PolyVect(
                double[2],
                PGT_POLYLINEP, double,
                PGT_PNT*, PGT_VEC*
        );

extern  long  pgtNC_TrimPolyline(
                double[2],
                PGT_POLYLINEP, double, double,
                PGT_POLYLINEP*
        );



/*----- PT Bxx : Move  -----------------------------------------------*/

extern  long  pgtNC_MovePolyline(
                double[2],
                PGT_POLYLINEP, double[4][4],
                PGT_POLYLINEP*
        );

extern  long  pgtNC_ShiftPolyline(
                double[2],
                PGT_POLYLINEP, double[3],
                PGT_POLYLINEP*
        );


/*----- PT Cxx : Operation -------------------------------------------*/

extern  long  pgtNC_RemTinySegInPoly(
                PGT_POLYLINEP, double,
                PGT_POLYLINEP*
        );

extern  long  pgtNC_BrkIntoG1Polys(
                double[2],
                PGT_POLYLINEP, double,
                long*, PGT_POLYLINEP**
        );

extern  long  pgtNC_ConcatTwoPolys(
                double[2],
                PGT_POLYLINEP, PGT_POLYLINEP,
                PGT_POLYLINEP*
        );

extern  long  pgtNC_ConcatPolyAry(
                double[2],
                long, PGT_POLYLINEP[],
                PGT_POLYLINEP*
        );


/*----- PT Dxx : File I/O --------------------------------------------*/

/*----- Ascii -----*/

extern  long  pgtNC_WritePolyline(
                char*, PGT_POLYLINEP
        );

extern  long  pgtNC_WritePolylineFP(
                FILE*, PGT_POLYLINEP
        );

extern  long  pgtNC_ReadPolyline(
                char*,
                PGT_POLYLINEP*
        );

extern  long  pgtNC_ReadPolylineFP(
                FILE*,
                PGT_POLYLINEP*
        );

extern  long  pgtNC_ReadRecordFP(
                FILE*, long, 
                char[], long*
        );

extern  long  pgtNC_WritePolylineArray(
                char*, long, PGT_POLYLINEP[]
        );

extern  long  pgtNC_ReadPolylineArray(
                char*,
                long*, PGT_POLYLINEP**
        );

/*----- Binary -----*/
extern  long  pgtNC_WritePolylineBIN(
                char*, PGT_POLYLINEP
        );

extern  long  pgtNC_WritePolylineBINFP(
                FILE*, PGT_POLYLINEP
        );

extern  long  pgtNC_ReadPolylineBIN(
                char*,
                PGT_POLYLINEP*
        );

extern  long  pgtNC_ReadPolylineBINFP(
                FILE*,
                PGT_POLYLINEP*
        );

extern  long  pgtNC_ReadBinaryFP(
                FILE*, size_t, size_t, 
                void*, long*
        );




/*--------------------------------------------------------------------*/
/*     BASE NC Axx : Curve  Alloc/Free/Copy                           */
/*--------------------------------------------------------------------*/

/*----- Alloc, Free, Copy --------------------------------------------*/
extern  long  pgtNC_AllocCurv(
                long, long,
                PGT_CURVP*
        );

extern  long  pgtNC_FreeCurv(
                PGT_CURVP*
        );

extern  long  pgtNC_CopyCurv(
                PGT_CURVP,
                PGT_CURVP*
        );

extern  long  pgtNC_AllocFlexCurvs(
                long, long, long,
                PGT_FLEXCURVSP*
        );

extern  long  pgtNC_FreeFlexCurvs(
                PGT_FLEXCURVSP*
        );

extern  long  pgtNC_AddCurvToFlex(
                PGT_FLEXCURVSP, PGT_ELMCURV
        );

extern  long  pgtNC_AllocLine(
                PGT_LINEP*
        );

extern  long  pgtNC_FreeLine(
                PGT_LINEP*
        );

extern  long  pgtNC_CopyLine(
                PGT_LINEP,
                PGT_LINEP*
        );

extern  long  pgtNC_AllocCircle(
                PGT_CIRCLEP*
        );

extern  long  pgtNC_FreeCircle(
                PGT_CIRCLEP*
        );

extern  long  pgtNC_CopyCircle(
                PGT_CIRCLEP,
                PGT_CIRCLEP*
        );

extern  long  pgtNC_AllocEllipse(
                PGT_ELLIPSEP*
        );

extern  long  pgtNC_FreeEllipse(
                PGT_ELLIPSEP*
        );

extern  long  pgtNC_CopyEllipse(
                PGT_ELLIPSEP,
                PGT_ELLIPSEP*
        );

extern  long  pgtNC_AllocParabola(
                PGT_PARABOLAP*
        );

extern  long  pgtNC_FreeParabola(
                PGT_PARABOLAP*
        );

extern  long  pgtNC_CopyParabola(
                PGT_PARABOLAP,
                PGT_PARABOLAP*
        );

extern  long  pgtNC_AllocHyperbola(
                PGT_HYPERBOLAP*
        );

extern  long  pgtNC_FreeHyperbola(
                PGT_HYPERBOLAP*
        );

extern  long  pgtNC_CopyHyperbola(
                PGT_HYPERBOLAP,
                PGT_HYPERBOLAP*
        );


/*----- Underlying DeBoor Cox Work Area ------------------------------*/

extern  long  pgtNC_AllocCvDBR(
                long, long,
                PGT_CVDEBOORP*
        );

extern  long  pgtNC_FreeCvDBR(
                PGT_CVDEBOORP*
        );

extern  long  pgtNC_AttachCvDBR(
                PGT_CURVP,
                long*
        );


/*----- Underlying Polynomial Curve ----------------------------------*/

extern  long  pgtNC_AllocPLCurv(
                long, long,
                PGT_PLCURVP*
        );

extern  long  pgtNC_FreePLCurv(
                PGT_PLCURVP*
        );


/*----- Underlying Analytical Expression -----------------------------*/

extern  long  pgtNC_FreeCvGeom(
                PGT_CVGEOM*
        );



/*--------------------------------------------------------------------*/
/*     BASE NC Bxx : Vector on Curve                                  */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_CvVect(
                double[2],
                PGT_CURVP, double, long,
                PGT_PNT*, PGT_VEC*
        );

extern  long  pgtNC_CvVectByDB(
                double[2],
                PGT_CURVP, double, long,
                double[3], double[3], double[3]
        );

extern  long  pgtNC_DeBoorVec(
                double[2],
                PGT_CURVP, double, long
        );

extern  long  pgtNC_GetBsplSec(
                double[2],
                PGT_CURVP, double,
                long*
        );

extern  long  pgtNC_CvVectByPL(
                double[2],
                PGT_PLCURVP, double, long,
                double[3], double[3], double[3]
        );

extern  long  pgtNC_CvCurvature(
                double[2],
                PGT_CURVP, double, 
                double*, double[3]
        );

extern  long  pgtNC_CvDiff(
                double[2],
                PGT_CURVP, double,
                PGT_PNT*, PGT_VEC*, PGT_VEC*
        );

extern  long  pgtNC_CvDBDiff(
                double[2],
                PGT_CURVP, double, 
                double[4], double[4], double[4]
        );

extern  long  pgtNC_CvPLDiff(
                double[2],
                PGT_CURVP, double,
                double[4], double[4], double[4]
        );

extern  long  pgtNC_CvTorsion(
                double[2],
                PGT_CURVP, double,
                double*
        );

extern  long  pgtNC_CvThirdDiff(
                double[2],
                PGT_CURVP, double,
                PGT_PNT*, PGT_VEC*, PGT_VEC*, PGT_VEC*
        );



/*--------------------------------------------------------------------*/
/*     BASE NC Cxx : B-Spline Basic Function                          */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_CalBFunc(
                long, long, double[], double, long,
                double[]
        );



/*--------------------------------------------------------------------*/
/*     BASE NC Dxx : Debug                                            */
/*--------------------------------------------------------------------*/

/*----- I/O Ascii -----*/

extern  long  pgtNC_WriteCurv(
                char*, PGT_CURVP
        );

extern  long  pgtNC_WriteCurvFP(
                FILE*, PGT_CURVP
        );

extern  long  pgtNC_ReadCurv(
                char*,
                PGT_CURVP*
        );

extern  long  pgtNC_ReadCurvFP(
                FILE*,
                PGT_CURVP*
        );

extern  long  pgtNC_WriteCurvArray(
                char*, long, PGT_CURVP[]
        );

extern  long  pgtNC_ReadCurvArray(
                char*,
                long*, PGT_CURVP**
        );


/*----- I/O Binary -----*/

extern  long  pgtNC_WriteCurvBIN(
                char*, PGT_CURVP
        );

extern  long  pgtNC_WriteCurvBINFP(
                FILE*, PGT_CURVP
        );

extern  long  pgtNC_ReadCurvBIN(
                char*,
                PGT_CURVP*
        );

extern  long  pgtNC_ReadCurvBINFP(
                FILE*,
                PGT_CURVP*
        );


/*----- Polyline for Control Points -----*/

extern  long  pgtNC_CvCtrlPnts(
                double[2],
                PGT_CURVP,
                PGT_POLYLINEP*
        );



/*--------------------------------------------------------------------*/
/*     BASE NC Exx : Polynimial Expression                            */
/*--------------------------------------------------------------------*/

extern  long  pgtNC_AttachPLCurv(
                PGT_CURVP
        );

extern  long  pgtNC_CrePLCurv(
                PGT_CURVP,
                PGT_PLCURVP*
        );


/*--------------------------------------------------------------------*/
/*     BASE NC Fxx : Curve Condition                                  */
/*--------------------------------------------------------------------*/

/*----- Flag ---------------------------------------------------------*/
extern  long  pgtNC_SetCvFlags(
                double[2],
                PGT_CURVP
        );

extern  long  pgtNC_SetClsFlag(
                double[2],
                PGT_CURVP
        );

extern  long  pgtNC_SetRatFlag(
                double[2],
                PGT_CURVP
        );

extern  long  pgtNC_SetPlanFlag(
                double[2],
                PGT_CURVP
        );


/*----- Curve Evaluation ---------------------------------------------*/
extern  long  pgtNC_IsCvClosed(
                double[2],
                PGT_CURVP,
                long*
        );

extern  long  pgtNC_IsCvOnPlane(
                double[2],
                PGT_CURVP,
                long*
        );

extern  long  pgtNC_IsCvLine(
                double[2],
                PGT_CURVP,
                long*
        );

extern  long  pgtNC_ChkCvDegen(
                double[2],
                PGT_CURVP,
                long*
        );

extern  long  pgtNC_ParmLength(
                double[2],
                PGT_CURVP, double,
                double*
        );

extern  long  pgtNC_CurvLength(
                double[2],
                PGT_CURVP, double, double, 
                double*
        );

extern  long  pgtNC_CurvLengthFull(
                double[2],
                PGT_CURVP,
                double*
        );

extern  long  pgtNC_FlatKnots(
                PGT_CURVP,
                long*, double**
        );

extern  long  pgtNC_FlatKnotsIndex(
                PGT_CURVP,
                long*, long**
        );

extern  long  pgtNC_MMBoxForCurv(
                double[2],
                PGT_CURVP,
                double[3], double[3] 
        );

extern  long  pgtNC_MMBoxForSegment(
                double[2],
                PGT_CURVP, long,
                double[3], double[3] 
        );

extern  long  pgtNC_MMBoxForPart(
                double[2],
                PGT_CURVP, double, double,
                double[3], double[3] 
        );



/*--------------------------------------------------------------------*/
/*     BASE NC Gxx : Curve Operation                                  */
/*--------------------------------------------------------------------*/

/*----- Curve Operation ----------------------------------------------*/
extern  long  pgtNC_NormalizeCv(
                PGT_CURVP, 
                PGT_CURVP* 
        );

extern  long  pgtNC_ReverseCv(
                PGT_CURVP, 
                PGT_CURVP* 
        );

extern  long  pgtNC_InsCvKnot(
                double[2],
                PGT_CURVP, double,
                PGT_CURVP* 
        );

extern  long  pgtNC_InsCvMaxKnot(
                double[2],
                PGT_CURVP, 
                PGT_CURVP* 
        );

extern  long  pgtNC_SplitCv(
                double[2],
                PGT_CURVP, double,
                PGT_CURVP*, PGT_CURVP*
        );

extern  long  pgtNC_SplitCvAdj(
                double[2],
                PGT_CURVP, double,
                PGT_CURVP*, PGT_CURVP*
        );

extern  long  pgtNC_TrimCv(
                double[2],
                PGT_CURVP, double, double,
                PGT_CURVP*
              );

extern  long  pgtNC_TrimCvAdj(
                double[2],
                PGT_CURVP, double, double,
                PGT_CURVP*
              );

extern  long  pgtNC_ConcatCv(
                double[2],
                PGT_CURVP, PGT_CURVP, 
                PGT_CURVP*
        );

extern  long  pgtNC_ConcatCvAry(
                double[2],
                long, PGT_CURVP[], 
                PGT_CURVP*
        );

extern  long  pgtNC_ElevateCvDeg(
                double[2],
                PGT_CURVP,
                PGT_CURVP*
        );

extern  long  pgtNC_RemTinyTermSeg(
                double[2], double,
                PGT_CURVP, 
                PGT_CURVP* 
        );

extern  long  pgtNC_MultCvEndKnots(
                PGT_CURVP, 
                PGT_CURVP* 
        );

extern  long  pgtNC_InsCvEndKnot(
                PGT_CURVP, double,
                PGT_CURVP* 
        );

extern  long  pgtNC_CurvBetMultEndKnots(
                PGT_CURVP,
                PGT_CURVP* 
        );



/*----- Move ---------------------------------------------------------*/

extern  long  pgtNC_MoveCv(
                double[2],
                PGT_CURVP, double[4][4],
                PGT_CURVP*
        );

extern  long  pgtNC_MoveLine(
                PGT_LINEP, double[4][4],
                PGT_LINEP*
        );

extern  long  pgtNC_MoveCircle(
                PGT_CIRCLEP, double[4][4],
                PGT_CIRCLEP*
        );

extern  long  pgtNC_MoveEllipse(
                PGT_ELLIPSEP, double[4][4],
                PGT_ELLIPSEP*
        );

extern  long  pgtNC_MoveParabola(
                PGT_PARABOLAP, double[4][4],
                PGT_PARABOLAP*
        );

extern  long  pgtNC_MoveHyperbola(
                PGT_HYPERBOLAP, double[4][4],
                PGT_HYPERBOLAP*
        );

extern  long  pgtNC_ShiftCv(
                double[2],
                PGT_CURVP, double[3],
                PGT_CURVP*
        );



/*--------------------------------------------------------------------*/
/*     BASE NC Hxx : Composite Curve                                  */
/*--------------------------------------------------------------------*/

/*----- Alloc, Free --------------------------------------------------*/

extern  long  pgtNC_AllocCompCrv(
                long,
                PGT_COMPCRVP*
        );

extern  long  pgtNC_FreeCompCrv(
                PGT_COMPCRVP*
        );

extern  long  pgtNC_CopyCompCrv(
                PGT_COMPCRVP,
                PGT_COMPCRVP*
        );

extern  long  pgtNC_MoveCompCrv(
                PGT_COMPCRVP, double[4][4],
                PGT_COMPCRVP*
        );

extern  long  pgtNC_AllocCompSeg(
                PGT_COMPSEGP*
        );

extern  long  pgtNC_FreeCompSeg(
                PGT_COMPSEGP*
        );

extern  long  pgtNC_CopyCompSeg(
                PGT_COMPSEGP,
                PGT_COMPSEGP*
        );

extern  long  pgtNC_MoveCompSeg(
                PGT_COMPSEGP, double[4][4],
                PGT_COMPSEGP*
        );



/*----- Vector on Composite Curve ------------------------------------*/

extern  long  pgtNC_CompCrvVect(
                double[2],
                PGT_COMPCRVP, double,
                PGT_PNT*
        );

extern  long  pgtNC_WriteCompCrv(
                    char[], PGT_COMPCRVP
        );

extern  long  pgtNC_WriteCompCrvArray(
                    char[], long, PGT_COMPCRVP[]
        );

extern  long  pgtNC_WriteCompCrvFP(
                    FILE*, PGT_COMPCRVP
        );

extern  long  pgtNC_ReadCompCrv(
                    char[], 
                    PGT_COMPCRVP*
        );

extern  long  pgtNC_ReadCompCrvArray(
                    char[], 
                    long*, PGT_COMPCRVP**
        );

extern  long  pgtNC_ReadCompCrvFP(
                    FILE*, 
                    PGT_COMPCRVP*
        );



/*----- File I/O -----------------------------------------------------*/






/*--------------------------------------------------------------------*/
/*     BASE NF Axx : Surface Alloc/Free/Copy                          */
/*--------------------------------------------------------------------*/

/*-----Surface Polynomial Expression ---------------------------------*/
extern  long  pgtNF_AllocSurf(
                long, long, long, long,
                PGT_SURFP*
        );

extern  long  pgtNF_FreeSurf( 
                PGT_SURFP*
        );

extern  long  pgtNF_CopySurf(
                PGT_SURFP,
                PGT_SURFP*
        );

extern  long  pgtNF_AllocFlexSurfs(
                long, long, long,
                PGT_FLEXSURFSP*
        );

extern  long  pgtNF_FreeFlexSurfs(
                PGT_FLEXSURFSP*
        );

extern  long  pgtNF_AddSurfToFlex(
                PGT_FLEXSURFSP, PGT_ELMSURF
        );

extern  long  pgtNF_AllocFlexTsrfs(
                long, long, long,
                PGT_FLEXTSRFSP*
        );

extern  long  pgtNF_FreeFlexTsrfs(
                PGT_FLEXTSRFSP*
        );

extern  long  pgtNF_AddTsrfToFlex(
                PGT_FLEXTSRFSP, PGT_ELMTSRF
        );


extern  long  pgtNF_AllocPlane(
                PGT_PLANEP*
        );

extern  long  pgtNF_FreePlane(
                PGT_PLANEP*
        );

extern  long  pgtNF_CopyPlane(
                PGT_PLANEP,
                PGT_PLANEP*
        );

extern  long  pgtNF_AllocCylinder(
                PGT_CYLINDERP*
        );

extern  long  pgtNF_FreeCylinder(
                PGT_CYLINDERP*
        );

extern  long  pgtNF_CopyCylinder(
                PGT_CYLINDERP,
                PGT_CYLINDERP*
        );

extern  long  pgtNF_AllocCone(
                PGT_CONEP*
        );

extern  long  pgtNF_FreeCone(
                PGT_CONEP*
        );

extern  long  pgtNF_CopyCone(
                PGT_CONEP,
                PGT_CONEP*
        );

extern  long  pgtNF_AllocSphere(
                PGT_SPHEREP*
        );

extern  long  pgtNF_FreeSphere(
                PGT_SPHEREP*
        );

extern  long  pgtNF_CopySphere(
                PGT_SPHEREP,
                PGT_SPHEREP*
        );

extern  long  pgtNF_AllocTorus(
                PGT_TORUSP*
        );

extern  long  pgtNF_FreeTorus(
                PGT_TORUSP*
        );

extern  long  pgtNF_CopyTorus(
                PGT_TORUSP,
                PGT_TORUSP*
        );




/*----- Underlying DeBoor Cox Work Area ------------------------------*/

extern  long  pgtNF_AllocSfDBR(
                long, long, long, long,
                PGT_SFDEBOORP*
        );

extern  long  pgtNF_FreeSfDBR(
                PGT_SFDEBOORP*
        );

extern  long  pgtNF_AttachSfDBR(
                PGT_SURFP,
                long*
        );


/*----- Underlying Polynomial Surface --------------------------------*/

extern  long  pgtNF_AllocPLSurf(
                long, long, long, long,
                PGT_PLSURFP*
        );

extern  long  pgtNF_FreePLSurf(
                PGT_PLSURFP*
        );


/*----- Underlying Analytical Expression -----------------------------*/

extern  long  pgtNF_FreeSfGeom(
                PGT_SFGEOM*
        );



/*--------------------------------------------------------------------*/
/*     BASE NF Bxx : Vector on Surface                                */
/*--------------------------------------------------------------------*/

extern  long  pgtNF_SfVect(
                double[2],
                PGT_SURFP, double, double, long,
                PGT_PNT*, PGT_VEC*, PGT_VEC*
        );

extern  long  pgtNF_SfVectByDB(
                double[2],
                PGT_SURFP, double, double, long,
                double[3], double[3], double[3], double[3]
        );

extern  long  pgtNF_GetBsplSec(
                double[2],
                PGT_SURFP, double, double,
                long*, long*
        );

extern  long  pgtNF_ChkDegenPatch(
                double[2],
                PGT_SURFP, long, long,
                long*, long*, long*, long*
        );

extern  long  pgtNF_SetBFunc(
                double[2],
                PGT_SURFP, double, double
        );

extern  long  pgtNF_BFuncVec(
                double[2],
                PGT_SURFP, double, double, long, long
        );

extern  long  pgtNF_SfVectByPL(
                double[2],
                PGT_PLSURFP, double, double, long,
                double[3], double[3], double[3], double[3]
        );

extern  long  pgtNF_SfCurvature(
                double[2],
                PGT_SURFP, double, double,
                double*, double*
                );

extern  long  pgtNF_SfDiff(
                double[2],
                PGT_SURFP, double, double,
                PGT_PNT*, 
                PGT_VEC*, PGT_VEC*, 
                PGT_VEC*, PGT_VEC*, PGT_VEC*
            );

extern  long  pgtNF_SfDBDiff(
                double[2],
                PGT_SURFP, double, double,
                double[4], 
                double[4], double[4], 
                double[4], double[4], double[4]
            );

extern  long  pgtNF_SfPLDiff(
                double[2],
                PGT_SURFP, double, double,
                double[4], 
                double[4], double[4], 
                double[4], double[4], double[4]
            );

extern  long  pgtNF_SfNormal(
                double[2],
                PGT_SURFP, double, double,
                PGT_PNT*, PGT_VEC*, PGT_VEC*, PGT_VEC*
            );

extern  long  pgtNF_SfCurvatureWithDir(
                double[2],
                PGT_SURFP, double, double,
                double*, double*,
                PGT_PNT*, PGT_VEC*, PGT_VEC*, PGT_VEC*
            );

extern  long  pgtNF_SfCurvatureDUDV(
                double[2],
                PGT_SURFP, double, double, double, double,
                double*
            );



/*--------------------------------------------------------------------*/
/*     BASE NF Dxx : Surface Debug                                    */
/*--------------------------------------------------------------------*/

/*----- I/O Ascii -----*/

extern  long  pgtNF_WriteSurf(
                char*, PGT_SURFP
        );

extern  long  pgtNF_WriteSurfFP(
                FILE*, PGT_SURFP
        );

extern  long  pgtNF_ReadSurf(
                char*,
                PGT_SURFP*
        );

extern  long  pgtNF_ReadSurfFP(
                FILE*,
                PGT_SURFP*
        );

extern  long  pgtNF_WriteSurfArray(
                char*, long, PGT_SURFP[]
        );

extern  long  pgtNF_ReadSurfArray(
                char*,
                long*, PGT_SURFP**
        );

/*----- I/O Binary -----*/

extern  long  pgtNF_WriteSurfBIN(
                char*, PGT_SURFP
        );

extern  long  pgtNF_WriteSurfBINFP(
                FILE*, PGT_SURFP
        );

extern  long  pgtNF_ReadSurfBIN(
                char*,
                PGT_SURFP*
        );

extern  long  pgtNF_ReadSurfBINFP(
                FILE*,
                PGT_SURFP*
        );


/*----- Polylines from Conrol Points -----*/

extern  long  pgtNF_SfCtrlPnts(
                double[2],
                PGT_SURFP,
                long*, long*, PGT_POLYLINEP**, PGT_POLYLINEP**
        );



/*--------------------------------------------------------------------*/
/*     BASE NF Exx : Surface Polynimial Expression                    */
/*--------------------------------------------------------------------*/

extern  long  pgtNF_AttachPLSurf(
                PGT_SURFP
        );

extern  long  pgtNF_CrePLSurf(
                PGT_SURFP,
                PGT_PLSURFP*
        );



/*--------------------------------------------------------------------*/
/*     BASE NF Fxx : Surface Condition                                */
/*--------------------------------------------------------------------*/

/*----- Flags --------------------------------------------------------*/
extern  long  pgtNF_SetSfFlags(
                double[2],
                PGT_SURFP
        );

extern  long  pgtNF_SetClsFlag(
                double[2],
                PGT_SURFP
        );

extern  long  pgtNF_SetPolFlag(
                double[2],
                PGT_SURFP
        );

extern  long  pgtNF_SetPolFlag2(
                double[2], double,
                PGT_SURFP
        );

extern  long  pgtNF_SetRatFlag(
                double[2],
                PGT_SURFP
        );


/*----- Surface Evaluation 1 -----------------------------------------*/
extern  long  pgtNF_IsSfClosed(
                double[2],
                PGT_SURFP,
                long*, long*
        );

extern  long  pgtNF_IsTherePole(
                double[2],
                PGT_SURFP,
                long*, long*
        );

extern  long  pgtNF_IsTherePole2(
                double[2], double,
                PGT_SURFP,
                long*, long*
        );

extern  long  pgtNF_ChkSfDegen(
                double[2],
                PGT_SURFP,
                long*
        );

extern  long  pgtNF_ParmLength(
                double[2],
                PGT_SURFP, double,
                double*, double*
        );

extern  long  pgtNF_SfFlatKnots(
                PGT_SURFP,
                long*, long*, double**, double**
        );

extern  long  pgtNF_SfFlatKnotsIndex(
                PGT_SURFP,
                long*, long*, long**, long**
        );

extern  long  pgtNF_MMBoxForSurf(
                double[2],
                PGT_SURFP,
                double[3], double[3]
        );

extern  long  pgtNF_MMBoxForPatch(
                double[2],
                PGT_SURFP, long, long,
                double[3], double[3]
        );

extern  long  pgtNF_MMBoxForPart(
                double[2],
                PGT_SURFP, double, double, double, double,
                double[3], double[3]
        );

extern  long  pgtNF_UVTole(
                double[2],
                PGT_SURFP, double[2]
        );

extern  long  pgtNF_IsSurfPlanar(
                double[2], double,
                PGT_SURFP,
                long*
        );



/*----- Surface Evaluation 2 -----------------------------------------*/
extern  long  pgtNF_IsoCvAtConstV(
                PGT_SURFP, double,
                PGT_CURVP*
        );

extern  long  pgtNF_IsoCvAtConstU(
                PGT_SURFP, double,
                PGT_CURVP*
        );

extern  long  pgtNF_SfBoundCurv(
                double[2],
                PGT_SURFP, long,
                long*, PGT_CURVP*, PGT_PNT*
        );



/*--------------------------------------------------------------------*/
/*     BASE NF Gxx : Surface Operation                                */
/*--------------------------------------------------------------------*/

/*----- Surface Operation --------------------------------------------*/

extern  long  pgtNF_NormalizeSf(
                PGT_SURFP, 
                PGT_SURFP*
        );

extern  long  pgtNF_SwapCtrlPnts(
                PGT_SURFP,
                PGT_SURFP*
        );

extern  long  pgtNF_ReverseSf(
                PGT_SURFP, long,
                PGT_SURFP*
        );

extern  long  pgtNF_InsSfKnot(
                double[2],
                PGT_SURFP, long, long, double[],
                PGT_SURFP*
        );

extern  long  pgtNF_InsSfMaxKnot(
                double[2],
                PGT_SURFP,
                PGT_SURFP*
        );

extern  long  pgtNF_SplitSf(
                double[2],
                PGT_SURFP, long, double,
                PGT_SURFP*, PGT_SURFP*
        );

extern  long  pgtNF_SplitSfAdj(
                double[2],
                PGT_SURFP, long, double,
                PGT_SURFP*, PGT_SURFP*
        );

extern  long  pgtNF_SplitSfAdj2(
                double[2],
                PGT_SURFP, long, double,
                long*, long*, PGT_SURFP*, PGT_SURFP*
        );

extern  long  pgtNF_TrimSf(
                double[2],
                PGT_SURFP, double, double, double, double,
                PGT_SURFP*
        );

extern  long  pgtNF_TrimSfAdj(
                double[2],
                PGT_SURFP, double, double, double, double,
                PGT_SURFP*
        );

extern  long  pgtNF_ConcatSf(
                double[2],
                PGT_SURFP, PGT_SURFP, long,
                PGT_SURFP*
        );

extern  long  pgtNF_ConcatSfAry(
                double[2],
                long, long, PGT_SURFP[],
                PGT_SURFP*
        );

extern  long  pgtNF_ElevateSfDeg(
                double[2],
                PGT_SURFP, long,
                PGT_SURFP*
        );

extern  long  pgtNF_MultSfEndKnots(
                PGT_SURFP, 
                PGT_SURFP* 
        );

extern  long  pgtNF_InsSfEndKnot(
                PGT_SURFP, long, double,
                PGT_SURFP* 
        );

extern  long  pgtNF_SurfBetMultEndKnots(
                PGT_SURFP, 
                PGT_SURFP* 
        );




/*----- Move Surface -------------------------------------------------*/

extern  long  pgtNF_MoveSf(
                double[2],
                PGT_SURFP, double[4][4],
                PGT_SURFP*
        );

extern  long  pgtNF_MovePlane(
                PGT_PLANEP, double[4][4],
                PGT_PLANEP*
        );

extern  long  pgtNF_MoveCylinder(
                PGT_CYLINDERP, double[4][4],
                PGT_CYLINDERP*
        );

extern  long  pgtNF_MoveCone(
                PGT_CONEP, double[4][4],
                PGT_CONEP*
        );

extern  long  pgtNF_MoveSphere(
                PGT_SPHEREP, double[4][4],
                PGT_SPHEREP*
        );

extern  long  pgtNF_MoveTorus(
                PGT_TORUSP, double[4][4],
                PGT_TORUSP*
        );

extern  long  pgtNF_ShiftSf(
                double[2],
                PGT_SURFP, double[3],
                PGT_SURFP*
        );



/*--------------------------------------------------------------------*/
/*     BASE NF Jxx : Trimmed Surface                                  */
/*--------------------------------------------------------------------*/

extern  long  pgtNF_AllocTrimSF(
                long,
                PGT_TRIMSFP*
        );

extern  long  pgtNF_FreeTrimSF(
                PGT_TRIMSFP*
        );

extern  long  pgtNF_AllocTrimLP(
                long,
                PGT_TRIMLPP*
        );

extern  long  pgtNF_FreeTrimLP(
                PGT_TRIMLPP*
        );

extern  long  pgtNF_AllocTrimED(
                PGT_TRIMEDP*
        );

extern  long  pgtNF_FreeTrimED(
                PGT_TRIMEDP*
        );





/*----- End of File --------------------------------------------------*/



#ifdef __cplusplus
}
#endif



#endif
