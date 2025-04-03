/**************************************************************************
 MainFactory.h
                                                    2012/43/06　名前
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Object.h"
#include "../Sprite.h"
#include "../ButtonPlate.h"

namespace wiz{
namespace Koromoeb{

/***************************************************************************
class MoveLevel : pbulic Sprite;
用途 : メインメニュークラス
***************************************************************************/
class MoveLevel : public Sprite{
public:

/**************************************************************************
MoveLevel(
LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
LPDIRECT3DTEXTURE9 pTexture	//テクスチャ
);
	用途: コンストラクタ
	戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
MoveLevel(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_filename,
		D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vOffsetPos,D3DXVECTOR3& i_vScale,
		D3DXVECTOR3& i_vCenter,D3DXVECTOR3& i_vRot,Rect* i_Rect);

/**************************************************************************
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
		vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};


/***************************************************************************
class NameScrew : public ButtonPlate;
用途 : メインメニュークラス
***************************************************************************/
//class NameScrew{}	//これがクラスの形
class NameScrew : public ButtonPlate{
public:

/**************************************************************************
NameScrew(
LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
);
	用途 : コンストラクタ
****************************************************************************/
	NameScrew(LPDIRECT3DDEVICE9 pD3DDevice,DWORD Cmd,DWORD Index,
		D3DXVECTOR3 pos,D3DXVECTOR3 size,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0);	//これがクラスの形

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
class BackGrund : public Sprite;
用途 : メインメニュークラス
***************************************************************************/
class BackGrund : public Sprite{
public:

/*************************************************************************
BackGrund(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
用途 : コンストラクタ
*************************************************************************/
	BackGrund(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_filename,
			D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vOffsetPos,D3DXVECTOR3& i_vScale,
			D3DXVECTOR3& i_vCenter,D3DXVECTOR3& i_vRot,Rect* i_Rect);

/**************************************************************************
 ~BackGrund();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~BackGrund();
};


/**************************************************************************
 class KoromoebFactoryMS;
 用途: メイン工場クラス
****************************************************************************/
class KoromoebFactoryMS{
public:
/**************************************************************************
 KoromoebFactoryMS(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	KoromoebFactoryMS(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~KoromoebFactoryMS();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~KoromoebFactoryMS();
};

/**************************************************************************
 class KoromoebFactoryGO;
 用途: 工場クラス
	   ここで基本となるオブジェの生成を行う
****************************************************************************/
class KoromoebFactoryGO{
public:
/**************************************************************************
 KoromoebFactoryGO(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	KoromoebFactoryGO(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~KoromoebFactoryGO();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~KoromoebFactoryGO();
};

}
}