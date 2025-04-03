/**************************************************************************
 MainFactory.h

 class Shadow: public Object; �錾

                                                    2012/04/17�@�����̖��O
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Object.h"
namespace wiz{

/**************************************************************************
 class Shadow: public Object;
 �p�r: �e�N���X
****************************************************************************/
class Shadow: public Object{
	struct BigSquareVertex{
		D3DXVECTOR4 p;
		D3DCOLOR    color;
	};
	LPDIRECT3DVERTEXBUFFER9 m_pBigVB;
	//BigSquareFVF�p��FVF��DIrectXAPI�ɓn���Ƃ��̃p�����[�^
	enum { BigSquareFVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
	// �V�F�[�_
	LPD3DXEFFECT	m_pEffect;     // �V�F�[�_�������ꂽ�G�t�F�N�g
	// �e�N�j�b�N�n���h��
	D3DXHANDLE	m_hRenderShadow;   //�V���h�E�������_�����O����G�t�F�N�g// Technique handle for rendering shadow
	D3DXHANDLE	m_hShowShadow;     //�V���h�E��\������Technique handle for showing shadow volume
	D3DXHANDLE	m_hRenderShadowVolumeComplexity; //�V���h�E�{�����[����\������
/**************************************************************************
 void Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 Shadow(
 LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Shadow(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 ~Shadow();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Shadow();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �e��`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};


}
//end of namespace wiz.

