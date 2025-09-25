// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ VECCALPOLYPGIN_EXPORTS
// �V���{���ŃR���p�C������܂��B���̃V���{���́A���� DLL ���g���v���W�F�N�g�Œ�`���邱�Ƃ͂ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// VECCALPOLYPGIN_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B
#ifdef VECCALPOLYPGIN_EXPORTS
#define VECCALPOLYPGIN_API __declspec(dllexport)
#else
#define VECCALPOLYPGIN_API __declspec(dllimport)
#endif

// ���̃N���X�� VecCalPolyPgin.dll ����G�N�X�|�[�g����܂����B
/*class VECCALPOLYPGIN_API CVecCalPolyPgin {
public:
	CVecCalPolyPgin(void);
	// TODO: ���\�b�h�������ɒǉ����Ă��������B
};

extern VECCALPOLYPGIN_API int nVecCalPolyPgin;

VECCALPOLYPGIN_API int fnVecCalPolyPgin(void);*/

// ��`
// �A�[���^��
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
#define	CALIB_VAR700L		"VAR700L"	//�ǉ�(2018.9.1)
#define	CALIB_VAR300M		"VAR300M"	//�ǉ�(2019.1.4)
#define	CALIB_VAR700LT		"VAR700LT"	//�ǉ�(2021.2.17yori)
#define CALIB_VAR800M		"VAR800M"	//�ǉ�(2021.6.8)
#define CALIB_VAR800L		"VAR800L"	//�ǉ�(2021.6.8)

// �L�����u���
#define CALIB_MODE_USER									2	// �}���`Tpr���[�U�L����				V6V7V8
#define CALIB_MODE_MAKER								1	// 500mmTpr���[�J�L����				V6V7V8
#define CALIB_MODE_PROBE								4	// �}���`Std�v���[�u�L����		V6V7
#define CALIB_MODE_PROBE_EXT						18	// �}���`Ext�v���[�u�L����		V6V7
//#define CALIB_MODE_PROBE_STR						19	// ���g�p
#define CALIB_MODE_PLATE									5	// �}���`Std�ʊԓ_��or�L����		V6V7V8
#define CALIB_MODE_PLATE_EXT							24	// �}���`Ext�ʊԓ_��or�L����		V6V7V8
#define CALIB_MODE_CHECK								13	// �}���`Std�n�ƑO�_��				V6V7V8
#define CALIB_MODE_PROBE_CHECK					14	// �}���`Std�v���[�u�_��			V6V7
#define CALIB_MODE_PROBE_CHECK_EXT			20	// �}���`Ext�v���[�u�_��			V6V7V8
//#define CALIB_MODE_PROBE_CHECK_STR		21	// ���g�p
#define CALIB_MODE_BALL									6	// �{�[��Tch�v���[�u�_��			V6V7		(V7�͓r���󒍑Ή��ρAV8�󒍌�Ή��\��)
#define CALIB_MODE_SIMPLE_BALL						15	// �{�[��Std�v���[�u�L����		V6V7V8
#define CALIB_MODE_SIMPLE_BALL_EXT				22	// �{�[��Ext�v���[�u�L����		V6V7V8
//#define CALIB_MODE_SIMPLE_BALL_STR			23	// ���g�p
//#define CALIB_MODE_SIMPLE_BALL_MASTER	16	// ���g�p
//#define CALIB_MODE_SIMPLE_CONE					17	// ���g�p
#define CALIB_MODE_MENKAN_B							8	// �}���`Std�ʊԓ_��					V6V7
#define CALIB_MODE_PITCH_X								9	// �o�[Std�s�b�`�_��					V6V7V8
#define CALIB_MODE_ONE_BALL_CHECK			25 //�����{�[���n�ƑO�_��(�L�c�����D�@�l�Ή�)(2022.5.6�ǉ�)


#define CALIB_GAUGE_LEN_V8				6	// N-1��ނ̒����ŃL�����u�\(2021.6.9�ǉ�)

// �Q�[�W�̒l
typedef struct
{
	double StylusDia;

	double BallBarLen;
	double PlateLen;
	double BallDia;
	double PitchBarLen;

	double BallBarLenV8[CALIB_GAUGE_LEN_V8];	// 5��ޒ����Ή��E[0]�͖��g�p 2021.6.9�ǉ�

	double AreaRFar;
	double AreaRNear;
	double AreaZHigh;
	double AreaZLow;
	double ErrMax;
	

} CALIB_GAUGE;

// �v���[�u�_��臒l
typedef struct
{
	double pp;
	double sigma2;
	double plate;
	double ld;	// ��]�ʒu�덷(ISO�d�l)(2018.2.9�ǉ�)
	double pf;	// �v���[�r���O�`��덷(ISO�d�l)(2018.2.9�ǉ�)
	double ps;	// �S�p���v���[�r���O���@�덷(ISO�d�l)(2018.2.9�ǉ�)
	double ri;	// �����덷(2018.2.16�ǉ�)
	double pl;	// �v���[�u���덷(2018.2.16�ǉ�) -> ���g�p(2021.6.28)
	double psi;	// ��p���v���[�r���O���@(�����a)�덷(2018.5.9�ǉ�) -> ���쐬���s�����m����ׂ̂������l(2021.6.28)

} CALIB_JUDGE;

// �n�ƑO�_��臒l
typedef struct
{
	double pp;
	double sigma2;
	double plate;
	double pitch;
	double maxmin; //�_�~�[�_����̊e�����S�܂ł̋����̍ő�|�ŏ��̂������l(2022.4.21�ǉ�)

} CALIB_JUDGE_CK;

// �n�ƑO�_������
typedef struct
{
	double pp[4];		// MAX-MIN
	double sigma2[4];	// 2��
	double plate;		// �ʊԋ���
	double pitch;		// �s�b�`�Q�[�W����
	//double Cmax[3];		// xyz max center position err(2018.3.10�ǉ�)
	//double Cmin[3];		// xyz min center position err(2018.3.10�ǉ�)
	double Ps;			// diamter max size err(2018.3.10�ǉ�)
	double Pf;			// form err(reseve)(2018.3.10�ǉ�)
	double Ld;			// Ldia(2021.6.30�ǉ�)
	double ri;			// �����덷(2018.3.12�ǉ�)
	double cxyzd[4][50];//�e���ő��肵�������S���W�l�A���a(2022.4.21�ǉ�)
	double ave[4];		//�����S���W�l�A���a�̕��ϒl(2022.4.21�ǉ�)
	double sdevp[3];	//�����S���W�lX�AY�AZ �̕�W�c�W���΍�(2022.4.21�ǉ�)
	double sqrtdevsq;	//�����aD �̕΍������a�̕�����(2022.4.21�ǉ�)
	double maxmin;		//�_�~�[�_����̊e�����S�܂ł̋����̍ő�|�ŏ�(2022.4.21�ǉ�)
	 
} CALIB_RESULT;


typedef struct
{
	char cmd[16];
	char para[2048];
	char para_in[2048];	// XYZ����(2018.3.14�ǉ�)
	int no;

} CALIB_PAPA;

typedef struct
{
	CALIB_PAPA test002;
	CALIB_PAPA test004;
	CALIB_PAPA test006;
	CALIB_PAPA test008;
	CALIB_PAPA test010; //�ǉ�(2019.8.7)
	CALIB_PAPA test012; //�ǉ�(2019.8.7)
	CALIB_PAPA test018; //�ǉ�(2019.8.7)
	CALIB_PAPA sprdc;	//�ǉ�(2019.8.7)
	CALIB_PAPA sprdc2;
	CALIB_PAPA sprobe;	//�ǉ�(2019.8.7)

} CALIB_DATA;


// ������
VECCALPOLYPGIN_API int	CalibSetPath(char *path);	// 20213.6.23�ǉ�(ini�t�@�C�����̐ݒ�t�@�C���̏ꏊ���w��F��ԏ��߂ɃR�[�����ė~�����֐�)
VECCALPOLYPGIN_API int	CalibInit(/*char *path, */int language, int calbmode);	// 2021.6.23 path�����폜
VECCALPOLYPGIN_API int	CalibEnd(void);

// �ݒ�
VECCALPOLYPGIN_API int	CalibGetArmNo(char *type, int bufsize);
VECCALPOLYPGIN_API int	CalibSetArmNo(char	*type, int bufsize);
VECCALPOLYPGIN_API int	CalibGetGaugeVal(CALIB_GAUGE *gauge);
VECCALPOLYPGIN_API int	CalibSetGaugeVal(CALIB_GAUGE gauge);
VECCALPOLYPGIN_API int	CalibGetSerialNo(char *mrx, int bufsize);
VECCALPOLYPGIN_API int	CalibSetSerialNo(char *mrx);
VECCALPOLYPGIN_API int	CalibGetThreshold(CALIB_JUDGE *val, int probeid);
VECCALPOLYPGIN_API int	CalibSetThreshold(CALIB_JUDGE val, int probeid);
VECCALPOLYPGIN_API int	CalibGetThresholdEx(CALIB_JUDGE *val, int probeid, int branch);	// 2022.6.17 �}�ԑΉ��̈׊֐��ǉ�
VECCALPOLYPGIN_API int	CalibSetThresholdEx(CALIB_JUDGE val, int probeid, int branch);	// 2022.6.17 �}�ԑΉ��̈׊֐��ǉ�
VECCALPOLYPGIN_API int	CalibGetThresholdCk(CALIB_JUDGE_CK *val);
VECCALPOLYPGIN_API int	CalibSetThresholdCk(CALIB_JUDGE_CK val);
VECCALPOLYPGIN_API int	CalibGetThresholdCkDef(CALIB_JUDGE_CK *val);	// 2016.6.24�ǉ�
VECCALPOLYPGIN_API int	CalibGetThresholdDef(CALIB_JUDGE *val, int probeid);	// 2016.6.24�ǉ�
VECCALPOLYPGIN_API int	CalibGetOneBallMesNo(int *count, int *point); //�����{�[���n�ƑO�_������񐔁A�_���̎擾(2022.4.30�ǉ�)
VECCALPOLYPGIN_API int	CalibSetOneBallMesNo(int count, int point); //�����{�[���n�ƑO�_������񐔁A�_���̐ݒ�(2022.4.30�ǉ�)

// ����
VECCALPOLYPGIN_API int	CalibMesReset(void);
VECCALPOLYPGIN_API int	CalibMesIn(VecCtEx2 *data);
VECCALPOLYPGIN_API int	CalibMesBack(void);
VECCALPOLYPGIN_API int	CalibMesOutPath(char *path);
VECCALPOLYPGIN_API int	CalibMesOutMesg(char *mesg1, char *mesg2);
VECCALPOLYPGIN_API int	CalibMesCheck(void);
VECCALPOLYPGIN_API int	CalibMesDataPosOut(int *position);
VECCALPOLYPGIN_API int	CalibMesPosChk(VecCtEx2 *data, double *radius, double *height);
VECCALPOLYPGIN_API int	CalibMesErrChk(VecCtEx2 *data, double *err);
VECCALPOLYPGIN_API int	CalibMesBallErrChk(double *err, int probeid);	// ������~�X�m�F(2018.2.9�ǉ�) // probeid�ǉ�(2018.5.9�ǉ�)
VECCALPOLYPGIN_API int	CalibMesOneBallCheck(int *count, int *point); //�����{�[���n�ƑO�_������I���`�F�b�N�A*count�F����񐔃J�E���g�_�E���A*point�F����_���J�E���g�A�b�v(2022.5.10�ǉ�)

// ���[�U�[�E�v���[�u�L�����u�֘A
VECCALPOLYPGIN_API int	CalibCalParaIn(CALIB_DATA *data, int psid);					// 2021.7.29 V8�p��PS ID �w�肷��׈����ǉ�
VECCALPOLYPGIN_API int	CalibCalParaOut(int *result, CALIB_DATA *data, int psid);	// 2021.7.29 V8�p��PS ID �w�肷��׈����ǉ�
VECCALPOLYPGIN_API int	CalibCalParaInEx(CALIB_DATA *data, int psid, int branch);					// 2022.6.17 �}�ԑΉ��̈׊֐��ǉ�
VECCALPOLYPGIN_API int	CalibCalParaOutEx(int *result, CALIB_DATA *data, int psid, int branch);	// 2022.6.17 �}�ԑΉ��̈׊֐��ǉ�
VECCALPOLYPGIN_API int	CalibCalParaOutPlt(double plate, CALIB_DATA *data);

// �n�ƑO�_�����ʁE�v���[�u�_��
VECCALPOLYPGIN_API int	CalibCheckResult(CALIB_RESULT *result);

// �����{�[���_������(2018.3.12�ǉ�)
VECCALPOLYPGIN_API int	CalibCheckBallResult(CALIB_RESULT *result);
VECCALPOLYPGIN_API int	OutDataNo(int *no);	// �S����_��(2018.3.14�ǉ�)
VECCALPOLYPGIN_API int	OutCntData(int no, CALIB_PAPA *data);	// �J�E���g�l�o��(2018.3.14�ǉ�)
VECCALPOLYPGIN_API int	GetXYZData(int no, CALIB_PAPA *data);	// XYZ�l����(2018.3.14�ǉ�)

// �����{�[���n�ƑO�_��(�L�c�����D�@�l�Ή�)(2022.5.12�ǉ�)
VECCALPOLYPGIN_API int	CalibMesOneBallResult(CALIB_RESULT *result); //�e���ő��肵�������S���W�l�Ƌ����a���v�Z
VECCALPOLYPGIN_API int	CalibCheckOneBallResult(CALIB_RESULT *result); //�_�����ʂ��v�Z

// �ʊԓ_������
VECCALPOLYPGIN_API int	CalibPltCheckResult(CALIB_RESULT *result);

// �s�b�`���茋��(2019.4.26�ǉ�)
VECCALPOLYPGIN_API int	CalibPitchCheckResult(CALIB_RESULT *result);

//���Ȑf�f�֘A(2019.8.9�ǉ�)
VECCALPOLYPGIN_API int	CalibParaRestore(CALIB_DATA *data, char *in_para);

// LOG�@�\�֘A(2016.8.10)
VECCALPOLYPGIN_API int	CalibLogSetTmp(char *tmp0, char *tmp3, char *tmp6,
									   char *ctmp0, char *ctmp3, char *ctmp6);

// �f�o�b�O�p
VECCALPOLYPGIN_API int	CalibTest(void);

// �f�o�b�O�p 20180409�ǉ�
void WhriteLog(char *log);