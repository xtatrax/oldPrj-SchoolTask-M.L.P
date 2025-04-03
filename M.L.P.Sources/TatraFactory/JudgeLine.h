/**************************************************************************
 JudgeLine.h

 class JudgeLine : public Plate 宣言
                                                    2012/03/04　名前 鴫原 徹
****************************************************************************/
#pragma once
#include "../MultiPlate.h"
#include "../Sound.h"

namespace wiz{
/**************************************************************************
 class JudgeLine : public Plate;
 用途: 判定ラインクラス
****************************************************************************/
class JudgeLine : public Plate{
protected:
public:
/**************************************************************************
 JudgeLine(
    LPDIRECT3DDEVICE9 pD3DDevice,	//IDirect3DDevice9インターフェイスへのポインタ
	D3DXVECTOR3 pos,				//	: 座標
	D3DXVECTOR3 size,				//	: 伸縮率
	D3DCOLORVALUE& Diffuse,			//	: 拡散反射光
	D3DCOLORVALUE& Specular,		//	: 鏡面反射光
	D3DCOLORVALUE& Ambient,			//	: 環境光
	LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
JudgeLine(
		LPDIRECT3DDEVICE9 pD3DDevice,
		D3DXVECTOR3 pos,
		D3DXVECTOR3 size,
        D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Specular,
		D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0);
/**************************************************************************
 virtual ~JudgeLine();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~JudgeLine();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,				//オブジェクトの配列
    const CONTROLER_STATE* pCntlState	//コントローラのステータス
	Command& Com						//シーンからステージ、もしくはステージからオブジェクトに
										//渡されるコマンドの参照
 );
 用途: 直方体を描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com);
/**************************************************************************
 OBB getObb();
 用途: OBB算出
 戻り値: このインスタンスのOBB
***************************************************************************/
	OBB getObb(float i_fSize = 0.5f){
		return m_MeshItem.getObb(i_fSize);
	}
};
}