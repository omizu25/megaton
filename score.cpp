//**************************************************
// 
// score.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "score.h"
#include "application.h"
#include "game.h"
#include "object2D.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CScore::STD_WIDTH = 30.0f;
const float CScore::STD_HEIGHT = 40.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CScore* CScore::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	CScore* pScore = nullptr;

	pScore = new CScore;

	if (pScore != nullptr)
	{// null�`�F�b�N
		// ������
		pScore->Init(pos, size);
	}

	return pScore;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CScore::CScore()
{
	for (int i = 0; i < MAX_COMMA; i++)
	{
		m_pComma[i] = nullptr;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CScore::~CScore()
{
	for (int i = 0; i < MAX_COMMA; i++)
	{
		assert(m_pComma[i] == nullptr);
	}
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CScore::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// ������
	CNumberManager::Init(pos, size);

	float interval = size.x * 0.5f;

	// �Ԋu�̐ݒ�
	CNumberManager::SetInterval(3, interval);

	D3DXVECTOR3 commaSize = size * 0.5f;
	D3DXVECTOR3 commaPos = D3DXVECTOR3(pos.x, pos.y + (size.y * 0.5f) - (commaSize.y * 0.5f), 0.0f);
	float width = size.x * 3.0f;
	float halfInterval = interval * 0.5f;

	for (int i = 0; i < MAX_COMMA; i++)
	{
		// �J���}�̍쐬
		m_pComma[i] = CObject2D::Create();

		// �T�C�Y�̐ݒ�
		m_pComma[i]->SetSize(commaSize);

		// �e�N�X�`���̐ݒ�
		m_pComma[i]->SetTexture(CTexture::LABEL_Comma);

		commaPos.x = pos.x - ((i * width) + (i * interval) + width + halfInterval);
		
		// �ʒu�̐ݒ�
		m_pComma[i]->SetPos(commaPos);

		// �`��̐ݒ�
		m_pComma[i]->SetDraw(false);

		// �t�F�[�h�̐ݒ�
		m_pComma[i]->SetFade(0.0f);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CScore::Uninit()
{
	// �I��
	CNumberManager::Uninit();

	for (int i = 0; i < MAX_COMMA; i++)
	{
		if (m_pComma[i] != nullptr)
		{// null�`�F�b�N
			// �I��
			m_pComma[i]->Uninit();
			m_pComma[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CScore::Release()
{
	// ���
	CNumberManager::Release();

	for (int i = 0; i < MAX_COMMA; i++)
	{
		if (m_pComma[i] != nullptr)
		{// null�`�F�b�N
			// ���
			m_pComma[i]->Release();
			m_pComma[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// ���Z
//--------------------------------------------------
void CScore::Add(int score)
{
	// ���Z
	CNumberManager::Add(score);

	// �J���}�̕`��
	DrawComma();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CScore::Set(int score)
{
	// �ݒ�
	CNumberManager::Set(score);

	// �J���}�̕`��
	DrawComma();
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void CScore::SetCol(const D3DXCOLOR& col)
{
	// �F�̐ݒ�
	CNumberManager::SetCol(col);

	for (int i = 0; i < MAX_COMMA; i++)
	{
		// �F�̐ݒ�
		m_pComma[i]->SetCol(col);
	}
}

//--------------------------------------------------
// �J���}�̕`��
//--------------------------------------------------
void CScore::DrawComma()
{
	for (int i = 0; i < MAX_COMMA; i++)
	{
		// �`��̐ݒ�
		m_pComma[i]->SetDraw(false);
	}

	int comma = (Digit(CNumberManager::Get()) - 1) / 3;

	for (int i = 0; i < comma; i++)
	{
		// �`��̐ݒ�
		m_pComma[i]->SetDraw(true);
	}
}

//--------------------------------------------------
// ���Z�b�g
//--------------------------------------------------
void CScore::Reset(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, bool draw)
{
	float interval = size.x * 0.5f;

	// �ʒu�̐ݒ�
	CNumberManager::SetPos(pos);

	D3DXVECTOR3 commaPos = D3DXVECTOR3(pos.x, 0.0f, 0.0f);
	float width = size.x * 3.0f;
	float halfInterval = interval * 0.5f;

	for (int i = 0; i < MAX_COMMA; i++)
	{
		commaPos.x = pos.x - ((i * width) + (i * interval) + width + halfInterval);

		commaPos.y = m_pComma[i]->GetPos().y;

		// �ʒu�̐ݒ�
		m_pComma[i]->SetPos(commaPos);
	}

	if (!draw)
	{// �����\�����Ȃ�
		for (int i = 0; i < MAX_COMMA; i++)
		{
			// �`��̐ݒ�
			m_pComma[i]->SetDraw(false);
		}
	}
	else
	{
		for (int i = 0; i < MAX_COMMA; i++)
		{
			DrawComma();
		}
	}
}