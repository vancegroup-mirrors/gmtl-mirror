/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Generate.h,v $
 * Date modified: $Date: 2002-02-18 20:56:05 $
 * Version:       $Revision: 1.3 $
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
#ifndef _GMTL_GENERATE_H_
#define _GMTL_GENERATE_H_

#include <gmtl/Matrix.h>
#include <gmtl/Meta.h>

namespace gmtl
{
   /** Create a matrix using an axis and an angle.
    *  to a rotation matrix defined by the rotation part of M
    */
   template< typename DATA_TYPE, unsigned ROWS, unsigned COLS >
   inline Matrix<DATA_TYPE, ROWS, COLS>& makeRot( Matrix<DATA_TYPE, ROWS, COLS> result, DATA_TYPE radians, DATA_TYPE x, DATA_TYPE y, DATA_TYPE z )
   {
      // TODO: make this a compile time assert...
      assert( ROWS >= 3 && COLS >= 3 && "this is undefined for Matrix smaller than 3x3" );
      
      // GGI: pg 466
      DATA_TYPE s = Math::sin( radians );
      DATA_TYPE c = Math::cos( radians );
      DATA_TYPE t = 1-c;

      /* From: Introduction to robotic.  Craig.  Pg. 52 */
      result( 0, 0 ) = (t*x*x)+c;     result( 0, 1 ) = (t*x*y)-(s*z); result( 0, 2 ) = (t*x*z)+(s*y); 
      result( 1, 0 ) = (t*x*y)+(s*z); result( 1, 1 ) = (t*y*y)+c;     result( 1, 2 ) = (t*y*z)-(s*x); 
      result( 2, 0 ) = (t*x*z)-(s*y); result( 2, 1 ) = (t*y*z)+(s*x); result( 2, 2 ) = (t*z*z)+c;     

      // if 4x3, 3x4, or 4x4, then fill in the rest with ident...
      if (ROWS > 3)
      {
         result( 3, 0 ) = 0.0f; result( 3, 1 ) = 0.0f; result( 3, 2 ) = 0.0f;
      }
                  
      if (COLS > 3)           
      {
         result( 0, 3 ) = 0.0f;
         result( 1, 3 ) = 0.0f;
         result( 2, 3 ) = 0.0f;
         
      }
      
      if (ROWS > 3 && COLS > 3)
      {
         result( 3, 3 ) = 1.0f;
      }

      return result;
   }

   /** Create a matrix using an axis and an angle. 
    *  to a rotation matrix defined by the rotation part of M
    */
   template< typename DATA_TYPE, unsigned ROWS, unsigned COLS >
   inline Matrix<DATA_TYPE, ROWS, COLS> makeRot( DATA_TYPE radians, DATA_TYPE x, DATA_TYPE y, DATA_TYPE z, Type2TypeUU<DATA_TYPE, ROWS, COLS> t = Type2TypeUU<DATA_TYPE, ROWS, COLS>() )
   {
      // (slow -> uses a temporary)
      Matrix<DATA_TYPE, ROWS, COLS> temporary;
      return makeRot( temporary, radians, x, y, z );
   }
   
   /** Create a matrix using euler angles
    */
   template< typename DATA_TYPE, unsigned ROWS, unsigned COLS >
   inline Matrix<DATA_TYPE, ROWS, COLS> makeRot( DATA_TYPE rotx, DATA_TYPE roty, DATA_TYPE rotz, int order, Type2TypeUU<DATA_TYPE, ROWS, COLS> t = Type2TypeUU<DATA_TYPE, ROWS, COLS>() )
   {
      
   }
      
} // end gmtl namespace.

#endif
