//=============================================================================
//
// 2D�Q�[�W�N���X(gauge2D.cpp)
// Author : �������l
// �T�v : 2D�Q�[�W�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "twin_circle.h"
#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "utility.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�Q�[�W�𐶐�����
//=============================================================================
CTwinCircle * CTwinCircle::Create(void)
{
	// �I�u�W�F�N�g�C���X�^���X
	CTwinCircle *pTwinCircle = nullptr;

	// �������̉��
	pTwinCircle = new CTwinCircle;

	if (pTwinCircle != nullptr)
	{// ���l�̏�����
		pTwinCircle->Init();
	}
	else
	{// �������̊m�ۂ��ł��Ȃ�����
		assert(false);
	}

	// �C���X�^���X��Ԃ�
	return pTwinCircle;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CTwinCircle::CTwinCircle(CObject::ECategory cat) : CObject(cat)
{
	pTarget0 = nullptr;									// �^�[�Q�b�g
	pTarget1 = nullptr;									// �^�[�Q�b�g1
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
	m_moveTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �^�[�Q�b�g�̈ړ���
	m_wave = D3DXVECTOR2(0.0f, 0.0f);					// �g
	m_fDistance = FLT_MAX;								// �^�[�Q�b�g�Ƃ̋���
	m_fMaxDistance = 0.0f;								// �^�[�Q�b�g�Ƃ̋����̍ő�
	m_nScore = 0;										// �X�R�A
	m_bAction = true;									// �A�N�V�������s����
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CTwinCircle::~CTwinCircle()
{

}

//=============================================================================
// �|���S���̏�����
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
void CTwinCircle::Init()
{
	//�ʒu�ݒ�p
	float fPosX = (CApplication::SCREEN_WIDTH * 0.32f);	//X��
	float fPosY = (CApplication::SCREEN_HEIGHT * 0.5f);	//Y��

	// �z�u�̏����ݒ�
	m_pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);			// �傫��

	// �^�[�Q�b�g�I�u�W�F�N�g0�̐ݒ�
	pTarget0 = CObject2D::Create();
	pTarget0->SetPos(m_pos);
	pTarget0->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	// �^�[�Q�b�g�I�u�W�F�N�g1�̐ݒ�
	pTarget1 = CObject2D::Create();
	pTarget1->SetPos(m_pos);
	pTarget1->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	// �f�B�X�^���X�̍ő�l
	float fMaxDistanceX = 1.0f / 0.1f * 18.0f;
	float fMaxDistanceY = 1.0f / 0.1f * 15.0f;
	m_fMaxDistance = sqrtf(fMaxDistanceX * fMaxDistanceX + fMaxDistanceY * fMaxDistanceY);
}

//=============================================================================
// �|���S���̏I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CTwinCircle::Uninit()
{
	pTarget0->Release();
	pTarget1->Release();
}

//=============================================================================
// �|���S���̍X�V
// Author : �������l
// �T�v : 2D�|���S���̍X�V���s��
//=============================================================================
void CTwinCircle::Update()
{
	if (m_bAction)
	{
		m_wave.x += 0.1f;
		m_wave.y += 0.1f;
		NormalizeAngle(&m_wave.x);
		NormalizeAngle(&m_wave.y);
		m_moveTarget.x = sinf(m_wave.x) * 18.0f;
		m_moveTarget.y = cosf(m_wave.y) * 15.0f;

		// �U��q�̈ړ�
		D3DXVECTOR3 pos0 = pTarget0->GetPos() + m_moveTarget;
		D3DXVECTOR3 pos1 = pTarget1->GetPos() - m_moveTarget;
		pTarget0->SetPos(pos0);
		pTarget1->SetPos(pos1);

		// �f�B�X�^���X�̐ݒ�
		float fDistanceX = pTarget0->GetPos().x - pTarget1->GetPos().x;
		float fDistanceY = pTarget0->GetPos().y - pTarget1->GetPos().y;
		if (fDistanceX < 0.0f)
		{
			fDistanceX *= -1;
		}
		else if (fDistanceY < 0.0f)
		{
			fDistanceY *= -1;
		}
		m_fDistance = sqrtf(fDistanceX * fDistanceX  + fDistanceY * fDistanceY);

		pTarget0->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pTarget1->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if (CollisionCircle(pTarget0->GetPos(), pTarget0->GetSize().x * 0.5f, pTarget1->GetPos(), pTarget1->GetSize().x * 0.5f))
		{
			pTarget0->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			pTarget1->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
	}
	else if (!m_bAction)
	{
		m_nScore = 100 - (int)(100.0f * (m_fDistance / m_fMaxDistance));

		if (m_nScore <= 0)
		{
			m_nScore = 0;
		}
	}
}

//=============================================================================
// �|���S���̕`��
// Author : �������l
// �T�v : 2D�|���S���̕`����s��
//=============================================================================
void CTwinCircle::Draw()
{

}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CTwinCircle::SetPos(const D3DXVECTOR3 &pos)
{
	// �z�u�̏����ݒ�
	m_pos = pos;			// �ʒu

	// �^�[�Q�b�g�I�u�W�F�N�g0�̐ݒ�
	pTarget0->SetPos(m_pos);

	// �^�[�Q�b�g�I�u�W�F�N�g1�̐ݒ�
	pTarget1->SetPos(m_pos);
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CTwinCircle::SetRot(const D3DXVECTOR3 &rot)
{
	// �z�u�̏����ݒ�
	m_rot = rot;				// ����
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CTwinCircle::SetSize(const D3DXVECTOR3 & size)
{
	// �z�u�̏����ݒ�
	m_size = size;				// �T�C�Y

	// �^�[�Q�b�g�I�u�W�F�N�g�̐ݒ�
	pTarget1->SetSize(m_size);

	// �U��q�I�u�W�F�N�g�̐ݒ�
	pTarget1->SetSize(m_size);
}