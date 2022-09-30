//**************************************************
// 
// pause.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "pause.h"
#include "menu.h"
#include "object2D.h"
#include "application.h"
#include "game.h"
#include "time.h"
#include "input.h"
#include "sound.h"
#include <assert.h>

//--------------------------------------------------
// ����
//--------------------------------------------------
CPause* CPause::Create()
{
	CPause* pPause = nullptr;

	pPause = new CPause;

	if (pPause != nullptr)
	{// null�`�F�b�N
		pPause->Init();
	}

	return pPause;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CPause::CPause() :
	m_pPause(nullptr),
	m_pMenu(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CPause::~CPause()
{
	assert(m_pPause == nullptr);
	assert(m_pMenu == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CPause::Init()
{
	{// ���j���[
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.65f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(350.0f, 100.0f, 0.0f);

		// ���j���[�̐���
		m_pMenu = CMenu::Create(pos, size, ESelect::SELECT_MAX, 40.0f, true, true);

		// �e�N�X�`���̐ݒ�
		m_pMenu->SetTexture(ESelect::SELECT_RESUME, CTexture::LABEL_Resume);
		m_pMenu->SetTexture(ESelect::SELECT_RESTART, CTexture::LABEL_Restart);
		m_pMenu->SetTexture(ESelect::SELECT_END, CTexture::LABEL_End);
	}

	{// �|�[�Y
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.25f, 0.0f);

		// �|�[�Y�̐���
		m_pPause = CObject2D::Create();

		// �ʒu�̐ݒ�
		m_pPause->SetPos(pos);

		// �T�C�Y�̐ݒ�
		m_pPause->SetSize(D3DXVECTOR3(500.0f, 150.0f, 0.0f));

		// �e�N�X�`���̐ݒ�
		m_pPause->SetTexture(CTexture::LABEL_Pause);

		// �t�F�[�h�̐ݒ�
		m_pPause->SetFade(0.0f);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CPause::Uninit()
{
	if (m_pMenu != nullptr)
	{// null�`�F�b�N
		m_pMenu->Uninit();
		delete m_pMenu;
		m_pMenu = nullptr;
	}

	if (m_pPause != nullptr)
	{// null�`�F�b�N
		m_pPause->Uninit();
		m_pPause = nullptr;
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CPause::Release()
{
	if (m_pMenu != nullptr)
	{// null�`�F�b�N
		m_pMenu->Release();
		delete m_pMenu;
		m_pMenu = nullptr;
	}

	if (m_pPause != nullptr)
	{// null�`�F�b�N
		m_pPause->Release();
		m_pPause = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
bool CPause::Update()
{
	// �X�V
	m_pMenu->Update();

	// �X�V
	m_pPause->Update();

	// �I��
	ESelect select = (ESelect)m_pMenu->Select();

	if (CInput::GetKey()->Trigger(CInput::KEY_PAUSE))
	{// P�L�[�������ꂽ
		// �^�C���̍ĊJ
		CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
		pGame->GetTime()->Restart();

		// SE
		CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Enter);
		return false;
	}

	switch (select)
	{
	case ESelect::SELECT_NONE:
		return true;	// �|�[�Y��
		break;

	case ESelect::SELECT_RESUME:
	{
		// �^�C���̍ĊJ
		CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
		pGame->GetTime()->Restart();
	}
		break;

	case ESelect::SELECT_RESTART:
		// ���[�h�̕ύX
		CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_GAME);
		break;

	case ESelect::SELECT_END:
		// ���[�h�̕ύX
		CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_TITLE);
		break;

	case ESelect::SELECT_MAX:
	default:
		assert(false);
		break;
	}

	return false;
}
