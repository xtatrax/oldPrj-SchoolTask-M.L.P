/**************************************************************************
 Plate.cpp

 Plate; ��`
                                                    2012/03/04�@���O 
****************************************************************************/
#include "StdAfx.h"
#include "BGPlate.h"

namespace wiz{
/**************************************************************************
 BGPlate ��`��
***************************************************************************/

/**************************************************************************
 void BGPlate::Clear();
 �p�r:Item�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
void BGPlate::Clear(){
	vector<PlateItem*>::iterator it;
    for(it = m_ItemVec.begin();it != m_ItemVec.end();it++){
        SafeDelete(*it);
    }
    m_ItemVec.clear();
	//*�e�N�X�`���̓����[�X���Ă͂����Ȃ�
}

/**************************************************************************
 virtual D3DXVECTOR3 BGPlate::getMove(vector<PlateItem*>::size_type index);
 �p�r: �v���[�g���ړ����Ă�ꍇ��X���Ă���ꍇ�ɁA�q�b�g�悪�ړ����ׂ��x�N�g��
 �߂�l: �x�N�g��
***************************************************************************/
D3DXVECTOR3 BGPlate::getMove(vector<PlateItem*>::size_type index){
	D3DXVECTOR3 ret(0,0,0);
	if(m_ItemVec[index]->m_MeshItem.m_RotQt.x != 0 || m_ItemVec[index]->m_MeshItem.m_RotQt.y != 0
		|| m_ItemVec[index]->m_MeshItem.m_RotQt.z){
		ret.x = -0.1f * sin(m_ItemVec[index]->m_MeshItem.m_RotQt.z);
		ret.y = -0.05f;
		ret.z = -0.1f * sin(m_ItemVec[index]->m_MeshItem.m_RotQt.x);
	}
	return ret;
}


/**************************************************************************
 BGPlate::BGPlate(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
BGPlate::BGPlate(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture)
	:Plate(pD3DDevice,
		D3DXVECTOR3(0.0f,0.0f,0.0f),
		D3DXVECTOR3(1.0f,1.0f,1.0f),
		D3DCOLORVALUE(),
		D3DCOLORVALUE(),
		D3DCOLORVALUE(),pTexture){
    try{
    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 virtual ~BGPlate();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
BGPlate::~BGPlate(){
	Clear();
}

/**************************************************************************
 virtual void BGPlate::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
 );
 �p�r: �����̂�`��
 �߂�l: �Ȃ��B
***************************************************************************/
void BGPlate::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){
    //�z�u�I�u�W�F�N�g�̕`��
    vector<PlateItem*>::size_type sz = m_ItemVec.size();
    for(vector<PlateItem*>::size_type i = 0;i < sz;i++){
		//CommonMesh�N���X�̃}�e�B���A����ݒ�
		m_MeshItem = m_ItemVec[i]->m_MeshItem;

		//�v���[�g���ړ�������
		m_ItemVec[i]->m_MeshItem.m_vPos.x	-= 0.2f;
		if(m_ItemVec[i]->m_MeshItem.m_vPos.x < -10.0f)	m_ItemVec[i]->m_MeshItem.m_vPos.x	= 10.0f;

		//�e�N�X�`��������ꍇ
		if(m_pTexture){
			DWORD wkdword;
			//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
			pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
			//�X�e�[�W�̐ݒ�
			pD3DDevice->SetTexture(0,m_pTexture);
			//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
			pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
			pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

			pD3DDevice->SetFVF(PlateFVF);
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(pD3DDevice,Vec,pCntlState,Com);
			pD3DDevice->SetTexture(0,0);
			//�X�e�[�W�����ɖ߂�
			pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//�e�N�X�`�����Ȃ��ꍇ
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(pD3DDevice,Vec,pCntlState,Com);
		}
    }
}

/**************************************************************************
 void BGPlate::AddPlate(
    D3DXVECTOR3 size,               //�傫��
    D3DXVECTOR3 pos,                //�ŏ��̈ʒu
	D3DXVECTOR3 rot,				//��]�Ax=x����]�p�x,y=y����]�p�x,z=z����]�p�x�B
    D3DCOLORVALUE Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE Specular,            //�X�y�L�����F
    D3DCOLORVALUE Ambient          //�A���r�G���g�F
    );
 �p�r: �v���[�g��ǉ�
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
void BGPlate::AddPlate(D3DXVECTOR3 size,D3DXVECTOR3 pos,D3DXVECTOR3 rot,
	  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient){
	try{
		PlateItem* pItem = new PlateItem(g_vZero,pos,size,g_vZero,rot,Diffuse,Specular,Ambient);

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
	virtual void BGPlate::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
 �p�r: �e�{�����[����`��i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void BGPlate::DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
	  D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj){
	if(m_pShadowVolume){
		//�z�u�I�u�W�F�N�g�̕`��
		vector<PlateItem*>::size_type sz = m_ItemVec.size();
		for(vector<PlateItem*>::size_type i = 0;i < sz;i++){
			//�g��k���p
			D3DXMATRIX mScale;
			D3DXMatrixIdentity(&mScale);
			D3DXMatrixScaling(&mScale,m_ItemVec[i]->m_MeshItem.m_vSize.x,
				m_ItemVec[i]->m_MeshItem.m_vSize.y,m_ItemVec[i]->m_MeshItem.m_vSize.z);
			//��]�p
			D3DXMATRIX mRot;
			D3DXMatrixIdentity(&mRot);
			D3DXMatrixRotationQuaternion(&mRot,&m_ItemVec[i]->m_MeshItem.m_RotQt);
			//�g��k���Ɖ�]���~�b�N�X�s��
			//�ړ��p
			D3DXMATRIX mMove;
			D3DXMatrixIdentity(&mMove);
			//�e�̈ړ��́AY���ɑ΂��Ă̈ړ���0.01f�����Ⴂ�ʒu�ɂ���B
			//���ȉe���f�肱�ނ̂𐧌䂵�Ă���
			D3DXMatrixTranslation(&mMove,m_ItemVec[i]->m_MeshItem.m_vPos.x,
				m_ItemVec[i]->m_MeshItem.m_vPos.y -0.01f,m_ItemVec[i]->m_MeshItem.m_vPos.z);
			//���ׂă~�b�N�X�s��
			D3DXMATRIX mAllMatrix;
			D3DXMatrixIdentity(&mAllMatrix);
			mAllMatrix = mScale * mRot * mMove;
			//�I�u�W�F�N�g�̃��[���h�s����J���������ɂ��ēo�^
			D3DXMATRIX WorldView;
			WorldView =  mAllMatrix  * mCameraView;
			pEffect->SetMatrix("g_mWorldView",&WorldView);
			//�J�����̃v���W�F�N�g�܂Ŋ܂񂾍s���o�^
			WorldView = WorldView * mCameraProj;
			pEffect->SetMatrix("g_mWorldViewProjection",&WorldView);
			//�e�{�����[���̕`��
			m_pShadowVolume->Draw(pD3DDevice,pEffect);
		}
	}
}

}