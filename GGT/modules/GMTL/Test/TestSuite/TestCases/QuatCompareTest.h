/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: QuatCompareTest.h,v $
 * Date modified: $Date: 2002-07-02 02:07:02 $
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
      : CppUnit::TestCase (name)
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

   template<typename T>
   class testEquiv
   {
   public:
      static void go()
      {
         gmtl::Quat<T> quat1((T)1.0, (T)2.0, (T)34.0, (T)4.0),
                       quat2(-(T)1.0, -(T)2.0, -(T)34.0, -(T)4.0),
                       quat3((T)1.0, (T)2.0, (T)34.0, (T)4.0),
                       quat4;

         // Test for geometric equivelency
         CPPUNIT_ASSERT( gmtl::isEquiv( quat1, quat2 ) );
         CPPUNIT_ASSERT( gmtl::isEquiv( quat1, quat2, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEquiv( quat2, quat1, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEquiv( quat2, quat1, (T)100000.0f ) );

         // Test for geometric equivelency
         CPPUNIT_ASSERT( gmtl::isEquiv( quat1, quat3 ) );
         CPPUNIT_ASSERT( gmtl::isEquiv( quat1, quat3, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEquiv( quat3, quat1, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEquiv( quat3, quat1, (T)100000.0f ) );

         // Test for geometric un-equivelency
         CPPUNIT_ASSERT( !gmtl::isEquiv( quat1, quat4 ) );
         CPPUNIT_ASSERT( !gmtl::isEquiv( quat1, quat4, (T)0.0f ) );
         CPPUNIT_ASSERT( !gmtl::isEquiv( quat4, quat1, (T)0.0f ) );
         CPPUNIT_ASSERT( !gmtl::isEquiv( quat4, quat1, (T)30.0f ) );
      }
   };

   void testQuatEquiv();
   void testQuatEqualityFloatTest();
   void testQuatEqualityDoubleTest();
   void testQuatTimingOpEqualityTest();
   void testQuatTimingOpNotEqualityTest();
   void testQuatTimingIsEqualTest();
   void testQuatTimingEquiv();


   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("QuatCompareTest");
      test_suite->addTest( new CppUnit::TestCaller<QuatCompareTest>("testQuatEqualityFloatTest", &QuatCompareTest::testQuatEqualityFloatTest));
      test_suite->addTest( new CppUnit::TestCaller<QuatCompareTest>("testQuatEqualityDoubleTest", &QuatCompareTest::testQuatEqualityDoubleTest));
      test_suite->addTest( new CppUnit::TestCaller<QuatCompareTest>("testQuatEquiv", &QuatCompareTest::testQuatEquiv));
      return test_suite;
   }

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("QuatCompareTiming");
      test_suite->addTest( new CppUnit::TestCaller<QuatCompareTest>("testQuatTimingOpEqualityTest", &QuatCompareTest::testQuatTimingOpEqualityTest));
      test_suite->addTest( new CppUnit::TestCaller<QuatCompareTest>("testQuatTimingIsEqualTest", &QuatCompareTest::testQuatTimingIsEqualTest));
      test_suite->addTest( new CppUnit::TestCaller<QuatCompareTest>("testQuatTimingOpNotEqualityTest", &QuatCompareTest::testQuatTimingOpNotEqualityTest));
      test_suite->addTest( new CppUnit::TestCaller<QuatCompareTest>("testQuatTimingEquiv", &QuatCompareTest::testQuatTimingEquiv));
      return test_suite;
   }
   
   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
