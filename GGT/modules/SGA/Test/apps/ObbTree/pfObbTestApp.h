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

#include <iostream>

#include <Performer/pf/pfChannel.h>
#include <Performer/pf/pfDCS.h>
#include <Performer/pf/pfLightSource.h>
#include <Performer/pf/pfGeode.h>
#include <Performer/pr/pfTexture.h>
#include <Performer/pr/pfGeoSet.h>
#include <Performer/pf/pfScene.h>

#include <string>

//-------------------------------------------------------------
//: Simple test application for performer
//
//
// @author Allen Bierbaum
//  Date: 12-7-2000
//-------------------------------------------------------------
//!PUBLIC_API:
class pfObbTestApp
{
public:
   //: Application init function
   // Execute any initialization needed before the API is started
   virtual void init() {;}

   //: Application API init function
   // Execute any initialization needed <b>after</b> API is started
   //  but before drawing
   virtual void apiInit();

   //: Execute any final cleanup needed for the application
   // Delete apps and output final performance info
   virtual void exit();

   // Called during frame updates from APP process
   virtual void preFrame();
   virtual void intraFrame() {;}
   virtual void postFrame() {;}

   //: Reset the application
   virtual void reset() {;}

   void appKey(unsigned char keyHit, int x, int y);

public: // --- PERFORMER SPECIFIC ---- //
   //: Initialize the scene graph
   // Called after pfInit & pfConfig but before apiInit
   virtual void initScene();

   //: Called between pfInit and pfConfig
   // This function allows the user application to do any processing that needs
   // to happen before performer forks its processes off but after
   // pfInit()
   virtual void preForkInit() {;}

   //: Function called in application process for each active channel each frame
   // Called immediately before draw (pfFrame())
   virtual void appChanFunc(pfChannel* chan) {;}

   //: Return the current scene graph
   // This function must be defined so that the performer draw manager
   // can get a scene graph to draw.
   // NOTE: Do NOT put model loading and manipulation in this function
   //       instead, but that type of think in initScene()
   virtual pfGroup* getScene()
   {
      return mSceneRoot;
   }

   //: Function called in the channel draw function to do the actual drawing
   //
   // For most programs the default behavior of this function is correct.
   // It simply does the following: <br>
   //    chan->clear(); <br>
   //    pfDraw();      <br>
   //
   //! PRE: chan is ready to draw
   //! POST: Channel should be drawn
   virtual void drawChan(pfChannel* chan, void* chandata)
   {
      this->preDrawChan(chan,chandata);
      chan->clear();       // Clear the channel
      pfDraw();            // Draw the channel
      this->postDrawChan(chan,chandata);
   }

   // Function called by the DEFAULT drawChan function before clearing the channel
   // and drawing the next frame (pfFrame())
   virtual void preDrawChan(pfChannel* chan, void* chandata){;}

   // Function called by the DEFAULT drawChan function after clearing the channel
   // and drawing the next frame (pfFrame())
   virtual void postDrawChan(pfChannel* chan, void* chandata){;}

public:
   void setUserFilename(std::string filename)
   { mUserFilename = filename; }

protected:
   // --- Scene graph info --- //
   pfGroup* mSceneRoot;                       // Group with surface callback

   std::string    mUserFilename;             // Name of filename passed by user


public:
   static pfObbTestApp* instance()
   {
      if(_instance == NULL)
      { _instance = new pfObbTestApp(); }
      return _instance;
   }
private:
   pfObbTestApp();
   static pfObbTestApp* _instance;
};


#endif

