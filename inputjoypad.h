//=============================================================================
//
// ���͏��� [directjoypad.h]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _INPUTJOYPAD_H_		//���̃}�N����`������Ȃ�������
#define _INPUTJOYPAD_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//���C�u�����[�t�@�C���̃����N
//----------------------------------------------------------------------------
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v(�L�[�{�[�h)
#pragma comment(lib,"xinput.lib")//���͏����ɕK�v�i�W���C�p�b�g�j
#pragma comment(lib,"dxguid.lib")//DirectX�R���|�[�l���g�Ɏg�p

//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include <Windows.h>
#include <d3dx9.h>
#define	 DIRECTINPUT_VERSION (0x0800)	//�r���h���̌x���΍��p�}�N��(���̈ʒu���瓮�����Ȃ�)
#include <Xinput.h>						//�W���C�p�b�g����
#include <dinput.h>						//���͏����ɕK�v

//----------------------------------------------------------------------------
//�N���X��`
//----------------------------------------------------------------------------
class CInputJoyPad
{
private:
	static const int NUM_KEY_MAX = 256;	//�L�[�̍ő吔�i�L�[�{�[�h�j
	static const int PLAYER_MAX = 4;		//�v���C���[�̍ő�l��
	static const int STICK_MAX = 2;
public:

	//�L�[���(�W���C�p�b�h)
	enum JOYKEY
	{
		JOYKEY_UP = 0,				//��
		JOYKEY_DOWN,				//��
		JOYKEY_LEFT,				//��
		JOYKEY_RIGHT,				//�E
		JOYKEY_START,				//�X�^�[�g�{�^��
		JOYKEY_BACK,				//�o�b�N�{�^��
		JOYKEY_LEFT_THUMB,			//���X�e�B�b�N������
		JOYKEY_RIGHT_THUMB,			//�E�X�e�B�b�N������
		JOYKEY_LEFT_SHOULDER,		//L�P�{�^��
		JOYKEY_RIGHT_SHOULDER,		//R�P�{�^��
		JOYKEY_LEFT_TRIGGER,		//L�Q�g���K�[
		JOYKEY_RIGHT_TRIGGER,		//R�Q�g���K�[
		JOYKEY_A,					//A�{�^��
		JOYKEY_B,					//B�{�^��
		JOYKEY_X,					//X�{�^��
		JOYKEY_Y,					//Y�{�^��
		JOYKEY_MAX,
	};

	CInputJoyPad();
	~CInputJoyPad();
	HRESULT Init();		//������
	void Uninit();		//�I������
	void Update();		//�X�V����

	bool GetPress(JOYKEY Key, int nPlayer);					//�v���X����
	bool GetTrigger(JOYKEY Key, int nPlayer);				//�g���K�[����
	const D3DXVECTOR3& GetStick(bool RightLeft, int nPlayer);	//�X�e�B�b�N����
	int GetTriggerPedal(JOYKEY Key, int nPlayer);			//�g���K�[�y�_������
	bool GetStickPress(JOYKEY Key, bool RightLeft, int nPlayer);
	bool GetStickTrigger(JOYKEY Key, bool RightLeft, int nPlayer);
private:

	LPDIRECTINPUT8 m_pInput;							//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevJoypad;				//���̓f�o�C�X�i�L�[�{�[�h�i�R���g���[���[�p�͕ʂɍ��j�j�ւ̃|�C���^
										//�W���C�p�b�h
	XINPUT_STATE m_JoyKeyState[PLAYER_MAX];				//�W���C�p�b�g�̃v���X���
	XINPUT_STATE m_JoyKeyStateTrigger[PLAYER_MAX];		//�W���C�p�b�g�̃g���K�[���
	D3DXVECTOR3 m_JoyStickPos[PLAYER_MAX];				//�W���C�X�e�B�b�N�̌X��
	JOYKEY m_JoyStickOldPos[PLAYER_MAX][STICK_MAX];		//�W���C�X�e�B�b�N�̑O��̌X��
};
#endif