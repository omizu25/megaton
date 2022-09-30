//**************************************************
// 
// pause.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PAUSE_H_	//���̃}�N����`������ĂȂ�������
#define _PAUSE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �O���錾
//==================================================
class CObject2D;
class CMenu;

//==================================================
// ��`
//==================================================
class CPause
{
	/* ����`�� */
private:
	enum ESelect
	{
		SELECT_NONE = -1,	// �g�p���Ȃ�
		SELECT_RESUME = 0,	// �ĊJ
		SELECT_RESTART,		// �n�߂���
		SELECT_END,			// �I��
		SELECT_MAX
	};

	/* ���ÓI�����o�֐��� */
public:
	static CPause* Create();	// ����

	/* �������o�֐��� */
public:
	CPause();	// �f�t�H���g�R���X�g���N�^
	~CPause();	// �f�X�g���N�^

public:
	void Init();	// ������
	void Uninit();	// �I��
	void Release();	// ���
	bool Update();	// �X�V

private:
	CObject2D* m_pPause;	// �|�[�Y
	CMenu* m_pMenu;			// ���j���[
};

#endif // !_PAUSE_H_
