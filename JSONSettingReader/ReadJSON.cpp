////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///   Commented JSON Reader  64Bit V1.00
///
///	  来歴	
///	  C#、ASP.Netでは、「//」ではコメント入りのJSONがプログラムが勝手に読み込めます。
///   「JSONにはコメント入れられるんだよね」が普通と思っていました。
///   しかし、仕様書（https://tools.ietf.org/html/rfc4627）では「そんなのないよ」でした。
///   C++のboost libraryを使用し発覚。
///   コメントのない設定ファイルは「使えない」ため、MS形式のコメントが入れられるようにしたいと思いました。
///   boost libraryを書き換えるより、プリプロを作ってしまえば問題解決。
///
///	  履歴	
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
///JSONのコメント外しストリーム
///
///入力:
/// コメント入りJSONを読み込み => JSONClean
///
///出力:
/// コメントを外したJSONテキスト返し => std::stringstream 
///
std::stringstream CleanJSONFuncStream(
	std::list<std::string> &JSONClean
)
{
	//返却データ
	std::stringstream ss;
	//加工済みデータ
	std::list<std::string> JSONData;

	//加工
	for (auto itr = JSONClean.begin(); itr != JSONClean.end(); itr++)
	{
		//加工処理
		std::string str = (*itr);

		//コメント削除
		boost::xpressive::sregex comment = boost::xpressive::sregex::compile("//([\\D]*|[\\d]*|[\\S]*|[\\s]*)$");
		std::string format = "";
		str = boost::xpressive::regex_replace(str, comment, format);

		//空行削除
		boost::xpressive::sregex nodataline = boost::xpressive::sregex::compile("^([\\s]*)$");
		str = boost::xpressive::regex_replace(str, nodataline, format);

		if (str != "")
		{
#ifdef _DEBUG
			//変換済み
			std::cout << str << std::endl;
#endif
			//書き出し
			JSONData.push_back(str);
		}
	}

	//ssに書き込み
	for (auto itr = JSONData.begin(); itr != JSONData.end(); itr++)
	{
		ss << *itr;
	}
	//戻し
	return ss;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///JSONのコメント外し
///
///入力:
/// コメントなしJSONを読み込み => JSONClean
/// 入力ファイル => fparam
/// 出力ファイルヘッダ => outheadder
///
void CleanJSONFunc(
	std::list<std::string> &JSONClean,
	std::string &fparam,
	std::string outheadder
)
{
	//加工済みデータ
	std::list<std::string> JSONData;

	//加工
	for (auto itr = JSONClean.begin(); itr != JSONClean.end(); itr++)
	{
		//加工処理
		std::string str = (*itr);

		//コメント削除
		boost::xpressive::sregex comment = boost::xpressive::sregex::compile("//([\\D]*|[\\d]*|[\\S]*|[\\s]*)$");
		std::string format = "";
		str = boost::xpressive::regex_replace(str, comment, format);

		//空行削除
		boost::xpressive::sregex nodataline = boost::xpressive::sregex::compile("^([\\s]*)$");
		str = boost::xpressive::regex_replace(str, nodataline, format);

		if (str != "")
		{
#ifdef _DEBUG
			//変換済み
			std::cout << str << std::endl;
#endif
			//書き出し
			JSONData.push_back(str);
		}
	}

	//テンポラリ書き込み
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

	//ファイル書き込み
	fparam = writepath;
	std::ofstream  JSONOut(writepath, std::ios::out);
	for (auto itr = JSONData.begin(); itr != JSONData.end(); itr++)
	{
		JSONOut << *itr << std::endl;
	}
	JSONOut.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///JSONファイルを読み込む
///
///入力:
/// 読み込みJSONオブジェクト => JSONptree
/// 入力ファイル => strfparam
///
void ReadJSON(
	std::string &strfparam,
	boost::property_tree::ptree &JSONptree
)
{
	const char* fparam = strfparam.c_str();

	///ファイル読み込み
	std::ifstream ifs(fparam);
	if (!ifs) {
		std::cerr << "File Not Found : -f\"" << fparam << "\"" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//読み込み
	std::list<std::string>JSONClean;
	std::string line;
	while (std::getline(ifs, line))
	{
		JSONClean.push_back(line);
	}

	//JSONのコメントを外してstringstreamに書き出す
	auto cJSON = CleanJSONFuncStream(JSONClean);

	//JSON読み込み
	boost::property_tree::read_json(cJSON, JSONptree);
#ifdef _DEBUG
	std::cout << "---------------" << std::endl;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///JSONファイルをクリーンにして書き出し
///
///入力:
/// 入力ファイル => strfparam
/// ヘッダ拡張子(省略可) => outheadder
///
void CleanJSON(
	std::string &strfparam,
	std::string outheadder = "TMPFILE_"
)
{
	const char* fparam = strfparam.c_str();

	///ファイル読み込み
	std::ifstream ifs(fparam);
	if (!ifs) {
		std::cerr
			<< "File Not Found : -f\""
			<< fparam 
			<< "\"" 
			<< std::endl;
		std::exit(EXIT_FAILURE);
	}

	//読み込み
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

	//JSONのコメントを外す
	CleanJSONFunc(
		JSONClean,
		strfparam,
		outheadder
	);
#ifdef _DEBUG
	std::cout << "---------------" << std::endl;
#endif

}
