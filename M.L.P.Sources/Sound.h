/**************************************************************************
 MainFactory.h

 class Light : public Object; �錾
 class DirectionalLight : public Light; �錾
 class Camera : public Object; �錾
 class LookDownCamera : public Camera; �錾
 class Guide : public Object; �錾
 class Shadow: public Object; �錾

                                                    2012/04/17�@�����̖��O
****************************************************************************/
#pragma once

#include "StdAfx.h"
namespace wiz{



/**************************************************************************
 class Sound: public Object;
 �p�r: �T�E���h�N���X
****************************************************************************/
class Sound : public Object{
protected:
	IXACT3Engine* m_pEngine;
	IXACT3WaveBank* m_pWaveBank;
	IXACT3SoundBank* m_pSoundBank;
	VOID* m_pbWaveBank; // Handle to wave bank data.  Its memory mapped so call UnmapViewOfFile() upon cleanup to release file
	VOID* m_pbSoundBank; // Pointer to sound bank data.  Call delete on it when the sound bank is destroyed
/**************************************************************************
 void Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 Sound(
 const wchar_t* pWavBankFileName,		//Wav�o���N�̃t�@�C����
 const wchar_t* pSoundBankFileName	//Sound�o���N�̃t�@�C����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName);
/**************************************************************************
 virtual ~Sound();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~Sound();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �`��i�T�E���h�Ȃ̂łȂɂ����Ȃ��j
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};


/**************************************************************************
 class ZapSound: public Sound;
 �p�r: Zap�T�E���h�N���X
****************************************************************************/
class ZapSound : public Sound{
	XACTINDEX m_iZap;
	XACTINDEX m_iFire;
public:
/**************************************************************************
 ZapSound(
 const wchar_t* pWavBankFileName,		//Wav�o���N�̃t�@�C����
 const wchar_t* pSoundBankFileName	//Sound�o���N�̃t�@�C����
 const char* pZapKey				//�������̃L�[
 const char* pFireKey				//���ˉ��̃L�[
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	ZapSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,
		const char* pZapKey,const char* pFireKey);
/**************************************************************************
 virtual ~ZapSound();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~ZapSound();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �`��i�T�E���h�Ȃ̂łȂɂ����Ȃ��j
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
/**************************************************************************
 void PlayZap();
 �p�r: ������炷
 �߂�l: �Ȃ��B
***************************************************************************/
    void PlayZap();
/**************************************************************************
 void PlayFire();
 �p�r: ���ˉ���炷
 �߂�l: �Ȃ��B
***************************************************************************/
    void PlayFire();

};




}
//end of namespace wiz.

