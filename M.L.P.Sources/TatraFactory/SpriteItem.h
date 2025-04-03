/**************************************************************************
 SpriteItem.h

 SpriteItem ; �錾
                                                    2012/03/04�@���O ���� �O
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Texture.h"
#include "../Prim2D.h"

namespace wiz{ 

/**************************************************************************
 class SpriteItem;
 �p�r: ���W�n����}�e���A���Ȃǂ����b�s���O����N���X
****************************************************************************/
class SpriteItem{
public:
	// :���O
	wstring				m_SpriteItemName;
		
	// :�e�N�X�`��
	Texture				m_Textuer;

	// :�e�N�X�`���`��͈�
	Rect*				m_pRect;

	// :���P�[�g�p�̃N�I�[�^�j�I��
    D3DXQUATERNION		m_RotQt;
	
	// :�^�[���p�̃N�I�[�^�j�I��
    D3DXQUATERNION		m_TurnQt;
	
	// :���̏�̒��S�Ƃ���ʒu
	D3DXVECTOR3			m_vCenter;
	
	// :�I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3			m_vPos;

	// :�I�t�Z�b�g
	D3DXVECTOR3			m_vOffsetPos;

	// :�T�C�Y
	D3DXVECTOR3			m_vSize;

	union MLPCOLOR{
		// :�F
		D3DCOLOR		m_DwordColor;
		struct{
			BYTE		b;
			BYTE		g;
			BYTE		r;
			BYTE		a;
		}m_ByteColor;
		MLPCOLOR(){};
		MLPCOLOR(D3DCOLOR i_COLOR)
			:m_DwordColor(i_COLOR)
		{};
	}m_Color;

public:
/**************************************************************************
 SpriteItem(SpriteItem& pMeshItem);
 �p�r: �R�s�[�R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	SpriteItem(SpriteItem& pMeshItem);
/**************************************************************************
 SpriteItem::SpriteItem(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: 
		wstring fileName,				//	: �e�N�X�`���̖��O
		Rect* rect,						//	: �`��͈�
		D3DXVECTOR3& center,			//	: ���S�ƂȂ�ʒu (�I���W�i���[���̂���̃I�t�Z�b�g���W)
		D3DXVECTOR3& pos,				//	: �`��ʒu
		D3DXVECTOR3& vOffsetPos,		//	: �Y��
		D3DXVECTOR3& size ,				//	: �傫���̔�
		D3DXVECTOR3& rot,				//	: ���P�[�g	(���])
		D3DCOLOR color					//	: �F
);							   
 �p�r: �R���X�g���N�^(�F�t)
 �߂�l: �Ȃ�
***************************************************************************/
	SpriteItem(//wstring name,
		LPDIRECT3DDEVICE9 pD3DDevice,
		wstring fileName,
		Rect* rect,
		D3DXVECTOR3& center,
		D3DXVECTOR3& pos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& size ,
		D3DXVECTOR3& rot,
		D3DCOLOR color = 0xFFFFFFFF);
	void Delete();
/**************************************************************************
~SpriteItem();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~SpriteItem();

/**************************************************************************
D3DXMATRIX getMatrix();
 �p�r: �}�g���b�N�X�Z�o
 �߂�l: �Z�o���ꂽ�}�g���b�N�X
***************************************************************************/
	D3DXMATRIX getMatrix();

/**************************************************************************
D3DXMATRIX getMatrix(
		SpriteItem& i_other	//	: �e�ƂȂ���̂̃A�C�e��
	);
 �p�r: ��SpriteItem�e���}�g���b�N�X�̎Z�o
 �߂�l: �Z�o���ꂽ�}�g���b�N�X
***************************************************************************/
	D3DXMATRIX getMatrix(SpriteItem& i_other);

/**************************************************************************
 SpriteItem& operator =(
	SpriteItem& i_OtherMeshItem		//	: ���̃C���X�^��
 );
 �p�r: �R�s�[
 �߂�l: this
***************************************************************************/
	SpriteItem& operator =(SpriteItem& i_OtherMeshItem);

	

};
}