/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: TriTest.h,v $
 * Date modified: $Date: 2002-02-10 04:38:06 $
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

#include <gmtl/Tri.h>

namespace gmtlTest
{
   using namespace gmtl;

class TriTest : public CppUnit::TestCase
{
public:
   TriTest( std::string name = "TriTest")
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
      gmtl::Tri  test_tri(ZeroVec3, XUnitVec3, YUnitVec3);
      CPPUNIT_ASSERT(test_tri[0] == ZeroVec3);
      CPPUNIT_ASSERT(test_tri[1] == XUnitVec3);
      CPPUNIT_ASSERT(test_tri[2] == YUnitVec3);
   }

   void testEdges()
   {
      gmtl::Tri  test_tri(ZeroVec3, XUnitVec3, YUnitVec3);
      Vec3 edge0 = ZeroVec3 - XUnitVec3;
      Vec3 edge1 = YUnitVec3 - XUnitVec3;

      CPPUNIT_ASSERT(test_tri.edge0() == edge0);
      CPPUNIT_ASSERT(test_tri.edge1() == edge1);
   }

   void testCenter()
   {
      gmtl::Tri  test_tri(ZeroVec3, XUnitVec3, YUnitVec3);

      Point3 center(0.333, 0.333, 0.0f);
      CPPUNIT_ASSERT(center.equal(test_tri.center(), 0.01));
   }


   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("TriTest");
      test_suite->addTest( new CppUnit::TestCaller<TriTest>("testTriCreation", &TriTest::testTriCreation));
      test_suite->addTest( new CppUnit::TestCaller<TriTest>("testEdges", &TriTest::testEdges));
      test_suite->addTest( new CppUnit::TestCaller<TriTest>("testCenter", &TriTest::testCenter));
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveTriTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
