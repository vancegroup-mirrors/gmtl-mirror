/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Intersection.h,v $
 * Date modified: $Date: 2002-08-06 21:08:49 $
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
#ifndef _GMTL_INTERSECTION_H_
#define _GMTL_INTERSECTION_H_

#include <gmtl/AABox.h>
#include <gmtl/Point.h>

namespace gmtl
{
   /**
    * Tests if the given AABoxes intersect with each other. Sharing an edge IS
    * considered intersection by this algorithm.
    *
    * @param box1    the first box to test
    * @param box2    the second box to test
    *
    * @return  true if the boxes intersect; false otherwise
    */
   template<class DATA_TYPE>
   bool intersect(const AABox<DATA_TYPE>& box1, const AABox<DATA_TYPE>& box2)
   {
      // Look for a separating axis on each box for each axis
      if (box1.getMin()[0] > box2.getMax()[0])  return false;
      if (box1.getMin()[1] > box2.getMax()[1])  return false;
      if (box1.getMin()[2] > box2.getMax()[2])  return false;

      if (box2.getMin()[0] > box1.getMax()[0])  return false;
      if (box2.getMin()[1] > box1.getMax()[1])  return false;
      if (box2.getMin()[2] > box1.getMax()[2])  return false;

      // No separating axis ... they must intersect
      return true;
   }
   
   /**
    * Tests if the given AABoxe and point intersect with each other. On an edge IS
    * considered intersection by this algorithm.
    *
    * @param box    the box to test
    * @param point  the point to test
    *
    * @return  true if the items intersect; false otherwise
    */
   template<class DATA_TYPE>
   bool intersect( const AABox<DATA_TYPE>& box, const Point<DATA_TYPE, 3>& point )
   {
      // Look for a separating axis on each box for each axis
      if (box.getMin()[0] > point[0])  return false;
      if (box.getMin()[1] > point[1])  return false;
      if (box.getMin()[2] > point[2])  return false;

      if (point[0] > box.getMax()[0])  return false;
      if (point[1] > box.getMax()[1])  return false;
      if (point[2] > box.getMax()[2])  return false;

      // they must intersect
      return true;
   }
}

#endif
