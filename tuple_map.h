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
	-> decltype(std::make_tuple(f(std::get<ns>(xs))...))
{
	return std::make_tuple(f(std::get<ns>(xs))...);
}




/*****************************************************************************
 *
 * @brief helps to map a tuple of functions to some arguments
 *
 *****************************************************************************/
template<class Tuple, int... ns, class... Args>
inline auto
mapfs_helper(Tuple&& fs, integer_sequence<ns...>, Args&&... args)
	-> decltype(std::make_tuple(std::get<ns>(fs)(args...)...))
{
	return std::make_tuple(std::get<ns>(fs)(args...)...);
}




/*****************************************************************************
 *
 * @brief helps to map a tuple of functions to some arguments
 *
 *****************************************************************************/
template<class Ftuple, class Xtuple, int... ns>
inline auto
zip_map_helper(Ftuple&& fs, Xtuple&& xs, integer_sequence<ns...>)
	-> 	decltype(std::make_tuple(std::get<ns>(fs)(std::get<ns>(xs))...))
{
	return std::make_tuple(std::get<ns>(fs)(std::get<ns>(xs))...);
}





/*****************************************************************************
 *
 * @brief helps to map a tuple of functions to some arguments
 *
 *****************************************************************************/
template<class F, class Tuple>
inline void
scan_helper(F&&, Tuple&&, integer_sequence<>)
{}

//-----------------------------------------------------
template<class F, class Tuple, int n, int...ns>
inline void
scan_helper(F&& f, Tuple&& xs, integer_sequence<n,ns...>)
{
	f(std::get<n>(xs));
	scan_helper(std::forward<F>(f),
		std::forward<Tuple>(xs), integer_sequence<ns...>{});
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
 * @brief map(f, {x1,x2,...,xn}) -> {f(x1),f(x2),...,f(xn)}
 *        maps a function to a tuple of arguments
 *
 * @return a tuple of results
 *
 *****************************************************************************/
template<class F>
inline std::tuple<>
map(F&&, std::tuple<>)
{
	return std::tuple<>();
}

//-----------------------------------------------------
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
 * @brief map({f1,f2,...,fn}, x1,x2,...,xn) -> {f1(x1,...,xn),...,fn(x1,...,xn)}
 *        maps a tuple of functions to a series of arguments
 *
 * @return a tuple of results
 *
 *****************************************************************************/
template<class... Args>
inline std::tuple<>
map(std::tuple<>, Args&&...)
{
	return std::tuple<>();
}

//-----------------------------------------------------
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
 * @brief zip_map({f1,f2,...,fn}, {x1,x2,...,xn}) -> {f1(x1),f2(x2),...,fn(xn)}
 *        maps a tuple of functions to a tuple of arguments 1 by 1
 *
 * @return a tuple of results
 *
 *****************************************************************************/

//---------------------------------------------------------------
template<class... Fs, class... Xs>
inline auto
zip_map(std::tuple<Fs...>& fs, std::tuple<Xs...>& xs)
	-> decltype(detail::zip_map_helper(fs, xs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{}))
{
	static_assert(sizeof...(Fs) == sizeof...(Xs),
		"zip_map(tuple<Fs>, tuple<Xs>): #Fs must be equal to #Xs");

	return detail::zip_map_helper(fs, xs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{});
}

//---------------------------------------------------------------
template<class... Fs, class... Xs>
inline auto
zip_map(const std::tuple<Fs...>& fs, std::tuple<Xs...>& xs)
	-> decltype(detail::zip_map_helper(fs, xs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{}))
{
	static_assert(sizeof...(Fs) == sizeof...(Xs),
		"zip_map(tuple<Fs>, tuple<Xs>): #Fs must be equal to #Xs");

	return detail::zip_map_helper(fs, xs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{});
}

//---------------------------------------------------------------
template<class... Fs, class... Xs>
inline auto
zip_map(std::tuple<Fs...>& fs, const std::tuple<Xs...>& xs)
	-> decltype(detail::zip_map_helper(fs, xs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{}))
{
	static_assert(sizeof...(Fs) == sizeof...(Xs),
		"zip_map(tuple<Fs>, tuple<Xs>): #Fs must be equal to #Xs");

	return detail::zip_map_helper(fs, xs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{});
}

//---------------------------------------------------------------
template<class... Fs, class... Xs>
inline auto
zip_map(const std::tuple<Fs...>& fs, const std::tuple<Xs...>& xs)
	-> decltype(detail::zip_map_helper(fs, xs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{}))
{
	static_assert(sizeof...(Fs) == sizeof...(Xs),
		"zip_map(tuple<Fs>, tuple<Xs>): #Fs must be equal to #Xs");

	return detail::zip_map_helper(fs, xs,
		ascending_int_sequence<0,sizeof...(Fs)-1>{});
}






/*****************************************************************************
 *
 * @brief  maps a function to a tuple of arguments
 * @return void
 *
 *****************************************************************************/
template<class F>
inline void
scan(F&&, std::tuple<>)
{}

//---------------------------------------------------------
template<class F, class...T>
inline void
scan(F&& f, std::tuple<T...>& xs)
{
	detail::scan_helper(
		std::forward<F>(f), xs, ascending_int_sequence<0,sizeof...(T)-1>{});
}

//---------------------------------------------------------
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
template< class...Args>
inline void
scan(std::tuple<>, Args&&...)
{}

//-----------------------------------------------------
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

