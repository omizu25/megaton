//**************************************************
// 
// application.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "object.h"
#include "mode.h"
#include "texture.h"
#include "camera.h"
#include "bg.h"
#include "effect_manager.h"
#include <time.h>
#include <assert.h>

//==================================================
// ��`
//==================================================
const bool CApplication::FULL_SCREEN = true;

//==================================================
// �ÓI�����o�ϐ�
//==================================================
CApplication* CApplication::m_pApplication = nullptr;

//--------------------------------------------------
// �C���X�^���X�̎擾
//--------------------------------------------------
CApplication* CApplication::GetInstanse()
{
	if (m_pApplication == nullptr)
	{// null�`�F�b�N
		m_pApplication = new CApplication;
	}

	return m_pApplication;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CApplication::CApplication() :
	m_pRenderer(nullptr),
	m_pInput(nullptr),
	m_pSound(nullptr),
	m_pMode(nullptr),
	m_pTexture(nullptr),
	m_pCamera(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CApplication::~CApplication()
{
	assert(m_pMode == nullptr);
	assert(m_pCamera == nullptr);
	assert(m_pTexture == nullptr);
	assert(m_pSound == nullptr);
	assert(m_pInput == nullptr);
	assert(m_pRenderer == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pRenderer == nullptr)
	{// null�`�F�b�N
		m_pRenderer = new CRenderer;
	}

	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		if (FAILED(m_pRenderer->Init(hWnd, FULL_SCREEN)))
		{// ������
			return S_FALSE;
		}
	}

	if (m_pInput == nullptr)
	{// null�`�F�b�N
		m_pInput = CInput::Create();
	}

	if (m_pInput != nullptr)
	{// null�`�F�b�N
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{// ������
			return E_FAIL;
		}
	}

	if (m_pSound == nullptr)
	{// null�`�F�b�N
		m_pSound = new CSound;
	}

	if (m_pSound != nullptr)
	{// null�`�F�b�N
		if (FAILED(m_pSound->Init(hWnd)))
		{// ������
			return S_FALSE;
		}
	}

	if (m_pTexture == nullptr)
	{// null�`�F�b�N
		m_pTexture = new CTexture;
	}

	if (m_pCamera == nullptr)
	{// null�`�F�b�N
		m_pCamera = new CCamera;
	}

	if (m_pCamera != nullptr)
	{// null�`�F�b�N
		m_pCamera->Init();
	}

	// �����_���̏�����
	srand((unsigned int)time(NULL));

	// ����
	CObject::Create();

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	
	// �w�i�̐���
	CBG::Create(pos, size);

	if (m_pMode == nullptr)
	{// null�`�F�b�N
		m_pMode = CMode::Create(CMode::MODE_TITLE);
	}

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CApplication::Uninit()
{
	if (m_pMode != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	// �j��
	CObject::Delete();

	{
		CEffectManager* pEffect = CEffectManager::GetInstanse();
		pEffect->Release();
	}

	if (m_pCamera != nullptr)
	{// null�`�F�b�N
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pTexture != nullptr)
	{// null�`�F�b�N
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pSound != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pInput != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pInput->Uninit();
		m_pInput = nullptr;
	}

	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CApplication::Update()
{
	if (m_pInput != nullptr)
	{// null�`�F�b�N
		// �X�V
		m_pInput->Update();
	}

	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		// �X�V����
		m_pRenderer->Update();
	}

	if (m_pMode != nullptr)
	{// null�`�F�b�N
		m_pMode = m_pMode->Set();
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		// �`�揈��
		m_pRenderer->Draw();
	}
}

//--------------------------------------------------
// �f�o�C�X�̎擾
//--------------------------------------------------
LPDIRECT3DDEVICE9 CApplication::GetDevice()
{
	return m_pRenderer->GetDevice();
}

//--------------------------------------------------
// �T�E���h�̏��̎擾
//--------------------------------------------------
CSound* CApplication::GetSound()
{
	return m_pSound;
}

//--------------------------------------------------
// �Q�[���̏��̎擾
//--------------------------------------------------
CMode* CApplication::GetMode()
{
	return m_pMode;
}

//--------------------------------------------------
// �e�N�X�`���̏��̎擾
//--------------------------------------------------
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//--------------------------------------------------
// �J�����̏��̎擾
//--------------------------------------------------
CCamera* CApplication::GetCamera()
{
	return m_pCamera;
}
