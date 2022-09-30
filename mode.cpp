//**************************************************
// 
// mode.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const int CMode::FADE_TIME = 10;

//--------------------------------------------------
// ����
//--------------------------------------------------
CMode* CMode::Create(EMode mode)
{
	CMode* pMode = nullptr;

	switch (mode)
	{
	case CMode::MODE_TITLE:
		pMode = new CTitle;
		break;

	case CMode::MODE_TUTORIAL:
		pMode = new CTutorial;
		break;

	case CMode::MODE_GAME:
		pMode = new CGame;
		break;

	case CMode::MODE_RESULT:
		pMode = new CResult;
		break;

	case CMode::MODE_RANKING:
		pMode = new CRanking;
		break;

	case CMode::MODE_NONE:
	case CMode::MODE_MAX:
	default:
		assert(false);
		break;
	}

	if (pMode != nullptr)
	{// null�`�F�b�N
		pMode->Init();
	}

	return pMode;
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CMode::CMode(EMode mode) :
	m_modeNext(MODE_NONE)
{
	m_mode = mode;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CMode::~CMode()
{
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
CMode* CMode::Set()
{
	if (m_modeNext == MODE_NONE)
	{// ���̃��[�h�����܂��ĂȂ�
		return this;
	}

	m_mode = m_modeNext;	// ���݂̉��(���[�h)��؂�ւ���
	m_modeNext = MODE_NONE;

	// �I��
	Uninit();

	return Create(m_mode);
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
CMode::EMode CMode::Get()
{
	return m_mode;
}

//--------------------------------------------------
// �ύX
//--------------------------------------------------
void CMode::Change(EMode mode)
{
	assert(mode > MODE_NONE && mode < MODE_MAX);

	m_modeNext = mode;
}
