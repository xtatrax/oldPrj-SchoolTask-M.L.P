/**************************************************************************
 MeshItem.h
 メッシュ表示に必要なデータ群をまとめるクラス
 class MeshItem ;
                                                    2012/03/04　名前 鴫原 徹
****************************************************************************/
#include "StdAfx.h"
#include "MeshItem.h"


namespace wiz{
/**************************************************************************
 MeshItem::MeshItem(
	MeshItem& pMeshItem		//	: 他のアイテム
	);
 用途: コピーコンストラクタ
 戻り値: なし
***************************************************************************/
	MeshItem::MeshItem(MeshItem& i_pOtherItem):m_MeshItemName(i_pOtherItem.m_MeshItemName),
				m_RotQt(i_pOtherItem.m_RotQt),
				m_TurnQt(i_pOtherItem.m_TurnQt),
				m_vCenter(i_pOtherItem.m_vCenter),
				m_vPos(i_pOtherItem.m_vPos),
				m_vSize(i_pOtherItem.m_vSize)
	{

		//m_pMaterial = new D3DMATERIAL9;
		// D3DMATERIAL9構造体を0でクリア
		::ZeroMemory( &m_pMaterial, sizeof(D3DMATERIAL9));
		m_pMaterial = i_pOtherItem.m_pMaterial;
		//新しいインスタンスの作成（勝手に他人のインスタンスを消さないため
	}
/**************************************************************************
 MeshItem::MeshItem(
 		//wstring name,				//	: オブジェの名前
		D3DXVECTOR3& center,		//	: 中心となる位置 (オリジナルゼロのからのオフセット座標)
		D3DXVECTOR3& pos,			//	: 描画位置
		D3DXVECTOR3& size ,			//	: 大きさの比
		D3DXVECTOR3& turn,			//	: ターン	(自転)
		D3DXVECTOR3& rot			//	: ロケート	(公転)
		D3DCOLORVALUE& Diffuse,		//	: 操作中のディフューズ色
		D3DCOLORVALUE& Specular,	//	: 操作中のスペキュラ色
		D3DCOLORVALUE& Ambient,		//	: 操作中のアンビエント色
);
 用途: コンストラクタ(色付き)
 戻り値: なし
***************************************************************************/
	MeshItem::MeshItem(//wstring name,
				D3DXVECTOR3& center,D3DXVECTOR3& pos,
				D3DXVECTOR3& size ,D3DXVECTOR3& turn,D3DXVECTOR3& rot,
				D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
				:m_MeshItemName(L""),m_vCenter(center),m_vPos(pos),m_vSize(size),
				m_pMaterial()
	{
		//	: 起点軸回転用クオータニオン計算
        D3DXQuaternionRotationYawPitchRoll(&m_RotQt,
            D3DXToRadian(rot.x),D3DXToRadian(rot.y),D3DXToRadian(rot.z));
		//	: 物体回転用クオータニオン計算
        D3DXQuaternionRotationYawPitchRoll(&m_TurnQt,
            D3DXToRadian(turn.x),D3DXToRadian(turn.y),D3DXToRadian(turn.z));

		//m_pMaterial = new D3DMATERIAL9;

		// D3DMATERIAL9構造体を0でクリア
		::ZeroMemory( &m_pMaterial, sizeof(D3DMATERIAL9));
		m_pMaterial.Diffuse = Diffuse;
		m_pMaterial.Specular = Specular;
		m_pMaterial.Ambient = Ambient;
	}
/**************************************************************************
 MeshItem::MeshItem(
 		//wstring name,				//	: オブジェの名前
		D3DXVECTOR3& center,		//	: 中心となる位置 (オリジナルゼロのからのオフセット座標)
		D3DXVECTOR3& pos,			//	: 描画位置
		D3DXVECTOR3& size ,			//	: 大きさの比
		D3DXVECTOR3& turn,			//	: ターン	(自転)
		D3DXVECTOR3& rot			//	: ロケート	(公転)
);
 用途: コンストラクタ(色無し)
 戻り値: なし
***************************************************************************/
	MeshItem::MeshItem(//wstring name,
				D3DXVECTOR3& center,
				D3DXVECTOR3& pos,
				D3DXVECTOR3& size ,
				D3DXVECTOR3& turn,
				D3DXVECTOR3& rot)
				:m_MeshItemName(L""),m_vCenter(center),m_vPos(pos),m_vSize(size),
				m_pMaterial()
	{
		//	: 起点軸回転用クオータニオン計算
        D3DXQuaternionRotationYawPitchRoll(&m_RotQt,
            D3DXToRadian(rot.x),D3DXToRadian(rot.y),D3DXToRadian(rot.z));
		//	: 物体回転用クオータニオン計算
        D3DXQuaternionRotationYawPitchRoll(&m_TurnQt,
            D3DXToRadian(turn.x),D3DXToRadian(turn.y),D3DXToRadian(turn.z));
	}
/**************************************************************************
MeshItem::~MeshItem();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	MeshItem::~MeshItem()
	{

		Delete();
	}
/**************************************************************************
void MeshItem::Delete();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	 void MeshItem::Delete(){
		//SafeDelete(m_pMaterial);
		//m_pMaterial = NULL;
	}

/**************************************************************************
D3DXMATRIX MeshItem::getMatrix();
 用途: マトリックス算出
 戻り値: 算出されたマトリックス
***************************************************************************/
	D3DXMATRIX MeshItem::getMatrix()
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
			D3DXMATRIX mWCenter;
			D3DXMatrixIdentity(&mWCenter);
			D3DXMatrixTranslation(&mWCenter, -m_vCenter.x, -m_vCenter.y, -m_vCenter.z);

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
D3DXMATRIX MeshItem::getMatrix(
		MeshItem& i_other	//	: 親となるもののアイテム
	);
 用途: 他MeshItem影響マトリックスの算出
 戻り値: 算出されたマトリックス
***************************************************************************/
	D3DXMATRIX MeshItem::getMatrix(MeshItem& i_other){

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
OBB MeshItem::getObb(
		float size	//	: 許容範囲(%)
	);
 用途: OBB算出
 戻り値: 算出されたOBB
***************************************************************************/
	OBB MeshItem::getObb(float size)
	{
			// 【Local】ターン回転(転)				算出【Matrix】
			D3DXMATRIX mTurn;
			D3DXMatrixIdentity(&mTurn);
			D3DXMatrixRotationQuaternion(&mTurn,&m_TurnQt);


			//// 【Local】ロケート回転(転回)			算出【Matrix】
			D3DXMATRIX mWRot;
			D3DXMatrixIdentity(&mWRot);
			//D3DXMatrixRotationQuaternion(&mWRot,&m_RotQt);

			// 
			D3DXMATRIX mLocalMatrix;
			D3DXMatrixIdentity(&mLocalMatrix);
			mLocalMatrix = mTurn;


		OBB obb;
		obb.m_Center = m_vPos - m_vCenter;	
		obb.m_Size   = m_vSize * size;	
		D3DXMATRIX	mMatrix = getMatrix();
		obb.m_Rot[0] = D3DXVECTOR3(mMatrix._11,mMatrix._12,mMatrix._13);
		obb.m_Rot[1] = D3DXVECTOR3(mMatrix._21,mMatrix._22,mMatrix._23);
		obb.m_Rot[2] = D3DXVECTOR3(mMatrix._31,mMatrix._32,mMatrix._33);
		return obb;
	}
/**************************************************************************
D3DMATERIAL9& MeshItem::getMaterial();
 用途: マテリアルを返す
 戻り値: このインスタンスのマテリアル
***************************************************************************/
	D3DMATERIAL9& MeshItem::getMaterial(){
		return m_pMaterial;
	}
/**************************************************************************
void MeshItem::setMaterial(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
 用途: Materialの設定
 戻り値: なし
***************************************************************************/
	void MeshItem::setMaterial(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
	{
		m_pMaterial.Diffuse = Diffuse;
		m_pMaterial.Specular = Specular;
		m_pMaterial.Ambient = Ambient;
	}
/**************************************************************************
MeshItem& MeshItem::operator =(MeshItem& i_OtherMeshItem);
 用途: コピー
 戻り値: 自己参照
***************************************************************************/
	MeshItem& MeshItem::operator =(MeshItem& i_OtherMeshItem)
	{
		//m_pMaterial = new D3DMATERIAL9;
		// D3DMATERIAL9構造体を0でクリア
		::ZeroMemory( &m_pMaterial, sizeof(D3DMATERIAL9));
		m_pMaterial = i_OtherMeshItem.m_pMaterial;
		m_RotQt		= i_OtherMeshItem.m_RotQt;
		m_TurnQt	= i_OtherMeshItem.m_TurnQt;
		m_vCenter	= i_OtherMeshItem.m_vCenter;
		m_vPos		= i_OtherMeshItem.m_vPos;
		m_vSize		= i_OtherMeshItem.m_vSize;
		return *this;
	}
}