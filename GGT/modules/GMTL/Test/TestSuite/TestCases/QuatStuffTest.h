/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: QuatStuffTest.h,v $
 * Date modified: $Date: 2002-06-11 21:52:54 $
 * Version:       $Revision: 1.11 $
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
#include <gmtl/Generate.h>
#include <gmtl/Xforms.h>

namespace gmtlTest
{

   /** a hodge podge of tests.  stuff that is a little higher level, some real world tests, etc... */
   class QuatStuffTest : public CppUnit::TestCase
   {
   public:
      QuatStuffTest( std::string name = "QuatStuffTest" )
         : CppUnit::TestCase( name )
      {
      }

      virtual ~QuatStuffTest()
      {}

      virtual void setUp()
      {
      }

      virtual void tearDown()
      {
      }


      void makeRotTest();
      void xformVecSweepTest();
      void makeRotGetRotSanityTest();

   //   for (int x = 0; x < 4; ++x)
   //             std::cout<<q[x]<<" "<<q2[x]<<std::endl;

      void simpleQuatProductTest();
      // another quaternion product test
      void secondQuatProductTest();
      void xformVecTest();

      // just trying stuff out... TODO think of a good add test...
      void specialCases();

      // just trying stuff out... TODO think of a good way to test this ability...
      // TODO: could we use a vector (pure quat) to scale a quat in a
      //        more robust way?  pretty sure we can... rewrite scaleAngle to use this
      //        method instead....
      void vectorScaleTest();

      // just trying stuff out... TODO think of a good add test...
      void quatAdd();

      // using a vector to increment rotation, much like angular velocity
      // here angular velocity is defined as a gmtl::Vec3f "w", using right hand rule
      // things spin at |w| speed and on the w vector.
      //
      // just trying stuff out... TODO think of a good way to test this ability...
      void pureQuatMultTest();

      static CppUnit::Test* suite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "QuatStuffTest" );
         test_suite->addTest( new CppUnit::TestCaller<QuatStuffTest>( "xformVecTest", &QuatStuffTest::xformVecTest));
         test_suite->addTest( new CppUnit::TestCaller<QuatStuffTest>( "xformVecSweepTest", &QuatStuffTest::xformVecSweepTest));
         test_suite->addTest( new CppUnit::TestCaller<QuatStuffTest>( "makeRotGetRotSanityTest", &QuatStuffTest::makeRotGetRotSanityTest));
         test_suite->addTest( new CppUnit::TestCaller<QuatStuffTest>( "simpleQuatProductTest", &QuatStuffTest::simpleQuatProductTest));
         test_suite->addTest( new CppUnit::TestCaller<QuatStuffTest>( "secondQuatProductTest", &QuatStuffTest::secondQuatProductTest));
         test_suite->addTest( new CppUnit::TestCaller<QuatStuffTest>( "makeRotTest", &QuatStuffTest::makeRotTest));
         return test_suite;
      }

      static Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("QuatStuffTiming");
      return test_suite;
   }
   
      static CppUnit::Test* interactiveSuite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "InteractiveQuatStuffTest" );
         //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>( "interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind ) );
         return test_suite;
      }

   protected:

   };

} // end namespace
