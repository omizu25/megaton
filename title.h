//**************************************************
// 
// title.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TITLE_H_	//���̃}�N����`������ĂȂ�������
#define _TITLE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"

//==================================================
// �O���錾
//==================================================
class CMenu;

//==================================================
// ��`
//==================================================
class CTitle : public CMode
{
	/* ��` */
private:
	enum ESelect
	{
		SELECT_NONE = -1,
		SELECT_NORMAL = 0,	// �ʏ�
		SELECT_SAFETY_AREA,	// ���S�G���A
		SELECT_DANGER_AREA,	// �댯�G���A
		SELECT_RANKING,		// �����L���O
		SELECT_MAX
	};

	/* �������o�֐��� */
public:
	CTitle();			// �f�t�H���g�R���X�g���N�^
	~CTitle() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void Effect();	// �G�t�F�N�g

	/* �����o�ϐ� */
private:
	CMenu* m_pMenu;		// ���j���[
	D3DXCOLOR m_col;	// �F
	int m_time;			// ����
	int m_partCnt;		// �p�[�e�B�N���J�E���^�[
};

#endif // !_TITLE_H_
