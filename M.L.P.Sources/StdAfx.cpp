/**************************************************************************
 StdAfx.cpp

 �v���R���p�C���ς݃w�b�_�쐬�p
****************************************************************************/

#include "StdAfx.h"

D3DXVECTOR3 g_vZero	= D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXVECTOR3 g_vOne	= D3DXVECTOR3(1.0f,1.0f,1.0f);
#if defined(DEBUG) || defined(_DEBUG)
bool        g_bLongNoteMode = true;
#else
bool        g_bLongNoteMode = false;
#endif
