/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: PointTest.h,v $
 * Date modified: $Date: 2002-03-18 18:25:14 $
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

#include <gmtl/Point.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>

namespace gmtlTest
{

class PointTest : public CppUnit::TestCase
{
public:
   PointTest( std::string name = "PointTest" )
   : CppUnit::TestCase (name)
   {;}

   virtual ~PointTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void testCreation()
   {
      gmtl::Point<double, 3> point;

      CPPUNIT_ASSERT( point[0] == 0.0f);
      CPPUNIT_ASSERT( point[1] == 0.0f);
      CPPUNIT_ASSERT( point[2] == 0.0f);

      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Point<float, 2> test_point2;
         test_point2[0] = 1.0f;
         gmtl::Point<float, 3> test_point3;
         test_point3[0] = 2.0f;
         gmtl::Point<float, 4> test_point4;
         test_point4[0] = 3.0f;

         use_value += test_point2[0] + test_point3[0] + test_point4[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/pointCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void testCopyConstruct()
   {
      gmtl::Point<double, 3> test_point;

      test_point[0] = 2.0f;
      test_point[1] = 4.0f;
      test_point[2] = 8.0f;

      gmtl::Point<double, 3> test_point_copy(test_point);

      CPPUNIT_ASSERT( test_point_copy[0] == 2.0f);
      CPPUNIT_ASSERT( test_point_copy[1] == 4.0f);
      CPPUNIT_ASSERT( test_point_copy[2] == 8.0f);

      // Test copy construction overhead
      const long iters(400000);
      gmtl::Point<float, 2> test_point2;
      test_point2[0] = 2.0f;
      gmtl::Point<float, 3> test_point3;
      test_point2[0] = 3.0f;
      gmtl::Point<float, 4> test_point4;
      test_point2[0] = 4.0f;
      float use_value;     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Point<float, 2> test_point2_copy(test_point2);
         use_value += test_point2_copy[0];
         gmtl::Point<float, 3> test_point3_copy(test_point3);
         use_value += test_point3_copy[0];
         gmtl::Point<float, 4> test_point4_copy(test_point4);
         use_value += test_point4_copy[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/CopyConstructOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }


   void testConstructors()
   {
      gmtl::Point<float, 4> test_point4(1.0f, 2.0f, 3.0f, 4.0f);
      CPPUNIT_ASSERT( test_point4[0] == 1.0f);
      CPPUNIT_ASSERT( test_point4[1] == 2.0f);
      CPPUNIT_ASSERT( test_point4[2] == 3.0f);
      CPPUNIT_ASSERT( test_point4[3] == 4.0f);

      gmtl::Point<float, 3> test_point3(1.0f, 2.0f, 3.0f);
      CPPUNIT_ASSERT( test_point3[0] == 1.0f);
      CPPUNIT_ASSERT( test_point3[1] == 2.0f);
      CPPUNIT_ASSERT( test_point3[2] == 3.0f);

      gmtl::Point<float, 2> test_point2(1.0f, 2.0f);
      CPPUNIT_ASSERT( test_point2[0] == 1.0f);
      CPPUNIT_ASSERT( test_point2[1] == 2.0f);

      gmtl::Point<float, 1> test_point1(1.0f);
      CPPUNIT_ASSERT( test_point1[0] == 1.0f);

      // Test constructor
      const long iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Point<float, 4> test_point4(1.0f, 2.0f, 3.0f, 4.0f);
         gmtl::Point<float, 3> test_point3(1.0f, 2.0f, 3.0f);
         gmtl::Point<float, 2> test_point2(1.0f, 2.0f);
         gmtl::Point<float, 1> test_point1(1.0f);

         use_value = use_value + test_point4[3] + test_point3[2] + test_point2[1] + test_point1[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/ConstructorsOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testSet()
   {
      gmtl::Point<float, 4> test_point4;
      test_point4.set(1.0f, 2.0f, 3.0f, 4.0f);
      CPPUNIT_ASSERT( test_point4[0] == 1.0f);
      CPPUNIT_ASSERT( test_point4[1] == 2.0f);
      CPPUNIT_ASSERT( test_point4[2] == 3.0f);
      CPPUNIT_ASSERT( test_point4[3] == 4.0f);

      gmtl::Point<float, 3> test_point3;
      test_point3.set(1.0f, 2.0f, 3.0f);
      CPPUNIT_ASSERT( test_point3[0] == 1.0f);
      CPPUNIT_ASSERT( test_point3[1] == 2.0f);
      CPPUNIT_ASSERT( test_point3[2] == 3.0f);

      gmtl::Point<float, 2> test_point2;
      test_point2.set(1.0f, 2.0f);
      CPPUNIT_ASSERT( test_point2[0] == 1.0f);
      CPPUNIT_ASSERT( test_point2[1] == 2.0f);

      gmtl::Point<float, 1> test_point1;
      test_point1.set(1.0f);
      CPPUNIT_ASSERT( test_point1[0] == 1.0f);

      // Test constructor
      const float iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         test_point4.set(iters+0, iters+1, iters+2, iters+3);
         test_point3.set(iters+0, iters+1, iters+2);
         test_point2.set(iters+0, iters+1);
         test_point1.set(iters+0);

         use_value = use_value + test_point4[3] + test_point3[2] + test_point2[1] + test_point1[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/SetOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void testSetPtr()
   {
      float data[4] = {1.0f, 2.0f, 3.0f, 4.0f};

      gmtl::Point<float, 4> test_point4;
      test_point4.set(data);
      CPPUNIT_ASSERT( test_point4[0] == 1.0f);
      CPPUNIT_ASSERT( test_point4[1] == 2.0f);
      CPPUNIT_ASSERT( test_point4[2] == 3.0f);
      CPPUNIT_ASSERT( test_point4[3] == 4.0f);

      gmtl::Point<float, 3> test_point3;
      test_point3.set(data);
      CPPUNIT_ASSERT( test_point3[0] == 1.0f);
      CPPUNIT_ASSERT( test_point3[1] == 2.0f);
      CPPUNIT_ASSERT( test_point3[2] == 3.0f);

      gmtl::Point<float, 2> test_point2;
      test_point2.set(data);
      CPPUNIT_ASSERT( test_point2[0] == 1.0f);
      CPPUNIT_ASSERT( test_point2[1] == 2.0f);

      gmtl::Point<float, 1> test_point1;
      test_point1.set(data);
      CPPUNIT_ASSERT( test_point1[0] == 1.0f);

      // Test constructor
      const float iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         data[0] += 1.0f; data[1] += 2.0f; data[2] += 4.0f; data[3] += 8.0f;    // Just make sure data changes
         test_point4.set(data);
         test_point3.set(data);
         test_point2.set(data);
         test_point1.set(data);

         use_value = use_value + test_point4[3] + test_point3[2] + test_point2[1] + test_point1[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/SetPtrOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }


   void testGetData()
   {
      float* data;
      gmtl::Point<float, 4> test_point4(1.0f, 2.0f, 3.0f, 4.0f);
      data = test_point4.getData();
      CPPUNIT_ASSERT( data[0] == 1.0f);
      CPPUNIT_ASSERT( data[1] == 2.0f);
      CPPUNIT_ASSERT( data[2] == 3.0f);
      CPPUNIT_ASSERT( data[3] == 4.0f);

      gmtl::Point<float, 3> test_point3(1.0f, 2.0f, 3.0f);
      data = test_point3.getData();
      CPPUNIT_ASSERT( data[0] == 1.0f);
      CPPUNIT_ASSERT( data[1] == 2.0f);
      CPPUNIT_ASSERT( data[2] == 3.0f);

      gmtl::Point<float, 2> test_point2(1.0f, 2.0f);
      data = test_point2.getData();
      CPPUNIT_ASSERT( data[0] == 1.0f);
      CPPUNIT_ASSERT( data[1] == 2.0f);
   }

   // -- Test comparison -- //
   void testEqualityCompare()
   {
      gmtl::Point<float, 4> test_point1(1.0f, 2.0f, 3.0f, 4.0f);
      gmtl::Point<float, 4> test_point2(test_point1);

      CPPUNIT_ASSERT( test_point1 == test_point2);
      CPPUNIT_ASSERT(! (test_point1 != test_point2));

      test_point2 = test_point1;     // Set equal, vary elt 0
      test_point2[0] = 21.10f;
      CPPUNIT_ASSERT( test_point1 != test_point2);
      CPPUNIT_ASSERT(! (test_point1 == test_point2));

      test_point2 = test_point1;     // Set equal, vary elt 0
      test_point2[1] = 21.10f;
      CPPUNIT_ASSERT( test_point1 != test_point2);
      CPPUNIT_ASSERT(! (test_point1 == test_point2));

      test_point2 = test_point1;     // Set equal, vary elt 0
      test_point2[2] = 21.10f;
      CPPUNIT_ASSERT( test_point1 != test_point2);
      CPPUNIT_ASSERT(! (test_point1 == test_point2));

      test_point2 = test_point1;     // Set equal, vary elt 0
      test_point2[3] = 21.10f;
      CPPUNIT_ASSERT( test_point1 != test_point2);
      CPPUNIT_ASSERT(! (test_point1 == test_point2));

      // Test comparison performance
      // Test constructor
      const float iters(400000);
      unsigned true_count(0);
      unsigned false_count(0);
      
      // -- Equality
      CPPUNIT_METRIC_START_TIMING();
      test_point1.set(0.0f, 0.0f, 0.0f, 2000.0f);
      test_point2.set(0.0f, 0.0f, 0.0f, 1000.0f);
      
      for( float iter=0;iter<iters; ++iter)
      {
         test_point1[3] += 1.0f;
         test_point2[3] += 2.0f;
         if(test_point1 == test_point2)
            true_count++;         
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/EqualityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- Inequality
      CPPUNIT_METRIC_START_TIMING();
      test_point1.set(0.0f, 0.0f, 0.0f, 2000.0f);
      test_point2.set(0.0f, 0.0f, 0.0f, 1000.0f);
      
      for( float iter=0;iter<iters; ++iter)
      {
         test_point1[3] += 1.0f;
         test_point2[3] += 2.0f;
         if(test_point1 != test_point2)
            false_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/InequalityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

   }

   // -- Test comparison -- //
   void testIsEqual()
   {
      gmtl::Point<float, 4> test_point1(1.0f, 2.0f, 3.0f, 4.0f);
      gmtl::Point<float, 4> test_point2(test_point1);
      float eps(0.0f);

      for(eps=0.0f;eps<10.0f;eps += 0.05f)
      {
         CPPUNIT_ASSERT( gmtl::isEqual(test_point1, test_point2, eps) );                     
      }

      test_point1.set(1.0f, 1.0f, 1.0f, 1.0f);
      for(unsigned elt=0; elt<4; elt++)
      {
         test_point2 = test_point1;     // Set equal, vary elt 0
         test_point2[elt] = 21.0f;
         CPPUNIT_ASSERT( !gmtl::isEqual(test_point1, test_point2, 10.0f) );
         CPPUNIT_ASSERT( !gmtl::isEqual(test_point1, test_point2, 19.9f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_point1, test_point2, 20.1f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_point1, test_point2, 22.0f) );
      }

      // Test comparison performance
      // Test constructor
      const float iters(400000);
      unsigned true_count(0);
      
      // -- Equality
      CPPUNIT_METRIC_START_TIMING();
      test_point1.set(0.0f, 0.0f, 0.0f, 2000.0f);
      test_point2.set(0.0f, 0.0f, 0.0f, 1000.0f);
      
      for( float iter=0;iter<iters; ++iter)
      {
         test_point1[3] += 1.0f;
         test_point2[3] += 2.0f;
         if(gmtl::isEqual(test_point1, test_point2, 1.0f) )
            true_count++;
         if(gmtl::isEqual(test_point1, test_point2, 0.1f) )
            true_count++;
         if(gmtl::isEqual(test_point1, test_point2, 100000.0f) )
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/isEqualOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      
   }

   // ---------------------------------- //
   // ---------- Math ops -------------- //
   // ---------------------------------- //
   void testOpPlusEq()
   {
      gmtl::Point<float,3> test_point1(1.0, 2.0, 3.0);
      gmtl::Point<float,3> test_point2(2.0, 2.0, 2.0);

      test_point1 += test_point2;
      CPPUNIT_ASSERT( test_point1[0] == 3.0f &&
                      test_point1[1] == 4.0f &&
                      test_point1[2] == 5.0f );

      // -- test op+= performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::Point<float,3> test_point3(5.0, 7.0, 9.0);

      for( float iter=0;iter<iters; ++iter)
      {
         test_point3.set(iter, iter+1, iter+2);
         test_point1 += test_point3;         
      }

      test_point2 = test_point1;

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/OpPlusEqOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testOpPlus()
   {
      gmtl::Point<float,3> test_point1(1.0, 2.0, 3.0);
      gmtl::Point<float,3> test_point2(2.0, 2.0, 2.0);
      gmtl::Point<float,3> test_point3(1.0, 2.0, 3.0);

      test_point1 = test_point3 + test_point2;
      CPPUNIT_ASSERT( test_point1[0] == 3.0f &&
                      test_point1[1] == 4.0f &&
                      test_point1[2] == 5.0f );

      // -- test op+ performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      test_point3.set(5.0, 7.0, 9.0);

      for( float iter=0;iter<iters; ++iter)
      {
         test_point3.set(iter, iter+1, iter+2);
         test_point1 = (test_point3 + test_point2);         
      }

      test_point2 = test_point1;

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/OpPlusOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testOpMinusEq()
   {
      gmtl::Point<float,3> test_point1(1.0, 2.0, 3.0);
      gmtl::Point<float,3> test_point2(2.0, 2.0, 2.0);

      test_point1 -= test_point2;
      CPPUNIT_ASSERT( test_point1[0] == -1.0f &&
                      test_point1[1] == 0.0f &&
                      test_point1[2] == 1.0f );

      // -- test op-= performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::Point<float,3> test_point3(5.0, 7.0, 9.0);

      for( float iter=0;iter<iters; ++iter)
      {
         test_point3.set(iter, iter+1, iter+2);
         test_point1 -= test_point3;         
      }

      test_point2 = test_point1;

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/OpMinusEqOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testOpMinus()
   {
      gmtl::Point<float,3> test_point1(1.0, 2.0, 3.0);
      gmtl::Point<float,3> test_point2(2.0, 2.0, 2.0);
      gmtl::Point<float,3> test_point3(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> vec_ans(0,0,0);

      vec_ans = test_point3 - test_point2;
      CPPUNIT_ASSERT( vec_ans[0] == -1.0f &&
                      vec_ans[1] == 0.0f &&
                      vec_ans[2] == 1.0f );

      // -- test op- performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      test_point3.set(5.0, 7.0, 9.0);

      for( float iter=0;iter<iters; ++iter)
      {
         test_point3.set(iter, iter+1, iter+2);
         test_point1 = (test_point3 - test_point2);         
      }

      test_point2 = test_point1;

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/OpMinusOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testOpMultScalarEq()
   {
      gmtl::Point<float,3> test_point1(1.0, 2.0, 3.0);
         
      test_point1 *= 4.0f;
      CPPUNIT_ASSERT( test_point1[0] == 4.0f &&
                      test_point1[1] == 8.0f &&
                      test_point1[2] == 12.0f );

      // -- test op-= performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();
            
      for( float iter=0;iter<iters; ++iter)
      {
         test_point1 *= 1.05f;         
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/OpMultScalarEqOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testOpMultScalar()
   {
      gmtl::Point<float,3> test_point1(1.0, 2.0, 3.0);
      gmtl::Point<float,3> test_point3(1.0, 2.0, 3.0);

      test_point1 = test_point3 * 4.0f;
      CPPUNIT_ASSERT( test_point1[0] == 4.0f &&
                      test_point1[1] == 8.0f &&
                      test_point1[2] == 12.0f );

      // -- test op- performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      test_point3.set(5.0, 7.0, 9.0);

      for( float iter=0;iter<iters; ++iter)
      {
         test_point1 = test_point3 * 1.05f;
         test_point3 = test_point1;         
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/OpMultScalarOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testOpDivScalarEq()
   {
      gmtl::Point<float,3> test_point1(12.0, 8.0, 4.0);
         
      test_point1 /= 4.0f;
      CPPUNIT_ASSERT( test_point1[0] == 3.0f &&
                      test_point1[1] == 2.0f &&
                      test_point1[2] == 1.0f );

      // -- test op-= performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();
            
      for( float iter=0;iter<iters; ++iter)
      {
         test_point1 /= 0.95f;         
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/OpDivScalarEqOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testOpDivScalar()
   {
      gmtl::Point<float,3> test_point1(1.0, 2.0, 3.0);
      gmtl::Point<float,3> test_point3(12.0, 8.0, 4.0);

      test_point1 = test_point3 / 4.0f;
      CPPUNIT_ASSERT( test_point1[0] == 3.0f &&
                      test_point1[1] == 2.0f &&
                      test_point1[2] == 1.0f );

      // -- test op- performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      test_point3.set(5.0, 7.0, 9.0);

      for( float iter=0;iter<iters; ++iter)
      {
         test_point1 = test_point3 / 0.95f;
         test_point3 = test_point1;         
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PointTest/OpDivScalarOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }



   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("PointTest");
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testCreation", &PointTest::testCreation));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testCopyConstruct", &PointTest::testCopyConstruct));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testConstructors", &PointTest::testConstructors));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testSet", &PointTest::testSet));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testSetPtr", &PointTest::testSetPtr));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testGetData", &PointTest::testGetData));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testEqualityCompare", &PointTest::testEqualityCompare));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testIsEqual", &PointTest::testIsEqual));

      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpPlusEq", &PointTest::testOpPlusEq));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpPlus", &PointTest::testOpPlus));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpMinusEq", &PointTest::testOpMinusEq));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpMinus", &PointTest::testOpMinus));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpMultScalarEq", &PointTest::testOpMultScalarEq)); 
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpMultScalar", &PointTest::testOpMultScalar)); 
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpDivScalarEq", &PointTest::testOpDivScalarEq)); 
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpDivScalar", &PointTest::testOpDivScalar)); 


      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractivePointTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
