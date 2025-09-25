/***********************************************************************

	�J�E���g�f�[�^�i�[�N���X

***********************************************************************/
#include "CalibDataBuff.h"


// �R���X�g���N�^
CalibDataBuff::CalibDataBuff(void)
{
    InitBuff();
}

// �f�X�g���N�^
CalibDataBuff::~CalibDataBuff(void)
{
}

// �o�b�t�@������
int CalibDataBuff::InitBuff()
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_PtrR = 0;
    m_PtrW = 0;
    m_Len = 0;
    return 0;
}

// �f�[�^�ǉ��i�������݁F���t�Ȃ�Â��f�[�^���㏑���j
int CalibDataBuff::PutData(VecCtEx2 data)
{
    std::lock_guard<std::mutex> lock(m_Mutex);

    if (m_Len >= CALIBDATABUFF_BUFF_SIZE) {
        // �Â��f�[�^���̂Ă� �� �ǂݎ��|�C���^��i�߂�
        m_PtrR = (m_PtrR + 1) % CALIBDATABUFF_BUFF_SIZE;
        m_Len--; // ��U���炷�i�����++�����̂őS�̂ł͕ω����Ȃ��j
    }

    m_pCntData[m_PtrW] = data;
    m_PtrW = (m_PtrW + 1) % CALIBDATABUFF_BUFF_SIZE;
    m_Len++;

    return 0;
}

// �f�[�^�擾�i�ǂݎ��j
int CalibDataBuff::GetData(VecCtEx2* data)
{
    std::lock_guard<std::mutex> lock(m_Mutex);

    if (m_Len <= 0) {
        // �o�b�t�@��
        return -1;
    }

    *data = m_pCntData[m_PtrR];
    m_PtrR = (m_PtrR + 1) % CALIBDATABUFF_BUFF_SIZE;
    m_Len--;

    return 0;
}

// �f�[�^�폜�i�擪��1���폜�j
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

// ���݂̃f�[�^���擾
int CalibDataBuff::LenData(void)
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    return m_Len;
}