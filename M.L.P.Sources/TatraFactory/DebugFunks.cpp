/**************************************************************************
 DebugFunks.cpp


****************************************************************************/
#include "StdAfx.h"

namespace wiz{
#if defined(DEBUG) || defined(_DEBUG)
namespace Debugger{
	wchar_t			DBGSTR::str[4096];
	LPD3DXFONT		DBGSTR::m_lpDebagFont;        // �t�H���g�I�u�W�F�N
}
#endif
}