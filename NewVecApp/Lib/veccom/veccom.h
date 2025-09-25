// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された VECCOM_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// VECCOM_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#pragma once

#ifdef VECCOM_EXPORTS
#define VECCOM_API __declspec(dllexport)
#else
#define VECCOM_API __declspec(dllimport)
#endif

////////////////////////////////////////////////////////////
// Error Code
#define VEC_OK				0
#define VEC_ER_STOP_WAT		1
#define VEC_ER_STOP_RST		2
#define VEC_ER_STOP_BUF		3
#define VEC_ER_STOP_OTR		4
#define	VEC_ER_OPEN			5
#define	VEC_ER_CLSE			6
#define VEC_ER_TMOT			7

#ifndef SOH
#define SOH				(char)0x01
#endif
#ifndef STX
#define STX				(char)0x02
#endif
#ifndef EOT
#define EOT				(char)0x04
#endif
#ifndef ENQ
#define ENQ				(char)0x05
#endif
#ifndef ACK
#define ACK				(char)0x06
#endif
#ifndef BS
#define BS				(char)0x08
#endif
#ifndef TAB
#define TAB				(char)0x09
#endif
#ifndef LF
#define LF				(char)0x0a
#endif
#ifndef CR
#define CR				(char)0x0d
#endif
#ifndef DC1
#define DC1				(char)0x11
#endif
#ifndef NAK
#define NAK				(char)0x15
#endif
#ifndef ESC
#define ESC				(char)0x1b
#endif
#ifndef SP
#define SP				(char)0x20
#endif

#define			GposLen		50
#define			GetCntLen		86
#define			GposV8Len	59	// 2021.11.25 更新
#define			GetCntV8Len	95	// 2021.11.25 更新


typedef unsigned int VEC_HANDLE;

typedef struct
{
	long	no;

	double	xyz[3];
	double	ijk[3];
	double	ijk2[3];
	
	unsigned int	button;

	int		er_code[9];	// 2008.1.29

} VecDt;


typedef struct	// 2012.8.27
{
	long	no;

	double	xyz[3];
	double	ijk[3];
	double	ijk2[3];
	
	unsigned int	button;

	int		er_code[9];

	double	angle[7];	////

	int		pbid_chg_fg;	// 1で変更有(2021.6.10)

	int		some_err_fg;	// !=0でエラー有(2021.11.25)

} VecDtEx;


typedef struct
{
	long	no;

	double	xyz[3];
	double	ijk[3];
	double	ijk2[3];
	
	unsigned int	button;
	
	long	cnt[9];

	int		er_code[9];	// 2008.1.29

} VecCt;


typedef struct
{
	long	no;

	double	xyz[3];
	double	ijk[3];
	double	ijk2[3];
	
	unsigned int	button;
	
	long	cnt[9];

	int		er_code[9];

	double	angle[7];	////

	int		pbid_chg_fg;	// 1で変更有(2021.6.10)

	int		some_err_fg;	// !=0でエラー有(2021.11.25)

} VecCtEx2; // TdsData.hで同じ構造体が定義されているため、VecCtEx→ VecCtEx2へ変更(2025.6.9yori)


typedef struct
{
	int		mode;
	unsigned int	init;
	int		ps_id;
	double	dia;
	int		beep;
	char 	EnErFg;	// エンコーダ不良検知フラグ
	char 	CnErFg;	// カウンタ基板故障検知フラグ
	char 	HsErFg;	// アーム内配線不良検知
	unsigned long 	PowLog;	// 通電時間ロギング機能(2021.8.11 unsignedに変更)
	char 	LimFg;	// 関節リミット軸表示機能
	char PsNo0Fg;	// No.0軸にエンコーダが付いているか判断する為のフラグ 2022.5.16

} VecSt;


// 2008.9.10
typedef struct
{
	double 	maxmin_x;
	double 	maxmin_y;
	double 	maxmin_z;
	double 	sigma2_x;
	double 	sigma2_y;
	double 	sigma2_z;
	double 	sigma2_r;
	double	menkangosa;
	double	menkanjig;
	short	judge;	// 1<-OK, 0<-NG
	char	ver;
} VecResult;


// 2021.6.11
// ApiScanTdsArm.iniのパラメータ格納用
typedef struct{
	double	No0[3];	// センサーチルトパラメータ基準値 基本固定値
	double	No1[3];	// センサーオフセットパラメータ基準値 基本固定値
	double	No2[3];	// センサーチルトパラメータ(可変)
	double	No3[3];	// センサーオフセットパラメータ(可変)

} VecTdsArmIni;



// 2021.6.11
// ProbeSetting.iniのパラメータ格納用
typedef struct{
	int		OffsetProbeUseFlag;					// プローブ登録フラグ(1:登録済、0:未登録)
	double	OffsetProbeTipAngle;					// プローブ先端曲がり角度
	double	OffsetProbeIjk2RotationAngle;		// IJK2回転角度
	int		OffsetProbeTouchFlag;				// タッチ式フラグ(0:通常　1:タッチ式)
	double	OffsetProbeBallDiameterCalib;		// ボール直径（点検/キャリブ用）
	double	OffsetProbeBallDiameterMeas;			// ボール直径（測定用）
	int		OffsetProbeTyp;						// プローブタイプ
													// 0:テーパ
													// 1:スタンダード
													// 2:エクステンション
													// 3:ストレート
													// 4:タッチ(V7/V8は無し)
	int		OffsetProbeCalibStatus;				// キャリブステータス(0:未実施　1:実施済み)
	double	OffsetProbeBallDiameterMeasBackup;	// ボール直径（測定用）※バックアップ用
	char	OffsetProbeCode[16];				// プローブ製品コード(半角英数文字)	// 2021.10.21(32->16変更)

} VecProbeSettingIni;



VECCOM_API int Vec_Open(VEC_HANDLE *pvecHandle, int tmout, char *dir);	// 引数追加(2018.6.5yori)
VECCOM_API int Vec_ReOpen(VEC_HANDLE* pvecHandle, int tmout);
VECCOM_API int Vec_Close(VEC_HANDLE vecHandle);
VECCOM_API int Vec_DataRequest(VEC_HANDLE vecHandle, int bufSize, VecDt *vecData, int *dataNo);
VECCOM_API int Vec_CntRequest(VEC_HANDLE vecHandle, int bufSize, VecCt *vecCntData, int *dataNo);
VECCOM_API int Vec_StatusRequest(VEC_HANDLE vecHandle, VecSt *vecStatus);
VECCOM_API int Vec_CmdTrans(VEC_HANDLE vecHandle, char *cmd, char *para, int paraNo);
VECCOM_API int Vec_CmdReceive(VEC_HANDLE vecHandle, char *cmd, char *para, int *paraNo);
VECCOM_API int Vec_SetPulsProbe(VEC_HANDLE vecHandle, double ofbx, double ofby, double ofbz, double ttbx, double ttby, double ttbz);
VECCOM_API int Vec_GetPulsProbe(VEC_HANDLE vecHandle, double *ofbx, double *ofby, double *ofbz, double *ttbx, double *ttby, double *ttbz);
VECCOM_API int Vec_WriteMemory(VEC_HANDLE vecHandle);
VECCOM_API int Vec_SetIpAddress(VEC_HANDLE vecHandle, DWORD dwAdrs);
VECCOM_API int Vec_SetNetworkAddress(VEC_HANDLE vecHandle, DWORD dwAdrs, DWORD dwMask, WORD wPort);
// 2012.8.27
VECCOM_API int Vec_DataRequestEx(VEC_HANDLE vecHandle, int bufSize, VecDtEx *vecData, int *dataNo);
VECCOM_API int Vec_CntRequestEx(VEC_HANDLE vecHandle, int bufSize, VecCtEx2 *vecCntData, int *dataNo); // TdsData.hで同じ構造体が定義されているため、VecCtEx→ VecCtEx2へ変更(2025.6.9yori)
// 2021.6.11
// ApiScanTdsArm.iniのパラメータ送受信関数
VECCOM_API int Vec_SetTdsArmIni (VEC_HANDLE vecHandle, VecTdsArmIni vecTdsArmIni);
VECCOM_API int Vec_GetTdsArmIni (VEC_HANDLE vecHandle, VecTdsArmIni *vecTdsArmIni);
// 2021.6.11
// ProbeSetting.iniのパラメータ送受信関数
VECCOM_API int Vec_SetProbeSettingIni (VEC_HANDLE vecHandle, VecProbeSettingIni vecProbeSettingIni[]);	// 17-19は枝番仕様に変更。使用しない(2022.1.13)
VECCOM_API int Vec_GetProbeSettingIni (VEC_HANDLE vecHandle, VecProbeSettingIni vecProbeSettingIni[]);

VECCOM_API int Vec_SetProbeSettingIniManual (VEC_HANDLE vecHandle, int  id/*(=17,18,19)*/, VecProbeSettingIni vecProbeSettingIni[]);	// 枝番0-14を入力
VECCOM_API int Vec_GetProbeSettingIniManual (VEC_HANDLE vecHandle, int  id/*(=17,18,19)*/, VecProbeSettingIni vecProbeSettingIni[]);	// 枝番0-14を入力
// 2021.7.16
VECCOM_API int Vec_DataRequestV8(VEC_HANDLE vecHandle, int bufSize, VecDtEx *vecData, int *dataNo);
VECCOM_API int Vec_CntRequestV8(VEC_HANDLE vecHandle, int bufSize, VecCtEx2 *vecCntData, int *dataNo); // TdsData.hで同じ構造体が定義されているため、VecCtEx→ VecCtEx2へ変更(2025.6.9yori)
// 2021.8.11
VECCOM_API int Vec_StatusRequestV8(VEC_HANDLE vecHandle, VecSt *vecStatus);

