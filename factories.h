/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2014 André Müller
 *
 *****************************************************************************/

#ifndef AM_GENERIC_FACTORIES_H_
#define AM_GENERIC_FACTORIES_H_

#include <array>
#include <cstddef>
#include <utility>
#include <memory>

#include "int_sequence.h"


namespace am {


/*****************************************************************************
 *
 * @brief make_unique from N3656 by Stephan T. Lavavej <stl@microsoft.com>
 *        make_unique will be in C++14
 *
 * @details make_unique<T>(args...)
 *          make_unique<T[]>(n)
 *          make_unique<T[N]>(args...) = delete
 *
 *****************************************************************************/

//-------------------------------------------------------------------
namespace detail {

template<class T>
struct _Unique_if
{
	using _Single_object = std::unique_ptr<T>;
};

template<class T>
struct _Unique_if<T[]>
{
	using _Unknown_bound = std::unique_ptr<T[]>;
};

template<class T, size_t N>
struct _Unique_if<T[N]>
{
	using _Known_bound = void;
};

}  // namespace detail


//-------------------------------------------------------------------
template<class T, class... Args>
typename detail::_Unique_if<T>::_Single_object
make_unique(Args&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

//---------------------------------------------------------
template<class T>
typename detail::_Unique_if<T>::_Unknown_bound
make_unique(size_t n)
{
	using U__ = typename std::remove_extent<T>::type;
	return std::unique_ptr<T>(new U__[n]());
}

//---------------------------------------------------------
template<class T, class... Args>
typename detail::_Unique_if<T>::_Known_bound
make_unique(Args&&...) = delete;








namespace gen {


/*****************************************************************************
 *
 *
 *
 *
 *
 *****************************************************************************/


namespace detail {

//-------------------------------------------------------------------
template<class T>
inline constexpr
T&& constant(T&& t, int) {
	return std::forward<T>(t);
}

//---------------------------------------------------------
/// @brief general case
template<class Target, class Arg, std::size_t... ints>
inline constexpr Target
make_uniform__(Target*, Arg&& a, index_sequence<ints...>)
{
	return Target{constant(std::forward<Arg>(a),ints)...};
}

//---------------------------------------------------------
/// @brief specialization for std::array
template<class T, std::size_t n, class Arg, std::size_t... ints>
inline constexpr std::array<T,n>
make_uniform__(std::array<T,n>*, Arg&& a, index_sequence<ints...>)
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
		std::forward<Arg>(a), make_index_sequence<n>{});
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
template<class Target, class Generator, std::size_t... ints>
inline constexpr Target
make_generate__(Target*, Generator&& g, index_sequence<ints...>)
{
	return Target{
		make_generate_call__(std::forward<Generator>(g),ints)...};
}

//---------------------------------------------------------
/// @brief specialization for std::array
template<class T, std::size_t n, class Generator, std::size_t... ints>
inline constexpr std::array<T,n>
make_generate__(std::array<T,n>*, Generator&& g, index_sequence<ints...>)
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
		std::forward<Generator>(g), make_index_sequence<n>{});
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
template<class Target, class Source, std::size_t... ints>
inline constexpr Target
make_copy__(
	Target*,
	const Source& source,
	gen::index_sequence<ints...>)
{
	return Target{source[ints]...};
}

//---------------------------------------------------------
template<std::size_t n, class T, class Source, std::size_t... ints>
inline constexpr std::array<T,n>
make_copy__(
	std::array<T,n>*,
	const Source& source,
	gen::index_sequence<ints...>)
{
	return std::array<T,n>{{source[ints]...}};
}


}  // namespace detail


//-----------------------------------------------------
/// @brief calls multi-param ctor of 'Target' with n times 'a'
template<
	class Target,
	std::size_t n = std::tuple_size<Target>::value,
	class Source
>
inline constexpr Target
make_copy(const Source& src)
{
	return detail::make_copy__(static_cast<Target*>(nullptr),
		src, make_index_sequence<n>{});
}


}  // namespace gen

}  // namespace am


#endif
