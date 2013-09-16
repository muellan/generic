/*****************************************************************************
 *
 * AM generic facilities
 *
 * released under MIT license
 *
 * 2008-2013 André Müller
 *
 *****************************************************************************/

#ifndef AM_GENERIC_CALL_CHAIN_H_
#define AM_GENERIC_CALL_CHAIN_H_


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
struct call_chain_call
{
	template<class F, class...Args>
	static auto
	exec(const F& f, Args&&... args)
		-> decltype(std::get<n-1>(f)(
			call_chain_call<n-1>::exec(f, std::forward<Args>(args)...)))
	{
		return std::get<n-1>(f)(call_chain_call<n-1>::exec(f, std::forward<Args>(args)...));
	}
};

template<>
struct call_chain_call<1>
{
	template<class F, class...Args>
	static auto
	exec(const F& f, Args&&... args)
		-> decltype(std::get<0>(f)(std::forward<Args>(args)...))
	{
		return std::get<0>(f)(std::forward<Args>(args)...);
	}
};



}  // namespace detail






/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class... Fns>
class call_chain
{
	using this_t = call_chain<Fns...>;
	using call_t = detail::call_chain_call<sizeof...(Fns)>;
	using fns_t  = std::tuple<Fns...>;

public:
	//---------------------------------------------------------------
	constexpr
	call_chain() = default;
	//-----------------------------------------------------
	template<class... Args>
	explicit constexpr
	call_chain(Args&&... args):
		fns_{std::forward<Args>(args)...}
	{}

	//---------------------------------------------------------------
	template<class... Args>
	auto
	operator () (Args&&... args) const
		-> decltype(call_t::exec(fns_t{}, std::forward<Args>(args)...))
	{
		return call_t::exec(fns_, std::forward<Args>(args)...);
	}


	//---------------------------------------------------------------
	template<std::size_t index>
	inline friend
	typename std::tuple_element<index,fns_t>::type&
	get(call_chain& c) {
		return std::get<index>(c.fns_);
	}
	//-----------------------------------------------------
	template<std::size_t index>
	inline friend
	const typename std::tuple_element<index,fns_t>::type&
	get(const call_chain& c) {
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
call_chain<typename std::decay<Fns>::type...>
make_call_chain(Fns&&... fns)
{
	return call_chain<typename std::decay<Fns>::type...>{
		std::forward<Fns>(fns)...};
}




} //namespace gen
} //namespace am





#endif
