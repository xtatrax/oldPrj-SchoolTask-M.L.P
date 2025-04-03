/**************************************************************************
 MusicPlate.cpp

 MusicPlate; ��`
                                                    2012/03/04�@���O 
****************************************************************************/
#include "StdAfx.h"
#include "MusicPlate.h"
#include "math.h"
#include "SpLv.h"
#include "../Scene.h"
#include "../TATRAFactory/SHS.h"

namespace wiz{
/**************************************************************************
 MusicPlate ��`��
***************************************************************************/

/**************************************************************************
 void MusicPlate::Clear();
 �p�r:Item�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
void MusicPlate::Clear(){
	vector<PlateItem*>::iterator it;
    for(it = m_ItemVec.begin();it != m_ItemVec.end();it++){
        SafeDelete(*it);
    }
    m_ItemVec.clear();
	//*�e�N�X�`���̓����[�X���Ă͂����Ȃ�
}

/**************************************************************************
 virtual D3DXVECTOR3 MusicPlate::getMove(vector<PlateItem*>::size_type index);
 �p�r: �v���[�g���ړ����Ă�ꍇ��X���Ă���ꍇ�ɁA�q�b�g�悪�ړ����ׂ��x�N�g��
 �߂�l: �x�N�g��
***************************************************************************/
D3DXVECTOR3 MusicPlate::getMove(vector<PlateItem*>::size_type index){
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
 MusicPlate::MusicPlate(
    LPDIRECT3DDEVICE9	pD3DDevice,		//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DTEXTURE9	pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
MusicPlate::MusicPlate(LPDIRECT3DDEVICE9 pD3DDevice)
	:Plate(pD3DDevice,
		D3DXVECTOR3(0.0f,0.0f,0.0f),
		D3DXVECTOR3(1.0f,1.0f,1.0f),
		D3DCOLORVALUE(),
		D3DCOLORVALUE(),
		D3DCOLORVALUE(),
		(LPDIRECT3DTEXTURE9)1),
		m_SelectLevel(0)
	{
		m_pTexture = 0;
    try{
    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 virtual ~MusicPlate();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
MusicPlate::~MusicPlate(){
	Clear();
}

/**************************************************************************
 virtual void MusicPlate::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
 );
 �p�r: �����̂�`��
 �߂�l: �Ȃ��B
***************************************************************************/
void MusicPlate::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){
    //�y�Ȑ�
    long MusicQt = m_ItemVec.size();

	//////////////////////////////
	//	: Level�̑I��
	//�\���L�[ ��
	if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT){
		m_SelectLevel	+= 1;
		m_SelectLevel	%= 3;
	}
	//�\���L�[ ��
	if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT){
		m_SelectLevel	-= 1;
		if(m_SelectLevel	< 0)	m_SelectLevel	+= 3;
	}
    for(vector<PlateItem*>::size_type i = 0;i < MusicQt;i++){

		//�v���[�g�̈ړ����������Ă��邩
		if(m_ItemVec[i]->m_MyNumber == m_ItemVec[i]->m_OldNumber){
			//�\���L�[��
			if( pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP){
				//	: �����̔ԍ�����i�߁A���̐������y�Ȑ��𒴂����ꍇ�C������
				m_ItemVec[i]->m_MyNumber	+= 1;
				m_ItemVec[i]->m_MyNumber	%= MusicQt;

				flg	= 5;
			}
			//�\���L�[��
			else if( pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN){
				//	: �����̔ԍ�����߂��A���̐�����0����������ꍇ�C������
				m_ItemVec[i]->m_MyNumber	-= 1;
				if(m_ItemVec[i]->m_MyNumber < 0)	m_ItemVec[i]->m_MyNumber	+= MusicQt;
				
				flg	= -5;
			}
		}
		//�v���[�g�̐������ʒu�̐ݒ�
		float Degree = (360.0f / MusicQt) * (float)m_ItemVec[i]->m_MyNumber;
		//�ʒu�̕ϓ����L������
		if( Degree != 360 / MusicQt * (m_ItemVec[i]->m_OldNumber) ){
			m_ItemVec[i]->m_RotDig	+= flg;
			//�p�x��0�������������C������
			if(m_ItemVec[i]->m_RotDig < 0){
				m_ItemVec[i]->m_RotDig	+= 360;
			}
			//�p�x��360������������C������
			m_ItemVec[i]->m_RotDig	%= 360;
		}
		//�������ʒu�ɂ��邩
		if( Degree == m_ItemVec[i]->m_RotDig ){
			m_ItemVec[i]->m_OldNumber	= m_ItemVec[i]->m_MyNumber;
		}

		//�v���[�g�̌��݈ʒu
		m_ItemVec[i]->m_MeshItem.m_vPos	= D3DXVECTOR3(-cosf(D3DXToRadian(m_ItemVec[i]->m_RotDig)) * 2.0f,
													   sinf(D3DXToRadian(m_ItemVec[i]->m_RotDig)) * 2.0f,
													  -cosf(D3DXToRadian(m_ItemVec[i]->m_RotDig)) * 2.0f);

		//�v���[�g�����ʂɂ��邩
		if(m_ItemVec[i]->m_OldNumber == 0){
			//�`�{�^���ŋȂƃ��x��������A�v���C��ʂɈړ�����
			if(pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_A){
				Script::MLPHeader* pHd; 
				pHd = &m_ItemVec[i]->m_Header;
				Com.m_Command	= Scene::SC_OPEN_PLAY;
				Com.m_Param1	= m_SelectLevel;
				Com.m_Param2	= (DWORD)pHd;
				break;
			}else{
				//�\������郌�x���𑗂�
				Com.m_Command	= SendLevel;
				Com.m_Param1	= m_SelectLevel;
				Com.m_Param2	= m_ItemVec[i]->m_Header.Level[m_SelectLevel];
			}
		}

		//CommonMesh�N���X�̃}�e�B���A����ݒ�
		m_MeshItem = m_ItemVec[i]->m_MeshItem;
		//�e�N�X�`��������ꍇ
		if(m_ItemVec[i]->m_pTexture){
			DWORD wkdword;
			//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
			pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
			//�X�e�[�W�̐ݒ�
			pD3DDevice->SetTexture(0,m_ItemVec[i]->m_pTexture);
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
 void MusicPlate::AddPlate(
    D3DXVECTOR3 size,               //�傫��
    D3DXVECTOR3 pos,                //�����ʒu
	D3DXVECTOR3 rot,				//��]�Ax=x����]�p�x,y=y����]�p�x,z=z����]�p�x�B
	int			num,				//�ʒu�ԍ�
	int			ItemQt,				//�y�Ȑ�
	Script::MLPHeader	header,		//�Ȃ̃��x��
    D3DCOLORVALUE		Diffuse,	//�f�B�t���[�Y�F
    D3DCOLORVALUE		Specular,	//�X�y�L�����F
    D3DCOLORVALUE		Ambient		//�A���r�G���g�F
    );
 �p�r: �v���[�g��ǉ�
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
void MusicPlate::AddPlate(D3DXVECTOR3 size,D3DXVECTOR3 pos,D3DXVECTOR3 rot,
		int num,int ItemQt,Script::MLPHeader header,
		D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient,LPDIRECT3DTEXTURE9 pTexture){
	try{
		PlateItem* pItem = new PlateItem(D3DXVECTOR3(-3.0f,0.0f,-2.0f),pos,size,g_vZero,rot,Diffuse,Specular,Ambient,pTexture);

		//�����ʒu�̔ԍ�
		pItem->m_MyNumber	= num;
		pItem->m_OldNumber	= num;
		//�������x��
		pItem->m_Header		= header;
		//��]�����猩���p�x
		pItem->m_RotDig	= (360/ItemQt)*(pItem->m_MyNumber);

		m_ItemVec.push_back(pItem);

	}
	catch(...){
		Clear();
		throw;
	}
}

/**************************************************************************
	virtual void MusicPlate::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
 �p�r: �e�{�����[����`��i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void MusicPlate::DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
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