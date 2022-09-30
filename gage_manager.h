//=============================================================================
//
// ゲージマネージャークラス(gage_manager.h)
// Author : 唐�ｱ結斗
// 概要 : ゲージマネージャー生成を行う
//
//=============================================================================
#ifndef _GAGE_MANAGER_H_		// このマクロ定義がされてなかったら
#define _GAGE_MANAGER_H_		// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"
#include "texture.h"
#include <d3dx9.h>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CGauge2D;
class CPendulum;
class CTwinCircle;

//=============================================================================
// ゲージマネージャークラス
// Author : 唐�ｱ結斗
// 概要 : ゲージマネージャー生成を行うクラス
//=============================================================================
class CGageManager : public CObject
{
public:
	//--------------------------------------------------------------------
	// ゲージの種類
	//--------------------------------------------------------------------
	enum GAGE_TYPE
	{
		GAGE_POLE = 0,		// 棒
		GAGE_PENDULUM,		// 振り子
		GAGE_TWINCIRCLE,	// サークル
		MAX_GAGETYPE		// 最大数
	};

	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CGageManager *Create(void);				// 振り子ゲージの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CGageManager(CObject::ECategory cat = CObject::CATEGORY_2D);
	~CGageManager() override;

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

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	CGauge2D		*m_pGauge2D;		// ターゲット
	CPendulum		*m_pPendulum;		// 振り子
	CTwinCircle		*m_pTwinCircle;		// サークル
	D3DXVECTOR3		m_pos;				// 位置
	D3DXVECTOR3		m_rot;				// 向き
	D3DXVECTOR3		m_size;				// 大きさ
	GAGE_TYPE		m_type;				// タイプ
	int				m_nScore;			// スコア
	int				m_nCntGage;			// ゲージのカウント
	bool			m_bKeyPress;		// ボタンを押したか
};

#endif




