/***********************************************************************

    関数名 : [BASE HD02]  pgt_base_const.h

    機  能 : ＢＡＳＥライブラリ用ヘッダファイル

    PGT BASE Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_BASE_CONST_H
#define PGT_BASE_CONST_H



/*----- Constants ----------------------------------------------------*/
#define     PGT_ZEROTOL     (1.0e-6)    /* zero tolerance             */
#define     PGT_KNOTTOL     (1.0e-6)    /* knot coincident tolenrace  */

#define     PGT_MAXORD      ( 16 )      /* max. order                 */
#define     PGT_MAXORDSQ    ( 256 )     /* max. order squared         */

#define     PGT_SEGNPNT     ( 4 )       /* min. no. of sampling pnts  */

#define     PGT_PI          ( 3.1415926535897932384626434 )
#define     PGT_DTOR        ( PGT_PI/180.0 )
#define     PGT_RTOD        ( 180.0/PGT_PI )

#define     PGT_BUFFSIZE    ( 512 )     /* buffer size                */

/*----- Variable Type -----*/
#define     PGT_LONG8       long long   /* 8 byte integer             */




/*----- End of File --------------------------------------------------*/



#endif
