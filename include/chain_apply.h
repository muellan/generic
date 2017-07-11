/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2017 André Müller
 *
 *****************************************************************************/

#ifndef AMLIB_GENERIC_APPLY_CHAIN_H_
#define AMLIB_GENERIC_APPLY_CHAIN_H_


#include <tuple>


namespace am {

namespace gen {

namespace detail {



/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<std::size_t n>
struct application_chain_call
{
    template<class F, class Arg>
    static void
    exec(const F& f, Arg& arg) {
        application_chain_call<n-1>::exec(f, arg);
        apply(std::get<n-1>(f), arg);
    }
};

template<>
struct application_chain_call<0>
{
    template<class F, class Arg>
    static void
    exec(const F&, Arg&) {}
};



}  // namespace detail






/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class... Fns>
class application_chain
{
    using this_t_ = application_chain<Fns...>;
    using call_t = detail::application_chain_call<sizeof...(Fns)>;
    using fns_t  = std::tuple<Fns...>;

public:
    //---------------------------------------------------------------
    constexpr
    application_chain() = default;
    //-----------------------------------------------------
    template<class... Args>
    explicit constexpr
    application_chain(Args&&... args):
        fns_{std::forward<Args>(args)...}
    {}

    //---------------------------------------------------------------
    template<class Arg>
    Arg operator () (Arg arg) const {
        call_t::exec(fns_, arg);
        return arg;
    }

    //---------------------------------------------------------------
    template<class Arg>
    inline friend void
    apply(const application_chain<Fns...>& ac, Arg& arg) {
        call_t::exec(ac.fns_, arg);
    }


    //---------------------------------------------------------------
    template<std::size_t index>
    inline friend
    typename std::tuple_element<index,fns_t>::type&
    get(application_chain& c) {
        return std::get<index>(c.fns_);
    }
    //-----------------------------------------------------
    template<std::size_t index>
    inline friend
    const typename std::tuple_element<index,fns_t>::type&
    get(const application_chain& c) {
        return std::get<index>(c.fns_);
    }


private:
    fns_t fns_;
};






/*****************************************************************************
 *
 *
 *
 *****************************************************************************/

//-------------------------------------------------------------------
template<class... Fns>
inline
application_chain<typename std::decay<Fns>::type...>
make_application_chain(Fns&&... fns)
{
    return application_chain<typename std::decay<Fns>::type...>{
        std::forward<Fns>(fns)...};
}



}  // namespace gen

}  // namespace am



#endif
