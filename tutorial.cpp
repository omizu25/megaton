//**************************************************
// 
// tutorial.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "tutorial.h"
#include "application.h"
#include "camera.h"
#include "input.h"
#include "object2D.h"
#include "effect_manager.h"
#include "utility.h"
#include "game.h"
#include "sound.h"
#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTutorial::CTutorial() : CMode(CMode::MODE_TUTORIAL),
	m_time(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTutorial::~CTutorial()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CTutorial::Init()
{
	m_time = 0;
	
	CObject2D* pTutorial = CObject2D::Create();
	pTutorial->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f));
	pTutorial->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));
	pTutorial->SetTexture(CTexture::LABEL_Tutorial);
	pTutorial->SetFade(0.0f);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CTutorial::Uninit()
{
	// �S�Ẳ��
	CObject::ReleaseAll(false);

	CApplication* pApp = CApplication::GetInstanse();

	// �e�N�X�`���̔j��
	pApp->GetTexture()->ReleaseAll();

	// ��~
	CApplication::GetInstanse()->GetSound()->Stop(CSound::LABEL_BGM_Title);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CTutorial::Update()
{
	// �X�V
	CObject::UpdateAll();

	// �G�t�F�N�g
	Effect();

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// ����L�[�������ꂽ
		if (m_time >= CMode::FADE_TIME)
		{// �t�F�[�h����
			Change(MODE_GAME);

			// SE
			CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Enter);
			return;
		}
	}

	// �J�����̍X�V
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CTutorial::Draw()
{
	// �J�����̐ݒ�
	CApplication::GetInstanse()->GetCamera()->Set();

	// �`��
	CObject::DrawAll();
}

//--------------------------------------------------
// �G�t�F�N�g
//--------------------------------------------------
void CTutorial::Effect()
{
	m_time++;

	if ((m_time % 30) != 0)
	{// ���Ԋu�҂�
		return;
	}

	// �w�i
	CEffectManager::GetInstanse()->BG();
}
