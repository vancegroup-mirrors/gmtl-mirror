/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Xforms.h,v $
 * Date modified: $Date: 2002-01-18 20:43:11 $
 * Version:       $Revision: 1.1.1.1 $
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
#ifndef _XFORMS_H_
#define _XFORMS_H_

#include <GMTL/gmtlDefines.h>
#include <GMTL/Matrix.h>
#include <GMTL/Vec3.h>
#include <GMTL/Vec4.h>
#include <GMTL/Point3.h>
#include <GMTL/OOBox.h>
#include <GMTL/matVecFuncs.h>


namespace gmtl
{

Vec4 operator*(const Matrix& _m, const Vec4& _v)
{
   // Take _v by value in case it is me
   // Treating Vector like a column vector
   // (4x4)(4x1) = (4x1)
   // | A B C D | | X |   | AX+BY+CZ+DW |
   // | E F G H | | Y | = | EY+FY+GY+HY |
   // | I J K L | | Z |   | IZ+JZ+KZ+LZ |
   // | M N O P | | W |   | MX+NY+OZ+PW |

   Vec4 ret_vec;
   for(int iRow=0;iRow<4;iRow++)
   {
      ret_vec[iRow] = (_v[0]* (_m[0][iRow]))
                    + (_v[1]* (_m[1][iRow]))
                    + (_v[2]* (_m[2][iRow]))
                    + (_v[3]* (_m[3][iRow]));
   }
   return ret_vec;
}


// XXX: Assuming that there is no projective portion to the matrix or homogeneous coord
// NOTE: It is a vec, so we don't deal with the translation
Vec3 operator*(const Matrix& mat, const Vec3& vec)
{

   Vec3 ret_vec;
   for(int iRow=0;iRow<3;iRow++)
   {
      ret_vec[iRow] = (vec[0]* (mat[0][iRow]))
                    + (vec[1]* (mat[1][iRow]))
                    + (vec[2]* (mat[2][iRow]));
   }
   return ret_vec;
}

// XXX: Assuming no projective or homogeneous coord to the mat
Point3 operator*(const Matrix& mat, const Point3& point)
{
   Point3 ret_pt;
   for(int iRow=0;iRow<3;iRow++)
   {
      ret_pt[iRow] = (point[0]* (mat[0][iRow]))
                   + (point[1]* (mat[1][iRow]))
                   + (point[2]* (mat[2][iRow]))
                   + (mat[3][iRow]);
   }
   return ret_pt;
}

// Xform an OOB by a matrix
// NOTE: This will NOT work if the matrix has shear or scale
OOBox operator*(const Matrix& mat, const OOBox& box)
{
   OOBox ret_box;

   ret_box.center() = mat * box.center();

   ret_box.axis(0) = mat * ret_box.axis(0);
   ret_box.axis(1) = mat * ret_box.axis(1);
   ret_box.axis(2) = mat * ret_box.axis(2);

   ret_box.halfLen(0) = box.halfLen(0);
   ret_box.halfLen(1) = box.halfLen(1);
   ret_box.halfLen(2) = box.halfLen(2);

   return ret_box;
}


};

#endif
