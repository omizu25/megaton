//**************************************************
// 
// instancing.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "instancing.h"
#include "application.h"
#include "utility.h"
#include "camera.h"
#include "texture.h"
#include "effect.h"

#include <assert.h>

//--------------------------------------------------
// ����
//--------------------------------------------------
CInstancing* CInstancing::Create()
{
	CInstancing* pInstancing = nullptr;

	pInstancing = new CInstancing;

	if (pInstancing != nullptr)
	{// null�`�F�b�N
		pInstancing->Init();
	}

	return pInstancing;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CInstancing::CInstancing() :
	m_pVtxBuff(nullptr),
	m_pPosBuff(nullptr),
	m_pColBuff(nullptr),
	m_pSizeBuff(nullptr),
	m_pDecl(nullptr),
	m_pIndexBuff(nullptr),
	m_pShader(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CInstancing::~CInstancing()
{
	assert(m_pVtxBuff == nullptr);
	assert(m_pPosBuff == nullptr);
	assert(m_pColBuff == nullptr);
	assert(m_pSizeBuff == nullptr);
	assert(m_pDecl == nullptr);
	assert(m_pIndexBuff == nullptr);
	assert(m_pShader == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CInstancing::Init()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();
	
	{// ���_�o�b�t�@
		Vtx vtx[4] =
		{// ���_�o�b�t�@
			{ -1.0f, +1.0f, 0.0f, 0.0f },
			{ +1.0f, +1.0f, 1.0f, 0.0f },
			{ -1.0f, -1.0f, 0.0f, 1.0f },
			{ +1.0f, -1.0f, 1.0f, 1.0f }
		};

		// ���_�o�b�t�@�쐬
		pDevice->CreateVertexBuffer(sizeof(vtx), 0, 0, D3DPOOL_MANAGED, &m_pVtxBuff, 0);

		// �o�b�t�@�̃R�s�[
		CopyBuf(m_pVtxBuff, vtx, sizeof(vtx));
	}

	{// �C���f�b�N�X�o�b�t�@
		WORD index[4] = { 0, 1, 2, 3 };

		pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuff, 0);

		void *p = 0;
		m_pIndexBuff->Lock(0, 0, &p, 0);
		memcpy(p, index, sizeof(index));
		m_pIndexBuff->Unlock();
	}

	{// ���_�錾�쐬
		D3DVERTEXELEMENT9 declElems[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	// LocalPos
			{ 0, 8, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// UV
			{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },	// WorldPos �� rot
			{ 2, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },		// Color
			{ 3, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },	// size
			D3DDECL_END()
		};

		pDevice->CreateVertexDeclaration(declElems, &m_pDecl);
	}

	{// �V�F�[�_�쐬
		ID3DXBuffer* pErrBuff = nullptr;
	
		D3DXCreateEffectFromFileA(pDevice, "data/TEXT/Effect.fx", 0, 0, 0, 0, &m_pShader, &pErrBuff);
		
		if (pErrBuff != nullptr)
		{// null�`�F�b�N
			const char *errMsg = (const char*)pErrBuff->GetBufferPointer();
			OutputDebugStringA(errMsg);
			assert(false);
		}
	}

	int objMax = CObject::GetMax(CObject::CATEGORY_EFFECT);
	pDevice->CreateVertexBuffer(sizeof(D3DXVECTOR3) * objMax, 0, 0, D3DPOOL_MANAGED, &m_pPosBuff, 0);
	pDevice->CreateVertexBuffer(sizeof(D3DXCOLOR) * objMax, 0, 0, D3DPOOL_MANAGED, &m_pColBuff, 0);
	pDevice->CreateVertexBuffer(sizeof(D3DXVECTOR2) * objMax, 0, 0, D3DPOOL_MANAGED, &m_pSizeBuff, 0);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CInstancing::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{// null�`�F�b�N
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pPosBuff != nullptr)
	{// null�`�F�b�N
		m_pPosBuff->Release();
		m_pPosBuff = nullptr;
	}

	if (m_pColBuff != nullptr)
	{// null�`�F�b�N
		m_pColBuff->Release();
		m_pColBuff = nullptr;
	}

	if (m_pSizeBuff != nullptr)
	{// null�`�F�b�N
		m_pSizeBuff->Release();
		m_pSizeBuff = nullptr;
	}

	if (m_pDecl != nullptr)
	{// null�`�F�b�N
		m_pDecl->Release();
		m_pDecl = nullptr;
	}

	if (m_pIndexBuff != nullptr)
	{// null�`�F�b�N
		m_pIndexBuff->Release();
		m_pIndexBuff = nullptr;
	}

	if (m_pShader != nullptr)
	{// null�`�F�b�N
		m_pShader->Release();
		m_pShader = nullptr;
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CInstancing::Draw()
{
	int numAll = CEffect::GetNumAll();

	if (numAll == 0)
	{// �\������Ă��Ȃ�
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// �����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	{// �G�t�F�N�g�̏��擾
		D3DXVECTOR3* worldPos = new D3DXVECTOR3[numAll];	// ���[���h���W�ʒu�o�b�t�@
		D3DXCOLOR* col = new D3DXCOLOR[numAll];
		D3DXVECTOR2* size = new D3DXVECTOR2[numAll];

		CEffect** pObject = (CEffect**)CObject::GetMyObject(CObject::CATEGORY_EFFECT);
		D3DXVECTOR3 objPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
		int num = 0;
		int objMax = CObject::GetMax(CObject::CATEGORY_EFFECT);

		for (int i = 0; i < objMax; i++)
		{
			if (pObject[i] == nullptr)
			{// null�`�F�b�N
				continue;
			}
			objPos = pObject[i]->GetPos();
			move = pObject[i]->GetMove();
			
			worldPos[num].x = objPos.x;
			worldPos[num].y = objPos.y;
			worldPos[num].z = atan2f(move.x, move.y);

			col[num] = pObject[i]->GetCol();
			size[num] = pObject[i]->GetSize();

			num++;
		}

		assert(num == numAll);

		// �o�b�t�@�̃R�s�[
		CopyBuf(m_pPosBuff, worldPos, sizeof(D3DXVECTOR3) * numAll);
		CopyBuf(m_pColBuff, col, sizeof(D3DXCOLOR) * numAll);
		CopyBuf(m_pSizeBuff, size, sizeof(D3DXVECTOR2) * numAll);

		delete[] worldPos;
		delete[] col;
		delete[] size;
	}

	// �C���X�^���X�錾
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | numAll);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | (unsigned)1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | (unsigned)1);
	pDevice->SetStreamSourceFreq(3, D3DSTREAMSOURCE_INSTANCEDATA | (unsigned)1);

	// ���_�ƃC���f�b�N�X��ݒ肵�ĕ`��
	pDevice->SetVertexDeclaration(m_pDecl);
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(Vtx));
	pDevice->SetStreamSource(1, m_pPosBuff, 0, sizeof(D3DXVECTOR3));
	pDevice->SetStreamSource(2, m_pColBuff, 0, sizeof(D3DXCOLOR));
	pDevice->SetStreamSource(3, m_pSizeBuff, 0, sizeof(D3DXVECTOR2));
	pDevice->SetIndices(m_pIndexBuff);

	m_pShader->SetTechnique("tech");

	m_pShader->SetTexture("g_tex", CApplication::GetInstanse()->GetTexture()->Get(CTexture::LABEL_Effect));

	CCamera* pCamera = CApplication::GetInstanse()->GetCamera();

	m_pShader->SetMatrix("g_view", &pCamera->GetView());
	m_pShader->SetMatrix("g_proj", &pCamera->GetProj());

	UINT passNum = 0;
	m_pShader->Begin(&passNum, 0);
	m_pShader->BeginPass(0);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);

	m_pShader->EndPass();
	m_pShader->End();

	// ��n��
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
	pDevice->SetStreamSourceFreq(3, 1);

	// �����_�[�X�e�[�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
