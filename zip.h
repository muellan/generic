/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2014 André Müller
 *
 *****************************************************************************/

#ifndef AM_GENERIC_ZIP_H_
#define AM_GENERIC_ZIP_H_


namespace am {

namespace gen {


/*****************************************************************************
 *
 * @brief
 *
 * @return
 *
 *****************************************************************************/

//-------------------------------------------------------------------
template<class InputIterator1, class InputIterator2, class OutputIterator>
inline void
zip(InputIterator1 beg1, InputIterator1 end1,
    InputIterator2 beg2, InputIterator2 end2, OutputIterator out)
{
    for(; (beg1 != end1) && (beg2 != end2); ++beg1, ++beg2) {
        *out++ = {*beg1,*beg2};
    }
}



}  // namespace gen

}  // namespace am



#endif

