//=============================================================================
//
// �U��q�Q�[�W�N���X(pendulum.h)
// Author : �������l
// �T�v : �U��q�Q�[�W�������s��
//
//=============================================================================
#ifndef _PENDULUM_H_		// ���̃}�N����`������ĂȂ�������
#define _PENDULUM_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "texture.h"
#include <d3dx9.h>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;

//=============================================================================
// �U��q�Q�[�W�N���X
// Author : �������l
// �T�v : �U��q�Q�[�W�������s���N���X
//=============================================================================
class CPendulum : public CObject
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CPendulum *Create(void);				// �U��q�Q�[�W�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CPendulum(CObject::ECategory cat = CObject::CATEGORY_2D);
	~CPendulum() override;

	//--------------------------------------------------------------------
	// �I�[�o�[���C�h�֐�
	//--------------------------------------------------------------------
	void Init() override;										// ������
	void Uninit() override;										// �I��
	void Update() override;										// �X�V
	void Draw() override;										// �`��
	void SetPos(const D3DXVECTOR3 &pos);						// �ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot);						// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size);						// �傫���̃Z�b�^�[
	D3DXVECTOR3 GetPos() { return m_pos; }						// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot() { return m_rot; }						// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize() { return m_size; }					// �傫���̃Q�b�^�[
	void SetAction(bool bAction) { m_bAction = bAction; }		// �A�N�V�����̐ݒ�
	int GetScore() { return m_nScore; }							// �X�R�A�̎擾

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CObject2D		*pTarget;			// �^�[�Q�b�g
	CObject2D		*pPendulum;			// �U��q
	D3DXVECTOR3		m_pos;				// �ʒu
	D3DXVECTOR3		m_rot;				// ����
	D3DXVECTOR3		m_size;				// �傫��
	D3DXVECTOR3		m_movePendulum;		// �U��q�̈ړ���
	D3DXVECTOR2		m_wave;				// �g
	float			m_fDistance;		// �^�[�Q�b�g�Ƃ̋���
	float			m_fMaxDistance;		// �^�[�Q�b�g�Ƃ̋����̍ő�
	int				m_nScore;			// �X�R�A
	bool			m_bAction;			// �A�N�V�������s����
};

#endif



