//**************************************************
// 
// object2D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT2D_H_	//���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"
#include "texture.h"
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CObject2D : public CObject
{
	/* ����`�� */
private:
	struct VERTEX_2D
	{// ���_�f�[�^
		D3DXVECTOR3 pos;
		float rhw;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	};

	static const DWORD FVF_VERTEX_2D;	// ���_�t�H�[�}�b�g
	static const int NUM_VERTEX;		// ���_�̐�
	static const int NUM_POLYGON;		// �|���S���̐�

	/* ���ÓI�����o�֐��� */
public:
	static CObject2D* Create();	// ����

	/* �������o�֐��� */
public:
	CObject2D();			// �f�t�H���g�R���X�g���N�^
	~CObject2D() override;	// �f�X�g���N�^

public: 
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:
	void SetPos(const D3DXVECTOR3& pos);		// �ʒu�̐ݒ�
	const D3DXVECTOR3& GetPos() const;			// �ʒu�̎擾
	void SetSize(const D3DXVECTOR3& size);		// �T�C�Y�̐ݒ�
	const D3DXVECTOR3& GetSize() const;			// �T�C�Y�̎擾
	void SetRot(float rot);						// �����̐ݒ�
	const float GetRot() const;					// �����̎擾
	void SetCol(const D3DXCOLOR& col);			// �F�̐ݒ�
	void SetDraw(bool draw);					// �`�悷�邩�ǂ����̐ݒ�
	bool GetDraw();								// �`�悷�邩�ǂ����̎擾
	void SetTexture(CTexture::ELabel texture);	// �e�N�X�`���̐ݒ�
	void SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2 v);	// �e�N�X�`�����W�̐ݒ�
	void SetFade(float alpha);	// �t�F�[�h�̐ݒ�

private:
	void SetVtxPos();	// ���_���̐ݒ�

	/* �������o�ϐ��� */
private:
	CTexture::ELabel m_texture;	// �e�N�X�`���̗񋓌^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_size;	// �T�C�Y
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXCOLOR m_col;	// �F
	float m_alpha;		// �A���t�@
	float m_rot;		// ����
	bool m_fade;		// �t�F�[�h
	bool m_inOut;		// �t�F�[�h���C���E�A�E�g
	bool m_draw;		// �`�悷�邩�ǂ���
};

#endif // !_OBJECT2D_H_
