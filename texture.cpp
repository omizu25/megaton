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
	"data/TEXTURE/effect.jpg",	// �G�t�F�N�g
	"data/TEXTURE/bg000.png",	// �w�i

	/* ���e�L�X�g�� */
	"data/TEXTURE/TEXT/Number.png",	// ��
	"data/TEXTURE/TEXT/title.png",	// �^�C�g��
	"data/TEXTURE/TEXT/rank.png",	// ��
	"data/TEXTURE/TEXT/Comma.png",	// �J���}

	/* ���n�b�J�\��(2022/09/30)�p�� */
	"data/TEXTURE/TEXT/Hackathon_PressEnter.png",	// Enter�������Ă�
	"data/TEXTURE/TEXT/Hackathon_Score.png",		// �X�R�A
	"data/TEXTURE/TEXT/Hackathon_Ranking.png",		// �����L���O
	"data/TEXTURE/TEXT/Hachathon_GameBg.png",		// �Q�[����ʂ̔w�i
	"data/TEXTURE/TEXT/Hachathon_NightSky.jpg",		// ���
	"data/TEXTURE/hanabitutu.png",					// �ԉΓ�
	"data/TEXTURE/TEXT/Hackathon_Number.png",		// 0�`9
	"data/TEXTURE/Hachathon_Pien_yellow.png",		// �҂���(��)
	"data/TEXTURE/Hachathon_Pien_white.png",		// �҂���(��)
	"data/TEXTURE/Hachathon_Target.png",			// �^�[�Q�b�g
	"data/TEXTURE/TEXT/Hachathon_Tutorial.png",		// �^�C�~���O�ǂ�Enter���������I
	"data/TEXTURE/Hackathon_otowakka_0.png",		// �T�[�N��(��)
	"data/TEXTURE/Hackathon_otowakka_1.png",		// �T�[�N��(��)
	"data/TEXTURE/Hackathon_otowakka_2.png",		// �T�[�N��(��)
	"data/TEXTURE/Hackathon_5shakuball.png",		// �ł��グ�ԉ΂̒e����
	"data/TEXTURE/Hackathon_TitleLogo.png",			// �^�C�g�����S
	"data/TEXTURE/TEXT/Hackathon_Retry.png",		// ���g���C
	"data/TEXTURE/TEXT/Hackathon_End.png",			// �I��
	"data/TEXTURE/Cursor.png",						// �J�[�\��
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
