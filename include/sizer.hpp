/*********************/

#ifndef SIZER_HPP_KSDHFGDHSFGDHSGFJGSJDHFGGSDG_INCLUDED
#define SIZER_HPP_KSDHFGDHSFGDHSGFJGSJDHFGGSDG_INCLUDED

namespace hl
{

/**
 * @brief The sizer struct
 */
template <int I>
struct sizer
{
    /**
     * @brief __Size_inst to make sizeof able to count
     */
    char __Size_inst[I];
};

} //namespace hl

#endif // SIZER_HPP_KSDHFGDHSFGDHSGFJGSJDHFGGSDG_INCLUDED
