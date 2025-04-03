/**************************************************************************
 MeshItem.h
 ���b�V���\���ɕK�v�ȃf�[�^�Q���܂Ƃ߂�N���X
 class MeshItem ;
                                                    2012/03/04�@���O ���� �O
****************************************************************************/
#include "StdAfx.h"
#include "MeshItem.h"


namespace wiz{
/**************************************************************************
 MeshItem::MeshItem(
	MeshItem& pMeshItem		//	: ���̃A�C�e��
	);
 �p�r: �R�s�[�R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	MeshItem::MeshItem(MeshItem& i_pOtherItem):m_MeshItemName(i_pOtherItem.m_MeshItemName),
				m_RotQt(i_pOtherItem.m_RotQt),
				m_TurnQt(i_pOtherItem.m_TurnQt),
				m_vCenter(i_pOtherItem.m_vCenter),
				m_vPos(i_pOtherItem.m_vPos),
				m_vSize(i_pOtherItem.m_vSize)
	{

		//m_pMaterial = new D3DMATERIAL9;
		// D3DMATERIAL9�\���̂�0�ŃN���A
		::ZeroMemory( &m_pMaterial, sizeof(D3DMATERIAL9));
		m_pMaterial = i_pOtherItem.m_pMaterial;
		//�V�����C���X�^���X�̍쐬�i����ɑ��l�̃C���X�^���X�������Ȃ�����
	}
/**************************************************************************
 MeshItem::MeshItem(
 		//wstring name,				//	: �I�u�W�F�̖��O
		D3DXVECTOR3& center,		//	: ���S�ƂȂ�ʒu (�I���W�i���[���̂���̃I�t�Z�b�g���W)
		D3DXVECTOR3& pos,			//	: �`��ʒu
		D3DXVECTOR3& size ,			//	: �傫���̔�
		D3DXVECTOR3& turn,			//	: �^�[��	(���])
		D3DXVECTOR3& rot			//	: ���P�[�g	(���])
		D3DCOLORVALUE& Diffuse,		//	: ���쒆�̃f�B�t���[�Y�F
		D3DCOLORVALUE& Specular,	//	: ���쒆�̃X�y�L�����F
		D3DCOLORVALUE& Ambient,		//	: ���쒆�̃A���r�G���g�F
);
 �p�r: �R���X�g���N�^(�F�t��)
 �߂�l: �Ȃ�
***************************************************************************/
	MeshItem::MeshItem(//wstring name,
				D3DXVECTOR3& center,D3DXVECTOR3& pos,
				D3DXVECTOR3& size ,D3DXVECTOR3& turn,D3DXVECTOR3& rot,
				D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
				:m_MeshItemName(L""),m_vCenter(center),m_vPos(pos),m_vSize(size),
				m_pMaterial()
	{
		//	: �N�_����]�p�N�I�[�^�j�I���v�Z
        D3DXQuaternionRotationYawPitchRoll(&m_RotQt,
            D3DXToRadian(rot.x),D3DXToRadian(rot.y),D3DXToRadian(rot.z));
		//	: ���̉�]�p�N�I�[�^�j�I���v�Z
        D3DXQuaternionRotationYawPitchRoll(&m_TurnQt,
            D3DXToRadian(turn.x),D3DXToRadian(turn.y),D3DXToRadian(turn.z));

		//m_pMaterial = new D3DMATERIAL9;

		// D3DMATERIAL9�\���̂�0�ŃN���A
		::ZeroMemory( &m_pMaterial, sizeof(D3DMATERIAL9));
		m_pMaterial.Diffuse = Diffuse;
		m_pMaterial.Specular = Specular;
		m_pMaterial.Ambient = Ambient;
	}
/**************************************************************************
 MeshItem::MeshItem(
 		//wstring name,				//	: �I�u�W�F�̖��O
		D3DXVECTOR3& center,		//	: ���S�ƂȂ�ʒu (�I���W�i���[���̂���̃I�t�Z�b�g���W)
		D3DXVECTOR3& pos,			//	: �`��ʒu
		D3DXVECTOR3& size ,			//	: �傫���̔�
		D3DXVECTOR3& turn,			//	: �^�[��	(���])
		D3DXVECTOR3& rot			//	: ���P�[�g	(���])
);
 �p�r: �R���X�g���N�^(�F����)
 �߂�l: �Ȃ�
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
		//	: �N�_����]�p�N�I�[�^�j�I���v�Z
        D3DXQuaternionRotationYawPitchRoll(&m_RotQt,
            D3DXToRadian(rot.x),D3DXToRadian(rot.y),D3DXToRadian(rot.z));
		//	: ���̉�]�p�N�I�[�^�j�I���v�Z
        D3DXQuaternionRotationYawPitchRoll(&m_TurnQt,
            D3DXToRadian(turn.x),D3DXToRadian(turn.y),D3DXToRadian(turn.z));
	}
/**************************************************************************
MeshItem::~MeshItem();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	MeshItem::~MeshItem()
	{

		Delete();
	}
/**************************************************************************
void MeshItem::Delete();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	 void MeshItem::Delete(){
		//SafeDelete(m_pMaterial);
		//m_pMaterial = NULL;
	}

/**************************************************************************
D3DXMATRIX MeshItem::getMatrix();
 �p�r: �}�g���b�N�X�Z�o
 �߂�l: �Z�o���ꂽ�}�g���b�N�X
***************************************************************************/
	D3DXMATRIX MeshItem::getMatrix()
	{
		//////////////////////
		//	Matrix
			// �yLocal�z�^�[����](�])				�Z�o�yMatrix�z

			D3DXMATRIX mTurn;
			D3DXMatrixIdentity(&mTurn);
			D3DXMatrixRotationQuaternion(&mTurn,&m_TurnQt);

			// �yLocal�z�L�k�ݒ�					�Z�o�yMatrix�z
			D3DXMATRIX mWScale;
			D3DXMatrixIdentity(&mWScale);
			D3DXMatrixScaling(&mWScale, m_vSize.x, m_vSize.y, m_vSize.z);

			// �yLocal�z���S�ݒ�					�Z�o�yMatrix�z
			D3DXMATRIX mWCenter;
			D3DXMatrixIdentity(&mWCenter);
			D3DXMatrixTranslation(&mWCenter, -m_vCenter.x, -m_vCenter.y, -m_vCenter.z);

			// �yLocal�z���P�[�g��](�]��)			�Z�o�yMatrix�z
			D3DXMATRIX mWRot;
			D3DXMatrixIdentity(&mWRot);
			D3DXMatrixRotationQuaternion(&mWRot,&m_RotQt);

			// �yLocal�z�ړ�						�Z�o�yMatrix�z
			D3DXMATRIX mWMove;
			D3DXMatrixIdentity(&mWMove);
			D3DXMatrixTranslation(&mWMove,m_vPos.x,m_vPos.y,m_vPos.z);
		//	Matrix
		//////////////////////

		//////////////////////
		//	Mix
			// �yLocal�z�]/�ό`						�����yMix�z
			D3DXMATRIX mTSWMixMatrix;
			D3DXMatrixIdentity(&mTSWMixMatrix);
			D3DXMatrixMultiply(&mTSWMixMatrix,&mTurn,&mWScale);

			// �yLocal�z�]/�ό`/���炷				�����yMix�z
			D3DXMATRIX mTSCWMixMatrix;
			D3DXMatrixIdentity(&mTSCWMixMatrix);
			D3DXMatrixMultiply(&mTSCWMixMatrix,&mTSWMixMatrix,&mWCenter);

			// �yLocal�z�]/�ό`/���炷/�]��			�����yMix�z
			D3DXMATRIX mTSCRWMixMatrix;
			D3DXMatrixIdentity(&mTSCRWMixMatrix);
			D3DXMatrixMultiply(&mTSCRWMixMatrix,&mTSCWMixMatrix,&mWRot);

			// �yLocal�z�]/�ό`/���炷/�]��/�ړ�	�����yMix�z
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
		MeshItem& i_other	//	: �e�ƂȂ���̂̃A�C�e��
	);
 �p�r: ��MeshItem�e���}�g���b�N�X�̎Z�o
 �߂�l: �Z�o���ꂽ�}�g���b�N�X
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
		float size	//	: ���e�͈�(%)
	);
 �p�r: OBB�Z�o
 �߂�l: �Z�o���ꂽOBB
***************************************************************************/
	OBB MeshItem::getObb(float size)
	{
			// �yLocal�z�^�[����](�])				�Z�o�yMatrix�z
			D3DXMATRIX mTurn;
			D3DXMatrixIdentity(&mTurn);
			D3DXMatrixRotationQuaternion(&mTurn,&m_TurnQt);


			//// �yLocal�z���P�[�g��](�]��)			�Z�o�yMatrix�z
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
 �p�r: �}�e���A����Ԃ�
 �߂�l: ���̃C���X�^���X�̃}�e���A��
***************************************************************************/
	D3DMATERIAL9& MeshItem::getMaterial(){
		return m_pMaterial;
	}
/**************************************************************************
void MeshItem::setMaterial(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
 �p�r: Material�̐ݒ�
 �߂�l: �Ȃ�
***************************************************************************/
	void MeshItem::setMaterial(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
	{
		m_pMaterial.Diffuse = Diffuse;
		m_pMaterial.Specular = Specular;
		m_pMaterial.Ambient = Ambient;
	}
/**************************************************************************
MeshItem& MeshItem::operator =(MeshItem& i_OtherMeshItem);
 �p�r: �R�s�[
 �߂�l: ���ȎQ��
***************************************************************************/
	MeshItem& MeshItem::operator =(MeshItem& i_OtherMeshItem)
	{
		//m_pMaterial = new D3DMATERIAL9;
		// D3DMATERIAL9�\���̂�0�ŃN���A
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