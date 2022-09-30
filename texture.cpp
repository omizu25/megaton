//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "texture.h"
#include "application.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const char* CTexture::FILE_NAME[] =
{// �e�N�X�`���̃p�X
	"data/TEXTURE/effect.jpg",		// �G�t�F�N�g
	"data/TEXTURE/bg000.png",		// �w�i
	"data/TEXTURE/Cursor.png",		// �J�[�\��
	"data/TEXTURE/Tutorial.png",	// �ʏ�̃`���[�g���A��

	/* ���e�L�X�g�� */
	"data/TEXTURE/TEXT/Number.png",		// ��
	"data/TEXTURE/TEXT/title.png",		// �^�C�g��
	"data/TEXTURE/TEXT/rank.png",		// ��
	"data/TEXTURE/TEXT/Comma.png",		// �J���}
	"data/TEXTURE/TEXT/Period.png",		// �s���I�h
	"data/TEXTURE/TEXT/Pause.png",		// �|�[�Y
	"data/TEXTURE/TEXT/Resume.png",		// �ĊJ
	"data/TEXTURE/TEXT/Restart.png",	// ���X�^�[�g
	"data/TEXTURE/TEXT/End.png",		// �I��
	"data/TEXTURE/TEXT/Retry.png",		// ���g���C

	/* ���n�b�J�\��(2022/09/30)�p�� */
	"data/TEXTURE/TEXT/Hackathon_PressAnyKey.png",	// �����L�[�������Ă�
	"data/TEXTURE/TEXT/Hackathon_Score.png",		// �X�R�A
	"data/TEXTURE/TEXT/Hackathon_Ranking.png",		// �����L���O
	"data/TEXTURE/TEXT/Hachathon_GameBg.png",		// �Q�[����ʂ̔w�i
	"data/TEXTURE/TEXT/Hachathon_NightSky.png",		// ���
};

static_assert(sizeof(CTexture::FILE_NAME) / sizeof(CTexture::FILE_NAME[0]) == CTexture::LABEL_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// �e�N�X�`���̓ǂݍ��݂�����Ă���
			continue;
		}

		// �ǂݍ���
		Load((ELabel)i);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(ELabel label)
{
	assert(label >= 0 && label < LABEL_MAX);

	if (s_pTexture[label] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FILE_NAME[label],
		&s_pTexture[label]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::ReleaseAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// �e�N�X�`���̉��
			s_pTexture[i]->Release();
			s_pTexture[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Release(ELabel label)
{
	assert(label >= 0 && label < LABEL_MAX);

	if (s_pTexture[label] != nullptr)
	{// �e�N�X�`���̉��
		s_pTexture[label]->Release();
		s_pTexture[label] = nullptr;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::Get(ELabel label)
{
	if (label == LABEL_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(label >= 0 && label < LABEL_MAX);

	// �ǂݍ���
	Load(label);

	return s_pTexture[label];
}
