////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/TITLEBANNERParameter
//	�t�@�C����		�FTITLEBANNERParameter.h
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
class TITLEBANNER :public bassManager{
public:
	TITLEBANNER(void);
	~TITLEBANNER(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}