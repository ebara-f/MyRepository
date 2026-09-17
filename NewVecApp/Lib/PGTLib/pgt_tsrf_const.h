/***********************************************************************

    関数名 : [TSRF HD02]  pgt_tsrf_const.h

    機  能 : ＴＳＲＦライブラリ用ヘッダファイル

    PGT TSRF Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_TSRF_CONST_H
#define PGT_TSRF_CONST_H



/*----- Constants ----------------------------------------------------*/

#define     PGTTS_MAXLEN    ( 256 )     /* max length of strings      */
#define     PGTTS_PNTTOL    ( 0.0005 )  /* standard point coince tole */

#define     PGTTS_TOLCLOSE  ( 0.005 )   /* tole to detect closed surf */
#define     PGTTS_TOLPOLE   ( 0.005 )   /* tole to find pole area     */
#define     PGTTS_TOLSEAM   ( 0.005 )   /* tole to find seam area     */

#define     PGTTS_LP_UNKNOWN   ( -1 )   /* loop type unknown          */
#define     PGTTS_LP_OUTER     (  0 )   /* loop type outer            */
#define     PGTTS_LP_INNER     (  1 )   /* loop type inner            */
#define     PGTTS_LP_HBANDU    (  2 )   /* loop type head band in u   */
#define     PGTTS_LP_HBANDV    (  3 )   /* loop type head band in v   */
#define     PGTTS_LP_HBANDT    (  4 )   /* loop type head band in u&v */
#define     PGTTS_LP_POLSEM    (  5 )   /* loop type for full sphere  */
#define     PGTTS_LP_COMPLEX   (  6 )   /* loop type not classified   */

#define     PGTTS_INTCV_UNKNOWN (  -1 )     /* type unknown           */
#define     PGTTS_INTCV_GENERAL (   0 )     /* type general           */
#define     PGTTS_INTCV_UBGN    (  11 )     /* type at ubgn           */
#define     PGTTS_INTCV_UMID    (  12 )     /* type at umid           */
#define     PGTTS_INTCV_UEND    (  13 )     /* type at uend           */
#define     PGTTS_INTCV_VBGN    (  21 )     /* type at vbgn           */
#define     PGTTS_INTCV_VMID    (  22 )     /* type at vmid           */
#define     PGTTS_INTCV_VEND    (  23 )     /* type at vend           */

#define     PGTTS_SPLT_UVMINLEN ( 0.001 )   /* min edge leng in uv    */
#define     PGTTS_SPLT_UVMAXGAP ( 0.002 )   /* max gap  leng in uv    */




/*----- End of File --------------------------------------------------*/



#endif
