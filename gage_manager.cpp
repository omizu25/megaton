//=============================================================================
//
// �Q�[�W�}�l�[�W���[�N���X(gage_manager.cpp)
// Author : �������l
// �T�v : �Q�[�W�}�l�[�W���[�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <math.h>

#include "gage_manager.h"
#include "gauge2D.h"
#include "pendulum.h"
#include "twin_circle.h"
#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "mode.h"
#include "game.h"
#include "score.h"
#include "input.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�Q�[�W�𐶐�����
//=============================================================================
CGageManager * CGageManager::Create(void)
{
	// �I�u�W�F�N�g�C���X�^���X
	CGageManager *pGageManager = nullptr;

	// �������̉��
	pGageManager = new CGageManager;

	if (pGageManager != nullptr)
	{// ���l�̏�����
		pGageManager->Init();
	}
	else
	{// �������̊m�ۂ��ł��Ȃ�����
		assert(false);
	}

	// �C���X�^���X��Ԃ�
	return pGageManager;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CGageManager::CGageManager(CObject::ECategory cat) : CObject(cat)
{
	m_pGauge2D = nullptr;						// �^�[�Q�b�g
	m_pPendulum = nullptr;						// �U��q
	m_pTwinCircle = nullptr;					// �T�[�N��
	m_pos = D3DXVECTOR3(0.0f, 0.f, 0.0f);		// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.f, 0.0f);		// ����
	m_size = D3DXVECTOR3(0.0f, 0.f, 0.0f);		// �傫��
	m_nScore = 0;								// �X�R�A
	m_nCntGage = 0;								// �Q�[�W�̃J�E���g
	m_bKeyPress = false;						// �{�^������������
	m_end = false;
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CGageManager::~CGageManager()
{

}

//=============================================================================
// �|���S���̏�����
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
void CGageManager::Init()
{
	// �z�u�̏����ݒ�
	m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);			// �傫��

	// �Q�[�W
	m_pGauge2D = CGauge2D::Create();
	m_pGauge2D->SetSize(D3DXVECTOR3(50.0f, 200.0f, 0.0f));
	m_pGauge2D->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y / 2.0f, 0.0f));
	m_pGauge2D->SetMaxNumber(100.0f);
	m_pGauge2D->SetCoefficient(1.0f);

	m_end = false;
}

//=============================================================================
// �|���S���̏I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CGageManager::Uninit()
{

}

//=============================================================================
// �|���S���̍X�V
// Author : �������l
// �T�v : 2D�|���S���̍X�V���s��
//=============================================================================
void CGageManager::Update()
{
	CInput* pInput = CInput::GetKey();

	m_bKeyPress = pInput->Trigger(CInput::KEY_DECISION);

	switch (m_type)
	{
	case CGageManager::GAGE_POLE:
		{// �Q�[�W�̍X�V
			// �T�C�Y�̍X�V
			m_nCntGage++;
			m_pGauge2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			if (m_nCntGage >= 95)
			{
				m_pGauge2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			}
			if (m_nCntGage > 100)
			{
				m_nCntGage = 0;
			}
			m_pGauge2D->SetNumber((float)m_nCntGage);
		}

		if (m_bKeyPress)
		{
			m_bKeyPress = false;
			m_nScore += m_nCntGage;
			CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();

			// �X�R�A�̉��Z
			pGame->GetScore(GAGE_POLE)->Set(m_pGauge2D->GetNumber());

			m_pGauge2D->Release();

			m_pPendulum = CPendulum::Create();
			m_type = GAGE_PENDULUM;
		}
		break;

	case CGageManager::GAGE_PENDULUM:
		if (m_bKeyPress)
		{
			m_bKeyPress = false;
			m_nScore += m_pPendulum->GetScore();

			CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();

			// �X�R�A�̉��Z
			pGame->GetScore(GAGE_PENDULUM)->Set(m_pPendulum->GetScore());
			m_pPendulum->Release();

			m_pTwinCircle = CTwinCircle::Create();
			m_type = GAGE_TWINCIRCLE;

		}
		break;

	case CGageManager::GAGE_TWINCIRCLE:
		if (m_bKeyPress)
		{
			m_bKeyPress = false;
			m_nScore += m_pTwinCircle->GetScore();
			CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();

			// �X�R�A�̉��Z
			pGame->GetScore(GAGE_PENDULUM)->Set(m_pTwinCircle->GetScore());

			m_pTwinCircle->Release();

			m_type = MAX_GAGETYPE;
		}
		break;

	case CGageManager::MAX_GAGETYPE:
	
		if (!m_end)
		{
			m_end = true;
			// ���[�h�̕ύX
			CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
			pGame->EndGame();
		}
	
		break;

	default:
		assert(false);
		break;
	}
}

//=============================================================================
// �|���S���̕`��
// Author : �������l
// �T�v : 2D�|���S���̕`����s��
//=============================================================================
void CGageManager::Draw()
{

}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CGageManager::SetPos(const D3DXVECTOR3 &pos)
{
	// �z�u�̏����ݒ�
	m_pos = pos;			// �ʒu
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CGageManager::SetRot(const D3DXVECTOR3 &rot)
{
	// �z�u�̏����ݒ�
	m_rot = rot;				// ����
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CGageManager::SetSize(const D3DXVECTOR3 & size)
{
	// �z�u�̏����ݒ�
	m_size = size;				// �T�C�Y
}