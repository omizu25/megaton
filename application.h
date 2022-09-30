//**************************************************
// 
// application.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _APPLICATION_H_	//���̃}�N����`������ĂȂ�������
#define _APPLICATION_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// �O���錾
//==================================================
class CRenderer;
class CInput;
class CSound;
class CMode;
class CTexture;
class CCamera;

//==================================================
// ��`
//==================================================
class CApplication
{
	/* ����`�� */
public:
	static const int SCREEN_WIDTH = 1280;	// �X�N���[���̕�
	static const int SCREEN_HEIGHT = 720;	// �X�N���[���̍���

private:
	static const bool FULL_SCREEN;	// �t���X�N���[���ɂ��邩�ǂ���

	/* ���ÓI�����o�֐��� */
public:
	static CApplication* GetInstanse();	// �C���X�^���X�̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static CApplication* m_pApplication;	// �����̃N���X

	/* �������o�֐��� */
private:
	CApplication();		// �f�t�H���g�R���X�g���N�^

public:
	~CApplication();	// �f�X�g���N�^

public:
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��
	LPDIRECT3DDEVICE9 GetDevice();	// �f�o�C�X�̎擾
	CSound* GetSound();				// �T�E���h�̏��̎擾
	CMode* GetMode();				// ���[�h�̏��̎擾
	CTexture* GetTexture();			// �e�N�X�`���̏��̎擾
	CCamera* GetCamera();			// �J�����̏��̎擾

	/* �������o�ϐ��� */
private:
	CRenderer* m_pRenderer;	// �����_���[�̏��
	CInput* m_pInput;		// ���͂̏��
	CSound* m_pSound;		// �T�E���h�̏��
	CMode* m_pMode;			// ���[�h�̏��
	CTexture* m_pTexture;	// �e�N�X�`���̏��
	CCamera* m_pCamera;		// �J�����̏��
};

#endif // !_APPLICATION_H_
