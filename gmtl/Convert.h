/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Convert.h,v $
 * Date modified: $Date: 2002-02-20 21:39:41 $
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
#ifndef _GMTL_CONVERT_H_
#define _GMTL_CONVERT_H_

namespace gmtl
{
   /** convert a quaternion to the rotation part of a 3x3, 3x4, or 4x4 matrix. */
   /*
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   void convert( Matrix<DATA_TYPE, ROWS, COLS>& mat, const Quat<DATA_TYPE>& q )
   {
      ggtASSERT( ((ROWS == 3 && COLS == 3) ||
               (ROWS == 3 && COLS == 4) ||
               (ROWS == 4 && COLS == 4)) && 
               "pre conditions not met on convert( mat, quat )" );

      // From Watt & Watt
      DATA_TYPE wx, wy, wz, xx, yy, yz, xy, xz, zz, xs, ys, zs;
      
      xs = q[VJ_X] + q[VJ_X];    ys = q[VJ_Y] + q[VJ_Y];    zs = q[VJ_Z] + q[VJ_Z];
      xx = q[VJ_X] * xs;   xy = q[VJ_X] * ys;   xz = q[VJ_X] * zs;
      yy = q[VJ_Y] * ys;   yz = q[VJ_Y] * zs;   zz = q[VJ_Z] * zs;
      wx = q[VJ_W] * xs;   wy = q[VJ_W] * ys;   wz = q[VJ_W] * zs;

      mat( 0, 0 ) = 1.0 - (yy+zz);
      mat( 1, 0 ) = xy+wz;
      mat( 2, 0 ) = xz-wy;
 
      mat( 0, 1 ) = xy-wz;
      mat( 1, 1 ) = 1.0 - (xx+zz);
      mat( 2, 1 ) = yz+wx;
 
      mat( 0, 2 ) = xz+wy;
      mat( 1, 2 ) = yz-wx;
      mat( 2, 2 ) = 1.0 - (xx+yy);

      if (ROWS == 4)
      {
         mat( 3, 0 ) = 0.0;
         mat( 3, 1 ) = 0.0;
         mat( 3, 2 ) = 0.0;
      }

      if (COLS == 4)
      {
         mat( 0, 3 ) = 0.0;
         mat( 1, 3 ) = 0.0;
         mat( 2, 3 ) = 0.0;
      }

      if (ROWS == 4 && COLS == 4)
         mat( 3, 3 ) = 1.0;
   }
   */
} // end namespace gmtl.

#endif
