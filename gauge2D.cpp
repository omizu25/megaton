//=============================================================================
//
// 2D�Q�[�W�N���X(gauge2D.cpp)
// Author : �������l
// �T�v : 2D�Q�[�W�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "gauge2D.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�Q�[�W�𐶐�����
//=============================================================================
CGauge2D * CGauge2D::Create(void)
{
	// �I�u�W�F�N�g�C���X�^���X
	CGauge2D *pGauge2D = nullptr;

	// �������̉��
	pGauge2D = new CGauge2D;

	if (pGauge2D != nullptr)
	{// ���l�̏�����
		pGauge2D->Init();
	}
	else
	{// �������̊m�ۂ��ł��Ȃ�����
		assert(false);
	}

	// �C���X�^���X��Ԃ�
	return pGauge2D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CGauge2D::CGauge2D(CObject::ECategory cat) : CObject(cat)
{
	m_pVtxBuff = nullptr;								// ���_�o�b�t�@
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
	m_maxSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �傫���ő�l
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			// �J���[
	m_fAngle = 0.0f;									// �Ίp���̊p�x
	m_fLength = 0.0f;									// �Ίp���̒���
	m_fAngleOrigin = 0.0f;								// ���Ƃ̑Ίp���̊p�x
	m_fLengthOrigin = 0.0f;								// ���ƑΊp���̒���
	m_fMaxNumber = 0.0f;								// ���l�̍ő吔
	m_fNumber = 0.0f;									// ���l
	m_fDestNumber = 0.0f;								// �ړI�̐��l
	m_fCoefficient = 0.0f;								// �����W��
	m_texture = CTexture::LABEL_NONE;					// �e�N�X�`���̗񋓌^
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CGauge2D::~CGauge2D()
{

}

//=============================================================================
// �|���S���̏�����
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
void CGauge2D::Init()
{// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,														// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �|���S�����̐ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);		// �傫��
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �J���[

	// ���_���W�̎Z�o
	SetVtx();

	// �F�̐ݒ�
	SetCol(m_col);

	// �e�N�X�`�����W�̐ݒ�
	SetVtxTex(D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
}

//=============================================================================
// �|���S���̏I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CGauge2D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{// ���_�o�b�t�@�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// �|���S���̍X�V
// Author : �������l
// �T�v : 2D�|���S���̍X�V���s��
//=============================================================================
void CGauge2D::Update()
{
	// ���l�̐ݒ�
	float fAdd = (m_fDestNumber - m_fNumber) * m_fCoefficient;

	m_fNumber += fAdd;

	if (fAdd > 0)
	{
		if (m_fNumber >= m_fDestNumber)
		{
			m_fNumber = m_fDestNumber;
		}
	}
	else if (fAdd < 0)
	{
		if (m_fNumber <= m_fDestNumber)
		{
			m_fNumber = m_fDestNumber;
		}
	}

	// �Q�[�W�̐ݒ�
	SetGauge();
}

//=============================================================================
// �|���S���̕`��
// Author : �������l
// �T�v : 2D�|���S���̕`����s��
//=============================================================================
void CGauge2D::Draw()
{// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture = CApplication::GetInstanse()->GetTexture();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->Get(m_texture));

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);
}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CGauge2D::SetPos(const D3DXVECTOR3 &pos)
{
	// �ʒu�̐ݒ�
	m_pos = pos;

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	// �F�̐ݒ�
	SetCol(m_col);
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CGauge2D::SetRot(const D3DXVECTOR3 &rot)
{
	// �����̐ݒ�
	m_rot = rot;

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	// �F�̐ݒ�
	SetCol(m_col);
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CGauge2D::SetSize(const D3DXVECTOR3 & size)
{
	// �傫���̐ݒ�
	m_maxSize = D3DXVECTOR3(size.x, size.y * 2.0f, 0.0f);

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	// �F�̐ݒ�
	SetCol(m_col);
}

//=============================================================================
// ���_���W�Ȃǂ̐ݒ�
// Author : �������l
// �T�v : 2D�|���S���̒��_���W�Arhw�A���_�J���[��ݒ肷��
//=============================================================================
void CGauge2D::SetVtx()
{
	//���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf((m_maxSize.x * m_maxSize.x) + (m_size.y * m_size.y)) / 2.0f;
	m_fLengthOrigin = sqrtf(m_maxSize.x * m_maxSize.x) / 2.0f;

	//�Ίp���̊p�x���Z�o
	m_fAngle = atan2f(m_maxSize.x, m_size.y);
	m_fAngleOrigin = atan2f(m_maxSize.x, 0.0f);

	// ���_����ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) *  m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) *  m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - (0 + m_fAngleOrigin)) * m_fLengthOrigin;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - (0 + m_fAngleOrigin)) * m_fLengthOrigin;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z - (0 - m_fAngleOrigin)) *  m_fLengthOrigin;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z - (0 - m_fAngleOrigin)) *  m_fLengthOrigin;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �F�̐ݒ�
// Author : �������l
// �T�v : ���_�J���[��ݒ肷��
//=============================================================================
void CGauge2D::SetCol(const D3DCOLOR &col)
{
	m_col = col;

	//���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
void CGauge2D::SetTexture(CTexture::ELabel texture)
{
	m_texture = texture;
}

//--------------------------------------------------
// �e�N�X�`�����W�̐ݒ�
//--------------------------------------------------
void CGauge2D::SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2 v)
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

//=============================================================================
// �Q�[�W�̐ݒ�
// Author : �������l
// �T�v : 2D�Q�[�W��ݒ肷��
//=============================================================================
void CGauge2D::SetGauge()
{
	// �傫���ɐ��l����
	m_size.y = (m_maxSize.y / m_fMaxNumber) * m_fNumber;

	// ���_���W�̐ݒ�
	SetVtx();
}

//=============================================================================
// ���l�̍ő�l�̐ݒ�
// Author : �������l
// �T�v : ���l�̍ő�l��ݒ肷��
//=============================================================================
void CGauge2D::SetMaxNumber(const float fMaxNumber)
{
	m_fMaxNumber = fMaxNumber;

	// �Q�[�W�̐ݒ�
	SetGauge();
}

