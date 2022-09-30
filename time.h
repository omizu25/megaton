//**************************************************
// 
// time.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TIME_H_	//���̃}�N����`������ĂȂ�������
#define _TIME_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

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
class CTime : public CNumberManager
{
	/* ����`�� */
public:
	static const float STD_WIDTH;	// ���̕W���l
	static const float STD_HEIGHT;	// �����̕W���l

	/* ���ÓI�����o�֐��� */
public:
	static CTime* Create(const D3DXVECTOR3& pos, int start, int end);	// ����

	/* �������o�֐��� */
public:
	CTime();	// �f�t�H���g�R���X�g���N�^
	~CTime();	// �f�X�g���N�^

public:
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size) override;	// ������
	void Uninit() override;		// �I��
	void Release() override;	// ���

public:
	void Update();	// �X�V
	void Restart();	// �ĊJ

	/* �������o�ϐ��� */
private:
	CObject2D* m_pPeriod;	// �s���I�h
	int m_start;	// �J�n
	int m_elapsed;	// �o��
	int m_end;		// �I��
};

#endif // !_TIME_H_
