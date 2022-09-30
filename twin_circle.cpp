//=============================================================================
//
// 2Dゲージクラス(gauge2D.cpp)
// Author : 唐﨑結斗
// 概要 : 2Dゲージ生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "twin_circle.h"
#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "utility.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : 2Dゲージを生成する
//=============================================================================
CTwinCircle * CTwinCircle::Create(void)
{
	// オブジェクトインスタンス
	CTwinCircle *pTwinCircle = nullptr;

	// メモリの解放
	pTwinCircle = new CTwinCircle;

	if (pTwinCircle != nullptr)
	{// 数値の初期化
		pTwinCircle->Init();
	}
	else
	{// メモリの確保ができなかった
		assert(false);
	}

	// インスタンスを返す
	return pTwinCircle;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CTwinCircle::CTwinCircle(CObject::ECategory cat) : CObject(cat)
{
	pTarget0 = nullptr;									// ターゲット
	pTarget1 = nullptr;									// ターゲット1
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 大きさ
	m_moveTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ターゲットの移動量
	m_wave = D3DXVECTOR2(0.0f, 0.0f);					// 波
	m_fDistance = FLT_MAX;								// ターゲットとの距離
	m_fMaxDistance = 0.0f;								// ターゲットとの距離の最大
	m_nScore = 0;										// スコア
	m_bAction = true;									// アクションを行うか
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CTwinCircle::~CTwinCircle()
{

}

//=============================================================================
// ポリゴンの初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
void CTwinCircle::Init()
{
	//位置設定用
	float fPosX = (CApplication::SCREEN_WIDTH * 0.32f);	//X軸
	float fPosY = (CApplication::SCREEN_HEIGHT * 0.5f);	//Y軸

	// 配置の初期設定
	m_pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);			// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向き
	m_size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);			// 大きさ

	// ターゲットオブジェクト0の設定
	pTarget0 = CObject2D::Create();
	pTarget0->SetPos(m_pos);
	pTarget0->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	// ターゲットオブジェクト1の設定
	pTarget1 = CObject2D::Create();
	pTarget1->SetPos(m_pos);
	pTarget1->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	// ディスタンスの最大値
	float fMaxDistanceX = 1.0f / 0.1f * 18.0f;
	float fMaxDistanceY = 1.0f / 0.1f * 15.0f;
	m_fMaxDistance = sqrtf(fMaxDistanceX * fMaxDistanceX + fMaxDistanceY * fMaxDistanceY);
}

//=============================================================================
// ポリゴンの終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CTwinCircle::Uninit()
{
	pTarget0->Release();
	pTarget1->Release();
}

//=============================================================================
// ポリゴンの更新
// Author : 唐﨑結斗
// 概要 : 2Dポリゴンの更新を行う
//=============================================================================
void CTwinCircle::Update()
{
	if (m_bAction)
	{
		m_wave.x += 0.1f;
		m_wave.y += 0.1f;
		NormalizeAngle(&m_wave.x);
		NormalizeAngle(&m_wave.y);
		m_moveTarget.x = sinf(m_wave.x) * 18.0f;
		m_moveTarget.y = cosf(m_wave.y) * 15.0f;

		// 振り子の移動
		D3DXVECTOR3 pos0 = pTarget0->GetPos() + m_moveTarget;
		D3DXVECTOR3 pos1 = pTarget1->GetPos() - m_moveTarget;
		pTarget0->SetPos(pos0);
		pTarget1->SetPos(pos1);

		// ディスタンスの設定
		float fDistanceX = pTarget0->GetPos().x - pTarget1->GetPos().x;
		float fDistanceY = pTarget0->GetPos().y - pTarget1->GetPos().y;
		if (fDistanceX < 0.0f)
		{
			fDistanceX *= -1;
		}
		else if (fDistanceY < 0.0f)
		{
			fDistanceY *= -1;
		}
		m_fDistance = sqrtf(fDistanceX * fDistanceX  + fDistanceY * fDistanceY);

		pTarget0->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pTarget1->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if (CollisionCircle(pTarget0->GetPos(), pTarget0->GetSize().x * 0.5f, pTarget1->GetPos(), pTarget1->GetSize().x * 0.5f))
		{
			pTarget0->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			pTarget1->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
	}
	else if (!m_bAction)
	{
		m_nScore = 100 - (int)(100.0f * (m_fDistance / m_fMaxDistance));

		if (m_nScore <= 0)
		{
			m_nScore = 0;
		}
	}
}

//=============================================================================
// ポリゴンの描画
// Author : 唐﨑結斗
// 概要 : 2Dポリゴンの描画を行う
//=============================================================================
void CTwinCircle::Draw()
{

}

//=============================================================================
// 位置のセッター
// Author : 唐﨑結斗
// 概要 : 位置のメンバ変数に引数を代入
//=============================================================================
void CTwinCircle::SetPos(const D3DXVECTOR3 &pos)
{
	// 配置の初期設定
	m_pos = pos;			// 位置

	// ターゲットオブジェクト0の設定
	pTarget0->SetPos(m_pos);

	// ターゲットオブジェクト1の設定
	pTarget1->SetPos(m_pos);
}

//=============================================================================
// 向きのセッター
// Author : 唐﨑結斗
// 概要 : 向きのメンバ変数に引数を代入
//=============================================================================
void CTwinCircle::SetRot(const D3DXVECTOR3 &rot)
{
	// 配置の初期設定
	m_rot = rot;				// 向き
}

//=============================================================================
// 大きさのセッター
// Author : 唐﨑結斗
// 概要 : 大きさのメンバ変数に引数を代入
//=============================================================================
void CTwinCircle::SetSize(const D3DXVECTOR3 & size)
{
	// 配置の初期設定
	m_size = size;				// サイズ

	// ターゲットオブジェクトの設定
	pTarget1->SetSize(m_size);

	// 振り子オブジェクトの設定
	pTarget1->SetSize(m_size);
}