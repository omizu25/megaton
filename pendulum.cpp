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
#include <math.h>

#include "pendulum.h"
#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "utility.h"
#include "sound.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�Q�[�W�𐶐�����
//=============================================================================
CPendulum * CPendulum::Create(void)
{
	// �I�u�W�F�N�g�C���X�^���X
	CPendulum *pPendulum = nullptr;

	// �������̉��
	pPendulum = new CPendulum;

	if (pPendulum != nullptr)
	{// ���l�̏�����
		pPendulum->Init();
	}
	else
	{// �������̊m�ۂ��ł��Ȃ�����
		assert(false);
	}

	// �C���X�^���X��Ԃ�
	return pPendulum;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CPendulum::CPendulum(CObject::ECategory cat) : CObject(cat)
{
	pTarget = nullptr;									// �^�[�Q�b�g
	pPendulum = nullptr;								// �U��q
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);				// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
	m_movePendulum = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �U��q�̈ړ���
	m_wave = D3DXVECTOR2(0.0f,0.0f);					// �g
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
CPendulum::~CPendulum()
{

}

//=============================================================================
// �|���S���̏�����
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
void CPendulum::Init()
{
	//�ʒu�ݒ�p
	float fPosX = (CApplication::SCREEN_WIDTH * 0.23f);	//X��
	float fPosY = (CApplication::SCREEN_HEIGHT * 0.7f);	//Y��

	// �z�u�̏����ݒ�
	m_pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);			// �傫��

	// �^�[�Q�b�g�I�u�W�F�N�g�̐ݒ�
	pTarget = CObject2D::Create();
	pTarget->SetPos(m_pos);
	pTarget->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	pTarget->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	pTarget->SetTexture(CTexture::LABEL_Circle_Green);

	// �U��q�I�u�W�F�N�g�̐ݒ�
	pPendulum = CObject2D::Create();
	pPendulum->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));
	pPendulum->SetSize(D3DXVECTOR3(45.0f, 45.0f, 0.0f));
	pPendulum->SetTexture(CTexture::LABEL_Pien_White);

	// �f�B�X�^���X�̍ő�l
	m_fMaxDistance = 400.0f;
}

//=============================================================================
// �|���S���̏I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CPendulum::Uninit()
{
	CApplication::GetInstanse()->GetSound()->Stop(CSound::LABEL_SE_Gauge_Halfway);
	pTarget->Release();
	pPendulum->Release();
}

//=============================================================================
// �|���S���̍X�V
// Author : �������l
// �T�v : 2D�|���S���̍X�V���s��
//=============================================================================
void CPendulum::Update()
{
	if(m_bAction)
	{// �ړ��l�̎Z�o
		m_wave.x += 0.05f;
		m_wave.y += 0.1f;
		NormalizeAngle(&m_wave.x);
		NormalizeAngle(&m_wave.y);
		m_movePendulum.x = cosf(m_wave.x) * 10.0f;
		m_movePendulum.y = sinf(m_wave.y) * -20.0f;

		// �U��q�̈ړ�
		D3DXVECTOR3 pos = pPendulum->GetPos() + m_movePendulum;
		pPendulum->SetPos(pos);

		// �f�B�X�^���X�̐ݒ�
		m_fDistance = pTarget->GetPos().y - pPendulum->GetPos().y;

		if (m_fDistance < 0.0f)
		{
			m_fDistance = 0.0f;
		}

		pPendulum->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if (CollisionCircle(pPendulum->GetPos(), pPendulum->GetSize().x * 0.5f, pTarget->GetPos(), pTarget->GetSize().x * 0.5f))
		{
			pPendulum->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Gauge_Halfway);
		}
	}
	else if (!m_bAction)
	{
		m_nScore = (int)(100 - (100 * m_fDistance / m_fMaxDistance));
	}
}

//=============================================================================
// �|���S���̕`��
// Author : �������l
// �T�v : 2D�|���S���̕`����s��
//=============================================================================
void CPendulum::Draw()
{

}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CPendulum::SetPos(const D3DXVECTOR3 &pos)
{
	// �z�u�̏����ݒ�
	m_pos = pos;			// �ʒu

	// �^�[�Q�b�g�I�u�W�F�N�g�̐ݒ�
	pTarget->SetPos(m_pos);

	// �U��q�I�u�W�F�N�g�̐ݒ�
	pPendulum->SetPos(m_pos);
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CPendulum::SetRot(const D3DXVECTOR3 &rot)
{
	// �z�u�̏����ݒ�
	m_rot = rot;				// ����

	// �^�[�Q�b�g�I�u�W�F�N�g�̐ݒ�
	pTarget->SetPos(m_rot);

	// �U��q�I�u�W�F�N�g�̐ݒ�
	pPendulum->SetPos(m_rot);
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CPendulum::SetSize(const D3DXVECTOR3 & size)
{
	// �z�u�̏����ݒ�
	m_size = size;				// �T�C�Y

	// �^�[�Q�b�g�I�u�W�F�N�g�̐ݒ�
	pTarget->SetSize(m_size);

	// �U��q�I�u�W�F�N�g�̐ݒ�
	pPendulum->SetSize(m_size);
}