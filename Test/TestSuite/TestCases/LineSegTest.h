/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: LineSegTest.h,v $
 * Date modified: $Date: 2002-06-11 21:52:53 $
 * Version:       $Revision: 1.9 $
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
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/LineSeg.h>
#include <gmtl/LineSegOps.h>

namespace gmtlTest
{

class LineSegTest : public CppUnit::TestCase
{
public:
   LineSegTest( std::string name = "LineSegTest")
   : CppUnit::TestCase (name)
   {}

   virtual ~LineSegTest()
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

      x1_lineseg = gmtl::LineSeg<float>(origin, x1_v);
      y1_lineseg = gmtl::LineSeg<float>(origin, y1_v);
      z1_lineseg = gmtl::LineSeg<float>(origin, z1_v);
   }

   virtual void tearDown()
   {}

   // ------------------------
   // CREATION TESTS
   // ------------------------
   void testCreation();
   void testPtVecCreation();
   void testPtPtCreation();
   void testCopyConstruct();

   void testGetOrigin();
   void testSetOrigin();
   void testGetDir();
   void testSetDir();

   // --------------------------
   // Comparison tests
   // --------------------------
   void testEqualityCompare();
   void testIsEqual();
/*
   // --------------------------
   // Operations tests
   // --------------------------
   void testDistance()
   {
      gmtl::Plane<float> test_plane( x1_v, 25.0f );
      CPPUNIT_ASSERT( gmtl::distance(test_plane, origin) == -25.0f );
      CPPUNIT_ASSERT( gmtl::distance(test_plane, x1_pt) == -24.0f );

      CPPUNIT_ASSERT( gmtl::distance(xy_plane, z1_pt) == 1.0f );

      gmtl::Point<float, 3> pt(-12.0f, 5.0f, -17.0f);
      CPPUNIT_ASSERT( gmtl::distance(xy_plane, pt) == -17.0f );

      gmtl::Plane<float> slanted_plane( gmtl::Vec<float, 3>(1.0f,1.0f,1.0f), origin );
      CPPUNIT_ASSERT( gmtl::distance(slanted_plane, origin) == 0.0f );

      pt.set(1.0f, 1.0f, 1.0f );
      CPPUNIT_ASSERT( gmtl::distance(slanted_plane, pt) > 0.0f );

      // Test distance performance
      const long iters(400000);
      float use_value(0.0f);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         test_plane.mOffset += 1.0f;
         use_value = use_value + gmtl::distance(test_plane, y1_pt);
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/DistanceOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testWhichSide()
   {
      gmtl::Plane<float>::Side answer;

      answer = gmtl::whichSide(xy_plane, gmtl::Point<float, 3>(0.0,0.0,1.0));
      CPPUNIT_ASSERT( answer == gmtl::Plane<float>::POS_SIDE );

      answer = gmtl::whichSide(xy_plane, gmtl::Point<float, 3>(0.0,0.0,-12.0f));
      CPPUNIT_ASSERT( answer == gmtl::Plane<float>::NEG_SIDE );

      answer = gmtl::whichSide(zx_plane, gmtl::Point<float, 3>(0.0,1e-10f,0.0f));
      CPPUNIT_ASSERT( answer == gmtl::Plane<float>::POS_SIDE );

      answer = gmtl::whichSide(zx_plane, gmtl::Point<float, 3>(0.0,-1e-10f,0.0f));
      CPPUNIT_ASSERT( answer == gmtl::Plane<float>::NEG_SIDE );

      answer = gmtl::whichSide(xy_plane, gmtl::Point<float, 3>(0.0,0.0,0.0));
      CPPUNIT_ASSERT( answer == gmtl::Plane<float>::ON_PLANE );

      // Test whichSide performance
      const long iters(400000);
      bool true_count(0);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         if ( gmtl::distance(xy_plane, y1_pt) == gmtl::Plane<float>::POS_SIDE )
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/WhichSideOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testFindNearestPt()
   {
      gmtl::Point<float, 3> answer, test_point, correct_result;
      float dist;

      // XY dist to point off origin
      test_point = gmtl::Point<float, 3>(0.0,0.0,1.0);
      CPPUNIT_ASSERT(distance(xy_plane, test_point) == findNearestPt(xy_plane, test_point, answer));
      CPPUNIT_ASSERT(answer == origin);

      // XY dist to point at 12,21
      test_point = gmtl::Point<float, 3>(12.0,-21.0,-13.0);
      correct_result = gmtl::Point<float, 3>(12.0,-21.0,0.0);
      CPPUNIT_ASSERT(distance(xy_plane, test_point) == findNearestPt(xy_plane, test_point, answer));
      CPPUNIT_ASSERT(answer == correct_result);

      // XY dist to point on plane at -17.05, 0.334
      test_point = gmtl::Point<float, 3>(-17.05,0.334,0.0);
      CPPUNIT_ASSERT(distance(xy_plane, test_point) == findNearestPt(xy_plane, test_point, answer));
      CPPUNIT_ASSERT(answer == test_point);

      // Test findNearestPt performance
      const long iters(400000);
      float use_value(0.0f);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         dist = gmtl::findNearestPt(xy_plane, test_point, answer);
         use_value = use_value + dist + answer[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/FindNearestPtOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
*/
   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("LineSegTest");
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testCreation", &LineSegTest::testCreation));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testPtVecCreation", &LineSegTest::testPtVecCreation));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testPtPtCreation", &LineSegTest::testPtPtCreation));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testCopyConstruct", &LineSegTest::testCopyConstruct));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testEqualityCompare", &LineSegTest::testEqualityCompare));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testIsEqual", &LineSegTest::testIsEqual));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testGetOrigin", &LineSegTest::testGetOrigin));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testSetOrigin", &LineSegTest::testSetOrigin));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testGetDir", &LineSegTest::testGetDir));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testSetDir", &LineSegTest::testSetDir));
//      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testDistance", &PlaneTest::testDistance));
//      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testWhichSide", &PlaneTest::testWhichSide));
//      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testFindNearestPt", &PlaneTest::testFindNearestPt));

      return test_suite;
   }

   static Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("LineSegTiming");
      return test_suite;
   }
   
   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("LineTestInteractive");
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

   gmtl::LineSeg<float> x1_lineseg;
   gmtl::LineSeg<float> y1_lineseg;
   gmtl::LineSeg<float> z1_lineseg;
};

} // namespace gmtlTest
