//=============================================================================
//
// 入力処理 [input.h]
// Author1 : KOZUNA HIROHITO
// 
//	＜最後の行を見ることを推奨＞
//
//=============================================================================

#ifndef _INPUT_H_		//このマクロ定義がされなかったら
#define _INPUT_H_		//2重インクルード防止のマクロ定義

//----------------------------------------------------------------------------
//インクルードファイル
//----------------------------------------------------------------------------
#include "inputkeyboard.h"
#include "inputjoypad.h"
//----------------------------------------------------------------------------
//クラス定義
//----------------------------------------------------------------------------
class CInput
{
public:
	enum STAN_DART_INPUT_KEY
	{
		KEY_UP = 0,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_DECISION,
		KEY_PAUSE,
	};

	CInput();
	~CInput();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//入力処理全部の初期化
	void Uninit();									//入力処理全部の終了処理
	void Update();									//入力処理全部の更新処理
	static CInput *Create();
	static CInput *GetKey() { return m_Input; }
	bool Press(STAN_DART_INPUT_KEY key);
	bool Trigger(STAN_DART_INPUT_KEY key);
	bool Press(int nKey);
	bool Trigger(int nkey);
	bool Press(CInputJoyPad::JOYKEY Key);
	bool Trigger(CInputJoyPad::JOYKEY Key);

private:
	CInputKeyboard *m_pKeyboard;
	CInputJoyPad *m_pJoypad;
	static CInput *m_Input;
};

#endif

