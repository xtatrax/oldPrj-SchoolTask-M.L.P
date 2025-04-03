/**************************************************************************
 MeshItem.h

 MeshItem ; 宣言
                                                    2012/03/04　名前 鴫原 徹
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Texture.h"

namespace wiz{ 
/**************************************************************************
 class MeshItem;
 用途: 座標系情報やマテリアルなどをラッピングするクラス
****************************************************************************/
class MeshItem{
private:
	// :検証用
	
public:
	// :名前
	wstring	m_MeshItemName;
	
	// :テクスチャ/0～1
	//LPDIRECT3DTEXTURE9		m_pTextuer;

	// :ロケート用のクオータニオン
    D3DXQUATERNION	m_RotQt;
	
	// :ターン用のクオータニオン
    D3DXQUATERNION	m_TurnQt;
	
	// :物体上の中心とする位置
	D3DXVECTOR3		m_vCenter;
	
	// :オブジェクトの位置
	D3DXVECTOR3		m_vPos;
	
	// :サイズ
	D3DXVECTOR3		m_vSize;

	// :マテリアル
	D3DMATERIAL9	m_pMaterial;

public:
/**************************************************************************
 MeshItem(MeshItem& pMeshItem);
 用途: コピーコンストラクタ
 戻り値: なし
***************************************************************************/
	MeshItem(MeshItem& pMeshItem);
/**************************************************************************
 MeshItem::MeshItem(
		wstring name,				//	: オブジェの名前
		D3DXVECTOR3& center,		//	: 中心となる位置 (オリジナルゼロのからのオフセット座標)
		D3DXVECTOR3& pos,			//	: 描画位置
		D3DXVECTOR3& size ,			//	: 大きさの比
		D3DXVECTOR3& turn,			//	: ターン	(自転)
		D3DXVECTOR3& rot			//	: ロケート	(公転)
		D3DCOLORVALUE& Diffuse,		//	: 操作中のディフューズ色
		D3DCOLORVALUE& Specular,	//	: 操作中のスペキュラ色
		D3DCOLORVALUE& Ambient,		//	: 操作中のアンビエント色
);							   
 用途: コンストラクタ(色付)
 戻り値: なし
***************************************************************************/
	MeshItem(//wstring name,
		D3DXVECTOR3& center,D3DXVECTOR3& pos,D3DXVECTOR3& size ,
		D3DXVECTOR3& turn,D3DXVECTOR3& rot,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
/**************************************************************************
 MeshItem::MeshItem(
		wstring name,				//	: オブジェの名前
		D3DXVECTOR3& center,		//	: 中心となる位置 (オリジナルゼロのからのオフセット座標)
		D3DXVECTOR3& pos,			//	: 描画位置
		D3DXVECTOR3& size ,			//	: 大きさの比
		D3DXVECTOR3& turn,			//	: ターン	(自転)
		D3DXVECTOR3& rot			//	: ロケート	(公転)
);							   
 用途: コンストラクタ(色無)
		
 戻り値: なし
***************************************************************************/
	MeshItem(//wstring name,
		D3DXVECTOR3& center,D3DXVECTOR3& pos,D3DXVECTOR3& size ,
		D3DXVECTOR3& turn,D3DXVECTOR3& rot);
	void Delete();
/**************************************************************************
~MeshItem();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~MeshItem();

/**************************************************************************
D3DXMATRIX getMatrix();
 用途: マトリックス算出
 戻り値: 算出されたマトリックス
***************************************************************************/
	D3DXMATRIX getMatrix();

/**************************************************************************
D3DXMATRIX getMatrix(
		MeshItem& i_other	//	: 親となるもののアイテム
	);
 用途: 他MeshItem影響マトリックスの算出
 戻り値: 算出されたマトリックス
***************************************************************************/
	D3DXMATRIX getMatrix(MeshItem& i_other);
	
/**************************************************************************
OBB getObb(float size);
 用途: OBB算出
 戻り値: 算出されたOBB
***************************************************************************/
	OBB getObb(float size = 0.5f);
/**************************************************************************
D3DMATERIAL9 getMaterial();
 用途: マテリアルを返す
 戻り値: 自分のマテリアル
***************************************************************************/
	D3DMATERIAL9& getMaterial();
/**************************************************************************
void setMaterial(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
 用途: Materialの設定
 戻り値: マテリアル
***************************************************************************/
	void setMaterial(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);

/**************************************************************************
MeshItem& operator =(MeshItem& i_OtherMeshItem);
 用途: コピー
 戻り値: this
***************************************************************************/
	MeshItem& operator =(MeshItem& i_OtherMeshItem);


	

};
typedef MeshItem FORMITEM;
}