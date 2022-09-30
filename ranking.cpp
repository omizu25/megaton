//**************************************************
// 
// ranking.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
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
#include "sound.h"
#include "fade.h"
#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CRanking::CRanking() : CMode(CMode::MODE_RANKING),
	m_pRanking(nullptr),
	m_pMenu(nullptr),
	m_time(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CRanking::~CRanking()
{
	assert(m_pRanking == nullptr);
	assert(m_pMenu == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CRanking::Init()
{
	m_time = 0;

	{// BGM
		CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_BGM_Result);
	}

	{// 背景
		CBG::Create(CTexture::LABEL_NightSky);
	}

	{// ランキングの背景
		float width = (float)CApplication::SCREEN_WIDTH * 0.75f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.5f - 15.0f;

		// ランキングの背景の生成
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(600.0f, 650.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_NONE);
		pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		pObj->SetFade(0.0f);
	}

	{// スコアの背景
		float width = (float)CApplication::SCREEN_WIDTH * 0.25f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.25f - 10.0f;

		// スコアの背景の生成
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(620.0f, 300.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_NONE);
		pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		pObj->SetFade(0.0f);
	}

	{// ランキング
		float width = (float)CApplication::SCREEN_WIDTH - 150.0f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

		// ランキングの生成
		m_pRanking = CRankingUI::Create(D3DXVECTOR3(width, height, 0.0f), 15.0f);
	}

	{// ランキングの文字列
		float width = (float)CApplication::SCREEN_WIDTH * 0.75f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.15f;

		// 文字列の生成
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(480.0f, 150.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_Ranking);
		pObj->SetFade(0.0f);
	}

	{// 今回のスコア
		D3DXVECTOR3 size = D3DXVECTOR3(CRankingUI::STD_WIDTH * 1.5f, CRankingUI::STD_HEIGHT * 1.5f, 0.0f);
		int score = CRankingUI::Get(-1);
		int digit = Digit(score);
		float center = (digit * (size.x * 0.5f)) + (((digit - 1) / 3) * (size.x * 0.25f));
		float width = (float)CApplication::SCREEN_WIDTH * 0.25f + center;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

		// スコアの生成
		m_pScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);

		// スコアの設定
		m_pScore->Set(score);
	}

	{// 今回のスコアの文字列
		float width = (float)CApplication::SCREEN_WIDTH * 0.25f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.15f - 12.5f;

		// 文字列の生成
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(350.0f, 150.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_Score);
		pObj->SetFade(0.0f);
	}

	{// メニュー
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.3f, (float)CApplication::SCREEN_HEIGHT * 0.75f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(350.0f, 120.0f, 0.0f);

		// メニューの生成
		m_pMenu = CMenu::Create(pos, size, ESelect::SELECT_MAX, 40.0f, true, true);

		// テクスチャの設定
		m_pMenu->SetTexture(ESelect::SELECT_RETRY, CTexture::LABEL_Retry);
		m_pMenu->SetTexture(ESelect::SELECT_END, CTexture::LABEL_End);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CRanking::Uninit()
{
	if (m_pRanking != nullptr)
	{// nullチェック
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = nullptr;
	}

	if (m_pMenu != nullptr)
	{// nullチェック
		m_pMenu->Uninit();
		delete m_pMenu;
		m_pMenu = nullptr;
	}

	// 全ての解放
	CApplication::GetInstanse()->GetSound()->Stop(CSound::LABEL_BGM_Result);

	CObject::ReleaseAll(false);

	CApplication* pApp = CApplication::GetInstanse();

	// テクスチャの破棄
	pApp->GetTexture()->ReleaseAll();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CRanking::Update()
{
	// 更新
	CObject::UpdateAll();

	// エフェクト
	Effect();

	// ランキングの更新
	m_pRanking->Update();

	// 選択
	ESelect select = (ESelect)m_pMenu->Select();

	if (m_time >= CMode::FADE_TIME)
	{// フェード時間
		switch (select)
		{
		case ESelect::SELECT_NONE:
			break;

		case ESelect::SELECT_RETRY:
			CApplication::GetInstanse()->GetFade()->SetFade(CMode::MODE_GAME);
			return;
			break;

		case ESelect::SELECT_END:
			CApplication::GetInstanse()->GetFade()->SetFade(CMode::MODE_TITLE);
			return;
			break;

		case ESelect::SELECT_MAX:
		default:
			assert(false);
			break;
		}
	}

	// カメラの更新
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CRanking::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}

//--------------------------------------------------
// エフェクト
//--------------------------------------------------
void CRanking::Effect()
{
	m_time++;

	if ((m_time % 13) != 0)
	{// 一定間隔待ち
		return;
	}

	// パーティクル
	CEffectManager::GetInstanse()->Particle();
}
