/**************************************************************************
 TSound.h
 class XACTSound; 宣言

                                                    2012/04/17　鴫原 徹
****************************************************************************/
//ヘッダーファイルのインクルード
#include "stdafx.h"
#include "TatraFactory/SHS.h"

//定数定義
#define MAX_WAV 0xFF //WAVサウンド最大数
namespace wiz{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//	かいりょうしよう!
//	いみわからん!
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

	//XACT関連
	XACTINDEX m_iSoundIndex;
	IXACT3Engine* m_pEngine;
	IXACT3WaveBank* m_pWaveBank;
	IXACT3SoundBank* m_pSoundBank;
	IXACT3Cue *m_pCue[0xFF];
	void* pbWaveBank;
	void* pbSoundBank;
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

}