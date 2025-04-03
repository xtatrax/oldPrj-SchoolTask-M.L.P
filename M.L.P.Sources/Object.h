/**************************************************************************
 Object.h

 struct CONTROLER_STATE; 宣言
 class XBoxController; 宣言、定義
 struct Command; 宣言、定義
 class Object; 宣言、定義
 class Stage; 宣言
 class ShadowVolume; 宣言
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Texture.h"
#include "Prim2D.h"
namespace wiz{


/**************************************************************************
 struct CONTROLER_STATE;
 用途: XBoxコントローラーのステータス
****************************************************************************/
struct CUSTOM_CONTROLER_STATE
{

    //	: 数値幅変更版[-1,+1]
    float fThumbRX;
    float fThumbRY;
    float fThumbLX;
    float fThumbLY;

	//	: 一フレームのみ有効
	WORD wPressedButtons;
    bool bPressedLeftTrigger;
    bool bPressedRightTrigger;

    //	: 最後に押されたボタンCONTROLER_STATE
    WORD wLastButtons;
    bool bLastLeftTrigger;
    bool bLastRightTrigger;

};
/**************************************************************************
 struct CONTROLER_STATE;
 用途: XBoxコントローラーのステータス
****************************************************************************/
struct CONTROLER_STATE
{
	CUSTOM_CONTROLER_STATE CustomState;
    XINPUT_STATE state;
    bool   bConnected;
	WPARAM KeyBoardState;
	Point  MousePoint;
};
/**************************************************************************
 class XBoxController;
 用途: XBoxコントローラー
****************************************************************************/
class XBoxController{
    static const DWORD MAX_CONTROLLERS = 4;
    CONTROLER_STATE m_State[MAX_CONTROLLERS];
public:
	static WPARAM KeyBoardState;
	static Point  MousePoint;
/**************************************************************************
 XBoxController();
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
    XBoxController(){
		::ZeroMemory(m_State,sizeof(CONTROLER_STATE));
	}
/**************************************************************************
 ~XBoxController();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    ~XBoxController(){}
/**************************************************************************
 const CONTROLER_STATE* GetState();
 用途: コントローラーの状態を得る
 戻り値: コントローラーのステータス
***************************************************************************/
    const CONTROLER_STATE* GetState(){
        DWORD dwResult;
        for( DWORD i = 0; i < MAX_CONTROLLERS; i++ )
        {
			m_State[i].KeyBoardState = KeyBoardState;
			KeyBoardState = 0;
			m_State[i].MousePoint = MousePoint;
			m_State[i].CustomState.wLastButtons = m_State[i].state.Gamepad.wButtons;

            // XInputから現在のステータスを得る
            dwResult = XInputGetState( i, &m_State[i].state );

			if( dwResult == ERROR_SUCCESS ){
                m_State[i].bConnected = true;
                //レバーのデッドゾーンの設定
                if((m_State[i].state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
                     m_State[i].state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) && 
                    (m_State[i].state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
                     m_State[i].state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) )
                {   
                   m_State[i].state.Gamepad.sThumbLX = 0;
                   m_State[i].state.Gamepad.sThumbLY = 0;
                }

                if( (m_State[i].state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
                     m_State[i].state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) && 
                    (m_State[i].state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
                    m_State[i].state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ) 
                {
                   m_State[i].state.Gamepad.sThumbRX = 0;
                   m_State[i].state.Gamepad.sThumbRY = 0;
                }
				m_State[i].CustomState.wPressedButtons = (m_State[i].CustomState.wLastButtons ^ m_State[i].state.Gamepad.wButtons) & m_State[i].state.Gamepad.wButtons;
            }
            else{
                m_State[i].bConnected = false;
            }
        }
        return m_State;
    }
/**************************************************************************
 const DWORD getMaxControllers() const;
 用途: コントローラーの最大数を得る
 戻り値: 現バージョンでは定数が返る（4）
***************************************************************************/
    const DWORD getMaxControllers() const{
        return MAX_CONTROLLERS;
    }
};



/**************************************************************************
 struct Command;
 用途: シーン内、ステージ内でやり取りされるコマンド
 ＊コマンド内容の定義は、各コンテンツにまかせる
****************************************************************************/
struct Command{
	DWORD m_Command;
	DWORD m_Param1;
	DWORD m_Param2;
	DWORD m_Param3;
	Command()
		:m_Command(0),m_Param1(0),m_Param2(0),m_Param3(0)
	{}
	void Clear(){
		m_Command = m_Param1 = m_Param2 = m_Param3 = 0;
	}
	~Command(){
		Clear();
	}
};



/**************************************************************************
 class Object;
 用途: シーン配置オブジェクトの基底クラス（抽象クラス）
****************************************************************************/
class Object{
public:
/**************************************************************************
 Object();
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
    Object(){}
/**************************************************************************
 virtual ~Object();
 用途: 仮想デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~Object(){}
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,
        const CONTROLER_STATE* pCntlState,Command& Com) = 0;
/**************************************************************************
	virtual void DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect,			//エフェクトのポインタ
	D3DXMATRIX& mCameraView,			//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
 用途: 影ボリュームを描画（仮想関数）
 戻り値: なし。
***************************************************************************/
	virtual void DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,
	LPD3DXEFFECT pEffect,
	D3DXMATRIX& mCameraView,
	D3DXMATRIX& mCameraProj){
		//基底クラスでは何もしない
	}
};



/**************************************************************************
 class Stage;
 用途: ゲームをステージ単位で管理するクラス
****************************************************************************/
class Stage{
protected:
	//親ステージ
	Stage* m_pParStage;
	//子ステージ
	Stage* m_pChildStage;
	//ダイアログステージかどうか
	bool m_IsDialog;
    //配置オブジェクトのポインタのベクトル
    vector<Object*> m_Vec;
    //テクスチャのポインタのベクトル
    vector<Texture*> m_TextureVec;
/**************************************************************************
 void Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 Stage();
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	Stage();
/**************************************************************************
 Stage(
 Stage* Par	//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	Stage(Stage* Par);
/**************************************************************************
virtual ~Stage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~Stage();
/**************************************************************************
Stage* getPar();
 用途: 親ステージを得る
 戻り値: 親ステージのポインタ
***************************************************************************/
	const Stage* getPar() const{
		return m_pParStage;
	}
/**************************************************************************
Stage* geChild();
 用途: 子ステージを得る
 戻り値: 子ステージのポインタ
***************************************************************************/
	Stage* geChild(){
		return m_pChildStage;
	}
/**************************************************************************
Stage* getLastStage();
 用途: 一番最後尾の子ステージを得る
 戻り値: 一番最後尾の子ステージのポインタ
***************************************************************************/
	Stage* getLastStage(){
		if(m_pChildStage){
			return m_pChildStage->getLastStage();
		}
		else{
			return this;
		}
	}
/**************************************************************************
Stage* getActiveStage();
 用途: 今、アクティブなステージを得る
 戻り値: アクティブなステージのポインタ
 ＊最後尾の子がダイアログタイプだった場合
 　そのダイアログを保持するステージを得る
***************************************************************************/
	Stage* getActiveStage(){
		Stage* ret = getLastStage();
		while(ret->m_IsDialog){
			ret = ret->m_pParStage;
		}
		return ret;
	}
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,
				Command& Com);
};


/**************************************************************************
 class ShadowVolume;
 用途: シャドウボリュームクラス
 ＊DXUTサンプルをベースに作成
****************************************************************************/
class ShadowVolume{
	/**************************************************************************
	 struct SHADOWVERT;
	 用途: 影のFVFデータ
	 ＊DXUTより引用
	****************************************************************************/
	struct SHADOWVERT
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Normal;
		const static D3DVERTEXELEMENT9 Decl[3];
	};
	/**************************************************************************
	 struct CEdgeMapping;
	 用途: エッジマッピングクラス
	 ＊DXUTより引用
	****************************************************************************/
	struct CEdgeMapping
	{
		int m_anOldEdge[2];  // vertex index of the original edge
		int m_aanNewEdge[2][2]; // vertex indexes of the new edge
		// First subscript = index of the new edge
		// Second subscript = index of the vertex for the edge
	public:
			CEdgeMapping()
			{
				FillMemory( m_anOldEdge, sizeof( m_anOldEdge ), -1 );
				FillMemory( m_aanNewEdge, sizeof( m_aanNewEdge ), -1 );
			}
	};
	const FLOAT ADJACENCY_EPSILON;
	LPD3DXMESH m_pShadowVolumeMesh;
	IDirect3DVertexDeclaration9*    m_pShadowDecl;
	/**************************************************************************
	 int FindEdgeInMappingTable()関数
	 用途: エッジマッピング関数
	 ＊DXUTより引用
	****************************************************************************/
	//--------------------------------------------------------------------------------------
	// Takes an array of CEdgeMapping objects, then returns an index for the edge in the
	// table if such entry exists, or returns an index at which a new entry for the edge
	// can be written.
	// nV1 and nV2 are the vertex indexes for the old edge.
	// nCount is the number of elements in the array.
	// The function returns -1 if an available entry cannot be found.  In reality,
	// this should never happens as we should have allocated enough memory.
	int FindEdgeInMappingTable( int nV1, int nV2, CEdgeMapping* pMapping, int nCount )
	{
		for( int i = 0; i < nCount; ++i )
		{
			// If both vertex indexes of the old edge in mapping entry are -1, then
			// we have searched every valid entry without finding a match.  Return
			// this index as a newly created entry.
			if( ( pMapping[i].m_anOldEdge[0] == -1 && pMapping[i].m_anOldEdge[1] == -1 ) ||

				// Or if we find a match, return the index.
				( pMapping[i].m_anOldEdge[1] == nV1 && pMapping[i].m_anOldEdge[0] == nV2 ) )
			{
				return i;
			}
		}

		return -1;  // We should never reach this line
	}
/**************************************************************************
 void Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 ShadowVolume(
 LPDIRECT3DDEVICE9 pd3dDevice,	//デバイス
 LPD3DXMESH pMesh			//元となるメッシュ
 );
 用途: コンストラクタ（シャドウボリュームを作成する）
 戻り値: なし
***************************************************************************/
	ShadowVolume(LPDIRECT3DDEVICE9 pd3dDevice, LPD3DXMESH pMesh);
/**************************************************************************
 ~ShadowVolume();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~ShadowVolume();
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect			//エフェクトへのポインタ
 );
 用途: 影ボリュームを描画
 戻り値: なし。
***************************************************************************/
    void Draw(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect);
};


}
//end of namespace wiz.

