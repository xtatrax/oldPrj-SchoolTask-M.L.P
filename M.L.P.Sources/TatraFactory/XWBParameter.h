////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/XWBParameter
//	�t�@�C����		�FXWBParameter.h
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
class XWB :public bassManager{
public:
	XWB(void);
	~XWB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class EASYXWB :public bassManager{
public:
	EASYXWB(void);
	~EASYXWB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class NORMALXWB :public bassManager{
public:
	NORMALXWB(void);
	~NORMALXWB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class HARDXWB :public bassManager{
public:
	HARDXWB(void);
	~HARDXWB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}