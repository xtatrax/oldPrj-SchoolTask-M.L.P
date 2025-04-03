/**************************************************************************
Texture.cpp

****************************************************************************/
#include "StdAfx.h"
#include "Texture.h"

namespace wiz{
/**************************************************************************
 Texture ��`��
****************************************************************************/
/**************************************************************************
 Texture::Texture(
	LPDIRECT3DDEVICE9 pD3DDevice,	//DirectX�f�o�C�X
	const wchar_t* filename	//�e�N�X�`���̃t�@�C����
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filename)
:m_pTexture(0){
	try{
		//�e�N�X�`���̍쐬
		if(FAILED(D3DXCreateTextureFromFile(pD3DDevice,filename,&m_pTexture))){
            // ���������s
            throw DxException(
                L"�e�N�X�`���ǂݍ��݂Ɏ��s���܂����B",
                L"Texture::Texture()"
                );
		}
	}
    catch(...){
        //�R���X�g���N�^��O����
        //��n��
        SafeRelease(m_pTexture);
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 Texture::Texture(
	LPDIRECT3DDEVICE9 pD3DDevice,	//DirectX�f�o�C�X
	const wchar_t* filename	//�e�N�X�`���̃t�@�C����
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wstring filename)
:m_pTexture(0)
{
	try{
		//�e�N�X�`���̍쐬
		if(FAILED(D3DXCreateTextureFromFile(pD3DDevice,filename.c_str(),&m_pTexture))){
            // ���������s
            throw DxException(
                L"�e�N�X�`���ǂݍ��݂Ɏ��s���܂����B",
                L"Texture::Texture()"
                );
		}
	}
    catch(...){
        //�R���X�g���N�^��O����
        //��n��
        SafeRelease(m_pTexture);
        //�ăX���[
        throw;
    }
}

/**************************************************************************
 Texture::~Texture();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Texture::~Texture(){
    //��n��
    SafeRelease(m_pTexture);
}


}
//end of namespace wiz.

