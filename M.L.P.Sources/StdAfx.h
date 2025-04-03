#pragma once

#ifndef UNICODE
#error This App requires a Unicode build.
#endif

#include "dxsdkver.h"
#if ( _DXSDK_PRODUCT_MAJOR < 9 || _DXSDK_BUILD_MAJOR < 1949 )
#error The installed DXSDK is out of date.
#endif

//必要なバージョンは Windows XP 以降
#ifndef WINVER
#define WINVER         0x0501
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0501
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT   0x0600
#endif

#define ___MLP_WINDOWSIZE_WIDTH		800
#define ___MLP_WINDOWSIZE_HEIGHT	480

//リンカの設計
#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "XInput.lib" )

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx9d.lib" )
#else
#pragma comment( lib, "d3dx9.lib" )
#endif

#pragma comment( lib, "d3dcompiler.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )

// 基本的なインクルード
#include "resource.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <wchar.h>
#include <time.h>

// STL
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <algorithm>
#include <string>
#include <new>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
//#using <system.dll>
// Direct3D9
#include <d3d9.h>
#include <d3dx9.h>

// XInput
#include <XInput.h>

// XACT
#include <xact3.h>


// HRESULT 使用 
#include <dxerr.h>

//例外とユーティリティ関数
#include "Function.h"

//時間
#include "TatraFactory/Tempus.h"

//下層ライブラリ
#include "Object.h"

//いろんなデータ群 めんどくさいからぷりこんしちゃう
#include "TatraFactory/SHS.h"

//	: グローバルデータ
extern D3DXVECTOR3 g_vZero;
extern D3DXVECTOR3 g_vOne;
extern bool        g_bLongNoteMode;

#ifdef SC_CONS_TEST
	#define CS_CONS_COMPILE
#endif

////////////////////////////////////////////////////////////////////////////////
//デバッグ用Define
#if defined(DEBUG) || defined(_DEBUG)


//カメラ位置表示
//#define ___MLP_DEBUG_CAMERAPOSDRAW_
//時間を描画
#define ___MLP_DEBUG_TIMEDRAW_


#include "TatraFactory/DebugFunks.h"
#endif
////////////////////////////////////////////////////////////////////////////////
