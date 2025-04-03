/**************************************************************************
 Texture.h

 Texture ; �錾
                                                    2012/03/04
****************************************************************************/


#pragma once

#include "StdAfx.h"
namespace wiz{
/**************************************************************************
 class Texture;
 �p�r: �e�N�X�`���̃��b�s���O�N���X
****************************************************************************/
class Texture{
	LPDIRECT3DTEXTURE9 m_pTexture;
public:
/**************************************************************************
 Texture(
	LPDIRECT3DDEVICE9 pD3DDevice,	//DirectX�f�o�C�X
	const wchar_t* filename	//�e�N�X�`���̃t�@�C����
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filename);
/**************************************************************************
 Texture(
	LPDIRECT3DDEVICE9 pD3DDevice,	//DirectX�f�o�C�X
	const wstring filename	//�e�N�X�`���̃t�@�C����
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wstring filename);
/**************************************************************************
 ~Texture();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Texture();
/**************************************************************************
 const LPDIRECT3DTEXTURE9 getTexture() const
 �p�r: �A�N�Z�b�T
 �߂�l: �Ȃ�
***************************************************************************/
	const LPDIRECT3DTEXTURE9 getTexture() const{
		return m_pTexture;
	}
};

}
//end of namespace wiz.

