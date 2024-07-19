# PreprocessorCounterMacro
A simple ``__COUNTER__``-like preprocessor macro implementation written in C.

This code offers the implementation of the ``MY_COUNTER`` macro and a code generator for generating customized versions of said macro.

It allows the user to obtain a similar behaviour to that of the non standard ``__COUNTER__`` macro in standard C.

This project exists out of the need of having a macro with the behaviour of ``__COUNTER__`` in an environment where the compiler in use did not offer such an extension, thus requiring a fully standard C implementation.
