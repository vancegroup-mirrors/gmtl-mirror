/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixGenTest.cpp,v $
 * Date modified: $Date: 2002-03-18 21:57:53 $
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
#include "MatrixGenTest.h"
#include <cppunit/extensions/MetricRegistry.h>
#include <gmtl/MatrixOps.h>

namespace gmtlTest {

   void MatrixGenTest::testMatrixMakeTrans()
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

      // --- Test standalone makeTrans(trans) against makeTrans(mat,trans) -- //
      {
         gmtl::Matrix44f expected_mat;
         gmtl::Vec3f trans3(1.0, 2.0, 3.0f);
         gmtl::Vec4f trans4(1.0, 2.0, 3.0f);
         gmtl::makeTrans(expected_mat, trans3);
         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeTrans<gmtl::Matrix44f>(trans3),
                                        expected_mat, eps ) );
         gmtl::makeTrans(expected_mat, trans4);
         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeTrans<gmtl::Matrix44f>(trans4),
                                        expected_mat, eps ) );

      }
   }

   void MatrixGenTest::testMatrixMakeAxes()
   {
      float eps = 0.001f;
      {
         gmtl::Matrix33f mat33, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat33[x] = 9382498138.0f;
         expected_result33.set( 0, 1, 0,
                                1, 0, 0,
                                0, 0, -1  );
         gmtl::makeAxes( mat33, gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );
      }
      {
         gmtl::Matrix44f mat44, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat44[x] = 9382498138.0f;
         expected_result44.set( 0, 1, 0, 0,
                                1, 0, 0, 0,
                                0, 0, -1, 0,
                                0, 0, 0, 1  );
         gmtl::makeAxes( mat44, gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
   }

   void MatrixGenTest::testMatrixMakeDirCos()
   {
      float eps = 0.001f;
      {
         gmtl::Matrix33f mat33, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat33[x] = 9382498138.0f;
         expected_result33.set( 0, 1, 0,
                                1, 0, 0,
                                0, 0, -1  );
         gmtl::makeDirCos( mat33, gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );
      }
      {
         gmtl::Matrix44f mat44, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat44[x] = 9382498138.0f;
         expected_result44.set( 0, 1, 0, 0,
                                1, 0, 0, 0,
                                0, 0, -1, 0,
                                0, 0, 0, 1  );
         gmtl::makeDirCos( mat44, gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
   }

   void MatrixGenTest::testMatrixMakeScale()
   {
      float eps = 0.001f;
      // 2D rot/trans
      {
         gmtl::Matrix<float, 2, 3> mat23, expected_result23;
         for (int x = 0; x < 6; ++x)
            mat23[x] = 9382498138.0f;
         expected_result23.set( 32, 0, 0,
                                0, 33, 0 );
         gmtl::makeScale( mat23, gmtl::Vec2f( 32, 33 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result23, mat23, eps ) );
      }
      // 2D rot/trans/skew
      {
         gmtl::Matrix33f mat33, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat33[x] = 9382498138.0f;
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
            mat34[x] = 9382498138.0f;
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
            mat44[x] = 9382498138.0f;
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
            mat23[x] = 9382498138.0f;
         expected_result23.set( 32, 0, 0,
                                0, 32, 0 );
         gmtl::makeScale( mat23, 32.0f );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result23, mat23, eps ) );
      }
      // 2D rot/trans/skew
      {
         gmtl::Matrix33f mat33, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat33[x] = 9382498138.0f;
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
            mat34[x] = 9382498138.0f;
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
            mat44[x] = 9382498138.0f;
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

   void MatrixGenTest::testMatrixMakeRot()
   {
      float eps = 0.01f;
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138.0f;
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
            mat[x] = 9382498138.0f;
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
            mat[x] = 9382498138.0f;
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
            mat[x] = 9382498138.0f;
         expected_result34.set( 0.804738f, 0.310617f, -0.505879f, 0.0f,
                                -0.505879f, 0.804738f, -0.310617f, 0.0f,
                                0.310617f, 0.505879f, 0.804738f, 0.0f  );
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
            mat[x] = 9382498138.0f;
         expected_result44.set( 0.804738f, -0.310617f, 0.505879f, 0.0f,
                                0.505879f, 0.804738f, -0.310617f, 0.0f,
                                -0.310617f, 0.505879f, 0.804738f, 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f );
         gmtl::Vec3f vec( 1.7f, 1.7f, 1.7f );
         gmtl::normalize( vec );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 45.0f ), vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );

         // make sure that the other version works the same...
         gmtl::Matrix44f mat2;
         gmtl::makeRot( mat2, gmtl::Math::deg2Rad( 45.0f ), 1.7f, 1.7f, 1.7f );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat, eps ) );
      }

      // ---- Test standalone one ---- //
      {
         gmtl::Matrix44f mat, expected_mat;
         gmtl::Vec3f rot_axis(1.0f, 2.0f, 3.0f);
         gmtl::normalize(rot_axis);
         gmtl::makeRot(expected_mat, 1.1f, rot_axis);
         mat = gmtl::makeRot<gmtl::Matrix44f>(1.1f, rot_axis);
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeRot<gmtl::Matrix44f>(1.1f, rot_axis), expected_mat, eps ) );
      }

      {
         gmtl::Matrix34f mat, expected_mat;
         gmtl::Vec3f rot_axis(1.0f, 2.0f, 3.0f);
         gmtl::normalize(rot_axis);
         gmtl::makeRot(expected_mat, 1.1f, rot_axis);
         mat = gmtl::makeRot<gmtl::Matrix34f>(1.1f, rot_axis);
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeRot<gmtl::Matrix34f>(1.1f, rot_axis), expected_mat, eps ) );
      }
   }

   void MatrixGenTest::testMatrixMakeRotEuler()
   {
      float eps = 0.001f;
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138.0f;
         expected_result33.set( 0.683013f, -0.183013f, 0.707107f,
                                0.683013f, -0.183013f, -0.707107f,
                                0.258819f, 0.965926f, 0.0f );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 45.0f ),
                             gmtl::Math::deg2Rad( 15.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138.0f;
         expected_result33.set( 1, 0,  0,
                                0, 0, -1,
                                0, 1,  0  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138.0f;
         expected_result33.set( 0, 0, 1,
                                0, 1, 0,
                                -1, 0, 0  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138.0f;
         expected_result33.set( 0, -1, 0,
                                1, 0, 0,
                                0, 0, 1  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }

      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138.0f;
         expected_result34.set( 0.683013f, 0.183013f, -0.707107f, 0.0f,
                               -0.0413633f, -0.956855f, -0.287606f, 0.0f,
                               -0.729234f, 0.225687f, -0.645974f, 0.0f   );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 156.0f ), gmtl::Math::deg2Rad( -45.0f ), gmtl::Math::deg2Rad( -15.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138.0f;
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
            mat[x] = 9382498138.0f;
         expected_result44.set( 0.697193f, 0.0121696f, 0.71678f, 0.0f,
                               -0.275553f, -0.918494f, 0.283617f, 0.0f,
                                0.66181f, -0.395247f, -0.637014f, 0.0f,
                                0, 0, 0, 1 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( -156.0f ), gmtl::Math::deg2Rad( 45.7892892f ), gmtl::Math::deg2Rad( -361.0f ), gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );
      }


      // ZYX
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138.0f;
         expected_result33.set( 0.0f, -0.965926f, 0.258819f,
                                0.707107f, 0.183013f, 0.683013f,
                                -0.707107f, 0.183013f, 0.683013f );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 45.0f ),
                             gmtl::Math::deg2Rad( 15.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138.0f;
         expected_result33.set( 0, -1, 0,
                                1, 0, 0,
                                0, 0, 1  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138.0f;
         expected_result33.set( 0, 0, 1,
                                0, 1, 0,
                                -1, 0, 0  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138.0f;
         expected_result33.set( 1, 0, 0,
                                0, 0, -1,
                                0, 1, 0  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }

      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138.0f;
         expected_result34.set( -0.645974f, -0.560068f, 0.518692f, 0.0f,
                                 0.287606f, -0.807979f, -0.514249f, 0.0f,
                                 0.707107f, -0.183013f, 0.683013f, 0.0f  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 156.0f ), gmtl::Math::deg2Rad( -45.0f ), gmtl::Math::deg2Rad( -15.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138.0f;
         expected_result34.set( 0, 0, 1, 0,
                                0, 1, 0, 0,
                                -1, 0, 0, 0 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }

      {
         gmtl::Matrix44f mat, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat[x] = 9382498138.0f;
         expected_result44.set( -0.637014f, 0.418103f, -0.647613f, 0.0f,
                                -0.283617f, -0.908318f, -0.30744f, 0.0f,
                                -0.71678f, -0.0121696f, 0.697193f, 0.0f,
                                 0, 0, 0, 1 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( -156.0f ), gmtl::Math::deg2Rad( 45.7892892f ), gmtl::Math::deg2Rad( -361.0f ), gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );
      }


      // ZXY
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138.0f;
         expected_result33.set( -0.183013f, -0.707107f, 0.683013f,
                                 0.965926f, 0.0f,       0.258819f,
                                -0.183013f, 0.707107f,  0.683013f );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 45.0f ),
                             gmtl::Math::deg2Rad( 15.0f ), gmtl::ZXY );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat[x] = 9382498138.0f;
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
            mat[x] = 9382498138.0f;
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
            mat[x] = 9382498138.0f;
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
            mat[x] = 9382498138.0f;
         expected_result34.set( -0.956855f, -0.287606f, -0.0413633f, 0.0f,
                                 0.225687f, -0.645974f, -0.729234f,  0.0f,
                                 0.183013f, -0.707107f,  0.683013f,  0.0f  );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 156.0f ),
                             gmtl::Math::deg2Rad( -45.0f ),
                             gmtl::Math::deg2Rad( -15.0f ), gmtl::ZXY );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat[x] = 9382498138.0f;
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
            mat[x] = 9382498138.0f;
         expected_result44.set( -0.918494f, 0.283617f, -0.275553f, 0.0f,
                                -0.395247f, -0.637014f, 0.66181f, 0.0f,
                                 0.0121696f, 0.71678f, 0.697193f, 0.0f,
                                 0, 0, 0, 1 );
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( -156.0f ),
                             gmtl::Math::deg2Rad( 45.7892892f ),
                             gmtl::Math::deg2Rad( -361.0f ), gmtl::ZXY );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );
      }


      // --- Test standalone makeRot(val,val,val) against makeRot(mat,val,val,val) -- //
      {
         gmtl::Matrix44f mat, expected_mat;
         gmtl::makeRot(expected_mat, 0.1f, 2.3f, -2.1f, gmtl::XYZ);
         mat = gmtl::makeRot<gmtl::Matrix44f>(0.1f, 2.3f, -2.1f, gmtl::XYZ);
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         gmtl::makeRot(expected_mat, 0.1f, 2.3f, -2.1f, gmtl::ZXY );
         mat = gmtl::makeRot<gmtl::Matrix44f>(0.1f, 2.3f, -2.1f, gmtl::ZXY);
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         gmtl::makeRot(expected_mat, 0.1f, 2.3f, -2.1f, gmtl::ZYX);
         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeRot<gmtl::Matrix44f>(0.1f, 2.3f, -2.1f, gmtl::ZYX),
                                        expected_mat, eps ) );
      }

      {
         gmtl::Matrix33f mat, expected_mat;
         gmtl::makeRot(expected_mat, 0.1f, 2.3f, -2.1f, gmtl::XYZ);
         mat = gmtl::makeRot<gmtl::Matrix33f>(0.1f, 2.3f, -2.1f, gmtl::XYZ);
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         gmtl::makeRot(expected_mat, 0.1f, 2.3f, -2.1f, gmtl::ZXY );
         mat = gmtl::makeRot<gmtl::Matrix33f>(0.1f, 2.3f, -2.1f, gmtl::ZXY);
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         gmtl::makeRot(expected_mat, 0.1f, 2.3f, -2.1f, gmtl::ZYX);
         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeRot<gmtl::Matrix33f>(0.1f, 2.3f, -2.1f, gmtl::ZYX),
                                        expected_mat, eps ) );
      }

      {
         gmtl::Matrix34f mat, expected_mat;
         gmtl::makeRot(expected_mat, 0.1f, 2.3f, -2.1f, gmtl::XYZ);
         mat = gmtl::makeRot<gmtl::Matrix34f>(0.1f, 2.3f, -2.1f, gmtl::XYZ);
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         gmtl::makeRot(expected_mat, 0.1f, 2.3f, -2.1f, gmtl::ZXY );
         mat = gmtl::makeRot<gmtl::Matrix34f>(0.1f, 2.3f, -2.1f, gmtl::ZXY);
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         gmtl::makeRot(expected_mat, 0.1f, 2.3f, -2.1f, gmtl::ZYX);
         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeRot<gmtl::Matrix34f>(0.1f, 2.3f, -2.1f, gmtl::ZYX),
                                        expected_mat, eps ) );
      }
   }

   void MatrixGenTest::testTimingMakeTrans()
   {
      gmtl::Matrix33f mat33;
      gmtl::Matrix34f mat34;
      gmtl::Matrix44f mat44;
      float a = 1.0f;

      const long iters(25000);

      // 2D translation
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeTrans( mat33, gmtl::Vec2f( a, 2 ) );
         a += mat33[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeTrans(mat33f,vec2f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat33[3] != 1234.0456f && a != 987654.321f  );


      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeTrans( mat33, gmtl::Vec3f( 1, a, 1.0f ) ); // homogeneous
         a += mat33[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeTrans(mat33f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat33[3] != 1234.0456f && a != 987654.321f  );


      // 3D translation
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeTrans( mat34, gmtl::Vec3f( a, 32, 121 ) );
         a += mat34[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeTrans(mat34f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat34[3] != 1234.0456f && a != 987654.321f  );


      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeTrans( mat44, gmtl::Vec3f( 30, a, 121 ) );
         a += mat44[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeTrans(mat44f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat44[3] != 1234.0456f && a != 987654.321f  );


      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeTrans( mat44, gmtl::Vec4f( 30, 32, a, 1.0f ) ); // homogeneous
         a += mat44[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeTrans(mat44f,vec4f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat44[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenTest::testTimingMakeScale()
   {
      float a = 2.1f;
      gmtl::Matrix33f mat33;
      gmtl::Matrix34f mat34;
      gmtl::Matrix44f mat44;
      gmtl::Matrix<float, 4, 3> mat43;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeScale( mat33, gmtl::Vec2f( a, 2 ) );
         a += mat33[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeScale(mat33f,vec2f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat33[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeScale( mat34, gmtl::Vec3f( 30, 32, a ) );
         a += mat34[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeScale(mat34f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat34[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeScale( mat43, gmtl::Vec3f( 30, 32, a ) );
         a += mat43[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeScale(mat43f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat43[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeScale( mat44, gmtl::Vec3f( 30, 32, a ) );
         a += mat44[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeScale(mat44f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat44[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeScale( mat33, a );
         a += mat33[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeScale(mat33f,f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat33[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeScale( mat34, a );
         a += mat34[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeScale(mat34f,f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat34[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeScale( mat43, a );
         a += mat43[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeScale(mat43f,f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat43[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeScale( mat44, a );
         a += mat44[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeScale(mat44f,f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat44[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenTest::testTimingMakeRot33()
   {
      gmtl::Matrix33f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( a ), gmtl::Vec3f( 1.0f, 0.0f, 0.0f ) );
         a += mat[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeRot33f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenTest::testTimingMakeRot34()
   {
      gmtl::Matrix34f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( a ), gmtl::Vec3f( 1.0f, 0.0f, 0.0f ) );
         a += mat[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeRot34f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenTest::testTimingMakeRot44()
   {
      gmtl::Matrix44f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( a ), gmtl::Vec3f( 1.0f, 0.0f, 0.0f ) );
         a += mat[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeRot44f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenTest::testTimingMakeRotEuler33()
   {
      gmtl::Matrix33f mat;
      float a = 0;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, a, 45.0f, 35.0f, gmtl::ZXY );
         a -= mat[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeRotEuler(mat33f,ZXY)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, a, 45.0f, 35.0f, gmtl::ZYX );
         a += mat[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeRotEuler(mat33f,ZYX)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, a, 45.0f, 35.0f, gmtl::XYZ );
         a -= mat[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeRotEuler(mat33f,XYZ)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenTest::testTimingMakeRotEuler34()
   {
      gmtl::Matrix34f mat;
      float a = 0;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, a, 45.0f, 35.0f, gmtl::ZXY );
         a -= mat[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeRotEuler(mat34f,ZXY)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, a, 45.0f, 35.0f, gmtl::ZYX );
         a += mat[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeRotEuler(mat34f,ZYX)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, a, 45.0f, 35.0f, gmtl::XYZ );
         a -= mat[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeRotEuler(mat34f,XYZ)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenTest::testTimingMakeRotEuler44()
   {
      gmtl::Matrix44f mat;
      float a = 0;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, a, 45.0f, 35.0f, gmtl::ZXY );
         a -= mat[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeRotEuler(mat44f,ZXY)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, a, 45.0f, 35.0f, gmtl::ZYX );
         a += mat[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeRotEuler(mat44f,ZYX)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeRot( mat, a, 45.0f, 35.0f, gmtl::XYZ );
         a -= mat[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeRotEuler(mat44f,XYZ)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenTest::testTimingMakeDirCos33()
   {
      gmtl::Matrix33f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeDirCos( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( a,1,0 ), gmtl::Vec3f( 0,0,1 ) );
         a += mat[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeDirCos33f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenTest::testTimingMakeDirCos34()
   {
      gmtl::Matrix34f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeDirCos( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( a,1,0 ), gmtl::Vec3f( 0,0,1 ) );
         a += mat[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeDirCos34f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenTest::testTimingMakeDirCos44()
   {
      gmtl::Matrix44f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeDirCos( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( a,1,0 ), gmtl::Vec3f( 0,0,1 ) );
         a += mat[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeDirCos44f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f );
   }

   void MatrixGenTest::testTimingMakeAxes33()
   {
      gmtl::Matrix33f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeAxes( mat, gmtl::Vec3f( 1,a,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
         a += mat[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeAxes33f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f );
   }

   void MatrixGenTest::testTimingMakeAxes34()
   {
      gmtl::Matrix34f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeAxes( mat, gmtl::Vec3f( 1,a,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
         a += mat[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeAxes34f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f );
   }

   void MatrixGenTest::testTimingMakeAxes44()
   {
      gmtl::Matrix44f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeAxes( mat, gmtl::Vec3f( 1,a,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
         a += mat[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/makeAxes44f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat[3] != 1234.0456f && a != 987654.321f );
   }
}
