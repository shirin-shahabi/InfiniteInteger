/**
 * @file demo.cpp
 * @author Shirin Shahabinejad
 * @brief 
 * @version 0.1
 * @date 2023-12-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <vector>
#include <iostream>

#include "bigint.hpp"

/**
 * @brief testing class of InfiniteInteger
 * @return int 
 */
int main(){
    try
    { 
        //Create Big_integers to check
        /*
        ---- A long long contains 64 bits.
        A signed long long takes values from -9223372036854775808 to 9223372036854775807.
        An unsigned long long takes values from 0 to 18446744073709551615.
        */

        InfiniteInteger a("412"); // 184467440737095516189
        // InfiniteInteger e("-5253");
        InfiniteInteger e("21");
        // InfiniteInteger b("-92233720368547758088");
        // InfiniteInteger c("0");
        // InfiniteInteger d("-92233720368547758088");
        // InfiniteInteger f;
        // InfiniteInteger g(123);
        // InfiniteInteger h("%67333");
        // InfiniteInteger m("00  34");

        std::cout << "a = " << a << "\n";
        // std::cout << "b = " << b << "\n";
        // std::cout << "c = " << c << "\n";
        // std::cout << "d = " << d << "\n";
        std::cout << "e = " << e << "\n";
        // std::cout << "f = " << f << "\n";

        std::cout << "a[0] = " << a[0] << "\n";
        std::cout << "a[1] = " << a[1] << "\n";

        std::cout << "a + e = " << a + e << "\n";
        std::cout << "a += e  " << (a +=e) << "\n";
        // std::cout << "e + c = " << e + c << "\n";

        std::cout << "a - e = " << a - e << "\n";
        std::cout << "a -= e  " << (a -= e) << "\n";
        // std::cout << "e - c = " << e - c << "\n";

        std::cout << "e * a = " << e * a << "\n";
        // std::cout << "e *= a " << (e *= a) << "\n";
        // std::cout << "e * c = " << e * c << "\n";

        std::cout << "a == e -> " << (a == e) << "\n";
        // std::cout << "b == d -> " << (b == d) << "\n";
        std::cout << "a != e -> " << (a != e) << "\n";
        // std::cout << "b != d  ->  " << (b != d) << "\n";

        // std::cout << "-b = ->  " << -b << "\n";
        std::cout << "-e =  -> " << -e << "\n";

        std::cout << "e < a -> " << (e < a) << "\n";
        // std::cout << "b < d  -> " << (b < d) << "\n";

        std::cout << "e <= a -> " << (e <= a) << "\n";
        // std::cout << "b <= d -> " << (b <= d) << "\n";

        std::cout << "e > a -> " << (e > a) << "\n";
        // std::cout << "b > d  -> " << (b > d) << "\n";

        std::cout << "e >= a -> " << (e >= a) << "\n";
        // std::cout << "b >= d -> " << (b >= d) << "\n";

        std::cout << "a = " << a << "\n";
        std::cout << "e = " << e << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
