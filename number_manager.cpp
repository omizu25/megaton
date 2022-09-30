//**************************************************
// 
// number_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "number_manager.h"
#include "number.h"
#include "utility.h"
#include <assert.h>

//--------------------------------------------------
// ����
//--------------------------------------------------
CNumberManager* CNumberManager::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int value)
{
	CNumberManager* pNumberManager = nullptr;

	pNumberManager = new CNumberManager;

	if (pNumberManager != nullptr)
	{// null�`�F�b�N
		// ������
		pNumberManager->Init(pos, size);

		// ���̐ݒ�
		pNumberManager->Set(value);
	}

	return pNumberManager;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CNumberManager::CNumberManager() :
	m_value(0),
	m_zeroDigit(0),
	m_interval(0),
	m_width(0.0f),
	m_zero(false)
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		m_number[i] = nullptr;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CNumberManager::~CNumberManager()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		assert(m_number[i] == nullptr);
	}
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CNumberManager::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	m_value = 0;
	m_interval = 0;
	m_width = 0.0f;
	m_zero = false;
	m_zeroDigit = MAX_DIGIT;

	float halfWidth = size.x * 0.5f;

	float posX = 0.0f;

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		posX = pos.x - (halfWidth + (size.x * i));

		// ����
		m_number[i] = CNumber::Create(D3DXVECTOR3(posX, pos.y, 0.0f), size);
	}
	
	// �ύX
	Change();

	// �[���̕`��
	ZeroDraw();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CNumberManager::Uninit()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		if (m_number[i] != nullptr)
		{
			// �I��
			m_number[i]->Uninit();
			m_number[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CNumberManager::Release()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		if (m_number[i] != nullptr)
		{
			// ���
			m_number[i]->Release();
			m_number[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// ���Z
//--------------------------------------------------
void CNumberManager::Add(int value)
{
	m_value += value;

	// �ύX
	Change();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CNumberManager::Set(int value)
{
	m_value = value;

	// �ύX
	Change();
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int CNumberManager::Get()
{
	return m_value;
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void CNumberManager::SetPos(const D3DXVECTOR3& pos)
{
	D3DXVECTOR3 size = m_number[0]->GetSize();
	float halfWidth = size.x * 0.5f;

	float posX = 0.0f;

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		posX = pos.x - ((halfWidth + (size.x * i)) + ((i / m_interval) * m_width));

		// ����
		m_number[i]->SetPos(D3DXVECTOR3(posX, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void CNumberManager::SetCol(const D3DXCOLOR& col)
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// �F�̐ݒ�
		m_number[i]->SetCol(col);
	}
}

//--------------------------------------------------
// �`��̐ݒ�
//--------------------------------------------------
void CNumberManager::SetDraw(bool draw)
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// �`��̐ݒ�
		m_number[i]->SetDraw(draw);
	}
}

//--------------------------------------------------
// �[���̐ݒ�
//--------------------------------------------------
void CNumberManager::SetZero(bool zero)
{
	m_zero = zero;

	// �[���̕`��
	ZeroDraw();
}

//--------------------------------------------------
// �[���̌����̐ݒ�
//--------------------------------------------------
void CNumberManager::SetZeroDigit(int digit)
{
	m_zeroDigit = digit;

	// �[���̕`��
	ZeroDraw();
}

//--------------------------------------------------
// �Ԋu�̐ݒ�
//--------------------------------------------------
void CNumberManager::SetInterval(int interval, float width)
{
	m_interval = interval;
	m_width = width;

	if (m_interval == 0)
	{// �Ԋu�͂���Ȃ�
		m_interval = 1;
		m_width = 0.0f;
	}

	D3DXVECTOR3 size = m_number[0]->GetSize();
	float halfWidth = size.x * 0.5f;

	D3DXVECTOR3 pos = m_number[0]->GetPos();
	pos.x += halfWidth;

	float posX = 0.0f;

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		posX = pos.x - ((halfWidth + (size.x * i)) + ((i / m_interval) * m_width));

		// ����
		m_number[i]->SetPos(D3DXVECTOR3(posX, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// �`��̐ݒ�
//--------------------------------------------------
void CNumberManager::ZeroDraw()
{
	if (m_zero)
	{// �[����`�悷��
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			m_number[i]->SetDraw(false);
		}

		for (int i = 0; i < m_zeroDigit; i++)
		{
			m_number[i]->SetDraw(true);
		}
	}
	else
	{// �[����`�悵�Ȃ�
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			m_number[i]->SetDraw(false);
		}

		for (int i = 0; i < Digit(m_value); i++)
		{
			m_number[i]->SetDraw(true);
		}
	}

	// 1���ڂ͐�΂ɕ`�悷��
	m_number[0]->SetDraw(true);
}

//--------------------------------------------------
// �ύX
//--------------------------------------------------
void CNumberManager::Change()
{
	int num[MAX_DIGIT];

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		num[i] = 0;
	}

	int saveValue = m_value;

	for (int i = 0; i < Digit(m_value); i++)
	{// �ꌅ���ɕ�����
		num[i] = saveValue % 10;
		saveValue /= 10;
	}

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// ���̕ύX
		m_number[i]->Change(num[i]);
	}

	// �[���̕`��
	ZeroDraw();
}
