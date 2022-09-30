//**************************************************
// 
// enemy.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy.h"
#include "effect_manager.h"
#include "application.h"
#include "game.h"
#include "score.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CEnemy::STD_SCORE = 100;
const int CEnemy::CREATE_TIME = 30;
const float CEnemy::STD_SIZE = 35.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CEnemy* CEnemy::Create(CEnemy::EType type, const D3DXVECTOR3& pos)
{
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case CEnemy::TYPE_HOMING:
		break;

	case CEnemy::TYPE_ROUNDTRIP:
		break;

	case CEnemy::TYPE_WINDMILL:
		break;

	case CEnemy::TYPE_SNAKE:
		break;

	case CEnemy::TYPE_DIVISION:
		break;

	case CEnemy::TYPE_ESCAPE:
		break;

	case CEnemy::TYPE_ROLLING:
		break;

	case CEnemy::TYPE_MAX:
	case CEnemy::TYPE_NONE:
	default:
		assert(false);
		break;
	}

	if (pEnemy != nullptr)
	{// null�`�F�b�N
		pEnemy->Init();
		pEnemy->Set(pos);
		pEnemy->m_type = type;
	}

	return pEnemy;
}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CEnemy::Collision()
{
	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CObject3D** pTarget = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CEnemy* pEnemy = nullptr;
	CObject3D::EType type = CObject3D::TYPE_NONE;
	CEnemy::EType typeObject = CEnemy::TYPE_NONE;
	CEnemy::EType typeTarget = CEnemy::TYPE_NONE;
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float width = STD_SIZE * 0.35f;

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

		type = pObject[i]->GetType();

		if (type != CObject3D::TYPE_ENEMY)
		{// �G�l�~�[�ł͂Ȃ�
			continue;
		}

		pEnemy = (CEnemy*)pObject[i];

		typeObject = pEnemy->GetType();
		
		if (typeObject != CEnemy::TYPE_HOMING
			&& typeObject != CEnemy::TYPE_DIVISION
			&& typeObject != CEnemy::TYPE_ESCAPE)
		{// �w��̃G�l�~�[�ł͂Ȃ�
			continue;
		}

		pos = pObject[i]->GetPos();

		for (int j = i + 1; j < objMax; j++)
		{
			if (pTarget[j] == nullptr)
			{// null�`�F�b�N
				continue;
			}

			if (!pTarget[j]->GetCollision())
			{// �����蔻������Ȃ�
				continue;
			}

			type = pTarget[j]->GetType();

			if (type != CObject3D::TYPE_ENEMY)
			{// �G�l�~�[�ł͂Ȃ�
				continue;
			}

			pEnemy = (CEnemy*)pTarget[j];

			typeTarget = pEnemy->GetType();

			if (typeObject != typeTarget)
			{// �����G�l�~�[�ł͂Ȃ�
				continue;
			}

			targetPos = pTarget[j]->GetPos();

			if (CollisionArea(pos, width, &targetPos, width))
			{// ��������
				// �ʒu�̐ݒ�
				pTarget[j]->SetPos(targetPos);
			}
		}
	}
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemy::CEnemy() :
	m_time(0),
	m_type(TYPE_NONE)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemy::~CEnemy()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEnemy::Init()
{
	m_time = 0;
	m_type = TYPE_NONE;

	// ������
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject3D::TYPE_ENEMY);

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemy::Uninit()
{
	// ����
	CEffectManager::GetInstanse()->Explosion(CObject3D::GetPos());

	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemy::Update()
{
	m_time++;

	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEnemy::Draw()
{
	// �`��
	CObject3D::Draw();
}

//--------------------------------------------------
// �L�����ꂽ
//--------------------------------------------------
void CEnemy::Kill()
{
}

//--------------------------------------------------
// �^�C���̎擾
//--------------------------------------------------
int CEnemy::GetTime()
{
	return m_time;
}

//--------------------------------------------------
// ��ނ̎擾
//--------------------------------------------------
CEnemy::EType CEnemy::GetType()
{
	return m_type;
}
