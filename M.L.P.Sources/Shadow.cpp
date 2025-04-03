/**************************************************************************
 MainFactory.cpp

 class Light : public Object; 定義
 class DirectionalLight : public Light 定義
 class Camera : public Object; 定義
 class LookDownCamera : public Camera; 定義
 class Guide : public Object; 定義
 class Shadow: public Object; 定義

                                                    2012/04/17　自分の名前
****************************************************************************/
#include "StdAfx.h"
#include "MainFactory.h"
#include "Shadow.h"
//#include "Camera.h"

namespace wiz{


/**************************************************************************
 Shadow 定義部
****************************************************************************/
/**************************************************************************
 void Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
void Shadow::Clear(){
    SafeRelease(m_pBigVB);
    SafeRelease(m_pEffect);
}
/**************************************************************************
 Shadow::Shadow(
 LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
Shadow::Shadow(LPDIRECT3DDEVICE9 pD3DDevice)
:m_pBigVB(0),m_pEffect(0),
m_hRenderShadow(0),m_hShowShadow(0),m_hRenderShadowVolumeComplexity(0)
{
	try{
        IDirect3DSurface9* pBackBuffer;
		if(FAILED(pD3DDevice->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer ))){
			// 初期化失敗
			throw DxException(
				L"バックバッファの取得に失敗しました。",
				L"Shadow::Shadow()"
				);
		}
		D3DSURFACE_DESC desc;
        ZeroMemory(&desc, sizeof( D3DSURFACE_DESC ) );
		pBackBuffer->GetDesc(&desc);
		SafeRelease( pBackBuffer );


	    DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;
#if defined( DEBUG ) || defined( _DEBUG )
		dwShaderFlags |= D3DXSHADER_DEBUG;
#endif
#ifdef DEBUG_VS
		dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
		dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif
//***************************************************************************
//リソース化したい。
		if(FAILED(D3DXCreateEffectFromFile(pD3DDevice,L"ShadowVolume.fx", NULL, NULL, 
			dwShaderFlags, NULL, &m_pEffect, NULL ))){
//***************************************************************************
			// 初期化失敗
			throw DxException(
				L"エフェクトの作成に失敗しました。",
				L"Shadow::Shadow()"
				);
		}
		D3DCAPS9 Caps;
		pD3DDevice->GetDeviceCaps( &Caps );
		m_hRenderShadowVolumeComplexity 
			= m_pEffect->GetTechniqueByName( "RenderShadowVolumeComplexity" );
		// If 2-sided stencil is supported, use it.
		if( Caps.StencilCaps & D3DSTENCILCAPS_TWOSIDED )
		{
			m_hRenderShadow = m_pEffect->GetTechniqueByName( "RenderShadowVolume2Sided" );
			m_hShowShadow = m_pEffect->GetTechniqueByName( "ShowShadowVolume2Sided" );
		}
		else
		{
			m_hRenderShadow = m_pEffect->GetTechniqueByName( "RenderShadowVolume" );
			m_hShowShadow = m_pEffect->GetTechniqueByName( "ShowShadowVolume" );
		}
		if(!m_hRenderShadowVolumeComplexity 
			|| !m_hRenderShadow 
			|| !m_hShowShadow){
			// 初期化失敗
			throw DxException(
				L"エフェクトハンドルの読み込みに失敗しました。",
				L"Shadow::Shadow()"
				);
		}
		if( FAILED( pD3DDevice->CreateVertexBuffer(
                                     4*sizeof(BigSquareVertex),
                                     D3DUSAGE_WRITEONLY,
                                     BigSquareFVF,
                                     D3DPOOL_MANAGED,
									 &m_pBigVB, NULL ) ) ){
			// 初期化失敗
			throw DxException(
				L"頂点バッファの作成に失敗しました。",
				L"Shadow::Shadow()"
				);
		}

		BigSquareVertex* v;
		m_pBigVB->Lock( 0, 0, (void**)&v, 0 );
		v[0].p = D3DXVECTOR4(  0, (FLOAT)desc.Height, 0.0f, 1.0f );
		v[1].p = D3DXVECTOR4(  0,  0, 0.0f, 1.0f );
		v[2].p = D3DXVECTOR4( (FLOAT)desc.Width, (FLOAT)desc.Height, 0.0f, 1.0f );
		v[3].p = D3DXVECTOR4( (FLOAT)desc.Width,  0, 0.0f, 1.0f );
		v[0].color = D3DCOLOR_RGBA(0,0,0,0x7f);
		v[1].color = D3DCOLOR_RGBA(0,0,0,0x7f);
		v[2].color = D3DCOLOR_RGBA(0,0,0,0x7f);
		v[3].color = D3DCOLOR_RGBA(0,0,0,0x7f);
		m_pBigVB->Unlock();
	}
	catch(...){
        //後始末
        Clear();
		//再throw
		throw;
	}
}

/**************************************************************************
 Shadow::~Shadow();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Shadow::~Shadow(){
    Clear();
}

/**************************************************************************
 virtual void Shadow::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 影を描画
 戻り値: なし。
***************************************************************************/
void Shadow::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
				  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
	Camera* pCamera = 0;
	DirectionalLight* pLight = 0;
	//まずカメラとライトを探す
	vector<Object*>::size_type sz = Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		const type_info& info = typeid(*(Vec[i]));
		if(info == typeid(DirectionalLight)){
			pLight = dynamic_cast<DirectionalLight*>(Vec[i]);
		}
		if(info == typeid(Camera) || info == typeid(LookDownCamera)){
			pCamera = dynamic_cast<Camera*>(Vec[i]);
		}
		if(pLight && pCamera){
			break;
		}
	}
	if(pCamera && pLight && m_pEffect){
		D3DXMATRIX mCameraView;
		D3DXMATRIX mCameraProj;
		//カメラの行列を取得
		pCamera->getMatrix(mCameraView,mCameraProj);
		//ライトのベクトルを取得
		D3DXVECTOR3 lightbaseVec = pLight->getDirection();
		//ライトを逆向きに
		lightbaseVec *= -1.0f;
		//10倍に増やす（ここがライトの位置）
		lightbaseVec *= 20.0f;
		//登録用に型変換
		D3DXVECTOR4 vLight(lightbaseVec.x,lightbaseVec.y,lightbaseVec.z,1.0f );
		//ライトをカメラ座標に変える
        D3DXVec4Transform( &vLight, &vLight, &mCameraView );
		// ビューポートの取得
		D3DVIEWPORT9 vp;
		if(FAILED(pD3DDevice->GetViewport(&vp))){
			//実行失敗
			//WinMainのCatchまで飛ぶ
			throw DxException(
				L"ビューポートの取得に失敗しました。",
				L"Shadow::Draw()"
				);
		}
		// アスペクト比の計算
		float aspect;
		aspect = (float)vp.Width / (float)vp.Height;
		// ライトの射影行列の初期化
		//ZのFarクリップ
		m_pEffect->SetFloat( "g_fFarClip", pCamera->getFar() - 0.1f );
		//エフェクトの射影行列を登録
		m_pEffect->SetMatrix( "g_mProj", &mCameraProj);
		//ライトの位置を登録
		m_pEffect->SetVector( "g_vLightView", &vLight);
		//ライトの色を登録
		D3DXVECTOR4 mColor(0.8f,0.8f,0.8f,0.4f);
		m_pEffect->SetVector( "g_vLightColor", &mColor);
		//ライトの影色を登録
		D3DXVECTOR4 mShadowColor(0.5f,0.0f,0.0f,0.3f);
        m_pEffect->SetVector( "g_vShadowColor", &mShadowColor );
		//テクニックを登録
		//影を現実のように表示する場合
		m_pEffect->SetTechnique(m_hRenderShadow);
		//影の流れを表示する場合（デバッグ用）
		//	m_pEffect->SetTechnique(m_hShowShadow);
		//影ボリュームを表示する場合（デバッグ用）
		//	m_pEffect->SetTechnique(m_hRenderShadowVolumeComplexity);
		//それぞれの影描画関数を呼ぶ
		vector<Object*>::size_type sz = Vec.size();
		for(vector<Object*>::size_type i = 0;i < sz;i++){
			Vec[i]->DrawShadowVolume(pD3DDevice,m_pEffect,mCameraView,mCameraProj);
		}
		//これより最後のステップ
		// 深度テストはしない
		pD3DDevice->SetRenderState( D3DRS_ZENABLE,          FALSE );
		// ステンシルテストはする
		pD3DDevice->SetRenderState( D3DRS_STENCILENABLE,  TRUE );
		// アルファブレンディングは線形に掛ける
		pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
		pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		// ポリゴンを描画するときには、テクスチャと頂点色の両方を見る
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
		// ステンシルバッファの値が１以上のときに書き込む
		pD3DDevice->SetRenderState( D3DRS_STENCILREF,  0x1 );
		pD3DDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL );
		pD3DDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_KEEP );
		//マスキング結果の表示		         
		pD3DDevice->SetFVF( BigSquareFVF );
		pD3DDevice->SetStreamSource( 0, m_pBigVB, 0, sizeof(BigSquareVertex));
		pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
		// 状態を元に戻す
		pD3DDevice->SetRenderState( D3DRS_ZENABLE,          TRUE );
		pD3DDevice->SetRenderState( D3DRS_STENCILENABLE,  FALSE );
		pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
	}
}


}
//end of namespace wiz.
