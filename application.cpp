//**************************************************
// 
// application.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
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
#include "fade.h"
#include <time.h>
#include <assert.h>

//==================================================
// 定義
//==================================================
const bool CApplication::FULL_SCREEN = true;

//==================================================
// 静的メンバ変数
//==================================================
CApplication* CApplication::m_pApplication = nullptr;

//--------------------------------------------------
// インスタンスの取得
//--------------------------------------------------
CApplication* CApplication::GetInstanse()
{
	if (m_pApplication == nullptr)
	{// nullチェック
		m_pApplication = new CApplication;
	}

	return m_pApplication;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CApplication::CApplication() :
	m_pRenderer(nullptr),
	m_pInput(nullptr),
	m_pSound(nullptr),
	m_pMode(nullptr),
	m_pTexture(nullptr),
	m_pCamera(nullptr),
	m_pFade(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CApplication::~CApplication()
{
	assert(m_pMode == nullptr);
	assert(m_pCamera == nullptr);
	assert(m_pTexture == nullptr);
	assert(m_pSound == nullptr);
	assert(m_pInput == nullptr);
	assert(m_pRenderer == nullptr);
	assert(m_pFade == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pRenderer == nullptr)
	{// nullチェック
		m_pRenderer = new CRenderer;
	}

	if (m_pRenderer != nullptr)
	{// nullチェック
		if (FAILED(m_pRenderer->Init(hWnd, FULL_SCREEN)))
		{// 初期化
			return S_FALSE;
		}
	}

	if (m_pInput == nullptr)
	{// nullチェック
		m_pInput = CInput::Create();
	}

	if (m_pInput != nullptr)
	{// nullチェック
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{// 初期化
			return E_FAIL;
		}
	}

	if (m_pSound == nullptr)
	{// nullチェック
		m_pSound = new CSound;
	}

	if (m_pSound != nullptr)
	{// nullチェック
		if (FAILED(m_pSound->Init(hWnd)))
		{// 初期化
			return S_FALSE;
		}
	}

	if (m_pTexture == nullptr)
	{// nullチェック
		m_pTexture = new CTexture;
	}

	if (m_pCamera == nullptr)
	{// nullチェック
		m_pCamera = new CCamera;
	}

	if (m_pCamera != nullptr)
	{// nullチェック
		m_pCamera->Init();
	}

	// ランダムの初期化
	srand((unsigned int)time(NULL));

	// 生成
	CObject::Create();

	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create();
	}

	if (m_pMode == nullptr)
	{// nullチェック
		m_pMode = CMode::Create(CMode::MODE_TITLE);
	}

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CApplication::Uninit()
{
	if (m_pMode != nullptr)
	{// nullチェック
		// 終了
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	m_pFade->Release();
	m_pFade = nullptr;

	// 破棄
	CObject::Delete();


	{
		CEffectManager* pEffect = CEffectManager::GetInstanse();
		pEffect->Release();
	}

	if (m_pCamera != nullptr)
	{// nullチェック
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pTexture != nullptr)
	{// nullチェック
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pSound != nullptr)
	{// nullチェック
		// 終了
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pInput != nullptr)
	{// nullチェック
		// 終了
		m_pInput->Uninit();
		m_pInput = nullptr;
	}

	if (m_pRenderer != nullptr)
	{// nullチェック
		// 終了
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CApplication::Update()
{
	if (m_pInput != nullptr)
	{// nullチェック
		// 更新
		m_pInput->Update();
	}

	if (m_pRenderer != nullptr)
	{// nullチェック
		// 更新処理
		m_pRenderer->Update();
	}

	if (m_pMode != nullptr)
	{// nullチェック
		m_pMode = m_pMode->Set();
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{// nullチェック
		// 描画処理
		m_pRenderer->Draw();
	}
}

//--------------------------------------------------
// デバイスの取得
//--------------------------------------------------
LPDIRECT3DDEVICE9 CApplication::GetDevice()
{
	return m_pRenderer->GetDevice();
}

//--------------------------------------------------
// サウンドの情報の取得
//--------------------------------------------------
CSound* CApplication::GetSound()
{
	return m_pSound;
}

//--------------------------------------------------
// ゲームの情報の取得
//--------------------------------------------------
CMode* CApplication::GetMode()
{
	return m_pMode;
}

//--------------------------------------------------
// テクスチャの情報の取得
//--------------------------------------------------
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//--------------------------------------------------
// カメラの情報の取得
//--------------------------------------------------
CCamera* CApplication::GetCamera()
{
	return m_pCamera;
}
