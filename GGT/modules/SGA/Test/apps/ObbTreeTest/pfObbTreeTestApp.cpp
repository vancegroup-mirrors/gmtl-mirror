/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: pfObbTreeTestApp.cpp,v $
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
#include <pfObbTreeTestApp.h>

// Performer classes and funcs
#include <Performer/pf.h>
#include <Performer/pr/pfGeoSet.h>
#include <Performer/pfdu.h>
#include <Performer/pf/pfScene.h>
#include <Performer/pf/pfDCS.h>

// GMTL stuff
#include <GMTL/Containment.h>
#include <GMTL/gmtlOutput.h>

// SGA
#include <SGA/ObbTraversals.h>
#include <SGA/TravFuncs.h>

#include <SGA/PfHelperFuncs.h>


namespace {
   pfObbTreeTestApp* gTheApp = NULL;    // Yuck!!! Global that is used to store pointer to the application
                                    // We need this because we have pfStupid callbacks!!!!

   // Helper functs
   pfGeoSet* createGsetGrid(unsigned size);
   pfGeoSet* createGsetSphere(int size);
   pfGeoSet* createRandomTris(unsigned numTris);

   void drawObb(const gmtl::OOBox& obb, float colorScale);

   struct printObbNode
   {
      printObbNode() : node_depth(0)
      {;}

      void pre(sga::ObbBoundingNode* node)
      {
         node_depth++;
         for(int i=0;i<node_depth;i++)
            std::cout << "  ";

         std::cout << node_depth << ": center(" << node->mBound.center() << ") " << std::endl;
      }

      void post(sga::ObbBoundingNode* node)
      {
         //std::cout << node_depth << "Coming back..." << std::endl;
         node_depth--;
      }

      int node_depth;
   };

   struct drawObbTree
   {
      drawObbTree() : cur_node_depth(0.0f), max_node_depth(0.0f)
      {;}

      void pre(sga::ObbBoundingNode* node)
      {
         cur_node_depth++;
         if(cur_node_depth > max_node_depth)
            max_node_depth = cur_node_depth;
      }

      void post(sga::ObbBoundingNode* node)
      {
         float color_scale = cur_node_depth/max_node_depth;

         if((cur_node_depth >= mMinRecurse) && (cur_node_depth <= mMaxRecurse))
         { drawObb(node->mBound, color_scale); }

         cur_node_depth--;
      }

      float cur_node_depth;
      float max_node_depth;

      unsigned mMinRecurse;
      unsigned mMaxRecurse;
   };


}

int PostDrawObbTreeTest(pfTraverser* trav, void* data);
int PreDrawObbTreeTest(pfTraverser* trav, void* data);

pfObbTreeTestApp::pfObbTreeTestApp() : mGsetTriAdapter(NULL)
{
   mSceneRoot = NULL;
   mTestGset = NULL;
   mNumTris = 7;

   mRecurseDepthMin = 0;
   mRecurseDepthMax = 15;

   gTheApp = this;
}

void pfObbTreeTestApp::init()
{

}

void pfObbTreeTestApp::apiInit()
{
   // Run any tests that we have for pf
   runFrameworkTests();
}

void pfObbTreeTestApp::appKey(unsigned char keyHit, int x, int y)
{
   std::cout << "Hit key: " << keyHit << std::endl;

   // Note that we're case-insensitive here (- and _ do the same thing).
  switch ( keyHit )
  {
  case 'r':
  case 'R':
     std::cout << "Regenerating Gset..." << std::flush;
     regenerateGset();
     break;
  default:
     break;
  }
}

//: Initialize the scene graph
// Called after pfInit & pfConfig but before apiInit
void pfObbTreeTestApp::initScene()
{
   // Init scene graphy
   mSceneRoot = new pfGroup;

   //pfNode* the_model;
   // the_model = pfdLoadFile("cow.obj");
   // mSceneRoot->addChild(the_model);


   mBoundTreeGroup = new pfGroup;
   pfSphere* obb_node_bound = new pfSphere();
   obb_node_bound->center.set(0,0,0);
   obb_node_bound->radius = 100.0f;
   mBoundTreeGroup->setTravFuncs(PFTRAV_DRAW, PreDrawObbTreeTest, PostDrawObbTreeTest);
   mSceneRoot->addChild(mBoundTreeGroup);
   mBoundTreeGroup->setBound(obb_node_bound,PFBOUND_STATIC);


   mTestGeode = new pfGeode();
   regenerateGset();                         // Do the first generation
   mSceneRoot->addChild(mTestGeode);
}

std::vector<pfuWidget*> pfObbTreeTestApp::createPanel(pfuPanel* panel, int minPanelId, int xOrigin, int yOrigin, int xSize, int ySize)
{
    int x, y, yTop;
    pfuWidget *wid;
    std::vector<pfuWidget*> new_widgets;

    // Compute starting point
    x = (int)xOrigin;
    yTop = (int)(yOrigin + ySize);
    y = (int)yTop - PFUGUI_BUTTON_YINC;      // To get lower left corner of first button


    // ------ CREATE WIDGET ------------- //

    // Num triangles widget
   mNumTrisWidgetId = ++minPanelId;
   mNumTrisWidget = pfuNewWidget(panel, PFUGUI_SLIDER_LOG, mNumTrisWidgetId);
   new_widgets.push_back(mNumTrisWidget);
   pfuWidgetDim(mNumTrisWidget,  x,  y,  PFUGUI_SLIDER_BIG_XSIZE, PFUGUI_SLIDER_YSIZE);
    pfuWidgetLabel(mNumTrisWidget, "Num tris");
    pfuWidgetRange(mNumTrisWidget, PFUGUI_SLIDER_LOG, 1.0, 1000.0, 7.0);
    x += PFUGUI_SLIDER_BIG_XINC;

    // ----- Recurse depth: Min ------- //
    mRecurseDepthMinWidgetId = ++minPanelId;
    mRecurseDepthMinWidget = pfuNewWidget(panel, PFUGUI_SLIDER, mRecurseDepthMinWidgetId);
    new_widgets.push_back(mRecurseDepthMinWidget);
    pfuWidgetDim(mRecurseDepthMinWidget,  x,  y,  PFUGUI_SLIDER_SMALL_XSIZE, PFUGUI_SLIDER_YSIZE);
    pfuWidgetLabel(mRecurseDepthMinWidget, "Min recurse");
    pfuWidgetRange(mRecurseDepthMinWidget, PFUGUI_SLIDER, 0.0, 15.0, 0.0);
    x += PFUGUI_SLIDER_SMALL_XINC;

    // ----- Recurse depth: Max ------- //
    mRecurseDepthMaxWidgetId = ++minPanelId;
    mRecurseDepthMaxWidget = pfuNewWidget(panel, PFUGUI_SLIDER, mRecurseDepthMaxWidgetId);
    new_widgets.push_back(mRecurseDepthMaxWidget);
    pfuWidgetDim(mRecurseDepthMaxWidget,  x,  y,  PFUGUI_SLIDER_SMALL_XSIZE, PFUGUI_SLIDER_YSIZE);
    pfuWidgetLabel(mRecurseDepthMaxWidget, "Max recurse");
    pfuWidgetRange(mRecurseDepthMaxWidget, PFUGUI_SLIDER, 0.0, 15.0, 15.0);
    x += PFUGUI_SLIDER_SMALL_XINC;


    x = (int)xOrigin;
    y -= PFUGUI_SLIDER_YINC;

    return new_widgets;
}

void pfObbTreeTestApp::panelWidgetAction(pfuWidget* widget)
{
   float val;
   int wid_id = pfuGetWidgetId(widget);

   if(wid_id == mNumTrisWidgetId)
   {
      mNumTris = int(pfuGetWidgetValue(mNumTrisWidget));
      regenerateGset();
      std::cout << "Set num tris: " << mNumTris << std::endl;
   }
   else if((wid_id == mRecurseDepthMaxWidgetId) || (wid_id == mRecurseDepthMinWidgetId))
   {
      mRecurseDepthMin = int(pfuGetWidgetValue(mRecurseDepthMinWidget));
      mRecurseDepthMax = int(pfuGetWidgetValue(mRecurseDepthMaxWidget));
   }
   else  // default
   {
      pfNotify(PFNFY_DEBUG, PFNFY_PRINT,
               "Have GUI Widget \"%s\": id=%d, val = %f\n",
               pfuGetWidgetLabel(widget), pfuGetWidgetId(widget), pfuGetWidgetValue(widget));
   }

}


int PostDrawObbTreeTest(pfTraverser* trav, void* data)
{
   return PFTRAV_CONT;
}
int PreDrawObbTreeTest(pfTraverser* trav, void* data)
{
   // draw the test stuff
   gTheApp->drawTest();
   return PFTRAV_CONT;
}

// Run them here because I can't get them to run in the frame work
void pfObbTreeTestApp::runFrameworkTests()
{
   //sgaTest::PfTriangleListAdapterTest::testIt();

}


void pfObbTreeTestApp::regenerateGset()
{
   if(mTestGset != NULL)
   {
      mTestGeode->removeGSet(mTestGset);
   }

   mTestGset = createRandomTris(mNumTris);
   //mTestGset = ::createGsetSphere(mNumTris);

   mTestGeode->addGSet(mTestGset);

   updateBoundingTree();
}

void pfObbTreeTestApp::updateBoundingTree()
{
   mGsetTriAdapter.setGeoSet(mTestGset);
   mBoundTree.setTriAdapter(&mGsetTriAdapter);
   mBoundTree.createBoundingTree();

   std::cout << "---- New Bounding Tree ----" << std::endl;

   printObbNode node_printer;

   sga::travObbTree(mBoundTree.getTree(),
                    member_func1(&node_printer,&printObbNode::pre),
                    member_func1(&node_printer,&printObbNode::post));

}


void pfObbTreeTestApp::drawTest()
{
   gfxASSERT(mBoundTree.getTree() != NULL);
   drawObbTree the_drawer;
   the_drawer.mMaxRecurse = this->mRecurseDepthMax;
   the_drawer.mMinRecurse = this->mRecurseDepthMin;
   sga::travObbTree(mBoundTree.getTree(),
                    member_func1(&the_drawer,&drawObbTree::pre),
                    member_func1(&the_drawer,&drawObbTree::post));
}




void pfObbTreeTestApp::drawPoints(const std::vector<gmtl::Point3>& points, gmtl::Vec3 color)
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


// HIDDEN HELPER FUNCS

namespace {

   void obbColorAndVert(unsigned vert, Point3 verts[8])
{
   static unsigned cube_lookup[8][3] = { {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1} };

   float r = ( cube_lookup[vert][0] ? 1.0f : 0.1f);
   float g = ( cube_lookup[vert][1] ? 1.0f : 0.1f);
   float b = ( cube_lookup[vert][2] ? 1.0f : 0.1f);

   glColor3f(r,g,b);
   glVertex3fv(&verts[vert][0]);
}

void drawObb(const gmtl::OOBox& obb, float colorScale)
{
   Point3 verts[8];
   obb.getVerts(verts);

   glPushAttrib(GL_ALL_ATTRIB_BITS);
   //glColor3f(1.0f,0.1f,0.1f);

   float r,g,b;
   r = ((colorScale < 0.5f) ? (1.0f-(2*colorScale)): 0.0f);
   g = ((colorScale < 0.5f) ? (0.0f+(2*colorScale)): (1.0f-(2*(colorScale-0.5))) );
   b = ((colorScale > 0.5f) ? (2*(colorScale-0.5)) : 0.0f);

   glColor3f(r,g,b);
   glLineWidth(2.0f);
   glBegin(GL_LINES);
   {
      /*
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
      */
      glVertex3fv(&verts[0][0]); glVertex3fv(&verts[1][0]);
      glVertex3fv(&verts[1][0]); glVertex3fv(&verts[2][0]);
      glVertex3fv(&verts[2][0]); glVertex3fv(&verts[3][0]);
      glVertex3fv(&verts[3][0]); glVertex3fv(&verts[0][0]);

      glVertex3fv(&verts[0][0]); glVertex3fv(&verts[4][0]);
      glVertex3fv(&verts[1][0]); glVertex3fv(&verts[5][0]);
      glVertex3fv(&verts[2][0]); glVertex3fv(&verts[6][0]);
      glVertex3fv(&verts[3][0]); glVertex3fv(&verts[7][0]);

      glVertex3fv(&verts[4][0]); glVertex3fv(&verts[5][0]);
      glVertex3fv(&verts[5][0]); glVertex3fv(&verts[6][0]);
      glVertex3fv(&verts[6][0]); glVertex3fv(&verts[7][0]);
      glVertex3fv(&verts[7][0]); glVertex3fv(&verts[4][0]);

   }
   glEnd();
   glPopAttrib();
}

   pfGeoSet* createGsetSphere(int size)
   {
       return pfdNewSphere(size, pfGetSharedArena());
   }


   pfGeoSet* createRandomTris(unsigned numTris)
   {
      pfVec3 *coords = new pfVec3[numTris*3];
      pfVec4 *colors = new pfVec4[numTris];

      const float POS_RANGE(2.0f);
      const float SIZE_RANGE(1.5f);

      for(int tri_num=0;tri_num<numTris;tri_num++)
      {
         // Compute random triangle
         gmtl::Vec3  tri_vec1, tri_vec2;
         gmtl::Point3 tri_center;
         float offset1, offset2;

         tri_vec1.set(gmtl::Math::unitRandom()-0.5, gmtl::Math::unitRandom()-0.5, gmtl::Math::unitRandom()-0.5);
         tri_vec2.set(gmtl::Math::unitRandom()-0.5, gmtl::Math::unitRandom()-0.5, gmtl::Math::unitRandom()-0.5);
         tri_vec1.normalize();
         tri_vec2.normalize();
         tri_center.set(gmtl::Math::unitRandom()*POS_RANGE,gmtl::Math::unitRandom()*POS_RANGE, gmtl::Math::unitRandom()*POS_RANGE);
         offset1 = (gmtl::Math::unitRandom()-0.5f)*SIZE_RANGE;
         offset2 = (gmtl::Math::unitRandom()-0.5f)*SIZE_RANGE;

         gmtl::Point3 v1, v2;
         v1 = tri_center+(tri_vec1*offset1);
         v2 = tri_center+(tri_vec2*offset2);

         // Put it in list
         coords[(tri_num*3)+0] = sga::getPfVec3(tri_center);
         coords[(tri_num*3)+1] = sga::getPfVec3(v1);
         coords[(tri_num*3)+2] = sga::getPfVec3(v2);
      }

      // Compute colors
      for(int cnum=0;cnum<numTris;cnum++)
      {
         colors[cnum] = pfVec4(gmtl::Math::unitRandom(), gmtl::Math::unitRandom(), gmtl::Math::unitRandom(), 1.0f);
      }


       pfGeoSet *gset = new pfGeoSet;
       gset->setAttr(PFGS_COORD3, PFGS_PER_VERTEX, coords, NULL);
       gset->setAttr(PFGS_COLOR4, PFGS_PER_PRIM, colors, NULL);
       gset->setPrimType(PFGS_TRIS);
       gset->setNumPrims(numTris);

       // Set up a geostate, backface removal turned off
       pfGeoState* gstate = new pfGeoState;
       gstate->setMode(PFSTATE_CULLFACE, PFCF_OFF);
       gset->setGState(gstate);

       return gset;
   }



   pfGeoSet* createGsetGrid(unsigned size)
   {
      pfVec3 *coords = new pfVec3[9];
      pfVec4 *colors = new pfVec4[9];

      coords[6].set(0,2,0);      coords[7].set(1,2,3);      coords[8].set(2,2,5);
      coords[3].set(0,1,2);      coords[4].set(1,1,1);      coords[5].set(2,1,3);
      coords[0].set(0,0,0);      coords[1].set(1,0,1);      coords[2].set(2,0,4);

      for(unsigned crd=0;crd<9;crd++)
      {
         coords[crd] *= 3.0f;
      }

      colors[6].set(.2,1,0,1);      colors[7].set(.6,1,0,1);      colors[8].set(1,1,0,1);
      colors[3].set(.2,.5,0,1);      colors[4].set(.6,.5,0,1);      colors[5].set(1,.5,0,1);
      colors[0].set(.2,.2,0,1);      colors[1].set(.6,.2,0,1);      colors[2].set(1,.2,0,1);

      int*    prim_len = new int[2];
      prim_len[0] = prim_len[1] = 6;

      ushort* vi = new ushort[12];
      for(int i=0;i<6;i++)
      {
         vi[(i*2)+0] = i;
         vi[(i*2)+1] = i+3;
      }

       pfGeoSet *gset = new pfGeoSet;
       gset->setAttr(PFGS_COORD3, PFGS_PER_VERTEX, coords, vi);
       gset->setAttr(PFGS_COLOR4, PFGS_PER_VERTEX, colors, vi);
       gset->setPrimLengths(prim_len);
       gset->setPrimType(PFGS_TRISTRIPS);
       gset->setNumPrims(2);

       // Set up a geostate, backface removal turned off
       pfGeoState* gstate = new pfGeoState;
       gstate->setMode(PFSTATE_CULLFACE, PFCF_OFF);
       gset->setGState(gstate);

       return gset;
   }



   /*
   // Creats a gset that is just a simple grid.
   // Try to keep many of the triangles from being coplannar
   pfGeoSet* createGsetGrid(unsigned size)
   {
      unsigned i,j;

      const float phase1(20.5f);
      const float offset1(1.2f);
      const float amp1(0.025f);
      const float phase2(20.6f);
      const float offset2(0.3f);
      const float amp2(0.015);

      unsigned dim = size+1;
      pfVec3 *coords = new pfVec3[dim*dim];
      pfVec4 *colors = new pfVec4[dim*dim];

      int*    prim_len = new int[size];
      for(i=0;i<size;i++)
         { prim_len[i] = (size*2)+2; }

      ushort* indices = new ushort[((size*2)+2)*size];
      for(unsigned strip=0;strip<size;strip++)
      {
         for(unsigned v=0;v<size+1;v++)
         {
            indicies[v] = (strip*dim)+v;
            indicies[v+1] = ((strip+1)*dim) + v;
         }
      }

      float x(0.0f), y(0.0f);

      // Update height values of the grid
      for(i=0;i<mXDim;i++)
      {
         x = (1.0f/float(dim))*float(i);     // Compute current x coord
         for(j=0;j<mYDim;j++)
         {
            y = (1.0f/float(dim))*float(j);
            coords[(i*dim)+j].set(x,y, (amp1*sin((phase1*var1)+offset1) +
                                       amp2*sin((phase2*var2)+offset2)) );
            colors[(i*dim)+j].set(x,y,x+y,1.0f);
            //mVerts[i][j] = vjVec3(x,y,getHeight(x,y,curTime));
         }
      }

           pfGeoSet *gset = new pfGeoSet;
       gset->setAttr(PFGS_COORD3, PFGS_PER_VERTEX, coords, NULL);
       gset->setAttr(PFGS_COLOR4, PFGS_PER_VERTEX, colors, NULL);

       gset->setPrimType(PFGS_QUADS);
       gset->setNumPrims(1);

       // Set up a geostate, backface removal turned off
       pfGeoState* gstate = new pfGeoState;
       gstate->setMode(PFSTATE_CULLFACE, PFCF_OFF);
       gset->setGState(gstate);

       pfdLoadFile
   }
*/

};


