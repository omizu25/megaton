//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CTexture
{
	/* ����`�� */
public:
	enum ELabel
	{
		LABEL_NONE = -1,	// �g�p���Ȃ�
		LABEL_Effect = 0,	// �G�t�F�N�g
		LABEL_BG_1,			// �w�i
		LABEL_Cursor,		// �J�[�\��
		LABEL_Tutorial,		// �`���[�g���A��

		/* ���e�L�X�g�� */
		LABEL_Number,			// ��
		LABEL_PressAny,			// PressAny
		LABEL_Title,			// �^�C�g��
		LABEL_Rank,				// ��
		LABEL_Rankig_Result,	// ���U���g�p�̃����L���O
		LABEL_NewScore,			// �V�����X�R�A
		LABEL_Comma,			// �J���}
		LABEL_Period,			// �s���I�h
		LABEL_Pause,			// �|�[�Y
		LABEL_Resume,			// �ĊJ
		LABEL_Restart,			// ���X�^�[�g
		LABEL_End,				// �I��
		LABEL_Retry,			// ���g���C
		LABEL_MAX
	};

	static const char* FILE_NAME[];	// �t�@�C���p�X

	/* �������o�֐��� */
public:
	CTexture();		// �f�t�H���g�R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

public:
	void LoadAll();				// �S�Ă̓ǂݍ���
	void Load(ELabel label);	// �w��̓ǂݍ���
	void ReleaseAll();			// �S�Ă̔j��
	void Release(ELabel label);	// �w��̔j��
	LPDIRECT3DTEXTURE9 Get(ELabel label);	// ���̎擾

	/* �������o�ϐ��� */
private:
	LPDIRECT3DTEXTURE9 s_pTexture[LABEL_MAX];	// �e�N�X�`���̏��
};

#endif // !_TEXTURE_H_
