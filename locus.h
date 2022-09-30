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
public:

	/* ↓静的メンバ関数↓ */
public:
	static CLocus* Create(const D3DXVECTOR3& start, const D3DXVECTOR3& end);	// 生成

	/* ↓メンバ関数↓ */
public:
	CLocus();			// デフォルトコンストラクタ
	~CLocus() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	void SetMove(const D3DXVECTOR3& start, const D3DXVECTOR3& end);

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_move;	// 移動量
};

#endif // !_LOCUS_H_
