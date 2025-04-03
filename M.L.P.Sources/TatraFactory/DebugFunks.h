/**************************************************************************
 DebugFunks.h

 
                                                    2012/03/04�@���O ���� �O
****************************************************************************/
#pragma once
#include "StdAfx.h"


namespace wiz{
#if defined(DEBUG) || defined(_DEBUG)
namespace Debugger{
/************************************************
class tagDBGSTR

�ړI:�@�ȈՓI�ɕ��������ʏ�ɕ`��
*************************************************/
class DBGSTR{
public:
	static wchar_t			str[4096];
	static LPD3DXFONT		m_lpDebagFont;        // �t�H���g�I�u�W�F�N

	static void addStr(wchar_t* addStr,...){
		wchar_t strBuf[1024];
		va_list	argp;
		va_start(argp, addStr);
		vswprintf_s( strBuf , 1024 , addStr, argp);
		va_end(argp);
		wsprintf(str,L"%s%s" , str ,strBuf);
	}
	static void Init(LPDIRECT3DDEVICE9	i_pD3DDevice){
		try{
			if (FAILED(D3DXCreateFont(i_pD3DDevice,				/* �f�o�C�X */
							10,									/* �����̍��� */
							0,									/* ������ */
							FW_NORMAL,							/* �t�H���g�̑��� */
							1,									/* MIPMAP�̃��x�� */
							FALSE,								/* �C�^���b�N���H */
							DEFAULT_CHARSET,					/* �����Z�b�g */
							OUT_DEFAULT_PRECIS,					/* �o�͐��x */
							DEFAULT_QUALITY,					/* �o�͕i�� */
							DEFAULT_PITCH | FF_SWISS,			/* �t�H���g�s�b�`�ƃt�@�~�� */
							L"�l�r �S�V�b�N",					/* �t�H���g�� */
							&m_lpDebagFont))) {					/* Direct3D�t�H���g�ւ̃|�C���^�ւ̃A�h���X */
				char		strBuf[2048]={0};
				sprintf_s(strBuf,sizeof(strBuf), "�f�o�b�O�p�t�H���g�̐����Ɏ��s\n �ꏊ : \"%s(%d) Func:%s\" \n�����܂����H",__FILE__,__LINE__,__FUNCTION__);
				wchar_t		outBuf[4096]={0};
				setlocale( LC_CTYPE, "jpn" );
				size_t nNameSize = 0;
				mbstowcs_s(&nNameSize,outBuf,strlen(strBuf),strBuf,_TRUNCATE);
				if(MessageBox(NULL,outBuf,L"�f�o�b�O�֐��G���[ �ꏊ:tagDBGSTR::Init",MB_YESNO) == IDNO){
					throw 1;
				}
			}
		}
		catch(...){
			throw;
		}
	}
	static void Draw(){
		m_lpDebagFont->DrawText(NULL,str, -1, NULL
			, 0 , D3DCOLOR_ARGB(255, 255, 255, 124));
		wsprintf(str,L"\n\n\n\n\n\n\n\n�f�o�b�O\n\0" );
	}
};
}
#endif
}