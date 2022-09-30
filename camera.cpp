//**************************************************
// 
// camera.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "camera.h"
#include "application.h"
#include "game.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CCamera::MAX_NEAR = 10.0f;
const float CCamera::MAX_FAR = 2500.0f;
const float CCamera::MAX_DISTANCE = -500.0f;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CCamera::CCamera() :
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vecU(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	memset(m_mtxProj, 0, sizeof(m_mtxProj));
	memset(m_mtxView, 0, sizeof(m_mtxView));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CCamera::~CCamera()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CCamera::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posDest = m_pos;
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// �Œ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = m_rot;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CCamera::Uninit()
{
	
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CCamera::Update()
{
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CCamera::Set()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 pos = D3DXVECTOR3(m_pos.x, m_pos.y, MAX_DISTANCE);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&pos,
		&m_pos,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProj);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
	D3DXMatrixOrthoLH(&m_mtxProj,			// �v���W�F�N�V�����}�g���b�N�X
		(float)CApplication::SCREEN_WIDTH,	// ��
		(float)CApplication::SCREEN_HEIGHT,	// ����
		MAX_NEAR,							// �j�A
		MAX_FAR);							// �t�@�[
	
	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void CCamera::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

//--------------------------------------------------
// �ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CCamera::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// �v���W�F�N�V�����̎擾
//--------------------------------------------------
const D3DXMATRIX& CCamera::GetProj() const
{
	return m_mtxProj;
}

//--------------------------------------------------
// �r���[�̎擾
//--------------------------------------------------
const D3DXMATRIX& CCamera::GetView() const
{
	return m_mtxView;
}
