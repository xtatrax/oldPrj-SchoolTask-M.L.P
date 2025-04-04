/**************************************************************************
 DxDevice.h

 class DxDevice;宣言
****************************************************************************/
#pragma once

#include "StdAfx.h"
namespace wiz{
/**************************************************************************
 依存するクラス
****************************************************************************/
class Scene;
class XBoxController;

/**************************************************************************
 class DxDevice;
 用途: DirectXデバイスクラス
****************************************************************************/
class DxDevice {
    LPDIRECT3D9             m_pD3D;         // IDirect3D9インターフェイスへのポインタ
    LPDIRECT3DDEVICE9       m_pD3DDevice;   // IDirect3DDevice9インターフェイスへのポインタ
    D3DPRESENT_PARAMETERS   m_D3DPP;        // デバイスのプレゼンテーションパラメータ
    XBoxController*         m_pController;  // コントローラのポインタ
/**************************************************************************
 void Clear();
 用途: オブジェクトのクリア
 戻り値: なし
***************************************************************************/
    void Clear();
public:
/**************************************************************************
 DxDevice(
    HWND hWnd,          //ウインドウのハンドル
    bool isFullScreen,  //フルスクリーンかどうか
    int Width,          //領域の幅
    int Height          //領域の高さ
);
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
    DxDevice(HWND hWnd,bool isFullScreen,int Width,int Height);
/**************************************************************************
 ~DxDevice();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    ~DxDevice();
/**************************************************************************
 LPDIRECT3DDEVICE9 getDevice();
 用途: デバイスの取得
 戻り値: IDirect3DDevice9インターフェイスへのポインタ。失敗したら0
***************************************************************************/
    LPDIRECT3DDEVICE9 getDevice();
/**************************************************************************
 void RenderScene(
     Scene* pScene  //シーンへのポインタ
 );
 用途: シーンの描画
 戻り値: なし
***************************************************************************/
    void RenderScene(Scene* pScene);
};
}
//end of namespace wiz.

