/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixGenTest.h,v $
 * Date modified: $Date: 2002-03-18 21:56:24 $
 * Version:       $Revision: 1.20 $
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

   void testMatrixMakeTrans();
   void testMatrixMakeAxes();
   void testMatrixMakeDirCos();
   void testMatrixMakeScale();
   void testMatrixMakeRot();
   void testMatrixMakeRotEuler();
   void testTimingMakeTrans();
   /*
   void testTimingMakeTransStatic()
   {
      gmtl::Matrix22f mat22;
      gmtl::Matrix33f mat33;
      gmtl::Matrix34f mat34;
      gmtl::Matrix44f mat44;
      gmtl::Matrix43f mat43;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeTrans( mat22, Vec2f( 1, 2 ) );
         gmtl::makeTrans( mat33, Vec3f( 30, 32, 121 ) );
         gmtl::makeTrans( mat34, Vec3f( 30, 32, 121 ) );
         gmtl::makeTrans( mat43, Vec3f( 30, 32, 121 ) );
         gmtl::makeTrans( mat44, Vec3f( 30, 32, 121 ) );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeScale", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   */

   void testTimingMakeScale();
   /*
   void testTimingMakeScaleStatic()
   {
      gmtl::Matrix22f mat22;
      gmtl::Matrix33f mat33;
      gmtl::Matrix34f mat34;
      gmtl::Matrix44f mat44;
      gmtl::Matrix43f mat43;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeScale( mat22, Vec2f( 1, 2 ) );
         gmtl::makeScale( mat33, Vec3f( 30, 32, 121 ) );
         gmtl::makeScale( mat34, Vec3f( 30, 32, 121 ) );
         gmtl::makeScale( mat43, Vec3f( 30, 32, 121 ) );
         gmtl::makeScale( mat44, Vec3f( 30, 32, 121 ) );
         gmtl::makeScale( mat33, 2.0f );
         gmtl::makeScale( mat34, 3.0f );
         gmtl::makeScale( mat43, 4.0f );
         gmtl::makeScale( mat44, 5.0f );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeScale", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   */

   void testTimingMakeRot33();
   void testTimingMakeRot34();
   void testTimingMakeRot44();
   /*
   void testTimingMakeRot33Static()
   {
      gmtl::bok<gmtl::Matrix33f>( (float)1.0f );
      gmtl::Matrix<float, 3, 3> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix33f>( 90.0f, 1.0f, 0.0f, 0.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot33Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeRot34Static()
   {
      gmtl::Matrix<float, 3, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix34f>( 90.0f, 1.0f, 0.0f, 0.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot34Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeRot44Static()
   {
      gmtl::Matrix<float, 4, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix44f>( 90.0f, 1.0f, 0.0f, 0.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot44Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   */
   
         
   void testTimingGetRot()
   {
      // @todo ... write a getRot( mat, rad, axis ) test here....
   }
   
         
   // makeRot Euler tests...
   void testTimingMakeRotEuler33();
   void testTimingMakeRotEuler34();
   void testTimingMakeRotEuler44();
   /*
   void testTimingMakeRotEuler33Static()
   {
      gmtl::Matrix<float, 3, 3> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix33f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRotEuler33Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeRotEuler34Static()
   {
      gmtl::Matrix<float, 3, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix34f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRotEuler34Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeRotEuler44Static()
   {
      gmtl::Matrix44f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix44f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRotEuler44Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   */

   void testTimingMakeDirCos33();
   void testTimingMakeDirCos34();
   void testTimingMakeDirCos44();
   /*
   void testTimingMakeDirCos33Static()
   {
      gmtl::Matrix<float, 3, 3> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix33f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos33Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeDirCos34Static()
   {
      gmtl::Matrix<float, 3, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix34f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos34Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeDirCos44Static()
   {
      gmtl::Matrix44f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix44f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos44Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   */

   void testTimingMakeAxes33();
   void testTimingMakeAxes34();
   void testTimingMakeAxes44();
   /*
   void testTimingMakeAxes33Static()
   {
      gmtl::Matrix<float, 3, 3> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeAxes<gmtl::Matrix33f>( gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes33Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeAxes34Static()
   {
      gmtl::Matrix<float, 3, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeAxes<gmtl::Matrix34f>( gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes34Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeAxes44Static()
   {
      gmtl::Matrix44f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeAxes<gmtl::Matrix44f>( gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes44Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   */
         
   // is this a convert test?
   void testTimingMakeAxes()
   {
//      gmtl::Matrix44f mat1, mat2;
//      gmtl::Vec3f xAxis1,yAxis1,zAxis1;
//      gmtl::Vec3f xAxis2,yAxis2,zAxis2;

      
      
      /*
      // Simple rotation around X axis
      mat1.makeRot(90,gmtl::XUnitVec3);
      mat1.getAxes(xAxis1,yAxis1,zAxis1);
      mat2.makeAxes(xAxis1,yAxis1,zAxis1);
      mat2.getAxes(xAxis2,yAxis2,zAxis2);

      CPPUNIT_ASSERT(xAxis1.equal(xAxis2,0.01));
      CPPUNIT_ASSERT(yAxis1.equal(yAxis2,0.01));
      CPPUNIT_ASSERT(zAxis1.equal(zAxis2,0.01));

      // More complex Euler rotation
      mat1.makeXYZEuler(45.0f, -35.0f, 13.0f);
      mat1.getAxes(xAxis1,yAxis1,zAxis1);
      mat2.makeAxes(xAxis1,yAxis1,zAxis1);
      mat2.getAxes(xAxis2,yAxis2,zAxis2);

      CPPUNIT_ASSERT(xAxis1.equal(xAxis2,0.01));
      CPPUNIT_ASSERT(yAxis1.equal(yAxis2,0.01));
      CPPUNIT_ASSERT(zAxis1.equal(zAxis2,0.01));

      // Use orthonormal axis
      xAxis1.set(7, 11, 21);     xAxis1.normalize();
      yAxis1.set(12, 21, 75);    yAxis1.normalize();
      zAxis1 = xAxis1.cross(yAxis1);   zAxis1.normalize();

      mat2.makeAxes(xAxis1,yAxis1,zAxis1);
      mat2.getAxes(xAxis2,yAxis2,zAxis2);

      CPPUNIT_ASSERT(xAxis1.equal(xAxis2,0.01));
      CPPUNIT_ASSERT(yAxis1.equal(yAxis2,0.01));
      CPPUNIT_ASSERT(zAxis1.equal(zAxis2,0.01));
      */
   }
   
         
   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixGenTest");
      
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixMakeTrans", &MatrixGenTest::testMatrixMakeTrans ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixMakeAxes", &MatrixGenTest::testMatrixMakeAxes ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixMakeDirCos", &MatrixGenTest::testMatrixMakeDirCos ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixMakeRotEuler", &MatrixGenTest::testMatrixMakeRotEuler ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixMakeScale", &MatrixGenTest::testMatrixMakeScale ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testMatrixMakeRot", &MatrixGenTest::testMatrixMakeRot ) );
      
      
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeTrans", &MatrixGenTest::testTimingMakeTrans ) );
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testTimingMakeTransStatic", &MatrixGenTest::testTimingMakeTransStatic ) );
      */
            
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeScale", &MatrixGenTest::testTimingMakeScale ) );
      /* 
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeScaleStatic", &MatrixGenTest::testTimingMakeScaleStatic) );
      */
      
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRot33", &MatrixGenTest::testTimingMakeRot33 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRot34", &MatrixGenTest::testTimingMakeRot34 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRot44", &MatrixGenTest::testTimingMakeRot44 ) );
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRot33Static", &MatrixGenTest::testTimingMakeRot33Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRot34Static", &MatrixGenTest::testTimingMakeRot34Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRot44Static", &MatrixGenTest::testTimingMakeRot44Static ) );
      */
            
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingGetRot", &MatrixGenTest::testTimingGetRot ) );
      
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRotEuler33", &MatrixGenTest::testTimingMakeRotEuler33 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRotEuler34", &MatrixGenTest::testTimingMakeRotEuler34 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRotEuler44", &MatrixGenTest::testTimingMakeRotEuler44 ) );
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRotEuler33Static", &MatrixGenTest::testTimingMakeRot33Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRotEuler34Static", &MatrixGenTest::testTimingMakeRot34Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRotEuler44Static", &MatrixGenTest::testTimingMakeRot44Static ) );
      */
            
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeDirCos33", &MatrixGenTest::testTimingMakeDirCos33 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeDirCos34", &MatrixGenTest::testTimingMakeDirCos34 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeDirCos44", &MatrixGenTest::testTimingMakeDirCos44 ) );
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeDirCos33Static", &MatrixGenTest::testTimingMakeDirCos33Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeDirCos34Static", &MatrixGenTest::testTimingMakeDirCos34Static ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeDirCos44Static", &MatrixGenTest::testTimingMakeDirCos44Static ) );
      */
            
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testTimingMakeAxes33", &MatrixGenTest::testTimingMakeAxes33 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testTimingMakeAxes34", &MatrixGenTest::testTimingMakeAxes34 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testTimingMakeAxes44", &MatrixGenTest::testTimingMakeAxes44 ) );
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
