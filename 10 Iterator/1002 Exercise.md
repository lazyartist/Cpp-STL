
1. ���� ���� �ݺ���, ����� �ݺ����� ������
2. X::iterator�� X::const_iterator ������
3. ������ ������ ��
   ```
    ��iter, ��riter �� �� 40�� ����Ű�� �ִ�

    10 20 30 40 50 
   ```
    1. *iter�� *riter�� ��
    2. *++iter�� *++riter�� ��
    3. X::iterator iter2 = riter ����?
    4. X::reverse_iterator riter2 = iter ����?
4. merge�� �պ��ϱ����� �ݵ�� �ʿ��� ����?
5. copy()�� ����Ͽ� v�� ���Ҹ� ȭ�鿡 ����ϱ�

<details>
<summary>����< / summary>
<ol>
<li>
    <ul>
        <li>
        ���� ���� �ݺ��� : �迭 ��� �����̳ʷμ� ���Ҹ� ���������� �������� �ʾƵ� �ȴ�.<br>
        [], +=, -=, +, -, ++, -- ���� ���� ����
        </li>
        <li>
        ����� ���� �ݺ��� : ��� ��� �����̳ʷμ� ���Ҹ� ���������� �����ؾߵȴ�.<br>
        ++, -- ���� ����
        </li>
    </ul>
<li>
X::iterator : �ݺ��ڰ� ����Ű�� �� ���� ����<br>
X::const_iterator : �ݺ��ڰ� ����Ű�� �� ���� �Ұ�
</li>
<li>
    <ol>
        <li>40, 30</li>
        <li>50, 20</li>
        <li>�Ұ�</li>
        <li>����</li>
    </ol>
</li>
<li>�����̳ʸ� �����Ѵ�.</li>
<li>copy(v.begin(), v.end(), ostream_iterator<int>(cout));</li>
</ol>
</details>
