/**************************************************************************
 JudgeLine.cpp

 JudgeLine; ��`
                                                    2012/03/04�@���O 
****************************************************************************/
#include "StdAfx.h"
#include "JudgeLine.h"
#include "../Stage_Play.h"
namespace wiz{
/**************************************************************************
 JudgeLine ��`��
***************************************************************************/


/**************************************************************************
 JudgeLine::JudgeLine(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
JudgeLine::JudgeLine(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3 pos,D3DXVECTOR3 size,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture)
	:Plate( pD3DDevice, pos, size, Diffuse, Specular, Ambient ,pTexture)
{
    try{
		
    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 virtual ~JudgeLine();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
JudgeLine::~JudgeLine(){
}

/**************************************************************************
 void JudgeLine::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
 );
 �p�r: �����̂�`��i�R���g���[�����������j
 �߂�l: �Ȃ��B
***************************************************************************/
void JudgeLine::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){

	static bool input = false;
    //�ړ��p(���I�ɂ͕ω����Ȃ�)
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
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(pD3DDevice,Vec,pCntlState,Com);
	}

}


}