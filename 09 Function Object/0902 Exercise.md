
1. ����� �Լ� ��ü ������ ����� ������ �����ϱ� ���� ���� �Լ� ��ü�� ���� �Լ� ��ü�� ����
2. STL�� less �Լ� ��ü�� ���� ������ �ϰ� ����� ������ ������ �Լ� ��ü ����
3. binder1st, binder2nd ������
4. not1, not2 ������

<details>
<summary>����</summary>
<ol>
<li>���� �Լ� : argument_type, result_type ����<br>
���� �Լ� : first_argument_type, second_argument_type, result_type ����</li>
<li>
template(typename T)
struct Less : public binary_function {<br>
    bool operator()(const T &l, const T &r) const {<br>
        return l < r;<br>
    }<br>
}
</li>
<li>
binder1st : ����(ù��°) ���ڸ� ����<br>
binder2nd : ������(�ι�°) ���ڸ� ����
</li>
<li>not1 : ���� �������� ����<br>
not2 : ���� �������� ����</li>
</ol>
</details>
