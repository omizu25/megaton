//**************************************************
// 
// number.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _NUMBER_H_	//���̃}�N����`������ĂȂ�������
#define _NUMBER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object2D.h"

//==================================================
// ��`
//==================================================
class CNumber : public CObject2D
{
	/* ����`�� */
private:
	static const int TEX_DIVISION;	// �e�N�X�`���̕�����

	/* ���ÓI�����o�֐��� */
public:
	static CNumber* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// ����

	/* �������o�֐��� */
public:
	CNumber();				// �f�t�H���g�R���X�g���N�^
	~CNumber() override;	// �f�X�g���N�^

public:
	void Init() override;		// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��
	void Change(int number);	// �ύX
};

#endif // !_NUMBER_H_
