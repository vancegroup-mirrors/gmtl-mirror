/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: SphereTest.h,v $
 * Date modified: $Date: 2002-02-18 21:42:52 $
 * Version:       $Revision: 1.5 $
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
#include <gmtl/gmtlConfig.h>
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Sphere.h>
#include <gmtl/Compare.h>
#include <gmtl/Containment.h>
#include <gmtl/Math.h>

namespace gmtlTest
{

class SphereTest : public CppUnit::TestCase
{
public:
   SphereTest( std::string name = "SphereTest" )
   : TestCase (name)
   {}

   virtual ~SphereTest()
   {}

   virtual void setUp()
   {}

   virtual void tearDown()
   {
   }

   void testCreation()
   {
      gmtl::Sphere<float> test_sph;

      CPPUNIT_ASSERT( test_sph.mCenter[0] == 0.0f );
      CPPUNIT_ASSERT( test_sph.mCenter[1] == 0.0f );
      CPPUNIT_ASSERT( test_sph.mCenter[2] == 0.0f );
      CPPUNIT_ASSERT( test_sph.mRadius == 0.0f );

      // Test overhead of creation
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Sphere<float> test_sph2;
         test_sph2.mRadius = 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/SphereCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testCopyConstruct()
   {
      gmtl::Sphere<float> test_sph;

      test_sph.mCenter[0] = 2.0f;
      test_sph.mCenter[1] = 4.0f;
      test_sph.mCenter[2] = 8.0f;
      test_sph.mRadius = 25.0f;

      gmtl::Sphere<float> test_sph_copy(test_sph);

      CPPUNIT_ASSERT( test_sph_copy.mCenter[0] == 2.0f);
      CPPUNIT_ASSERT( test_sph_copy.mCenter[1] == 4.0f);
      CPPUNIT_ASSERT( test_sph_copy.mCenter[2] == 8.0f);
      CPPUNIT_ASSERT( test_sph_copy.mRadius == 25.0f);

      // Test copy construction overhead
      const long iters(400000);
      gmtl::Sphere<float> test_sph2;
      test_sph2.mCenter[0] = 2.0f;
      float use_value;     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Sphere<float> test_sph2_copy(test_sph2);
         use_value += test_sph2_copy.mCenter[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/CopyConstructOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testConstructors()
   {
      gmtl::Sphere<float> test_sph( gmtl::Point<float, 3>(1.0f, 2.0f, 3.0f), 25.0f );
      CPPUNIT_ASSERT( test_sph.mCenter[0] == 1.0f);
      CPPUNIT_ASSERT( test_sph.mCenter[1] == 2.0f);
      CPPUNIT_ASSERT( test_sph.mCenter[2] == 3.0f);
      CPPUNIT_ASSERT( test_sph.mRadius == 25.0f);

      // Test constructor
      const long iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Sphere<float> test_sph2( gmtl::Point<float, 3>(1.0f, 2.0f, 3.0f), 25.0f );

         use_value = use_value + test_sph.mCenter[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/ConstructorsOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   // -- Test accessors --//
   void testGetCenter()
   {
      gmtl::Point<float, 3> center( 1.0f, 2.0f, 3.0f );
      gmtl::Sphere<float> test_sph( center, 25.0f );
      CPPUNIT_ASSERT( test_sph.getCenter() == center );

      // Test getCenter overhead
      const long iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the compiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         center = test_sph.getCenter();
         use_value = use_value + center[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/GetCenterOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testGetRadius()
   {
      float radius = 25.0f;
      gmtl::Sphere<float> test_sph( gmtl::Point<float, 3>( 1.0f, 2.0f, 3.0f ), radius );
      CPPUNIT_ASSERT( test_sph.getRadius() == radius );

      // Test getCenter overhead
      const long iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the compiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         radius = test_sph.getRadius();
         use_value = use_value + radius;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/GetRadiusOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   // -- Test setters --//
   void testSetCenter()
   {
      gmtl::Sphere<float> test_sph( gmtl::Point<float, 3>( 1.0f, 2.0f, 3.0f ), 25.0f );
      gmtl::Point<float, 3> center( 2.0f, 4.0f, 1.0f );
      test_sph.setCenter( center );
      CPPUNIT_ASSERT( test_sph.getCenter() == center );

      // Test getCenter overhead
      const long iters(400000);

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         center.set( iter, iter, iter );
         test_sph.setCenter( center );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/SetCenterOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testSetRadius()
   {
      gmtl::Sphere<float> test_sph( gmtl::Point<float, 3>( 1.0f, 2.0f, 3.0f ), 25.0f );
      test_sph.setRadius( 45.0f );
      CPPUNIT_ASSERT( test_sph.getRadius() == 45.0f );

      // Test getCenter overhead
      const long iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the compiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         test_sph.setRadius( iter );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/SetRadiusOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   // -- Test comparison -- //
   void testEqualityCompare()
   {
      gmtl::Sphere<float> test_sph1( gmtl::Point<float, 3>(1.0f, 2.0f, 3.0f), 4.0f);
      gmtl::Sphere<float> test_sph2(test_sph1);

      CPPUNIT_ASSERT( test_sph1 == test_sph2);
      CPPUNIT_ASSERT(! (test_sph1 != test_sph2));

      test_sph2 = test_sph1;     // Set equal, vary center
      test_sph2.mCenter[0] = 21.10f;
      CPPUNIT_ASSERT( test_sph1 != test_sph2);
      CPPUNIT_ASSERT(! (test_sph1 == test_sph2));

      test_sph2 = test_sph1;     // Set equal, vary radius
      test_sph2.mRadius = 21.10f;
      CPPUNIT_ASSERT( test_sph1 != test_sph2);
      CPPUNIT_ASSERT(! (test_sph1 == test_sph2));

      // Test comparison performance
      // Test constructor
      const float iters(400000);
      unsigned true_count(0);
      unsigned false_count(0);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();
      test_sph1.mCenter.set( 0.0f, 0.0f, 0.0f );
      test_sph1.mRadius = 2000.0f;
      test_sph2 = test_sph1;
      test_sph2.mRadius = 1000.0f;

      for( float iter=0;iter<iters; ++iter)
      {
         test_sph1.mRadius += 1.0f;
         test_sph2.mRadius += 2.0f;
         if(test_sph1 == test_sph2)
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/EqualityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- Inequality
      CPPUNIT_METRIC_START_TIMING();
      test_sph1.mCenter.set( 0.0f, 0.0f, 0.0f );
      test_sph1.mRadius = 2000.0f;
      test_sph2 = test_sph1;
      test_sph2.mRadius = 1000.0f;

      for( float iter=0;iter<iters; ++iter)
      {
         test_sph1.mRadius += 1.0f;
         test_sph2.mRadius += 2.0f;
         if(test_sph1 != test_sph2)
            false_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/InequalityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

   }

   // -- Test comparison -- //
   void testIsEqual()
   {
      gmtl::Sphere<float> test_sph1( gmtl::Point<float, 3>(1.0f, 2.0f, 3.0f), 4.0f );
      gmtl::Sphere<float> test_sph2(test_sph1);
      float eps(0.0f);

      for(eps=0.0f;eps<10.0f;eps += 0.05f)
      {
         CPPUNIT_ASSERT( gmtl::isEqual(test_sph1, test_sph2, eps) );
      }

      test_sph1.mCenter.set(1.0f, 1.0f, 1.0f);
      test_sph1.mRadius = 1.0f;
      for(unsigned elt=0; elt<4; elt++)
      {
         test_sph2 = test_sph1;     // Set equal, vary elt 0
         if ( elt < 3 ) {
            test_sph2.mCenter[elt] = 21.0f;
         } else {
            test_sph2.mRadius = 21.0f;
         }
         CPPUNIT_ASSERT( !gmtl::isEqual(test_sph1, test_sph2, 10.0f) );
         CPPUNIT_ASSERT( !gmtl::isEqual(test_sph1, test_sph2, 19.9f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_sph1, test_sph2, 20.1f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_sph1, test_sph2, 22.0f) );
      }

      // Test comparison performance
      // Test constructor
      const float iters(400000);
      unsigned true_count(0);
      unsigned false_count(0);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();
      test_sph1.mCenter.set(0.0f, 0.0f, 0.0f);
      test_sph1.mRadius = 2000.0f;
      test_sph2 = test_sph1;
      test_sph2.mRadius = 1000.0f;

      for( float iter=0;iter<iters; ++iter)
      {
         test_sph1.mRadius += 1.0f;
         test_sph2.mRadius += 2.0f;
         if(gmtl::isEqual(test_sph1, test_sph2, 1.0f) )
            true_count++;
         if(gmtl::isEqual(test_sph1, test_sph2, 0.1f) )
            true_count++;
         if(gmtl::isEqual(test_sph1, test_sph2, 100000.0f) )
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/isEqualOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   //---------------------------------------------------------------------------
   // Containment tests
   //---------------------------------------------------------------------------
   void testIsInVolumePoint()
   {
      gmtl::Sphere<float> test_sph( gmtl::Point<float, 3>(0.0f, 0.0f, 0.0f), 4.0f);
      gmtl::Point<float, 3> pt( 0.5, 0.5f, 0.5f );
      CPPUNIT_ASSERT( gmtl::isInVolume(test_sph, pt) );
      pt[0] = 5.0f;
      CPPUNIT_ASSERT( ! gmtl::isInVolume(test_sph, pt) );

      // test isInVolume performace
      const float iters(400000);
      unsigned true_count(0);
      pt.set( 0.0f, 0.0f, 0.0f );

      CPPUNIT_METRIC_START_TIMING();
      for ( float iter=0;iter<iters; ++iter)
      {
         pt[0] += 0.05f;
         if ( gmtl::isInVolume(test_sph, pt) ) {
            true_count++;
         }
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/isInVolumePointOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testIsInVolumeSphere()
   {
      gmtl::Sphere<float> test_sph( gmtl::Point<float, 3>(0.0f, 0.0f, 0.0f), 4.0f);
      gmtl::Sphere<float> sph( gmtl::Point<float, 3>(0.5f, 0.5f, 0.5f ), 2.0f);
      CPPUNIT_ASSERT( gmtl::isInVolume(test_sph, sph) );
      sph.mCenter[0] = 5.0f;
      CPPUNIT_ASSERT( ! gmtl::isInVolume(test_sph, sph) );

      // test isInVolume performace
      const float iters(400000);
      unsigned true_count(0);
      sph.mCenter.set( 0.0f, 0.0f, 0.0f );

      CPPUNIT_METRIC_START_TIMING();
      for ( float iter=0;iter<iters; ++iter)
      {
         sph.mCenter[0] += 0.05f;
         if ( gmtl::isInVolume(test_sph, sph) ) {
            true_count++;
         }
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/isInVolumeSphereOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testIsOnVolume()
   {
      gmtl::Sphere<float> test_sph( gmtl::Point<float, 3>(0.0f, 0.0f, 0.0f), 4.0f);
      gmtl::Point<float, 3> pt( 0.0, 0.0f, 4.0f );

      // zero tolerance
      CPPUNIT_ASSERT( gmtl::isOnVolume(test_sph, pt) );
      pt[0] = 1.0f;
      CPPUNIT_ASSERT( ! gmtl::isOnVolume(test_sph, pt) );

      // epsilon tolerance
      pt.set( 0.0f, 0.0f, 4.0f );
      float eps(0.0f);
      for ( eps=0.0f; eps<10.0f; eps+=0.05f )
      {
         CPPUNIT_ASSERT( gmtl::isOnVolume(test_sph, pt, eps) );
      }

      for ( unsigned elt=0; elt<3; ++elt )
      {
         pt.set( 0.0f, 0.0f, 0.0f );
         pt[elt] = 2.0f;
         CPPUNIT_ASSERT( gmtl::isOnVolume(test_sph, pt, 21.0f) );
         CPPUNIT_ASSERT( gmtl::isOnVolume(test_sph, pt, 2.0f) );
         CPPUNIT_ASSERT( ! gmtl::isOnVolume(test_sph, pt, 1.9f) );
         CPPUNIT_ASSERT( ! gmtl::isOnVolume(test_sph, pt, 1.0f) );
      }

      // test isOnVolume performance
      const float iters(400000);
      unsigned true_count(0);
      eps = 0;
      pt.set( 0.0f, 0.0f, 0.0f );

      CPPUNIT_METRIC_START_TIMING();
      for ( float iter=0; iter<iters; ++iter )
      {
         eps += 0.01f;
         pt[2] += 0.1f;
         if ( gmtl::isOnVolume( test_sph, pt, eps ) )
            ++true_count;
         if ( gmtl::isOnVolume( test_sph, pt ) )
            ++true_count;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/isOnVolumeOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testExtendVolumePoint()
   {
      gmtl::Sphere<float> test_sph1( gmtl::Point<float, 3>(0.0f, 0.0f, 0.0f), 1.0f );
      gmtl::Point<float, 3> pt1( 2.0f, 0.0f, 0.0f );
      gmtl::Point<float, 3> pt2( pt1 );
      gmtl::Sphere<float> test_sph2;

      for (unsigned elt=0; elt<3; elt++ )
      {
         test_sph2 = test_sph1;
         pt1.set( 0.0f, 0.0f, 0.0f );
         pt1[elt] = 3.0f;
         pt2.set( 0.0f, 0.0f, 0.0f );
         pt2[elt] = 1.0f;
         extendVolume( test_sph2, pt1 );
         CPPUNIT_ASSERT( test_sph2.mCenter == pt2 );
         CPPUNIT_ASSERT( test_sph2.mRadius == 2.0f );
      }

      // test extendVolume performance
      const float iters(400000);
      test_sph1.mCenter.set( 0.0f, 0.0f, 0.0f );
      test_sph1.mRadius = 0.0f;
      pt1.set( 0.0f, 0.0f, 0.0f );

      CPPUNIT_METRIC_START_TIMING();
      for ( float iter=0; iter<iters; ++iter )
      {
         pt1[0] += 2.0f;
         pt1[1] += 1.0f;
         pt1[2] += 2.5f;
         gmtl::extendVolume( test_sph1, pt1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/extendVolumePointOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testExtendVolumeSphere()
   {
      gmtl::Sphere<float> test_sph1( gmtl::Point<float, 3>(0.0f, 0.0f, 0.0f), 0.0f );
      gmtl::Sphere<float> sph( gmtl::Point<float, 3>(0.0f, 0.0f, 0.0f), 0.0f );
      gmtl::Point<float, 3> pt1( 0.0f, 0.0f, 0.0f );
      gmtl::Sphere<float> test_sph2;

      for (unsigned elt=0; elt<3; ++elt )
      {
         test_sph2 = test_sph1;
         test_sph2.mCenter.set( 0.0f, 0.0f, 0.0f );
         test_sph2.mRadius = 1.0f;
         sph.mCenter.set( 0.0f, 0.0f, 0.0f );
         sph.mCenter[elt] = 5.0f;
         sph.mRadius = 2.0f;
         pt1.set( 0.0f, 0.0f, 0.0f );
         pt1[elt] = 3.0f;
         extendVolume( test_sph2, sph );
         CPPUNIT_ASSERT( test_sph2.mCenter == pt1 );
         CPPUNIT_ASSERT( test_sph2.mRadius == 4.0f );
      }

      // test extendVolume performance
      const float iters(400000);
      test_sph1.mCenter.set( 0.0f, 0.0f, 0.0f );
      test_sph1.mRadius = 0.0f;
      sph.mCenter.set( 0.0f, 0.0f, 0.0f );
      sph.mRadius = 0.0f;

      CPPUNIT_METRIC_START_TIMING();
      for ( float iter=0; iter<iters; ++iter )
      {
         sph.mCenter[0] += 2.0f;
         sph.mCenter[1] += 1.0f;
         sph.mCenter[2] += 2.5f;
         sph.mRadius += 0.5f;
         gmtl::extendVolume( test_sph1, sph );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/extendVolumeSphereOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testMakeVolumePoint()
   {
      gmtl::Sphere<float> test_sph;
      std::vector< gmtl::Point<float, 3> > pts;

      pts.push_back( gmtl::Point<float, 3>(1.0f, 0.0f, 0.0f) );
      pts.push_back( gmtl::Point<float, 3>(0.0f, 5.0f, 0.0f) );
      pts.push_back( gmtl::Point<float, 3>(0.0f, 5.0f, 10.0f) );
      pts.push_back( gmtl::Point<float, 3>(0.0f, 5.0f, -10.0f) );

      makeVolume( test_sph, pts );

      gmtl::Point<float, 3> pt(0.25f, 3.75f, 0.0f);
      CPPUNIT_ASSERT( gmtl::Math::isEqual( test_sph.mRadius, 10.08f, 0.01f ) );
      CPPUNIT_ASSERT( test_sph.mCenter == pt);

      // test makeVolume performance
      const float iters(10000);
      for ( unsigned i=0; i<100; ++i )
      {
         gmtl::Point<float, 3> pt;
         pt[0] = gmtl::Math::rangeRandom( -10000.0f, 10000.0f );
         pt[1] = gmtl::Math::rangeRandom( -10000.0f, 10000.0f );
         pt[2] = gmtl::Math::rangeRandom( -10000.0f, 10000.0f );
         pts.push_back( pt );
      }

      CPPUNIT_METRIC_START_TIMING();
      for ( float iter=0; iter<iters; ++iter )
      {
         pts[(int)iter % pts.size()][2] += 12.0f;
         gmtl::makeVolume( test_sph, pts );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/makeVolumePointOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
/*
   void testMakeVolumeSphere()
   {
      gmtl::Sphere<float> test_sph;
      std::vector< gmtl::Sphere<float> > spheres;

      spheres.push_back( gmtl::Sphere<float>( gmtl::Point<float, 3>(7.0f, 0.0f, 0.0f), 1.0f ) );
      spheres.push_back( gmtl::Sphere<float>( gmtl::Point<float, 3>(3.0f, 0.0f, 0.0f), 1.0f ) );
      spheres.push_back( gmtl::Sphere<float>( gmtl::Point<float, 3>(5.0f, 2.0f, 0.0f), 1.0f ) );
      spheres.push_back( gmtl::Sphere<float>( gmtl::Point<float, 3>(5.0f, -2.0f, 0.0f), 1.0f ) );

      makeVolume( test_sph, spheres );

      gmtl::Point<float, 3> pt( 5.0f, 0.0f, 0.0f );
      CPPUNIT_ASSERT( test_sph.mRadius == 3.0f );
      CPPUNIT_ASSERT( test_sph.mCenter == pt );

      // test makeVolume performance
      const float iters(400000);
      for ( unsigned i=0; i<1000; ++i )
      {
         gmtl::Point<float, 3> pt;
         pt[0] = gmtl::Math::rangeRandom( -10000.0f, 10000.0f );
         pt[1] = gmtl::Math::rangeRandom( -10000.0f, 10000.0f );
         pt[2] = gmtl::Math::rangeRandom( -10000.0f, 10000.0f );
         float rad = gmtl::Math::rangeRandom( -10000.0f, 10000.0f );
         
         spheres.push_back( gmtl::Sphere<float>(pt, rad) );
      }

      CPPUNIT_METRIC_START_TIMING();
      for ( float iter=0; iter<iters; ++iter )
      {
         spheres[(int)iter % spheres.size()].mCenter[2] += 32.0f;
         gmtl::makeVolume( test_sph, spheres );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("SphereTest/makeVolumeSphereOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
*/

   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("SphereTest");
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testCreation", &SphereTest::testCreation));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testCopyConstruct", &SphereTest::testCopyConstruct));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testConstructors", &SphereTest::testConstructors));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testEqualityCompare", &SphereTest::testEqualityCompare));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testIsEqual", &SphereTest::testIsEqual));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testGetCenter", &SphereTest::testGetCenter));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testGetRadius", &SphereTest::testGetRadius));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testSetCenter", &SphereTest::testSetCenter));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testSetRadius", &SphereTest::testSetRadius));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testIsInVolumePoint", &SphereTest::testIsInVolumePoint));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testIsInVolumeSphere", &SphereTest::testIsInVolumeSphere));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testIsOnVolume", &SphereTest::testIsOnVolume));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testExtendVolumePoint", &SphereTest::testExtendVolumePoint));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testExtendVolumeSphere", &SphereTest::testExtendVolumeSphere));
      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testMakeVolumePoint", &SphereTest::testMakeVolumePoint));
//      test_suite->addTest( new CppUnit::TestCaller<SphereTest>("testMakeVolumeSphere", &SphereTest::testMakeVolumeSphere));

      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveSphereTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
