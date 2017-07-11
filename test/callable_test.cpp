/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2017 André Müller
 *
 *****************************************************************************/

#include <iostream>

#include "../include/callable.h"


//-------------------------------------------------------------------
struct A {};
struct B {};

void f1(double, float&, const int&) { }

struct f3_t {
    int operator()(double, int) {return 0; }
};


//-------------------------------------------------------------------
template<class F>
bool gen_callable_test_1(F&&) {
    return am::gen::is_callable<F,void,double,float&,int>::value;
}


template<class F>
bool gen_callable_test_2(F&&) {
    return am::gen::is_callable<F,const A&,B&,A&>::value;
}


template<class F>
bool gen_callable_test_3(F&&) {
    return am::gen::is_callable<F,int,double,int>::value;
}



//-------------------------------------------------------------------
int main()
{
    auto f2 = [] (const B&, A& a) -> const A& {return a; };

    auto f3 = f3_t{};

    const bool success =
         gen_callable_test_1(f1) &&
        !gen_callable_test_1(f2) &&
        !gen_callable_test_1(f3) &&

        !gen_callable_test_2(f1) &&
         gen_callable_test_2(f2) &&
        !gen_callable_test_2(f3) &&

        !gen_callable_test_3(f1) &&
        !gen_callable_test_3(f2) &&
         gen_callable_test_3(f3);

    if(!success) {
        std::cerr << "gen::is_callable";
        return 1;
    }
}
