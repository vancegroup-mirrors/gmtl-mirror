/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: PlaneTest.h,v $
 * Date modified: $Date: 2002-01-31 00:56:20 $
 * Version:       $Revision: 1.3 $
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
#include <gfxConfig.h>
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Plane.h>

namespace gmtlTest
{

class PlaneTest : public CppUnit::TestCase
{
public:
   PlaneTest( std::string name = "PlaneTest")
   : TestCase (name),
      origin(gmtl::ZeroVec3),
      x1_pt(gmtl::XUnitVec3),
      y1_pt(gmtl::YUnitVec3),
      z1_pt(gmtl::ZUnitVec3)
   {;}

   virtual ~PlaneTest()
   {}

   virtual void setUp()
   {
      xy_plane = gmtl::Plane(origin,x1_pt,y1_pt);
      zx_plane = gmtl::Plane(origin,z1_pt,x1_pt);
      yz_plane = gmtl::Plane(origin,y1_pt,z1_pt);
   }

   virtual void tearDown()
   {;}

   // ------------------------
   // CREATION TESTS
   // ------------------------
   void testThreePtCreation()
   {
     // Check normals of the standard planes
     CPPUNIT_ASSERT(xy_plane.mNorm == gmtl::ZUnitVec3);   // Z-Plane
     CPPUNIT_ASSERT(zx_plane.mNorm == gmtl::YUnitVec3);   // Y-Plane
     CPPUNIT_ASSERT(yz_plane.mNorm == gmtl::XUnitVec3);   // Z-Plane
     CPPUNIT_ASSERT(xy_plane.mOffset == 0.0f);
     CPPUNIT_ASSERT(zx_plane.mOffset == 0.0f);
     CPPUNIT_ASSERT(yz_plane.mOffset == 0.0f);

     // Test offset of some simple planes
     gmtl::Plane test_plane;
     test_plane = gmtl::Plane(gmtl::Point3(1.0,0.0,0.0), gmtl::Point3(1.0,1.0,0.0), gmtl::Point3(1.0,0.0,1.0));
     CPPUNIT_ASSERT(test_plane.mNorm == gmtl::XUnitVec3);
     CPPUNIT_ASSERT(test_plane.mOffset == 1.0f);
   }

   void testNormPtCreation()
   {
      gmtl::Plane test_plane;
      test_plane = gmtl::Plane(gmtl::XUnitVec3, origin);    // X-axis through origin
      CPPUNIT_ASSERT(test_plane.mNorm == gmtl::XUnitVec3);
      CPPUNIT_ASSERT(test_plane.mOffset == 0.0f);

      test_plane = gmtl::Plane(gmtl::XUnitVec3, x1_pt);    // X-axis through 1,0,0
      CPPUNIT_ASSERT(test_plane.mNorm == gmtl::XUnitVec3);
      CPPUNIT_ASSERT(test_plane.mOffset == 1.0f);

      test_plane = gmtl::Plane(gmtl::ZUnitVec3, x1_pt);    // Z-axis through 1,0,0
      CPPUNIT_ASSERT(test_plane.mNorm == gmtl::ZUnitVec3);
      CPPUNIT_ASSERT(test_plane.mOffset == 0.0f);

      test_plane = gmtl::Plane(gmtl::ZUnitVec3, gmtl::Point3(0,0,-1));    // Z-axis through 0,0,-1
      CPPUNIT_ASSERT(test_plane.mNorm == gmtl::ZUnitVec3);
      CPPUNIT_ASSERT(test_plane.mOffset == -1.0f);
   }

   void testNormOffsetCreation()
   {
      gmtl::Plane test_plane;
      test_plane = gmtl::Plane(gmtl::XUnitVec3, 0.0f);    // X-axis through origin
      CPPUNIT_ASSERT(test_plane.mNorm == gmtl::XUnitVec3);
      CPPUNIT_ASSERT(test_plane.mOffset == 0.0f);
   }

   // --------------------------
   // Dist and side tests
   // --------------------------
   void testDistToPt()
   {
      float dist;

      dist = xy_plane.distanceToPt(gmtl::ZUnitVec3);
      CPPUNIT_ASSERT(dist == 1.0f);

      dist = xy_plane.distanceToPt(gmtl::Point3(-12.0,5.0,-17.0f));
      CPPUNIT_ASSERT(dist == -17.0f);

      gmtl::Plane slanted_plane(gmtl::Vec3(1.0f,1.0f,1.0f), origin);
      dist = slanted_plane.distanceToPt(origin);
      CPPUNIT_ASSERT(dist == 0.0f);

      dist = slanted_plane.distanceToPt(gmtl::Vec3(1.0f,1.0f,1.0f));
      CPPUNIT_ASSERT(dist > 0.0f);
   }

   void testWhichSide()
   {
      gmtl::Plane::Side answer;

      answer = xy_plane.whichSide(gmtl::Point3(0.0,0.0,1.0));
      CPPUNIT_ASSERT(answer == gmtl::Plane::POS_SIDE);

      answer = xy_plane.whichSide(gmtl::Point3(0.0,0.0,-12.0f));
      CPPUNIT_ASSERT(answer == gmtl::Plane::NEG_SIDE);

      answer = zx_plane.whichSide(gmtl::Point3(0.0,1e-10f,0.0f));
      CPPUNIT_ASSERT(answer == gmtl::Plane::POS_SIDE);

      answer = zx_plane.whichSide(gmtl::Point3(0.0,-1e-10f,0.0f));
      CPPUNIT_ASSERT(answer == gmtl::Plane::NEG_SIDE);

      answer = xy_plane.whichSide(gmtl::Point3(0.0,0.0,0.0));
      CPPUNIT_ASSERT(answer == gmtl::Plane::ON_PLANE);
   }

   void testFindNearestPt()
   {
      gmtl::Point3 answer, test_point;
      //float dist;

      // XY dist to point off origin
      test_point = gmtl::Point3(0.0,0.0,1.0);
      CPPUNIT_ASSERT(xy_plane.distanceToPt(test_point) == xy_plane.findNearestPt(test_point, answer));
      CPPUNIT_ASSERT(answer == gmtl::Point3(0.0,0.0,0.0));

      // XY dist to point at 12,21
      test_point = gmtl::Point3(12.0,-21.0,-13.0);
      CPPUNIT_ASSERT(xy_plane.distanceToPt(test_point) == xy_plane.findNearestPt(test_point, answer));
      CPPUNIT_ASSERT(answer == gmtl::Point3(12.0,-21.0,0.0));

      // XY dist to point on plane at -17.05, 0.334
      test_point = gmtl::Point3(-17.05,0.334,0.0);
      CPPUNIT_ASSERT(xy_plane.distanceToPt(test_point) == xy_plane.findNearestPt(test_point, answer));
      CPPUNIT_ASSERT(answer == test_point);
   }


   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("PlaneTest");
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testThreePtCreation", &PlaneTest::testThreePtCreation));
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testNormPtCreation", &PlaneTest::testNormPtCreation));
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testNormOffsetCreation", &PlaneTest::testNormOffsetCreation));
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testDistToPt", &PlaneTest::testDistToPt));
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testWhichSide", &PlaneTest::testWhichSide));
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testFindNearestPt", &PlaneTest::testFindNearestPt));

      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("PlaneTestInteractive");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:
   gmtl::Vec3 origin;
   gmtl::Vec3 x1_pt;
   gmtl::Vec3 y1_pt;
   gmtl::Vec3 z1_pt;

   gmtl::Plane xy_plane;
   gmtl::Plane zx_plane;
   gmtl::Plane yz_plane;
};

};
