//**************************************************
// 
// object3D.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "object3D.h"
#include "application.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const DWORD CObject3D::FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
const int CObject3D::NUM_VERTEX = 4;
const int CObject3D::NUM_POLYGON = 2;

//--------------------------------------------------
// ����
//--------------------------------------------------
CObject3D* CObject3D::Create()
{
	CObject3D* pObject3D = nullptr;

	pObject3D = new CObject3D;

	if (pObject3D != nullptr)
	{// null�`�F�b�N
		pObject3D->Init();
	}

	return pObject3D;
}

//--------------------------------------------------
// ���݂��邩�ǂ���
//--------------------------------------------------
bool CObject3D::Exist(EType type)
{
	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);

	for (int i = 0; i < objMax; i++)
	{
		if (pObject[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		if (pObject[i]->m_type == type)
		{// �w��̒l�Ɠ���
			return true;
		}
	}

	return false;
}

//--------------------------------------------------
// �w��̃^�C�v�̑S�Ẳ��
//--------------------------------------------------
void CObject3D::ReleaseAll(EType type)
{
	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);

	for (int i = 0; i < objMax; i++)
	{
		if (pObject[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		if (pObject[i]->m_type == type)
		{// �w��̒l�Ɠ���
			// ���
			pObject[i]->Release();
		}
	}
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CObject3D::CObject3D(CObject::ECategory cat) : CObject(cat),
	m_type(TYPE_NONE),
	m_texture(CTexture::LABEL_NONE),
	m_rot(0.0f),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_pVtxBuff(nullptr),
	m_collision(false)
{
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObject3D::~CObject3D()
{
	assert(m_pVtxBuff == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CObject3D::Init()
{
	m_rot = 0.0f;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_texture = CTexture::LABEL_NONE;
	m_collision = true;

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CObject3D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{// ���_�o�b�t�@�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CObject3D::Update()
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CObject3D::Draw()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture* pTexture = CApplication::GetInstanse()->GetTexture();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->Get(m_texture));

	D3DXMATRIX mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�̔��f
	D3DXMatrixRotationZ(&m_mtxWorld, -m_rot);

	// �ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, 0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`�悷��ŏ��̒��_�C���f�b�N�X
		NUM_POLYGON);			// �v���~�e�B�u(�|���S��)��
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void CObject3D::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

//--------------------------------------------------
// �ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CObject3D::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// �T�C�Y�̐ݒ�
//--------------------------------------------------
void CObject3D::SetSize(const D3DXVECTOR3& size)
{
	m_size = size;

	VERTEX_3D *pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float width = m_size.x * 0.5f;
	float height = m_size.y * 0.5f;

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-width, +height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+width, +height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-width, -height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+width, -height, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �T�C�Y�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CObject3D::GetSize() const
{
	return m_size;
}

//--------------------------------------------------
// �����̐ݒ�
//--------------------------------------------------
void CObject3D::SetRot(float rot)
{
	m_rot = rot;
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
const float CObject3D::GetRot() const
{
	return m_rot;
}

//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
void CObject3D::SetTexture(CTexture::ELabel texture)
{
	m_texture = texture;
}

//--------------------------------------------------
// �e�N�X�`�����W�̐ݒ�
//--------------------------------------------------
void CObject3D::SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2 v)
{
	VERTEX_3D *pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(u.x, v.x);
	pVtx[1].tex = D3DXVECTOR2(u.y, v.x);
	pVtx[2].tex = D3DXVECTOR2(u.x, v.y);
	pVtx[3].tex = D3DXVECTOR2(u.y, v.y);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void CObject3D::SetCol(const D3DXCOLOR& col)
{
	m_col = col;

	VERTEX_3D *pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �F�̎擾
//--------------------------------------------------
const D3DXCOLOR& CObject3D::GetCol() const
{
	return m_col;
}

//--------------------------------------------------
// ��ނ̐ݒ�
//--------------------------------------------------
void CObject3D::SetType(EType type)
{
	m_type = type;
}

//--------------------------------------------------
// ��ނ̎擾
//--------------------------------------------------
const CObject3D::EType CObject3D::GetType() const
{
	return m_type;
}

//--------------------------------------------------
// �����蔻������邩�ǂ����̐ݒ�
//--------------------------------------------------
void CObject3D::SetCollision(bool collision)
{
	m_collision = collision;
}

//--------------------------------------------------
// �����蔻������邩�ǂ����̎擾
//--------------------------------------------------
const bool CObject3D::GetCollision() const
{
	return m_collision;
}
