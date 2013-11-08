/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2013 André Müller
 *
 *****************************************************************************/

#ifdef AM_USE_DEMOS

#include <iostream>

#include "tuple_map.h"
#include "tuple_map_demo.h"


namespace am {

namespace gen {

namespace demo {


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
	using std::get;

	auto xs = std::tuple<int,int,double>{1,1,1.0};
	auto fcxs = map(fc{}, xs);
	std::cout << get<0>(fcxs) <<' '<< get<1>(fcxs) <<' '<< get<2>(fcxs) << std::endl;

	auto fsx = map(std::tuple<fa,fb,fc>{}, 1);
	std::cout << get<0>(fsx) <<' '<< get<1>(fsx) <<' '<< get<2>(fsx) << std::endl;
}



//-------------------------------------------------------------------
void using_tuple_scan()
{

	scan(fv2{}, std::make_tuple(1,2,3.0));

	int i = 1;

	scan(
		[&i](double x){std::cout << (i*x) << ' '; i *= 2; } ,
		std::make_tuple(1,2,3,4));

	std::cout << std::endl;

	scan(std::tuple<fv1,fv2>{}, 1);
}



}  // namespace demo

}  // namespace gen

}  // namespace am

#endif
