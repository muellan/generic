/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2014 André Müller
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
 *
 *****************************************************************************/
template<class F, class Tuple, std::size_t... ns>
inline auto
map_helper(F&& f, const Tuple& xs, index_sequence<ns...>)
    -> decltype(std::make_tuple(f(std::get<ns>(xs))...))
{
    return std::make_tuple(f(std::get<ns>(xs))...);
}




/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class Tuple, std::size_t... ns, class... Args>
inline auto
mapfs_helper(Tuple&& fs, index_sequence<ns...>, Args&&... args)
    -> decltype(std::make_tuple(std::get<ns>(fs)(args...)...))
{
    return std::make_tuple(std::get<ns>(fs)(args...)...);
}




/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class Ftuple, class Xtuple, std::size_t... ns>
inline auto
zip_map_helper(Ftuple&& fs, Xtuple&& xs, index_sequence<ns...>)
    ->     decltype(std::make_tuple(std::get<ns>(fs)(std::get<ns>(xs))...))
{
    return std::make_tuple(std::get<ns>(fs)(std::get<ns>(xs))...);
}





/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class F, class Tuple>
inline void
act_helper(F&&, Tuple&&, index_sequence<>)
{}

//-----------------------------------------------------
template<class F, class Tuple, std::size_t n, std::size_t... ns>
inline void
act_helper(F&& f, Tuple&& xs, index_sequence<n,ns...>)
{
    f(std::get<n>(xs));
    act_helper(std::forward<F>(f),
        std::forward<Tuple>(xs), index_sequence<ns...>{});
}




/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class Tuple, class... Args>
inline void
actfs_helper(Tuple&&, index_sequence<>, Args&&...)
{}

//-----------------------------------------------------
template<class Tuple, std::size_t n, std::size_t... ns, class... Args>
inline void
actfs_helper(Tuple&& fs, index_sequence<n,ns...>, Args&&... args)
{
    std::get<n>(fs)(args...);
    actfs_helper(
        std::forward<Tuple>(fs), index_sequence<ns...>{},
        std::forward<Args>(args)...);
}




/*****************************************************************************
 *
 *
 *****************************************************************************/
template<std::size_t n>
struct apply_at_helper
{
    template<class Fs, class... Args>
    static void
    apply(Fs&& fs, std::size_t index, Args&&... args) {

        using std::get;
        if(index == (n-1)) {
            get<n-1>(fs)(std::forward<Args>(args)...);
        } else {
            apply_at_helper<n-1>::apply(
                std::forward<Fs>(fs), index, std::forward<Args>(args)...);
        }
    }
};

//---------------------------------------------------------
template<>
struct apply_at_helper<0>
{
    template<class Fs, class... Args>
    static void
    apply(Fs&&, std::size_t, Args&&...) {}
};




/*****************************************************************************
 *
 *
 *****************************************************************************/
template<std::size_t n>
struct apply_op_at_helper
{
    template<class Op, class Fs>
    static void
    apply(Op&& op, Fs&& fs, std::size_t index) {

        using std::get;
        if(index == (n-1)) {
            op(get<n-1>(fs));
        } else {
            apply_at_helper<n-1>::apply(
                std::forward<Op>(op), std::forward<Fs>(fs), index);
        }
    }
};

//---------------------------------------------------------
template<>
struct apply_op_at_helper<0>
{
    template<class Op, class Fs>
    static void
    apply(Op&&, Fs&&, std::size_t) {}
};




/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class Ftuple, class Xtuple>
inline void
zip_act_helper(Ftuple&&, Xtuple&&, index_sequence<>)
{}

//---------------------------------------------------------
template<class Ftuple, class Xtuple, std::size_t n, std::size_t... ns>
inline void
zip_act_helper(Ftuple&& fs, Xtuple&& xs, index_sequence<n,ns...>)
{
    std::get<n>(fs)(std::get<n>(xs));

    zip_act_helper(
        std::forward<Ftuple>(fs),
        std::forward<Xtuple>(xs), index_sequence<ns...>{});
}


}  // namespace detail






/*****************************************************************************
 *
 * @brief map(f, {x1,x2,...,xn}) -> {f(x1),f(x2),...,f(xn)}
 *        applies a functor to each argument of a tuple of arguments
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
        std::forward<F>(f), xs, make_index_sequence<sizeof...(T)>{}))
{
    return detail::map_helper(
        std::forward<F>(f), xs, make_index_sequence<sizeof...(T)>{});
}






/*****************************************************************************
 *
 * @brief map({f1,f2,...,fn}, x1,x2,...,xn) -> {f1(x1,...,xn),...,fn(x1,...,xn)}
 *        applies each functor in a tuple to a series of arguments
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
        make_index_sequence<sizeof...(Fs)>{},
        std::forward<Args>(args)...))
{
    return detail::mapfs_helper(fs,
        make_index_sequence<sizeof...(Fs)>{},
        std::forward<Args>(args)...);
}

//-----------------------------------------------------
template<class... Fs, class... Args>
inline auto
map(const std::tuple<Fs...>& fs, Args&&... args)
    -> decltype(detail::mapfs_helper(fs,
        make_index_sequence<sizeof...(Fs)>{},
        std::forward<Args>(args)...))
{
    return detail::mapfs_helper(fs,
        make_index_sequence<sizeof...(Fs)>{},
        std::forward<Args>(args)...);
}






/*****************************************************************************
 *
 * @brief zip_map({f1,f2,...,fn}, {x1,x2,...,xn}) -> {f1(x1),f2(x2),...,fn(xn)}
 *        applies each functor to each argument 1-by-1
 *
 * @return a tuple of results
 *
 *****************************************************************************/

//---------------------------------------------------------------
template<class... Fs, class... Xs>
inline auto
zip_map(std::tuple<Fs...>& fs, std::tuple<Xs...>& xs)
    -> decltype(detail::zip_map_helper(fs, xs,
        make_index_sequence<sizeof...(Fs)>{}))
{
    static_assert(sizeof...(Fs) == sizeof...(Xs),
        "zip_map(tuple<Fs>, tuple<Xs>): #Fs must be equal to #Xs");

    return detail::zip_map_helper(fs, xs,
        make_index_sequence<sizeof...(Fs)>{});
}

//---------------------------------------------------------------
template<class... Fs, class... Xs>
inline auto
zip_map(const std::tuple<Fs...>& fs, std::tuple<Xs...>& xs)
    -> decltype(detail::zip_map_helper(fs, xs,
        make_index_sequence<sizeof...(Fs)>{}))
{
    static_assert(sizeof...(Fs) == sizeof...(Xs),
        "zip_map(tuple<Fs>, tuple<Xs>): #Fs must be equal to #Xs");

    return detail::zip_map_helper(fs, xs,
        make_index_sequence<sizeof...(Fs)>{});
}

//---------------------------------------------------------------
template<class... Fs, class... Xs>
inline auto
zip_map(std::tuple<Fs...>& fs, const std::tuple<Xs...>& xs)
    -> decltype(detail::zip_map_helper(fs, xs,
        make_index_sequence<sizeof...(Fs)>{}))
{
    static_assert(sizeof...(Fs) == sizeof...(Xs),
        "zip_map(tuple<Fs>, tuple<Xs>): #Fs must be equal to #Xs");

    return detail::zip_map_helper(fs, xs,
        make_index_sequence<sizeof...(Fs)>{});
}

//---------------------------------------------------------------
template<class... Fs, class... Xs>
inline auto
zip_map(const std::tuple<Fs...>& fs, const std::tuple<Xs...>& xs)
    -> decltype(detail::zip_map_helper(fs, xs,
        make_index_sequence<sizeof...(Fs)>{}))
{
    static_assert(sizeof...(Fs) == sizeof...(Xs),
        "zip_map(tuple<Fs>, tuple<Xs>): #Fs must be equal to #Xs");

    return detail::zip_map_helper(fs, xs,
        make_index_sequence<sizeof...(Fs)>{});
}






/*****************************************************************************
 *
 * @brief act(f, {x1,x2,...,xn}): {f(x1); f(x2); ...; f(xn);}
 *        applies a functor to each argument in a tuple of arguments and
 *        discards the results
 *
 * @return void
 *
 *****************************************************************************/
template<class F>
inline void
act(F&&, std::tuple<>)
{}

//---------------------------------------------------------
template<class F, class...T>
inline void
act(F&& f, std::tuple<T...>& xs)
{
    detail::act_helper(
        std::forward<F>(f), xs, make_index_sequence<sizeof...(T)>{});
}

//---------------------------------------------------------
template<class F, class...T>
inline void
act(F&& f, const std::tuple<T...>& xs)
{
    detail::act_helper(
        std::forward<F>(f), xs, make_index_sequence<sizeof...(T)>{});
}






/*****************************************************************************
 *
 * @brief act({f1,f2,...,fn}, x1,x2,...,xn): {f1(x1,...,xn); ...; fn(x1,...,xn);}
 *        applies each functor in a tuple to a series of arguments and
 *        discards the results
 *
 * @return void
 *
 *****************************************************************************/
template< class...Args>
inline void
act(std::tuple<>, Args&&...)
{}

//-----------------------------------------------------
template<class... Fs, class...Args>
inline void
act(std::tuple<Fs...>& fs, Args&&... args)
{
    detail::actfs_helper(fs,
        make_index_sequence<sizeof...(Fs)>{},
        std::forward<Args>(args)...);
}

//-----------------------------------------------------
template<class... Fs, class...Args>
inline void
act(const std::tuple<Fs...>& fs, Args&&... args)
{
    detail::actfs_helper(fs,
        make_index_sequence<sizeof...(Fs)>{},
        std::forward<Args>(args)...);
}






/*****************************************************************************
 *
 * @brief apply_at(i, {f0,f1,...,fn}, args...): fi(args...)
 *        applies a functor contained in a tuple to some arguments
 *
 * @return void
 *
 *****************************************************************************/
template<class... Fs, class... Args>
inline void
apply_at(std::tuple<Fs...>& fs, std::size_t index, Args&&... args)
{
    detail::apply_at_helper<sizeof...(Fs)>::apply(
        fs, index, std::forward<Args>(args)...);
}

//---------------------------------------------------------
template<class... Fs, class... Args>
inline void
apply_at(const std::tuple<Fs...>& fs, std::size_t index, Args&&... args)
{
    detail::apply_at_helper<sizeof...(Fs)>::apply(
        fs, index, std::forward<Args>(args)...);
}






/*****************************************************************************
 *
 * @brief apply_at(op, {f0,f1,...,fn}, i): op(fi)
 *        applies a functor to an element contained in a tuple
 *
 * @return void
 *
 *****************************************************************************/
template<class... Fs, class Op>
inline void
apply_at(Op&& op, std::tuple<Fs...>& fs, std::size_t index)
{
    detail::apply_op_at_helper<sizeof...(Fs)>::apply(
        std::forward<Op>(op), fs, index);
}

//---------------------------------------------------------
template<class... Fs, class Op>
inline void
apply_at(Op&& op, const std::tuple<Fs...>& fs, std::size_t index)
{
    detail::apply_op_at_helper<sizeof...(Fs)>::apply(
        std::forward<Op>(op), fs, index);
}






/*****************************************************************************
 *
 * @brief zip_act({f1,f2,...,fn}, {x1,x2,...,xn})
 *        applies each functor to each argument 1-by-1 and
 *        discards the results
 *
 * @return void
 *
 *****************************************************************************/

//---------------------------------------------------------------
template<class... Fs, class... Xs>
inline void
zip_act(std::tuple<Fs...>& fs, std::tuple<Xs...>& xs)
{
    static_assert(sizeof...(Fs) == sizeof...(Xs),
        "zip_map(tuple<Fs>, tuple<Xs>): #Fs must be equal to #Xs");

    detail::zip_act_helper(fs, xs,
        make_index_sequence<sizeof...(Fs)>{});
}

//---------------------------------------------------------------
template<class... Fs, class... Xs>
inline void
zip_act(const std::tuple<Fs...>& fs, std::tuple<Xs...>& xs)
{
    static_assert(sizeof...(Fs) == sizeof...(Xs),
        "zip_map(tuple<Fs>, tuple<Xs>): #Fs must be equal to #Xs");

    detail::zip_act_helper(fs, xs,
        make_index_sequence<sizeof...(Fs)>{});
}

//---------------------------------------------------------------
template<class... Fs, class... Xs>
inline void
zip_act(std::tuple<Fs...>& fs, const std::tuple<Xs...>& xs)
{
    static_assert(sizeof...(Fs) == sizeof...(Xs),
        "zip_map(tuple<Fs>, tuple<Xs>): #Fs must be equal to #Xs");

    detail::zip_act_helper(fs, xs,
        make_index_sequence<sizeof...(Fs)>{});
}

//---------------------------------------------------------------
template<class... Fs, class... Xs>
inline void
zip_act(const std::tuple<Fs...>& fs, const std::tuple<Xs...>& xs)
{
    static_assert(sizeof...(Fs) == sizeof...(Xs),
        "zip_map(tuple<Fs>, tuple<Xs>): #Fs must be equal to #Xs");

    detail::zip_act_helper(fs, xs,
        make_index_sequence<sizeof...(Fs)>{});
}



}  // namespace gen
}  // namespace am


#endif

