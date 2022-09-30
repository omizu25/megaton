//**************************************************
// 
// locus.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _LOCUS_H_	//このマクロ定義がされてなかったら
#define _LOCUS_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CLocus : public CObject3D
{
	/* ↓定義↓ */
private:
	static const float STD_SIZE;	// サイズの標準値

	/* ↓静的メンバ関数↓ */
public:
	static CLocus* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CLocus();			// デフォルトコンストラクタ
	~CLocus() override;	// デストラクタ

public:
	void Init() override;															// 初期化
	void Uninit() override;															// 終了
	void Update() override;															// 更新
	void Draw() override;															// 描画
	void SetSpeed(const float fSpeed) { m_fSpeed = fSpeed; }						// 速度の設定
	void SetWaveSpeed(const float fWaveSpeed) { m_fWaveSpeed = fWaveSpeed; }		// 波の加算量の設定
	void SetWaveWidth(const float fWaveWidth) { m_fWaveWidth = fWaveWidth; }		// 波の倍率の設定
	void SetLife(const int nLife) { m_nLife = nLife; }								// 体力の設定

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3		m_move;				// 移動量
	float			m_fSpeed;			// 速度
	float			m_fWave;			// 波
	float			m_fWaveSpeed;		// 波の加算量
	float			m_fWaveWidth;		// 波の倍率
	int				m_nLife;			// 寿命
};

#endif // !_LOCUS_H_
