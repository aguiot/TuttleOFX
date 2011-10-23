#ifndef _TERRY_NUMERIC_PIXEL_NUMERIC_OPERATIONS_ASSIGN_HPP_
#define _TERRY_NUMERIC_PIXEL_NUMERIC_OPERATIONS_ASSIGN_HPP_

/*!
/// \brief Structures for pixel-wise numeric operations
/// Currently defined structures:
///     pixel_plus_assign_t (+=),
///     pixel_minus_assign_t (-=)
///     pixel_multiplies_scalar_assign_t (*=),
///     pixel_divides_scalar_assign_t (/=)
*/

#include "channel_numeric_operations_assign.hpp"

#include <boost/gil/gil_config.hpp>
#include <boost/gil/pixel.hpp>
#include <boost/gil/color_base_algorithm.hpp>

#include <functional>

namespace terry {

using namespace boost::gil;

/// \ingroup PixelNumericOperations
/// \brief p2 += p1
template <typename PixelSrc, // models pixel concept
          typename PixelDst = PixelSrc> // models pixel concept
struct pixel_plus_assign_t {
	GIL_FORCEINLINE
    PixelDst& operator()( const PixelSrc& p1,
                          PixelDst& p2 ) const {
        static_for_each( p1, p2,
                         channel_plus_assign_t<typename channel_type<PixelSrc>::type,
                                               typename channel_type<PixelDst>::type>() );
        return p2;
    }
};

/// \ingroup PixelNumericOperations
/// \brief p2 -= p1
template <typename PixelSrc, // models pixel concept
          typename PixelDst = PixelSrc> // models pixel concept
struct pixel_minus_assign_t {
	GIL_FORCEINLINE
    PixelDst& operator()( const PixelSrc& p1,
                          PixelDst& p2 ) const {
        static_for_each( p1, p2,
                         channel_minus_assign_t<typename channel_type<PixelSrc>::type,
                                                typename channel_type<PixelDst>::type>() );
        return p2;
    }
};

/// \ingroup PixelNumericOperations
/// \brief p *= s
template <typename Scalar, // models a scalar type
	      typename PixelDst>  // models pixel concept
struct pixel_multiplies_scalar_assign_t {
	GIL_FORCEINLINE
    PixelDst& operator()( const Scalar& s,
	                      PixelDst& p ) const {
        static_for_each( p, std::bind1st( channel_multiplies_scalar_assign_t<Scalar, typename channel_type<PixelDst>::type>(), s ) );
		return p;
    }
};

/// \ingroup PixelNumericOperations
/// \brief p /= s
template <typename Scalar, // models a scalar type
	      typename PixelDst>  // models pixel concept
struct pixel_divides_scalar_assign_t
{
	GIL_FORCEINLINE
    PixelDst& operator()( const Scalar& s,
	                      PixelDst& p ) const
	{
        static_for_each( p, std::bind1st( channel_divides_scalar_assign_t<Scalar, typename channel_type<PixelDst>::type>(), s ) );
		return p;
    }
};


}

#endif
