//**************************************************
// 
// instancing.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _INSTANCING_H_	//���̃}�N����`������ĂȂ�������
#define _INSTANCING_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CInstancing
{
	/* ��` */
private:
	struct Vtx
	{// ���_�o�b�t�@
		float x, y;	// pos
		float u, v;	// tex
	};

	/* ���ÓI�����o�֐��� */
public:
	static CInstancing* Create();	// ����

	/* �������o�֐��� */
public:
	CInstancing();	// �f�t�H���g�R���X�g���N�^
	~CInstancing();	// �f�X�g���N�^

public:
	void Init();	// ������
	void Uninit();	// �I��
	void Draw();	// �`��

	/* �������o�ϐ��� */
private:
	IDirect3DVertexBuffer9* m_pVtxBuff;		// ���_�o�b�t�@
	IDirect3DVertexBuffer9* m_pPosBuff;		// �ʒu�̃o�b�t�@
	IDirect3DVertexBuffer9* m_pColBuff;		// �F�̃o�b�t�@
	IDirect3DVertexBuffer9* m_pSizeBuff;	// �T�C�Y�̃o�b�t�@
	IDirect3DVertexDeclaration9* m_pDecl;	// �v�f�̐錾
	IDirect3DIndexBuffer9* m_pIndexBuff;	// �C���f�b�N�X�o�b�t�@
	ID3DXEffect* m_pShader;					// �V�F�[�_�[
};

#endif // !_INSTANCING_H_
