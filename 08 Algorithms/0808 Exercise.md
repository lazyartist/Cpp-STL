
1. -
   1. 구간 [b,e)에서 찾기 관련 알고리즘이 원소를 발견하지 못했다면 알고리즘은 (   ) 반복자를 반환
   2. bool 형식을 반환하는 합수, 함수 포인터, 함수 객체를 (   )라 한다
   3. 모든 알고리즘은 삽입(insert) 모드가 아닌 (   ) 모드로 작동한다.
2. vector의 원소를 제거
    ```
    전 : 1   2   3   4   5
    후 : 1   2   3   4
    ```
3. vector의 일부 원소를 뒤집기
    ```
    전 : 1   2   3   4   5   6
    후 : 3   2   1   4   5   6
    ```
4. vector를 정렬하고 모든 원소가 유일하게 하기
5. v1의 원소를 v2에 복사하고 v3에 출력하기
6. v1과 v2를 v3로 병합하기
7. 전 벡터를 후 벡터로 만들기
    ```
    전 : 1   2   3   4   5   6
    후 : 4   5   6   1   2   3
    ```
8. v1과 v2의 합집합을 v3에 출력하기


<details>
<summary>정답</summary>
<ol>
<li>
    <ol>
    <li>끝 표시(past-the-end) 반복자</li>
    <li>predicate(조건자)</li>
    <li>덮어쓰기(overwrite> 모드</li>
    </ol>
</li>
<li>erase(find(v.begin(), v.end(), 5));</li>
<li>reverse(v.begin(), v.begin()+3);</li>
<li>
    sort(v.begin(), v.end()); // 정렬<br>
    iter = unique(v.begin(), v.end()); // 중복 제거<br>
    v.erase(iter, v.end()); // 물리적 제거<br>
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


