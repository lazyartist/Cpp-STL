
1. 사용자 함수 객체 구현시 어댑터 적용이 가능하기 위한 단항 함수 객체와 이항 함수 객체의 조건
2. STL의 less 함수 객체와 같은 동작을 하고 어댑터 적용이 가능한 함수 객체 구현
3. binder1st, binder2nd 차이점
4. not1, not2 차이점

<details>
<summary>정답</summary>
<ol>
<li>단항 함수 : argument_type, result_type 정의<br>
이항 함수 : first_argument_type, second_argument_type, result_type 정의</li>
<li>
template(typename T)
struct Less : public binary_function {<br>
    bool operator()(const T &l, const T &r) const {<br>
        return l < r;<br>
    }<br>
}
</li>
<li>
binder1st : 왼쪽(첫번째) 인자를 고정<br>
binder2nd : 오른쪽(두번째) 인자를 고정
</li>
<li>not1 : 단항 조건자의 부정<br>
not2 : 이항 조건자의 부정</li>
</ol>
</details>
