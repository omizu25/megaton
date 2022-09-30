//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CTexture
{
	/* ↓定義↓ */
public:
	enum ELabel
	{
		LABEL_NONE = -1,	// 使用しない
		LABEL_Effect = 0,	// エフェクト
		LABEL_BG_1,			// 背景
		LABEL_Cursor,		// カーソル
		LABEL_Tutorial,		// チュートリアル

		/* ↓テキスト↓ */
		LABEL_Number,			// 数
		LABEL_Title,			// タイトル
		LABEL_Rank,				// 位
		LABEL_Comma,			// カンマ
		LABEL_Period,			// ピリオド
		LABEL_Pause,			// ポーズ
		LABEL_Resume,			// 再開
		LABEL_Restart,			// リスタート
		LABEL_End,				// 終了
		LABEL_Retry,			// リトライ

		/* ↓ハッカソン(2022/09/30)用↓ */
		LABEL_PressEnter,	// Enterを押してね
		LABEL_Score,		// スコア
		LABEL_Ranking,		// ランキング
		LABEL_GameBg,		// ゲーム画面の背景
		LABEL_NightSky,		// 夜空
		LABEL_Hanabitutu,	// 花火筒
		LABEL_Number_0to9,	// 0～9
		LABEL_Pien_yellow,	// ぴえん(黄)
		LABEL_Pien_white,	// ぴえん(白)
		LABEL_Target,		// ターゲット

		LABEL_MAX
	};

	static const char* FILE_NAME[];	// ファイルパス

	/* ↓メンバ関数↓ */
public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public:
	void LoadAll();				// 全ての読み込み
	void Load(ELabel label);	// 指定の読み込み
	void ReleaseAll();			// 全ての破棄
	void Release(ELabel label);	// 指定の破棄
	LPDIRECT3DTEXTURE9 Get(ELabel label);	// 情報の取得

	/* ↓メンバ変数↓ */
private:
	LPDIRECT3DTEXTURE9 s_pTexture[LABEL_MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
