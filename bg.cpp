//**************************************************
// 
// bg.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "bg.h"
#include "application.h"
#include <assert.h>

//--------------------------------------------------
// 生成
//--------------------------------------------------
CBG* CBG::Create(CTexture::ELabel texture)
{
	CBG* pBG = nullptr;

	pBG = new CBG;

	if (pBG != nullptr)
	{// nullチェック
		pBG->Init();

		// テクスチャの設定
		pBG->SetTexture(texture);
	}

	return pBG;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CBG::CBG()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CBG::~CBG()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CBG::Init()
{
	// 初期化
	CObject3D::Init();

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CBG::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CBG::Update()
{
	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CBG::Draw()
{
	// 描画
	CObject3D::Draw();
}
