/***********************************************************************

    関数名 : [TSRF HD04]  pgt_tsrf_struct.h

    機  能 : ＴＳＲＦライブラリ用ヘッダファイル
             構造体の定義

    PGT TSRF Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.04.01

***********************************************************************/



#ifndef PGT_TSRF_STRUCT_H
#define PGT_TSRF_STRUCT_H



#include    "pgt_base_point.h"          /* point                      */
#include    "pgt_base_curve.h"          /* curve                      */
#include    "pgt_base_surface.h"        /* curve                      */




/*--------------------------------------------------------------------*/
/*     Split Trimmed Surf                                             */
/*--------------------------------------------------------------------*/

/*----- Edge for Split Trimmed Surf. ---------------------------------*/

typedef  struct _pgt_tsedge {

    /*----- Edge -----*/
    long            edgeID;             /* this edge ID               */
    long            useflg;             /* used flag 0;yet 1:used     */
    PGT_CURVP       uv_curv;            /* uv curve                   */
    PGT_CURVP       xyzcurv;            /* xyz curve (NULL if degen.) */

    /*----- Vertex 0 -----*/
    long            vtexID0;            /* start vertex ID            */
    long            boundF0;            /* boundary flag              */
    PGT_PNT         uv_pos0;            /* uv  position               */
    PGT_PNT         xyzpos0;            /* xyz position               */

    /*----- Vertex 1 -----*/
    long            vtexID1;            /* end vertex ID              */
    long            boundF1;            /* boundary flag              */
    PGT_PNT         uv_pos1;            /* uv  position               */
    PGT_PNT         xyzpos1;            /* xyz position               */

} PGT_TSEDGE, *PGT_TSEDGEP;



/*----- Loop : Array of Edges (Loop) ---------------------------------*/

typedef  struct _pgt_tsloop {
    long            max_size;           /* max size of this array     */
    long            idummy;             /* padding                    */
    long            nedg;               /* no. of edges               */
    long            sideF;              /* -1:unknown 0:left 1:right  */

    /*----- Edge -----*/
    PGT_TSEDGE*     ed;                 /* array of ts-edges          */
    void*           pdummy;             /* padding                    */

} PGT_TSLOOP, *PGT_TSLOOPP;



/*----- Group : Array of Loops ---------------------------------------*/

typedef  struct _pgt_tsgroup {
    long            nlop;               /* no. of loops               */
    long            idummy;             /* padding                    */
    long*           lop_index;          /* array of loop index        */
    void*           pdummy;             /* padding                    */

} PGT_TSGROUP, *PGT_TSGROUPP;




/*----- Intsec Curves between Plane and Base Surf --------------------*/

typedef  struct _pgt_tsintsec {

    /*----- in UV Space -----*/
    PGT_PNT         uv_pos;             /* intsec uv pos.             */
    double          uv_tpar;            /* intsec t parm of uv curv   */

    /*----- in XYZ Space -----*/
    PGT_PNT         xyz_pos;            /* intsec xyz pos.            */
    double          xyz_tpar;           /* intsec t parm of xyz curv  */

    /*----- Intsec Type -----*/
    long            type;               /* intsec type ( uv pos. )    */
    long            idummy;             /* padding                    */

} PGT_TSINTSEC, *PGT_TSINTSECP;



typedef  struct _pgt_tsintcrv {

    /*----- Basic Member -----*/
    PGT_CURVP       uv_baseCV;          /* intsec curve in UV  space  */
    PGT_CURVP       xyz_baseCV;         /* intsec curve ub XYZ space  */
    long            degenF;             /* if ON baseCV degenerates   */
    long            dupF;               /* if ON whole curv on seamCV */
    long            type;               /* 0:general                  */
    long            idummy;             /* 11:ubgn 12:umid 13:uend    */
                                        /* 21:vbgn 22:vmid 23:vend    */
    double          gap_dist;           /* dist between srf and crv   */

    /*----- Extension -----*/
    long            max_intsec;         /* max no. of intersects      */
    long            num_intsec;         /* no.     of intersects      */
    PGT_TSINTSEC*   ary_intsec;         /* array   of intersects      */
    void*           pdummy;             /* padding                    */

} PGT_TSINTCRV, *PGT_TSINTCRVP;




/*----- TS Fragment Vertex -------------------------------------------*/

typedef  struct _pgt_tsfragvt {

    /*----- Basic Members -----*/
    long            vtexID;             /* this vertex ID             */
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            idummy;             /* padding                    */
    PGT_PNT         uv_pnt;             /* uv_pos.                    */
    PGT_PNT         xyz_pnt;            /* xyz_pos.                   */

} PGT_TSFRAGVT, *PGT_TSFRAGVTP;




/*----- TS Fragment Edge ----------------------------------------------*/

typedef  struct _pgt_tsfraged {
    long            edgeID;             /* edge ID                    */
    long            useflg;             /* used flag                  */
    long            on_seamF;           /* if ON edge from seam line  */
    long            idummy;             /* padding                    */
    PGT_CURVP       xyz_curv;           /* xyz curve                  */
    PGT_CURVP       uv_curv;            /* uv curve                   */
    PGT_POLYLINEP   uv_poly;            /* uv polyline                */
    void*           pdummy;             /* padding                    */
    long            on_poleFS;          /* if ON start pos at pole    */
    long            on_poleFE;          /* if ON end   pos at pole    */
                                        /* 0:none 1:u0 2:u1 3:v0 4:v1 */
    long            vtexIDS;            /* start vertex ID            */
    long            vtexIDE;            /* end   vertex ID            */
    PGT_PNT         uv_posS;            /* start pos of uv curve      */
    PGT_PNT         uv_posE;            /* end   pos of uv curve      */

} PGT_TSFRAGED, *PGT_TSFRAGEDP;




/*----- TS Fragment Loop ----------------------------------------------*/

typedef  struct _pgt_tsfraglp {
    double          area;               /* area                       */
    long            innerF;             /* if ON this loop is inner   */
    long            useflg;             /* use flag                   */
    long            out_index;          /* index of outer loop        */
    long            idummy;             /* padding                    */
    PGT_POLYLINEP   cls_uvpoly;         /* closed uv polyline         */
    void*           pdummy;             /* padding                    */
    long            num_edge;           /* no. of edges in this loop  */
    long            idummy2;            /* padding                    */
    PGT_TSFRAGEDP*  ary_edge;           /* array of edges             */
    void*           pdummy2;            /* padding                    */

} PGT_TSFRAGLP, *PGT_TSFRAGLPP;




/*----- TS Fragnment Loop Group ---------------------------------------*/

typedef  struct _pgt_tsfraggr {
    long            num_loop;           /* no.   of fragment loops    */
    long            idummy;             /* padding                    */
    PGT_TSFRAGLPP*  ary_loop;           /* array of fragment loops    */
    void*           pdummy;             /* padding                    */

} PGT_TSFRAGGR, *PGT_TSFRAGGRP;




/*--------------------------------------------------------------------*/
/*     Is Trimmed Surf like Sliver ?                                  */
/*--------------------------------------------------------------------*/

/*----- TSBR Vertex --------------------------------------------------*/

typedef  struct _pgt_tsbrvtex {

    /*----- Basic Member -----*/
    long            vtexID;             /* vertex ID                  */
    long            parentID;           /* parent entity ID           */
    PGT_PNT         pnt;                /* geometry point             */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */

} PGT_TSBRVTEX, *PGT_TSBRVTEXP;




/*----- TSBR Vertex Table --------------------------------------------*/

typedef  struct _pgt_tsbrvttab {
    long            max_size;           /* max size of this table     */
    long            num_vtex;           /* no. of vetexes             */
    PGT_TSBRVTEXP*  ary_vtex;           /* vertexes                   */
    void*           pdummy;             /* ptr padding                */

} PGT_TSBRVTTAB, *PGT_TSBRVTTABP;




/*----- TSBR EDGE ----------------------------------------------------*/

typedef  struct _pgt_tsbredge {

    /*----- Basic Member -----*/
    long            edgeID;             /* edge ID                    */
    long            degenF;             /* if ON xyzcurve degenerates */
                                        /* and curve may be NULL      */
    long            parentID;           /* parent entity ID           */
    long            idummy;             /* padding                    */
    PGT_CURVP       curv;               /* geometry curve             */
    void*           pdummy;             /* padding                    */

    long            vtexID0;            /* start vertex ID            */
    long            vtexID1;            /* end   vertex ID            */
    PGT_PNT         pnt0;               /* start position             */
    PGT_PNT         pnt1;               /* end   position             */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */

} PGT_TSBREDGE, *PGT_TSBREDGEP;




/*----- TSBR Edge Table ----------------------------------------------*/

typedef  struct _pgt_tsbredtab {
    long            max_size;           /* max size of this table     */
    long            num_edge;           /* no. of edges               */
    PGT_TSBREDGEP*  ary_edge;           /* edges                      */
    void*           pdummy;             /* ptr padding                */

} PGT_TSBREDTAB, *PGT_TSBREDTABP;




/*----- Position to Split Edge ---------------------------------------*/

typedef  struct _pgt_tssplitpos {
    long            fac_index;          /* face index in shell        */
    long            lop_index;          /* loop index in face         */
    long            ced_index;          /* coedge index in loop       */
    long            num_split;          /* no. of positions to split  */
    long*           ary_vtexID;         /* vertexes to split          */
    double*         ary_tpar;           /* parameter pos.s to split   */

} PGT_TSSPLITPOS, *PGT_TSSPLITPOSP;




typedef  struct _pgt_tsedcurv {
    long            degenF;             /* degenerate flag            */
    long            idummy;             /* padding                    */
    PGT_CURVP       ed_curv;            /* edge underlying curve      */
    PGT_POLYLINEP   ed_poly;            /* edge underlying polyline   */
    long            vtexID0;            /* start  vertex ID           */
    long            vtexID1;            /* end    vertex ID           */

} PGT_TSEDCURV, *PGT_TSEDCURVP;




/*----- End of File --------------------------------------------------*/



#endif
