//=============================================================================
//
// 2D�Q�[�W�N���X(gauge2D.h)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================
#ifndef _GAUGE2D_H_		// ���̃}�N����`������ĂȂ�������
#define _GAUGE2D_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "texture.h"
#include <d3dx9.h>

//=============================================================================
// 2D�I�u�W�F�N�g�N���X
// Author : �������l
// �T�v : 2D�I�u�W�F�N�g�������s���N���X
//=============================================================================
class CGauge2D : public CObject
{
public:
	// ���_�t�H�[�}�b�g
	const unsigned int	FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	//*****************************************************************************
	// �\���̒�`
	//*****************************************************************************
	// ���_�f�[�^
	struct VERTEX_2D
	{
		D3DXVECTOR3		pos;		// �ʒu
		float			rhw;		// rhw
		D3DCOLOR		col;		// �J���[
		D3DXVECTOR2		tex;		// �e�N�X�`�����W
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CGauge2D *Create(void);				// 2D�I�u�W�F�N�g�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CGauge2D(CObject::ECategory cat = CObject::CATEGORY_2D);
	~CGauge2D() override;

	//--------------------------------------------------------------------
	// �I�[�o�[���C�h�֐�
	//--------------------------------------------------------------------
	void Init() override;																	// ������
	void Uninit() override;																	// �I��
	void Update() override;																	// �X�V
	void Draw() override;																	// �`��
	void SetPos(const D3DXVECTOR3 &pos);													// �ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot);													// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size);													// �傫���̃Z�b�^�[
	D3DXVECTOR3 GetPos() { return m_pos; }													// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot() { return m_rot; }													// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize() { return m_size; }												// �傫���̃Q�b�^�[
	void SetCol(const D3DCOLOR &col);														// �F�̃Z�b�^�[
	void SetMaxNumber(const float fMaxNumber);												// ���l�̍ő�
	void SetNumber(const float fNumber) { m_fDestNumber = fNumber; }						// ���l�̐ݒ�
	void SetCoefficient(const float fCoefficient) { m_fCoefficient = fCoefficient; }		// �����W���̐ݒ�
	int GetNumber() { return (int)m_fDestNumber; }
	void SetChange(bool change, const D3DXVECTOR3 &size);

protected:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void SetVtx();															// ���_���W�Ȃǂ̐ݒ�
	void SetTexture(CTexture::ELabel texture);								// �e�N�X�`���̐ݒ�
	void SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2 v);				// �e�N�X�`�����W�̐ݒ�

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void SetGauge();

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;					// ���_�o�b�t�@
	D3DXVECTOR3						m_pos;						// �ʒu
	D3DXVECTOR3						m_rot;						// ����
	D3DXVECTOR3						m_size;						// �傫��
	D3DXVECTOR3						m_maxSize;					// �傫���ő�l
	D3DCOLOR						m_col;						// �J���[
	CTexture::ELabel				m_texture;					// �e�N�X�`���̗񋓌^
	float							m_fAngle;					// �Ίp���̊p�x
	float							m_fLength;					// �Ίp���̒���
	float							m_fAngleOrigin;				// ���Ƃ̑Ίp���̊p�x
	float							m_fLengthOrigin;			// ���ƑΊp���̒���
	float							m_fMaxNumber;				// ���l�̍ő吔
	float							m_fNumber;					// ���l
	float							m_fDestNumber;				// �ړI�̐��l
	float							m_fCoefficient;				// �����W��
	bool							m_change;
};

#endif



