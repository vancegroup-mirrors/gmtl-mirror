/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: SphereTest.h,v $
 * Date modified: $Date: 2003-02-05 02:21:17 $
 * Version:       $Revision: 1.16 $
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
#ifndef _SPHERE_TEST_H
#define _SPHERE_TEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   class SphereTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(SphereTest);

      CPPUNIT_TEST(testCreation);
      CPPUNIT_TEST(testCopyConstruct);
      CPPUNIT_TEST(testConstructors);
      CPPUNIT_TEST(testGetCenter);
      CPPUNIT_TEST(testGetRadius);
      CPPUNIT_TEST(testEqualityCompare);
      CPPUNIT_TEST(testIsEqual);
      CPPUNIT_TEST(testIsInVolumePoint);
      CPPUNIT_TEST(testIsInVolumeSphere);
      CPPUNIT_TEST(testIsOnVolume);
      CPPUNIT_TEST(testExtendVolumePoint);
      CPPUNIT_TEST(testExtendVolumeSphere);
      CPPUNIT_TEST(testMakeVolumePoint);
//      CPPUNIT_TEST(testMakeVolumeSphere);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testCreation();
      void testCopyConstruct();
      void testConstructors();

      // -- Test accessors --//
      void testGetCenter();
      void testGetRadius();

      // -- Test setters --//
      void testSetCenter();
      void testSetRadius();

      // -- Test comparison -- //
      void testEqualityCompare();
      void testIsEqual();

      //---------------------------------------------------------------------------
      // Containment tests
      //---------------------------------------------------------------------------
      void testIsInVolumePoint();
      void testIsInVolumeSphere();
      void testIsOnVolume();
      void testExtendVolumePoint();
      void testExtendVolumeSphere();
      void testMakeVolumePoint();
   //   void testMakeVolumeSphere();
   };
}

#endif
