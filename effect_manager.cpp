//**************************************************
// 
// effect_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "effect_manager.h"
#include "utility.h"
#include "effect.h"
#include "application.h"
#include "sound.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CEffectManager::MAX_PARTICLE = 500;
const int CEffectManager::MAX_PLAYER = 500;
const int CEffectManager::MAX_EXPLOSION = 50;
const int CEffectManager::HALF_EXPLOSION = MAX_EXPLOSION / 2;
const int CEffectManager::MAX_BULLET = 50;
const int CEffectManager::MAX_BOM = 500;
const float CEffectManager::PARTICLE_MOVE = 20.0f;
const float CEffectManager::PLAYER_MOVE = 50.0f;
const float CEffectManager::EXPLOSION_MOVE = 10.0f;
const float CEffectManager::BULLET_MOVE = 5.0f;
const float CEffectManager::BOM_MOVE = 70.0f;

//==================================================
// �ÓI�����o�ϐ�
//==================================================
CEffectManager* CEffectManager::m_pEffectManager = nullptr;

//--------------------------------------------------
// �C���X�^���X�̎擾
//--------------------------------------------------
CEffectManager* CEffectManager::GetInstanse()
{
	if (m_pEffectManager == nullptr)
	{// null�`�F�b�N
		m_pEffectManager = new CEffectManager;
	}

	return m_pEffectManager;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEffectManager::CEffectManager()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEffectManager::~CEffectManager()
{
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEffectManager::Release()
{
	if (m_pEffectManager != nullptr)
	{// null�`�F�b�N
		delete m_pEffectManager;
		m_pEffectManager = nullptr;
	}
}

//--------------------------------------------------
// �p�[�e�B�N��
//--------------------------------------------------
void CEffectManager::Particle(float move)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	col.r = FloatRandom(1.0f, 0.0f);
	col.g = FloatRandom(1.0f, 0.0f);
	col.b = FloatRandom(1.0f, 0.0f);

	D3DXCOLOR randomCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 randomMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 randomPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	float random = 0.0f;
	int max = (int)move * 30;

	for (int i = 0; i < max; i++)
	{
		rot = (D3DX_PI * 2.0f) / max * i;

		// �p�x�̐��K��
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(100.0f, 50.0f);

		random = FloatRandom(move, move * 0.1f);

		randomMove.x = sinf(rot) * random;
		randomMove.y = cosf(rot) * random;

		randomCol.r = col.r + FloatRandom(0.25f, -0.25f);
		randomCol.g = col.g + FloatRandom(0.25f, -0.25f);
		randomCol.b = col.b + FloatRandom(0.25f, -0.25f);

		// ����
		CEffect::Create(pos + randomPos, randomMove, randomCol);
	}

	D3DXCOLOR a = col;
	a.r = col.r + FloatRandom(col.r, 0.0f);
	a.g = col.g + FloatRandom(col.g, 0.0f);
	a.b = col.b + FloatRandom(col.b, 0.0f);

	for (int i = 0; i < (max / 2); i++)
	{
		rot = (D3DX_PI * 2.0f) / (max / 2) * i;

		// �p�x�̐��K��
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(100.0f, 50.0f);

		random = FloatRandom(move * 0.5f, move * 0.1f);

		randomMove.x = sinf(rot) * random;
		randomMove.y = cosf(rot) * random;

		randomCol.r = a.r + FloatRandom(0.25f, -0.25f);
		randomCol.g = a.g + FloatRandom(0.25f, -0.25f);
		randomCol.b = a.b + FloatRandom(0.25f, -0.25f);

		// ����
		CEffect* pEffect = CEffect::Create(pos, randomMove, randomCol);

		// �F�̌��Z�����Ȃ�
		pEffect->SetColSubtract(false);
	}
}

//--------------------------------------------------
// �v���C���[
//--------------------------------------------------
void CEffectManager::Player(const D3DXVECTOR3& pos)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 randomPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	float random = 0.0f;

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_PLAYER * i;

		// �p�x�̐��K��
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(100.0f, 50.0f);

		random = FloatRandom(PLAYER_MOVE, PLAYER_MOVE * 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = 1.0f + FloatRandom(0.0f, -0.25f);
		col.g = 1.0f + FloatRandom(0.0f, -0.25f);
		col.b = 1.0f + FloatRandom(0.0f, -0.25f);

		// ����
		CEffect::Create(pos + randomPos, move, col);
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CEffectManager::Explosion(const D3DXVECTOR3& pos)
{
	float red = FloatRandom(1.0f, 0.0f);
	float green = FloatRandom(1.0f, 0.0f);
	float blue = FloatRandom(1.0f, 0.0f);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 randomPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	float random = 0.0f;

	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_EXPLOSION * i;

		// �p�x�̐��K��
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(75.0f, 50.0f);

		random = FloatRandom(EXPLOSION_MOVE, EXPLOSION_MOVE * 0.5f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = red + FloatRandom(0.25f, -0.25f); 
		col.g = green + FloatRandom(0.25f, -0.25f);
		col.b = blue + FloatRandom(0.25f, -0.25f);

		// ����
		CEffect::Create(pos + randomPos, move, col);
	}

	for (int i = 0; i < HALF_EXPLOSION; i++)
	{
		rot = (D3DX_PI * 2.0f) / HALF_EXPLOSION * i;

		// �p�x�̐��K��
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(75.0f, 50.0f);

		random = FloatRandom(EXPLOSION_MOVE, EXPLOSION_MOVE * 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = red + FloatRandom(0.25f, -0.25f);
		col.g = green + FloatRandom(0.25f, -0.25f);
		col.b = blue + FloatRandom(0.25f, -0.25f);

		// ����
		CEffect::Create(pos + randomPos, move, col);
	}

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Explosion);
}

//--------------------------------------------------
// �e
//--------------------------------------------------
void CEffectManager::Bullet(const D3DXVECTOR3& pos)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 0.2f, 0.1f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	float random = 0.0f;

	for (int i = 0; i < MAX_BULLET; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_BULLET * i;

		// �p�x�̐��K��
		NormalizeAngle(&rot);

		random = FloatRandom(BULLET_MOVE, BULLET_MOVE * 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = 0.5f + FloatRandom(0.1f, -0.1f);

		// ����
		CEffect::Create(pos, move, col);
	}
}

//--------------------------------------------------
// �{��
//--------------------------------------------------
void CEffectManager::Bom(const D3DXVECTOR3& pos)
{
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	CEffect* pEffect = nullptr;

	for (int i = 0; i < MAX_BOM; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_BOM * i;

		// �p�x�̐��K��
		NormalizeAngle(&rot);

		{// �O��
			move.x = sinf(rot) * BOM_MOVE;
			move.y = cosf(rot) * BOM_MOVE;

			// ����
			pEffect = CEffect::Create(pos, move, col);
		}

		{// ����
			move.x = sinf(rot) * (BOM_MOVE * 0.75f);
			move.y = cosf(rot) * (BOM_MOVE * 0.75f);

			// ����
			pEffect = CEffect::Create(pos, move, col);
		}
	}

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Bom);
}

//--------------------------------------------------
// �w�i
//--------------------------------------------------
void CEffectManager::BG()
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	col.r = FloatRandom(1.0f, 0.0f);
	col.g = FloatRandom(1.0f, 0.0f);
	col.b = FloatRandom(1.0f, 0.0f);

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 randomPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR randomCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
	float rot = 0.0f;
	float random = 0.0f;
	CEffect* pEffect = nullptr;

	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_PARTICLE * i;

		// �p�x�̐��K��
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(100.0f, 50.0f);

		random = FloatRandom(PARTICLE_MOVE, PARTICLE_MOVE * 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		randomCol.r = col.r + FloatRandom(0.25f, -0.25f);
		randomCol.g = col.g + FloatRandom(0.25f, -0.25f);
		randomCol.b = col.b + FloatRandom(0.25f, -0.25f);

		// ����
		pEffect = CEffect::Create(pos + randomPos, move, randomCol);

		// �F�̌��Z�����Ȃ�
		pEffect->SetColSubtract(false);
	}
}
