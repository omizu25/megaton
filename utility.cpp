//**************************************************
// 
// utility.cpp
// Author  : katsuki mizuki
// Author YudaKaito
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "utility.h"

//--------------------------------------------------
// �p�x�̐��K��
//--------------------------------------------------
void NormalizeAngle(float *pAngle)
{
	if (*pAngle >= D3DX_PI)
	{// 3.14���傫��
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{// -3.14��菬����
		*pAngle += D3DX_PI * 2.0f;
	}
}

//--------------------------------------------------
// �z�[�~���O
//--------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed)
{
	D3DXVECTOR3 vecDiff = posDest - posNow;

	float fLength = D3DXVec3Length(&vecDiff);

	if (fLength <= fSpeed)
	{// ������蒷������������
		*pPosOut = posDest;
		return true;
	}
	else
	{// ������蒷�����傫����
		*pPosOut = posNow + ((vecDiff / fLength) * fSpeed);
		return false;
	}
}

//--------------------------------------------------
// �����_�̃����_��
//--------------------------------------------------
float FloatRandom(float fMax, float fMin)
{
	return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
}

//--------------------------------------------------
// �����̃����_��
//--------------------------------------------------
int IntRandom(int nMax, int nMin)
{
	return (int)((rand() / (float)RAND_MAX) * (nMax - nMin)) + nMin;
}

//--------------------------------------------------
// sin�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
//--------------------------------------------------
float SinCurve(int nTime, float fCycle)
{
	return  (sinf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// cos�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
//--------------------------------------------------
float CosCurve(int nTime, float fCycle)
{
	return  (cosf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// �J�[�u�̒l���A���Ă���
//--------------------------------------------------
float Curve(float fCurve, float fMax, float fMin)
{
	return (fCurve * (fMax - fMin)) + fMin;
}

//--------------------------------------------------
// �͈͓�
//--------------------------------------------------
bool InRange(D3DXVECTOR3* pPos, const D3DXVECTOR3& range)
{
	bool out = false;

	if (pPos->x >= range.x)
	{// �E�̕�
		pPos->x = range.x;
		out = true;
	}
	else if (pPos->x <= -range.x)
	{// ���̕�
		pPos->x = -range.x;
		out = true;
	}

	if (pPos->y >= range.y)
	{// ��̕�
		pPos->y = range.y;
		out = true;
	}
	else if (pPos->y <= -range.y)
	{// ���̕�
		pPos->y = -range.y;
		out = true;
	}

	return out;
}

//--------------------------------------------------
// �͈͓��Ŕ���
//--------------------------------------------------
bool InRangeReflect(D3DXVECTOR3* pPos, D3DXVECTOR3* pMove, const D3DXVECTOR3& range)
{
	bool out = false;

	if (pPos->x >= range.x)
	{// �E�̕�
		pPos->x = range.x;
		pMove->x *= -1.0f;
		out = true;
	}
	else if (pPos->x <= -range.x)
	{// ���̕�
		pPos->x = -range.x;
		pMove->x *= -1.0f;
		out = true;
	}

	if (pPos->y >= range.y)
	{// ��̕�
		pPos->y = range.y;
		pMove->y *= -1.0f;
		out = true;
	}
	else if (pPos->y <= -range.y)
	{// ���̕�
		pPos->y = -range.y;
		pMove->y *= -1.0f;
		out = true;
	}

	return out;
}

//--------------------------------------------------
// �~�̓����蔻��
//--------------------------------------------------
bool CollisionCircle(const D3DXVECTOR3& pos1, float radius1, const D3DXVECTOR3& pos2, float radius2)
{
	// �Q�̕��̂̔��a���m�̘a
	float radius = radius1 + radius2;

	// X�̍���
	float diffX = pos1.x - pos2.x;

	// Y�̍���
	float diffY = pos1.y - pos2.y;

	// ���݂̂Q�_�̋���
	float length = sqrtf((diffX * diffX) + (diffY * diffY));

	if (radius >= length)
	{// �Q�̕��̂̔��a���m�̘a��茻�݂̂Q�_�̋��������������ǂ���
		// ��������
		return true;
	}

	// �������ĂȂ�
	return false;
}

//--------------------------------------------------
// �G���A�̓����蔻��
//--------------------------------------------------
bool CollisionArea(const D3DXVECTOR3& pos1, float radius1, D3DXVECTOR3* pPos2, float radius2)
{
	// �Q�̕��̂̔��a���m�̘a
	float radius = radius1 + radius2;

	// X�̍���
	float diffX = pos1.x - pPos2->x;

	// Y�̍���
	float diffY = pos1.y - pPos2->y;

	// ���݂̂Q�_�̋���
	float length = sqrtf((diffX * diffX) + (diffY * diffY));

	if (radius >= length)
	{// �Q�̕��̂̔��a���m�̘a��茻�݂̂Q�_�̋��������������ǂ���
		float rot = atan2f(diffX, diffY);
		pPos2->x = pos1.x - (sinf(rot) * radius);
		pPos2->y = pos1.y - (cosf(rot) * radius);

		// ��������
		return true;
	}

	// �������ĂȂ�
	return false;
}

//--------------------------------------------------
// �o�b�t�@�̃R�s�[
//--------------------------------------------------
void CopyBuf(IDirect3DVertexBuffer9* pBuf, void* pSrc, unsigned size)
{
	void *p = 0;
	pBuf->Lock(0, 0, &p, 0);
	memcpy(p, pSrc, size);
	pBuf->Unlock();
}

//--------------------------------------------------
// ����
//--------------------------------------------------
int Digit(int number)
{
	if (number == 0)
	{
		return 1;
	}

	return (int)log10f((float)number) + 1;
}
