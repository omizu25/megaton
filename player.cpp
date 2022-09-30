//**************************************************
// 
// player.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "player.h"
#include "application.h"
#include "utility.h"
#include "input.h"
#include "enemy.h"
#include "game.h"
#include "effect_manager.h"
#include "sound.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CPlayer::INVINCIBLE_TIME = 180;
const int CPlayer::RIGOR_TIME = 30;
const float CPlayer::STD_SIZE = 35.0f;
const float CPlayer::STD_MOVE = 6.0f;
const float CPlayer::STD_ROT = 0.1f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = nullptr;

	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{// null�`�F�b�N
		pPlayer->Init();
	}

	return pPlayer;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CPlayer::CPlayer() :
	m_time(0),
	m_rotDest(0.0f)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CPlayer::Init()
{
	m_time = 0;
	m_rotDest = 0;

	// ������
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject3D::TYPE_PLAYER);

	// �ʒu�̐ݒ�
	CObject3D::SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Player);

	// �p�[�e�B�N��
	CEffectManager::GetInstanse()->Player(CObject3D::GetPos());
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CPlayer::Uninit()
{
	// �p�[�e�B�N��
	CEffectManager::GetInstanse()->Player(CObject3D::GetPos());

	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CPlayer::Update()
{
	// ���G����
	InvincibleTime();

	// �ړ�
	Move();

	// ����
	Rot();

	// �����蔻��
	Collision();
	
	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CPlayer::Draw()
{
	// �`��
	CObject3D::Draw();
}

//--------------------------------------------------
// �ړ�
//--------------------------------------------------
void CPlayer::Move()
{
	if (m_time <= RIGOR_TIME)
	{// �d������
		return;
	}

	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CInput* pInput = CInput::GetKey();

	if (pInput->Press(CInput::KEY_PLAYER_LEFT))
	{// ���L�[�������ꂽ
		vec.x -= 1.0f;
	}
	
	if (pInput->Press(CInput::KEY_PLAYER_RIGHT))
	{// �E�L�[�������ꂽ
		vec.x += 1.0f;
	}
	
	if (pInput->Press(CInput::KEY_PLAYER_UP))
	{// ��L�[�������ꂽ
		vec.y += 1.0f;
	}
	
	if (pInput->Press(CInput::KEY_PLAYER_DOWN))
	{// ���L�[�������ꂽ
		vec.y -= 1.0f;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
	{// �ړ����ĂȂ�
		return;
	}

	// ���K��
	D3DXVec3Normalize(&vec, &vec);

	// �ړI�̌���
	m_rotDest = atan2f(vec.x, vec.y);

	// �p�x�̐��K��
	NormalizeAngle(&m_rotDest);

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �ړ�
	pos.x += vec.x * STD_MOVE;
	pos.y += vec.y * STD_MOVE;

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CPlayer::Rot()
{
	float angle = 0.0f;

	float rot = CObject3D::GetRot();

	angle = m_rotDest - rot;

	// �p�x�̐��K��
	NormalizeAngle(&angle);

	//�����E�������X�V (����������)
	rot += angle * STD_ROT;

	// �p�x�̐��K��
	NormalizeAngle(&rot);

	// �����̐ݒ�
	CObject3D::SetRot(rot);
}

//--------------------------------------------------
// ���G����
//--------------------------------------------------
void CPlayer::InvincibleTime()
{
	if (m_time >= INVINCIBLE_TIME)
	{// ���G���Ԃ͉߂���
		// �F�̐ݒ�
		CObject3D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		return;
	}

	m_time++;

	// �F�̎擾
	D3DXCOLOR col = CObject3D::GetCol();

	col.a = 1.0f - (CosCurve(m_time, 0.1f) * 0.9f);

	// �F�̐ݒ�
	CObject3D::SetCol(col);
}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CPlayer::Collision()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();
	float size = CObject3D::GetSize().x * 0.25f;

	CObject3D** pObject = (CObject3D**)GetMyObject(CObject::CATEGORY_3D);
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);
	D3DXVECTOR3 targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float targetSize = 0.0f;
	CEnemy* pEnemy = nullptr;

	for (int i = 0; i < objMax; i++)
	{
		if (pObject[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		if (!pObject[i]->GetCollision())
		{// �����蔻������Ȃ�
			continue;
		}

		CObject3D::EType type = pObject[i]->GetType();

		if (type != CObject3D::TYPE_ENEMY && type != CObject3D::TYPE_BODY)
		{// �w��̒l�ł͂Ȃ�
			continue;
		}

		targetPos = pObject[i]->GetPos();
		targetSize = pObject[i]->GetSize().x * 0.5f;

		if (CollisionCircle(pos, size, targetPos, targetSize))
		{// �����蔻��
			if (m_time < INVINCIBLE_TIME)
			{// ���G����
				if (type == CObject3D::TYPE_ENEMY)
				{// �G
					pEnemy = (CEnemy*)pObject[i];

					// �L��
					pEnemy->Kill();

					// �G�̉��
					pObject[i]->Release();
				}
				return;
			}

			// ���
			CObject::Release();

			// ���[�h�̕ύX
			CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_RESULT);

			// SE
			CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_GameOver);

			return;
		}
	}
}
