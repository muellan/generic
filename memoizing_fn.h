/*****************************************************************************
 *
 * AM generic facilities
 *
 * released under MIT license
 *
 * 2008-2013 André Müller
 *
 *****************************************************************************/

#ifndef AM_GENERIC_MEMOIZING_FUNCTION_H_
#define AM_GENERIC_MEMOIZING_FUNCTION_H_

#include <type_traits>
#include <functional>
#include <unordered_map>

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
class memoizing_function; //not available


//-------------------------------------------------------------------
template<class Ret, class... Args>
class memoizing_function<Ret(Args...)>
{
	using arg_t = std::tuple<typename std::decay<Args>::type...>;

	using functor_t = std::function<Ret(Args...)>;

	using hasher_t = tuple_hash<typename std::decay<Args>::type...>;

public:
	//---------------------------------------------------------------
	using result_type = Ret;


	//---------------------------------------------------------------
	///@brief construct with function object
	explicit
	memoizing_function(const functor_t& fn):
		fn_(fn), mem_()
	{}

	//-----------------------------------------------------
	///@brief default copy constructor
	memoizing_function(const memoizing_function&) = default;

	//-----------------------------------------------------
	///@brief move constructor
	memoizing_function(memoizing_function&& src):
		fn_(std::move(src.fn_)), mem_(std::move(src.mem_))
	{}


	//---------------------------------------------------------------
	///@brief default copy assignment operator
	memoizing_function&
	operator = (const memoizing_function&) = default;

	//-----------------------------------------------------
	///@brief move assignment operator
	memoizing_function&
	operator = (memoizing_function&& src)
	{
		using std::swap;
		swap(fn_, src.fn_);
		swap(mem_, src.mem_);
		return *this;
	}

	//---------------------------------------------------------------
	///@brief resets functor member and clears cache
	memoizing_function&
	operator = (const functor_t& fn)
	{
		fn_ = fn;
		mem_.clear();
		return *this;
	}


	//---------------------------------------------------------------
	/// @brief functor call with cache lookup
	const Ret&
	operator() (const Args&... args) const
	{
		//pack arguments into tuple
		auto arg = arg_t{args...};

		//if result cached -> return cached value
		auto it = mem_.find(arg);
		if(it != mem_.end()) {
			return it->second;
		}

		//compute, insert and return result
		return (mem_[arg] = fn_(args...));
	}


private:
	functor_t fn_;

	//mutable preserves the const-ness of operator() which
	//one would expected from a normal function call
	mutable std::unordered_map<arg_t,result_type,hasher_t> mem_;
};



} //namespace gen
} //namespace am


#endif
