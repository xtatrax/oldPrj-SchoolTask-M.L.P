/**************************************************************************
 MainFactory.cpp

 class Light : public Object; 定義
 class DirectionalLight : public Light 定義
 class Camera : public Object; 定義
 class LookDownCamera : public Camera; 定義
 class Guide : public Object; 定義
 class Shadow: public Object; 定義
 class MainFactory
                                                    2012/04/17　自分の名前
****************************************************************************/
#include "StdAfx.h"
#include "MainFactory.h"
#include "Sprite.h"


namespace wiz{

/**************************************************************************
 Light 定義部
****************************************************************************/
/**************************************************************************
 Light::Light(LPDIRECT3DDEVICE9 pD3DDevice);
 用途: プロテクトコンストラクタ
 戻り値: なし
 説明: 直接構築できないように、プロテクトにする
***************************************************************************/
Light::Light(LPDIRECT3DDEVICE9 pD3DDevice){
	try{
		// D3DLIGHT9構造体を0でクリアする
		::ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
	}
	catch(...){
		//再スロー
		throw;
	}
}
/**************************************************************************
 virtual Light::~Light();
 用途: プロテクトデストラクタ（仮想デストラクタ）
 戻り値: なし
***************************************************************************/
Light::~Light(){
//何もしない
}

/**************************************************************************
 void Light::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
void Light::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,
							const CONTROLER_STATE* pCntlState,Command& Com){
//何もしない
}

/**************************************************************************
 DirectionalLight 定義部
****************************************************************************/
/**************************************************************************
 DirectionalLight::DirectionalLight(
    LPDIRECT3DDEVICE9 pD3DDevice,   //デバイス
    D3DCOLORVALUE Diffuse,          //ディフューズ色
    D3DCOLORVALUE Specular,         //スペキュラ色
    D3DCOLORVALUE Ambient,          //アンビエント色
    D3DXVECTOR3 Direction           //ワールド空間で光が指す方向
 );
 用途: コンストラクタ
 戻り値: なし
 説明: ディレクショナルライトを構築する
***************************************************************************/
DirectionalLight::DirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
    D3DCOLORVALUE Diffuse,
    D3DCOLORVALUE Specular,
    D3DCOLORVALUE Ambient,
    D3DXVECTOR3 Direction)
    :Light(pD3DDevice),m_Direction(0,0,0)
{
    m_Light.Type       = D3DLIGHT_DIRECTIONAL;
    m_Light.Diffuse = Diffuse;
    m_Light.Specular = Specular;
    m_Light.Ambient = Ambient;
    D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &Direction);
	m_Direction = m_Light.Direction;
    // ライトをレンダリングパイプラインに設定
    pD3DDevice->SetLight( 0, &m_Light );
    // ライトを有効にする
    pD3DDevice->LightEnable( 0, TRUE );
}
/**************************************************************************
 virtual DirectionalLight::~DirectionalLight();
 用途: デストラクタ（仮想デストラクタ）
 戻り値: なし
***************************************************************************/
DirectionalLight::~DirectionalLight(){
//何もしない
}
/**************************************************************************
 Camera 定義部
****************************************************************************/
/**************************************************************************
 Camera::Camera(
    D3DXVECTOR3& At,    //直視点
	FLOAT AbsPosZFromAt,//直視点から見た、カメラ位置のZの位置(絶対値指定)
	FLOAT PosYFromAt,	//直視点から見た、カメラ位置のYの位置
    FLOAT Near,         //射影の手前側の距離
    FLOAT Far,          //射影の奥側の距離
    FLOAT FovY          //Y軸射影角度
    );
 用途: コンストラクタ
 ＊カメラ位置の初期値は直接は指定できない。
 ＊直視点からみて、Zの手前に引く相対位置とYの相対位置を指定する。Xは0に固定
 ＊Zの手前に引く相対位置（AbsPosZFromAt）は絶対値化されるので、
	マイナスを指定しても意味がない。
 戻り値: なし
***************************************************************************/
Camera::Camera(D3DXVECTOR3& At,FLOAT AbsPosZFromAt,FLOAT PosYFromAt,
    FLOAT Near,FLOAT Far,FLOAT FovY)
:Object(),m_Eye(),m_At(At),m_Near(Near),m_Far(Far),m_FovY(FovY)
{
	//カメラ位置の確定
	m_Eye.x = m_At.x;
	m_Eye.y = m_At.y + PosYFromAt;
	m_Eye.z = m_At.z - fabs(AbsPosZFromAt);
	//カメラビューの作成
    D3DXMatrixIdentity(&m_View);
    D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
	//カメラと直視点との間（Arm）ｗ０作成
    m_Arm = m_At - m_Eye;
	D3DXVECTOR3 m;
	//正規化
	D3DXVec3Normalize(&m,&m_Arm);
	m_TotalAngleXZ = 0;
	//正規化されたYの値から高さのラジアンを得る
	FLOAT a_c,a_s;
	a_c = acos(m.z);
	a_s = asin(m.y);
	if(a_s < 0.0f){
		m_TotalAngleY = a_c;
	}
	else{
		m_TotalAngleY = D3DX_PI + D3DX_PI - a_c;
	}

}

/**************************************************************************
Camera::Camera(
    D3DXVECTOR3& Eye,    //カメラの位置
    D3DXVECTOR3& At,    //直視点
    FLOAT Near,         //射影の手前側の距離
    FLOAT Far,          //射影の奥側の距離
    FLOAT FovY          //Y軸射影角度
    );
 用途: Fixカメラの時に使用するコンストラクタ
 戻り値: なし
***************************************************************************/
Camera::Camera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,
	 FLOAT Near,FLOAT Far,FLOAT FovY)
	 :m_View(),m_Proj(),m_Eye(Eye),m_At(At),m_Near(Near),m_Far(Far),m_FovY(FovY)
{
    m_Arm = m_At - m_Eye;
	//Fixカメラの時に使用するコンストラクタなので
	//カメラ変化はなくても良い
	m_TotalAngleXZ = 0;
	m_TotalAngleY = 0;
}


/**************************************************************************
 Camera::~Camera();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Camera::~Camera(){
}
/**************************************************************************
 void Camera::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
 );
 用途: カメラを設置
 戻り値: なし。
***************************************************************************/
/**************************************************************************
 void Camera::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: カメラを設置
 戻り値: なし。
***************************************************************************/
void Camera::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
    // ビューポートの取得
    D3DVIEWPORT9 vp;
    if(FAILED(pD3DDevice->GetViewport(&vp))){
        //実行失敗
		//WinMainのCatchまで飛ぶ
        throw DxException(
            L"ビューポートの取得に失敗しました。",
            L"Camera::Draw()"
            );
	}
	m_Eye = m_At - m_Arm;
    D3DXMatrixIdentity(&m_View);
    D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
    // アスペクト比の計算
    float aspect;
    aspect = (float)vp.Width / (float)vp.Height;
    // 射影行列の初期化
    D3DXMatrixIdentity(&m_Proj);
    D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
    // 射影行列の設定
    pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
    // カメラの設定
    pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
#ifdef	___MLP_DEBUG_CAMERAPOSDRAW_
	Debugger::DBGSTR::addStr(
		L"カメラ情報 : 位置 | X= %5.1f Y= %5.1f Z= %5.1f \n"
		L"　　　　　　 視点 | X= %5.1f Y= %5.1f Z= %5.1f \n"
		L"　　　　　　 射影 | 前 %5.1f 奥 %5.1f 角 %3.2f \n"
		L"　　　　視直間Vec | X= %5.1f Y= %5.1f Z= %5.1f \n"
		L"　　　　　　 回転 | XZ %5.1f y= %5.1f\n",
		m_Eye.x,m_Eye.y,m_Eye.z,
		m_At.x,m_At.y,m_At.z,   
		m_Near,m_Far,m_FovY,
		m_Arm.x,m_Arm.y,m_Arm.z,  
		m_TotalAngleXZ,m_TotalAngleY);
#endif
}


/**************************************************************************
 LookDownCamera 定義部
****************************************************************************/
/**************************************************************************
LookDownCamera::LookDownCamera(
    D3DXVECTOR3& Eye,    //カメラの位置
    D3DXVECTOR3& At,    //直視点
    FLOAT Near,         //射影の手前側の距離
    FLOAT Far,          //射影の奥側の距離
    FLOAT FovY          //Y軸射影角度
    );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
LookDownCamera::LookDownCamera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,
	 FLOAT Near,FLOAT Far,FLOAT FovY)
	 :Camera(Eye,At,Near,Far,FovY)
{
}
/**************************************************************************
 virtual void LookDownCamera::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: カメラを設置
 戻り値: なし。
***************************************************************************/
void LookDownCamera::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
					 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
    // ビューポートの取得
    D3DVIEWPORT9 vp;
    if(FAILED(pD3DDevice->GetViewport(&vp))){
        //実行失敗
		//WinMainのCatchまで飛ぶ
        throw DxException(
            L"ビューポートの取得に失敗しました。",
            L"Camera::Draw()"
            );
    }
    D3DXMatrixIdentity(&m_View);
		D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
				&D3DXVECTOR3( 0.0f, 0.0f, 1.0f));
    // アスペクト比の計算
    float aspect;
    aspect = (float)vp.Width / (float)vp.Height;
    // 射影行列の初期化
    D3DXMatrixIdentity(&m_Proj);
    D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
    // 射影行列の設定
    pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
    // カメラの設定
    pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
#ifdef	___MLP_DEBUG_CAMERAPOSDRAW_
	Debugger::DBGSTR::addStr(
		L"カメラ情報 : 位置 | X= %5.1f Y= %5.1f Z= %5.1f \n"
		L"　　　　　　 視点 | X= %5.1f Y= %5.1f Z= %5.1f \n"
		L"　　　　　　 射影 | 前 %5.1f 奥 %5.1f 角 %3.2f \n"
		L"　　　　視直間Vec | X= %5.1f Y= %5.1f Z= %5.1f \n"
		L"　　　　　　 回転 | XZ %5.1f y= %5.1f\n",
		m_Eye.x,m_Eye.y,m_Eye.z,
		m_At.x,m_At.y,m_At.z,   
		m_Near,m_Far,m_FovY,
		m_Arm.x,m_Arm.y,m_Arm.z,  
		m_TotalAngleXZ,m_TotalAngleY);
#endif
}

/**************************************************************************
 class Guide 定義部
****************************************************************************/
/**************************************************************************
 Guide::Guide(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9インターフェイスへのポインタ
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
Guide::Guide(LPDIRECT3DDEVICE9 pD3DDevice)
    :Object(),m_pVB(0)
{
    try{
        CUSTOMVERTEX Vertices[] = 
        {
            {D3DXVECTOR3(-1000.0,0.0,0.0),D3DCOLOR_ARGB(0xff,0xff,0,0)},
            {D3DXVECTOR3(1000.0,0.0,0.0),D3DCOLOR_ARGB(0xff,0xff,0,0)},
            {D3DXVECTOR3(0.0,-1000.0,0.0),D3DCOLOR_ARGB(0xff,0,0xff,0)},
            {D3DXVECTOR3(0.0,1000.0,0.0),D3DCOLOR_ARGB(0xff,0,0xff,0)},
            {D3DXVECTOR3(0.0,0.0,-1000.0),D3DCOLOR_ARGB(0xff,0,0,0xff)},
            {D3DXVECTOR3(0.0,0.0,1000.0),D3DCOLOR_ARGB(0xff,0,0,0xff)}
        };
        if(FAILED(pD3DDevice->CreateVertexBuffer( 6 * sizeof( CUSTOMVERTEX ),
                                    0,D3DFVF_XYZ|D3DFVF_DIFFUSE,
                                    D3DPOOL_DEFAULT, &m_pVB, NULL)))
        {
            // 初期化失敗
            throw DxException(
                L"頂点バッファの作成に失敗しました。",
                L"Guide::Guide()"
                );
        }
        //バッファをロック
        VOID* pVertices;
        if(FAILED( m_pVB->Lock( 0, sizeof(Vertices),( void** )&pVertices, 0 ))){
            // 初期化失敗
            throw DxException(
                L"頂点バッファのロックに失敗しました。",
                L"Guide::Guide()"
                );
        }
        //頂点データから頂点バッファに転送
        memcpy( pVertices,Vertices, sizeof(Vertices) );
        //頂点バッファをアンロック
        m_pVB->Unlock();
    }
    catch(...){
        //コンストラクタ例外発生
        //後始末
        SafeRelease(m_pVB);
        //再スロー
        throw;
    }
}
/**************************************************************************
 Guide::~Guide();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Guide::~Guide(){
    SafeRelease(m_pVB);
}
/**************************************************************************
 void Guide::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: ガイドを設置（コントローラには反応しない）
 戻り値: なし。
***************************************************************************/
void Guide::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
    D3DXMATRIX  wm;
    //座標変換無し
    D3DXMatrixIdentity(&wm);
    // マトリックスをレンダリングパイプラインに設定
    pD3DDevice->SetTransform(D3DTS_WORLD, &wm);
    pD3DDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ) );
    pD3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
    pD3DDevice->SetRenderState( D3DRS_LIGHTING,FALSE);
    pD3DDevice->LightEnable( 0, FALSE );
    pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, 3);
    pD3DDevice->SetRenderState( D3DRS_LIGHTING,TRUE);
    pD3DDevice->LightEnable( 0, TRUE );
}

/**************************************************************************
 MainFactory 定義部
****************************************************************************/
/**************************************************************************
 MainFactory::MainFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
MainFactory::MainFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{
        // ライティングモード
        pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
        //ライトのインスタンス初期化
        D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,0.0f};
        vec.push_back(new DirectionalLight(pD3DDevice,Diffuse,Specular,Ambient,
                    D3DXVECTOR3( -0.0f, -1.0f, 0.0f)));
        //カメラのインスタンス初期化
        vec.push_back(
			new Camera(D3DXVECTOR3( 0.0f, 0.0f, 5.0f),D3DXVECTOR3( 0.0f, 0.0f, 0.0f),
				    1.0f, 100.0f,30.0f));
        //ガイドのインスタンス初期化
        vec.push_back(new Guide(pD3DDevice));



	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 MainFactory::~MainFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
MainFactory::~MainFactory(){
    //なにもしない
}


}
//end of namespace wiz.
