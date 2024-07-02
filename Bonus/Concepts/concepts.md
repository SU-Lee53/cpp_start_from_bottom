
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
> It is said that a standard concept is satisfied if its syntactic requirements are met, and is modeled if it is satisfied 
> and its semantic requirements (if any) are also met.
> 
> In general, only the syntactic requirements can be checked by the compiler. If the validity or meaning of a program depends 
> whether a sequence of template arguments models a concept, and the concept is satisfied but not modeled, 
> or if a semantic requirement is not met at the point of use, the program is ill-formed, no diagnostic required.
