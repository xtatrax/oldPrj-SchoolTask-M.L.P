////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScriptManagerFactory
//	�t�@�C����		�FSMFactory.h
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
//////////////////////////////
//	:
//	: 
class SMFactory{
public:
	//	: �R���X�g���N�^
	SMFactory(std::map<std::wstring , bassManager*>& i_ScriptMap);
	//	: �f�X�g���N�^
	~SMFactory();
};

}}