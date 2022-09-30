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
		LABEL_Player = 0,			// �v���C���[
		LABEL_Bullet,				// �e
		LABEL_Effect,				// �G�t�F�N�g
		LABEL_BG,					// �w�i
		LABEL_Cursor,				// �J�[�\��
		LABEL_TutorialNormal,		// �ʏ�̃`���[�g���A��
		LABEL_TutorialSafetyArea,	// ���S�G���A�̃`���[�g���A��
		LABEL_TutorialDangerArea,	// �댯�G���A�̃`���[�g���A��
		LABEL_Circle,				// �~
		LABEL_Bom,					// �{��

		/* ���G�� */
		LABEL_Homing,			// �z�[�~���O
		LABEL_HomingEscape,		// ������z�[�~���O
		LABEL_HomingDivision,	// ����z�[�~���O
		LABEL_PaperAirplane,	// ����s�@
		LABEL_Windmill,			// ����
		LABEL_Snake_Body,		// �ւ̑�
		
		/* ���e�L�X�g�� */
		LABEL_Number,			// ��
		LABEL_Result,			// ���U���g
		LABEL_Title,			// �^�C�g��
		LABEL_Mul,				// �|����
		LABEL_Rank,				// ��
		LABEL_Rankig_Title,		// �^�C�g���p�̃����L���O
		LABEL_Rankig_Result,	// ���U���g�p�̃����L���O
		LABEL_NewScore,			// �V�����X�R�A
		LABEL_Comma,			// �J���}
		LABEL_Period,			// �s���I�h
		LABEL_Pause,			// �|�[�Y
		LABEL_Resume,			// �ĊJ
		LABEL_Restart,			// ���X�^�[�g
		LABEL_End,				// �I��
		LABEL_End_Ranking,		// �����L���O�p�̏I��
		LABEL_Retry,			// ���g���C
		LABEL_Normal,			// �ʏ�
		LABEL_SafetyArea,		// ���S�G���A
		LABEL_DangerArea,		// �댯�G���A
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
