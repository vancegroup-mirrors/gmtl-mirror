/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: pfObbTreeTestApp.h,v $
 * Date modified: $Date: 2002-01-18 20:43:11 $
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

#include <SGA/ObbBoundingTree.h>
#include <SGA/PfTriangleListAdapter.h>

//-------------------------------------------------------------
//: Simple test application for performer
//
//
// @author Allen Bierbaum
//  Date: 12-7-2000
//-------------------------------------------------------------
//!PUBLIC_API:
class pfObbTreeTestApp : public pfAppBase
{
public:
   pfObbTreeTestApp();

   virtual void init();
   virtual void apiInit();

   virtual void appKey(unsigned char keyHit, int x, int y);

public: // --- PERFORMER SPECIFIC ---- //
   //: Initialize the scene graph
   // Called after pfInit & pfConfig but before apiInit
   virtual void initScene();

   //: Return the current scene graph
   virtual pfGroup* getScene()
   { return mSceneRoot; }

   // Called when panel widget is hit
   virtual void panelWidgetAction(pfuWidget* widget);

   // Create panel
   virtual std::vector<pfuWidget*> createPanel(pfuPanel* panel, int minPanelId, int xOrigin, int yOrigin, int xSize, int ySize);

public:
   void drawTest();

protected:
   void runFrameworkTests();

   void regenerateGset();
   void updateBoundingTree();


   void drawPoints(const std::vector<gmtl::Point3>& points, gmtl::Vec3 color);

protected:
   // --- Scene graph info --- //
   pfGroup* mSceneRoot;                       // Group with surface callback

   pfGroup*    mBoundTreeGroup;            // Node to draw the OBB on
   /*
   gmtl::OOBox mObb1;             // The first OBB to use
   gmtl::OOBox mObb2;
   gmtl::OOBox mCombinedObbFast;     // Combined OBB
   gmtl::OOBox mCombinedObbTight;   // Combined OBB using tight fit

   std::vector<gmtl::Point3> mPoints1;  // Points contained in the OBB
   std::vector<gmtl::Point3> mPoints2;
   */

   sga::ObbBoundingTree       mBoundTree;    // The bounding tree

   unsigned    mNumTris;       // The number of points to put in box
   unsigned    mRecurseDepthMin;    // The number of levels to recurse
   unsigned    mRecurseDepthMax;

   pfGeoSet*   mTestGset;        // The Gset to test
   pfGeode*    mTestGeode;       // The geode holding our geoset

   sga::PfTriangleListAdapter mGsetTriAdapter;

   // Panel items
   pfuWidget*  mNumTrisWidget;
   int         mNumTrisWidgetId;

   pfuWidget*  mRecurseDepthMinWidget;
   int         mRecurseDepthMinWidgetId;
   pfuWidget*  mRecurseDepthMaxWidget;
   int         mRecurseDepthMaxWidgetId;
};

pfAppRegistrator<pfObbTreeTestApp> gRegisterObbTestApp;


#endif

