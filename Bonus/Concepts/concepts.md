
# __Concepts library (since C++ 20) https://en.cppreference.com/w/cpp/concepts__

> The concepts library provides definitions of fundamental library concepts that can be used to perform compile-time 
> validation of template arguments and perform function dispatch based on properties of types. 
> These concepts provide a foundation for equational reasoning in programs.
>
>> concepts ���̺귯���� ������ Ÿ�ӿ� ���ø� ���ڵ��� ��ȿ���� Ȯ���ϰ� Ÿ���� Ư���� ����� �Լ� ȣ�⿡ ���� �� �ִ�
>> �⺻���� concepts ���� ���ǵ��� �����մϴ�. �̷��� concepts ���� ���α׷������� ��� �߷��� ���� ����� �����մϴ�.
>> + function dispatch : Ÿ�Կ� ���� �˸��� �Լ��� ȣ���ϴ� ���� �ǹ���.
>
> 
> Most concepts in the standard library impose both syntactic and semantic requirements. 
> It is said that a standard concept is _satisfied_ if its syntactic requirements are met, and is _modeled_ if it is satisfied 
> and its semantic requirements (if any) are also met.
> 
>> ǥ�� ���̺귯���� �ִ� ��κ��� �������� ������, �ǹ��� �䱸���� ���� �����մϴ�.
>> ������ �䱸������ �����Ǹ� ǥ�� ������ _����_�Ǿ��ٰ� �ϰ�, �ǹ��� �䱸���� ���� �����Ѵٸ� _��ȭ_ �˴ϴ�.
>
> In general, only the syntactic requirements can be checked by the compiler. If the validity or meaning of a program depends 
> whether a sequence of template arguments models a concept, and the concept is satisfied but not modeled, 
> or if a semantic requirement is not met at the point of use, the program is ill-formed, no diagnostic required.
>
>> �Ϲ�������, ������ �䱸���� ���� �����Ϸ��� ���� üũ�� �����մϴ�. ���� ���α׷��� ��ȿ���̳� �ǹ̰� 
>> concept �� �����ϴ� �Ϸ��� ���ø� ���ڵ鿡 ���� �޶����� ���, �׸��� concept�� ���������� ��ȭ ���� �ʰų�, 
>> ��� �������� �ǹ��� �䱸������ �������� �ʴ´ٸ� ���α׷��� �߸��� �����̰�, ������ ��û���� �ʽ��ϴ�.
>>> + ill-formed : �߸��� ����, Ÿ�� ����ġ, undefined behavior ���� ������ �ڵ尡 �߸��� �������� ����.
>>> + no diagnostic required : ��Ģ�� ill-formed ������ �����Ϸ��� ��� �����̳� ���� �޼����� ������ �ʴ� ���� ����.
