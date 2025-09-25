/***********************************************************************

	カウントデータ格納クラス

***********************************************************************/
#include "CalibDataBuff.h"


// コンストラクタ
CalibDataBuff::CalibDataBuff(void)
{
    InitBuff();
}

// デストラクタ
CalibDataBuff::~CalibDataBuff(void)
{
}

// バッファ初期化
int CalibDataBuff::InitBuff()
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_PtrR = 0;
    m_PtrW = 0;
    m_Len = 0;
    return 0;
}

// データ追加（書き込み：満杯なら古いデータを上書き）
int CalibDataBuff::PutData(VecCtEx2 data)
{
    std::lock_guard<std::mutex> lock(m_Mutex);

    if (m_Len >= CALIBDATABUFF_BUFF_SIZE) {
        // 古いデータを捨てる → 読み取りポインタを進める
        m_PtrR = (m_PtrR + 1) % CALIBDATABUFF_BUFF_SIZE;
        m_Len--; // 一旦減らす（直後に++されるので全体では変化しない）
    }

    m_pCntData[m_PtrW] = data;
    m_PtrW = (m_PtrW + 1) % CALIBDATABUFF_BUFF_SIZE;
    m_Len++;

    return 0;
}

// データ取得（読み取り）
int CalibDataBuff::GetData(VecCtEx2* data)
{
    std::lock_guard<std::mutex> lock(m_Mutex);

    if (m_Len <= 0) {
        // バッファ空
        return -1;
    }

    *data = m_pCntData[m_PtrR];
    m_PtrR = (m_PtrR + 1) % CALIBDATABUFF_BUFF_SIZE;
    m_Len--;

    return 0;
}

// データ削除（先頭の1件削除）
int CalibDataBuff::DelData(void)
{
    std::lock_guard<std::mutex> lock(m_Mutex);

    if (m_Len <= 0) {
        return -1;
    }

    m_PtrR = (m_PtrR + 1) % CALIBDATABUFF_BUFF_SIZE;
    m_Len--;

    return 0;
}

// 現在のデータ数取得
int CalibDataBuff::LenData(void)
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    return m_Len;
}