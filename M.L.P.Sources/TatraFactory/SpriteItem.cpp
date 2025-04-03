/**************************************************************************
 SpriteItem.h

 SpriteItem ; 宣言
                                                    2012/03/04　名前 鴫原 徹
****************************************************************************/
#include "StdAfx.h"
#include "SpriteItem.h"


namespace wiz{
/**************************************************************************
 SpriteItem::SpriteItem(SpriteItem& pMeshItem);
 用途: コピーコンストラクタ
 戻り値: なし
***************************************************************************/
	SpriteItem::SpriteItem(SpriteItem& pMeshItem)
				:m_SpriteItemName(pMeshItem.m_SpriteItemName),
				 m_RotQt(pMeshItem.m_RotQt),
				 m_TurnQt(pMeshItem.m_TurnQt),
				 m_vCenter(pMeshItem.m_vCenter),
				 m_vPos(pMeshItem.m_vPos),
				 m_vSize(pMeshItem.m_vSize),
				 m_Textuer(pMeshItem.m_Textuer)
	{
		//新しいインスタンスの作成（勝手に他人のインスタンスを消さないため
	}
/**************************************************************************
 SpriteItem::SpriteItem(
 		wstring name,				//	: オブジェの名前
		D3DXVECTOR3& center,		//	: 中心となる位置 (オリジナルゼロのからのオフセット座標)
		D3DXVECTOR3& pos,			//	: 描画位置
		D3DXVECTOR3& size ,			//	: 大きさの比
		D3DXVECTOR3& turn,			//	: ターン	(自転)
		D3DXVECTOR3& rot			//	: ロケート	(公転)
		D3DCOLORVALUE& Diffuse,		//	: 操作中のディフューズ色
		D3DCOLORVALUE& Specular,	//	: 操作中のスペキュラ色
		D3DCOLORVALUE& Ambient,		//	: 操作中のアンビエント色
);
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	SpriteItem::SpriteItem(//wstring name,
				LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* rect,
				D3DXVECTOR3& center,D3DXVECTOR3& pos,D3DXVECTOR3& vOffsetPos,
				D3DXVECTOR3& size ,D3DXVECTOR3& rot,D3DCOLOR color)
				:m_SpriteItemName(fileName.c_str()),
				 m_Textuer(pD3DDevice,fileName.c_str()),m_pRect(rect),
				 m_vCenter(center),m_vPos(pos),m_vSize(size),
				 m_vOffsetPos(vOffsetPos),m_Color(color)
	{
		if(rect){
			m_pRect = new Rect;
			*m_pRect = *rect;
		}

		//	: 起点軸回転用クオータニオン計算
        D3DXQuaternionRotationYawPitchRoll(&m_RotQt,
            D3DXToRadian(rot.x),D3DXToRadian(rot.y),D3DXToRadian(rot.z));
		//	: 物体回転用クオータニオン計算
        //D3DXQuaternionRotationYawPitchRoll(&m_TurnQt,
        //    D3DXToRadian(turn.x),D3DXToRadian(turn.y),D3DXToRadian(turn.z));
        D3DXQuaternionRotationYawPitchRoll(&m_TurnQt,
            D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0));

	}
/**************************************************************************
SpriteItem::~SpriteItem();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	SpriteItem::~SpriteItem()
	{
		Delete();
	}
/**************************************************************************
SpriteItem::~SpriteItem();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	 void SpriteItem::Delete(){
		if(m_pRect)
		{
			delete m_pRect;
		}
	}

/**************************************************************************
D3DXMATRIX SpriteItem::getMatrix();
 用途: マトリックス算出
 戻り値: 算出されたマトリックス
***************************************************************************/
	D3DXMATRIX SpriteItem::getMatrix()
	{
		//////////////////////
		//	Matrix
			// 【Local】ターン回転(転)				算出【Matrix】

			D3DXMATRIX mTurn;
			D3DXMatrixIdentity(&mTurn);
			D3DXMatrixRotationQuaternion(&mTurn,&m_TurnQt);

			// 【Local】伸縮設定					算出【Matrix】
			D3DXMATRIX mWScale;
			D3DXMatrixIdentity(&mWScale);
			D3DXMatrixScaling(&mWScale, m_vSize.x, m_vSize.y, m_vSize.z);

			// 【Local】中心設定					算出【Matrix】
			//D3DXMATRIX mWCenter;
			//D3DXMatrixIdentity(&mWCenter);
			//D3DXMatrixTranslation(&mWCenter, -m_vCenter.x, -m_vCenter.y, -m_vCenter.z);
			D3DXMATRIX mWCenter;
			D3DXMatrixIdentity(&mWCenter);
			D3DXMatrixTranslation(&mWCenter, 0, 0, 0);

			// 【Local】ロケート回転(転回)			算出【Matrix】
			D3DXMATRIX mWRot;
			D3DXMatrixIdentity(&mWRot);
			D3DXMatrixRotationQuaternion(&mWRot,&m_RotQt);

			// 【Local】移動						算出【Matrix】
			D3DXMATRIX mWMove;
			D3DXMatrixIdentity(&mWMove);
			D3DXMatrixTranslation(&mWMove,m_vPos.x,m_vPos.y,m_vPos.z);
		//	Matrix
		//////////////////////

		//////////////////////
		//	Mix
			// 【Local】転/変形						合成【Mix】
			D3DXMATRIX mTSWMixMatrix;
			D3DXMatrixIdentity(&mTSWMixMatrix);
			D3DXMatrixMultiply(&mTSWMixMatrix,&mTurn,&mWScale);

			// 【Local】転/変形/ずらす				合成【Mix】
			D3DXMATRIX mTSCWMixMatrix;
			D3DXMatrixIdentity(&mTSCWMixMatrix);
			D3DXMatrixMultiply(&mTSCWMixMatrix,&mTSWMixMatrix,&mWCenter);

			// 【Local】転/変形/ずらす/転回			合成【Mix】
			D3DXMATRIX mTSCRWMixMatrix;
			D3DXMatrixIdentity(&mTSCRWMixMatrix);
			D3DXMatrixMultiply(&mTSCRWMixMatrix,&mTSCWMixMatrix,&mWRot);

			// 【Local】転/変形/ずらす/転回/移動	合成【Mix】
			D3DXMATRIX mAllMatrix;
			D3DXMatrixIdentity(&mAllMatrix);
			D3DXMatrixMultiply(&mAllMatrix,&mTSCRWMixMatrix,&mWMove);
		//	Mix
		//////////////////////
		//BtestDrawOBB::add(this->getObb());
		return mAllMatrix;
	}	
/**************************************************************************
D3DXMATRIX SpriteItem::getMatrix(
		SpriteItem& i_other	//	: 親となるもののアイテム
	);
 用途: 他SpriteItem影響マトリックスの算出
 戻り値: 算出されたマトリックス
***************************************************************************/
	D3DXMATRIX SpriteItem::getMatrix(SpriteItem& i_other){

		//////////////////////
		//	Local
			D3DXMATRIX mLocalMatrix;
			D3DXMatrixIdentity(&mLocalMatrix);
			mLocalMatrix = getMatrix();
		//	Local
		//////////////////////

		//////////////////////
		//	World
			D3DXMATRIX mWorldMatrix;
			D3DXMatrixIdentity(&mWorldMatrix);
			mWorldMatrix = i_other.getMatrix();
		//	World
		//////////////////////

		//////////////////////
		//	AllMix
			D3DXMATRIX mAllMatrix;
			D3DXMatrixIdentity(&mAllMatrix);
			mAllMatrix = mLocalMatrix * mWorldMatrix;
		//	AllMix
		//////////////////////
		return mAllMatrix;
	}	
/**************************************************************************
SpriteItem& SpriteItem::operator =(SpriteItem& i_OtherMeshItem);
 用途: コピー
 戻り値: this
***************************************************************************/
	SpriteItem& SpriteItem::operator =(SpriteItem& i_OtherMeshItem)
	{
		m_SpriteItemName = i_OtherMeshItem.m_SpriteItemName;
		m_Textuer	= i_OtherMeshItem.m_Textuer;
		m_pRect		= i_OtherMeshItem.m_pRect;
		m_RotQt		= i_OtherMeshItem.m_RotQt;
		m_TurnQt	= i_OtherMeshItem.m_TurnQt;
		m_vCenter	= i_OtherMeshItem.m_vCenter;
		m_vPos		= i_OtherMeshItem.m_vPos;
		m_vSize		= i_OtherMeshItem.m_vSize;

		return *this;
	}
}