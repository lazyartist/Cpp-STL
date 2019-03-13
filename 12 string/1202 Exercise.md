
1. 빈 칸 채우기
   1. string 클래스는 문자들을 저장하는 컨텐이너로 C, C++처럼 (   )문자를 요구하지 않기 때문에 C-Style 문자열로 변환하려면 c_str() 멤버 함수를 사용
   2. c_str() 멤버 함수는 (   )를 반환하며 data() 멤버 함수는 (   )를 반환
2. 빈 칸 채우기
   1. string 객체의 찾기 관련 함수가 실패하면 (   )을 반환
   2. string 객체는 vector처럼 메모리 재할당으로 발생하는 성능저하를 막기 위해 예약된 메모리 공간의 크기를 확인하려면 (   ) 멤버 함수를 사용할 수 있고 미리 메모리 공간을 예약하려면 (   ) 멤버 함수를 사용할 수 있다.
3. 다음 함수의 기능
   1. copy()
   2. c_str()
   3. append()
   4. replace()_


<details>
<summary>정답< / summary>
<ol>
<li>
    <ol>
        <li>\0</li>
        <li>\0을 포함한 char*(문자열), \0 포함을 필수로 하지 않는 문자열 반환</li>
    </ol>
</li>
<li>
    <ol>
        <li>string::npos</li>
        <li>capacity, reserve</li>
    </ol>
</li>
<li>
    <ol>
        <li>버퍼(다른 문자열 or 배열)에 \0없는 문자열 복사</li>
        <li>\0을 포함하는 문자열 주소 반환</li>
        <li>문자열 덧붙임</li>
        <li>문자, 문자열 교체</li>
    </ol>
</li>
</ol>
</details>
