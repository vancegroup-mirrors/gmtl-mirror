/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: pfObbGraphTestApp.cpp,v $
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
#include <pfObbGraphTestApp.h>

// Performer classes and funcs
#include <Performer/pf.h>
#include <Performer/pr/pfGeoSet.h>
#include <Performer/pfdu.h>
#include <Performer/pf/pfScene.h>
#include <Performer/pf/pfDCS.h>

// GMTL stuff
#include <GMTL/Matrix.h>
#include <GMTL/Containment.h>
#include <GMTL/gmtlOutput.h>
#include <GMTL/Intersection.h>
#include <GMTL/OOBox.h>
#include <GMTL/Xforms.h>

// SGA
#include <SGA/ObbBoundingTreeTravFuncs.h>
#include <SGA/ObbTraversals.h>
#include <SGA/Traverser.h>
#include <SGA/ObbTreeContainer.h>
#include <SGA/ObbNodeContainer.h>

#include <SGA/PfHelperFuncs.h>
#include <SGA/TravFuncs.h>
#include <SGA/Traverser.h>

#include <string>


namespace {
   pfObbGraphTestApp* gTheApp = NULL;    // Yuck!!! Global that is used to store pointer to the application
                                    // We need this because we have pfStupid callbacks!!!!

   void getColor(const float val, float& r, float& g, float& b);
   void drawObb(const gmtl::OOBox& obb, float colorScale);
   void drawObb(const gmtl::OOBox& obb, float r, float g, float b);

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

   // TRAV_TYPE: Must support pfTraverser and TrackXform
   //template<class TRAV_TYPE>
   struct DrawObbGraph
   {
     DrawObbGraph() : cur_node_depth(0.0f), max_node_depth(0.0f)
     {;}
     sga::Traverser::TravStatus pre(sga::PfTraverser* trav);
     sga::Traverser::TravStatus post(sga::PfTraverser* trav);

     void drawObbTree(sga::ObbBoundingTree& boundTree)
     {
        std::cout << "About to draw tree:\nxform: " << mCurObbTreeXform << std::endl;
        sga::travObbTree(boundTree.getTree(),
                      member_func1(this,&DrawObbGraph::obbTreeDrawPre),
                      member_func1(this,&DrawObbGraph::obbTreeDrawPost));
     }

     // --- For drawing tree --- //
      void obbTreeDrawPre(sga::ObbBoundingNode* node)
      {
         cur_node_depth++;
         if(cur_node_depth > max_node_depth)
            max_node_depth = cur_node_depth;
      }

      void obbTreeDrawPost(sga::ObbBoundingNode* node)
      {
         float color_scale = cur_node_depth/max_node_depth;

         if((cur_node_depth >= mMinRecurse) && (cur_node_depth <= mMaxRecurse))
         {
            gmtl::OOBox draw_box = node->mBound;
            draw_box = mCurObbTreeXform * draw_box;
            drawObb(node->mBound, color_scale);
         }

         cur_node_depth--;
      }

      float cur_node_depth;
      float max_node_depth;

      unsigned mMinRecurse;
      unsigned mMaxRecurse;

      gmtl::Matrix mCurObbTreeXform;
   };

   template< class TRAV_TYPE >
   struct printPfNodeInfo
   {
      printPfNodeInfo()
      {;}

      sga::Traverser::TravStatus pre(TRAV_TYPE* trav)
      {
         sga::PfTravState* trav_state = trav->travState();

         for(unsigned d=0;d<trav_state->depth();d++)
         { std::cout << "  "; }

         std::cout << trav_state->depth() << ": [";

         std::cout << trav_state->node()->getName()
                   << "]  type: " << trav_state->node()->getType()->getName();
         if(trav_state->node()->isOfType(pfGroup::getClassType()))
            std::cout << "numChildren: " << static_cast<pfGroup*>(trav_state->node())->getNumChildren();
         std::cout << std::endl;
         return sga::Traverser::CONT;
      }

      sga::Traverser::TravStatus post(TRAV_TYPE* trav)
      {
         sga::PfTravState* trav_state = trav->travState();

         for(unsigned d=0;d<trav_state->depth();d++)
         { std::cout << "  "; }

         std::cout << trav_state->depth() << ": [";
         std::cout << "<--- back up" << std::endl;
         return sga::Traverser::CONT;
      }

   };

   template<class TRAV_TYPE>
   struct NullTrav
   {
      sga::Traverser::TravStatus operator()(TRAV_TYPE* trav)
      { return sga::Traverser::CONT; }
   };


/*
      //: Call to traverse the scene
   template<class _TpreFunctor,
            class _TpostFunctor>
   Traverser::TravStatus traverse(pfNode* node, _TpreFunctor preFunc, _TpostFunctor postFunc);

protected:
   PfTravState*    mTravState;
*/

};


   // Class of traversal functions for testing intersection of two OBB graphs
   class ObbIntersectTraverser
   {
   public:
      ObbIntersectTraverser()
      {
         mMaxDepth = 10;
      }

      void init()
      {
         // Initialize the state objects
         tree1State.init();
         tree2State.init();

         mNumObbTests = 0;
         mNumObbXforms = 0;
         mNumFuncCalls = 0;
      }

      bool testIntersection(pfNode* node1, pfNode* node2)
      {
         init();
         tree1State.pushChild(node1);
         tree2State.pushChild(node2);

         return testNodeNodeIntersection(tree1State, tree2State);
      }

   protected:
      // Simply recurse through the graph portion
      // NOTE: Need to keep track of traversal state
      bool testNodeNodeIntersection(sga::TrackXform& tState1, sga::TrackXform& tState2)
      {
         bool ret = false;                      // Report no hit by default
         pfNode* child_node(NULL);

         if(mMaxDepth < tState1.depth())
            mMaxDepth = tState1.depth();
         if(mMaxDepth < tState2.depth())
            mMaxDepth = tState2.depth();

         pfNode* node1 = tState1.node();
         pfNode* node2 = tState2.node();

         std::cout << "nn:[" << node1->getName() << "-" << tState1.depth()
                   << "," << node2->getName() << "-" << tState2.depth() << "] \n";

         sga::ContainerHolder& cont_holder1 = sga::NodeAdapter(node1).contHolder();
         sga::ContainerHolder& cont_holder2 = sga::NodeAdapter(node2).contHolder();

         // Make sure that we have containers on these nodes
         if((cont_holder1.getContainer<sga::ObbNodeContainer>() == NULL) ||
            (cont_holder2.getContainer<sga::ObbNodeContainer>() == NULL))
         {
            std::cout << "ERROR: Trying to intersect nodes w/o obb containers" << std::endl;
            return false;
         }

         gmtl::OOBox box1 = cont_holder1.getContainer<sga::ObbNodeContainer>()->box();
         gmtl::OOBox box2 = cont_holder2.getContainer<sga::ObbNodeContainer>()->box();

         gmtl::Matrix xform_mat1 = tState1.getXformMat();
         gmtl::Matrix xform_mat2 = tState2.getXformMat();

         std::cout << "xform1:\n" << xform_mat1 << "\nxform2:\n" << xform_mat2 << std::endl;
         box1 = xform_mat1 * box1;
         box2 = xform_mat2 * box2;

         // Test for overlap -- If not overlap, then return now because nothing futher down can hit
         if(!gmtl::TestIntersect(box1,
                                 box2))
         {
            drawObb(box1, 1.0f, 0.0f, 1.0f);
            drawObb(box2, 0.0f, 1.0f, 1.0f);

            return false;
         }

         // draw obb's
         drawObb(box1, float(tState1.depth())/ mMaxDepth, 0.0f, 0.08f);
         drawObb(box2, 0.0f, float(tState2.depth())/mMaxDepth, 0.08f);

         // --- RECURSE DOWN TREES --- //
         if(node1->isOfType(pfGeode::getClassType() ))     // If Node1 is Geode
         {
            if(node2->isOfType(pfGeode::getClassType() ))  // and Node 2 is Geode, Test node1 vs node2 trees
            {
               sga::ObbTreeContainer* gset_obb_tree_cont;
               sga::ObbBoundingNode* gset_tree_root;
               pfGeoSet*  child_gset(NULL);
               pfGeode* geode_node = static_cast<pfGeode*>(node2);
               int num_gsets = geode_node->getNumGSets();

               // For all gsets
               for(int g=0;(g<num_gsets) && (ret == false);g++)
               {
                  child_gset = geode_node->getGSet(g);
                  gset_obb_tree_cont = sga::NodeAdapter(child_gset).contHolder().getContainer<sga::ObbTreeContainer>();
                  gset_tree_root = gset_obb_tree_cont->tree().getTree();

                  ret = testNodeObbIntersection(tState1, gset_tree_root, tState2);
               }
            }
            else                                         // Node2 is notGeode --> Test Node2 children vs node1
            {
               for (unsigned child = 0; (child < tState2.numChildren()) && (ret == false) ; child++)
               {
                  gfxASSERT((child < tState2.numChildren()) && "Out of range child access in ...");
                  child_node = tState2.getChild(child);
                  if(child_node != NULL)
                  {
                     tState2.pushChild(child_node);
                     ret = testNodeNodeIntersection(tState1, tState2);
                     tState2.pop();
                  }
               }
            }
         }
         else     // Node1 is not a leaf, test Node1 children against Node2. No leaf-leaf because we don't want to do O(n^2) child-child check
         {
            for (unsigned child = 0; (child < tState1.numChildren()) && (ret == false) ; child++)
            {
               gfxASSERT((child < tState1.numChildren()) && "Out of range child access in ...");
               child_node = tState1.getChild(child);
               if(child_node != NULL)
               {
                  tState1.pushChild(child_node);
                  ret = testNodeNodeIntersection(tState1, tState2);
                  tState1.pop();
               }
            }
         }

         // Fall through to return
         return ret;
      }

      bool testNodeObbIntersection(sga::TrackXform& tState1, sga::ObbBoundingNode* bNode2, sga::TrackXform& tState2)
      {
         bool ret = false;

         pfNode* node1 = tState1.node();
         pfNode* node2 = tState2.node();
         sga::ContainerHolder& cont_holder1 = sga::NodeAdapter(node1).contHolder();
         sga::ContainerHolder& cont_holder2 = sga::NodeAdapter(node2).contHolder();

         if(mMaxDepth < tState1.depth())
            mMaxDepth = tState1.depth();
         if(mMaxDepth < tState2.depth())
            mMaxDepth = tState2.depth();

         std::cout << "no:[" << node1->getName() << "-" << tState1.depth()
                   << "," << node2->getName() << "-" << tState2.depth() << "] ";;

         // Make sure that we have containers on these nodes
         if((cont_holder1.getContainer<sga::ObbNodeContainer>() == NULL) ||
            (cont_holder2.getContainer<sga::ObbNodeContainer>() == NULL))
         {
            std::cout << "ERROR: Trying to intersect nodes w/o obb containers" << std::endl;
            return false;
         }

         gmtl::Matrix xform_mat1 = tState1.getXformMat();
         gmtl::Matrix xform_mat2 = tState2.getXformMat();

         // Test for overlap -- If not overlap, then return now
         gmtl::OOBox box1 = cont_holder1.getContainer<sga::ObbNodeContainer>()->box();
         gmtl::OOBox box2 = bNode2->mBound;

         std::cout << "xform1:\n" << xform_mat1 << "\nxform2:\n" << xform_mat2 << std::endl;

         box1 = xform_mat1 * box1;
         box2 = xform_mat2 * box2;

         bool isect(false);
         isect = gmtl::TestIntersect(box1,box2);

         if(!isect)
         {
            drawObb(box1, 1.0f, 0.0f, 1.0f);
            drawObb(box2, 0.0f, 1.0f, 1.0f);

            std::cout << "\nbox1:\n" << box1 << "\nbox2:\n" << box2 << std::endl;
            return false;
         }

         drawObb(box1, float(tState1.depth())/ mMaxDepth, 0.0f, 0.0f);
         drawObb(box2, 0.0f, float(tState2.depth())/ mMaxDepth, 0.0f);

         // -- RECURSE FURTHER --- //
         if(node1->isOfType(pfGeode::getClassType()))    // If Node1 is a Geode --> Node1 trees vs tree2
         {
            sga::ObbTreeContainer* gset_obb_tree_cont;
            sga::ObbBoundingNode* gset_tree_root;
            pfGeoSet*  child_gset(NULL);
            pfGeode* geode_node = static_cast<pfGeode*>(node1);
            int num_gsets = geode_node->getNumGSets();

            // For all gsets
            for(int g=0;(g<num_gsets) && (ret == false);g++)
            {
               child_gset = geode_node->getGSet(g);
               gset_obb_tree_cont = sga::NodeAdapter(child_gset).contHolder().getContainer<sga::ObbTreeContainer>();
               gset_tree_root = gset_obb_tree_cont->tree().getTree();

               ret = testObbObbIntersection(gset_tree_root, tState1, bNode2, tState2);
            }
         }
         else                                            // Test all Node1.children against the obbTree
         {
            pfNode* child_node(NULL);
            for (unsigned child = 0; (child < tState1.numChildren()) && (ret == false) ; child++)
            {
               gfxASSERT((child < tState1.numChildren()) && "Out of range child access in ...");
               child_node = tState1.getChild(child);
               if(child_node != NULL)
               {
                  tState1.pushChild(child_node);
                  ret = testNodeObbIntersection(tState1, bNode2, tState2);
                  tState1.pop();
               }
            }
         }

         return ret;
      }

      bool testObbObbIntersection(sga::ObbBoundingNode* bNode1, sga::TrackXform& tState1, sga::ObbBoundingNode* bNode2, sga::TrackXform& tState2)
      {
         std::cout << "oo:[" << tState1.depth() << "," << tState2.depth() << " ";

         bool ret = false;

         gmtl::OOBox box1 = bNode1->mBound;
         gmtl::OOBox box2 = bNode2->mBound;

         gmtl::Matrix xform_mat1 = tState1.getXformMat();
         gmtl::Matrix xform_mat2 = tState2.getXformMat();

         box1 = xform_mat1 * box1;
         box2 = xform_mat2 * box2;

         // Test for overlap -- If not overlap, then return now
         if(!gmtl::TestIntersect(box1,
                                 box2))
         {
            drawObb(box1, 1.0f, 0.0f, 1.0f);
            drawObb(box2, 0.0f, 1.0f, 1.0f);
            return false;
         }

         drawObb(box1, float(tState1.depth())/ mMaxDepth, 0.0f, 0.0f);
         drawObb(box2, 0.0f, float(tState2.depth())/ mMaxDepth, 0.0f);

         // --- RECURSE down OBBTree --- //
         if((bNode1->mLeftNode == NULL) && (bNode1->mRightNode == NULL))         // If bNode1 is leaf
         {
            if((bNode2->mLeftNode == NULL) && (bNode2->mRightNode == NULL))      // If bNode2 is leaf
            {
               std::cout << "---- Found isect ----" << std::flush;
               // We have collision
               return true;
            }
            else              // bNode2 has children ==> bNode1 vs bNode2 children
            {
               if(bNode2->mLeftNode != NULL)
                  ret = testObbObbIntersection(bNode1, tState1, bNode2->mLeftNode, tState2);

               if((bNode2->mRightNode != NULL) && (ret == false))
                  ret = testObbObbIntersection(bNode1, tState1, bNode2->mRightNode, tState2);
            }
         }
         else                // bNode1 has children ==> bNode2 vs bNode1 children
         {
            if(bNode1->mLeftNode != NULL)
               ret = testObbObbIntersection(bNode1->mLeftNode, tState1, bNode2, tState2);

            if((bNode1->mRightNode != NULL) && (ret == false))
               ret = testObbObbIntersection(bNode1->mRightNode, tState1, bNode2, tState2);
         }

         return ret;       // Fall through and return what was found
      }

      sga::TrackXform tree1State;
      sga::TrackXform tree2State;

      float  mMaxDepth;     // The max recurse depth we have done

      // Metrics
      long mNumObbTests;
      long mNumObbXforms;
      long mNumFuncCalls;
   };


int PostDrawObbTreeTest(pfTraverser* trav, void* data);
int PreDrawObbTreeTest(pfTraverser* trav, void* data);

pfObbGraphTestApp::pfObbGraphTestApp()
{
   //mFileName = std::string("cow.obj");

   mSceneRoot = NULL;
   /*
   mTestGset = NULL;
   mNumTris = 7;
   */

   mRecurseDepthMin = 0;
   mRecurseDepthMax = 25;

   gTheApp = this;
}

void pfObbGraphTestApp::cmdline(int argc, char *argv[])
{
   if(argc > 1)
   {
      mFileName1 = std::string(argv[1]);
      std::cout << "cmdline: Load file1: " << mFileName1 << std::endl;
   }
   if(argc > 2)
   {
      mFileName2 = std::string(argv[2]);
      std::cout << "cmdline: Load file2: " << mFileName2 << std::endl;
   }
}

void pfObbGraphTestApp::init()
{
   float r,b,g;
   float val(0.0f);

   std::cout << "--------- Color vals ---------\n";

   while(val < 1.0f)
   {
      getColor(val, r,g,b);
      std::cout << val << ": " << r << " " << g << " " << b << std::endl;
      val += 0.05f;
   }

   std::cout << "------------------------------\n";
}

void pfObbGraphTestApp::apiInit()
{
   // Run any tests that we have for pf
   runFrameworkTests();
}

void pfObbGraphTestApp::appKey(unsigned char keyHit, int x, int y)
{
   std::cout << "Hit key: " << keyHit << "x: " << x << "y: " << y << std::endl;

   // Note that we're case-insensitive here (- and _ do the same thing).
  switch ( keyHit )
  {
  case 'r':
     std::cout << "Do random stuff\n";
     break;
  case '1':
     std::cout << "Switch to scene xformer" << std::endl;
     mActiveXformer = mSceneXformer;
     break;
  case '2':
     std::cout << "Switch to obj xformer" << std::endl;
     mActiveXformer = mObjXformer;
     break;
  default:
     break;
  }
}

//: Initialize the scene graph
// Called after pfInit & pfConfig but before apiInit
//
//               mRootNode
//             /         \
//      preXScene
//         |
//  sceneXformDCS
//         |
//    postXScene
//         |
//     sceneRoot    -----------
//       /     \               \
//  mModel1   mModel2Root   mBoundGraphGroup
//              |
//            preX2
//              |
//            objXdcs
//              |
//            postX2
//              |
//            mModel2
//
void pfObbGraphTestApp::initScene()
{
   pfFilePath("/usr/share/Performer/data:/home/users/allenb/Data/Models:/home/users/allenb/Data/Models/collision:/home/allenb/Data/Models:/home/allenb/Data/Models/collision/");

   // Init scene graphy
   mRootNode = new pfGroup;
   mRootNode->setName("mRootNode");
   mSceneRoot = new pfGroup;
   mSceneRoot->setName("mSceneRoot");
   mModel1Root = new pfGroup;
   mModel1Root->setName("mModel1Root");

   // setup xformer scene graph
   pfDCS* preXformerScene = new pfDCS;      preXformerScene->setRot(0.0,-90.0,0.0);
   pfDCS* postXformerScene = new pfDCS;     postXformerScene->setRot(0.0,90.0,0.0);
   mSceneXformerDCS = new pfDCS;

   mRootNode->addChild(preXformerScene);
   preXformerScene->addChild(mSceneXformerDCS);
   mSceneXformerDCS->addChild(postXformerScene);
   postXformerScene->addChild(mSceneRoot);


   if(!mFileName2.empty())
   {
      mModel1 = pfdLoadFile(mFileName2.c_str());
      mModel1->setName("mModel1");
      mModel1Root->addChild(mModel1);
      mSceneRoot->addChild(mModel1Root);
   }
   else
   {
      pfGroup* ring_group = new pfGroup;
      ring_group->setName("ring group");

      pfNode* rings[4];
      for(int r=0;r<4;r++)
         rings[r] = pfdLoadFile("ring.nff");

      const float single_ring_trans(2.5f);      // How much seperation is needed between two rings

      gmtl::Matrix xforms[4];
      pfDCS* dcs_xforms[4];
      pfMatrix temp_pf_mat;

      xforms[1].makeXYZEuler(0.0,90.0,0.0);
      xforms[3].makeXYZEuler(0.0,-90.0,0.0);

      xforms[0].setTrans(0.0, 2*single_ring_trans, 0.0f);
      xforms[1].setTrans(0.0, 1*single_ring_trans, 0.0f);
      xforms[2].setTrans(0.0, 0*single_ring_trans, 0.0f);
      xforms[3].setTrans(0.0, -1*single_ring_trans, 0.0f);

      for(int d=0;d<4;d++)
      {
         dcs_xforms[d] = new pfDCS;
         temp_pf_mat = sga::getPfMatrix<false>(xforms[d]);
         dcs_xforms[d]->setMat(temp_pf_mat);
         dcs_xforms[d]->addChild(rings[d]);
         ring_group->addChild(dcs_xforms[d]);
      }

      mModel1 = ring_group;
      mModel1Root->addChild(mModel1);
      mSceneRoot->addChild(mModel1Root);
   }

   if(!mFileName1.empty())
   {
      mModel2 = pfdLoadFile(mFileName1.c_str());
      mModel2->setName("mModel2");

      // Setup xformer for model 2
      pfDCS* preXformer2 = new pfDCS;      preXformer2->setRot(0.0,-90.0,0.0);  preXformer2->setName("preX2");
      pfDCS* postXformer2 = new pfDCS;     postXformer2->setRot(0.0,90.0,0.0);  postXformer2->setName("postX2");
      mObjXformerDCS = new pfDCS;
      mObjXformerDCS->setName("objXformer");
      mModel2Root = new pfGroup;
      mModel2Root->setName("mModel2Root");

      mModel2Root->addChild(preXformer2);
      preXformer2->addChild(mObjXformerDCS);
      mObjXformerDCS->addChild(postXformer2);
      postXformer2->addChild(mModel2);

      mSceneRoot->addChild(mModel2Root);
   }
   else
   {
      mModel2 = NULL;
   }

   // --- Initial traversals --- //
   sga::PfTraverser output_trav;
   printPfNodeInfo<sga::PfTraverser> node_printer;
   std::cout << "About to traverse.....\n" << std::flush;
   //output_trav.traverse(mSceneRoot, printPfNodeInfo(),NullTrav());
   output_trav.traverse(mSceneRoot,
                        member_func1(&node_printer, &printPfNodeInfo<sga::PfTraverser>::pre),
                        member_func1(&node_printer, &printPfNodeInfo<sga::PfTraverser>::post));

   // Create Obb graph
   sga::createObbGraph(mSceneRoot);

   // --- Draw Callback Node --- //
   mBoundGraphGroup = new pfGroup;
   pfSphere* obb_node_bound = new pfSphere();
   obb_node_bound->center.set(0,0,0);
   obb_node_bound->radius = 100.0f;
   mBoundGraphGroup->setTravFuncs(PFTRAV_DRAW, PreDrawObbTreeTest, PostDrawObbTreeTest);
   mSceneRoot->addChild(mBoundGraphGroup);
   mBoundGraphGroup->setBound(obb_node_bound,PFBOUND_STATIC);
}

void pfObbGraphTestApp::preFrame()
{
   //std::cout << "preFrame." << std::endl;

   // --- Test for intersection --- //
   /*
   bool isect_test(false);
   ObbIntersectTraverser isect_tester;

   if((mModel1Root != NULL) && (mModel2Root != NULL))
   {
      isect_test = isect_tester.testIntersection(mModel1Root, mModel2Root);

      std::cout << "Tested isect: " << isect_test << std::endl;

      if(isect_test == true)
         pfuWidgetLabel(mHitStatusPanel, "Hit: TRUE");
      else
         pfuWidgetLabel(mHitStatusPanel, "Hit: false");
   }
   */

}

std::vector<pfuWidget*> pfObbGraphTestApp::createPanel(pfuPanel* panel, int minPanelId, int xOrigin, int yOrigin, int xSize, int ySize)
{
    int x, y, yTop;
    //pfuWidget *wid;
    std::vector<pfuWidget*> new_widgets;

    // Compute starting point
    x = (int)xOrigin;
    yTop = (int)(yOrigin + ySize);
    y = (int)yTop - PFUGUI_BUTTON_YINC;      // To get lower left corner of first button


    // ------ CREATE WIDGET ------------- //

   // ----- Recurse depth: Min ------- //
    mRecurseDepthMinWidgetId = ++minPanelId;
    mRecurseDepthMinWidget = pfuNewWidget(panel, PFUGUI_SLIDER, mRecurseDepthMinWidgetId);
    new_widgets.push_back(mRecurseDepthMinWidget);
    pfuWidgetDim(mRecurseDepthMinWidget,  x,  y,  PFUGUI_SLIDER_SMALL_XSIZE, PFUGUI_SLIDER_YSIZE);
    pfuWidgetLabel(mRecurseDepthMinWidget, "Min recurse");
    pfuWidgetRange(mRecurseDepthMinWidget, PFUGUI_SLIDER, 0.0, 25.0, 0.0);
    x += PFUGUI_SLIDER_SMALL_XINC;

    // ----- Recurse depth: Max ------- //
    mRecurseDepthMaxWidgetId = ++minPanelId;
    mRecurseDepthMaxWidget = pfuNewWidget(panel, PFUGUI_SLIDER, mRecurseDepthMaxWidgetId);
    new_widgets.push_back(mRecurseDepthMaxWidget);
    pfuWidgetDim(mRecurseDepthMaxWidget,  x,  y,  PFUGUI_SLIDER_SMALL_XSIZE, PFUGUI_SLIDER_YSIZE);
    pfuWidgetLabel(mRecurseDepthMaxWidget, "Max recurse");
    pfuWidgetRange(mRecurseDepthMaxWidget, PFUGUI_SLIDER, 0.0, 25.0, 25.0);
    x += PFUGUI_SLIDER_SMALL_XINC;

    // ------ Hit status panel ----- //
    mHitStatusPanel = pfuNewWidget(panel, PFUGUI_MESSAGE, ++minPanelId);
    new_widgets.push_back(mHitStatusPanel);
    pfuWidgetDim(mHitStatusPanel, x, y,  PFUGUI_BUTTON_MED_XSIZE, PFUGUI_SLIDER_YSIZE);
    pfuWidgetLabel(mHitStatusPanel, "Hit: false");
    x += PFUGUI_BUTTON_MED_XINC;

    x = (int)xOrigin;
    y -= PFUGUI_SLIDER_YINC;

    return new_widgets;
}

void pfObbGraphTestApp::panelWidgetAction(pfuWidget* widget)
{
  int wid_id = pfuGetWidgetId(widget);

   if((wid_id == mRecurseDepthMaxWidgetId) || (wid_id == mRecurseDepthMinWidgetId))
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
void pfObbGraphTestApp::runFrameworkTests()
{
   //sgaTest::PfTriangleListAdapterTest::testIt();

}


void pfObbGraphTestApp::drawTest()
{
   //sga::TrackXform<sga::PfTraverser> draw_obb_graph_trav;
   //sga::TrackXform<sga::PfTravState> draw_obb_graph_trav_state;
   sga::PfTraverser draw_obb_graph_trav(new sga::TrackXform());

   DrawObbGraph  draw_obb;
   draw_obb.mMaxRecurse = this->mRecurseDepthMax;
   draw_obb.mMinRecurse = this->mRecurseDepthMin;

   std::cout << "--------- drawing obb --------" << std::endl;
   draw_obb_graph_trav.traverse(this->mSceneRoot,
                     member_func1(&draw_obb, &DrawObbGraph::pre),
                     member_func1(&draw_obb, &DrawObbGraph::post));

   /*
   std::cout << "--------- testing isect -------" << std::endl;
   // Isect test
   bool isect_test(false);
   ObbIntersectTraverser isect_tester;

   if((mModel1Root != NULL) && (mModel2Root != NULL))
   {
      isect_test = isect_tester.testIntersection(mModel1Root, mModel2Root);

      std::cout << "Tested isect: " << isect_test << std::endl;

      if(isect_test == true)
         pfuWidgetLabel(mHitStatusPanel, "Hit: TRUE");
      else
         pfuWidgetLabel(mHitStatusPanel, "Hit: false");
   }
   */

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

   void getColor(const float val, float& r, float& g, float& b)
   {
      r = ((val < 0.5f) ? (1.0f-(2*val)): 0.0f);
      g = ((val < 0.5f) ? (0.0f+(2*val)): (1.0f-(2*(val-0.5))) );
      b = ((val > 0.5f) ? (2*(val-0.5)) : 0.0f);
   }

   void drawObb(const gmtl::OOBox &obb, float colorScale)
   {
      float r,g,b;
      getColor(colorScale, r,g,b);
      drawObb(obb,r, g, b);
   }

   void drawObb(const gmtl::OOBox& obb, float r, float g, float b)
   {
      Point3 verts[8];
      obb.getVerts(verts);

      glPushAttrib(GL_LINE_BIT);
      //glColor3f(1.0f,0.1f,0.1f);

      glDisable(GL_LIGHTING);

      glColor3f(r,g,b);
      glLineWidth(2.0f);
      glBegin(GL_LINES);
      {
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



   sga::Traverser::TravStatus DrawObbGraph::pre(sga::PfTraverser* trav)
   {
         cur_node_depth++;
         if(cur_node_depth > max_node_depth)
            max_node_depth = cur_node_depth;

         return sga::Traverser::CONT;
   }

   sga::Traverser::TravStatus DrawObbGraph::post(sga::PfTraverser* trav)
   {
      const bool use_gl_mat(true);
      // Push matrix
      sga::TrackXform* xform_trav_state = dynamic_cast<sga::TrackXform*>(trav->travState());
      gfxASSERT(xform_trav_state != NULL);
      gmtl::Matrix xform_mat = xform_trav_state->getXformMat();

      if(use_gl_mat)
      {
         glPushMatrix();                           // Now group xform is saved and is on top
         glMultMatrixf(xform_mat.floatPtr());
      }

      std::cout << "drawNode: " << xform_trav_state->node()->getName() << std::endl;
      std::cout << "xform:" << xform_mat << std::endl;

      // PFGEODE NODE
      // - Draw local bbox
      // - Draw trees for each gset
      if(trav->travState()->node()->isOfType(pfGeode::getClassType()))
      {
         pfGeode* geode_node = static_cast<pfGeode*>(trav->travState()->node());
         pfGeoSet* gset(NULL);
         sga::NodeAdapter geode_node_adapter(geode_node);

         ///*
         if(geode_node_adapter.contHolder().getContainer<sga::ObbNodeContainer>() != NULL)
         {
            // Draw geode OBB
            if((cur_node_depth >= mMinRecurse) && (cur_node_depth <= mMaxRecurse))
            {
               gmtl::OOBox draw_box = geode_node_adapter.contHolder().getContainer<sga::ObbNodeContainer>()->box();
               if(!use_gl_mat)
                  draw_box = xform_mat * draw_box;
               drawObb(draw_box,cur_node_depth/max_node_depth);
            }

            for(int g=0;g<geode_node->getNumGSets();g++)
            {
               gset = geode_node->getGSet(g);
               sga::NodeAdapter gset_adapter(gset);

               if(gset_adapter.contHolder().getContainer<sga::ObbTreeContainer>() != NULL)
               {
                  gmtl::Matrix old_mat = mCurObbTreeXform;
                  if(!use_gl_mat)
                     mCurObbTreeXform = xform_mat;    // Store xform may for drawObbTree
                  drawObbTree(gset_adapter.contHolder().getContainer<sga::ObbTreeContainer>()->tree());
                  if(!use_gl_mat)
                     mCurObbTreeXform = old_mat;
               }
            }
         }
         //*/
      }
      else // if(trav->node()->isOfType(pfGroup::getClassType()))
      {
         //sga::createObbContainerForGroupNode(static_cast<pfGroup*>(trav->node()));
         sga::NodeAdapter node_adapter(trav->travState()->node());
         /*
         sga::ObbNodeContainer* obb_node_cont;
         obb_node_cont = node_adapter.contHolder().getContainer<int> ();
         */
         ///*
         if((node_adapter.contHolder()).getContainer<sga::ObbNodeContainer>() != NULL)
         {
            if((cur_node_depth >= mMinRecurse) && (cur_node_depth <= mMaxRecurse))
            {
               gmtl::OOBox draw_box = node_adapter.contHolder().getContainer<sga::ObbNodeContainer>()->box();
               if(!use_gl_mat)
                  draw_box = xform_mat * draw_box;
               drawObb(draw_box,1.0f);
            }

         }
         //*/

      }

      cur_node_depth--;

      // Pop GL matrix
      if(use_gl_mat)
         glPopMatrix();          // Now group xform is back on top (like when we came in)

      return sga::Traverser::CONT;
   }

};



