/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2015 André Müller
 *
 *****************************************************************************/

#ifndef AMLIB_GENERIC_CONCAT_H_
#define AMLIB_GENERIC_CONCAT_H_


#include <array>
#include <algorithm>


namespace am {
namespace gen {


//-------------------------------------------------------------------
template<std::size_t n, class T, std::size_t m>
std::array<T,n+m>
concat(std::array<T,n> a, std::array<T,m> b)
{
    std::array<T,n+m> res;

    std::move(begin(a), end(a), begin(res));
    std::move(begin(b), end(b), next(begin(res),n));

    return res;
}



//-------------------------------------------------------------------
template<std::size_t n, class T, std::size_t m, std::size_t k>
std::array<T,n+m+k>
concat(std::array<T,n> a, std::array<T,m> b, std::array<T,k> c)
{
    std::array<T,n+m+k> res;

    std::move(begin(a), end(a), begin(res));
    std::move(begin(b), end(b), next(begin(res),n));
    std::move(begin(c), end(c), next(begin(res),n+m));

    return res;
}



}  // namespace gen
}  // namespace am



#endif
