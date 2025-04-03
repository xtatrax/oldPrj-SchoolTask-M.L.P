/**************************************************************************
 MainFactory.cpp

                                                    2012/04/06�@���O 
****************************************************************************/
#include "StdAfx.h"
#include "../Object.h"
#include "../Scene.h"
#include "KoromoebFactory.h"

namespace wiz{
namespace Koromoeb{

/**************************************************************************
Sprite ��`��
**************************************************************************/
/**************************************************************************
MoveLevel::MoveLevel(
LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
LPDIRECT3DTEXTURE9 pTexture	//�e�N�X�`��
);
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
MoveLevel::MoveLevel(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_filename,
		D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vOffsetPos,D3DXVECTOR3& i_vScale,
		D3DXVECTOR3& i_vCenter,D3DXVECTOR3& i_vRot,Rect* i_Rect)
:Sprite(pD3DDevice,i_filename,i_Rect,i_vPos,i_vOffsetPos,i_vScale,i_vCenter,i_vRot)
{
}

/**************************************************************************
 virtual void ButtonPlate::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �����̂�`��
 �߂�l: �Ȃ��B
***************************************************************************/
void MoveLevel::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
					 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	//if(m_pTexture){
	//	DWORD wkdword;
	//	pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
	//	pD3DDevice->SetTexture(0,m_pTexture);
	//	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
	//	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	//	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	//	pD3DDevice->SetFVF(PlateFVF);
	//	//�}�g���b�N�X�����_�����O�p�C�v���C���ɐݒ�
	//	pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
	//	//�{�^���v���[�g��Draw���Ă�
	//	ButtonPlate::Draw(pD3DDevice,Vec,pCntlState,Com);
	//	pD3DDevice->SetTexture(0,0);

	//	pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	//}
	//else{
	//	//�}�g���b�N�X�����_�����O�p�C�v���C���ɐݒ�
	//	pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
	//	//�{�^���v���[�g��Draw���Ă�
	//	ButtonPlate::Draw(pD3DDevice,Vec,pCntlState,Com);
	//}
}



/**************************************************************************
ButtonPlate ��`��
****************************************************************************/
/**************************************************************************
NameScrew::NameScrew(
    LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	DWORD Cmd,						//�I�����s���ꂽ�Ƃ��̃R�}���h
	DWORD Index,					//���j���[�X�e�[�W��̃C���f�b�N�X
    D3DXVECTOR3 size,               //�傫��
    D3DXVECTOR3 pos,                //�ʒu
    D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,        //�X�y�L�����F
    D3DCOLORVALUE& Ambient,         //�A���r�G���g�F
	LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
NameScrew::NameScrew(LPDIRECT3DDEVICE9 pD3DDevice,DWORD Cmd,DWORD Index,
	D3DXVECTOR3 pos,D3DXVECTOR3 size,
	D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	LPDIRECT3DTEXTURE9 pTexture)
:ButtonPlate(pD3DDevice,Cmd,Index,size,pos,Diffuse,Specular,Ambient,pTexture)
{
}

/**************************************************************************
 virtual void ButtonPlate::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �����̂�`��
 �߂�l: �Ȃ��B
***************************************************************************/
void NameScrew::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
					 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	if(m_pTexture){
		DWORD wkdword;
		pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		pD3DDevice->SetTexture(0,m_pTexture);
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		pD3DDevice->SetFVF(PlateFVF);
		//�}�g���b�N�X�����_�����O�p�C�v���C���ɐݒ�
		pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
		//�{�^���v���[�g��Draw���Ă�
		ButtonPlate::Draw(pD3DDevice,Vec,pCntlState,Com);
		pD3DDevice->SetTexture(0,0);

		pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
		//�}�g���b�N�X�����_�����O�p�C�v���C���ɐݒ�
		pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
		//�{�^���v���[�g��Draw���Ă�
		ButtonPlate::Draw(pD3DDevice,Vec,pCntlState,Com);
	}
}


/*************************************************************************
BackGrund ��`��
**************************************************************************/
/*************************************************************************
BackGrund::BackGrund(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
�p�r : �R���X�g���N�^
�߂�l : �Ȃ�
*************************************************************************/
BackGrund::BackGrund(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_filename,
			D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vOffsetPos,D3DXVECTOR3& i_vScale,
			D3DXVECTOR3& i_vCenter,D3DXVECTOR3& i_vRot,Rect* i_Rect)
:Sprite(pD3DDevice,i_filename,i_Rect,i_vPos,i_vOffsetPos,i_vScale,i_vCenter,i_vRot)
{
		try{
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 BackGrund::~BackGrund();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
BackGrund::~BackGrund(){
    //�Ȃɂ����Ȃ�
}




/**************************************************************************
 KoromoebFactoryMS ��`��
****************************************************************************/
/**************************************************************************
 KoromoebFactoryMS::KoromoebFactoryMS(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
KoromoebFactoryMS::KoromoebFactoryMS(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{

	//	D3DCOLORVALUE Diffuse	= {0.0f,1.0f,0.0f,1.0f};
	//	D3DCOLORVALUE Specular	= {0.0f,0.0f,0.0f,0.0f};
	//	D3DCOLORVALUE Ambient	= {0.5f,0.5f,0.5f,1.0f};

 //       //���N���X�̃}�e�B���A��
 //       D3DCOLORVALUE Plate1Diffuse		= {0.0f,1.0f,0.0f,1.0f};
 //       D3DCOLORVALUE Plate1Specular	= {0.0f,0.0f,0.0f,0.0f};
 //       D3DCOLORVALUE Plate1Ambient		= {0.5f,0.5f,0.5f,1.0f};

	//	//���N���X2�̃}�e�B���A��
	//	D3DCOLORVALUE Plate2Diffuse		= {0.0f,0.0f,1.0f,1.0f};
	//	D3DCOLORVALUE Plate2Specular	= {0.0f,0.0f,0.0f,0.0f};
	//	D3DCOLORVALUE Plate2Ambient		= {0.5f,0.5f,0.5f,1.0f};

	//	//���N���X3�̃}�e�B���A��
	//	D3DCOLORVALUE Plate3Diffuse		= {1.0f,0.0f,0.0f,1.0f};
	//	D3DCOLORVALUE Plate3Specular	= {0.0f,0.0f,0.0f,0.0f};
	//	D3DCOLORVALUE Plate3Ambient		= {0.5f,0.5f,0.5f,1.0f};

	//	//���j���[��}���`�v���[�g�̃}�e�B���A��
 //       D3DCOLORVALUE MPlateDiffuse2	= {1.0f,1.0f,1.0f,1.0f};
 //       D3DCOLORVALUE MPlateSpecular2	= {0.0f,0.0f,0.0f,0.0f};
 //       D3DCOLORVALUE MPlateAmbient2	= {0.5f,0.5f,0.5f,1.0f};

	//	//���j���[�}���`�v���[�g�̃}�e�B���A��
 //       D3DCOLORVALUE MPlateDiffuse3	= {1.0f,1.0f,1.0f,1.0f};
 //       D3DCOLORVALUE MPlateSpecular3	= {0.0f,0.0f,0.0f,0.0f};
 //       D3DCOLORVALUE MPlateAmbient3	= {0.5f,0.5f,0.5f,1.0f};



	//	//Texture* pFloorTx = new Texture(pD3DDevice,L"Media/Texture/floor_select.jpg");
	//	//Texture* pStartTx = new Texture(pD3DDevice,L"Media/Texture/game_start.jpg");
	//	//Texture* pExitTx = new Texture(pD3DDevice,L"Media/Texture/game_exit.jpg");

	//	////�e�N�X�`�����e�N�X�`���z��ɒǉ�
	//	//TexVec.push_back(pFloorTx);
	//	//TexVec.push_back(pStartTx);
	//	//TexVec.push_back(pExitTx);

 // //      //���N���X�̃C���X�^���X�\�z
	//	////����͒��ڒǉ�
 // //      vec.push_back(
 // //          new Plate(pD3DDevice,
 // //                  D3DXVECTOR3(10.0f,1.0f,0.0f),
 // //                  D3DXVECTOR3(0.0f,0.0f,0.0f),
	//	//			Plate1Diffuse,Plate1Specular,Plate1Ambient,
	//	//			pFloorTx->getTexture()));

	//	//�e�N�X�`��
	//	Texture* pEasyTx		= new Texture(pD3DDevice,L"Media/Texture/Easy.png");
	//	Texture* pNormalTx		= new Texture(pD3DDevice,L"Media/Texture/Normal.png");
	//	Texture* pMusicSelectTx = new Texture(pD3DDevice,L"Media/Texture/MusicSelect.png");
	//	Texture* pPleaseStartTx = new Texture(pD3DDevice,L"Media/Texture/PleaseStart.png");
	//	Texture* pHardTx		= new Texture(pD3DDevice,L"Media/Texture/Hard.png");
	//	Texture* pSongTx		= new Texture(pD3DDevice,L"Media/Texture/Song.png");


	//	//�e�N�X�`�����e�N�X�`���z��ɒǉ�
	//	TexVec.push_back(pMusicSelectTx);
	//	TexVec.push_back(pEasyTx);
	//	TexVec.push_back(pNormalTx);
	//	TexVec.push_back(pHardTx);
	//	TexVec.push_back(pSongTx);
	//	TexVec.push_back(pPleaseStartTx);

	//	//���N���X�̃C���X�^���X�\�z
	//	//�C�[�W�[�o�[
	//	vec.push_back(
	//		new Sprite(pD3DDevice,
	//			pEasyTx->getTexture(),
	//			D3DXVECTOR3(29.5f,0.5f,0.0f),		//Pos
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),		//OffsetPos
	//			D3DXVECTOR3(1.0f,1.2f,0.0f),		//Scale
	//			D3DXVECTOR3(0.0f,-120.0f,0.0f),		//Center
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),		//Rot
	//			NULL));								//Rect


	//	//���N���X2�̃C���X�^���X�\�z
	//	//�m�[�}���o�[
	//	vec.push_back(
	//		new Sprite(pD3DDevice,
	//			pNormalTx->getTexture(),
	//			D3DXVECTOR3(29.5f,0.5f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			D3DXVECTOR3(1.0f,1.2f,0.0f),
	//			D3DXVECTOR3(1.0f,-180.0f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			NULL));

	//	//���N���X3�̃C���X�^���X�\�z
	//	//�n�[�h�o�[
	//	vec.push_back(
	//		new Sprite(pD3DDevice,
	//			pHardTx->getTexture(),
	//			D3DXVECTOR3(29.5f,0.5f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			D3DXVECTOR3(1.0f,1.2f,0.0f),
	//			D3DXVECTOR3(1.0f,-240.0f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			NULL));

	//	//���j���[��̃}���`�v���[�g�̃C���X�^���X�\�z
	//	//�~���[�W�b�N�Z���N�g�o�[
	//	vec.push_back(
	//		new Sprite(pD3DDevice,
	//			pMusicSelectTx->getTexture(),
	//			D3DXVECTOR3(10.0f,0.5f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			D3DXVECTOR3(1.0f,0.5,0.0f),
	//			D3DXVECTOR3(1.0f,0.0f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			NULL));

	//	//���j���[��̃}���`�v���[�g�̃C���X�^���X�\�z
	//	//�v���[�Y�X�^�[�g�o�[
	//	vec.push_back(
	//		new Sprite(pD3DDevice,
	//			pPleaseStartTx->getTexture(),
	//			D3DXVECTOR3(5.0f,410.0f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			D3DXVECTOR3(0.7f,1.0f,0.0f),
	//			D3DXVECTOR3(1.5f,0.0f,0.0f),
	//			D3DXVECTOR3(0.0f,0.0f,0.0f),
	//			NULL));

	//	////���j���[��̃}���`�v���[�g�̃C���X�^���X�\�z
	//	////�^�񒆂̋Ȗ��o�[
	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(1.0f,0.0f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));


	//	////���������̋Ȗ��o�[
	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(1.5f,0.6f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));

	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(2.0f,1.2f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));

	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(2.5f,1.8f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));

	//	////�������牺�̋Ȗ��o�[
	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(1.5f,-0.6f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));

	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(2.0f,-1.2f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));

	//	//vec.push_back(
	//	//	new NameScrew(pD3DDevice,
	//	//		0,
	//	//		0,
	//	//		D3DXVECTOR3(2.5f,-1.8f,0.0f),
	//	//		D3DXVECTOR3(2.0f,0.5f,0.0f),
	//	//		Diffuse,Specular,Ambient,
	//	//		pSongTx->getTexture()));
	//	//		//�����܂ł��Ȗ��o�[

	//	
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 KoromoebFactoryMS::~KoromoebFactoryMS();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
KoromoebFactoryMS::~KoromoebFactoryMS(){
    //�Ȃɂ����Ȃ�
}



/**************************************************************************
 KoromoebFactoryGO ��`��
****************************************************************************/
/**************************************************************************
 KoromoebFactoryGO::KoromoebFactoryGO(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
KoromoebFactoryGO::KoromoebFactoryGO(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{

		vec.push_back(
			new Sprite(pD3DDevice,
				L"Media/Texture/Lose.png",
				NULL,							//Rect
				D3DXVECTOR3(0.0f,0.0f,0.0f),	//Cneter
				D3DXVECTOR3(0.0f,0.0f,0.0f),	//Pos
				D3DXVECTOR3(0.0f,0.0f,0.0f),	//OffsetPos
				D3DXVECTOR3(0.79f,0.95f,0.0f),	//Scale
				D3DXVECTOR3(0.0f,0.0f,0.0f)		//Rot
				));							


	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 KoromoebFactoryGO::~KoromoebFactoryGO();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
KoromoebFactoryGO::~KoromoebFactoryGO(){
    //�Ȃɂ����Ȃ�
}

}
}