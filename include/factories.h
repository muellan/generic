/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2017 André Müller
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
    using U_t_ = typename std::remove_extent<T>::type;
    return std::unique_ptr<T>(new U_t_[n]());
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
inline constexpr const T&
constant(const T& t, int) {
    return t;
}

//---------------------------------------------------------
/// @brief general case
template<class Target, class Arg, std::size_t... ints>
inline constexpr Target
make_uniform_t_(Target*, const Arg& a, index_sequence<ints...>)
{
    return Target{constant(a,ints)...};
}

//---------------------------------------------------------
/// @brief specialization for std::array
template<class T, std::size_t n, class Arg, std::size_t... ints>
inline constexpr std::array<T,n>
make_uniform_t_(std::array<T,n>*, const Arg& a, index_sequence<ints...>)
{
    return std::array<T,n>{{constant(a,ints)...}};
}


}  // namespace detail


//-----------------------------------------------------
/// @brief calls multi-param ctor of 'Target' with n times 'a'
template<class Target, std::size_t n = std::tuple_size<Target>::value, class Arg>
inline constexpr Target
make_uniform(Arg&& a)
{
    return detail::make_uniform_t_(static_cast<Target*>(nullptr),
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
make_generate_call_t_(Generator&& g, int) -> decltype(g())
{
    return g();
}

//---------------------------------------------------------
/// @brief general case
template<class Target, class Generator, std::size_t... ints>
inline constexpr Target
make_generate_t_(Target*, Generator&& g, index_sequence<ints...>)
{
    return Target{
        make_generate_call_t_(std::forward<Generator>(g),ints)...};
}

//---------------------------------------------------------
/// @brief specialization for std::array
template<class T, std::size_t n, class Generator, std::size_t... ints>
inline constexpr std::array<T,n>
make_generate_t_(std::array<T,n>*, Generator&& g, index_sequence<ints...>)
{
    return std::array<T,n>{
        {make_generate_call_t_(std::forward<Generator>(g),ints)...} };
}

}  // namespace detail


//-----------------------------------------------------
/// @brief calls multi-param ctor of 'Target' with n times the result of 'g()'
template<class Target, std::size_t n = std::tuple_size<Target>::value, class Generator>
inline constexpr Target
make_generate(Generator&& g)
{
    return detail::make_generate_t_(static_cast<Target*>(nullptr),
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
make_with_elems_t_(
    Target*,
    const Source& source,
    gen::index_sequence<ints...>)
{
    return Target{source[ints]...};
}

//---------------------------------------------------------
template<std::size_t n, class T, class Source, std::size_t... ints>
inline constexpr std::array<T,n>
make_with_elems_t_(
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
make_with_elems(const Source& src)
{
    return detail::make_with_elems_t_(static_cast<Target*>(nullptr),
        src, make_index_sequence<n>{});
}


}  // namespace gen

}  // namespace am


#endif
