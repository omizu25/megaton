//**************************************************
// 
// tutorial.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TUTORIAL_H_	//���̃}�N����`������ĂȂ�������
#define _TUTORIAL_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"

//==================================================
// ��`
//==================================================
class CTutorial : public CMode
{
	/* �������o�֐��� */
public:
	CTutorial();			// �f�t�H���g�R���X�g���N�^
	~CTutorial() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void Effect();	// �G�t�F�N�g

	/* �����o�ϐ� */
private:
	int m_time;	// ����
};

#endif // !_TUTORIAL_H_
