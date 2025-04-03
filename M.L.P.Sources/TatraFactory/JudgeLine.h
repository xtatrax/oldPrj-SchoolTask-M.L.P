/**************************************************************************
 JudgeLine.h

 class JudgeLine : public Plate �錾
                                                    2012/03/04�@���O ���� �O
****************************************************************************/
#pragma once
#include "../MultiPlate.h"
#include "../Sound.h"

namespace wiz{
/**************************************************************************
 class JudgeLine : public Plate;
 �p�r: ���胉�C���N���X
****************************************************************************/
class JudgeLine : public Plate{
protected:
public:
/**************************************************************************
 JudgeLine(
    LPDIRECT3DDEVICE9 pD3DDevice,	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	D3DXVECTOR3 pos,				//	: ���W
	D3DXVECTOR3 size,				//	: �L�k��
	D3DCOLORVALUE& Diffuse,			//	: �g�U���ˌ�
	D3DCOLORVALUE& Specular,		//	: ���ʔ��ˌ�
	D3DCOLORVALUE& Ambient,			//	: ����
	LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
JudgeLine(
		LPDIRECT3DDEVICE9 pD3DDevice,
		D3DXVECTOR3 pos,
		D3DXVECTOR3 size,
        D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Specular,
		D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0);
/**************************************************************************
 virtual ~JudgeLine();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~JudgeLine();
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
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com);
/**************************************************************************
 OBB getObb();
 �p�r: OBB�Z�o
 �߂�l: ���̃C���X�^���X��OBB
***************************************************************************/
	OBB getObb(float i_fSize = 0.5f){
		return m_MeshItem.getObb(i_fSize);
	}
};
}