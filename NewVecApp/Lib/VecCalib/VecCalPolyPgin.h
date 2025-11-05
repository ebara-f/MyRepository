// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された VECCALPOLYPGIN_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// VECCALPOLYPGIN_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef VECCALPOLYPGIN_EXPORTS
#define VECCALPOLYPGIN_API __declspec(dllexport)
#else
#define VECCALPOLYPGIN_API __declspec(dllimport)
#endif

// このクラスは VecCalPolyPgin.dll からエクスポートされました。
/*class VECCALPOLYPGIN_API CVecCalPolyPgin {
public:
	CVecCalPolyPgin(void);
	// TODO: メソッドをここに追加してください。
};

extern VECCALPOLYPGIN_API int nVecCalPolyPgin;

VECCALPOLYPGIN_API int fnVecCalPolyPgin(void);*/

// 定義
// アーム型式
#define CALIB_VAR600M		"VAR600"
#define CALIB_VAR600M2		"VAR600MII"
#define CALIB_VAR600C		"VAR600C"
#define CALIB_VAR600CT		"VAR600CT"
//#define CALIB_VAR500G		"VAR500G"
//#define	CALIB_VAR300E	"VAR300E"
//#define	CALIB_VAR300	"VAR300"
//#define	CALIB_VAR200L	"VAR200L"
//#define	CALIB_VAR200	"VAR200"
#define	CALIB_VAR600MT		"VAR600MT"
#define	CALIB_VAR700M		"VAR700M"
#define	CALIB_VAR700L		"VAR700L"	//追加(2018.9.1)
#define	CALIB_VAR300M		"VAR300M"	//追加(2019.1.4)
#define	CALIB_VAR700LT		"VAR700LT"	//追加(2021.2.17yori)
#define CALIB_VAR800M		"VAR800M"	//追加(2021.6.8)
#define CALIB_VAR800L		"VAR800L"	//追加(2021.6.8)

// キャリブ種類
#define CALIB_MODE_USER									2	// マルチTprユーザキャリ				V6V7V8
#define CALIB_MODE_MAKER								1	// 500mmTprメーカキャリ				V6V7V8
#define CALIB_MODE_PROBE								4	// マルチStdプローブキャリ		V6V7
#define CALIB_MODE_PROBE_EXT						18	// マルチExtプローブキャリ		V6V7
//#define CALIB_MODE_PROBE_STR						19	// 未使用
#define CALIB_MODE_PLATE									5	// マルチStd面間点検orキャリ		V6V7V8
#define CALIB_MODE_PLATE_EXT							24	// マルチExt面間点検orキャリ		V6V7V8
#define CALIB_MODE_CHECK								13	// マルチStd始業前点検				V6V7V8
#define CALIB_MODE_PROBE_CHECK					14	// マルチStdプローブ点検			V6V7
#define CALIB_MODE_PROBE_CHECK_EXT			20	// マルチExtプローブ点検			V6V7V8
//#define CALIB_MODE_PROBE_CHECK_STR		21	// 未使用
#define CALIB_MODE_BALL									6	// ボールTchプローブ点検			V6V7		(V7は途中受注対応済、V8受注後対応予定)
#define CALIB_MODE_SIMPLE_BALL						15	// ボールStdプローブキャリ		V6V7V8
#define CALIB_MODE_SIMPLE_BALL_EXT				22	// ボールExtプローブキャリ		V6V7V8
//#define CALIB_MODE_SIMPLE_BALL_STR			23	// 未使用
//#define CALIB_MODE_SIMPLE_BALL_MASTER	16	// 未使用
//#define CALIB_MODE_SIMPLE_CONE					17	// 未使用
#define CALIB_MODE_MENKAN_B							8	// マルチStd面間点検					V6V7
#define CALIB_MODE_PITCH_X								9	// バーStdピッチ点検					V6V7V8
#define CALIB_MODE_ONE_BALL_CHECK			25 //ワンボール始業前点検(豊田自動織機様対応)(2022.5.6追加)


#define CALIB_GAUGE_LEN_V8				6	// N-1種類の長さでキャリブ可能(2021.6.9追加)

// ゲージの値
typedef struct
{
	double StylusDia;

	double BallBarLen;
	double PlateLen;
	double BallDia;
	double PitchBarLen;

	double BallBarLenV8[CALIB_GAUGE_LEN_V8];	// 5種類長さ対応・[0]は未使用 2021.6.9追加

	double AreaRFar;
	double AreaRNear;
	double AreaZHigh;
	double AreaZLow;
	double ErrMax;
	

} CALIB_GAUGE;

// プローブ点検閾値
typedef struct
{
	double pp;
	double sigma2;
	double plate;
	double ld;	// 回転位置誤差(ISO仕様)(2018.2.9追加)
	double pf;	// プロービング形状誤差(ISO仕様)(2018.2.9追加)
	double ps;	// 全姿勢プロービング寸法誤差(ISO仕様)(2018.2.9追加)
	double ri;	// 距離誤差(2018.2.16追加)
	double pl;	// プローブ長誤差(2018.2.16追加) -> 未使用(2021.6.28)
	double psi;	// 一姿勢プロービング寸法(球直径)誤差(2018.5.9追加) -> 球作成失敗を検知する為のしきい値(2021.6.28)

} CALIB_JUDGE;

// 始業前点検閾値
typedef struct
{
	double pp;
	double sigma2;
	double plate;
	double pitch;
	double maxmin; //ダミー点からの各球中心までの距離の最大－最小のしきい値(2022.4.21追加)

} CALIB_JUDGE_CK;

// 始業前点検結果
typedef struct
{
	double pp[4];		// MAX-MIN
	double sigma2[4];	// 2σ
	double plate;		// 面間距離
	double pitch;		// ピッチゲージ距離
	//double Cmax[3];		// xyz max center position err(2018.3.10追加)
	//double Cmin[3];		// xyz min center position err(2018.3.10追加)
	double Ps;			// diamter max size err(2018.3.10追加)
	double Pf;			// form err(reseve)(2018.3.10追加)
	double Ld;			// Ldia(2021.6.30追加)
	double ri;			// 距離誤差(2018.3.12追加)
	double cxyzd[4][50];//各球で測定した球中心座標値、直径(2022.4.21追加)
	double ave[4];		//球中心座標値、直径の平均値(2022.4.21追加)
	double sdevp[3];	//球中心座標値X、Y、Z の母集団標準偏差(2022.4.21追加)
	double sqrtdevsq;	//球直径D の偏差平方和の平方根(2022.4.21追加)
	double maxmin;		//ダミー点からの各球中心までの距離の最大－最小(2022.4.21追加)
	 
} CALIB_RESULT;


typedef struct
{
	char cmd[16];
	char para[2048];
	char para_in[2048];	// XYZ入力(2018.3.14追加)
	int no;

} CALIB_PAPA;

typedef struct
{
	CALIB_PAPA test002;
	CALIB_PAPA test004;
	CALIB_PAPA test006;
	CALIB_PAPA test008;
	CALIB_PAPA test010; //追加(2019.8.7)
	CALIB_PAPA test012; //追加(2019.8.7)
	CALIB_PAPA test018; //追加(2019.8.7)
	CALIB_PAPA sprdc;	//追加(2019.8.7)
	CALIB_PAPA sprdc2;
	CALIB_PAPA sprobe;	//追加(2019.8.7)

} CALIB_DATA;


// 初期化
VECCALPOLYPGIN_API int	CalibSetPath(char *path);	// 20213.6.23追加(iniファイル等の設定ファイルの場所を指定：一番初めにコールして欲しい関数)
VECCALPOLYPGIN_API int	CalibInit(/*char *path, */int language, int calbmode);	// 2021.6.23 path引数削除
VECCALPOLYPGIN_API int	CalibEnd(void);

// 設定
VECCALPOLYPGIN_API int	CalibGetArmNo(char *type, int bufsize);
VECCALPOLYPGIN_API int	CalibSetArmNo(char	*type, int bufsize);
VECCALPOLYPGIN_API int	CalibGetGaugeVal(CALIB_GAUGE *gauge);
VECCALPOLYPGIN_API int	CalibSetGaugeVal(CALIB_GAUGE gauge);
VECCALPOLYPGIN_API int	CalibGetSerialNo(char *mrx, int bufsize);
VECCALPOLYPGIN_API int	CalibSetSerialNo(char *mrx);
VECCALPOLYPGIN_API int	CalibGetThreshold(CALIB_JUDGE *val, int probeid);
VECCALPOLYPGIN_API int	CalibSetThreshold(CALIB_JUDGE val, int probeid);
VECCALPOLYPGIN_API int	CalibGetThresholdEx(CALIB_JUDGE *val, int probeid, int branch);	// 2022.6.17 枝番対応の為関数追加
VECCALPOLYPGIN_API int	CalibSetThresholdEx(CALIB_JUDGE val, int probeid, int branch);	// 2022.6.17 枝番対応の為関数追加
VECCALPOLYPGIN_API int	CalibGetThresholdCk(CALIB_JUDGE_CK *val);
VECCALPOLYPGIN_API int	CalibSetThresholdCk(CALIB_JUDGE_CK val);
VECCALPOLYPGIN_API int	CalibGetThresholdCkDef(CALIB_JUDGE_CK *val);	// 2016.6.24追加
VECCALPOLYPGIN_API int	CalibGetThresholdDef(CALIB_JUDGE *val, int probeid);	// 2016.6.24追加
VECCALPOLYPGIN_API int	CalibGetOneBallMesNo(int *count, int *point); //ワンボール始業前点検測定回数、点数の取得(2022.4.30追加)
VECCALPOLYPGIN_API int	CalibSetOneBallMesNo(int count, int point); //ワンボール始業前点検測定回数、点数の設定(2022.4.30追加)

// 共通
VECCALPOLYPGIN_API int	CalibMesReset(void);
VECCALPOLYPGIN_API int	CalibMesIn(VecCtEx2 *data);
VECCALPOLYPGIN_API int	CalibMesBack(void);
VECCALPOLYPGIN_API int	CalibMesOutPath(char *path);
VECCALPOLYPGIN_API int	CalibMesOutMesg(char *mesg1, char *mesg2);
VECCALPOLYPGIN_API int	CalibMesCheck(void);
VECCALPOLYPGIN_API int	CalibMesDataPosOut(int *position);
VECCALPOLYPGIN_API int	CalibMesPosChk(VecCtEx2 *data, double *radius, double *height);
VECCALPOLYPGIN_API int	CalibMesErrChk(VecCtEx2 *data, double *err);
VECCALPOLYPGIN_API int	CalibMesBallErrChk(double *err, int probeid);	// 球測定ミス確認(2018.2.9追加) // probeid追加(2018.5.9追加)
VECCALPOLYPGIN_API int	CalibMesOneBallCheck(int *count, int *point); //ワンボール始業前点検測定終了チェック、*count：測定回数カウントダウン、*point：測定点数カウントアップ(2022.5.10追加)

// ユーザー・プローブキャリブ関連
VECCALPOLYPGIN_API int	CalibCalParaIn(CALIB_DATA *data, int psid);					// 2021.7.29 V8用にPS ID 指定する為引数追加
VECCALPOLYPGIN_API int	CalibCalParaOut(int *result, CALIB_DATA *data, int psid);	// 2021.7.29 V8用にPS ID 指定する為引数追加
VECCALPOLYPGIN_API int	CalibCalParaInEx(CALIB_DATA *data, int psid, int branch);					// 2022.6.17 枝番対応の為関数追加
VECCALPOLYPGIN_API int	CalibCalParaOutEx(int *result, CALIB_DATA *data, int psid, int branch);	// 2022.6.17 枝番対応の為関数追加
VECCALPOLYPGIN_API int	CalibCalParaOutPlt(double plate, CALIB_DATA *data);

// 始業前点検結果・プローブ点検
VECCALPOLYPGIN_API int	CalibCheckResult(CALIB_RESULT *result);

// ワンボール点検結果(2018.3.12追加)
VECCALPOLYPGIN_API int	CalibCheckBallResult(CALIB_RESULT *result);
VECCALPOLYPGIN_API int	OutDataNo(int *no);	// 全測定点数(2018.3.14追加)
VECCALPOLYPGIN_API int	OutCntData(int no, CALIB_PAPA *data);	// カウント値出力(2018.3.14追加)
VECCALPOLYPGIN_API int	GetXYZData(int no, CALIB_PAPA *data);	// XYZ値入力(2018.3.14追加)

// ワンボール始業前点検(豊田自動織機様対応)(2022.5.12追加)
VECCALPOLYPGIN_API int	CalibMesOneBallResult(CALIB_RESULT *result); //各球で測定した球中心座標値と球直径を計算
VECCALPOLYPGIN_API int	CalibCheckOneBallResult(CALIB_RESULT *result); //点検結果を計算

// 面間点検結果
VECCALPOLYPGIN_API int	CalibPltCheckResult(CALIB_RESULT *result);

// ピッチ測定結果(2019.4.26追加)
VECCALPOLYPGIN_API int	CalibPitchCheckResult(CALIB_RESULT *result);

//自己診断関連(2019.8.9追加)
VECCALPOLYPGIN_API int	CalibParaRestore(CALIB_DATA *data, char *in_para);

// LOG機能関連(2016.8.10)
VECCALPOLYPGIN_API int	CalibLogSetTmp(char *tmp0, char *tmp3, char *tmp6,
									   char *ctmp0, char *ctmp3, char *ctmp6);

// デバッグ用
VECCALPOLYPGIN_API int	CalibTest(void);

// デバッグ用 20180409追加
void WhriteLog(char *log);