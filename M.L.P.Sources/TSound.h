/**************************************************************************
 TSound.h
 class XACTSound; �錾

                                                    2012/04/17�@���� �O
****************************************************************************/
//�w�b�_�[�t�@�C���̃C���N���[�h
#include "stdafx.h"
#include "TatraFactory/SHS.h"

//�萔��`
#define MAX_WAV 0xFF //WAV�T�E���h�ő吔
namespace wiz{
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//	������傤���悤!
//	���݂킩���!
//
class XACTSound
{
public:
	XACTSound(const wstring& szWaveBankName,const wstring& szSoundBankFile);
	XACTSound(const Script::MLPHeader& Header,const Script::SCORELEVEL Level);
	~XACTSound();
	void Run();
	HRESULT InitSound();
	XACTINDEX LoadSound(const wstring& szWaveBankName,const wstring& szSoundBankFile);
	void  PlaySound(XACTINDEX SoundIndex);
	void  PlaySoundB(XACTINDEX SoundIndex);

	//XACT�֘A
	XACTINDEX m_iSoundIndex;
	IXACT3Engine* m_pEngine;
	IXACT3WaveBank* m_pWaveBank;
	IXACT3SoundBank* m_pSoundBank;
	IXACT3Cue *m_pCue[0xFF];
	void* pbWaveBank;
	void* pbSoundBank;
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

}