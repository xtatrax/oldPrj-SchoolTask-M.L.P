/**************************************************************************
 WhiteoutEffect.cpp

 WhiteoutEffect; 定義
                                                    2012/06/21　名前 鴫原 徹
****************************************************************************/
#include "StdAfx.h"
#include "WhiteoutEffect.h"
#include "../Stage_Play.h"
namespace wiz{
/**************************************************************************
 WhiteoutEffect 定義部
***************************************************************************/
/**************************************************************************
 WhiteoutEffect::WhiteoutEffect(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9インターフェイスへのポインタ
	LPDIRECT3DTEXTURE9 pTexture = 0		//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
WhiteoutEffect::WhiteoutEffect(LPDIRECT3DDEVICE9 pD3DDevice,
					wstring fileName,float fWhiteoutTime,D3DCOLOR Color)
	:Sprite( pD3DDevice, fileName, NULL,g_vZero,g_vZero,g_vZero,g_vOne,g_vZero,Color),
	 m_bWhiteout(false),m_bComplete(false),m_bWhiteWait(false),
	 m_fAlphaBuffer(0),m_fTimeAccumulator(0)
{
    try{
		m_fAddAlpha =  0xFF / fWhiteoutTime;

    }
    catch(...){
        //コンストラクタ例外発生
        //再スロー
        throw;
    }
}
/**************************************************************************
 virtual ~WhiteoutEffect();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
WhiteoutEffect::~WhiteoutEffect(){
}

/**************************************************************************
 void WhiteoutEffect::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,				//オブジェクトの配列
    const CONTROLER_STATE* pCntlState	//コントローラのステータス
 );
 用途: 直方体を描画（コントローラ反応無し）
 戻り値: なし。
***************************************************************************/
void WhiteoutEffect::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){



	if(m_bWhiteWait){
		if((m_fTimeAccumulator += Tempus::getOneFrameTime()) >= 1.0f){
			m_bComplete = true;
		}
	}else
	if(m_bWhiteout){
		if( (m_fAlphaBuffer += m_fAddAlpha * Tempus::getOneFrameTime()) >= 255){
			m_bWhiteWait = true;
		}else{
			m_SpriteItem.m_Color.m_ByteColor.a =  (int)m_fAlphaBuffer;
		}
	}
	


	Sprite::Draw( pD3DDevice, Vec, pCntlState, Com);
}


}