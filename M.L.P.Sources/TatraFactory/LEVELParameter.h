////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/LEVELParameter
//	�t�@�C����		�FLEVELParameter.h
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
class EASYLEVEL :public bassManager{
public:
	EASYLEVEL(void);
	~EASYLEVEL(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class NORMALLEVEL :public bassManager{
public:
	NORMALLEVEL(void);
	~NORMALLEVEL(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class HARDLEVEL :public bassManager{
public:
	HARDLEVEL(void);
	~HARDLEVEL(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}