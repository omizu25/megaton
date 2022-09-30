//**************************************************
// 
// object2D.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "object2D.h"
#include "application.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const DWORD CObject2D::FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
const int CObject2D::NUM_VERTEX = 4;
const int CObject2D::NUM_POLYGON = 2;

//--------------------------------------------------
// ����
//--------------------------------------------------
CObject2D* CObject2D::Create()
{
	CObject2D* pObject2D = nullptr;

	pObject2D = new CObject2D;

	if (pObject2D != nullptr)
	{// null�`�F�b�N
		pObject2D->Init();
	}

	return pObject2D;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CObject2D::CObject2D() : CObject(CObject::CATEGORY_2D),
	m_texture(CTexture::LABEL_NONE),
	m_pVtxBuff(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_alpha(0.0f),
	m_rot(0.0f),
	m_fade(false),
	m_inOut(false),
	m_draw(false)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObject2D::~CObject2D()
{
	assert(m_pVtxBuff == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CObject2D::Init()
{
	m_rot = 0.0f;
	m_alpha = 0.0f;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_texture = CTexture::LABEL_NONE;
	m_draw = true;
	m_fade = false;
	m_inOut = false;
	
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
void CObject2D::Uninit()
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
void CObject2D::Update()
{
	if (!m_fade)
	{// �t�F�[�h���Ȃ�
		return;
	}

	if (m_inOut)
	{// �t�F�[�h�C��
		m_alpha += 0.05f;

		if (m_alpha >= m_col.a)
		{// �ړI�̐F
			m_col.a = m_alpha;
			m_fade = false;
		}

		if (m_alpha >= 1.0f)
		{
			m_col.a = 1.0f;
			m_fade = false;
		}
	}
	else
	{// �t�F�[�h�A�E�g
		m_alpha -= 0.05f;

		if (m_alpha <= 0.0f)
		{
			m_col.a = 0.0f;
			m_fade = false;
		}
	}

	// �F�̐ݒ�
	SetCol(m_col);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CObject2D::Draw()
{
	if (!m_draw)
	{// �`�悵�Ȃ�
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	CTexture* pTexture = CApplication::GetInstanse()->GetTexture();
	 
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->Get(m_texture));

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`�悷��ŏ��̒��_�C���f�b�N�X
		NUM_POLYGON);			// �v���~�e�B�u(�|���S��)��
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void CObject2D::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;

	// ���_���̐ݒ�
	SetVtxPos();
}

//--------------------------------------------------
// �ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CObject2D::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// �T�C�Y�̐ݒ�
//--------------------------------------------------
void CObject2D::SetSize(const D3DXVECTOR3& size)
{
	m_size = size;

	// ���_���̐ݒ�
	SetVtxPos();
}

//--------------------------------------------------
// �T�C�Y�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CObject2D::GetSize() const
{
	return m_size;
}

//--------------------------------------------------
// �����̐ݒ�
//--------------------------------------------------
void CObject2D::SetRot(float rot)
{
	m_rot = rot;
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
const float CObject2D::GetRot() const
{
	return m_rot;
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void CObject2D::SetCol(const D3DXCOLOR& col)
{
	m_col = col;
	
	VERTEX_2D *pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (!m_fade)
	{// �t�F�[�h���Ȃ�
		// ���_�J���[�̐ݒ�
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;
	}
	else
	{// �t�F�[�h����
		D3DXCOLOR fadeCol = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_alpha);
		// ���_�J���[�̐ݒ�
		pVtx[0].col = fadeCol;
		pVtx[1].col = fadeCol;
		pVtx[2].col = fadeCol;
		pVtx[3].col = fadeCol;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �`�悷�邩�ǂ����̐ݒ�
//--------------------------------------------------
void CObject2D::SetDraw(bool draw)
{
	m_draw = draw;
}

//--------------------------------------------------
// �`�悷�邩�ǂ����̎擾
//--------------------------------------------------
bool CObject2D::GetDraw()
{
	return m_draw;
}

//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
void CObject2D::SetTexture(CTexture::ELabel texture)
{
	m_texture = texture;
}

//--------------------------------------------------
// �e�N�X�`�����W�̐ݒ�
//--------------------------------------------------
void CObject2D::SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2 v)
{
	VERTEX_2D *pVtx = nullptr;	// ���_���ւ̃|�C���^

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
// ���_���̐ݒ�
//--------------------------------------------------
void CObject2D::SetVtxPos()
{
	D3DXMATRIX mtx, mtxTrans;

	// ��]�̔��f
	D3DXMatrixRotationZ(&mtx, -m_rot);

	// �ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);
	
	D3DXVECTOR3 pVtxPos[NUM_VERTEX];

	float width = m_size.x * 0.5f;
	float height = m_size.y * 0.5f;

	// ���_���̐ݒ�
	pVtxPos[0] = D3DXVECTOR3(-width, -height, 0.0f);
	pVtxPos[1] = D3DXVECTOR3(+width, -height, 0.0f);
	pVtxPos[2] = D3DXVECTOR3(-width, +height, 0.0f);
	pVtxPos[3] = D3DXVECTOR3(+width, +height, 0.0f);

	VERTEX_2D* pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_VERTEX; i++)
	{// ���_���̐ݒ�
		D3DXVec3TransformCoord(&pVtx[i].pos, &pVtxPos[i], &mtx);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �t�F�[�h�̐ݒ�
//--------------------------------------------------
void CObject2D::SetFade(float alpha)
{
	m_alpha = alpha;

	if (m_alpha <= 0.0f)
	{// �t�F�[�h�C��
		if (m_alpha >= m_col.a)
		{// �ړI�̐F
			return;
		}

		m_inOut = true;
	}
	else
	{// �t�F�[�h�A�E�g
		m_inOut = false;
	}

	m_fade = true;

	// �F�̐ݒ�
	SetCol(m_col);
}
