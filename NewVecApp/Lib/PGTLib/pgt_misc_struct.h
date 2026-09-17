/***********************************************************************

    関数名 : [MISC HD04]  pgt_misc_struct.h

    機  能 : ＭＩＳＣライブラリ用ヘッダファイル
             構造体の定義

    PGT MISC Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Yojiro Mandachi    / GeomLab        2024.07.31
    Modified  : Hiroyuki Kitazawa  / GeomLab        2025.04.12

***********************************************************************/



#ifndef PGT_MISC_STRUCT_H
#define PGT_MISC_STRUCT_H


#include    <limits.h>
#include    "pgt_base_const.h"
#include    "pgt_base_point.h"




/*----- Coordinate System --------------------------------------------*/

typedef struct  _pgt_codsys {
    double      orig[3];                /* origin                     */
    double      vec0[3];                /* 1st vector                 */
    double      vec1[3];                /* 2nd vector                 */
    double      vec2[3];                /* Normal vector              */

} PGT_CODSYS, *PGT_CODSYSP;



/*----- Points Tree --------------------------------------------------*/

typedef  struct _pgt_elmpnt {
    PGT_PNT         pnt;                /* point coordinates          */
    long            pntID;              /* point ID                   */
    long            userF;              /* user flag                  */
    double          userV0;             /* user value 0               */
    double          userV1;             /* user value 1               */
    long            countF;             /* count flag                 */
    long            sortF;              /* sort key                   */
    struct _pgt_elmpnt *  this_pntp;    /* "this" pointer as class    */
    void*           pdummy;             /* ptr padding                */

} PGT_ELMPNT, *PGT_ELMPNTP;


typedef  struct _pgt_ptnode {
    long            leafF;              /* leaf flag                  */
    long            idummy;             /* 0:has branches 1:has points*/
    PGT_BOX         mmbox;              /* min-max box of this node   */
    long            num_elmpnt;         /* no. of points              */
    long            idummy2;            /* padding                    */
    PGT_ELMPNT*     ary_elmpnt;         /* points (reference only)    */
    void*           pdummy;             /* ptr padding                */
    
    struct _pgt_ptnode *  node[8];      /* underlying node(branches)  */

} PGT_PTNODE, *PGT_PTNODEP;


typedef  struct _pgt_pntstree {
    PGT_PTNODEP     root_node;          /* root node                  */
    void*           pdummy;             /* ptr padding                */
    long            num_elmpnt;         /* no.   of element points    */
    long            idummy;             /* padding                    */
    PGT_ELMPNT*     ary_elmpnt;         /* array of element points    */
    void*           pdummy2;            /* ptr padding                */

} PGT_PNTSTREE, *PGT_PNTSTREEP;



/*----- Flex Pnts ----------------------------------------------------*/

typedef  struct _pgt_flexpnts {
    long            max_size;           /* max_size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_elmpnt;         /* no. of valid points        */
    long            idummy;             /* padding                    */
    PGT_ELMPNT*     ary_elmpnt;         /* points                     */
    void*           pdummy;             /* ptr padding                */

} PGT_FLEXPNTS, *PGT_FLEXPNTSP;



/*----- Triangles Tree -----------------------------------------------*/

typedef  struct _pgt_tristree {
    long            level;              /* level of tree              */
    long            leafF;              /* ON if this node is leaf    */
    PGT_BOX         mmbox;              /* mimmax box of this node    */
    long            num_tris;           /* no. of triangles           */
    long            idummy;             /* padding                    */
    PGT_TRIANGLE*   ary_tris;           /* triangles                  */
    void*           pdummy;             /* ptr padding                */

    struct _pgt_tristree * node[8];     /* underlying nodes(branches) */

} PGT_TRISTREE, *PGT_TRISTREEP;



/*----- Flex Triangles -----------------------------------------------*/

typedef  struct _pgt_flextris {
    long            max_size;           /* max size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_tris;           /* no. of triangles           */
    long            idummy;             /* padding                    */
    PGT_TRIANGLE*   ary_tris;           /* triangles                  */
    void*           pdummy;             /* padding                    */

} PGT_FLEXTRIS, *PGT_FLEXTRISP;



/*----- Elements Tree ------------------------------------------------*/

typedef  struct _pgt_element {
    PGT_BOX         box;                /* point coordinates          */
    long            elementID;          /* element id                 */
    long            userID;             /* user id                    */
    long            useflg;             /* user flag                  */
    long            idummy;             /* padding                    */

} PGT_ELEMENT, *PGT_ELEMENTP;


typedef  struct _pgt_elmstree {
    long            level;              /* level of tree              */
    long            leafF;              /* ON if this node is leaf    */
    PGT_BOX         mmbox;              /* mimmax box of this node    */
    long            num_element;        /* no. of elements            */
    long            idummy;             /* padding                    */
    PGT_ELEMENT*    ary_element;        /* elements                   */
    void*           pdummy;             /* ptr padding                */

    struct _pgt_elmstree * node[8];     /* underlying nodes(branches) */

} PGT_ELMSTREE, *PGT_ELMSTREEP;



/*----- Flex Elements ------------------------------------------------*/

typedef  struct _pgt_flexelms {
    long            max_size;           /* max size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_element;        /* no. of elements            */
    long            idummy;             /* padding                    */
    PGT_ELEMENT*    ary_element;        /* elements                   */
    void*           pdummy;             /* ptr padding                */

} PGT_FLEXELMS, *PGT_FLEXELMSP;



/*----- Flex Integers ------------------------------------------------*/

typedef  struct _pgt_flexints {
    long            max_size;           /* max size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_ints;           /* no. of integers            */
    long            idummy;             /* padding                    */
    long*           ary_ints;           /* integers                   */
    void*           pdummy;             /* ptr padding                */

} PGT_FLEXINTS, *PGT_FLEXINTSP;



/*----- Flex Floats --------------------------------------------------*/

typedef  struct _pgt_flexdflts {
    long            max_size;           /* max size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_flts;           /* no. of floats              */
    long            idummy;             /* padding                    */
    float*          ary_flts;           /* floats                     */
    void*           pdummy;             /* ptr padding                */

} PGT_FLEXFLTS, *PGT_FLEXFLTSP;



/*----- Flex Doubles -------------------------------------------------*/

typedef  struct _pgt_flexdbls {
    long            max_size;           /* max size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_dbls;           /* no. of doubles             */
    long            idummy;             /* padding                    */
    double*         ary_dbls;           /* doubles                    */
    void*           pdummy;             /* ptr padding                */

} PGT_FLEXDBLS, *PGT_FLEXDBLSP;



/*----- Flex Pointers ------------------------------------------------*/

typedef  struct _pgt_flexptrs {
    long            max_size;           /* max size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_ptrs;           /* no. of pointer             */
    long            idummy;             /* padding                    */
    void**          ary_ptrs;           /* pointers                   */
    void*           pdummy;             /* ptr padding                */

} PGT_FLEXPTRS, *PGT_FLEXPTRSP;



/*----- Domain -------------------------------------------------------*/

typedef  struct _pgt_polydm {

    /*----- Basic Member -----*/
    long              num_poly;         /* no. of 2D polyline         */
    long              idummy;           /* padding                    */
    PGT_POLYLINEP*    ary_poly;         /* 2D polylines               */
    void*             pdummy;           /* padding                    */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flg                   */

} PGT_POLYDM, *PGT_POLYDMP;


#define     pgt_PLDMNPOLY(p)        ( (p)->num_poly )
#define     pgt_PLDMPOLY(p,i)       ( (p)->ary_poly[(i)] )
#define     pgt_PLDMUSERID(p)       ( (p)->userID )
#define     pgt_PLDMUSEFLG(p)       ( (p)->useflg )



/*----- T Part -------------------------------------------------------*/

typedef  struct _pgt_tpart {

    /*----- Basic Member -----*/
    double          tbgn;               /* start t parameter          */
    double          tend;               /* end   t parameter          */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flg                   */

} PGT_TPART, *PGT_TPARTP;



/*----- Flex T Parts -------------------------------------------------*/

typedef  struct _pgt_flextprs {

    /*----- Basic Member -----*/
    long            max_size;           /* max_size of array          */
    long            inc_size;           /* size to increase max size  */
    long            num_part;           /* no. of parts               */
    long            idummy;             /* padding                    */
    PGT_TPART*      ary_part;           /* parts                      */
    void*           pdummy;             /* padding                    */

} PGT_FLEXTPRS, *PGT_FLEXTPRSP;



/*----- Bit Array ----------------------------------------------------*/

typedef  struct _pgt_bitary {

    /*----- Basic Member -----*/
    PGT_LONG8       num_bits;           /* no. of bits                */
    unsigned char*  ary_bits;           /* bits                       */
    void*           pdummy;             /* padding                    */

} PGT_BITARY, *PGT_BITARYP;


/* Position of Bit within Character */
#define     pgt_BITARY_IBITTOICHR(I)      ( (I) / CHAR_BIT )

/* Array Index for Character Containing Bit */
#define     pgt_BITARY_IBITTOISUB(I)      ( 1 << ( CHAR_BIT - 1 - ( (I) % CHAR_BIT ) ) )

/* Number of Characters Required to Contain Number of Bits */
#define     pgt_BITARY_NBITTONCHR(N)      ( ( ( (N) - 1) / CHAR_BIT ) + 1 )



/*----- Complex Number -----------------------------------------------*/

typedef struct  _pgt_complex {
    double      real;                   /* real part                  */
    double      imag;                   /* imaginary part             */

} PGT_COMPLEX, *PGT_COMPLEXP;




/*----- End of File --------------------------------------------------*/



#endif
