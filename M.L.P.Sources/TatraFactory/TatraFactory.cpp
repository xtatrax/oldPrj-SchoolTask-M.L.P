/**************************************************************************
 TatraFactory.cpp

                                                    2012/04/06　名前 鴫原 徹
****************************************************************************/
#include "StdAfx.h"
#include "../Object.h"
#include "../Scene.h"
#include "../MultiPlate.h"
#include "TatraFactory.h"
#include "JudgeLine.h"
#include "NoteObjects.h"
#include "../MainFactory.h"
#include "../ButtonPlate.h"
#include "../Sprite.h"
namespace wiz{
namespace Tatra{



/**************************************************************************
 TatraFactoryPlay 定義部
****************************************************************************/
/**************************************************************************
 TatraFactoryPlay::TatraFactoryPlay(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
TatraFactoryPlay::TatraFactoryPlay(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{

		//	: 判定スプライト
		Rect ClientRect;
		GetClientRect(NULL, ClientRect);

		//ぼたん
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*0,0,48*1,48),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 280 - 16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*2,0,48*3,48),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 350-16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*1,0,48*2,48),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 425-16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*3,0,48*4,48),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 500-16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));


		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*0,48,48*1,48*2),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 280+16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*2,48,48*3,48*2),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 350+16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*1,48,48*2,48*2),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 425+16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*3,48,48*4,48*2),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 500+16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));

	}
	catch(...){
		//再throw
		throw;
	}

}

/**************************************************************************
 TatraFactoryPlay::~TatraFactoryPlay();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
TatraFactoryPlay::~TatraFactoryPlay(){
    //なにもしない
}


/**************************************************************************
 TatraFactoryDBGS 定義部
****************************************************************************/
/**************************************************************************
 TatraFactoryDBGS::TatraFactoryDBGS(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
TatraFactoryDBGS::TatraFactoryDBGS(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{

        //平板クラスのインスタンス構築
		vec.push_back(new Guide(pD3DDevice));
        //平板クラスのマティリアル
        D3DCOLORVALUE Plate1Diffuse		= {0.8f,0.8f,0.8f,1.0f};
        D3DCOLORVALUE Plate1Specular	= {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE Plate1Ambient		= {0.2f,0.2f,0.2f,0.2f};

        //平板クラスのインスタンス構築
		vec.push_back(new JudgeLine(pD3DDevice ,
                    D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(0.5f,0.5f,0.5f),
					Plate1Diffuse,Plate1Specular,Plate1Ambient));
		//*/
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 TatraFactoryDBGS::~TatraFactoryDBGS();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
TatraFactoryDBGS::~TatraFactoryDBGS(){
    //なにもしない
}

/**************************************************************************
 TatraFactoryDBGM 定義部
****************************************************************************/
/**************************************************************************
 TatraFactoryDBGM::TatraFactoryDBGM(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
TatraFactoryDBGM::TatraFactoryDBGM(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{

        //平板クラスのインスタンス構築
		vec.push_back(new Guide(pD3DDevice));
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 TatraFactoryDBGM::~TatraFactoryDBGM();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
TatraFactoryDBGM::~TatraFactoryDBGM(){
    //なにもしない
}


}
}