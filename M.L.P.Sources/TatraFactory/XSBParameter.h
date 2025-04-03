////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/XSBParameter
//	�t�@�C����		�FXSBParameter.h
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
class XSB :public bassManager{
public:
	XSB(void);
	~XSB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class EASYXSB :public bassManager{
public:
	EASYXSB(void);
	~EASYXSB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class NORMALXSB :public bassManager{
public:
	NORMALXSB(void);
	~NORMALXSB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class HARDXSB :public bassManager{
public:
	HARDXSB(void);
	~HARDXSB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}