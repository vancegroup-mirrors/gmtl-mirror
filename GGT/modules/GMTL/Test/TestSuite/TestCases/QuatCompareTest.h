/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: QuatCompareTest.h,v $
 * Date modified: $Date: 2002-02-21 23:19:14 $
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

namespace gmtlTest
{

class QuatCompareTest : public CppUnit::TestCase
{
public:
   QuatCompareTest( std::string name = "QuatCompareTest" )
   : TestCase (name)
   {;}

   virtual ~QuatCompareTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   template<typename T>
   class testEqual
   {
   public:
      static void go()
      {
         gmtl::Quat<T> quat1, quat2;
         quat1.set( (T)1.0, (T)2.0, (T)34.0, (T)4.0 );
         quat1 = quat2;
         CPPUNIT_ASSERT( quat1 == quat2 );
         CPPUNIT_ASSERT( quat2 == quat1 );

         // Test that != works on all elements
         for (int j = 0; j < 4; ++j)
         {
            quat2[j] = (T)1221.0f;
            CPPUNIT_ASSERT(  (quat1 != quat2) );
            CPPUNIT_ASSERT( !(quat1 == quat2) );
            quat2[j] = quat1[j]; // put it back
         }

         // Test for epsilon equals working
         CPPUNIT_ASSERT( gmtl::isEqual( quat1, quat2 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( quat1, quat2, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( quat2, quat1, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( quat2, quat1, (T)100000.0f ) );
         T eps = (T)10.0;
         for (int j = 0; j < 4; ++j)
         {
               quat2[j] = quat1[j] - (eps / (T)2.0);
               CPPUNIT_ASSERT(  gmtl::isEqual( quat1, quat2, eps ) );
               CPPUNIT_ASSERT( !gmtl::isEqual( quat1, quat2, (T)(eps / 3.0) ) );
               quat2[j] = quat1[j]; // put it back
         }
      }
   };
   
   void testMatEqualityFloatTest()
   {
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
   }
   
   void testMatEqualityDoubleTest()
   {
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
   }
   
   void testMatTimingOpEqualityTest()
   {
      // Test overhead of creation
      const long iters(400000);
      
      gmtl::Quat<float> src_quat11;
      gmtl::Quat<float> src_quat22;
      gmtl::Quat<float> src_quat33;
      gmtl::Quat<float> src_quat34;
      gmtl::Quat<float> src_quat44;
      gmtl::Quat<double> src_quat101;
      
      // half of them will be equal
      src_quat11[0] = 1.0f;
      src_quat22[2] = 1.0f;
      src_quat33[3] = 2.0f;
      
      gmtl::Quat<float> test_quat11( src_quat11 );
      gmtl::Quat<float> test_quat22( src_quat22 );
      gmtl::Quat<float> test_quat33( src_quat33 );
      gmtl::Quat<float> test_quat34( src_quat34 );
      gmtl::Quat<float> test_quat44( src_quat44 );
      gmtl::Quat<double> test_quat101( src_quat101 );
      
      // half will be not equal
       src_quat34[0] = 2.0f;
       src_quat44[1] = 3.0f;
      src_quat101[3] = 1.0;
      
      CPPUNIT_METRIC_START_TIMING();

      bool result = false;
      for( long iter=0;iter<iters; ++iter)
      {
         result = (src_quat11 == test_quat11);
         result = (src_quat22 == test_quat22);
         result = (src_quat33 == test_quat33);
         result = (src_quat34 == test_quat34);
         result = (src_quat44 == test_quat44);
         result = (src_quat101 == test_quat101);
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatCompareTest/operator==", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatTimingOpNotEqualityTest()
   {
      // Test overhead of creation
      const long iters(400000);
      
      gmtl::Quat<float> src_quat11;
      gmtl::Quat<float> src_quat22;
      gmtl::Quat<float> src_quat33;
      gmtl::Quat<float> src_quat34;
      gmtl::Quat<float> src_quat44;
      gmtl::Quat<double> src_quat101;
      
      // half will be equal
      src_quat11[0] = 1.0f;
      src_quat22[2] = 1.0f;
      src_quat33[3] = 2.0f;
      
      gmtl::Quat<float> test_quat11( src_quat11 );
      gmtl::Quat<float> test_quat22( src_quat22 );
      gmtl::Quat<float> test_quat33( src_quat33 );
      gmtl::Quat<float> test_quat34( src_quat34 );
      gmtl::Quat<float> test_quat44( src_quat44 );
      gmtl::Quat<double> test_quat101( src_quat101 );
      
      // half will be not equal
       src_quat34[0] = 2.0f;
       src_quat44[1] = 3.0f;
      src_quat101[3] = 1.0f;
      
      CPPUNIT_METRIC_START_TIMING();

      bool result = false;
      for( long iter=0;iter<iters; ++iter)
      {
         result = (src_quat11 != test_quat11);
         result = (src_quat22 != test_quat22);
         result = (src_quat33 != test_quat33);
         result = (src_quat34 != test_quat34);
         result = (src_quat44 != test_quat44);
         result = (src_quat101 != test_quat101);
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatCompareTest/operator!=", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatTimingIsEqualTest()
   {
      // Test overhead of creation
      const long iters(400000);
      
      gmtl::Quat<float> src_quat11;
      gmtl::Quat<float> src_quat22;
      gmtl::Quat<float> src_quat33;
      gmtl::Quat<float> src_quat34;
      gmtl::Quat<float> src_quat44;
      gmtl::Quat<double> src_quat101;
      
      // half will be equal
      src_quat11[0] = 1.0f;
      src_quat22[1] = 1.0f;
      src_quat33[2] = 2.0f;
      
      gmtl::Quat<float> test_quat11( src_quat11 );
      gmtl::Quat<float> test_quat22( src_quat22 );
      gmtl::Quat<float> test_quat33( src_quat33 );
      gmtl::Quat<float> test_quat34( src_quat34 );
      gmtl::Quat<float> test_quat44( src_quat44 );
      gmtl::Quat<double> test_quat101( src_quat101 );
      
      // half will be not equal
      src_quat34[3] = 23.0f;
      src_quat44[2] = 234.0f;
      src_quat101[1] = 1234.0f;
      
      CPPUNIT_METRIC_START_TIMING();

      bool result = false;
      for( long iter=0;iter<iters; ++iter)
      {
         result = gmtl::isEqual( src_quat11,  test_quat11, 0.0f  );
         result = gmtl::isEqual( src_quat22,  test_quat22, 0.2f  );
         result = gmtl::isEqual( src_quat33,  test_quat33, 0.3f  );
         result = gmtl::isEqual( src_quat34,  test_quat34, 0.6f  );
         result = gmtl::isEqual( src_quat44,  test_quat44, 0.8f  );
         result = gmtl::isEqual( src_quat101, test_quat101, 111.1 );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatCompareTest/isEqual(...)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }   
   
   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("QuatCompareTest");
      test_suite->addTest( new CppUnit::TestCaller<QuatCompareTest>("testMatTimingOpEqualityTest", &QuatCompareTest::testMatTimingOpEqualityTest));
      test_suite->addTest( new CppUnit::TestCaller<QuatCompareTest>("testMatTimingIsEqualTest", &QuatCompareTest::testMatTimingIsEqualTest));
      test_suite->addTest( new CppUnit::TestCaller<QuatCompareTest>("testMatTimingOpNotEqualityTest", &QuatCompareTest::testMatTimingOpNotEqualityTest));
      test_suite->addTest( new CppUnit::TestCaller<QuatCompareTest>("testMatEqualityFloatTest", &QuatCompareTest::testMatEqualityFloatTest));
      test_suite->addTest( new CppUnit::TestCaller<QuatCompareTest>("testMatEqualityDoubleTest", &QuatCompareTest::testMatEqualityDoubleTest));
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
