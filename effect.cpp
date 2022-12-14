//**************************************************
// 
// effect.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "effect.h"
#include "application.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CEffect::MAX_LIFE = 100;
const float CEffect::STD_WIDTH = 12.0f;
const float CEffect::STD_HEIGHT = 100.0f;
const float CEffect::MIN_WIDTH = 5.0f;

//==================================================
// 静的メンバ変数
//==================================================
int CEffect::m_numAll = 0;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CEffect* CEffect::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXCOLOR& col)
{
	if (m_numAll >= CObject::GetMax(CObject::CATEGORY_EFFECT))
	{// 最大数を越した
		return nullptr;
	}

	CEffect* pEffect = nullptr;

	pEffect = new CEffect;
	
	if (pEffect != nullptr)
	{// nullチェック
		pEffect->Init();
		pEffect->m_pos = pos;
		pEffect->m_move = move;
		pEffect->m_col = col;
	}

	return pEffect;
}

//--------------------------------------------------
// 総数の取得
//--------------------------------------------------
int CEffect::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEffect::CEffect() : CObject(CObject::CATEGORY_EFFECT),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f)),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_life(0),
	m_colSubtract(false)
{
	m_numAll++;
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEffect::~CEffect()
{
	m_numAll--;
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEffect::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(STD_WIDTH, STD_HEIGHT);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_life = MAX_LIFE;
	m_colSubtract = true;

	// キープの設定
	CObject::SetKeep(true);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEffect::Uninit()
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEffect::Update()
{
	m_life--;

	if (m_life <= 0)
	{
		CObject::Release();
		return;
	}

	m_pos += m_move;

	//慣性・移動量を更新 (減衰させる)
	m_move.x += (0.0f - m_move.x) * 0.05f;
	m_move.y += (0.0f - m_move.y) * 0.05f;
	float ratio = ((float)(MAX_LIFE - m_life) / MAX_LIFE);
	m_col.a = 1.0f - (ratio * ratio);

	if (m_colSubtract)
	{// 色の減算

		float len = STD_HEIGHT * D3DXVec3Length(&m_move);

		if (len >= STD_HEIGHT)
		{// 指定の値よりも大きい
			len = STD_HEIGHT;
		}
		else if (len <= STD_WIDTH)
		{// 指定の値よりも小さい
			len = STD_WIDTH;
		}

		m_size.y = len;
	}
	else
	{
		m_size = D3DXVECTOR2(STD_WIDTH, STD_WIDTH);
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEffect::Draw()
{
	/* インスタンシングで描画 */
}

//--------------------------------------------------
// 位置の取得
//--------------------------------------------------
const D3DXVECTOR3& CEffect::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// 色の取得
//--------------------------------------------------
const D3DXCOLOR& CEffect::GetCol() const
{
	return m_col;
}

//--------------------------------------------------
// 移動量の取得
//--------------------------------------------------
const D3DXVECTOR3& CEffect::GetMove() const
{
	return m_move;
}

//--------------------------------------------------
// サイズの取得
//--------------------------------------------------
const D3DXVECTOR2& CEffect::GetSize() const
{
	return m_size;
}

//--------------------------------------------------
// 色の減算をするかどうかの設定
//--------------------------------------------------
void CEffect::SetColSubtract(bool subtract)
{
	m_colSubtract = subtract;
}

//--------------------------------------------------
// サイズの設定
//--------------------------------------------------
void CEffect::SetSize(const D3DXVECTOR2& size)
{
	m_size = size;
}