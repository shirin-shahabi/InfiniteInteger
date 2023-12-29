# Summary
This Program is defined based on 2 files described in README, Bigint.hpp and demo.cpp, demo.cpp is the test of the class named 'InfiniteInteger' with two objects: sign and a vector named my_int.

Class InfiniteInteger {

    Private Objects: 

    bool sign;
    std::vector<int64_t> my_int;

}

## Infinite precision integer

This is a simple implementation of arithmetic operators on InfiniteIntegers with size greater than system defined operators, in c++ A long long integer contains 64 bits.
A signed long long takes values from -9223372036854775808 to 9223372036854775807.
An unsigned long long takes values from 0 to 18446744073709551615.

The purpose of this program is to handel values greater than this values and define operators for arithmetic calculation.

Method to Handel large Integer:
 
Store the number as a vector of 8-bit unsigned integers, which only take values from 0 to 9, that is, a single decimal digit in base 10.(There are other methods like : Store the number as a string, and implement the operations character by character or a faster implementation: Store the number as a vector of 32-bit or 64-bit unsigned integers - essentially, as a number in "base 232" or "base 264")

## Input and output

### Input & storing format

a vector called *my_int* is used to store an infinite integer, an infinite integer can have input types of Integer, String or Null, Input can accept negative and positive integers or strings. It also handle advanced zero's and white spaces like "0098" or "  890", however using Regex other than number and white spaces(Ex"75^&4") is not allowed.

`InfiniteInteger()`: Default constructor, Initialize with the value Zero.
`InfiniteInteger(int value)`: Constructor with one integer argument, setting value to the defined integer.
`InfiniteInteger(const std::string& str)`: Constructor with one string input. Able to detect and handle '-' as Negative representation of a Number. 

### Output

`std::ostream &operator<<(std::ostream &out, const InfiniteInteger &num)`: output is a string with checking positive/negative; print out one by one number. 

## Operators

### Basic Operations

* `InfiniteInteger operator-() const`: Negation Operator, return the negative value of vector. 
* `InfiniteInteger& operator=(const InfiniteInteger& other)`: Assignment Operator

### Arithmetic Operators

* `InfiniteInteger operator+(const InfiniteInteger& other) const`: Addition Operator (Adding two integers presented as vectors; can be both negative, both positive and one negative and the other one positive)
* `InfiniteInteger& operator+=(const InfiniteInteger& other)`: Addition Assignment Operator 

* `InfiniteInteger operator-(const InfiniteInteger &other)`: Subtraction Operator(Subtracting two integers presented as vectors; can be both negative, both positive and one negative and the other one positive)
* `InfiniteInteger& operator-=(const InfiniteInteger& other)`: Subtraction Assignment Operator 

* `InfiniteInteger operator *(const InfiniteInteger&  other) const`: Multiplication Operator (Summation n times for the current object)
* `InfiniteInteger &operator*=(const InfiniteInteger &other)`: Multiplication Operator Assignment

### Comparison Operators

* `bool operator<(const InfiniteInteger& other)` : Checking for smaller/equal integer, returns true/false .
* `bool operator>(const InfiniteInteger &other)` : Checking for greater integer

* `bool operator>=(const InfiniteInteger &other)` : Checking for smaller/equality or not in comparing two integers, returns true/false respectively.
* `bool operator<=(const InfiniteInteger &other)` : Checking for greater/equality integer

* `bool operator==(const InfiniteInteger& other)` : Equality operator, returns True if two big int are the same(both value and sign).
* `bool operator!=(const InfiniteInteger& other)` : Equality operator, returns False if two big int are the same(both value and sign).

## Helper Functions

1. `operator[](int64_t index)` : Reverse the index for the arithmetic calculation.
Example addition "ab"+"cd" is in order index=1, index=0(first "ones" d+b and then "tens" a+c)
2. `InfiniteInteger subtractOne(const InfiniteInteger &num)`: Subtracting by one from an Infinite Integer Number.
