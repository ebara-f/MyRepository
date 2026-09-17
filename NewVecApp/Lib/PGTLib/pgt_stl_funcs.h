/***********************************************************************

    関数名 : [STL HD03]  pgt_stl_funcs.h

    機  能 : ＳＴＬライブラリ用ヘッダファイル

    PGT STL Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2024.07.05
    Modified  : Hiroyuki Kitazawa  / GeomLab        2025.04.07

***********************************************************************/



#ifndef PGT_STL_FUNCS_H
#define PGT_STL_FUNCS_H



#include    "pgt_stl_struct.h"



#ifdef __cplusplus
extern "C"{
#endif



/*----- [Axx] : Interference in Triangles ----------------------------*/

extern  long  pgtST_InterfInTris(
                double[2], double,
                long, PGT_TRIANGLE[],
                long*, PGT_PNT*
        );

extern  long  pgtST_CalTriInterf(
                double[2], double,
                long, PGT_TRIANGLE[],
                long, PGT_INTTRIS[]
        );

extern  long  pgtST_CalTriInterfBySubDiv(
                double[2], double,
                long,
                PGT_TRISTREEP, PGT_BOX,
                long, PGT_INTTRIS[]
        );

extern  long  pgtST_IsVertexShared(
                long, long, long, long, long, long,
                long*
        );

extern  long  pgtST_UpdateInttrisTable(
                long, PGT_INTTRIS[],
                long, PGT_INTTRIS[]
        );

extern  long  pgtST_InterfInTrisWithSPBox(
                double[2], double,
                long, PGT_TRIANGLE[], long, PGT_BOX[],
                long*, PGT_PNT*
        );

extern  long  pgtST_AllocPairTab(
                long,
                PGT_PAIRTABP*
        );

extern  long  pgtST_FreePairTab(
                PGT_PAIRTABP*
        );

extern  long  pgtST_SetPair(
                PGT_PAIRTABP, long, long
        );

extern  long  pgtST_GetPair(
                PGT_PAIRTABP, long, long,
                long*
        );

extern  long  pgtST_TriInterfWithPairTab(
                double[2], double,
                long, PGT_TRIANGLE[], PGT_PAIRTABP,
                long, PGT_INTTRIS[]
        );

extern  long  pgtST_RegTriInterf(
                double[2], double,
                long, PGT_TRIANGLE[],
                PGT_PAIRTABP
        );

extern  long  pgtST_RegTriInterfBySubDiv(
                double[2], double,
                long,
                PGT_TRISTREEP, PGT_BOX,
                PGT_PAIRTABP
        );




/*----- [Bxx] STL Topology -------------------------------------------*/

extern  long  pgtST_AllocSTLNvec(
                PGT_STLNVECP*
        );

extern  long  pgtST_FreeSTLNvec(
                PGT_STLNVECP*
        );

extern  long  pgtST_CopySTLNvec(
                PGT_STLNVECP,
                PGT_STLNVECP*
        );


extern  long  pgtST_AllocSTLVtex(
                PGT_STLVTEXP*
        );

extern  long  pgtST_FreeSTLVtex(
                PGT_STLVTEXP*
        );

extern  long  pgtST_CopySTLVtex(
                PGT_STLVTEXP,
                PGT_STLVTEXP*
        );


extern  long  pgtST_AllocSTLEdge(
                PGT_STLEDGEP*
        );

extern  long  pgtST_FreeSTLEdge(
                PGT_STLEDGEP*
        );

extern  long  pgtST_CopySTLEdge(
                PGT_STLEDGEP,
                PGT_STLEDGEP*
        );


extern  long  pgtST_AllocSTLFace(
                PGT_STLFACEP*
        );

extern  long  pgtST_FreeSTLFace(
                PGT_STLFACEP*
        );

extern  long  pgtST_CopySTLFace(
                PGT_STLFACEP,
                PGT_STLFACEP*
        );


extern  long  pgtST_AllocSTLNvecTab(
                long,
                PGT_STLNVECTABP*
        );

extern  long  pgtST_FreeSTLNvecTab(
                PGT_STLNVECTABP*
        );

extern  long  pgtST_CopySTLNvecTab(
                PGT_STLNVECTABP,
                PGT_STLNVECTABP*
        );


extern  long  pgtST_AllocSTLVtexTab(
                long,
                PGT_STLVTEXTABP*
        );

extern  long  pgtST_FreeSTLVtexTab(
                PGT_STLVTEXTABP*
        );

extern  long  pgtST_CopySTLVtexTab(
                PGT_STLVTEXTABP,
                PGT_STLVTEXTABP*
        );


extern  long  pgtST_AllocSTLEdgeTab(
                long,
                PGT_STLEDGETABP*
        );

extern  long  pgtST_FreeSTLEdgeTab(
                PGT_STLEDGETABP*
        );

extern  long  pgtST_CopySTLEdgeTab(
                PGT_STLEDGETABP,
                PGT_STLEDGETABP*
        );


extern  long  pgtST_AllocSTLFaceTab(
                long,
                PGT_STLFACETABP*
        );

extern  long  pgtST_FreeSTLFaceTab(
                PGT_STLFACETABP*
        );

extern  long  pgtST_CopySTLFaceTab(
                PGT_STLFACETABP,
                PGT_STLFACETABP*
        );


extern  long  pgtST_AllocSTLMesh(
                PGT_STLMESHP*
        );

extern  long  pgtST_FreeSTLMesh(
                PGT_STLMESHP*
        );

extern  long  pgtST_CopySTLMesh(
                PGT_STLMESHP,
                PGT_STLMESHP*
        );


/*----- Array of Entity IDs -----*/

extern  long  pgtST_AllocFaceIDAry(
                long,
                PGT_STLFCIDARYP*
        );

extern  long  pgtST_FreeFaceIDAry(
                PGT_STLFCIDARYP*
        );

extern  long  pgtST_AllocEdgeIDAry(
                long,
                PGT_STLEDIDARYP*
        );

extern  long  pgtST_FreeEdgeIDAry(
                PGT_STLEDIDARYP*
        );

extern  long  pgtST_AllocVtexIDAry(
                long,
                PGT_STLVTIDARYP*
        );

extern  long  pgtST_FreeVtexIDAry(
                PGT_STLVTIDARYP*
        );


/*----- Remove Obsolete Entities -----*/

extern  long  pgtST_RemoveSTLFaces(
                PGT_STLMESHP, long, long[]
        );

extern  long  pgtST_RemoveNonRefSTLEdges(
                PGT_STLMESHP,
                long*
        );

extern  long  pgtST_RemoveNonRefSTLVtexs(
                PGT_STLMESHP,
                long*
        );

extern  long  pgtST_RemoveNonRefSTLNvecs(
                PGT_STLMESHP,
                long*
        );

extern  long  pgtST_CompressSTLMesh(
                PGT_STLMESHP
        );





/*----- [Cxx] STL Relation -------------------------------------------*/

/*----- Set Relation -----*/
extern  long  pgtST_RelVtexToEdge(
                PGT_STLEDGETABP,
                PGT_STLVTEXTABP
        );

extern  long  pgtST_RelVtexToFace(
                PGT_STLFACETABP,
                PGT_STLVTEXTABP
        );

extern  long  pgtST_RelEdgeToFace(
                PGT_STLFACETABP,
                PGT_STLEDGETABP
        );

/*----- Detach Relation -----*/

extern  long  pgtST_DetachRelation(
                PGT_STLMESHP
        );



/*----- Get Vtex/Edge/Face/Nvec from ID -----*/
extern  long  pgtST_GetSTLVtex(
                PGT_STLVTEXTABP, long,
                PGT_STLVTEXP*
        );

extern  long  pgtST_GetSTLVtexSORT(
                PGT_STLVTEXTABP, long,
                PGT_STLVTEXP*
        );

extern  long  pgtST_GetSTLVtexRNUM(
                PGT_STLVTEXTABP, long,
                PGT_STLVTEXP*
        );

extern  long  pgtST_GetSTLEdge(
                PGT_STLEDGETABP, long,
                PGT_STLEDGEP*
        );

extern  long  pgtST_GetSTLEdgeSORT(
                PGT_STLEDGETABP, long,
                PGT_STLEDGEP*
        );

extern  long  pgtST_GetSTLEdgeRNUM(
                PGT_STLEDGETABP, long,
                PGT_STLEDGEP*
        );

extern  long  pgtST_GetSTLFace(
                PGT_STLFACETABP, long,
                PGT_STLFACEP*
        );

extern  long  pgtST_GetSTLFaceSORT(
                PGT_STLFACETABP, long,
                PGT_STLFACEP*
        );

extern  long  pgtST_GetSTLFaceRNUM(
                PGT_STLFACETABP, long,
                PGT_STLFACEP*
        );

extern  long  pgtST_GetSTLNvec(
                PGT_STLNVECTABP, long,
                PGT_STLNVECP*
        );

extern  long  pgtST_GetSTLNvecSORT(
                PGT_STLNVECTABP, long,
                PGT_STLNVECP*
        );

extern  long  pgtST_GetSTLNvecRNUM(
                PGT_STLNVECTABP, long,
                PGT_STLNVECP*
        );

extern  long  pgtST_GetSTLEdgeByVtexID0(
                PGT_STLEDGETABP, long,
                long*, long*, long*
        );


/*----- Create STL Edge Table -----*/

extern  long  pgtST_CreSTLEdgeTab(
                PGT_STLFACETABP, PGT_STLVTEXTABP,
                PGT_STLEDGETABP*
        );

extern  long  pgtST_AttachSTLEdgeTab(
                PGT_STLMESHP

        );

extern  long  pgtST_DetachSTLEdgeTab(
                PGT_STLMESHP

        );


/*----- Sort Table -----*/

extern  long  pgtST_SortSTLVtexTab(
                PGT_STLVTEXTABP
        );

extern  long  pgtST_SortSTLEdgeTab(
                PGT_STLEDGETABP
        );

extern  long  pgtST_SortSTLEdgeTabByVtexID(
                PGT_STLEDGETABP
        );

extern  long  pgtST_SortSTLFaceTab(
                PGT_STLFACETABP
        );

extern  long  pgtST_SortSTLFaceTabByVtexID(
                PGT_STLFACETABP
        );

extern  long  pgtST_SortSTLFaceTabByEdgeID(
                PGT_STLFACETABP
        );

extern  long  pgtST_SortSTLFaceTabByNvecIDC(
                PGT_STLFACETABP
        );

extern  long  pgtST_SortSTLNvecTab(
                PGT_STLNVECTABP
        );

/*----- Add Relation ID -----*/

extern  long  pgtST_AddEdgeToVtex(
                long, PGT_STLVTEXP
        );

extern  long  pgtST_AddFaceToEdge(
                long, PGT_STLEDGEP
        );

extern  long  pgtST_AddFaceToVtex(
                long, PGT_STLVTEXP
        );




/*----- [Dxx] Create STL Mesh ----------------------------------------*/

extern  long  pgtST_STLFromLatticePnts(
                double[2],
                long, long, PGT_ELMPNT[],
                PGT_STLMESHP*
        );

extern  long  pgtST_STLFromRandomPnts(
                double[2],
                long, PGT_ELMPNT[],
                PGT_STLMESHP*
        );

extern  long  pgtST_InitSTLVtexTab(
                double[2],
                long, PGT_ELMPNT[],
                PGT_STLVTEXTABP*
        );

extern  long  pgtST_InitSTLFaceTab(
                double[2],
                PGT_STLVTEXTABP,
                PGT_STLFACETABP*, PGT_STLEDGETABP*
        );

extern  long  pgtST_DelaunaryTriangles(
                double[2],
                PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP
        );

extern  long  pgtST_CleanSTLFaces(
                PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP
        );

extern  long  pgtST_CreSTLMesh(
                PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP,
                PGT_STLMESHP*
        );

extern  long  pgtST_BinSortPnts(
                double[2],
                long, PGT_ELMPNT[], long,
                long*, PGT_ELMPNT**
        );

extern  long  pgtST_AddSTLFaceToTab(
                PGT_STLFACETABP,
                long, long, long, long, long, long, long, long, long,
                long,
                PGT_STLFACEP*,  long*
        );

extern  long  pgtST_AddSTLVtexToTab(
                PGT_STLVTEXTABP, PGT_PNT,
                PGT_STLVTEXP*,  long*
        );

extern  long  pgtST_AddSTLEdgeToTab(
                PGT_STLEDGETABP, long, long,
                PGT_STLEDGEP*,  long*
        );

extern  long  pgtST_AddSTLNvecToTab(
                PGT_STLNVECTABP, PGT_VEC,
                PGT_STLNVECP*,  long*
        );

extern  long  pgtST_InsertVertex(
                double[2],
                PGT_STLVTEXP,
                PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP
        );

extern  long  pgtST_SearchFace(
                double[2],
                PGT_STLVTEXP,
                PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP,
                PGT_STLFACEP*, long*, PGT_STLEDGEP*
        );

extern  long  pgtST_SplitFaceInto3(
                double[2],
                PGT_STLVTEXP, PGT_STLFACEP,
                PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP
        );

extern  long  pgtST_SplitEdge(
                PGT_STLVTEXP, PGT_STLEDGEP,
                PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP
        );

extern  long  pgtST_ExamSidePntLies(
                double[2],
                PGT_PNT, PGT_PNT, PGT_PNT,
                long*, long*
        );

extern  long  pgtST_SwapEdge(
                double[2],
                PGT_STLEDGEP,
                PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP,
                long*
        );

extern  long  pgtST_RemVirtualFace(
                PGT_STLFACETABP, long, long, long, long,
                long*
        );

extern  long  pgtST_RemVirtualEdge(
                PGT_STLEDGETABP, long, long, long, long,
                long*
        );




/*----- [Exx] STL Mesh Utility for Geometry --------------------------*/

extern  long  pgtST_IsTriangleDegenerate(
                double[2], double,
                PGT_PNT, PGT_PNT, PGT_PNT,
                long*
        );

extern  long  pgtST_IsSTLFaceDegen(
                double[2], double,
                PGT_STLFACEP, PGT_STLVTEXTABP, long,
                long*
        );

extern  long  pgtST_STLMeshFromTris(
                    long, PGT_TRIANGLE[],
                    PGT_STLMESHP*
        );

extern  long  pgtST_KnitSTLFaces(
                    double[2], double,
                    PGT_STLMESHP,
                    PGT_STLMESHP*
        );

extern  long  pgtST_KnitSTLFacesInUV(
                    double[2], double,
                    PGT_STLMESHP,
                    PGT_STLMESHP*
        );

extern  long  pgtST_RemDegenElemInSTLMesh(
                    double[2],
                    PGT_STLMESHP
        );

extern  long  pgtST_RemDegenElemInSTLMeshTOPO(
                    double[2],
                    PGT_STLMESHP
        );

extern  long  pgtST_RenumSTLMesh(
                    PGT_STLMESHP,
                    PGT_STLMESHP*
        );

extern  long  pgtST_RenumSTLMeshSELF(
                    PGT_STLMESHP
        );

extern  long  pgtST_ReverseSTLFace(
                    PGT_STLFACEP
        );

extern  long  pgtST_ReverseSTLMesh(
                    PGT_STLFACETABP
        );

extern  long  pgtST_AlignDirOfSTLFace(
                    PGT_STLFACETABP, PGT_STLEDGETABP, long,
                    long*
        );

extern  long  pgtST_GetBorderSTLEdges(
                    PGT_STLFACETABP, PGT_STLEDGETABP,
                    long, long[],
                    long*, long[], long*, long[]
        );

extern  long  pgtST_AdjBorderSTLFaceDir(
                    PGT_STLFACETABP, PGT_STLEDGETABP, long, long[]
        );

extern  long  pgtST_MMBoxForSTLMesh(
                double, PGT_STLMESHP,
                PGT_BOX*
        );

extern  long  pgtST_GravityCenterForSTLMesh(
                PGT_STLMESHP,
                PGT_PNT*
        );

extern  long  pgtST_AlignSTLMesh(
                double[2],
                PGT_STLMESHP,
                PGT_STLMESHP*
        );

extern  long  pgtST_FindStartFaceToAlign(
                double[2],
                PGT_STLMESHP,
                long*, long*
        );

extern  long  pgtST_AlignDirOfSTLFace2(
                PGT_STLFACETABP, PGT_STLEDGETABP,
                long,
                long*
        );

extern  long  pgtST_MergeSTLMeshes(         /* 2022.04.01 */
                double[2],
                double,
                long, PGT_STLMESHP[],
                PGT_STLMESHP*
        );




/*----- [Fxx] STL File I/O -------------------------------------------*/

extern  long  pgtST_WriteSimpleSTLMesh(
                char*, PGT_STLMESHP
        );

extern  long  pgtST_WriteSimpleSTLMeshFP(
                FILE*, PGT_STLMESHP
        );


/*----- Write STL Mesh -----*/

extern  long  pgtST_WriteSTLMesh(
                char[], long, PGT_STLMESHP
        );

extern  long  pgtST_WriteSTLMeshArray(
                char[], long, long, PGT_STLMESHP[]
        );


/*----- Write STL Mesh in ASCII -----*/

extern  long  pgtST_WriteSTLMeshASC(
                char[], PGT_STLMESHP
        );

extern  long  pgtST_WriteSTLMeshArrayASC(
                char[], long, PGT_STLMESHP[]
        );

extern  long  pgtST_WriteSTLMeshASCFP(
                FILE*, PGT_STLMESHP
        );

extern  long  pgtST_WriteSTLHeadASC(
                FILE*,
                PGT_STLFACETABP, PGT_STLEDGETABP,
                PGT_STLVTEXTABP, PGT_STLNVECTABP
        );

extern  long  pgtST_WriteSTLFaceTabASC(
                FILE*,
                PGT_STLFACETABP
        );

extern  long  pgtST_WriteSTLEdgeTabASC(
                FILE*,
                PGT_STLEDGETABP
        );

extern  long  pgtST_WriteSTLVtexTabASC(
                FILE*,
                PGT_STLVTEXTABP
        );

extern  long  pgtST_WriteSTLNvecTabASC(
                FILE*,
                PGT_STLNVECTABP
        );


/*----- Write STL Mesh in Binary -----*/

extern  long  pgtST_WriteSTLMeshBIN(
                char[], PGT_STLMESHP
        );

extern  long  pgtST_WriteSTLMeshArrayBIN(
                char[], long, PGT_STLMESHP[]
        );

extern  long  pgtST_WriteSTLMeshBINFP(
                FILE*, PGT_STLMESHP
        );

extern  long  pgtST_WriteSTLHeadBIN(
                FILE*,
                PGT_STLFACETABP, PGT_STLEDGETABP,
                PGT_STLVTEXTABP, PGT_STLNVECTABP
        );

extern  long  pgtST_WriteSTLFaceTabBIN(
                FILE*,
                PGT_STLFACETABP
        );

extern  long  pgtST_WriteSTLEdgeTabBIN(
                FILE*,
                PGT_STLEDGETABP
        );

extern  long  pgtST_WriteSTLVtexTabBIN(
                FILE*,
                PGT_STLVTEXTABP
        );

extern  long  pgtST_WriteSTLNvecTabBIN(
                FILE*,
                PGT_STLNVECTABP
        );


/*----- Read STL Mesh -----*/

extern  long  pgtST_ReadSTLMesh(
                char[],
                PGT_STLMESHP*
        );

extern  long  pgtST_ReadSTLMeshArray(
                char[],
                long*, PGT_STLMESHP**
        );

extern  long  pgtST_VerifyFileFormat(
                char[],
                long*
        );

extern  long  pgtST_VerifyFileFormat2(
                char[],
                long*
        );

extern  long  pgtST_ReadBinaryFP(
                FILE*, long, long,
                void*, long*
        );


/*----- Read STL Mesh in ASCII Format -----*/

extern  long  pgtST_ReadSTLMeshASC(
                char[],
                PGT_STLMESHP*
        );

extern  long  pgtST_ReadSTLMeshArrayASC(
                char[],
                long*, PGT_STLMESHP**
        );

extern  long  pgtST_ReadSTLMeshASCFP(
                FILE*,
                PGT_STLMESHP*
        );


extern  long  pgtST_ReadSTLHeadASC(
                FILE*,
                long*, long*, long*, long*
        );

extern  long  pgtST_ReadSTLFaceTabASC(
                FILE*,
                PGT_STLFACETABP*
        );

extern  long  pgtST_ReadSTLEdgeTabASC(
                FILE*,
                PGT_STLEDGETABP*
        );

extern  long  pgtST_ReadSTLVtexTabASC(
                FILE*,
                PGT_STLVTEXTABP*
        );

extern  long  pgtST_ReadSTLNvecTabASC(
                FILE*,
                PGT_STLNVECTABP*
        );


/*----- Read STL Mesh in Binary Format -----*/

extern  long  pgtST_ReadSTLMeshBIN(
                char[],
                PGT_STLMESHP*
        );

extern  long  pgtST_ReadSTLMeshArrayBIN(
                char[],
                long*, PGT_STLMESHP**
        );

extern  long  pgtST_ReadSTLMeshBINFP(
                FILE*,
                PGT_STLMESHP*
        );

extern  long  pgtST_ReadSTLHeadBIN(
                FILE*,
                long*, long*, long*, long*
        );

extern  long  pgtST_ReadSTLFaceTabBIN(
                FILE*,
                PGT_STLFACETABP*
        );

extern  long  pgtST_ReadSTLEdgeTabBIN(
                FILE*,
                PGT_STLEDGETABP*
        );

extern  long  pgtST_ReadSTLVtexTabBIN(
                FILE*,
                PGT_STLVTEXTABP*
        );

extern  long  pgtST_ReadSTLNvecTabBIN(
                FILE*,
                PGT_STLNVECTABP*
        );



/*----- [Gxx] Character Line -----------------------------------------*/

extern  long  pgtST_GetCharChain(
                PGT_STLEDGETABP, PGT_STLVTEXTABP,
                long*, PGT_STLCHAINP**
        );

extern  long  pgtST_MakeCharEdgeTab(
                PGT_STLEDGETABP,
                PGT_STLEDGETABP*
        );

extern  long  pgtST_CrePolylineFromChain(
                PGT_STLCHAINP,
                PGT_POLYLINEP*
        );

extern  long  pgtST_AllocChain(
                long,
                PGT_STLCHAINP*
        );

extern  long  pgtST_FreeChain(
                PGT_STLCHAINP*
        );




/*----- [Hxx] Knit Free Edges ----------------------------------------*/

extern  long  pgtST_KnitSTLFreeEdges(
                    double[2], double,
                    PGT_STLMESHP,
                    PGT_STLMESHP*
        );

extern  long  pgtST_FindFreeEdge(
                    PGT_STLFACETABP,
                    PGT_STLEDGETABP
        );

extern  long  pgtST_FindMultEdge(
                    PGT_STLFACETABP,
                    PGT_STLEDGETABP
        );

extern  long  pgtST_FindFreeVtex(
                    PGT_STLEDGETABP,
                    PGT_STLVTEXTABP
        );

extern  long  pgtST_MergeFreeVtexes(
                    double[2], double,
                    PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP,
                    PGT_STLVTEXTABP*
        );

extern  long  pgtST_SplitFreeEdgeByFreeVtex(
                    double[2], double,
                    PGT_STLEDGETABP, PGT_STLVTEXTABP,
                    long*, PGT_SPLITINFO**
        );

extern  long  pgtST_SplitFaceByFreeVtex(
                    double[2],
                    PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP,
                    long, PGT_SPLITINFO[],
                    PGT_STLFACETABP*
        );

extern  long  pgtST_SplitPosOnEDLine(
                    double[2], double,
                    PGT_PNT, PGT_PNT, long, PGT_ELMPNT[],
                    long*, long**
        );

extern  long  pgtST_SplitFaceTriangle(
                    double[2],
                    PGT_STLEDGETABP, PGT_STLVTEXTABP,
                    long, PGT_SPLITINFO[],
                    long, long, long,
                    long, long, long,
                    long, long, long,
                    long*, PGT_STLFACE**
        );

extern  long  pgtST_TrisFromPolyLoop(
                    double[2],
                    long, PGT_ELMPNT[], double[3],
                    long*, PGT_STLFACE**
        );




/*----- [Ixx] Normal Vectors -----------------------------------------*/

extern  long  pgtST_CreSTLNvecTab(
                double[2], double, double,
                PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP,
                PGT_STLNVECTABP*
        );

extern  long  pgtST_VerifyEdgeFold(
                double[2], double,
                PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP,
                long, long[],
                long*
        );

extern  long  pgtST_CalFoldAngle(
                double[2],
                PGT_STLVTEXTABP,
                long, long,
                long, long, long, long, long, long,
                double*
        );

extern  long  pgtST_NormDirByAverage(
                double[2],
                PGT_STLFACETABP, PGT_STLVTEXTABP,
                long, long[],
                PGT_VEC*,long*
        );

extern  long  pgtST_CreSTLNvecTabCENT(
                double[2],
                PGT_STLFACETABP, PGT_STLVTEXTABP,
                PGT_STLNVECTABP*
        );

extern  long  pgtST_CreSTLNvecTabCENT2(
                double[2], double,
                PGT_STLFACETABP, PGT_STLVTEXTABP,
                PGT_STLNVECTABP*
        );




/*----- [Jxx] Make Triangles in Polyline Loop ------------------------*/

extern  long  pgtST_VerifyPlaneOnLoop(
                double[2],
                PGT_POLYLINEP,
                long*, PGT_PLANE*, PGT_POLYLINEP*
        );

extern  long  pgtST_CreTrianglesInLoop(
                double[2],
                PGT_POLYLINEP,
                long*, PGT_TRIANGLE**
        );




/*----- [Kxx] Read and Write STL File --------------------------------*/

/*----- Read (ASCII MultiByte ) -----*/

extern  long  pgtST_ReadSTL(
                char[],
                char[80], PGT_STLMESHP*
        );

extern  long  pgtST_ReadSTLASCII(
                char[],
                char[80], PGT_STLMESHP*
        );

extern  long  pgtST_ReadSTLBINARY(
                char[],
                char[80], PGT_STLMESHP*
        );

extern  long  pgtST_CheckSTLFormat(
                char[],
                long*
        );

extern  long  pgtST_ConvertExpNotation(
                char[]
);


/*----- Write (ASCII MultiByte ) -----*/

extern  long  pgtST_WriteSTL(
                double[2], double,
                char[], long, long, char*, PGT_STLMESHP,
                long*, long*
        );

extern  long  pgtST_WriteSTLMULT(
                double[2], double,
                char[], long, long, char*, long, PGT_STLMESHP[],
                long*, long*
        );

extern  long  pgtST_WriteSTLASCII(
                double[2], double,
                char[], long, char*, PGT_STLMESHP,
                long*, long*
        );

extern  long  pgtST_WriteSTLBINARY(
                double[2], double,
                char[], long, char*, PGT_STLMESHP,
                long*, long*
        );

extern  long  pgtST_NormalByThreePos(
                double[2], double,
                PGT_PNT, PGT_PNT, PGT_PNT,
                long*, PGT_VEC*
        );




/*----- [Lxx] Slice STL Mesh -----------------------------------------*/

extern  long  pgtST_SliceSTLMesh(
                double[2],
                PGT_STLMESHP, PGT_PNT, PGT_VEC, double, double, long,
                long*, PGT_POLYLINEP**
        );

extern  long  pgtST_SetSTLVertexHeight(
                double[2],
                PGT_STLVTEXTABP, PGT_PNT, PGT_VEC
        );

extern  long  pgtST_SliceSTLMeshSingle(
                double[2],
                PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP,
                PGT_VEC, double,
                long*, PGT_POLYLINEP**
        );

extern  long  pgtST_SliceSTLEdge(
                double[2],
                PGT_STLEDGETABP, PGT_STLVTEXTABP, PGT_VEC, double
        );

extern  long  pgtST_SliceSTLEdge2(
                double[2],
                PGT_STLFACETABP, PGT_STLEDGETABP, PGT_STLVTEXTABP,
                PGT_VEC, double
        );

extern  long  pgtST_MakeSTLEdgeChain(
                double[2],
                PGT_STLFACETABP, PGT_STLEDGETABP,
                long*, PGT_STLEDIDARYP**
        );

extern  long  pgtST_SectIntoPolyline(
                double[2],
                PGT_STLEDGETABP, PGT_STLEDIDARYP,
                PGT_POLYLINEP*
        );

extern  long  pgtST_ConcatPolylines(            /* 2022.04.01 */
                double[2], double,
                long, PGT_POLYLINEP[],
                long*, PGT_POLYLINEP**
        );




/*----- [Mxx] Move STL Mesh ------------------------------------------*/

extern  long  pgtST_MoveSTLMesh(
                    double[2],
                    PGT_STLMESHP, double[4][4],
                    PGT_STLMESHP*
        );

extern  long  pgtST_MoveSTLMeshSELF(
                    double[2],
                    double[4][4],
                    PGT_STLMESHP
        );




/*----- [Nxx] Normal Dir on STL Mesh ---------------------------------*/

extern  long  pgtST_NormDirsOnSTLMesh(
                double[2],
                PGT_STLMESHP,
                long, PGT_PNT[],
                long*, PGT_VEC**
        );




/*----- [Oxx] Normal Dir on STL Mesh ---------------------------------*/

extern  long  pgtST_SmoothSTLMesh(
                double[2],
                PGT_STLMESHP,
                PGT_STLMESHP*
        );




/*----- [Pxx] Closest Point on STL Mesh ------------------------------*/

extern  long  pgtST_ClsPntToSTLMesh(         /* 2022.04.01 */
                double[2],
                PGT_STLMESHP, PGT_PNT,
                PGT_PNT*, double*, long*
        );

extern  long  pgtST_FitPntsToSTLMesh(         /* 2022.04.01 */
                double[2],
                double,
                PGT_STLMESHP, long, PGT_PNT[],
                long*, PGT_PNT**
        );




/*----- End of File --------------------------------------------------*/



#ifdef __cplusplus
}
#endif



#endif
