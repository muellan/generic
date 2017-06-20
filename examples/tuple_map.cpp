/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2014 André Müller
 *
 *****************************************************************************/

#include <iostream>

#include "../include/tuple_map.h"


//---------------------------------------------------------------
struct fa {
    template<class T>
    int operator() (T x) const {return (2 * x); }
};

struct fb {
    template<class T>
    double operator() (T x) const{return (3.5 * x); }
};

struct fc {
    int operator() (int x) const {return (2 * x); }
    double operator() (double x) const {return (3.5 * x); }
};

struct fv1 {
    template<class T>
    void operator()(T x) const {std::cout << x << std::endl; }
};

struct fv2 {
    template<class T>
    void operator()(T x) const {std::cout << (2*x) << std::endl; }
};



//-------------------------------------------------------------------
void using_tuple_map()
{
    using namespace am::gen;

    {
        auto xs = std::tuple<int,int,double>{1,1,1.0};
        auto fcxs = map(fc{}, xs);
        std::cout
            << std::get<0>(fcxs) <<' '
            << std::get<1>(fcxs) <<' '
            << std::get<2>(fcxs) << std::endl;
    }

    {
        auto fsx = map(std::tuple<fa,fb,fc>{}, 1);
        std::cout
            << std::get<0>(fsx) <<' '
            << std::get<1>(fsx) <<' '
            << std::get<2>(fsx) << std::endl;
    }

    {
        auto fs = std::make_tuple(
            [](int i){return 2*i; },
            [](int i){return 4*i; },
            [](int i){return 8*i; });

        auto xs = std::make_tuple(1,2,3);
        auto fsxs = zip_map(fs,xs);

        std::cout
            << std::get<0>(fsxs) <<' '
            << std::get<1>(fsxs) <<' '
            << std::get<2>(fsxs) << std::endl;
    }
}



//-------------------------------------------------------------------
void using_for_each()
{
    using namespace am::gen;

    {
        for_each_arg(fv2{}, std::make_tuple(1,2,3.0));
    }

    {
        int i = 1;

        for_each_arg(
            [&i](double x){std::cout << (i*x) << ' '; i *= 2; } ,
            std::make_tuple(1,2,3,4));

        std::cout << std::endl;
    }

    {
        for_each_function(std::tuple<fv1,fv2>{}, 1);
    }

    {
        auto fs = std::make_tuple(
            [](int i){std::cout << 2*i << std::endl; },
            [](int i){std::cout << 4*i << std::endl; },
            [](int i){std::cout << 8*i << std::endl; });

        auto xs = std::make_tuple(1,2,3);

        zip_for_each(fs,xs);
    }
}

int main()
{
    using_tuple_map();
    using_for_each();
}
