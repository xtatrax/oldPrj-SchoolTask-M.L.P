////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/BPMParameter
//	�t�@�C����		�FBPMParameter.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#include "stdafx.h"
#include "BPMParameter.h"
namespace wiz{
namespace Script{
BPM::BPM(void)
{
}

BPM::~BPM(void)
{
}
void BPM::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	//char* ch; 
	Header.Bpm = wcstoul( Subsequent.c_str(),NULL,10);
}

}}