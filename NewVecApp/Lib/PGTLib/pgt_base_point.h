/***********************************************************************

    関数名 : [BASE HD03]  pgt_base_point.h

    機  能 : ＢＡＳＥライブラリ用ヘッダファイル
             点の構造体

    PGT BASE Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_BASE_POINT_H
#define PGT_BASE_POINT_H




/*--------------------------------------------------------------------*/
/*     Basic Geometry                                                 */
/*--------------------------------------------------------------------*/

/*----- Vector -------------------------------------------------------*/

typedef  struct _pgt_vec {
    double          veccod[3];          /* x,y,z                      */

} PGT_VEC, *PGT_VECP;



/*----- Point --------------------------------------------------------*/

typedef PGT_VEC     PGT_PNT;
typedef PGT_VECP    PGT_PNTP;



/*----- LC Point -----------------------------------------------------*/

typedef  struct _pgt_lcpnt {

    /*----- Basic Members -----*/
    PGT_PNT         pnt;                /* x,y,z                      */

    /*----- Extension -----*/
    long            lay_no;             /* layer no.                  */
    long            icolor;             /* color char[4] r.g.b.a      */

} PGT_LCPNT, *PGT_LCPNTP;


#define  pgt_LCPNTCOD(p,k)      ( (p)->pnt.veccod[(k)] )
#define  pgt_LCPNT(p)           ( (p)->pnt )

#define  pgt_LCPNTLAYNO(P)      ( (P)->lay_no )
#define  pgt_LCPNTICOLOR(P)     ( (P)->icolor )



/*----- Points(box) --------------------------------------------------*/

typedef  struct _pgt_box {
    double          minpos[3];          /* min. position of box       */
    double          maxpos[3];          /* max. position of box       */

} PGT_BOX, *PGT_BOXP;



/*----- Points(Polyline) ---------------------------------------------*/

typedef  struct _pgt_polyline {

    /*----- Basic Members -----*/
    long            npnt;               /* no. of points              */
    long            idummy;             /* padding                    */
    PGT_PNT*        ary_pnt;            /* points                     */
    void*           pdummy;             /* ptr padding                */

    /*----- Extension -----*/
    long            lay_no;             /* layer no.                  */
    long            icolor;             /* color char[4] r.g.b.a      */

} PGT_POLYLINE, *PGT_POLYLINEP;


#define  pgt_POLYNPNT(p)        ( (p)->npnt )
#define  pgt_POLYCOD(p,n,k)     ( (p)->ary_pnt[(n)].veccod[(k)] )

#define  pgt_POLYLAYNO(P)       ( (P)->lay_no )
#define  pgt_POLYICOLOR(P)      ( (P)->icolor )

#define  pgt_POLYCODP(p)        ( (p)->ary_pnt )



/*----- Points(Triangle) ---------------------------------------------*/

typedef  struct _pgt_triangle {

    /*----- Basic Membere -----*/
    long            triID;              /* triangle ID                */

    long            vtexID0;            /* vertex ID 0                */
    long            vtexID1;            /* vertex ID 1                */
    long            vtexID2;            /* vertex ID 2                */

    double          pos0[3];            /* vertex position 0          */
    double          pos1[3];            /* vertex position 1          */
    double          pos2[3];            /* vertex position 2          */

    /*----- Extension -----*/
    PGT_BOX         mmbox;              /* min-max box                */
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */

} PGT_TRIANGLE, *PGT_TRIANGLEP;



/*--------------------------------------------------------------------*/
/*     Flex Array of Polylines                                        */
/*--------------------------------------------------------------------*/

/*----- Element Polyline ---------------------------------------------*/

typedef  struct _pgt_elmpoly {
    PGT_POLYLINEP   poly;               /* polyline (don't free)      */
    void*           pdummy;             /* ptr padding                */
    long            polyID;             /* polyline ID                */
    long            userF;              /* user flag                  */
    long            useflg;             /* used flag                  */
    long            idummy;             /* padding                    */

} PGT_ELMPOLY, *PGT_ELMPOLYP;



/*----- Flex Array of Polylines --------------------------------------*/

typedef  struct _pgt_flexpolys {
    long            max_size;           /* max_size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_elmpoly;        /* no. of valid polylines     */
    long            idummy;             /* padding                    */
    PGT_ELMPOLY*    ary_elmpoly;        /* polylines                  */
    void*           pdummy;             /* ptr padding                */

} PGT_FLEXPOLYS, *PGT_FLEXPOLYSP;




/*----- End of File --------------------------------------------------*/

#endif
