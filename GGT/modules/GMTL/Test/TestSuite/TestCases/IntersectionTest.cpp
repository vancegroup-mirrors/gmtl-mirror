/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: IntersectionTest.cpp,v $
 * Date modified: $Date: 2003-02-05 22:50:39 $
 * Version:       $Revision: 1.6 $
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
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Intersection.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(IntersectionTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(IntersectionMetricTest, Suites::metric());

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

   void IntersectionMetricTest::testTimingIntersectAABoxAABox()
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
   
   
   
   void IntersectionTest::testIntersectAABoxPoint()
   {
      // Test point in box
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
         gmtl::Point3f point(gmtl::Point3f(0,0,0));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }

      //////////
      
      // test point on edge (bottom face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,-1,-0.5f));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }
      // test point on edge (top face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,0,-0.5f));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }
      // test point on edge (left face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-1.0f,-0.5,-0.5f));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }
      // test point on edge (right face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(0.0f,-0.5,-0.5f));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }
      // test point on edge (near face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,-0.5,0.0f));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }
      // test point on edge (far face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,-0.5,-1.0f));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }
      
      /////////

      // test point outside (bottom face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,-1.01,-0.5f));
         CPPUNIT_ASSERT(!gmtl::intersect(box1, point));
      }
      // test point outside (top face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,0.01,-0.5f));
         CPPUNIT_ASSERT(!gmtl::intersect(box1, point));
      }
      // test point outside (left face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-1.01f,-0.5,-0.5f));
         CPPUNIT_ASSERT(!gmtl::intersect(box1, point));
      }
      // test point outside (right face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(0.01f,-0.5,-0.5f));
         CPPUNIT_ASSERT(!gmtl::intersect(box1, point));
      }
      // test point outside (near face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,-0.5,0.01f));
         CPPUNIT_ASSERT(!gmtl::intersect(box1, point));
      }
      // test point outside (far face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,-0.5,-1.01f));
         CPPUNIT_ASSERT(!gmtl::intersect(box1, point));
      }
      
      // @todo, could use more rigorous testing here, test all sides of the box, 
      //        in and out and on the edges...
   }

   void IntersectionMetricTest::testTimingIntersectAABoxPoint()
   {
      gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
      gmtl::Point3f point(gmtl::Point3f(-0.5f,-0.5,-1.01f));
      const long iters(400000);
      unsigned true_count(0);
      CPPUNIT_METRIC_START_TIMING();

      for(long iter=0;iter<iters; ++iter)
      {
         if (gmtl::intersect(box1, point))
         {
            ++true_count;
         }
         point[0] += 0.01;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("IntersectionTest/IntersectAABoxPoint", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT(true_count == 0);
   }

   void IntersectionTest::testIntersectAABoxSphere()
   {
      // Overlapping
      {
         gmtl::AABoxf box(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Spheref sph(gmtl::Point3f(0,0,0), 2);
         CPPUNIT_ASSERT(gmtl::intersect(box, sph));
         CPPUNIT_ASSERT(gmtl::intersect(sph, box));
      }
      // Shared edge
      {
         gmtl::AABoxf box(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Spheref sph(gmtl::Point3f(2,0,0), 2);
         CPPUNIT_ASSERT(gmtl::intersect(box, sph));
         CPPUNIT_ASSERT(gmtl::intersect(sph, box));
      }
      // Non-overlapping
      {
         gmtl::AABoxf box(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Spheref sph(gmtl::Point3f(3,3,3), 2);
         CPPUNIT_ASSERT(! gmtl::intersect(box, sph));
         CPPUNIT_ASSERT(! gmtl::intersect(sph, box));
      }
   }

   void IntersectionTest::testIntersectAABoxSweep()
   {
      gmtl::AABoxf box1(gmtl::Point3f(-3,1,-3), gmtl::Point3f(-2,2,-2));
      gmtl::AABoxf box2(gmtl::Point3f( 2,1,-3), gmtl::Point3f( 3,3,-2));
      gmtl::Vec3f path1(5,0,0);
      gmtl::Vec3f path2(-5,0,0);

      float first, second;
      bool result = gmtl::intersect(box1, path1, box2, path2, first, second);
      CPPUNIT_ASSERT(result);
      CPPUNIT_ASSERT(first == 0.4f);
      CPPUNIT_ASSERT(second == 0.6f);
   }

   void IntersectionMetricTest::testTimingIntersectAABoxSweep()
   {
      gmtl::AABoxf box1(gmtl::Point3f(-3,1,-3), gmtl::Point3f(-2,2,-2));
      gmtl::AABoxf box2(gmtl::Point3f( 2,1,-3), gmtl::Point3f( 3,3,-2));
      gmtl::Vec3f path1(1,0,0);
      gmtl::Vec3f path2(-5,0,0);
      float first, second;

      const long iters(400000);
      unsigned true_count(0);
      CPPUNIT_METRIC_START_TIMING();

      for(long iter=0;iter<iters; ++iter)
      {
         if (gmtl::intersect(box1, path1, box2, path2, first, second))
         {
            ++true_count;
         }
         path1[0] += 0.1f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("IntersectionTest/IntersectAABoxSweep", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT(true_count > 0);
   }

   void IntersectionTest::testIntersectSphereSweep()
   {
      gmtl::Spheref sph1(gmtl::Point3f(-3,1,-3), 2);
      gmtl::Spheref sph2(gmtl::Point3f( 2,1,-3), 1);
      gmtl::Vec3f path1(5,0,0);
      gmtl::Vec3f path2(-5,0,0);

      float first, second;
      bool result = gmtl::intersect(sph1, path1, sph2, path2, first, second);
      CPPUNIT_ASSERT(result);
      CPPUNIT_ASSERT(gmtl::Math::isEqual(first, 0.2f, 0.001f));
      CPPUNIT_ASSERT(gmtl::Math::isEqual(second, 0.8f, 0.001f));
   }

   void IntersectionMetricTest::testTimingIntersectSphereSweep()
   {
      gmtl::Spheref sph1(gmtl::Point3f(-3,1,-3), 2);
      gmtl::Spheref sph2(gmtl::Point3f( 2,1,-3), 1);
      gmtl::Vec3f path1(1,0,0);
      gmtl::Vec3f path2(-5,0,0);
      float first, second;

      const long iters(400000);
      unsigned true_count(0);
      CPPUNIT_METRIC_START_TIMING();

      for(long iter=0;iter<iters; ++iter)
      {
         if (gmtl::intersect(sph1, path1, sph2, path2, first, second))
         {
            ++true_count;
         }
         path1[0] += 0.1f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("IntersectionTest/IntersectSphereSweep", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT(true_count > 0);
   }
}
