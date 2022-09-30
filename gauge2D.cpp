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

#include "gauge2D.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : 2Dゲージを生成する
//=============================================================================
CGauge2D * CGauge2D::Create(void)
{
	// オブジェクトインスタンス
	CGauge2D *pGauge2D = nullptr;

	// メモリの解放
	pGauge2D = new CGauge2D;

	if (pGauge2D != nullptr)
	{// 数値の初期化
		pGauge2D->Init();
	}
	else
	{// メモリの確保ができなかった
		assert(false);
	}

	// インスタンスを返す
	return pGauge2D;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CGauge2D::CGauge2D(CObject::ECategory cat) : CObject(cat)
{
	m_pVtxBuff = nullptr;								// 頂点バッファ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 大きさ
	m_maxSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 大きさ最大値
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			// カラー
	m_fAngle = 0.0f;									// 対角線の角度
	m_fLength = 0.0f;									// 対角線の長さ
	m_fAngleOrigin = 0.0f;								// もとの対角線の角度
	m_fLengthOrigin = 0.0f;								// もと対角線の長さ
	m_fMaxNumber = 0.0f;								// 数値の最大数
	m_fNumber = 0.0f;									// 数値
	m_fDestNumber = 0.0f;								// 目的の数値
	m_fCoefficient = 0.0f;								// 減衰係数
	m_texture = CTexture::LABEL_NONE;					// テクスチャの列挙型
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CGauge2D::~CGauge2D()
{

}

//=============================================================================
// ポリゴンの初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
void CGauge2D::Init()
{// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,														// 頂点ファーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ポリゴン情報の設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
	m_size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);		// 大きさ
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// カラー

	// 頂点座標の算出
	SetVtx();

	// 色の設定
	SetCol(m_col);

	// テクスチャ座標の設定
	SetVtxTex(D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
}

//=============================================================================
// ポリゴンの終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CGauge2D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{// 頂点バッファの破棄
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// ポリゴンの更新
// Author : 唐﨑結斗
// 概要 : 2Dポリゴンの更新を行う
//=============================================================================
void CGauge2D::Update()
{
	// 数値の設定
	float fAdd = (m_fDestNumber - m_fNumber) * m_fCoefficient;

	m_fNumber += fAdd;

	if (fAdd > 0)
	{
		if (m_fNumber >= m_fDestNumber)
		{
			m_fNumber = m_fDestNumber;
		}
	}
	else if (fAdd < 0)
	{
		if (m_fNumber <= m_fDestNumber)
		{
			m_fNumber = m_fDestNumber;
		}
	}

	// ゲージの設定
	SetGauge();
}

//=============================================================================
// ポリゴンの描画
// Author : 唐﨑結斗
// 概要 : 2Dポリゴンの描画を行う
//=============================================================================
void CGauge2D::Draw()
{// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// テクスチャポインタの取得
	CTexture *pTexture = CApplication::GetInstanse()->GetTexture();

	//テクスチャの設定
	pDevice->SetTexture(0, nullptr);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->Get(m_texture));

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//テクスチャの設定
	pDevice->SetTexture(0, nullptr);
}

//=============================================================================
// 位置のセッター
// Author : 唐﨑結斗
// 概要 : 位置のメンバ変数に引数を代入
//=============================================================================
void CGauge2D::SetPos(const D3DXVECTOR3 &pos)
{
	// 位置の設定
	m_pos = pos;

	// 頂点座標などの設定
	SetVtx();

	// 色の設定
	SetCol(m_col);
}

//=============================================================================
// 向きのセッター
// Author : 唐﨑結斗
// 概要 : 向きのメンバ変数に引数を代入
//=============================================================================
void CGauge2D::SetRot(const D3DXVECTOR3 &rot)
{
	// 向きの設定
	m_rot = rot;

	// 頂点座標などの設定
	SetVtx();

	// 色の設定
	SetCol(m_col);
}

//=============================================================================
// 大きさのセッター
// Author : 唐﨑結斗
// 概要 : 大きさのメンバ変数に引数を代入
//=============================================================================
void CGauge2D::SetSize(const D3DXVECTOR3 & size)
{
	// 大きさの設定
	m_maxSize = D3DXVECTOR3(size.x, size.y * 2.0f, 0.0f);

	// 頂点座標などの設定
	SetVtx();

	// 色の設定
	SetCol(m_col);
}

//=============================================================================
// 頂点座標などの設定
// Author : 唐﨑結斗
// 概要 : 2Dポリゴンの頂点座標、rhw、頂点カラーを設定する
//=============================================================================
void CGauge2D::SetVtx()
{
	//頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//対角線の長さを算出する
	m_fLength = sqrtf((m_maxSize.x * m_maxSize.x) + (m_size.y * m_size.y)) / 2.0f;
	m_fLengthOrigin = sqrtf(m_maxSize.x * m_maxSize.x) / 2.0f;

	//対角線の角度を算出
	m_fAngle = atan2f(m_maxSize.x, m_size.y);
	m_fAngleOrigin = atan2f(m_maxSize.x, 0.0f);

	// 頂点情報を設定
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) *  m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) *  m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - (0 + m_fAngleOrigin)) * m_fLengthOrigin;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - (0 + m_fAngleOrigin)) * m_fLengthOrigin;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z - (0 - m_fAngleOrigin)) *  m_fLengthOrigin;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z - (0 - m_fAngleOrigin)) *  m_fLengthOrigin;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 色の設定
// Author : 唐﨑結斗
// 概要 : 頂点カラーを設定する
//=============================================================================
void CGauge2D::SetCol(const D3DCOLOR &col)
{
	m_col = col;

	//頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// テクスチャの設定
//--------------------------------------------------
void CGauge2D::SetTexture(CTexture::ELabel texture)
{
	m_texture = texture;
}

//--------------------------------------------------
// テクスチャ座標の設定
//--------------------------------------------------
void CGauge2D::SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2 v)
{
	VERTEX_2D *pVtx = nullptr;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(u.x, v.x);
	pVtx[1].tex = D3DXVECTOR2(u.y, v.x);
	pVtx[2].tex = D3DXVECTOR2(u.x, v.y);
	pVtx[3].tex = D3DXVECTOR2(u.y, v.y);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ゲージの設定
// Author : 唐﨑結斗
// 概要 : 2Dゲージを設定する
//=============================================================================
void CGauge2D::SetGauge()
{
	// 大きさに数値を代入
	m_size.y = (m_maxSize.y / m_fMaxNumber) * m_fNumber;

	// 頂点座標の設定
	SetVtx();
}

//=============================================================================
// 数値の最大値の設定
// Author : 唐﨑結斗
// 概要 : 数値の最大値を設定する
//=============================================================================
void CGauge2D::SetMaxNumber(const float fMaxNumber)
{
	m_fMaxNumber = fMaxNumber;

	// ゲージの設定
	SetGauge();
}

