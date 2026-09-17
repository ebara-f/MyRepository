/***********************************************************************

    関数名 : [ERR HD01]  pgt_errutil.h

    機  能 : ＥＲＲライブラリ用ヘッダファイル

    PGT ERR Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2025.04.07

***********************************************************************/



#ifndef PGT_ERRUTIL_H
#define PGT_ERRUTIL_H



#ifdef __cplusplus      /* C linkage */
extern "C"{
#endif



/*----- Error Utility ------------------------------------------------*/
extern long pgtER_ErrPush ( char*, long, char* );
extern long pgtER_ErrPop  ( char**, long*, char** );
extern long pgtER_ErrPrint( char* );
extern long pgtER_ErrClear( void );
extern long pgtER_IsMemoryShort( long*);
extern long pgtER_ErrNum( long*);
extern long pgtER_ErrInfo( long, char[35], long*, char[76] );



/*----- Interrupt ----------------------------------------------------*/
extern long pgtER_PeekBreakFlag( long, long*);



/*----- Keep Element IDs ---------------------------------------------*/
extern long pgtER_ElmIDClear( void );
extern long pgtER_ElmIDPush ( long, long, long, long, long*);
extern long pgtER_ElmIDCount( long*);
extern long pgtER_ElmIDGet  ( long, long*, long*, long*, long*);
extern long pgtER_ElmIDPush2( long, long, long, long, double[3], long*);
extern long pgtER_ElmIDGet2 ( long, long*, long*, long*, long*, double[3] );

extern long pgtER_ElmIDPush3(
                    long, long, long, long, long, long,
                    double, double, double[3],
                    long*
        );

extern long pgtER_ElmIDGet3 (
                    long,
                    long*, long*, long*, long*, long*, long*,
                    double*, double*, double[3]
        );

/*----- Element Type -----*/
#define     PGT_ELID_NOTYPE             (   0 )

#define     PGT_ELID_PNT                ( 111 )
#define     PGT_ELID_CURV               ( 112 )
#define     PGT_ELID_SURF               ( 113 )
#define     PGT_ELID_TSRF               ( 114 )

#define     PGT_ELID_VERTEX             ( 121 )
#define     PGT_ELID_EDGE               ( 122 )
#define     PGT_ELID_COEDGE             ( 123 )
#define     PGT_ELID_LOOP               ( 124 )
#define     PGT_ELID_FACE               ( 125 )
#define     PGT_ELID_SHELL              ( 126 )
#define     PGT_ELID_VOLUME             ( 127 )

#define     PGT_ELID_STLMESH            ( 131 )
#define     PGT_ELID_STLFACE            ( 132 )
#define     PGT_ELID_STLEDGE            ( 133 )
#define     PGT_ELID_STLVTEX            ( 134 )

#define     PGT_ELID_PART               ( 141 )
#define     PGT_ELID_INSTANCE           ( 142 )
#define     PGT_ELID_ASSEMBLY           ( 143 )

/*----- Reason Flag -----*/
#define     PGT_ELID_NOREASON           (   0 )
#define     PGT_ELID_WARNING            ( 101 )
#define     PGT_ELID_ERROR              ( 102 )





#ifdef __cplusplus      /* C linkage */
}
#endif



#endif
