/**************************************************************************
 CommonMesh.h

 class CommonMesh : public Object �錾
 MyFactory; �錾
                                                    2012/03/04�@���O
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "TatraFactory/MeshItem.h"

namespace wiz{
/**************************************************************************
 class CommonMesh : public Object;
 �p�r: �R�������b�V���N���X
****************************************************************************/
class CommonMesh : public Object{
protected:
    //���b�V��
    LPD3DXMESH m_pMesh;
	//�e�̃��b�V��
    LPD3DXMESH m_pShadowMesh;
	//�e�{�����[���N���X
	ShadowVolume* m_pShadowVolume;
	//	: ���b�V���A�C�e�� �i �}�e���A���Ƃ�
	MeshItem  m_MeshItem;

/**************************************************************************
 CommonMesh(
    D3DXVECTOR3 pos,				//�ʒu
    D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,		//�X�y�L�����F
    D3DCOLORVALUE& Ambient			//�A���r�G���g�F
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
  CommonMesh(D3DXVECTOR3& center,D3DXVECTOR3& pos,D3DXVECTOR3& size ,
		D3DXVECTOR3& turn,D3DXVECTOR3& rot,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
/**************************************************************************
 virtual ~Plate();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~CommonMesh();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState	//�R���g���[���̃X�e�[�^�X
	Command& Com						//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: ���b�V����`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com);
public:
/**************************************************************************
 D3DXVECTOR3 getPos() const;
 �p�r: ���݂̃|�W�V�����𓾂�
 �߂�l: ���݂̃|�W�V����
***************************************************************************/
	D3DXVECTOR3 getPos() const{
		return m_MeshItem.m_vPos;
	}
};
}