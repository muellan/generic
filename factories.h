/*****************************************************************************
 *
 * AM generic facilities
 *
 * released under MIT license
 *
 * 2008-2013 André Müller
 *
 *****************************************************************************/

#ifndef AM_GENERIC_FACTORIES_H_
#define AM_GENERIC_FACTORIES_H_

#include <array>
#include <cstddef>
#include <utility>

#include "int_sequence.h"




namespace am {

namespace gen {


namespace detail {

//-------------------------------------------------------------------
template<class T>
inline constexpr
T&& constant(T&& t, int) {
	return std::forward<T>(t);
}

//---------------------------------------------------------
/// @brief general case
template<class Target, class Arg, int... ints>
inline constexpr Target
make_uniform__(Target*, Arg&& a, integer_sequence<ints...>)
{
	return Target{constant(std::forward<Arg>(a),ints)...};
}

//---------------------------------------------------------
/// @brief specialization for std::array
template<class T, std::size_t n, class Arg, int... ints>
inline constexpr std::array<T,n>
make_uniform__(std::array<T,n>*, Arg&& a, integer_sequence<ints...>)
{
	return std::array<T,n>{{constant(std::forward<Arg>(a),ints)...}};
}


}  // namespace detail


//-----------------------------------------------------
/// @brief calls multi-param ctor of 'Target' with n times 'a'
template<class Target, std::size_t n = std::tuple_size<Target>::value, class Arg>
inline constexpr Target
make_uniform(Arg&& a)
{
	return detail::make_uniform__(static_cast<Target*>(nullptr),
		std::forward<Arg>(a), ascending_int_sequence<n>{});
}






/*****************************************************************************
 *
 *
 *
 *
 *
 *****************************************************************************/

namespace detail {

//-------------------------------------------------------------------
template<class Generator>
inline constexpr auto
make_generate_call__(Generator&& g, int) -> decltype(g())
{
	return g();
}

//---------------------------------------------------------
/// @brief general case
template<class Target, class Generator, int... ints>
inline constexpr Target
make_generate__(Target*, Generator&& g, integer_sequence<ints...>)
{
	return Target{
		make_generate_call__(std::forward<Generator>(g),ints)...};
}

//---------------------------------------------------------
/// @brief specialization for std::array
template<class T, std::size_t n, class Generator, int... ints>
inline constexpr std::array<T,n>
make_generate__(std::array<T,n>*, Generator&& g, integer_sequence<ints...>)
{
	return std::array<T,n>{
		{make_generate_call__(std::forward<Generator>(g),ints)...} };
}

}  // namespace detail


//-----------------------------------------------------
/// @brief calls multi-param ctor of 'Target' with n times 'g'
template<class Target, std::size_t n = std::tuple_size<Target>::value, class Generator>
inline constexpr Target
make_generate(Generator&& g)
{
	return detail::make_generate__(static_cast<Target*>(nullptr),
		std::forward<Generator>(g), ascending_int_sequence<n>{});
}






/*****************************************************************************
 *
 *
 *
 *
 *
 *****************************************************************************/

namespace detail {


//-------------------------------------------------------------------
template<class Target, class Source, int... ints>
inline constexpr Target
make_copy_elems__(
	Target*,
	const Source& source,
	gen::integer_sequence<ints...>)
{
	return Target{source[ints]...};
}

//---------------------------------------------------------
template<std::size_t n, class T, class Source, int... ints>
inline constexpr std::array<T,n>
make_copy_elems__(
	std::array<T,n>*,
	const Source& source,
	gen::integer_sequence<ints...>)
{
	return std::array<T,n>{{source[ints]...}};
}


}  // namespace detail


//-----------------------------------------------------
/// @brief calls multi-param ctor of 'Target' with n times 'a'
template<class Target, class Source,
	std::size_t n = std::tuple_size<Target>::value, class Generator>
inline constexpr Target
make_copy_elems(const Source& src)
{
	return detail::make_copy_elems__(static_cast<Target*>(nullptr),
		src, ascending_int_sequence<n>{});
}


} //namespace gen
} //namespace am




#endif
