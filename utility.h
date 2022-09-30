//**************************************************
//
// utility.h
// Author  : katsuki mizuki
// Author YudaKaito
//
//**************************************************
#ifndef _UTILITY_H_	// ���̃}�N����`������ĂȂ�������
#define _UTILITY_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

#ifdef _DEBUG
//==================================================
// �f�o�b�O�p
//==================================================
#include <crtdbg.h>

//--------------------------------------------------
// �o�͂Ƀe�L�X�g���o�͂���B
// ����  : pAngle / �p�x
//--------------------------------------------------
#define DEBUG_PRINT(...) _RPT_BASE(_CRT_WARN, __FILE__, __LINE__, NULL, __VA_ARGS__)
#else
#define DEBUG_PRINT(...) ((void)0)
#endif

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// �p�x�̐��K��
// ����  : pAngle / �p�x
//--------------------------------------------------
void NormalizeAngle(float *pAngle);

//--------------------------------------------------
// �z�[�~���O
// ����1  : D3DXVECTOR3 *pPosOut / �ʒu
// ����2  : D3DXVECTOR3 &posNow / ���݂̈ʒu
// ����3  : D3DXVECTOR3 &posDest / �ړI�̈ʒu
// ����4  : float fSpeed / ����
// �Ԓl  : bool / �ړI�̈ʒu�ɒ��������ǂ���
//--------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed);

//--------------------------------------------------
// �����_�̃����_��
// ����1  : float fMax / �ő�l
// ����2  : float fMin / �ŏ��l
// �Ԓl  : float / �����_���l
//--------------------------------------------------
float FloatRandom(float fMax, float fMin);

//--------------------------------------------------
// �����̃����_��
// ����1  : int nMax / �ő�l
// ����2  : int nMin / �ŏ��l
// �Ԓl  : int / �����_���l
//--------------------------------------------------
int IntRandom(int nMax, int nMin);

//--------------------------------------------------
// sin�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
// ����1  : int nTime / �^�C��
// ����2  : float fCycle / ����
// �Ԓl  : float / 1.0f�`0.0f��sin�J�[�u
//--------------------------------------------------
float SinCurve(int nTime, float fCycle);

//--------------------------------------------------
// cos�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
// ����1  : int nTime / �^�C��
// ����2  : float fCycle / ����
// �Ԓl  : float / 1.0f�`0.0f��cos�J�[�u
//--------------------------------------------------
float CosCurve(int nTime, float fCycle);

//--------------------------------------------------
// �J�[�u�̒l���A���Ă���
// ����1  : float fCurve / �J�[�u
// ����2  : float fMax / �ő�l
// ����3  : float fMin / �ŏ��l
// �Ԓl  : float / �J�[�u
//--------------------------------------------------
float Curve(float fCurve, float fMax, float fMin);

//--------------------------------------------------
// �͈͓�
// ����1  : D3DXVECTOR3* pPos / �ʒu
// ����2  : D3DXVECTOR3 range / �͈�
// �Ԓl  : bool / �͈͊O�ɏo�����ǂ���
//--------------------------------------------------
bool InRange(D3DXVECTOR3* pPos, const D3DXVECTOR3& range);

//--------------------------------------------------
// �͈͓��Ŕ���
// ����1  : D3DXVECTOR3* pPos / �ʒu
// ����2  : D3DXVECTOR3* pMove / �ړ���
// ����3  : D3DXVECTOR3 range / �͈�
// �Ԓl  : bool / �͈͊O�ɏo�����ǂ���
//--------------------------------------------------
bool InRangeReflect(D3DXVECTOR3* pPos, D3DXVECTOR3* pMove, const D3DXVECTOR3& range);

//--------------------------------------------------
// �~�̓����蔻��
// ����1  : D3DXVECTOR3& pos1 / �P�ڂ̈ʒu
// ����2  : float radius1 / �P�ڂ̔��a
// ����3  : D3DXVECTOR3& pos2 / �Q�ڂ̈ʒu
// ����4  : float radius2 / �Q�ڂ̔��a
// �Ԓl  : bool / �͈͊O�ɏo�����ǂ���
//--------------------------------------------------
bool CollisionCircle(const D3DXVECTOR3& pos1, float radius1, const D3DXVECTOR3& pos2, float radius2);

//--------------------------------------------------
// �G���A�̓����蔻��
// ����1  : D3DXVECTOR3& pos1 / �P�ڂ̈ʒu
// ����2  : float radius1 / �P�ڂ̔��a
// ����3  : D3DXVECTOR3* pPos2 / �Q�ڂ̈ʒu
// ����4  : float radius2 / �Q�ڂ̔��a
// �Ԓl  : bool / �͈͊O�ɏo�����ǂ���
//--------------------------------------------------
bool CollisionArea(const D3DXVECTOR3& pos1, float radius1, D3DXVECTOR3* pPos2, float radius2);

//--------------------------------------------------
// �o�b�t�@�̃R�s�[
// ����1  : IDirect3DVertexBuffer9* pBuf / �o�b�t�@
// ����2  : void* pSrc / �\�[�X
// ����3  : unsigned size / �\�[�X�̃T�C�Y
//--------------------------------------------------
void CopyBuf(IDirect3DVertexBuffer9* pBuf, void* pSrc, unsigned size);

//--------------------------------------------------
// ����
// ����  : int number / ��
// �Ԓl  : int / ����
//--------------------------------------------------
int Digit(int number);

#endif // !_UTILITY_H_
