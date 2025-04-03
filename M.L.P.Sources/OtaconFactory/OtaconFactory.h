/**************************************************************************
 MainFactory.h
                                                    2012/43/06　名前
													2012/06/17  大幅修正 鴫原 徹
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Object.h"
#include "../Sprite.h"
#include "../Stage_Play.h"
namespace wiz{
namespace Otacon{

	
	

	
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/	
/**************************************************************************
 class OtaconFactory;
 用途: メイン工場クラス
****************************************************************************/
class OtaconFactory{
public:
/**************************************************************************
 OtaconFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	OtaconFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~OtaconFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~OtaconFactory();
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/






/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class ResultFactory;
 用途: メイン工場クラス
****************************************************************************/
class ResultFactory{
public:


/**************************************************************************
 ResultFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
ResultFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec,int Score,ResultFactor& Factor);
/**************************************************************************
 ~ResultFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	//~ResultFactory();
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/





/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class RankSprite : public Sprite
 用途: ランクの計算及び描画のためのクラス
****************************************************************************/
class RankSprite : public Sprite{
	public:
/**************************************************************************
 RankSprite(
	LPDIRECT3DDEVICE9 pD3DDevice,	//	: IDirect3DDevice9 インターフェイスへのポインタ
	wstring	     I_fileName,		//	: テクスチャファイル名
	Rect*        i_Rect,			//	: テクスチャの描画範囲
	D3DXVECTOR3& i_vPos,			//	: 描画する座標
	D3DXVECTOR3& i_vScale			//	: 伸縮率
	);
 用途: コンストラクタ
 戻り値: なし。
***************************************************************************/
		RankSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_fileName,Rect* i_Rect,
			D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vScale ,ResultFactor i_RankFactor,int i_iScore);
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
		void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
				 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/





/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class ScoreSprite : public Sprite
 用途: スコアを描画するためのクラス
****************************************************************************/
class ScoreSprite : public Sprite{
	protected:
        int SHaba;
		int RScore;

	public:
		Rect SFont[10];
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
		ScoreSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_fileName,Rect* i_Rect,
			D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vScale ,int i_Score);
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
		void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
				 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/






/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class WhiteOutSprite : public Sprite
 用途: ホワイトアウト処理を行うためのクラス
****************************************************************************/
class WhiteOutSprite : public Sprite{
	protected:
		bool OutFlg;
		bool m_CntrolLock;
		DWORD m_Command;

	public:
/**************************************************************************
 WhiteOutSprite(
	LPDIRECT3DDEVICE9 pD3DDevice,	//	: IDirect3DDevice9 インターフェイスへのポインタ
	wstring	     i_fileName,		//	: テクスチャファイル名
	);
 用途: コンストラクタ
 戻り値: なし。
***************************************************************************/
		WhiteOutSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_fileName,DWORD i_Command);
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
		void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
					 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);


};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/







}
}