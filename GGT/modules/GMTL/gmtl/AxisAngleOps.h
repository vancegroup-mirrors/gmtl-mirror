/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: AxisAngleOps.h,v $
 * Date modified: $Date: 2003-02-23 07:05:41 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 *********************************************************** ggt-head end */
/*************************************************************** ggt-cpr beg
*
* GGT: The Generic Graphics Toolkit
* Copyright (C) 2001,2002 Allen Bierbaum 
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*
 ************************************************************ ggt-cpr end */
#ifndef EULER_ANGLE_OPS
#define EULER_ANGLE_OPS

#include <gmtl/AxisAngle.h>

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
