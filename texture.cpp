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
	"data/TEXTURE/Player.png",				// �v���C���[
	"data/TEXTURE/Bullet.png",				// �e
	"data/TEXTURE/effect.jpg",				// �G�t�F�N�g
	"data/TEXTURE/bg.png",					// �w�i
	"data/TEXTURE/Cursor.png",				// �J�[�\��
	"data/TEXTURE/TutorialNormal.png",		// �ʏ�̃`���[�g���A��
	"data/TEXTURE/TutorialSafetyArea.png",	// ���S�G���A�̃`���[�g���A��
	"data/TEXTURE/TutorialDangerArea.png",	// �댯�G���A�̃`���[�g���A��
	"data/TEXTURE/Circle.png",				// �~
	"data/TEXTURE/Bom.png",					// �{��

	/* ���G�� */
	"data/TEXTURE/Homing.png",			// �z�[�~���O
	"data/TEXTURE/HomingEscape.png",	// ������z�[�~���O
	"data/TEXTURE/HomingDivision.png",	// ����z�[�~���O
	"data/TEXTURE/PaperAirplane.png",	// ����s�@
	"data/TEXTURE/Windmill.png",		// ����
	"data/TEXTURE/snake_body.png",		// �ւ̑�

	/* ���e�L�X�g�� */
	"data/TEXTURE/TEXT/Number.png",			// ��
	"data/TEXTURE/TEXT/result.png",			// ���U���g
	"data/TEXTURE/TEXT/title.png",			// �^�C�g��
	"data/TEXTURE/TEXT/mul.png",			// �|����
	"data/TEXTURE/TEXT/rank.png",			// ��
	"data/TEXTURE/TEXT/Ranking_Title.png",	// �^�C�g���p�̃����L���O
	"data/TEXTURE/TEXT/Ranking_Result.png",	// ���U���g�p�̃����L���O
	"data/TEXTURE/TEXT/NewScore.png",		// �V�����X�R�A
	"data/TEXTURE/TEXT/Comma.png",			// �J���}
	"data/TEXTURE/TEXT/Period.png",			// �s���I�h
	"data/TEXTURE/TEXT/Pause.png",			// �|�[�Y
	"data/TEXTURE/TEXT/Resume.png",			// �ĊJ
	"data/TEXTURE/TEXT/Restart.png",		// ���X�^�[�g
	"data/TEXTURE/TEXT/End.png",			// �I��
	"data/TEXTURE/TEXT/End_Ranking.png",	// �����L���O�p�̏I��
	"data/TEXTURE/TEXT/Retry.png",			// ���g���C
	"data/TEXTURE/TEXT/Normal.png",			// �ʏ�
	"data/TEXTURE/TEXT/SafetyArea.png",		// ���S�G���A
	"data/TEXTURE/TEXT/DangerArea.png",		// �댯�G���A
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
