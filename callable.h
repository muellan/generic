/*****************************************************************************
 *
 * AM generic facilities
 *
 * released under MIT license
 *
 * 2014 - 2015 André Müller
 *
 *****************************************************************************/

#ifndef AMLIB_GENERIC_CALLABLE_H_
#define AMLIB_GENERIC_CALLABLE_H_

#include <type_traits>


namespace am {
namespace gen {


namespace detail {

template<class Fn, class Return, class... Args>
constexpr typename
std::is_same<decltype(std::declval<Fn>()(std::declval<Args>()...)),
             Return>::type
check_is_callable(int);


template<class... Ts>
constexpr std::false_type
check_is_callable(long);



} //namespace detail


template<class Fn, class Return, class... Args>
struct is_callable :
    public decltype(detail::check_is_callable<Fn,Return,Args...>(0))
{};



}  // namespace gen
}  // namespace am


#endif
