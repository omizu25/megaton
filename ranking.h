//**************************************************
// 
// ranking.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RANKING_H_	//このマクロ定義がされてなかったら
#define _RANKING_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 前方宣言
//==================================================
class CRankingUI;
class CMenu;
class CScore;

//==================================================
// 定義
//==================================================
class CRanking : public CMode
{
	/* 定義 */
private:
	enum ESelect
	{
		SELECT_NONE = -1,	// 使用しない
		SELECT_RETRY = 0,	// リトライ
		SELECT_END,			// 終了
		SELECT_MAX
	};

	/* ↓メンバ関数↓ */
public:
	CRanking();				// デフォルトコンストラクタ
	~CRanking() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	void Effect();	// エフェクト

	/* メンバ変数 */
private:
	CRankingUI* m_pRanking;	// ランキング
	CScore* m_pScore;		// 今回のスコア
	CMenu* m_pMenu;			// メニュー
	int m_time;				// 時間
};

#endif // !_RANKING_H_
