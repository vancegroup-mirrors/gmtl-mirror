/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: AABox.h,v $
 * Date modified: $Date: 2002-02-10 04:38:07 $
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
#ifndef _GMTL_AABox_H_
#define _GMTL_AABox_H_

#include <gmtl/gmtlConfig.h>
#include <gmtl/Vec3.h>

#include <vector>

namespace gmtl
{

// AABox : Defines an axially aligned box
class  AABox
{

public:
   AABox()
   { makeEmpty(); }

   AABox(AABox& box)
   {
      mMin = box.mMin;
      mMax = box.mMax;
      mEmpty = box.mEmpty;
   }

public:
   //CAPI:verb
   void  makeEmpty()
   {
      mEmpty = 1;
      mMin = ZeroVec3;
      mMax = ZeroVec3;
   }

   // Containment tests
   bool  contains(const Point3& pt) const;
   bool   contains(const AABox& box);
   //int   contains(const sgSphere& sphere) const;

   // EXTEND box around the following
   // POST: Box is set to one that contains all the given pts
   void  around(std::vector<Point3>& pts);
   void  around(std::vector<Vec3>& pts);
   // POST: Box is set to a new one that contains all the passed boxes
   void  around(std::vector<AABox>& boxes);

   // Extends the box to contaian the given pt
   inline void  extendBy(const Point3& pt);

   // POST: (This) contains everything it used to AND the passed box
   inline void  extendBy(const AABox& box);

public:
   Vec3  mMin;    // The min point
   Vec3  mMax;    // The max point
   bool  mEmpty;     // Is the box empty?
};


//---------------------------------------------------------------------
//---------------------------------------------------------------------
inline bool  AABox::contains(const Point3& pt) const
{
   if(!mEmpty)
   {
      return ( pt[0] >= mMin[0] &&
               pt[1] >= mMin[1] &&
               pt[2] >= mMin[2] &&
               pt[0] <= mMax[0] &&
               pt[1] <= mMax[1] &&
               pt[2] <= mMax[2]);
   }
   else
      return false;
}


   // retVal = 1.  There is an intersection
   //       0.  There is NO intersection
inline bool AABox::contains(const AABox& box)
{
      // Test for box not overlapping in any axis
   if (mMax[0] < box.mMin[0] || mMin[0] > box.mMax[0] ||
      mMax[1] < box.mMin[1] || mMin[1] > box.mMax[1] ||
      mMax[2] < box.mMin[2] || mMin[2] > box.mMax[2] )
   {
      return false;
   } else {
      return true;
   }
}

inline void  AABox::around(std::vector<Point3>& pts)
{
   for(unsigned i=0; i<pts.size(); i++)
      extendBy(pts[i]);
}

inline void  AABox::around(std::vector<Vec3>& pts)
{
   for(unsigned i=0; i<pts.size(); i++)
      extendBy(pts[i]);
}



// POST: Box is set to a new one that contains all the passed boxes
inline void  AABox::around(std::vector<AABox>& boxes)
{
   for(unsigned i=0;i<boxes.size(); i++)
      extendBy(boxes[i]);
}


inline void  AABox::extendBy(const Point3& pt)
{
   if(!mEmpty)
   {
      if(pt[0] > mMax[0])           // X coord
         mMax[0] = pt[0];
      else if(pt[0] < mMin[0])
         mMin[0] = pt[0];
      if(pt[1] > mMax[1])           // Y Coord
         mMax[1] = pt[1];
      else if(pt[1] < mMin[1])
         mMin[1] = pt[1];
      if(pt[2] > mMax[2])           // Z Coord
         mMax[2] = pt[2];
      else if(pt[2] < mMin[2])
         mMin[2] = pt[2];

   } else {
      mMin = pt;
      mMax = pt;
      mEmpty = false;      // We are not empty anymore
   }
}

// POST: (This) contains everything it used to AND the passed box
inline void  AABox::extendBy(const AABox& box)
{
   extendBy(box.mMin);     // Just extend by the coords of the box
   extendBy(box.mMax);
}

/*
// Sends the GL_LINE commands to draw the box
   // PRE: State is set and color is set to draw
   void draw()
   {
      glBegin(GL_LINES);
      glVertex3f(min[0], min[1], min[2]); glVertex3f(max[0], min[1], min[2]); // 000 100  Bottom
      glVertex3f(max[0], min[1], min[2]); glVertex3f(max[0], min[1], max[2]); // 100 101
      glVertex3f(max[0], min[1], max[2]); glVertex3f(min[0], min[1], max[2]); // 101 001
      glVertex3f(min[0], min[1], max[2]); glVertex3f(min[0], min[1], min[2]); // 001 000

      glVertex3f(min[0], max[1], min[2]); glVertex3f(max[0], max[1], min[2]); // 010 110  top
      glVertex3f(max[0], max[1], min[2]); glVertex3f(max[0], max[1], max[2]); // 110 111
      glVertex3f(max[0], max[1], max[2]); glVertex3f(min[0], max[1], max[2]); // 111 011
      glVertex3f(min[0], max[1], max[2]); glVertex3f(min[0], max[1], min[2]); // 011 010

      glVertex3f(min[0], min[1], min[2]); glVertex3f(min[0], max[1], min[2]); // 000 010  sides
      glVertex3f(max[0], min[1], min[2]); glVertex3f(max[0], max[1], min[2]); // 100 110
      glVertex3f(max[0], min[1], max[2]); glVertex3f(max[0], max[1], max[2]); // 101 111
      glVertex3f(min[0], min[1], max[2]); glVertex3f(min[0], max[1], max[2]); // 001 011
      glEnd();
   }
   */


};

#endif
