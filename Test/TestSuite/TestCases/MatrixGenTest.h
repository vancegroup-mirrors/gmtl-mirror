/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixGenTest.h,v $
 * Date modified: $Date: 2002-05-10 23:16:09 $
 * Version:       $Revision: 1.24 $
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
   MatrixGenTest( std::string name = "MatrixGenTest" )
      : CppUnit::TestCase (name)
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

   // correctness tests
   void testMatrixsetTrans();
   void testMatrixsetAxes();
   void testMatrixsetDirCos();
   void testMatrixsetScale();
   void testMatrixsetRot();
   void testMatrixsetRotEuler();
   void testMatrixgetRotEuler();
   void testMatrixmakeInverse();
   
   // performance tests
   void testTimingsetTrans();
   void testTimingsetScale();
   void testTimingsetRot33();
   void testTimingsetRot34();
   void testTimingsetRot44();
   void testTimingGetRot();
   void testTimingsetRotEuler33();
   void testTimingsetRotEuler34();
   void testTimingsetRotEuler44();
   void testTimingsetDirCos33();
   void testTimingsetDirCos34();
   void testTimingsetDirCos44();
   void testTimingsetAxes33();
   void testTimingsetAxes34();
   void testTimingsetAxes44();
   void testTimingsetAxes();
   
   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixGenTest");

      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixgetRotEuler", &MatrixGenTest::testMatrixgetRotEuler ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixsetTrans", &MatrixGenTest::testMatrixsetTrans ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixsetAxes", &MatrixGenTest::testMatrixsetAxes ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixsetDirCos", &MatrixGenTest::testMatrixsetDirCos ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixsetRotEuler", &MatrixGenTest::testMatrixsetRotEuler ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixsetScale", &MatrixGenTest::testMatrixsetScale ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixsetRot", &MatrixGenTest::testMatrixsetRot ) );
       test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixmakeInverse", &MatrixGenTest::testMatrixmakeInverse ) );

      return test_suite;
   }

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixGenPerfTest");

      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingsetTrans", &MatrixGenTest::testTimingsetTrans ) );
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testTimingMakeTransStatic", &MatrixGenTest::testTimingMakeTransStatic ) );
      */

      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingsetScale", &MatrixGenTest::testTimingsetScale ) );
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeScaleStatic", &MatrixGenTest::testTimingMakeScaleStatic) );
      */

      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingsetRot33", &MatrixGenTest::testTimingsetRot33 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingsetRot34", &MatrixGenTest::testTimingsetRot34 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingsetRot44", &MatrixGenTest::testTimingsetRot44 ) );
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRot33Static", &MatrixGenTest::testTimingMakeRot33Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRot34Static", &MatrixGenTest::testTimingMakeRot34Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRot44Static", &MatrixGenTest::testTimingMakeRot44Static ) );
      */

      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingGetRot", &MatrixGenTest::testTimingGetRot ) );

      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingsetRotEuler33", &MatrixGenTest::testTimingsetRotEuler33 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingsetRotEuler34", &MatrixGenTest::testTimingsetRotEuler34 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingsetRotEuler44", &MatrixGenTest::testTimingsetRotEuler44 ) );
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRotEuler33Static", &MatrixGenTest::testTimingMakeRot33Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRotEuler34Static", &MatrixGenTest::testTimingMakeRot34Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRotEuler44Static", &MatrixGenTest::testTimingMakeRot44Static ) );
      */

      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingsetDirCos33", &MatrixGenTest::testTimingsetDirCos33 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingsetDirCos34", &MatrixGenTest::testTimingsetDirCos34 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingsetDirCos44", &MatrixGenTest::testTimingsetDirCos44 ) );
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeDirCos33Static", &MatrixGenTest::testTimingMakeDirCos33Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeDirCos34Static", &MatrixGenTest::testTimingMakeDirCos34Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeDirCos44Static", &MatrixGenTest::testTimingMakeDirCos44Static ) );
      */

      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testTimingsetAxes33", &MatrixGenTest::testTimingsetAxes33 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testTimingsetAxes34", &MatrixGenTest::testTimingsetAxes34 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testTimingsetAxes44", &MatrixGenTest::testTimingsetAxes44 ) );
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testTimingMakeAxes33Static", &MatrixGenTest::testTimingMakeAxes33Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testTimingMakeAxes34Static", &MatrixGenTest::testTimingMakeAxes34Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testTimingMakeAxes44Static", &MatrixGenTest::testTimingMakeAxes44Static ) );
      */

      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("bokbokbokbokbokbokbokbok");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
