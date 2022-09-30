//**************************************************
// 
// utility.cpp
// Author  : katsuki mizuki
// Author YudaKaito
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "utility.h"
#include "application.h"
#include "camera.h"

//--------------------------------------------------
// 角度の正規化
//--------------------------------------------------
void NormalizeAngle(float *pAngle)
{
	if (*pAngle >= D3DX_PI)
	{// 3.14より大きい
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{// -3.14より小さい
		*pAngle += D3DX_PI * 2.0f;
	}
}

//--------------------------------------------------
// ホーミング
//--------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed)
{
	D3DXVECTOR3 vecDiff = posDest - posNow;

	float fLength = D3DXVec3Length(&vecDiff);

	if (fLength <= fSpeed)
	{// 速さより長さが小さい時
		*pPosOut = posDest;
		return true;
	}
	else
	{// 速さより長さが大きい時
		*pPosOut = posNow + ((vecDiff / fLength) * fSpeed);
		return false;
	}
}

//--------------------------------------------------
// 小数点のランダム
//--------------------------------------------------
float FloatRandom(float fMax, float fMin)
{
	return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
}

//--------------------------------------------------
// 整数のランダム
//--------------------------------------------------
int IntRandom(int nMax, int nMin)
{
	return (int)((rand() / (float)RAND_MAX) * (nMax - nMin)) + nMin;
}

//--------------------------------------------------
// sinカーブの値が1.0f～0.0fで帰ってくる
//--------------------------------------------------
float SinCurve(int nTime, float fCycle)
{
	return  (sinf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// cosカーブの値が1.0f～0.0fで帰ってくる
//--------------------------------------------------
float CosCurve(int nTime, float fCycle)
{
	return  (cosf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// カーブの値が帰ってくる
//--------------------------------------------------
float Curve(float fCurve, float fMax, float fMin)
{
	return (fCurve * (fMax - fMin)) + fMin;
}

//--------------------------------------------------
// 範囲内
//--------------------------------------------------
bool InRange(D3DXVECTOR3* pPos, const D3DXVECTOR3& range)
{
	bool out = false;

	if (pPos->x >= range.x)
	{// 右の壁
		pPos->x = range.x;
		out = true;
	}
	else if (pPos->x <= -range.x)
	{// 左の壁
		pPos->x = -range.x;
		out = true;
	}

	if (pPos->y >= range.y)
	{// 上の壁
		pPos->y = range.y;
		out = true;
	}
	else if (pPos->y <= -range.y)
	{// 下の壁
		pPos->y = -range.y;
		out = true;
	}

	return out;
}

//--------------------------------------------------
// 範囲内で反射
//--------------------------------------------------
bool InRangeReflect(D3DXVECTOR3* pPos, D3DXVECTOR3* pMove, const D3DXVECTOR3& range)
{
	bool out = false;

	if (pPos->x >= range.x)
	{// 右の壁
		pPos->x = range.x;
		pMove->x *= -1.0f;
		out = true;
	}
	else if (pPos->x <= -range.x)
	{// 左の壁
		pPos->x = -range.x;
		pMove->x *= -1.0f;
		out = true;
	}

	if (pPos->y >= range.y)
	{// 上の壁
		pPos->y = range.y;
		pMove->y *= -1.0f;
		out = true;
	}
	else if (pPos->y <= -range.y)
	{// 下の壁
		pPos->y = -range.y;
		pMove->y *= -1.0f;
		out = true;
	}

	return out;
}

//--------------------------------------------------
// 円の当たり判定
//--------------------------------------------------
bool CollisionCircle(const D3DXVECTOR3& pos1, float radius1, const D3DXVECTOR3& pos2, float radius2)
{
	// ２つの物体の半径同士の和
	float radius = radius1 + radius2;

	// Xの差分
	float diffX = pos1.x - pos2.x;

	// Yの差分
	float diffY = pos1.y - pos2.y;

	// 現在の２点の距離
	float length = sqrtf((diffX * diffX) + (diffY * diffY));

	if (radius >= length)
	{// ２つの物体の半径同士の和より現在の２点の距離が小さいかどうか
		// 当たった
		return true;
	}

	// 当たってない
	return false;
}

//--------------------------------------------------
// エリアの当たり判定
//--------------------------------------------------
bool CollisionArea(const D3DXVECTOR3& pos1, float radius1, D3DXVECTOR3* pPos2, float radius2)
{
	// ２つの物体の半径同士の和
	float radius = radius1 + radius2;

	// Xの差分
	float diffX = pos1.x - pPos2->x;

	// Yの差分
	float diffY = pos1.y - pPos2->y;

	// 現在の２点の距離
	float length = sqrtf((diffX * diffX) + (diffY * diffY));

	if (radius >= length)
	{// ２つの物体の半径同士の和より現在の２点の距離が小さいかどうか
		float rot = atan2f(diffX, diffY);
		pPos2->x = pos1.x - (sinf(rot) * radius);
		pPos2->y = pos1.y - (cosf(rot) * radius);

		// 当たった
		return true;
	}

	// 当たってない
	return false;
}

//--------------------------------------------------
// バッファのコピー
//--------------------------------------------------
void CopyBuf(IDirect3DVertexBuffer9* pBuf, void* pSrc, unsigned size)
{
	void *p = 0;
	pBuf->Lock(0, 0, &p, 0);
	memcpy(p, pSrc, size);
	pBuf->Unlock();
}

//--------------------------------------------------
// 桁数
//--------------------------------------------------
int Digit(int number)
{
	if (number == 0)
	{
		return 1;
	}

	return (int)log10f((float)number) + 1;
}

//---------------------------------------------------------------------------
// スクリーン座標をワールド座標へのキャスト
//---------------------------------------------------------------------------
D3DXVECTOR3 WorldCastScreen(D3DXVECTOR3 *screenPos,			// スクリーン座標
	D3DXVECTOR3 screenSize,									// スクリーンサイズ
	D3DXMATRIX* mtxView,									// ビューマトリックス
	D3DXMATRIX* mtxProjection)								// プロジェクションマトリックス
{
	// 変数宣言
	D3DXVECTOR3 ScreenPos;

	// 計算用マトリックスの宣言
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;

	// 各行列の逆行列を算出
	D3DXMatrixInverse(&InvView, NULL, mtxView);
	D3DXMatrixInverse(&InvPrj, NULL, mtxProjection);
	D3DXMatrixIdentity(&VP);
	VP._11 = screenSize.x / 2.0f; VP._22 = -screenSize.y / 2.0f;
	VP._41 = screenSize.x / 2.0f; VP._42 = screenSize.y / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// ワールド座標へのキャスト
	D3DXMATRIX mtxWorld = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(&ScreenPos, screenPos, &mtxWorld);

	return ScreenPos;
}

//---------------------------------------------------------------------------
// スクリーン座標をワールド座標へのキャスト
//---------------------------------------------------------------------------
D3DXVECTOR3 ScreenCastWorld(D3DXVECTOR3 *screenPos,			// スクリーン座標
	D3DXVECTOR3 screenSize									// スクリーンサイズ
)															// プロジェクションマトリックス
{
	// 変数宣言

	D3DXVECTOR3 pos = *screenPos;

	D3DXVECTOR3 Camerapos = CApplication::GetInstanse()->GetCamera()->GetPos();

	pos.y *= -1;

	pos -= (Camerapos - D3DXVECTOR3(screenSize.x / 2, screenSize.y / 2, 0.0f));

	return pos;
}
