/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2015 André Müller
 *
 *****************************************************************************/

#ifndef AMLIB_GENERIC_TUPLE_HASH_H_
#define AMLIB_GENERIC_TUPLE_HASH_H_


#include <tuple>
#include <cstdint>

#include "int_sequence.h"



namespace am {

namespace gen {


namespace detail {


//-------------------------------------------------------------------
template<class ResultT, class T, class... Ts>
struct combine_hashes
{
    static ResultT
    get(const T& t , const Ts&... ts) {
        return (
            ResultT(std::hash<T>()(t))
            xor
            combine_hashes<ResultT,Ts...>::get(ts...)
        );
    }
};

//-------------------------------------------------------------------
template<class ResultT, class T>
struct combine_hashes<ResultT,T>
{
    static ResultT
    get(const T& t) {
        return ResultT(std::hash<T>()(t));
    }
};



}  // namespace detail






/*****************************************************************************
 *
 *
 *
 *
 *****************************************************************************/
template<
    class... T
>
struct tuple_hash
{
    using argument_type = std::tuple<T...>;
    using result_type = std::uint_least64_t;

    result_type
    operator()(const argument_type& t) const
    {
        return make_hash(
            t, make_index_sequence<std::tuple_size<argument_type>::value>());
    }

private:
    template<std::size_t...idx>
    static result_type
    make_hash(const argument_type& t, index_sequence<idx...>)
    {
        return detail::combine_hashes<result_type,T...>::get(std::get<idx>(t)...);
    }

};




}  // namespace gen

}  // namespace am


#endif
