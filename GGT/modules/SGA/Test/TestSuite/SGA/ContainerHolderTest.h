/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ContainerHolderTest.h,v $
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

#include <SGA/ContainerBase.h>
#include <SGA/ContainerHolder.h>

// Containers to test with it
#include <SGA/ObbNodeContainer.h>

namespace sgaTest
{

class ContainerHolderTest : public TestCase
{
public:
   ContainerHolderTest( std::string name )
   : TestCase (name)
   {;}

   virtual ~ContainerHolderTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void testHolderCreation()
   {
      sga::ContainerHolder holder;
      sga::ObbNodeContainer* obb_cont = new sga::ObbNodeContainer;
      sga::ObbNodeContainer* ret_obb_cont;

      ret_obb_cont = holder.getContainer<sga::ObbNodeContainer>();
      assertTest(ret_obb_cont == NULL);

      holder.setContainer(obb_cont);
      ret_obb_cont = holder.getContainer<sga::ObbNodeContainer>();
      assertTest(obb_cont == ret_obb_cont);

      holder.setContainer<sga::ObbNodeContainer>(obb_cont);
      ret_obb_cont = holder.getContainer<sga::ObbNodeContainer>();
      assertTest(obb_cont == ret_obb_cont);
   }

   static Test* suite()
   {
      TestSuite* test_suite = new TestSuite ("ContainerHolderTest");
      test_suite->addTest( new TestCaller<ContainerHolderTest>("testHolderCreation", &ContainerHolderTest::testHolderCreation));
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      TestSuite* test_suite = new TestSuite ("InteractiveContainerHolderTest");
      //test_suite->addTest( new TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
