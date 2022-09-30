//**************************************************
// 
// player.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PLAYER_H_	//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CPlayer : public CObject3D
{
	/* ��` */
private:
	static const int INVINCIBLE_TIME;	// ���G����
	static const int RIGOR_TIME;		// �d������
	static const float STD_MOVE;		// �ړ��ʂ̕W���l
	static const float STD_SIZE;		// �T�C�Y�̕W���l
	static const float STD_ROT;			// �����̕W���l

	/* ���ÓI�����o�֐��� */
public:
	static CPlayer* Create();	// ����

	/* �������o�֐��� */
public:
	CPlayer();				// �f�t�H���g�R���X�g���N�^
	 ~CPlayer() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void Move();			// �ړ�
	void Rot();				// ����
	void InvincibleTime();	// ���G����
	void Collision();		// �����蔻��

private:
	int m_time;			// �^�C��
	float m_rotDest;	// �ړI�̌���
};

#endif // !_OBJECT_H_
