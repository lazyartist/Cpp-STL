1. -

   1. STL 구성 요소에서 객체들을 저장하는 객체를 ( )라 합니다.
   2. 컨테이너의 원소를 순회하고 참조하는 객체를 ( )라 합니다.
   3. 여러 가지 문제 해결을 위한 반복자와 동작하는 함수 템플릿을 ( )라 합니다.

2. -

   1. 컨테이너 원소가 자신만의 삽입 위치를 갖는 것을 ( ) 컨테이너라 합니다.
   2. 컨테이너 원소가 특정 정렬 기준에 의해 자동 정렬된 것을 ( ) 컨테이너라 합니다.

3. -
   1. 배열 기반 컨테이너인 vector와 deque는 ( ) 반복자를 (추가적으로) 제공하며, 그외 모든 STL 컨테이너는 ( ) 반복자를 제공합니다.
   2. ( )은 원소의 순서 있는 집합을 의미하며, 이 ( )은 반복자 쌍(구간)으로 표현합니다.

4. -
   1. 다음 구간 [begin, end), [begin iter), [iter, end)의 순차열을 쓰세요.
      ```
      begin          iter          end
        A       B      C      D     E
      ```

5. 다음중 양방향 반복자가 지원하지 않는 연산자를 고르시오
   1. ++
   2. --
   3. *
   4. []
   5. +=
   6. -=

6. -

   1. STL 컨테이너는 자신이 지원하는 반복자를 반환하기 위한 멤버 함수 ( )와 ( )를 제공하며 각각 시작 원소의 반복자와 끝 표시 반복자입니다.
   2. iter 반복자가 가리키는 원소를 참조하기 위해 ( ) 연산자를 사용합니다.

7. -

   1. ( )는 구성 요소의 인터페이스를 변경합니다.
   2. stack, queue, priority_queue는 ( )이며, reverse_iterator, insert_iterator 등을 ( )라 합니다.
   3. ( )에는 바인더(binder), 부정자(negator) 등이 있습니다.



<details>
    <summary>
	정답
	</summary>
	1. 컨테이너 / 반복자(Iterator) / 알고리즘 <br>
    2. 연속(Sequence) 컨테이너 / 연관(Associate) 컨테이너 <br>
    3. 임의 접근 반복자, 양방향 반복자 / 순차열, 순차열<br>
    4. A, B, C, D / A, B / C, D<br>
    5. 4, 5, 6<br>
    6. begin, end / * <br>
    7. 어댑터 / 컨테이너 어댑터, 반복자 어댑터 / 함수 어댑터<br>
</details>


