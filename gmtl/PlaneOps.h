/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: PlaneOps.h,v $
 * Date modified: $Date: 2002-02-18 23:53:20 $
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
#ifndef _GMTL_PLANEOPS_H_
#define _GMTL_PLANEOPS_H_

#include <gmtl/gmtlConfig.h>
#include <gmtl/Plane.h>
#include <gmtl/Math.h>

namespace gmtl
{

/**
 * Computes the distance from the plane to the point.
 *
 * @param plane      the plane to compare the point to it
 * @param pt         a point in space
 *
 * @return  the distance from the point to the plane
 */
template< class DATA_TYPE >
DATA_TYPE distance( const Plane<DATA_TYPE>& plane, const Point<DATA_TYPE, 3>& pt )
{
   return ( dot(plane.mNorm, static_cast< Vec<DATA_TYPE, 3> >(pt)) - plane.mOffset );
}

//--- Plane Comparisons --//
/**
 * Compare two planes to see if they are EXACTLY the same. In other words, this
 * comparison is done with zero tolerance.
 *
 * @param p1      the first plane to compare
 * @param p2      the second plane to compare
 *
 * @return  true if they are equal, false otherwise
 */
template< class DATA_TYPE >
inline bool operator==( const Plane<DATA_TYPE>& p1, const Plane<DATA_TYPE>& p2 )
{
   return ( (p1.mNorm == p2.mNorm) && (p1.mOffset == p2.mOffset) );
}

/**
 * Compare two planes to see if they are not EXACTLY the same. In other words,
 * this comparison is done with zero tolerance.
 *
 * @param p1      the first plane to compare
 * @param p2      the second plane to compare
 *
 * @return  true if they are not equal, false otherwise
 */
template< class DATA_TYPE >
inline bool operator!=( const Plane<DATA_TYPE>& p1, const Plane<DATA_TYPE>& p2 )
{
   return (! (p1 == p2));
}

/**
 * Compare two planes to see if they are the same within the given tolerance.
 *
 * @param p1      the first plane to compare
 * @param p2      the second plane to compare
 * @param eps     the tolerance value to use
 *
 * @pre eps must be >= 0
 *
 * @return  true if they are equal, false otherwise
 */
template< class DATA_TYPE >
inline bool isEqual( const Plane<DATA_TYPE>& p1, const Plane<DATA_TYPE>& p2,
                     const DATA_TYPE& eps )
{
   ggtASSERT( eps >= 0 );
   return ( (isEqual(p1.mNorm, p2.mNorm, eps)) &&
            (Math::isEqual(p1.mOffset, p2.mOffset, eps)) );
}

} // namespace gmtl

#endif

