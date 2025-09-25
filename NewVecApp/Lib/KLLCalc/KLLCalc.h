// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ KLLCALC_EXPORTS
// �V���{���ŃR���p�C������܂��B���̃V���{���́A���� DLL ���g���v���W�F�N�g�Œ�`���邱�Ƃ͂ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// KLLCALC_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B
#ifdef KLLCALC_EXPORTS
#define KLLCALC_DLL __declspec(dllexport)
#else
#define KLLCALC_DLL __declspec(dllimport)
#endif

//======================================================
// �萔��`
//======================================================
#define M_PI	3.14159265358979323846

//======================================================
// �֐��錾
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


//�e�X�g�֐�
KLLCALC_DLL int testinc( int a );

/*---------------------------------------------------------------------------*/
/*  BF�֘A�֐�			                                                     */
/*---------------------------------------------------------------------------*/
#define tbf_NRMEND ( 0 )  /* ����I��                                         */
#define tbfERINPUT ( 1 )  /* ���͒l���ُ�                                     */
#define tbfERMEMAL ( 8 )  /* ���������m�ۂł��Ȃ�                             */
#define tbfEROTHER ( 9 )  /* ����`�G���[                                     */
#define tbfUNDERFLOW ( 1.0e-15 )             /* �ŏ� 0 ����g�������X         */


/*---------------------------------------------------------------------------*/
/*  �_�񂩂�{�b�N�X���쐬����                                               */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL int    tbfBoxPnt( long num, const double pnt[][3], double box[2][3] ) ;


/*---------------------------------------------------------------------------*/
/*  �}�g���N�X�̋t�}�g���N�X�����߂�                                         */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL int    tbfMtxInv( double tol, long m, const double mx1[], double mx2[] ) ;

/*---------------------------------------------------------------------------*/
/*  n �s n �� �̃}�g���N�X�̋t�}�g���N�X�����߂�                             */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL int    tbfMtxInvLUP( double tol, const int n, const double mx[], double mxInv[]) ;

/*---------------------------------------------------------------------------*/
/*  m �s n ��̃}�g���N�X���X�J���[�{����                                    */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL int    tbfMtxEqt( const double scl, const int m, const int n, const double mxIn[], double mxOut[] ) ;

/*---------------------------------------------------------------------------*/
/*  ���W�ϊ��}�g���N�X�����߂�                                               */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL int    tbfAfnTrs( double       tol,
							const double pnt[3],
							const double vcu[3],
							const double vcv[3],
							const double vcn[3], double mtx[4][4] ) ;


/*---------------------------------------------------------------------------*/
/*  MT�֘A�֐�			                                                     */
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
/*  MTPT�֘A�֐�			                                                 */
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
/*  CVecV6�p����֐��̈ڐA	                                                 */
/*---------------------------------------------------------------------------*/
KLLCALC_DLL void tbCalcMatrix( const double	planecod[3],	// (I) �ʂ̊�_[xyz]
							const double	planeijk[3],	// (I) �ʂ̕����x�N�g��[xyz]
							const double	axiscod[3],		// (I) ���̊�_[xyz]
							const double	axisijk[3],		// (I) ���̕����x�N�g��[xyz]
							const double	origincod[3],	// (I) ���_�̊�_[xyz]
							double			martix[4][4] );	// (O) ���i�ϊ��}�g���N�X�j
