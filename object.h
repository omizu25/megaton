//**************************************************
// 
// object.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT_H_	//���̃}�N����`������ĂȂ�������
#define _OBJECT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// �O���錾
//==================================================
class CInstancing;

//==================================================
// ��`
//==================================================
class CObject
{
	/* ����`�� */
public:
	enum ECategory
	{
		CATEGORY_NONE = -1,
		CATEGORY_3D = 0,	// 3D
		CATEGORY_EFFECT,	// �G�t�F�N�g
		CATEGORY_2D,		// 2D
		CATEGORY_MAX
	};

private:
	static const int MAX_OBJECT[CATEGORY_MAX];	// �ő吔�̔z��

	/* ���ÓI�����o�֐��� */
public:
	static void Create();	// ����
	static void Delete();	// �j��
	static void ReleaseAll(bool releaseKeep);		// �S�Ẳ��
	static void UpdateAll();						// �S�Ă̍X�V
	static void DrawAll();							// �S�Ă̕`��
	static int GetNumAll();							// �����̎擾
	static int GetMax(ECategory cat);				// �ő吔�̎擾
	static CObject** GetMyObject(ECategory cat);	// �I�u�W�F�N�g�̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_numAll;	// ����
	static CObject** m_pObject[CATEGORY_MAX];	// �I�u�W�F�N�g�̏��
	static CInstancing* m_pInstancing;			// �C���X�^���V���O�̏��

	/* �������o�֐��� */
public:
	CObject() = delete;	// �f�t�H���g�R���X�g���N�^
	explicit CObject(ECategory cat);	// �R���X�g���N�^
	virtual ~CObject();	// �f�X�g���N�^

public:
	virtual void Init() = 0;	// ������
	virtual void Uninit() = 0;	// �I��
	virtual void Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��

public:
	void SetKeep(bool keep);	// �����Ǝ����Ă��邩�̐ݒ�
	void Release();	// ���

	/* �������o�ϐ��� */
private:
	ECategory m_cat;	// �J�e�S���[
	int m_index;		// �i�[��̔ԍ�
	bool m_keep;		// �����Ǝ����Ă��邩�ǂ���
};

#endif // !_OBJECT_H_
