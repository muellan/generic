#ifndef AM_GENERIC_TUPLE_HASH_H_
#define AM_GENERIC_TUPLE_HASH_H_


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
			t, ascending_int_sequence<0,std::tuple_size<argument_type>::value-1>());
	}

private:
	template<int...idx>
	static result_type
	make_hash(const argument_type& t, integer_sequence<idx...>)
	{
		using std::get;
		return detail::combine_hashes<result_type,T...>::get(get<idx>(t)...);
	}

};




}  // namespace gen

}  // namespace am


#endif
