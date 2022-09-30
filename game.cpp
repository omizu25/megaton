//**************************************************
// 
// game.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "game.h"
#include "application.h"
#include "camera.h"
#include "number_manager.h"
#include "time.h"
#include "score.h"
#include "effect_manager.h"
#include "input.h"
#include "rankingUI.h"
#include "utility.h"
#include "pause.h"
#include "object2D.h"
#include "sound.h"
#include "enemy.h"
#include "gage_manager.h"
#include "bg.h"
#include "gauge2D.h"

#include <assert.h>

//==================================================
// ��`
//==================================================

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CGame::CGame() : CMode(CMode::MODE_GAME),
	m_time(0),
	m_end(false)
{
	for (int i = 0; i < CGageManager::MAX_GAGETYPE; i++)
	{
		m_pScore[i] = nullptr;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CGame::~CGame()
{
	for (int i = 0; i < CGageManager::MAX_GAGETYPE; i++)
	{
		m_pScore[i] = nullptr;
	}
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CGame::Init()
{
	m_time = 0;
	m_end = false;

	{// �w�i
		CBG::Create(CTexture::LABEL_GameBg);
	}

	{// �Q�[�W�g
		D3DXVECTOR3 pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(60.0f, 410.0f, 0.0f);			// �傫��
		CGauge2D* m_pGauge2D = CGauge2D::Create();
		m_pGauge2D->SetPos(D3DXVECTOR3(pos.x, pos.y + size.y / 4.1f, 0.0f));
		m_pGauge2D->SetChange(false, size);
	}

	{// �Q�[�W�w�i
		D3DXVECTOR3 pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(50.0f, 400.0f, 0.0f);			// �傫��
		CGauge2D* m_pGauge2D = CGauge2D::Create();
		m_pGauge2D->SetPos(D3DXVECTOR3(pos.x, pos.y + size.y / 4.0f, 0.0f));
		m_pGauge2D->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_pGauge2D->SetChange(false, size);
	}

	D3DXVECTOR3 size = D3DXVECTOR3(CScore::STD_WIDTH, CScore::STD_HEIGHT, 0.0f);
	float width = (float)CApplication::SCREEN_WIDTH * 0.9f;
	float height = 0.0f;

	for (int i = 0; i < CGageManager::MAX_GAGETYPE; i++)
	{// �X�R�A
		height = (float)CApplication::SCREEN_HEIGHT * 0.35f + (150.0f * i);

		// �X�R�A�̐���
		m_pScore[i] = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);
	}

	{// �Q�[�W�}�l�[�W���[
		m_pGageManager = CGageManager::Create();
	}

	// BGM
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_BGM_Game);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CGame::Uninit()
{
	int score = 0;

	for (int i = 0; i < CGageManager::MAX_GAGETYPE; i++)
	{
		score += m_pScore[i]->Get();
	}

	
	// �����L���O�̐ݒ�
	CRankingUI::Set(score);

	for (int i = 0; i < CGageManager::MAX_GAGETYPE; i++)
	{
		if (m_pScore[i] != nullptr)
		{// null�`�F�b�N
			m_pScore[i]->Uninit();
			delete m_pScore[i];
			m_pScore[i] = nullptr;
		}
	}

	// �S�Ẳ��
	CObject::ReleaseAll(false);

	// ��~
	CApplication::GetInstanse()->GetSound()->Stop(CSound::LABEL_BGM_Game);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CGame::Update()
{
	// �X�V
	CObject::UpdateAll();

	if (m_end)
	{
		m_time++;

		if (m_time >= 120)
		{
			Change(MODE_RESULT);
		}
	}

	// �J�����̍X�V
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CGame::Draw()
{
	// �J�����̐ݒ�
	CApplication::GetInstanse()->GetCamera()->Set();

	// �`��
	CObject::DrawAll();
}

//--------------------------------------------------
// �X�R�A�̎擾
//--------------------------------------------------
CScore* CGame::GetScore(CGageManager::GAGE_TYPE type)
{
	return m_pScore[type];
}

//--------------------------------------------------
// �X�R�A�̎擾
//--------------------------------------------------
void CGame::EndGame()
{
	m_end = true;
}
