/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixGenTest.h,v $
 * Date modified: $Date: 2002-02-18 20:02:04 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 *********************************************************** ggt-head end */
/*************************************************************** ggt-cpr beg
*
* GGT: The Generic Graphics Toolkit
* Copyright (C) 2001, 2002 Allen Bierbaum
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

#include <gmtl/Matrix.h>
#include <gmtl/Generate.h>

namespace gmtlTest
{

class MatrixGenTest : public CppUnit::TestCase
{
public:
   MatrixGenTest( std::string name = "MatrixGenTest" ) : TestCase (name)
   {
   }

   virtual ~MatrixGenTest()
   {
   }

   virtual void setUp()
   {
   }

   virtual void tearDown()
   {
   }

   void testMatrixMakeRot33ByRef()
   {
      gmtl::Matrix33f mat;
      
      // Test overhead of creation
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, 90.0f, 1.0f, 0.0f, 0.0f );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixTest/matMakeRot33ByRef", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeRot34ByRef()
   {
      gmtl::Matrix34f mat;
      
      // Test overhead of creation
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, 90.0f, 1.0f, 0.0f, 0.0f );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixTest/matMakeRot34ByRef", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeRot44ByRef()
   {
      gmtl::Matrix44f mat;
      
      // Test overhead of creation
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, 90.0f, 1.0f, 0.0f, 0.0f );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixTest/matMakeRot44ByRef", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixGenTest");
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot33ByRef", &MatrixGenTest::testMatrixMakeRot33ByRef));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot34ByRef", &MatrixGenTest::testMatrixMakeRot34ByRef));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot44ByRef", &MatrixGenTest::testMatrixMakeRot44ByRef));
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
