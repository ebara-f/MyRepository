/***********************************************************************

    ä÷êîñº : [BREP HD03]  pgt_brep_funcs.h

    ã@  î\ : ÇaÇqÇdÇoÉâÉCÉuÉâÉäópÉwÉbÉ_ÉtÉ@ÉCÉã

    PGT BREP Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Yojiro Mandachi    / GeomLab        2023.08.04
    Modified  : Hiroyuki Kitazawa  / GeomLab        2023.08.18
    Modified  : Yojiro Mandachi    / GeomLab        2025.08.08

***********************************************************************/



#ifndef PGT_BREP_FUNCS_H
#define PGT_BREP_FUNCS_H



#include    "pgt_brep_struct.h"



#ifdef __cplusplus
extern "C"{
#endif



/*--------------------------------------------------------------------*/
/*     Basic Functions                                                */
/*--------------------------------------------------------------------*/

/*----- Alloc / Free / Copy ------------------------------------------*/

/*----- ID Array -----*/

extern  long  pgtBR_AllocEdgeIDAry(
                    long,
                    PGT_BREDIDARYP* 
        );

extern  long  pgtBR_FreeEdgeIDAry(
                    PGT_BREDIDARYP* 
        );

extern  long  pgtBR_AllocCoedIDAry(
                    long,
                    PGT_BRCEIDARYP* 
        );

extern  long  pgtBR_FreeCoedIDAry(
                    PGT_BRCEIDARYP* 
        );

extern  long  pgtBR_AllocFaceIDAry(
                    long,
                    PGT_BRFCIDARYP* 
        );

extern  long  pgtBR_FreeFaceIDAry(
                    PGT_BRFCIDARYP* 
        );

/*----- Face Table -----*/

extern  long  pgtBR_AllocFaceTab(
                    long,
                    PGT_BRFACETABP* 
        );

extern  long  pgtBR_FreeFaceTab(
                    PGT_BRFACETABP* 
        );

extern  long  pgtBR_CopyFaceTab(
                    PGT_BRFACETABP,
                    PGT_BRFACETABP* 
        );

/*----- Edge Table -----*/

extern  long  pgtBR_AllocEdgeTab(
                    long,
                    PGT_BREDGETABP* 
        );

extern  long  pgtBR_FreeEdgeTab(
                    PGT_BREDGETABP* 
        );

extern  long  pgtBR_CopyEdgeTab(
                    PGT_BREDGETABP,
                    PGT_BREDGETABP* 
        );

/*----- Vertex Table -----*/

extern  long  pgtBR_AllocVtexTab(
                    long,
                    PGT_BRVTEXTABP* 
        );

extern  long  pgtBR_FreeVtexTab(
                    PGT_BRVTEXTABP* 
        );

extern  long  pgtBR_CopyVtexTab(
                    PGT_BRVTEXTABP,
                    PGT_BRVTEXTABP* 
        );

/*----- Edge -----*/

extern  long  pgtBR_AllocEdge(
                    PGT_BREDGEP* 
        );

extern  long  pgtBR_FreeEdge(
                    PGT_BREDGEP* 
        );

extern  long  pgtBR_CopyEdge(
                    PGT_BREDGEP,
                    PGT_BREDGEP* 
        );

/*----- Vertex -----*/

extern  long  pgtBR_AllocVtex(
                    PGT_BRVTEXP* 
        );

extern  long  pgtBR_FreeVtex(
                    PGT_BRVTEXP* 
        );

extern  long  pgtBR_CopyVtex(
                    PGT_BRVTEXP,
                    PGT_BRVTEXP* 
        );

/*----- Coedge -----*/

extern  long  pgtBR_AllocCoedge(
                    PGT_BRCOEDGEP* 
        );

extern  long  pgtBR_FreeCoedge(
                    PGT_BRCOEDGEP* 
        );

extern  long  pgtBR_CopyCoedge(
                    PGT_BRCOEDGEP, 
                    PGT_BRCOEDGEP* 
        );

/*----- Loop -----*/

extern  long  pgtBR_AllocLoop(
                    long,
                    PGT_BRLOOPP* 
        );

extern  long  pgtBR_FreeLoop(
                    PGT_BRLOOPP* 
        );

extern  long  pgtBR_CopyLoop(
                    PGT_BRLOOPP, 
                    PGT_BRLOOPP* 
        );

/*----- Face -----*/

extern  long  pgtBR_AllocFace(
                    long,
                    PGT_BRFACEP* 
        );

extern  long  pgtBR_FreeFace(
                    PGT_BRFACEP* 
        );

extern  long  pgtBR_CopyFace(
                    PGT_BRFACEP, 
                    PGT_BRFACEP* 
        );

/*----- Shell -----*/

extern  long  pgtBR_AllocShell(
                    long,
                    PGT_BRSHELLP* 
        );

extern  long  pgtBR_FreeShell(
                    PGT_BRSHELLP* 
        );

extern  long  pgtBR_CopyShell(
                    PGT_BRSHELLP, 
                    PGT_BRSHELLP* 
        );

/*----- Sheet -----*/

extern  long  pgtBR_AllocSheet(
                    PGT_SHEETP* 
        );

extern  long  pgtBR_FreeSheet(
                    PGT_SHEETP* 
        );

extern  long  pgtBR_CopySheet( 
                    PGT_SHEETP,
                    PGT_SHEETP*
        );

/*----- Solid -----*/

extern  long  pgtBR_AllocSolid(
                    long,
                    PGT_SOLIDP* 
        );

extern  long  pgtBR_FreeSolid(
                    PGT_SOLIDP* 
        );

extern  long  pgtBR_CopySolid(
                    PGT_SOLIDP,
                    PGT_SOLIDP*
        );

/*----- All Shell -----*/

extern  long  pgtBR_AllocAllShell(
                    PGT_ALLSHELLP* 
        );

extern  long  pgtBR_FreeAllShell(
                    PGT_ALLSHELLP* 
        );

extern  long  pgtBR_CopyAllShell( 
                    PGT_ALLSHELLP,
                    PGT_ALLSHELLP*
        );



/*----- [Dxx] --------------------------------------------------------*/

extern  long  pgtBR_GetEdgeIndex(
                    PGT_BREDGETABP, long,
                    long* 
        );

extern  long  pgtBR_GetVtexIndex(
                    PGT_BRVTEXTABP, long,
                    long* 
        );

extern  long  pgtBR_GetFTFace(
                    PGT_BRFACETABP, long,
                    PGT_BRFACEP* 
        );

extern  long  pgtBR_GetFTLoop(
                    PGT_BRFACETABP, long,
                    PGT_BRLOOPP* 
        );

extern  long  pgtBR_GetFTCoedge(
                    PGT_BRFACETABP, long,
                    PGT_BRCOEDGEP* 
        );

extern  long  pgtBR_GetETEdge(
                    PGT_BREDGETABP, long,
                    PGT_BREDGEP* 
        );

extern  long  pgtBR_GetVTVtex(
                    PGT_BRVTEXTABP, long,
                    PGT_BRVTEXP* 
        );

extern  long  pgtBR_SortFaceTab(
                    PGT_BRFACETABP
        );

extern  long  pgtBR_SortEdgeTab(
                    PGT_BREDGETABP
        );

extern  long  pgtBR_SortVtexTab(
                    PGT_BRVTEXTABP
        );

extern  long  pgtBR_SortPartTab(
                    PGT_BRPARTTABP
        );

extern  long  pgtBR_GetFTFaceSORT(
                    PGT_BRFACETABP, long,
                    PGT_BRFACEP*
        );

extern  long  pgtBR_GetETEdgeSORT(
                    PGT_BREDGETABP, long,
                    PGT_BREDGEP*
        );

extern  long  pgtBR_GetVTVtexSORT(
                    PGT_BRVTEXTABP, long,
                    PGT_BRVTEXP*
        );

extern  long  pgtBR_GetPTPartSORT(
                    PGT_BRPARTTABP, long,
                    PGT_BRPARTP*
        );



/*----- [Exx] --------------------------------------------------------*/

extern  long  pgtBR_RelEdgeToCoed(
                    PGT_BRFACETABP, PGT_BREDGETABP
        );

extern  long  pgtBR_RelEdgeToFace(
                    PGT_BRFACETABP, PGT_BREDGETABP
        );

extern  long  pgtBR_RelVtexToEdge(
                    PGT_BREDGETABP, PGT_BRVTEXTABP
        );

extern  long  pgtBR_RelVtexToFace(
                    PGT_BRFACETABP, PGT_BREDGETABP, PGT_BRVTEXTABP
        );



/*----- [Fxx] --------------------------------------------------------*/

extern  long  pgtBR_FaceIntoTrimSF(
                    PGT_BRFACEP, PGT_BREDGETABP,
                    PGT_TRIMSFP*
        );

extern  long  pgtBR_FaceIntoTrimSFAdj(
                    PGT_BRFACEP, PGT_BREDGETABP,
                    PGT_TRIMSFP*
        );

extern  long  pgtBR_SetFaceDirInFaceTab(
                    PGT_BRFACETABP, PGT_BREDGETABP, long
        );

extern  long  pgtBR_GetBorderEdges(
                    PGT_BRFACETABP, PGT_BREDGETABP,
                    long*, long** 
        );

extern  long  pgtBR_SetBorderFacDir(
                    PGT_BRFACETABP, PGT_BREDGETABP, long, long[] 
        );

extern  long  pgtBR_DomainsInFaces(
                    PGT_BRFACETABP, PGT_BREDGETABP,
                    long*, PGT_BRFCIDARYP**
        );

extern  long  pgtBR_ReverseLoop(
                    PGT_BRLOOPP, 
                    PGT_BRLOOPP*
        );

extern  long  pgtBR_NormalizeFaceTabGEOM(
                    PGT_BRFACETABP,
                    PGT_BRFACETABP*
        );

extern  long  pgtBR_NormalizeEdgeTabGEOM( 
                    PGT_BREDGETABP,
                    PGT_BREDGETABP*
        );

extern  long  pgtBR_RemoveFaces(
                    PGT_ALLSHELLP,
                    long, long[]
        );

extern  long  pgtBR_RemoveNonRefEdge(
                    PGT_BRFACETABP, PGT_BREDGETABP,
                    PGT_BREDGETABP*
        );

extern  long  pgtBR_RemoveNonRefVtex(
                    PGT_BREDGETABP, PGT_BRVTEXTABP,
                    PGT_BRVTEXTABP*
        );



/*----- [Gxx] --------------------------------------------------------*/

extern  long  pgtBR_MMBoxForEdgeTab(
                    double[2],
                    double, PGT_BREDGETABP,
                    PGT_BOX*
        );

extern  long  pgtBR_MoveSheet(
                    double[2],
                    double[4][4], PGT_SHEETP
        );

extern  long  pgtBR_MoveSolid(
                    double[2],
                    double[4][4], PGT_SOLIDP
        );

extern  long  pgtBR_MoveAllShell(
                    double[2],
                    double[4][4], PGT_ALLSHELLP
        );

extern  long  pgtBR_MoveBrepTable(
                    double[2],
                    double[4][4],
                    PGT_BRFACETABP, PGT_BREDGETABP, PGT_BRVTEXTABP
        );



/*----- [Hxx] --------------------------------------------------------*/

extern  long  pgtBR_AddCoedgeOnPole(
                    double[2], double,
                    PGT_BRFACETABP, PGT_BREDGETABP, long,
                    PGT_BRFACETABP*
        );

extern  long  pgtBR_AttachUVCurvToCoedge(
                    double[2], double,
                    PGT_SURFP, PGT_BREDGETABP, PGT_BRLOOPP
        );



/*----- [Ixx] Convert Brep -------------------------------------------*/

extern  long  pgtBR_SheetIntoAllShell(
                    PGT_SHEETP,
                    PGT_ALLSHELLP*
        );



/*----- [Jxx] Align Brep ---------------------------------------------*/

extern  long  pgtBR_AlignSolid(
                    PGT_SOLIDP, long, long[]
        );

extern  long  pgtBR_AlignShell(
                    PGT_BRSHELLP, PGT_BRFACETABP, PGT_BREDGETABP, long
        );



/*----- [Pxx] Wire Frame ---------------------------------------------*/

extern  long  pgtBR_KnitCurvs(
                    double[2], double,
                    long, PGT_CURVP[],
                    PGT_WIREP*
        );

extern  long  pgtBR_AllocWire(
                    PGT_WIREP* 
        );

extern  long  pgtBR_FreeWire(
                    PGT_WIREP* 
        );

extern  long  pgtBR_CopyWire(
                    PGT_WIREP, 
                    PGT_WIREP* 
        );



/*----- [Lxx] Assembly -----------------------------------------------*/

extern  long  pgtBR_AllocAssembly(
                    long,
                    PGT_ASSEMBLYP*
        );

extern  long  pgtBR_FreeAssembly(
                    PGT_ASSEMBLYP*
        );

extern  long  pgtBR_AllocInstance(
                    PGT_INSTANCEP*
        );

extern  long  pgtBR_FreeInstance(
                    PGT_INSTANCEP*
        );

extern  long  pgtBR_CopyInstance(
                    PGT_INSTANCEP,
                    PGT_INSTANCEP*
        );

extern  long  pgtBR_AllocAssemblyTree(
                    PGT_ASSEMTREEP*
        );

extern  long  pgtBR_FreeAssemblyTree(
                    PGT_ASSEMTREEP*
        );

extern  long  pgtBR_AllocPartTab(
                    long, long, long,
                    PGT_BRPARTTABP*
        );

extern  long  pgtBR_FreePartTab(
                    PGT_BRPARTTABP*
        );

extern  long  pgtBR_AllocPart(
                    PGT_BRPARTP*
        );

extern  long  pgtBR_FreePart(
                    PGT_BRPARTP*
        );

extern  long  pgtBR_AddPartToTab(
                    PGT_BRPARTTABP, PGT_BRPARTP
        );

extern  long  pgtBR_GetPTPart(
                    PGT_BRPARTTABP, long,
                    PGT_BRPARTP*
        );

extern  long  pgtBR_AddInstToAsem(
                    PGT_ASSEMBLYP, PGT_INSTANCEP
        );

extern  long  pgtBR_ExtractMidAsem(
                    PGT_BRPARTTABP, PGT_ASSEMBLYP, PGT_INSTANCEP
        );

extern  long  pgtBR_CopyAssembly(
                    PGT_ASSEMBLYP, PGT_ASSEMBLYP*
        );

extern  long  pgtBR_CopyPart(
                    PGT_BRPARTP, PGT_BRPARTP*
        );

extern  long  pgtBR_SetNameToPart(
                    PGT_BRPARTP, char[] 
        );

extern  long  pgtBR_SetNameToInst(
                    PGT_INSTANCEP, char[] 
        );

extern  long  pgtBR_ExpandAssembly(
                    PGT_ASSEMTREEP,
                    PGT_ASSEMTREEP*
        );



/*----- [Mxx] Knit TrimSF -------------------------------------------*/

extern  long  pgtBR_KnitTrimSFs(
                    double[2], double,
                    long, PGT_TRIMSFP[], long,
                    PGT_ALLSHELLP*
        );

extern  long  pgtBR_InitTabFromTrimSFs(
                    long, PGT_TRIMSFP[],
                    PGT_BRFACETABP*, PGT_BREDGETABP*
        );

extern  long  pgtBR_CreInitVtexTab(
                    double[2],
                    PGT_BRFACETABP, PGT_BREDGETABP,
                    PGT_BRVTEXTABP*
        );

extern  long  pgtBR_MergeVertexes(
                    double[2], double,
                    PGT_BREDGETABP, PGT_BRVTEXTABP,
                    PGT_BRVTEXTABP*
        );

extern  long  pgtBR_SplitEdgeByVertex(
                    double[2], double,
                    PGT_BRFACETABP, PGT_BREDGETABP, PGT_BRVTEXTABP,
                    PGT_BREDGETABP*
        );

extern  long  pgtBR_GetVertexOnFace(
                    PGT_BRFACEP, PGT_BREDGETABP,
                    long*, long**
        );

extern  long  pgtBR_SplitPosOnEDCurv(
                    double[2], double,
                    PGT_CURVP, long, PGT_ELMPNT[],
                    long, long[],
                    long*, long**, double**
        );

extern  long  pgtBR_SplitEdge(
                    double[2],
                    long, PGT_CURVP, long, long,
                    long, long[], double[],
                    long*, PGT_BREDCURV**
        );

extern  long  pgtBR_MergeEdges(
                    double[2], double,
                    PGT_BRFACETABP, PGT_BREDGETABP, long,
                    PGT_BREDGETABP*
        );

extern  long  pgtBR_AreCurvsSame(
                    double[2], double,
                    PGT_CURVP, PGT_CURVP,
                    long*
        );

extern  long  pgtBR_AreCurvsSameDir(
                    double[2],
                    PGT_CURVP, PGT_CURVP,
                    long*
        );

extern  long  pgtBR_KnitSheetAndTrimSFs(
                    double[2], double,
                    PGT_SHEETP, long, PGT_TRIMSFP[], long,
                    PGT_SHEETP*
        );

extern  long  pgtBR_KnitAllShellAndTrimSFs(
                    double[2], double,
                    PGT_ALLSHELLP, long, PGT_TRIMSFP[], long,
                    PGT_ALLSHELLP*
        );

extern  long  pgtBR_ShiftAddTopoID(
                    PGT_SHEETP, PGT_SHEETP
        );

extern  long  pgtBR_ShiftAddTopoID2(
                    PGT_ALLSHELLP, PGT_ALLSHELLP
        );

extern  long  pgtBR_UniteShells(
                    PGT_BRSHELLP, PGT_BRSHELLP,
                    PGT_BRSHELLP*
        );

extern  long  pgtBR_UniteFaceTabs(
                    PGT_BRFACETABP, PGT_BRFACETABP,
                    PGT_BRFACETABP*
        );

extern  long  pgtBR_UniteEdgeTabs(
                    PGT_BREDGETABP, PGT_BREDGETABP,
                    PGT_BREDGETABP*
        );

extern  long  pgtBR_UniteVtexTabs(
                    PGT_BRVTEXTABP, PGT_BRVTEXTABP,
                    PGT_BRVTEXTABP*
        );

extern  long  pgtBR_MergeVtexesBetweenShells(
                    double[2], double,
                    PGT_BREDGETABP, PGT_BRVTEXTABP,
                    PGT_BRVTEXTABP*
        );

extern  long  pgtBR_SplitEdgeByOposVtex(
                    double[2], double,
                    PGT_BRFACETABP, PGT_BREDGETABP, PGT_BRVTEXTABP,
                    PGT_BREDGETABP*
        );

extern  long  pgtBR_SplitPosOnEDCurv3(
                    double[2], double,
                    PGT_CURVP, long, PGT_ELMPNT[], long,
                    long*, long**, double**
        );

extern  long  pgtBR_MergeEdgesBetweenShells(
                    double[2], double,
                    PGT_BRFACETABP, PGT_BREDGETABP, long,
                    PGT_BREDGETABP*
        );


/*----- [Jxx] Write Brep Entities ------------------------------------*/

extern  long  pgtBR_WriteSheet(
                    char*, PGT_SHEETP
        );

extern  long  pgtBR_WriteSolid(
                    char*, PGT_SOLIDP
        );

extern  long  pgtBR_WriteAllShell(
                    char*, PGT_ALLSHELLP
        );

extern  long  pgtBR_WriteHeadFP(
                    FILE*, char*, long, long
        );

extern  long  pgtBR_WriteShellFP(
                    FILE*, PGT_BRSHELLP
        );

extern  long  pgtBR_WriteFaceTabFP(
                    FILE*, PGT_BRFACETABP
        );

extern  long  pgtBR_WriteFaceFP(
                    FILE*, PGT_BRFACEP
        );

extern  long  pgtBR_WriteLoopFP(
                    FILE*, PGT_BRLOOPP
        );

extern  long  pgtBR_WriteCoedgeFP(
                    FILE*, PGT_BRCOEDGEP
        );

extern  long  pgtBR_WriteEdgeTabFP(
                    FILE*, PGT_BREDGETABP
        );

extern  long  pgtBR_WriteEdgeFP(
                    FILE*, PGT_BREDGEP
        );

extern  long  pgtBR_WriteVtexTabFP(
                    FILE*, PGT_BRVTEXTABP
        );

extern  long  pgtBR_WriteVtexFP(
                    FILE*, PGT_BRVTEXP
        );



/*----- [Kxx] Read Brep Entities -------------------------------------*/

extern  long  pgtBR_ReadSheet(
                    char*, 
                    PGT_SHEETP*
        );

extern  long  pgtBR_ReadSolid(
                    char*, 
                    PGT_SOLIDP*
        );

extern  long  pgtBR_ReadAllShell(
                    char*, 
                    PGT_ALLSHELLP*
        );

extern  long  pgtBR_ReadHeadFP(
                    FILE*, 
                    char*, long*, long*
        );

extern  long  pgtBR_ReadShellFP(
                    FILE*, 
                    PGT_BRSHELLP*
        );

extern  long  pgtBR_ReadFaceTabFP(
                    FILE*, 
                    PGT_BRFACETABP*
        );

extern  long  pgtBR_ReadFaceFP(
                    FILE*, 
                    PGT_BRFACEP*
        );

extern  long  pgtBR_ReadLoopFP(
                    FILE*, 
                    PGT_BRLOOPP*
        );

extern  long  pgtBR_ReadCoedgeFP(
                    FILE*, 
                    PGT_BRCOEDGEP*
        );

extern  long  pgtBR_ReadEdgeTabFP(
                    FILE*, 
                    PGT_BREDGETABP*
        );

extern  long  pgtBR_ReadEdgeFP(
                    FILE*, 
                    PGT_BREDGEP*
        );

extern  long  pgtBR_ReadVtexTabFP(
                    FILE*, 
                    PGT_BRVTEXTABP*
        );

extern  long  pgtBR_ReadVtexFP(
                    FILE*, 
                    PGT_BRVTEXP*
        );

extern  long  pgtBR_ReadRecordFP(
                    FILE*, long,
                    char[], long*
        );




/*----- End of File --------------------------------------------------*/



#ifdef __cplusplus
}
#endif



#endif
