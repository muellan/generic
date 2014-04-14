/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2014 André Müller
 *
 *****************************************************************************/

#ifndef AM_GENERIC_MAP_TRAIT_H_
#define AM_GENERIC_MAP_TRAIT_H_

#include <type_traits>


namespace am {
namespace gen {


/*****************************************************************************
 *
 * @brief maps a boolean trait over a variadic type list
 *
 *
 *****************************************************************************/
template<template<class> class Trait, class H, class... T>
struct map_bool_trait :
    public std::integral_constant<bool,
        Trait<H>::value && map_bool_trait<Trait,T...>::value>
{};

//-------------------------------------------------------------------
template<template<class> class Trait, class T>
struct map_bool_trait<Trait,T> :
    public std::integral_constant<bool,Trait<T>::value>
{};






/*****************************************************************************
 *
 * @brief
 *
 *
 *****************************************************************************/
template<class Type, class H, class... T>
struct are_all_same :
    public std::integral_constant<bool,
        std::is_same<Type,H>::value && are_all_same<Type,T...>::value>
{};

//-------------------------------------------------------------------
template<class Type, class T>
struct are_all_same<Type,T> :
    public std::integral_constant<bool,std::is_same<Type,T>::value>
{};



}  // namespace gen
}  // namespace am



#endif
