/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: OptTest.h,v $
 * Date modified: $Date: 2002-02-11 20:38:12 $
 * Version:       $Revision: 1.7 $
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
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Vec3.h>
#include <gmtl/matVecFuncs.h>

namespace gmtlTest
{
   
class OptTest : public CppUnit::TestCase
{
public:
   OptTest( std::string name = "OptTest" );

   virtual ~OptTest();

   virtual void setUp();

   virtual void tearDown();

   // this simulates the invert or normalize func
   // two possibilities:
   //    invert( srcAndResult )
   //    invert( result, source )
   // 
   void testInPlace();
   
   // test perf of copy ops
   void testSetEqual();
   
   // test perf of returning result by reference (no temporary)
   void testRetByReference();
   
   // test perf of returning internal temporary by value
   void testRetValOptUsingInternalTemporary();
   
   // test perf of the the return value optimization when returning a temporary by value
   void testRetValOpt();
   
   // test performance of loop unrolling
   void testLoopUnrolling();
   
   

   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("OptTest");
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testInPlace", &OptTest::testInPlace));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testSetEqual", &OptTest::testSetEqual));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testRetByReference", &OptTest::testRetByReference));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testRetValOptUsingInternalTemporary", &OptTest::testRetValOptUsingInternalTemporary));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testRetValOpt", &OptTest::testRetValOpt));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testLoopUnrolling", &OptTest::testLoopUnrolling));
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }
private:
   
};

};
