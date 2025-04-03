/**************************************************************************
 ButtonPlate.cpp

 ButtonPlate; ��`
                                                    2012/03/04�@���O ���� �O
****************************************************************************/
#include "StdAfx.h"
#include "ButtonPlate.h"
#include "TatraFactory/Button.h"

namespace wiz{



/**************************************************************************
 ButtonPlate ��`��
****************************************************************************/
/**************************************************************************
 ButtonPlate::ButtonPlate(
    LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	DWORD Cmd,						//�I�����s���ꂽ�Ƃ��̃R�}���h
	DWORD Index,					//���j���[�X�e�[�W��̃C���f�b�N�X
    D3DXVECTOR3 size,               //�傫��
    D3DXVECTOR3 pos,                //�ʒu
    D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,		//�X�y�L�����F
    D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
	LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
ButtonPlate::ButtonPlate(
	LPDIRECT3DDEVICE9 pD3DDevice,
	DWORD Cmd,
	DWORD Index,
	D3DXVECTOR3 pos,
	D3DXVECTOR3 size,
	D3DCOLORVALUE& Diffuse,
	D3DCOLORVALUE& Specular,
	D3DCOLORVALUE& Ambient,
	LPDIRECT3DTEXTURE9 pTexture)
:Plate(pD3DDevice,size,pos,Diffuse,Specular,Ambient,pTexture),
m_ButtonPrm(Cmd,Index)
{
}
/**************************************************************************
 virtual ~ButtonPlate::ButtonPlate();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ButtonPlate::~ButtonPlate(){

}

/**************************************************************************
 virtual void ButtonPlate::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState	//�R���g���[���̃X�e�[�^�X
	Command& Com						//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �����̂�`��
 �߂�l: �Ȃ��B
***************************************************************************/
void ButtonPlate::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	   vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){

	if(m_ButtonPrm.getSelect()){
		//�{�^���N���X�̃}�e�B���A��
        D3DCOLORVALUE Plate1Diffuse		= {1.0f,0.0f,0.0f,1.0f};
        D3DCOLORVALUE Plate1Specular	= {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE Plate1Ambient		= {1.0f,0.2f,0.2f,0.2f};
		m_MeshItem.setMaterial(Plate1Diffuse,Plate1Specular,Plate1Ambient);

	}else{
		//�{�^���N���X�̃}�e�B���A��
        D3DCOLORVALUE Plate1Diffuse		= {0.8f,0.8f,0.8f,1.0f};
        D3DCOLORVALUE Plate1Specular	= {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE Plate1Ambient		= {0.2f,0.2f,0.2f,0.2f};
		m_MeshItem.setMaterial(Plate1Diffuse,Plate1Specular,Plate1Ambient);
	
	}
		   
	// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
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
	if(m_ButtonPrm.getBoot()){
		//�R�}���h���s
		Com = m_ButtonPrm.CommandIssue();
	}
}

/**************************************************************************
	virtual void ButtonPlate::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,	//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,		//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,		//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
 �p�r: �e�{�����[����`��i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void ButtonPlate::DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
	D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj){
	if(m_pShadowVolume){

		//�I�u�W�F�N�g�̃��[���h�s����J���������ɂ��ēo�^
		D3DXMATRIX WorldView;
		WorldView =  m_MeshItem.getMatrix()  * mCameraView;
		pEffect->SetMatrix("g_mWorldView",&WorldView);
		//�J�����̃v���W�F�N�g�܂Ŋ܂񂾍s���o�^
		WorldView = WorldView * mCameraProj;
		pEffect->SetMatrix("g_mWorldViewProjection",&WorldView);
		//�e�{�����[���̕`��
		m_pShadowVolume->Draw(pD3DDevice,pEffect);
	}
}



}
//end of namespace wiz.
