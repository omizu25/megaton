//=============================================================================
//
// ゲージマネージャークラス(gage_manager.cpp)
// Author : 唐﨑結斗
// 概要 : ゲージマネージャー生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>
#include <math.h>

#include "gage_manager.h"
#include "gauge2D.h"
#include "pendulum.h"
#include "twin_circle.h"
#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "mode.h"
#include "game.h"
#include "score.h"
#include "input.h"
#include "locus.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : 2Dゲージを生成する
//=============================================================================
CGageManager * CGageManager::Create(void)
{
	// オブジェクトインスタンス
	CGageManager *pGageManager = nullptr;

	// メモリの解放
	pGageManager = new CGageManager;

	if (pGageManager != nullptr)
	{// 数値の初期化
		pGageManager->Init();
	}
	else
	{// メモリの確保ができなかった
		assert(false);
	}

	// インスタンスを返す
	return pGageManager;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CGageManager::CGageManager(CObject::ECategory cat) : CObject(cat)
{
	m_pGauge2D = nullptr;						// ターゲット
	m_pPendulum = nullptr;						// 振り子
	m_pTwinCircle = nullptr;					// サークル
	m_pos = D3DXVECTOR3(0.0f, 0.f, 0.0f);		// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.f, 0.0f);		// 向き
	m_size = D3DXVECTOR3(0.0f, 0.f, 0.0f);		// 大きさ
	m_nScore = 0;								// スコア
	m_nCntGage = 0;								// ゲージのカウント
	m_nCntFrame = 0;							// フレームカウント
	m_bKeyPress = false;						// ボタンを押したか
	m_end = false;
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CGageManager::~CGageManager()
{

}

//=============================================================================
// ポリゴンの初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
void CGageManager::Init()
{
	// 配置の初期設定
	float posX = (float)(CApplication::SCREEN_WIDTH * 0.3f);
	float posY = (float)(CApplication::SCREEN_HEIGHT * 0.7f);

	m_pos = D3DXVECTOR3(posX, posY, 0.0f);			// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
	m_size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);		// 大きさ

	{// ゲージ枠
		m_pMax = CGauge2D::Create();	//生成

		//設定用
		float height = 810.0f;	//高さ
		D3DXVECTOR3 size = D3DXVECTOR3(60.0f, height, 0.0f);	// 大きさ

		//各種設定
		m_pMax->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + size.y / (height * 0.01f), 0.0f));
		m_pMax->SetChange(false, size);
	}

	{// ゲージ背景
		m_pFrame = CGauge2D::Create();	//生成

		//設定用
		float height = 800.0f;	//高さ
		D3DXVECTOR3 size = D3DXVECTOR3(50.0f, height, 0.0f);	// 大きさ

		//各種設定
		m_pFrame->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + size.y / (height * 0.01f), 0.0f));
		m_pFrame->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_pFrame->SetChange(false, size);
	}

	{// ゲージ
		m_pGauge2D = CGauge2D::Create();	//生成

		//設定用
		float height = 200.0f;	//高さ

		//各種設定
		m_pGauge2D->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y / (height * 0.01f), 0.0f));
		m_pGauge2D->SetSize(D3DXVECTOR3(50.0f, height, 0.0f));
		m_pGauge2D->SetMaxNumber(50.0f);
		m_pGauge2D->SetCoefficient(1.0f);
		m_pGauge2D->SetNumber(30.0f);
		m_end = false;
	}
}

//=============================================================================
// ポリゴンの終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CGageManager::Uninit()
{

}

//=============================================================================
// ポリゴンの更新
// Author : 唐﨑結斗
// 概要 : 2Dポリゴンの更新を行う
//=============================================================================
void CGageManager::Update()
{
	CInput* pInput = CInput::GetKey();

	if (!m_bKeyPress)
	{
		m_bKeyPress = pInput->Trigger(CInput::KEY_DECISION);
	}

	switch (m_type)
	{
	case CGageManager::GAGE_POLE:
		if(!m_bKeyPress)
		{// ゲージの更新
			// サイズの更新
			m_nCntGage++;
			m_pGauge2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			if (m_nCntGage >= 95)
			{
				m_pGauge2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			}
			if (m_nCntGage > 100)
			{
				m_nCntGage = 0;
			}
			m_pGauge2D->SetNumber((float)m_nCntGage);
		}

		if (m_bKeyPress)
		{
			m_nCntFrame++;
			if (m_nCntFrame >= MAX_FRAME)
			{
				m_nCntFrame = 0;
				m_bKeyPress = false;
				m_nScore += m_nCntGage;
				CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();

				// スコアの加算
				pGame->GetScore(GAGE_POLE)->Set(m_pGauge2D->GetNumber());

				m_pGauge2D->Release(); 
				m_pMax->Release(); 
				m_pFrame->Release();

				m_pPendulum = CPendulum::Create();
				m_type = GAGE_PENDULUM;
			}
		}
		break;

	case CGageManager::GAGE_PENDULUM:

		if (m_bKeyPress)
		{
			m_pPendulum->SetAction(false);
			m_nCntFrame++;
			if (m_nCntFrame >= MAX_FRAME)
			{
				m_nCntFrame = 0;
				m_bKeyPress = false;
				m_nScore += m_pPendulum->GetScore();

				CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();

				// スコアの加算
				pGame->GetScore(GAGE_PENDULUM)->Set(m_pPendulum->GetScore());
				m_pPendulum->Release();

				m_pTwinCircle = CTwinCircle::Create();
				m_type = GAGE_TWINCIRCLE;
			}
		}
		break;

	case CGageManager::GAGE_TWINCIRCLE:

		if (m_bKeyPress)
		{
			m_pTwinCircle->SetAction(false);
			m_nCntFrame++;
			if (m_nCntFrame >= MAX_FRAME)
			{
				m_nCntFrame = 0;
				m_bKeyPress = false;
				m_nScore += m_pTwinCircle->GetScore();
				CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();

				// スコアの加算
				pGame->GetScore(GAGE_TWINCIRCLE)->Set(m_pTwinCircle->GetScore());

				m_pTwinCircle->Release();

				m_type = MAX_GAGETYPE;
				CLocus *pLocus = CLocus::Create();
				pLocus->SetPos(D3DXVECTOR3(0.0f, -300.0f, 0.0f));
				pLocus->SetLife(600);
				pLocus->SetSpeed(15.0f);
				pLocus->SetWaveSpeed(0.4f);
				pLocus->SetWaveWidth(15.0f);
			}
		}
		break;

	case CGageManager::MAX_GAGETYPE:
	
		if (!m_end)
		{
			m_end = true;
			// モードの変更
			CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
			pGame->EndGame();
		}
	
		break;

	default:
		assert(false);
		break;
	}
}

//=============================================================================
// ポリゴンの描画
// Author : 唐﨑結斗
// 概要 : 2Dポリゴンの描画を行う
//=============================================================================
void CGageManager::Draw()
{

}

//=============================================================================
// 位置のセッター
// Author : 唐﨑結斗
// 概要 : 位置のメンバ変数に引数を代入
//=============================================================================
void CGageManager::SetPos(const D3DXVECTOR3 &pos)
{
	// 配置の初期設定
	m_pos = pos;			// 位置
}

//=============================================================================
// 向きのセッター
// Author : 唐﨑結斗
// 概要 : 向きのメンバ変数に引数を代入
//=============================================================================
void CGageManager::SetRot(const D3DXVECTOR3 &rot)
{
	// 配置の初期設定
	m_rot = rot;				// 向き
}

//=============================================================================
// 大きさのセッター
// Author : 唐﨑結斗
// 概要 : 大きさのメンバ変数に引数を代入
//=============================================================================
void CGageManager::SetSize(const D3DXVECTOR3 & size)
{
	// 配置の初期設定
	m_size = size;				// サイズ
}
