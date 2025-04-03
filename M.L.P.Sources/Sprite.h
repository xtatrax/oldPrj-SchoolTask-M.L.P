/**************************************************************************
 Sprite.h

 class Sprite : public Object �錾
                                                    2012/04/26�@���O ���� �O
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Prim2D.h"
#include "TatraFactory/SpriteItem.h"
namespace wiz{
/**************************************************************************
 class Sprite : public Object;
 �p�r: �QD���̃X�v���C�g�N���X
 �����ڍ\�z�ł��Ȃ��悤�ɁA�R���X�g���N�^�A�f�X�g���N�^��protected�����o�ɂ���
 ��Draw()�֐����p�ӂ��Ȃ�
****************************************************************************/
class Sprite : public Object{
protected:
	LPD3DXSPRITE	m_pSprite;		//	: �`�悷�邽�߂̃X�v���C�g
	SpriteItem		m_SpriteItem;	//	: ���W�f�[�^�Ƃ��}�e���A���Ƃ��B�iSpriteItem�ɕύX�\��j

public:
/**************************************************************************
 Sprite(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
		wstring			fileName,		//	: �t�@�C����
		Rect&			Rect,			//	: �e�N�X�`���̕`��͈�
		D3DXVECTOR3&	vCenter,		//	: ���S�ʒu
		D3DXVECTOR3&	vPos,			//	: �\���ʒu
		D3DXVECTOR3&	vOffsetPos,		//	: ���[�J�����W
		D3DXVECTOR3&	vScale,			//	: �L�k
		D3DXVECTOR3&	vRot,			//	: ��]
		D3DCOLOR		color			//	: �F
	);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	Sprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* Rect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vPos,D3DXVECTOR3& vOffsetPos,
			D3DXVECTOR3& vScale,D3DXVECTOR3& vRot,D3DCOLOR color = 0xFFFFFFFF);
/**************************************************************************
 ~Sprite();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~Sprite();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,	//�R���g���[���̃X�e�[�^�X
	Command& Com						//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �I�u�W�F�N�g��`��
 �߂�l: �Ȃ��B
***************************************************************************/
	virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
		vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);




};


}
//end of namespace wiz.
