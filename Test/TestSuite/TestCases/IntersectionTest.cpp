/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: IntersectionTest.cpp,v $
 * Date modified: $Date: 2002-07-28 23:55:18 $
 * Version:       $Revision: 1.1 $
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
#include "IntersectionTest.h"
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Intersection.h>

namespace gmtlTest
{
   void IntersectionTest::testIntersectAABoxAABox()
   {
      // Test overlapping boxes
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
         gmtl::AABoxf box2(gmtl::Point3f(0,0,0), gmtl::Point3f(2,2,2));
         CPPUNIT_ASSERT(gmtl::intersect(box1, box2));
      }

      // Test boxes with shared edge
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::AABoxf box2(gmtl::Point3f(0,0,0), gmtl::Point3f(-1,-1,-1));
         CPPUNIT_ASSERT(gmtl::intersect(box1, box2));
      }

      // Test non-overlapping boxes
      {
         gmtl::AABoxf box1(gmtl::Point3f(-2,-2,-2), gmtl::Point3f(-1,-1,-1));
         gmtl::AABoxf box2(gmtl::Point3f(1,1,1), gmtl::Point3f(2,2,2));
         CPPUNIT_ASSERT(! gmtl::intersect(box1, box2));
      }
   }

   void IntersectionTest::testTimingIntersectAABoxAABox()
   {
      gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
      gmtl::AABoxf box2(gmtl::Point3f(0,0,0), gmtl::Point3f(2,2,2));
      const long iters(400000);
      unsigned true_count(0);
      CPPUNIT_METRIC_START_TIMING();

      for(long iter=0;iter<iters; ++iter)
      {
         if (gmtl::intersect(box1, box2))
         {
            ++true_count;
         }
         box2.mMax[0] += 0.01;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("IntersectionTest/IntersectAABoxAABox", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT(true_count > 0.0f);
   }
}
