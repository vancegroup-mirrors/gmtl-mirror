#ifndef EULER_ANGLE_OPS
#define EULER_ANGLE_OPS

#include "gmtl/AxisAngle.h"

namespace gmtl
{

/** @ingroup Compare
 *  @name AxisAngle Comparitors
 *  @{
 */

/**
 * Compares v1 and v2 to see if they are exactly the same with zero tolerance.
 *
 * @param v1   the first vector
 * @param v2   the second vector
 *
 * @return  true if v1 equals v2; false if they differ
 */
template<class DATA_TYPE>
inline bool operator==(const AxisAngle<DATA_TYPE>& v1,
                       const AxisAngle<DATA_TYPE>& v2)
{
   // @todo metaprogramming.
   if (v1[0] != v2[0]) return false;
   if (v1[1] != v2[1]) return false;
   if (v1[2] != v2[2]) return false;
   if (v1[3] != v2[3]) return false;
   return true;
}

/**
 * Compares v1 and v2 to see if they are NOT exactly the same with zero
 * tolerance.
 *
 * @param v1   the first vector
 * @param v2   the second vector
 *
 * @return  true if v1 does not equal v2; false if they are equal
 */
template<class DATA_TYPE>
inline bool operator!=(const AxisAngle<DATA_TYPE>& v1,
                       const AxisAngle<DATA_TYPE>& v2)
{
   return !(v1 == v2);
}

/**
 * Compares v1 and v2 to see if they are the same within the given epsilon
 * tolerance.
 *
 * @pre eps must be >= 0
 *
 * @param v1   the first vector
 * @param v2   the second vector
 * @param eps  the epsilon tolerance value
 *
 * @return  true if v1 equals v2; false if they differ
 */
template<class DATA_TYPE>
inline bool isEqual( const AxisAngle<DATA_TYPE>& v1,
                     const AxisAngle<DATA_TYPE>& v2, 
                     const DATA_TYPE& eps = (DATA_TYPE)0 )
{
   gmtlASSERT( eps >= (DATA_TYPE)0 );
   
   // @todo metaprogramming.
   if (!Math::isEqual( v1[0], v2[0], eps )) return false;
   if (!Math::isEqual( v1[1], v2[1], eps )) return false;
   if (!Math::isEqual( v1[2], v2[2], eps )) return false;
   if (!Math::isEqual( v1[3], v2[3], eps )) return false;
   return true;
}

// @todo write isEquiv function for AxisAngle


/** @} */

} // namespace

#endif
