//-----------------------------------------------------------------------------
//１．キュー操作関数
//  プロセス間のデータ通信関数が有ります。
//
//DLL名            :LplQue.dll
//LIB名            :LplQue.lib
//ヘッダーファイル :LplQue.h
//
//-------------------------------------------
//  プロセス間データ通信関数
//-------------------------------------------
//
//			関数名	            		内 容
//	LplInitialIFCommon			プロセス間共有データ管理領域の初期化
//	LplInitialIFCommonEx		プロセス間共有データ管理領域の初期化(番号指定版)
//	LplSendMesBox	        	他プロセスへのデータ送信
//	LplRecvMesBox	        	他プロセスからのデータ受信
//	LplCreateCommonArea			プロセス間共通領域の確保
//
//	LplSendMesBox2			    他プロセスへのデータ送信(キューを介在させないモード)
//	LplSendMesBoxBuffferEmpty	バッファが空かどうかを判断
//	LplTerminateALL	            プロセス間共有データ管理領域の終了処理
//
//-----------------------------------------------------------------------------
extern void		__stdcall LplInitialIFCommon(void);
extern void		__stdcall LplInitialIFCommonEx(int TblNo);
extern int		__stdcall LplSendMesBox(int TID, int Leng, char SBuf[]);
extern int		__stdcall LplRecvMesBox(int TId, char RBuf[]);
extern char*	__stdcall LplCreateCommonArea(char CName[], int CSize);

extern int 		__stdcall LplSendMesBox2(int TId, int Leng, char SBuf[]);	// 2021.4.15
extern int 		__stdcall LplSendMesBoxBuffferEmpty(int TId);				// 2021.4.15

extern void	    __stdcall LplTerminateALL();                                // 2025.4.11
extern void	    __stdcall LplGetQueCount(int TId, int* pWCnt, int* pRCnt);
