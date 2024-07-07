
# __Concepts library (since C++ 20) https://en.cppreference.com/w/cpp/concepts__

> The concepts library provides definitions of fundamental library concepts that can be used to perform compile-time 
> validation of template arguments and perform function dispatch based on properties of types. 
> These concepts provide a foundation for equational reasoning in programs.

concepts 라이브러리는 컴파일 타임에 템플릿 인자들이 유효한지 확인하고 타입의 특성에 기반한 함수 호출에 사용될 수 있는
기본적인 concepts 들의 정의들을 제공합니다. 이러한 concepts 들은 프로그램에서의 등식 추론을 위한 기반을 제공합니다.
+ function dispatch : 타입에 따라 알맞은 함수를 호출하는 것을 의미함.

> Most concepts in the standard library impose both syntactic and semantic requirements. 
> It is said that a standard concept is _satisfied_ if its syntactic requirements are met, and is _modeled_ if it is satisfied 
> and its semantic requirements (if any) are also met.
 
표준 라이브러리에 있는 대부분의 컨셉들은 구문적, 의미적 요구사항 들을 강요합니다.
구문적 요구사항이 충족되면 표준 컨셉이 _만족_ 되었다고 하고, 의미적 요구사항 까지 만족한다면 _모델화_ 됩니다.

> In general, only the syntactic requirements can be checked by the compiler. If the validity or meaning of a program depends 
> whether a sequence of template arguments models a concept, and the concept is satisfied but not modeled, 
> or if a semantic requirement is not met at the point of use, the program is ill-formed, no diagnostic required.

일반적으로, 구문적 요구사항 만이 컴파일러에 의해 체크가 가능합니다. 만약 프로그램의 유효성이나 의미가 
concept 를 설계하는 일련의 템플릿 인자들에 따라 달라지는 경우, 그리고 concept는 만족되지만 모델화 되지 않거나, 
사용 시점에서 의미적 요구사항을 만족하지 않는다면 프로그램은 잘못된 형태이고, 진단이 요청되지 않습니다.
+ ill-formed : 잘못된 문법, 타입 불일치, undefined behavior 등의 문제로 코드가 잘못된 상태임을 말함.
+ [no diagnostic required](https://en.cppreference.com/w/cpp/language/ndr"cppreference 의 No Diagnostic Required") : 규칙상 ill-formed 이지만 컴파일러가 어떠한 진단이나 에러 메세지를 내놓지 않는 것을 말함.
	+ 이 외에 cppreference 에서 여러 오류들에 대한 명칭은 [여기](https://en.cppreference.com/w/cpp/language/ub) 를 참고

## Equality preservation 동등성 보존

> An expression is equality-preserving if it results in equal outputs given equal inputs, where
> + the inputs consist of its operands (not neccessarily making the expression semantically valid), and
> + the outputs consist of its result and all modifications to the operands by the expression, if any
>
> where, for convenience of wording, its "operands" refer to its largest sub-expressions that consist of an id-expression 
> or invocations of std::move, std::forward, and std::declval.

표현식은 동일한 주어진 입력에 대해 동일한 출력이 나오는 경우 _동등성 보존_ 됩니다

+ 입력이 피연산자로 구성되고(표현식이 의미적으로 유효하게 만드는데 필수가 아닐 수 있음), 
+ 출력이 표현식이 피연산자에 행한 모든 수정과 결과로 구성됨(존재한다면)

편의를 위해서 "피연산자" 는 식별자 혹은 std::move, std::forward, std::declval 의 호출로 구성된 가장 큰 하위 표현식을 말합니다.

> The cv-qualification and value category of each operand is determined by assuming that each template type parameter 
> in its type denotes a cv-unqualified complete non-array object type.

각 연산자의 c-v 한정자와 값 카테고리는 각 템플릿 타입 인자

> Every expression required to be equality preserving is further required to be stable, that is, two evaluations of 
> it with the same input objects must have equal outputs without any explicit intervening modification of those input objects.

> Unless noted otherwise, every expression used in a requires expression of the standard library concepts is required 
> to be equality preserving, and the evaluation of the expression may modify only its non-constant operands. 
> Operands that are constant must not be modified.

> In the standard library, the following concepts are allowed to have non equality-preserving requires expressions:
> + output_iterator
> + indirectly_writable
> + invocable
> + weakly_incrementable
> + range

























[참고](https://www.youtube.com/watch?v=_doRiQS4GS8)