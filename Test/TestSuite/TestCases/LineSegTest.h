/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: LineSegTest.h,v $
 * Date modified: $Date: 2002-03-11 18:31:08 $
 * Version:       $Revision: 1.5 $
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
   void testCreation()
   {
      gmtl::LineSeg<float> test_lineseg;
      gmtl::Vec<float, 3> zeroVec(0,0,0);
      CPPUNIT_ASSERT( test_lineseg.mOrigin == origin );
      CPPUNIT_ASSERT( test_lineseg.mDir == zeroVec );

      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         gmtl::LineSeg<float> test_lineseg;
         use_value += test_lineseg.mDir[0] + 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/DefaultCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void testPtVecCreation()
   {
      CPPUNIT_ASSERT(x1_lineseg.mOrigin == origin);
      CPPUNIT_ASSERT(y1_lineseg.mOrigin == origin);
      CPPUNIT_ASSERT(z1_lineseg.mOrigin == origin);
      CPPUNIT_ASSERT(x1_lineseg.mDir == x1_v);
      CPPUNIT_ASSERT(y1_lineseg.mDir == y1_v);
      CPPUNIT_ASSERT(z1_lineseg.mDir == z1_v);

      gmtl::LineSeg<float> test_lineseg;
      gmtl::Vec<float, 3> vec(1.0,1.0,1.0);
      test_lineseg = gmtl::LineSeg<float>(x1_pt, vec);
      CPPUNIT_ASSERT(test_lineseg.mOrigin == x1_pt);
      CPPUNIT_ASSERT(test_lineseg.mDir == vec);

      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         gmtl::LineSeg<float> test_lineseg2(y1_pt, z1_v);
         use_value += test_lineseg2.mDir[0] + 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/PtVecCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void testPtPtCreation()
   {
      gmtl::LineSeg<float> test_lineseg;
      test_lineseg = gmtl::LineSeg<float>(origin, x1_pt);
      CPPUNIT_ASSERT(test_lineseg.mOrigin == origin);
      CPPUNIT_ASSERT(test_lineseg.mDir == (x1_pt - origin));

      test_lineseg = gmtl::LineSeg<float>(x1_pt, y1_pt);
      CPPUNIT_ASSERT(test_lineseg.mOrigin == x1_pt);
      CPPUNIT_ASSERT(test_lineseg.mDir == (y1_pt - x1_pt));

      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         gmtl::LineSeg<float> test_lineseg2( x1_pt, z1_pt );
         use_value += test_lineseg2.mDir[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/PtPtCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value != 0 );
   }

   void testCopyConstruct()
   {
      gmtl::LineSeg<float> test_lineseg( x1_lineseg );
      CPPUNIT_ASSERT( test_lineseg.mOrigin == x1_lineseg.mOrigin );
      CPPUNIT_ASSERT( test_lineseg.mDir == x1_lineseg.mDir );

      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         gmtl::LineSeg<float> test_lineseg2( test_lineseg );
         use_value += test_lineseg2.mDir[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/CopyConstructOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void testGetOrigin()
   {
      CPPUNIT_ASSERT( x1_lineseg.getOrigin() == origin );
      CPPUNIT_ASSERT( y1_lineseg.getOrigin() == origin );
      CPPUNIT_ASSERT( z1_lineseg.getOrigin() == origin );

      gmtl::Point<float, 3> pt( 25.0, 23.0 );
      gmtl::LineSeg<float> test_lineseg( pt, x1_pt );
      CPPUNIT_ASSERT( test_lineseg.getOrigin() == pt );

      // Test overhead
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Point<float, 3> pt = test_lineseg.getOrigin();
         use_value += pt[0] + 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/GetOriginOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void testSetOrigin()
   {
      gmtl::LineSeg<float> test_lineseg;
      test_lineseg.setOrigin( x1_pt );
      CPPUNIT_ASSERT( test_lineseg.getOrigin() == x1_pt );

      // Test overhead
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         test_lineseg.setOrigin( x1_pt );
         use_value += test_lineseg.mOrigin[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/SetOriginOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void testGetDir()
   {
      CPPUNIT_ASSERT( x1_lineseg.getDir() == x1_v );
      CPPUNIT_ASSERT( y1_lineseg.getDir() == y1_v );
      CPPUNIT_ASSERT( z1_lineseg.getDir() == z1_v );

      gmtl::Vec<float, 3> dir( 25.0, 23.0 );
      gmtl::LineSeg<float> test_lineseg( x1_pt, dir );
      CPPUNIT_ASSERT( test_lineseg.getDir() == dir );

      // Test overhead
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Vec<float, 3> vec = test_lineseg.getDir();
         use_value += vec[0] + 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/GetDirOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void testSetDir()
   {
      gmtl::LineSeg<float> test_lineseg;
      test_lineseg.setDir( x1_v );
      CPPUNIT_ASSERT( test_lineseg.getDir() == x1_v );

      // Test overhead
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         test_lineseg.setDir( x1_v );
         use_value += test_lineseg.mDir[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/SetDirOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   // --------------------------
   // Comparison tests
   // --------------------------
   void testEqualityCompare()
   {
      gmtl::LineSeg<float> test_lineseg1( x1_pt, x1_v );
      gmtl::LineSeg<float> test_lineseg2( test_lineseg1 );

      CPPUNIT_ASSERT( test_lineseg1 == test_lineseg2 );
      CPPUNIT_ASSERT( !(test_lineseg1 != test_lineseg2) );

      // set equal, vary origin
      test_lineseg2 = test_lineseg1;
      test_lineseg2.mOrigin[0] += 2.0f;
      CPPUNIT_ASSERT( test_lineseg1 != test_lineseg2 );
      CPPUNIT_ASSERT( !(test_lineseg1 == test_lineseg2) );

      // set equal, vary dir
      test_lineseg2 = test_lineseg1;
      test_lineseg2.mDir[0] += 2.0f;
      CPPUNIT_ASSERT( test_lineseg1 != test_lineseg2 );
      CPPUNIT_ASSERT( !(test_lineseg1 == test_lineseg2) );

      // test comparison performance
      const long iters(400000);
      unsigned true_count(0);

      // -- Equality
      test_lineseg2 = test_lineseg1;

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0; iter<iters; ++iter )
      {
         if ( test_lineseg1 == test_lineseg2 )
            ++true_count;
         test_lineseg1.mOrigin[0] += 1.0f;
         test_lineseg2.mOrigin[0] += 2.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/EqualityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- Inequality
      test_lineseg1.mOrigin = x1_pt;
      test_lineseg1.mDir = x1_v;
      test_lineseg2 = test_lineseg1;

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0; iter<iters; ++iter )
      {
         if ( test_lineseg1 == test_lineseg2 )
            ++true_count;
         test_lineseg1.mOrigin[0] += 1.0f;
         test_lineseg2.mOrigin[0] += 2.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/InequalityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void testIsEqual()
   {
      gmtl::LineSeg<float> test_lineseg1( x1_pt, x1_v );
      gmtl::LineSeg<float> test_lineseg2( test_lineseg1 );
      float eps(0.0f);

      for( eps=0.0f; eps<10.0f; eps+=0.05f )
      {
         CPPUNIT_ASSERT( gmtl::isEqual(test_lineseg1, test_lineseg2, eps) );
      }

      for ( unsigned elt=0; elt<6; ++elt )
      {
         test_lineseg2 = test_lineseg1;
         if ( elt < 3 ) {
            test_lineseg2.mOrigin[elt] += 20.0f;
         } else {
            test_lineseg2.mDir[elt] += 20.0f;
         }
         CPPUNIT_ASSERT( !gmtl::isEqual(test_lineseg1, test_lineseg2, 10.0f) );
         CPPUNIT_ASSERT( !gmtl::isEqual(test_lineseg1, test_lineseg2, 19.9f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_lineseg1, test_lineseg2, 20.1f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_lineseg1, test_lineseg2, 22.0f) );
      }

      // Test comparison performance
      const long iters(400000);
      unsigned true_count(0);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();
      test_lineseg2 = test_lineseg1;

      for( long iter=0;iter<iters; ++iter)
      {
         test_lineseg1.mOrigin[0] += 1.0f;
         test_lineseg2.mOrigin[0] += 2.0f;
         if(gmtl::isEqual(test_lineseg1, test_lineseg2, 1.0f) )
            true_count++;
         if(gmtl::isEqual(test_lineseg1, test_lineseg2, 0.1f) )
            true_count++;
         if(gmtl::isEqual(test_lineseg1, test_lineseg2, 100000.0f) )
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/isEqualOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
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
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testEqualityCompare", &PlaneTest::testEqualityCompare));
      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testIsEqual", &PlaneTest::testIsEqual));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testGetOrigin", &LineSegTest::testGetOrigin));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testSetOrigin", &LineSegTest::testSetOrigin));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testGetDir", &LineSegTest::testGetDir));
      test_suite->addTest( new CppUnit::TestCaller<LineSegTest>("testSetDir", &LineSegTest::testSetDir));
//      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testDistance", &PlaneTest::testDistance));
//      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testWhichSide", &PlaneTest::testWhichSide));
//      test_suite->addTest( new CppUnit::TestCaller<PlaneTest>("testFindNearestPt", &PlaneTest::testFindNearestPt));

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
