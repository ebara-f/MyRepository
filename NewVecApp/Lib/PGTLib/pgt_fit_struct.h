/***********************************************************************

    関数名 : [FIT HD04]  pgt_fit_struct.h

    機  能 : ＦＩＴライブラリ用ヘッダファイル
             構造体の定義

    PGT FIT Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_FIT_STRUCT_H
#define PGT_FIT_STRUCT_H



#include    "pgt_base.h"



/*----- Polyline From Curve ------------------------------------------*/

typedef  struct _pgt_ftdigit {
    double          cod[3];             /* passing points             */
    double          tpar;               /* parameter position         */
    double          rho;                /* curvature                  */
    double          acc_area;           /* accumulated curvature area */

} PGT_FTDIGIT, *PGT_FTDIGITP;




/*----- Tree Structure of Part Surface -------------------------------*/

typedef  struct _pgt_sfnode {
    long            level;              /* level of tree              */
    long            leafF;              /* ON if this node is leaf    */
    double          uu0;                /* u lower                    */
    double          uu1;                /* u upper                    */
    double          vv0;                /* v lower                    */
    double          vv1;                /* v upper                    */
    PGT_SURFP       surf;               /* part surface               */
    void*           pdummy;             /* padding                    */

    struct _pgt_sfnode* node[2];        /* underlying nodes           */

} PGT_SFNODE, *PGT_SFNODEP;


typedef  struct _pgt_movpos {

    /*----- from Original Surface Corner -----------------------------*/
    long            orig_index;         /* index of orig. surface     */
    long            cornerF;            /* corner 0:00 1:10 2:01 3:11 */
    PGT_PNT         orig_pos;           /* original pos.              */

    /*----- to Next Suface Boundary ----------------------------------*/
    long            next_index;         /* index of next surface      */
    long            boundF;             /* boundary flag              */

    /*----- user data ------------------------------------------------*/
    double          userV0;             /* user value 0               */

} PGT_MOVPOS, *PGT_MOVPOSP;




/*----- End of File --------------------------------------------------*/



#endif
