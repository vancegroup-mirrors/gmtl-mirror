/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: LineSegTest.cpp,v $
 * Date modified: $Date: 2002-10-17 09:20:30 $
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
#include "LineSegTest.h"
#include <cppunit/extensions/MetricRegistry.h>

namespace gmtlTest
{
   // ------------------------
   // CREATION TESTS
   // ------------------------
   void LineSegTest::testCreation()
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

   void LineSegTest::testPtVecCreation()
   {
      CPPUNIT_ASSERT(x1_lineseg.mOrigin == origin);
      CPPUNIT_ASSERT(y1_lineseg.mOrigin == origin);
      CPPUNIT_ASSERT(z1_lineseg.mOrigin == origin);
      CPPUNIT_ASSERT(x1_lineseg.mDir == x1_v);
      CPPUNIT_ASSERT(y1_lineseg.mDir == y1_v);
      CPPUNIT_ASSERT(z1_lineseg.mDir == z1_v);

      gmtl::LineSeg<float> test_lineseg;
      gmtl::Vec<float, 3> vec(1.0, 1.0, 1.0);
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
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/PtVecCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void LineSegTest::testPtPtCreation()
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

   void LineSegTest::testCopyConstruct()
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

   void LineSegTest::testGetOrigin()
   {
      CPPUNIT_ASSERT( x1_lineseg.getOrigin() == origin );
      CPPUNIT_ASSERT( y1_lineseg.getOrigin() == origin );
      CPPUNIT_ASSERT( z1_lineseg.getOrigin() == origin );

      gmtl::Point<float, 3> pt( 25.0f, 23.0f, 0.0f );
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

   void LineSegTest::testSetOrigin()
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

   void LineSegTest::testGetDir()
   {
      CPPUNIT_ASSERT( x1_lineseg.getDir() == x1_v );
      CPPUNIT_ASSERT( y1_lineseg.getDir() == y1_v );
      CPPUNIT_ASSERT( z1_lineseg.getDir() == z1_v );

      gmtl::Vec<float, 3> dir( 25.0f, 23.0f, 0.0f );
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

   void LineSegTest::testSetDir()
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

   void LineSegTest::testGetLength()
   {
      gmtl::LineSeg<float> test_lineseg1(x1_pt, x1_v);
      CPPUNIT_ASSERT(test_lineseg1.getLength() == gmtl::length(x1_v));
   }

   void LineSegTest::testTimingGetLength()
   {
      gmtl::LineSeg<float> lineseg;
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter=0; iter<iters; ++iter)
      {
         use_value += lineseg.getLength();
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/TimingGetLength", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT(use_value > 0);
   }

   // --------------------------
   // Comparison tests
   // --------------------------
   void LineSegTest::testEqualityCompare()
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

   void LineSegTest::testIsEqual()
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
            test_lineseg2.mDir[elt-3] += 20.0f;
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
}
