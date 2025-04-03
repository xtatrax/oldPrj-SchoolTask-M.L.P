/**************************************************************************
 SpriteItem.h

 SpriteItem ; �錾
                                                    2012/03/04�@���O ���� �O
****************************************************************************/
#include "StdAfx.h"
#include "SpriteItem.h"


namespace wiz{
/**************************************************************************
 SpriteItem::SpriteItem(SpriteItem& pMeshItem);
 �p�r: �R�s�[�R���X�g���N�^
 �߂�l: �Ȃ�
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
		//�V�����C���X�^���X�̍쐬�i����ɑ��l�̃C���X�^���X�������Ȃ�����
	}
/**************************************************************************
 SpriteItem::SpriteItem(
 		wstring name,				//	: �I�u�W�F�̖��O
		D3DXVECTOR3& center,		//	: ���S�ƂȂ�ʒu (�I���W�i���[���̂���̃I�t�Z�b�g���W)
		D3DXVECTOR3& pos,			//	: �`��ʒu
		D3DXVECTOR3& size ,			//	: �傫���̔�
		D3DXVECTOR3& turn,			//	: �^�[��	(���])
		D3DXVECTOR3& rot			//	: ���P�[�g	(���])
		D3DCOLORVALUE& Diffuse,		//	: ���쒆�̃f�B�t���[�Y�F
		D3DCOLORVALUE& Specular,	//	: ���쒆�̃X�y�L�����F
		D3DCOLORVALUE& Ambient,		//	: ���쒆�̃A���r�G���g�F
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
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

		//	: �N�_����]�p�N�I�[�^�j�I���v�Z
        D3DXQuaternionRotationYawPitchRoll(&m_RotQt,
            D3DXToRadian(rot.x),D3DXToRadian(rot.y),D3DXToRadian(rot.z));
		//	: ���̉�]�p�N�I�[�^�j�I���v�Z
        //D3DXQuaternionRotationYawPitchRoll(&m_TurnQt,
        //    D3DXToRadian(turn.x),D3DXToRadian(turn.y),D3DXToRadian(turn.z));
        D3DXQuaternionRotationYawPitchRoll(&m_TurnQt,
            D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0));

	}
/**************************************************************************
SpriteItem::~SpriteItem();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	SpriteItem::~SpriteItem()
	{
		Delete();
	}
/**************************************************************************
SpriteItem::~SpriteItem();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	 void SpriteItem::Delete(){
		if(m_pRect)
		{
			delete m_pRect;
		}
	}

/**************************************************************************
D3DXMATRIX SpriteItem::getMatrix();
 �p�r: �}�g���b�N�X�Z�o
 �߂�l: �Z�o���ꂽ�}�g���b�N�X
***************************************************************************/
	D3DXMATRIX SpriteItem::getMatrix()
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
			//D3DXMATRIX mWCenter;
			//D3DXMatrixIdentity(&mWCenter);
			//D3DXMatrixTranslation(&mWCenter, -m_vCenter.x, -m_vCenter.y, -m_vCenter.z);
			D3DXMATRIX mWCenter;
			D3DXMatrixIdentity(&mWCenter);
			D3DXMatrixTranslation(&mWCenter, 0, 0, 0);

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
D3DXMATRIX SpriteItem::getMatrix(
		SpriteItem& i_other	//	: �e�ƂȂ���̂̃A�C�e��
	);
 �p�r: ��SpriteItem�e���}�g���b�N�X�̎Z�o
 �߂�l: �Z�o���ꂽ�}�g���b�N�X
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
 �p�r: �R�s�[
 �߂�l: this
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