/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2014 André Müller
 *
 *****************************************************************************/

#ifndef AM_GENERIC_FUNCTOR_COMPOSITION_H_
#define AM_GENERIC_FUNCTOR_COMPOSITION_H_


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
struct function_composition_call
{
	template<class F, class...Args>
	static auto
	exec(const F& f, Args&&... args)
		-> decltype(std::get<n-1>(f)(
			function_composition_call<n-1>::exec(f, std::forward<Args>(args)...)))
	{
		return std::get<n-1>(f)(function_composition_call<n-1>::exec(f, std::forward<Args>(args)...));
	}
};

template<>
struct function_composition_call<1>
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
class function_composition
{
	using this_t = function_composition<Fns...>;
	using call_t = detail::function_composition_call<sizeof...(Fns)>;
	using fns_t  = std::tuple<Fns...>;

public:
	//---------------------------------------------------------------
	constexpr
	function_composition() = default;
	//-----------------------------------------------------
	template<class... Args>
	explicit constexpr
	function_composition(Args&&... args):
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
	get(function_composition& c) {
		return std::get<index>(c.fns_);
	}
	//-----------------------------------------------------
	template<std::size_t index>
	inline friend
	const typename std::tuple_element<index,fns_t>::type&
	get(const function_composition& c) {
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
function_composition<typename std::decay<Fns>::type...>
make_function_composition(Fns&&... fns)
{
	return function_composition<typename std::decay<Fns>::type...>{
		std::forward<Fns>(fns)...};
}




}  // namespace gen

}  // namespace am



#endif
