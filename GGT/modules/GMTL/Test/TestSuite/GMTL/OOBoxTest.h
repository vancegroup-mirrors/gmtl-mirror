/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: OOBoxTest.h,v $
 * Date modified: $Date: 2002-01-18 20:43:11 $
 * Version:       $Revision: 1.1.1.1 $
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

#include <GMTL/OOBox.h>

namespace gmtlTest
{

class OOBoxTest : public TestCase
{
public:
   OOBoxTest( std::string name )
   : TestCase (name)
   {;}

   virtual ~OOBoxTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {;}

   void testBoxCreation()
   {
      gmtl::OOBox box1;
      gmtl::OOBox box2;

      box1.center().set(0.0, 1.0f, -2.0f);
      box1.axis(0) = gmtl::Vec3::UNIT_X;
      box1.axis(1) = gmtl::Vec3::UNIT_Y;
      box1.axis(2) = gmtl::Vec3::UNIT_Z;

      box2 = box1;

      assertTest(box2.center() == gmtl::Point3(0.0, 1.0f, -2.0f));
      assertTest(box2 == box1);
      assertTest(box1 == box2);
   }

   void testGetBoxVerts()
   {
      gmtl::OOBox box1;

      // Create box centered on origin
      // Aligned with major axes
      // with half lens 1,2,3
      box1.center().set(0.0, 0.0f, 0.0f);
      box1.axis(0) = gmtl::Vec3::UNIT_X;
      box1.axis(1) = gmtl::Vec3::UNIT_Y;
      box1.axis(2) = gmtl::Vec3::UNIT_Z;
      box1.halfLen(0) = 1.0f;
      box1.halfLen(1) = 2.0f;
      box1.halfLen(2) = 3.0f;

      gmtl::Point3 verts[8];
      box1.getVerts(verts);

      assertTest(verts[0] == gmtl::Point3(-1.0f,-2.0f,-3.0f));   // 000
      assertTest(verts[1] == gmtl::Point3(1.0f,-2.0f,-3.0f));   // 100
      assertTest(verts[2] == gmtl::Point3(1.0f,2.0f,-3.0f));   // 110
      assertTest(verts[3] == gmtl::Point3(-1.0f,2.0f,-3.0f));   // 010

      assertTest(verts[4] == gmtl::Point3(-1.0f,-2.0f,3.0f));   // 001
      assertTest(verts[5] == gmtl::Point3(1.0f,-2.0f,3.0f));   // 101
      assertTest(verts[6] == gmtl::Point3(1.0f,2.0f,3.0f));   // 111
      assertTest(verts[7] == gmtl::Point3(-1.0f,2.0f,3.0f));   // 011
   }


   static Test* suite()
   {
      TestSuite* test_suite = new TestSuite ("OOBoxTest");
      test_suite->addTest( new TestCaller<OOBoxTest>("testBoxCreation", &OOBoxTest::testBoxCreation));
      test_suite->addTest( new TestCaller<OOBoxTest>("testGetBoxVerts", &OOBoxTest::testGetBoxVerts));

      return test_suite;
   }

   static Test* interactiveSuite()
   {
      TestSuite* test_suite = new TestSuite ("OOBoxTestInteractive");
      //test_suite->addTest( new TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
