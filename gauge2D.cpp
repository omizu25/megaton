//=============================================================================
//
// 2DQ[WNX(gauge2D.cpp)
// Author : ϊ±l
// Tv : 2DQ[WΆ¬πs€
//
//=============================================================================

//*****************************************************************************
// CN[h
//*****************************************************************************
#include <assert.h>

#include "gauge2D.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// CX^XΆ¬
// Author : ϊ±l
// Tv : 2DQ[WπΆ¬·ι
//=============================================================================
CGauge2D * CGauge2D::Create(void)
{
	// IuWFNgCX^X
	CGauge2D *pGauge2D = nullptr;

	// Μπϊ
	pGauge2D = new CGauge2D;

	if (pGauge2D != nullptr)
	{// lΜϊ»
		pGauge2D->Init();
	}
	else
	{// ΜmΫͺΕ«Θ©Α½
		assert(false);
	}

	// CX^XπΤ·
	return pGauge2D;
}

//=============================================================================
// RXgN^
// Author : ϊ±l
// Tv : CX^XΆ¬Ιs€
//=============================================================================
CGauge2D::CGauge2D(CObject::ECategory cat) : CObject(cat)
{
	m_pVtxBuff = nullptr;								// Έ_obt@
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// Κu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ό«
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ε«³
	m_maxSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ε«³Εεl
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			// J[
	m_fAngle = 0.0f;									// ΞpόΜpx
	m_fLength = 0.0f;									// ΞpόΜ·³
	m_fAngleOrigin = 0.0f;								// ΰΖΜΞpόΜpx
	m_fLengthOrigin = 0.0f;								// ΰΖΞpόΜ·³
	m_fMaxNumber = 0.0f;								// lΜΕε
	m_fNumber = 0.0f;									// l
	m_fDestNumber = 0.0f;								// ΪIΜl
	m_fCoefficient = 0.0f;								// ΈW
	m_texture = CTexture::LABEL_NONE;					// eNX`Μρ^
	m_change = false;
}

//=============================================================================
// fXgN^
// Author : ϊ±l
// Tv : CX^XIΉΙs€
//=============================================================================
CGauge2D::~CGauge2D()
{

}

//=============================================================================
// |SΜϊ»
// Author : ϊ±l
// Tv : Έ_obt@πΆ¬΅AoΟΜϊlπέθ
//=============================================================================
void CGauge2D::Init()
{// foCXΦΜ|C^ΜζΎ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	//Έ_obt@ΜΆ¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		// mΫ·ιobt@TCY
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,														// Έ_t@[}bg
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// |SξρΜέθ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// Κu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ό«
	m_size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);		// ε«³
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// J[
	m_change = true;

	// Έ_ΐWΜZo
	SetVtx();

	// FΜέθ
	SetCol(m_col);

	// eNX`ΐWΜέθ
	SetVtxTex(D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
}

//=============================================================================
// |SΜIΉ
// Author : ϊ±l
// Tv : eNX`Μ|C^ΖΈ_obt@Μπϊ
//=============================================================================
void CGauge2D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{// Έ_obt@Μjό
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// |SΜXV
// Author : ϊ±l
// Tv : 2D|SΜXVπs€
//=============================================================================
void CGauge2D::Update()
{
	if (!m_change)
	{
		return;
	}

	// lΜέθ
	float fAdd = (m_fDestNumber - m_fNumber) * m_fCoefficient;

	m_fNumber += fAdd;

	if (fAdd > 0)
	{
		if (m_fNumber >= m_fDestNumber)
		{
			m_fNumber = m_fDestNumber;
		}
	}
	else if (fAdd < 0)
	{
		if (m_fNumber <= m_fDestNumber)
		{
			m_fNumber = m_fDestNumber;
		}
	}

	// Q[WΜέθ
	SetGauge();
}

//=============================================================================
// |SΜ`ζ
// Author : ϊ±l
// Tv : 2D|SΜ`ζπs€
//=============================================================================
void CGauge2D::Draw()
{// foCXΦΜ|C^ΜζΎ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// eNX`|C^ΜζΎ
	CTexture *pTexture = CApplication::GetInstanse()->GetTexture();

	//eNX`Μέθ
	pDevice->SetTexture(0, nullptr);

	//eNX`Μέθ
	pDevice->SetTexture(0, pTexture->Get(m_texture));

	//Έ_obt@πf[^Xg[Ιέθ
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// Έ_tH[}bgΜέθ
	pDevice->SetFVF(FVF_VERTEX_2D);

	//|S`ζ
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//eNX`Μέθ
	pDevice->SetTexture(0, nullptr);
}

//=============================================================================
// ΚuΜZb^[
// Author : ϊ±l
// Tv : ΚuΜoΟΙψπγό
//=============================================================================
void CGauge2D::SetPos(const D3DXVECTOR3 &pos)
{
	// ΚuΜέθ
	m_pos = pos;

	// Έ_ΐWΘΗΜέθ
	SetVtx();

	// FΜέθ
	SetCol(m_col);
}

//=============================================================================
// ό«ΜZb^[
// Author : ϊ±l
// Tv : ό«ΜoΟΙψπγό
//=============================================================================
void CGauge2D::SetRot(const D3DXVECTOR3 &rot)
{
	// ό«Μέθ
	m_rot = rot;

	// Έ_ΐWΘΗΜέθ
	SetVtx();

	// FΜέθ
	SetCol(m_col);
}

//=============================================================================
// ε«³ΜZb^[
// Author : ϊ±l
// Tv : ε«³ΜoΟΙψπγό
//=============================================================================
void CGauge2D::SetSize(const D3DXVECTOR3 & size)
{
	// ε«³Μέθ
	m_maxSize = D3DXVECTOR3(size.x, size.y * 2.0f, 0.0f);

	// Έ_ΐWΘΗΜέθ
	SetVtx();

	// FΜέθ
	SetCol(m_col);
}

//=============================================================================
// Έ_ΐWΘΗΜέθ
// Author : ϊ±l
// Tv : 2D|SΜΈ_ΐWArhwAΈ_J[πέθ·ι
//=============================================================================
void CGauge2D::SetVtx()
{
	//Έ_ξρΦΜ|C^πΆ¬
	VERTEX_2D *pVtx;

	//Έ_obt@πbN΅AΈ_ξρΦΜ|C^πζΎ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ΞpόΜ·³πZo·ι
	m_fLength = sqrtf((m_maxSize.x * m_maxSize.x) + (m_size.y * m_size.y)) / 2.0f;
	m_fLengthOrigin = sqrtf(m_maxSize.x * m_maxSize.x) / 2.0f;

	//ΞpόΜpxπZo
	m_fAngle = atan2f(m_maxSize.x, m_size.y);
	m_fAngleOrigin = atan2f(m_maxSize.x, 0.0f);

	// Έ_ξρπέθ
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) *  m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) *  m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - (0 + m_fAngleOrigin)) * m_fLengthOrigin;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - (0 + m_fAngleOrigin)) * m_fLengthOrigin;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z - (0 - m_fAngleOrigin)) *  m_fLengthOrigin;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z - (0 - m_fAngleOrigin)) *  m_fLengthOrigin;
	pVtx[3].pos.z = 0.0f;

	// rhwΜέθ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//Έ_obt@πAbN
	m_pVtxBuff->Unlock();
}

//=============================================================================
// FΜέθ
// Author : ϊ±l
// Tv : Έ_J[πέθ·ι
//=============================================================================
void CGauge2D::SetCol(const D3DCOLOR &col)
{
	m_col = col;

	//Έ_ξρΦΜ|C^πΆ¬
	VERTEX_2D *pVtx;

	//Έ_obt@πbN΅AΈ_ξρΦΜ|C^πζΎ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// Έ_J[Μέθ
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//Έ_obt@πAbN
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// eNX`Μέθ
//--------------------------------------------------
void CGauge2D::SetTexture(CTexture::ELabel texture)
{
	m_texture = texture;
}

//--------------------------------------------------
// eNX`ΐWΜέθ
//--------------------------------------------------
void CGauge2D::SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2 v)
{
	VERTEX_2D *pVtx = nullptr;	// Έ_ξρΦΜ|C^

	// Έ_ξρπbN΅AΈ_ξρΦΜ|C^πζΎ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// eNX`ΐWΜέθ
	pVtx[0].tex = D3DXVECTOR2(u.x, v.x);
	pVtx[1].tex = D3DXVECTOR2(u.y, v.x);
	pVtx[2].tex = D3DXVECTOR2(u.x, v.y);
	pVtx[3].tex = D3DXVECTOR2(u.y, v.y);

	// Έ_obt@πAbN·ι
	m_pVtxBuff->Unlock();
}

//=============================================================================
// Q[WΜέθ
// Author : ϊ±l
// Tv : 2DQ[Wπέθ·ι
//=============================================================================
void CGauge2D::SetGauge()
{
	// ε«³Ιlπγό
	m_size.y = (m_maxSize.y / m_fMaxNumber) * m_fNumber;

	// Έ_ΐWΜέθ
	SetVtx();
}

//=============================================================================
// lΜΕεlΜέθ
// Author : ϊ±l
// Tv : lΜΕεlπέθ·ι
//=============================================================================
void CGauge2D::SetMaxNumber(const float fMaxNumber)
{
	m_fMaxNumber = fMaxNumber;

	// Q[WΜέθ
	SetGauge();
}

void CGauge2D::SetChange(bool change, const D3DXVECTOR3& size)
{
	// ε«³Μέθ
	m_maxSize = D3DXVECTOR3(size.x, size.y, 0.0f);
	m_size = D3DXVECTOR3(size.x, size.y, 0.0f);

	// Έ_ΐWΘΗΜέθ
	SetVtx();

	m_change = change;
}