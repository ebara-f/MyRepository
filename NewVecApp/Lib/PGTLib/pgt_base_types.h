/***********************************************************************

    関数名 : [BASE HD02]  pgt_base_types.h

    機  能 : ＢＡＳＥライブラリ用ヘッダファイル
             曲線曲面の構造体用フラグ

    PGT BASE Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_BASE_TYPES_H 
#define PGT_BASE_TYPES_H 



/*----- Close Flag ---------------------------------------------------*/
typedef enum _pgt_clsflg {
    PGT_CLSFLG_UNKNOWN = -1,
    PGT_CLSFLG_OPEN,
    PGT_CLSFLG_CLOSE,
    PGT_CLSFLG_PERIODIC
} PGT_CLSFLG ; 



/*----- Rational Flag ------------------------------------------------*/
typedef enum _pgt_ratflg {
    PGT_RATFLG_UNKNOWN = -1,
    PGT_RATFLG_NONE,
    PGT_RATFLG_RATIONAL
} PGT_RATFLG ;



/*----- Pole Flag ----------------------------------------------------*/
typedef enum _pgt_polflg {
    PGT_POLFLG_UNKNOWN = -1,
    PGT_POLFLG_NONE,
    PGT_POLFLG_START,
    PGT_POLFLG_END,
    PGT_POLFLG_BOTH
} PGT_POLFLG ;



/*----- Plane Flag ---------------------------------------------------*/
typedef enum _pgt_plnflg {
    PGT_PLNFLG_UNKNOWN = -1,
    PGT_PLNFLG_NONE,
    PGT_PLNFLG_PLANAR
} PGT_PLNFLG ;



/*----- Curve Type ---------------------------------------------------*/
typedef enum _pgt_cvtype {
    PGT_CVTYPE_UNKNOWN = -1,
    PGT_CVTYPE_GENERAL,
    PGT_CVTYPE_LINE,
    PGT_CVTYPE_CIRCLE,
    PGT_CVTYPE_ELLIPSE,
    PGT_CVTYPE_PARABOLA,
    PGT_CVTYPE_HYPERBOLA
} PGT_CVTYPE ;



/*----- Surface Type -------------------------------------------------*/
typedef enum _pgt_sftype {
    PGT_SFTYPE_UNKNOWN = -1,
    PGT_SFTYPE_GENERAL,
    PGT_SFTYPE_PLANE,
    PGT_SFTYPE_CYLINDER,
    PGT_SFTYPE_CONE,
    PGT_SFTYPE_SPHERE,
    PGT_SFTYPE_TORUS
} PGT_SFTYPE ;



/*----- End of File --------------------------------------------------*/



#endif
