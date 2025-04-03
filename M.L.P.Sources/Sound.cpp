/**************************************************************************
 MainFactory.cpp

 class Light : public Object; 定義
 class DirectionalLight : public Light 定義
 class Camera : public Object; 定義
 class LookDownCamera : public Camera; 定義
 class Guide : public Object; 定義
 class Shadow: public Object; 定義

                                                    2012/04/17　自分の名前
****************************************************************************/
#include "StdAfx.h"
#include "Sound.h"
namespace wiz{



/**************************************************************************
 Sound 定義部
****************************************************************************/
/**************************************************************************
 void Sound::Clear();
 用途:オブジェクトの破棄
 戻り値: なし
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
 const wchar_t* pWavBankFileName,		//Wavバンクのファイル名
 const wchar_t* pSoundBankFileName	//Soundバンクのファイル名
 );
 用途: コンストラクタ
 戻り値: なし
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
			// 初期化失敗
			throw DxException(
				L"Com初期化に失敗しました。",
				L"Sound::Sound()"
				);
		}


		//デバッグ時は以下をtrueにする
		bool bDebugMode = false;
		DWORD dwCreationFlags = 0;
		if( bDebugMode ) dwCreationFlags |= XACT_FLAG_API_DEBUG_MODE;
		if(FAILED(XACT3CreateEngine( dwCreationFlags, &m_pEngine ))){
			// 初期化失敗
			throw DxException(
				L"サウンドエンジン構築に失敗しました。",
				L"Sound::Sound()"
				);
		}
		// Initialize & create the XACT runtime 
		XACT_RUNTIME_PARAMETERS xrParams = {0};
		xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
		if(FAILED(m_pEngine->Initialize( &xrParams ))){
			// 初期化失敗
			throw DxException(
				L"サウンドエンジン初期化に失敗しました。",
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
							// 初期化失敗
							throw DxException(
								L"Wavバンクハンドル初期化に失敗しました。",
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
							// 初期化失敗
							throw DxException(
								L"Soundバンクハンドル初期化に失敗しました。",
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
		//再throw
		throw;
	}



}
/**************************************************************************
 virtual Sound::~Sound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Sound::~Sound(){
	Clear();
}
/**************************************************************************
 virtual void Sound::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 影を描画
 戻り値: なし。
***************************************************************************/
void Sound::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
}


/**************************************************************************
 ZapSound 定義部
****************************************************************************/
/**************************************************************************
 ZapSound::ZapSound(
 const wchar_t* pWavBankFileName,		//Wavバンクのファイル名
 const wchar_t* pSoundBankFileName	//Soundバンクのファイル名
 const char* pZapKey,				//Zapのキー
 const char* pFireKey				//発射音のキー
 );
 用途: コンストラクタ
 戻り値: なし
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
		//再throw
		throw;
	}
}
/**************************************************************************
 virtual ~ZapSound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ZapSound::~ZapSound(){
	//Clear()は親クラスが呼ぶ
}
/**************************************************************************
 virtual void ZapSound::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 描画（サウンドなのでなにもしない）
 戻り値: なし。
***************************************************************************/
void ZapSound::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
		  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
}
/**************************************************************************
 void PlayZap();
 用途: Zapを鳴らす
 戻り値: なし。
***************************************************************************/
void ZapSound::PlayZap(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iZap, 0, 0, NULL );
	}
}
/**************************************************************************
 void ZapSound::PlayFire();
 用途: 発射音を鳴らす
 戻り値: なし。
***************************************************************************/
void ZapSound::PlayFire(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iFire, 0, 0, NULL );
	}
}






}
//end of namespace wiz.
