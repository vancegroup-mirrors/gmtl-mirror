/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: matVecFuncs.h,v $
 * Date modified: $Date: 2002-02-15 22:16:08 $
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
#ifndef _GMTL_MAT_VEC_FUNCS_H_
#define _GMTL_MAT_VEC_FUNCS_H_

#include <gmtl/gmtlConfig.h>
#include <gmtl/Matrix.h>
#include <gmtl/Vec3.h>
#include <gmtl/Vec4.h>

namespace gmtl
{

   //////////////////////////////////////////////////////////////
   //                VEC3 OPS
   //////////////////////////////////////////////////////////////
   // Arithmetic ops	
   inline Vec3 operator+ (const Vec3& v1, const Vec3& v2)
   {
      return Vec3(v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2]);
   }

   inline Vec3 operator- (const Vec3& v1, const Vec3& v2)
   {
      return Vec3(v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2]);
   }

   inline Vec3 operator* (const Vec3& v1, const float scalar)
   {
      return Vec3(v1[0]*scalar, v1[1]*scalar, v1[2]*scalar);
   }
   inline Vec3 operator* (const float scalar, const Vec3& v1)
   {
      return v1*scalar;
   }
   inline Vec3 operator/ (const Vec3& v1, const float scalar)
   {
      return Vec3(v1[0]/scalar, v1[1]/scalar, v1[2]/scalar);
   }

   inline Vec3 operator -(const Vec3& v1)
   {
      return Vec3(-v1[0], -v1[1], -v1[2]);
   }

};

#endif


