#include <iostream>
#include <string>

using namespace std;

/*
string 컨테이너는 문자만을 원소로 저장하고 문자열을 조작할 목적으로 만들어진 컨테이너.
string은 C++ 표준 컨테이너의 요구사항을 모두 만족하지 않기 때문에 유사 컨테이너(almost container)라 부르고 STL에는 포함하지 않음.

string은 문자를 원소로 취급하는 배열 기반 시퀸스 컨테이너이며 vector와 비슷하다.
문자열에 \0을 포함해야하는 요구사항이 없다.

string.begin()은 첫 문자, string.end()는 마지막 문자 다음을 가리킨다.

reserve()로 메모리 공간을 예약하고 사용가능.
capacity()로 메모리 공간 확인.

string은 basic_string<char>의 typedef
wstring은 basic_string<wchar_t>의 typedef

http://www.cplusplus.com/reference/string/string/
*/

int main() {
	cout << "string 생성" << endl;
	{
		string s("a");
		cout << s << endl; // a
	}

	cout << "범위 지정하여 string 생성" << endl;
	{
		string s("abcd", 2);
		cout << s << endl; // ab
	}

	cout << "문자 반복하여 string 생성" << endl;
	{
		string s(2, 'a');
		cout << s << endl; // aa
	}

	cout << "string의 iterator로 범위 지정하여 string 생성" << endl;
	{
		string tmp("abcd");
		string s(++tmp.begin(), --tmp.end());
		cout << s << endl; // bc
	}

	cout << "문자열 포인터로 범위 지정하여 string 생성" << endl;
	{
		char tmp[] = "abcd";
		string s(tmp + 1, tmp + 4);
		cout << s << endl; // bcd
	}
	
	cout << "임의 접근 연산자, 반복자" << endl;
	{
		string s("abc");
		auto iter  = s.begin();
		cout << s[1] << endl; // b
		cout << iter[2] << endl; // c
	}

	cout << "+= 문자열 붙이기" << endl;
	{
		string s("ab");
		s += "cd";
		cout << s << endl; // abcd
	}

	cout << "append() 문자열 붙이기" << endl;
	{
		string s("ab");
		s.append("cd");
		cout << s << endl; // abcd
	}

	cout << "append() 범위 지정하여 문자열 붙이기" << endl;
	{
		string s("ab");
		string tmp("cdef");

		s.append(tmp, 3);
		cout << s << endl; // abf

		s.append(tmp, 1/*start pos*/, 3/*end pos(지정하지 않으면 문자열 끝까지)*/); // 끝 위치 포함
		cout << s << endl; // abfdef

		s.append(tmp.begin(), tmp.end());
		cout << s << endl; // abfdefcdef

		const char* p = "ABC";
		s.append(p, p + 1); // 끝 위치 포함하지 않음
		cout << s << endl; // abfdefcdefA
	}

	cout << "push_back() 문자 붙이기" << endl;
	{
		string s("ab");
		s.push_back('Z');
		cout << s << endl; // abZ
	}

	cout << "= 문자열 할당" << endl;
	{
		string s("ab");
		s = "cd";
		cout << s << endl; // cd
	}

	cout << "assign 문자열 할당, 부분 문자열 할당은 append() 사용법과 동일" << endl;
	{
		string s("ab");
		s.assign("cd");
		cout << s << endl; // cd
	}

	cout << "C-Style('\\0'문자 포함) 문자열 반환 : c_s()" << endl;
	{
		string s("ab");
		cout << s.c_str() << endl; // cd
	}

	cout << "'\\0'문자 포함하지 않는 문자열 반환 : data()" << endl;
	{
		string s("ab");
		cout << s.data() << endl; // cd
	}

	cout << "compare() 문자열 비교 : l > r -> 1, l < r -> -1, l == r -> 0" << endl;
	{
		string s1("abc");
		string s2("bcd");
		string s3("cde");

		cout << s1.compare(s2) << endl; // -1
		cout << s3.compare(s2) << endl; // 1
		cout << s1.compare(s1) << endl; // 0

		cout << s1.compare(1, 2, s2, 0, 2) << endl; // -1
	}


	cout << "compare() 문자열 부분 비교 : l > r -> 1, l < r -> -1, l == r -> 0" << endl;
	{
		string s1("abc");
		string s2("bcd");

		cout << s1.compare(1/*pos*/, 2/*len*/, s2, 0/*pos*/, 2/*len*/) << endl; // 0
		cout << s1.compare(1/*pos*/, 2/*len*/, s2, 0/*pos*/, 3/*len*/) << endl; // -1 : s1의 3번째 문자가 없으므로 쓰레기 값과 비교해서 -1이 나온듯하다. 1, 0이 나올수도 있겠다.
	}

	cout << "copy() 문자열 복사(\\0문자를 포함하지 않는다)" << endl;
	{
		string s("abc");
		char ch[10];

		s.copy(ch, s.length());
		ch[s.length()] = '\0'; // \0문자를 넣어주지 않으므로 넣어준다.
		cout << ch << endl; // abc

		memset(ch, 0, 10);
		s.copy(ch, s.length()/*len 복사 길이*/, 1/*off 복사 시작 위치*/);
		cout << ch << endl; // bc
	}


	cout << "find(), rfind() 문자 검색해서 위치 반환" << endl;
	{
		string s("abc def abc def");
		cout << s.find('d') << endl; // 4

		cout << (s.find('d') == string::npos) << endl; // 0 : false, 검색결과가 없으면 string::npos를 반환, string(basic_string<>)의 멤버 정의 정수로서 -1이다.
		cout << (s.find('z') == string::npos) << endl; // 1 : true

		cout << (s.find("c d")) << endl; // 2
		cout << (s.find("c d", 3/*pos*/)) << endl; // 10
		cout << (s.find("c d", 3/*pos*/, 3/*len*/) == string::npos) << endl; // 0 : false, 찾음. 문자 3개가 맞아야함.
		cout << (s.find("c d", 3/*pos*/, 4/*len*/) == string::npos) << endl; // 1 : true, 못 찾음. 문자 4개가 맞아야함.

		cout << s.rfind('d') << endl; // 12, rfind() 거꾸로 검색
	}

	cout << "insert() 문자열 삽입" << endl;
	{
		string s1("abc");

		s1.insert(1/*pos*/, "z"/*char**/); // pos 앞에 삽입한다. char 문자를 받지 않고 문자열만 받는다.
		cout << s1 << endl; // azbc

		s1.insert(s1.begin()/*iterator*/, 'a'/*char*/); // single character : iterator insert(iterator p, char c);
		cout << s1 << endl; // aazbc

		string s2("def");
		s1.insert(--s1.end()/*pos*/, s2.begin()/*first*/, s2.end()/*last*/); // 특정 위치에 부분적으로 문자열 삽입
		cout << s1 << endl; // aazbdefc
	}

	cout << "replace() 문자열 교체" << endl;
	{
		string s1("abc");
		s1.replace(1, 2, "z");
		cout << s1 << endl; // az, 1~2 문자열 bc를 z로 교체

		string s2("def");
		s1.replace(s1.begin(), --s1.end(), s2.begin(), s2.end());
		cout << s1 << endl; // defz, a를 def로 교체
	}

	cout << "substr() 문자열 추출" << endl;
	{
		string s("abc");
		cout << s.substr(0) << endl; // abc, 0 위치에서 끝까지 추출
		cout << s.substr(1, string::npos) << endl; // bc, 1 위치에서 끝까지 추출
		cout << s.substr(0, 2) << endl; // ab, 0 위치에서 2개 추출
	}

	cout << ">>, getline() 문자열 입력" << endl;
	{
		string s1, s2;
		//cin >> s1; // 공백을 구분자로하여 변수에 저장, 공백이 변수보다 많으면 이후 입력값은 무시된다.
		cin >> s1 >> s2; // 공백을 구분자로하여 변수에 저장, 공백이 변수보다 많으면 이후 입력값은 무시된다.
		cout << s1 << endl; // 입력값1
		cout << s2 << endl; // 입력값2

		// cin >> s1 >> s2; 입력 시 입력된 Enter를 getline이 입력 완료로 인식한다. 따라서 다음과 같이 입력 스트림을 비워준다.
		cin.clear(); // cin객체의 내부 상태 플래그 초기화
		cin.ignore(10000/*무시문자 길이*/, '\n'/*종료문자*/); // 현재 버퍼안에 있는 내용 무시

		getline(cin, s1); // cin.getline(buf)와 동일
		getline(cin, s2, '\n'/*종료 문자: 이 문자를 입력해야 입력이 종료된다.*/);
		cout << "getline: " << s1 << endl; // 입력값1
		cout << "getline: " << s2 << endl; // 입력값2
	}

	return 0;
}