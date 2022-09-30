//=============================================================================
//
// ���͏��� [input.cpp]
// Author1 : KOZUNA HIROHITO
// input.h���Q�Ƃ𐄏�
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "input.h"

CInput *CInput::m_Input = nullptr;

//*************************************************************************************
//�R���X�g���N�^
//*************************************************************************************
CInput::CInput()
{
	m_pKeyboard = nullptr;
	m_pJoypad = nullptr;
}

//*************************************************************************************
//�f�X�g���N�^
//*************************************************************************************
CInput::~CInput()
{
}

//*************************************************************************************
//������
//*************************************************************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_pKeyboard = new CInputKeyboard;

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	m_pJoypad = new CInputJoyPad;

	if (FAILED(m_pJoypad->Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//*************************************************************************************
//�I������
//*************************************************************************************
void CInput::Uninit()
{
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	if (m_pJoypad != nullptr)
	{
		m_pJoypad->Uninit();
		delete m_pJoypad;
		m_pJoypad = nullptr;
	}

	if (m_Input != nullptr)
	{
		delete m_Input;
		m_Input = nullptr;
	}
}

//*************************************************************************************
//�X�V����
//*************************************************************************************
void CInput::Update()
{
	m_pKeyboard->Update();
	m_pJoypad->Update();
}

//*************************************************************************************
//�C���v�b�g�̐���
//*************************************************************************************
CInput *CInput::Create()
{
	m_Input = new CInput;
	return m_Input;
}

//*************************************************************************************
//�v���X����
//*************************************************************************************
bool CInput::Press(STAN_DART_INPUT_KEY key)
{
	switch (key)
	{
	case CInput::KEY_UP:
		if (m_pKeyboard->GetPress(DIK_W)
			|| m_pKeyboard->GetPress(DIK_UP)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_UP,0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_UP, true, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_UP, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_DOWN:
		if (m_pKeyboard->GetPress(DIK_S)
			|| m_pKeyboard->GetPress(DIK_DOWN)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_DOWN, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_DOWN, true, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_DOWN, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_LEFT:
		if (m_pKeyboard->GetPress(DIK_A)
			|| m_pKeyboard->GetPress(DIK_LEFT)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_LEFT, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_LEFT, true, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_LEFT, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_RIGHT:
		if (m_pKeyboard->GetPress(DIK_D)
			|| m_pKeyboard->GetPress(DIK_RIGHT)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_RIGHT, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_RIGHT, true, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_RIGHT, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_PLAYER_UP:
		if (m_pKeyboard->GetPress(DIK_W)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_UP, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_UP, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_PLAYER_DOWN:
		if (m_pKeyboard->GetPress(DIK_S)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_DOWN, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_DOWN, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_PLAYER_LEFT:
		if (m_pKeyboard->GetPress(DIK_A)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_LEFT, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_LEFT, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_PLAYER_RIGHT:
		if (m_pKeyboard->GetPress(DIK_D)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_RIGHT, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_RIGHT, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_BULLET_UP:
		if (m_pKeyboard->GetPress(DIK_UP)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_Y, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_UP, true, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_BULLET_DOWN:
		if (m_pKeyboard->GetPress(DIK_DOWN)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_A, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_DOWN, true, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_BULLET_LEFT:
		if (m_pKeyboard->GetPress(DIK_LEFT)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_X, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_LEFT, true, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_BULLET_RIGHT:
		if (m_pKeyboard->GetPress(DIK_RIGHT)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_B, 0)
			|| m_pJoypad->GetStickPress(CInputJoyPad::JOYKEY_RIGHT, true, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_BOM:
		if (m_pKeyboard->GetPress(DIK_SPACE)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_LEFT_SHOULDER, 0)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_RIGHT_SHOULDER, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_DECISION:
		if (m_pKeyboard->GetPress(DIK_RETURN)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_A , 0)
			|| m_pJoypad->GetPress(CInputJoyPad::JOYKEY_LEFT_SHOULDER, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_PAUSE:
		if (m_pKeyboard->GetPress(DIK_P)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_START, 0))
		{
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

//*************************************************************************************
//�g���K�[����
//*************************************************************************************
bool CInput::Trigger(STAN_DART_INPUT_KEY key)
{
	switch (key)
	{
	case CInput::KEY_UP:
		if (m_pKeyboard->GetTrigger(DIK_W)
			|| m_pKeyboard->GetTrigger(DIK_UP)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_UP, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_UP, true, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_UP, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_DOWN:
		if (m_pKeyboard->GetTrigger(DIK_S)
			|| m_pKeyboard->GetTrigger(DIK_DOWN)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_DOWN, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_DOWN, true, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_DOWN, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_LEFT:
		if (m_pKeyboard->GetTrigger(DIK_A)
			|| m_pKeyboard->GetTrigger(DIK_LEFT)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_LEFT, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_LEFT, true, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_LEFT, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_RIGHT:
		if (m_pKeyboard->GetTrigger(DIK_D)
			|| m_pKeyboard->GetTrigger(DIK_RIGHT)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_RIGHT, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_RIGHT, true, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_RIGHT, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_PLAYER_UP:
		if (m_pKeyboard->GetTrigger(DIK_W)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_UP, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_UP, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_PLAYER_DOWN:
		if (m_pKeyboard->GetTrigger(DIK_S)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_DOWN, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_DOWN, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_PLAYER_LEFT:
		if (m_pKeyboard->GetTrigger(DIK_A)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_LEFT, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_LEFT, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_PLAYER_RIGHT:
		if (m_pKeyboard->GetTrigger(DIK_D)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_RIGHT, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_RIGHT, false, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_BULLET_UP:
		if (m_pKeyboard->GetTrigger(DIK_UP)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_Y, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_UP, true, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_BULLET_DOWN:
		if (m_pKeyboard->GetTrigger(DIK_DOWN)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_A, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_DOWN, true, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_BULLET_LEFT:
		if (m_pKeyboard->GetTrigger(DIK_LEFT)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_X, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_LEFT, true, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_BULLET_RIGHT:
		if (m_pKeyboard->GetTrigger(DIK_RIGHT)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_B, 0)
			|| m_pJoypad->GetStickTrigger(CInputJoyPad::JOYKEY_RIGHT, true, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_BOM:
		if (m_pKeyboard->GetTrigger(DIK_SPACE)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_LEFT_SHOULDER, 0)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_RIGHT_SHOULDER, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_DECISION:
		if (m_pKeyboard->GetTrigger(DIK_RETURN)
			|| m_pKeyboard->GetTrigger(DIK_SPACE)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_A, 0)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_B, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_PAUSE:
		if (m_pKeyboard->GetTrigger(DIK_P)
			|| m_pJoypad->GetTrigger(CInputJoyPad::JOYKEY_START, 0))
		{
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

//*************************************************************************************
//�v���X����(�L�[�{�[�h)
//*************************************************************************************
bool CInput::Press(int nKey)
{
	return m_pKeyboard->GetPress(nKey);
}

//*************************************************************************************
//�g���K�[����(�L�[�{�[�h)
//*************************************************************************************
bool CInput::Trigger(int nkey)
{
	return m_pKeyboard->GetTrigger(nkey);
}

//*************************************************************************************
//�v���X����(�W���C�p�b�h)
//*************************************************************************************
bool CInput::Press(CInputJoyPad::JOYKEY key)
{
	return m_pJoypad->GetPress(key, 0);
}

//*************************************************************************************
//�g���K�[����(�W���C�p�b�h)
//*************************************************************************************
bool CInput::Trigger(CInputJoyPad::JOYKEY key)
{
	return m_pJoypad->GetTrigger(key, 0);
}
