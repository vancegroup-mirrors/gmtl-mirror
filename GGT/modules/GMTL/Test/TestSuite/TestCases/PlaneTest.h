/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: PlaneTest.h,v $
 * Date modified: $Date: 2002-02-18 23:22:15 $
 * Version:       $Revision: 1.8 $
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
#include <gmtl/gmtlConfig.h>
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Plane.h>
#include <gmtl/PlaneOps.h>

namespace gmtlTest
{

class PlaneTest : public CppUnit::TestCase
{
public:
   PlaneTest( std::string name = "PlaneTest")
   : TestCase (name)
   {;}

   virtual ~PlaneTest()
   {}

   virtual void setUp()
   {
      origin.set( 0,0,0 );
      x1_v.set( 1,0,0 );
      y1_v.set( 0,1,0 );
      z1_v.set( 0,0,1 );
      x1_pt.set( 1,0,0 );
      y1_pt.set( 0,1,0 );
      z1_pt.set( 0,0,1 );
      xy_plane = gmtl::Plane<float>(origin,x1_pt,y1_pt);
      zx_plane = gmtl::Plane<float>(origin,z1_pt,x1_pt);
      yz_plane = gmtl::Plane<float>(origin,y1_pt,z1_pt);
   }

   virtual void tearDown()
   {;}

   // ------------------------
   // CREATION TESTS
   // ------------------------
   void testCreation()
   {
      gmtl::Plane<float> test_plane;
      gmtl::Vec<float, 3> zeroVec(0,0,0);
      CPPUNIT_ASSERT( test_plane.mNorm == zeroVec );
      CPPUNIT_ASSERT( test_plane.mOffset == 0.0f );

      // Test overhead of creation
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Plane<float> test_plane2;
         test_plane.mOffset = 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/DefaultCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testThreePtCreation()
   {
      // Check normals of the standard planes
      CPPUNIT_ASSERT(xy_plane.mNorm == z1_v);    // Z-Plane
      CPPUNIT_ASSERT(zx_plane.mNorm == y1_v);    // Y-Plane
      CPPUNIT_ASSERT(yz_plane.mNorm == x1_v);    // Z-Plane
      CPPUNIT_ASSERT(xy_plane.mOffset == 0.0f);
      CPPUNIT_ASSERT(zx_plane.mOffset == 0.0f);
      CPPUNIT_ASSERT(yz_plane.mOffset == 0.0f);

      // Test offset of some simple planes
      gmtl::Plane<float> test_plane;
      test_plane = gmtl::Plane<float>(
           gmtl::Point<float, 3>(1.0,0.0,0.0),
           gmtl::Point<float, 3>(1.0,1.0,0.0),
           gmtl::Point<float, 3>(1.0,0.0,1.0)
      );
      CPPUNIT_ASSERT(test_plane.mNorm == x1_v);
      CPPUNIT_ASSERT(test_plane.mOffset == 1.0f);

      // Test overhead of creation
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Plane<float> test_plane( x1_pt, y1_pt, z1_pt );
         test_plane.mOffset = 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/ThreePtCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testNormPtCreation()
   {
      gmtl::Plane<float> test_plane;
      test_plane = gmtl::Plane<float>(x1_v, origin);    // X-axis through origin
      CPPUNIT_ASSERT(test_plane.mNorm == x1_v);
      CPPUNIT_ASSERT(test_plane.mOffset == 0.0f);

      test_plane = gmtl::Plane<float>(x1_v, x1_pt);    // X-axis through 1,0,0
      CPPUNIT_ASSERT(test_plane.mNorm == x1_v);
      CPPUNIT_ASSERT(test_plane.mOffset == 1.0f);

      test_plane = gmtl::Plane<float>(z1_v, x1_pt);    // Z-axis through 1,0,0
      CPPUNIT_ASSERT(test_plane.mNorm == z1_v);
      CPPUNIT_ASSERT(test_plane.mOffset == 0.0f);

      test_plane = gmtl::Plane<float>(z1_v, gmtl::Point<float, 3>(0,0,-1));    // Z-axis through 0,0,-1
      CPPUNIT_ASSERT(test_plane.mNorm == z1_v);
      CPPUNIT_ASSERT(test_plane.mOffset == -1.0f);

      // Test overhead of creation
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Plane<float> test_plane2( x1_v, z1_pt );
         test_plane.mOffset = 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/NormPtCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testNormOffsetCreation()
   {
      gmtl::Plane<float> test_plane(x1_v, 0.0f);    // X-axis through origin
      CPPUNIT_ASSERT(test_plane.mNorm == x1_v);
      CPPUNIT_ASSERT(test_plane.mOffset == 0.0f);

      // Test overhead of creation
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Plane<float> test_plane2( x1_v, 25.0f );
         test_plane.mOffset = 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/NormOffsetCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testCopyConstruct()
   {
      gmtl::Plane<float> test_plane( xy_plane );
      CPPUNIT_ASSERT( test_plane.mNorm == xy_plane.mNorm );
      CPPUNIT_ASSERT( test_plane.mOffset == xy_plane.mOffset );

      // Test overhead of creation
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Plane<float> test_plane2( test_plane );
         test_plane.mOffset = 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/CopyConstructOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   // --------------------------
   // Comparison tests
   // --------------------------
   void testEqualityCompare()
   {
      gmtl::Plane<float> test_plane1( x1_v, 35.0f );
      gmtl::Plane<float> test_plane2( test_plane1 );

      CPPUNIT_ASSERT( test_plane1 == test_plane2 );
      CPPUNIT_ASSERT( !(test_plane1 != test_plane2) );

      // set equal, vary normal
      test_plane2 = test_plane1;
      test_plane2.mNorm[0] += 2.0f;
      CPPUNIT_ASSERT( test_plane1 != test_plane2 );
      CPPUNIT_ASSERT( !(test_plane1 == test_plane2) );

      // set equal, vary offset
      test_plane2 = test_plane1;
      test_plane2.mOffset += 2.0f;
      CPPUNIT_ASSERT( test_plane1 != test_plane2 );
      CPPUNIT_ASSERT( !(test_plane1 == test_plane2) );

      // test comparison performance
      const long iters(400000);
      unsigned true_count(0);

      // -- Equality
      test_plane2 = test_plane1;

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0; iter<iters; ++iter )
      {
         test_plane1.mOffset += 1.0f;
         test_plane2.mOffset += 2.0f;
         if ( test_plane1 == test_plane2 )
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/EqualityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- Inequality
      test_plane1.mNorm = x1_v;
      test_plane1.mOffset = 0.0f;
      test_plane2 = test_plane1;

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0; iter<iters; ++iter )
      {
         test_plane1.mOffset += 1.0f;
         test_plane2.mOffset += 2.0f;
         if ( test_plane1 == test_plane2 )
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/InequalityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testIsEqual()
   {
      gmtl::Plane<float> test_plane1( x1_v, 0.0f );
      gmtl::Plane<float> test_plane2( test_plane1 );
      float eps(0.0f);

      for( eps=0.0f; eps<10.0f; eps+=0.05f )
      {
         CPPUNIT_ASSERT( gmtl::isEqual(test_plane1, test_plane2, eps) );
      }

      for ( unsigned elt=0; elt<4; ++elt )
      {
         test_plane2 = test_plane1;
         if ( elt < 3 ) {
            test_plane2.mNorm[elt] += 20.0f;
         } else {
            test_plane2.mOffset += 20.0f;
         }
         CPPUNIT_ASSERT( !gmtl::isEqual(test_plane1, test_plane2, 10.0f) );
         CPPUNIT_ASSERT( !gmtl::isEqual(test_plane1, test_plane2, 19.9f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_plane1, test_plane2, 20.1f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_plane1, test_plane2, 22.0f) );
      }

      // Test comparison performance
      const long iters(400000);
      unsigned true_count(0);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();
      test_plane2 = test_plane1;

      for( long iter=0;iter<iters; ++iter)
      {
         test_plane1.mOffset += 1.0f;
         test_plane2.mOffset += 2.0f;
         if(gmtl::isEqual(test_plane1, test_plane2, 1.0f) )
            true_count++;
         if(gmtl::isEqual(test_plane1, test_plane2, 0.1f) )
            true_count++;
         if(gmtl::isEqual(test_plane1, test_plane2, 100000.0f) )
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/isEqualOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

/*
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
*/

   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("PlaneTest");
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testCreation", &PlaneTest::testCreation));
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testThreePtCreation", &PlaneTest::testThreePtCreation));
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testNormPtCreation", &PlaneTest::testNormPtCreation));
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testNormOffsetCreation", &PlaneTest::testNormOffsetCreation));
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testCopyConstruct", &PlaneTest::testCopyConstruct));
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testEqualityCompare", &PlaneTest::testEqualityCompare));
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testIsEqual", &PlaneTest::testIsEqual));
//      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testDistToPt", &PlaneTest::testDistToPt));
//      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testWhichSide", &PlaneTest::testWhichSide));
//      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testFindNearestPt", &PlaneTest::testFindNearestPt));

      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("PlaneTestInteractive");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:
   gmtl::Point<float, 3> origin;
   gmtl::Point<float, 3> x1_pt;
   gmtl::Point<float, 3> y1_pt;
   gmtl::Point<float, 3> z1_pt;
   gmtl::Vec<float, 3> x1_v;
   gmtl::Vec<float, 3> y1_v;
   gmtl::Vec<float, 3> z1_v;

   gmtl::Plane<float> xy_plane;
   gmtl::Plane<float> zx_plane;
   gmtl::Plane<float> yz_plane;
};

} // namespace gmtlTest
