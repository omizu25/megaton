//**************************************************
// 
// game.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
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
// 定義
//==================================================

//--------------------------------------------------
// デフォルトコンストラクタ
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
// デストラクタ
//--------------------------------------------------
CGame::~CGame()
{
	for (int i = 0; i < CGageManager::MAX_GAGETYPE; i++)
	{
		m_pScore[i] = nullptr;
	}
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CGame::Init()
{
	m_time = 0;
	m_end = false;

	{// 背景
		CBG::Create(CTexture::LABEL_GameBg);
	}

	{// ゲージ枠
		D3DXVECTOR3 pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(60.0f, 410.0f, 0.0f);			// 大きさ
		CGauge2D* m_pGauge2D = CGauge2D::Create();
		m_pGauge2D->SetPos(D3DXVECTOR3(pos.x, pos.y + size.y / 4.1f, 0.0f));
		m_pGauge2D->SetChange(false, size);
	}

	{// ゲージ背景
		D3DXVECTOR3 pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(50.0f, 400.0f, 0.0f);			// 大きさ
		CGauge2D* m_pGauge2D = CGauge2D::Create();
		m_pGauge2D->SetPos(D3DXVECTOR3(pos.x, pos.y + size.y / 4.0f, 0.0f));
		m_pGauge2D->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_pGauge2D->SetChange(false, size);
	}

	D3DXVECTOR3 size = D3DXVECTOR3(CScore::STD_WIDTH, CScore::STD_HEIGHT, 0.0f);
	float width = (float)CApplication::SCREEN_WIDTH * 0.9f;
	float height = 0.0f;

	for (int i = 0; i < CGageManager::MAX_GAGETYPE; i++)
	{// スコア
		height = (float)CApplication::SCREEN_HEIGHT * 0.35f + (150.0f * i);

		// スコアの生成
		m_pScore[i] = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);
	}

	{// ゲージマネージャー
		m_pGageManager = CGageManager::Create();
	}

	// BGM
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_BGM_Game);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
	int score = 0;

	for (int i = 0; i < CGageManager::MAX_GAGETYPE; i++)
	{
		score += m_pScore[i]->Get();
	}

	
	// ランキングの設定
	CRankingUI::Set(score);

	for (int i = 0; i < CGageManager::MAX_GAGETYPE; i++)
	{
		if (m_pScore[i] != nullptr)
		{// nullチェック
			m_pScore[i]->Uninit();
			delete m_pScore[i];
			m_pScore[i] = nullptr;
		}
	}

	// 全ての解放
	CObject::ReleaseAll(false);

	// 停止
	CApplication::GetInstanse()->GetSound()->Stop(CSound::LABEL_BGM_Game);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	// 更新
	CObject::UpdateAll();

	if (m_end)
	{
		m_time++;

		if (m_time >= 120)
		{
			Change(MODE_RESULT);
		}
	}

	// カメラの更新
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CGame::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}

//--------------------------------------------------
// スコアの取得
//--------------------------------------------------
CScore* CGame::GetScore(CGageManager::GAGE_TYPE type)
{
	return m_pScore[type];
}

//--------------------------------------------------
// スコアの取得
//--------------------------------------------------
void CGame::EndGame()
{
	m_end = true;
}
