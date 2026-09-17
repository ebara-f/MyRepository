/***********************************************************************

    関数名 : [VM HD01]  pgt_vecmat.h

    機  能 : ＶＭライブラリ用ヘッダファイル

    PGT VM Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2023.12.11

***********************************************************************/



#ifndef PGT_VECMAT_H
#define PGT_VECMAT_H



#include    "pgt_errutil.h"



#ifdef __cplusplus      /* C linkage */
extern "C"{
#endif



/*----- Vector Processor ---------------------------------------------*/
extern  long  pgtVM_VecCpy( double[3], double[3] );
extern  long  pgtVM_VecEqt( double,    double[3], double[3] );
extern  long  pgtVM_VecLen( double[3], double*   );
extern  long  pgtVM_VecUnt( double,    double[3], double[3] );
extern  long  pgtVM_VecAdd( double[3], double[3], double[3] );
extern  long  pgtVM_VecSub( double[3], double[3], double[3] );
extern  long  pgtVM_VecInr( double[3], double[3], double*   );
extern  long  pgtVM_VecPrd( double[3], double[3], double[3] );
extern  long  pgtVM_VecDst( double[3], double[3], double*   );
extern  long  pgtVM_VecMid( double[3], double[3], double[3] );



/*----- Matrix Processor ---------------------------------------------*/
extern  long  pgtVM_MatUnt( 
                long, double* 
        );

extern  long  pgtVM_MatCpy( 
                long, long, double*, 
                double* 
        );

extern  long  pgtVM_MatAdd( 
                long, long, double*, double*, 
                double* 
        );

extern  long  pgtVM_MatSub( 
                long, long, double*, double*, 
                double* 
        );

extern  long  pgtVM_MatMlt( 
                long, long, double*, long, long, double*,
                long*, long*, double*
        );

extern  long  pgtVM_m44cpy(
                double[4][4],
                double[4][4]
        );

extern  long  pgtVM_m14x41(
                double[4], double[4], 
                double*
        );

extern  long  pgtVM_m14x44(
                double[4], double[4][4], 
                double[4]
        );

extern  long  pgtVM_m44x41(
                double[4][4], double[4], 
                double[4]
        );

extern  long  pgtVM_m44x44(
                double[4][4], double[4][4],
                double[4][4]
        );



/*----- Polynomial ---------------------------------------------------*/

extern  long  pgtVM_U0MtV0(
                long, long, double*, double, double,
                double*
        );

extern  long  pgtVM_U0MtV1(
                long, long, double*, double, double,
                double*
        );

extern  long  pgtVM_U0MtV2(
                long, long, double*, double, double,
                double*
        );

extern  long  pgtVM_U1MtV0(
                long, long, double*, double, double,
                double*
        );

extern  long  pgtVM_U1MtV1(
                long, long, double*, double, double,
                double*
        );

extern  long  pgtVM_U2MtV0(
                long, long, double*, double, double,
                double*
        );



/*----- Affin Mapping ------------------------------------------------*/

extern  long  pgtVM_AfnScale(
                double,
                double[4][4]
        );

extern  long  pgtVM_AfnPolongSym(
                double[3],
                double[4][4]
        );

extern  long  pgtVM_AfnAxisSym(
                double[3], double[3],
                double[4][4]
        );

extern  long  pgtVM_AfnMirrorSym(
                double[3], double[3],
                double[4][4]
        );

extern  long  pgtVM_AfnTranslate(
                double[3],
                double[4][4]
        );

extern  long  pgtVM_AfnRotate(
                double,
                double[3], double[3], double,
                double[4][4]
        );

extern  long  pgtVM_AfnLocalSys(
                double[3], double[3], double[3], double[3],
                double[4][4]
        );

extern  long  pgtVM_TransLocalSysAtoB(
                double,
                double[3], double[3], double[3], double[3],
                double[3], double[3], double[3], double[3],
                double[4][4]
        );



/*----- System of Linear Equations -----------------------------------*/
extern  long  pgtVM_Simult(
                double,
                long, double*, double*,
                double*
        );

extern  long  pgtVM_SimultV(
                double,
                long, double*, double*,
                double*
        );

extern  long  pgtVM_LUDecomp(
                double,
                long, double*, long*
        );

extern  long  pgtVM_LUSolve(
                double,
                long, double*, long*, double*,
                double*
        );



/*----- Inverse Matrix -----------------------------------------------*/
extern  long  pgtVM_InverseMat(
                double,
                long, double*, 
                double*
        );

extern  long  pgtVM_InverseMat44(
                double,
                double[4][4], 
                double[4][4]
        );



/*----- Bezier Matrix ------------------------------------------------*/
extern  long  pgtVM_BezierMat(
                long,
                double*
        );



/*----- Cal. Proper Values -------------------------------------------*/
extern  long  pgtVM_Jacobi(
                double,
                long, double*,
                double*, double*
        );



/*----- End of File --------------------------------------------------*/



#ifdef __cplusplus      /* C linkage */
}
#endif



#endif
