/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: VecTest.h,v $
 * Date modified: $Date: 2002-02-10 04:38:06 $
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
#include <gmtl/gmtlConfig.h>
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Vec.h>

namespace gmtlTest
{

class VecTest : public CppUnit::TestCase
{
public:
   VecTest( std::string name = "VecTest" )
   : TestCase (name)
   {;}

   virtual ~VecTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void testVecCreation()
   {
      gmtl::Vec<3,gmtl::Float>  float_vec3;
      gmtl::Vec<3,gmtl::Double> double_vec3;
      gmtl::Vec<4,gmtl::Float>  float_vec4;
      gmtl::Vec<4,gmtl::Double> double_vec4;
   }



   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("VecTest");
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testVecCreate", &VecTest::testVecCreation));
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      /*
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
      */
   }

protected:

};

};
