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

//==================================================
// �O���錾
//==================================================
class CGauge2D;
class CObject2D;
class CPause;
class CTime;
class CScore;

//==================================================
// ��`
//==================================================
class CGame : public CMode
{
	/* ��` */
private:
	static const int MAX_TIME;		// ���Ԃ̍ő�l
	static const int PAUSE_TIME;	// �|�[�Y���o����l�ɂȂ�܂ł̎���
	
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
	void Reset();	// ���Z�b�g

public:
	CScore* GetScore();		// �X�R�A�̎擾
	CTime* GetTime();		// �^�C���̎擾

private:
	void Effect();	// �G�t�F�N�g

	/* �������o�ϐ��� */
private:
	CObject2D* m_pPauseBG;	// �|�[�Y�̔w�i
	CPause* m_pPause;		// �|�[�Y
	CTime* m_pTime;			// �^�C��
	CScore* m_pScore;		// �X�R�A
	CScore* m_pBestScore;	// �x�X�g�X�R�A
	CGauge2D* m_pGauge;		// �Q�[�W
	int m_time;	//�^�C��
	int m_nGageWave;
};

#endif // !_GAME_H_
