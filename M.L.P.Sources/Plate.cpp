/**************************************************************************
 Plate.cpp

 Plate; 定義
                                                    2012/03/04　名前 鴫原 徹
****************************************************************************/
#include "StdAfx.h"
#include "Plate.h"

namespace wiz{
/**************************************************************************
 Plate 定義部
***************************************************************************/
/**************************************************************************
 void Plate::VecNomal2UV(
	D3DXVECTOR3 vec,		//頂点
	D3DXVECTOR3 normal,		//法線
	float& u,				//変換するu（テクスチャ上のU座標）
	float& v				//変換するv（テクスチャ上のV座標）
	); 
 用途: Vectorと法線からUとVを作り出す
 戻り値: なし
 float& uとfloat& vに変換後の値を代入
***************************************************************************/
void Plate::VecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v){
	if((normal.x < 0 && vec.y > 0 &&  vec.z > 0) 
		|| (normal.x > 0 && vec.y > 0 &&  vec.z < 0)
		|| (normal.z < 0 && vec.y > 0 &&  vec.x < 0)
		|| (normal.z > 0 && vec.y > 0 &&  vec.x > 0)
		|| (normal.y > 0 && vec.x < 0 &&  vec.z > 0)
		|| (normal.y < 0 && vec.x < 0 &&  vec.z < 0)){
			u = 0;
			v = 0;
	}
	else if((normal.x < 0 && vec.y < 0 &&  vec.z > 0) 
		|| (normal.x > 0 && vec.y < 0 &&  vec.z < 0)
		|| (normal.z < 0 && vec.y < 0 &&  vec.x < 0)
		|| (normal.z > 0 && vec.y < 0 &&  vec.x > 0)
		|| (normal.y > 0 && vec.x < 0 &&  vec.z < 0)
		|| (normal.y < 0 && vec.x < 0 &&  vec.z > 0)){
		u = 0;
		v = 1.0f;
	}
	else if((normal.x < 0 && vec.y > 0 &&  vec.z < 0) 
		|| (normal.x > 0 && vec.y > 0 &&  vec.z > 0)
		|| (normal.z < 0 && vec.y > 0 &&  vec.x > 0)
		|| (normal.z > 0 && vec.y > 0 &&  vec.x < 0)
		|| (normal.y > 0 && vec.x > 0 &&  vec.z > 0)
		|| (normal.y < 0 && vec.x > 0 &&  vec.z < 0)){
		u = 1.0f;
		v = 0.0f;
	}
	else{
		u = 1.0f;
		v = 1.0f;
	}
}

/**************************************************************************
 Plate::Plate(
    LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
    D3DXVECTOR3 size,				//大きさ
    D3DXVECTOR3 pos,				//位置
    D3DCOLORVALUE& Diffuse,			//ディフューズ色
    D3DCOLORVALUE& Specular,		//スペキュラ色
    D3DCOLORVALUE& Ambient,			//アンビエント色
	LPDIRECT3DTEXTURE9 pTexture = 0	//	テクスチャ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
Plate::Plate(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3 pos,D3DXVECTOR3 size,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture)
    :CommonMesh(g_vZero,pos,size,g_vZero,g_vZero,Diffuse,Specular,Ambient),m_pTexture(pTexture)
{
    try{
		//平板の作成
		if(FAILED(D3DXCreateBox(pD3DDevice, 
						size.x,
						size.y,
						size.z,
						&m_pMesh, 
						NULL))){
			// 初期化失敗
			throw DxException(
				L"平板の作成に失敗しました。",
				L"Plate::Plate()"
				);
		}
		//テクスチャがある場合
		if(m_pTexture){
			LPD3DXMESH m_pMesh2 = 0;
			//作成されたメッシュを元に、テクスチャつきのメッシュを作成
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,PlateFVF,pD3DDevice,&m_pMesh2))){
				// 初期化失敗
				throw DxException(
					L"テクスチャ付の平板の作成に失敗しました。",
					L"Plate::Plate()"
					);
			}
			//もうもとのメッシュはいらないので削除
	        SafeRelease(m_pMesh);
			m_pMesh = m_pMesh2;
			m_pMesh2 = 0;
			//テクスチャ上の座標をマッピング
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			PlateVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			DWORD vsize = m_pMesh->GetNumVertices();
			for(DWORD n = 0;n < vsize;n++){ //頂点の数を取得する
				//法線と頂点からuv値を得る
				VecNomal2UV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
			}
			pVB->Unlock();
		}
		//影ボリュームを作成
		m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
    }
    catch(...){
        //コンストラクタ例外発生
        //後始末
	    SafeDelete(m_pShadowVolume);
        SafeRelease(m_pMesh);
        SafeRelease(m_pShadowMesh);
        //再スロー
        throw;
    }
}
/**************************************************************************
 Plate::~Plate();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Plate::~Plate(){
    //後始末（メッシュのReleaseは
	//CommonMeshで行なうので、本来はしなくても良い。
	//しても問題ない
    SafeDelete(m_pShadowVolume);
    SafeRelease(m_pMesh);
    SafeRelease(m_pShadowMesh);
	//SafeRelease(m_pTexture);
}

/**************************************************************************
 void Plate::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,				//オブジェクトの配列
    const CONTROLER_STATE* pCntlState	//コントローラのステータス
 );
 用途: 直方体を描画（コントローラ反応無し）
 戻り値: なし。
***************************************************************************/
void Plate::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){
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