/**************************************************************************
 Sp.h

 class Sp : public Object �錾
                                                    2012/04/26�@���O ���� �O
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Prim2D.h"
#include "../TatraFactory/SpriteItem.h"
namespace wiz{
/**************************************************************************
 class Sp : public Object;
 �p�r: �QD���̃X�v���C�g�N���X
 �����ڍ\�z�ł��Ȃ��悤�ɁA�R���X�g���N�^�A�f�X�g���N�^��protected�����o�ɂ���
 ��Draw()�֐����p�ӂ��Ȃ�
****************************************************************************/
class Sp : public Object{
protected:
	LPD3DXSPRITE	m_pSprite;		//	: �`�悷�邽�߂̃X�v���C�g
	SpriteItem		m_MeshItem;		//	: ���W�f�[�^�Ƃ��}�e���A���Ƃ��B�iSpriteItem�ɕύX�\��j
	Rect			m_Rect;			//	: �\������摜�͈̔�

public:
/**************************************************************************
 Sp(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
		wstring fileName,				//	: �t�@�C����
		Rect& m_Rect,					//	: �e�N�X�`���̕`��͈�
		D3DXVECTOR3& m_vCenter,			//	: ���S�ʒu
		D3DXVECTOR3& m_vPos,			//	: �\���ʒu
		D3DXVECTOR3& m_vOffsetPos,		//	: ���[�J�����W
		D3DXVECTOR3& m_vScale,			//	: �L�k
		D3DXVECTOR3& m_vRot				//	: ��]
	);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	Sp(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* Rect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vPos,D3DXVECTOR3& vOffsetPos,
			D3DXVECTOR3& vScale,D3DXVECTOR3& vRot);
/**************************************************************************
 ~Sp();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~Sp();
	virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
		vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);




};


}
//end of namespace wiz.
