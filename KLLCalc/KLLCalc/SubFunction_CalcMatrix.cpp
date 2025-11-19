
#include "stdafx.h"
#include <math.h>
#include "KLLCalc.h"
#include "sub_functions.h"


void sub_180007320(double* pMtx)
{
	pMtx[0] = 1.0;// x3ff000000000000;
	pMtx[1] = 0.0;
	pMtx[2] = 0.0;
	pMtx[3] = 0.0;
	pMtx[4] = 0.0;
	//
	pMtx[5] = 1.0;// 0x3ff000000000000;
	pMtx[6] = 0.0;
	pMtx[7] = 0.0;
	pMtx[8] = 0.0;
	pMtx[9] = 0.0;
	//
	pMtx[10] = 1.0;//0x3ff000000000000;
	pMtx[11] = 0.0;
	pMtx[12] = 0.0;
	pMtx[13] = 0.0;
	pMtx[14] = 0.0;
	//
	pMtx[15] = 1.0;//0x3ff000000000000;
	pMtx[16] = 0.0;
	pMtx[17] = 0.0;
	pMtx[18] = 0.0;
	pMtx[19] = 0.0;
	//
	pMtx[20] = 0.0;
	pMtx[21] = 0.0;
	pMtx[22] = 0.0;
	pMtx[23] = 0.0;
	pMtx[24] = 0.0;
	//
	pMtx[25] = 0.0;
	pMtx[26] = 0.0;
	pMtx[27] = 0.0;
	pMtx[28] = 0.0;
	pMtx[29] = 0.0;
	//
	pMtx[30] = 0.0;
	pMtx[31] = 1.0;//0x3ff000000000000;
	pMtx[32] = 1.0;//0x3ff000000000000;
	pMtx[33] = 1.0;//0x3ff000000000000;
	pMtx[34] = -1;
	pMtx[35] = -1;
}

int sub_180008730(double* a1, double a2, double* a3, double* a4, int a5, double a6, double* a7, double* a8, double* a9, double* a10, double* a11, double* a12)
{
	double v69[3];
	double v75[3];
	double v81[3];
	double v83[8];
	double v84[2];
	double v85[32];

	v81[0] = 1.0;
	v81[1] = 0.0;
	//
	v83[0] = 0.0;
	v83[1] = 0.0;
	v83[2] = 1.0;
	v83[3] = 0.0;
	v83[4] = 0.0;
	v83[5] = 0.0;
	v83[6] = 1.0;
	//
	v84[0] = 0.001;//0x3F50624DD2F1A9FC
	v84[1] = 1.0e-12;//0x3D719799812DEA11
	//
	v85[0] = 0.0;
	v85[1] = 0.0;
	v85[2] = 1.0;
	v85[3] = 1.0;
	v85[4] = 0.0;
	v85[5] = 0.0;
	v85[6] = 0.0;
	v85[7] = 1.0;
	v85[8] = 0.0;
	v85[9] = 0.0;
	v85[10] = -2;

	double v12 = a3[0];
	double v13 = a3[1];
	double v14 = a3[2];

	double v78 = a4[0];
	double v79 = a4[1];
	double v80 = a4[2];

	sub_1800076C0(a12, v85, a4);
	
	double v16 = v13 * a12[1] + v12 * a12[0] + v14 * a12[2]  + a12[3];
	double v17 = v13 * a12[5] + v12 * a12[4] + v14 * a12[6]  + a12[7];
	double v18 = v12 * a12[8] + v13 * a12[9] + v14 * a12[10] + a12[11];

	v75[0] = v16 * -1.0;//=v75
	v75[1] = v17 * -1.0;//=v76
	v75[2] = v18 * -1.0;//=v77


	sub_1800083C0(a12, v75);

	v69[0] = a2 * 0.0;
	v69[1] = a2 * 0.0;
	v69[2] = a2;

	sub_1800083C0(a12, v69);


	a12[34] = 0.0;
	a12[16] = a2 * 0.0;
	a12[17] = a2 * 0.0;
	a12[18] = a2;
	a12[19] = 0.0;
	a12[20] = 0.0;
	a12[21] = 1.0;

	double v19 = a7[0];
	double v20 = a7[1];
	//
	double v21 = a8[0];
	double v22 = a8[1];
	double v23 = a8[2];
	//
	double v24 = a12[1];
	double v25 = a12[2];
	double v26 = a12[5];
	double v27 = a12[6];
	double v29 = a12[9];
	double v30 = a12[10];
	//
	v75[0] = a12[0] * a8[0] + v24 * v22 + v25 * v23;
	v75[1] = a12[4] * a8[0] + v26 * v22 + v27 * v23;
	v75[2] = a12[8] * a8[0] + v29 * v22 + v30 * v23;
	//


	double dDummy[20];
	for (int k = 0; k < 19; k++) {
		dDummy[k] = a12[k];
	}

	double v32 = a7[2];
	double v86 = a12[0] * v19 + v24 * v20 + v25 * v32 + a12[3];
	double v33 = a12[4] * v19 + v26 * v20 + v27 * v32 + a12[7];
	double v34 = a12[8] * v19 + v29 * v20 + v30 * v32 + a12[11];
	double v35 = a12[16];
	double v37 = a12[17];
	double v39 = a12[18];
	double v36 = v86 - v35;
	double v38 = v33 - v37;
	double v40 = v34 - v39;
	//
	double v43 = 0.0;
	double v44 = 0.0;
	double v45 = 0.0;
	double v46 = 0.0;
	//
	double v72[3];


	if (sqrt(v36 * v36 + v38*v38 + v40*v40) >= 0.001) {
		double v41 = a12[19];
		double v42 = sqrt(v41*v41 + a12[20] * a12[20] + a12[21] * a12[21]);

		if (v42 <= 0.001) {
			v43 = 0.0;
			v44 = 0.0;
			v45 = 0.0;
		}
		else {
			v43 = v41 * (1.0 / v42);
			v44 = 1.0 / v42 * a12[20];
			v45 = 1.0 / v42 * a12[21];
		}
		v46 = v44 * v38 + v43 * v36 + v45 * v40;
		v72[0] = v86 - v43 * v46;
		v72[1] = v33 - v44 * v46;
		v72[2] = v34 - v45 * v46;
	}
	else {
		v72[0] = v35;
		v72[1] = v37;
		v72[2] = v39;
	}

	//コードとは違うがsub_1800079F0の引き数的にこうなので定義
	v81[0] = 1.0;
	v81[1] = 0.0;
	v81[2] = 0.0;

	sub_180003790(v84, &a12[19], v75, v75);
	sub_1800079F0(a12, v85, a4, v81, v75, v72);

	double v47 = a7[1];
	double v48 = a7[2];
	double v49 = v47 * a12[1] + a7[0] * a12[0] + v48 * a12[2] + a12[3];
	double v50 = v47 * a12[5] + a7[0] * a12[4] + v48 * a12[6] + a12[7];
	double v51 = v47 * a12[9] + a7[0] * a12[8] + v48 * a12[10] + a12[11];//上の処理とは[]内のIndexが違う？

	double v52 = 0.0;
	double v53 = 1.0;
	double v54 = 1.0 - v52 - v53;
	double v55 = 1.0 - v52 - v52;
	double v56 = 1.0 - v53 - v52;

	v72[0] = v49 * v54 * -1.0;
	v72[1] = v50 * v55 * -1.0;
	v72[2] = v51 * v56 * -1.0;

	sub_1800083C0(a12, v72);

	double v57 = v54 * a6;
	double v58 = v55 * a6;
	double v59 = v56 * a6;

	v69[0] = v57;
	v69[1] = v58;
	v69[2] = v59;

	a12[16] = v57;
	a12[17] = v58;
	a12[18] = v59;
	a12[25] = 1.0;
	a12[26] = 0.0;
	a12[27] = 0.0;

	double v60 = a9[0];
	double v61 = a9[1];
	double v62 = a9[2];

	v78 = a11[0];
	v79 = a11[1];
	v80 = a11[2];

	double v63 = v61 * a12[1] + v60 * a12[0] + v62 * a12[2] + a12[3];
	double v64 = v61 * a12[5] + v60 * a12[4] + v62 * a12[6] + a12[7];
	double v65 = v61 * a12[9] + v60 * a12[8] + v62 * a12[10] + a12[11];

	/*for (int i = 0; i < 3; i++) {
		if (a10[4 * i] != 0.0) {
			double v69[3];
			v69[0] = v63 * v81[3 * i] * -1.0;
			v69[1] = v64 * v83[3 * i - 1] * -1.0;
			v69[2] = v65 * v83[3 * i] * -1.0;
			sub_1800083C0(a12, v69);
			//
			double v67 = a11[i];
			v69[0] = v67 * v81[3 * i];
			v69[1] = v67 * v83[3 * i - 1];
			v69[2] = v67 * v83[3 * i];
			sub_1800083C0(a12, v69);
		}
	}*/
	for (int i = 0;  i < 3; i++) {
		double v69[3] = { -0.0, -0.0, -0.0 };

		switch (i) {
		case 0:
			v69[0] = v63 * -1.0;
			break;
		case 1:
			v69[1] = v64 * -1.0;
			break;
		case 2:
			v69[2] = v65 * -1.0;
			break;
		}
		sub_1800083C0(a12, v69);

		v69[0] = v69[1] = v69[2] = 0.0;
		sub_1800083C0(a12, v69);
	}

	a12[28] = a11[0];
	a12[29] = a11[1];
	a12[30] = a11[2];

	return(0);
}

int sub_180003790(double* a1, double* a2, double* a3, double* a4)
{
	double v4 = 0.0;
	double v8 = a1[0];
	double v9 = a3[0];
	double v10;
	double v11;
	double v12;
	double v14;
	double v15;
	double v16;
	double v17;
	double v18;
	double v19;
	double v20;

	a4[0] = a3[0];
	a4[1] = a3[1];
	a4[2] = a3[2];


	if (v8 <= sqrt(a3[0] * a3[0] + a3[1] * a3[1] + a3[2] * a3[2])) {
		v12 = a3[1];
		v14 = a3[2];
		v15 = sqrt(a2[0] * a2[0] + a2[1] * a2[1] + a2[2] * a2[2]);

		if (v15 <= v8) {
			v16 = 0.0;
			v17 = 0.0;
			v18 = 0.0;
		}
		else {
			v16 = a2[0] * (1.0 / v15);
			v17 = 1.0 / v15 * a2[1];
			v18 = 1.0 / v15 * a2[2];
		}
		v19 = v17 * v12 + v16 * v9 + v18 * v14;
		v4  = v9  - v16 * v19;
		v10 = v12 - v17 * v19;
		v11 = v14 - v18 * v19;
	}
	else {
		v10 = 0.0;
		v11 = 0.0;
	}

	v20 = sqrt(v10 * v10 + v4 * v4 + v11 * v11);

	if (v20 <= v8) {
		a4[0] = 0.0;
		a4[1] = 0.0;
		a4[2] = 0.0;
	}
	else {
		a4[0] = v4  * (1.0 / v20);
		a4[1] = v10 * (1.0 / v20);
		a4[2] = v11 * (1.0 / v20);
	}

	return(0);
}

int sub_1800079F0(double* a1, double* a2, double* a3, double* a4, double* a5, double* a6)
{
	double v11;
	double v12;
	double v13;
	double v14;
	double v15;
	double v16;
	double v17;
	double v18;
	double v19;
	double v20;
	double v21;
	//
	double v55[3];
	double v58[3];
	double v59[4 * 4];
	double v75[4 * 4];
	double v91[3];
	double v92[4 * 4];
	double v93[4 * 4];


	v55[0] = 0.0;
	v55[1] = 0.0;
	v55[2] = 0.0;

	//関数内の処理は不明だが、戻り値=1.0なのでダミーとして1.0を返す
	v11 = sub_180007660(v55, a4);
	
	if (v11 >= 1.0e-12) {
		v12 = a4[0] / v11;
		v13 = a4[1] / v11;
		v14 = a4[2] / v11;
		v91[0] = v12;
		v91[1] = v13;
		v91[2] = v14;

		//関数内の処理は不明だが、戻り値=1.0なのでダミーとして1.0を返す
		v15 = sub_180007660(v55, a5);

		if (v15 >= 1.0e-12) {
			v16 = a5[0] / v15;
			v17 = a5[1] / v15;
			v18 = a5[2] / v15;
			v19 = sqrt(v14*v14 + v13 * v13 + v12 * v12);
			v20 = (v17 * v13 + v16 * v12 + v18 * v14) / (sqrt(v18 * v18 + v17 * v17 + v16 * v16) * v19);

			if (v20 <= 1.0) {
				if (v20 < -1.0) {
					v20 = -1.0;
				}
			}
			else {
				v20 = 1.0;
			}
			v21 = acos(v20);

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (i == j)
						v59[4 * i + j] = 1.0;
					else
						v59[4 * i + j] = 0.0;
				}
			}

			if (v55) {
				sub_180003120(0.001, v55, a2, v21, v59);
			}

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (i == j)
						v75[4 * i + j] = 1.0;
					else
						v75[4 * i + j] = 0.0;
				}
			}
			if (v55) {
				sub_180003120(0.001, v55, a2, v21 * -1.0, v75);
			}

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (i == j)
						v92[4 * i + j] = 1.0;
					else
						v92[4 * i + j] = 0.0;
				}
			}
			if (v55) {
				sub_180003120(0.001, v55, a3, v21, v92);
			}

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (i == j)
						v93[4 * i + j] = 1.0;
					else
						v93[4 * i + j] = 0.0;
				}
			}
			if (v55) {
				sub_180003120(0.001, v55, a3, v21*-1.0, v93);
			}


			double p59 = v59[0];
			double v60 = v59[1];
			double v61 = v59[2];
			double v62 = v59[3];
			double v63 = v59[4];
			double v64 = v59[5];
			double v65 = v59[6];
			double v66 = v59[7];
			double v67 = v59[8];
			double v68 = v59[9];
			double v69 = v59[10];
			double v70 = v59[11];
			double v71 = v59[12];
			double v72 = v59[13];
			double v73 = v59[14];
			double v74 = v59[15];
			//
			double p75 = v75[0];
			double v76 = v75[1];
			double v77 = v75[2];
			double v78 = v75[3];
			double v79 = v75[4];
			double v80 = v75[5];
			double v81 = v75[6];
			double v82 = v75[7];
			double v83 = v75[8];
			double v84 = v75[9];
			double v85 = v75[10];
			double v86 = v75[11];
			double v87 = v75[12];
			double v88 = v75[13];
			double v89 = v75[14];
			double v90 = v75[15];


			v55[0] = p59 * v16 + v60 * v17 + v61 * v18;
			v55[1] = v64 * v17 + v63 * v16 + v65 * v18;
			v55[2] = v68 * v17 + v67 * v16 + v69 * v18;
			//
			v58[0] = v76 * v17 + p75 * v16 + v77 * v18;
			v58[1] = v80 * v17 + v79 * v16 + v81 * v18;
			v58[2] = v84 * v17 + v83 * v16 + v85 * v18;

			double v30 = sub_180007660(v91, v55);
			double v31 = sub_180007660(v91, v58);

			v75[0]  = a1[0];
			v75[1]  = a1[1];
			v75[2]  = a1[2];
			v75[3]  = a1[3];
			v75[4]  = a1[4];
			v75[5]  = a1[5];
			v75[6]  = a1[6];
			v75[7]  = a1[7];
			v75[8]  = a1[8];
			v75[9]  = a1[9];
			v75[10] = a1[10];
			v75[11] = a1[11];
			v75[12] = a1[12];
			v75[13] = a1[13];
			v75[14] = a1[14];
			v75[15] = a1[15];


			double v32;
			double v33;
			double v34;
			double v35;
			double v36;
			double v37;

			if (v31 <= v30) {
				tbfMtxPrd(4, 4, 4, v75, v93, v59);
				v36   = a6[1];
				v37   = a6[2];
				v34   = v93[4] * a6[0] + v93[5] * v36   + v93[6] * v37 + v93[7];
				v35   = v93[8] * a6[0] + v93[9] * v36   + v93[10]* v37 + v93[11];
				a6[0] = v93[1] * v36   + v93[0] * a6[0] + v93[2] * v37 + v93[3];
			}
			else {
				tbfMtxPrd(4, 4, 4, v75, v92, v59);
				v32   = a6[1];
				v33   = a6[2];
				v34   = v92[4] * a6[0] + v92[5] * v32   + v92[6] * v33 + v92[7];
				v35   = v92[8] * a6[0] + v92[9] * v32   + v92[10]* v33 + v92[11];
				a6[0] = v92[1] * v32   + v92[0] * a6[0] + v92[2] * v33 + v92[3];
			}

			a6[1] = v34;
			a6[2] = v35;
			//
			a1[ 0] = v59[0];
			a1[ 1] = v59[1];
			a1[ 2] = v59[2];
			a1[ 3] = v59[3];
			a1[ 4] = v59[4];
			a1[ 5] = v59[5];
			a1[ 6] = v59[6];
			a1[ 7] = v59[7];
			a1[ 8] = v59[8];
			a1[ 9] = v59[9];
			a1[10] = v59[10];
			a1[11] = v59[11];
			a1[12] = v59[12];
			a1[13] = v59[13];
			a1[14] = v59[14];
			a1[15] = v59[15];

			return(1);
		}
	}
	return(0);
}

double sub_180007660(double* a1, double* a2)
{
	double v1;

	v1 = sub_1800075F0(a1, a2);//分からんのでカンで
	return(sqrt(v1));
}

double sub_1800075F0(double* a1, double* a2)
{
	//この関数内処理はアセンブラコードから作成
	double dA = a2[1] - a1[2];
	double dB = a2[0] - a1[0];
	double dC = a2[2] - a1[2];
	double dD = dA*dA + dB * dB + dC * dC;

	return(dD);
}



int sub_1800076C0(double* a1, double* a2, double* a3)
{
	if ((a2[0] == a3[0]) && (a2[1] == a3[1]) && (a2[2] == a3[2]))
		return(1);

	double v9;
	double v10;
	double v11;
	double v15[3];
	double v18[16];
	double v19[18];

	v15[0] = 0.0;
	v15[1] = 0.0;
	v15[2] = 0.0;

	sub_180007540(v15, a2, a3, v19);

	v9  = sqrt(a2[1] * a2[1] + a2[0] * a2[0] + a2[2] * a2[2]);
	v10 = (a3[0] * a2[0] + a3[1] * a2[1] + a3[2] * a2[2]) / sqrt(a3[0] * a3[0] + a3[1] * a3[1] + a3[2] * a3[2])*v9;

	if (v10 <= 1.0) {
		if (v10 < -1.0) {
			v10 = -1.0;
		}
	}
	else {
		v10 = 1.0;
	}

	//解析コードと異なるがアセンブラコードに合わせて変更
	double dHoge = acos(v10);
	dHoge *= -1.0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				v11 = j;
				v18[4 * i + j] = 1.0;
			}
			else {
				v11 = 4 * i + j;
				v18[4 * i + j] = 0.0;
			}
		}
	}

	//if()の判断条件が１つ足りないが意味が分からない
	v11 = 1.0;//tbがそうなのでとりあえずセット
	if (!sub_180003120(v11, v15, v19, dHoge ,v18)) {

		a1[0]  = v18[0];
		a1[1]  = v18[1];
		a1[2]  = v18[2];
		a1[3]  = v18[3];
		a1[4]  = v18[4];
		a1[5]  = v18[5];
		a1[6]  = v18[6];
		a1[7]  = v18[7];
		a1[8]  = v18[8];
		a1[9]  = v18[9];
		a1[10] = v18[10];
		a1[11] = v18[11];
		a1[12] = v18[12];
		a1[13] = v18[13];
		a1[14] = v18[14];
		a1[15] = v18[15];

		return(1);
	}
	return(0);
}

int sub_180003120(double a1, double* a2, double* a3, double a4, double* a5)
{
	double v8;
	double v9;
	double v10;
	double v11;
	double v12;
	double v13;
	double v15;
	double v16;
	double v17;
	double v22;
	double v23;
	double v24;
	double v27[4];
	double v28[16];
	double v29[16];
	double v30[16];
	double v31[18];
	double* pV14;
	double*pV21;
	//
	int    v20;


	if ((a3 == NULL) || (fabs(a4) < 0.00000001))
		return(1);

	v8 = a3[0];
	v9 = sqrt(v8*v8 + a3[1] * a3[1] + a3[2] * a3[2]);

	if (v9 + 0.00005 <= a1)
	//if (v9 + 0.00005 <= a1)//本チャン
	{
		v10 = 0.0;
		v11 = 0.0;
		v12 = 0.0;
	}
	else {
		v10 = v8 * (1.0 / v9);
		v11 = 1.0 / v9 * a3[1];
		v12 = 1.0 / v9 * a3[2];
	}

	//本コード
	v13 = sin(a4 * 0.5);
	v27[0] = cos(a4* 0.5);

	//<-[テスト用]
	//v13    = -0.9499290788093195;
	//v27[0] = 0.3124655904775399;
	//->[テスト用]

	v27[1] = v10 * v13;
	v27[2] = v11 * v13;
	v27[3] = v12 * v13;

	sub_180002f60(v27, v30);

	//pV14 = v29;
	v15 = a2[0];
	v16 = a2[1];
	v17 = a2[2];

	//単位行列の作成
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				v29[4*i+j] = 1.0;
			}
			else {
				v29[4*i+j] = 0.0;
			}
		}
	}

	v29[3]  = v15;
	v29[7]  = v16;
	v29[11] = v17;

	v20 = 0;
	pV21 = v28;
	v22 = v15 * -1.0;
	v23 = v16 * -1.0;
	v24 = v17 * -1.0;

	for (int k = 0; k < 4*4; k++) {
		double set_value = 0.0;
		switch (k) {
		case 0:
		case 5:
		case 10:
		case 15:
			set_value = 1.0;
			break;
		}
		v28[k] = set_value;
	}

	v28[3] = v22;
	v28[7] = v23;
	v28[11] = v24;

	//コードには無いがtbfMtxPrdが返すのは[0]～[15]までなので念ののため初期化
	for (int k = 0; k < 18; k++) {
		v31[k] = 0.0;
	}
	tbfMtxPrd(4, 4, 4, v30, v28, v31);
	tbfMtxPrd(4, 4, 4, v29, v31, a5);

	return(0);
}

int sub_180002f60(double* param_1, double* param_2)
{
	int v2;
	double v5;
	double v6;
	double v7;
	double v8;
	double v9;
	double v10;
	double v11;
	double v12;
	double v13;
	double v14;
	double v15;
	double v16;
	double v17;
	double v18;
	double* pResult;

	v2 = 0;
	pResult = param_2;

	do {
		for (int i = 0; i < 4; i++) {
			if (v2 == i) {
				*pResult = 1.0;
			}
			else {
				*pResult = 0.0;
			}
			pResult++;
		}
		v2++;

	} while (v2 < 4);

	v5 = param_1[0];
	v6 = param_1[1];
	v7 = param_1[2];
	v8 = param_1[3];
	v9 = v5 * v5;
	v10 = v5;
	v11 = v5;
	v12 = v5 * v8 * 2.0;
	v13 = v10 * v6 * 2.0;
	v14 = v8 * v6 * 2.0;
	v15 = v7 * v6 * 2.0;
	v16 = v8 * v7 * 2.0;
	v17 = v11 * v7 * 2.0;
	v18 = v9 - v6 * v6;

	param_2[8] = v14 - v17;
	param_2[2] = v17 + v14;
	param_2[0] = v9 + v6 * v6 - v7 * v7 - v8 * v8;
	param_2[1] = v15 - v12;
	param_2[4] = v12 + v15;
	param_2[10] = v18 - v7 * v7 + v8 * v8;
	param_2[5] = v18 + v7*v7 - v8*v8;
	param_2[9] = v13 + v16;
	param_2[6] = v16 - v13;
	param_2[15] = 1.0;

	//この関数の戻り値は使っていなさそうなので0を返す
	return 0;
}

int sub_180007540(double* a1, double* a2, double* a3, double* a4)
{
	double v5[3];
	double v6[5];

	v6[0] = a2[0] - a1[0];
	v6[1] = a2[1] - a1[1];
	v6[2] = a2[2] - a1[2];
	//
	v5[0] = a3[0] - a1[0];
	v5[1] = a3[1] - a1[1];
	v5[2] = a3[2] - a1[2];

	return(sub_180007430(v6, v5, a4));
}

int sub_180007430(double* a1, double* a2, double* a3)
{
	double v4;
	double v5;
	double v6;
	double v7;

	v4 = a2[2] * a1[1] - a1[2] * a2[1];
	v5 = a1[2] * a2[0] - a1[0] * a2[2];
	v6 = a1[0] * a2[1] - a2[0] * a1[1];

	v7 = sqrt(v4 * v4 + v5 * v5 + v6 * v6);

	if (v7 > 0.0) {
		a3[0] = v4 / v7;
		a3[1] = v5 / v7;
		a3[2] = v6 / v7;
	}
	else {
		a3[0] = v4;
		a3[1] = v5;
		a3[2] = v6;
	}

	return(1);
}

int sub_1800083C0(double* param_1, double* param_2)
{
	double v2;
	double v3;
	double v4;
	double v9;
	double v10;
	double v11;
	//

/*
	double v30 = param_1[1];
	double v34 = param_1[5];
	double v38 = param_1[9];
*/
	double v30 = param_1[3];
	double v34 = param_1[7];
	double v38 = param_1[11];


	v2 = param_2[0] * -1.0;
	v3 = param_2[1] * -1.0;
	v4 = param_2[2] * -1.0;
		

	if (param_2[0] == 0.0) {
		v9 = v30;
	}
	else {
		v9 = v30 - v2;
	}

	if (param_2[1] == 0.0) {
		v10 = v34;
	}
	else {
		v10 = v34 - v3;
	}

	if (param_2[2] == 0.0) {
		v11 = v38;
	}
	else {
		v11 = v38 - v4;
	}

	param_1[ 3] = v9;
	param_1[ 7] = v10;
	param_1[11] = v11;

	double dDummy[16];

	for (int k = 0; k < 16; k++) {
		dDummy[k] = param_1[k];
	}

	return(1);
}

