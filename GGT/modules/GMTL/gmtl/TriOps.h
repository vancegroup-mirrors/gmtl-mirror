/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: TriOps.h,v $
 * Date modified: $Date: 2002-02-18 21:07:38 $
 * Version:       $Revision: 1.1 $
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
#ifndef _GMTL_TRIOPS_H_
#define _GMTL_TRIOPS_H_

#include <gmtl/gmtlConfig.h>
#include <gmtl/Tri.h>

namespace gmtl
{
/**
 * Computes the point at the center of the given triangle.
 *
 * @param tri     the triangle to find the center of
 *
 * @return  the point at the center of the triangle
 */
template< class DATA_TYPE >
Point<DATA_TYPE, 3> center( const Tri<DATA_TYPE>& tri )
{
   const float one_third = (1.0f/3.0f);
   return (tri[0] + tri[1] + tri[2]) * one_third;
}

/**
 * Computes the normal for this triangle.
 *
 * @param tri     the triangle for which to compute the normal
 *
 * @return  the normal vector for tri
 */
template< class DATA_TYPE >
Vec<DATA_TYPE, 3> normal( const Tri<DATA_TYPE>& tri )
{
   Vec<DATA_TYPE, 3> normal = cross( tri[1] - tri[0], tri[2] - tri[0] );
   normalize( normal );
   return normal;
}

} // namespace gmtl

#endif

