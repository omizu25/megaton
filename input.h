//=============================================================================
//
// ���͏��� [input.h]
// Author1 : KOZUNA HIROHITO
// 
//	���Ō�̍s�����邱�Ƃ𐄏���
//
//=============================================================================

#ifndef _INPUT_H_		//���̃}�N����`������Ȃ�������
#define _INPUT_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include "inputkeyboard.h"
#include "inputjoypad.h"
//----------------------------------------------------------------------------
//�N���X��`
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
		KEY_PLAYER_UP,
		KEY_PLAYER_DOWN,
		KEY_PLAYER_LEFT,
		KEY_PLAYER_RIGHT,
		KEY_BULLET_UP,
		KEY_BULLET_DOWN,
		KEY_BULLET_LEFT,
		KEY_BULLET_RIGHT,
		KEY_BOM,
		KEY_DECISION,
		KEY_PAUSE,
	};

	CInput();
	~CInput();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//���͏����S���̏�����
	void Uninit();									//���͏����S���̏I������
	void Update();									//���͏����S���̍X�V����
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

