# JSONSettingReader

Commented JSON Reader  64Bit V1.00

来歴	
 
 C#、ASP.Netでは、「//」ではコメント入りのJSONがプログラムが勝手に読み込めます。
 
 「JSONにはコメント入れられるんだよね」が普通と思っていました。
 
 しかし、仕様書（https://tools.ietf.org/html/rfc4627）では「そんなのないよ」でした。
 
 C++のboost libraryを使用し発覚。
 
 コメントのない設定ファイルは「使えない」ため、MS形式のコメントが入れられるようにしたいと思いました。
 
 boost libraryを書き換えるより、プリプロを作ってしまえば問題解決。

履歴	

2020/03/05 V1.00 First 
 
Copyright(c) 2020, Retar.jp, All Rights Reserved.

http://www.retar.jp/

●Win32 APIのwinmm.libライブラリをリンクしてください。

「#pragma comment(lib, "winmm.lib")」でもリンクされます。

●Boost Libraryを用意してください。

正規表現などで使っています。
https://www.boost.org/

●VC 2017でコンパイルしていますが、基本的に何でもOKだと思います。

64Bit版のみで確認しています。
