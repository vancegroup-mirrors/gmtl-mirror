/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: AABoxContainTest.cpp,v $
 * Date modified: $Date: 2002-06-24 03:35:07 $
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
#include "AABoxContainTest.h"
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Containment.h>

namespace gmtlTest
{
   void AABoxContainTest::testIsInVolumePt()
   {
      // Test empty box
      gmtl::AABoxf box;
      gmtl::Point3f origin;
      CPPUNIT_ASSERT(! gmtl::isInVolume(box, origin));

      // Test valid box with pt outside
      gmtl::AABoxf box2(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
      gmtl::Point3f pt1(2,2,2);
      CPPUNIT_ASSERT(! gmtl::isInVolume(box2, pt1));

      //Test valid vox with pt inside
      CPPUNIT_ASSERT(gmtl::isInVolume(box2, origin));
   }

   void AABoxContainTest::testTimingIsInVolumePt()
   {
      gmtl::AABoxf box(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
      gmtl::Point3f origin;
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for(long iter=0;iter<iters; ++iter)
      {
         gmtl::isInVolume(box, origin);
         use_value = use_value + box.mMin[0] + 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxContainTest/IsInVolumePt", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT(use_value > 0.0f);
   }

   void AABoxContainTest::testIsInVolumeAABox()
   {
      // Test valid box against empty box
      gmtl::AABoxf empty;
      gmtl::AABoxf box(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
      CPPUNIT_ASSERT(! gmtl::isInVolume(empty, box));
      CPPUNIT_ASSERT(! gmtl::isInVolume(box, empty));

      // Test non-overlapping valid boxes
      gmtl::AABoxf box2(gmtl::Point3f(30,30,30), gmtl::Point3f(40,40,40));
      CPPUNIT_ASSERT(! gmtl::isInVolume(box, box2));
      CPPUNIT_ASSERT(! gmtl::isInVolume(box2, box));

      // Test overlapping valid boxes
      gmtl::AABoxf box3(gmtl::Point3f(35,35,35), gmtl::Point3f(37,37,37));
      CPPUNIT_ASSERT(gmtl::isInVolume(box2, box3));
      CPPUNIT_ASSERT(gmtl::isInVolume(box3, box2));

      // Test valid box against itself
      CPPUNIT_ASSERT(gmtl::isInVolume(box, box));
   }

   void AABoxContainTest::testTimingIsInVolumeAABox()
   {
      gmtl::AABoxf box(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
      gmtl::AABoxf box2(gmtl::Point3f(0,0,0), gmtl::Point3f(-0.5f, -0.5f, -0.5f));

      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for(long iter=0;iter<iters; ++iter)
      {
         gmtl::isInVolume(box, box2);
         use_value = use_value + box.mMin[0] + 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxContainTest/IsInVolumeAABox", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT(use_value > 0.0f);
   }
}
