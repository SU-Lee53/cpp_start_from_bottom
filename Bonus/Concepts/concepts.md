
# __Concepts library (since C++ 20) https://en.cppreference.com/w/cpp/concepts__

> The concepts library provides definitions of fundamental library concepts that can be used to perform compile-time 
> validation of template arguments and perform function dispatch based on properties of types. 
> These concepts provide a foundation for equational reasoning in programs.

concepts ���̺귯���� ������ Ÿ�ӿ� ���ø� ���ڵ��� ��ȿ���� Ȯ���ϰ� Ÿ���� Ư���� ����� �Լ� ȣ�⿡ ���� �� �ִ�
�⺻���� concepts ���� ���ǵ��� �����մϴ�. �̷��� concepts ���� ���α׷������� ��� �߷��� ���� ����� �����մϴ�.
+ function dispatch : Ÿ�Կ� ���� �˸��� �Լ��� ȣ���ϴ� ���� �ǹ���.

> Most concepts in the standard library impose both syntactic and semantic requirements. 
> It is said that a standard concept is _satisfied_ if its syntactic requirements are met, and is _modeled_ if it is satisfied 
> and its semantic requirements (if any) are also met.
 
ǥ�� ���̺귯���� �ִ� ��κ��� �������� ������, �ǹ��� �䱸���� ���� �����մϴ�.
������ �䱸������ �����Ǹ� ǥ�� ������ _����_ �Ǿ��ٰ� �ϰ�, �ǹ��� �䱸���� ���� �����Ѵٸ� _��ȭ_ �˴ϴ�.

> In general, only the syntactic requirements can be checked by the compiler. If the validity or meaning of a program depends 
> whether a sequence of template arguments models a concept, and the concept is satisfied but not modeled, 
> or if a semantic requirement is not met at the point of use, the program is ill-formed, no diagnostic required.

�Ϲ�������, ������ �䱸���� ���� �����Ϸ��� ���� üũ�� �����մϴ�. ���� ���α׷��� ��ȿ���̳� �ǹ̰� 
concept �� �����ϴ� �Ϸ��� ���ø� ���ڵ鿡 ���� �޶����� ���, �׸��� concept�� ���������� ��ȭ ���� �ʰų�, 
��� �������� �ǹ��� �䱸������ �������� �ʴ´ٸ� ���α׷��� �߸��� �����̰�, ������ ��û���� �ʽ��ϴ�.
+ ill-formed : �߸��� ����, Ÿ�� ����ġ, undefined behavior ���� ������ �ڵ尡 �߸��� �������� ����.
+ [no diagnostic required](https://en.cppreference.com/w/cpp/language/ndr"cppreference �� No Diagnostic Required") : ��Ģ�� ill-formed ������ �����Ϸ��� ��� �����̳� ���� �޼����� ������ �ʴ� ���� ����.
	+ �� �ܿ� cppreference ���� ���� �����鿡 ���� ��Ī�� [����](https://en.cppreference.com/w/cpp/language/ub) �� ����

## Equality preservation ��� ����

> An expression is equality-preserving if it results in equal outputs given equal inputs, where
> + the inputs consist of its operands (not neccessarily making the expression semantically valid), and
> + the outputs consist of its result and all modifications to the operands by the expression, if any
>
> where, for convenience of wording, its "operands" refer to its largest sub-expressions that consist of an id-expression 
> or invocations of std::move, std::forward, and std::declval.

ǥ������ ������ �־��� �Է¿� ���� ������ ����� ������ ��� _��� ����_ �˴ϴ�

+ �Է��� �ǿ����ڷ� �����ǰ�(ǥ������ �ǹ������� ��ȿ�ϰ� ����µ� �ʼ��� �ƴ� �� ����), 
+ ����� ǥ������ �ǿ����ڿ� ���� ��� ������ ����� ������(�����Ѵٸ�)

���Ǹ� ���ؼ� "�ǿ�����" �� �ĺ��� Ȥ�� std::move, std::forward, std::declval �� ȣ��� ������ ���� ū ���� ǥ������ ���մϴ�.

> The cv-qualification and value category of each operand is determined by assuming that each template type parameter 
> in its type denotes a cv-unqualified complete non-array object type.

�� �������� c-v �����ڿ� �� ī�װ��� �� ���ø� Ÿ�� ����

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

























[����](https://www.youtube.com/watch?v=_doRiQS4GS8)