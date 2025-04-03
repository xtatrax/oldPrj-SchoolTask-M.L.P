/**************************************************************************
 OjouFactoryP.h

													2012/06/18  �C�� ���� �O
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Sprite.h"
#include "../MultiPlate.h"

#define	NUMBERS_WIDTH	(27)	//	: �e�����̕�
#define	NUMBERS_HEIGHT	(40)	//	: �e�����̍���

#define GROOVE_WIDTH (29)		//  : �O���[���̈ꃁ�����̕�
#define GROOVE_HEIGHT (70)		//  : �O���[���̈ꃁ�����̍���



namespace wiz{
namespace Ojou{

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/***********************************************************************
class SupportMultiPlateDown	public MultiPlate
�p�r: �����̒����̃N���X
	  �R���g���[���[���������ƑΉ������v���[�g��������
************************************************************************/
class SupportMultiPlateDown : public MultiPlate{
protected:
	struct ButtonMoveItem : public MultiPlate::PlateItem{
		MeshItem m_MeshItem;
		int m_SupportButtonL;	//  : �\���L�[�̒l
		int m_SupportButtonR;	//  : �{�^���̒l
	virtual ~ButtonMoveItem(){}
		ButtonMoveItem(D3DXVECTOR3& center,D3DXVECTOR3& pos,D3DXVECTOR3& size ,
		D3DXVECTOR3& turn,D3DXVECTOR3& rot,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,int SupportButtonL,int SupportButtonR)
			:m_MeshItem(center,pos,size,turn,rot,Diffuse,Specular,Ambient),
			PlateItem(center,pos,size,turn,rot,Diffuse,Specular,Ambient),
		m_SupportButtonL(SupportButtonL),m_SupportButtonR(SupportButtonR){
		}
	D3DXVECTOR3 m_Move;			//  : ������l
	D3DXVECTOR3 m_BasePos;		//  : �����ʒu
};

/**************************************************************************
 void Clear();
 �p�r:Item�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 SupportMultiPlateDown(
    LPDIRECT3DDEVICE9 pD3DDevice   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	SupportMultiPlateDown(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 virtual ~SimpleMoveMultiPlate();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~SupportMultiPlateDown();
/**************************************************************************
 void AddPlate(
    D3DXVECTOR3 move,				//�ړ�
    D3DXVECTOR3 size,               //�傫��
    D3DXVECTOR3 pos,                //�ŏ��̈ʒu
	D3DXVECTOR3 rot,				//��](�p�x�P��)�B
    D3DCOLORVALUE Diffuse,          //�f�B�t���[�Y�F
    D3DCOLORVALUE Specular,         //�X�y�L�����F
    D3DCOLORVALUE Ambient           //�A���r�G���g�F
	int SupportButtonL				//�\���L�[�̒l
	int SupportButtonR				//�{�^���̒l
    );
 �p�r: �v���[�g��ǉ�
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
    void AddPlate(D3DXVECTOR3 move,D3DXVECTOR3 center,D3DXVECTOR3 pos,D3DXVECTOR3 size ,
		D3DXVECTOR3 turn,D3DXVECTOR3 rot,
		D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient,int SupportButtonL,int SupportButtonR);
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
 );
 �p�r: �����̂�`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com);
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/



/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class Groove;
 �p�r: �O���[���N���X
****************************************************************************/
class Groove : public Sprite{
	
	float	m_GaugePercent;
	BYTE	m_BadQt;
	int		m_iTextureWideFive;
	RECT	m_rectGrooveBorder;
	RECT	g_rectGroove;
public:
/*************************************************************************
 Groove(
	LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
  D3DXVECTOR3		m_vPos;			//	: �`�悷��ʒu(��ʍ����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vOffsetPos;	//	: �I�t�Z�b�g���W(�`��ʒu��0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vScale;		//	: �L�k�x����
	D3DXVECTOR3		m_vCenter;		//	: �摜�̒��S�Ƃ���ʒu(�摜�̍����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vRot;			//	: �`�������Ƃ̉�]�x����
	Rect*			m_Rect;			//	: �\������摜�͈̔�
	SpriteItem		m_MeshItem;		//	: ���W�f�[�^�Ƃ��}�e���A���Ƃ��B�iSpriteItem�ɕύX�\��j
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    Groove(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* Rect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vPos,D3DXVECTOR3& vOffsetPos,
			D3DXVECTOR3& vScale,D3DXVECTOR3& vRot);
/**************************************************************************
 virtual ~Groove();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~Groove();
/**************************************************************************
 void GrooveCalculation(float i_Score);
 �p�r: �Q�[�W�����̌v�Z
 �߂�l: �Ȃ�
***************************************************************************/
	void GrooveCalculation(float i_fDistanceRate,JUDGE i_Judge);
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);

	float getGaugePercent(){
		return m_GaugePercent;
	}


};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/




/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class Score;
 �p�r: �X�R�A�N���X
****************************************************************************/
class Score : public Sprite{
	
public:
		RECT	g_Rect[ 10 ];		//  : ������\���͈�
		int     g_iScore;			//  : �X�R�A�̃f�[�^
		int     num_places;			//  : �`�悷��X�R�A�̌���
		int     place;				//  : �X�R�A�̕`��Ώۂ̈�
		int		number;				//  : �X�R�A�̈ʂ�؂�o��
		D3DXVECTOR3   pos;			//  : �X�R�A��\��������W�����炷
/*************************************************************************
 Score(
	LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    D3DXVECTOR3		m_vPos;			//	: �`�悷��ʒu(��ʍ����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vOffsetPos;	//	: �I�t�Z�b�g���W(�`��ʒu��0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vScale;		//	: �L�k�x����
	D3DXVECTOR3		m_vCenter;		//	: �摜�̒��S�Ƃ���ʒu(�摜�̍����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vRot;			//	: �`�������Ƃ̉�]�x����
	Rect*			m_Rect;			//	: �\������摜�͈̔�
	SpriteItem		m_MeshItem;		//	: ���W�f�[�^�Ƃ��}�e���A���Ƃ��B�iSpriteItem�ɕύX�\��j
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    Score(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* Rect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vPos,D3DXVECTOR3& vOffsetPos,
			D3DXVECTOR3& vScale,D3DXVECTOR3& vRot);
/**************************************************************************
 virtual ~Score();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~Score();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/




/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class OjouFactoryP;
 �p�r: �ÓI�ȃX�R�A�ƃQ�[�W�̕`��N���X
****************************************************************************/
	class OjouFactoryP {

	public:
/**************************************************************************
 OjouFactoryP(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	OjouFactoryP(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~OjouFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~OjouFactoryP();
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

	
}
}