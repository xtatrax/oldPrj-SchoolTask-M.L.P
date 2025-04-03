/**************************************************************************
OjouFactoryP.cpp

													2012/04/06　名前 
													2012/06/18  修正 鴫原 徹
****************************************************************************/
#include "StdAfx.h"
#include "OjouFactoryP.h"


namespace wiz{
namespace Ojou{

/**************************************************************************
 SupportMultiPlateDown 定義部
****************************************************************************/
/**************************************************************************
 SupportMultiPlateDown::SupportMultiPlateDown(
    LPDIRECT3DDEVICE9 pD3DDevice   //IDirect3DDevice9インターフェイスへのポインタ
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
SupportMultiPlateDown::SupportMultiPlateDown(LPDIRECT3DDEVICE9 pD3DDevice)
:MultiPlate(pD3DDevice)
{}
/**************************************************************************
 void MultiPlate::Clear();
 用途:Itemの破棄
 戻り値: なし
***************************************************************************/
void SupportMultiPlateDown::Clear(){
	vector<PlateItem*>::iterator it;
    for(it = m_ItemVec.begin();it != m_ItemVec.end();it++){
        SafeDelete(*it);
    }
    m_ItemVec.clear();
	//*テクスチャはリリースしてはいけない
}

/**************************************************************************
 SupportMultiPlateDown::~SupportMultiPlateDown();
 戻り値: なし
***************************************************************************/
SupportMultiPlateDown::~SupportMultiPlateDown(){
}
/**************************************************************************
 void SupportMultiPlateDown::AddPlate(
    D3DXVECTOR3 move,				//移動
    D3DXVECTOR3 size,               //大きさ
    D3DXVECTOR3 pos,                //最初の位置
	D3DXVECTOR3 rot,				//回転(角度単位)。
    D3DCOLORVALUE Diffuse,          //ディフューズ色
    D3DCOLORVALUE Specular,         //スペキュラ色
    D3DCOLORVALUE Ambient           //アンビエント色
	int SupportButtonL				//十字キーの値
	int SupportButtonR				//ボタンの値
	D3DXVECTOR3 m_BasePos;			//初期位置
    );
 用途: プレートを追加
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
void SupportMultiPlateDown::AddPlate(D3DXVECTOR3 move,D3DXVECTOR3 center,D3DXVECTOR3 pos,
		D3DXVECTOR3 size ,D3DXVECTOR3 turn,D3DXVECTOR3 rot,
		D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient,int SupportButtonL,int SupportButtonR){
	try{
		ButtonMoveItem* pItem = new ButtonMoveItem(g_vZero,pos,size,g_vZero,rot,Diffuse,Specular,Ambient,SupportButtonL,SupportButtonR);
		pItem->m_Move = move;
		pItem->m_MeshItem.m_vSize = size;
		pItem->m_MeshItem.m_vPos = pos;
		pItem->m_BasePos = pos;

		pItem->m_SupportButtonL=SupportButtonL;
		pItem->m_SupportButtonR=SupportButtonR;

		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationYawPitchRoll(&mRot,
			D3DXToRadian(rot.y),D3DXToRadian(rot.x),D3DXToRadian(rot.z));
   
		m_ItemVec.push_back(pItem);
	}
	catch(...){
		Clear();
		throw;
	}
}


/**************************************************************************
 void SupportMultiPlateDown::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
 );
 用途: 直方体を描画
 戻り値: なし。
***************************************************************************/
void SupportMultiPlateDown::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){
    //配置オブジェクトの描画
    vector<PlateItem*>::size_type sz = m_ItemVec.size();
    for(vector<PlateItem*>::size_type i = 0;i < sz;i++){
		ButtonMoveItem* pItem = dynamic_cast<ButtonMoveItem*>(m_ItemVec[i]);

		//CommonMeshクラスのマティリアルを設定
		m_MeshItem = m_ItemVec[i]->m_MeshItem;



		//押されている間下げる
		if(pCntlState[0].state.Gamepad.wButtons & pItem->m_SupportButtonR 
			||pCntlState[0].state.Gamepad.wButtons & pItem->m_SupportButtonL) 
		{
			if(m_ItemVec[i]->m_MeshItem.m_vPos.y >= -0.0000000001f)
				m_ItemVec[i]->m_MeshItem.m_vPos-=pItem->m_Move;
		}

		//押されていない
		else
		{
			//初期位置に戻る
			if(m_ItemVec[i]->m_MeshItem.m_vPos != pItem->m_BasePos){
				m_ItemVec[i]->m_MeshItem.m_vPos.y += 0.035f;
				if(m_ItemVec[i]->m_MeshItem.m_vPos.y >= pItem->m_BasePos.y)
					m_ItemVec[i]->m_MeshItem.m_vPos = pItem->m_BasePos;
			}
		}
		// マトリックスをレンダリングパイプラインに設定
		pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
		
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(pD3DDevice,Vec,pCntlState,Com);
    }
}

/**************************************************************************
 Groove 定義部
****************************************************************************/
/**************************************************************************
 Groove::Groove(
    LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9インターフェイスへのポインタ
    D3DXVECTOR3		m_vPos;			//	: 描画する位置(画面左上を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vOffsetPos;	//	: オフセット座標(描画位置を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vScale;		//	: 伸縮度合い
	D3DXVECTOR3		m_vCenter;		//	: 画像の中心とする位置(画像の左上を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vRot;			//	: 描く軸ごとの回転度合い
	Rect*			m_Rect;			//	: 表示する画像の範囲
	SpriteItem		m_SpriteItem;		//	: 座標データとかマテリアルとか。（SpriteItemに変更予定）
    );
 用途: コンストラクタ
 戻り値: なし
****************************************************************************/
Groove::Groove(LPDIRECT3DDEVICE9 pD3DDevice, 
		wstring fileName,
		Rect* rect,
		D3DXVECTOR3& vCenter,
		D3DXVECTOR3& vPos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& vScale,
		D3DXVECTOR3& vRot)
		:Sprite(pD3DDevice, fileName, rect, vCenter, vPos, vOffsetPos, vScale, vRot),
		 m_GaugePercent(20.00f),
		 m_BadQt(0)
{
	m_rectGrooveBorder	= g_rectGroove	= *rect;
	m_rectGrooveBorder.top += rect->bottom;
	m_rectGrooveBorder.bottom = m_rectGrooveBorder.top + rect->bottom;
	g_rectGroove.left	= rect->left	+ 16;
	g_rectGroove.right	= rect->right	- 16;
	m_iTextureWideFive  = (g_rectGroove.right - g_rectGroove.left) / 20;
}
/**************************************************************************
  ~Groove::Groove();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Groove::~Groove(){
}
/**************************************************************************
 void GrooveCalculation(float i_Score);
 用途: ゲージ増減の計算
 戻り値: なし
***************************************************************************/
void Groove::GrooveCalculation(float i_fDistanceRate,JUDGE i_Judge){
	if(i_Judge == GREAT || i_Judge == GOOD ){
		m_GaugePercent += i_fDistanceRate;
	}else{
		if(++m_BadQt >= 3){
			m_GaugePercent -= 5.0f;
			if(m_GaugePercent < 0.0f)
				m_GaugePercent = 0.0f;
			m_BadQt = 0;
		}
	}
	if(m_GaugePercent <= 0){
		m_GaugePercent = 0;
	}
	if(m_GaugePercent >= 100.0f){
		m_GaugePercent = 100.0f;
	}
}

void Groove::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	if(m_pSprite && m_SpriteItem.m_Textuer.getTexture())
	{
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			m_pSprite->SetTransform( &m_SpriteItem.getMatrix());

			g_rectGroove.right	= (m_iTextureWideFive * (int(m_GaugePercent / 5) +1 ));

			D3DXVECTOR3	vInFramePos  =  D3DXVECTOR3(16.0f,0.0f,0.0f);
			m_pSprite->Draw(m_SpriteItem.m_Textuer.getTexture(), &g_rectGroove,
				&m_SpriteItem.m_vCenter, &vInFramePos, 0xffffffff );

			m_pSprite->Draw(m_SpriteItem.m_Textuer.getTexture(), &m_rectGrooveBorder,
				&m_SpriteItem.m_vCenter, &m_SpriteItem.m_vOffsetPos, 0xffffffff );
		}
		m_pSprite->End();
	}
}


/**************************************************************************
 Score 定義部
****************************************************************************/
/**************************************************************************
 Score::Score(
    LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9インターフェイスへのポインタ
    D3DXVECTOR3		m_vPos;			//	: 描画する位置(画面左上を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vOffsetPos;	//	: オフセット座標(描画位置を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vScale;		//	: 伸縮度合い
	D3DXVECTOR3		m_vCenter;		//	: 画像の中心とする位置(画像の左上を0,0としピクセル単位、スクリーン座標系)
	D3DXVECTOR3		m_vRot;			//	: 描く軸ごとの回転度合い
	Rect*			m_Rect;			//	: 表示する画像の範囲
	SpriteItem		m_SpriteItem;		//	: 座標データとかマテリアルとか。（SpriteItemに変更予定）
    );
 用途: コンストラクタ
 戻り値: なし
****************************************************************************/
Score::Score(LPDIRECT3DDEVICE9 pD3DDevice, 
		wstring fileName,
		Rect* rect,
		D3DXVECTOR3& vCenter,
		D3DXVECTOR3& vPos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& vScale,
		D3DXVECTOR3& vRot)
		:Sprite(pD3DDevice, fileName, rect, vCenter, vPos, vOffsetPos, vScale, vRot),
		 g_iScore()
{
}
/**************************************************************************
  ~Score::Score();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Score::~Score(){
}

void Score::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	if(m_pSprite && m_SpriteItem.m_Textuer.getTexture()){
			m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
			{
				m_pSprite->SetTransform( &m_SpriteItem.getMatrix());

				////	: スコアのデータ
				//g_iScore	= 20120523 ;	
				
				//	: 数字の描画範囲の設定
				for( int i = 0 ; i < 10 ; i++ )
				{
					g_Rect[ i ].left	= i * NUMBERS_WIDTH ;	
					g_Rect[ i ].top		= 0 ;	
					g_Rect[ i ].right	= g_Rect[ i ].left + NUMBERS_WIDTH ;
					g_Rect[ i ].bottom	= NUMBERS_HEIGHT ;
				}

				//	: スコアを描画する処理	
				num_places	= 8 ;	//桁数
				place		= 1 ;	
				for( int i = 0 ; i < num_places ; i++ ) {
					number	= g_iScore / place % 10 ;									
					pos	= D3DXVECTOR3( float((num_places-1-i)*NUMBERS_WIDTH), 0.0f, 0.0f );

				m_pSprite->Draw(m_SpriteItem.m_Textuer.getTexture(),&g_Rect[number] /*m_SpriteItem.m_pRect*/,
					&m_SpriteItem.m_vCenter, &pos, 0xffffffff );
				place	*= 10 ;																
				}
			}
			m_pSprite->End();
		}

	
}	

/**************************************************************************
 OjouFactoryP 定義部
****************************************************************************/
/**************************************************************************
 OjouFactoryP::OjouFactoryP(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	vector<Texture*>& TexVec		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
OjouFactoryP::OjouFactoryP(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{

		//ラインのマティリア
        D3DCOLORVALUE ButtonLineDiffuse	= {0.0f,0.0f,0.0f,1.0f};
        D3DCOLORVALUE ButtonLineSpecular= {0.0f,0.0f,0.0f,0.3f};
        D3DCOLORVALUE ButtonLineAmbient	= {0.0f,0.0f,0.0f,0.3f};

		//ボタン青
		D3DCOLORVALUE ButtonBDiffuse	= {0.0f,0.0f,1.0f,1.0f};
        D3DCOLORVALUE ButtonBSpecular	= {0.0f,0.0f,1.0f,1.0f};
        D3DCOLORVALUE ButtonBAmbient	= {0.0f,0.0f,1.0f,1.0f};

		//ボタン緑
		D3DCOLORVALUE ButtonGDiffuse	= {0.0f,1.0f,0.0f,1.0f};
        D3DCOLORVALUE ButtonGSpecular	= {0.0f,1.0f,0.0f,0.0f};
        D3DCOLORVALUE ButtonGAmbient	= {0.0f,1.0f,0.0f,0.0f};

		//ボタン黄
		D3DCOLORVALUE ButtonYDiffuse	= {1.0f,1.0f,0.0f,1.0f};
        D3DCOLORVALUE ButtonYSpecular	= {1.0f,1.0f,0.0f,0.0f};
        D3DCOLORVALUE ButtonYAmbient	= {1.0f,1.0f,0.0f,0.0f};

		//ボタン赤
		D3DCOLORVALUE ButtonRDiffuse	= {1.0f,0.0f,0.0f,1.0f};
        D3DCOLORVALUE ButtonRSpecular	= {1.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE ButtonRAmbient	= {1.0f,0.0f,0.0f,0.0f};
		
		//スコア
		vec.push_back(
			new Score(pD3DDevice,
			L"Media/Texture/play_scoreF.png",
			&Rect(0,0,NUMBERS_WIDTH,NUMBERS_HEIGHT),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(570.0f,5.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f)));

		//グルーヴゲージ内枠
		vec.push_back(
			new Groove(pD3DDevice,
			L"Media/Texture/Play_groove.png",
			&Rect(0,0,352,64),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(2.5f,5.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f)));

		////グルーヴゲージ外枠
		//vec.push_back(
		//	new Sprite(pD3DDevice,
		//	L"Media/Texture/Play_groove.png",
		//	&Rect(0,0,325,78),
		//	D3DXVECTOR3(0.0f,0.0f,0.0f),
		//	D3DXVECTOR3(2.50f,5.0f,0.0f),
		//	D3DXVECTOR3(0.0f,0.0f,0.0f),
		//	D3DXVECTOR3(1.0f,1.0f,0.0f),
		//	D3DXVECTOR3(0.0f,0.0f,0.0f)));

		//スコアプレート
		vec.push_back(
			new Sprite(pD3DDevice,
			L"Media/Texture/play_scoreB.png",
			&Rect(0,0,110,40),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(450.0f,5.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f)));

		//ノートが消える後ろのライン
		vec.push_back(
			new Plate(pD3DDevice,
			D3DXVECTOR3(0.0f,0.090f,-2.1f),
			D3DXVECTOR3(1.5f,0.01f,0.2f),
			ButtonLineDiffuse,ButtonLineSpecular,ButtonLineAmbient));

		SupportMultiPlateDown* mp = new SupportMultiPlateDown(pD3DDevice);

		//青
		mp->AddPlate(D3DXVECTOR3(0.0f,0.03f,0.0f),//下がる速さ
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(-0.715f,0.09f,-2.4f),//pos
					D3DXVECTOR3(0.3f,0.15f,0.3f),//size
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					ButtonBDiffuse,ButtonBSpecular,ButtonBAmbient,
					XINPUT_GAMEPAD_DPAD_LEFT,
					XINPUT_GAMEPAD_X);

		//緑
		mp->AddPlate(D3DXVECTOR3(0.0f,0.03f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(-0.28f,0.09f,-2.4f),
					D3DXVECTOR3(0.3f,0.15f,0.3f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					ButtonGDiffuse,ButtonGSpecular,ButtonGAmbient,
					XINPUT_GAMEPAD_DPAD_DOWN,
					XINPUT_GAMEPAD_A);

		//黄
		mp->AddPlate(D3DXVECTOR3(0.0f,0.03f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(+0.15f,0.09f,-2.4f),
					D3DXVECTOR3(0.3f,0.15f,0.3f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					ButtonYDiffuse,ButtonYSpecular,ButtonYAmbient,
					XINPUT_GAMEPAD_DPAD_UP,
					XINPUT_GAMEPAD_Y);

		//赤
		mp->AddPlate(D3DXVECTOR3(0.0f,0.03f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(+0.58f,0.09f,-2.4f),
					D3DXVECTOR3(0.3f,0.15f,0.3f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					ButtonRDiffuse,ButtonRSpecular,ButtonRAmbient,
					XINPUT_GAMEPAD_DPAD_RIGHT,
					XINPUT_GAMEPAD_B);

		vec.push_back(mp);

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
OjouFactoryP::~OjouFactoryP(){
    //なにもしない
}



}
}