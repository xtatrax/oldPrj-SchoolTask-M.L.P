/**************************************************************************
 JudgeLine.cpp

 JudgeLine; 定義
                                                    2012/03/04　名前 
****************************************************************************/
#include "StdAfx.h"
#include "JudgeLine.h"
#include "../Stage_Play.h"
namespace wiz{
/**************************************************************************
 JudgeLine 定義部
***************************************************************************/


/**************************************************************************
 JudgeLine::JudgeLine(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
JudgeLine::JudgeLine(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3 pos,D3DXVECTOR3 size,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture)
	:Plate( pD3DDevice, pos, size, Diffuse, Specular, Ambient ,pTexture)
{
    try{
		
    }
    catch(...){
        //コンストラクタ例外発生
        //再スロー
        throw;
    }
}
/**************************************************************************
 virtual ~JudgeLine();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
JudgeLine::~JudgeLine(){
}

/**************************************************************************
 void JudgeLine::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
 );
 用途: 直方体を描画（コントローラ反応無し）
 戻り値: なし。
***************************************************************************/
void JudgeLine::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){

	static bool input = false;
    //移動用(動的には変化しない)
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
		// マトリックスをレンダリングパイプラインに設定
		pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(pD3DDevice,Vec,pCntlState,Com);
	}

}


}