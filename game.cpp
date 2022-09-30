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
#include "gauge2D.h"
#include "pendulum.h"
#include "twin_circle.h"
#include "bg.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const int CGame::MAX_TIME = 4500;
const int CGame::PAUSE_TIME = 100;

//--------------------------------------------------
// デフォルトコンストラクタ
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
// デストラクタ
//--------------------------------------------------
CGame::~CGame()
{
	assert(m_pTime == nullptr);
	assert(m_pScore == nullptr);
	assert(m_pBestScore == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CGame::Init()
{
	m_time = 0;

	{// 背景
		CBG::Create(CTexture::LABEL_GameBg);
	}

	{// タイム
		float width = (float)CApplication::SCREEN_WIDTH * 0.5f + (CTime::STD_WIDTH * 2.25f);
		float height = CTime::STD_HEIGHT * 0.5f + 15.0f;

		// タイムの生成
		m_pTime = CTime::Create(D3DXVECTOR3(width, height, 0.0f), timeGetTime(), MAX_TIME);
	}

	{// スコア
		D3DXVECTOR3 size = D3DXVECTOR3(CScore::STD_WIDTH, CScore::STD_HEIGHT, 0.0f);
		float width = (float)CApplication::SCREEN_WIDTH;
		float height = CScore::STD_HEIGHT * 0.5f + 10.0f;

		// スコアの生成
		m_pScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);
	}
	
	{// ベストスコア
		D3DXVECTOR3 size = D3DXVECTOR3(CScore::STD_WIDTH, CScore::STD_HEIGHT, 0.0f);
		int score = CRankingUI::Get(0);

		float width = (size.x * Digit(score)) + (((Digit(score) - 1) / 3) * (size.x * 0.5f));
		float height = size.y * 0.5f + 10.0f;

		// ベストスコアの生成
		m_pBestScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);

		// スコアの設定
		m_pBestScore->Set(score);
	}

	{// ゲージ
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
// 終了
//--------------------------------------------------
void CGame::Uninit()
{	
	// ランキングの設定
	CRankingUI::Set(m_pScore->Get());

	if (m_pBestScore != nullptr)
	{// nullチェック
		m_pBestScore->Uninit();
		delete m_pBestScore;
		m_pBestScore = nullptr;
	}

	if (m_pScore != nullptr)
	{// nullチェック
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = nullptr;
	}

	if (m_pTime != nullptr)
	{// nullチェック
		m_pTime->Uninit();
		delete m_pTime;
		m_pTime = nullptr;
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
	// エフェクト
	Effect();

	// タイムの減算
	m_pTime->Update();

	//{// ゲージの更新
	//	// サイズの更新
	//	m_nGageWave++;
	//	if (m_nGageWave >= 100)
	//	{
	//		m_nGageWave = 0;
	//	}
	//	m_pGauge->SetNumber((float)m_nGageWave);
	//}

	// 更新
	CObject::UpdateAll();

	// 敵の当たり判定
	CEnemy::Collision();

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
// リセット
//--------------------------------------------------
void CGame::Reset()
{
	// 敵の全ての解放
	CObject3D::ReleaseAll(CObject3D::TYPE_ENEMY);

	// 弾の全ての解放
	CObject3D::ReleaseAll(CObject3D::TYPE_BULLET);

	// EXPの全ての解放
	CObject3D::ReleaseAll(CObject3D::TYPE_EXP);

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Start);
}

//--------------------------------------------------
// スコアの取得
//--------------------------------------------------
CScore* CGame::GetScore()
{
	return m_pScore;
}

//--------------------------------------------------
// タイムの取得
//--------------------------------------------------
CTime* CGame::GetTime()
{
	return m_pTime;
}

//--------------------------------------------------
// エフェクト
//--------------------------------------------------
void CGame::Effect()
{
	m_time++;

	if ((m_time % 30) != 0)
	{// 一定間隔待ち
		return;
	}

	// 背景
	CEffectManager::GetInstanse()->BG();
}
