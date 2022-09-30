//**************************************************
// 
// result.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RESULT_H_	//���̃}�N����`������ĂȂ�������
#define _RESULT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"

//==================================================
// �O���錾
//==================================================
class CRankingUI;
class CScore;
class CMenu;

//==================================================
// ��`
//==================================================
class CResult : public CMode
{
	/* ��` */
private:
	enum ESelect
	{
		SELECT_NONE = -1,	// �g�p���Ȃ�
		SELECT_RETRY = 0,	// ���g���C
		SELECT_END,			// �I��
		SELECT_MAX
	};

	/* �������o�֐��� */
public:
	CResult();				// �f�t�H���g�R���X�g���N�^
	~CResult() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void Effect();	// �G�t�F�N�g

	/* �����o�ϐ� */
private:
	CRankingUI* m_pRanking;	// �����L���O
	CScore* m_pScore;		// ����̃X�R�A
	CMenu* m_pMenu;			// ���j���[
	int m_time;				// ����
};

#endif // !_RESULT_H_
