/*****************************************************************************
 *
 * AM generic facilities
 *
 * released under MIT license
 *
 * 2008-2013 André Müller
 *
 *****************************************************************************/

#ifndef AM_MEMOIZING_FUNCTION_DEMO_H_
#define AM_MEMOIZING_FUNCTION_DEMO_H_

#include <cstdint>
#include <iostream>

#include "memoizing_fn.h"
#include "timer.h"


namespace am {

namespace gen {

namespace example {


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
void memoizing_1()
{

	//make new memoizing_functions with signature double(int,float)
	//can take any callable object with return type double and
	//two int arguments

	//note: automatic dedcution of the call signature seems to be hard,
	//mabye I'll get back to it in the future...

	//with functions
	auto m1 = memoizing_function<double(int,int)>(my_fn);
	std::cout << m1(1,2) << std::endl;
	std::cout << m1(1,2) << std::endl;


	//with function objects
	auto m2 = memoizing_function<double(int,int)>(my_ftor());
	std::cout << m2(1,2) << std::endl;
	std::cout << m2(1,2) << std::endl;


	//with lambdas
	auto m3 = memoizing_function<double(int,int)>(
		[](int x, int y) -> double {return 1.1 * (x+y);}
	);
	std::cout << m3(1,2) << std::endl;
	std::cout << m3(1,2) << std::endl;


	auto m4 = memoizing_function<int(int)>([](int x) {return x*x;});
	std::cout << m4(5) << std::endl;
	std::cout << m4(5) << std::endl;
}



//-------------------------------------------------------------------
void memoizing_2()
{
	auto m = memoizing_function<double(int,int)>(
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
		std::cin >> i >> j;

		if(i > 0 && j > 0) {
			timer t;
			t.start();
			auto x = m(i,j);
			t.stop();
			std::cout << t.seconds() << "  "<< x << std::endl;
		}
	} while(i > 0 && j > 0);
}





}  // namespace example


} //namespace gen
} //namespace am


#endif
