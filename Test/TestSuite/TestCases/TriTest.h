/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: TriTest.h,v $
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

#include <GMTL/Tri.h>

namespace gmtlTest
{
   using namespace gmtl;

class TriTest : public TestCase
{
public:
   TriTest( std::string name )
   : TestCase (name)
   {;}

   virtual ~TriTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void testTriCreation()
   {
      gmtl::Tri  test_tri(Vec3::ZERO, Vec3::UNIT_X, Vec3::UNIT_Y);
      assertTest(test_tri[0] == Vec3::ZERO);
      assertTest(test_tri[1] == Vec3::UNIT_X);
      assertTest(test_tri[2] == Vec3::UNIT_Y);
   }

   void testEdges()
   {
      gmtl::Tri  test_tri(Vec3::ZERO, Vec3::UNIT_X, Vec3::UNIT_Y);
      Vec3 edge0 = Vec3::ZERO - Vec3::UNIT_X;
      Vec3 edge1 = Vec3::UNIT_Y - Vec3::UNIT_X;

      assertTest(test_tri.edge0() == edge0);
      assertTest(test_tri.edge1() == edge1);
   }

   void testCenter()
   {
      gmtl::Tri  test_tri(Vec3::ZERO, Vec3::UNIT_X, Vec3::UNIT_Y);

      Point3 center(0.333, 0.333, 0.0f);
      assertTest(center.equal(test_tri.center(), 0.01));
   }


   static Test* suite()
   {
      TestSuite* test_suite = new TestSuite ("TriTest");
      test_suite->addTest( new TestCaller<TriTest>("testTriCreation", &TriTest::testTriCreation));
      test_suite->addTest( new TestCaller<TriTest>("testEdges", &TriTest::testEdges));
      test_suite->addTest( new TestCaller<TriTest>("testCenter", &TriTest::testCenter));
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      TestSuite* test_suite = new TestSuite ("InteractiveTriTest");
      //test_suite->addTest( new TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
