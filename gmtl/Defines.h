/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Defines.h,v $
 * Date modified: $Date: 2002-07-11 23:40:02 $
 * Version:       $Revision: 1.4 $
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
#ifndef _GMTL_DEFINES_H
#define _GMTL_DEFINES_H

namespace gmtl
{
   /** use the values in this enum to index vector data 
    *  types (such as Vec, Point, Quat).
    *
    * <h3> "Example (access elements in a Vec3f):" </h3>
    * \code
    *    Vec3f vec;
    *    vec[Xelt] = 1.0f;
    *    vec[Yelt] = 3.0f;
    *    vec[Zelt] = 2.0f;
    * \endcode
    * @ingroup Defines
    */
   enum VectorIndex { Xelt = 0, Yelt = 1, Zelt = 2, Welt = 3 };

   /**
    * Used to describe where a point lies in relationship to a plane.
    * ON_PLANE means the point lies on the plane.
    * POS_SIDE means the point lies on the side that the normal points.
    * NEG_SIDE means the point lies on the side away from the normal.
    * @ingroup Defines
    */
   enum PlaneSide
   {
      ON_PLANE,
      POS_SIDE,
      NEG_SIDE
   };

   /** @ingroup Defines
    * @name Constants
    * @{
    */    
   const float GMTL_EPSILON = 1.0e-6f;
   const float GMTL_MAT_EQUAL_EPSILON = 0.001f;  // Epsilon for matrices to be equal
   const float GMTL_VEC_EQUAL_EPSILON = 0.0001f; // Epsilon for vectors to be equal
   /** @} */
   
#define GMTL_NEAR(x,y,eps) (gmtl::Math::abs((x)-(y))<(eps))

};

// Platform-specific settings.
#if defined(__sun__) || defined(__APPLE__)
#define NO_ACOSF 1
#define NO_ASINF 1
#define NO_TANF 1
#define NO_ATAN2F 1
#define NO_COSF 1
#define NO_SINF 1
#define NO_TANF 1
#define NO_SQRTF 1
#define NO_LOGF 1
#define NO_EXPF 1
#define NO_POWF 1
#define NO_CEILF 1
#define NO_FLOORF 1
#endif


#endif
