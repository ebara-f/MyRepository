/***********************************************************************

    関数名 : [PntsFilter HD03]  pgt_PntsFilter_struct.h

    機  能 : PntsFilter ライブラリ用ヘッダファイル
             構造体の定義

    KSK PntsFilter Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2025.07.15
    Modified  : Hiroyuki Kitazawa  / GeomLab        2025.08.02
    Modified  : Keiichirou Watanabe/ GeomLab        2025.09.03

***********************************************************************/



#ifndef KSK_PNTSFILTER_STRUCT_H
#define KSK_PNTSFILTER_STRUCT_H




/*----- Scan Line ----------------------------------------------------*/

/*----- Scan Point -----*/

typedef  struct _ksk_pfscanpnt {

    /*----- Basic Member -----*/
    PGT_PNT         pnt;                /* point                      */
    long            orig_idx;           /* original index at scanline */
    long            orig_idx_scanline;  /* original index of scanline */
    long            invalidF;           /* if ON, invalid             */
    long            modifyF;            /* if ON, modified            */

    /*----- Extension -----*/
    long            removeF;            /* if ON, removed             */
    long            userF;              /* flag for user              */
    PGT_VEC         nvec;               /* normal dir.                */

} KSK_PFSCANPNT, *KSK_PFSCANPNTP;


/*----- Scan Sub Line -----*/

typedef  struct _ksk_pfsubline {

    /*----- Basic Member -----*/
    long            num_scanpnt;        /* no. of point               */
    long            idummy;             /* padding                    */
    KSK_PFSCANPNT*  ary_scanpnt;        /* points                     */
    void*           pdummy;             /* ptr padding                */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */

} KSK_PFSUBLINE, *KSK_PFSUBLINEP;


/*----- Scan Line -----*/

typedef  struct _ksk_pfscanline {

    /*----- Basic Member -----*/
    long            scanlineID;         /* unique ID                  */
    long            num_subline;        /* no. of sub line            */
    KSK_PFSUBLINEP* ary_subline;        /* sub lines                  */
    void*           pdummy;             /* ptr padding                */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */

} KSK_PFSCANLINE, *KSK_PFSCANLINEP;




/*----- End of File --------------------------------------------------*/



#endif
