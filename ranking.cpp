//**************************************************
// 
// ranking.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "ranking.h"
#include "application.h"
#include "camera.h"
#include "effect_manager.h"
#include "utility.h"
#include "rankingUI.h"
#include "menu.h"
#include "object2D.h"
#include "bg.h"
#include "score.h"
#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CRanking::CRanking() : CMode(CMode::MODE_RANKING),
	m_pRanking(nullptr),
	m_pMenu(nullptr),
	m_time(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CRanking::~CRanking()
{
	assert(m_pRanking == nullptr);
	assert(m_pMenu == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CRanking::Init()
{
	m_time = 0;

	{// �w�i
		CBG::Create(CTexture::LABEL_NightSky);
	}

	{// �����L���O�̔w�i
		float width = (float)CApplication::SCREEN_WIDTH * 0.75f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.5f - 15.0f;

		// �����L���O�̔w�i�̐���
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(600.0f, 650.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_NONE);
		pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		pObj->SetFade(0.0f);
	}

	{// �X�R�A�̔w�i
		float width = (float)CApplication::SCREEN_WIDTH * 0.25f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.25f - 10.0f;

		// �X�R�A�̔w�i�̐���
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(620.0f, 300.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_NONE);
		pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		pObj->SetFade(0.0f);
	}

	{// �����L���O
		float width = (float)CApplication::SCREEN_WIDTH - 35.0f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

		// �����L���O�̐���
		m_pRanking = CRankingUI::Create(D3DXVECTOR3(width, height, 0.0f), 40.0f);
	}

	{// �����L���O�̕�����
		float width = (float)CApplication::SCREEN_WIDTH * 0.75f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.15f;

		// ������̐���
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(480.0f, 150.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_Ranking);
		pObj->SetFade(0.0f);
	}

	{// ����̃X�R�A
		D3DXVECTOR3 size = D3DXVECTOR3(CRankingUI::STD_WIDTH * 1.3f, CRankingUI::STD_HEIGHT * 1.3f, 0.0f);
		int score = CRankingUI::Get(-1);
		int digit = Digit(score);
		float center = (digit * (size.x * 0.5f)) + (((digit - 1) / 3) * (size.x * 0.25f));
		float width = (float)CApplication::SCREEN_WIDTH * 0.25f + center;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

		// �X�R�A�̐���
		m_pScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);

		// �X�R�A�̐ݒ�
		m_pScore->Set(score);
	}

	{// ����̃X�R�A�̕�����
		float width = (float)CApplication::SCREEN_WIDTH * 0.25f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.15f - 12.5f;

		// ������̐���
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(350.0f, 150.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_Score);
		pObj->SetFade(0.0f);
	}

	{// ���j���[
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.3f, (float)CApplication::SCREEN_HEIGHT * 0.75f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(350.0f, 120.0f, 0.0f);

		// ���j���[�̐���
		m_pMenu = CMenu::Create(pos, size, ESelect::SELECT_MAX, 40.0f, true, true);

		// �e�N�X�`���̐ݒ�
		m_pMenu->SetTexture(ESelect::SELECT_RETRY, CTexture::LABEL_Retry);
		m_pMenu->SetTexture(ESelect::SELECT_END, CTexture::LABEL_End);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CRanking::Uninit()
{
	if (m_pRanking != nullptr)
	{// null�`�F�b�N
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = nullptr;
	}

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
void CRanking::Update()
{
	// �X�V
	CObject::UpdateAll();

	// �G�t�F�N�g
	Effect();

	// �����L���O�̍X�V
	m_pRanking->Update();

	// �I��
	ESelect select = (ESelect)m_pMenu->Select();

	if (m_time >= CMode::FADE_TIME)
	{// �t�F�[�h����
		switch (select)
		{
		case ESelect::SELECT_NONE:
			break;

		case ESelect::SELECT_RETRY:
			Change(CMode::MODE_GAME);
			return;
			break;

		case ESelect::SELECT_END:
			Change(CMode::MODE_TITLE);
			return;
			break;

		case ESelect::SELECT_MAX:
		default:
			assert(false);
			break;
		}
	}

	float width = (float)CApplication::SCREEN_WIDTH - 35.0f;
	float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

	// ���Z�b�g
	m_pRanking->Reset(D3DXVECTOR3(width, height, 0.0f), 40.0f, false);

	// �J�����̍X�V
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CRanking::Draw()
{
	// �J�����̐ݒ�
	CApplication::GetInstanse()->GetCamera()->Set();

	// �`��
	CObject::DrawAll();
}

//--------------------------------------------------
// �G�t�F�N�g
//--------------------------------------------------
void CRanking::Effect()
{
	m_time++;

	if ((m_time % 13) != 0)
	{// ���Ԋu�҂�
		return;
	}

	// �p�[�e�B�N��
	CEffectManager::GetInstanse()->Particle();
}
