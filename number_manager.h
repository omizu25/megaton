//**************************************************
// 
// number_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _NUMBER_MANAGER_H_	//���̃}�N����`������ĂȂ�������
#define _NUMBER_MANAGER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// �O���錾
//==================================================
class CNumber;

//==================================================
// ��`
//==================================================
class CNumberManager
{
	/* ����`�� */
public:
	static const int MAX_DIGIT = 10;	// ���̍ő吔
	static const int MAX_COMMA = 3;		// �J���}�̍ő吔

	/* ���ÓI�����o�֐��� */
public:
	static CNumberManager* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int value);	// ����

	/* �������o�֐��� */
public:
	CNumberManager();	// �f�t�H���g�R���X�g���N�^
	~CNumberManager();	// �f�X�g���N�^

public:
	virtual void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// ������
	virtual void Uninit();	// �I��
	virtual void Release();	// ���

public:
	void Add(int value);	// ���Z
	void Set(int value);	// �ݒ�
	int Get();				// �擾
	void SetPos(const D3DXVECTOR3& pos);			// �ʒu�̐ݒ�
	void SetCol(const D3DXCOLOR& col);				// �F�̐ݒ�
	void SetDraw(bool draw);						// �`��̐ݒ�
	void SetZero(bool zero);						// �[���̐ݒ�
	void SetZeroDigit(int digit);					// �[���̌����̐ݒ�
	void SetInterval(int interval, float width);	// �Ԋu�̐ݒ�

private:
	void ZeroDraw();	// �[���̕`��
	void Change();		// �ύX

	/* �������o�ϐ��� */
private:
	CNumber* m_number[MAX_DIGIT];	// ��
	int m_value;		// �l
	int m_zeroDigit;	// �[����`�悷�錅��
	int m_interval;		// �Ԋu
	float m_width;		// �Ԋu�̕�
	bool m_zero;		// �[����`�悷�邩�ǂ���
};

#endif // !_NUMBER_MANAGER_H_
