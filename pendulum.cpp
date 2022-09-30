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
#include <math.h>

#include "pendulum.h"
#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "utility.h"
#include "sound.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : 2Dゲージを生成する
//=============================================================================
CPendulum * CPendulum::Create(void)
{
	// オブジェクトインスタンス
	CPendulum *pPendulum = nullptr;

	// メモリの解放
	pPendulum = new CPendulum;

	if (pPendulum != nullptr)
	{// 数値の初期化
		pPendulum->Init();
	}
	else
	{// メモリの確保ができなかった
		assert(false);
	}

	// インスタンスを返す
	return pPendulum;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CPendulum::CPendulum(CObject::ECategory cat) : CObject(cat)
{
	pTarget = nullptr;									// ターゲット
	pPendulum = nullptr;								// 振り子
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);				// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 大きさ
	m_movePendulum = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 振り子の移動量
	m_wave = D3DXVECTOR2(0.0f,0.0f);					// 波
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
CPendulum::~CPendulum()
{

}

//=============================================================================
// ポリゴンの初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
void CPendulum::Init()
{
	//位置設定用
	float fPosX = (CApplication::SCREEN_WIDTH * 0.23f);	//X軸
	float fPosY = (CApplication::SCREEN_HEIGHT * 0.7f);	//Y軸

	// 配置の初期設定
	m_pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);			// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向き
	m_size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);			// 大きさ

	// ターゲットオブジェクトの設定
	pTarget = CObject2D::Create();
	pTarget->SetPos(m_pos);
	pTarget->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	pTarget->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	pTarget->SetTexture(CTexture::LABEL_Circle_Green);

	// 振り子オブジェクトの設定
	pPendulum = CObject2D::Create();
	pPendulum->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));
	pPendulum->SetSize(D3DXVECTOR3(45.0f, 45.0f, 0.0f));
	pPendulum->SetTexture(CTexture::LABEL_Pien_White);

	// ディスタンスの最大値
	m_fMaxDistance = 400.0f;
}

//=============================================================================
// ポリゴンの終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CPendulum::Uninit()
{
	CApplication::GetInstanse()->GetSound()->Stop(CSound::LABEL_SE_Gauge_Halfway);
	pTarget->Release();
	pPendulum->Release();
}

//=============================================================================
// ポリゴンの更新
// Author : 唐﨑結斗
// 概要 : 2Dポリゴンの更新を行う
//=============================================================================
void CPendulum::Update()
{
	if(m_bAction)
	{// 移動値の算出
		m_wave.x += 0.05f;
		m_wave.y += 0.1f;
		NormalizeAngle(&m_wave.x);
		NormalizeAngle(&m_wave.y);
		m_movePendulum.x = cosf(m_wave.x) * 10.0f;
		m_movePendulum.y = sinf(m_wave.y) * -20.0f;

		// 振り子の移動
		D3DXVECTOR3 pos = pPendulum->GetPos() + m_movePendulum;
		pPendulum->SetPos(pos);

		// ディスタンスの設定
		m_fDistance = pTarget->GetPos().y - pPendulum->GetPos().y;

		if (m_fDistance < 0.0f)
		{
			m_fDistance = 0.0f;
		}

		pPendulum->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if (CollisionCircle(pPendulum->GetPos(), pPendulum->GetSize().x * 0.5f, pTarget->GetPos(), pTarget->GetSize().x * 0.5f))
		{
			pPendulum->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Gauge_Halfway);
		}
	}
	else if (!m_bAction)
	{
		m_nScore = (int)(100 - (100 * m_fDistance / m_fMaxDistance));
	}
}

//=============================================================================
// ポリゴンの描画
// Author : 唐﨑結斗
// 概要 : 2Dポリゴンの描画を行う
//=============================================================================
void CPendulum::Draw()
{

}

//=============================================================================
// 位置のセッター
// Author : 唐﨑結斗
// 概要 : 位置のメンバ変数に引数を代入
//=============================================================================
void CPendulum::SetPos(const D3DXVECTOR3 &pos)
{
	// 配置の初期設定
	m_pos = pos;			// 位置

	// ターゲットオブジェクトの設定
	pTarget->SetPos(m_pos);

	// 振り子オブジェクトの設定
	pPendulum->SetPos(m_pos);
}

//=============================================================================
// 向きのセッター
// Author : 唐﨑結斗
// 概要 : 向きのメンバ変数に引数を代入
//=============================================================================
void CPendulum::SetRot(const D3DXVECTOR3 &rot)
{
	// 配置の初期設定
	m_rot = rot;				// 向き

	// ターゲットオブジェクトの設定
	pTarget->SetPos(m_rot);

	// 振り子オブジェクトの設定
	pPendulum->SetPos(m_rot);
}

//=============================================================================
// 大きさのセッター
// Author : 唐﨑結斗
// 概要 : 大きさのメンバ変数に引数を代入
//=============================================================================
void CPendulum::SetSize(const D3DXVECTOR3 & size)
{
	// 配置の初期設定
	m_size = size;				// サイズ

	// ターゲットオブジェクトの設定
	pTarget->SetSize(m_size);

	// 振り子オブジェクトの設定
	pPendulum->SetSize(m_size);
}