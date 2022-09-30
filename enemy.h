//**************************************************
// 
// enemy.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CEnemy : public CObject3D
{
	/* ��` */
public:
	enum EType
	{
		TYPE_NONE = -1,
		TYPE_HOMING = 0,	// �z�[�~���O
		TYPE_ROUNDTRIP,		// ����
		TYPE_WINDMILL,		// ����
		TYPE_SNAKE,			// ��
		TYPE_DIVISION,		// ����
		TYPE_ESCAPE,		// �e���瓦����
		TYPE_ROLLING,		// ��]
		TYPE_MAX
	};

	static const int STD_SCORE;		// �X�R�A�̕W���l
	static const int CREATE_TIME;	// ��������
	
private:
	static const float STD_SIZE;	// �T�C�Y�̕W���l

	/* ���ÓI�����o�֐��� */
public:
	static CEnemy* Create(CEnemy::EType type, const D3DXVECTOR3& pos);	// ����
	static void Collision(); // �����蔻��

	/* �������o�֐��� */
public:
	CEnemy();				// �f�t�H���g�R���X�g���N�^
	 ~CEnemy() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��
	virtual void Kill();	// �L�����ꂽ

public:
	int GetTime();	// �^�C���̎擾

private:
	EType GetType();	// ��ނ̎擾
	virtual void Set(const D3DXVECTOR3& pos) = 0;	// �ݒ�

	/* �������o�ϐ��� */
private:
	int m_time;		// �^�C��
	EType m_type;	// ���
};

#endif // !_ENEMT_H_
