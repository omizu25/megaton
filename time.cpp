//**************************************************
// 
// time.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "time.h"
#include "utility.h"
#include "application.h"
#include "mode.h"
#include "object2D.h"
#include "sound.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CTime::STD_WIDTH = 50.0f;
const float CTime::STD_HEIGHT = 60.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CTime* CTime::Create(const D3DXVECTOR3& pos, int start, int end)
{
	CTime* pTime = nullptr;

	pTime = new CTime;

	if (pTime != nullptr)
	{// null�`�F�b�N
		D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

		// ������
		pTime->Init(pos, size);
		pTime->m_start = start;
		pTime->m_end = end;
	}

	return pTime;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTime::CTime() :
	m_pPeriod(nullptr),
	m_start(0),
	m_elapsed(0),
	m_end(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTime::~CTime()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CTime::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	m_start = 0;
	m_elapsed = 0;
	m_end = 0;

	// ������
	CNumberManager::Init(pos, size);
	CNumberManager::SetZero(true);
	CNumberManager::SetZeroDigit(4);

	float interval = size.x * 0.5f;

	// �Ԋu�̐ݒ�
	CNumberManager::SetInterval(2, interval);

	// �s���I�h�̐���
	m_pPeriod = CObject2D::Create();

	D3DXVECTOR3 periodPos = D3DXVECTOR3(pos.x, pos.y + (size.y * 0.5f) - (size.y * 0.25f), 0.0f);
	periodPos.x = pos.x - ((size.x * 2.0f) + (interval * 0.5f));

	// �ʒu�̐ݒ�
	m_pPeriod->SetPos(periodPos);

	// �T�C�Y�̐ݒ�
	m_pPeriod->SetSize(size * 0.5f);

	// �e�N�X�`���̐ݒ�
	m_pPeriod->SetTexture(CTexture::LABEL_Period);

	// �t�F�[�h�̐ݒ�
	m_pPeriod->SetFade(0.0f);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CTime::Uninit()
{
	// �I��
	CNumberManager::Uninit();

	if (m_pPeriod != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pPeriod->Uninit();
		m_pPeriod = nullptr;
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTime::Release()
{
	// ���
	CNumberManager::Release();

	if (m_pPeriod != nullptr)
	{// null�`�F�b�N
		// ���
		m_pPeriod->Release();
		m_pPeriod = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CTime::Update()
{
	int time = timeGetTime();

	m_elapsed = (time - m_start);

	int number = m_end - (m_elapsed / 10);

	// ���̕ύX
	CNumberManager::Set(number);

	if (number < 0)
	{// ���Ԑ؂�
		// ���̕ύX
		CNumberManager::Set(0);

		// ���[�h�̕ύX
		CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_RESULT);

		// SE
		CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_GameClear);
	}
}

//--------------------------------------------------
// ��~
//--------------------------------------------------
void CTime::Restart()
{
	int time = timeGetTime();

	m_start += (time - (m_elapsed + m_start));
}
