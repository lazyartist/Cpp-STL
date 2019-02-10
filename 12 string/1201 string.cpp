#include <iostream>
#include <string>

using namespace std;

/*
string �����̳ʴ� ���ڸ��� ���ҷ� �����ϰ� ���ڿ��� ������ �������� ������� �����̳�.
string�� C++ ǥ�� �����̳��� �䱸������ ��� �������� �ʱ� ������ ���� �����̳�(almost container)�� �θ��� STL���� �������� ����.

string�� ���ڸ� ���ҷ� ����ϴ� �迭 ��� ������ �����̳��̸� vector�� ����ϴ�.
���ڿ��� \0�� �����ؾ��ϴ� �䱸������ ����.

string.begin()�� ù ����, string.end()�� ������ ���� ������ ����Ų��.

reserve()�� �޸� ������ �����ϰ� ��밡��.
capacity()�� �޸� ���� Ȯ��.

string�� basic_string<char>�� typedef
wstring�� basic_string<wchar_t>�� typedef

http://www.cplusplus.com/reference/string/string/
*/

int main() {
	cout << "string ����" << endl;
	{
		string s("a");
		cout << s << endl; // a
	}

	cout << "���� �����Ͽ� string ����" << endl;
	{
		string s("abcd", 2);
		cout << s << endl; // ab
	}

	cout << "���� �ݺ��Ͽ� string ����" << endl;
	{
		string s(2, 'a');
		cout << s << endl; // aa
	}

	cout << "string�� iterator�� ���� �����Ͽ� string ����" << endl;
	{
		string tmp("abcd");
		string s(++tmp.begin(), --tmp.end());
		cout << s << endl; // bc
	}

	cout << "���ڿ� �����ͷ� ���� �����Ͽ� string ����" << endl;
	{
		char tmp[] = "abcd";
		string s(tmp + 1, tmp + 4);
		cout << s << endl; // bcd
	}
	
	cout << "���� ���� ������, �ݺ���" << endl;
	{
		string s("abc");
		auto iter  = s.begin();
		cout << s[1] << endl; // b
		cout << iter[2] << endl; // c
	}

	cout << "+= ���ڿ� ���̱�" << endl;
	{
		string s("ab");
		s += "cd";
		cout << s << endl; // abcd
	}

	cout << "append() ���ڿ� ���̱�" << endl;
	{
		string s("ab");
		s.append("cd");
		cout << s << endl; // abcd
	}

	cout << "append() ���� �����Ͽ� ���ڿ� ���̱�" << endl;
	{
		string s("ab");
		string tmp("cdef");

		s.append(tmp, 3);
		cout << s << endl; // abf

		s.append(tmp, 1/*start pos*/, 3/*end pos(�������� ������ ���ڿ� ������)*/); // �� ��ġ ����
		cout << s << endl; // abfdef

		s.append(tmp.begin(), tmp.end());
		cout << s << endl; // abfdefcdef

		const char* p = "ABC";
		s.append(p, p + 1); // �� ��ġ �������� ����
		cout << s << endl; // abfdefcdefA
	}

	cout << "push_back() ���� ���̱�" << endl;
	{
		string s("ab");
		s.push_back('Z');
		cout << s << endl; // abZ
	}

	cout << "= ���ڿ� �Ҵ�" << endl;
	{
		string s("ab");
		s = "cd";
		cout << s << endl; // cd
	}

	cout << "assign ���ڿ� �Ҵ�, �κ� ���ڿ� �Ҵ��� append() ������ ����" << endl;
	{
		string s("ab");
		s.assign("cd");
		cout << s << endl; // cd
	}

	cout << "C-Style('\\0'���� ����) ���ڿ� ��ȯ : c_s()" << endl;
	{
		string s("ab");
		cout << s.c_str() << endl; // cd
	}

	cout << "'\\0'���� �������� �ʴ� ���ڿ� ��ȯ : data()" << endl;
	{
		string s("ab");
		cout << s.data() << endl; // cd
	}

	cout << "compare() ���ڿ� �� : l > r -> 1, l < r -> -1, l == r -> 0" << endl;
	{
		string s1("abc");
		string s2("bcd");
		string s3("cde");

		cout << s1.compare(s2) << endl; // -1
		cout << s3.compare(s2) << endl; // 1
		cout << s1.compare(s1) << endl; // 0

		cout << s1.compare(1, 2, s2, 0, 2) << endl; // -1
	}


	cout << "compare() ���ڿ� �κ� �� : l > r -> 1, l < r -> -1, l == r -> 0" << endl;
	{
		string s1("abc");
		string s2("bcd");

		cout << s1.compare(1/*pos*/, 2/*len*/, s2, 0/*pos*/, 2/*len*/) << endl; // 0
		cout << s1.compare(1/*pos*/, 2/*len*/, s2, 0/*pos*/, 3/*len*/) << endl; // -1 : s1�� 3��° ���ڰ� �����Ƿ� ������ ���� ���ؼ� -1�� ���µ��ϴ�. 1, 0�� ���ü��� �ְڴ�.
	}

	cout << "copy() ���ڿ� ����(\\0���ڸ� �������� �ʴ´�)" << endl;
	{
		string s("abc");
		char ch[10];

		s.copy(ch, s.length());
		ch[s.length()] = '\0'; // \0���ڸ� �־����� �����Ƿ� �־��ش�.
		cout << ch << endl; // abc

		memset(ch, 0, 10);
		s.copy(ch, s.length()/*len ���� ����*/, 1/*off ���� ���� ��ġ*/);
		cout << ch << endl; // bc
	}


	cout << "find(), rfind() ���� �˻��ؼ� ��ġ ��ȯ" << endl;
	{
		string s("abc def abc def");
		cout << s.find('d') << endl; // 4

		cout << (s.find('d') == string::npos) << endl; // 0 : false, �˻������ ������ string::npos�� ��ȯ, string(basic_string<>)�� ��� ���� �����μ� -1�̴�.
		cout << (s.find('z') == string::npos) << endl; // 1 : true

		cout << (s.find("c d")) << endl; // 2
		cout << (s.find("c d", 3/*pos*/)) << endl; // 10
		cout << (s.find("c d", 3/*pos*/, 3/*len*/) == string::npos) << endl; // 0 : false, ã��. ���� 3���� �¾ƾ���.
		cout << (s.find("c d", 3/*pos*/, 4/*len*/) == string::npos) << endl; // 1 : true, �� ã��. ���� 4���� �¾ƾ���.

		cout << s.rfind('d') << endl; // 12, rfind() �Ųٷ� �˻�
	}

	cout << "insert() ���ڿ� ����" << endl;
	{
		string s1("abc");

		s1.insert(1/*pos*/, "z"/*char**/); // pos �տ� �����Ѵ�. char ���ڸ� ���� �ʰ� ���ڿ��� �޴´�.
		cout << s1 << endl; // azbc

		s1.insert(s1.begin()/*iterator*/, 'a'/*char*/); // single character : iterator insert(iterator p, char c);
		cout << s1 << endl; // aazbc

		string s2("def");
		s1.insert(--s1.end()/*pos*/, s2.begin()/*first*/, s2.end()/*last*/); // Ư�� ��ġ�� �κ������� ���ڿ� ����
		cout << s1 << endl; // aazbdefc
	}

	cout << "replace() ���ڿ� ��ü" << endl;
	{
		string s1("abc");
		s1.replace(1, 2, "z");
		cout << s1 << endl; // az, 1~2 ���ڿ� bc�� z�� ��ü

		string s2("def");
		s1.replace(s1.begin(), --s1.end(), s2.begin(), s2.end());
		cout << s1 << endl; // defz, a�� def�� ��ü
	}

	cout << "substr() ���ڿ� ����" << endl;
	{
		string s("abc");
		cout << s.substr(0) << endl; // abc, 0 ��ġ���� ������ ����
		cout << s.substr(1, string::npos) << endl; // bc, 1 ��ġ���� ������ ����
		cout << s.substr(0, 2) << endl; // ab, 0 ��ġ���� 2�� ����
	}

	cout << ">>, getline() ���ڿ� �Է�" << endl;
	{
		string s1, s2;
		//cin >> s1; // ������ �����ڷ��Ͽ� ������ ����, ������ �������� ������ ���� �Է°��� ���õȴ�.
		cin >> s1 >> s2; // ������ �����ڷ��Ͽ� ������ ����, ������ �������� ������ ���� �Է°��� ���õȴ�.
		cout << s1 << endl; // �Է°�1
		cout << s2 << endl; // �Է°�2

		// cin >> s1 >> s2; �Է� �� �Էµ� Enter�� getline�� �Է� �Ϸ�� �ν��Ѵ�. ���� ������ ���� �Է� ��Ʈ���� ����ش�.
		cin.clear(); // cin��ü�� ���� ���� �÷��� �ʱ�ȭ
		cin.ignore(10000/*���ù��� ����*/, '\n'/*���Ṯ��*/); // ���� ���۾ȿ� �ִ� ���� ����

		getline(cin, s1); // cin.getline(buf)�� ����
		getline(cin, s2, '\n'/*���� ����: �� ���ڸ� �Է��ؾ� �Է��� ����ȴ�.*/);
		cout << "getline: " << s1 << endl; // �Է°�1
		cout << "getline: " << s2 << endl; // �Է°�2
	}

	return 0;
}