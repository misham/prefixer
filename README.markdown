# First Thing

To build the program, run _make help_ for possible targets.

The program uses __prefixer__ wrapper script for those
who do not have and don't want to (or cannot) install Boost library.
The script will set the LD_LIBRARY_PATH properly when running
the program with the locally built Boost library.

If you have Boost > 1.38.0 installed, all you need to do
is run _make_.  See Requirements section below for more info on Boost.

Tests are provided with the library and can be built with __make tests__.
This will also run the tests. You can always run __make run_tests__ to
execute the tests again.

There are also 6 examples provided to test with. They are:

  1. 3 * x - 4 + ( 2 * y ) / z
  2. 3 * x + ( 9 + y ) / 4
  3. 3 * 3 + ( 4 + x ) / y
  4. 3 * ( 2 + 4 ) / 2
  5. 3 * ( 2 + 4 ) / x
  6. 3

Run the program with _--help_ option for possible paramaters the program
accepts.

# Requirements

The program uses Boost library from http://www.boost.org.

You can use the library that came with your distribution as long as
the version is > 1.38.0

The library is also provided with the source and can be built on your
system.  Run _make help_ for instructions on how to build.

# Problem
Write a program that given an infix arithmetic expression, outputs a prefix
version (the output order is unimportant as long as it evaluates to the same
result).

For example:

    3 becomes 3
    1 + 1 becomes (+ 1 1)
    2 * 5 + 1 becomes (+ (* 2 5) 1)
    2 * ( 5 + 1 ) becomes (* 2 (+ 5 1))
    3 * x + ( 9 + y ) / 4 becomes (+ (* 3 x) (/ (+ 9 y) 4))

The format of the input expression is highly restricted. All values are either
single alphabetic characters or positive integers. All operators, including
( and ), are always separated by at least one space from other values or operators.

You should respect operator precedence, so 3 + 5 * 4 should always be parsed as 23, not 32.

Your program should be run from the command line as

prefixer FILE_NAME

where FILE_NAME is the name of a file containing an infix expression.

Final step: Reduce all expressions as much as possible before you output them.
This behavior should be triggered by a -r flag.

