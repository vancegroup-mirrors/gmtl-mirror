/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: gmtlOutput.h,v $
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
#ifndef _GMTL_OUTPUT_H_
#define _GMTL_OUTPUT_H_

// NOTE:
//
//  DO NOT INCLUDE THIS FILE IN ANY .h FILES OF GMTL
//   IT WILL CAUSE DEPENDENCY PROBLEMS
//
// Only use in user code or .cpp gmtl files
//

#include <GMTL/gmtlDefines.h>
#include <iostream>
#include <GMTL/Matrix.h>
#include <GMTL/Vec3.h>
#include <GMTL/Vec4.h>
#include <GMTL/OOBox.h>
#include <GMTL/Tri.h>

std::ostream& operator<<(std::ostream& out, gmtl::Matrix& _mat)
{
   for(int j=0;j<4;j++)
   {
      for(int i=0;i<4;i++)
         out << _mat.mMat[i][j] << " ";
      out << std::endl;
   }

   return out;
}

std::ostream& operator<<(std::ostream& out, gmtl::Vec3& _v)
{
   out << "[" << _v[0] << ", " << _v[1] << ", " << _v[2] << "]";
   return out;
}

std::ostream& operator<<(std::ostream& out, gmtl::Vec4& _v)
{
   out << "[" << _v[0] << ", " << _v[1] << ", " << _v[2] << ", " << _v[3] << "]";
   return out;
}

std::ostream& operator<<(std::ostream& out, gmtl::OOBox& box)
{
   out << "( cntr: " << box.center() << std::endl
       << "    ax: " << box.axis(0) << " xh:" << box.halfLen(0) << std::endl
       << "    ay: " << box.axis(1) << " yh:" << box.halfLen(1) << std::endl
       << "    az: " << box.axis(2) << " zh:" << box.halfLen(2) << std::endl;
   return out;
}

std::ostream& operator<<(std::ostream& out, gmtl::Tri& tri)
{
   out << "( v0:" << tri[0] << " v1:" << tri[1] << " v2:" << tri[2] << " ";
   return out;
}




#endif

