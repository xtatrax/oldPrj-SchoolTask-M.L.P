////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/MLPSCRIPTVERSIONParameter
//	�t�@�C����		�FMLPSCRIPTVERSIONParameter.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#pragma once
#include "../stdafx.h"
#include "bassManager.h"

namespace wiz{
namespace Script{
class MLPSCRIPTVERSION :public bassManager{
public:
	MLPSCRIPTVERSION(void);
	~MLPSCRIPTVERSION(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}