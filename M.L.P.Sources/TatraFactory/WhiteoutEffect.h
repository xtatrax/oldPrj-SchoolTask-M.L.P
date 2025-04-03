/**************************************************************************
 WhiteoutEffect.h

 class WhiteoutEffect : public Plate 宣言
                                                    2012/06/21　名前 鴫原 徹
****************************************************************************/
#pragma once
#include "../Sprite.h"
#include "../Sound.h"
namespace wiz{
/**************************************************************************
 class WhiteoutEffect : public Plate;
 用途: 複数の直方体クラス（コントローラで動作しない）
****************************************************************************/
class WhiteoutEffect : public Sprite{
protected:
	bool	m_bWhiteout;
	bool	m_bComplete;
	bool	m_bWhiteWait;
	float	m_fTimeAccumulator;
	float	m_fAddAlpha;
	float	m_fAlphaBuffer;
public:
/**************************************************************************
 WhiteoutEffect(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
WhiteoutEffect(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,
			   float fWhiteoutTime,D3DCOLOR Color);
/**************************************************************************
 virtual ~WhiteoutEffect();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~WhiteoutEffect();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
 );
 用途: 直方体を描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com);
/**************************************************************************
 virtual ~WhiteoutEffect();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	void setWhiteout(){
		m_bWhiteout = true;
	};
	bool getCompleteFlag(){
		return m_bComplete;
	}

};
}