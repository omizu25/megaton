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
class CPause;
class CTime;
class CScore;

//==================================================
// 定義
//==================================================
class CGame : public CMode
{
	/* 定義 */
private:
	static const int MAX_TIME;		// 時間の最大値
	static const int PAUSE_TIME;	// ポーズが出来る様になるまでの時間
	
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
	void Reset();	// リセット

public:
	CScore* GetScore();		// スコアの取得
	CTime* GetTime();		// タイムの取得

private:
	void Effect();	// エフェクト

	/* ↓メンバ変数↓ */
private:
	CObject2D* m_pPauseBG;				// ポーズの背景
	CPause* m_pPause;					// ポーズ
	CTime* m_pTime;						// タイム
	CScore* m_pScore;					// スコア
	CScore* m_pBestScore;				// ベストスコア
	CGageManager* m_pGageManager;		// ゲージマネージャー
	int m_time;	//タイム
};

#endif // !_GAME_H_
