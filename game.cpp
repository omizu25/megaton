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
#include "gauge2D.h"
#include "pendulum.h"
#include "twin_circle.h"
#include "bg.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const int CGame::MAX_TIME = 4500;
const int CGame::PAUSE_TIME = 100;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CGame::CGame() : CMode(CMode::MODE_GAME),
	m_pTime(nullptr),
	m_pScore(nullptr),
	m_pBestScore(nullptr),
	m_time(0),
	m_nGageWave(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CGame::~CGame()
{
	assert(m_pTime == nullptr);
	assert(m_pScore == nullptr);
	assert(m_pBestScore == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CGame::Init()
{
	m_time = 0;

	{// �w�i
		CBG::Create(CTexture::LABEL_GameBg);
	}

	{// �^�C��
		float width = (float)CApplication::SCREEN_WIDTH * 0.5f + (CTime::STD_WIDTH * 2.25f);
		float height = CTime::STD_HEIGHT * 0.5f + 15.0f;

		// �^�C���̐���
		m_pTime = CTime::Create(D3DXVECTOR3(width, height, 0.0f), timeGetTime(), MAX_TIME);
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

	{// �Q�[�W
		/*m_pGauge = CGauge2D::Create();
		m_pGauge->SetPos(D3DXVECTOR3(640.0f, 500.0f, 0.0f));
		m_pGauge->SetSize(D3DXVECTOR3(50.0f, 300.0f, 0.0f));
		m_pGauge->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pGauge->SetMaxNumber(100.0f);
		m_pGauge->SetCoefficient(1.0f);

		CPendulum *pPendulum = CPendulum::Create();*/
		CTwinCircle *pTwinCircle = CTwinCircle::Create();
	}

	// BGM
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_BGM_Game);

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Start);
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

	if (m_pTime != nullptr)
	{// null�`�F�b�N
		m_pTime->Uninit();
		delete m_pTime;
		m_pTime = nullptr;
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
	// �G�t�F�N�g
	Effect();

	// �^�C���̌��Z
	m_pTime->Update();

	//{// �Q�[�W�̍X�V
	//	// �T�C�Y�̍X�V
	//	m_nGageWave++;
	//	if (m_nGageWave >= 100)
	//	{
	//		m_nGageWave = 0;
	//	}
	//	m_pGauge->SetNumber((float)m_nGageWave);
	//}

	// �X�V
	CObject::UpdateAll();

	// �G�̓����蔻��
	CEnemy::Collision();

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
// ���Z�b�g
//--------------------------------------------------
void CGame::Reset()
{
	// �G�̑S�Ẳ��
	CObject3D::ReleaseAll(CObject3D::TYPE_ENEMY);

	// �e�̑S�Ẳ��
	CObject3D::ReleaseAll(CObject3D::TYPE_BULLET);

	// EXP�̑S�Ẳ��
	CObject3D::ReleaseAll(CObject3D::TYPE_EXP);

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Start);
}

//--------------------------------------------------
// �X�R�A�̎擾
//--------------------------------------------------
CScore* CGame::GetScore()
{
	return m_pScore;
}

//--------------------------------------------------
// �^�C���̎擾
//--------------------------------------------------
CTime* CGame::GetTime()
{
	return m_pTime;
}

//--------------------------------------------------
// �G�t�F�N�g
//--------------------------------------------------
void CGame::Effect()
{
	m_time++;

	if ((m_time % 30) != 0)
	{// ���Ԋu�҂�
		return;
	}

	// �w�i
	CEffectManager::GetInstanse()->BG();
}
