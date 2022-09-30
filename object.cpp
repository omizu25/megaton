//**************************************************
// 
// object.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"
#include "instancing.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const int CObject::MAX_OBJECT[]
{
	1024,
	50000,
	256
};

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CObject::m_numAll = 0;
CObject** CObject::m_pObject[CATEGORY_MAX];
CInstancing* CObject::m_pInstancing = nullptr;

//--------------------------------------------------
// ����
//--------------------------------------------------
void CObject::Create()
{
	for (int i = 0; i < CATEGORY_MAX; i++)
	{
		m_pObject[i] = new CObject* [MAX_OBJECT[i]];
	}

	for (int numCat = 0; numCat < CATEGORY_MAX; numCat++)
	{
		for (int numObj = 0; numObj < MAX_OBJECT[numCat]; numObj++)
		{
			m_pObject[numCat][numObj] = nullptr;
		}
	}

	if (m_pInstancing == nullptr)
	{// null�`�F�b�N
		m_pInstancing = CInstancing::Create();
	}
}

//--------------------------------------------------
// �j��
//--------------------------------------------------
void CObject::Delete()
{
	// �S�Ẳ��
	ReleaseAll(true);

	for (int i = 0; i < CATEGORY_MAX; i++)
	{
		delete[] m_pObject[i];
	}

	if (m_pInstancing != nullptr)
	{// null�`�F�b�N
		m_pInstancing->Uninit();
	}
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CObject::ReleaseAll(bool releaseKeep)
{
	for (int numCat = 0; numCat < CATEGORY_MAX; numCat++)
	{
		for (int numObj = 0; numObj < MAX_OBJECT[numCat]; numObj++)
		{
			if (m_pObject[numCat][numObj] == nullptr)
			{// NULL�`�F�b�N
				continue;
			}

			if (!releaseKeep && m_pObject[numCat][numObj]->m_keep)
			{// �L�[�v���Ă�����͉̂�����Ȃ�
				continue;
			}

			// �I�u�W�F�N�g�̊J��
			m_pObject[numCat][numObj]->Release();
		}
	}
}

//--------------------------------------------------
// �S�Ă̍X�V
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int numCat = 0; numCat < CATEGORY_MAX; numCat++)
	{
		for (int numObj = 0; numObj < MAX_OBJECT[numCat]; numObj++)
		{
			if (m_pObject[numCat][numObj] == nullptr)
			{// NULL�`�F�b�N
				continue;
			}

			// �I�u�W�F�N�g�̍X�V
			m_pObject[numCat][numObj]->Update();
		}
	}
}

//--------------------------------------------------
// �S�Ă̕`��
//--------------------------------------------------
void CObject::DrawAll()
{
	for (int numObj = 0; numObj < MAX_OBJECT[CATEGORY_3D]; numObj++)
	{
		if (m_pObject[CATEGORY_3D][numObj] == nullptr)
		{// NULL�`�F�b�N
			continue;
		}

		// �I�u�W�F�N�g�̕`��
		m_pObject[CATEGORY_3D][numObj]->Draw();
	}

	if (m_pInstancing != nullptr)
	{// null�`�F�b�N
		m_pInstancing->Draw();
	}

	for (int numObj = 0; numObj < MAX_OBJECT[CATEGORY_2D]; numObj++)
	{
		if (m_pObject[CATEGORY_2D][numObj] == nullptr)
		{// NULL�`�F�b�N
			continue;
		}

		// �I�u�W�F�N�g�̕`��
		m_pObject[CATEGORY_2D][numObj]->Draw();
	}
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
int CObject::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// �ő吔�̎擾
//--------------------------------------------------
int CObject::GetMax(ECategory cat)
{
	return MAX_OBJECT[cat];
}

//--------------------------------------------------
// �I�u�W�F�N�g�̎擾
//--------------------------------------------------
CObject** CObject::GetMyObject(ECategory cat)
{
	assert(cat > CATEGORY_NONE && cat < CATEGORY_MAX);

	return m_pObject[cat];
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CObject::CObject(ECategory cat) :
	m_keep(false)
{
	static_assert(sizeof(MAX_OBJECT) / sizeof(MAX_OBJECT[0]) == CATEGORY_MAX, "aho");

	assert(cat > CATEGORY_NONE && cat < CATEGORY_MAX);

	for (int i = 0; i < MAX_OBJECT[cat]; i++)
	{
		if (m_pObject[cat][i] == nullptr)
		{// null�`�F�b�N
			m_pObject[cat][i] = this;
			m_cat = cat;
			m_index = i;
			m_numAll++;
			break;
		}
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObject::~CObject()
{
	m_numAll--;
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CObject::Release()
{
	if (m_pObject[m_cat][m_index] != nullptr)
	{// NULL�`�F�b�N
		int index = m_index;
		int cat = m_cat;
		m_pObject[cat][index]->Uninit();
		delete m_pObject[cat][index];
		m_pObject[cat][index] = nullptr;
	}
}

//--------------------------------------------------
// �����Ǝ����Ă��邩�̐ݒ�
//--------------------------------------------------
void CObject::SetKeep(bool keep)
{
	m_keep = keep;
}
