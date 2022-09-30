//**************************************************
// 
// result.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "result.h"
#include "application.h"
#include "camera.h"
#include "object2D.h"
#include "effect_manager.h"
#include "utility.h"
#include "rankingUI.h"
#include "score.h"
#include "menu.h"
#include "sound.h"
#include "bg.h"
#include "fade.h"
#include "locus.h"
#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CResult::CResult() : CMode(CMode::MODE_RESULT),
	m_time(0),
	m_fireworks(false)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CResult::Init()
{
	m_time = 0;
	m_fireworks = false;

	{// �w�i
		CBG::Create(CTexture::LABEL_NightSky);
	}

	CLocus *pLocus = CLocus::Create();
	pLocus->SetPos(D3DXVECTOR3(-50.0f, -550.0f, 0.0f));
	pLocus->SetLife(35);	pLocus->SetSpeed(15.0f);
	pLocus->SetWaveSpeed(0.4f);
	pLocus->SetWaveWidth(15.0f);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CResult::Uninit()
{
	// �S�Ẳ��
	CApplication::GetInstanse()->GetSound()->Stop();

	CObject::ReleaseAll(false);

	CApplication* pApp = CApplication::GetInstanse();

	// �e�N�X�`���̔j��
	pApp->GetTexture()->ReleaseAll();

	// ��~
	pApp->GetSound()->Stop();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CResult::Update()
{
	// �X�V
	CObject::UpdateAll();

	m_time++;
	if (m_time == 1)
	{
		CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Explosion_Short);
	}
	
	if (m_time >= 240)
	{// �t�F�[�h����


		CApplication::GetInstanse()->GetFade()->SetFade(CMode::MODE_RANKING);
	}

	if (!m_fireworks)
	{
		if (m_time >= 60)
		{
			float move = 1.0f;
			int score = CRankingUI::Get(-1);

			move += (float)(score / 10);

			CEffectManager::GetInstanse()->Fireworks(move);
			m_fireworks = true;
		}

	}

	// �J�����̍X�V
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CResult::Draw()
{
	// �J�����̐ݒ�
	CApplication::GetInstanse()->GetCamera()->Set();

	// �`��
	CObject::DrawAll();
}
