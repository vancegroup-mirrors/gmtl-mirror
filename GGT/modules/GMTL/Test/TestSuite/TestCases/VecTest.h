/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: VecTest.h,v $
 * Date modified: $Date: 2002-01-26 23:10:48 $
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
#include <gfxConfig.h>
#include <iostream>

#include <TestCase.h>
#include <TestSuite.h>
#include <TestCaller.h>

#include <GMTL/Vec.h>

namespace gmtlTest
{

class VecTest : public TestCase
{
public:
   VecTest( std::string name )
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
      TestSuite* test_suite = new TestSuite ("VecTest");
      test_suite->addTest( new TestCaller<VecTest>("testVecCreate", &VecTest::testVecCreation));
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      /*
      TestSuite* test_suite = new TestSuite ("InteractiveThreadTest");
      test_suite->addTest( new TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
      */
   }

protected:

};

};
