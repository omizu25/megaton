//**************************************************
// 
// title.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "title.h"
#include "application.h"
#include "camera.h"
#include "object2D.h"
#include "effect_manager.h"
#include "utility.h"
#include "menu.h"
#include "sound.h"
#include "game.h"
#include "bg.h"
#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTitle::CTitle() : CMode(CMode::MODE_TITLE),
	m_pMenu(nullptr),
	m_time(0),
	m_partCnt(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTitle::~CTitle()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CTitle::Init()
{
	m_time = 0;
	m_partCnt = 0;

	{// 背景
		CBG::Create(CTexture::LABEL_NightSky);
	}

	CObject2D* pTitle = CObject2D::Create();
	pTitle->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.3f, 0.0f));
	pTitle->SetSize(D3DXVECTOR3(1000.0f, 375.0f, 0.0f));
	pTitle->SetTexture(CTexture::LABEL_TitleLogo);
	pTitle->SetFade(0.0f);

	{// メニュー
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.75f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(600.0f, 150.0f, 0.0f);

		// メニューの生成
		m_pMenu = CMenu::Create(pos, size, 1, 0.0f, true, false);

		// テクスチャの設定
		m_pMenu->SetTexture(0, CTexture::LABEL_PressEnter);
	}

	// BGM
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_BGM_Title);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTitle::Uninit()
{
	if (m_pMenu != nullptr)
	{// nullチェック
		m_pMenu->Uninit();
		delete m_pMenu;
		m_pMenu = nullptr;
	}

	// 全ての解放
	CObject::ReleaseAll(false);

	CApplication* pApp = CApplication::GetInstanse();

	// テクスチャの破棄
	pApp->GetTexture()->ReleaseAll();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CTitle::Update()
{
	// 更新
	CObject::UpdateAll();

	// エフェクト
	Effect();

	// 選択
	int select = m_pMenu->Select();

	if (m_time >= CMode::FADE_TIME)
	{// フェード時間
		if (select != -1)
		{
			Change(MODE_GAME);
		}
	}

	// カメラの更新
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CTitle::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}

//--------------------------------------------------
// エフェクト
//--------------------------------------------------
void CTitle::Effect()
{
	m_time++;

	if ((m_time % 30) != 0)
	{// 一定間隔待ち
		return;
	}

	// パーティクル
	CEffectManager::GetInstanse()->Particle();
}
