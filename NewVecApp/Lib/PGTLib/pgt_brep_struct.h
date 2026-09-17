/***********************************************************************

    関数名 : [BREP HD04]  pgt_brep_struct.h

    機  能 : ＢＲＥＰライブラリ用ヘッダファイル
             構造体の定義

    PGT BREP Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2022.07.15
    Modified  : Yojiro Mandachi    / GeomLab        2023.03.07

***********************************************************************/



#ifndef PGT_BREP_STRUCT_H
#define PGT_BREP_STRUCT_H



#include    "pgt_base_point.h"          /* point                      */
#include    "pgt_base_curve.h"          /* curve                      */
#include    "pgt_base_surface.h"        /* surface                    */
#include    "pgt_stl_struct.h"          /* slt mesh                   */







/*--------------------------------------------------------------------*/
/*    For Any Entity from Other System                                */
/*--------------------------------------------------------------------*/

typedef     void*   PGT_BRVOIDP;



/*--------------------------------------------------------------------*/
/*    BREP Relation                                                   */
/*--------------------------------------------------------------------*/

/*----- Edge ID Array ------------------------------------------------*/

typedef  struct _pgt_bredidelem {
    long        edgeID;                 /* edge ID                    */
    long        termF;                  /* terminal flag 0:start 1:end*/

} PGT_BREDIDELEM, *PGT_BREDIDELEMP;


typedef  struct _pgt_bredidary {
    long            max_size;           /* max size of this array     */
    long            num_elem;           /* no. of edges               */
    PGT_BREDIDELEM* ary_elem;           /* edges                      */
    void*           pdummy;             /* ptr padding                */

} PGT_BREDIDARY, *PGT_BREDIDARYP;


#define     pgt_EARYMAXSIZE(P)      ( (P)->max_size )
#define     pgt_EARYNEDGE(P)        ( (P)->num_elem )
#define     pgt_EARYEDELEM(P,N)     ( (P)->ary_elem[(N)]  )
#define     pgt_EARYEDGEID(P,N)     ( (P)->ary_elem[(N)].edgeID )
#define     pgt_EARYTERMF(P,N)      ( (P)->ary_elem[(N)].termF )


/*----- Coedge ID Array ----------------------------------------------*/

typedef  struct _pgt_brceidelem {
    long            coedgeID;           /* coedge ID                  */
    long            revflg;             /* reversed flag              */
    long            faceID;             /* parent face ID             */
    long            loopID;             /* parent loop ID             */

} PGT_BRCEIDELEM, *PGT_BRCEIDELEMP;


typedef  struct _pgt_brceidary {
    long            max_size;           /* max size of this array     */
    long            num_elem;           /* no. of coedges             */
    PGT_BRCEIDELEM* ary_elem;           /* coedges                    */
    void*           pdummy;             /* ptr padding                */

} PGT_BRCEIDARY, *PGT_BRCEIDARYP;


#define     pgt_CARYMAXSIZE(P)      ( (P)->max_size )
#define     pgt_CARYNCOED(P)        ( (P)->num_elem )
#define     pgt_CARYCEELEM(P,N)     ( (P)->ary_elem[(N)]  )
#define     pgt_CARYCOEDID(P,N)     ( (P)->ary_elem[(N)].coedgeID )
#define     pgt_CARYREVFLG(P,N)     ( (P)->ary_elem[(N)].revflg )
#define     pgt_CARYFACEID(P,N)     ( (P)->ary_elem[(N)].faceID )
#define     pgt_CARYLOOPID(P,N)     ( (P)->ary_elem[(N)].loopID )


/*----- Face ID Array ------------------------------------------------*/

typedef  struct _pgt_brfcidelem {
    long            faceID;             /* face ID                    */
    long            idummy;             /* padding                    */

} PGT_BRFCIDELEM, *PGT_BRFCIDELEMP;


typedef  struct _pgt_brfcidary {
    long            max_size;           /* max size of this array     */
    long            num_elem;           /* no. of faces               */
    PGT_BRFCIDELEM* ary_elem;           /* faces                      */
    void*           pdummy;             /* ptr padding                */

} PGT_BRFCIDARY, *PGT_BRFCIDARYP;


#define     pgt_FARYMAXSIZE(P)      ( (P)->max_size )
#define     pgt_FARYNFACE(P)        ( (P)->num_elem )
#define     pgt_FARYFCELEM(P,N)     ( (P)->ary_elem[(N)]  )
#define     pgt_FARYFACEID(P,N)     ( (P)->ary_elem[(N)].faceID )



/*--------------------------------------------------------------------*/
/*     BREP Tables                                                    */
/*--------------------------------------------------------------------*/

/*----- Vertex with Point --------------------------------------------*/

typedef  struct _pgt_brvtex {

    /*----- Basic Member -----*/
    long            vtexID;             /* vertex ID                  */
    long            parentID;           /* parent entity ID           */
    PGT_PNT         pnt;                /* geometry point             */
    PGT_PNT         pntSB;              /* geometry point (sub)       */

    /*----- Relation -----*/
    PGT_BREDIDARYP  edidary;            /* array of edges at this vtx.*/
    PGT_BRFCIDARYP  fcidary;            /* array of faces at this vtx.*/

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            useflgA;            /* used flag (sub)            */
    long            useflgB;            /* used flag (sub)            */

    long            lay_no;             /* layer no.                  */
    long            icolor;             /* color char[4] r.g.b.a      */
    long            insertF;            /* for ps ring edge           */
    long            idummy2;            /* padding                    */

    PGT_BRVOIDP     userVT;             /* user vertex entity         */
    PGT_BRVOIDP     userPT;             /* user point  entity         */

} PGT_BRVTEX, *PGT_BRVTEXP;


#define     pgt_BRVTEX_SZ           ( sizeof( PGT_BRVTEX ) )

#define     pgt_VTTHISID(P)         ( (P)->vtexID   )
#define     pgt_VTPARENTID(P)       ( (P)->parentID )
#define     pgt_VTPNT(P)            ( (P)->pnt      )
#define     pgt_VTPNTSB(P)          ( (P)->pntSB    )

#define     pgt_VTEDIDARY(P)        ( (P)->edidary  )
#define     pgt_VTFCIDARY(P)        ( (P)->fcidary  )

#define     pgt_VTUSERID(P)         ( (P)->userID   )
#define     pgt_VTUSEFLG(P)         ( (P)->useflg   )
#define     pgt_VTUSEFLGA(P)        ( (P)->useflgA  )
#define     pgt_VTUSEFLGB(P)        ( (P)->useflgB  )

#define     pgt_VTLAYNO(P)          ( (P)->lay_no   )
#define     pgt_VTICOLOR(P)         ( (P)->icolor   )
#define     pgt_VTINSERTF(P)        ( (P)->insertF  )

#define     pgt_VTUSERVT(P)         ( (P)->userVT   )
#define     pgt_VTUSERPT(P)         ( (P)->userPT   )


/*----- Vertex Table -------------------------------------------------*/

typedef  struct _pgt_brvtextab {
    long            max_size;           /* max size of this table     */
    long            num_vtex;           /* no. of vetexes             */
    PGT_BRVTEXP*    ary_vtex;           /* vertexes                   */
    void*           pdummy;             /* ptr padding                */

} PGT_BRVTEXTAB, *PGT_BRVTEXTABP;


#define     pgt_VTABMAXSIZE(P)      ( (P)->max_size )
#define     pgt_VTABNVTEX(P)        ( (P)->num_vtex )
#define     pgt_VTABVTEXARY(P)      ( (P)->ary_vtex )
#define     pgt_VTABVTEX(P,N)       ( (P)->ary_vtex[(N)] )


/*----- EDGE with Curve ----------------------------------------------*/

/**********************************************************************/
/*     Direction of Edge is same as direction of underlying curve.    */
/*     Edge is compoesd of whole of underlying curve.                 */
/*                                                                    */
/*     If edge degenerates in xyz space degenerate flag will be ON    */
/*     and underlying curve may be NULL. Vertex IDs are same.         */
/**********************************************************************/

typedef  struct _pgt_bredge {

    /*----- Basic Member -----*/
    long            edgeID;             /* edge ID                    */
    long            degenF;             /* if ON xyzcurve degenerates */
                                        /* and curve may be NULL      */
    long            parentID;           /* parent entity ID           */
    long            idummy;             /* padding                    */
    PGT_CURVP       curv;               /* geometry curve             */
    PGT_CURVP       curvSB;             /* geometry curve (sub)       */

    long            vtexID0;            /* start vertex ID            */
    long            vtexID1;            /* end   vertex ID            */
    PGT_PNT         pnt0;               /* start position             */
    PGT_PNT         pnt1;               /* end   position             */

    /*----- Relation -----*/
    PGT_BRFCIDARYP  fcidary;            /* array of faces at this edg.*/
    PGT_BRCEIDARYP  ceidary;            /* array of coedges           */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            useflgA;            /* used flag (sub)            */
    long            useflgB;            /* used flag (sub)            */
    
    long            lay_no;             /* layer no.                  */
    long            icolor;             /* color char[4] r.g.b.a      */

    PGT_BRVOIDP     userVT0;            /* user vertex entity         */
    PGT_BRVOIDP     userVT1;            /* user vertxe entity         */
    PGT_BRVOIDP     userED;             /* user edge entity           */
    PGT_BRVOIDP     userCV;             /* user curv entity           */

} PGT_BREDGE, *PGT_BREDGEP;


#define     pgt_BREDGE_SZ           ( sizeof( PGT_BREDGE ) )

#define     pgt_EDTHISID(P)         ( (P)->edgeID   )
#define     pgt_EDDEGENF(P)         ( (P)->degenF   )
#define     pgt_EDPARENTID(P)       ( (P)->parentID )
#define     pgt_EDCURV(P)           ( (P)->curv     )
#define     pgt_EDCURVSB(P)         ( (P)->curvSB   )
#define     pgt_EDVTEXID0(P)        ( (P)->vtexID0  )
#define     pgt_EDVTEXID1(P)        ( (P)->vtexID1  )

#define     pgt_EDPNT0(P)           ( (P)->pnt0     )
#define     pgt_EDPNT1(P)           ( (P)->pnt1     )

#define     pgt_EDFCIDARY(P)        ( (P)->fcidary  )
#define     pgt_EDCEIDARY(P)        ( (P)->ceidary  )

#define     pgt_EDUSERID(P)         ( (P)->userID   )
#define     pgt_EDUSEFLG(P)         ( (P)->useflg   )
#define     pgt_EDUSEFLGA(P)        ( (P)->useflgA  )
#define     pgt_EDUSEFLGB(P)        ( (P)->useflgB  )

#define     pgt_EDLAYNO(P)          ( (P)->lay_no   )
#define     pgt_EDICOLOR(P)         ( (P)->icolor   )

#define     pgt_EDUSERVT0(P)        ( (P)->userVT0  )
#define     pgt_EDUSERVT1(P)        ( (P)->userVT1  )
#define     pgt_EDUSERED(P)         ( (P)->userED   )
#define     pgt_EDUSERCV(P)         ( (P)->userCV   )


/*----- Edge Table ---------------------------------------------------*/

typedef  struct _pgt_bredgetab {
    long            max_size;           /* max size of this table     */
    long            num_edge;           /* no. of edges               */
    PGT_BREDGEP*    ary_edge;           /* edges                      */
    void*           pdummy;             /* ptr padding                */

} PGT_BREDGETAB, *PGT_BREDGETABP;


#define     pgt_ETABMAXSIZE(P)      ( (P)->max_size )
#define     pgt_ETABNEDGE(P)        ( (P)->num_edge )
#define     pgt_ETABEDGEARY(P)      ( (P)->ary_edge )
#define     pgt_ETABEDGE(P,N)       ( (P)->ary_edge[(N)] )


/*----- Coedge -------------------------------------------------------*/

/**********************************************************************/
/*     Direction of UV curve and uv points are same as LOOP direction.*/
/*     If reversed flag is ON  direction of uv_curve is opposite to   */
/*     direction of edge underlying curve.                            */
/*                                                                    */
/*     Coedge on Degenerate Edge                                      */
/*     At that time  xyz_degenF is ON and xyz_pnt may be set.         */
/*     NULL(-1) is set as edgeID.                                     */
/**********************************************************************/

typedef  struct _pgt_brcoedge {

    /*----- Basic Member -----*/
    long            coedgeID;           /* this coedge ID             */
    long            edgeID;             /* underlying EDGE ID         */
    long            revflg;             /* reversed flag              */
    long            degenF;             /* xyz curve degenerate flag  */

    PGT_CURVP       uv_curv;            /* uv curve                   */
    PGT_POLYLINEP   uv_poly;            /* uv polyline                */
    PGT_PNT         uv_pnt0;            /* start position in uv space */
    PGT_PNT         uv_pnt1;            /* end   position in uv space */

    PGT_PNT         xyz_pnt;            /* degenerate point in xyz    */
    PGT_CURVP       xyz_curv;           /* xyz curve                  */
    void*           pdummy;             /* ptr padding                */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            useflgA;            /* used flag (sub)            */
    long            useflgB;            /* used flag (sub)            */

    PGT_BRVOIDP     userCE;             /* user coedge   entity       */
    PGT_BRVOIDP     userED;             /* user edge     entity       */
    PGT_BRVOIDP     userUV;             /* user uv  curv entity       */
    PGT_BRVOIDP     userCV;             /* user xyz curv entity       */

} PGT_BRCOEDGE, *PGT_BRCOEDGEP;


#define     pgt_COEDGE_SZ           ( sizeof( PGT_BRCOEDGE ) )

#define     pgt_CETHISID(P)         ( (P)->coedgeID )
#define     pgt_CEEDGEID(P)         ( (P)->edgeID   )
#define     pgt_CEREVFLG(P)         ( (P)->revflg   )
#define     pgt_CEDEGENF(P)         ( (P)->degenF   )

#define     pgt_CEUVCURV(P)         ( (P)->uv_curv  )
#define     pgt_CEUVPOLY(P)         ( (P)->uv_poly  )
#define     pgt_CEUVPNT0(P)         ( (P)->uv_pnt0  )
#define     pgt_CEUVPNT1(P)         ( (P)->uv_pnt1  )
#define     pgt_CEXYZPNT(P)         ( (P)->xyz_pnt  )
#define     pgt_CE3DCURV(P)         ( (P)->xyz_curv )

#define     pgt_CEUSERID(P)         ( (P)->userID   )
#define     pgt_CEUSEFLG(P)         ( (P)->useflg   )
#define     pgt_CEUSEFLGA(P)        ( (P)->useflgA  )
#define     pgt_CEUSEFLGB(P)        ( (P)->useflgB  )

#define     pgt_CEUSERCE(P)         ( (P)->userCE   )
#define     pgt_CEUSERUV(P)         ( (P)->userUV   )
#define     pgt_CEUSERED(P)         ( (P)->userED   )
#define     pgt_CEUSERCV(P)         ( (P)->userCV   )


/*----- Loop ---------------------------------------------------------*/

/**********************************************************************/
/*     First loop must be outer loop in a face.                       */
/*     If a man walks on a surface along loop  domain is on left      */
/*     side of the man.                                               */
/**********************************************************************/

typedef  struct  _pgt_brloop {

    /*----- Basic Member -----*/
    long            loopID;             /* this loop ID               */
    long            idummy;             /* padding                    */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            useflgA;            /* used flag (sub)            */
    long            useflgB;            /* used flag (sub)            */

    PGT_BRVOIDP     userLP;             /* user loop entity           */
    void*           pdummy;             /* ptr padding                */

    /*----- Underlying Coedges -----*/
    long            num_coed;           /* no. of coedges             */
    long            idummy2;            /* padding                    */
    PGT_BRCOEDGEP*  ary_coed;           /* coedges                    */
    void*           pdummy2;            /* ptr padding                */

} PGT_BRLOOP, *PGT_BRLOOPP;


#define     pgt_LPTHISID(P)         ( (P)->loopID  )

#define     pgt_LPUSERID(P)         ( (P)->userID  )
#define     pgt_LPUSEFLG(P)         ( (P)->useflg  )
#define     pgt_LPUSEFLGA(P)        ( (P)->useflgA )
#define     pgt_LPUSEFLGB(P)        ( (P)->useflgB )

#define     pgt_LPUSERLP(P)         ( (P)->userLP  )

#define     pgt_LPNCOED(P)          ( (P)->num_coed )
#define     pgt_LPCOEDARY(P)        ( (P)->ary_coed )
#define     pgt_LPCOED(P,N)         ( (P)->ary_coed[(N)] )


/*----- Face ---------------------------------------------------------*/

/**********************************************************************/
/*     Direction of Face is same as direction of surface.             */
/*     Surface direction is defined by Pu x Pv.                       */
/**********************************************************************/

typedef  struct  _pgt_brface {

    /*----- Basic Member -----*/
    long            faceID;             /* this face ID               */
    long            sh_revflg;          /* reversed flag to shell     */
    long            periodF;            /* periodic flag              */
    long            idummy;             /* padding                    */

    /*----- Underlying Loops -----*/
    long            num_loop;           /* no. of loops               */
    long            idummy2;            /* padding                    */
    PGT_BRLOOPP*    ary_loop;           /* loops                      */
    void*           pdummy2;            /* ptr padding                */

    /*----- Underlying Surface -----*/
    PGT_SURFP       surf;               /* geometry surface           */
    PGT_SURFP       surfSB;             /* geometry surface (sub)     */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            useflgA;            /* used flag (sub)            */
    long            useflgB;            /* used flag (sub)            */

    long            lay_no;             /* layer no.                  */
    long            icolor;             /* color char[4] r.g.b.a      */

    PGT_BRVOIDP     userFC;             /* user face entity           */
    PGT_BRVOIDP     userSF;             /* user surf entity           */

} PGT_BRFACE, *PGT_BRFACEP;


#define     pgt_FCTHISID(P)         ( (P)->faceID    )
#define     pgt_FCREVFLG(P)         ( (P)->sh_revflg )
#define     pgt_FCPERIODF(P)        ( (P)->periodF   )

#define     pgt_FCNLOOP(P)          ( (P)->num_loop )
#define     pgt_FCLOOPARY(P)        ( (P)->ary_loop )
#define     pgt_FCLOOP(P,N)         ( (P)->ary_loop[(N)] )

#define     pgt_FCSURF(P)           ( (P)->surf     )
#define     pgt_FCSURFSB(P)         ( (P)->surfSB   )

#define     pgt_FCUSERID(P)         ( (P)->userID  )
#define     pgt_FCUSEFLG(P)         ( (P)->useflg  )
#define     pgt_FCUSEFLGA(P)        ( (P)->useflgA )
#define     pgt_FCUSEFLGB(P)        ( (P)->useflgB )

#define     pgt_FCLAYNO(P)          ( (P)->lay_no  )
#define     pgt_FCICOLOR(P)         ( (P)->icolor  )

#define     pgt_FCUSERFC(P)         ( (P)->userFC  )
#define     pgt_FCUSERSF(P)         ( (P)->userSF  )


/*----- Face Table ---------------------------------------------------*/

typedef  struct  _pgt_brfacetab {
    long            max_size;           /* max size of this table     */
    long            num_face;           /* no. of faces               */
    PGT_BRFACEP*    ary_face;           /* faces                      */
    void*           pdummy;             /* ptr padding                */

} PGT_BRFACETAB, *PGT_BRFACETABP;


#define     pgt_FTABMAXSIZE(P)      ( (P)->max_size )
#define     pgt_FTABNFACE(P)        ( (P)->num_face )
#define     pgt_FTABFACEARY(P)      ( (P)->ary_face )
#define     pgt_FTABFACE(P,N)       ( (P)->ary_face[(N)] )


/*----- SHELL --------------------------------------------------------*/

typedef  struct  _pgt_brshell {

    /*----- Basic Member -----*/
    long            shellID;            /* this shell ID              */

    /*----- Underlying Faces -----*/
    long            num_face;           /* no. of faces               */
    long*           ary_faceID;         /* ary of faces               */
    void*           pdummy;             /* ptr padding                */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            lay_no;             /* layer no.                  */
    long            icolor;             /* color char[4] r.g.b.a      */

    PGT_BRVOIDP     userSH;             /* user shell                 */
    void*           pdummy2;            /* ptr padding                */

} PGT_BRSHELL, *PGT_BRSHELLP;


#define     pgt_SHTHISID(P)         ( (P)->shellID )

#define     pgt_SHNFACE(P)          ( (P)->num_face )
#define     pgt_SHFACEIDARY(P)      ( (P)->ary_faceID )
#define     pgt_SHFACEID(P,N)       ( (P)->ary_faceID[(N)] )

#define     pgt_SHUSERID(P)         ( (P)->userID  )
#define     pgt_SHUSEFLG(P)         ( (P)->useflg  )
#define     pgt_SHLAYNO(P)          ( (P)->lay_no  )
#define     pgt_SHICOLOR(P)         ( (P)->icolor  )
#define     pgt_SHUSERSH(P)         ( (P)->userSH  )



/*--------------------------------------------------------------------*/
/*    BREP Top Entity                                                 */
/*--------------------------------------------------------------------*/

/*----- Sheet --------------------------------------------------------*/

typedef  struct  _pgt_sheet {

    /*----- Basic Member -----*/
    long            sheetID;            /* this sheet ID              */
    long            idummy;             /* padding                    */
    PGT_BRSHELLP    shell;              /* shell                      */

    /*----- Brep Tables -----*/
    PGT_BRFACETABP  facetab;            /* face    table              */
    PGT_BREDGETABP  edgetab;            /* edge    table              */
    PGT_BRVTEXTABP  vtextab;            /* vertex  table              */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            lay_no;             /* layer no.                  */
    long            icolor;             /* color char[4] r.g.b.a      */
    PGT_BRVOIDP     userSHT;            /* user sheet                 */
    void*           pdummy;             /* padding                    */

} PGT_SHEET, *PGT_SHEETP;


#define     pgt_SHTTHISID(P)        ( (P)->sheetID )
#define     pgt_SHTSHELL(P)         ( (P)->shell   )

#define     pgt_SHTFCTAB(P)         ( (P)->facetab )
#define     pgt_SHTEDTAB(P)         ( (P)->edgetab )
#define     pgt_SHTVTTAB(P)         ( (P)->vtextab )

#define     pgt_SHTUSERID(P)        ( (P)->userID  )
#define     pgt_SHTUSEFLG(P)        ( (P)->useflg  )
#define     pgt_SHTLAYNO(P)         ( (P)->lay_no  )
#define     pgt_SHTICOLOR(P)        ( (P)->icolor  )

#define     pgt_SHTUSERSHT(P)       ( (P)->userSHT )


/*----- Solid --------------------------------------------------------*/

typedef  struct  _pgt_solid {

    /*----- Basic Member -----*/
    long            solidID;            /* this solid ID              */
    long            num_shell;          /* no. of shells              */
    PGT_BRSHELLP*   ary_shell;          /* ary of shells              */

    /*----- Brep Tables -----*/
    PGT_BRFACETABP  facetab;            /* face    table              */
    PGT_BREDGETABP  edgetab;            /* geometry curve             */
    PGT_BRVTEXTABP  vtextab;            /* geometry point             */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            lay_no;             /* layer no.                  */
    long            icolor;             /* color char[4] r.g.b.a      */
    PGT_BRVOIDP     userSLD;            /* user solid                 */
    void*           pdummy;             /* ptr padding                */

} PGT_SOLID, *PGT_SOLIDP;


#define     pgt_SLDTHISID(P)        ( (P)->solidID   )

#define     pgt_SLDNSHELL(P)        ( (P)->num_shell )
#define     pgt_SLDSHELLARY(P)      ( (P)->ary_shell )
#define     pgt_SLDSHELL(P,N)       ( (P)->ary_shell[(N)] )

#define     pgt_SLDFCTAB(P)         ( (P)->facetab   )
#define     pgt_SLDEDTAB(P)         ( (P)->edgetab   )
#define     pgt_SLDVTTAB(P)         ( (P)->vtextab   )

#define     pgt_SLDUSERID(P)        ( (P)->userID    )
#define     pgt_SLDUSEFLG(P)        ( (P)->useflg    )
#define     pgt_SLDLAYNO(P)         ( (P)->lay_no    )
#define     pgt_SLDICOLOR(P)        ( (P)->icolor    )

#define     pgt_SLDUSERSLD(P)       ( (P)->userSLD   )


/*----- All Shell ----------------------------------------------------*/

typedef  struct  _pgt_allshell {

    /*----- Basic Member -----*/
    long            allshellID;         /* this all shell ID          */
    long            idummy;             /* padding                    */

    /*----- Brep Tables -----*/
    PGT_BRFACETABP  facetab;            /* face   table               */
    PGT_BREDGETABP  edgetab;            /* edge   table               */
    PGT_BRVTEXTABP  vtextab;            /* vertex table               */
    void*           pdummy;             /* ptr padding                */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            lay_no;             /* layer no.                  */
    long            icolor;             /* color char[4] r.g.b.a      */
    PGT_BRVOIDP     userASH;            /* user all shell             */
    void*           pdummy2;            /* ptr padding                */

} PGT_ALLSHELL, *PGT_ALLSHELLP;


#define     pgt_ASHTHISID(P)        ( (P)->allshellID )

#define     pgt_ASHFCTAB(P)         ( (P)->facetab )
#define     pgt_ASHEDTAB(P)         ( (P)->edgetab )
#define     pgt_ASHVTTAB(P)         ( (P)->vtextab )

#define     pgt_ASHUSERID(P)        ( (P)->userID  )
#define     pgt_ASHUSEFLG(P)        ( (P)->useflg  )
#define     pgt_ASHLAYNO(P)         ( (P)->lay_no  )
#define     pgt_ASHICOLOR(P)        ( (P)->icolor  )

#define     pgt_ASHUSERASH(P)       ( (P)->userASH )


/*----- Wire ---------------------------------------------------------*/

typedef  struct  _pgt_wire {

    /*----- Basic Member -----*/
    long            wireID;             /* wire ID                    */
    long            idummy;             /* padding                    */
    PGT_BREDGETABP  edgetab;            /* geometry curve             */
    PGT_BRVTEXTABP  vtextab;            /* geometry point             */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            lay_no;             /* layer no.                  */
    long            icolor;             /* color char[4] r.g.b.a      */
    PGT_BRVOIDP     userWR;             /* user all wire              */
    void*           pdummy;             /* padding                    */

} PGT_WIRE, *PGT_WIREP;


#define     pgt_WRTHISID(P)         ( (P)->wireID  )

#define     pgt_WREDTAB(P)          ( (P)->edgetab )
#define     pgt_WRVTTAB(P)          ( (P)->vtextab )

#define     pgt_WRUSERID(P)         ( (P)->userID  )
#define     pgt_WRUSEFLG(P)         ( (P)->useflg  )
#define     pgt_WRLAYNO(P)          ( (P)->lay_no  )
#define     pgt_WRICOLOR(P)         ( (P)->icolor  )

#define     pgt_WRUSERWR(P)         ( (P)->userWR  )



/*--------------------------------------------------------------------*/
/*    ASSEMBLY, INSTANCE. PART                                        */
/*--------------------------------------------------------------------*/

/*----- INSTANCE -----------------------------------------------------*/

typedef  struct  _pgt_instance {

    /*----- Basic Member -----*/
    long            instanceID;         /* instance ID                */
    long            partID;             /* part ID                    */
    double          matrix[4][4];       /* convert into parent assem  */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            useflgA;            /* used flag (sub)            */
    long            useflgB;            /* used flag (sub)            */
    long            showF;              /* show flag 0:NoShow 1:Show  */
    long            idummy;             /* padding                    */
    double          uservalA;           /* user value A               */
    double          uservalB;           /* user value B               */
    PGT_VEC         uservec;            /* user vector                */
    char*           name;               /* name                       */
    PGT_BRVOIDP     userINS;            /* user instance entity       */

} PGT_INSTANCE, *PGT_INSTANCEP;


#define     pgt_INSTANCE_SZ         ( sizeof( PGT_INSTANCE ) )

#define     pgt_INSTHISID(P)        ( (P)->instanceID       )
#define     pgt_INSPARTID(P)        ( (P)->partID           )
#define     pgt_INSMATRIX(P)        ( (P)->matrix           )
#define     pgt_INSMATELM(P,I,J)    ( (P)->matrix[(I)][(J)] )

#define     pgt_INSUSERID(P)        ( (P)->userID   )
#define     pgt_INSUSEFLG(P)        ( (P)->useflg   )
#define     pgt_INSUSEFLGA(P)       ( (P)->useflgA  )
#define     pgt_INSUSEFLGB(P)       ( (P)->useflgB  )
#define     pgt_INSSHOWF(P)         ( (P)->showF    )

#define     pgt_INSUSERVALA(P)      ( (P)->uservalA )
#define     pgt_INSUSERVALB(P)      ( (P)->uservalB )
#define     pgt_INSUSERVEC(P)       ( (P)->uservec  )
#define     pgt_INSNAME(P)          ( (P)->name     )
#define     pgt_INSUSERINS(P)       ( (P)->userINS  )


/*----- ASSEMBLY -----------------------------------------------------*/

typedef  struct  _pgt_assembly {

    /*----- Basic Member -----*/
    long            assemblyID;         /* assembly ID                */
    long            max_size;           /* max size of instance array */
    long            num_inst;           /* no. of instances           */
    long            idummy;             /* padding                    */
    PGT_INSTANCEP*  ary_inst;           /* ary of instances           */
    void*           pdummy;             /* ptr padding                */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            useflgA;            /* used flag (sub)            */
    long            useflgB;            /* used flag (sub)            */

    PGT_BRVOIDP     userASM;            /* user assembly entity       */
    void*           pdummy2;            /* (reference only)           */

} PGT_ASSEMBLY, *PGT_ASSEMBLYP;


#define     pgt_ASSEMBLY_SZ         ( sizeof( PGT_ASSEMBLY ) )

#define     pgt_ASMTHISID(P)        ( (P)->assemblyID    )

#define     pgt_ASMMAXSIZE(P)       ( (P)->max_size      )
#define     pgt_ASMNINST(P)         ( (P)->num_inst      )
#define     pgt_ASMINST(P,N)        ( (P)->ary_inst[(N)] )
#define     pgt_ASMARYINST(P)       ( (P)->ary_inst      )

#define     pgt_ASMUSERID(P)        ( (P)->userID        )
#define     pgt_ASMUSEFLG(P)        ( (P)->useflg        )
#define     pgt_ASMUSEFLGA(P)       ( (P)->useflgA       )
#define     pgt_ASMUSEFLGB(P)       ( (P)->useflgB       )

#define     pgt_ASMUSERASM(P)       ( (P)->userASM       )


/*----- PART ---------------------------------------------------------*/
typedef  struct _pgt_brpart {

    /*----- Basic Member -----*/
    long            partID;             /* part ID                    */
    long            type;               /* part type                  */
                                        /* 1:shl 2:vol 3:asm 4:stl    */
    PGT_SHEETP      sheet;              /* sheet                      */
    PGT_SOLIDP      solid;              /* solid                      */
    PGT_ASSEMBLYP   asem;               /* assembly                   */
    PGT_STLMESHP    stlmesh;            /* stl triangle polygon mesh  */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            useflgA;            /* used flag (sub)            */
    long            useflgB;            /* used flag (sub)            */
    long            lay_no;             /* layer no.                  */
    long            idummy;             /* padding                    */
    long            icolor;             /* color char[4] r.g.b.a      */
    long            geom_colorF;        /* if ON geom has its color   */
    char*           name;               /* name                       */
    PGT_BRVOIDP     userPRT;            /* user part entity           */

} PGT_BRPART, *PGT_BRPARTP;


#define     pgt_BRPART_SZ           ( sizeof( PGT_BRPART ) )

#define     pgt_PRTTHISID(P)        ( (P)->partID      )
#define     pgt_PRTTYPE(P)          ( (P)->type        )
#define     pgt_PRTSHEET(P)         ( (P)->sheet       )
#define     pgt_PRTSOLID(P)         ( (P)->solid       )
#define     pgt_PRTASSEMBLY(P)      ( (P)->asem        )
#define     pgt_PRTSTLMESH(P)       ( (P)->stlmesh     )

#define     pgt_PRTUSERID(P)        ( (P)->userID      )
#define     pgt_PRTUSEFLG(P)        ( (P)->useflg      )
#define     pgt_PRTUSEFLGA(P)       ( (P)->useflgA     )
#define     pgt_PRTUSEFLGB(P)       ( (P)->useflgB     )
#define     pgt_PRTLAYNO(P)         ( (P)->lay_no      )
#define     pgt_PRTICOLOR(P)        ( (P)->icolor      )
#define     pgt_PRTGEOMCOLORF(P)    ( (P)->geom_colorF )
#define     pgt_PRTNAME(P)          ( (P)->name        )

#define     pgt_PRTUSERPRT(P)       ( (P)->userPRT     )

#define     pgt_PRTTYPE_UNKNOWN     ( -1 )
#define     pgt_PRTTYPE_SHEET       (  1 )
#define     pgt_PRTTYPE_SOLID       (  2 )
#define     pgt_PRTTYPE_ASSEMBLY    (  3 )
#define     pgt_PRTTYPE_STLMESH     (  4 )


/*----- Part Table ---------------------------------------------------*/

typedef  struct _pgt_brparttab {
    long            max_partID;         /* max ID used                */
    long            max_size;           /* max size of this table     */
    long            inc_size;           /* size to increase max size  */
    long            num_part;           /* no. of instances           */
    PGT_BRPARTP*    ary_part;           /* parts                      */
    void*           pdummy;             /* ptr padding                */

} PGT_BRPARTTAB, *PGT_BRPARTTABP;


#define     pgt_PTABMAXPARTID(P)    ( (P)->max_partID    )
#define     pgt_PTABMAXSIZE(P)      ( (P)->max_size      )
#define     pgt_PTABINCSIZE(P)      ( (P)->inc_size      )
#define     pgt_PTABNPART(P)        ( (P)->num_part      )
#define     pgt_PTABPART(P,N)       ( (P)->ary_part[(N)] )
#define     pgt_PTABARYPART(P)      ( (P)->ary_part      )


/*----- Assembly Tree ------------------------------------------------*/

typedef  struct _pgt_assemtree {

    /*----- Basic Members -----*/
    long            asemtreeID;         /* assembly tree ID           */
    long            idummy;             /* padding                    */

    PGT_ASSEMBLYP   topasem;            /* top assemby                */
    PGT_BRPARTTABP  parttab;            /* part table                 */

} PGT_ASSEMTREE, *PGT_ASSEMTREEP;


#define     pgt_ASMTREETHISID(P)    ( (P)->asemtreeID )
#define     pgt_ASMTREETOPASEM(P)   ( (P)->topasem    )
#define     pgt_ASMTREEPARTTAB(P)   ( (P)->parttab    )



/*--------------------------------------------------------------------*/
/*    For Knitting                                                    */
/*--------------------------------------------------------------------*/

/*----- Position to Split Edge ---------------------------------------*/

typedef  struct _pgt_brsplitpos {
    long            fac_index;          /* face index in shell        */
    long            lop_index;          /* loop index in face         */
    long            ced_index;          /* coedge index in loop       */
    long            num_split;          /* no. of positions to split  */
    long*           ary_vtexID;         /* vertexes to split          */
    double*         ary_tpar;           /* parameter pos.s to split   */

} PGT_BRSPLITPOS, *PGT_BRSPLITPOSP;



typedef  struct _pgt_bredcurv {
    long            degenF;             /* degenerate flag            */
    long            idummy;             /* padding                    */
    PGT_CURVP       ed_curv;            /* edge underlying curve      */
    PGT_POLYLINEP   ed_poly;            /* edge underlying polyline   */
    long            vtexID0;            /* start  vertex ID           */
    long            vtexID1;            /* end    vertex ID           */

} PGT_BREDCURV, *PGT_BREDCURVP;




/*----- End of File --------------------------------------------------*/



#endif
