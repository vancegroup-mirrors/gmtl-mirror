/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: EulerAngleCompareTest.h,v $
 * Date modified: $Date: 2002-06-12 19:38:53 $
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
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/EulerAngle.h>
#include <gmtl/EulerAngleOps.h>

namespace gmtlTest
{

class EulerAngleCompareTest : public CppUnit::TestCase
{
public:
   EulerAngleCompareTest( std::string name = "EulerAngleCompareTest" )
      : CppUnit::TestCase (name)
   {;}

   virtual ~EulerAngleCompareTest()
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
         gmtl::EulerAngle<T, gmtl::ZYX> euler1, euler2;
         euler1.set( (T)1.0, (T)2.0, (T)34.0 );
         euler1 = euler2;
         CPPUNIT_ASSERT( euler1 == euler2 );
         CPPUNIT_ASSERT( euler2 == euler1 );

         // Test that != works on all elements
         for (int j = 0; j < 3; ++j)
         {
            euler2[j] = (T)1221.0f;
            CPPUNIT_ASSERT(  (euler1 != euler2) );
            CPPUNIT_ASSERT( !(euler1 == euler2) );
            euler2[j] = euler1[j]; // put it back
         }
         
         // just for fun
         CPPUNIT_ASSERT(  (euler1 == euler2) );
         CPPUNIT_ASSERT( !(euler1 != euler2) );

         // Test for epsilon equals working
         CPPUNIT_ASSERT( gmtl::isEqual( euler1, euler2 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( euler1, euler2, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( euler2, euler1, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( euler2, euler1, (T)100000.0f ) );
         T eps = (T)10.0;
         for (int j = 0; j < 3; ++j)
         {
            euler2[j] = euler1[j] - (eps / (T)2.0);
            CPPUNIT_ASSERT(  gmtl::isEqual( euler1, euler2, eps ) );
            CPPUNIT_ASSERT( !gmtl::isEqual( euler1, euler2, (T)(eps / 3.0) ) );
            euler2[j] = euler1[j]; // put it back
         }
      }
   };

  
   void testEulerAngleEqualityFloatTest();
   void testEulerAngleEqualityDoubleTest();
   void testEulerAngleTimingOpEqualityTest();
   void testEulerAngleTimingOpNotEqualityTest();
   void testEulerAngleTimingIsEqualTest();
   

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("EulerAngleCompareTest");
      test_suite->addTest( new CppUnit::TestCaller<EulerAngleCompareTest>("testEulerAngleEqualityFloatTest", &EulerAngleCompareTest::testEulerAngleEqualityFloatTest));
      test_suite->addTest( new CppUnit::TestCaller<EulerAngleCompareTest>("testEulerAngleEqualityDoubleTest", &EulerAngleCompareTest::testEulerAngleEqualityDoubleTest));
      return test_suite;
   }

   static Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("EulerAngleTiming");
      test_suite->addTest( new CppUnit::TestCaller<EulerAngleCompareTest>("testEulerAngleTimingOpEqualityTest", &EulerAngleCompareTest::testEulerAngleTimingOpEqualityTest));
      test_suite->addTest( new CppUnit::TestCaller<EulerAngleCompareTest>("testEulerAngleTimingIsEqualTest", &EulerAngleCompareTest::testEulerAngleTimingIsEqualTest));
      test_suite->addTest( new CppUnit::TestCaller<EulerAngleCompareTest>("testEulerAngleTimingOpNotEqualityTest", &EulerAngleCompareTest::testEulerAngleTimingOpNotEqualityTest));
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
