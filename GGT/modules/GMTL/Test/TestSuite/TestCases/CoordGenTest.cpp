/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: CoordGenTest.cpp,v $
 * Date modified: $Date: 2002-03-20 23:35:43 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 *********************************************************** ggt-head end */
/*************************************************************** ggt-cpr beg
*
* GGT: The Generic Graphics Toolkit
* Copyright (C) 2001,2002 Allen Bierbaum
*
* This library is free software; you can redistribute it and/or
* modify it under th MathPrimitives  [PrimName]Ops.h  Vec & Point [100%] -ab
Coord [] -km Transforcoordions XformInterface? Xform.h   Collision detection CollisionInterface? Intersection.h   Bounding volumes BoundingInterface? Containment.h   Math factories MathFactories Builder.h  e terms of the GNU Lesser General Public
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
#include "CoordGenTest.h"
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Generate.h>
#include <gmtl/MatrixOps.h>

namespace gmtlTest
{
   void CoordGenTest::testCoordMakeCoord()
   {
      gmtl::RotationOrder order = gmtl::XYZ;
      gmtl::Matrix44f mat;
      gmtl::Coord<float, 3, 3> q1;
      
      // test translation with makeCoord
      /// @todo test rotation
      mat = gmtl::makeTrans<gmtl::Matrix44f>( gmtl::Vec3f( 1.0f, 2.0f, 3.0f ) );
      q1 = gmtl::makeCoord<gmtl::Coord<float, 3, 3> >( mat, order );
      CPPUNIT_ASSERT( q1.getPos()[0] == 1.0f );
      CPPUNIT_ASSERT( q1.getPos()[1] == 2.0f );
      CPPUNIT_ASSERT( q1.getPos()[2] == 3.0f );
      
      // test translation with setCoord
      /// @todo test rotation
      mat = gmtl::makeTrans<gmtl::Matrix44f>( gmtl::Vec3f( 4.0f, 5.0f, 6.0f ) );
      gmtl::setCoord( q1, mat, order );
      CPPUNIT_ASSERT( q1.getPos()[0] == 4.0f );
      CPPUNIT_ASSERT( q1.getPos()[1] == 5.0f );
      CPPUNIT_ASSERT( q1.getPos()[2] == 6.0f );

      
      // make sure this compiles...
      ///@todo testme
      convert( q1, mat, order );
   }

   void CoordGenTest::testCoordGetMatrix()
   {
      gmtl::RotationOrder order = gmtl::XYZ;
      gmtl::Matrix44f mat;
      gmtl::Vec3f trans( 1, 2, 3 );
      gmtl::Vec3f rot( 4, 5, 6 );
      gmtl::Coord<float, 3, 3> q1( trans, rot );
    
      // test translation with makeMatrix
      /// @todo test rotation
      mat = gmtl::makeMatrix<gmtl::Matrix44f>( q1, order );
      
      // test translation 
      gmtl::Vec3f v2 = gmtl::makeTrans<gmtl::Vec3f>( mat );
      CPPUNIT_ASSERT( v2 == trans );
      
      // make sure this compiles...
      ///@todo testme
      convert( mat, q1, order );

            
      // do some of the euler tests to test out rotation...
      float eps = 0.001f;
      {
         gmtl::Matrix33f mat, expected_result33;
         expected_result33.set( 0.683013f, -0.183013f, 0.707107f,
                                0.683013f, -0.183013f, -0.707107f,
                                0.258819f, 0.965926f, 0.0f );
         q1.rot()[0] = gmtl::Math::deg2Rad( 90.0f );
         q1.rot()[1] = gmtl::Math::deg2Rad( 45.0f );
         q1.rot()[2] = gmtl::Math::deg2Rad( 15.0f );
         
         mat = gmtl::makeMatrix<gmtl::Matrix33f>( q1, gmtl::XYZ );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      
      {
         gmtl::Matrix34f mat, expected_result34;
         expected_result34.set( -0.645974f, -0.560068f, 0.518692f, gmtl::Math::deg2Rad( 1.0f ),
                                 0.287606f, -0.807979f, -0.514249f,gmtl::Math::deg2Rad( 2.0f ),
                                 0.707107f, -0.183013f, 0.683013f, gmtl::Math::deg2Rad( 3.0f ) );
         q1.pos()[0] = gmtl::Math::deg2Rad( 1.0f );
         q1.pos()[1] = gmtl::Math::deg2Rad( 2.0f );
         q1.pos()[2] = gmtl::Math::deg2Rad( 3.0f );
         q1.rot()[0] = gmtl::Math::deg2Rad( 156.0f );
         q1.rot()[1] = gmtl::Math::deg2Rad( -45.0f );
         q1.rot()[2] = gmtl::Math::deg2Rad( -15.0f );
         mat = gmtl::makeMatrix<gmtl::Matrix34f>( q1, gmtl::ZYX );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }
      
      {
         gmtl::Matrix44f mat, expected_result44;
         expected_result44.set( -0.918494f, 0.283617f, -0.275553f,gmtl::Math::deg2Rad( 1.0f ),
                                -0.395247f, -0.637014f, 0.66181f, gmtl::Math::deg2Rad( 2.0f ),
                                 0.0121696f, 0.71678f, 0.697193f, gmtl::Math::deg2Rad( 3.0f ),
                                 0,0,0,1 );
         
         q1.pos()[0] = gmtl::Math::deg2Rad( 1.0f );
         q1.pos()[1] = gmtl::Math::deg2Rad( 2.0f );
         q1.pos()[2] = gmtl::Math::deg2Rad( 3.0f );
         q1.rot()[0] = gmtl::Math::deg2Rad( -156.0f  );
         q1.rot()[1] = gmtl::Math::deg2Rad(  45.7892892f );
         q1.rot()[2] = gmtl::Math::deg2Rad( -361.0f );
         
         mat = gmtl::makeMatrix<gmtl::Matrix44f>( q1, gmtl::ZXY );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );
      }
   }


   void CoordGenTest::testGenTimingMakeCoord()
   {
      gmtl::RotationOrder order = gmtl::XYZ;
      gmtl::Matrix44f mat;
      gmtl::Coord<float, 3, 3> q1;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         q1 = gmtl::makeCoord<gmtl::Coord<float, 3, 3> >( mat, order );
         mat[3] += q1.getPos()[2];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "CoordGenTest/makeCoord<33f>(mat,XYZ)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      
      CPPUNIT_ASSERT( q1.pos()[1] != 10000.0f );
   }
   
   void CoordGenTest::testGenTimingMakeMatrix()
   {
      gmtl::RotationOrder order = gmtl::XYZ;
      gmtl::Matrix44f mat;
      gmtl::Coord<float, 3, 3> q1;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         mat = gmtl::makeMatrix<gmtl::Matrix44f>( q1, order );
         q1.pos()[2] += mat[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "CoordGenTest/makeMatrix<44f>(q1,XYZ)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( q1.pos()[1] != 10000.0f );
   }


   void CoordGenTest::testGenTimingSetCoord()
   {
      gmtl::RotationOrder order = gmtl::XYZ;
      gmtl::Matrix44f mat;
      gmtl::Coord<float, 3, 3> q1;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setCoord( q1, mat, order );
         mat[3] += q1.getPos()[2];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "CoordGenTest/setCoord(coord,mat,XYZ)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( q1.pos()[1] != 10000.0f );
   }
}
