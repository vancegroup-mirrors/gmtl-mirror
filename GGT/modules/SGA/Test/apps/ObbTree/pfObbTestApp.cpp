/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: pfObbTestApp.cpp,v $
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
#include <pfObbTestApp.h>

#include <Performer/pfdu.h>

#include <Performer/pf/pfScene.h>
#include <Performer/pf/pfDCS.h>

pfObbTestApp* pfObbTestApp::_instance = NULL;

/*
int PostDrawSurface(pfTraverser* trav, void* data);
int PreDrawSurface(pfTraverser* trav, void* data);
*/

pfObbTestApp::pfObbTestApp() : mUserFilename("")
{
   mSceneRoot = NULL;
}


void pfObbTestApp::exit()
{;}

void pfObbTestApp::apiInit()
{
}

void pfObbTestApp::appKey(unsigned char keyHit, int x, int y)
{
  // Note that we're case-insensitive here (- and _ do the same thing).
  switch ( keyHit )
  {
  case 't':
     std::cout << "Hit the t key\n" << std::flush;
     break;
  default:
     break;
  }


}

//: Initialize the scene graph
// Called after pfInit & pfConfig but before apiInit
void pfObbTestApp::initScene()
{
   // Init fluid stuff
   mSceneRoot = new pfGroup;
   pfNode* the_model;

   if(!mUserFilename.empty())
      the_model = pfdLoadFile(mUserFilename.c_str());
   else
      the_model = pfdLoadFile("cow.obj");

   mSceneRoot->addChild(the_model);
}


void pfObbTestApp::preFrame()
{
}

/*
int PostDrawSurface(pfTraverser* trav, void* data)
{
   return PFTRAV_CONT;
}
int PreDrawSurface(pfTraverser* trav, void* data)
{
   pfFluidApp::instance()->appDraw();
   return PFTRAV_CONT;
}
*/
