/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: SphereTest.h,v $
 * Date modified: $Date: 2002-07-02 02:07:02 $
 * Version:       $Revision: 1.15 $
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

namespace gmtlTest
{

class SphereTest : public CppUnit::TestCase
{
public:
   SphereTest( std::string name = "SphereTest" )
   : CppUnit::TestCase (name)
   {}

   virtual ~SphereTest()
   {}

   virtual void setUp()
   {}

   virtual void tearDown()
   {
   }

   void testCreation();
   void testCopyConstruct();
   void testConstructors();

   // -- Test accessors --//
   void testGetCenter();
   void testGetRadius();

   // -- Test setters --//
   void testSetCenter();
   void testSetRadius();

   // -- Test comparison -- //
   void testEqualityCompare();
   void testIsEqual();

   //---------------------------------------------------------------------------
   // Containment tests
   //---------------------------------------------------------------------------
   void testIsInVolumePoint();
   void testIsInVolumeSphere();
   void testIsOnVolume();
   void testExtendVolumePoint();
   void testExtendVolumeSphere();
   void testMakeVolumePoint();
//   void testMakeVolumeSphere();

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("SphereTest");
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testCreation", &SphereTest::testCreation));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testCopyConstruct", &SphereTest::testCopyConstruct));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testConstructors", &SphereTest::testConstructors));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testEqualityCompare", &SphereTest::testEqualityCompare));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testIsEqual", &SphereTest::testIsEqual));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testGetCenter", &SphereTest::testGetCenter));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testGetRadius", &SphereTest::testGetRadius));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testSetCenter", &SphereTest::testSetCenter));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testSetRadius", &SphereTest::testSetRadius));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testIsInVolumePoint", &SphereTest::testIsInVolumePoint));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testIsInVolumeSphere", &SphereTest::testIsInVolumeSphere));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testIsOnVolume", &SphereTest::testIsOnVolume));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testExtendVolumePoint", &SphereTest::testExtendVolumePoint));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testExtendVolumeSphere", &SphereTest::testExtendVolumeSphere));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testMakeVolumePoint", &SphereTest::testMakeVolumePoint));
//      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testMakeVolumeSphere", &SphereTest::testMakeVolumeSphere));

      return test_suite;
   }

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("SphereTiming");
      return test_suite;
   }
   
   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveSphereTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
