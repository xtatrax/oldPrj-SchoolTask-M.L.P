/**************************************************************************
 BGPlate.h

 class BGPlate : public Plate 宣言
                                                    2012/03/04　名前
****************************************************************************/
#pragma once
#include "../Plate.h"

namespace wiz{
/**************************************************************************
 class BGPlate : public Plate;
 用途: 複数の直方体クラス（コントローラで動作しない）
****************************************************************************/
class BGPlate : public Plate{
protected:
	struct PlateItem{
		MeshItem m_MeshItem;

		//派生クラスを作ってもClear()関数で
		//削除できるように仮想デストラクタにしておく
		virtual ~PlateItem(){}
		PlateItem(D3DXVECTOR3& center,D3DXVECTOR3& pos,D3DXVECTOR3& size ,
		D3DXVECTOR3& turn,D3DXVECTOR3& rot,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
			:m_MeshItem(center,pos,size,turn,rot,Diffuse,Specular,Ambient){}
	};
	vector<PlateItem*> m_ItemVec;
/**************************************************************************
 void Clear();
 用途:Itemの破棄
 戻り値: なし
***************************************************************************/
	void Clear();
/**************************************************************************
 virtual D3DXVECTOR3 getMove(vector<PlateItem*>::size_type index);
 用途: プレートが移動してる場合や傾いている場合に、ヒット先が移動すべきベクトル
 戻り値: ベクトル
***************************************************************************/
 virtual D3DXVECTOR3 getMove(vector<PlateItem*>::size_type index);
public:
/**************************************************************************
 BGPlate(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
    BGPlate(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0);
/**************************************************************************
 virtual ~BGPlate();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~BGPlate();
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
 void AddPlate(
    D3DXVECTOR3 size,               //大きさ
    D3DXVECTOR3 pos,                //最初の位置
	D3DXVECTOR3 rot,				//回転。
    D3DCOLORVALUE Diffuse,         //ディフューズ色
    D3DCOLORVALUE Specular,            //スペキュラ色
    D3DCOLORVALUE Ambient          //アンビエント色
    );
 用途: プレートを追加
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
    void AddPlate(D3DXVECTOR3 size,D3DXVECTOR3 pos,D3DXVECTOR3 rot,
     D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient);
/**************************************************************************
	virtual void DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect,			//エフェクトのポインタ
	D3DXMATRIX& mCameraView,			//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
 用途: 影ボリュームを描画（仮想関数）
 戻り値: なし。
***************************************************************************/
	virtual void DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
		D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);


};
}