//**************************************************
// 
// renderer.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "renderer.h"
#include "main.h"
#include "application.h"
#include "object.h"
#include "effect.h"
#include "mode.h"
#include <assert.h>
#include <tchar.h> // _T

//==================================================
// ���C�u�����[�����N
//==================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CRenderer::CRenderer() : 
#ifdef _DEBUG
	m_pFont(nullptr),
#endif // _DEBUG
	m_pD3D(nullptr),
	m_pD3DDevice(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CRenderer::~CRenderer()
{
	assert(m_pD3D == nullptr);
	assert(m_pD3DDevice == nullptr);
	assert(m_pFont == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{
		// �������s
		return E_FAIL;
	}

	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{// ���݂̃f�B�X�v���C���[�h���擾
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = CApplication::SCREEN_WIDTH;			// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = CApplication::SCREEN_HEIGHT;		// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;									// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`��ƒ��_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))))
	{// �������s
		return E_FAIL;
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �摜�����������Ă��Y��ɂ���
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �摜��傫�����Ă��Y��ɂ���
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`����U�̌J��Ԃ�����ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`����V�̌J��Ԃ�����ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �|���S���ƃe�N�X�`���̃����܂���
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �P�ڂ̐F�̓e�N�X�`���̐F
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�ڂ̐F�͌��݂̐F

	// ���C�g�𖳌��ɂ���
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif // _DEBUG

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CRenderer::Uninit()
{
#ifdef _DEBUG
	if (m_pFont != nullptr)
	{// �f�o�b�O���\���p�t�H���g�̔j��
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG

	if (m_pD3DDevice != nullptr)
	{// �f�o�C�X�̔j��
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	if (m_pD3D != nullptr)
	{// Direct3D�I�u�W�F�N�g�̔j��
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CRenderer::Update()
{
	// ���[�h�̍X�V
	CApplication::GetInstanse()->GetMode()->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CRenderer::Draw()
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{// Direct3D�ɂ��`��̊J�n

		// ���[�h�̕`��
		CApplication::GetInstanse()->GetMode()->Draw();

#ifdef _DEBUG
		// FPS�\��
		DrawFPS();
#endif // _DEBUG

		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//--------------------------------------------------
// �f�o�C�X�̎擾
//--------------------------------------------------
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;
};

#ifdef _DEBUG
//--------------------------------------------------
// FPS�\��
//--------------------------------------------------
void CRenderer::DrawFPS()
{
	RECT rect = { 0, 0, CApplication::SCREEN_WIDTH, CApplication::SCREEN_HEIGHT };
	TCHAR str[256];
	int length = 0;

	wsprintf(&str[length], _T("FPS : %d\n"), GetFPS());
	length = (int)strlen(str);

	wsprintf(&str[length], _T("�I�u�W�F�N�g�̑��� : %d\n"), CObject::GetNumAll() - CEffect::GetNumAll());
	length = (int)strlen(str);

	wsprintf(&str[length], _T("�G�t�F�N�g�̑��� : %d\n"), CEffect::GetNumAll());
	length = (int)strlen(str);

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0x00));
}
#endif // _DEBUG
