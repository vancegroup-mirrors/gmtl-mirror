/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Point3.h,v $
 * Date modified: $Date: 2002-01-18 20:43:12 $
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
#ifndef _GMTL_POINT3_H_
#define _GMTL_POINT3_H_

#include <iostream>
#include <GMTL/gmtlDefines.h>
#include <GMTL/Vec3.h>

namespace gmtl
{

//
// Simple wrapper class so that we can make custom functions for anything
// That needs to know we are a point instead of a vec (ex. Matrix xform)
class Point3 : public Vec3
{

public:
	// Constructor
	Point3() : Vec3()
   {;}
   Point3(const float& _x, const float& _y, const float& _z) : Vec3(_x,_y,_z)
   {;}
   Point3(const Point3& rPoint) : Vec3((Vec3)rPoint)
   {;}
   Point3(const Vec3& rVec) : Vec3(rVec)
   {;}

};


};

#endif
