////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/DBGHiSpeedParameter
//	�t�@�C����		�FDBGHiSpeedParameter.h
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
class DBGHiSpeed :public bassManager{
public:
	DBGHiSpeed(void);
	~DBGHiSpeed(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}