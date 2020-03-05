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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///●Win32 APIのwinmm.libライブラリをリンクしてください。
///「#pragma comment(lib, "winmm.lib")」でもリンクされます。
///
///●Boost Libraryを用意してください。
///正規表現などで使っています。
///https://www.boost.org/
///
///●VC 2017でコンパイルしていますが、基本的に何でもOKだと思います。
///64Bit版のみで確認しています。
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <windows.h>
#include <filesystem.hpp>
#include "ReadJSON.h"

///サンプルのJSONファイル
#define JSONFILE "sample.json"

///Main
int main()
{
	//*********************************************//
	//プログラムスタート時間
	DWORD program_start = timeGetTime();

	//*********************************************//
	//カレントディレクトリ
	boost::filesystem::path full_path(boost::filesystem::current_path());
	std::string pathdir = full_path.generic_string();
	std::cout 
		<< "Current Path : "
		<< pathdir
		<< std::endl;
	std::cout << "---------------" << std::endl;

	//*********************************************//
	//実行ファイルパス
	std::string jsonfile = pathdir;
	jsonfile.append("/");
	jsonfile.append(JSONFILE);
	std::cout
		<< "JSON FILE : "
		<< jsonfile
		<< std::endl;
	std::cout << "---------------" << std::endl;

	//*********************************************//
	//JSONクリーニング・ファイル変換
	//
	// JSONFILEを"TMPFILE_"を加えたファイルに変換
	// コメントを外したファイルに変換
	//
	boost::system::error_code jsonfile_error;
	const bool jsonfile_result = boost::filesystem::exists(jsonfile, jsonfile_error);
	if (!jsonfile_result || jsonfile_error)
	{
		MessageBox(NULL, L"JSON File Not Found", TEXT("Fail"), MB_OK);
		return 0;
	}
	CleanJSON(jsonfile);	//CleanJSON(jsonfile,"TMPFILE_");

	//*********************************************//
	//JSONファイルを読み込む
	//
	// JSONFILEを読み込み、jsonptに読み込む
	// コメントを外したファイルに変換
	//
	boost::property_tree::ptree jsonpt;
	ReadJSON(
		jsonfile,	//ファイル名	
		jsonpt		//JSON ptree
	);

	//*********************************************//
	//jsonptに読み込まれたデータの出力
	//
	//Comment
	if (boost::optional<std::string> item = jsonpt.get_optional<std::string>("Comment")) {
		auto itemget = item.get();
		std::cout << "Comment : " << itemget << std::endl;
	}
	else {
		std::cout << "Comment is nothing" << std::endl;
	}
	//
	//Number
	if (boost::optional<int> item = jsonpt.get_optional<int>("Number")) {
		auto itemget = item.get();
		std::cout << "Number : " << itemget << std::endl;
	}
	else {
		std::cout << "Number is nothing" << std::endl;
	}
	//
	//Indent.Comment
	if (boost::optional<std::string> item = jsonpt.get_optional<std::string>("Indent.Comment")) {
		auto itemget = item.get();
		std::cout << "Indent.Comment : " << itemget << std::endl;
	}
	else {
		std::cout << "Indent.Comment is nothing" << std::endl;
	}
	//
	//Indent.IndentNumber
	if (boost::optional<int> item = jsonpt.get_optional<int>("Indent.IndentNumber")) {
		auto itemget = item.get();
		std::cout << "Indent.IndentNumber : " << itemget << std::endl;
	}
	else {
		std::cout << "Indent.IndentNumber is nothing" << std::endl;
	}

	//*********************************************//
	//プログラム終了時間
	DWORD program_end = timeGetTime();
	std::cout << "---------------" << std::endl;
	std::cout
		<< "Run Time = "
		<< (double)(program_end - program_start) / 1000
		<< " sec.\n";
}
