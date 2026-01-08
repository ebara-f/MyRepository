/***********************************************************************

    Vec Scanerからのデータ読み出しスレット MyForm_NonContactMenu::GetScanDataThread_new
    Polyworksへのデータ書き込みスレット　　MyForm_NonContactMenu::ReadScanDataThread
    より呼び出される関数群
    [add]nakayama 2020.09.28
    データ読込テストのためのクラスを追加
	移植(2025.5.15yori)

***********************************************************************/

/*
測定仕様（モード毎）
項目					単位			C＋		D		E		F		Fh
測定X幅※1				(mm)			213.54	100.36	50.44	51.28	21.56
X測定ピッチ				(mm)			0.125	0.125	0.062	0.031	0.031
X測定ピッチ（補間有り）	(mm)			0.063	0.063	0.031	0.016	0.016
ポイント速度			(点/秒)			68,600	61,677	68,085	75,015	70,700
ポイント速度（補間有り）(点/秒)			137,199	123,353	136,169	150,029	141,399
ライン速度				(ライン/秒)		40		77		85		45		100
ポイント数				(点/ライン)		1715	801		821		1667	707		// TDSLibrary.iniの[Section 00]の2=またはTdsVecGetModeを参照(2021.6.14yori)
ポイント数(補間有り)	(点/ライン)		3429	1601	1641	3333	1413	// 計算式：上記数値×2-1またはTdsVecGetModeを参照(2021.6.14yori)
*/


#pragma once
#include <stdio.h>

//コメントアウト(2021.9.10yori)
/*
#include "../Lib/AppQue(x64)/LplQue.h"
#include "../Lib/PSControl/TdsData.h"

#pragma comment( lib, "../Lib/AppQue(x64)/LplQue.lib")
#pragma comment( lib, "../Lib/PSControl/PSControl.lib")
*/

// *** #define MAX_LINEDATA 256								// ﾗｲﾝデータの確保数   MAX_ONELINEDATA * MAX_LINEDATA ポイント数宇が確保される
#define MAX_LINEDATA 1024

#define MAX_ONELINEDATA 3500							//測定幅213.54mm、測定ピッチ0.063mmで3389.52381点が最大？　詳細は「K470001-1003-G-0_ApiScan製品仕様書」P.10 // 3390→3500へ変更(2021.6.14yori)
														//#define MAX_ONELINEDATA 821
#define SHARED_MEMORY_NAME1 L"TEST_LINEDATA_MEMORY"		//共有メモリの名前（ラインデータ）  2021.4.2現在他で共有していない
														// スキャナより直接読み出し確保するバッファ
#define SHARED_MEMORY_NAME2 L"TEST_DATA_STATUS"			//共有メモリの名前（ステータス）	2021.4.2現在他で共有していない
														// スキャナから読み出しデータを転送するためのバッファ
#define SEMAPHORE_NAME L"SHAREDMEMORY"					//セマフォの名前  SharedMemoryでのみ使用
#define LOG_FILE_NAME L"KLLAppLineScanner_Log.txt"		//取り込んだデータを落とすファイルの名前

//#include "VecCnt.h" コメントアウト(2021.9.10yori)

//namespace nsVecApp { // コメントアウト(2025.5.15yori)

	//コメントアウト(2021.9.10yori)
	/*
	using namespace System::Windows::Forms; 
	using namespace nsVecCnt;			// 2021.3.5 Vectron i/f Dll
	*/

	//コメントアウト解除(2025.5.15yori)
	typedef struct{
		bool initflag;			//初期化フラグ
		int readIx;				//次に書き込むリングバッファの位置
		int writeIx;			//次に読み込むリングバッファの位置
		int userate;			//リングバッファの使用率
	}Status;

	typedef struct
	{
		int lineNo;		//3DデータのNo
		char	cDateTime[32];	//取り込んだ日時
		int iDataNum_Rec;		//取り込んだサンプルの数(戻り値)
		int iDataNum;			//取り込んだサンプルの数(引数値)
		PulsData*	ptPulsData;	//1ラインのデータ
		VecRet		tVecData;			//ベクトロンのデータ
	}OneLineData;

	// 以下の全データをPolyWorksへ送付するために作製(2021.5.27yori)
	typedef struct
	{
		int lineNo;								//3DデータのNo
		char cDateTime[32];						//取り込んだ日時
		int iDataNum_Rec;						//取り込んだサンプルの数(戻り値)
		int iDataNum;							//取り込んだサンプルの数(引数値)
		int iSendDataNo;						//有効データ数(2021.12.1yori)
		bool bMeasDataFg;						//スキャンデータの種類：測定データ=true、ダミースキャンデータ=false(2021.6.11yori)
		bool bButtonFg;							//トリガボタンの状態：OFF→ON=true、それ以外=false(2021.11.16yori)
		VecRet tVecData;						//ベクトロンのデータ
		PulsData tPulsData[MAX_ONELINEDATA];	//1ラインのデータ
	}OneLineData2;

	//コメントアウト(2021.9.10yori)
	/*
	public ref class SharedMemory
	{
	public:
	
		HANDLE hSEMA;							//セマフォのハンドル	
		HANDLE hSEMA2;							//セマフォのハンドル追加(2021.6.11yori)
		Status* ptstatus;						//データの状態
		OneLineData* ptlinedata;				//ラインデータの格納先
		OneLineData2* ptlinedata2;				// ラインデータの格納先(2021.5.27yori)
		HANDLE hMapLineData;					// 点郡データ自身転送用メモリマップドファイル
		HANDLE hMapData;						// 点郡データの転送用メモリマップドファイル

		int     m_iXSize;						// スキャン幅 スレット起動時にセットされる
		double	m_dXPitch;						// ﾋﾟｯﾁ
	
		const double INVALID_CHECK = 999998.0;	// 無効値判断値 (無効値は999999.0 floatデータのため）
		bool m_bmeasfg;							// 追加(2021.6.11yori)

	public:
		CVecCnt^ hVecCnt;						// Vectoron間通信制御クラス(MyFormで構築され参照のみ引き渡し) 
	
	public:
		SharedMemory();
		~SharedMemory();
		void GetMeasScanFlag(bool* ret_code);   // セマフォ用で作成(2021.6.11yori)
		void SetMeasScanFlag(bool flg_onoff);	// セマフォ用で作成(2021.6.11yori)

		bool Allocat_Memory();									//共有メモリ確保
		bool Memory_Read();										//メモリ読出し
		// bool SetVec1stPnt();					//ベクトロンの最初の1点をライブラリへ設定する
		// bool GetLineData(int iLineNo, int iXSize);			//1ラインのデータ書込み
		void Memory_ResetCounter();								// ストアーカウンタ郡のリセット
		// bool ResetOneLineData(int resetIx);						//読み出したあとラインデータをリセットする
		bool SendOneLineData();									//Queへラインデータを積む
		int SendLineDataCheck(int index, PulsData ptPData[]);	// 無効データのチェック
		void GetLocalTime(char* pBuf, int type);				//日時取得

	public:
		void ConvertVecTranceData(const VecDtEx* pGetData, VecRet* pVecData);		//構造体の内容がことなるため変換が必要
		void ConvertVecCtExTranceData(const VecDtEx* pGetData, VecCtEx* pVecData);	//構造体の内容がことなるため変換が必要(2021.8.9yori)
		// int GetSamplingData(int iMode);											//サンプリング作業 0-Dummy 1-main
		void SetTds1stPosition(const VecDtEx* pGetData);
		bool GetandStoreScannerLineData(const VecRet* pVecData, bool tranceFg);
		int SendPolyworksMessage(int TID, int Leng, char SBuf[]);
		void FileOutput(); // Debug用SWL形式で出力(2021.8.24yori)
		int iShotNo; // Debug用(2021.8.24yori)
		int iOldShotNo; // Debug用(2021.8.24yori)
		bool WriteOnceFg; // Debug用(2021.8.24yori)
		BOOL ScanCalibCalcu(); // Debug用(2021.8.31yori)
	};
	*/

//}