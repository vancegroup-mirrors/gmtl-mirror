/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixGenTest.h,v $
 * Date modified: $Date: 2002-02-19 22:35:15 $
 * Version:       $Revision: 1.5 $
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

   void testMatrixMakeTrans()
   {
      gmtl::Matrix33f mat33;
      gmtl::Matrix34f mat34;
      gmtl::Matrix44f mat44;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // 2D translation
         gmtl::makeTrans( mat33, gmtl::Vec2f( 1, 2 ) );
         gmtl::makeTrans( mat33, gmtl::Vec2f( 1, 2, 1.0f ) ); // homogeneous
         
         // 3D translation
         gmtl::makeTrans( mat34, gmtl::Vec3f( 30, 32, 121 ) );
         gmtl::makeTrans( mat44, gmtl::Vec3f( 30, 32, 121 ) );
         gmtl::makeTrans( mat44, gmtl::Vec4f( 30, 32, 121, 1.0f ) ); // homogeneous
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeTrans", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   /*
   void testMatrixMakeTransStatic()
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
   
   void testMatrixMakeScale()
   {
      gmtl::Matrix33f mat33;
      gmtl::Matrix34f mat34;
      gmtl::Matrix44f mat44;
      gmtl::Matrix<float, 4, 3> mat43;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeScale( mat33, gmtl::Vec2f( 1, 2 ) );
         gmtl::makeScale( mat34, gmtl::Vec3f( 30, 32, 121 ) );
         gmtl::makeScale( mat43, gmtl::Vec3f( 30, 32, 121 ) );
         gmtl::makeScale( mat44, gmtl::Vec3f( 30, 32, 121 ) );
         gmtl::makeScale( mat33, 2.0f );
         gmtl::makeScale( mat34, 3.0f );
         gmtl::makeScale( mat43, 4.0f );
         gmtl::makeScale( mat44, 5.0f );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeScale", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   /*
   void testMatrixMakeScaleStatic()
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
         
   void testMatrixMakeRot33()
   {
      gmtl::Matrix33f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeRot( mat, 90.0f, 1.0f, 0.0f, 0.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot33", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeRot34()
   {
      gmtl::Matrix34f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeRot( mat, 90.0f, 1.0f, 0.0f, 0.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot34", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeRot44()
   {
      gmtl::Matrix44f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeRot( mat, 90.0f, 1.0f, 0.0f, 0.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot44", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   /*
   void testMatrixMakeRot33Static()
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
   
   void testMatrixMakeRot34Static()
   {
      gmtl::Matrix<float, 3, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix34f>( 90.0f, 1.0f, 0.0f, 0.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot34Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeRot44Static()
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
   
   // makeRot Euler tests...
   
   void testMatrixMakeRotEuler33()
   {
      gmtl::Matrix33f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, 90.0f, 45.0f, 35.0f, gmtl::XYZ );
         gmtl::makeRot( mat, 90.0f, 45.0f, 35.0f, gmtl::ZYX );
         gmtl::makeRot( mat, 90.0f, 45.0f, 35.0f, gmtl::ZXY );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRotEuler33", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeRotEuler34()
   {
      gmtl::Matrix34f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, 90.0f, 45.0f, 35.0f, gmtl::XYZ );
         gmtl::makeRot( mat, 90.0f, 45.0f, 35.0f, gmtl::ZYX );
         gmtl::makeRot( mat, 90.0f, 45.0f, 35.0f, gmtl::ZXY );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRotEuler34", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeRotEuler44()
   {
      gmtl::Matrix44f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, 90.0f, 45.0f, 35.0f, gmtl::XYZ );
         gmtl::makeRot( mat, 90.0f, 45.0f, 35.0f, gmtl::ZYX );
         gmtl::makeRot( mat, 90.0f, 45.0f, 35.0f, gmtl::ZXY );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRotEuler44", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   /*
   void testMatrixMakeRotEuler33Static()
   {
      gmtl::Matrix<float, 3, 3> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix33f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRotEuler33Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeRotEuler34Static()
   {
      gmtl::Matrix<float, 3, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix34f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRotEuler34Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeRotEuler44Static()
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
         
   void testMatrixMakeDirCos33()
   {
      gmtl::Matrix33f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeDirCos( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos33", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeDirCos34()
   {
      gmtl::Matrix34f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeDirCos( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos34", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeDirCos44()
   {
      gmtl::Matrix44f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeDirCos( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos44", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   /*
   void testMatrixMakeDirCos33Static()
   {
      gmtl::Matrix<float, 3, 3> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix33f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos33Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeDirCos34Static()
   {
      gmtl::Matrix<float, 3, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix34f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos34Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeDirCos44Static()
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
         
   void testMatrixMakeAxes33()
   {
      gmtl::Matrix33f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeAxes( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes33", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeAxes34()
   {
      gmtl::Matrix34f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeAxes( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes34", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeAxes44()
   {
      gmtl::Matrix44f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeAxes( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes44", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   /*
   void testMatrixMakeAxes33Static()
   {
      gmtl::Matrix<float, 3, 3> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeAxes<gmtl::Matrix33f>( gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes33Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeAxes34Static()
   {
      gmtl::Matrix<float, 3, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeAxes<gmtl::Matrix34f>( gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes34Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testMatrixMakeAxes44Static()
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
   void testMatrixMakeAxes()
   {
      gmtl::Matrix44f mat1, mat2;
      gmtl::Vec3f xAxis1,yAxis1,zAxis1;
      gmtl::Vec3f xAxis2,yAxis2,zAxis2;

      
      
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
   
         
   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixGenTest");
      
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeTrans", &MatrixGenTest::testMatrixMakeTrans));
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeTransStatic", &MatrixGenTest::testMatrixMakeTransStatic));
      */
            
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeScale", &MatrixGenTest::testMatrixMakeScale));
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeScaleStatic", &MatrixGenTest::testMatrixMakeScaleStatic));
      */
      
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot33", &MatrixGenTest::testMatrixMakeRot33));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot34", &MatrixGenTest::testMatrixMakeRot34));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot44", &MatrixGenTest::testMatrixMakeRot44));
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot33Static", &MatrixGenTest::testMatrixMakeRot33Static));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot34Static", &MatrixGenTest::testMatrixMakeRot34Static));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRot44Static", &MatrixGenTest::testMatrixMakeRot44Static));
      */
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRotEuler33", &MatrixGenTest::testMatrixMakeRot33));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRotEuler34", &MatrixGenTest::testMatrixMakeRot34));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRotEuler44", &MatrixGenTest::testMatrixMakeRot44));
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRotEuler33Static", &MatrixGenTest::testMatrixMakeRot33Static));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRotEuler34Static", &MatrixGenTest::testMatrixMakeRot34Static));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeRotEuler44Static", &MatrixGenTest::testMatrixMakeRot44Static));
      */
            
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeDirCos33", &MatrixGenTest::testMatrixMakeDirCos33));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeDirCos34", &MatrixGenTest::testMatrixMakeDirCos34));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeDirCos44", &MatrixGenTest::testMatrixMakeDirCos44));
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeDirCos33Static", &MatrixGenTest::testMatrixMakeDirCos33Static));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeDirCos34Static", &MatrixGenTest::testMatrixMakeDirCos34Static));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeDirCos44Static", &MatrixGenTest::testMatrixMakeDirCos44Static));
      */
            
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeAxes33", &MatrixGenTest::testMatrixMakeAxes33));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeAxes34", &MatrixGenTest::testMatrixMakeAxes34));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeAxes44", &MatrixGenTest::testMatrixMakeAxes44));
      /*
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeAxes33Static", &MatrixGenTest::testMatrixMakeAxes33Static));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeAxes34Static", &MatrixGenTest::testMatrixMakeAxes34Static));
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>("testMatrixMakeAxes44Static", &MatrixGenTest::testMatrixMakeAxes44Static));
      */
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
