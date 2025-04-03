/**************************************************************************
 MainFactory.cpp

                                                    2012/04/06　名前 
****************************************************************************/
#include "StdAfx.h"
#include "OujiFactory2.h"
#include "../MultiPlate.h"
#include "../Sprite.h"
#include "Sp.h"
#include "SpLv.h"
#include "MusicPlate.h"
#include "BGPlate.h"
#include "../TATRAFactory/ScriptManager.h"

namespace wiz{
namespace Ouji{

/**************************************************************************
 OujiFactory2 定義部
****************************************************************************/
/**************************************************************************
 OujiFactory2::OujiFactory2(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
OujiFactory2::OujiFactory2(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{
        //平板クラスのマティリアル
        D3DCOLORVALUE Plate1Diffuse = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE Plate1Specular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE Plate1Ambient = {0.4f,0.4f,0.4f,0.2f};

		//メニュー台マルチプレートのマティリアル
        D3DCOLORVALUE MPlateDiffuse2 = {1.0f,1.0f,1.0f,1.0f};
        D3DCOLORVALUE MPlateSpecular2 = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE MPlateAmbient2 = {0.5f,0.5f,0.5f,0.5f};

		//メニューマルチプレートのマティリアル
        D3DCOLORVALUE MPlateDiffuse3 = {0.4f,0.2f,0.0f,1.0f};
        D3DCOLORVALUE MPlateSpecular3 = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE MPlateAmbient3 = {0.2f,0.0f,0.0f,0.0f};

//背景**********************************************************************
		Texture* BTx = new Texture(pD3DDevice,L"Media/Texture/back_serect.png");
		TexVec.push_back(BTx);

		Texture* GT1x = new Texture(pD3DDevice,L"Media/Texture/gradation1.png");
		TexVec.push_back(GT1x);

		Texture* GT2x = new Texture(pD3DDevice,L"Media/Texture/gradation2.png");
		TexVec.push_back(GT2x);

		Texture* GT3x = new Texture(pD3DDevice,L"Media/Texture/gradation3.png");
		TexVec.push_back(GT3x);

		Texture* GT4x = new Texture(pD3DDevice,L"Media/Texture/gradation4.png");
		TexVec.push_back(GT4x);

		MultiPlate* bmp	= new MultiPlate(pD3DDevice,BTx->getTexture());
		BGPlate* gmp1	= new BGPlate(pD3DDevice,GT1x->getTexture());
		BGPlate* gmp2	= new BGPlate(pD3DDevice,GT2x->getTexture());
		BGPlate* gmp3	= new BGPlate(pD3DDevice,GT3x->getTexture());
		BGPlate* gmp4	= new BGPlate(pD3DDevice,GT4x->getTexture());

		bmp->AddPlate(D3DXVECTOR3(15.0f,9.0f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,4.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					Plate1Diffuse,Plate1Specular,Plate1Ambient);

	//グラデーション******************
		gmp1->AddPlate(D3DXVECTOR3(6.0f,9.0f,0.0f),
					D3DXVECTOR3(-5.0f,0.0f,5.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					Plate1Diffuse,Plate1Specular,Plate1Ambient);

		gmp2->AddPlate(D3DXVECTOR3(6.0f,9.0f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,5.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					Plate1Diffuse,Plate1Specular,Plate1Ambient);

		gmp3->AddPlate(D3DXVECTOR3(6.0f,9.0f,0.0f),
					D3DXVECTOR3(5.0f,0.0f,5.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					Plate1Diffuse,Plate1Specular,Plate1Ambient);

		gmp4->AddPlate(D3DXVECTOR3(6.0f,9.0f,0.0f),
					D3DXVECTOR3(10.0f,0.0f,5.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					Plate1Diffuse,Plate1Specular,Plate1Ambient);
	//******************************
		vec.push_back(gmp1);
		vec.push_back(gmp2);
		vec.push_back(gmp3);
		vec.push_back(gmp4);
		vec.push_back(bmp);

//シーンタイトル***************************************************************
		vec.push_back(
			new Sprite(pD3DDevice,
						L"Media/Texture/MusicSelect.png",
						&Rect(0,0,256,128),
						D3DXVECTOR3(0.0f,0.0f,0.0f),
						D3DXVECTOR3(0.0f,0.0f,0.0f),
						D3DXVECTOR3(0.0f,0.0f,0.0f),
						D3DXVECTOR3(1.0f,1.0f,0.0f),
						D3DXVECTOR3(0.0f,0.0f,0.0f)));

		vec.push_back(
			new Sprite(pD3DDevice,
						L"Media/Texture/PleaseStart.png",
						&Rect(0,0,512,64),
						D3DXVECTOR3(0.0f,0.0f,0.0f),
						D3DXVECTOR3(0.0f,420.0f,0.0f),
						D3DXVECTOR3(0.0f,0.0f,0.0f),
						D3DXVECTOR3(1.0f,1.2f,0.0f),
						D3DXVECTOR3(0.0f,0.0f,0.0f)));

//曲名プレート*****************************************************************
		//曲とレベルを読み込む
		vector<Script::MLPHeader> hVec;
		Script::ScriptManager::SearchSongs(hVec);

		MusicPlate* mp = new MusicPlate(pD3DDevice);
		for(vector<Script::MLPHeader>::size_type i = 0, sz = hVec.size();i < sz ; i++)
		{
			Texture* MSTx = new Texture(pD3DDevice,hVec.at(i).FilePath + hVec.at(i).TitleBanner);
			TexVec.push_back(MSTx);
			mp->AddPlate(D3DXVECTOR3(3.8f,0.7f,0.0f),
						D3DXVECTOR3(0.0f,0.0f,0.0f),
						D3DXVECTOR3(0.0f,0.0f,0.0f),
						i,
						sz,
						hVec.at(i),
						MPlateDiffuse2,MPlateSpecular2,MPlateAmbient2,
						MSTx->getTexture());
			
		}
			vec.push_back(mp);

//レベルバー*******************************************************************
		vec.push_back(
			new Sp(pD3DDevice,
						L"Media/Texture/LevelBar.png",
						NULL,
						D3DXVECTOR3(0.0f,0.0f,0.0f),
						D3DXVECTOR3(30.0f,200.0f,0.0f),
						D3DXVECTOR3(0.0f,0.0f,0.0f),
						D3DXVECTOR3(1.0f,1.0f,0.0f),
						D3DXVECTOR3(0.0f,0.0f,0.0f)));

		vec.push_back(
			new SpLv(pD3DDevice,
						L"Media/Texture/Level.png",
						NULL,
						D3DXVECTOR3(0.0f,0.0f,0.0f),
						D3DXVECTOR3(190.0f,200.0f,0.0f),
						D3DXVECTOR3(0.0f,0.0f,0.0f),
						D3DXVECTOR3(1.0f,1.0f,0.0f),
						D3DXVECTOR3(0.0f,0.0f,0.0f)));

//***************************************************************************
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 OujiFactory2::~OujiFactory2();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
OujiFactory2::~OujiFactory2(){
    //なにもしない
}

}
}