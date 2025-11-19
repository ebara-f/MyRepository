// KLLCalc.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//
#include "stdafx.h"
#include "KLLCalc.h"
#include "sub_functions.h"
#include <math.h>

#include <iostream>
#include <vector>

//! @struct point
//! @brief 座標を表すデータ型
struct point {
	double p[3];
	point(double x, double y, double z) {
		p[0] = x;
		p[1] = y;
		p[2] = z;
	}
	point() {}
};

//! @brief 固有値・固有ベクトル
struct eigen {
	double val;   //!< 固有値
	double vec[3];//!< 固有ベクトル
};
int EigenJacobiMethod(float* a, float* v, int n);

void data(std::vector<point>& pt, const double pary[][3], int num);
void eigen_vector(eigen* ev, point* average, const std::vector<point>& pt);

//->[]

#define RADIAN_90	1.570796326794895

//-------------------------------------
//! @fn ベクトルの単位化
//-------------------------------------
//! @param [in] tol
//-------------------------------------
double tbfVecNrm(double tol, const double vc1[3], double vc2[3])
{
	double dVecSize;
	double dValue;
	double dRetValue;

	dVecSize = sqrt(vc1[0] * vc1[0] + vc1[1] * vc1[1] + vc1[2] * vc1[2]);

	if (dVecSize < tol) {
		dRetValue = 0.0;
		vc2[0] = 0.0;
		vc2[1] = 0.0;
		vc2[2] = 0.0;
	}
	else {
		dValue = 1.0 / dVecSize;
		vc2[0] = vc1[0] * dValue;
		vc2[1] = vc1[1] * dValue;
		vc2[2] = vc1[2] * dValue;
	}

	return (dVecSize);
}

//-------------------------------------
//! ベクトルのスカラー倍
//-------------------------------------
int tbfVecEqt(double scl, const double vc1[3], double vc2[3])
{
	vc2[0] = vc1[0] * scl;
	vc2[1] = vc1[1] * scl;
	vc2[2] = vc1[2] * scl;

	return(0);
}

//-------------------------------------
//! ベクトルの外積を求める
//-------------------------------------
int tbfVecPrd(const double vc1[3], const double vc2[3], double vc3[3])
{
	vc3[0] = vc2[2] * vc1[1] - vc1[2] * vc2[1];
	vc3[1] = vc1[2] * vc2[0] - vc1[0] * vc2[2];
	vc3[2] = vc1[0] * vc2[1] - vc2[0] * vc1[1];

	return(0);
}

//-------------------------------------
//! ベクトルの差
//-------------------------------------
int tbfVecSub(const double vc1[3], const double vc2[3], double vc3[3])
{
	vc3[0] = vc1[0] - vc2[0];
	vc3[1] = vc1[1] - vc2[1];
	vc3[2] = vc1[2] - vc2[2];

	return 0;
}

//-------------------------------------
//! ベクトルの角度を求める
//-------------------------------------
double tbfVecAng(double tol, const double vc1[3], const double vc2[3])
{
	double dValue;
	double dValue_X;
	double dVecSize_1;
	double dVecSize_2;
	double dArcCos;

	dValue     = vc1[0] * vc2[0] + vc1[1] * vc2[1] + vc1[2] * vc2[2];
	dVecSize_1 = sqrt(vc1[0] * vc1[0] + vc1[1] * vc1[1] + vc1[2] * vc1[2]);
	dVecSize_2 = sqrt(vc2[0] * vc2[0] + vc2[1] * vc2[1] + vc2[2] * vc2[2]);

	dValue_X = dValue / (dVecSize_1 * dVecSize_2);

	//ここの条件は要確認のこと
	if((1.0 < dValue_X)||(dValue_X < -1.0)){
		dValue_X = 1.0;
	}

	dArcCos = acos(dValue_X);

	return(dArcCos);
}

//-------------------------------------
//! ベクトル(点間)の距離を求める
//-------------------------------------
double tbfVecDst(const double vc1[3], const double vc2[3])
{
	double dRetValue;

	dRetValue = sqrt((vc1[0] - vc2[0])*(vc1[0] - vc2[0]) +
					 (vc1[1] - vc2[1])*(vc1[1] - vc2[1]) +
					 (vc1[2] - vc2[2])*(vc1[2] - vc2[2]));

	return(dRetValue);
}

//-------------------------------------
//! マトリクスの積を求める
//-------------------------------------
int tbfMtxPrd(long l, long m, long n, const double mx1[], const double mx2[], double mx3[])
{
	double* pMx1 = (double*)mx1;
	double* pMx2 = (double*)mx2;
	double* pMx3 = (double*)mx3;
	double* pMx2Tmp;
	double* pMx3Tmp;
	int i, j, k;
	int p,r;

	pMx2Tmp = new double[m*m];
	pMx3Tmp = new double[m*m];

	//中間処理用のpMx3Tmp,pMx3Tmpの配列数はm*m
	for (r = 0; r < m * m; r++) {
		pMx2Tmp[r] = 0.0;
		pMx3Tmp[r] = 0.0;
	}

	//最終的な格納先であるpMx3の配列数はm*nなので注意(m*mではない)
	for (p = 0; p < m * n; p++) {
		pMx3[p] = 0.0;
	}

	//pMx2をm*mの配列の該当位置に格納し直す
	int r_idx = 0;
	for (k = 0; k < m; k++) {
		for (j = 0; j < n; j++) {
			pMx2Tmp[k*m+j] = pMx2[r_idx];
			r_idx++;
		}
	}

	//A[i][k]*B[k][i]の行列積を計算(=C[i][j])
	for (i = 0; i < l; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < m; k++) {
				pMx3Tmp[i*l+j] += pMx1[i*l + k] * pMx2Tmp[k*m+j];
			}
		}
	}

	//計算結果のpMx3Tmp内はm*m分の配列なので、pMx3に結果を入れ直す
	int w_idx = 0;
	for (k = 0; k < m; k++) {
		for (j = 0; j < n; j++) {
			pMx3[w_idx] = pMx3Tmp[k*m + j];
			w_idx++;
		}
	}


	delete[] pMx2Tmp; //[]追加(2022.1.5yori)
	delete[] pMx3Tmp; //[]追加(2022.1.5yori)
	return 0;
}

//-------------------------------------
//! ポイントを平面に投影
//-------------------------------------
long tmtProjectPNT(
	const double tole[],
	const double pnta[3],//!< 平面
	const double vecn[3],//!< 平面の法線ベクトル
	const double pnti[3],//!< 元となるポイント	
	double pnto[3],		 //!< 算出した点を格納
	double *dist) {

	double dVal_1;
	double dVal_2;
	double dVal_3;
	double dVal_4;
	double dVal_5;
	double dVal_6;

	dVal_4 = pnti[0] - pnta[0];
	dVal_5 = pnti[1] - pnta[1];
	dVal_6 = pnti[2] - pnta[2];

	dVal_3 = tole[0];
	dVal_1 = sqrt(dVal_4*dVal_4 + dVal_5*dVal_5 + dVal_6*dVal_6);

	if (dVal_3 <= dVal_1) {
		dVal_1 = vecn[0];
		dVal_2 = sqrt(dVal_1 * dVal_1 + vecn[1] * vecn[1] + vecn[2] * vecn[2]);

		if (dVal_2 <= dVal_3) {
			dVal_1 = 0.0;
			dVal_2 = 0.0;
			dVal_3 = 0.0;
		}
		else {
			dVal_2 = 1.0 / dVal_2;
			//
			dVal_1 = dVal_1 * dVal_2;
			dVal_3 = dVal_2 * vecn[1];
			dVal_2 = dVal_2 * vecn[2];
		}
		dVal_4 = dVal_3 * dVal_5 + dVal_1 * dVal_4 + dVal_2 * dVal_6;

		if (dist != (double*)0x00) {
			*dist = dVal_4;
		}
		pnto[0] = pnti[0] - dVal_1 * dVal_4;
		pnto[1] = pnti[1] - dVal_3 * dVal_4;
		pnto[2] = pnti[2] - dVal_2 * dVal_4;
	}
	else {
		if (dist != (double*)0x00) {
			*dist = 0.0;
		}
		pnto[0] = pnta[0];
		pnto[1] = pnta[1];
		pnto[2] = pnta[2];
	}

	return(0);
}

//-------------------------------------
//! @fn ポリラインの線長を求める
//-------------------------------------
//! @param [in]　判定トレランス
//! @param [in]　配列数
//! @param [in]　点の可変配列
//! @param [out] 求めた線長
//-------------------------------------
//! @return =0:固定
//-------------------------------------
//! @note ポリラインの線長は配列内の隣り合う点同士を結んだ長さ(3次元のベクトル長)の合計
//-------------------------------------
long tmtLengthPOL(
	const double tole[],
	long		 npnt,
	const double pntary[][3],
	double*	 	 prLeng)
{

	double dGetVal = 0.0;
	
	for (int k = 0; k < npnt-1; k++) {
		double dVal_1 = pntary[k][0] - pntary[k + 1][0];
		double dVal_2 = pntary[k][1] - pntary[k + 1][1];
		double dVal_3 = pntary[k][2] - pntary[k + 1][2];

		double dst = sqrt((dVal_1*dVal_1) + (dVal_2*dVal_2) + (dVal_3*dVal_3));
		dGetVal += dst;
	}

	*prLeng = dGetVal;

	return 0;
}

//------------------------------------------------
//! @fn m行・m列の逆マトリクスを作成する
//------------------------------------------------
//! @note
//! 逆行列が存在しないことのチェックが必要？
//! 1) 正方行列ではない場合->行・列数=mなので考える必要が無い
//! 2）行列式=0 -> m>3の場合は余因子展開し、三次行列をサラスの方法で計算（めんどいので後回し・・・）
//------------------------------------------------
//! @param [in]  判定トレランス
//! @param [in]  行列数(mxm)
//! @param [in]  行列データ
//! @param [out] 求めた逆行列	
//------------------------------------------------
//! @return =1:引数エラー, =0:正常
//------------------------------------------------
int tbfMtxInv(double tol, long m,  const double mx1[], double mx2[])
{
	//引数チェック
	if ((m < 1) || (mx1 == NULL) || (mx2 == NULL)) {
		return 1;
	}

	double* pInvMtx = new double[m*m];
	double* pTmp    = new double[m*m];
	double  buf; //一時的なデータを蓄える


	//単位行列の作成
	for (int i = 0; i<m; i++) {
		for (int j = 0; j<m; j++) {
			if (i == j) {
				pInvMtx[i*m + j] = 1.0;
			}
			else {
				pInvMtx[i*m + j] = 0.0;
			}
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			pTmp[i*m + j] = mx1[i*m+j];
		}
	}

	//掃き出し法
	for (int i = 0; i<m; i++) {
		buf = 1 / pTmp[i*m+i];

		for (int j = 0; j<m; j++) {
			pTmp[i*m+j] *= buf;
			pInvMtx[i*m+j] *= buf;
		}

		for (int j = 0; j<m; j++) {
			if (i != j) {
				buf = pTmp[j*m+i];
				for (int k = 0; k<m; k++) {
					pTmp[j*m+k] -= pTmp[i*m+k] * buf;
					pInvMtx[j*m+k] -= pInvMtx[i*m+k] * buf;
				}
			}
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			mx2[i*m + j] = pInvMtx[i*m + j];
		}
	}

	delete[] pInvMtx; //追加(2022.1.5yori)
	delete[] pTmp; //追加(2022.1.5yori)
	return 0;
}

//------------------------------------------------
//! @fn n行・n列の逆マトリクスを作成する
//------------------------------------------------
//! @param [in]  判定トレランス
//! @param [in]  行列数(mxm)
//! @param [in]  行列データ
//! @param [out] 求めた逆行列	
//------------------------------------------------
//! @return =0: (※固定)
//------------------------------------------------
//! @note
//! この関数はtbfMtxInv()でm>4の場合に内部的に使用されているらしい。@n
//! 当社のアルゴリズムは逆マトリクスの算出に掃出し法を使用しているので、m>4でも @n
//! 別処理にする必要がありません。@n
//! そのため、下記関数はダミーとして残すのみです。@n
//! (ヘッダーでexportされていますが、パルステック殿は使っていないとのことです)
//-----------------------------------------------------------------------------------
int tbfMtxInvLUP(double tol, const int n, const double mx[], double mxInv[])
{
	return 0;
}

//------------------------------------------------
//! @fn m行・m列のマトリクスをスカラー倍する
//------------------------------------------------
//! @param [in] scl : スカラー倍
//! @param [in] m : 行数
//! @param [in] n : 列数
//! @param [in] mxIn[] :元の行列（※一次元になっているので注意)
//! @param [out] mxOut[] : スカラー倍された行列（※一次元になっているので注意)
//------------------------------------------------
//! @return =0(固定)
//------------------------------------------------
int tbfMtxEqt(const double scl, const int m, const int n, const double mxIn[], double mxOut[])
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			mxOut[i*m + j] = scl * mxIn[i*m + j];
		}
	}

	return 0;
}

//------------------------------------------------
//! @fn 点列から三次元のボックスを作成
//------------------------------------------------
//! @param [in] num : 点群データ数
//! @param [in] pnt[][3] : 点群データ
//! @param [out] box[2][3] : 求めたバウンディングボックスの2頂点の座標(ボックスの中心を通る対になっている頂点)
//------------------------------------------------
//! @return =0:正常、=1:固定値または不明として返す(引数num<3, num=0の場合)
//------------------------------------------------
//! @note
//! ボックスは対角となる2点を結果として返しいます。@n
//! また、ボックスは点列の各軸の最大・最小値をサーチし、2点として格納します。@n
//! このボックスはバウンディングボックス(Bounding Box)と呼ばれるもので　@n
//! オブジェクト(ここでは点群データ)に対してできるだけ余白が出ないようにすっぽりと覆うBoxになります。@n
//! ですが、ここで求めるBoxはAABB(Axis Aligned Boudning Box)であり、XYZ軸(Axis)に平行(Aligned)なBoxとなります。@n
//! そのため、例えば点群が斜め45度方向に分布するような場合でも軸に平行なBoxとなるため、余分な余白ができることになります。@n
//------------------------------------------------
int tbfBoxPnt(long num, const double pnt[][3], double box[2][3])
{
	double dMin_X = pnt[0][0];
	double dMin_Y = pnt[0][1];
	double dMin_Z = pnt[0][2];
	double dMax_X = pnt[0][0];
	double dMax_Y = pnt[0][1];
	double dMax_Z = pnt[0][2];


	if (3 < num - 1) {

		//Xの最小値・最大値を検索
		for (int i = 1; i < num; i++) {
			if (pnt[i][0] < dMin_X) {
				dMin_X = pnt[i][0];
			}
			if (pnt[i][0] > dMax_X) {
				dMax_X = pnt[i][0];
			}
		}

		//Yの最小値・最大値を検索
		for (int i = 1; i < num; i++) {
			if (pnt[i][1] < dMin_Y) {
				dMin_Y = pnt[i][1];
			}
			if (pnt[i][1] > dMax_Y) {
				dMax_Y = pnt[i][1];
			}
		}

		//Zの最小値・最大値を検索
		for (int i = 1; i < num; i++) {
			if (pnt[i][2] < dMin_Z) {
				dMin_Z = pnt[i][2];
			}
			if (pnt[i][2] > dMax_Z) {
				dMax_Z = pnt[i][2];
			}
		}

		box[0][0] = dMin_X;
		box[0][1] = dMin_Y;
		box[0][2] = dMin_Z;
		//
		box[1][0] = dMax_X;
		box[1][1] = dMax_Y;
		box[1][2] = dMax_Z;

		return(0);
	}

	if (0 < num) {

		box[0][0] = pnt[0][0];
		box[0][1] = pnt[0][1];
		box[0][2] = pnt[0][2];
		//
		box[1][0] = pnt[0][0];
		box[1][1] = pnt[0][1];
		box[1][2] = pnt[0][2];

		return(1);
	}

	box[0][0] = 0.0;
	box[0][1] = 0.0;
	box[0][2] = 0.0;
	//
	box[1][0] = 0.0;
	box[1][1] = 0.0;
	box[1][2] = 0.0;

	return(1);
}

//------------------------------------------------
//! アフィン変換マトリクスの作成
//------------------------------------------------
//! @param []
//!  @param [in] 判定トレランス
//!< 新座標系の原点
//!< 新座標系のX軸ベクトル
//!< 新座標系のY軸ベクトル
//!< 新座標系のZ軸ベクトル 
//!< 座標変換マトリクス 
//------------------------------------------------
//! @return =1:引数エラー, =0:固定
//------------------------------------------------
int tbfAfnTrs(double tol,
			  const double pnt[3],
			  const double vcu[3],
			  const double vcv[3],
			  const double vcn[3],
			  double mtx[4][4])	
{
	//引数チェック
	if ((pnt == NULL) || (vcu == NULL) || (vcv == NULL) || (vcn == NULL) || (mtx == NULL))
		return(1);//NG

	//二次元配列を扱いやすいように一次元ポインタに置き換え
	double* pMtx = *mtx;

	//-------------------------------
	//単位行列の作成(引数が4x4なので4固定)
	//-------------------------------
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			if (i == j) {
				pMtx[i*4 + j] = 1.0;
			}
			else {
				pMtx[i*4 + j] = 0.0;
			}
		}
	}

	//-------------------------------
	// 単位ベクトルを求める
	//-------------------------------
	double Vcu_Nrm[3] = { 0 };
	double Vcv_Nrm[3] = { 0 };
	double Vcn_Nrm[3] = { 0 };

	tbfVecNrm(tol, vcu, Vcu_Nrm);
	tbfVecNrm(tol, vcv, Vcv_Nrm);
	tbfVecNrm(tol, vcn, Vcn_Nrm);


	double v13 = Vcu_Nrm[0];
	double v14 = Vcu_Nrm[1];
	double v15 = Vcu_Nrm[2];
	double v16 = Vcv_Nrm[1];

	double v19 = Vcu_Nrm[0] * pnt[0];
	double v18 = Vcu_Nrm[1] * pnt[1];
	double v17 = Vcu_Nrm[2] * pnt[2];

	double v20 = v17 * -1.0 -(v18+v19);
	double v21 = Vcv_Nrm[0];
	double v22 = Vcv_Nrm[2];
	double v23 = v22 * pnt[2];
	double v24 = Vcv_Nrm[1] * pnt[1] + Vcv_Nrm[0]*pnt[0];
	double v26 = v23 * -1.0 - v24;
	double v27 = Vcn_Nrm[1];

	double v31 = Vcn_Nrm[0] * pnt[0];
	double v30 = Vcn_Nrm[1] * pnt[1];
	double v29 = Vcn_Nrm[2] * pnt[2];


	mtx[0][0] = Vcu_Nrm[0];//[0]
	mtx[0][1] = Vcu_Nrm[1];//[1]
	mtx[0][2] = Vcu_Nrm[2];//[2]
	mtx[0][3] = v20;//[3]

	mtx[1][0] = Vcv_Nrm[0];//[4]
	mtx[1][1] = Vcv_Nrm[1];//[5]
	mtx[1][2] = Vcv_Nrm[2];//[6]
	mtx[1][3] = v26;//[7]

	mtx[2][0] = Vcn_Nrm[0];//[8]
	mtx[2][1] = Vcn_Nrm[1];//[9]
	mtx[2][2] = Vcn_Nrm[2];//[10]
	mtx[2][3] = v29 * -1.0 -(v30+v31);//[11]

	mtx[3][0] = 0.0;//[12]
	mtx[3][1] = 0.0;//[13]
	mtx[3][2] = 0.0;//[14]
	mtx[3][3] = 1.0;//[15]

	return 0;
}


//------------------------------------------------
//! 球の生成
//------------------------------------------------
#define N_DIM	4
#define EPS		1e-8
//
int  is_zero(double val);
void sphere_fitting(double *x, double *y, double *z, int len, double *a, double *b, double *c, double *r);
void solve(double A[N_DIM][N_DIM], double B[N_DIM]);
int ExCalLeastSqSphere(double *center, double *diamter,
	double *in_x, double *in_y, double *in_z, int len);


long tmtptCreateUSPH(
	const double tole[],
	const   long npnt,
	const double pary[][3],
	const double pmin[],
	const double pmax[],
	double pnto[],
	double *radx,
	double *gap)
{
	double* pIn_x = new double[npnt];
	double* pIn_y = new double[npnt];
	double* pIn_z = new double[npnt];

	for (int i = 0; i < npnt; i++) {
		pIn_x[i] = pary[i][0];
		pIn_y[i] = pary[i][1];
		pIn_z[i] = pary[i][2];
	}

	double center[3];
	double radius;

	ExCalLeastSqSphere(center, &radius, pIn_x, pIn_y, pIn_z, npnt);

	pnto[0] = center[0];
	pnto[1] = center[1];
	pnto[2] = center[2];

	*radx = radius;

	delete[] pIn_x; //追加(2022.1.5yori)
	delete[] pIn_y; //追加(2022.1.5yori)
	delete[] pIn_z; //追加(2022.1.5yori)
	return 0;
}


int ExCalLeastSqSphere(double *center, double *radius,
	double *in_x, double *in_y, double *in_z, int len)
{
	double out_a, out_b, out_c, out_r;

	// 最小二乗法で計算する
	sphere_fitting(in_x, in_y, in_z, len, &out_a, &out_b, &out_c, &out_r);

	center[0] = out_a;//cx
	center[1] = out_b;//cy
	center[2] = out_c;//cz
	*radius = out_r;

	return 0;
}

void sphere_fitting(double *x, double *y, double *z, int len, double *a, double *b, double *c, double *r)
{
	double A[4][4] = { { 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 } };
	double B[4] = { 0.0, 0.0, 0.0, 0.0 };
	int    i;

	// ※後から2を掛けた方が良いとかそういうツッコミは無しで
	for (i = 0; i < len; i++) {
		// 左辺(係数行列)
		A[0][0] += 2.0 * x[i] * x[i];
		A[0][1] += 2.0 * x[i] * y[i];
		A[0][2] += 2.0 * x[i] * z[i];
		A[0][3] += 2.0 * x[i];

		A[1][0] += 2.0 * y[i] * x[i];
		A[1][1] += 2.0 * y[i] * y[i];
		A[1][2] += 2.0 * y[i] * z[i];
		A[1][3] += 2.0 * y[i];

		A[2][0] += 2.0 * z[i] * x[i];
		A[2][1] += 2.0 * z[i] * y[i];
		A[2][2] += 2.0 * z[i] * z[i];
		A[2][3] += 2.0 * z[i];

		A[3][0] += 2.0 * x[i];
		A[3][1] += 2.0 * y[i];
		A[3][2] += 2.0 * z[i];
		A[3][3] += 2.0 * 1.0;

		// 右辺
		B[0] += x[i] * (x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
		B[1] += y[i] * (x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
		B[2] += z[i] * (x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
		B[3] += x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
	}
	// 連立方程式を計算
	solve(A, B);		

	// a,b,c,dのパラメータがB[0],B[1],B[2],B[3]に代入されているので
	// a,b,c,rを代入して関数を終わる
	*a = B[0];
	*b = B[1];
	*c = B[2];
	*r = sqrt(B[0] * B[0] + B[1] * B[1] + B[2] * B[2] + 2 * B[3]);
}


// 連立方程式を求める関数
void solve(double A[N_DIM][N_DIM], double B[N_DIM]) {
	double temp;
	int    i, j, k;

	for (i = 0; i < N_DIM; i++) {
		// ピボット選択的みたいな処理
		for (j = i + 1; j < N_DIM; j++) {
			//if (is_zero(A[i][j]==false))
			if (is_zero(A[i][j]) == -1)
				break;

			for (k = 0; k < N_DIM; k++) {
				A[i][k] += A[j][k];
			}
			B[i] += B[j];
		}

		// 対角成分を1に
		temp = A[i][i];
		for (j = i; j < N_DIM; j++) {
			A[i][j] /= temp;
		}
		B[i] /= temp;

		// 前進消去
		for (j = i + 1; j < N_DIM; j++) {
			temp = A[j][i];

			for (k = i; k < N_DIM; k++)
				A[j][k] -= temp * A[i][k];
			B[j] -= temp * B[i];
		}
	}

	// 後進消去
	for (i = N_DIM - 1; i >= 0; i--)
		for (j = i - 1; j >= 0; j--)
			B[j] -= A[j][i] * B[i];
}

// ほぼ0ならtrueを返す関数
int is_zero(double val) {
	if (-EPS < val && val < EPS) {
		return 0;//TRUE
	}
	else {
		return -1;//FALSE
	}
}


//------------------------------------------------
//! 点から直線への最近点を求める
//------------------------------------------------
long tmtNearestPNTToULIN(
	const double  tole[2],
	const double  pntx[3],
	const double  pntL[3],
	const double  vecL[3],
	double  pnto[3],
	double *dist)
{
	double dVal_1;
	double dVal_2;
	double dVal_3;
	double dVal_4;
	double dVal_5;
	double dVal_6;


	dVal_3 = vecL[0];
	dVal_4 = pntx[0] - pntL[0];
	dVal_5 = pntx[1] - pntL[1];
	dVal_6 = pntx[2] - pntL[2];


	dVal_1 = sqrt(vecL[0]*vecL[0] + vecL[1]*vecL[1] + vecL[2]*vecL[2]);

	if ((dVal_1 < tole[0]) || (dVal_1 == tole[0])) {
		dVal_1 = 0.0;
		dVal_2 = 0.0;
		dVal_3 = 0.0;
	}
	else {
		dVal_1 = 1.0 / dVal_1;
		dVal_3 = dVal_3 * dVal_1;
		dVal_2 = dVal_1 * vecL[1];
		dVal_1 = dVal_1 * vecL[2];
	}

	dVal_5 = dVal_2 * dVal_5 + dVal_3 * dVal_4 + dVal_1 * dVal_6;
	dVal_3 = dVal_3 * dVal_5 + pntL[0];
	dVal_4 = dVal_2 * dVal_5 + pntL[1];
	dVal_1 = dVal_1 * dVal_5 + pntL[2];

	pnto[0] = dVal_3;
	pnto[1] = dVal_4;
	pnto[2] = dVal_1;

	dVal_3 = pntx[0] - dVal_3;
	dVal_4 = pntx[1] - dVal_4;
	dVal_1 = pntx[2] - dVal_1;

	*dist = sqrt(dVal_3*dVal_3 + dVal_4 * dVal_4 + dVal_1*dVal_1);

	return 0;
}

//------------------------------------------------
//! 直線を生成する
//------------------------------------------------
long tmtptCreateULIN(
	const double tole[],
	const long npnt,		//!< 点数
	const double pary[][3],	//!< 点列座標
	const double pmin[],	//!< MinMaxBoxの最小点座標
	const double pmax[],	//!< MinMaxBoxの最大点座標
	double pntL[],			//!< 直線基準点(重心点)
	double vecL[],			//!< 直線の方向ベクトル
	double *gap)			//!< 誤差和(==NULLあり)
{
	std::vector<point> pt;

	//データの準備
	data(pt, pary, npnt);

	eigen ev[3];
	point average;
	eigen_vector(ev, &average, pt);

	//[Add](2022.01.05 kanamura)
	pt.clear();

	double val = ev[0].val;
	int    idx = 0;

	//固有値が最大固有ベクトルを選ぶ
	for (int i = 1; i < 3; i++) {
		if (val < ev[i].val) {
			idx = i;
		}
	}

	//求めた方向ベクトルをセット
	vecL[0] = ev[idx].vec[0];//X
	vecL[1] = ev[idx].vec[1];//Y
	vecL[2] = ev[idx].vec[2];//Z

	//求めた重心点をセット
	pntL[0] = average.p[0];
	pntL[1] = average.p[1];
	pntL[2] = average.p[2];

	return 0;
}

//------------------------------------------------
//! 点群から誤差最小の平面を求める
//------------------------------------------------
int LUDecomposition(int n, double** aMatrix, double b[3], double* pRst);
int EigenJacobiMethod(double *a, double *v, int n);

long tmtptCreateUPLN(
	const double tole[],	//!< トレランス [0]:同一点判定値, [1]:アンダーフロー判定値
	const   long npnt,		//!< 点数
	const double pary[][3],	//!< 点列座標
	const double pmin[],	//!< MinMaxBoxの最小点座標
	const double pmax[],	//!< MinMaxBoxの最大点座標
	double pnto[],			//!< 平面基準点
	double vecN[],			//!< 法線方向単位ベクトル
	double *gap)			//!< 誤差和(==NULLあり)
{
	std::vector<point> pt;

	//データの準備
	data(pt, pary, npnt);

	eigen ev[3];
	point average;
	eigen_vector(ev, &average, pt);

	double val = ev[0].val;
	int    idx = 0;

	//固有値が最小の固有ベクトルを選ぶ
	for (int i = 1; i < 3; i++) {
		if (val > ev[i].val) {
			idx = i;
		}
	}

	//求めた法線方向ベクトルをセット
	//(※方向が逆らしいので*-1し、順番も違うので入れ替えた)
	/*
	double vec_x = ev[idx].vec[2] * -1;//Z
	double vec_y = ev[idx].vec[0] * -1;//X
	double vec_z = ev[idx].vec[1] * -1;//Y 
	*/
	/*
	double vec_x = ev[idx].vec[0];//X
	double vec_y = ev[idx].vec[1];//Y
	double vec_z = ev[idx].vec[2];//Z
	*/

	//上記より方向反転(2021.12.17yori)
	double vec_x = ev[idx].vec[0] * -1;//X
	double vec_y = ev[idx].vec[1] * -1;//Y
	double vec_z = ev[idx].vec[2] * -1;//Z 

	vecN[0] = vec_x;
	vecN[1] = vec_y;
	vecN[2] = vec_z;

	//求めた平面基準点(重心点)をセット
	pnto[0] = average.p[0];
	pnto[1] = average.p[1];
	pnto[2] = average.p[2];

	return 0;
}

//! @brief データの平均を求める
//! @param [in] vec データの配列
//! @return 各要素の平均
point Covariance_Ave(const std::vector<point>& vec) {

	// 初期化
	point ave;
	ave.p[0] = 0;
	ave.p[1] = 0;
	ave.p[2] = 0;

	// 各要素平均
	for (size_t i = 0; i < vec.size(); i++) {
		ave.p[0] += vec[i].p[0];
		ave.p[1] += vec[i].p[1];
		ave.p[2] += vec[i].p[2];
	}
	ave.p[0] /= vec.size();
	ave.p[1] /= vec.size();
	ave.p[2] /= vec.size();

	return ave;

}

//! @brief 共分散を求める
//! @param [in] average 各要素の平均
//! @param [in] vec データ
//! @param [in] param どの要素に対して求めるか。例えばxyzの時、x,yに対する共分散なら{0,1}を与える。
//! @return 偏差の積の和の要素数分の一
double Covariance(const point& average, const std::vector<point>& vec, const int param[]) {

	double sum = 0.0;
	for (size_t i = 0; i < vec.size(); i++) {

		//指定したパラメータの偏差を求める
		point deviation;
		for (size_t j = 0; j < 2; j++) {
			int target = param[j];
			deviation.p[target] = (vec[i].p[target] - average.p[target]);
		}

		//偏差の積
		double product = 1.0;
		for (size_t j = 0; j < 2; j++) {
			int target = param[j];
			product *= deviation.p[target];
		}

		//偏差の積の和を更新
		sum += product;
	}

	//偏差の積の和のN分の一
	return 1.0 / vec.size() * sum;
}

//! @brief データを主成分分析する
//! @param [out] ev 固有値と固有ベクトル
//! @param [in] average 全データの各要素の平均
//! @param [in] pt 三次元の座標値一覧
//! @return なし
void eigen_vector(eigen* ev, point* average, const std::vector<point>& pt) {

	//各要素の平均を求める。
	//これは共分散を求めるときに (x[i] - xの平均)×(y[i] - yの平均) 等の計算が必要なため
	*average = Covariance_Ave(pt);

	//共分散を求める
	//第三引数の{0,0}はxxを表す。xyなら{0,1}。これはデータがxyzの順に並んでいる事が前提。
	int param_1[] = { 0, 0 };  double Sxx = Covariance(*average, pt, param_1);
	int param_2[] = { 0, 1 };  double Sxy = Covariance(*average, pt, param_2);
	int param_3[] = { 0, 2 };  double Sxz = Covariance(*average, pt, param_3);
	int param_4[] = { 1, 1 };  double Syy = Covariance(*average, pt, param_4);
	int param_5[] = { 1, 2 };  double Syz = Covariance(*average, pt, param_5);
	int param_6[] = { 2, 2 };  double Szz = Covariance(*average, pt, param_6);

	// 分散共分散行列
	double a[3 * 3] = {
		Sxx,Sxy,Sxz,
		Sxy,Syy,Syz,
		Sxz,Syz,Szz
	};


	double v[3 * 3];
	int cnt = EigenJacobiMethod(a, v, 3);

	ev[0].val = a[0];   //固有値
	ev[0].vec[0] = v[0];//固有値に対応した固有ベクトル
	ev[0].vec[1] = v[3];
	ev[0].vec[2] = v[6];

	ev[1].val = a[4];   //固有値
	ev[1].vec[0] = v[1];//固有値に対応した固有ベクトル
	ev[1].vec[1] = v[4];
	ev[1].vec[2] = v[7];

	ev[2].val = a[8];   //固有値
	ev[2].vec[0] = v[2];//固有値に対応した固有ベクトル
	ev[2].vec[1] = v[5];
	ev[2].vec[2] = v[8];
}

void data(std::vector<point>& pt, const double pary[][3], int num) {
	
	//[UPLN]
	/*
	pt.emplace_back(25.846, 53.622, 100.532);
	pt.emplace_back(26.090, 54.942, 99.796);
	pt.emplace_back(24.846, 56.008, 98.646);
	pt.emplace_back(22.834, 56.785, 97.381);
	pt.emplace_back(20.822, 57.562, 96.116);
	pt.emplace_back(18.985, 57.685, 95.330);
	pt.emplace_back(17.798, 56.729, 95.473);
	pt.emplace_back(17.554, 55.409, 96.209);
	pt.emplace_back(18.799, 54.343, 97.359);
	pt.emplace_back(20.810, 53.566, 98.624);
	pt.emplace_back(22.822, 52.790, 99.888);
	pt.emplace_back(24.659, 52.666, 100.675);
	*/
	
	for (int i = 0; i < num; i++) {
		//pt.emplace_back(pary[i][0], pary[i][1], pary[i][2]);
		double x = pary[i][0];
		double y = pary[i][1];
		double z = pary[i][2];
		point* pPoint = new point(x, y, z);

		pt.push_back(*pPoint);

		//delete pPoint; //追加(2022.1.5yori)
	}
}

/*!
* Jacobi法による固有値の算出
* @param[inout] a 実対称行列．計算後，対角要素に固有値が入る
* @param[out] v 固有ベクトル(aと同じサイズ)
* @param[in] n 行列のサイズ(n×n)
* @param[in] eps 収束誤差
* @param[in] iter_max 最大反復回数
* @return 反復回数
* @see http://www.slis.tsukuba.ac.jp/~fujisawa.makoto.fu/cgi-bin/wiki/index.php?%B8%C7%CD%AD%C3%CD/%B8%C7%CD%AD%A5%D9%A5%AF%A5%C8%A5%EB
*/
int EigenJacobiMethod(double* a, double* v, int n)
{
	double* bim, *bjm;
	double bii, bij, bjj, bji;
	double eps = 1e-15;
	int iter_max = 100;

	bim = new double[n];
	bjm = new double[n];

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			v[i * n + j] = (i == j) ? 1.0 : 0.0;
		}
	}

	int cnt = 0;
	for (;;) {
		int i, j;

		float x = 0.0;
		for (int ia = 0; ia < n; ++ia) {
			for (int ja = 0; ja < n; ++ja) {
				int idx = ia * n + ja;
				if (ia != ja && fabs(a[idx]) > x) {
					i = ia;
					j = ja;
					x = fabs(a[idx]);
				}
			}
		}

		double aii = a[i * n + i];
		double ajj = a[j * n + j];
		double aij = a[i * n + j];

		double alpha, beta;
		alpha = (aii - ajj) / 2.0;
		beta = sqrt(alpha * alpha + aij * aij);

		double st, ct;
		ct = sqrt((1.0 + fabs(alpha) / beta) / 2.0);    // sinθ
		st = (((aii - ajj) >= 0.0) ? 1.0 : -1.0) * aij / (2.0 * beta * ct);    // cosθ

																			   // A = PAPの計算
		for (int m = 0; m < n; ++m) {
			if (m == i || m == j) continue;

			double aim = a[i * n + m];
			double ajm = a[j * n + m];

			bim[m] = aim * ct + ajm * st;
			bjm[m] = -aim * st + ajm * ct;
		}

		bii = aii * ct * ct + 2.0 * aij * ct * st + ajj * st * st;
		bij = 0.0;

		bjj = aii * st * st - 2.0 * aij * ct * st + ajj * ct * ct;
		bji = 0.0;

		for (int m = 0; m < n; ++m) {
			a[i * n + m] = a[m * n + i] = bim[m];
			a[j * n + m] = a[m * n + j] = bjm[m];
		}
		a[i * n + i] = bii;
		a[i * n + j] = bij;
		a[j * n + j] = bjj;
		a[j * n + i] = bji;

		// V = PVの計算
		for (int m = 0; m < n; ++m) {
			double vmi = v[m * n + i];
			double vmj = v[m * n + j];

			bim[m] = vmi * ct + vmj * st;
			bjm[m] = -vmi * st + vmj * ct;
		}
		for (int m = 0; m < n; ++m) {
			v[m * n + i] = bim[m];
			v[m * n + j] = bjm[m];
		}

		double e = 0.0;
		for (int ja = 0; ja < n; ++ja) {
			for (int ia = 0; ia < n; ++ia) {
				if (ia != ja) {
					e += fabs(a[ja * n + ia]);
				}
			}
		}
		if (e < eps) break;

		cnt++;
		if (cnt > iter_max) break;
	}

	delete[] bim;
	delete[] bjm;

	return cnt;
}

//->[]

//共分散
double coefficient(double *x, double *y, int len) {
	double avgx, avgy;
	double sumxy, sumxx, sumyy;
	int i;
	avgx = avgy = sumxx = sumyy = sumxy = 0.0;
	for (i = 0; i<len; ++i) {
		avgx += x[i];
		avgy += y[i];
	}

	avgx /= len;
	avgy /= len;
	for (i = 0; i<len; ++i) {
		sumxy += (x[i] - avgx)*(y[i] - avgy);
	}

	return sumxy / len;
}

//分散
double dispersion(double *x, double len) {
	double avgx = 0, diff = 0;
	double sumx = 0, sumxx = 0, powdiff[255];

	//平均
	for (int i = 0; i<len; ++i) {
		sumx += x[i];
	}

	avgx = sumx / len;

	//偏差ベクトル
	for (int i = 0; i<len - 1; ++i) {
		diff = avgx - x[i];
		powdiff[i] = pow(diff, 2.0);
		sumxx += powdiff[i];
	}

	return sumxx / len;
}




int Func(int npnt, const double pary[][3], double* rst)
{
	double x = 0.0;//Xの合計値
	double y = 0.0;//Yの合計値
	double z = 0.0;//Zの合計値
	double x2 = 0.0;//X^2の合計値
	double y2 = 0.0;//Y^2の合計値
	double xy = 0.0;//X*Yの合計値
	double xz = 0.0;//X*Zの合計値
	double yz = 0.0;//Y*Zの合計値


	//点群データから必要な合計値を算出
	for (int i = 0; i < npnt; i++) {
		double vx = pary[i][0];
		double vy = pary[i][2];//vy<-z
		double vz = pary[i][1];//vz<-y

		x += vx;
		x2 += (vx * vx);
		xy += (vx * vy);
		xz += (vx * vz);

		y += vy;
		y2 += (vy * vy);
		yz += (vy * vz);

		z += vz;
	}

	double** pMatA = new double*[3];
	for (int i = 0; i < 3; i++) {
		pMatA[i] = new double[3];
	}

	double l = 1 * npnt;

	pMatA[0][0] = l;
	pMatA[0][1] = x;
	pMatA[0][2] = y;
	//
	pMatA[1][0] = x;
	pMatA[1][1] = x2;
	pMatA[1][2] = xy;
	//
	pMatA[2][0] = y;
	pMatA[2][1] = xy;
	pMatA[2][2] = y2;

	double* pMatB = new double[3];
	pMatB[0] = z;
	pMatB[1] = xz;
	pMatB[2] = yz;

	double* Rst = new double[3];

	LUDecomposition(3, pMatA, pMatB, Rst);

	rst[0] = Rst[0];
	rst[1] = Rst[1];
	rst[2] = Rst[2];

	delete[] pMatA; //追加(2022.1.5yoir)
	delete[] pMatB; //追加(2022.1.5yoir)
	delete[] Rst; //追加(2022.1.5yoir)

	return 0;
}

int LUDecomposition(int n, double** aMatrix, double b[3], double* pRst)
{
	//---------------------------------------
	// LU分解用のバッファを生成
	//---------------------------------------
	double** pLMatrix = new double*[n];//L行列
	double** pUMatrix = new double*[n];//U行列
	double** pBuffer  = new double*[n];//計算用バッファ


	//二次元配列[][]として扱いたいので2段階で生成
	for (int i = 0; i < n; i++) {
		pLMatrix[i] = new double[n];
		pUMatrix[i] = new double[n];
		pBuffer[i]  = new double[n];
	}

	//L行列を零行列に初期化（ついでに計算要バッファも初期化)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			pLMatrix[i][j] = 0.0;
			pBuffer[i][j]  = 0.0;
		}
	}

	//U行列を対角要素を1に初期化(クラウト法)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				pUMatrix[i][j] = 1;
			}
			else {
				pUMatrix[i][j] = 0;
			}
		}
	}

	//LU分解処理
	for (int i = 0; i < n; i++) {
		int num = n - i - 1;

		double dL0 = pLMatrix[i][i] = aMatrix[0][0];

		//l1成分をコピー
		double* pL1 = new double[num];
		for (int j = 0; j < num; j++) {
			pLMatrix[j + i + 1][i] = pL1[j] = aMatrix[j + 1][0];
		}

		//U1^T成分をコピー
		double* pU1 = new double[num];
		for (int j = 0; j < num; j++) {
			pUMatrix[i][j + i + 1] = pU1[j] = aMatrix[0][j + 1] / dL0;
		}

		//LUを求める
		for (int j = 0; j < num; j++) {
			for (int k = 0; k < num; k++) {
				pBuffer[j][k] = pL1[j] * pU1[k];
			}
		}

		//A1の算出(n-1行列)
		double** pA1 = new double*[num];
		for (int i = 0; i < num; i++) {
			pA1[i] = new double[num];
		}

		for (int j = 0; j < num; j++) {
			for (int k = 0; k < num; k++) {
				pA1[j][k] = aMatrix[j + 1][k + 1] - pBuffer[j][k];
			}
		}
		//pA1を改めてamatrixとして再帰的に解いていく(ここ重要)
		aMatrix = pA1;

		delete[] pL1; //追加(2022.1.5yoir)
		delete[] pU1; //追加(2022.1.5yoir)
		delete[] pA1; //追加(2022.1.5yoir)
	}

	//求めたLU行列を使って連立方程式を解く
	double* pY = new double[n];
	for (int i = 0; i < n; i++) {
		double sum = 0.0;
		for (int k = 0; k <= i - 1; k++) {
			sum += pLMatrix[i][k] * pY[k];
		}
		pY[i] = (b[i] - sum) / pLMatrix[i][i];
	}

	double* pX = new double[n];
	for (int i = 0; i < n; i++) {
		pX[i] = 0.0;
	}

	for (int i = n - 1; i >= 0; i--) {
		double sum = 0.0;
		for (int j = i + 1; j <= n - 1; j++) {
			sum += pUMatrix[i][j] * pX[j];
		}
		pX[i] = pY[i] - sum;
	}

	pRst[0] = pX[0];
	pRst[1] = pX[1];
	pRst[2] = pX[2];

	delete[] pLMatrix; //追加(2022.1.5yoir)
	delete[] pUMatrix; //追加(2022.1.5yoir)
	delete[] pBuffer; //追加(2022.1.5yoir)
	delete[] pY; //追加(2022.1.5yoir)
	delete[] pX; //追加(2022.1.5yoir)

	return 0;
}

int SubFunc(int param_1, double* param_2, double* param_3, int* param_4, double* param_5)
{
	int		v5;
	int		v6;
	int*	pV8;
	double* pV7;
	double* pV9;


	v5  = param_1;
	v6  = 0;
	pV7 = param_2;
	pV8 = param_4;
	pV9 = param_3;

	param_3[0] = 0.0;
	param_3[1] = 0.0;
	param_3[2] = 0.0;

	return 0;
}



//------------------------------------------------
//! 無限直線と無限平面との交点を求める
//------------------------------------------------
long tmtIntersectULINxUPLN(
	const double  tole[2],	//! @param [in] トレランス(=許容範囲?)
	const double  pntl[3],	//! @param [in] 無限直線の基準点
	const double  vecl[3],	//! @param [in] 無限直線の単位ベクトル
	const double  pnta[3],	//! @param [in] 平面基準点
	const double  vecn[3],	//! @param [in] 平面の法線ベクトル
	double		  pntx[3])	//! @param [out] 求めた交点
{

	double v6  = vecn[0];
	double v7  = vecl[1];
	double v12 = vecl[2];
	double v13 = vecn[1];
	double v14 = vecn[2];
	double v15 = vecn[0];
	//
	double v16 = vecn[0] * vecl[0] + vecn[1] * vecl[1] + vecn[2] * vecl[2];
	double v17 = sqrt(vecl[0] * vecl[0] + vecl[1] * vecl[1] + vecl[2] * vecl[2]);//無限直線の単位ベクトルの大きさ?
	double v18 = v16 / sqrt(vecn[0] * vecn[0] + vecn[1] * vecn[1] + vecn[2] * vecn[2]);

	if (v18 <= 1.0) {
		if (v18 < -1.0) {
			v18 = -1.0;
		}
	}
	else {
		v18 = 1.0;
	}

	double v19 = acos(v18);
	double v20 = cos(v19);
	double v21 = tole[0];
	double v22 = fabs(v20);
	double* pV47 = new double[3];

	double v25;
	double v30;
	double dst;


	if (tole[0] > v22) {	
		//ポイントを平面に投影
		if (!tmtProjectPNT(tole, pnta, vecn, pntl, pV47, &dst) && tole[0] > fabs(*(double*)&dst)) {

			//無限直線の基準点を交点として返す
			pntx[0] = pntl[0];
			pntx[1] = pntl[1];
			pntx[2] = pntl[2];

			return (-1);
		}
		else {
			pntx[0] = 0.0;
			pntx[1] = 0.0;
			pntx[2] = 0.0;

			return(-2);
		}
	}

	if (tmtProjectPNT(tole, pnta, vecn, pntl, pV47, &dst)) {

		pntx[0] = 0.0;
		pntx[1] = 0.0;
		pntx[2] = 0.0;
		return(1);
	}

	v25 = dst;
	if(	(v21 > fabs(dst))||
		(v21 > fabs(v19))||
		(v21 > fabs(v19 - M_PI)))
	{
		//多分、OK
		pntx[0] = pV47[0];
		pntx[1] = pV47[1];
		pntx[2] = pV47[2];
		return 0;
	}

	if (v19 > RADIAN_90)
		v22 = fabs(cos(M_PI - v19));

	v30 = *(double*)&v25 / v22;
	tbfVecNrm(v21, vecl, pV47);

	double v31 = pntl[0];
	double v32 = pntl[1];
	double v53 = pntl[2];

	double v33 = pV47[0] * v30;
	double v34 = pV47[1] * v30;
	double v35 = pV47[2] * v30;

	double v36 = v31;
	double v37 = v32;
	double v38 = v31 + pV47[0] * v30;
	double v39 = v32 + pV47[1] * v30;
	double v40 = v53 + pV47[2] * v30;

	double v5012[3];
	v5012[0] = v38;
	v5012[1] = v39;
	v5012[2] = v40;

	tmtProjectPNT(tole, pnta, vecn, v5012, pV47, &dst);


	double dst_v53;
	double v41 = v36 + 0.0 - v33;
	double v42 = v37 + 0.0 - v34;
	double v43 = v53 + 0.0 - v35;
	v5012[0] = v41;
	v5012[1] = v42;
	v5012[2] = v43;

	double v24 = tmtProjectPNT(tole,  pnta, vecn,v5012, pV47,  &dst_v53);

	if (fabs(dst_v53) <= fabs(*(double*)&dst)) {
		pntx[0] = v41;
		pntx[1] = v42;
		pntx[2] = v43;
	}
	else {
		pntx[0] = v38;
		pntx[1] = v39;
		pntx[2] = v40;
	}

	delete[] pV47; //追加(2022.1.5yoir)

	return(v24);
}



//------------------------------------------------
//!  
//------------------------------------------------
void tbCalcMatrix(const double	planecod[3],	// (I) 面の基準点[xyz]
				  const double	planeijk[3],	// (I) 面の方向ベクトル[xyz]
				  const double	axiscod[3],		// (I) 軸の基準点[xyz]
				  const double	axisijk[3],		// (I) 軸の方向ベクトル[xyz]
				  const double	origincod[3],	// (I) 原点の基準点[xyz]
				  double		matrix[4][4])	// (O) 解（変換マトリクス）
{
	double v10;
	double v11[3];
	double v12[4];
	double v13[38];

	v10 = 0.0;//たぶん
	v11[0] = 1.0;
	v11[1] = 1.0;
	v11[2] = 1.0;

	v12[0] = 0.0;
	v12[1] = 0.0;
	v12[2] = 0.0;
	v12[3] = 0.0;

	double* pV9 = (double*)planecod;
	double* pV8 = (double*)planeijk;
	double* pV7 = (double*)axiscod;
	double* pV6 = (double*)axisijk;
	double* pV5 = (double*)origincod;


	sub_180007320(v13);
	sub_180008730(0, v10, pV9, pV8, 0, 0, pV7, pV6, pV5, v11, v12, v13);


	matrix[0][0] = v13[0];
	matrix[0][1] = v13[1];
	matrix[0][2] = v13[2];
	matrix[0][3] = v13[3];
	//
	matrix[1][0] = v13[4];
	matrix[1][1] = v13[5];
	matrix[1][2] = v13[6];
	matrix[1][3] = v13[7];
	//
	matrix[2][0] = v13[8];
	matrix[2][1] = v13[9];
	matrix[2][2] = v13[10];
	matrix[2][3] = v13[11];
	//
	matrix[3][0] = v13[12];
	matrix[3][1] = v13[13];
	matrix[3][2] = v13[14];
	matrix[3][3] = v13[15];
}


