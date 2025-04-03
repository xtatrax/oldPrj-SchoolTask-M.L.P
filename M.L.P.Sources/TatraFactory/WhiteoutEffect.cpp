/**************************************************************************
 WhiteoutEffect.cpp

 WhiteoutEffect; ��`
                                                    2012/06/21�@���O ���� �O
****************************************************************************/
#include "StdAfx.h"
#include "WhiteoutEffect.h"
#include "../Stage_Play.h"
namespace wiz{
/**************************************************************************
 WhiteoutEffect ��`��
***************************************************************************/
/**************************************************************************
 WhiteoutEffect::WhiteoutEffect(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pTexture = 0		//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
WhiteoutEffect::WhiteoutEffect(LPDIRECT3DDEVICE9 pD3DDevice,
					wstring fileName,float fWhiteoutTime,D3DCOLOR Color)
	:Sprite( pD3DDevice, fileName, NULL,g_vZero,g_vZero,g_vZero,g_vOne,g_vZero,Color),
	 m_bWhiteout(false),m_bComplete(false),m_bWhiteWait(false),
	 m_fAlphaBuffer(0),m_fTimeAccumulator(0)
{
    try{
		m_fAddAlpha =  0xFF / fWhiteoutTime;

    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 virtual ~WhiteoutEffect();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
WhiteoutEffect::~WhiteoutEffect(){
}

/**************************************************************************
 void WhiteoutEffect::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState	//�R���g���[���̃X�e�[�^�X
 );
 �p�r: �����̂�`��i�R���g���[�����������j
 �߂�l: �Ȃ��B
***************************************************************************/
void WhiteoutEffect::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){



	if(m_bWhiteWait){
		if((m_fTimeAccumulator += Tempus::getOneFrameTime()) >= 1.0f){
			m_bComplete = true;
		}
	}else
	if(m_bWhiteout){
		if( (m_fAlphaBuffer += m_fAddAlpha * Tempus::getOneFrameTime()) >= 255){
			m_bWhiteWait = true;
		}else{
			m_SpriteItem.m_Color.m_ByteColor.a =  (int)m_fAlphaBuffer;
		}
	}
	


	Sprite::Draw( pD3DDevice, Vec, pCntlState, Com);
}


}