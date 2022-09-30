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
	// �z�u�̏����ݒ�
	m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);			// �傫��
}

//=============================================================================
// �|���S���̏I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CTwinCircle::Uninit()
{

}

//=============================================================================
// �|���S���̍X�V
// Author : �������l
// �T�v : 2D�|���S���̍X�V���s��
//=============================================================================
void CTwinCircle::Update()
{
	m_wave.x += 0.1f;
	m_wave.y += 0.1f;
	NormalizeAngle(&m_wave.x);
	NormalizeAngle(&m_wave.y);
	m_moveTarget.x = sinf(m_wave.x) * 10.0f;
	m_moveTarget.y = cosf(m_wave.y) * -10.0f;

	// �U��q�̈ړ�
	D3DXVECTOR3 pos = pTarget1->GetPos() + m_moveTarget;
	pTarget1->SetPos(pos);
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

	// �^�[�Q�b�g�I�u�W�F�N�g�̐ݒ�
	pTarget1->SetPos(m_pos);

	// �U��q�I�u�W�F�N�g�̐ݒ�
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

	// �^�[�Q�b�g�I�u�W�F�N�g�̐ݒ�
	pTarget1->SetPos(m_rot);

	// �U��q�I�u�W�F�N�g�̐ݒ�
	pTarget1->SetPos(m_rot);
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