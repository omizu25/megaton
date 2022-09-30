//=============================================================================
//
// ツインサークルゲージクラス(twin_circle.h)
// Author : 唐�ｱ結斗
// 概要 : 振り子ゲージ生成を行う
//
//=============================================================================
#ifndef _TWIN_CIRCLE_H_		// このマクロ定義がされてなかったら
#define _TWIN_CIRCLE_H_		// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"
#include "texture.h"
#include <d3dx9.h>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;

//=============================================================================
// 振り子ゲージクラス
// Author : 唐�ｱ結斗
// 概要 : 振り子ゲージ生成を行うクラス
//=============================================================================
class CTwinCircle : public CObject
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CTwinCircle *Create(void);				// 振り子ゲージの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CTwinCircle(CObject::ECategory cat = CObject::CATEGORY_2D);
	~CTwinCircle() override;

	//--------------------------------------------------------------------
	// オーバーライド関数
	//--------------------------------------------------------------------
	void Init() override;										// 初期化
	void Uninit() override;										// 終了
	void Update() override;										// 更新
	void Draw() override;										// 描画
	void SetPos(const D3DXVECTOR3 &pos);						// 位置のセッター
	void SetRot(const D3DXVECTOR3 &rot);						// 向きのセッター
	void SetSize(const D3DXVECTOR3 &size);						// 大きさのセッター
	D3DXVECTOR3 GetPos() { return m_pos; }						// 位置のゲッター
	D3DXVECTOR3 GetRot() { return m_rot; }						// 向きのゲッター
	D3DXVECTOR3 GetSize() { return m_size; }					// 大きさのゲッター
	void SetAction(bool bAction) { m_bAction = bAction; }		// アクションの設定
	int GetScore() { return m_nScore; }							// スコアの取得

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	CObject2D		*pTarget;			// ターゲット
	CObject2D		*pTarget0;			// ターゲット
	CObject2D		*pTarget1;			// ターゲット1
	D3DXVECTOR3		m_pos;				// 位置
	D3DXVECTOR3		m_rot;				// 向き
	D3DXVECTOR3		m_size;				// 大きさ
	D3DXVECTOR3		m_moveTarget;		// 振り子の移動量
	D3DXVECTOR2		m_wave;				// 波
	float			m_fDistance;		// ターゲットとの距離
	float			m_fMaxDistance;		// ターゲットとの距離の最大
	int				m_nScore;			// スコア
	bool			m_bAction;			// アクションを行うか
};

#endif




