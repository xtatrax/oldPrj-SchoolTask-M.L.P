/**************************************************************************
 MultiPlate.h

 class MultiPlate : public Plate �錾
                                                    2012/03/04�@���O
****************************************************************************/
#pragma once
#include "Plate.h"

namespace wiz{
/**************************************************************************
 class MultiPlate : public Plate;
 �p�r: �����̒����̃N���X�i�R���g���[���œ��삵�Ȃ��j
****************************************************************************/
class MultiPlate : public Plate{
protected:
	struct PlateItem{
		MeshItem m_MeshItem;
		//�Փ˔���p��OBB
		OBB m_Obb;
		bool m_bDead;
		//�h���N���X������Ă�Clear()�֐���
		//�폜�ł���悤�ɉ��z�f�X�g���N�^�ɂ��Ă���
		virtual ~PlateItem(){}
		PlateItem(D3DXVECTOR3& center,D3DXVECTOR3& pos,D3DXVECTOR3& size ,
		D3DXVECTOR3& turn,D3DXVECTOR3& rot,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
			:m_MeshItem(center,pos,size,turn,rot,Diffuse,Specular,Ambient){
		}
	};
	vector<PlateItem*> m_ItemVec;
/**************************************************************************
 void Clear();
 �p�r:Item�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
	void Clear();
/**************************************************************************
 virtual D3DXVECTOR3 getMove(vector<PlateItem*>::size_type index);
 �p�r: �v���[�g���ړ����Ă�ꍇ��X���Ă���ꍇ�ɁA�q�b�g�悪�ړ����ׂ��x�N�g��
 �߂�l: �x�N�g��
***************************************************************************/
 virtual D3DXVECTOR3 getMove(vector<PlateItem*>::size_type index);
public:
/**************************************************************************
 MultiPlate(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pTexture = 0		//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
    MultiPlate(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0);
/**************************************************************************
 virtual ~MultiPlate();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~MultiPlate();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState	//�R���g���[���̃X�e�[�^�X
 );
 �p�r: �����̂�`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com);
/**************************************************************************
 void AddPlate(
    D3DXVECTOR3 size,               //�傫��
    D3DXVECTOR3 pos,                //�ŏ��̈ʒu
	D3DXVECTOR3 rot,				//��]�B
    D3DCOLORVALUE Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE Specular,            //�X�y�L�����F
    D3DCOLORVALUE Ambient          //�A���r�G���g�F
    );
 �p�r: �v���[�g��ǉ�
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
    void AddPlate(D3DXVECTOR3 size,D3DXVECTOR3 pos,D3DXVECTOR3 rot,
     D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient);
/**************************************************************************
	bool HitTestSphere(
	Sphere sp,			//���Ƃ̏Փ˔���
	D3DXVECTOR3& vec,	//�Փ˂����ʒu�̎Q��
	OBB& obb,			//�Փ˂���OBB
	D3DXVECTOR3& move	//�q�b�g�����Ƃ��Ɉړ����ׂ��x�N�g��
	);
 �p�r: ���Ƃ̏Փ˔���
 �߂�l: �Փ˂��Ă����true�j
***************************************************************************/
	bool HitTestSphere(Sphere sp,D3DXVECTOR3& vec,OBB& obb,D3DXVECTOR3& move);

/**************************************************************************
	bool HitTestOBB(
	const OBB& obb1,		//�Փ˔��肷�鑊���OBB
	OBB& ret_obb			//�Փ˂���OBB
	);
 �p�r: OBB�Ƃ̏Փ˔���
 �߂�l: �Փ˂��Ă����true�j
***************************************************************************/
	bool HitTestOBB(const OBB& obb1,OBB& ret_obb);
/**************************************************************************
	virtual void IsHitTransition(
	D3DXVECTOR3 vec,	//�Փ˂������̒��_
	vector<PlateItem*>::size_type index  //�v���[�g�̃C���f�b�N�X
	);
 �p�r: �Փ˂������̕ω��i���z�֐��j
�@�@�@�@�Փ˂����Ƃ��ω�������ꍇ�͐V���ȃN���X������āA���̊֐��𑽏d��`����
 �߂�l: �Ȃ�
***************************************************************************/
	virtual void IsHitTransition(D3DXVECTOR3 vec,vector<PlateItem*>::size_type index);
/**************************************************************************
	virtual void DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj				//�J�����̃v���W�F�N�V�����s��
	);
 �p�r: �e�{�����[����`��i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
	virtual void DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
		D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);

	vector<PlateItem*>::size_type getSize(){
		return m_ItemVec.size();
	}
};
}