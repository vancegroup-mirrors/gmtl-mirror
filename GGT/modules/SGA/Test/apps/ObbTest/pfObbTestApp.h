/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: pfObbTestApp.h,v $
 * Date modified: $Date: 2002-01-18 20:43:10 $
 * Version:       $Revision: 1.1.1.1 $
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
#ifndef _PF_OBB_TEST_APP_H_
#define _PF_OBB_TEST_APP_H_

#include <apps/pfCore/pfAppBase.h>

#include <iostream>

#include <Performer/pf/pfChannel.h>
#include <Performer/pf/pfDCS.h>
#include <Performer/pf/pfLightSource.h>
#include <Performer/pf/pfGeode.h>
#include <Performer/pr/pfTexture.h>
#include <Performer/pr/pfGeoSet.h>
#include <Performer/pf/pfScene.h>

#include <GMTL/Point3.h>
#include <GMTL/OOBox.h>
#include <GMTL/Vec3.h>
#include <GMTL/Matrix.h>

using gmtl::Point3;
using gmtl::OOBox;
using gmtl::Vec3;
using gmtl::Matrix;
using gmtl::Math;

#include <string>

//-------------------------------------------------------------
//: Simple test application for performer
//
//
// @author Allen Bierbaum
//  Date: 12-7-2000
//-------------------------------------------------------------
//!PUBLIC_API:
class pfObbTestApp : public pfAppBase
{
public:
   pfObbTestApp();

   virtual void init();

   virtual void appKey(unsigned char keyHit, int x, int y);

public: // --- PERFORMER SPECIFIC ---- //
   //: Initialize the scene graph
   // Called after pfInit & pfConfig but before apiInit
   virtual void initScene();

   //: Return the current scene graph
   virtual pfGroup* getScene()
   { return mSceneRoot; }

public:
   void drawTest();

protected:
   void generateRandomObb();
   void drawObb(const gmtl::OOBox& obb);
   void drawPoints(const std::vector<gmtl::Point3>& points, gmtl::Vec3 color);

protected:
   // --- Scene graph info --- //
   pfGroup* mSceneRoot;                       // Group with surface callback

   pfGroup*    mObbTestNode;            // Node to draw the OBB on
   gmtl::OOBox mObb1;             // The first OBB to use
   gmtl::OOBox mObb2;
   gmtl::OOBox mCombinedObbFast;     // Combined OBB
   gmtl::OOBox mCombinedObbTight;   // Combined OBB using tight fit

   std::vector<gmtl::Point3> mPoints1;  // Points contained in the OBB
   std::vector<gmtl::Point3> mPoints2;

   unsigned    mNumPoints;       // The number of points to put in box
};

pfAppRegistrator<pfObbTestApp> gRegisterObbTestApp;


#endif

