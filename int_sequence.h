#ifndef AM_GENERIC_INTEGER_SEQUENCE_H_
#define AM_GENERIC_INTEGER_SEQUENCE_H_

#include <cstdint>


namespace am {

namespace gen {


/*****************************************************************************
 *
 *
 * HELPERS FOR CONSTEXPR INDEXING / UNPACKING
 *
 *
 *****************************************************************************/

//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
template<int... ints>
struct integer_sequence {};


//-------------------------------------------------------------------
template<class Ostream>
inline
Ostream&
operator << (Ostream& os, integer_sequence<>)
{
	return os;
}

//---------------------------------------------------------
template<class Ostream, int i>
inline
Ostream&
operator << (Ostream& os, integer_sequence<i>)
{
	return (os << i);
}

//---------------------------------------------------------
template<class Ostream, int i, int... is>
inline
Ostream&
operator << (Ostream& os, integer_sequence<i,is...>)
{
	return (os << i <<' '<< integer_sequence<is...>());
}






namespace detail {


//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
template<class IntegerSequence, int right>
struct append_integer;

//-----------------------------------------------------
template<int... init, int last>
struct append_integer<integer_sequence<init...>,last>
{
	using type = integer_sequence<init...,last>;
};




//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
template<int min, int max>
struct make_ascending_integer_sequence
{
    using type = typename append_integer<
    	typename make_ascending_integer_sequence<min,max-1>::type, max>::type;
};
//-----------------------------------------------------
template<int min>
struct make_ascending_integer_sequence<min,min>
{
	using type = integer_sequence<min>;
};




//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
template<int max, int min = max>
struct make_descending_integer_sequence
{
    using type = typename append_integer<
    	typename make_descending_integer_sequence<max,min+1>::type, min>::type;
};
//-----------------------------------------------------
template<int max>
struct make_descending_integer_sequence<max,max>
{
	using type = integer_sequence<max>;
};




//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
template<int size, int value>
struct make_uniform_sequence
{
	using type = typename append_integer<
			typename make_uniform_sequence<size-1,value>::type,value>::type;
};
//-----------------------------------------------------
template<int value>
struct make_uniform_sequence<0,value>
{
	using type = integer_sequence<>;
};




//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
template<int pos, int size = pos, int one = 1, int zero = 0>
struct make_integer_sequence_mask
{
	using type = typename append_integer<
			typename make_integer_sequence_mask<pos,size-1,one,zero>::type,
			(((size-1) == pos) ? one : zero)
		>::type;
};
//-----------------------------------------------------
template<int pos, int one, int zero>
struct make_integer_sequence_mask<pos,1,one,zero>
{
	using type = integer_sequence<((pos == 0) ? one : zero)>;
};
//-----------------------------------------------------
template<int pos, int one, int zero>
struct make_integer_sequence_mask<pos,0,one,zero>
{
	using type = integer_sequence<>;
};



}  // namespace detail





/*****************************************************************************
 *
 *
 *
 *****************************************************************************/

//-----------------------------------------------------
template<int size, int value>
using uniform_int_sequence =
	typename detail::make_uniform_sequence<size,value>::type;

//-----------------------------------------------------
template<int pos, int size = pos, int one = 1, int zero = 0>
using int_sequence_mask =
	typename detail::make_integer_sequence_mask<pos,size,one,zero>::type;

//-----------------------------------------------------
template<int min, int max>
using ascending_int_sequence =
	typename detail::make_ascending_integer_sequence<min,max>::type;

//-----------------------------------------------------
template<int max, int min>
using descending_int_sequence =
	typename detail::make_descending_integer_sequence<max,min>::type;



}  // namespace gen

}  // namespace am


#endif
