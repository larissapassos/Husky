# Husky - A C++ Functional Library

The functional programming paradigm treats computation as the evaluation of functions, avoiding state changes and mutable data. It intends to eliminate side effects (i.e. changes in state that do not depend on the function inputs), to make it easier to understand and predict the behavior of a program. Several purely functional languages have been developed over the years, with Haskell being the most famous one.

The rise of the functional paradigm has reached classic imperative languages as well. Java and C++, for example, have over the years incorporated some functional features, like the use of lambdas and the emulation of higher-order functions. Husky was developed with the intent of providing C++ programmers with several higher -order functions, using an interface closer to the functional programming style.

Husky does not pretend to replace the STL, but instead extends it. As such, the library supports STL standard containers, barring some exceptions (that will be discussed in the interface design). Several of the library’s functions also can receive lambdas or functors as parameters, and the return types are defined accordingly. We have also used STL functions as much as possible, as they are certainly more optimized and tested than anything we could possibly develop.