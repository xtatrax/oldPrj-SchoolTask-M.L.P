/**************************************************************************
 MainFactory.h
 class Camera:: public Object; 宣言
 class Guide: public Object; 宣言
 class CommonMesh: public Object; 宣言
 class Plate public Object: 宣言
 class MainFactory; 宣言
                                                    2012/43/06　名前
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Object.h"
#include "../Sprite.h"
#include "../TatraFactory/Button.h"
#include "../Scene.h"





namespace wiz{
namespace Ojou{


/**************************************************************************
 class IconMove;
 用途: コマンドによって動くクラス
****************************************************************************/
class IconMove : public Sprite{
	
public:
/*************************************************************************
 IconMove(
	LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9インターフェイスへのポインタ
    D3DXVECTOR3		m_vPos;			//	: 描画する位置(画面左上を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vOffsetPos;	//	: オフセット座標(描画位置を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vScale;		//	: 伸縮度合い
	D3DXVECTOR3		m_vCenter;		//	: 画像の中心とする位置(画像の左上を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vRot;			//	: 描く軸ごとの回転度合い
	Rect*			m_Rect;			//	: 表示する画像の範囲
	LPD3DXSPRITE	m_pSprite;		//	: 描画するためのスプライト
	SpriteItem		m_MeshItem;		//	: 座標データとかマテリアルとか。（SpriteItemに変更予定）
    );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
    IconMove(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* Rect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vPos,D3DXVECTOR3& vOffsetPos,
			D3DXVECTOR3& vScale,D3DXVECTOR3& vRot);
/**************************************************************************
 virtual ~IconMove();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~IconMove();
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

/**************************************************************************
 class ButtonSprite;
 用途: 2Dボタンクラス
****************************************************************************/
class ButtonSprite : public Sprite{
protected:
		
		bool m_IsAnime;	           // : アニメーションフラグ
		int m_AnimeCounter;	       // : アニメーションカウン
		D3DXVECTOR3 m_BasePos;     // : 基本の位置

public:
	    Button m_ButtonPrm;		   // : ボタンのパラメーター

		enum{
			SELECT_ITEM = 2000,
		};

/*************************************************************************
 ButtonSprite(
	LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9インターフェイスへのポインタ
	DWORD Cmd,						//  : 選択実行されたときのコマンド
	DWORD Index,					//  : メニューステージ上のインデックス
    D3DXVECTOR3		m_vPos;			//	: 描画する位置(画面左上を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vOffsetPos;	//	: オフセット座標(描画位置を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vScale;		//	: 伸縮度合い
	D3DXVECTOR3		m_vCenter;		//	: 画像の中心とする位置(画像の左上を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vRot;			//	: 描く軸ごとの回転度合い
	Rect*			m_Rect;			//	: 表示する画像の範囲
	LPD3DXSPRITE	m_pSprite;		//	: 描画するためのスプライト
	SpriteItem		m_MeshItem;		//	: 座標データとかマテリアルとか。（SpriteItemに変更予定）
    );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
    ButtonSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* Rect,
		DWORD Cmd,DWORD Index,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vPos,D3DXVECTOR3& vOffsetPos,
			D3DXVECTOR3& vScale,D3DXVECTOR3& vRot);
/**************************************************************************
 virtual ~ButtonSprite();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~ButtonSprite();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 直方体を描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};

/**************************************************************************
 class OjouFactory;
 用途: メイン工場クラス
****************************************************************************/
	class OjouFactory {
	public:

/**************************************************************************
 OjouFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	OjouFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~OjouFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~OjouFactory();
};

	
}
}