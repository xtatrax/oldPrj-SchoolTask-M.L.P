////////////////////////////// //////////////////////////////
//	�\�[�X��		�FbassScriptManager
//	�t�@�C����		�FbassManager.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#ifndef  TLIB_SCRIPT_MANAGER
#define  TLIB_SCRIPT_MANAGER
#include "../stdafx.h"
#include "SHS.h"
namespace wiz{
namespace Script{
class bassManager;
class bassManager{
protected:
	std::wstring ParameterName;
public:
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1 = 0) = 0;
	//	: �C�j�V�����C�U( Parameter�l��this���󂯎��
	bassManager();
};
}
}
#endif