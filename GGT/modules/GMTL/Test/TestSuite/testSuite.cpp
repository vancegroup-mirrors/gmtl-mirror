/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: testSuite.cpp,v $
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
#include <CppUnit/textui/TestRunner.h>

// GFX tests
#include <Threads/ThreadTest.h>
#include <Threads/ThreadPoolTest.h>

// GMTL tests
#include <GMTL/Vec3Test.h>
#include <GMTL/MatrixTest.h>
#include <GMTL/Point3Test.h>
#include <GMTL/XformTest.h>
#include <GMTL/OOBoxTest.h>
#include <GMTL/PlaneTest.h>
#include <GMTL/ContainmentTest.h>
#include <GMTL/IntersectionTest.h>
#include <GMTL/QuatTest.h>
#include <GMTL/TriTest.h>

// SGA tests
#include <SGA/ContainerHolderTest.h>
#include <SGA/PfTriangleListAdapterTest.h>
#include <SGA/PfNodeAdapterTest.h>


int main (int ac, char **av)
{
   TestRunner runner;
	
   //------------------------------------
   //  GFX Tests
   //------------------------------------	
   // Create the tests
   TestSuite* gfx_suite = new TestSuite("gfx_suite");
	gfx_suite->addTest(gfxTest::ThreadTest::suite());
	gfx_suite->addTest(gfxTest::ThreadPoolTest::suite());
	
	TestSuite* interactive_gfx_suite = new TestSuite("InteractiveGFX");
	interactive_gfx_suite->addTest(gfxTest::ThreadTest::interactiveSuite());
	interactive_gfx_suite->addTest(gfxTest::ThreadPoolTest::interactiveSuite());

    // Add the tests
    runner.addTest( "gfx", gfx_suite );
    runner.addTest( "interactiveGfx", interactive_gfx_suite );

    //------------------------------------
   //  GMTL Tests
   //------------------------------------
   // Create the tests
   TestSuite* gmtl_suite = new TestSuite("gmtl_suite");
	gmtl_suite->addTest(gmtlTest::Vec3Test::suite());
   gmtl_suite->addTest(gmtlTest::MatrixTest::suite());
   gmtl_suite->addTest(gmtlTest::Point3Test::suite());
   gmtl_suite->addTest(gmtlTest::XformTest::suite());
   gmtl_suite->addTest(gmtlTest::OOBoxTest::suite());
   gmtl_suite->addTest(gmtlTest::PlaneTest::suite());
   gmtl_suite->addTest(gmtlTest::ContainmentTest::suite());
   gmtl_suite->addTest(gmtlTest::IntersectionTest::suite());
   gmtl_suite->addTest(gmtlTest::QuatTest::suite());
   gmtl_suite->addTest(gmtlTest::TriTest::suite());
   // Add the tests
   runner.addTest("gmtl", gmtl_suite);

   //------------------------------------
   //  SGA Tests
   //------------------------------------
   // Create the tests
   TestSuite* sga_suite = new TestSuite("sga_suite");
	sga_suite->addTest(sgaTest::ContainerHolderTest::suite());
   sga_suite->addTest(sgaTest::PfTriangleListAdapterTest::suite());
   sga_suite->addTest(sgaTest::PfNodeAdapterTest::suite());
   //sgaTest::PfTriangleListAdapterTest::testIt();

   // Add the tests
   runner.addTest("sga", sga_suite);


    // --- RUN THEM --- //
    runner.run( ac, av );


    return 0;
}
