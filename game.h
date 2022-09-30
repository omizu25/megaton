//**************************************************
// 
// game.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _GAME_H_	//���̃}�N����`������ĂȂ�������
#define _GAME_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"
#include "gage_manager.h"

//==================================================
// �O���錾
//==================================================
class CGageManager;
class CObject2D;
class CScore;

//==================================================
// ��`
//==================================================
class CGame : public CMode
{
	/* ��` */
private:
	
	/* �������o�֐��� */
public:
	CGame();			// �f�t�H���g�R���X�g���N�^
	~CGame() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:
	CScore* GetScore(CGageManager::GAGE_TYPE type);		// �X�R�A�̎擾
	void EndGame();		// �Q�[���ݒ�

	/* �������o�ϐ��� */
private:
	CScore* m_pScore[CGageManager::MAX_GAGETYPE];	// �X�R�A
	CGageManager* m_pGageManager;		// �Q�[�W�}�l�[�W���[
	int m_time;	//�^�C��
	bool m_end;	// �Q�[���I��������ǂ���
};

#endif // !_GAME_H_
