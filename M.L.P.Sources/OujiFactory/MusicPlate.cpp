/**************************************************************************
 MusicPlate.cpp

 MusicPlate; 定義
                                                    2012/03/04　名前 
****************************************************************************/
#include "StdAfx.h"
#include "MusicPlate.h"
#include "math.h"
#include "SpLv.h"
#include "../Scene.h"
#include "../TATRAFactory/SHS.h"

namespace wiz{
/**************************************************************************
 MusicPlate 定義部
***************************************************************************/

/**************************************************************************
 void MusicPlate::Clear();
 用途:Itemの破棄
 戻り値: なし
***************************************************************************/
void MusicPlate::Clear(){
	vector<PlateItem*>::iterator it;
    for(it = m_ItemVec.begin();it != m_ItemVec.end();it++){
        SafeDelete(*it);
    }
    m_ItemVec.clear();
	//*テクスチャはリリースしてはいけない
}

/**************************************************************************
 virtual D3DXVECTOR3 MusicPlate::getMove(vector<PlateItem*>::size_type index);
 用途: プレートが移動してる場合や傾いている場合に、ヒット先が移動すべきベクトル
 戻り値: ベクトル
***************************************************************************/
D3DXVECTOR3 MusicPlate::getMove(vector<PlateItem*>::size_type index){
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
 MusicPlate::MusicPlate(
    LPDIRECT3DDEVICE9	pD3DDevice,		//IDirect3DDevice9インターフェイスへのポインタ
	LPDIRECT3DTEXTURE9	pTexture = 0	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
MusicPlate::MusicPlate(LPDIRECT3DDEVICE9 pD3DDevice)
	:Plate(pD3DDevice,
		D3DXVECTOR3(0.0f,0.0f,0.0f),
		D3DXVECTOR3(1.0f,1.0f,1.0f),
		D3DCOLORVALUE(),
		D3DCOLORVALUE(),
		D3DCOLORVALUE(),
		(LPDIRECT3DTEXTURE9)1),
		m_SelectLevel(0)
	{
		m_pTexture = 0;
    try{
    }
    catch(...){
        //コンストラクタ例外発生
        //再スロー
        throw;
    }
}
/**************************************************************************
 virtual ~MusicPlate();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
MusicPlate::~MusicPlate(){
	Clear();
}

/**************************************************************************
 virtual void MusicPlate::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
 );
 用途: 直方体を描画
 戻り値: なし。
***************************************************************************/
void MusicPlate::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){
    //楽曲数
    long MusicQt = m_ItemVec.size();

	//////////////////////////////
	//	: Levelの選択
	//十字キー →
	if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT){
		m_SelectLevel	+= 1;
		m_SelectLevel	%= 3;
	}
	//十字キー ←
	if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT){
		m_SelectLevel	-= 1;
		if(m_SelectLevel	< 0)	m_SelectLevel	+= 3;
	}
    for(vector<PlateItem*>::size_type i = 0;i < MusicQt;i++){

		//プレートの移動が完了しているか
		if(m_ItemVec[i]->m_MyNumber == m_ItemVec[i]->m_OldNumber){
			//十字キー↑
			if( pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP){
				//	: 自分の番号を一つ進め、その数字が楽曲数を超えた場合修正する
				m_ItemVec[i]->m_MyNumber	+= 1;
				m_ItemVec[i]->m_MyNumber	%= MusicQt;

				flg	= 5;
			}
			//十字キー↓
			else if( pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN){
				//	: 自分の番号を一つ戻し、その数字が0を下回った場合修正する
				m_ItemVec[i]->m_MyNumber	-= 1;
				if(m_ItemVec[i]->m_MyNumber < 0)	m_ItemVec[i]->m_MyNumber	+= MusicQt;
				
				flg	= -5;
			}
		}
		//プレートの正しい位置の設定
		float Degree = (360.0f / MusicQt) * (float)m_ItemVec[i]->m_MyNumber;
		//位置の変動が有ったか
		if( Degree != 360 / MusicQt * (m_ItemVec[i]->m_OldNumber) ){
			m_ItemVec[i]->m_RotDig	+= flg;
			//角度が0°を下回ったら修正する
			if(m_ItemVec[i]->m_RotDig < 0){
				m_ItemVec[i]->m_RotDig	+= 360;
			}
			//角度が360°を上回ったら修正する
			m_ItemVec[i]->m_RotDig	%= 360;
		}
		//正しい位置にあるか
		if( Degree == m_ItemVec[i]->m_RotDig ){
			m_ItemVec[i]->m_OldNumber	= m_ItemVec[i]->m_MyNumber;
		}

		//プレートの現在位置
		m_ItemVec[i]->m_MeshItem.m_vPos	= D3DXVECTOR3(-cosf(D3DXToRadian(m_ItemVec[i]->m_RotDig)) * 2.0f,
													   sinf(D3DXToRadian(m_ItemVec[i]->m_RotDig)) * 2.0f,
													  -cosf(D3DXToRadian(m_ItemVec[i]->m_RotDig)) * 2.0f);

		//プレートが正面にいるか
		if(m_ItemVec[i]->m_OldNumber == 0){
			//Ａボタンで曲とレベルが決定、プレイ画面に移動する
			if(pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_A){
				Script::MLPHeader* pHd; 
				pHd = &m_ItemVec[i]->m_Header;
				Com.m_Command	= Scene::SC_OPEN_PLAY;
				Com.m_Param1	= m_SelectLevel;
				Com.m_Param2	= (DWORD)pHd;
				break;
			}else{
				//表示されるレベルを送る
				Com.m_Command	= SendLevel;
				Com.m_Param1	= m_SelectLevel;
				Com.m_Param2	= m_ItemVec[i]->m_Header.Level[m_SelectLevel];
			}
		}

		//CommonMeshクラスのマティリアルを設定
		m_MeshItem = m_ItemVec[i]->m_MeshItem;
		//テクスチャがある場合
		if(m_ItemVec[i]->m_pTexture){
			DWORD wkdword;
			//現在のテクスチャステータスを得る
			pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
			//ステージの設定
			pD3DDevice->SetTexture(0,m_ItemVec[i]->m_pTexture);
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
 void MusicPlate::AddPlate(
    D3DXVECTOR3 size,               //大きさ
    D3DXVECTOR3 pos,                //初期位置
	D3DXVECTOR3 rot,				//回転、x=x軸回転角度,y=y軸回転角度,z=z軸回転角度。
	int			num,				//位置番号
	int			ItemQt,				//楽曲数
	Script::MLPHeader	header,		//曲のレベル
    D3DCOLORVALUE		Diffuse,	//ディフューズ色
    D3DCOLORVALUE		Specular,	//スペキュラ色
    D3DCOLORVALUE		Ambient		//アンビエント色
    );
 用途: プレートを追加
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
void MusicPlate::AddPlate(D3DXVECTOR3 size,D3DXVECTOR3 pos,D3DXVECTOR3 rot,
		int num,int ItemQt,Script::MLPHeader header,
		D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient,LPDIRECT3DTEXTURE9 pTexture){
	try{
		PlateItem* pItem = new PlateItem(D3DXVECTOR3(-3.0f,0.0f,-2.0f),pos,size,g_vZero,rot,Diffuse,Specular,Ambient,pTexture);

		//初期位置の番号
		pItem->m_MyNumber	= num;
		pItem->m_OldNumber	= num;
		//初期レベル
		pItem->m_Header		= header;
		//回転軸から見た角度
		pItem->m_RotDig	= (360/ItemQt)*(pItem->m_MyNumber);

		m_ItemVec.push_back(pItem);

	}
	catch(...){
		Clear();
		throw;
	}
}

/**************************************************************************
	virtual void MusicPlate::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect,			//エフェクトのポインタ
	D3DXMATRIX& mCameraView,			//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
 用途: 影ボリュームを描画（仮想関数）
 戻り値: なし。
***************************************************************************/
void MusicPlate::DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
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