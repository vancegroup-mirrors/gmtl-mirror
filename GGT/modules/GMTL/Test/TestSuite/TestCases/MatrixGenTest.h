/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixGenTest.h,v $
 * Date modified: $Date: 2002-02-18 20:39:59 $
 * Version:       $Revision: 1.2 $
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
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot33ByRef", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
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
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot34ByRef", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
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
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot44ByRef", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeRot33ByVal()
   {
      gmtl::Matrix<float, 3, 3> mat;
      
      // Test overhead of creation
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         mat = gmtl::makeRot<float, 3, 3>( 90.0f, 1.0f, 0.0f, 0.0f );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot33ByVal", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeRot34ByVal()
   {
      gmtl::Matrix<float, 3, 4> mat;
      
      // Test overhead of creation
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         mat = gmtl::makeRot<float, 3, 4>( 90.0f, 1.0f, 0.0f, 0.0f );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot34ByVal", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeRot44ByVal()
   {
      gmtl::Matrix<float, 4, 4> mat;
      
      // Test overhead of creation
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         mat = gmtl::makeRot<float, 4, 4>( 90.0f, 1.0f, 0.0f, 0.0f );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot44ByVal", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixGenTest");
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot33ByRef", &MatrixGenTest::testMatrixMakeRot33ByRef));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot34ByRef", &MatrixGenTest::testMatrixMakeRot34ByRef));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot44ByRef", &MatrixGenTest::testMatrixMakeRot44ByRef));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot33ByVal", &MatrixGenTest::testMatrixMakeRot33ByVal));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot34ByVal", &MatrixGenTest::testMatrixMakeRot34ByVal));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot44ByVal", &MatrixGenTest::testMatrixMakeRot44ByVal));
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
