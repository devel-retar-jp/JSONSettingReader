////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///   Commented JSON Reader 64Bit V1.00
///
///	  ����	
///	  C#�AASP.Net�ł́A�u//�v�ł̓R�����g�����JSON���v���O����������ɓǂݍ��߂܂��B
///   �uJSON�ɂ̓R�����g�������񂾂�ˁv�����ʂƎv���Ă��܂����B
///   �������A�d�l���ihttps://tools.ietf.org/html/rfc4627�j�ł́u����Ȃ̂Ȃ���v�ł����B
///   C++��boost library���g�p�����o�B
///   �R�����g�̂Ȃ��ݒ�t�@�C���́u�g���Ȃ��v���߁AMS�`���̃R�����g���������悤�ɂ������Ǝv���܂����B
///   boost library��������������A�v���v��������Ă��܂��Ζ������B
///
///	  ����	
///   2020/03/05 V1.00 First 
///
///                        Copyright(c) 2020, Retar.jp, All Rights Reserved.
///                        http://www.retar.jp/
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///JSON�t�@�C����ǂݍ���
///
///����:
/// �ǂݍ���JSON�I�u�W�F�N�g => JSONptree
/// ���̓t�@�C�� => strfparam
///
void ReadJSON(
	std::string& strfparam,
	boost::property_tree::ptree& JSONptree
);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///JSON�N���[�j���O�E�t�@�C���ϊ�
///
///����:
/// ���̓t�@�C�� => strfparam
/// �o�̓t�@�C���w�b�_ => outheadder
///
void CleanJSON(
	std::string& strfparam,
	std::string outheadder = "TMPFILE_"
);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///JSON�̃R�����g�O���X�g���[��
///
///����:
/// �R�����g����JSON��ǂݍ��� => JSONClean
///
///�o��:
/// �R�����g���O����JSON�e�L�X�g�Ԃ� => std::stringstream 
///
std::stringstream CleanJSONFuncStream(
	std::list<std::string> &JSONClean
);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///JSON�̃R�����g�O��
///
///����:
/// �R�����g�Ȃ�JSON��ǂݍ��� => JSONClean
/// ���̓t�@�C�� => fparam
/// �o�̓t�@�C���w�b�_ => outheadder
///
void CleanJSONFunc(
	std::list<std::string> &JSONClean,
	std::string &fparam,
	std::string outheadder = "TMPFILE_"
);

