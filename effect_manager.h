//**************************************************
// 
// effect_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EFFECT_MANAGER_H_	//���̃}�N����`������ĂȂ�������
#define _EFFECT_MANAGER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CEffectManager
{
	/* ��` */
private:
	static const int MAX_PARTICLE;		// �p�[�e�B�N���̍ő吔
	static const int MAX_PLAYER;		// �v���C���[�̍ő吔
	static const int MAX_EXPLOSION;		// �����̍ő吔
	static const int HALF_EXPLOSION;	// �����̍ő吔�̔���
	static const int MAX_BULLET;		// �e�̍ő吔
	static const int MAX_BOM;			// �{���̍ő吔
	static const float PARTICLE_MOVE;	// �p�[�e�B�N���̈ړ���
	static const float PLAYER_MOVE;		// �v���C���[�̈ړ���
	static const float EXPLOSION_MOVE;	// �����̈ړ���
	static const float BULLET_MOVE;		// �e�̈ړ���
	static const float BOM_MOVE;		// �{���̈ړ���

	/* ���ÓI�����o�֐��� */
public:
	static CEffectManager* GetInstanse();	// �C���X�^���X�̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static CEffectManager* m_pEffectManager;	// �����̃N���X

	/* �������o�֐��� */
private:
	CEffectManager();	// �f�t�H���g�R���X�g���N�^

public:
	~CEffectManager();	// �f�X�g���N�^

public:
	void Release();	// ���
	void Particle(const D3DXCOLOR& col);	// �p�[�e�B�N��
	void Player(const D3DXVECTOR3& pos);	// �v���C���[
	void Explosion(const D3DXVECTOR3& pos);	// ����
	void Bullet(const D3DXVECTOR3& pos);	// �e
	void Bom(const D3DXVECTOR3& pos);		// �{��
	void BG();	// �w�i

	/* �������o�ϐ��� */
private:
};

#endif // !_EFFECT_MANAGER_H_
