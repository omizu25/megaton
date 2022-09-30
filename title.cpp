//**************************************************
// 
// title.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "title.h"
#include "application.h"
#include "camera.h"
#include "object2D.h"
#include "effect_manager.h"
#include "utility.h"
#include "menu.h"
#include "sound.h"
#include "game.h"
#include "bg.h"
#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTitle::CTitle() : CMode(CMode::MODE_TITLE),
	m_pMenu(nullptr),
	m_time(0),
	m_partCnt(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTitle::~CTitle()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CTitle::Init()
{
	m_time = 0;
	m_partCnt = 0;

	{// �w�i
		CBG::Create(CTexture::LABEL_NightSky);
	}

	CObject2D* pTitle = CObject2D::Create();
	pTitle->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.3f, 0.0f));
	pTitle->SetSize(D3DXVECTOR3(1000.0f, 375.0f, 0.0f));
	pTitle->SetTexture(CTexture::LABEL_TitleLogo);
	pTitle->SetFade(0.0f);

	{// ���j���[
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.75f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(600.0f, 150.0f, 0.0f);

		// ���j���[�̐���
		m_pMenu = CMenu::Create(pos, size, 1, 0.0f, true, false);

		// �e�N�X�`���̐ݒ�
		m_pMenu->SetTexture(0, CTexture::LABEL_PressEnter);
	}

	// BGM
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_BGM_Title);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CTitle::Uninit()
{
	if (m_pMenu != nullptr)
	{// null�`�F�b�N
		m_pMenu->Uninit();
		delete m_pMenu;
		m_pMenu = nullptr;
	}

	// �S�Ẳ��
	CObject::ReleaseAll(false);

	CApplication* pApp = CApplication::GetInstanse();

	// �e�N�X�`���̔j��
	pApp->GetTexture()->ReleaseAll();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CTitle::Update()
{
	// �X�V
	CObject::UpdateAll();

	// �G�t�F�N�g
	Effect();

	// �I��
	int select = m_pMenu->Select();

	if (m_time >= CMode::FADE_TIME)
	{// �t�F�[�h����
		if (select != -1)
		{
			Change(MODE_GAME);
		}
	}

	// �J�����̍X�V
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CTitle::Draw()
{
	// �J�����̐ݒ�
	CApplication::GetInstanse()->GetCamera()->Set();

	// �`��
	CObject::DrawAll();
}

//--------------------------------------------------
// �G�t�F�N�g
//--------------------------------------------------
void CTitle::Effect()
{
	m_time++;

	if ((m_time % 30) != 0)
	{// ���Ԋu�҂�
		return;
	}

	// �p�[�e�B�N��
	CEffectManager::GetInstanse()->Particle();
}
