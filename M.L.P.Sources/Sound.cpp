/**************************************************************************
 MainFactory.cpp

 class Light : public Object; ��`
 class DirectionalLight : public Light ��`
 class Camera : public Object; ��`
 class LookDownCamera : public Camera; ��`
 class Guide : public Object; ��`
 class Shadow: public Object; ��`

                                                    2012/04/17�@�����̖��O
****************************************************************************/
#include "StdAfx.h"
#include "Sound.h"
namespace wiz{



/**************************************************************************
 Sound ��`��
****************************************************************************/
/**************************************************************************
 void Sound::Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
void Sound::Clear(){
    if(m_pEngine){
        m_pEngine->ShutDown();
		SafeRelease(m_pEngine);
    }
	SafeDeleteArr(m_pbSoundBank);
	if(m_pbWaveBank){
        UnmapViewOfFile(m_pbWaveBank);
	}
    m_pbWaveBank = 0;
    CoUninitialize();
}
/**************************************************************************
 Sound::Sound(
 const wchar_t* pWavBankFileName,		//Wav�o���N�̃t�@�C����
 const wchar_t* pSoundBankFileName	//Sound�o���N�̃t�@�C����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Sound::Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName)
:m_pEngine(0),m_pWaveBank(0),m_pSoundBank(0),m_pbWaveBank(0),m_pbSoundBank(0)
{
	try{
		HANDLE hFile;
		DWORD dwFileSize;
		DWORD dwBytesRead;
		HANDLE hMapFile;

		if(FAILED(CoInitializeEx( NULL, COINIT_MULTITHREADED))){
			// ���������s
			throw DxException(
				L"Com�������Ɏ��s���܂����B",
				L"Sound::Sound()"
				);
		}


		//�f�o�b�O���͈ȉ���true�ɂ���
		bool bDebugMode = false;
		DWORD dwCreationFlags = 0;
		if( bDebugMode ) dwCreationFlags |= XACT_FLAG_API_DEBUG_MODE;
		if(FAILED(XACT3CreateEngine( dwCreationFlags, &m_pEngine ))){
			// ���������s
			throw DxException(
				L"�T�E���h�G���W���\�z�Ɏ��s���܂����B",
				L"Sound::Sound()"
				);
		}
		// Initialize & create the XACT runtime 
		XACT_RUNTIME_PARAMETERS xrParams = {0};
		xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
		if(FAILED(m_pEngine->Initialize( &xrParams ))){
			// ���������s
			throw DxException(
				L"�T�E���h�G���W���������Ɏ��s���܂����B",
				L"Sound::Sound()"
				);
		}

		hFile = CreateFile(pWavBankFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
		if( hFile != INVALID_HANDLE_VALUE ){
			dwFileSize = GetFileSize( hFile, NULL );
			if( dwFileSize != -1 ){
				hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
				if( hMapFile ){
					m_pbWaveBank = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
					if(m_pbWaveBank){
						if(FAILED(m_pEngine->CreateInMemoryWaveBank(m_pbWaveBank, dwFileSize, 0,
							0, &m_pWaveBank))){
							CloseHandle( hMapFile );
							CloseHandle( hFile );
							// ���������s
							throw DxException(
								L"Wav�o���N�n���h���������Ɏ��s���܂����B",
								L"Sound::Sound()"
								);
						}
					}
					CloseHandle( hMapFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
				}
			}
			CloseHandle( hFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
		}
		hFile = CreateFile(pSoundBankFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
		if( hFile != INVALID_HANDLE_VALUE )
		{
			dwFileSize = GetFileSize( hFile, NULL );
			if( dwFileSize != -1 )
			{
				// Allocate the data here and free the data when recieving the sound bank destroyed notification
				m_pbSoundBank = new BYTE[dwFileSize];
				if(m_pbSoundBank)
				{
					if( 0 != ReadFile( hFile,m_pbSoundBank, dwFileSize, &dwBytesRead, NULL ) )
					{
						if(FAILED(m_pEngine->CreateSoundBank(m_pbSoundBank, dwFileSize, 0,
							0, &m_pSoundBank))){
							CloseHandle( hFile );
							// ���������s
							throw DxException(
								L"Sound�o���N�n���h���������Ɏ��s���܂����B",
								L"Sound::Sound()"
								);

						}
					}
				}
			}
			CloseHandle( hFile );
		}

	}
	catch(...){
		Clear();
		//��throw
		throw;
	}



}
/**************************************************************************
 virtual Sound::~Sound();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Sound::~Sound(){
	Clear();
}
/**************************************************************************
 virtual void Sound::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �e��`��
 �߂�l: �Ȃ��B
***************************************************************************/
void Sound::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
}


/**************************************************************************
 ZapSound ��`��
****************************************************************************/
/**************************************************************************
 ZapSound::ZapSound(
 const wchar_t* pWavBankFileName,		//Wav�o���N�̃t�@�C����
 const wchar_t* pSoundBankFileName	//Sound�o���N�̃t�@�C����
 const char* pZapKey,				//Zap�̃L�[
 const char* pFireKey				//���ˉ��̃L�[
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ZapSound::ZapSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,
				   const char* pZapKey,const char* pFireKey)
:Sound(pWavBankFileName,pSoundBankFileName),m_iZap(0),m_iFire(0)
{
	try{
		if(m_pSoundBank){
			m_iZap = m_pSoundBank->GetCueIndex(pZapKey);
			m_iFire = m_pSoundBank->GetCueIndex(pFireKey);
		}
	}
	catch(...){
		Clear();
		//��throw
		throw;
	}
}
/**************************************************************************
 virtual ~ZapSound();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ZapSound::~ZapSound(){
	//Clear()�͐e�N���X���Ă�
}
/**************************************************************************
 virtual void ZapSound::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �`��i�T�E���h�Ȃ̂łȂɂ����Ȃ��j
 �߂�l: �Ȃ��B
***************************************************************************/
void ZapSound::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
		  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
}
/**************************************************************************
 void PlayZap();
 �p�r: Zap��炷
 �߂�l: �Ȃ��B
***************************************************************************/
void ZapSound::PlayZap(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iZap, 0, 0, NULL );
	}
}
/**************************************************************************
 void ZapSound::PlayFire();
 �p�r: ���ˉ���炷
 �߂�l: �Ȃ��B
***************************************************************************/
void ZapSound::PlayFire(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iFire, 0, 0, NULL );
	}
}






}
//end of namespace wiz.
