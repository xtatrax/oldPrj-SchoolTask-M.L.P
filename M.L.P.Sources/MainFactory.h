/**************************************************************************
 MainFactory.h

 class Light : public Object; 宣言
 class DirectionalLight : public Light; 宣言
 class Camera : public Object; 宣言
 class LookDownCamera : public Camera; 宣言
 class Guide : public Object; 宣言
 class Shadow: public Object; 宣言

                                                    2012/04/17　自分の名前
****************************************************************************/
#pragma once

#include "StdAfx.h"
namespace wiz{

/**************************************************************************
 class Light : public Object;
 用途: ライトクラス
****************************************************************************/
class Light : public Object{
/**************************************************************************
 void Clear();
 用途: オブジェクトのクリア
 戻り値: なし
***************************************************************************/
    void Clear();
protected:
    D3DLIGHT9   m_Light;
/**************************************************************************
 Light(LPDIRECT3DDEVICE9 pD3DDevice);
 用途: プロテクトコンストラクタ
 戻り値: なし
 説明: 直接構築できないように、プロテクトにする
***************************************************************************/
    Light(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 ~virtual ~Light();
 用途: プロテクトデストラクタ（仮想デストラクタ）
 戻り値: なし
***************************************************************************/
    virtual ~Light();
public:
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,
        const CONTROLER_STATE* pCntlState,Command& Com);

};

/**************************************************************************
 class DirectionalLight : public Light;
 用途: ディレクショナルライトクラス
****************************************************************************/
class DirectionalLight : public Light{
	D3DXVECTOR3 m_Direction;
public:
/**************************************************************************
 DirectionalLight(
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
    DirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE Diffuse,
        D3DCOLORVALUE Specular,
        D3DCOLORVALUE Ambient,
        D3DXVECTOR3 Direction);
/**************************************************************************
 virtual ~DirectionalLight();
 用途: デストラクタ（仮想デストラクタ）
 戻り値: なし
***************************************************************************/
    virtual ~DirectionalLight();
/**************************************************************************
 D3DXVECTOR3 getDirection();
 用途: 光の方向を得る
 戻り値: 光の方向
***************************************************************************/
	D3DXVECTOR3 getDirection(){
		return m_Direction;
	}
};


/**************************************************************************
 class Camera : public Object;
 用途: カメラクラス
****************************************************************************/
class Camera : public Object{
protected:
    D3DXMATRIX  m_View;     // カメラの配置
    D3DXMATRIX  m_Proj;		// 射影行列
    D3DXVECTOR3 m_Eye;      //カメラの位置
    D3DXVECTOR3 m_At;       //直視点
    FLOAT m_Near;           //射影の手前側の距離
    FLOAT m_Far;            //射影の奥側の距離
    FLOAT m_FovY;           //射影角度

    D3DXVECTOR3 m_Arm;       //視点と直視点の間（腕）のベクトル
	FLOAT m_TotalAngleXZ;	//カメラのXZ回転のラジアン値
	FLOAT m_TotalAngleY;	//カメラのY回転のラジアン値

public:
/**************************************************************************
 Camera(
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
 Camera(D3DXVECTOR3& At,FLOAT PosZFromAt,FLOAT PosYFromAt,
    FLOAT Near,FLOAT Far,FLOAT FovY);
/**************************************************************************
Camera(
    D3DXVECTOR3& Eye,    //カメラの位置
    D3DXVECTOR3& At,    //直視点
    FLOAT Near,         //射影の手前側の距離
    FLOAT Far,          //射影の奥側の距離
    FLOAT FovY          //Y軸射影角度
    );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	Camera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,
		FLOAT Near,FLOAT Far,FLOAT FovY);

/**************************************************************************
 virtual ~Camera();
 用途: 仮想デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~Camera();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: カメラを設置
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
/**************************************************************************
 void getPos(
 D3DXVECTOR3& Eye,	//カメラの位置
 D3DXVECTOR3& At	//注視点
 );
 用途: カメラの現在の位置と注視点を得る
 戻り値: なし。EyeとATに値を代入
***************************************************************************/
	void getPos(D3DXVECTOR3& Eye,D3DXVECTOR3& At){
		Eye = m_Eye;
		At = m_At;
	}
/**************************************************************************
 void getMatrix(
 D3DXMATRIX& View,	//ビュー行列
 D3DXMATRIX& Proj	//射影行列
 );
 用途: カメラのビュー行列と射影行列を得る
 戻り値: なし。ViewとProjに値を代入
***************************************************************************/
	void getMatrix(D3DXMATRIX& View,D3DXMATRIX& Proj){
		View = m_View;
		Proj = m_Proj;
	}
/**************************************************************************
 FLOAT getFar();
 用途: カメラのFar位置を得る
 戻り値: Far位置
***************************************************************************/
	FLOAT getFar(){
		return m_Far;
	}
};

/**************************************************************************
 class LookDownCamera : public Camera;
 用途: 真上から見るカメラクラス
****************************************************************************/
class LookDownCamera : public Camera{
public:
/**************************************************************************
LookDownCamera(
    D3DXVECTOR3& Eye,    //カメラの位置
    D3DXVECTOR3& At,    //直視点
    FLOAT Near,         //射影の手前側の距離
    FLOAT Far,          //射影の奥側の距離
    FLOAT FovY          //Y軸射影角度
    );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	LookDownCamera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,
		FLOAT Near,FLOAT Far,FLOAT FovY);
/**************************************************************************
 virtual ~FixCamera();
 用途: 仮想デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~LookDownCamera(){}
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: カメラを設置
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};




/**************************************************************************
 class Guide : public Object;
 用途: ガイドクラス（x、y、z方向に伸びるガイド線）
****************************************************************************/
class Guide : public Object{
    IDirect3DVertexBuffer9* m_pVB;
    //クラス内構造体
    //ここでしか使用しないので、内部に持つ
    struct CUSTOMVERTEX
    {
        D3DXVECTOR3 vec;
        DWORD color;
    };

public:
/**************************************************************************
 Guide(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9インターフェイスへのポインタ
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
    Guide(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 virtual ~Guide();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~Guide();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: ガイドを設置（コントローラには反応しない）
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};


/**************************************************************************
 class MainFactory;
 用途: メイン工場クラス
****************************************************************************/
class MainFactory{
public:
/**************************************************************************
 MainFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（オブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	MainFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~MainFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~MainFactory();
};


}
//end of namespace wiz.

