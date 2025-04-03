/**************************************************************************
 ButtonPlate.h

 class ButtonPlate : public Object �錾
 MyFactory; �錾
                                                    2012/03/04�@���O
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Plate.h"
#include "TatraFactory/Button.h"
namespace wiz{


/**************************************************************************
 class ButtonPlate : public  Plate;
 �p�r: �{�^���N���X�i���j���[�X�e�[�W�ɔz�u����R���g���[���őI���ł���j
****************************************************************************/
class ButtonPlate :  public  Plate{
public:
	//	: �{�^���p�����[�^�[
	Button m_ButtonPrm; 
/**************************************************************************
 ButtonPlate(
    LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	DWORD Cmd,						//�I�����s���ꂽ�Ƃ��̃R�}���h
	DWORD Index,					//���j���[�X�e�[�W��̃C���f�b�N�X
    D3DXVECTOR3 size,				//�傫��
    D3DXVECTOR3 pos,				//�ʒu
    D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,		//�X�y�L�����F
    D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
	LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    ButtonPlate(LPDIRECT3DDEVICE9 pD3DDevice,DWORD Cmd,DWORD Index,
		D3DXVECTOR3 pos,D3DXVECTOR3 size,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0);
/**************************************************************************
 virtual ~ButtonPlate();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~ButtonPlate();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState	//�R���g���[���̃X�e�[�^�X
	Command& Com						//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �����̂�`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
/**************************************************************************
	virtual void DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,	//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,		//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,		//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
 �p�r: �e�{�����[����`��i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
	virtual void DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
		D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);
};

}
//end of namespace wiz.
