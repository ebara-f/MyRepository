/***********************************************************************

    関数名 : [STL HD04]  pgt_stl_struct.h

    機  能 : ＳＴＬライブラリ用ヘッダファイル
             構造体の定義

    PGT STL Library
    Programed : Hiroyuki Kitazawa  / GeomLab        2022.04.01
    Modified  : Hiroyuki Kitazawa  / GeomLab        2023.09.09

***********************************************************************/



#ifndef PGT_STL_STRUCT_H
#define PGT_STL_STRUCT_H



#include    "pgt_base_point.h"




/*--------------------------------------------------------------------*/
/*    For Any Entity from Other System                                */
/*--------------------------------------------------------------------*/

typedef     void*   PGT_STVOIDP;



/*--------------------------------------------------------------------*/
/*     STL Normal Direction                                           */
/*--------------------------------------------------------------------*/

/*----- STL Normal Direction -----------------------------------------*/
typedef  struct _pgt_stlnvec {

    /*----- Basic Member -----*/
    long            nvecID;             /* this nvec ID               */
    long            seq_no;             /* sequential no.             */
    PGT_VEC         nvec;               /* normal vector (unit)       */

    /*----- Relation -----*/
    long            max_size;           /* max size of nvec ID array  */
    long            num_nvecID;         /* no. of nvecs gathering     */
    long*           ary_nvecID;         /* nvec IDs                   */
    void*           pdummy;             /* padding                    */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* ues flag                   */
    long            invalidF;           /* invalidF                   */
    long            prevID;             /* prev nvec ID               */
    long            nextID;             /* next nvec ID               */
    long            idummy;             /* padding                    */

} PGT_STLNVEC, *PGT_STLNVECP;


#define     pgt_STLNVTHISID(P)          ( (P)->nvecID )
#define     pgt_STLNVSEQNO(P)           ( (P)->seq_no )
#define     pgt_STLNVNVEC(P)            ( (P)->nvec   )

#define     pgt_STLNVMAXSZ(P)           ( (P)->max_size )
#define     pgt_STLNVNUMNVEC(P)         ( (P)->num_nvecID )
#define     pgt_STLNVARYNVEC(P)         ( (P)->ary_nvecID )

#define     pgt_STLNVUSERID(P)          ( (P)->userID   )
#define     pgt_STLNVUSEFLG(P)          ( (P)->useflg   )
#define     pgt_STLNVINVALIDF(P)        ( (P)->invalidF )
#define     pgt_STLNVPREVID(P)          ( (P)->prevID   )
#define     pgt_STLNVNEXTID(P)          ( (P)->nextID   )



/*----- STL Normal Direction Table -----------------------------------*/

typedef  struct _pgt_stlnvectab {
    long            num_nvec;           /* no. of normal vectors      */
    long            max_size;           /* max size of this table     */
    long            max_nvecID;         /* max nvec ID                */
    long            idummy;             /* padding                    */
    PGT_STLNVECP*   nv;                 /* normal vectors             */
    void*           pdummy;             /* padding                    */
    long            headID;             /* head nvex ID               */
    long            tailID;             /* tail nvec ID               */

} PGT_STLNVECTAB, *PGT_STLNVECTABP;


#define     pgt_STLNTABMAXSIZE(P)       ( (P)->max_size )
#define     pgt_STLNTABNNVEC(P)         ( (P)->num_nvec )
#define     pgt_STLNTABMAXNVECID(P)     ( (P)->max_nvecID )
#define     pgt_STLNTABNVEC(P,N)        ( (P)->nv[(N)]  )
#define     pgt_STLNTABNV(P)            ( (P)->nv       )
#define     pgt_STLNTABHEADID(P)        ( (P)->headID )
#define     pgt_STLNTABTAILID(P)        ( (P)->tailID )




/*--------------------------------------------------------------------*/
/*     STL Vertex                                                     */
/*--------------------------------------------------------------------*/

/*----- STL Vertex ---------------------------------------------------*/
typedef  struct _pgt_stlvtex {

    /*----- Basic Member -----*/
    long            vtexID;             /* this vertex ID             */
    long            seq_no;             /* sequential no.             */
    PGT_PNT         pnt;                /* position                   */
    PGT_PNT         uv_pnt;             /* uv position (z=0.0)        */

    /*----- Relation -----*/
    long            max_sizeFC;         /* max size of face ID array  */
    long            num_faceID;         /* no. of faces gathering     */
    long*           ary_faceID;         /* face IDs                   */
    void*           pdummy;             /* padding                    */

    long            max_sizeED;         /* max size of edge ID array  */
    long            num_edgeID;         /* no. of edges gathering     */
    long*           ary_edgeID;         /* edge IDs                   */
    void*           pdummy2;            /* padding                    */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            boundF;             /* ON if vertex is on bound.  */
    long            invalidF;           /* invalidF                   */
    long            icolor;             /* uchar[4]  r,g,b,a          */
    long            nvecID;             /* normal vector ID           */
    double          height;             /* height                     */
    PGT_VEC         usrvec;             /* user vector                */
    long            prevID;             /* prev vtex ID               */
    long            nextID;             /* next vtex ID               */
    PGT_STVOIDP     userVT;             /* pointer to user vtex       */
    void*           pdummy3;            /* (reference only)           */

} PGT_STLVTEX, *PGT_STLVTEXP;


#define     pgt_STLVTTHISID(P)          ( (P)->vtexID )
#define     pgt_STLVTSEQNO(P)           ( (P)->seq_no )
#define     pgt_STLVTPNT(P)             ( (P)->pnt    )
#define     pgt_STLVTUVPNT(P)           ( (P)->uv_pnt )

#define     pgt_STLVTMAXSZFC(P)         ( (P)->max_sizeFC )
#define     pgt_STLVTNUMFACE(P)         ( (P)->num_faceID )
#define     pgt_STLVTARYFACE(P)         ( (P)->ary_faceID )

#define     pgt_STLVTMAXSZED(P)         ( (P)->max_sizeED )
#define     pgt_STLVTNUMEDGE(P)         ( (P)->num_edgeID )
#define     pgt_STLVTARYEDGE(P)         ( (P)->ary_edgeID )

#define     pgt_STLVTUSERID(P)          ( (P)->userID   )
#define     pgt_STLVTUSEFLG(P)          ( (P)->useflg   )
#define     pgt_STLVTBOUNDF(P)          ( (P)->boundF   )
#define     pgt_STLVTINVALIDF(P)        ( (P)->invalidF )
#define     pgt_STLVTICOLOR(P)          ( (P)->icolor   )
#define     pgt_STLVTNVECID(P)          ( (P)->nvecID   )
#define     pgt_STLVTHEIGHT(P)          ( (P)->height   )
#define     pgt_STLVTUSRVEC(P)          ( (P)->usrvec   )
#define     pgt_STLVTPREVID(P)          ( (P)->prevID   )
#define     pgt_STLVTNEXTID(P)          ( (P)->nextID   )
#define     pgt_STLVTUSERVT(P)          ( (P)->userVT   )



/*----- STL Vertex Table ---------------------------------------------*/

typedef  struct _pgt_stlvtextab {
    long            num_vtex;           /* no. of vertexes            */
    long            max_size;           /* max size of this table     */
    long            max_vtexID;         /* max vtex ID                */
    long            idummy;             /* padding                    */
    PGT_STLVTEXP*   vt;                 /* vertexes                   */
    void*           pdummy;             /* padding                    */
    long            headID;             /* head vtex ID               */
    long            tailID;             /* tail vtex ID               */

} PGT_STLVTEXTAB, *PGT_STLVTEXTABP;


#define     pgt_STLVTABMAXSIZE(P)       ( (P)->max_size )
#define     pgt_STLVTABNVTEX(P)         ( (P)->num_vtex )
#define     pgt_STLVTABMAXVTEXID(P)     ( (P)->max_vtexID )
#define     pgt_STLVTABVTEX(P,N)        ( (P)->vt[(N)]  )
#define     pgt_STLVTABVT(P)            ( (P)->vt       )
#define     pgt_STLVTABHEADID(P)        ( (P)->headID )
#define     pgt_STLVTABTAILID(P)        ( (P)->tailID )




/*--------------------------------------------------------------------*/
/*     STL Edge                                                       */
/*--------------------------------------------------------------------*/

/*----- STL Edge -----------------------------------------------------*/

typedef  struct _pgt_stledge {

    /*----- Basic Member -----*/
    long            edgeID;             /* this edge ID               */
    long            seq_no;             /* sequential no.             */
    long            vtexID0;            /* start vertex ID            */
    long            vtexID1;            /* end   vertex ID            */

    /*----- Relation -----*/
    long            max_sizeFC;         /* max size of face ID array  */
    long            num_faceID;         /* no. of faces gathering     */
    long*           ary_faceID;         /* face IDs                   */
    void*           pdummy;             /* padding                    */

    long            faceIDL;            /* left  face ID              */
    long            faceIDR;            /* right face ID              */

    /*----- Extension -----*/
    PGT_PNT         pnt0;               /* start  position            */
    PGT_PNT         pnt1;               /* end    position            */
    PGT_PNT         pntM;               /* middle position            */
    double          angle;              /* folding angle              */
    double          length;             /* edge length                */

    long            userID;             /* userID                     */
    long            useflg;             /* useflg                     */
    long            invalidF;           /* invalid   flag             */
    long            no_swapF;           /* no swap   flag             */
    long            no_splitF;          /* no split  flag             */
    long            charlineF;          /* character line flag        */
    long            revflg;             /* reversed flag              */
    long            icolor;             /* uchar[4] r,g,b,a           */
    long            prevID;             /* prev edge ID               */
    long            nextID;             /* next edge ID               */
    PGT_STVOIDP     userED;             /* pointer to user edge       */
    void*           pdummy2;            /* (reference only)           */

} PGT_STLEDGE, *PGT_STLEDGEP;


#define     pgt_STLEDTHISID(P)          ( (P)->edgeID  )
#define     pgt_STLEDSEQNO(P)           ( (P)->seq_no  )
#define     pgt_STLEDVTEXID0(P)         ( (P)->vtexID0 )
#define     pgt_STLEDVTEXID1(P)         ( (P)->vtexID1 )

#define     pgt_STLEDMAXSZFC(P)         ( (P)->max_sizeFC )
#define     pgt_STLEDNUMFACE(P)         ( (P)->num_faceID )
#define     pgt_STLEDARYFACE(P)         ( (P)->ary_faceID )

#define     pgt_STLEDFACEIDL(P)         ( (P)->faceIDL   )
#define     pgt_STLEDFACEIDR(P)         ( (P)->faceIDR   )

#define     pgt_STLEDPNT0(P)            ( (P)->pnt0      )
#define     pgt_STLEDPNT1(P)            ( (P)->pnt1      )
#define     pgt_STLEDPNTM(P)            ( (P)->pntM      )

#define     pgt_STLEDANGLE(P)           ( (P)->angle     )
#define     pgt_STLEDLENGTH(P)          ( (P)->length    )

#define     pgt_STLEDUSERID(P)          ( (P)->userID    )
#define     pgt_STLEDUSEFLG(P)          ( (P)->useflg    )
#define     pgt_STLEDINVALIDF(P)        ( (P)->invalidF  )
#define     pgt_STLEDNOSWAPF(P)         ( (P)->no_swapF  )
#define     pgt_STLEDNOSPLITF(P)        ( (P)->no_splitF )
#define     pgt_STLEDCHARLINEF(P)       ( (P)->charlineF )
#define     pgt_STLEDREVFLG(P)          ( (P)->revflg    )
#define     pgt_STLEDICOLOR(P)          ( (P)->icolor    )
#define     pgt_STLEDPREVID(P)          ( (P)->prevID   )
#define     pgt_STLEDNEXTID(P)          ( (P)->nextID   )
#define     pgt_STLEDUSERED(P)          ( (P)->userED   )



/*----- STL Edge Table -----------------------------------------------*/

typedef  struct _pgt_stledgetab {
    long            num_edge;           /* no. of edges               */
    long            max_size;           /* max size of this table     */
    long            max_edgeID;         /* max edgeID                 */
    long            idummy;             /* padding                    */
    PGT_STLEDGEP*   ed;                 /* edges                      */
    void*           pdummy;             /* padding                    */
    long            headID;             /* head edge ID               */
    long            tailID;             /* tail edge ID               */

} PGT_STLEDGETAB, *PGT_STLEDGETABP;


#define     pgt_STLETABMAXSIZE(P)       ( (P)->max_size   )
#define     pgt_STLETABNEDGE(P)         ( (P)->num_edge   )
#define     pgt_STLETABMAXEDGEID(P)     ( (P)->max_edgeID )
#define     pgt_STLETABEDGE(P,N)        ( (P)->ed[(N)]    )
#define     pgt_STLETABED(P)            ( (P)->ed         )
#define     pgt_STLETABHEADID(P)        ( (P)->headID )
#define     pgt_STLETABTAILID(P)        ( (P)->tailID )




/*--------------------------------------------------------------------*/
/*     STL Face                                                       */
/*--------------------------------------------------------------------*/

/**********************************************************************/
/*  Note                                                              */
/*  A STL face is composed of 3 vertexes. The face may have 3 edges.  */
/*  The vertexes are arranged in counter clockwise. Edge0 starts      */
/*  at vertex0 and ends at vertex1. Edge1 starts at vertex1 and ends  */
/*  at vertex2, edge2 starts at vertex2 and ends at vertex0.          */
/*  Edges belong to an edge table and it has direction.  To fit       */
/*  direction in a face, a revesed flag is added to each edge.        */
/**********************************************************************/


/*----- STL Face -----------------------------------------------------*/
typedef  struct _pgt_stlface {

    /*----- Basic Member -----*/
    long            faceID;             /* this face ID               */
    long            seq_no;             /* sequential no.             */
    long            vtexID0;            /* 1st vertex ID              */
    long            vtexID1;            /* 2nd vertex ID              */
    long            vtexID2;            /* 3rd vertex ID              */
    long            idummy;             /* padding                    */

    /*----- Extension -----*/
    long            edgeID0;            /* 1st edge   ID (v0 -> v1)   */
    long            edgeID1;            /* 2nd edge   ID (v1 -> v2)   */
    long            edgeID2;            /* 3rd edge   ID (v2 -> v0)   */

    long            revflg0;            /* 1st edge reversed flag     */
    long            revflg1;            /* 2nd edge reversed flag     */
    long            revflg2;            /* 3rd edge reversed flag     */

    long            nvecID0;            /* normal dir. on 1st vertex  */
    long            nvecID1;            /* normal dir. on 2nd vertex  */
    long            nvecID2;            /* normal dir. on 3rd vertex  */
    long            nvecIDC;            /* normal dir. on tri center  */

    /*----- Extension -----*/
    long            userID;             /* user ID                    */
    long            useflg;             /* used flag                  */
    long            invalidF;           /* invalid  flag              */
    long            icolor;             /* uchar[4]  r,g,b,a          */
    long            sh_revflg;          /* reverse flag to shell      */
    long            idummy2;            /* padding                    */
    long            prevID;             /* prev face ID               */
    long            nextID;             /* next next ID               */
    double          userDBL;            /* user real value            */
    PGT_STVOIDP     userFC;             /* pointer to user face       */
    void*           pdummy;             /* (reference only)           */

} PGT_STLFACE, *PGT_STLFACEP;


#define     pgt_STLFCTHISID(P)          ( (P)->faceID  )
#define     pgt_STLFCSEQNO(P)           ( (P)->seq_no  )

#define     pgt_STLFCVTEXID0(P)         ( (P)->vtexID0 )
#define     pgt_STLFCVTEXID1(P)         ( (P)->vtexID1 )
#define     pgt_STLFCVTEXID2(P)         ( (P)->vtexID2 )

#define     pgt_STLFCEDGEID0(P)         ( (P)->edgeID0 )
#define     pgt_STLFCEDGEID1(P)         ( (P)->edgeID1 )
#define     pgt_STLFCEDGEID2(P)         ( (P)->edgeID2 )

#define     pgt_STLFCREVFLG0(P)         ( (P)->revflg0 )
#define     pgt_STLFCREVFLG1(P)         ( (P)->revflg1 )
#define     pgt_STLFCREVFLG2(P)         ( (P)->revflg2 )

#define     pgt_STLFCNVECID0(P)         ( (P)->nvecID0 )
#define     pgt_STLFCNVECID1(P)         ( (P)->nvecID1 )
#define     pgt_STLFCNVECID2(P)         ( (P)->nvecID2 )
#define     pgt_STLFCNVECIDC(P)         ( (P)->nvecIDC )

#define     pgt_STLFCUSERID(P)          ( (P)->userID    )
#define     pgt_STLFCUSEFLG(P)          ( (P)->useflg    )
#define     pgt_STLFCINVALIDF(P)        ( (P)->invalidF  )
#define     pgt_STLFCICOLOR(P)          ( (P)->icolor    )
#define     pgt_STLFCSHREVFLG(P)        ( (P)->sh_revflg )
#define     pgt_STLFCPREVID(P)          ( (P)->prevID   )
#define     pgt_STLFCNEXTID(P)          ( (P)->nextID   )
#define     pgt_STLFCUSERDBL(P)         ( (P)->userDBL  )
#define     pgt_STLFCUSERFC(P)          ( (P)->userFC   )



/*----- STL Face Table -----------------------------------------------*/

typedef  struct _pgt_stlfacetab {
    long            num_face;           /* no. of faces               */
    long            max_size;           /* max size of this table     */
    long            max_faceID;         /* max face ID                */
    long            idummy;             /* padding                    */
    PGT_STLFACEP*   fc;                 /* faces                      */
    void*           pdummy;             /* padding                    */
    long            headID;             /* head face ID               */
    long            tailID;             /* tail face ID               */

} PGT_STLFACETAB, *PGT_STLFACETABP;


#define     pgt_STLFTABMAXSIZE(P)       ( (P)->max_size   )
#define     pgt_STLFTABNFACE(P)         ( (P)->num_face   )
#define     pgt_STLFTABMAXFACEID(P)     ( (P)->max_faceID )
#define     pgt_STLFTABFACE(P,N)        ( (P)->fc[(N)]    )
#define     pgt_STLFTABFC(P)            ( (P)->fc         )
#define     pgt_STLFTABHEADID(P)        ( (P)->headID )
#define     pgt_STLFTABTAILID(P)        ( (P)->tailID )



/*----- STL Mesh -----------------------------------------------------*/

typedef  struct _pgt_stlmesh {

    /*----- Basic Member -----*/
    PGT_STLFACETABP     facetab;        /* table of faces             */
    PGT_STLEDGETABP     edgetab;        /* table of edges             */
    PGT_STLVTEXTABP     vtextab;        /* table of vertexes          */
    PGT_STLNVECTABP     nvectab;        /* table of normal vectors    */

    /*----- Extension -----*/
    PGT_STVOIDP         userMS;         /* mesh in user system        */
    void*               pdummy;         /* (reference only)           */
    long                userID;         /* userID                     */
    long                useflg;         /* useflg                     */

} PGT_STLMESH, *PGT_STLMESHP;


#define     pgt_STLMSFACETAB(P)         ( (P)->facetab )
#define     pgt_STLMSEDGETAB(P)         ( (P)->edgetab )
#define     pgt_STLMSVTEXTAB(P)         ( (P)->vtextab )
#define     pgt_STLMSNVECTAB(P)         ( (P)->nvectab )

#define     pgt_STLMSUSERMS(P)          ( (P)->userMS  )
#define     pgt_STLMSUSERID(P)          ( (P)->userID  )
#define     pgt_STLMSUSEFLG(P)          ( (P)->useflg  )




/*--------------------------------------------------------------------*/
/*     Element ID Array                                               */
/*--------------------------------------------------------------------*/

/*----- Face ID Array ------------------------------------------------*/

typedef  struct _pgt_stlfcidary {
    long            max_size;           /* max size of face iD array  */
    long            useflg;             /* used flag                  */

    long            num_faceID;         /* no.   of face IDs          */
    long            idummy;             /* padding                    */
    long*           ary_faceID;         /* array of face IDs          */
    void*           pdummy;             /* padding                    */

} PGT_STLFCIDARY, *PGT_STLFCIDARYP;


#define     pgt_STLFARYMAXSIZE(P)       ( (P)->max_size        )
#define     pgt_STLFARYUSEFLG(P)        ( (P)->useflg          )
#define     pgt_STLFARYNFACE(P)         ( (P)->num_faceID      )
#define     pgt_STLFARYFACEID(P,N)      ( (P)->ary_faceID[(N)] )



/*----- Edge ID Array ------------------------------------------------*/

typedef  struct _pgt_stledidary {
    long            max_size;           /* max size of edge iD array  */
    long            useflg;             /* used     flag              */
    long            revflg;             /* reversed flag              */
    long            clsflg;             /* closed   flag              */
    long            bgn_vtexID;         /* start vertex ID in chain   */
    long            end_vtexID;         /* end   vertex ID in chain   */

    long            num_edgeID;         /* no.   of edge IDs          */
    long            idummy;             /* padding                    */
    long*           ary_edgeID;         /* array of edge IDs          */
    void*           pdummy;             /* padding                    */

} PGT_STLEDIDARY, *PGT_STLEDIDARYP;


#define     pgt_STLEARYMAXSIZE(P)       ( (P)->max_size        )
#define     pgt_STLEARYUSEFLG(P)        ( (P)->useflg          )
#define     pgt_STLEARYREVFLG(P)        ( (P)->revflg          )
#define     pgt_STLEARYCLSFLG(P)        ( (P)->clsflg          )
#define     pgt_STLEARYBGNVTEXID(P)     ( (P)->bgn_vtexID      )
#define     pgt_STLEARYENDVTEXID(P)     ( (P)->end_vtexID      )
#define     pgt_STLEARYNEDGE(P)         ( (P)->num_edgeID      )
#define     pgt_STLEARYEDGEID(P,N)      ( (P)->ary_edgeID[(N)] )




/*----- Vertex ID Array ----------------------------------------------*/

typedef  struct _pgt_stlvtidary {
    long            max_size;           /* max size of face iD array  */
    long            useflg;             /* used flag                  */
    long            type;               /* vertex ID array type       */
    long            num_vtexID;         /* no.   of vertex IDs        */
    long*           ary_vtexID;         /* array of vertex IDs        */
    long*           ary_nvecID;         /* array of normal vector IDs */

} PGT_STLVTIDARY, *PGT_STLVTIDARYP;


#define     pgt_STLVARYMAXSIZE(P)       ( (P)->max_size        )
#define     pgt_STLVARYUSEFLG(P)        ( (P)->useflg          )
#define     pgt_STLVARYTYPE(P)          ( (P)->type            )
#define     pgt_STLVARYNVTEX(P)         ( (P)->num_vtexID      )
#define     pgt_STLVARYVTEXID(P,N)      ( (P)->ary_vtexID[(N)] )
#define     pgt_STLVARYNVECID(P,N)      ( (P)->ary_nvecID[(N)] )




/*--------------------------------------------------------------------*/
/*     Edge Chain                                                     */
/*--------------------------------------------------------------------*/

typedef  struct _pgt_stlchned {

    /*----- Basic Member -----*/
    long            edgeID;             /* edge ID                    */
    long            vtexIDS;            /* start vtexID    (adjusted) */
    long            vtexIDE;            /* end   vtexID    (adjusted) */
    long            idummy;             /* padding                    */
    PGT_PNT         ed_posS;            /* edge start pos. (adjusted) */
    PGT_PNT         ed_posE;            /* edge end   pos. (adjusted) */

} PGT_STLCHNED,*PGT_STLCHNEDP;


typedef  struct _pgt_stlchain {

    /*----- Basic Member -----*/
    long            num_edge;           /* no. of edges               */
    long            idummy;             /* padding                    */
    PGT_STLCHNED*   ary_edge;           /* edges                      */
    void*           pdummy;             /* padding                    */

} PGT_STLCHAIN, *PGT_STLCHAINP;




/*--------------------------------------------------------------------*/
/*     Interference between Triangles                                 */
/*--------------------------------------------------------------------*/

/*----- Pair of Interference Triangles -------------------------------*/
typedef  struct _pgt_inttris {
    long            triID;              /* this triangle ID           */
    long            num_oposID;         /* no. of oposite triangles   */
    long*           ary_oposID;         /* oposite triangles          */
    void*           pdummy;             /* padding                    */

} PGT_INTTRIS, *PGT_INTTRISP;




/*--------------------------------------------------------------------*/
/*     Table of Triangle Pair                                         */
/*--------------------------------------------------------------------*/

/*----- Table of Triangle Pair ---------------------------------------*/
typedef  struct _pgt_charbit {
    unsigned int    bit0    : 1 ;       /* bit 0                      */
    unsigned int    bit1    : 1 ;       /* bit 1                      */
    unsigned int    bit2    : 1 ;       /* bit 2                      */
    unsigned int    bit3    : 1 ;       /* bit 3                      */
    unsigned int    bit4    : 1 ;       /* bit 4                      */
    unsigned int    bit5    : 1 ;       /* bit 5                      */
    unsigned int    bit6    : 1 ;       /* bit 6                      */
    unsigned int    bit7    : 1 ;       /* bit 7                      */

} PGT_CHARBIT, *PGT_CHARBITP;


typedef  struct _pgt_pairtab {
    long            num_tris;           /* no. of triangles           */
    long            size;               /* size of elements           */
    char*           elem;               /* elements                   */
    void*           pdummy;             /* padding                    */

} PGT_PAIRTAB, *PGT_PAIRTABP;




/*--------------------------------------------------------------------*/
/*     Knit Free Edges in STL Mesh                                    */
/*--------------------------------------------------------------------*/

/*----- Position to Split Edge ---------------------------------------*/

typedef  struct _pgt_splitinfo {
    long            edgeID;             /* face ID                    */
    long            num_split;          /* no. of positions to split  */
    long*           ary_vtexID;         /* vertexes to split          */
    void*           pdummy;             /* padding                    */

} PGT_SPLITINFO, *PGT_SPLITINFOP;





/*----- End of File --------------------------------------------------*/



#endif
