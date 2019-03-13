
1. 임의 접근 반복자, 양방향 반복자의 차이점
2. X::iterator와 X::const_iterator 차이점
3. 다음의 물음에 답
   ```
    정iter, 역riter 둘 다 40을 가리키고 있다

    10 20 30 40 50 
   ```
    1. *iter와 *riter의 값
    2. *++iter와 *++riter의 값
    3. X::iterator iter2 = riter 가능?
    4. X::reverse_iterator riter2 = iter 가능?
4. merge로 합병하기전에 반드시 필요한 것은?
5. copy()를 사용하여 v의 원소를 화면에 출력하기

<details>
<summary>정답< / summary>
<ol>
<li>
    <ul>
        <li>
        임의 접근 반복자 : 배열 기반 컨테이너로서 원소를 순차적으로 접근하지 않아도 된다.<br>
        [], +=, -=, +, -, ++, -- 등의 연산 가능
        </li>
        <li>
        양방향 접근 반복자 : 노드 기반 컨테이너로서 원소를 순차적으로 접근해야된다.<br>
        ++, -- 연산 가능
        </li>
    </ul>
<li>
X::iterator : 반복자가 가리키는 값 변경 가능<br>
X::const_iterator : 반복자가 가리키는 값 변경 불가
</li>
<li>
    <ol>
        <li>40, 30</li>
        <li>50, 20</li>
        <li>불가</li>
        <li>가능</li>
    </ol>
</li>
<li>컨테이너를 정렬한다.</li>
<li>copy(v.begin(), v.end(), ostream_iterator<int>(cout));</li>
</ol>
</details>
