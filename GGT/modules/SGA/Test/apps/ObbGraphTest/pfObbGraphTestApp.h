/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: pfObbGraphTestApp.h,v $
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
#include <apps/pfCore/pfXformerAppMixin.h>

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
class pfObbGraphTestApp : public pfAppBase, public pfXformerAppMixin
{
public:
   pfObbGraphTestApp();
   virtual ~pfObbGraphTestApp() {;}

   virtual void cmdline(int argc, char *argv[]);

   virtual void init();
   virtual void apiInit();

   virtual void appKey(unsigned char keyHit, int x, int y);

   virtual void preFrame();

public: // --- PERFORMER SPECIFIC ---- //
   //: Initialize the scene graph
   // Called after pfInit & pfConfig but before apiInit
   virtual void initScene();

   //: Return the current scene graph
   virtual pfGroup* getScene()
   { return mRootNode; }

   // Called when panel widget is hit
   virtual void panelWidgetAction(pfuWidget* widget);

   // Create panel
   virtual std::vector<pfuWidget*> createPanel(pfuPanel* panel, int minPanelId, int xOrigin, int yOrigin, int xSize, int ySize);

public:
   void drawTest();

public:     // -- Xformer interface -- //
   virtual void initXformer(pfChannel* chan, pfuMouse* mouse, pfuEventStream* events)
   {
      mSceneXformer = (pfiXformer *)pfiNewTDFXformer(pfGetSharedArena());
      mSceneXformer->setAutoInput(chan, mouse, events);
      mSceneXformer->setNode(mSceneRoot);
      mSceneXformer->setAutoPosition(chan, mSceneXformerDCS);
      mSceneXformer->selectModel(PFITDF_TRACKBALL);
      //mSceneXformer->setResetCoord(&Shared->initView);

      if(mModel2 != NULL)
      {
         mObjXformer = (pfiXformer *)pfiNewTDFXformer(pfGetSharedArena());
         mObjXformer->setAutoInput(chan, mouse, events);
         mObjXformer->setNode(mModel2Root);
         mObjXformer->setAutoPosition(chan, mObjXformerDCS);
         mObjXformer->selectModel(PFITDF_TRACKBALL);
      }
      else
      {
         mObjXformer = NULL;
      }

      mActiveXformer = mSceneXformer;
   }

   virtual void updateXformer()
   {
      if(mActiveXformer != NULL)
         mActiveXformer->update();
      //pfiUpdateXformer(mSceneXformer);
   }
   virtual void resetXformer()
   {;}


protected:
   void runFrameworkTests();

protected:
   // --- Scene graph info --- //
   pfGroup*       mRootNode;                    // Root node of everything
   pfGroup*       mSceneRoot;                       // Group with surface callback
   pfNode*        mModel1;
   pfGroup*       mModel1Root;            // Base root for the model
   pfNode*        mModel2;
   pfGroup*       mModel2Root;
   pfGroup*       mBoundGraphGroup;            // Node to draw the OBB on
   std::string    mFileName1;
   std::string    mFileName2;

   unsigned mRecurseDepthMin;
   unsigned mRecurseDepthMax;

   // Panel items
   pfuWidget*  mRecurseDepthMinWidget;
   int         mRecurseDepthMinWidgetId;
   pfuWidget*  mRecurseDepthMaxWidget;
   int         mRecurseDepthMaxWidgetId;
   pfuWidget*  mHitStatusPanel;

   // Xformer items
   pfDCS*      mSceneXformerDCS;    // DCS for trackball interface
   pfiXformer* mSceneXformer;       // interactive movement model
   pfDCS*      mObjXformerDCS;
   pfiXformer* mObjXformer;
   pfiXformer* mActiveXformer;      // Which xformer is active now


};

pfAppRegistrator<pfObbGraphTestApp> gRegisterObbTestApp;


#endif

