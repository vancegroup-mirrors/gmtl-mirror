/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MathTest.h,v $
 * Date modified: $Date: 2002-07-02 02:07:01 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 *********************************************************** ggt-head end */
/*************************************************************** ggt-cpr beg
*
* GGT: The Generic Graphics Toolkit
* Copyright (C) 2001, 2002 Allen Bierbaum
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
#ifndef _GMTL_MATHTEST_H_
#define _GMTL_MATHTEST_H_

#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Math.h>

namespace gmtlTest
{

class MathTest : public CppUnit::TestCase
{
public:
   MathTest( std::string name = "MathTest" )
   : CppUnit::TestCase (name)
   {}

   virtual ~MathTest()
   {}

   virtual void setUp()
   {}

   virtual void tearDown()
   {
   }

   template< class T >
   void testZeroClamp()
   {
      T val;
      
      val = T(0.5);
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val) == val );
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val, T(0.49)) == val );
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val, T(0.50)) == T(0) );
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val, T(0.51)) == T(0) );

      val = T(25.0);
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val) == val );
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val, T(24.9)) == val );
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val, T(25.0)) == T(0) );
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val, T(25.1)) == T(0) );

      // test performance
      const long iters(400000);
      T use_val(0);
      val = T(0);

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         val += T(0.5);
         use_val += gmtl::Math::zeroClamp( val, T(0.4) );
         use_val += gmtl::Math::zeroClamp( val, T(0.2) );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      std::string typeName = std::string("MathTest/ZeroClamp[") + std::string(typeid(T).name()) + std::string("]");
      CPPUNIT_ASSERT_METRIC_TIMING_LE(typeName, iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize out use_val
      CPPUNIT_ASSERT( use_val > 0 );
   }

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MathTest");
// work around buggy VC7
#ifndef _WIN32
      test_suite->addTest(new CppUnit::TestCaller<MathTest>("testZeroClampFloat", &MathTest::testZeroClamp<float>));
      test_suite->addTest(new CppUnit::TestCaller<MathTest>("testZeroClampDouble", &MathTest::testZeroClamp<double>));
#else
      test_suite->addTest(new CppUnit::TestCaller<MathTest>("testZeroClampFloat", MathTest::testZeroClamp<float>));
      test_suite->addTest(new CppUnit::TestCaller<MathTest>("testZeroClampDouble", MathTest::testZeroClamp<double>));
#endif // ! _WIN32

      return test_suite;
   }

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MathTiming");
      return test_suite;
   }
   
   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }
};

} // namespace gmtlTest

#endif
