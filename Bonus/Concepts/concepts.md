
# __Concepts library (since C++ 20) https://en.cppreference.com/w/cpp/concepts__

> The concepts library provides definitions of fundamental library concepts that can be used to perform compile-time 
> validation of template arguments and perform function dispatch based on properties of types. 
> These concepts provide a foundation for equational reasoning in programs.
>
>> concepts 라이브러리는 컴파일 타임에 템플릿 인자들이 유효한지 확인하고 타입의 특성에 기반한 함수 호출에 사용될 수 있는
>> 기본적인 concepts 들의 정의들을 제공합니다. 이러한 concepts 들은 프로그램에서의 등식 추론을 위한 기반을 제공합니다.
>> + function dispatch : 타입에 따라 알맞은 함수를 호출하는 것을 의미함.
>
> 
> Most concepts in the standard library impose both syntactic and semantic requirements. 
> It is said that a standard concept is _satisfied_ if its syntactic requirements are met, and is _modeled_ if it is satisfied 
> and its semantic requirements (if any) are also met.
> 
>> 표준 라이브러리에 있는 대부분의 컨셉들은 구문적, 의미적 요구사항 들을 강요합니다.
>> 구문적 요구사항이 충족되면 표준 컨셉이 _만족_되었다고 하고, 의미적 요구사할 까지 만족한다면 _모델화_ 됩니다.
>
> In general, only the syntactic requirements can be checked by the compiler. If the validity or meaning of a program depends 
> whether a sequence of template arguments models a concept, and the concept is satisfied but not modeled, 
> or if a semantic requirement is not met at the point of use, the program is ill-formed, no diagnostic required.
>
>> 일반적으로, 구문적 요구사항 만이 컴파일러에 의해 체크가 가능합니다. 만약 프로그램의 유효성이나 의미가 
>> concept 를 설계하는 일련의 템플릿 인자들에 따라 달라지는 경우, 그리고 concept는 만족되지만 모델화 되지 않거나, 
>> 사용 시점에서 의미적 요구사항을 만족하지 않는다면 프로그램은 잘못된 형태이고, 진단이 요청되지 않습니다.
>>> + ill-formed : 잘못된 문법, 타입 불일치, undefined behavior 등의 문제로 코드가 잘못된 상태임을 말함.
>>> + no diagnostic required : 규칙상 ill-formed 이지만 컴파일러가 어떠한 진단이나 에러 메세지를 내놓지 않는 것을 말함.
