/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: OutputTest.h,v $
 * Date modified: $Date: 2002-07-02 02:07:02 $
 * Version:       $Revision: 1.7 $
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
#ifndef _GMTL_OUTPUTTEST_H_
#define _GMTL_OUTPUTTEST_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

namespace gmtlTest
{
   class OutputTest : public CppUnit::TestCase
   {
   public:
      OutputTest( std::string name = "SphereTest" )
         : CppUnit::TestCase( name )
      {}

      virtual ~OutputTest()
      {}

      virtual void setUp()
      {}

      virtual void tearDown()
      {}

      void testVec();
      void testPoint();
      void testMatrix();
      void testQuat();
      void testTri();
      void testPlane();
      void testSphere();

      static CppUnit::Test* suite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "OutputTest" );
         test_suite->addTest( new CppUnit::TestCaller<OutputTest>("testVec", &OutputTest::testVec) );
         test_suite->addTest( new CppUnit::TestCaller<OutputTest>("testPoint", &OutputTest::testPoint) );
         test_suite->addTest( new CppUnit::TestCaller<OutputTest>("testMatrix", &OutputTest::testMatrix) );
         test_suite->addTest( new CppUnit::TestCaller<OutputTest>("testQuat", &OutputTest::testQuat) );
         test_suite->addTest( new CppUnit::TestCaller<OutputTest>("testTri", &OutputTest::testTri) );
         test_suite->addTest( new CppUnit::TestCaller<OutputTest>("testPlane", &OutputTest::testPlane) );
         test_suite->addTest( new CppUnit::TestCaller<OutputTest>("testSphere", &OutputTest::testSphere) );

         return test_suite;
      }
      
      static CppUnit::Test* perfSuite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("OutputTiming");
         return test_suite;
      }
   };

}

#endif
