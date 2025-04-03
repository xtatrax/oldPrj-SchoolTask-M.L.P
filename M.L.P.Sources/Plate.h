/**************************************************************************
 Plate.h

 class Plate : public CommonMesh �錾
                                                    2012/03/04�@���O
****************************************************************************/
#pragma once
#include "CommonMesh.h"

namespace wiz{
/**************************************************************************
 class Plate : public CommonMesh;
 �p�r: ���N���X�i�R���g���[���[�œ��삵�Ȃ��j
****************************************************************************/
class Plate : public CommonMesh{

protected:
/**************************************************************************
 void VecNomal2UV(
	D3DXVECTOR3 vec,	//���_
	D3DXVECTOR3 normal,	//�@��
	float& u,			//�ϊ�����u�i�e�N�X�`�����U���W�j
	float& v			//�ϊ�����v�i�e�N�X�`�����V���W�j
	);
 �p�r: Vector�Ɩ@������U��V�����o��
 �߂�l: �Ȃ�
 float& u��float& v�ɕϊ���̒l����
***************************************************************************/
	void VecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v);
	LPDIRECT3DTEXTURE9 m_pTexture;
	//	�e�N�X�`��������ꍇ�̒��_�t�H�[�}�b�g�̒�`
	// D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	// ���\���̉����Ă���
	struct  PlateVertex{
		D3DXVECTOR3 vec;
		D3DXVECTOR3 normal;
		FLOAT       tu,tv;
	};
	//Plate�p��FVF��DIrectXAPI�ɓn���Ƃ��̃p�����[�^
	enum { PlateFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
public:
/**************************************************************************
 Plate(
    LPDIRECT3DDEVICE9 pD3DDevice,		////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    D3DXVECTOR3 size,					//�傫��
    D3DXVECTOR3 pos,					//�ʒu
    D3DCOLORVALUE& Diffuse,				//�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,			//�X�y�L�����F
    D3DCOLORVALUE& Ambient,				//�A���r�G���g�F
	LPDIRECT3DTEXTURE9 pTexture = 0		//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
    Plate(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3 pos,D3DXVECTOR3 size,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0);
/**************************************************************************
 virtual ~Plate();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~Plate();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState	//�R���g���[���̃X�e�[�^�X
 );
 �p�r: ����`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com);
};
}