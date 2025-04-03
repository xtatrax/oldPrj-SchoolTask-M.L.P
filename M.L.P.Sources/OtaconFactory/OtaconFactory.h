/**************************************************************************
 MainFactory.h
                                                    2012/43/06�@���O
													2012/06/17  �啝�C�� ���� �O
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Object.h"
#include "../Sprite.h"
#include "../Stage_Play.h"
namespace wiz{
namespace Otacon{

	
	

	
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/	
/**************************************************************************
 class OtaconFactory;
 �p�r: ���C���H��N���X
****************************************************************************/
class OtaconFactory{
public:
/**************************************************************************
 OtaconFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	OtaconFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~OtaconFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~OtaconFactory();
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/






/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class ResultFactory;
 �p�r: ���C���H��N���X
****************************************************************************/
class ResultFactory{
public:


/**************************************************************************
 ResultFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
ResultFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec,int Score,ResultFactor& Factor);
/**************************************************************************
 ~ResultFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	//~ResultFactory();
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/





/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class RankSprite : public Sprite
 �p�r: �����N�̌v�Z�y�ѕ`��̂��߂̃N���X
****************************************************************************/
class RankSprite : public Sprite{
	public:
/**************************************************************************
 RankSprite(
	LPDIRECT3DDEVICE9 pD3DDevice,	//	: IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	wstring	     I_fileName,		//	: �e�N�X�`���t�@�C����
	Rect*        i_Rect,			//	: �e�N�X�`���̕`��͈�
	D3DXVECTOR3& i_vPos,			//	: �`�悷����W
	D3DXVECTOR3& i_vScale			//	: �L�k��
	);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��B
***************************************************************************/
		RankSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_fileName,Rect* i_Rect,
			D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vScale ,ResultFactor i_RankFactor,int i_iScore);
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
		void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
				 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/





/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class ScoreSprite : public Sprite
 �p�r: �X�R�A��`�悷�邽�߂̃N���X
****************************************************************************/
class ScoreSprite : public Sprite{
	protected:
        int SHaba;
		int RScore;

	public:
		Rect SFont[10];
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
		ScoreSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_fileName,Rect* i_Rect,
			D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vScale ,int i_Score);
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
		void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
				 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/






/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class WhiteOutSprite : public Sprite
 �p�r: �z���C�g�A�E�g�������s�����߂̃N���X
****************************************************************************/
class WhiteOutSprite : public Sprite{
	protected:
		bool OutFlg;
		bool m_CntrolLock;
		DWORD m_Command;

	public:
/**************************************************************************
 WhiteOutSprite(
	LPDIRECT3DDEVICE9 pD3DDevice,	//	: IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	wstring	     i_fileName,		//	: �e�N�X�`���t�@�C����
	);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��B
***************************************************************************/
		WhiteOutSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_fileName,DWORD i_Command);
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
		void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
					 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);


};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/







}
}