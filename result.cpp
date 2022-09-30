//**************************************************
// 
// result.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
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
// デフォルトコンストラクタ
//--------------------------------------------------
CResult::CResult() : CMode(CMode::MODE_RESULT),
	m_time(0),
	m_fireworks(false)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CResult::Init()
{
	m_time = 0;
	m_fireworks = false;

	{// 背景
		CBG::Create(CTexture::LABEL_NightSky);
	}

	CLocus *pLocus = CLocus::Create();
	pLocus->SetPos(D3DXVECTOR3(-50.0f, -550.0f, 0.0f));
	pLocus->SetLife(35);	pLocus->SetSpeed(15.0f);
	pLocus->SetWaveSpeed(0.4f);
	pLocus->SetWaveWidth(15.0f);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CResult::Uninit()
{
	// 全ての解放
	CApplication::GetInstanse()->GetSound()->Stop();

	CObject::ReleaseAll(false);

	CApplication* pApp = CApplication::GetInstanse();

	// テクスチャの破棄
	pApp->GetTexture()->ReleaseAll();

	// 停止
	pApp->GetSound()->Stop();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CResult::Update()
{
	// 更新
	CObject::UpdateAll();

	m_time++;
	if (m_time == 1)
	{
		CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Explosion_Short);
	}
	
	if (m_time >= 240)
	{// フェード時間


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

	// カメラの更新
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CResult::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}
