/**************************************************************************
 MusicPlate.h

 class MusicPlate : public Plate �錾
                                                    2012/03/04�@���O
****************************************************************************/
#pragma once
#include "../Plate.h"
#include "../TATRAFactory/SHS.h"
namespace wiz{

/**************************************************************************
 class MusicPlate : public Plate;
 �p�r: �����̒����̃N���X�i�R���g���[���œ��삵�Ȃ��j
****************************************************************************/
class MusicPlate : public Plate{
protected:
	struct PlateItem{
		MeshItem	m_MeshItem;
		//���݂̃��x��
		Script::MLPHeader	m_Header;
		//�v���[�g�̌��݂̈ʒu
		INT		m_MyNumber;
		//�v���[�g�̈ړ��O�̈ʒu
		INT		m_OldNumber;
		//��]�����猩���p�x
		int		m_RotDig;
		LPDIRECT3DTEXTURE9 m_pTexture;

		//�h���N���X������Ă�Clear()�֐���
		//�폜�ł���悤�ɉ��z�f�X�g���N�^�ɂ��Ă���
		virtual ~PlateItem(){}
		PlateItem(D3DXVECTOR3& center,D3DXVECTOR3& pos,D3DXVECTOR3& size,
		D3DXVECTOR3& turn,D3DXVECTOR3& rot,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture)
			:m_MeshItem(center,pos,size,turn,rot,Diffuse,Specular,Ambient),
			 m_pTexture(pTexture)
		{}
	};
	//1�t���[���œ����p�x
	int		flg;
	//�\�����郌�x��
	char	m_SelectLevel;
	vector<PlateItem*> m_ItemVec;
/**************************************************************************
 void Clear();
 �p�r:Item�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
	void Clear();
/**************************************************************************
 virtual D3DXVECTOR3 getMove(vector<PlateItem*>::size_type index);
 �p�r: �v���[�g���ړ����Ă�ꍇ��X���Ă���ꍇ�ɁA�q�b�g�悪�ړ����ׂ��x�N�g��
 �߂�l: �x�N�g��
***************************************************************************/
 virtual D3DXVECTOR3 getMove(vector<PlateItem*>::size_type index);
public:
	enum{
			//���x���̊i�[�ꏊ
			SendLevel	= 3000 };
/**************************************************************************
 MusicPlate(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
    MusicPlate(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 virtual ~MusicPlate();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~MusicPlate();
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
/**************************************************************************
 void AddPlate(
    D3DXVECTOR3 size,               //�傫��
    D3DXVECTOR3 pos,                //�����ʒu
	D3DXVECTOR3 rot,				//��]�B
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
    void AddPlate(D3DXVECTOR3 size,D3DXVECTOR3 pos,D3DXVECTOR3 rot,
		int num,int ItemQt,Script::MLPHeader header,
		D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient,LPDIRECT3DTEXTURE9 pTexture);
/**************************************************************************
	virtual void DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
 �p�r: �e�{�����[����`��i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
	virtual void DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
		D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);


};
}