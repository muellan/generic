/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2017 André Müller
 *
 *****************************************************************************/

#ifndef AMLIB_GENERIC_CACHED_FUNCTION_H_
#define AMLIB_GENERIC_CACHED_FUNCTION_H_

#include <type_traits>
#include <functional>
#include <unordered_map>
#include <mutex>

#include "tuple_hash.h"


namespace am {
namespace gen {


/*****************************************************************************
 *
 * @brief function value cache with a similar template parameter interface
 *        as std::function
 *
 *
 *****************************************************************************/
template<class Signature>
class cached_function; //not available


//-------------------------------------------------------------------
template<class Ret, class... Args>
class cached_function<Ret(Args...)>
{
    using arg_t_ = std::tuple<typename std::decay<Args>::type...>;

    using function_t_ = std::function<Ret(Args...)>;

    using hasher_t_ = tuple_hash<typename std::decay<Args>::type...>;

public:
    //---------------------------------------------------------------
    using result_type = Ret;


    //---------------------------------------------------------------
    ///@brief construct with function object
    explicit
    cached_function(const function_t_& fn):
        fn_(fn), mutables_(), mem_()
    {}
    //-----------------------------------------------------
    explicit
    cached_function(function_t_&& fn) noexcept :
        fn_(std::move(fn)), mutables_(), mem_()
    {}

    //-----------------------------------------------------
    ///@brief default copy constructor
    cached_function(const cached_function&) = default;

    //-----------------------------------------------------
    ///@brief move constructor
    cached_function(cached_function&& src) noexcept :
        fn_(std::move(src.fn_)), mutables_(), mem_(std::move(src.mem_))
    {}

    //---------------------------------------------------------------
    ///@brief default copy assignment operator
    cached_function& operator = (const cached_function&) = default;

    //-----------------------------------------------------
    ///@brief move assignment operator
    cached_function&
    operator = (cached_function&& src) noexcept
    {
        using std::swap;
        swap(fn_, src.fn_);
        swap(mem_, src.mem_);
        return *this;
    }


    //---------------------------------------------------------------
    ///@brief resets functor member and clears cache
    cached_function&
    operator = (const function_t_& fn)
    {
        mem_.clear();
        fn_ = fn;
        return *this;
    }


    //---------------------------------------------------------------
    /// @brief functor call with cache lookup
    const Ret&
    operator() (const Args&... args) const  //logically const
    {
        //pack arguments into tuple
        const arg_t_ arg {args...};

        //protect agains concurrent calls
        std::lock_guard<std::mutex> lock {mutables_};

        //if result cached -> return cached value
        const auto it = mem_.find(arg);
        if(it != mem_.end()) {
            return it->second;
        }

        //compute, insert and return result
        return (mem_[arg] = fn_(args...));
    }


private:
    function_t_ fn_;

    //note: mutable preserves the const-ness of operator() which
    //one would expected from a normal function call
    mutable std::mutex mutables_;
    mutable std::unordered_map<arg_t_,result_type,hasher_t_> mem_;
};



}  // namespace gen
}  // namespace am

#endif
