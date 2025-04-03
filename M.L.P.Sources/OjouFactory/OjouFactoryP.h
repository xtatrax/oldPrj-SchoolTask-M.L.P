/**************************************************************************
 OjouFactoryP.h

													2012/06/18  修正 鴫原 徹
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Sprite.h"
#include "../MultiPlate.h"

#define	NUMBERS_WIDTH	(27)	//	: 各数字の幅
#define	NUMBERS_HEIGHT	(40)	//	: 各数字の高さ

#define GROOVE_WIDTH (29)		//  : グルーヴの一メモリの幅
#define GROOVE_HEIGHT (70)		//  : グルーヴの一メモリの高さ



namespace wiz{
namespace Ojou{

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/***********************************************************************
class SupportMultiPlateDown	public MultiPlate
用途: 複数の直方体クラス
	  コントローラーが押されると対応したプレートが下がる
************************************************************************/
class SupportMultiPlateDown : public MultiPlate{
protected:
	struct ButtonMoveItem : public MultiPlate::PlateItem{
		MeshItem m_MeshItem;
		int m_SupportButtonL;	//  : 十字キーの値
		int m_SupportButtonR;	//  : ボタンの値
	virtual ~ButtonMoveItem(){}
		ButtonMoveItem(D3DXVECTOR3& center,D3DXVECTOR3& pos,D3DXVECTOR3& size ,
		D3DXVECTOR3& turn,D3DXVECTOR3& rot,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,int SupportButtonL,int SupportButtonR)
			:m_MeshItem(center,pos,size,turn,rot,Diffuse,Specular,Ambient),
			PlateItem(center,pos,size,turn,rot,Diffuse,Specular,Ambient),
		m_SupportButtonL(SupportButtonL),m_SupportButtonR(SupportButtonR){
		}
	D3DXVECTOR3 m_Move;			//  : 下がる値
	D3DXVECTOR3 m_BasePos;		//  : 初期位置
};

/**************************************************************************
 void Clear();
 用途:Itemの破棄
 戻り値: なし
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 SupportMultiPlateDown(
    LPDIRECT3DDEVICE9 pD3DDevice   //IDirect3DDevice9インターフェイスへのポインタ
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	SupportMultiPlateDown(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 virtual ~SimpleMoveMultiPlate();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~SupportMultiPlateDown();
/**************************************************************************
 void AddPlate(
    D3DXVECTOR3 move,				//移動
    D3DXVECTOR3 size,               //大きさ
    D3DXVECTOR3 pos,                //最初の位置
	D3DXVECTOR3 rot,				//回転(角度単位)。
    D3DCOLORVALUE Diffuse,          //ディフューズ色
    D3DCOLORVALUE Specular,         //スペキュラ色
    D3DCOLORVALUE Ambient           //アンビエント色
	int SupportButtonL				//十字キーの値
	int SupportButtonR				//ボタンの値
    );
 用途: プレートを追加
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
    void AddPlate(D3DXVECTOR3 move,D3DXVECTOR3 center,D3DXVECTOR3 pos,D3DXVECTOR3 size ,
		D3DXVECTOR3 turn,D3DXVECTOR3 rot,
		D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient,int SupportButtonL,int SupportButtonR);
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
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/



/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class Groove;
 用途: グルーヴクラス
****************************************************************************/
class Groove : public Sprite{
	
	float	m_GaugePercent;
	BYTE	m_BadQt;
	int		m_iTextureWideFive;
	RECT	m_rectGrooveBorder;
	RECT	g_rectGroove;
public:
/*************************************************************************
 Groove(
	LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9インターフェイスへのポインタ
  D3DXVECTOR3		m_vPos;			//	: 描画する位置(画面左上を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vOffsetPos;	//	: オフセット座標(描画位置を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vScale;		//	: 伸縮度合い
	D3DXVECTOR3		m_vCenter;		//	: 画像の中心とする位置(画像の左上を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vRot;			//	: 描く軸ごとの回転度合い
	Rect*			m_Rect;			//	: 表示する画像の範囲
	SpriteItem		m_MeshItem;		//	: 座標データとかマテリアルとか。（SpriteItemに変更予定）
    );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
    Groove(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* Rect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vPos,D3DXVECTOR3& vOffsetPos,
			D3DXVECTOR3& vScale,D3DXVECTOR3& vRot);
/**************************************************************************
 virtual ~Groove();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~Groove();
/**************************************************************************
 void GrooveCalculation(float i_Score);
 用途: ゲージ増減の計算
 戻り値: なし
***************************************************************************/
	void GrooveCalculation(float i_fDistanceRate,JUDGE i_Judge);
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);

	float getGaugePercent(){
		return m_GaugePercent;
	}


};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/




/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class Score;
 用途: スコアクラス
****************************************************************************/
class Score : public Sprite{
	
public:
		RECT	g_Rect[ 10 ];		//  : 数字を表す範囲
		int     g_iScore;			//  : スコアのデータ
		int     num_places;			//  : 描画するスコアの桁数
		int     place;				//  : スコアの描画対象の位
		int		number;				//  : スコアの位を切り出す
		D3DXVECTOR3   pos;			//  : スコアを表示する座標をずらす
/*************************************************************************
 Score(
	LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9インターフェイスへのポインタ
    D3DXVECTOR3		m_vPos;			//	: 描画する位置(画面左上を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vOffsetPos;	//	: オフセット座標(描画位置を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vScale;		//	: 伸縮度合い
	D3DXVECTOR3		m_vCenter;		//	: 画像の中心とする位置(画像の左上を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vRot;			//	: 描く軸ごとの回転度合い
	Rect*			m_Rect;			//	: 表示する画像の範囲
	SpriteItem		m_MeshItem;		//	: 座標データとかマテリアルとか。（SpriteItemに変更予定）
    );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
    Score(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* Rect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vPos,D3DXVECTOR3& vOffsetPos,
			D3DXVECTOR3& vScale,D3DXVECTOR3& vRot);
/**************************************************************************
 virtual ~Score();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~Score();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/




/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class OjouFactoryP;
 用途: 静的なスコアとゲージの描画クラス
****************************************************************************/
	class OjouFactoryP {

	public:
/**************************************************************************
 OjouFactoryP(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	OjouFactoryP(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~OjouFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~OjouFactoryP();
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

	
}
}