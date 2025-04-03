/**************************************************************************
 Plate.cpp

 Plate; 定義
                                                    2012/03/04　名前 
****************************************************************************/
#include "StdAfx.h"
#include "NoteObjects.h"
#include "../Stage_Play.h"
#include "../OjouFactory/OjouFactoryP.h"

namespace wiz{
/**************************************************************************
 NoteObjects 定義部
***************************************************************************/
float NoteObjects::m_fNotationLength = 1.0f;
float NoteObjects::m_fHighSpeed = 1.0f;
float NoteObjects::m_fDeadLineZ = -1.75f;
/**************************************************************************
 void MultiPlate::Clear();
 用途:Itemの破棄
 戻り値: なし
***************************************************************************/
void NoteObjects::Clear(){
	//StdVecSafeDelete(m_ItemVec);
	vector<NoteItem*>::iterator it;
    for(it = m_ItemVec.begin();it != m_ItemVec.end();it++){
        SafeDelete(*it);
    }
    m_ItemVec.clear();
	//*テクスチャはリリースしてはいけない
}

/**************************************************************************
 NoteObjects::NoteObjects(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	D3DXVECTOR3 i_vPos,				//	: 出現位置
	D3DXVECTOR3 i_vSize,			//	: 大きさ
	D3DCOLORVALUE Diffuse,			//	: 
	D3DCOLORVALUE Specular,			//	:
	D3DCOLORVALUE Ambient,			//	: 
	LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
NoteObjects::NoteObjects(LPDIRECT3DDEVICE9 pD3DDevice,
		D3DXVECTOR3 i_vPos,
		D3DXVECTOR3 i_vSize,
		D3DCOLORVALUE i_Diffuse,
		D3DCOLORVALUE i_Specular,
		D3DCOLORVALUE i_Ambient,
		float HiSpeed,
		LPDIRECT3DTEXTURE9 pTexture
		)
	:Plate(pD3DDevice,i_vPos,g_vOne,i_Diffuse,i_Specular,i_Ambient,pTexture),
	 m_BassItem(g_vZero,i_vPos,i_vSize,g_vZero,g_vZero,i_Diffuse,i_Specular,i_Ambient)
{
    try{
		m_fHighSpeed = HiSpeed;
		m_MeshItem = m_BassItem;
    }
    catch(...){
        //コンストラクタ例外発生
        //再スロー
        throw;
    }
}
/**************************************************************************
 virtual ~NoteObjects();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
NoteObjects::~NoteObjects(){
	//Clear();
}
/**************************************************************************
 bool NoteObjects::FrameUpdate4SingleNote(
 );
 用途: 単音符状態の音符の更新
 戻り値: なし。
***************************************************************************/
bool NoteObjects::FrameUpdate4SingleNote(NoteItem* pTargetItem,float i_fMoveDis){

	pTargetItem->m_vPos.z -= i_fMoveDis;
	//	: 死亡フラグ
	if( pTargetItem->m_vPos.z < m_fDeadLineZ ){
		pTargetItem->m_bDead = true;
		return true;
	}
	return false;
}

/**************************************************************************
 void NoteObjects::FrameUpdate4LongNote(
 );
 用途: 長音符状態の音符の更新
 戻り値: なし。
***************************************************************************/
void NoteObjects::FrameUpdate4LongNote(NoteItem* pTargetItem,float i_fMoveDis,float i_fJudgePosZ){

	if(pTargetItem->m_byStatus == NoteItem::LongBegin){
		pTargetItem->m_vPos.z -= i_fMoveDis / 2;
		pTargetItem->m_vScale.z += i_fMoveDis;
	}else{
		pTargetItem->m_vPos.z -= i_fMoveDis;
	}
	float fWkDis;	//	ラインからはみ出した長さ
	if( (pTargetItem->m_bBoot && 
		(fWkDis = pTargetItem->m_vPos.z - (pTargetItem->m_vScale.z / 2) - i_fJudgePosZ ) <= 0 ) ||
		(fWkDis = pTargetItem->m_vPos.z - (pTargetItem->m_vScale.z / 2) - m_fDeadLineZ ) <= 0 )
		{
		pTargetItem->m_vPos.z += abs(fWkDis) / 2;
		if((pTargetItem->m_vScale.z -= abs(fWkDis)) <=0.0f){
			pTargetItem->m_bDead = true;
		}
		pTargetItem->m_bLastBoot = pTargetItem->m_bBoot;
		pTargetItem->m_bBoot = false;
	}
}


/**************************************************************************
 virtual void NoteObjects::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
 );
 用途: 直方体を描画
 戻り値: なし。
***************************************************************************/
void NoteObjects::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){

	//配置オブジェクトの描画
	PlayCommandPacket*		pPCPacket = NULL;
	Ojou::Groove*			pGroove   = NULL;
	//	: 一小節の
	if(Com.m_Command == PlayStage::SENDITEM){
		pPCPacket = (PlayCommandPacket*)Com.m_Param1;
		pGroove   = (Ojou::Groove*)Com.m_Param2;
	}
    NoteItemSizeType sz = m_ItemVec.size();
    for(NoteItemSizeType i = 0;i < sz;i++){
		//	: 生死判断
		//	: 描画するか
		//	: 埋葬するか
		NoteItem* pTargetItem = m_ItemVec[i];
		if(pTargetItem->m_bDead){

			SafeDelete(pTargetItem);
			m_ItemVec.erase(m_ItemVec.begin() + i--);
			sz = m_ItemVec.size();
		}
		else{
			//	: 移動距離の計算
			float MoveDis = ((m_fNotationLength / (pPCPacket->m_fMeasureChangeDelay * 2 )) * Tempus::getOneFrameTime() );

			//	: 処理方法の判断
			if(pTargetItem->m_byStatus == NoteItem::Single){
				//	: 単音の時
				if(FrameUpdate4SingleNote(pTargetItem,MoveDis)){
					pPCPacket->m_pJudgeSprite->setJudge(POOR);
					pPCPacket->m_pRankFactor->m_dwPoorQt++;
					pGroove->GrooveCalculation(0.0f,POOR);
				}
			}
			else{
				//	: 長音の時
				FrameUpdate4LongNote(pTargetItem,MoveDis,pPCPacket->m_fJudgePosZ);
			}

			D3DXMATRIX mPos;
			D3DXMatrixTranslation( &mPos , pTargetItem->m_vPos.x , pTargetItem->m_vPos.y ,pTargetItem->m_vPos.z );

			D3DXMATRIX mScale;
			D3DXMatrixScaling( &mScale,pTargetItem->m_vScale.x,pTargetItem->m_vScale.y,pTargetItem->m_vScale.z);
			m_Matrix = mScale * mPos;
			//テクスチャがある場合
			if(m_pTexture){
				DWORD wkdword;
				//現在のテクスチャステータスを得る
				pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
				//ステージの設定
				pD3DDevice->SetTexture(0,m_pTexture);
				//デフィーズ色とテクスチャを掛け合わせる設定
				pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
				pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
				pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

				pD3DDevice->SetFVF(PlateFVF);
				// マトリックスをレンダリングパイプラインに設定
				pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
				//コモンメッシュのDraw()を呼ぶ
				CommonMesh::Draw(pD3DDevice,Vec,pCntlState,Com);
				pD3DDevice->SetTexture(0,0);
				//ステージを元に戻す
				pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
			}
			else{
			//テクスチャがない場合
				// マトリックスをレンダリングパイプラインに設定
				pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
				//コモンメッシュのDraw()を呼ぶ
				CommonMesh::Draw(pD3DDevice,Vec,pCntlState,Com);
			}
#if defined(DEBUG) || defined(_DEBUG)
			Debugger::DBGSTR::addStr(L"ステータス = %d / SoundNum = %d\n" , m_ItemVec[i]->m_byStatus,m_ItemVec[i]->m_SoundNum);
#endif
		}

		//*/
    }
}
/**************************************************************************
 void NoteObjects::AddNote();
 用途: ノートを追加
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
void NoteObjects::AddNote(BYTE i_SoundNum,BYTE i_StatusNum){
	try{
		NoteItem* pItem = new NoteItem(
			m_BassItem.m_vPos,
			m_BassItem.m_vSize,
			i_SoundNum);
		pItem->m_bDead = false;
		pItem->m_byStatus  = i_SoundNum;
		m_ItemVec.push_back(pItem);
	}
	catch(...){
		Clear();
		throw;
	}
}

}