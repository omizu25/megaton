//**************************************************
// 
// mode.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MODE_H_	//���̃}�N����`������ĂȂ�������
#define _MODE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CMode
{
	/* ����`�� */
public:
	enum EMode
	{
		MODE_NONE = -1,
		MODE_TITLE = 0,	// �^�C�g��
		MODE_TUTORIAL,	// �`���[�g���A��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_RANKING,	// �����L���O
		MODE_MAX,
	};

	static const int FADE_TIME;	// �t�F�[�h�̎���

	/* ���ÓI�����o�֐��� */
public:
	static CMode* Create(EMode mode);	// ����

	/* �������o�֐��� */
public:
	CMode() = delete;	// �f�t�H���g�R���X�g���N�^
	CMode(EMode mode);	// �R���X�g���N�^
	virtual ~CMode();	// �f�X�g���N�^

public:
	virtual void Init() = 0;	// ������
	virtual void Uninit() = 0;	// �I��
	virtual void Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��

public:
	CMode* Set();				// �ݒ�
	EMode Get();				// �擾
	void Change(EMode mode);	// �ύX

	 /* �������o�ϐ��� */
private:
	EMode m_mode;		// ���[�h
	EMode m_modeNext;	// ���̃��[�h
};

#endif // !_MODE_H_
