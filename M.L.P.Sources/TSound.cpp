/**************************************************************************
 Sound.cpp

 XACTSound; ��`
                                                    2012/03/04�@���O ���� �O
****************************************************************************/


#include "stdafx.h"
#include "TSound.h"
namespace wiz{
/**************************************************************************
 XACTSound ��`��
****************************************************************************/
/**************************************************************************
 XACTSound::XACTSound();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
XACTSound::XACTSound(const wstring& szWaveBankName,const wstring& szSoundBankFile)
{
	for(XACTINDEX i = 0; i <= 0xFF ; i++) m_pCue[i] = NULL;
	ZeroMemory(this,sizeof(XACTSound));
	//�T�E���h�֘A�iXAudio2�j�̏�����
	if(FAILED(InitSound()))
	{
		MessageBox(0,L"XACT ���������s",NULL,MB_OK);
		return;
	}
	InitSound();
	m_pEngine->DoWork();
	m_iSoundIndex = LoadSound(szWaveBankName,szSoundBankFile);
}
XACTSound::XACTSound(const Script::MLPHeader& Header,const Script::SCORELEVEL Level)
{
	wstring XSBName;
	wstring XWBName;
	switch(Level){
		case Script::EASY:
			XSBName = Header.EASYXSBPath;
			XWBName = Header.EASYXWBPath;
		break;
		case Script::NORMAL:
			XSBName = Header.NORMALXSBPath;
			XWBName = Header.NORMALXWBPath;
		break;
		case Script::HARD:
			XSBName = Header.HARDXSBPath;
			XWBName = Header.HARDXWBPath;
		break;
	}
	if( XSBName.empty()){
		XSBName = Header.XSBPath;
	}
	if( XWBName.empty()){
		XWBName = Header.XWBPath;
	}

	ZeroMemory(this,sizeof(XACTSound));
	//�T�E���h�֘A�iXAudio2�j�̏�����
	if(FAILED(InitSound()))
	{
		MessageBox(0,L"XACT ���������s",NULL,MB_OK);
		return;
	}
	InitSound();
	m_pEngine->DoWork();
	m_iSoundIndex = LoadSound(Header.FilePath + XWBName,Header.FilePath + XSBName);
}
//
//
//
XACTSound::~XACTSound()
{
	for(XACTINDEX i = 0; i < 0xFF ; i++){
		if(m_pCue[i] != NULL){
			m_pCue[i]->Destroy();
		}
		m_pCue[i] = NULL;
	}
	m_pWaveBank->Destroy();
	m_pSoundBank->Destroy();
	m_pEngine->ShutDown();
	m_pEngine->Release();

	CoUninitialize();
}
//
//
//
HRESULT XACTSound::InitSound()
{
	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	if(FAILED(XACT3CreateEngine( XACT_FLAG_API_DEBUG_MODE, &m_pEngine )))
	{
		return E_FAIL;
	}
	XACT_RUNTIME_PARAMETERS xrParams ={0};
	xrParams.lookAheadTime=XACT_ENGINE_LOOKAHEAD_DEFAULT;
	if(FAILED(m_pEngine->Initialize(&xrParams)))
	{
		return E_FAIL;
	}
	return S_OK;
}
//
//
//
XACTINDEX XACTSound::LoadSound(const wstring& szWaveBankName,const wstring& szSoundBankFile)
{
	static int iIndex=-1;
	//Wave�o���N
	HANDLE hFile = CreateFile(szWaveBankName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return 0;
	}
	DWORD dwFileSize = GetFileSize( hFile, NULL );
	HANDLE hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
	pbWaveBank = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
	if(pbWaveBank)
	{
		m_pEngine->CreateInMemoryWaveBank(pbWaveBank, dwFileSize, 0,0, &m_pWaveBank );
	}
	CloseHandle( hMapFile );
	CloseHandle( hFile );
	//Sound�o���N
	hFile=CreateFile(szSoundBankFile.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return 0;
	}
	dwFileSize = GetFileSize( hFile, NULL );
	pbSoundBank = new BYTE[dwFileSize];
	if(pbSoundBank)
	{
		DWORD dwBytesRead=0;
		ReadFile( hFile, pbSoundBank, dwFileSize, &dwBytesRead, NULL );
		m_pEngine->CreateSoundBank( pbSoundBank, dwFileSize, 0,0, &m_pSoundBank );
	}
	CloseHandle( hFile );
	XACTINDEX CueNum = 0;
	m_pSoundBank->GetNumCues(&CueNum);
	for(XACTINDEX i = 0 ; i < CueNum ; i++ ){
		m_pSoundBank->Prepare(i, 0, 0,&m_pCue[i]);
		DWORD dwCueStatus = 0;
		m_pCue[i]->GetState(&dwCueStatus);
	}
	//iIndex = m_pSoundBank->GetCueIndex(szCueName);
	
	return iIndex;
}
//
//
//
void  XACTSound::PlaySound(XACTINDEX SoundIndex)//,
{
	 m_pCue[SoundIndex]->Play( );
}
void  XACTSound::PlaySoundB(XACTINDEX SoundIndex)//,
{
	m_pSoundBank->Play( SoundIndex, 0, 0, NULL );
}
}