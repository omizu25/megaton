//**************************************************
// 
// locus.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _LOCUS_H_	//���̃}�N����`������ĂȂ�������
#define _LOCUS_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CLocus : public CObject3D
{
	/* ����`�� */
private:
	static const float STD_SIZE;	// �T�C�Y�̕W���l

	/* ���ÓI�����o�֐��� */
public:
	static CLocus* Create();	// ����

	/* �������o�֐��� */
public:
	CLocus();			// �f�t�H���g�R���X�g���N�^
	~CLocus() override;	// �f�X�g���N�^

public:
	void Init() override;															// ������
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��
	void SetSpeed(const float fSpeed) { m_fSpeed = fSpeed; }						// ���x�̐ݒ�
	void SetWaveSpeed(const float fWaveSpeed) { m_fWaveSpeed = fWaveSpeed; }		// �g�̉��Z�ʂ̐ݒ�
	void SetWaveWidth(const float fWaveWidth) { m_fWaveWidth = fWaveWidth; }		// �g�̔{���̐ݒ�
	void SetLife(const int nLife) { m_nLife = nLife; }								// �̗͂̐ݒ�

	/* �������o�ϐ��� */
private:
	D3DXVECTOR3		m_move;				// �ړ���
	float			m_fSpeed;			// ���x
	float			m_fWave;			// �g
	float			m_fWaveSpeed;		// �g�̉��Z��
	float			m_fWaveWidth;		// �g�̔{��
	int				m_nLife;			// ����
};

#endif // !_LOCUS_H_
