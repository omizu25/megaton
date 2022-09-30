//**************************************************
// 
// bg.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _BG_H_	//���̃}�N����`������ĂȂ�������
#define _BG_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CBG : public CObject3D
{
	/* ���ÓI�����o�֐��� */
public:
	static CBG* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// ����

	/* �������o�֐��� */
public:
	CBG();				// �f�t�H���g�R���X�g���N�^
	~CBG() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��
};

#endif // !_BG_H_
