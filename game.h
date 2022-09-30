//**************************************************
// 
// game.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _GAME_H_	//このマクロ定義がされてなかったら
#define _GAME_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 前方宣言
//==================================================
class CGageManager;
class CObject2D;
class CScore;

//==================================================
// 定義
//==================================================
class CGame : public CMode
{
	/* 定義 */
private:
	
	/* ↓メンバ関数↓ */
public:
	CGame();			// デフォルトコンストラクタ
	~CGame() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	CScore* GetScore();		// スコアの取得
	void EndGame();		// ゲーム設定

	/* ↓メンバ変数↓ */
private:
	CScore* m_pScore;					// スコア
	CScore* m_pBestScore;				// ベストスコア
	CGageManager* m_pGageManager;		// ゲージマネージャー
	int m_time;	//タイム
	bool m_end;	// ゲーム終わったかどうか
};

#endif // !_GAME_H_
