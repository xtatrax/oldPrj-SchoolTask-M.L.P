/**************************************************************************
 Plate.cpp

 Plate; ��`
                                                    2012/03/04�@���O ���� �O
****************************************************************************/
#include "StdAfx.h"
#include "Plate.h"

namespace wiz{
/**************************************************************************
 Plate ��`��
***************************************************************************/
/**************************************************************************
 void Plate::VecNomal2UV(
	D3DXVECTOR3 vec,		//���_
	D3DXVECTOR3 normal,		//�@��
	float& u,				//�ϊ�����u�i�e�N�X�`�����U���W�j
	float& v				//�ϊ�����v�i�e�N�X�`�����V���W�j
	); 
 �p�r: Vector�Ɩ@������U��V�����o��
 �߂�l: �Ȃ�
 float& u��float& v�ɕϊ���̒l����
***************************************************************************/
void Plate::VecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v){
	if((normal.x < 0 && vec.y > 0 &&  vec.z > 0) 
		|| (normal.x > 0 && vec.y > 0 &&  vec.z < 0)
		|| (normal.z < 0 && vec.y > 0 &&  vec.x < 0)
		|| (normal.z > 0 && vec.y > 0 &&  vec.x > 0)
		|| (normal.y > 0 && vec.x < 0 &&  vec.z > 0)
		|| (normal.y < 0 && vec.x < 0 &&  vec.z < 0)){
			u = 0;
			v = 0;
	}
	else if((normal.x < 0 && vec.y < 0 &&  vec.z > 0) 
		|| (normal.x > 0 && vec.y < 0 &&  vec.z < 0)
		|| (normal.z < 0 && vec.y < 0 &&  vec.x < 0)
		|| (normal.z > 0 && vec.y < 0 &&  vec.x > 0)
		|| (normal.y > 0 && vec.x < 0 &&  vec.z < 0)
		|| (normal.y < 0 && vec.x < 0 &&  vec.z > 0)){
		u = 0;
		v = 1.0f;
	}
	else if((normal.x < 0 && vec.y > 0 &&  vec.z < 0) 
		|| (normal.x > 0 && vec.y > 0 &&  vec.z > 0)
		|| (normal.z < 0 && vec.y > 0 &&  vec.x > 0)
		|| (normal.z > 0 && vec.y > 0 &&  vec.x < 0)
		|| (normal.y > 0 && vec.x > 0 &&  vec.z > 0)
		|| (normal.y < 0 && vec.x > 0 &&  vec.z < 0)){
		u = 1.0f;
		v = 0.0f;
	}
	else{
		u = 1.0f;
		v = 1.0f;
	}
}

/**************************************************************************
 Plate::Plate(
    LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    D3DXVECTOR3 size,				//�傫��
    D3DXVECTOR3 pos,				//�ʒu
    D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,		//�X�y�L�����F
    D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
	LPDIRECT3DTEXTURE9 pTexture = 0	//	�e�N�X�`��
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
Plate::Plate(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3 pos,D3DXVECTOR3 size,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture)
    :CommonMesh(g_vZero,pos,size,g_vZero,g_vZero,Diffuse,Specular,Ambient),m_pTexture(pTexture)
{
    try{
		//���̍쐬
		if(FAILED(D3DXCreateBox(pD3DDevice, 
						size.x,
						size.y,
						size.z,
						&m_pMesh, 
						NULL))){
			// ���������s
			throw DxException(
				L"���̍쐬�Ɏ��s���܂����B",
				L"Plate::Plate()"
				);
		}
		//�e�N�X�`��������ꍇ
		if(m_pTexture){
			LPD3DXMESH m_pMesh2 = 0;
			//�쐬���ꂽ���b�V�������ɁA�e�N�X�`�����̃��b�V�����쐬
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,PlateFVF,pD3DDevice,&m_pMesh2))){
				// ���������s
				throw DxException(
					L"�e�N�X�`���t�̕��̍쐬�Ɏ��s���܂����B",
					L"Plate::Plate()"
					);
			}
			//�������Ƃ̃��b�V���͂���Ȃ��̂ō폜
	        SafeRelease(m_pMesh);
			m_pMesh = m_pMesh2;
			m_pMesh2 = 0;
			//�e�N�X�`����̍��W���}�b�s���O
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			PlateVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			DWORD vsize = m_pMesh->GetNumVertices();
			for(DWORD n = 0;n < vsize;n++){ //���_�̐����擾����
				//�@���ƒ��_����uv�l�𓾂�
				VecNomal2UV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
			}
			pVB->Unlock();
		}
		//�e�{�����[�����쐬
		m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
    }
    catch(...){
        //�R���X�g���N�^��O����
        //��n��
	    SafeDelete(m_pShadowVolume);
        SafeRelease(m_pMesh);
        SafeRelease(m_pShadowMesh);
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 Plate::~Plate();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Plate::~Plate(){
    //��n���i���b�V����Release��
	//CommonMesh�ōs�Ȃ��̂ŁA�{���͂��Ȃ��Ă��ǂ��B
	//���Ă����Ȃ�
    SafeDelete(m_pShadowVolume);
    SafeRelease(m_pMesh);
    SafeRelease(m_pShadowMesh);
	//SafeRelease(m_pTexture);
}

/**************************************************************************
 void Plate::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState	//�R���g���[���̃X�e�[�^�X
 );
 �p�r: �����̂�`��i�R���g���[�����������j
 �߂�l: �Ȃ��B
***************************************************************************/
void Plate::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){
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