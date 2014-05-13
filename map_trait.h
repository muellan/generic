/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008 - 2014 André Müller
 *
 *****************************************************************************/

#ifndef AM_GENERIC_MAP_TRAIT_H_
#define AM_GENERIC_MAP_TRAIT_H_

#include <type_traits>


namespace am {
namespace gen {


/*****************************************************************************
 *
 * @brief maps OR over a variadic list of boolean traits
 *
 *
 *****************************************************************************/
template<class...>
struct any;

template<>
struct any<> :
    public std::false_type
{};

template<class T1>
struct any<T1> :
    public T1
{};

template<class T1, class T2>
struct any<T1,T2> :
    public std::conditional<T1::value,T1,T2>::type
{};

template<class T1, class T2, class T3, class... Ts>
struct any<T1,T2,T3,Ts...> :
    public std::conditional<T1::value,T1, any<T2,T3,Ts...>>::type
{};






/*****************************************************************************
 *
 * @brief maps AND over a variadic list of boolean traits
 *
 *
 *****************************************************************************/
template<class...>
struct all;

template<>
struct all<> :
    public std::true_type
{};

template<class T1>
struct all<T1> :
    public T1
{};

template<class T1, class T2>
struct all<T1,T2> :
    public std::conditional<T1::value,T2,T1>::type
{};

template<class T1, class T2, class T3, class... Ts>
struct all<T1,T2,T3,Ts...> :
    public std::conditional<T1::value, all<T2,T3,Ts...>,T1>::type
{};


}  // namespace gen
}  // namespace am



#endif
