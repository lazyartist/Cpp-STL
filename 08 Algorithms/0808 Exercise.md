
1. -
   1. ���� [b,e)���� ã�� ���� �˰����� ���Ҹ� �߰����� ���ߴٸ� �˰����� (   ) �ݺ��ڸ� ��ȯ
   2. bool ������ ��ȯ�ϴ� �ռ�, �Լ� ������, �Լ� ��ü�� (   )�� �Ѵ�
   3. ��� �˰����� ����(insert) ��尡 �ƴ� (   ) ���� �۵��Ѵ�.
2. vector�� ���Ҹ� ����
    ```
    �� : 1   2   3   4   5
    �� : 1   2   3   4
    ```
3. vector�� �Ϻ� ���Ҹ� ������
    ```
    �� : 1   2   3   4   5   6
    �� : 3   2   1   4   5   6
    ```
4. vector�� �����ϰ� ��� ���Ұ� �����ϰ� �ϱ�
5. v1�� ���Ҹ� v2�� �����ϰ� v3�� ����ϱ�
6. v1�� v2�� v3�� �����ϱ�
7. �� ���͸� �� ���ͷ� �����
    ```
    �� : 1   2   3   4   5   6
    �� : 4   5   6   1   2   3
    ```
8. v1�� v2�� �������� v3�� ����ϱ�


<details>
<summary>����</summary>
<ol>
<li>
    <ol>
    <li>�� ǥ��(past-the-end) �ݺ���</li>
    <li>predicate(������)</li>
    <li>�����(overwrite> ���</li>
    </ol>
</li>
<li>erase(find(v.begin(), v.end(), 5));</li>
<li>reverse(v.begin(), v.begin()+3);</li>
<li>
    sort(v.begin(), v.end()); // ����<br>
    iter = unique(v.begin(), v.end()); // �ߺ� ����<br>
    v.erase(iter, v.end()); // ������ ����<br>
</li>
<li>transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), [](int&l, int&r) -> int {return l+r;});</li>
<li>
sort(v1.begin(), v1.end());<br>
sort(v2.begin(), v2.end());<br>
merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
</li>
<li>rotate(v.begin(), v.begin()+3, v.end());</li>
<li>
sort(v1.begin(), v1.end());<br>
sort(v2.begin(), v2.end());<br>
set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
</li>
</ol>
</details>


