/**************************************************************************
 DxDevice.cpp

 class DxDevice 定義
****************************************************************************/
#include "StdAfx.h"
#include "DxDevice.h"
#include "Scene.h"
#include "TatraFactory/DebugFunks.h"
namespace wiz{
/**************************************************************************
 DxDevice 定義部
***************************************************************************/
/**************************************************************************
 void DxDevice::Clear();
 用途: オブジェクトのクリア
 戻り値: なし
***************************************************************************/
void DxDevice::Clear(){
    //コントローラーの開放
    SafeDelete(m_pController);
    // デバイスオブジェクトの解放
    SafeRelease(m_pD3DDevice);
    // DirectXGraphicsの解放
    SafeRelease(m_pD3D);
}
/**************************************************************************
 DxDevice::DxDevice(
    HWND hWnd,          //ウインドウのハンドル
    bool isFullScreen,  //フルスクリーンかどうか
    int Width,          //領域の幅
    int Height          //領域の高さ
);
 用途: コンストラクタ
 戻り値: なし。失敗したら例外をthrow
***************************************************************************/
DxDevice::DxDevice(HWND hWnd,bool isFullScreen,int Width,int Height)
 : m_pD3D(0), m_pD3DDevice(0),m_pController(0)
{
    try{
        D3DDISPLAYMODE d3ddm;
        // Direct3D9オブジェクトの作成
        if((m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION)) == 0){
            throw DxException(
                L"DirectXの初期化に失敗しました。DirectXインターフェイスが取得できません。",
                L"DxDevice::DxDevice()"
                );
        }
        
        // 現在のディスプレイモードを取得
        if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
            throw DxException(
                L"デバイスの初期化に失敗しました。ディスプレイモードを取得できません。",
                L"DxDevice::DxDevice()"
                );
        }

        // デバイスのプレゼンテーションパラメータを初期化
        ZeroMemory(&m_D3DPP, sizeof(D3DPRESENT_PARAMETERS));
        m_D3DPP.BackBufferCount         = 1;
        if(isFullScreen) { // フルスクリーンの場合
            m_D3DPP.Windowed                = FALSE;            // フルスクリーン表示の指定
            m_D3DPP.BackBufferWidth         = Width;            // フルスクリーン時の横幅
            m_D3DPP.BackBufferHeight        = Height;           // フルスクリーン時の縦幅
        }
        else {
            m_D3DPP.Windowed                = TRUE;             // ウインドウ内表示の指定
        }
        m_D3DPP.BackBufferFormat        = d3ddm.Format;         // カラーモードの指定
        m_D3DPP.SwapEffect              = D3DSWAPEFFECT_DISCARD; 
        m_D3DPP.EnableAutoDepthStencil  = TRUE;
        m_D3DPP.AutoDepthStencilFormat  = D3DFMT_D24S8;
        
        // ディスプレイアダプタを表すためのデバイスを作成
        // 描画と頂点処理をハードウェアで行なう
        if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                        D3DDEVTYPE_HAL, 
                                        hWnd, 
                                        D3DCREATE_HARDWARE_VERTEXPROCESSING, 
                                        &m_D3DPP, &m_pD3DDevice))) {
            // 上記の設定が失敗したら
            // 描画をハードウェアで行い、頂点処理はCPUで行なう
            if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                            D3DDEVTYPE_HAL, 
                                            hWnd, 
                                            D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
                                            &m_D3DPP, &m_pD3DDevice))) {
                // 上記の設定が失敗したら
                // 描画と頂点処理をCPUで行なう
                if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                                D3DDEVTYPE_REF, hWnd, 
                                                D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
                                                &m_D3DPP, &m_pD3DDevice))) {
                    // 初期化失敗
                    throw DxException(
                        L"デバイスの初期化に失敗しました。的確なデバイスを取得できません。",
                        L"DxDevice::DxDevice()"
                        );
                }
            }
        }

        m_pController = new XBoxController;
#if defined(DEBUG) || defined(_DEBUG)
		//	: デバッグ用文字列描画関数の初期化
		wiz::Debugger::DBGSTR::Init(m_pD3DDevice);
#endif
	}
    catch(...){
        //破棄処理
        Clear();
        //再スロー
        throw;
    }
}
/**************************************************************************
 DxDevice::~DxDevice();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
DxDevice::~DxDevice(){
    //オブジェクトの破棄
    Clear();
}
/**************************************************************************
 void DxDevice::RenderScene(
 Scene* pScene  // シーンへのポインタ
 );
 用途: シーンの描画
 戻り値: なし
***************************************************************************/
void DxDevice::RenderScene(Scene* pScene)
{
    try{
        if(!pScene){
            //シーンが無効ならスロー
            throw DxException(
                L"シーンが見つかりません。",
                L"DxDevice::RenderScene()"
                );
        }
        const CONTROLER_STATE* pCntlState;
        if(m_pController){
            pCntlState = m_pController->GetState();
        }
        // ビューポートと深度バッファの初期化とステンシルバッファのクリア
        if(FAILED(m_pD3DDevice->Clear(0,NULL,               // 初期化する領域は全面
                        D3DCLEAR_STENCIL |                  // ステンシルバッファを指定
                        D3DCLEAR_TARGET |                   // バックバッファを指定
                        D3DCLEAR_ZBUFFER,                   // 深度バッファ（Zバッファ）を指定
                        D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),  // 初期化する色
                        1.0f,                               // 初期化する深度バッファ（Zバッファ）の値
                        0))){                               // 初期化するステンシルバッファの値
            //失敗したらスロー
            throw DxException(
                L"バッファをクリアできません。",
                L"DxDevice::RenderScene()"
                );
        }
        // 描画開始宣言
        if(SUCCEEDED(m_pD3DDevice->BeginScene())) {
            // モデルなどの描画
            pScene->Draw(m_pD3DDevice,pCntlState);
#if defined(DEBUG) || defined(_DEBUG)
			//	: デバッグ用文字列の描画
			wiz::Debugger::DBGSTR::Draw();
#endif
            // 描画終了宣言
            m_pD3DDevice->EndScene();
        }
        // 描画結果の転送
        if(FAILED(m_pD3DDevice->Present( 0, 0, 0, 0 ))) {
            // デバイス消失から復帰
            if(m_pD3DDevice->Reset(&m_D3DPP)!= D3D_OK){
                //デバイスの復帰に失敗したらスロー
                throw DxException(
                    L"デバイスを復帰できません。",
                    L"DxDevice::RenderScene()"
                    );
            }
        }
        //タイミングをあわせる
		//::Sleep(10);
    }
    catch(...){
        //破棄処理
        Clear();
        //再スロー
        throw;
    }
}

/**************************************************************************
 LPDIRECT3DDEVICE9 DxDevice::getDevice();
 用途: デバイスの取得
 戻り値: IDirect3DDevice9インターフェイスへのポインタ。失敗したら0
***************************************************************************/
LPDIRECT3DDEVICE9 DxDevice::getDevice(){
    return m_pD3DDevice;
}
}
//end of namespace wiz.

