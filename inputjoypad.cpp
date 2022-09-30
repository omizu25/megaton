//=============================================================================
//
// ���͏��� [inputjoypad.cpp]
// Author1 : HAMADA RYUUGA
// input.h���Q�Ƃ𐄏�
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "inputjoypad.h"

//*************************************************************************************
//�R���X�g���N�^
//*************************************************************************************
CInputJoyPad::CInputJoyPad()
{
	m_pInput = nullptr;
	m_pDevJoypad = nullptr;
}

//*************************************************************************************
//�f�X�g���N�^
//*************************************************************************************
CInputJoyPad::~CInputJoyPad()
{
}

//*************************************************************************************
//������
//*************************************************************************************
HRESULT CInputJoyPad::Init()
{
	//XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		//�������[�̃N���A
		memset(&m_JoyKeyState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_JoyKeyStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));
	}
	return S_OK;
}

//*************************************************************************************
//�I������
//*************************************************************************************
void CInputJoyPad::Uninit(void)
{
	//XInput�̃X�e�[�g��ݒ�i�����ɂ���j
	XInputEnable(false);
}

//*************************************************************************************
//�X�V����
//*************************************************************************************
void CInputJoyPad::Update(void)
{
	XINPUT_STATE JoyKeyState[PLAYER_MAX];		//�W���C�p�b�h���͏��

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		//�W���C�p�b�h�̏�Ԃ��擾
		if (XInputGetState(nCnt, &JoyKeyState[nCnt]) == ERROR_SUCCESS)
		{
			m_JoyKeyStateTrigger[nCnt].Gamepad.wButtons
				= ~m_JoyKeyState[nCnt].Gamepad.wButtons
				& JoyKeyState[nCnt].Gamepad.wButtons; //�g���K�[����ۑ�
			m_JoyKeyState[nCnt] = JoyKeyState[nCnt];  //�v���X����
		}
	}
}

//�v���X����
bool CInputJoyPad::GetPress(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
//�g���K�[����
bool CInputJoyPad::GetTrigger(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//�X�e�B�b�N�v���X����
const D3DXVECTOR3& CInputJoyPad::GetStick(bool RightLeft, int nPlayer)
{
	if (RightLeft)
	{// �E
		m_JoyStickPos[nPlayer] = D3DXVECTOR3(m_JoyKeyState[nPlayer].Gamepad.sThumbRX / 32767.0f, -m_JoyKeyState[nPlayer].Gamepad.sThumbRY / 32767.0f, 0.0f);
	}
	else
	{// ��
		m_JoyStickPos[nPlayer] = D3DXVECTOR3(m_JoyKeyState[nPlayer].Gamepad.sThumbLX / 32767.0f, -m_JoyKeyState[nPlayer].Gamepad.sThumbLY / 32767.0f, 0.0f);
	}

	return m_JoyStickPos[nPlayer];
}

//�g���K�[�y�_������
int  CInputJoyPad::GetTriggerPedal(JOYKEY Key, int nPlayer)
{
	int nJoypadTriggerPedal = 0;
	switch (Key)
	{
	case JOYKEY_LEFT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState[nPlayer].Gamepad.bLeftTrigger;
		break;
	case JOYKEY_RIGHT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState[nPlayer].Gamepad.bRightTrigger;
		break;
	}

	return nJoypadTriggerPedal;
}

//�W���C�p�b�h�X�e�B�b�N�v���X�W����
bool CInputJoyPad::GetStickPress(JOYKEY Key, bool RightLeft, int nPlayer)
{
	D3DXVECTOR3 pos = GetStick(RightLeft, nPlayer);	//���݂̌X���̎擾
	pos.y *= -1.0f;//Y�𕪂���₷�����邽�߂Ɂ{�|�𔽓]

	if (pos.y > 0.5f
		&& JOYKEY_UP == Key)
	{
		return true;
	}
	else if (pos.x > 0.5f
		&& JOYKEY_RIGHT == Key)
	{
		return true;
	}
	else if (pos.y < -0.5f
		&& JOYKEY_DOWN == Key)
	{
		return true;
	}
	else if (pos.x < -0.5f
		&& JOYKEY_LEFT == Key)
	{
		return true;
	}
	return false;
}

//�W���C�p�b�h�X�e�B�b�N�g���K�[�W����
bool CInputJoyPad::GetStickTrigger(JOYKEY Key, bool RightLeft, int nPlayer)
{
	if (GetStickPress(Key, RightLeft, nPlayer)
		&& Key != m_JoyStickOldPos[nPlayer][RightLeft])
	{
		m_JoyStickOldPos[nPlayer][RightLeft] = Key;
		return true;
	}
	else if (GetStickPress(Key, RightLeft, nPlayer)
		&& Key == m_JoyStickOldPos[nPlayer][RightLeft])
	{
		return false;
	}
	else if (!GetStickPress(Key, RightLeft, nPlayer)
		&& Key != m_JoyStickOldPos[nPlayer][RightLeft])
	{
		return false;
	}

	m_JoyStickOldPos[nPlayer][RightLeft] = JOYKEY_MAX;
	return false;
}
