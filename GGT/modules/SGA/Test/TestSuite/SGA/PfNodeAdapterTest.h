/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: PfNodeAdapterTest.h,v $
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

#include <Performer/pf.h>
#include <Performer/pf/pfNode.h>
#include <Performer/pf/pfGroup.h>
#include <Performer/pf/pfDCS.h>
#include <Performer/pr/pfObject.h>

#include <SGA/PfNodeAdapters.h>

// Containers to test with it
#include <SGA/ObbNodeContainer.h>


#include <gfxConfig.h>
#include <Util/Assert.h>


namespace sgaTest
{

class PfNodeAdapterTest : public TestCase
{
public:
   PfNodeAdapterTest( std::string name )
   : TestCase (name)
   //PfTriangleListAdapterTest()
   {;}

   virtual ~PfNodeAdapterTest()
   {}


   virtual void setUp()
   {
      if(!pfIsInited())
      {
         pfInit();
         pfInitState(NULL);
      }

      if(!pfIsConfiged())
      {
         pfConfig();
      }
   }

   virtual void tearDown()
   {
   }

   // Verify that performer returns NULL by default for unassigned slots
   void testNullSlotDefault()
   {
      int test_slot_id;
      test_slot_id = pfObject::getNamedUserDataSlot("PfNodeAdapterTest_testNull");
      std::cout << "test_slot_id: " << test_slot_id << std::endl;

      //pfNode* test_node = new pfNode;
      pfGroup* test_group = new pfGroup;
      pfDCS* test_dcs = new pfDCS;

      //assertTest(test_node->getUserData(test_slot_id) == NULL);
      assertTest(test_group->getUserData(test_slot_id) == NULL);
      assertTest(test_dcs->getUserData(test_slot_id) == NULL);
   }

   void testNodeAdapterInit()
   {
      pfGroup* test_group = new pfGroup;
      sga::NodeAdapter adapted_group(test_group);

      assertTest((&adapted_group.contHolder()) != NULL);
   }

   void testNodeAdapterContainer()
   {
      pfGroup* test_group = new pfGroup;
      sga::NodeAdapter adapted_group(test_group);

      sga::ObbNodeContainer* obb_cont = new sga::ObbNodeContainer;
      sga::ObbNodeContainer* ret_obb_cont;

      ret_obb_cont = adapted_group.contHolder().getContainer<sga::ObbNodeContainer>();
      assertTest(ret_obb_cont == NULL);

      adapted_group.contHolder().setContainer(obb_cont);
      ret_obb_cont = adapted_group.contHolder().getContainer<sga::ObbNodeContainer>();
      assertTest(obb_cont == ret_obb_cont);

      adapted_group.contHolder().setContainer<sga::ObbNodeContainer>(obb_cont);
      ret_obb_cont = adapted_group.contHolder().getContainer<sga::ObbNodeContainer>();
      assertTest(obb_cont == ret_obb_cont);
   }


   static Test* suite()
   {
      TestSuite* test_suite = new TestSuite ("PfNodeAdapterTest");
      test_suite->addTest( new TestCaller<PfNodeAdapterTest>("testNullSlotDefault", &PfNodeAdapterTest::testNullSlotDefault));
      test_suite->addTest( new TestCaller<PfNodeAdapterTest>("testNodeAdapterInit", &PfNodeAdapterTest::testNodeAdapterInit));
      test_suite->addTest( new TestCaller<PfNodeAdapterTest>("testNodeAdapterContainer", &PfNodeAdapterTest::testNodeAdapterContainer));
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      TestSuite* test_suite = new TestSuite ("InteractivePfTriangleListAdapterTest");
      //test_suite->addTest( new TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }
};

};
