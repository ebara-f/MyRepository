/***********************************************************************

    関数名 : [SF HD03]  pgt_sf_funcs.h

    機  能 : ＳＦライブラリ用ヘッダファイル

    PGT SF Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_SF_FUNCS_H
#define PGT_SF_FUNCS_H



#include    "pgt_sf_struct.h"



#ifdef __cplusplus
extern "C"{
#endif



/*----- A : Make Skin Surface on Rib Curves --------------------------*/

extern  long  pgtSF_MkSkinSurf(
                double[2], double,
                long, PGT_CURVP[],
                PGT_SURFP*, double*
        );

extern  long  pgtSF_AlignRibDirect(
                double[2],
                long, PGT_CURVP[],
                PGT_CURVP[]
        );

extern  long  pgtSF_TotalFlatKnots(
                double[2], double,
                long, PGT_CURVP[],
                long*, double**
        );

extern  long  pgtSF_ApproxRibCrvs(
                double[2], double,
                long, PGT_CURVP[], long, double*,
                PGT_CURVP[], double*
        );

extern  long  pgtSF_SkinOnRibs(
                double[2],
                long, PGT_CURVP[],
                PGT_SURFP*
        );

extern  long  pgtSF_DigitCurv(
                double[2],
                PGT_CURVP,
                long*, PGT_PNT**
        );

extern  long  pgtSF_AddFlatKnots(
                long, double[], long, double[],
                long*, double**
        );



/*----- B : Repatch Surface ------------------------------------------*/

extern  long  pgtSF_RepatchSurf(
                double[2],
                PGT_SURFP, long, long, double[], double[],
                PGT_SURFP*, double*
        );

extern  long  pgtSF_DigitSurf(
                double[2],
                PGT_SURFP, long, long, double[], double[], long,
                PGT_SFMESHP*
        );

extern  long  pgtSF_SamplePosOnGeom(
                double[2],
                long, long, double[], double[], long,
                long*, long*, PGT_CNVTAB**, PGT_CNVTAB**
        );

extern  long  pgtSF_CreConvTab(
                double[2],
                PGT_SURFP,
                long*, long*, PGT_CNVTAB**, PGT_CNVTAB**
        );

extern  long  pgtSF_SamplePosOnSfParm(
                double[2],
                long, long, PGT_CNVTAB[], PGT_CNVTAB[],
                long, long, PGT_CNVTAB[], PGT_CNVTAB[]
        );

extern  long  pgtSF_ConvGeomToParm(
                long, PGT_CNVTAB[], double,
                double*
        );

extern  long  pgtSF_CalCpntAlongU(
                double[2],
                PGT_SFMESHP, long, double[],
                long*, PGT_CURVP**
        );

extern  long  pgtSF_CalCpntAlongU2(
                double[2],
                PGT_SFMESHP, long, long, double[],
                long*, PGT_CURVP**
        );

extern  long  pgtSF_CalCpntAlongV(
                double[2],
                PGT_SFMESHP, long, double[], long, PGT_CURVP[],
                long*, PGT_CURVP**
        );

extern  long  pgtSF_CalCpntAlongV2(
                double[2],
                PGT_SFMESHP, long, long, double[], long, PGT_CURVP[],
                long*, PGT_CURVP**
        );

extern  long  pgtSF_AllocSfMesh(
                long, long,
                PGT_SFMESHP*
        );

extern  long  pgtSF_FreeSfMesh(
                PGT_SFMESHP*
        );

extern  long  pgtSF_RepatchSurfToFitA(
                double[2], double,
                PGT_SURFP, long, long, double[], double[], long,
                PGT_SURFP*, double*
        );

extern  long  pgtSF_RepatchSurfToFitB(
                double[2], double,
                PGT_SURFP, long, long, double[], double[], long,
                PGT_SURFP*, double*
        );

extern  long  pgtSF_SetFlatKnots(
                long, long, double[], double[], long[], long[],
                long*, long*, double**, double**
        );

extern  long  pgtSF_SurfFromSfMesh(
                double[2],
                PGT_SFMESHP, long, long, double[], double[],
                PGT_SURFP*
        );

extern  long  pgtSF_SurfFromSfMesh2(
                double[2],
                PGT_SFMESHP, long, long, long, long, double[], double[],
                PGT_SURFP*
        );

extern  long  pgtSF_CalFitError(
                double[2], double,
                PGT_SURFP, PGT_SFMESHP,
                long, long, double[], double[], long, long[], double[],
                long*, long[], double[], double*
        );

extern  long  pgtSF_GetPntsInSfMesh(
                PGT_SFMESHP, double, double, double, double,
                long*, PGT_PNT[], double[], double[]
        );

extern  long  pgtSF_MapOutPatch(
                long, long, double[], double[], long, long[], double[],
                long*, long[], double[]
        );

extern  long  pgtSF_SfFlatKnotsOnGeom(
                double[2],
                PGT_SURFP,
                long*, long*, double**, double**
        );

extern  long  pgtSF_SfFlatKnotsByDiv(
                double[2],
                long, long,
                long*, long*, double**, double**
        );

extern  long  pgtSF_SfRemTinyKnots(
                double[2],
                double, long, double[],
                long*, double**
        );

extern  long  pgtSF_ConvParmToGeom(
                long, PGT_CNVTAB[], double,
                double*
        );




/*----- C : Check Surface Distortion ---------------------------------*/

extern  long  pgtSF_CheckSfDistort(
                double[2],
                PGT_SURFP,
                long*, long*, long*
        );

extern  long  pgtSF_DetectSfDegen(
                double[2],
                PGT_SURFP,
                long*, PGT_PNT*
        );

extern  long  pgtSF_DetectSfPleats(
                double[2],
                PGT_SURFP,
                long*, PGT_PNT*
        );

extern  long  pgtSF_DetectSfSelfInterf(
                double[2], double,
                PGT_SURFP,
                long*, PGT_PNT*
        );

extern  long  pgtSF_TriMeshFromPolys(
                double[2],
                long, PGT_POLYLINEP[],
                long*, PGT_TRIANGLE**
        );

extern  long  pgtSF_SpaceBoxesOnSurf(
                double[2],
                PGT_SURFP,
                long*, PGT_BOX**
        );

extern  long  pgtSF_DetectSfPoleIntsec(
                double[2],
                PGT_SURFP,
                long*, PGT_PNT*
        );



/*----- D : Make Skin Surface of Ladder Frame ------------------------*/

extern  long  pgtSF_MkSkinOnLadder(
                double[2], double,
                PGT_CURVP, PGT_CURVP, long, PGT_CURVP[],
                PGT_SURFP*, double*
        );

extern  long  pgtSF_CreLadder(
                double[2], double,
                PGT_CURVP, PGT_CURVP, long, PGT_CURVP[],
                PGT_LADDERP*
        );

extern  long  pgtSF_FreeLadder(
                PGT_LADDERP*
        );

extern  long  pgtSF_ApproxSecCrvs(
                double[2], double,
                PGT_LADDERP, double*
        );

extern  long  pgtSF_ApproxGuideCrvs(
                double[2], double,
                PGT_LADDERP, double*
        );

extern  long  pgtSF_SetLocalSys(
                double[2],
                PGT_LADDERP
        );

extern  long  pgtSF_CalLocalSys(
                double[2],
                PGT_PNT, PGT_VEC, PGT_PNT, PGT_VEC,
                PGT_CODSYS*
        );

extern  long  pgtSF_CreSubSections(
                double[2],
                PGT_LADDERP
        );

extern  long  pgtSF_MoveIntoLocalSys(
                double[2],
                PGT_CURVP, PGT_CODSYS,
                PGT_CURVP*
        );

extern  long  pgtSF_MoveIntoWorldSys(
                double[2],
                PGT_CURVP, PGT_CODSYS,
                PGT_CURVP*
        );

extern  long  pgtSF_CreSurfOnLadder(
                double[2],
                PGT_LADDERP,
                PGT_SURFP*
        );



/*----- E : Make Surface From Boundary -------------------------------*/

extern  long  pgtSF_MkSurfFromBound4(
                double[2], double,
                PGT_CURVP[4],
                PGT_SURFP*, double*
        );

extern  long  pgtSF_SetFrame(
                double[2], double,
                PGT_CURVP[4],
                PGT_CURVP*, PGT_CURVP*, PGT_CURVP*, PGT_CURVP*, double*
        );

extern  long  pgtSF_MakeOneChain(
                double[2],
                long, PGT_CURVP[],
                PGT_CURVP[], long*
        );

extern  long  pgtSF_MakeOneChainFIT(
                double[2], double,
                long, PGT_CURVP[],
                long*, PGT_CURVP**, long*
        );

extern  long  pgtSF_CreSweep(
                double[2],
                PGT_CURVP, PGT_CURVP, PGT_CURVP, PGT_CURVP,
                PGT_SURFP*
        );

extern  long  pgtSF_SetLocalSys2(
                double[2],
                PGT_FRAME*
        );

extern  long  pgtSF_CreSubSec2(
                double[2],
                PGT_FRAME*
        );

extern  long  pgtSF_CreSurfOnFrame(
                double[2],
                PGT_FRAMEP,
                PGT_SURFP*
        );

extern  long  pgtSF_SkinOnRibsWithKnots(
                double[2],
                long, PGT_CURVP[], double[],
                PGT_SURFP*
        );

extern  long  pgtSF_BlendSweep(
                double[2],
                PGT_SURFP, PGT_SURFP, double,
                PGT_SURFP*
        );



/*----- F : Make Surface From Triangle Boundary ----------------------*/

extern  long  pgtSF_MkSurfFromBound3(
                double[2], double,
                PGT_CURVP[3],
                PGT_SURFP*, double*
        );

extern  long  pgtSF_MkSurfFromBound3SPIN(
                double[2], double,
                PGT_CURVP[3],
                PGT_SURFP*, double*
        );

extern  long  pgtSF_SetFrameTri(
                double[2], double,
                PGT_CURVP[3],
                PGT_CURVP*, PGT_CURVP*, PGT_CURVP*, double[3], double*
        );

extern  long  pgtSF_CreSweepByOneGuide(
                double[2],
                PGT_CURVP, double[3], PGT_CURVP, PGT_CURVP,
                PGT_SURFP*
        );

extern  long  pgtSF_SetLocalSysByOneGuide(
                double[2],
                PGT_FRAME*
        );

extern  long  pgtSF_CreSubSecByOneGuide(
                double[2],
                PGT_FRAME*
        );

extern  long  pgtSF_CreSweepByOneSec(
                double[2],
                PGT_CURVP, PGT_CURVP, PGT_CURVP, double[3],
                PGT_SURFP*
        );

extern  long  pgtSF_SetLocalSysByOneSec(
                double[2],
                PGT_FRAME*
        );

extern  long  pgtSF_CreSubSecByOneSec(
                double[2],
                PGT_FRAME*
        );



/*----- G : Offset Surface : Surface ---------------------------------*/

extern  long  pgtSF_OffsetSurf(
                double[2], double,
                PGT_SURFP, long, double,
                PGT_SURFP*, double*
        );

extern  long  pgtSF_OffsetSurf2(
                double[2], double,
                PGT_SURFP, long, double,
                PGT_SURFP*, double*
        );

extern  long  pgtSF_CreSfMesh(
                double[2],
                PGT_SURFP,
                PGT_SFMESHP*
        );

extern  long  pgtSF_OffsetSfMesh(
                double[2],
                PGT_SURFP, long, double,
                PGT_SFMESHP
        );

extern  long  pgtSF_SurfOnSfMesh(
                double[2],
                PGT_SFMESHP, long,
                PGT_SURFP*
        );

extern  long  pgtSF_VerifyOffSrf(
                double[2], double,
                PGT_SURFP, long, double, PGT_SFMESHP, PGT_SURFP,
                long*, double*
        );

extern  long  pgtSF_UpdateSfMesh(
                double[2],
                PGT_SFMESHP, PGT_SURFP, long, double,
                PGT_SFMESHP*
        );

extern  long  pgtSF_UpdateSfMesh2(
                double[2],
                PGT_SFMESHP, PGT_SURFP, long, long, long, double,
                PGT_SFMESHP*
        );

extern  long  pgtSF_CreInitSfMesh(
                double[2],
                PGT_SURFP, long, double,
                PGT_SFMESHP*
        );

extern  long  pgtSF_CleanSfMesh(
                double[2],
                PGT_SFMESHP, PGT_SURFP, long, double,
                PGT_SFMESHP*
        );

extern  long  pgtSF_OffsetSfMeshTry(
                double[2],
                PGT_SURFP, long, double,
                PGT_SFMESHP
        );

extern  long  pgtSF_RemPntsInSfMesh(
                PGT_SFMESHP,
                PGT_SFMESHP*
        );

extern  long  pgtSF_RemSegInSfMesh(
                double[2],
                PGT_SFMESHP,
                PGT_SFMESHP*
        );



/*----- J : Offset Surface : Curve -----------------------------------*/

extern  long  pgtSF_OffsetCurv(
                double[2], double,
                double, PGT_CURVP, PGT_SURFP,
                PGT_CURVP*, double*
        );

extern  long  pgtSF_CreCvMesh(
                double[2],
                PGT_CURVP,
                PGT_CVMESHP*
        );

extern  long  pgtSF_OffsetCvMesh(
                double[2],
                PGT_CURVP, PGT_SURFP,
                PGT_CVMESHP
        );

extern  long  pgtSF_CurvOnCvMesh(
                double[2],
                PGT_CVMESHP, long,
                PGT_CURVP*
        );

extern  long  pgtSF_VerifyOffCrv(
                double[2], double,
                double, PGT_CURVP, PGT_CVMESHP, PGT_SURFP, PGT_CURVP,
                long*, double*
        );

extern  long  pgtSF_UpdateCvMesh(
                double[2],
                PGT_CVMESHP, PGT_CURVP, PGT_SURFP,
                PGT_CVMESHP*
        );

extern  long  pgtSF_AllocCvMesh(
                long,
                PGT_CVMESHP*
        );

extern  long  pgtSF_FreeCvMesh(
                PGT_CVMESHP*
        );

extern  long  pgtSF_MergeCv(
                double[2],
                PGT_CURVP, PGT_CURVP,
                PGT_CURVP*
        );

extern  long  pgtSF_CreInitCvMesh(
                double[2],
                PGT_CURVP, PGT_SURFP,
                PGT_CVMESHP*
        );

extern  long  pgtSF_CleanCvMesh(
                double[2],
                PGT_CVMESHP, PGT_CURVP, PGT_SURFP,
                PGT_CVMESHP*
        );



/*----- K : Make Surface From N Boundaries ---------------------------*/

extern  long  pgtSF_MkSurfFromBoundN(
                double[2], double,
                long, PGT_CURVP[],
                long*, PGT_SURFP**, double*
        );

extern  long  pgtSF_AllocNSideFrame(
                long,
                PGT_NSIDEFRMP*
        );

extern  long  pgtSF_FreeNSideFrame(
                PGT_NSIDEFRMP*
        );

extern  long  pgtSF_BaseSurfOnFrame(
                double[2],
                PGT_NSIDEFRMP
        );

extern  long  pgtSF_CalRadialCenter(
                double[2],
                PGT_NSIDEFRMP
        );

extern  long  pgtSF_CalRadialCurv(
                double[2],
                PGT_NSIDEFRMP
        );

extern  long  pgtSF_SurfsFromNSideFrame(
                double[2], double,
                PGT_NSIDEFRMP,
                long*, PGT_SURFP**, double*
        );



/*----- L : Make Surface From 1,2 Curves -----------------------------*/

extern  long  pgtSF_MkSurfFromBound2(
                double[2], double,
                PGT_CURVP[2],
                PGT_SURFP*, double*
        );

extern  long  pgtSF_MkSurfFromBound2GEN(
                double[2], double,
                PGT_CURVP[2],
                PGT_SURFP*, double*
        );

extern  long  pgtSF_ConcatG1Curvs(
                double[2], double,
                long, PGT_CURVP[],
                long*, PGT_CURVP**
        );

extern  long  pgtSF_ApproxCurvByPassPnts(
                double[2], double,
                PGT_CURVP,
                long*, PGT_PNT**, double*
        );

extern  long  pgtSF_MakeChainsFIT(
                double[2], double,
                long, PGT_CURVP[],
                long*, PGT_CVCHAINP**
        );

extern  long  pgtSF_AllocCvChain(
                long,
                PGT_CVCHAINP*
        );

extern  long  pgtSF_FreeCvChain(
                PGT_CVCHAINP*
        );



/*----- M : Make Planar Surface  -------------------------------------*/

extern  long  pgtSF_AreCurvsOnPlane(
                double[2], double,
                long, PGT_CURVP[],
                long*
        );

extern  long  pgtSF_MkPlanarSurfFromCvs(
                double[2],
                long, PGT_CURVP[],
                PGT_SURFP*
        );



/*----- End of File --------------------------------------------------*/



#ifdef __cplusplus
}
#endif



#endif
