/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixGenTest.h,v $
 * Date modified: $Date: 2002-03-08 22:46:30 $
 * Version:       $Revision: 1.12 $
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

   void testMatrixMakeTrans()
   {
      float eps = 0.001f;
      // 2D rot/trans
      { 
         gmtl::Matrix<float, 2, 3> mat23, expected_result23;
         expected_result23.set( 1, 0, 32,
                                0, 1, 33 );
         gmtl::makeTrans( mat23, gmtl::Vec2f( 32, 33 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result23, mat23, eps ) );
      }
      // 2D rot/trans/skew
      { 
         gmtl::Matrix33f mat33, expected_result33;
         expected_result33.set( 1, 0, 32,
                                0, 1, 33,
                                0, 0, 1 );
         gmtl::makeTrans( mat33, gmtl::Vec2f( 32, 33 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );
      }
      // 2D rot/trans/skew set by homogeneous vector
      { 
         gmtl::Matrix33f mat33, expected_result33;
         expected_result33.set( 1, 0, 64,
                                0, 1, 66,
                                0, 0, 1 );
         gmtl::makeTrans( mat33, gmtl::Vec3f( 32, 33, 0.5f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );
      }
      // 3D rot/trans
      { 
         gmtl::Matrix34f mat34, expected_result34;
         expected_result34.set( 1, 0, 0, 32,
                                0, 1, 0, 33,
                                0, 0, 1, 34 );
         gmtl::makeTrans( mat34, gmtl::Vec3f( 32, 33, 34 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat34, eps ) );
      }
      // 3D rot/trans set by homogeneous vector
      { 
         gmtl::Matrix34f mat34, expected_result34;
         expected_result34.set( 1, 0, 0, 64,
                                0, 1, 0, 66,
                                0, 0, 1, 68 );
         gmtl::makeTrans( mat34, gmtl::Vec4f( 32, 33, 34, 0.5f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat34, eps ) );
      }
      // 3D rot/trans/skew
      { 
         gmtl::Matrix44f mat44, expected_result44;
         expected_result44.set( 1, 0, 0, 32,
                                0, 1, 0, 33, 
                                0, 0, 1, 34,
                                0, 0, 0, 1  );
         gmtl::makeTrans( mat44, gmtl::Vec3f( 32, 33, 34 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
      // 3D rot/trans/skew set by homogeneous vector...
      { 
         gmtl::Matrix44f mat44, expected_result44;
         expected_result44.set( 1, 0, 0, 64,
                                0, 1, 0, 66,
                                0, 0, 1, 68,
                                0, 0, 0, 1  );
         gmtl::makeTrans( mat44, gmtl::Vec4f( 32, 33, 34, 0.5f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
   }
   
   void testMatrixMakeAxes()
   {
      float eps = 0.001f;
      {
         gmtl::Matrix33f mat33, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat33[x] = 9382498138;
         expected_result33.set( 0, 1, 0,
                                1, 0, 0,
                                0, 0, -1  );
         gmtl::makeAxes( mat33, gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) ); 
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );
      }
      {
         gmtl::Matrix44f mat44, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat44[x] = 9382498138;
         expected_result44.set( 0, 1, 0, 0,
                                1, 0, 0, 0,
                                0, 0, -1, 0,
                                0, 0, 0, 1  );
         gmtl::makeAxes( mat44, gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) ); 
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
   }
   
   void testMatrixMakeDirCos()
   {
      float eps = 0.001f;
      {
         gmtl::Matrix33f mat33, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat33[x] = 9382498138;
         expected_result33.set( 0, 1, 0,
                                1, 0, 0,
                                0, 0, -1  );
         gmtl::makeDirCos( mat33, gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) ); 
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );
      }
      {
         gmtl::Matrix44f mat44, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat44[x] = 9382498138;
         expected_result44.set( 0, 1, 0, 0,
                                1, 0, 0, 0,
                                0, 0, -1, 0,
                                0, 0, 0, 1  );
         gmtl::makeDirCos( mat44, gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) ); 
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
   }
   
   
   void testMatrixMakeScale()
   {
      float eps = 0.001f;
      // 2D rot/trans
      { 
         gmtl::Matrix<float, 2, 3> mat23, expected_result23;
         for (int x = 0; x < 6; ++x)
            mat23[x] = 9382498138;
         expected_result23.set( 32, 0, 0,
                                0, 33, 0 );
         gmtl::makeScale( mat23, gmtl::Vec2f( 32, 33 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result23, mat23, eps ) );
      }
      // 2D rot/trans/skew
      { 
         gmtl::Matrix33f mat33, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat33[x] = 9382498138;
         expected_result33.set( 32, 0, 0,
                                0, 33, 0,
                                0, 0, 1 );
         gmtl::makeScale( mat33, gmtl::Vec2f( 32, 33 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );
      }
      // 3D rot/trans
      { 
         gmtl::Matrix34f mat34, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat34[x] = 9382498138;
         expected_result34.set( 32, 0, 0, 0,
                                0, 33, 0, 0,
                                0, 0, 34, 0 );
         gmtl::makeScale( mat34, gmtl::Vec3f( 32, 33, 34 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat34, eps ) );
      }
      // 3D rot/trans/skew
      { 
         gmtl::Matrix44f mat44, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat44[x] = 9382498138;
         expected_result44.set( 32, 0, 0, 0,
                                0, 33, 0, 0,
                                0, 0, 34, 0,
                                0, 0, 0, 1  );
         gmtl::makeScale( mat44, gmtl::Vec3f( 32, 33, 34 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
      
      
      
      // 2D rot/trans
      { 
         gmtl::Matrix<float, 2, 3> mat23, expected_result23;
         for (int x = 0; x < 6; ++x)
            mat23[x] = 9382498138;
         expected_result23.set( 32, 0, 0,
                                0, 32, 0 );
         gmtl::makeScale( mat23, 32.0f );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result23, mat23, eps ) );
      }
      // 2D rot/trans/skew
      { 
         gmtl::Matrix33f mat33, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat33[x] = 9382498138;
         expected_result33.set( 32, 0, 0,
                                0, 32, 0,
                                0, 0, 1 );
         gmtl::makeScale( mat33, 32.0f );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );
      }
      // 3D rot/trans
      { 
         gmtl::Matrix34f mat34, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat34[x] = 9382498138;
         expected_result34.set( 32, 0, 0, 0,
                                0, 32, 0, 0,
                                0, 0, 32, 0 );
         gmtl::makeScale( mat34, 32.0f );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat34, eps ) );
      }
      // 3D rot/trans/skew
      { 
         gmtl::Matrix44f mat44, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat44[x] = 9382498138;
         expected_result44.set( 32, 0, 0, 0,
                                0, 32, 0, 0,
                                0, 0, 32, 0,
                                0, 0, 0, 1  );
         gmtl::makeScale( mat44, 32.0f );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
      { 
         // make sure this compiles, and runs without internal assert.
         gmtl::Matrix<float, 4, 8> mat48;
         gmtl::makeScale( mat48, 32.0f );
         
         gmtl::Matrix<float, 8, 4> mat84;
         gmtl::makeScale( mat84, 32.0f );
      }
   }
   
   void testMatrixMakeRot()
   {
      float eps = 0.01f;
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( 1, 0, 0,
                                0, 0, -1,
                                0, 1, 0 );
         gmtl::Vec3f vec( 1.0f, 0.0f, 0.0f );
         gmtl::normalize( vec );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ), vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
         
         // make sure that the other version works the same...
         gmtl::Matrix33f mat2;
         gmtl::makeRot( mat2, gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( 1, 0, 0,
                                0, 1, 0,
                                0, 0, 1 );
         gmtl::Vec3f vec( -1.0f, 1.0f, -1.0f );
         gmtl::normalize( vec );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( -360.0f ), vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
         
         // make sure that the other version works the same...
         gmtl::Matrix33f mat2;
         gmtl::makeRot( mat2, gmtl::Math::deg2Rad( -360.0f ), -1.0f, 1.0f, -1.0f );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat, eps ) );
      }
      
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138;
         expected_result34.set( 1, 0, 0, 0,
                                0, 0, 1, 0,
                                0, -1, 0, 0 );
         gmtl::Vec3f vec( 1.0f, 0.0f, 0.0f );
         gmtl::normalize( vec );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( -90.0f ), vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
         
         // make sure that the other version works the same...
         gmtl::Matrix34f mat2;
         gmtl::makeRot( mat2, gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat, eps ) );
      }
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138;
         expected_result34.set( 0.804738, 0.310617, -0.505879, 0, 
                                -0.505879, 0.804738, -0.310617, 0, 
                                0.310617, 0.505879, 0.804738, 0  );
         gmtl::Vec3f vec( 0.7f, -0.7f, -0.7f );
         gmtl::normalize( vec );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 45.0f ), vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
         
         // make sure that the other version works the same...
         gmtl::Matrix34f mat2;
         gmtl::makeRot( mat2, gmtl::Math::deg2Rad( 45.0f ), 0.7f, -0.7f, -0.7f );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat, eps ) );
      }
      // test that unnormalized vec works...
      {
         gmtl::Matrix44f mat, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat[x] = 9382498138;
         expected_result44.set( 0.804738, -0.310617, 0.505879, 0,
                                0.505879, 0.804738, -0.310617, 0,
                                -0.310617, 0.505879, 0.804738, 0,
                                0, 0, 0, 1 );
         gmtl::Vec3f vec( 1.7f, 1.7f, 1.7f );
         gmtl::normalize( vec );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 45.0f ), vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );
         
         // make sure that the other version works the same...
         gmtl::Matrix44f mat2;
         gmtl::makeRot( mat2, gmtl::Math::deg2Rad( 45.0f ), 1.7f, 1.7f, 1.7f );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat, eps ) );
      }
   }
   
   void testMatrixMakeRotEuler()
   {
      float eps = 0.001f;
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( 0.683013, -0.183013, 0.707107, 
                                0.683013, -0.183013, -0.707107, 
                                0.258819, 0.965926, 0 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ), 
                             gmtl::Math::deg2Rad( 45.0f ), 
                             gmtl::Math::deg2Rad( 15.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( 1, 0,  0,
                                0, 0, -1, 
                                0, 1,  0  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( 0, 0, 1,
                                0, 1, 0, 
                                -1, 0, 0  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( 0, -1, 0,
                                1, 0, 0, 
                                0, 0, 1  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138;
         expected_result34.set( 0.683013, 0.183013, -0.707107, 0, 
                               -0.0413633, -0.956855, -0.287606, 0, 
                               -0.729234, 0.225687, -0.645974, 0   );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 156.0f ), gmtl::Math::deg2Rad( -45.0f ), gmtl::Math::deg2Rad( -15.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138;
         expected_result34.set( 0, 0, 1, 0,
                                0, 1, 0, 0,
                                -1, 0, 0, 0 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), 
                             gmtl::Math::deg2Rad( 90.0f ), 
                             gmtl::Math::deg2Rad( 0.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }

      {
         gmtl::Matrix44f mat, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat[x] = 9382498138;
         expected_result44.set( 0.697193, 0.0121696, 0.71678, 0,
                               -0.275553, -0.918494, 0.283617, 0,
                                0.66181, -0.395247, -0.637014, 0,
                                0, 0, 0, 1 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( -156.0f ), gmtl::Math::deg2Rad( 45.7892892f ), gmtl::Math::deg2Rad( -361.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );
      }
      
      
      // ZYX
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( 0, -0.965926, 0.258819, 
                                0.707107, 0.183013, 0.683013,
                                -0.707107, 0.183013, 0.683013 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ), 
                             gmtl::Math::deg2Rad( 45.0f ), 
                             gmtl::Math::deg2Rad( 15.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( 0, -1, 0,
                                1, 0, 0, 
                                0, 0, 1  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( 0, 0, 1,
                                0, 1, 0, 
                                -1, 0, 0  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( 1, 0, 0,
                                0, 0, -1, 
                                0, 1, 0  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138;
         expected_result34.set( -0.645974, -0.560068, 0.518692, 0, 
                                 0.287606, -0.807979, -0.514249, 0, 
                                 0.707107, -0.183013, 0.683013, 0  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 156.0f ), gmtl::Math::deg2Rad( -45.0f ), gmtl::Math::deg2Rad( -15.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138;
         expected_result34.set( 0, 0, 1, 0,
                                0, 1, 0, 0,
                                -1, 0, 0, 0 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }

      {
         gmtl::Matrix44f mat, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat[x] = 9382498138;
         expected_result44.set( -0.637014, 0.418103, -0.647613, 0,
                                -0.283617, -0.908318, -0.30744, 0,
                                -0.71678, -0.0121696, 0.697193, 0,
                                 0, 0, 0, 1 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( -156.0f ), gmtl::Math::deg2Rad( 45.7892892f ), gmtl::Math::deg2Rad( -361.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );
      }
      
      
      // ZXY
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( -0.183013, -0.707107, 0.683013,
                                 0.965926, 0,         0.258819,
                                -0.183013, 0.707107,  0.683013 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ), 
                             gmtl::Math::deg2Rad( 45.0f ), 
                             gmtl::Math::deg2Rad( 15.0f ), gmtl::ZXY );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( 0, -1, 0,
                                1, 0, 0, 
                                0, 0, 1  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ), 
                             gmtl::Math::deg2Rad( 0.0f ), 
                             gmtl::Math::deg2Rad( 0.0f ), gmtl::ZXY );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set( 1, 0,  0,
                                0, 0, -1, 
                                0, 1,  0  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), 
                             gmtl::Math::deg2Rad( 90.0f ), 
                             gmtl::Math::deg2Rad( 0.0f ), gmtl::ZXY );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138;
         expected_result33.set(  0, 0, 1,
                                 0, 1, 0, 
                                -1, 0, 0  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), 
                             gmtl::Math::deg2Rad( 0.0f ), 
                             gmtl::Math::deg2Rad( 90.0f ), gmtl::ZXY );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138;
         expected_result34.set( -0.956855, -0.287606, -0.0413633, 0, 
                                 0.225687, -0.645974, -0.729234,  0, 
                                 0.183013, -0.707107,  0.683013,  0  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 156.0f ), 
                             gmtl::Math::deg2Rad( -45.0f ), 
                             gmtl::Math::deg2Rad( -15.0f ), gmtl::ZXY );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138;
         expected_result34.set( 1, 0,  0, 0,
                                0, 0, -1, 0,
                                0, 1,  0, 0 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), 
                             gmtl::Math::deg2Rad( 90.0f ), 
                             gmtl::Math::deg2Rad( 0.0f ), gmtl::ZXY );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }

      {
         gmtl::Matrix44f mat, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat[x] = 9382498138;
         expected_result44.set( -0.918494, 0.283617, -0.275553, 0, 
                                -0.395247, -0.637014, 0.66181, 0, 
                                 0.0121696, 0.71678, 0.697193, 0, 
                                 0, 0, 0, 1 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( -156.0f ), 
                             gmtl::Math::deg2Rad( 45.7892892f ), 
                             gmtl::Math::deg2Rad( -361.0f ), gmtl::ZXY );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );
      }
   }
         
   void testTimingMakeTrans()
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
         gmtl::makeTrans( mat33, gmtl::Vec3f( 1, 2, 1.0f ) ); // homogeneous
         
         // 3D translation
         gmtl::makeTrans( mat34, gmtl::Vec3f( 30, 32, 121 ) );
         gmtl::makeTrans( mat44, gmtl::Vec3f( 30, 32, 121 ) );
         gmtl::makeTrans( mat44, gmtl::Vec4f( 30, 32, 121, 1.0f ) ); // homogeneous
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeTrans", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
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
   
   void testTimingMakeScale()
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
         
   void testTimingMakeRot33()
   {
      gmtl::Matrix33f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ), gmtl::Vec3f( 1.0f, 0.0f, 0.0f ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot33", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeRot34()
   {
      gmtl::Matrix34f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ), gmtl::Vec3f( 1.0f, 0.0f, 0.0f ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot34", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeRot44()
   {
      gmtl::Matrix44f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ), gmtl::Vec3f( 1.0f, 0.0f, 0.0f )  );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot44", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
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
   
   // makeRot Euler tests...
   
   void testTimingMakeRotEuler33()
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
   
   void testTimingMakeRotEuler34()
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
   
   void testTimingMakeRotEuler44()
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
         
   void testTimingMakeDirCos33()
   {
      gmtl::Matrix33f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeDirCos( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos33", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeDirCos34()
   {
      gmtl::Matrix34f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeDirCos( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos34", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeDirCos44()
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
         
   void testTimingMakeAxes33()
   {
      gmtl::Matrix33f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeAxes( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes33", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeAxes34()
   {
      gmtl::Matrix34f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         gmtl::makeAxes( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes34", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   
   void testTimingMakeAxes44()
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
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRotEuler33", &MatrixGenTest::testTimingMakeRot33 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRotEuler34", &MatrixGenTest::testTimingMakeRot34 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixGenTest>( "testTimingMakeRotEuler44", &MatrixGenTest::testTimingMakeRot44 ) );
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
