/**************************************************************************
 WhiteoutEffect.h

 class WhiteoutEffect : public Plate �錾
                                                    2012/06/21�@���O ���� �O
****************************************************************************/
#pragma once
#include "../Sprite.h"
#include "../Sound.h"
namespace wiz{
/**************************************************************************
 class WhiteoutEffect : public Plate;
 �p�r: �����̒����̃N���X�i�R���g���[���œ��삵�Ȃ��j
****************************************************************************/
class WhiteoutEffect : public Sprite{
protected:
	bool	m_bWhiteout;
	bool	m_bComplete;
	bool	m_bWhiteWait;
	float	m_fTimeAccumulator;
	float	m_fAddAlpha;
	float	m_fAlphaBuffer;
public:
/**************************************************************************
 WhiteoutEffect(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
WhiteoutEffect(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,
			   float fWhiteoutTime,D3DCOLOR Color);
/**************************************************************************
 virtual ~WhiteoutEffect();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~WhiteoutEffect();
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
 virtual ~WhiteoutEffect();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	void setWhiteout(){
		m_bWhiteout = true;
	};
	bool getCompleteFlag(){
		return m_bComplete;
	}

};
}