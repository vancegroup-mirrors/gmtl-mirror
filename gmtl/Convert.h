/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Convert.h,v $
 * Date modified: $Date: 2002-05-20 22:39:22 $
 * Version:       $Revision: 1.11 $
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
#ifndef _GMTL_CONVERT_H_
#define _GMTL_CONVERT_H_

#include <gmtl/Matrix.h>
#include <gmtl/Vec.h>
#include <gmtl/Quat.h>
#include <gmtl/Coord.h>

namespace gmtl
{
   /** @ingroup Convert
    *  @name Matrix/Coord
    *  @{
    */
          
   /** Convert Matrix to Coord (Euler Type). 
    * @see Coord
    * @see Matrix
    */
   template <typename DATATYPE, unsigned POSSIZE, unsigned MATCOLS, unsigned MATROWS >
   inline Coord<DATATYPE, POSSIZE, 3>& convert( Coord<DATATYPE, POSSIZE, 3>& eulercoord, const Matrix<DATATYPE, MATROWS, MATCOLS>& mat, RotationOrder order = gmtl::XYZ )
   {
      return setCoord( eulercoord, mat, order );
   }
   
   /** Convert Coord (Euler Type) to Matrix. 
    * @see Coord
    * @see Matrix
    */
   template <typename DATATYPE, unsigned POSSIZE, unsigned MATCOLS, unsigned MATROWS >
   inline Matrix<DATATYPE, MATROWS, MATCOLS>& convert( Matrix<DATATYPE, MATROWS, MATCOLS>& mat, const Coord<DATATYPE, POSSIZE, 3>& eulercoord, RotationOrder order = gmtl::XYZ )
   {
      return setMatrix( mat, eulercoord, order );
   }
   /** @} */
   
   /** @ingroup Convert
    *  @name Vec/Quat
    *  @{
    */

   /** convert vector to a "pure" quaternion.
    *  @post quat = [v,0] = [v0,v1,v2,0]
    */
   template <typename DATA_TYPE>
   Quat<DATA_TYPE>& convert( Quat<DATA_TYPE>& pure_quat, const Vec<DATA_TYPE, 3>& vector )
   {
      gmtl::setPure(pure_quat, vector);
      return pure_quat;
   }
   /** @} */
   
   
   /** @ingroup Convert
    *  @name Matrix/Quat
    * @{
    */
          
   /** convert a quaternion to the rotation part of a 3x3, 3x4, 4x3, or 4x4 matrix. 
    * @todo Implement using setRot
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   Matrix<DATA_TYPE, ROWS, COLS>& convert( Matrix<DATA_TYPE, ROWS, COLS>& mat, const Quat<DATA_TYPE>& q )
   {
      gmtlASSERT( ((ROWS == 3 && COLS == 3) ||
               (ROWS == 3 && COLS == 4) ||
               (ROWS == 4 && COLS == 3) ||
               (ROWS == 4 && COLS == 4)) &&
               "pre conditions not met on convert( mat, quat ) which only converts a quaternion to the rotation part of a 3x3, 3x4, 4x3, or 4x4 matrix." );

      // From Watt & Watt
      DATA_TYPE wx, wy, wz, xx, yy, yz, xy, xz, zz, xs, ys, zs;

      xs = q[Xelt] + q[Xelt]; ys = q[Yelt] + q[Yelt]; zs = q[Zelt] + q[Zelt];
      xx = q[Xelt] * xs;      xy = q[Xelt] * ys;      xz = q[Xelt] * zs;
      yy = q[Yelt] * ys;      yz = q[Yelt] * zs;      zz = q[Zelt] * zs;
      wx = q[Welt] * xs;      wy = q[Welt] * ys;      wz = q[Welt] * zs;

      mat( 0, 0 ) = DATA_TYPE(1.0) - (yy + zz);
      mat( 1, 0 ) = xy + wz;
      mat( 2, 0 ) = xz - wy;

      mat( 0, 1 ) = xy - wz;
      mat( 1, 1 ) = DATA_TYPE(1.0) - (xx + zz);
      mat( 2, 1 ) = yz + wx;

      mat( 0, 2 ) = xz + wy;
      mat( 1, 2 ) = yz - wx;
      mat( 2, 2 ) = DATA_TYPE(1.0) - (xx + yy);

      if (ROWS == 4)
      {
         mat( 3, 0 ) = DATA_TYPE(0.0);
         mat( 3, 1 ) = DATA_TYPE(0.0);
         mat( 3, 2 ) = DATA_TYPE(0.0);
      }

      if (COLS == 4)
      {
         mat( 0, 3 ) = DATA_TYPE(0.0);
         mat( 1, 3 ) = DATA_TYPE(0.0);
         mat( 2, 3 ) = DATA_TYPE(0.0);
      }

      if (ROWS == 4 && COLS == 4)
         mat( 3, 3 ) = DATA_TYPE(1.0);

      return mat;
   }

   /** convert a matrix (3x3, 3x4, 4x3, or 4x4) to a quaternion.
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Quat<DATA_TYPE>& convert( Quat<DATA_TYPE>& quat, const Matrix<DATA_TYPE, ROWS, COLS>& mat  )
   {
      gmtlASSERT( ((ROWS == 3 && COLS == 3) ||
               (ROWS == 3 && COLS == 4) ||
               (ROWS == 4 && COLS == 3) ||
               (ROWS == 4 && COLS == 4)) &&
               "pre conditions not met on convert( quat, pos, mat ) which only converts a quaternion to the rotation part of a 3x3, 3x4, 4x3, or 4x4 matrix." );

      DATA_TYPE tr( mat( 0, 0 ) + mat( 1, 1 ) + mat( 2, 2 ) ), s( 0.0f );

      // If diagonal is positive
      if (tr > (DATA_TYPE)0.0)
      {
         s = Math::sqrt( tr + (DATA_TYPE)1.0 );
         quat[Welt] = s * (DATA_TYPE)0.5;
         s = DATA_TYPE(0.5) / s;

         quat[Xelt] = (mat( 2, 1 ) - mat( 1, 2 )) * s;
         quat[Yelt] = (mat( 0, 2 ) - mat( 2, 0 )) * s;
         quat[Zelt] = (mat( 1, 0 ) - mat( 0, 1 )) * s;
      }

      // when Diagonal is negative
      else
      {
         static const unsigned int nxt[3] = { 1, 2, 0 };
         unsigned int i( Xelt ), j, k;

         if (mat( 1, 1 ) > mat( 0, 0 ))
            i = 1;

         if (mat( 2, 2 ) > mat( i, i ))
            i = 2;

         j = nxt[i];
         k = nxt[j];

         s = Math::sqrt( (mat( i, i )-(mat( j, j )+mat( k, k ))) + (DATA_TYPE)1.0 );

         DATA_TYPE q[4];
         q[i] = s * (DATA_TYPE)0.5;

         if (s != (DATA_TYPE)0.0)
            s = DATA_TYPE(0.5) / s;

         q[3] = (mat( k, j ) - mat( j, k )) * s;
         q[j] = (mat( j, i ) + mat( i, j )) * s;
         q[k] = (mat( k, i ) + mat( i, k )) * s;

         quat[Xelt] = q[0];
         quat[Yelt] = q[1];
         quat[Zelt] = q[2];
         quat[Welt] = q[3];
      }

      return quat;
   }
   /** @} */
   
} // end namespace gmtl.

#endif
