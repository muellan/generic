/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2013 André Müller
 *
 *****************************************************************************/

#ifndef AM_GENERIC_TUPLE_MAP_H_
#define AM_GENERIC_TUPLE_MAP_H_

#include <type_traits>
#include <utility>
#include <tuple>

#include "int_sequence.h"


namespace am {

namespace gen {

namespace detail {


/*****************************************************************************
 *
 * @brief helps to map a function to tuple elements
 *
 *****************************************************************************/
template<class F, class Tuple, int...ns>
inline auto
map_helper(F&& f, const Tuple& xs, integer_sequence<ns...>)
	-> std::tuple<typename std::decay<decltype(f(std::get<ns>(xs)))>::type...>
{
	return std::tuple<
		typename std::decay<decltype(f(std::get<ns>(xs)))>::type...>
			{f(std::get<ns>(xs))...};
}




/*****************************************************************************
 *
 * @brief helps to map a tuple of functions to some arguments
 *
 *****************************************************************************/
template<class Tuple, int... ns, class... Args>
inline auto
mapfs_helper(Tuple&& fs, integer_sequence<ns...>, Args&&... args)
	-> 	std::tuple<typename std::decay<decltype(
			std::get<ns>(fs)(args...))
		>::type...>
{
	return std::tuple<
		typename std::decay<decltype(std::get<ns>(fs)(args...))>::type...>
			{std::get<ns>(fs)(args...)...};
}




/*****************************************************************************
 *
 * @brief helps to map a tuple of functions to some arguments
 *
 *****************************************************************************/
template<class F, class Tuple, int...ns>
inline void
scan_helper(F&&, const Tuple&, integer_sequence<ns...>)
{}

//-----------------------------------------------------
template<class F, class Tuple, int n, int...ns>
inline void
scan_helper(F&& f, const Tuple& xs, integer_sequence<n,ns...>)
{
	f(std::get<n>(xs));
	scan_helper(std::forward<F>(f), xs, integer_sequence<ns...>{});
}




/*****************************************************************************
 *
 * @brief helps to map a tuple of functions to some arguments
 *
 *****************************************************************************/
template<class Tuple, class... Args>
inline void
scanfs_helper(Tuple&&, integer_sequence<>, Args&&...)
{}

//-----------------------------------------------------
template<class Tuple, int n, int... ns, class... Args>
inline void
scanfs_helper(Tuple&& fs, integer_sequence<n,ns...>, Args&&... args)
{
	std::get<n>(fs)(args...);
	scanfs_helper(fs, integer_sequence<ns...>{}, std::forward<Args>(args)...);
}


}  // namespace detail




/*****************************************************************************
 *
 * @brief  maps a function to a tuple of arguments
 * @return a tuple of results
 *
 *****************************************************************************/
template<class F, class...T>
inline auto
map(F&& f, const std::tuple<T...>& xs)
	-> decltype(detail::map_helper(
		std::forward<F>(f), xs, ascending_int_sequence<0,sizeof...(T)-1>{}))
{
	return detail::map_helper(
		std::forward<F>(f), xs, ascending_int_sequence<0,sizeof...(T)-1>{});
}




/*****************************************************************************
 *
 * @brief  maps a tuple of functions to a series of arguments
 * @return a tuple of results
 *
 *****************************************************************************/
template<class... Fs, class... Args>
inline auto
map(std::tuple<Fs...>& fs, Args&&... args)
	-> decltype(detail::mapfs_helper(fs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{},
		std::forward<Args>(args)...))
{
	return detail::mapfs_helper(fs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{},
		std::forward<Args>(args)...);
}

//-----------------------------------------------------
template<class... Fs, class... Args>
inline auto
map(const std::tuple<Fs...>& fs, Args&&... args)
	-> decltype(detail::mapfs_helper(fs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{},
		std::forward<Args>(args)...))
{
	return detail::mapfs_helper(fs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{},
		std::forward<Args>(args)...);
}




/*****************************************************************************
 *
 * @brief  maps a function to a tuple of arguments
 * @return void
 *
 *****************************************************************************/
template<class F, class...T>
inline void
scan(F&& f, const std::tuple<T...>& xs)
{
	detail::scan_helper(
		std::forward<F>(f), xs, ascending_int_sequence<0,sizeof...(T)-1>{});
}




/*****************************************************************************
 *
 * @brief maps a tuple of functions to a series of arguments
 * @return void
 *
 *****************************************************************************/
template<class... Fs, class...Args>
inline void
scan(std::tuple<Fs...>& fs, Args&&... args)
{
	detail::scanfs_helper(fs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{},
		std::forward<Args>(args)...);
}

//-----------------------------------------------------
template<class... Fs, class...Args>
inline void
scan(const std::tuple<Fs...>& fs, Args&&... args)
{
	detail::scanfs_helper(fs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{},
		std::forward<Args>(args)...);
}



}  // namespace gen

}  // namespace am



#endif
