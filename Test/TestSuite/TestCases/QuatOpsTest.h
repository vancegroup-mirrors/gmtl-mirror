/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: QuatOpsTest.h,v $
 * Date modified: $Date: 2002-02-22 10:41:40 $
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
* modify it under th MathPrimitives  [PrimName]Ops.h  Vec & Point [100%] -ab
Quat [] -km Transforquations XformInterface? Xform.h   Collision detection CollisionInterface? Intersection.h   Bounding volumes BoundingInterface? Containment.h   Math factories MathFactories Builder.h  e terms of the GNU Lesser General Public
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

#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>

namespace gmtlTest
{

class QuatOpsTest : public CppUnit::TestCase
{
public:
   QuatOpsTest( std::string name = "QuatOpsTest" )
   : TestCase (name)
   {;}

   virtual ~QuatOpsTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void output( gmtl::Quatf q )
   {
      std::cout<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<std::endl;
   } 
   
   void testQuatTimingMult()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         q4 = mult( q1, q2, q3 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/mult(q1,q2)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   void testQuatTimingOperatorMult()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         q4 = q2 * q3;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/operator*()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testQuatTimingDiv()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         q4 = div( q1, q2, q3 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/invert()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testQuatTimingVectorMult()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      float bok;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         q4 = mult( q1, q2, bok );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/mult(q,scalar)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testQuatTimingVectorAdd()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         q4 = add( q1, q2, q3 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/add(r,q1,q2)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testQuatTimingVectorSub()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         q4 = sub( q1, q2, q3 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/sub(r,q1,q2)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testQuatTimingVectorDot()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      float bok;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         bok = dot( q1, q2 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/dot(q1,q2)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testQuatTimingNorm()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      float bok;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         bok = lengthSquared( q1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/lengthSquared(q)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testQuatTimingMag()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      float bok;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         bok = length( q1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/length(q)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testQuatTimingNormalize()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         q4 = normalize( q1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/normalize(q)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testQuatTimingNormalizeFast()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         q4 = normalizeFast( q1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/normalizeFast(q)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testQuatTimingConj()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         q4 = conj( q1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/conj(q)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testQuatTimingInvert()
   {
      gmtl::Quatf<float> q1, q2, q3, q4;
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      bool result = false;
      for (long iter = 0; iter < iters; ++iter)
      {
         q4 = invert( q1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatOpsTest/invert(q)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   
   
   
   
   ///////////////////////////////////////////////
   // real tests...
   ///////////////////////////////////////////////
   
   
   
   
   
   void testQuatMult()
   {
      // test out mult( result, quat, quat )
      const float eps = 0.0001f;
      gmtl::Quatf q3( 1, 2, 3, 4 ), q4( 5, 6, 7, 8 ), q5, q6;
      gmtl::mult( q5, q3, q4 );
      gmtl::mult( q6, q4, q3 );
      
      gmtl::Quatf expected_result1( 24, 48, 48, -6 ), expected_result2( 32, 32, 56, -6 );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, q5, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result2, q6, eps ) );
      
      // operator* should be same
      gmtl::Quatf q7, q8;
      q7 = q3 * q4;
      q8 = q4 * q3;
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, q7, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result2, q8, eps ) );
      
      gmtl::Quatf  bokbokbok( 9, 10, 11, 12 ), expected_result3( 122, 476, 638, -1296 );
      q6 = q4 * q3 * bokbokbok;
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result3, q6, eps ) );
   }
   
   void testQuatDiv()
   {
      // test out mult( result, quat, quat )
      const float eps = 0.0001f;
      gmtl::Quatf q3( 1, 2, 3, 4 ), q4( 5, 6, 7, 8 ), q5, q6;
      gmtl::div( q5, q3, q4 );
      gmtl::div( q6, q4, q3 );
      
      gmtl::Quatf expected_result1( 0.173913, 0.347826, -0, -1.52174 ), expected_result2( 4, 8, 0, 35 );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, q5, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result2, q6, eps ) );
   }
   
   void testQuatVectorMult()
   {
      // test out mult( result, quat, quat )
      const float eps = 0.0001f;
      gmtl::Quatf q3( 1, 2, 3, 4 ), q5;
      gmtl::mult( q5, q3, 23.0f );
      
      gmtl::Quatf expected_result1( 1 * 23.0f, 2 * 23.0f, 3 * 23.0f, 4 * 23.0f );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, q5, eps ) );
   }
   
   void testQuatVectorAdd()
   {
      // test out mult( result, quat, quat )
      const float eps = 0.0001f;
      gmtl::Quatf q3( 1, 2, 3, 4 ), q5, q6( 2, 3, 4, 5 );
      gmtl::add( q5, q3, q6 );
      
      gmtl::Quatf expected_result1( 3, 5, 7, 9 );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, q5, eps ) );
   }
   
   void testQuatVectorSub()
   {
      // test out mult( result, quat, quat )
      const float eps = 0.0001f;
      gmtl::Quatf q3( 1, 2, 3, 4 ), q5, q6( 2, 3, 4, 5 );
      gmtl::sub( q5, q3, q6 );

      gmtl::Quatf expected_result1( -1, -1, -1, -1 );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, q5, eps ) );
   }
   
   void testQuatVectorDot()
   {
      // test out mult( result, quat, quat )
      const float eps = 0.0001f;
      CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::dot( gmtl::Quatf( 1, 0, 0, 0 ), gmtl::Quatf( 1, 0, 0, 0 ) ), 1.0f, eps ) );
      CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::dot( gmtl::Quatf( 1, 0, 0, 0 ), gmtl::Quatf( 0, 1, 0, 0 ) ), 0.0f, eps ) );
      CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::dot( gmtl::Quatf( 1, 0, 0, 0 ), gmtl::Quatf( 1, 1, 0, 0 ) ), 1.0f, eps ) );
      CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::dot( gmtl::Quatf( 1, 0, 0, 10 ), gmtl::Quatf( 1, 0, 0, 223 ) ), 2231.0f, eps ) );
   }
   
   void testQuatNorm()
   {
      const float eps = 0.0001f;
      gmtl::Quatf q1( 1,1,1,1 );
      CPPUNIT_ASSERT( gmtl::Math::isEqual( lengthSquared( q1 ), 4.0f, eps ) );
   }
   
   void testQuatMag()
   {
      const float eps = 0.0001f;
      gmtl::Quatf q1( 1,1,1,1 );
      CPPUNIT_ASSERT( gmtl::Math::isEqual( length( q1 ), 2.0f, eps ) );
   }
   
   void testQuatNormalize()
   {
      const float eps = 0.0001f;
      gmtl::Quatf q3( 0,0,342334,0 ), q5( 342334,-342334,342334,-342334 );
      gmtl::normalize( q3 );
      gmtl::normalize( q5 );

      gmtl::Quatf expected_result1( 0, 0, 1, 0 ), expected_result2( 0.5, -0.5, 0.5, -0.5 );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, q3, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result2, q5, eps ) );
      
      CPPUNIT_ASSERT( gmtl::isNormalized( expected_result1 ) );
      CPPUNIT_ASSERT( gmtl::isNormalized( expected_result2 ) );
   }
   
   void testQuatNormalizeFast()
   {
      const float eps = 0.0001f;
      gmtl::Quatf q3( 0,0,2,0 ), q5( 2,-2,2,-2 );
      gmtl::normalizeFast( q3 );
      gmtl::normalizeFast( q5 );

      gmtl::Quatf expected_result1( 0, 0, 0.5, 0 ), expected_result2( 0.125, -0.125, 0.125, -0.125 );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, q3, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result2, q5, eps ) );
   }
   
   void testQuatConj()
   {
      const float eps = 0.0001f;
      gmtl::Quatf q3( 0,0,342334,0 ), q5( 342334,-342334,342334,-342334 );
      gmtl::conj( q3 );
      gmtl::conj( q5 );

      gmtl::Quatf expected_result1( 0, 0, -342334, 0 ), expected_result2( -342334,342334,-342334,-342334 );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, q3, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result2, q5, eps ) );
   }

   void testQuatInvert()
   {
      // test out mult( result, quat, quat )
      const float eps = 0.0001f;
      gmtl::Quatf q( 0.2, 0.33, 0.44, 0.101 ), expected_result( -0.567053, -0.935637, -1.24752, 0.286362 );
      gmtl::Quatf q2( q );
      gmtl::Quatf q3( gmtl::invert( q2 ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result, q3, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result, q2, eps ) );
      
      gmtl::Quatf q4( makeInvert( q ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result, q4, eps ) );
   }

   /** @todo, slerp, lerp, squad, meantangent, exp, log */
   

   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("QuatOpsTest");
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatMult", &QuatOpsTest::testQuatMult));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatVectorMult", &QuatOpsTest::testQuatVectorMult));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatDiv", &QuatOpsTest::testQuatDiv));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatVectorAdd", &QuatOpsTest::testQuatVectorAdd));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatVectorSub", &QuatOpsTest::testQuatVectorSub));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatVectorDot", &QuatOpsTest::testQuatVectorDot));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatNorm", &QuatOpsTest::testQuatNorm));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatMag", &QuatOpsTest::testQuatMag));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatNormalize", &QuatOpsTest::testQuatNormalize));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatNormalizeFast", &QuatOpsTest::testQuatNormalizeFast));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatConj", &QuatOpsTest::testQuatConj));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatInvert", &QuatOpsTest::testQuatInvert));
      
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingMult", &QuatOpsTest::testQuatTimingMult));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingOperatorMult", &QuatOpsTest::testQuatTimingOperatorMult));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingVectorMult", &QuatOpsTest::testQuatTimingVectorMult));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingDiv", &QuatOpsTest::testQuatTimingDiv));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingVectorAdd", &QuatOpsTest::testQuatTimingVectorAdd));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingVectorSub", &QuatOpsTest::testQuatTimingVectorSub));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingVectorDot", &QuatOpsTest::testQuatTimingVectorDot));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingNorm", &QuatOpsTest::testQuatTimingNorm));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingMag", &QuatOpsTest::testQuatTimingMag));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingNormalize", &QuatOpsTest::testQuatTimingNormalize));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingNormalizeFast", &QuatOpsTest::testQuatTimingNormalizeFast));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingConj", &QuatOpsTest::testQuatTimingConj));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>("testQuatTimingInvert", &QuatOpsTest::testQuatTimingInvert));

      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
