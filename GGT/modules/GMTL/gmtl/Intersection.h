/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Intersection.h,v $
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
#ifndef _GMTL_INTERSECTION_H_
#define _GMTL_INTERSECTION_H_

namespace gmtl
{
   class OOBox;

   /**
    * Test for intersection of two OOB's
    *
    * @param box0   First box
    * @param box1   Second box
    * @return True - Boxes intersect
    */
   bool TestIntersect(const OOBox& box0, const OOBox& box1);

   // boxes have constant linear velocity
   bool TestIntersect(float time,
                      const OOBox& box0, const Vec3& vel0,
                      const OOBox& box1, const Vec3& vel1);
   bool TestIntersect(float time,
                      const OOBox& box0, const Vec3& vel0,
                      const OOBox& box1, const Vec3& vel1,
                      float& tFirstContact);
}

#endif
