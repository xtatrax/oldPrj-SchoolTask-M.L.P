/**************************************************************************
 CommonMesh.h

 class CommonMesh : public Object 宣言
 MyFactory; 宣言
                                                    2012/03/04　名前
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "TatraFactory/MeshItem.h"

namespace wiz{
/**************************************************************************
 class CommonMesh : public Object;
 用途: コモンメッシュクラス
****************************************************************************/
class CommonMesh : public Object{
protected:
    //メッシュ
    LPD3DXMESH m_pMesh;
	//影のメッシュ
    LPD3DXMESH m_pShadowMesh;
	//影ボリュームクラス
	ShadowVolume* m_pShadowVolume;
	//	: メッシュアイテム （ マテリアルとか
	MeshItem  m_MeshItem;

/**************************************************************************
 CommonMesh(
    D3DXVECTOR3 pos,				//位置
    D3DCOLORVALUE& Diffuse,			//ディフューズ色
    D3DCOLORVALUE& Specular,		//スペキュラ色
    D3DCOLORVALUE& Ambient			//アンビエント色
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
  CommonMesh(D3DXVECTOR3& center,D3DXVECTOR3& pos,D3DXVECTOR3& size ,
		D3DXVECTOR3& turn,D3DXVECTOR3& rot,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
/**************************************************************************
 virtual ~Plate();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~CommonMesh();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,				//オブジェクトの配列
    const CONTROLER_STATE* pCntlState	//コントローラのステータス
	Command& Com						//シーンからステージ、もしくはステージからオブジェクトに
										//渡されるコマンドの参照
 );
 用途: メッシュを描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com);
public:
/**************************************************************************
 D3DXVECTOR3 getPos() const;
 用途: 現在のポジションを得る
 戻り値: 現在のポジション
***************************************************************************/
	D3DXVECTOR3 getPos() const{
		return m_MeshItem.m_vPos;
	}
};
}