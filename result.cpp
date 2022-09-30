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
	m_time(0)
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

	{// �w�i
		CBG::Create(CTexture::LABEL_NightSky);
	}

	CLocus *pLocus = CLocus::Create();
	pLocus->SetPos(D3DXVECTOR3(0.0f, -500.0f, 0.0f));
	pLocus->SetLife(40);
	pLocus->SetSpeed(15.0f);
	pLocus->SetWaveSpeed(0.4f);
	pLocus->SetWaveWidth(15.0f);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CResult::Uninit()
{
	// �S�Ẳ��
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

	if (m_time >= 240)
	{// �t�F�[�h����
		CApplication::GetInstanse()->GetFade()->SetFade(CMode::MODE_RANKING);
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
