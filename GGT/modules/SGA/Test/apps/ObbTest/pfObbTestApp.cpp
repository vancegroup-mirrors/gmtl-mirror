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

// Performer classes and funcs
#include <Performer/pfdu.h>
#include <Performer/pf/pfScene.h>
#include <Performer/pf/pfDCS.h>

// GMTL stuff
#include <GMTL/Containment.h>
#include <GMTL/gmtlOutput.h>

namespace {
   pfObbTestApp* gTheApp = NULL;    // Yuck!!! Global that is used to store pointer to the application
                                    // We need this because we have pfStupid callbacks!!!!
};

int PostDrawObbTest(pfTraverser* trav, void* data);
int PreDrawObbTest(pfTraverser* trav, void* data);

pfObbTestApp::pfObbTestApp()
{
   mSceneRoot = NULL;
   mNumPoints = 7;
   gTheApp = this;
}

void pfObbTestApp::init()
{
   generateRandomObb();
}

void pfObbTestApp::appKey(unsigned char keyHit, int x, int y)
{
   std::cout << "Hit key: " << keyHit << std::endl;

   // Note that we're case-insensitive here (- and _ do the same thing).
  switch ( keyHit )
  {
  case 'p':
     std::cout << "Regenerating OBB..." << std::flush;
     generateRandomObb();
     break;
  default:
     break;
  }
}

//: Initialize the scene graph
// Called after pfInit & pfConfig but before apiInit
void pfObbTestApp::initScene()
{
   // Init scene graphy
   mSceneRoot = new pfGroup;

   //pfNode* the_model;
   // the_model = pfdLoadFile("cow.obj");
   // mSceneRoot->addChild(the_model);

   mObbTestNode = new pfGroup;
   pfSphere* obb_node_bound = new pfSphere();
   obb_node_bound->center.set(0,0,0);
   obb_node_bound->radius = 100.0f;
   mObbTestNode->setTravFuncs(PFTRAV_DRAW, PreDrawObbTest, PostDrawObbTest);
   mSceneRoot->addChild(mObbTestNode);
   mObbTestNode->setBound(obb_node_bound,PFBOUND_STATIC);
}

int PostDrawObbTest(pfTraverser* trav, void* data)
{
   return PFTRAV_CONT;
}
int PreDrawObbTest(pfTraverser* trav, void* data)
{
   // draw the test stuff
   gTheApp->drawTest();
   return PFTRAV_CONT;
}


void pfObbTestApp::generateRandomObb()
{
   // Get random cloud of points
   mPoints1.erase(mPoints1.begin(), mPoints1.end());
   mPoints2.erase(mPoints2.begin(), mPoints2.end());
   for (int i=0;i<mNumPoints;i++)
   {
      float scale = (Math::unitRandom()-0.5f)*10.0f;
      mPoints1.push_back(Point3(Math::unitRandom()*scale, Math::unitRandom()*scale, Math::unitRandom()*scale));
      mPoints2.push_back(Point3(Math::unitRandom()*scale, Math::unitRandom()*scale, Math::unitRandom()*scale));
   }

   std::cout << "----- Random points ------" << std::endl;
   std::cout << "Box1 Points:\n";
   for(int i=0;i<mNumPoints;i++)
   {
      std::cout << i << ": " << mPoints1[i] << std::endl;
   }
   std::cout << "Box2 Points:\n";
   for(int i=0;i<mNumPoints;i++)
   {
      std::cout << i << ": " << mPoints2[i] << std::endl;
   }



   gmtl::computeContainment(mObb1, mPoints1);
   gmtl::computeContainment(mObb2, mPoints2);
   gmtl::computeContainment(mCombinedObbFast, mObb1, mObb2, true);
   gmtl::computeContainment(mCombinedObbTight, mObb1, mObb2, false);
}

void pfObbTestApp::drawTest()
{
   //std::cout << "Drawing drawTest..." << std::endl;
   drawObb(mObb1);
   drawPoints(mPoints1, Vec3(1.0f,0.0f,0.0f));

   drawObb(mObb2);
   drawPoints(mPoints2, Vec3(0.0f,1.0f,0.0f));

   drawObb(mCombinedObbFast);
   drawObb(mCombinedObbTight);
}

void obbColorAndVert(unsigned vert, Point3 verts[8])
{
   static unsigned cube_lookup[8][3] = { {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1} };

   float r = ( cube_lookup[vert][0] ? 1.0f : 0.1f);
   float g = ( cube_lookup[vert][1] ? 1.0f : 0.1f);
   float b = ( cube_lookup[vert][2] ? 1.0f : 0.1f);

   glColor3f(r,g,b);
   glVertex3fv(&verts[vert][0]);
}

void pfObbTestApp::drawObb(const gmtl::OOBox& obb)
{
   Point3 verts[8];
   obb.getVerts(verts);

   glPushAttrib(GL_LINE_BIT);
   glColor3f(1.0f,0.1f,0.1f);
   glLineWidth(3.0f);
   glBegin(GL_LINES);
   {
      obbColorAndVert(0, verts); obbColorAndVert(1, verts);
      obbColorAndVert(1, verts); obbColorAndVert(2, verts);
      obbColorAndVert(2, verts); obbColorAndVert(3, verts);
      obbColorAndVert(3, verts); obbColorAndVert(0, verts);

      obbColorAndVert(0, verts); obbColorAndVert(4, verts);
      obbColorAndVert(1, verts); obbColorAndVert(5, verts);
      obbColorAndVert(2, verts); obbColorAndVert(6, verts);
      obbColorAndVert(3, verts); obbColorAndVert(7, verts);

      obbColorAndVert(4, verts); obbColorAndVert(5, verts);
      obbColorAndVert(5, verts); obbColorAndVert(6, verts);
      obbColorAndVert(6, verts); obbColorAndVert(7, verts);
      obbColorAndVert(7, verts); obbColorAndVert(4, verts);
   }
   glEnd();
   glPopAttrib();
}


void pfObbTestApp::drawPoints(const std::vector<gmtl::Point3>& points, gmtl::Vec3 color)
{
   glPushAttrib(GL_POINT_BIT);
   glColor3fv(&color[0]);
   glPointSize(4.0f);
   glBegin(GL_POINTS);
   {
      for(unsigned i=0;i<points.size();i++)
         glVertex3fv(&points[i][0]);
   }
   glEnd();
   glPopAttrib();
}



