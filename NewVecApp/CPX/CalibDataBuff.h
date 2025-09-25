/***********************************************************************

	カウントデータを格納する関数
	2025.9.2 eba
	トリガーボタンを押したデータが発生するとPutData関数の
	戻り値を１とし、AppMain内のワーカースレッドでメッセージを
	C#へ送信し、CalibCommのUpDateData関数をコールバックさせるしくみ

***********************************************************************/

#pragma once
#include <mutex>
#include "HwCtrl.h"

#define CALIBDATABUFF_BUFF_SIZE	0x000F

// 暫定で限られた範囲でこの構造体を使う
// パルスの名前とバッティングするらしいのでプロジェクト内でグローバルに使えない
/*typedef struct
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

} VecCtEx;*/


class CalibDataBuff
{
public :
	CalibDataBuff(void);
	virtual ~CalibDataBuff(void);

private :
	VecCtEx2 m_pCntData[CALIBDATABUFF_BUFF_SIZE];

	int m_PtrR;
	int m_PtrW;
	int m_Len;

	std::mutex m_Mutex; // 排他制御用ミューテックス

public:
	int InitBuff();
	int PutData(VecCtEx2 data);
	int GetData(VecCtEx2* data);
	int DelData(void);
	int LenData(void);

};