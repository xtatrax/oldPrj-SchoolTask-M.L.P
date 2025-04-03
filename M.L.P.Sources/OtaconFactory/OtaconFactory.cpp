/**************************************************************************
 MainFactory.cpp

                                                    2012/04/06�@���O 
													2012/06/17  �啝�C�� ���� �O
****************************************************************************/
#include "StdAfx.h"
#include "../Object.h"
#include "../Scene.h"
#include "OtaconFactory.h"
#include "../Sprite.h"

namespace wiz{
namespace Otacon{

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 OtaconFactory ��`��
****************************************************************************/
/**************************************************************************
 OtaconFactory::OtaconFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
OtaconFactory::OtaconFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec)
{
	try{

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 OtaconFactory::~OtaconFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
OtaconFactory::~OtaconFactory()
		{
			//�Ȃɂ����Ȃ�
		}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/





/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 ResultFactory ��`��
****************************************************************************/
/**************************************************************************
 ResultFactory::ResultFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
ResultFactory::ResultFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec,int Score,ResultFactor& Factor)
{
	try{
		//�摜�̐F��ȃf�[�^
		//�w�i
		vec.push_back(new Sprite(pD3DDevice, L"Media/Texture/result-back.png",
					  &Rect(0,0,800,480),         //�؂�o��
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//���S�i�j
					  D3DXVECTOR3(0.0f,0.0f,1.0f),//�|�W�V�����i�䂪�݂ˁ`�j
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//�I�t�Z�b�g
					  D3DXVECTOR3(1.0f,1.0f,0.0f),//�傫���i�i�E���j
					  D3DXVECTOR3(0.0f,0.0f,0.0f))//�p�x
					  
					  );
		////�Ȗ��o�[
		//vec.push_back(new Sprite(pD3DDevice,L"Media/Texture/result-music_nameB.png",
		//			  &Rect(0,0,396,78),                       //�؂�o��
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),//���S�i�j
		//			  D3DXVECTOR3(20.0f,105.0f,0.9f),//�|�W�V�����i�䂪�݂ˁ`�j
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),//�I�t�Z�b�g
		//			  D3DXVECTOR3(1.0f,1.0f,0.0f),//�傫���i�i�E���j
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f))//�p�x
		//			  
		//			  );

		//�Ȗ�
		vec.push_back(new Sprite(pD3DDevice,Factor.m_BannerPath,
					  NULL,                       //�؂�o��
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//���S�i�j
					  D3DXVECTOR3(30.0f,110.0f,0.8f),//�|�W�V�����i�䂪�݂ˁ`�j
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//�I�t�Z�b�g
					  D3DXVECTOR3(1.0f,1.0f,0.0f),//�傫���i�i�E���j
					  D3DXVECTOR3(0.0f,0.0f,0.0f))//�p�x
					  
					  );




		//�X�R�A�o�[
		vec.push_back(new Sprite(pD3DDevice,L"Media/Texture/result-scoreB.png",
					  &Rect(0,0,400,50),       //�؂�o��
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//���S�i�j
					  D3DXVECTOR3(380.0f,420.0f,0.9f),//�|�W�V�����i�䂪�݂ˁ`�j
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//�I�t�Z�b�g
					  D3DXVECTOR3(1.0f,1.0f,0.0f),//�傫���i�i�E���j
					  D3DXVECTOR3(0.0f,0.0f,0.0f))//�p�x
					  
					  );

		//�����N�o�[
		vec.push_back(new Sprite(pD3DDevice,L"Media/Texture/result-rankB.png",
					  &Rect(0,0,295,277),                       //�؂�o��
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//���S�i�j
					  D3DXVECTOR3(20.0f,193.0f,0.9f),//�|�W�V�����i�䂪�݂ˁ`�j
					  D3DXVECTOR3(0.0f,0.0f,0.0f),//�I�t�Z�b�g
					  D3DXVECTOR3(1.0f,1.0f,0.0f),//�傫���i�i�E���j
					  D3DXVECTOR3(0.0f,0.0f,0.0f))//�p�x
					  
					  );



		//�����N�t�H���g
		vec.push_back(new RankSprite(
				pD3DDevice,
				L"Media/Texture/result-rankF.png",
				&Rect(0,0,200,200),					//	: �e�N�X�`���̕`��͈�
				D3DXVECTOR3(80.0f,240.0f,0.8f),		//	: �`����W
				g_vOne,								//	: �L�k��
				Factor,								//	: �����N���v�Z���邽�߂�
				Score								//	: �X�R�A
				)
		);

		//�X�R�A�t�H���g
		vec.push_back(new ScoreSprite(
				pD3DDevice,
				L"Media/Texture/result-scoreF.png",
				&Rect(0,0,27,40),					//	: �e�N�X�`���̕`��͈�
				D3DXVECTOR3(750.0f,425.0f,0.8f),	//	: �`����W
				g_vOne,								//	: �L�k��
				Score								//	: �`�悷��X�R�A
				)
		);

		DWORD com ;
		if(Factor.m_fGaugePar >= 70.0f){
			//�N���A
			vec.push_back(new Sprite(
				pD3DDevice,
				L"Media/Texture/result_Clear.png",
				NULL,
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXVECTOR3(340.0f,240.0f,0.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f))
				);

			com = Scene::SC_OPEN_MUSICSELECT;
		}else{
			//�Q�[���I�[�o�[
			vec.push_back(new Sprite(
				pD3DDevice,
				L"Media/Texture/result_Not Clear.png",
				NULL,
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXVECTOR3(330.0f,190.0f,0.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f))
				);

			com = Scene::SC_OPEN_GAMEOVER;
		}
		//�z���C�g�A�E�g
		vec.push_back(new WhiteOutSprite(pD3DDevice, L"Media/Texture/result-WhiteOut.png",com));

	}
	catch(...){
		//��throw
		throw;
	}
}
/**************************************************************************
 ResultFactory::~ResultFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
//ResultFactory::~ResultFactory()
//{
//    //�Ȃɂ����Ȃ�
//}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/








/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 RankSprite ��`��
****************************************************************************/
/**************************************************************************
 RankSprite::RankSprite(
	LPDIRECT3DDEVICE9 pD3DDevice,	//	: IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	wstring	     I_fileName,		//	: �e�N�X�`���t�@�C����
	Rect*        i_Rect,			//	: �e�N�X�`���̕`��͈�
	D3DXVECTOR3& i_vPos,			//	: �`�悷����W
	D3DXVECTOR3& i_vScale			//	: �L�k��
	);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��B
***************************************************************************/
RankSprite::RankSprite(
		LPDIRECT3DDEVICE9  pD3DDevice,wstring i_fileName,Rect* i_Rect,
		D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vScale,ResultFactor i_RankFactor,int i_iScore)
		:Sprite( pD3DDevice, i_fileName, i_Rect, g_vZero,i_vPos,g_vZero,i_vScale,g_vZero)
{
	try{
		BYTE byteRankNum = 0;
		float fRankPar = (float)i_iScore / ((float)i_RankFactor.m_dwAllNoteQt * 100.0f) ;
		if(fRankPar >= 0.90f){
			byteRankNum = 0;
		}else
		if(fRankPar >= 0.70f){
			byteRankNum = 1;
		}else
		if(fRankPar >= 0.60f){
			byteRankNum = 2;
		}else
		//if(fRankPar >= 0.90f)
		{
			byteRankNum = 3;
		}
		i_Rect->right;
		m_SpriteItem.m_pRect->left  = i_Rect->right * byteRankNum;
		m_SpriteItem.m_pRect->right = m_SpriteItem.m_pRect->left + i_Rect->right;
	}
	catch(...)
	{
		throw;
	}
}
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �����N�摜��`��
 �߂�l: �Ȃ��B
***************************************************************************/
void RankSprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	Sprite::Draw( pD3DDevice, Vec, pCntlState, Com);
}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/








/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 ScoreSprite ��`��
****************************************************************************/
/**************************************************************************
 ScoreSprite(
	LPDIRECT3DDEVICE9 pD3DDevice,	//	: IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	wstring	     I_fileName,		//	: �e�N�X�`���t�@�C����
	Rect*        i_Rect,			//	: �e�N�X�`���̕`��͈�
	D3DXVECTOR3& i_vPos,			//	: �`�悷����W
	D3DXVECTOR3& i_vScale,			//	: �L�k��
	int			 i_iScore			//	: �X�R�A
	);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��B
***************************************************************************/
ScoreSprite::ScoreSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_fileName,Rect* i_Rect,
									D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vScale,int i_Score)
	: Sprite( pD3DDevice, i_fileName, i_Rect, g_vZero, i_vPos, g_vZero, i_vScale, g_vZero)
{
	try{
		SHaba =27;
		RScore = i_Score;
		for(int i = 0;i < 10; i++)
		{
			SFont[i].left = i * SHaba;
			SFont[i].top = 0;
			SFont[i].right = SFont[i].left + SHaba;
			SFont[i].bottom = 40;
		
		}
	}
	catch(...)
	{		
		throw;
	}

}
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �X�R�A�摜��`��
 �߂�l: �Ȃ��B
***************************************************************************/
void ScoreSprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	int Keta = 1;
	m_SpriteItem.m_vOffsetPos.x = 0.0f;
	for(int i = 0;i <8; i++)
	{
		// �`�悷��ʒu�ƌ��A�؂�o���ʒu�̌v�Z
		*m_SpriteItem.m_pRect = SFont[RScore / Keta % 10];
		Keta *=10;

		m_SpriteItem.m_vOffsetPos.x -=  SHaba;
		
		//	�`�悷��
		Sprite::Draw( pD3DDevice, Vec, pCntlState, Com);
	}
}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/




/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 ScoreSprite ��`��
****************************************************************************/
/**************************************************************************
 WhiteOutSprite(
	LPDIRECT3DDEVICE9 pD3DDevice,	//	: IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	wstring	     i_fileName,		//	: �e�N�X�`���t�@�C����
	);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��B
***************************************************************************/
WhiteOutSprite::WhiteOutSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,DWORD i_Command)
	:Sprite( pD3DDevice, fileName, NULL,g_vZero,g_vZero,g_vZero,g_vOne,g_vZero),
	 m_CntrolLock(true),m_Command(i_Command)
{
	try{
		m_SpriteItem.m_Color =(0x00000000);
		OutFlg = 0;
	}
	catch(...)
	{
			
		throw;
	}

}

/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �z���C�g��������`��
 �߂�l: �Ȃ��B
***************************************************************************/
void WhiteOutSprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	if(!(pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_A)){
		m_CntrolLock = false;

	}
	//�Z���N�g��ʂɈړ�����
	if(!m_CntrolLock && !OutFlg && (pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_A)){
		OutFlg =true;
	}

	if(OutFlg){
		if( m_SpriteItem.m_Color.m_DwordColor >= (0xFF000000)){
			Com.m_Command =m_Command;
			Com.m_Param1 = 0;
			Com.m_Param2 = 0;
			
		}
		m_SpriteItem.m_Color.m_DwordColor += 0x01000000;
	}
	//	�`�悷��
	Sprite::Draw( pD3DDevice, Vec, pCntlState, Com);
	
}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/





}
}