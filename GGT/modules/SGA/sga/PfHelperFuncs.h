/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: PfHelperFuncs.h,v $
 * Date modified: $Date: 2002-01-18 20:43:10 $
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
#ifndef _PF_HELPER_FUNCS_
#define _PF_HELPER_FUNCS_

#include <Performer/pr/pfLinMath.h>
#include <GMTL/Point3.h>
#include <GMTL/Vec3.h>
#include <GMTL/Matrix.h>

namespace sga
{
   inline gmtl::Point3 getPoint3(const pfVec3& pf_vec)
   {
      return gmtl::Point3(pf_vec[0], pf_vec[1], pf_vec[2]);
   }

   inline gmtl::Vec3 getVec3(const pfVec3& pf_vec)
   {
      return gmtl::Vec3(pf_vec[0], pf_vec[1], pf_vec[2]);
   }

   inline pfVec3 getPfVec3(const gmtl::Vec3& vec)
   {
      return pfVec3(vec[0], vec[1], vec[2]);
   }

   template<bool _Xform>
   inline pfMatrix getPfMatrix(const gmtl::Matrix& mat)
   {
      if(_Xform)
      {
         std::cerr << "pfMatrix getPrfmatrix(...,true) not implemented." << std::endl;
         return pfMatrix();
      }
      else
      {
         pfMatrix  pf_mat;
         pf_mat.set(const_cast<float*>(mat.floatPtr()));
         return pf_mat;
      }
   }

   template<bool _Xform>
   inline gmtl::Matrix getMatrix(const pfMatrix& pf_mat)
   {
      if(_Xform)
      {
         std::cerr << "Matrix getMatrix(pfMat,true) not implemented." << std::endl;
         return gmtl::Matrix();
      }
      else
      {
         gmtl::Matrix mat;
         mat.set( &pf_mat[0][0]);
         return mat;
      }
   }
};


#endif
