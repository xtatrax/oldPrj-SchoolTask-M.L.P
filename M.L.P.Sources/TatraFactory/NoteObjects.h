/**************************************************************************
 NoteObjects.h

 class NoteObjects : public Plate 宣言
                                                    2012/03/04　名前 鴫原 徹
****************************************************************************/
#pragma once
#include "../MultiPlate.h"

namespace wiz{
/**************************************************************************
 class NoteObjects : public Plate;
 用途: 複数の直方体クラス（コントローラで動作しない）
****************************************************************************/
class NoteObjects : public Plate{
protected:
	struct NoteItem {
		bool m_bDead;				//	: 死亡フラグ
		bool m_bInputReception;		//	: 入力受付
		bool m_bBoot;				//	:
		bool m_bLastBoot;			//	:
		BYTE		m_SoundNum;		//	: 再生する音声番号
		D3DXVECTOR3	m_vPos;			//	: 座標データ
		D3DXVECTOR3	m_vScale;		//	: 大きさ
		enum {
			ZERO,
			Single,
			LongBegin,
			LongEnd,
		};
		BYTE m_byStatus;
		NoteItem(D3DXVECTOR3& pos,D3DXVECTOR3& scale,BYTE SoundNum)
			:m_vPos(pos),m_vScale(scale),m_SoundNum(SoundNum),
			m_bDead(false),m_bInputReception(true),m_bBoot(false),m_bLastBoot(false)
		{
		}
	};
	vector<NoteItem*> m_ItemVec;
	static float m_fNotationLength;	//	: 60BPMの際 1秒に1小節ずつ流れる速さ
	static float m_fHighSpeed;	//	: 
	static float m_fDeadLineZ;	//	: 

	MeshItem	 m_BassItem;	//	: ベースとなる座標データやマテリアルなど
	D3DXMATRIX	 m_Matrix;		//	: 
	enum __STATUS{
		Live,					//	: 描画中
		Dead					//	: データ破棄
	};
	//BYTE Status;
	typedef vector<NoteItem*>::size_type NoteItemSizeType;
/**************************************************************************
 bool FrameUpdate4SingleNote(
 );
 用途: 単音符状態の音符の更新
 戻り値: なし。
***************************************************************************/
    bool FrameUpdate4SingleNote(NoteItem* pTargetItem,float i_fMoveDis);
/**************************************************************************
 void FrameUpdate4LongNote(
 );
 用途: 単音符状態の音符の更新
 戻り値: なし。
***************************************************************************/
    void FrameUpdate4LongNote(NoteItem* pTargetItem,float i_fMoveDis,float i_fJudgePosZ);
public:
	void Clear();
/**************************************************************************
 NoteObjects(
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
    NoteObjects(LPDIRECT3DDEVICE9 pD3DDevice,
		D3DXVECTOR3 i_vPos,D3DXVECTOR3 i_vSize,
		D3DCOLORVALUE i_Diffuse,D3DCOLORVALUE i_Specular,D3DCOLORVALUE i_Ambient,
		float HiSpeed,
		LPDIRECT3DTEXTURE9 pTexture = 0
		);
/**************************************************************************
 virtual ~NoteObjects();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~NoteObjects();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState   //コントローラのステータス
 );
 用途: 直方体を描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com);
/**************************************************************************
 void AddNote(BYTE i_SoundNum);
 用途: ノート追加
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
    void AddNote(BYTE i_SoundNum,BYTE i_StatusNum);

//////////
//	: セッター
/**************************************************************************
 void setLastStatus(BYTE i_StatusNum );
 用途: ノートの状態を設定
 戻り値: なし
***************************************************************************/
	void setLastStatus(BYTE i_StatusNum){
		m_ItemVec.back()->m_byStatus = i_StatusNum;
	}
/**************************************************************************
 void setFirstBoot();
 用途: 
 戻り値: なし
***************************************************************************/
	void setFirstBoot(){
		m_ItemVec[0]->m_bBoot = true;
	}
/**************************************************************************
	void setFirstDead();
 用途: 死亡フラグをビンビンにする
 戻り値: あし
***************************************************************************/
	void setFirstDead(){
		m_ItemVec[0]->m_bDead = true;
	}
/**************************************************************************
	void setFirstDead();
 用途: ベースの速さ
 戻り値: あし
***************************************************************************/
	static void setLineLength(float i_Speed){
		m_fNotationLength = i_Speed;
	}
/**************************************************************************
	void setHiSpeed();
 用途: ベースの速さ
 戻り値: あし
***************************************************************************/
	static void setHiSpeed(float i_Speed){
		m_fHighSpeed = i_Speed;
	}

//////////
//	: ゲッター
/**************************************************************************
 void getFirstBoot();
 用途: 
 戻り値: なし
***************************************************************************/
	const bool getFirstBootFlag(){
		return m_ItemVec[0]->m_bLastBoot;
	}
/**************************************************************************
 const D3DXVECTOR3& setFirstPos();
 用途: 一番最初のアイテムの座標を獲得
 戻り値: 座標
***************************************************************************/
	const D3DXVECTOR3& getFirstPos(){
		return m_ItemVec[0]->m_vPos;
	}
/**************************************************************************
 const D3DXVECTOR3& setFirstSize();
 用途:
 戻り値: 座標
***************************************************************************/
	const D3DXVECTOR3& setFirstSize(){
		return m_ItemVec[0]->m_vScale;
	}
/**************************************************************************
 BYTE getFirstStatus( );
 用途: ノートの状態を獲得
 戻り値: なし
***************************************************************************/
	const BYTE getFirstStatus(){
		return m_ItemVec[0]->m_byStatus;
	}
/**************************************************************************
 const OBB getFirstObb();
 用途: 一番最初のアイテムのOBBを返す
 戻り値: 先頭アイテムのOBB
***************************************************************************/
	const vector<NoteItem*>::size_type getSize(){
		return m_ItemVec.size();
	}
/**************************************************************************
 const BYTE getFirstSoundNum();
 用途: 一番最初のアイテムのサウンド番号を得る
 戻り値: 先頭アイテムのサウンド番号
***************************************************************************/
	const BYTE getFirstSoundNum(){
		if(m_ItemVec.empty())
			return 0;
		return m_ItemVec[0]->m_SoundNum;
	}
/**************************************************************************
 const bool getFirstDeadORLive();
 用途:   一番最初のアイテムの死亡フラグ確認
 戻り値: 死んでる = true / 生きてる = false
***************************************************************************/
	const bool getFirstDeadFlag(){
		return m_ItemVec[0]->m_bDead;
	}
};
}