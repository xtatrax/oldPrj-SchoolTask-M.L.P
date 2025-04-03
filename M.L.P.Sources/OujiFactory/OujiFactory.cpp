/**************************************************************************
 MainFactory.cpp

                                                    2012/04/06　名前 
****************************************************************************/
#include "StdAfx.h"
#include "../Object.h"
#include "../Scene.h"
#include "OujiFactory.h"
#include "../Plate.h"
#include "../MainFactory.h"
#include "../MultiPlate.h"
#include "../Sprite.h"

namespace wiz{
namespace Ouji{

/**************************************************************************
 OujiFactory 定義部
****************************************************************************/
/**************************************************************************
 OujiFactory::OujiFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
OujiFactory::OujiFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{
        //平板クラスのマティリアル
        D3DCOLORVALUE Plate1Diffuse = {1.0f,1.0f,0.0f,1.0f};
        D3DCOLORVALUE Plate1Specular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE Plate1Ambient = {0.4f,0.4f,0.4f,0.2f};

		//メニュー台マルチプレートのマティリアル
        D3DCOLORVALUE MPlateDiffuse2 = {0.5f,0.5f,0.5f,1.0f};
        D3DCOLORVALUE MPlateSpecular2 = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE MPlateAmbient2 = {0.2f,0.2f,0.2f,0.2f};

		//メニューマルチプレートのマティリアル
        D3DCOLORVALUE MPlateDiffuse3 = {0.4f,0.2f,0.0f,1.0f};
        D3DCOLORVALUE MPlateSpecular3 = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE MPlateAmbient3 = {0.2f,0.0f,0.0f,0.0f};




	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 OujiFactory::~OujiFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
OujiFactory::~OujiFactory(){
    //なにもしない
}

}
}