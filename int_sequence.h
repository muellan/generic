/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008 - 2014 André Müller
 *
 *****************************************************************************/

#ifndef AM_GENERIC_INTEGER_SEQUENCE_H_
#define AM_GENERIC_INTEGER_SEQUENCE_H_

#include <cstdint>


namespace am {

namespace gen {


/*****************************************************************************
 *
 *
 * @brief integer sequence
 *
 *
 *****************************************************************************/
template<class Int, Int... ints>
struct integer_sequence
{
    using value_type = Int;

    static constexpr
    std::size_t size() noexcept {
        return sizeof...(ints);
    }

};


//-------------------------------------------------------------------
template<std::size_t... indices>
using index_sequence = integer_sequence<std::size_t,indices...>;


//-------------------------------------------------------------------
template<class Ostream, class Int>
inline
Ostream&
operator << (Ostream& os, integer_sequence<Int>)
{
    return os;
}

//---------------------------------------------------------
template<class Ostream, class Int, Int i>
inline
Ostream&
operator << (Ostream& os, integer_sequence<Int,i>)
{
    return (os << i);
}

//---------------------------------------------------------
template<class Ostream, class Int, Int i, Int... is>
inline
Ostream&
operator << (Ostream& os, integer_sequence<Int,i,is...>)
{
    return (os << i <<' '<< integer_sequence<Int,is...>());
}






namespace detail {


//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
template<class IntegerSequence, typename IntegerSequence::value_type right>
struct integer_appender;

//---------------------------------------------------------
template<class Int, Int... init, Int last>
struct integer_appender<integer_sequence<Int,init...>,last>
{
    using type = integer_sequence<Int,init...,last>;
};


} //namespace detail




//---------------------------------------------------------
template<class IntegerSequence, typename IntegerSequence::value_type right>
using append_integer =
    typename detail::integer_appender<IntegerSequence,right>::type;






namespace detail {


//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
template<class Int, Int min, Int max, bool empty = (min > max)>
struct ascending_integer_sequence_maker
{
    using type = append_integer<
        typename ascending_integer_sequence_maker<Int,min,max-1>::type, max>;
};
//-----------------------------------------------------
template<class Int, Int min, Int max>
struct ascending_integer_sequence_maker<Int,min,max,true>
{
    using type = integer_sequence<Int>;
};
//-----------------------------------------------------
template<class Int, Int min>
struct ascending_integer_sequence_maker<Int,min,min,false>
{
    using type = integer_sequence<Int,min>;
};




//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
template<class Int, Int max, Int min, bool empty = (min > max)>
struct descending_integer_sequence_maker
{
    using type = append_integer<
        typename descending_integer_sequence_maker<Int,max,min+1>::type, min>;
};
//-----------------------------------------------------
template<class Int, Int min, Int max>
struct descending_integer_sequence_maker<Int,min,max,true>
{
    using type = integer_sequence<Int>;
};
//-----------------------------------------------------
template<class Int, Int max>
struct descending_integer_sequence_maker<Int,max,max,false>
{
    using type = integer_sequence<Int,max>;
};




//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
template<class Int, std::size_t size, Int value>
struct uniform_integer_sequence_maker
{
    using type = append_integer<
            typename uniform_integer_sequence_maker<Int,size-1,value>::type,value>;
};
//-----------------------------------------------------
template<class Int, Int value>
struct uniform_integer_sequence_maker<Int,0,value>
{
    using type = integer_sequence<Int>;
};




//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
template<
    class Int,
    std::size_t pos,
    std::size_t size = pos,
    int one = 1,
    int zero = 0
>
struct integer_sequence_mask_maker
{
    using type = append_integer<
            typename integer_sequence_mask_maker<Int,pos,size-1,one,zero>::type,
            (((size-1) == pos) ? one : zero)
        >;
};
//-----------------------------------------------------
template<class Int, std::size_t pos, int one, int zero>
struct integer_sequence_mask_maker<Int,pos,1,one,zero>
{
    using type = integer_sequence<Int,((pos == 0) ? one : zero)>;
};
//-----------------------------------------------------
template<class Int, std::size_t pos, int one, int zero>
struct integer_sequence_mask_maker<Int,pos,0,one,zero>
{
    using type = integer_sequence<Int>;
};



}  // namespace detail





/*****************************************************************************
 *
 *
 *
 *
 *****************************************************************************/


//-------------------------------------------------------------------
// similar to upcoming standard
//-------------------------------------------------------------------
template<class Int, Int maxExcl>
using make_integer_sequence =
    typename detail::ascending_integer_sequence_maker<Int,0,maxExcl-1>::type;

//---------------------------------------------------------
template<std::size_t maxExcl>
using make_index_sequence =
    typename detail::ascending_integer_sequence_maker<
        std::size_t,0,maxExcl-1>::type;



//-------------------------------------------------------------------
// custom
//-------------------------------------------------------------------
template<class Int, Int min, Int max>
using make_ascending_integer_sequence =
    typename detail::ascending_integer_sequence_maker<Int,min,max>::type;

//-----------------------------------------------------
template<class Int, Int max, Int min>
using make_descending_integer_sequence =
    typename detail::descending_integer_sequence_maker<Int,max,min>::type;

//-----------------------------------------------------
template<class Int, std::size_t size, Int value>
using make_uniform_integer_sequence =
    typename detail::uniform_integer_sequence_maker<Int,size,value>::type;

//-----------------------------------------------------
template<
    class Int, std::size_t pos, std::size_t size = pos,
    int one = 1, int zero = 0
>
using make_integer_sequence_mask =
    typename detail::integer_sequence_mask_maker<Int,pos,size,one,zero>::type;


}  // namespace gen

}  // namespace am


#endif
