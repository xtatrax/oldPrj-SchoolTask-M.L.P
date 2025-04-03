/**************************************************************************
OjouFactory.cpp

                                                    2012/04/06　名前 
****************************************************************************/
#include "StdAfx.h"
#include "../Object.h"
#include "../Scene.h"
#include "../Plate.h"
#include "OjouFactory.h"
#include "../Sprite.h"
#include "../TatraFactory/SpriteItem.h"




namespace wiz{
namespace Ojou{


/**************************************************************************
 IconMove 定義部
****************************************************************************/
/**************************************************************************
 IconMove::IconMove(
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
	SpriteItem		m_SpriteItem;		//	: 座標データとかマテリアルとか。（SpriteItemに変更予定）
    );
 用途: コンストラクタ
 戻り値: なし
****************************************************************************/
IconMove::IconMove(LPDIRECT3DDEVICE9 pD3DDevice,
		wstring fileName,
		Rect* rect,
		D3DXVECTOR3& vCenter,
		D3DXVECTOR3& vPos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& vScale,
		D3DXVECTOR3& vRot)
		:Sprite(pD3DDevice, fileName, rect, vCenter, vPos, vOffsetPos, vScale, vRot)
{
}
/**************************************************************************
  ~IconMove::IconMove();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
IconMove::~IconMove(){
}
void IconMove::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	
	
	//コマンドを受け取る
	if(Com.m_Command == ButtonSprite::SELECT_ITEM){
		if(Com.m_Param1)
		{
			//Iconの位置を移動
			m_SpriteItem.m_vPos.x = 420;
			
		}
		else
		{
			
			m_SpriteItem.m_vPos.x = 60;
		}
	}
	
	if(m_pSprite && m_SpriteItem.m_Textuer.getTexture()){
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{

			m_pSprite->SetTransform( &m_SpriteItem.getMatrix());
			m_pSprite->Draw(m_SpriteItem.m_Textuer.getTexture(), m_SpriteItem.m_pRect,
				&m_SpriteItem.m_vCenter, &m_SpriteItem.m_vOffsetPos, 0xffffffff );
		}
		m_pSprite->End();
	}

	
}

/**************************************************************************
 ButtonSprite 定義部
****************************************************************************/
/**************************************************************************
 ButtonSprite::ButtonSprite(
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
	SpriteItem		m_SpriteItem;		//	: 座標データとかマテリアルとか。（SpriteItemに変更予定）
    );
 用途: コンストラクタ
 戻り値: なし
****************************************************************************/
ButtonSprite::ButtonSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,
		Rect* rect,
		DWORD Cmd, 
		DWORD Index,
		D3DXVECTOR3& vCenter,
		D3DXVECTOR3& vPos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& vScale,
		D3DXVECTOR3& vRot)
		:Sprite(pD3DDevice,fileName, rect, vCenter, vPos, vOffsetPos, vScale, vRot),m_ButtonPrm(Cmd,Index)

{
}

/**************************************************************************
  ~ButtonSprite::ButtonSprite();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ButtonSprite::~ButtonSprite(){
}
void ButtonSprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	

	D3DXMATRIX mTurn;
	D3DXQUATERNION mTurnQt;
	
	// ： 選択されていたら
	if(m_ButtonPrm.getSelect())
	{

		//コマンドを渡す
		Com.m_Command = this->SELECT_ITEM;
		Com.m_Param1 = m_ButtonPrm.getIndex();

		//くるくる
		static int flg = false;
		static float RotZ = 1.0f;
		D3DXMATRIX mRotZ;
		D3DXMatrixIdentity(&mRotZ);

		if(!flg && RotZ <= 58.0f)
		{
			RotZ += 1.0f;
			////D3DXQuaternionRotationYawPitchRoll(&m_SpriteItem.m_RotQt,
            //D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0));
			m_SpriteItem.m_RotQt=D3DXQUATERNION(0.0f,D3DXToRadian(RotZ),0.0f,0.0f);
		}	
	

		else if (flg && RotZ <= 1.0f)
		{
			flg = false;
		}
		else if (!flg && RotZ >= 59.0f)
		{
			RotZ -= 1.0f;
			m_SpriteItem.m_RotQt=D3DXQUATERNION(0.0f,D3DXToRadian(RotZ),0.0f,0.0f);
			flg = true;
		}

		else 
		{
			RotZ -= 1.0f;	
			m_SpriteItem.m_RotQt=D3DXQUATERNION(0.0f,D3DXToRadian(RotZ),0.0f,0.0f);		
		}
		
	}

	
	else
	{	
		//通常
		m_SpriteItem.m_RotQt=D3DXQUATERNION(0.0f,0.0f,0.0f,0.0f);
		D3DXMATRIX mTurn;
		D3DXMatrixIdentity(&mTurn);
		D3DXMatrixRotationQuaternion(&mTurn,&m_SpriteItem.m_TurnQt);	

	}
	
	if(m_pSprite && m_SpriteItem.m_Textuer.getTexture()){
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			m_pSprite->SetTransform( &m_SpriteItem.getMatrix());
			m_pSprite->Draw(m_SpriteItem.m_Textuer.getTexture(), m_SpriteItem.m_pRect,
				&m_SpriteItem.m_vCenter, &m_SpriteItem.m_vOffsetPos, 0xffffffff );
		}
		m_pSprite->End();
	}

	if(m_ButtonPrm.getBoot()){
		//コマンド発行
		Com = m_ButtonPrm.CommandIssue();
	}
}


/**************************************************************************
 OjouFactory 定義部
****************************************************************************/
/**************************************************************************
 OjouFactory::OjouFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
OjouFactory::OjouFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{
		
		//タイトル
		vec.push_back(
			new Sprite(pD3DDevice,
			L"Media/Texture/TraecLine.png",
			&Rect(0,0,550,280),
			D3DXVECTOR3(275.0f,140.0f,0.0f),
			D3DXVECTOR3(400.0f,140.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f)));

		//アイコン
		vec.push_back(
			new IconMove(pD3DDevice,
			L"Media/Texture/icon.png",
			&Rect(0,0,75,50),
			D3DXVECTOR3(37.5f,25.0f,0.0f),
			D3DXVECTOR3(60.0f,320.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f)));

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 OjouFactory::~OjouFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
OjouFactory::~OjouFactory(){
    //なにもしない
}



}
}