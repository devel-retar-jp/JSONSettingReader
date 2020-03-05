////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///   Commented JSON Reader  64Bit V1.00
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
)
{
	//�ԋp�f�[�^
	std::stringstream ss;
	//���H�ς݃f�[�^
	std::list<std::string> JSONData;

	//���H
	for (auto itr = JSONClean.begin(); itr != JSONClean.end(); itr++)
	{
		//���H����
		std::string str = (*itr);

		//�R�����g�폜
		boost::xpressive::sregex comment = boost::xpressive::sregex::compile("//([\\D]*|[\\d]*|[\\S]*|[\\s]*)$");
		std::string format = "";
		str = boost::xpressive::regex_replace(str, comment, format);

		//��s�폜
		boost::xpressive::sregex nodataline = boost::xpressive::sregex::compile("^([\\s]*)$");
		str = boost::xpressive::regex_replace(str, nodataline, format);

		if (str != "")
		{
#ifdef _DEBUG
			//�ϊ��ς�
			std::cout << str << std::endl;
#endif
			//�����o��
			JSONData.push_back(str);
		}
	}

	//ss�ɏ�������
	for (auto itr = JSONData.begin(); itr != JSONData.end(); itr++)
	{
		ss << *itr;
	}
	//�߂�
	return ss;
}

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
	std::string outheadder
)
{
	//���H�ς݃f�[�^
	std::list<std::string> JSONData;

	//���H
	for (auto itr = JSONClean.begin(); itr != JSONClean.end(); itr++)
	{
		//���H����
		std::string str = (*itr);

		//�R�����g�폜
		boost::xpressive::sregex comment = boost::xpressive::sregex::compile("//([\\D]*|[\\d]*|[\\S]*|[\\s]*)$");
		std::string format = "";
		str = boost::xpressive::regex_replace(str, comment, format);

		//��s�폜
		boost::xpressive::sregex nodataline = boost::xpressive::sregex::compile("^([\\s]*)$");
		str = boost::xpressive::regex_replace(str, nodataline, format);

		if (str != "")
		{
#ifdef _DEBUG
			//�ϊ��ς�
			std::cout << str << std::endl;
#endif
			//�����o��
			JSONData.push_back(str);
		}
	}

	//�e���|������������
	boost::filesystem::path pathname(fparam);
	std::string writepath;
	if (pathname.parent_path().string() != "")
	{
		writepath = pathname.parent_path().string() + "\\" + outheadder + pathname.filename().string();
	}
	else
	{
		writepath = outheadder + pathname.filename().string();
	}

	//�t�@�C����������
	fparam = writepath;
	std::ofstream  JSONOut(writepath, std::ios::out);
	for (auto itr = JSONData.begin(); itr != JSONData.end(); itr++)
	{
		JSONOut << *itr << std::endl;
	}
	JSONOut.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///JSON�t�@�C����ǂݍ���
///
///����:
/// �ǂݍ���JSON�I�u�W�F�N�g => JSONptree
/// ���̓t�@�C�� => strfparam
///
void ReadJSON(
	std::string &strfparam,
	boost::property_tree::ptree &JSONptree
)
{
	const char* fparam = strfparam.c_str();

	///�t�@�C���ǂݍ���
	std::ifstream ifs(fparam);
	if (!ifs) {
		std::cerr << "File Not Found : -f\"" << fparam << "\"" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//�ǂݍ���
	std::list<std::string>JSONClean;
	std::string line;
	while (std::getline(ifs, line))
	{
		JSONClean.push_back(line);
	}

	//JSON�̃R�����g���O����stringstream�ɏ����o��
	auto cJSON = CleanJSONFuncStream(JSONClean);

	//JSON�ǂݍ���
	boost::property_tree::read_json(cJSON, JSONptree);
#ifdef _DEBUG
	std::cout << "---------------" << std::endl;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///JSON�t�@�C�����N���[���ɂ��ď����o��
///
///����:
/// ���̓t�@�C�� => strfparam
/// �w�b�_�g���q(�ȗ���) => outheadder
///
void CleanJSON(
	std::string &strfparam,
	std::string outheadder = "TMPFILE_"
)
{
	const char* fparam = strfparam.c_str();

	///�t�@�C���ǂݍ���
	std::ifstream ifs(fparam);
	if (!ifs) {
		std::cerr
			<< "File Not Found : -f\""
			<< fparam 
			<< "\"" 
			<< std::endl;
		std::exit(EXIT_FAILURE);
	}

	//�ǂݍ���
	std::list<std::string>JSONClean;
	std::string line;
	while (std::getline(ifs, line))
	{		
#ifdef _DEBUG
		std::cout << line << std::endl;
#endif
		JSONClean.push_back(line);
	}
#ifdef _DEBUG
	std::cout << "---------------" << std::endl;
#endif

	//JSON�̃R�����g���O��
	CleanJSONFunc(
		JSONClean,
		strfparam,
		outheadder
	);
#ifdef _DEBUG
	std::cout << "---------------" << std::endl;
#endif

}
