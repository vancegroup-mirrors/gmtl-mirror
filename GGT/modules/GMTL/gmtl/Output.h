/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Output.h,v $
 * Date modified: $Date: 2002-03-20 19:49:12 $
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
#ifndef _GMTL_OUTPUT_H_
#define _GMTL_OUTPUT_H_

#include <gmtl/gmtlConfig.h>
#include <gmtl/Assert.h>
#include <iostream>

#include <gmtl/VecBase.h>
#include <gmtl/Matrix.h>
#include <gmtl/Quat.h>
#include <gmtl/Tri.h>
#include <gmtl/Plane.h>
#include <gmtl/Sphere.h>

namespace gmtl
{
   /**
    * Outputs a string representation of the given VecBase type to the given
    * output stream. This works for both Point and Vec types. The output is
    * formatted such that Vec<int, 4>(1,2,3,4) will appear as "(1, 2, 3, 4)".
    *
    * @param out     the stream to write to
    * @param v       the VecBase type to output
    *
    * @return  out after it has been written to
    */
   template< class DATA_TYPE, unsigned SIZE >
   std::ostream& operator<<( std::ostream& out,
                             const VecBase<DATA_TYPE, SIZE>& v )
   {
      out << "(";
      for ( unsigned i=0; i<SIZE; ++i )
      {
         if ( i != 0 )
         {
            out << ", ";
         }
         out << v[i];
      }
      out << ")";
      return out;
   }

   /**
    * Outputs a string representation of the given Matrix to the given output
    * stream. The output is formatted along the lines of:
    * <pre>
    *    | 1 2 3 4 |
    *    | 5 6 7 8 |
    *    | 9 10 11 12 |
    * </pre>
    *
    * @param out     the stream to write to
    * @param m       the Matrix to output
    *
    * @return  out after it has been written to
    */
   template< class DATA_TYPE, unsigned ROWS, unsigned COLS >
   std::ostream& operator<<( std::ostream& out,
                             const Matrix<DATA_TYPE, ROWS, COLS>& m )
   {
      for ( unsigned row=0; row<ROWS; ++row )
      {
         out << "|";
         for ( unsigned col=0; col<COLS; ++col )
         {
            out << " " << m(row, col);
         }
         out << " |" << std::endl;
      }
      return out;
   }

   /**
    * Outputs a string representation of the given Matrix to the given output
    * stream. The output is formatted such that Quat<int>(1,2,3,4) will appear
    * as "(1, 2, 3, 4)".
    *
    * @param out     the stream to write to
    * @param q       the Quat to output
    *
    * @return  out after it has been written to
    */
   template< typename DATA_TYPE >
   std::ostream& operator<<( std::ostream& out, const Quat<DATA_TYPE>& q )
   {
      out << q.mData;
      return out;
   }

   /**
    * Outputs a string representation of the given Tri to the given output
    * stream. The output is formatted along the lines of:
    * <pre>
    *    (1, 2, 3), (4, 5, 6), (7, 8, 9)
    * </pre>
    *
    * @param out     the stream to write to
    * @param t       the Tri to output
    *
    * @return  out after it has been written to
    */
   template< typename DATA_TYPE >
   std::ostream& operator<<( std::ostream& out, const Tri<DATA_TYPE> &t )
   {
      out << t[0] << ", " << t[1] << ", " << t[2];
      return out;
   }

   /**
    * Outputs a string representation of the given Plane to the given output
    * stream. The output is formatted along the lines of:
    * <pre>
    *   (1, 2, 3), 4
    * </pre>
    *
    * @param out     the stream to write to
    * @param p       the Plane to output
    *
    * @return  out after it has been written to
    */
   template< typename DATA_TYPE >
   std::ostream& operator<<( std::ostream& out, const Plane<DATA_TYPE> &p )
   {
      out << p.mNorm << ", " << p.mOffset;
      return out;
   }
} // end namespace gmtl

#endif
