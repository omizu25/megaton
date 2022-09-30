//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "texture.h"
#include "application.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const char* CTexture::FILE_NAME[] =
{// テクスチャのパス
	"data/TEXTURE/effect.jpg",	// エフェクト
	"data/TEXTURE/bg000.png",	// 背景

	/* ↓テキスト↓ */
	"data/TEXTURE/TEXT/Number.png",	// 数
	"data/TEXTURE/TEXT/title.png",	// タイトル
	"data/TEXTURE/TEXT/rank.png",	// 位
	"data/TEXTURE/TEXT/Comma.png",	// カンマ

	/* ↓ハッカソン(2022/09/30)用↓ */
	"data/TEXTURE/TEXT/Hackathon_PressEnter.png",	// Enterを押してね
	"data/TEXTURE/TEXT/Hackathon_Score.png",		// スコア
	"data/TEXTURE/TEXT/Hackathon_Ranking.png",		// ランキング
	"data/TEXTURE/TEXT/Hachathon_GameBg.png",		// ゲーム画面の背景
	"data/TEXTURE/TEXT/Hachathon_NightSky.jpg",		// 夜空
	"data/TEXTURE/hanabitutu.png",					// 花火筒
	"data/TEXTURE/TEXT/Hackathon_Number.png",		// 0～9
	"data/TEXTURE/Hachathon_Pien_yellow.png",		// ぴえん(黄)
	"data/TEXTURE/Hachathon_Pien_white.png",		// ぴえん(白)
	"data/TEXTURE/Hachathon_Target.png",			// ターゲット
	"data/TEXTURE/TEXT/Hachathon_Tutorial.png",		// タイミング良くEnterを押そう！
	"data/TEXTURE/Hackathon_otowakka_0.png",		// サークル(赤)
	"data/TEXTURE/Hackathon_otowakka_1.png",		// サークル(緑)
	"data/TEXTURE/Hackathon_otowakka_2.png",		// サークル(青)
	"data/TEXTURE/Hackathon_5shakuball.png",		// 打ち上げ花火の弾部分
	"data/TEXTURE/Hackathon_TitleLogo.png",			// タイトルロゴ
	"data/TEXTURE/TEXT/Hackathon_Retry.png",		// リトライ
	"data/TEXTURE/TEXT/Hackathon_End.png",			// 終了
	"data/TEXTURE/Cursor.png",						// カーソル
};

static_assert(sizeof(CTexture::FILE_NAME) / sizeof(CTexture::FILE_NAME[0]) == CTexture::LABEL_MAX, "aho");

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTexture::CTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void CTexture::LoadAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// テクスチャの読み込みがされている
			continue;
		}

		// 読み込み
		Load((ELabel)i);
	}
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CTexture::Load(ELabel label)
{
	assert(label >= 0 && label < LABEL_MAX);

	if (s_pTexture[label] != nullptr)
	{// テクスチャの読み込みがされている
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_NAME[label],
		&s_pTexture[label]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CTexture::ReleaseAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// テクスチャの解放
			s_pTexture[i]->Release();
			s_pTexture[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CTexture::Release(ELabel label)
{
	assert(label >= 0 && label < LABEL_MAX);

	if (s_pTexture[label] != nullptr)
	{// テクスチャの解放
		s_pTexture[label]->Release();
		s_pTexture[label] = nullptr;
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::Get(ELabel label)
{
	if (label == LABEL_NONE)
	{// テクスチャを使用しない
		return nullptr;
	}

	assert(label >= 0 && label < LABEL_MAX);

	// 読み込み
	Load(label);

	return s_pTexture[label];
}
