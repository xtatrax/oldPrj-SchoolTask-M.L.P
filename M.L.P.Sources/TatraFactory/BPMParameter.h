////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/BPMParameter
//	�t�@�C����		�FBPMParameter.h
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
class BPM :public bassManager{
public:
	BPM(void);
	~BPM(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}