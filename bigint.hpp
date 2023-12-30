
/**
 * This Program is defined based on 2 files described in README, Bigint.hpp and demo.cpp;
 * @brief bigint.hpp is including A class definition containing constructors and operators
Method to Handel large number: Store the number as a vector of 8-bit unsigned integers,
which only take values from 0 to 9, that is, a single decimal digit in base 10.
* @author Shirin Shahabinejad
 */


#pragma once
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>


class InfiniteInteger{
    public:
    // Default Constructor
    InfiniteInteger() : sign(true), my_int(1, 0) {}

    // Initial_64-bit integer value Constructor
    InfiniteInteger(int64_t value)
    {
        sign = (value < 0) ? (value = -value, false) : true; // Making sure sign is always positive

        while (value != 0)
        {
            my_int.push_back(value % 10);
            value /= 10;
        }
    }

    // constructor that takes a string of digits and converts it to an arbitrary-precision integer.
    InfiniteInteger(const std::string &str){
        size_t start = 0;

        // Skip leading whitespaces and zeroes
        while (start < str.size() && (isspace(str[start]) || str[start] == '0'))
        {
            start++;
        }

        // Empty string
        if (start == str.size()) {
            sign = true;
            my_int.push_back(0);
            return;
        }


        //Check if string is valid
        for (size_t i = start; i < str.size(); i++){
            if (i == 0 && str[i] == '-'){
                continue;
            }
            

            if(str[i] < '0' || str[i] > '9'){
                throw std::invalid_argument("Invalid String!");
            }
        }
        
        // Signed Value

        sign = (str[start] != '-');

        for (int64_t i = int64_t(str.size()) - 1; i >= int64_t(start) + (sign ? 0 : 1); i--)
        {
            my_int.push_back(str[uint64_t(i)] - '0');
        }
    }

    // Explicitly define the copy constructor
    InfiniteInteger(const InfiniteInteger& other) : sign(other.sign), my_int(other.my_int) {}

    // Part 2 : Defining 'Negation', 'Assignment', 'Addition', 'Subtraction', 'Multiplication', 'Comparison', 'Insertion'

    /**
     * @brief     Reverse Index_wise operator []
     * Example addition "ab"+"cd" is in order index=1, index=0(first "ones" d+b and then "tens" a+c)
     * @param index
     * @return int64_t
     * References : https://en.cppreference.com/w/cpp/language/operators 
     * & https://cplusplus.com/reference/vector/vector/operator[]/
     */

    int64_t operator[](size_t index) const
    {

        // Check if index is valid (out of range)
        if (index >= my_int.size())
        {
            throw std::invalid_argument("ERROR! Index is out of Range!");
        }

        // Calculate the reverse index
        index = my_int.size() - index - 1;

        // Return the element at the reverse index
        return my_int[index];
    }

    // Negation Operator
    InfiniteInteger operator-() const
    {
        InfiniteInteger result = *this; 
        result.sign = !this->sign;
        return result;
    }

    // Assignment Operator
    InfiniteInteger& operator=(const InfiniteInteger& other){
        if(this == &other) {
            return *this;
        }

        this->my_int= other.my_int;
        this->sign = other.sign;

        return *this;
    }

    /**
     * @brief Addition Operator
    https://www.delftstack.com/howto/cpp/cpp-biginteger/
    https://www.geeksforgeeks.org/bigint-big-integers-in-c-with-example/
    https://www.tutorialspoint.com/sum-of-two-large-numbers-in-cplusplus#:~:text=Step%201%3A%20loop%20from%20n,Step%203%3A%20return%20sum.
    Addition Scenarios : 2 numbers are Negative, One Negative + One Positive(Using Operator-),
                         and 2 numbers are positive
     * @param other
     * @return InfiniteInteger
     */
    InfiniteInteger operator+(const InfiniteInteger& other) const {

        // Adding two negative numbers
        if(!sign && !other.sign) {
            InfiniteInteger result = *this;
            result.sign = true; //Temporary Positive
            InfiniteInteger otherTemp = other;
            otherTemp.sign = true;
            result = result + otherTemp;
            result.sign = false;
            return result;
        }


        //Adding one Negative + one Positive
        if (sign != other.sign){
            if(sign) {
                return *this - (-other);
            }else{
                return other - (-*this);
            }
            
        }

        // Adding two positive numbers with Potential overflow

        InfiniteInteger result;
        result.sign = sign;
        result.my_int.resize(std::max(my_int.size(), other.my_int.size()));


        int64_t carry = 0;
        for(size_t i =0; i < result.my_int.size(); i++){
            int64_t sum = carry;
            if (i < my_int.size()){
                sum += my_int[i];
            }
            if (i < other.my_int.size()) {
                sum += other.my_int[i];
            }

            result.my_int[i] = sum % 10;
            carry = sum / 10;
            
        }

        if(carry != 0) {
            result.my_int.push_back(carry);
        }

        return result;


    }


    //Addition Assignment Operator

    InfiniteInteger& operator+=(const InfiniteInteger& other){
        *this = *this + other;
        return *this;
    }

    /**
     * @brief  Subtraction Operator
     * @param other
     * @return InfiniteInteger
     * // https: // www.geeksforgeeks.org/difference-of-two-large-numbers/
       // https: // cplusplus.com/forum/beginner/244579/
     */

    InfiniteInteger operator-(const InfiniteInteger &other) const
    {
        InfiniteInteger result;
        // Subtracting one negative and one positive (convert to addition)
        if (sign != other.sign)
        {
            InfiniteInteger temp = other;
            temp.sign = !other.sign;
            return *this + temp;
        }
        else if (!sign && !other.sign)
        {
            // Subtracting two negative numbers
            return (-other) - (-*this);
        }

        // Subtracting two positive numbers
        result.sign = *this >= other;
        const InfiniteInteger &larger = result.sign ? *this : other;
        const InfiniteInteger &smaller = result.sign ? other : *this;

        result.my_int.resize(larger.my_int.size());
        int64_t borrow = 0;
        for (size_t i = 0; i < larger.my_int.size(); ++i)
        {
            int64_t diff = larger.my_int[i] - (i < smaller.my_int.size() ? smaller.my_int[i] : 0) - borrow;
            borrow = (diff < 0) ? 1 : 0;
            result.my_int[i] = (diff + 10) % 10;
        }

        return result;
    }

    InfiniteInteger& operator-=(const InfiniteInteger& other) {
        *this = *this - other;
        return *this;
    }

    
    /**
     * @brief Multiplication operator
     * 
     * @param other 
     * @return InfiniteInteger 
     */
    InfiniteInteger operator*(const InfiniteInteger &other) 
    {
        InfiniteInteger result;
        result.sign = sign == other.sign;
        result.my_int.resize(my_int.size() + other.my_int.size(), 0); // static vector 

        for (size_t i = 0; i < my_int.size(); ++i)
        {
            for (size_t j = 0; j < other.my_int.size(); ++j)
            {
                result.my_int[i + j] += my_int[i] * other.my_int[j];
                result.my_int[i + j + 1] += result.my_int[i + j] / 10;
                result.my_int[i + j] %= 10;
            }
        }

        return result;
    }

    InfiniteInteger &operator*=(const InfiniteInteger &other)
    {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Comparison Operators
     * https://brevzin.github.io/c++/2019/07/28/comparisons-cpp20/
     * @param other
     * @return true
     * @return false
     */
    // Comparison operators
    bool operator<(const InfiniteInteger &other) const
    {
        // Scenario 1: Different Signs - a negative and a positive number
        if (sign != other.sign)
        {
            return !sign;
        }
        // Scenario 2: both integers have a same Sign
        // First Comparing the sizes
        if (my_int.size() != other.my_int.size())
        {
            return my_int.size() < other.my_int.size();
        }
        // Compare Digits
        for (int64_t i = int64_t(my_int.size()) - 1; i >= 0; i--)
        {
            if (my_int[uint64_t(i)] != other.my_int[uint64_t(i)])
            {
                return my_int[uint64_t(i)] < other.my_int[uint64_t(i)];
            }
        }

        // Two numbers are Equal

        return false;
    }

    bool operator==(const InfiniteInteger& other) const{
        return my_int == other.my_int;
    }

    bool operator!=(const InfiniteInteger& other) const{
        return !(my_int == other.my_int);
    }

    bool operator>(const InfiniteInteger &other) const { return other < *this; }

    bool operator<=(const InfiniteInteger &other) const
    {
        return !(other < *this);
    }

    bool operator>=(const InfiniteInteger &other) const
    {
        return !(*this < other);
    }

private:

    bool sign;
    std::vector<int64_t> my_int;

    // Declare the operator<< as a friend of this class
    friend std::ostream &operator<<(std::ostream &out, const InfiniteInteger &num);
    friend InfiniteInteger subtractOne(const InfiniteInteger &num);
};



/**
 * @brief Cout Operator for handling Custom Infinite precision Integer, Printing Operator.
 * @param out 
 * @param num 
 * @return std::ostream& 
 */

std::ostream &operator<<(std::ostream &out, const InfiniteInteger &num)
{ 
    if (!num.sign)
    {
        out << '-';
    }
    for (int64_t i = int64_t(num.my_int.size()) - 1; i >= 0; i--)
    {
        out << num.my_int[uint64_t(i)];
    }
    return out;
}

// Helper function to subtract 1 from an InfiniteInteger
InfiniteInteger subtractOne(const InfiniteInteger &num)
{
    InfiniteInteger one;
    one.my_int = {1};
    one.sign = true;
    return num - one;
}