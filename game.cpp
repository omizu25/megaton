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

#include <assert.h>

//==================================================
// ��`
//==================================================

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CGame::CGame() : CMode(CMode::MODE_GAME),
	m_pScore(nullptr),
	m_pBestScore(nullptr),
	m_time(0),
	m_end(false)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CGame::~CGame()
{
	assert(m_pScore == nullptr);
	assert(m_pBestScore == nullptr);
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

	{// �X�R�A
		D3DXVECTOR3 size = D3DXVECTOR3(CScore::STD_WIDTH, CScore::STD_HEIGHT, 0.0f);
		float width = (float)CApplication::SCREEN_WIDTH;
		float height = CScore::STD_HEIGHT * 0.5f + 10.0f;

		// �X�R�A�̐���
		m_pScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);
	}
	
	{// �x�X�g�X�R�A
		D3DXVECTOR3 size = D3DXVECTOR3(CScore::STD_WIDTH, CScore::STD_HEIGHT, 0.0f);
		int score = CRankingUI::Get(0);

		float width = (size.x * Digit(score)) + (((Digit(score) - 1) / 3) * (size.x * 0.5f));
		float height = size.y * 0.5f + 10.0f;

		// �x�X�g�X�R�A�̐���
		m_pBestScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);

		// �X�R�A�̐ݒ�
		m_pBestScore->Set(score);
	}

	{// �Q�[�W�}�l�[�W���[
		m_pGageManager = CGageManager::Create();
	}

	// BGM
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_BGM_Game);

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Enter);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CGame::Uninit()
{	
	// �����L���O�̐ݒ�
	CRankingUI::Set(m_pScore->Get());

	if (m_pBestScore != nullptr)
	{// null�`�F�b�N
		m_pBestScore->Uninit();
		delete m_pBestScore;
		m_pBestScore = nullptr;
	}

	if (m_pScore != nullptr)
	{// null�`�F�b�N
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = nullptr;
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
CScore* CGame::GetScore()
{
	return m_pScore;
}

//--------------------------------------------------
// �X�R�A�̎擾
//--------------------------------------------------
void CGame::EndGame()
{
	m_end = true;
}
