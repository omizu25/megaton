//**************************************************
// 
// ranking.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RANKING_H_	//���̃}�N����`������ĂȂ�������
#define _RANKING_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"

//==================================================
// �O���錾
//==================================================
class CRankingUI;
class CMenu;
class CScore;

//==================================================
// ��`
//==================================================
class CRanking : public CMode
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
	CRanking();				// �f�t�H���g�R���X�g���N�^
	~CRanking() override;	// �f�X�g���N�^

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

#endif // !_RANKING_H_
