//**************************************************
// 
// locus.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "locus.h"
#include "application.h"
#include "effect.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CLocus::STD_SIZE = 0.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CLocus* CLocus::Create()
{
	CLocus* pLocus = nullptr;

	pLocus = new CLocus;

	if (pLocus != nullptr)
	{// null�`�F�b�N
		pLocus->Init();
	}

	return pLocus;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CLocus::CLocus()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	m_fWave = 0.0f;								// �g
	m_fSpeed = 0.0f;							// ���x
	m_fWaveSpeed = 0.0f;						// �g�̉��Z��
	m_fWaveWidth = 0.0f;						// �g�̔{��
	m_nLife = 0;								// ����
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CLocus::~CLocus()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CLocus::Init()
{
	// ������
	CObject3D::Init();

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// ���x�̐ݒ�
	m_fSpeed = 1.0f;

	// �g�̉��Z��
	m_fWaveSpeed = 0.01f;

	// �g�̔{��
	m_fWaveWidth = 1.0f;

	// ����
	m_nLife = 300;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CLocus::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CLocus::Update()
{
	// �ړ��ʂ̐ݒ�
	m_fWave += m_fWaveSpeed;
	m_move.x = sinf(m_fWave) * m_fWaveWidth;
	m_move.y = cosf(0.0f) * m_fSpeed;

	// �ړ�
	SetPos(GetPos() + m_move);

	// �X�V
	CObject3D::Update();

	CEffect::Create(GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));

	m_nLife--;

	if (m_nLife <= 0)
	{
		m_nLife = 0;
		CObject::Release();
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CLocus::Draw()
{
	// �`��
	CObject3D::Draw();
}
