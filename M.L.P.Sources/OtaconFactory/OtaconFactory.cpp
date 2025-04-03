/**************************************************************************
 MainFactory.cpp

                                                    2012/04/06　名前 
													2012/06/17  大幅修正 鴫原 徹
****************************************************************************/
#include "StdAfx.h"
#include "../Object.h"
#include "../Scene.h"
#include "OtaconFactory.h"
#include "../Sprite.h"

namespace wiz{
namespace Otacon{

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 OtaconFactory 定義部
****************************************************************************/
/**************************************************************************
 OtaconFactory::OtaconFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
OtaconFactory::OtaconFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec)
{
	try{

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 OtaconFactory::~OtaconFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
OtaconFactory::~OtaconFactory()
		{
			//なにもしない
		}
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/





/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 ResultFactory 定義部
****************************************************************************/
/**************************************************************************
 ResultFactory::ResultFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
ResultFactory::ResultFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec,int Score,ResultFactor& Factor)
{
	try{
		//画像の色んなデータ
		//背景
		vec.push_back(new Sprite(pD3DDevice, L"Media/Texture/result-back.png",
					  &Rect(0,0,800,480),         //切り出し
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//中心（）
					  D3DXVECTOR3(0.0f,0.0f,1.0f),//ポジション（ゆがみね～）
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//オフセット
					  D3DXVECTOR3(1.0f,1.0f,0.0f),//大きさ（ナウい）
					  D3DXVECTOR3(0.0f,0.0f,0.0f))//角度
					  
					  );
		////曲名バー
		//vec.push_back(new Sprite(pD3DDevice,L"Media/Texture/result-music_nameB.png",
		//			  &Rect(0,0,396,78),                       //切り出し
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),//中心（）
		//			  D3DXVECTOR3(20.0f,105.0f,0.9f),//ポジション（ゆがみね～）
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),//オフセット
		//			  D3DXVECTOR3(1.0f,1.0f,0.0f),//大きさ（ナウい）
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f))//角度
		//			  
		//			  );

		//曲名
		vec.push_back(new Sprite(pD3DDevice,Factor.m_BannerPath,
					  NULL,                       //切り出し
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//中心（）
					  D3DXVECTOR3(30.0f,110.0f,0.8f),//ポジション（ゆがみね～）
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//オフセット
					  D3DXVECTOR3(1.0f,1.0f,0.0f),//大きさ（ナウい）
					  D3DXVECTOR3(0.0f,0.0f,0.0f))//角度
					  
					  );




		//スコアバー
		vec.push_back(new Sprite(pD3DDevice,L"Media/Texture/result-scoreB.png",
					  &Rect(0,0,400,50),       //切り出し
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//中心（）
					  D3DXVECTOR3(380.0f,420.0f,0.9f),//ポジション（ゆがみね～）
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//オフセット
					  D3DXVECTOR3(1.0f,1.0f,0.0f),//大きさ（ナウい）
					  D3DXVECTOR3(0.0f,0.0f,0.0f))//角度
					  
					  );

		//ランクバー
		vec.push_back(new Sprite(pD3DDevice,L"Media/Texture/result-rankB.png",
					  &Rect(0,0,295,277),                       //切り出し
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//中心（）
					  D3DXVECTOR3(20.0f,193.0f,0.9f),//ポジション（ゆがみね～）
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//オフセット
					  D3DXVECTOR3(1.0f,1.0f,0.0f),//大きさ（ナウい）
					  D3DXVECTOR3(0.0f,0.0f,0.0f))//角度
					  
					  );



		//ランクフォント
		vec.push_back(new RankSprite(
				pD3DDevice,
				L"Media/Texture/result-rankF.png",
				&Rect(0,0,200,200),					//	: テクスチャの描画範囲
				D3DXVECTOR3(80.0f,240.0f,0.8f),		//	: 描画座標
				g_vOne,								//	: 伸縮率
				Factor,								//	: ランクを計算するための
				Score								//	: スコア
				)
		);

		//スコアフォント
		vec.push_back(new ScoreSprite(
				pD3DDevice,
				L"Media/Texture/result-scoreF.png",
				&Rect(0,0,27,40),					//	: テクスチャの描画範囲
				D3DXVECTOR3(750.0f,425.0f,0.8f),	//	: 描画座標
				g_vOne,								//	: 伸縮率
				Score								//	: 描画するスコア
				)
		);

		DWORD com ;
		if(Factor.m_fGaugePar >= 70.0f){
			//クリア
			vec.push_back(new Sprite(
				pD3DDevice,
				L"Media/Texture/result_Clear.png",
				NULL,
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXVECTOR3(340.0f,240.0f,0.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f))
				);

			com = Scene::SC_OPEN_MUSICSELECT;
		}else{
			//ゲームオーバー
			vec.push_back(new Sprite(
				pD3DDevice,
				L"Media/Texture/result_Not Clear.png",
				NULL,
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXVECTOR3(330.0f,190.0f,0.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f))
				);

			com = Scene::SC_OPEN_GAMEOVER;
		}
		//ホワイトアウト
		vec.push_back(new WhiteOutSprite(pD3DDevice, L"Media/Texture/result-WhiteOut.png",com));

	}
	catch(...){
		//再throw
		throw;
	}
}
/**************************************************************************
 ResultFactory::~ResultFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
//ResultFactory::~ResultFactory()
//{
//    //なにもしない
//}
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/








/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 RankSprite 定義部
****************************************************************************/
/**************************************************************************
 RankSprite::RankSprite(
	LPDIRECT3DDEVICE9 pD3DDevice,	//	: IDirect3DDevice9 インターフェイスへのポインタ
	wstring	     I_fileName,		//	: テクスチャファイル名
	Rect*        i_Rect,			//	: テクスチャの描画範囲
	D3DXVECTOR3& i_vPos,			//	: 描画する座標
	D3DXVECTOR3& i_vScale			//	: 伸縮率
	);
 用途: コンストラクタ
 戻り値: なし。
***************************************************************************/
RankSprite::RankSprite(
		LPDIRECT3DDEVICE9  pD3DDevice,wstring i_fileName,Rect* i_Rect,
		D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vScale,ResultFactor i_RankFactor,int i_iScore)
		:Sprite( pD3DDevice, i_fileName, i_Rect, g_vZero,i_vPos,g_vZero,i_vScale,g_vZero)
{
	try{
		BYTE byteRankNum = 0;
		float fRankPar = (float)i_iScore / ((float)i_RankFactor.m_dwAllNoteQt * 100.0f) ;
		if(fRankPar >= 0.90f){
			byteRankNum = 0;
		}else
		if(fRankPar >= 0.70f){
			byteRankNum = 1;
		}else
		if(fRankPar >= 0.60f){
			byteRankNum = 2;
		}else
		//if(fRankPar >= 0.90f)
		{
			byteRankNum = 3;
		}
		i_Rect->right;
		m_SpriteItem.m_pRect->left  = i_Rect->right * byteRankNum;
		m_SpriteItem.m_pRect->right = m_SpriteItem.m_pRect->left + i_Rect->right;
	}
	catch(...)
	{
		throw;
	}
}
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: ランク画像を描画
 戻り値: なし。
***************************************************************************/
void RankSprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	Sprite::Draw( pD3DDevice, Vec, pCntlState, Com);
}
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/








/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 ScoreSprite 定義部
****************************************************************************/
/**************************************************************************
 ScoreSprite(
	LPDIRECT3DDEVICE9 pD3DDevice,	//	: IDirect3DDevice9 インターフェイスへのポインタ
	wstring	     I_fileName,		//	: テクスチャファイル名
	Rect*        i_Rect,			//	: テクスチャの描画範囲
	D3DXVECTOR3& i_vPos,			//	: 描画する座標
	D3DXVECTOR3& i_vScale,			//	: 伸縮率
	int			 i_iScore			//	: スコア
	);
 用途: コンストラクタ
 戻り値: なし。
***************************************************************************/
ScoreSprite::ScoreSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_fileName,Rect* i_Rect,
									D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vScale,int i_Score)
	: Sprite( pD3DDevice, i_fileName, i_Rect, g_vZero, i_vPos, g_vZero, i_vScale, g_vZero)
{
	try{
		SHaba =27;
		RScore = i_Score;
		for(int i = 0;i < 10; i++)
		{
			SFont[i].left = i * SHaba;
			SFont[i].top = 0;
			SFont[i].right = SFont[i].left + SHaba;
			SFont[i].bottom = 40;
		
		}
	}
	catch(...)
	{		
		throw;
	}

}
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: スコア画像を描画
 戻り値: なし。
***************************************************************************/
void ScoreSprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	int Keta = 1;
	m_SpriteItem.m_vOffsetPos.x = 0.0f;
	for(int i = 0;i <8; i++)
	{
		// 描画する位置と桁、切り出し位置の計算
		*m_SpriteItem.m_pRect = SFont[RScore / Keta % 10];
		Keta *=10;

		m_SpriteItem.m_vOffsetPos.x -=  SHaba;
		
		//	描画する
		Sprite::Draw( pD3DDevice, Vec, pCntlState, Com);
	}
}
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/




/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 ScoreSprite 定義部
****************************************************************************/
/**************************************************************************
 WhiteOutSprite(
	LPDIRECT3DDEVICE9 pD3DDevice,	//	: IDirect3DDevice9 インターフェイスへのポインタ
	wstring	     i_fileName,		//	: テクスチャファイル名
	);
 用途: コンストラクタ
 戻り値: なし。
***************************************************************************/
WhiteOutSprite::WhiteOutSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,DWORD i_Command)
	:Sprite( pD3DDevice, fileName, NULL,g_vZero,g_vZero,g_vZero,g_vOne,g_vZero),
	 m_CntrolLock(true),m_Command(i_Command)
{
	try{
		m_SpriteItem.m_Color =(0x00000000);
		OutFlg = 0;
	}
	catch(...)
	{
			
		throw;
	}

}

/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: ホワイトあうおを描画
 戻り値: なし。
***************************************************************************/
void WhiteOutSprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	if(!(pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_A)){
		m_CntrolLock = false;

	}
	//セレクト画面に移動する
	if(!m_CntrolLock && !OutFlg && (pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_A)){
		OutFlg =true;
	}

	if(OutFlg){
		if( m_SpriteItem.m_Color.m_DwordColor >= (0xFF000000)){
			Com.m_Command =m_Command;
			Com.m_Param1 = 0;
			Com.m_Param2 = 0;
			
		}
		m_SpriteItem.m_Color.m_DwordColor += 0x01000000;
	}
	//	描画する
	Sprite::Draw( pD3DDevice, Vec, pCntlState, Com);
	
}
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/





}
}