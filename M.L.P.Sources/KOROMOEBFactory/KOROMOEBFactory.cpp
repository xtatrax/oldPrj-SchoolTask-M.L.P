/**************************************************************************
 MainFactory.cpp

                                                    2012/04/06　名前 
****************************************************************************/
#include "StdAfx.h"
#include "../Object.h"
#include "../Scene.h"
#include "KoromoebFactory.h"

namespace wiz{
namespace Koromoeb{

/**************************************************************************
Sprite 定義部
**************************************************************************/
/**************************************************************************
MoveLevel::MoveLevel(
LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
LPDIRECT3DTEXTURE9 pTexture	//テクスチャ
);
	用途: コンストラクタ
	戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
MoveLevel::MoveLevel(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_filename,
		D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vOffsetPos,D3DXVECTOR3& i_vScale,
		D3DXVECTOR3& i_vCenter,D3DXVECTOR3& i_vRot,Rect* i_Rect)
:Sprite(pD3DDevice,i_filename,i_Rect,i_vPos,i_vOffsetPos,i_vScale,i_vCenter,i_vRot)
{
}

/**************************************************************************
 virtual void ButtonPlate::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 直方体を描画
 戻り値: なし。
***************************************************************************/
void MoveLevel::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
					 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	//if(m_pTexture){
	//	DWORD wkdword;
	//	pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
	//	pD3DDevice->SetTexture(0,m_pTexture);
	//	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
	//	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	//	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	//	pD3DDevice->SetFVF(PlateFVF);
	//	//マトリックスレンダリングパイプラインに設定
	//	pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
	//	//ボタンプレートのDrawを呼ぶ
	//	ButtonPlate::Draw(pD3DDevice,Vec,pCntlState,Com);
	//	pD3DDevice->SetTexture(0,0);

	//	pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	//}
	//else{
	//	//マトリックスレンダリングパイプラインに設定
	//	pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
	//	//ボタンプレートのDrawを呼ぶ
	//	ButtonPlate::Draw(pD3DDevice,Vec,pCntlState,Com);
	//}
}



/**************************************************************************
ButtonPlate 定義部
****************************************************************************/
/**************************************************************************
NameScrew::NameScrew(
    LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
	DWORD Cmd,						//選択実行されたときのコマンド
	DWORD Index,					//メニューステージ上のインデックス
    D3DXVECTOR3 size,               //大きさ
    D3DXVECTOR3 pos,                //位置
    D3DCOLORVALUE& Diffuse,         //ディフューズ色
    D3DCOLORVALUE& Specular,        //スペキュラ色
    D3DCOLORVALUE& Ambient,         //アンビエント色
	LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし
****************************************************************************/
NameScrew::NameScrew(LPDIRECT3DDEVICE9 pD3DDevice,DWORD Cmd,DWORD Index,
	D3DXVECTOR3 pos,D3DXVECTOR3 size,
	D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	LPDIRECT3DTEXTURE9 pTexture)
:ButtonPlate(pD3DDevice,Cmd,Index,size,pos,Diffuse,Specular,Ambient,pTexture)
{
}

/**************************************************************************
 virtual void ButtonPlate::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 直方体を描画
 戻り値: なし。
***************************************************************************/
void NameScrew::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
					 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	if(m_pTexture){
		DWORD wkdword;
		pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		pD3DDevice->SetTexture(0,m_pTexture);
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		pD3DDevice->SetFVF(PlateFVF);
		//マトリックスレンダリングパイプラインに設定
		pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
		//ボタンプレートのDrawを呼ぶ
		ButtonPlate::Draw(pD3DDevice,Vec,pCntlState,Com);
		pD3DDevice->SetTexture(0,0);

		pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
		//マトリックスレンダリングパイプラインに設定
		pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
		//ボタンプレートのDrawを呼ぶ
		ButtonPlate::Draw(pD3DDevice,Vec,pCntlState,Com);
	}
}


/*************************************************************************
BackGrund 定義部
**************************************************************************/
/*************************************************************************
BackGrund::BackGrund(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
用途 : コンストラクタ
戻り値 : なし
*************************************************************************/
BackGrund::BackGrund(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_filename,
			D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vOffsetPos,D3DXVECTOR3& i_vScale,
			D3DXVECTOR3& i_vCenter,D3DXVECTOR3& i_vRot,Rect* i_Rect)
:Sprite(pD3DDevice,i_filename,i_Rect,i_vPos,i_vOffsetPos,i_vScale,i_vCenter,i_vRot)
{
		try{
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 BackGrund::~BackGrund();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
BackGrund::~BackGrund(){
    //なにもしない
}




/**************************************************************************
 KoromoebFactoryMS 定義部
****************************************************************************/
/**************************************************************************
 KoromoebFactoryMS::KoromoebFactoryMS(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
KoromoebFactoryMS::KoromoebFactoryMS(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{

	//	D3DCOLORVALUE Diffuse	= {0.0f,1.0f,0.0f,1.0f};
	//	D3DCOLORVALUE Specular	= {0.0f,0.0f,0.0f,0.0f};
	//	D3DCOLORVALUE Ambient	= {0.5f,0.5f,0.5f,1.0f};

 //       //平板クラスのマティリアル
 //       D3DCOLORVALUE Plate1Diffuse		= {0.0f,1.0f,0.0f,1.0f};
 //       D3DCOLORVALUE Plate1Specular	= {0.0f,0.0f,0.0f,0.0f};
 //       D3DCOLORVALUE Plate1Ambient		= {0.5f,0.5f,0.5f,1.0f};

	//	//平板クラス2のマティリアル
	//	D3DCOLORVALUE Plate2Diffuse		= {0.0f,0.0f,1.0f,1.0f};
	//	D3DCOLORVALUE Plate2Specular	= {0.0f,0.0f,0.0f,0.0f};
	//	D3DCOLORVALUE Plate2Ambient		= {0.5f,0.5f,0.5f,1.0f};

	//	//平板クラス3のマティリアル
	//	D3DCOLORVALUE Plate3Diffuse		= {1.0f,0.0f,0.0f,1.0f};
	//	D3DCOLORVALUE Plate3Specular	= {0.0f,0.0f,0.0f,0.0f};
	//	D3DCOLORVALUE Plate3Ambient		= {0.5f,0.5f,0.5f,1.0f};

	//	//メニュー台マルチプレートのマティリアル
 //       D3DCOLORVALUE MPlateDiffuse2	= {1.0f,1.0f,1.0f,1.0f};
 //       D3DCOLORVALUE MPlateSpecular2	= {0.0f,0.0f,0.0f,0.0f};
 //       D3DCOLORVALUE MPlateAmbient2	= {0.5f,0.5f,0.5f,1.0f};

	//	//メニューマルチプレートのマティリアル
 //       D3DCOLORVALUE MPlateDiffuse3	= {1.0f,1.0f,1.0f,1.0f};
 //       D3DCOLORVALUE MPlateSpecular3	= {0.0f,0.0f,0.0f,0.0f};
 //       D3DCOLORVALUE MPlateAmbient3	= {0.5f,0.5f,0.5f,1.0f};



	//	//Texture* pFloorTx = new Texture(pD3DDevice,L"Media/Texture/floor_select.jpg");
	//	//Texture* pStartTx = new Texture(pD3DDevice,L"Media/Texture/game_start.jpg");
	//	//Texture* pExitTx = new Texture(pD3DDevice,L"Media/Texture/game_exit.jpg");

	//	////テクスチャをテクスチャ配列に追加
	//	//TexVec.push_back(pFloorTx);
	//	//TexVec.push_back(pStartTx);
	//	//TexVec.push_back(pExitTx);

 // //      //平板クラスのインスタンス構築
	//	////これは直接追加
 // //      vec.push_back(
 // //          new Plate(pD3DDevice,
 // //                  D3DXVECTOR3(10.0f,1.0f,0.0f),
 // //                  D3DXVECTOR3(0.0f,0.0f,0.0f),
	//	//			Plate1Diffuse,Plate1Specular,Plate1Ambient,
	//	//			pFloorTx->getTexture()));

	//	//テクスチャ
	//	Texture* pEasyTx		= new Texture(pD3DDevice,L"Media/Texture/Easy.png");
	//	Texture* pNormalTx		= new Texture(pD3DDevice,L"Media/Texture/Normal.png");
	//	Texture* pMusicSelectTx = new Texture(pD3DDevice,L"Media/Texture/MusicSelect.png");
	//	Texture* pPleaseStartTx = new Texture(pD3DDevice,L"Media/Texture/PleaseStart.png");
	//	Texture* pHardTx		= new Texture(pD3DDevice,L"Media/Texture/Hard.png");
	//	Texture* pSongTx		= new Texture(pD3DDevice,L"Media/Texture/Song.png");


	//	//テクスチャをテクスチャ配列に追加
	//	TexVec.push_back(pMusicSelectTx);
	//	TexVec.push_back(pEasyTx);
	//	TexVec.push_back(pNormalTx);
	//	TexVec.push_back(pHardTx);
	//	TexVec.push_back(pSongTx);
	//	TexVec.push_back(pPleaseStartTx);

	//	//平板クラスのインスタンス構築
	//	//イージーバー
	//	vec.push_back(
	//		new Sprite(pD3DDevice,
	//			pEasyTx->getTexture(),
	//			D3DXVECTOR3(29.5f,0.5f,0.0f),		//Pos
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),		//OffsetPos
	//			D3DXVECTOR3(1.0f,1.2f,0.0f),		//Scale
	//			D3DXVECTOR3(0.0f,-120.0f,0.0f),		//Center
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),		//Rot
	//			NULL));								//Rect


	//	//平板クラス2のインスタンス構築
	//	//ノーマルバー
	//	vec.push_back(
	//		new Sprite(pD3DDevice,
	//			pNormalTx->getTexture(),
	//			D3DXVECTOR3(29.5f,0.5f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			D3DXVECTOR3(1.0f,1.2f,0.0f),
	//			D3DXVECTOR3(1.0f,-180.0f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			NULL));

	//	//平板クラス3のインスタンス構築
	//	//ハードバー
	//	vec.push_back(
	//		new Sprite(pD3DDevice,
	//			pHardTx->getTexture(),
	//			D3DXVECTOR3(29.5f,0.5f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			D3DXVECTOR3(1.0f,1.2f,0.0f),
	//			D3DXVECTOR3(1.0f,-240.0f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			NULL));

	//	//メニュー台のマルチプレートのインスタンス構築
	//	//ミュージックセレクトバー
	//	vec.push_back(
	//		new Sprite(pD3DDevice,
	//			pMusicSelectTx->getTexture(),
	//			D3DXVECTOR3(10.0f,0.5f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			D3DXVECTOR3(1.0f,0.5,0.0f),
	//			D3DXVECTOR3(1.0f,0.0f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			NULL));

	//	//メニュー台のマルチプレートのインスタンス構築
	//	//プリーズスタートバー
	//	vec.push_back(
	//		new Sprite(pD3DDevice,
	//			pPleaseStartTx->getTexture(),
	//			D3DXVECTOR3(5.0f,410.0f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			D3DXVECTOR3(0.7f,1.0f,0.0f),
	//			D3DXVECTOR3(1.5f,0.0f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			NULL));

	//	////メニュー台のマルチプレートのインスタンス構築
	//	////真ん中の曲名バー
	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(1.0f,0.0f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));


	//	////ここから上の曲名バー
	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(1.5f,0.6f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));

	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(2.0f,1.2f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));

	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(2.5f,1.8f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));

	//	////ここから下の曲名バー
	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(1.5f,-0.6f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));

	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(2.0f,-1.2f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));

	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(2.5f,-1.8f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));
	//	//		//ここまでが曲名バー

	//	
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 KoromoebFactoryMS::~KoromoebFactoryMS();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
KoromoebFactoryMS::~KoromoebFactoryMS(){
    //なにもしない
}



/**************************************************************************
 KoromoebFactoryGO 定義部
****************************************************************************/
/**************************************************************************
 KoromoebFactoryGO::KoromoebFactoryGO(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
KoromoebFactoryGO::KoromoebFactoryGO(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{

		vec.push_back(
			new Sprite(pD3DDevice,
				L"Media/Texture/Lose.png",
				NULL,							//Rect
				D3DXVECTOR3(0.0f,0.0f,0.0f),	//Cneter
				D3DXVECTOR3(0.0f,0.0f,0.0f),	//Pos
				D3DXVECTOR3(0.0f,0.0f,0.0f),	//OffsetPos
				D3DXVECTOR3(0.79f,0.95f,0.0f),	//Scale
				D3DXVECTOR3(0.0f,0.0f,0.0f)		//Rot
				));							


	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 KoromoebFactoryGO::~KoromoebFactoryGO();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
KoromoebFactoryGO::~KoromoebFactoryGO(){
    //なにもしない
}

}
}