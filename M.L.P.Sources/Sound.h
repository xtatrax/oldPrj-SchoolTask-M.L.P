/**************************************************************************
 MainFactory.h

 class Light : public Object; 宣言
 class DirectionalLight : public Light; 宣言
 class Camera : public Object; 宣言
 class LookDownCamera : public Camera; 宣言
 class Guide : public Object; 宣言
 class Shadow: public Object; 宣言

                                                    2012/04/17　自分の名前
****************************************************************************/
#pragma once

#include "StdAfx.h"
namespace wiz{



/**************************************************************************
 class Sound: public Object;
 用途: サウンドクラス
****************************************************************************/
class Sound : public Object{
protected:
	IXACT3Engine* m_pEngine;
	IXACT3WaveBank* m_pWaveBank;
	IXACT3SoundBank* m_pSoundBank;
	VOID* m_pbWaveBank; // Handle to wave bank data.  Its memory mapped so call UnmapViewOfFile() upon cleanup to release file
	VOID* m_pbSoundBank; // Pointer to sound bank data.  Call delete on it when the sound bank is destroyed
/**************************************************************************
 void Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 Sound(
 const wchar_t* pWavBankFileName,		//Wavバンクのファイル名
 const wchar_t* pSoundBankFileName	//Soundバンクのファイル名
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName);
/**************************************************************************
 virtual ~Sound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~Sound();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 描画（サウンドなのでなにもしない）
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};


/**************************************************************************
 class ZapSound: public Sound;
 用途: Zapサウンドクラス
****************************************************************************/
class ZapSound : public Sound{
	XACTINDEX m_iZap;
	XACTINDEX m_iFire;
public:
/**************************************************************************
 ZapSound(
 const wchar_t* pWavBankFileName,		//Wavバンクのファイル名
 const wchar_t* pSoundBankFileName	//Soundバンクのファイル名
 const char* pZapKey				//爆発音のキー
 const char* pFireKey				//発射音のキー
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	ZapSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,
		const char* pZapKey,const char* pFireKey);
/**************************************************************************
 virtual ~ZapSound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~ZapSound();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 描画（サウンドなのでなにもしない）
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
/**************************************************************************
 void PlayZap();
 用途: 爆発を鳴らす
 戻り値: なし。
***************************************************************************/
    void PlayZap();
/**************************************************************************
 void PlayFire();
 用途: 発射音を鳴らす
 戻り値: なし。
***************************************************************************/
    void PlayFire();

};




}
//end of namespace wiz.

