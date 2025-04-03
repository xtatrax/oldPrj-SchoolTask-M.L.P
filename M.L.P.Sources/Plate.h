/**************************************************************************
 Plate.h

 class Plate : public CommonMesh 宣言
                                                    2012/03/04　名前
****************************************************************************/
#pragma once
#include "CommonMesh.h"

namespace wiz{
/**************************************************************************
 class Plate : public CommonMesh;
 用途: 平板クラス（コントローラーで動作しない）
****************************************************************************/
class Plate : public CommonMesh{

protected:
/**************************************************************************
 void VecNomal2UV(
	D3DXVECTOR3 vec,	//頂点
	D3DXVECTOR3 normal,	//法線
	float& u,			//変換するu（テクスチャ上のU座標）
	float& v			//変換するv（テクスチャ上のV座標）
	);
 用途: Vectorと法線からUとVを作り出す
 戻り値: なし
 float& uとfloat& vに変換後の値を代入
***************************************************************************/
	void VecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v);
	LPDIRECT3DTEXTURE9 m_pTexture;
	//	テクスチャがある場合の頂点フォーマットの定義
	// D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	// を構造体化している
	struct  PlateVertex{
		D3DXVECTOR3 vec;
		D3DXVECTOR3 normal;
		FLOAT       tu,tv;
	};
	//Plate用のFVFをDIrectXAPIに渡すときのパラメータ
	enum { PlateFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
public:
/**************************************************************************
 Plate(
    LPDIRECT3DDEVICE9 pD3DDevice,		////IDirect3DDevice9インターフェイスへのポインタ
    D3DXVECTOR3 size,					//大きさ
    D3DXVECTOR3 pos,					//位置
    D3DCOLORVALUE& Diffuse,				//ディフューズ色
    D3DCOLORVALUE& Specular,			//スペキュラ色
    D3DCOLORVALUE& Ambient,				//アンビエント色
	LPDIRECT3DTEXTURE9 pTexture = 0		//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
    Plate(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3 pos,D3DXVECTOR3 size,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0);
/**************************************************************************
 virtual ~Plate();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~Plate();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,				//オブジェクトの配列
    const CONTROLER_STATE* pCntlState	//コントローラのステータス
 );
 用途: 平板を描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com);
};
}