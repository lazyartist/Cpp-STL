- 보기
   1. 시퀸스 컨테이너
   2. sort(), splice() 멤버 함수를 제공
   3. 배열 기반 컨테이너
   4. 컨테이너 앞, 뒤로 추가/제거가 가능
   5. 임의 접근 반복자를 제공
   6. reserve() 멤버 함수를 제공
   7. 빠른 시간(상수 시간)에 원소를 삽입, 삭제할 수 있슴


1. 보기 중 vector 컨테이너의 특징을 고르시오.

2. 보기 중 deque 컨테이너의 특징을 고르시오.
3. 보기 중 list 컨테이너의 특징을 고르시오.
4. 다음 iter가 가리키는 위치에 100 원소를 삽입(insert)하면 vector 컨테이너는 어떤 순차열을 가질까요?
   ```
          iter
   10      20      30      40      50
   ```
5. size와 capacity가 모두 5인 vector 컨테이너에 reserve(10)를 사용하여 메모리를 10으로 확장하면 다음 size와 capacity는 얼마일까요?
6. size와 capacity가 모두 5인 vector 컨테이너에 clear() 멤버 함수를 사용했다면 다음 size와 capacity는 얼마일까요? 또한, size, capacity를 모두 0으로 만드려면 어떻게 해야 할까요?
7. vector의 [] 연산자와 at()의 공통점과 차이점
8. vector와 deque의 차이점
9. vector와 list의 차이점
10. --
    1. vector, list가 제공하는 반복자
    2. vector, list 공통점
    3. vector, list의 erase() 차이점
    4. vector, list의 insert() 차이점
11. list가 sort() 멤버함수를 제공하는 이유
12. list의 insert(), splice() 멤버함수의 차이점


<details>
<summary>정답</summary>
<ol>
<li> 1, 3, 5, 6 </li>
<li> 1, 3, 4, 5 </li>
<li> 1, 2, 4, 7 </li>
<li> 10 100 20 30 40 50<br>
    itet는 20을 가리킴<br> </li>
<li> size : 5, capacity : 10 </li>
<li> clear -> size : 5, capacity : 5<br>
    capacity를 0으로 만드려면 capacity가 0인 vector를 만들어 서로 swap 시킨다.<br>
    v.swap(vector<int>());</li>
<li> 공통점 : 임의 점근 가능, 차이점 : at은 범위 유효성 검사를 하고 []는 하지 않는다.(boundary check) </li>
<li> deque은 여러 메모리 블록에 원소들이 저장되고 앞 뒤로 메모리 블록을 할당하여 확장할 수 있기 때문에 원소를 앞, 뒤로 추가할 수 있다. </li>
<li> vector는 배열 기반, list는 노드 기반 </li>
<li>
    <ol>
        <li> vector : 임의 접근 반복자 <br> list : 양방향 반복자 </li>
        <li> 시퀸스 컨테이너(모든 원소의 상대적 순서가 지켜진다) </li>
        <li> vector : 원소 삭제 후 다음 원소들을 앞으로 땡긴다.<br> list : 원소 삭제 후 링크만 재연결 해준다.</li>
        <li> vector : 원소 삽입 후 다음 원소들을 뒤로 민다.<br>list : 원소 삽입 후 링크만 재연결 해준다. </li>
    </ol>
</li>
<li> 알고리즘에서 제공하는 정렬은 모두 연속 메모리 기반의 컨테이너인 vector와 deque에만 동작하며 list에서는 작동하지 않기 때문에 자체 sort() 멤버 함수를 제공한다.</li>
<li> insert : 원본에 변화없이 삽입한다. <br> splice : 원본의 원소들을 잘라내어 대상에 붙인다. </li>
</ol>
</details>


