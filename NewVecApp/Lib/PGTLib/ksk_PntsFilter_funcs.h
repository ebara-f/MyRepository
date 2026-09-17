/***********************************************************************

    関数名 : [PntsFilter HD04]  pgt_PntsFilter_funcs.h

    機  能 : PntsFilter ライブラリ用ヘッダファイル

    KSK PntsFilter Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2025.07.15
    Modified  : Hiroyuki Kitazawa  / GeomLab        2025.07.15
    Modified  : Keiichirou Watanabe/ GeomLab        2025.09.03
    Modified  : Keiichirou Watanabe/ GeomLab        2025.10.08

***********************************************************************/



#ifndef KSK_PNTSFILTER_FUNCS_H
#define KSK_PNTSFILTER_FUNCS_H



#include    "ksk_PntsFilter_struct.h"



#ifdef __cplusplus
extern "C"{
#endif



/*----- Scan Line ----------------------------------------------------*/

extern  long  kskPF_CreateScanLine(
                    long, KSK_PFSCANPNT[], double,
                    KSK_PFSCANLINEP*
        );

extern  long  kskPF_FindAnyInvalidScanPnt(
                    KSK_PFSCANLINEP,
                    long*
        );

extern  long  kskPF_ClsPntToScanLine(
                    double[2],
                    PGT_PNT, KSK_PFSCANLINEP,
                    long*, PGT_PNT*, double*
        );

extern  long  kskPF_ClsPntToSubLine(
                    double[2],
                    PGT_PNT, KSK_PFSUBLINEP,
                    PGT_PNT*, double*, double*
        );

extern  long  kskPF_ClsPntToSubLine2(
                    double[2],
                    PGT_PNT, KSK_PFSUBLINEP,
                    PGT_PNT*, double*, double*
        );

extern  long  kskPF_ReadScanLinesBIN(
                    char[],
                    long*, KSK_PFSCANLINEP**
        );

extern  long  kskPF_WriteScanLinesBIN(
                    char[],
                    long, KSK_PFSCANLINEP[]
        );

extern  long  kskPF_ReadScanLineBINFP(
                    FILE*,
                    KSK_PFSCANLINEP*
        );

extern  long  kskPF_ReadSubLineBINFP(
                    FILE*,
                    KSK_PFSUBLINEP*
        );

extern  long  kskPF_WriteScanLineBINFP(
                    FILE*,
                    KSK_PFSCANLINEP
        );

extern  long  kskPF_WriteSubLineBINFP(
                    FILE*,
                    KSK_PFSUBLINEP
        );

extern  long  kskPF_AllocScanLine(
                    long,
                    KSK_PFSCANLINEP*
        );

extern  long  kskPF_FreeScanLine(
                    KSK_PFSCANLINEP*
        );

extern  long  kskPF_CopyScanLine(
                    KSK_PFSCANLINEP,
                    KSK_PFSCANLINEP*
        );

extern  long  kskPF_AllocSubLine(
                    long,
                    KSK_PFSUBLINEP*
        );

extern  long  kskPF_FreeSubLine(
                    KSK_PFSUBLINEP*
        );

extern  long  kskPF_CopySubLine(
                    KSK_PFSUBLINEP,
                    KSK_PFSUBLINEP*
        );

extern  long  kskPF_RemoveMarkedPntsScanLine(
                    KSK_PFSCANLINEP
        );

extern  long  kskPF_RemoveMarkedPntsSubLine(
                    KSK_PFSUBLINEP
        );

extern  long  kskPF_InitializeRemFlagScanLine(
                    long, KSK_PFSCANLINEP
);

extern  long  kskPF_InitializeRemFlagSubLine(
                    long, KSK_PFSUBLINEP
        );

extern  long  kskPF_ClsPntToScanLineLight(
                    double[], double, 
                    PGT_PNT, KSK_PFSCANLINEP,
                    long*, PGT_PNT*, double*
        );

extern  long  kskPF_ClsPntToSubLineLight(
                    double[], double,
                    PGT_PNT, KSK_PFSUBLINEP,
                    PGT_PNT*, double*
        );

extern  long  kskPF_MakePolylineLight(
                    double[], double,
                    PGT_POLYLINEP,
                    PGT_POLYLINEP*
        );

extern  long  kskPF_MergeSublines(
                    KSK_PFSCANLINEP
);



/*----- Points Filter ------------------------------------------------*/

/*----- Thin Out -----*/

extern  long  kskPF_ThinOutScanLine(
                    long,
                    KSK_PFSCANLINEP
        );

extern  long  kskPF_DetectThinOutScanLine(
                    long,
                    KSK_PFSCANLINEP
        );

extern  long  kskPF_DetectThinOutSubLine(
                    long,
                    KSK_PFSUBLINEP
        );

extern  long  kskPF_DetectRemovableEndPntsScanLine(
                    long, long,
                    KSK_PFSCANLINEP
        );

extern  long  kskPF_RemoveEndPntsScanLine(
                    long, long,
                    KSK_PFSCANLINEP
        );


/*----- Denoise -----*/

extern  long  kskPF_DetectRemovableTiltedPntsScanLine(
                    long, double, PGT_VEC,
                    KSK_PFSCANLINEP
        );

extern  long  kskPF_DetectRemovableTiltedPntsSubLine(
                    long, double, PGT_VEC,
                    KSK_PFSUBLINEP
        );

extern  long  kskPF_RemoveTiltedPntsScanLine(
                    long, double, PGT_VEC,
                    KSK_PFSCANLINEP
        );


extern  long  kskPF_DetectRemovableAbnormalPitchPntsScanLine(
                    double,
                    KSK_PFSCANLINEP
        );

extern  long  kskPF_DetectRemovableAbnormalPitchPntsSubLine(
                    double,
                    KSK_PFSUBLINEP
        );

extern  long  kskPF_RemoveAbnormalPitchPntsScanLine(
                    double,
                    KSK_PFSCANLINEP
        );


extern  long  kskPF_DetectRemovableDisplacedPntsScanLine(
                    double,
                    KSK_PFSCANLINEP
        );

extern  long  kskPF_DetectRemovableDisplacedPntsSubLine(
                    double,
                    KSK_PFSUBLINEP
        );

extern  long  kskPF_RemoveDisplacedPntsScanLine(
                    double,
                    KSK_PFSCANLINEP
        );


extern  long  kskPF_DetectRemovableTiltedPntsScanLineSURF(
                    double, double, PGT_VEC,
                    KSK_PFSCANLINEP, KSK_PFSCANLINEP, KSK_PFSCANLINEP
        );

extern  long  kskPF_RemoveTiltedPntsScanLineSURF(
                    double, double, PGT_VEC,
                    KSK_PFSCANLINEP, KSK_PFSCANLINEP, KSK_PFSCANLINEP,
                    KSK_PFSCANLINEP*
        );


/*----- Align -----*/
extern  long  kskPF_AlignPntsInParallelScanLine(
                    double, KSK_PFSCANLINEP, KSK_PFSCANLINEP, KSK_PFSCANLINEP,
                    KSK_PFSCANLINEP*
        );

extern  long  kskPF_ClsPntOnLinePT(
                    double[],
                    double[], double[], double[], double,
                    double*, double[], double*
        );

extern  long  kskPF_VecLenSqrd(
                    double[],
                    double*
        );

extern  long  kskPF_VecDstSqrd(
                    double[], double[],
                    double*
        );


/*----- Evaluate -----*/
extern  long  kskPF_CalcNoiseRatioScanLine(
                    long, double, KSK_PFSCANLINEP,
                    double*
        );

extern  long  kskPF_CalcErrorStdDevSubLine(
                    long, long, KSK_PFSUBLINEP,
                    double*, PGT_CURVP*
        );

extern  long  kskPF_CalcNoiseForScanLine(
                    long, KSK_PFSCANLINEP,
                    long*, double**, PGT_CURVP**
        );

extern  long kskPF_FitCurvToPntsF(
                    double[2], double,
                    long, PGT_PNT[], double[], long,
                    PGT_CURVP*
        );



/*----- Error Utility ------------------------------------------------*/

extern  long  kskPF_ErrPrint(
                    char[]
        );

extern  long  kskPF_ErrClear();




#ifdef __cplusplus
}
#endif




/*----- End of File --------------------------------------------------*/




#endif
