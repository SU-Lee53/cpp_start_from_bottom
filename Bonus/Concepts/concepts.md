
# __Concepts library (since C++ 20) https://en.cppreference.com/w/cpp/concepts__

>> The concepts library provides definitions of fundamental library concepts that can be used to perform compile-time 
>> validation of template arguments and perform function dispatch based on properties of types. 
>> These concepts provide a foundation for equational reasoning in programs.
>> 
>> Most concepts in the standard library impose both syntactic and semantic requirements. 
>> It is said that a standard concept is satisfied if its syntactic requirements are met, and is modeled if it is satisfied 
>> and its semantic requirements (if any) are also met.
>> 
>> In general, only the syntactic requirements can be checked by the compiler. If the validity or meaning of a program depends 
>> whether a sequence of template arguments models a concept, and the concept is satisfied but not modeled, 
>> or if a semantic requirement is not met at the point of use, the program is ill-formed, no diagnostic required.
