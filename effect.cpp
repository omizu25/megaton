//**************************************************
// 
// effect.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "effect.h"
#include "application.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CEffect::MAX_LIFE = 100;
const float CEffect::STD_WIDTH = 12.0f;
const float CEffect::STD_HEIGHT = 100.0f;
const float CEffect::MIN_WIDTH = 5.0f;

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CEffect::m_numAll = 0;

//--------------------------------------------------
// ����
//--------------------------------------------------
CEffect* CEffect::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXCOLOR& col)
{
	if (m_numAll >= CObject::GetMax(CObject::CATEGORY_EFFECT))
	{// �ő吔���z����
		return nullptr;
	}

	CEffect* pEffect = nullptr;

	pEffect = new CEffect;
	
	if (pEffect != nullptr)
	{// null�`�F�b�N
		pEffect->Init();
		pEffect->m_pos = pos;
		pEffect->m_move = move;
		pEffect->m_col = col;
	}

	return pEffect;
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
int CEffect::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEffect::CEffect() : CObject(CObject::CATEGORY_EFFECT),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f)),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_life(0),
	m_collision(false),
	m_colSubtract(false)
{
	m_numAll++;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEffect::~CEffect()
{
	m_numAll--;
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEffect::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(STD_WIDTH, STD_HEIGHT);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_life = MAX_LIFE;
	m_colSubtract = true;
	m_collision = true;

	// �L�[�v�̐ݒ�
	CObject::SetKeep(true);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEffect::Uninit()
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEffect::Update()
{
	m_life--;

	if (m_life <= 0)
	{
		CObject::Release();
		return;
	}

	m_pos += m_move;

	//�����E�ړ��ʂ��X�V (����������)
	m_move.x += (0.0f - m_move.x) * 0.05f;
	m_move.y += (0.0f - m_move.y) * 0.05f;
	
	float len = STD_HEIGHT * D3DXVec3Length(&m_move);

	if (len >= STD_HEIGHT)
	{// �w��̒l�����傫��
		len = STD_HEIGHT;
	}
	else if (len <= MIN_WIDTH)
	{// �w��̒l����������
		len = MIN_WIDTH;
	}

	m_size.y = len;

	if (m_colSubtract)
	{// �F�̌��Z
		float ratio = ((float)(MAX_LIFE - m_life) / MAX_LIFE);
		m_col.a = 1.0f - (ratio * ratio);
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEffect::Draw()
{
	/* �C���X�^���V���O�ŕ`�� */
}

//--------------------------------------------------
// �ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CEffect::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// �F�̎擾
//--------------------------------------------------
const D3DXCOLOR& CEffect::GetCol() const
{
	return m_col;
}

//--------------------------------------------------
// �ړ��ʂ̎擾
//--------------------------------------------------
const D3DXVECTOR3& CEffect::GetMove() const
{
	return m_move;
}

//--------------------------------------------------
// �T�C�Y�̎擾
//--------------------------------------------------
const D3DXVECTOR2& CEffect::GetSize() const
{
	return m_size;
}

//--------------------------------------------------
// �����蔻��̐ݒ�
//--------------------------------------------------
void CEffect::SetCollision(bool collision)
{
	m_collision = collision;
}

//--------------------------------------------------
// �F�̌��Z�����邩�ǂ����̐ݒ�
//--------------------------------------------------
void CEffect::SetColSubtract(bool subtract)
{
	m_colSubtract = subtract;
}
