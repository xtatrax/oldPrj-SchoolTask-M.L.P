/**************************************************************************
 JudgeSprite.h

 class JudgeSprite : public Sprite;
                                                    2012/06/14　名前 鴫原 徹
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Sprite.h"

namespace wiz{
/**************************************************************************
 class JudgeSprite : public Sprite;
 用途: 判定を描画するクラス
****************************************************************************/
class JudgeSprite : public Sprite{
private:
	bool             m_bDrawFlag;			//	: 判定を描画するか否か
	float            m_fTimeAccumulator;	//	: 描画を開始してからの時間
	Rect             m_BassRect;			//	: ベースとなる描画範囲
protected:
public:
/**************************************************************************
 JudgeSprite(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
		wstring fileName,				//	: ファイル名
		Rect rect,						//	: テクスチャの描画範囲
		D3DXVECTOR3& vCenter,			//	: 中心位置
		D3DXVECTOR3& vPos,				//	: 表示位置
		D3DXVECTOR3& vOffsetPos,		//	: ローカル座標
		D3DXVECTOR3& vScale,			//	: 伸縮
		D3DXVECTOR3& vRot,				//	: 回転
		D3DCOLOR color					//	: 色
	);
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	JudgeSprite(
		LPDIRECT3DDEVICE9 pD3DDevice,
		wstring fileName,
		Rect rect,
		D3DXVECTOR3& vCenter,
		D3DXVECTOR3& vPos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& vScale,
		D3DXVECTOR3& vRot,
		D3DCOLOR color);

/**************************************************************************
 virtual ~JudgeSprite();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~JudgeSprite();

/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,				//オブジェクトの配列
    const CONTROLER_STATE* pCntlState,	//コントローラのステータス
	Command& Com						//シーンからステージ、もしくはステージからオブジェクトに
										//渡されるコマンドの参照
 );
 用途: オブジェクトを描画
 戻り値: なし。
***************************************************************************/
	virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
		vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
/**************************************************************************
 void setJudge(
	PlayStage::JUDGE			//	: 描画する判定
 );
 用途: オブジェクトを描画
 戻り値: なし。
***************************************************************************/
	void setJudge(BYTE Judge);
};


}