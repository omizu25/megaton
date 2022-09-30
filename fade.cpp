//=============================================================================
//
// �t�F�[�h�N���X(fade.cpp)
// Author : �������l
// �T�v : �t�F�[�h�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "fade.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�o���b�g�𐶐�����
//=============================================================================
CFade *CFade::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CFade *pFade = nullptr;

	pFade = new CFade;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pFade != nullptr);

	// ���l�̏�����
	pFade->Init();

	// �C���X�^���X��Ԃ�
	return pFade;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CFade::CFade(CObject::ECategory cat) : CObject2D(cat)
{
	m_fadeMode = FADE_NONE;				// �t�F�[�h���[�h
	m_mode = CMode::MODE_NONE;			// �V�[�����[�h				
	m_fAlpha = 0.0f;					// �A���t�@�l
	m_nFadeFrame = 0;					// �t�F�[�h�����܂ł̎���
	m_bFade = false;					// �t�F�[�h���s���Ă��邩�ǂ���
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : �e�N�X�`���̐ݒ肵�A�����o�ϐ��̏����l��ݒ�
//=============================================================================
void CFade::Init()
{
	// �I�u�W�F�N�g2D�̏�����
	CObject2D::Init();

	// �t�F�[�h�����܂ł̎���
	m_nFadeFrame = 60;					
	m_bFade = false;

	// ���_�o�b�t�@�̐ݒ�
	SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	SetSize(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CFade::Uninit()
{// �I�u�W�F�N�g2D�̏I��
	CObject2D::Uninit();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CFade::Update()
{
	switch (m_fadeMode)
	{
	case CFade::FADE_NONE:
		break;

	case CFade::FADE_IN:
		FadeIn();
		break;

	case CFade::FADE_OUT:
		FadeOut();
		break;

	default:
		assert(false);
		break;
	}

	// �I�u�W�F�N�g2D�̍X�V
	CObject2D::Update();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CFade::Draw()
{// �v���C���[2D�̕`��
	CObject2D::Draw();
}

//=============================================================================
// �t�F�[�h���[�h�̐ݒ�
// Author : �������l
// �T�v : �t�F�[�h���[�h�̐ݒ���s��
//=============================================================================
void CFade::SetFade(CMode::EMode mode)
{
	if (m_fadeMode == FADE_NONE)
	{
		m_bFade = true;
		m_fadeMode = FADE_IN;
		m_fAlpha = 0.0f;
		m_mode = mode;
	}	
}

//=============================================================================
// �t�F�[�h�C��
// Author : �������l
// �T�v : �t�F�[�h���s��
//=============================================================================
void CFade::FadeIn()
{
	CMode *pMode = CApplication::GetInstanse()->GetMode();

	m_fAlpha += 1.0f / m_nFadeFrame;

	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fAlpha));

	if (m_fAlpha >= 1.0f)
	{
		m_fAlpha = 1.0f;
		pMode->Change(m_mode);
		m_fadeMode = FADE_OUT;
	}
}

//=============================================================================
// �t�F�[�h�A�E�g
// Author : �������l
// �T�v : �t�F�[�h���s��
//=============================================================================
void CFade::FadeOut()
{
	m_fAlpha -= 1.0f / m_nFadeFrame;

	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fAlpha));

	if (m_fAlpha <= 0.0f)
	{
		m_fAlpha = 0.0f;
		m_fadeMode = FADE_NONE;
		m_bFade = false;
	}
}