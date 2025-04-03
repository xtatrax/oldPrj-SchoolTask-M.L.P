/**************************************************************************
 Plate.cpp

 Plate; 定義
                                                    2012/03/04　名前 
****************************************************************************/
#include "StdAfx.h"
#include "BGPlate.h"

namespace wiz{
/**************************************************************************
 BGPlate 定義部
***************************************************************************/

/**************************************************************************
 void BGPlate::Clear();
 用途:Itemの破棄
 戻り値: なし
***************************************************************************/
void BGPlate::Clear(){
	vector<PlateItem*>::iterator it;
    for(it = m_ItemVec.begin();it != m_ItemVec.end();it++){
        SafeDelete(*it);
    }
    m_ItemVec.clear();
	//*テクスチャはリリースしてはいけない
}

/**************************************************************************
 virtual D3DXVECTOR3 BGPlate::getMove(vector<PlateItem*>::size_type index);
 用途: プレートが移動してる場合や傾いている場合に、ヒット先が移動すべきベクトル
 戻り値: ベクトル
***************************************************************************/
D3DXVECTOR3 BGPlate::getMove(vector<PlateItem*>::size_type index){
	D3DXVECTOR3 ret(0,0,0);
	if(m_ItemVec[index]->m_MeshItem.m_RotQt.x != 0 || m_ItemVec[index]->m_MeshItem.m_RotQt.y != 0
		|| m_ItemVec[index]->m_MeshItem.m_RotQt.z){
		ret.x = -0.1f * sin(m_ItemVec[index]->m_MeshItem.m_RotQt.z);
		ret.y = -0.05f;
		ret.z = -0.1f * sin(m_ItemVec[index]->m_MeshItem.m_RotQt.x);
	}
	return ret;
}


/**************************************************************************
 BGPlate::BGPlate(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
BGPlate::BGPlate(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture)
	:Plate(pD3DDevice,
		D3DXVECTOR3(0.0f,0.0f,0.0f),
		D3DXVECTOR3(1.0f,1.0f,1.0f),
		D3DCOLORVALUE(),
		D3DCOLORVALUE(),
		D3DCOLORVALUE(),pTexture){
    try{
    }
    catch(...){
        //コンストラクタ例外発生
        //再スロー
        throw;
    }
}
/**************************************************************************
 virtual ~BGPlate();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
BGPlate::~BGPlate(){
	Clear();
}

/**************************************************************************
 virtual void BGPlate::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
 );
 用途: 直方体を描画
 戻り値: なし。
***************************************************************************/
void BGPlate::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){
    //配置オブジェクトの描画
    vector<PlateItem*>::size_type sz = m_ItemVec.size();
    for(vector<PlateItem*>::size_type i = 0;i < sz;i++){
		//CommonMeshクラスのマティリアルを設定
		m_MeshItem = m_ItemVec[i]->m_MeshItem;

		//プレートを移動させる
		m_ItemVec[i]->m_MeshItem.m_vPos.x	-= 0.2f;
		if(m_ItemVec[i]->m_MeshItem.m_vPos.x < -10.0f)	m_ItemVec[i]->m_MeshItem.m_vPos.x	= 10.0f;

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
    }
}

/**************************************************************************
 void BGPlate::AddPlate(
    D3DXVECTOR3 size,               //大きさ
    D3DXVECTOR3 pos,                //最初の位置
	D3DXVECTOR3 rot,				//回転、x=x軸回転角度,y=y軸回転角度,z=z軸回転角度。
    D3DCOLORVALUE Diffuse,         //ディフューズ色
    D3DCOLORVALUE Specular,            //スペキュラ色
    D3DCOLORVALUE Ambient          //アンビエント色
    );
 用途: プレートを追加
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
void BGPlate::AddPlate(D3DXVECTOR3 size,D3DXVECTOR3 pos,D3DXVECTOR3 rot,
	  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient){
	try{
		PlateItem* pItem = new PlateItem(g_vZero,pos,size,g_vZero,rot,Diffuse,Specular,Ambient);

		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);

		D3DXMatrixRotationYawPitchRoll(&mRot,
			D3DXToRadian(rot.y),D3DXToRadian(rot.x),D3DXToRadian(rot.z));
		m_ItemVec.push_back(pItem);
	}
	catch(...){
		Clear();
		throw;
	}
}

/**************************************************************************
	virtual void BGPlate::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect,			//エフェクトのポインタ
	D3DXMATRIX& mCameraView,			//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
 用途: 影ボリュームを描画（仮想関数）
 戻り値: なし。
***************************************************************************/
void BGPlate::DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
	  D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj){
	if(m_pShadowVolume){
		//配置オブジェクトの描画
		vector<PlateItem*>::size_type sz = m_ItemVec.size();
		for(vector<PlateItem*>::size_type i = 0;i < sz;i++){
			//拡大縮小用
			D3DXMATRIX mScale;
			D3DXMatrixIdentity(&mScale);
			D3DXMatrixScaling(&mScale,m_ItemVec[i]->m_MeshItem.m_vSize.x,
				m_ItemVec[i]->m_MeshItem.m_vSize.y,m_ItemVec[i]->m_MeshItem.m_vSize.z);
			//回転用
			D3DXMATRIX mRot;
			D3DXMatrixIdentity(&mRot);
			D3DXMatrixRotationQuaternion(&mRot,&m_ItemVec[i]->m_MeshItem.m_RotQt);
			//拡大縮小と回転をミックス行列
			//移動用
			D3DXMATRIX mMove;
			D3DXMatrixIdentity(&mMove);
			//影の移動は、Y軸に対しての移動は0.01fだけ低い位置にする。
			//自己影が映りこむのを制御している
			D3DXMatrixTranslation(&mMove,m_ItemVec[i]->m_MeshItem.m_vPos.x,
				m_ItemVec[i]->m_MeshItem.m_vPos.y -0.01f,m_ItemVec[i]->m_MeshItem.m_vPos.z);
			//すべてミックス行列
			D3DXMATRIX mAllMatrix;
			D3DXMatrixIdentity(&mAllMatrix);
			mAllMatrix = mScale * mRot * mMove;
			//オブジェクトのワールド行列をカメラ視線にして登録
			D3DXMATRIX WorldView;
			WorldView =  mAllMatrix  * mCameraView;
			pEffect->SetMatrix("g_mWorldView",&WorldView);
			//カメラのプロジェクトまで含んだ行列を登録
			WorldView = WorldView * mCameraProj;
			pEffect->SetMatrix("g_mWorldViewProjection",&WorldView);
			//影ボリュームの描画
			m_pShadowVolume->Draw(pD3DDevice,pEffect);
		}
	}
}

}