/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: CoordGenTest.cpp,v $
 * Date modified: $Date: 2002-03-20 22:32:22 $
 * Version:       $Revision: 1.1 $
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

namespace gmtlTest
{
   void CoordGenTest::testCoordMakeRot()
   {
      gmtl::RotationOrder order = gmtl::XYZ;
      gmtl::Matrix44f mat;
      gmtl::Coord<float, 3, 3> q1;
      
      mat = gmtl::makeTrans<gmtl::Matrix44f>( gmtl::Vec3f( 1.0f, 2.0f, 3.0f ) );
      q1 = gmtl::makeCoord<gmtl::Coord<float, 3, 3> >( mat, order );
      CPPUNIT_ASSERT( q1.getPos()[0] == 1.0f );
      CPPUNIT_ASSERT( q1.getPos()[1] == 2.0f );
      CPPUNIT_ASSERT( q1.getPos()[2] == 3.0f );
      
      mat = gmtl::makeTrans<gmtl::Matrix44f>( gmtl::Vec3f( 4.0f, 5.0f, 6.0f ) );
      gmtl::setCoord( q1, mat, order );
      CPPUNIT_ASSERT( q1.getPos()[0] == 4.0f );
      CPPUNIT_ASSERT( q1.getPos()[1] == 5.0f );
      CPPUNIT_ASSERT( q1.getPos()[2] == 6.0f );
      
      /// @todo test rotation
   }

   void CoordGenTest::testCoordGetRot()
   {
      gmtl::RotationOrder order = gmtl::XYZ;
      gmtl::Matrix44f mat;
      gmtl::Coord<float, 3, 3> q1;
    
      /// @todo test me  
   }


   void CoordGenTest::testGenTimingMakeRot()
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
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "CoordGenTest/makeCoord(mat,XYZ)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      
      CPPUNIT_ASSERT( q1.pos()[1] != 10000.0f );
   }


   void CoordGenTest::testGenTimingSetRot()
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
