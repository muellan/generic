/*****************************************************************************
 *
 * AM generic facilities
 *
 * released under MIT license
 *
 * 2008 - 2014 André Müller
 *
 *****************************************************************************/

#ifndef AM_GENERIC_TESTS_H_
#define AM_GENERIC_TESTS_H_

#include "callable.h"
#include "chain_apply.h"
#include "concat.h"
#include "composition.h"
#include "factories.h"
#include "int_sequence.h"
#include "map_trait.h"
#include "cached_fn.h"
#include "timer.h"
#include "tuple_apply.h"
#include "tuple_hash.h"
#include "tuple_map.h"

#include "cached_fn_demo.h"
#include "tuple_map_demo.h"

using namespace am::gen;


//-------------------------------------------------------------------
int main()
{
    #ifdef USE_DEMOS
        demo::using_cached_fn_1();
        demo::using_cached_fn_2();
        demo::using_for_each();
    #endif
}


#endif
