/**************************************************************************
Texture.cpp

****************************************************************************/
#include "StdAfx.h"
#include "Texture.h"

namespace wiz{
/**************************************************************************
 Texture 定義部
****************************************************************************/
/**************************************************************************
 Texture::Texture(
	LPDIRECT3DDEVICE9 pD3DDevice,	//DirectXデバイス
	const wchar_t* filename	//テクスチャのファイル名
);
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filename)
:m_pTexture(0){
	try{
		//テクスチャの作成
		if(FAILED(D3DXCreateTextureFromFile(pD3DDevice,filename,&m_pTexture))){
            // 初期化失敗
            throw DxException(
                L"テクスチャ読み込みに失敗しました。",
                L"Texture::Texture()"
                );
		}
	}
    catch(...){
        //コンストラクタ例外発生
        //後始末
        SafeRelease(m_pTexture);
        //再スロー
        throw;
    }
}
/**************************************************************************
 Texture::Texture(
	LPDIRECT3DDEVICE9 pD3DDevice,	//DirectXデバイス
	const wchar_t* filename	//テクスチャのファイル名
);
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wstring filename)
:m_pTexture(0)
{
	try{
		//テクスチャの作成
		if(FAILED(D3DXCreateTextureFromFile(pD3DDevice,filename.c_str(),&m_pTexture))){
            // 初期化失敗
            throw DxException(
                L"テクスチャ読み込みに失敗しました。",
                L"Texture::Texture()"
                );
		}
	}
    catch(...){
        //コンストラクタ例外発生
        //後始末
        SafeRelease(m_pTexture);
        //再スロー
        throw;
    }
}

/**************************************************************************
 Texture::~Texture();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Texture::~Texture(){
    //後始末
    SafeRelease(m_pTexture);
}


}
//end of namespace wiz.

