// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された KLLCALC_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// KLLCALC_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef KLLCALC_EXPORTS
#define KLLCALC_DLL __declspec(dllexport)
#else
#define KLLCALC_DLL __declspec(dllimport)
#endif

//======================================================
// 定数定義
//======================================================
#define M_PI	3.14159265358979323846

//======================================================
// 関数宣言
//======================================================
KLLCALC_DLL double tbfVecNrm(double tol, const double vc1[3], double vc2[3]);
KLLCALC_DLL int    tbfVecEqt(double scl, const double vc1[3], double vc2[3]);
KLLCALC_DLL int    tbfVecPrd(const double vc1[3], const double vc2[3], double vc3[3]);
KLLCALC_DLL int    tbfVecSub(const double vc1[3], const double vc2[3], double vc3[3]);
KLLCALC_DLL double tbfVecAng(double tol, const double vc1[3], const double vc2[3]);
KLLCALC_DLL double tbfVecDst(const double vc1[3], const double vc2[3]);
KLLCALC_DLL int    tbfMtxPrd(long l, long m, long n, const double mx1[], const double mx2[], double mx3[]);


KLLCALC_DLL long tmtProjectPNT(
	const double tole[],
	const double pnta[3],
	const double vecn[3],
	const double pnti[3],
	double pnto[3],
	double *dist);


KLLCALC_DLL long tmtLengthPOL(
	const double tole[],
	long		 npnt,
	const double pntary[][3],
	double*	 	 prLeng);


//テスト関数
KLLCALC_DLL int testinc( int a );

/*---------------------------------------------------------------------------*/
/*  BF関連関数			                                                     */
/*---------------------------------------------------------------------------*/
#define tbf_NRMEND ( 0 )  /* 正常終了                                         */
#define tbfERINPUT ( 1 )  /* 入力値が異常                                     */
#define tbfERMEMAL ( 8 )  /* メモリを確保できない                             */
#define tbfEROTHER ( 9 )  /* 未定義エラー                                     */
#define tbfUNDERFLOW ( 1.0e-15 )             /* 最小 0 判定トレランス         */


/*---------------------------------------------------------------------------*/
/*  点列からボックスを作成する                                               */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL int    tbfBoxPnt( long num, const double pnt[][3], double box[2][3] ) ;


/*---------------------------------------------------------------------------*/
/*  マトリクスの逆マトリクスを求める                                         */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL int    tbfMtxInv( double tol, long m, const double mx1[], double mx2[] ) ;

/*---------------------------------------------------------------------------*/
/*  n 行 n 列 のマトリクスの逆マトリクスを求める                             */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL int    tbfMtxInvLUP( double tol, const int n, const double mx[], double mxInv[]) ;

/*---------------------------------------------------------------------------*/
/*  m 行 n 列のマトリクスをスカラー倍する                                    */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL int    tbfMtxEqt( const double scl, const int m, const int n, const double mxIn[], double mxOut[] ) ;

/*---------------------------------------------------------------------------*/
/*  座標変換マトリクスを求める                                               */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL int    tbfAfnTrs( double       tol,
							const double pnt[3],
							const double vcu[3],
							const double vcv[3],
							const double vcn[3], double mtx[4][4] ) ;


/*---------------------------------------------------------------------------*/
/*  MT関連関数			                                                     */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL long tmtIntersectULINxUPLN(
  const double  tole[2],
  const double  pntl[3],
  const double  vecl[3],
  const double  pnta[3],
  const double  vecn[3],
        double  pntx[3]) ;

KLLCALC_DLL long tmtNearestPNTToULIN(
  const double  tole[2],
  const double  pntx[3],
  const double  pntL[3],
  const double  vecL[3],
        double  pnto[3],
        double *dist   ) ;


/*---------------------------------------------------------------------------*/
/*  MTPT関連関数			                                                 */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL long tmtptCreateUPLN(
  const double tole[],
  const   long npnt,
  const double pary[][3],
  const double pmin[],
  const double pmax[],
        double pnto[],
        double vecN[],
        double *gap ) ;
KLLCALC_DLL long tmtptCreateULIN(
  const double tole[],
  const   long npnt,
  const double pary[][3],
  const double pmin[],
  const double pmax[],
        double pntL[],
        double vecL[],
        double *gap ) ; 
KLLCALC_DLL long tmtptCreateUSPH(
  const double tole[],
  const   long npnt,
  const double pary[][3],
  const double pmin[],
  const double pmax[],
        double pnto[],
        double *radx,
        double *gap ) ;

/*---------------------------------------------------------------------------*/
/*  CVecV6用特定関数の移植	                                                 */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL void tbCalcMatrix( const double	planecod[3],	// (I) 面の基準点[xyz]
							const double	planeijk[3],	// (I) 面の方向ベクトル[xyz]
							const double	axiscod[3],		// (I) 軸の基準点[xyz]
							const double	axisijk[3],		// (I) 軸の方向ベクトル[xyz]
							const double	origincod[3],	// (I) 原点の基準点[xyz]
							double			martix[4][4] );	// (O) 解（変換マトリクス）
