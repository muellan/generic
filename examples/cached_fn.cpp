/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2017 André Müller
 *
 *****************************************************************************/

#include <cstdint>
#include <iostream>

#include "../include/cached_fn.h"
#include "timer.h"


using am::gen::cached_function;


//-------------------------------------------------------------------
//some function
double my_fn(int x, int y) {
    return 1.1 * (x + y);
}


//-------------------------------------------------------------------
//some functor
struct my_ftor {
    double operator () (int x, int y) const {
        return 1.1 * (x + y);
    }
};



//-------------------------------------------------------------------
void using_cached_fn_1()
{

    //make new cached_functions with signature double(int,float)
    //can take any callable object with return type double and
    //two int arguments

    //with functions
    auto m1 = cached_function<double(int,int)>(my_fn);
    std::cout << m1(1,2) << std::endl;
    std::cout << m1(1,2) << std::endl;


    //with function objects
    auto m2 = cached_function<double(int,int)>(my_ftor());
    std::cout << m2(1,2) << std::endl;
    std::cout << m2(1,2) << std::endl;


    //with lambdas
    auto m3 = cached_function<double(int,int)>(
        [](int x, int y) -> double {return 1.1 * (x+y);}
    );
    std::cout << m3(1,2) << std::endl;
    std::cout << m3(1,2) << std::endl;


    auto m4 = cached_function<int(int)>([](int x) {return x*x;});
    std::cout << m4(5) << std::endl;
    std::cout << m4(5) << std::endl;

}



//-------------------------------------------------------------------
void using_cached_fn_2()
{
    auto m = cached_function<double(int,int)>(
        [](int a, int b) -> double {
            double x = 0;
            for(int i = 0; i < a; ++i) {
                for(int j = i+1; j < a; ++j) {
                    x += b / double(1 + i + j);
                }
            }
            return x;
        });

    int i,j;
    do {
        i = 0;
        j = 0;
        std::cout << "enter two natural numbers (0 to abort): " << std::flush;
        std::cin >> i >> j;

        if(i > 0 && j > 0) {
            am::timer t;
            t.start();
            auto x = m(i,j);
            t.stop();
            std::cout << t.seconds() << "  "<< x << std::endl;
        }
    } while(i > 0 && j > 0);
}



//-------------------------------------------------------------------
int main()
{
    using_cached_fn_1();
    using_cached_fn_2();
}
