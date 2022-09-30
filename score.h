//**************************************************
// 
// score.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _SCORE_H_	//���̃}�N����`������ĂȂ�������
#define _SCORE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "number_manager.h"

//==================================================
// �O���錾
//==================================================
class CObject2D;

//==================================================
// ��`
//==================================================
class CScore : public CNumberManager
{
	/* ����`�� */
public:
	static const float STD_WIDTH;	// ���̕W���l
	static const float STD_HEIGHT;	// �����̕W���l

	/* ���ÓI�����o�֐��� */
public:
	static CScore* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// ����

	/* �������o�֐��� */
public:
	CScore();	// �f�t�H���g�R���X�g���N�^
	~CScore();	// �f�X�g���N�^

public:
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size) override;	// ������
	void Uninit() override;		// �I��
	void Release() override;	// ���

public:
	void Add(int score);	// ���Z
	void Set(int value);	// �ݒ�
	void SetCol(const D3DXCOLOR& col);	// �F�̐ݒ�
	void DrawComma();	// �J���}�̕`��
	void Reset(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, bool draw);	// ���Z�b�g

	/* �������o�ϐ��� */
private:
	CObject2D* m_pComma[MAX_COMMA];	// �J���}
};

#endif // !_SCORE_H_
