/**************************************************************************
 ButtonPlate.cpp

 ButtonPlate; 定義
                                                    2012/03/04　名前 鴫原 徹
****************************************************************************/
#include "StdAfx.h"
#include "ButtonPlate.h"
#include "TatraFactory/Button.h"

namespace wiz{



/**************************************************************************
 ButtonPlate 定義部
****************************************************************************/
/**************************************************************************
 ButtonPlate::ButtonPlate(
    LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
	DWORD Cmd,						//選択実行されたときのコマンド
	DWORD Index,					//メニューステージ上のインデックス
    D3DXVECTOR3 size,               //大きさ
    D3DXVECTOR3 pos,                //位置
    D3DCOLORVALUE& Diffuse,         //ディフューズ色
    D3DCOLORVALUE& Specular,		//スペキュラ色
    D3DCOLORVALUE& Ambient,			//アンビエント色
	LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし
****************************************************************************/
ButtonPlate::ButtonPlate(
	LPDIRECT3DDEVICE9 pD3DDevice,
	DWORD Cmd,
	DWORD Index,
	D3DXVECTOR3 pos,
	D3DXVECTOR3 size,
	D3DCOLORVALUE& Diffuse,
	D3DCOLORVALUE& Specular,
	D3DCOLORVALUE& Ambient,
	LPDIRECT3DTEXTURE9 pTexture)
:Plate(pD3DDevice,size,pos,Diffuse,Specular,Ambient,pTexture),
m_ButtonPrm(Cmd,Index)
{
}
/**************************************************************************
 virtual ~ButtonPlate::ButtonPlate();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ButtonPlate::~ButtonPlate(){

}

/**************************************************************************
 virtual void ButtonPlate::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,				//オブジェクトの配列
    const CONTROLER_STATE* pCntlState	//コントローラのステータス
	Command& Com						//シーンからステージ、もしくはステージからオブジェクトに
										//渡されるコマンドの参照
 );
 用途: 直方体を描画
 戻り値: なし。
***************************************************************************/
void ButtonPlate::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	   vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){

	if(m_ButtonPrm.getSelect()){
		//ボタンクラスのマティリアル
        D3DCOLORVALUE Plate1Diffuse		= {1.0f,0.0f,0.0f,1.0f};
        D3DCOLORVALUE Plate1Specular	= {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE Plate1Ambient		= {1.0f,0.2f,0.2f,0.2f};
		m_MeshItem.setMaterial(Plate1Diffuse,Plate1Specular,Plate1Ambient);

	}else{
		//ボタンクラスのマティリアル
        D3DCOLORVALUE Plate1Diffuse		= {0.8f,0.8f,0.8f,1.0f};
        D3DCOLORVALUE Plate1Specular	= {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE Plate1Ambient		= {0.2f,0.2f,0.2f,0.2f};
		m_MeshItem.setMaterial(Plate1Diffuse,Plate1Specular,Plate1Ambient);
	
	}
		   
	// マトリックスをレンダリングパイプラインに設定
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
	//テクスチャがある場合
	if(m_pTexture){
		DWORD wkdword;
		//現在のテクスチャステータスを得る
		pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//ステージの設定
		pD3DDevice->SetTexture(0,m_pTexture);
		//デフィーズ色とテクスチャを掛け合わせる設定
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		pD3DDevice->SetFVF(PlateFVF);
		// マトリックスをレンダリングパイプラインに設定
		pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(pD3DDevice,Vec,pCntlState,Com);
		pD3DDevice->SetTexture(0,0);
		//ステージを元に戻す
		pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
	//テクスチャがない場合
		// マトリックスをレンダリングパイプラインに設定
		pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(pD3DDevice,Vec,pCntlState,Com);
	}
	if(m_ButtonPrm.getBoot()){
		//コマンド発行
		Com = m_ButtonPrm.CommandIssue();
	}
}

/**************************************************************************
	virtual void ButtonPlate::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,	//IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect,		//エフェクトのポインタ
	D3DXMATRIX& mCameraView,		//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
 用途: 影ボリュームを描画（仮想関数）
 戻り値: なし。
***************************************************************************/
void ButtonPlate::DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
	D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj){
	if(m_pShadowVolume){

		//オブジェクトのワールド行列をカメラ視線にして登録
		D3DXMATRIX WorldView;
		WorldView =  m_MeshItem.getMatrix()  * mCameraView;
		pEffect->SetMatrix("g_mWorldView",&WorldView);
		//カメラのプロジェクトまで含んだ行列を登録
		WorldView = WorldView * mCameraProj;
		pEffect->SetMatrix("g_mWorldViewProjection",&WorldView);
		//影ボリュームの描画
		m_pShadowVolume->Draw(pD3DDevice,pEffect);
	}
}



}
//end of namespace wiz.
