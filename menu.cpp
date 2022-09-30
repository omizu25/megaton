//**************************************************
// 
// menu.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "menu.h"
#include "object2D.h"
#include "utility.h"
#include "input.h"
#include "application.h"
#include "sound.h"
#include "mode.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CMenu::CURSOR_INTERVAL = 30.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CMenu* CMenu::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int numUse, float interval, bool sort, bool cursor)
{
	CMenu* pMenu = nullptr;

	pMenu = new CMenu;

	if (pMenu != nullptr)
	{// null�`�F�b�N
		// ������
		pMenu->Init(pos, size, numUse, interval, sort, cursor);
	}

	return pMenu;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CMenu::CMenu() :
	m_pFrame(nullptr),
	m_pCursor(nullptr),
	m_selectIdx(0),
	m_numUse(0),
	m_time(0),
	m_sort(false)
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		m_pOption[i] = nullptr;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CMenu::~CMenu()
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		assert(m_pOption[i] == nullptr);
	}

	assert(m_pFrame == nullptr);
	assert(m_pCursor == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CMenu::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int numUse, float interval, bool sort, bool cursor)
{
	assert(numUse > 0 && numUse <= MAX_OPTION);

	m_numUse = numUse;
	m_sort = sort;
	m_selectIdx = 0;
	m_time = 0;

	// �g�̍쐬
	m_pFrame = CObject2D::Create();

	// �`��̐ݒ�
	m_pFrame->SetDraw(false);

	// �ʒu�̐ݒ�
	m_pFrame->SetPos(pos);

	// �t�F�[�h�̐ݒ�
	m_pFrame->SetFade(0.0f);

	D3DXVECTOR3 optionPos = pos;

	if (m_sort)
	{// �c
		optionPos.y -= ((m_numUse - 1) * ((size.y * 0.5f) + (interval * 0.5f)));
	}
	else
	{// ��
		optionPos.x -= ((m_numUse - 1) * ((size.x * 0.5f) + (interval * 0.5f)));
	}

	if (cursor)
	{// �J�[�\�����g�p����
		// �J�[�\���̍쐬
		m_pCursor = CObject2D::Create();

		float cursorSize = size.y * 0.8f;
		D3DXVECTOR3 cursorPos = optionPos;
		cursorPos.x -= ((cursorSize * 0.5f) + (size.x * 0.5f) + CURSOR_INTERVAL);

		// �ʒu�̐ݒ�
		m_pCursor->SetPos(cursorPos);

		// �T�C�Y�̐ݒ�
		m_pCursor->SetSize(D3DXVECTOR3(cursorSize, cursorSize, 0.0f));

		// �e�N�X�`���̐ݒ�
		m_pCursor->SetTexture(CTexture::LABEL_Cursor);

		// �t�F�[�h�̐ݒ�
		m_pCursor->SetFade(0.0f);
	}
	else
	{
		m_pCursor = nullptr;
	}
	
	for (int i = 0; i < MAX_OPTION; i++)
	{
		if (i >= m_numUse)
		{// �w��̒l�ȏ�
			m_pOption[i] = nullptr;
			continue;
		}

		// �I�����̍쐬
		m_pOption[i] = CObject2D::Create();

		// �ʒu�̐ݒ�
		m_pOption[i]->SetPos(optionPos);

		// �T�C�Y�̐ݒ�
		m_pOption[i]->SetSize(size);

		// �t�F�[�h�̐ݒ�
		m_pOption[i]->SetFade(0.0f);

		if (m_sort)
		{// �c
			optionPos.y += size.y + interval;
		}
		else
		{// ��
			optionPos.x += size.x + interval;
		}
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CMenu::Uninit()
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		if (m_pOption[i] != nullptr)
		{// null�`�F�b�N
			// �I��
			m_pOption[i]->Uninit();
			m_pOption[i] = nullptr;
		}
	}

	if (m_pFrame != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pCursor != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pCursor->Uninit();
		m_pCursor = nullptr;
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CMenu::Release()
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		if (m_pOption[i] != nullptr)
		{// null�`�F�b�N
			// ���
			m_pOption[i]->Release();
			m_pOption[i] = nullptr;
		}
	}

	if (m_pFrame != nullptr)
	{// null�`�F�b�N
		// ���
		m_pFrame->Release();
		m_pFrame = nullptr;
	}

	if (m_pCursor != nullptr)
	{// null�`�F�b�N
		// ���
		m_pCursor->Release();
		m_pCursor = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CMenu::Update()
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		if (m_pOption[i] != nullptr)
		{// null�`�F�b�N
			// �X�V
			m_pOption[i]->Update();
		}
	}

	if (m_pFrame != nullptr)
	{// null�`�F�b�N
		 // �X�V
		m_pFrame->Update();
	}

	if (m_pCursor != nullptr)
	{// null�`�F�b�N
		// �X�V
		m_pCursor->Update();
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
int CMenu::Select()
{
	m_time++;

	if (m_time <= CMode::FADE_TIME)
	{// �t�F�[�h��
		return -1;
	}

	CInput* pInput = CInput::GetKey();

	if (m_sort)
	{// �c
		if (pInput->Trigger(CInput::KEY_UP))
		{// ��L�[�������ꂽ
			Add(-1);
		}
		if (pInput->Trigger(CInput::KEY_DOWN))
		{// ���L�[�������ꂽ
			Add(1);
		}
	}
	else
	{// ��
		if (pInput->Trigger(CInput::KEY_LEFT))
		{// ���L�[�������ꂽ
			Add(-1);
		}
		if (pInput->Trigger(CInput::KEY_RIGHT))
		{// �E�L�[�������ꂽ
			Add(1);
		}
	}

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.a = 1.0f - (CosCurve(m_time, 0.025f) * 0.7f);

	// �F�̐ݒ�
	m_pOption[m_selectIdx]->SetCol(col);

	if (pInput->Trigger(CInput::KEY_DECISION))
	{// ����L�[�������ꂽ
		// SE
		CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Enter);

		return m_selectIdx;
	}

	return -1;
}

//--------------------------------------------------
// �t���[���̐ݒ�
//--------------------------------------------------
void CMenu::SetFrame(const D3DXVECTOR3& size, const D3DXCOLOR& col)
{
	if (m_pFrame->GetDraw())
	{// ���łɃt���[��������
		m_pFrame->SetSize(size);
		return;
	}

	// �T�C�Y�̐ݒ�
	m_pFrame->SetSize(size);

	// �F�̐ݒ�
	m_pFrame->SetCol(col);

	// �`��̐ݒ�
	m_pFrame->SetDraw(true);
}

//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
void CMenu::SetTexture(int idx, CTexture::ELabel label)
{
	if (idx == -1)
	{// �w��̒l
		m_pFrame->SetTexture(label);
		return;
	}

	assert(idx >= 0 && idx < MAX_OPTION);

	if (m_pOption[idx] != nullptr)
	{// null�`�F�b�N
		m_pOption[idx]->SetTexture(label);
	}
}

//--------------------------------------------------
// ���Z
//--------------------------------------------------
void CMenu::Add(int add)
{
	// �F�̐ݒ�
	m_pOption[m_selectIdx]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_selectIdx = ((m_selectIdx + add) + m_numUse) % m_numUse;

	m_time = 0;

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Select);

	if (m_pCursor != nullptr)
	{// null�`�F�b�N
		D3DXVECTOR3 pos = m_pOption[m_selectIdx]->GetPos();
		D3DXVECTOR3 optionSize = m_pOption[m_selectIdx]->GetSize();
		D3DXVECTOR3 cursorSize = m_pCursor->GetSize();
		pos.x -= ((optionSize.x * 0.5f) + (cursorSize.x * 0.5f) + CURSOR_INTERVAL);

		// �ʒu�̐ݒ�
		m_pCursor->SetPos(pos);
	}
}

//--------------------------------------------------
// �I������Ă���ԍ��̎擾
//--------------------------------------------------
int CMenu::GetSelectIdx()
{
	return m_selectIdx;
}
