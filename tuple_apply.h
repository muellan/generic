/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2013 André Müller
 *
 *****************************************************************************/

#ifndef AM_GENERIC_TUPLE_APPLY_H_
#define AM_GENERIC_TUPLE_APPLY_H_

#include <type_traits>
#include <utility>
#include <tuple>

#include "int_sequence.h"


namespace am {

namespace gen {

namespace detail {


/*****************************************************************************
 *
 * @brief helper function exploding the tuple arguments into a function call
 *
 *****************************************************************************/
template<class F, class Tuple, int...ns>
inline auto
apply_helper(F&& f, Tuple&& t, integer_sequence<ns...>)
	-> decltype(f(
		std::forward<
			typename std::tuple_element<ns,typename std::decay<Tuple>::type>::type
		>(std::get<ns>(t)) ... ) )
{
	return f(
			std::forward<
			typename std::tuple_element<ns,typename std::decay<Tuple>::type>::type
		>(std::get<ns>(t)) ... );
}


}  // namespace detail



/*****************************************************************************
 *
 * @brief calls a callable object with a tuple of arguments
 *
 *****************************************************************************/
template<class F, class...T>
inline auto
apply(F&& f, std::tuple<T...>& t)
	-> decltype(detail::apply_helper(std::forward<F>(f),t,ascending_int_sequence<0,sizeof...(T)-1>{}))
{
	return detail::apply_helper(std::forward<F>(f),t,ascending_int_sequence<0,sizeof...(T)-1>{});
}

//-----------------------------------------------------
template<class F, class...T>
inline auto
apply(F&& f, const std::tuple<T...>& t)
	-> decltype(detail::apply_helper(std::forward<F>(f),t,ascending_int_sequence<0,sizeof...(T)-1>{}))
{
	return detail::apply_helper(std::forward<F>(f),t,ascending_int_sequence<0,sizeof...(T)-1>{});
}



}  // namespace gen

}  // namespace am



#endif
