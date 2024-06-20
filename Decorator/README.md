# Pattern Decorator

This is an implementation, in C, of the Decorator pattern, 
as described by [Refactoring Guru](https://refactoring.guru/design-patterns/decorator "Refactoring Guru"),
and with the same problematic of notifying clients through different media.

I had to use several advanced C features, such as function pointers or unions. 
I'll eventually describe the implementation of the concept in this file.

Note that it is only emulating the behavior of OOP, and that in that special case, 
it would have been more concise, readable, simple, less repetitive, and, in a word, better,
to simply use a function pointer in a struct.