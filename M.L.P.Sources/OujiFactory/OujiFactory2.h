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
#include "../CommonMesh.h"
namespace wiz{
namespace Ouji{

/**************************************************************************
 class OujiFactory;
 用途: メイン工場クラス
****************************************************************************/
class OujiFactory2{
public:
/**************************************************************************
 OujiFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	OujiFactory2(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~OujiFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~OujiFactory2();
};

}
}