/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ObbTraversals.cpp,v $
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
#include <SGA/ObbTraversals.h>
#include <SGA/PfTriangleListAdapter.h>
#include <SGA/TravFuncs.h>
#include <GMTL/Containment.h>

namespace
{
   struct constructObbGraph
   {
     constructObbGraph() {;}
     sga::Traverser::TravStatus pre(sga::PfTraverser* trav);
     sga::Traverser::TravStatus post(sga::PfTraverser* trav);
   };
};

namespace sga
{


   void createObbGraph(pfNode* base_node)
   {
      sga::PfTraverser create_obb_graph_trav;      // Use default trav state
      constructObbGraph  construct_obb;
      create_obb_graph_trav.traverse(base_node,
                        member_func1(&construct_obb, &constructObbGraph::pre),
                        member_func1(&construct_obb, &constructObbGraph::post));
   }

   // Create bounding node that covers all children.
   // ASSERT: Each child should already have a group node
   void createObbContainerForGroupNode(pfGroup* groupNode)
   {
      std::cout << "Creating box for group node: " << (void*)groupNode << std::endl;

      sga::NodeAdapter node_adapter(groupNode);
      sga::ObbNodeContainer* obb_node_cont =
               node_adapter.contHolder().autoGetContainer<sga::ObbNodeContainer>();
      pfNode*  child_node(NULL);

      gmtl::OOBox new_box;                               // new box for this node
      int num_children = groupNode->getNumChildren();

      std::cout << "   NumChildren:" << num_children << std::endl;

      // If we have children, then set the first box to the first child's box
      ///*
      if(num_children > 0)
      {
         child_node = groupNode->getChild(0);
         new_box = sga::NodeAdapter(child_node).contHolder().getContainer<sga::ObbNodeContainer>()->box();
      }
      //*/

      // For the rest of the children
      for(unsigned child=1; child<num_children; child++)
      {
         gfxASSERT(child < groupNode->getNumChildren());
         child_node = groupNode->getChild(child);
         gfxASSERT(child_node != NULL);
         gfxASSERT(sga::NodeAdapter(child_node).contHolder().autoGetContainer<sga::ObbNodeContainer>() != NULL);
         gmtl::computeContainment(new_box,
                                  new_box,
                                  sga::NodeAdapter(child_node).contHolder().autoGetContainer<sga::ObbNodeContainer>()->box(),false);
      }

      obb_node_cont->box() = new_box;     // Assign the new box
   }

   // Create boundign node that covers all gset in geode
   // ASSERT: Each gset should already have an ObbTree assigned to it
   void createObbContainerForGeodeNode(pfGeode* geodeNode)
   {
      std::cout << "Creating box for geode node: " << (void*)geodeNode << std::endl;

      sga::NodeAdapter node_adapter(geodeNode);
      sga::ObbNodeContainer* obb_node_cont =
               node_adapter.contHolder().autoGetContainer<sga::ObbNodeContainer>();
      pfGeoSet*  gset(NULL);

      // Set bound to nothing
      gmtl::OOBox new_box;
      int num_gsets = geodeNode->getNumGSets();

      // If have gsets, initialize box to the first gset's size
      // XXX: Could get much better fit by writing a computeContainment(box, listOfBoxes) function
      /*
      if(num_gsets > 0)
      {
         gset = geodeNode->getGSet(0);
         gfxASSERT(sga::NodeAdapter(0).contHolder().getContainer<sga::ObbTreeContainer>() != NULL);
         new_box = sga::NodeAdapter(0).contHolder().getContainer<sga::ObbTreeContainer>()->tree().treeBox();
      }
      */

      // For the rest of the gsets
      for(int g=0;g<num_gsets;g++)
      {
         gset = geodeNode->getGSet(g);

         // Create ObbTree
         createObbContainerForGset(gset);

         // Extend parent bound
         gfxASSERT(sga::NodeAdapter(gset).contHolder().getContainer<sga::ObbTreeContainer>() != NULL);
         gmtl::computeContainment(new_box, new_box,
                        sga::NodeAdapter(gset).contHolder().getContainer<sga::ObbTreeContainer>()->tree().treeBox(),
                                  false);
      }

      obb_node_cont->box() = new_box;     // Assign the new box
   }

   // Create an ObbTree for the given geoset
   void createObbContainerForGset(pfGeoSet* gset)
   {
      std::cout << "Creating box for gset node: " << (void*)gset << std::endl;
      sga::NodeAdapter node_adapter(gset);
      sga::ObbTreeContainer* obb_tree_cont =
               node_adapter.contHolder().autoGetContainer<sga::ObbTreeContainer>();

      // XXX: Memory leak here. Should do something about deleting old version of the stuff
      obb_tree_cont->tree().setTriAdapter( new sga::PfTriangleListAdapter(gset));
      obb_tree_cont->tree().createBoundingTree();
   }

};

// --------------- LOCAL HELPER FUNCTIONS ---------------- //
namespace
{
   sga::Traverser::TravStatus constructObbGraph::pre(sga::PfTraverser* trav)
   {
      std::cout << "constructObbGraph::pre: ";

      for (unsigned d=0;d<trav->travState()->depth();d++)
      { std::cout << "  "; }

      std::cout << trav->travState()->depth() << ": [";
      std::cout << trav->travState()->node()->getName() << "]  type: " << trav->travState()->node()->getType()->getName() << std::endl << std::flush;

      return sga::Traverser::CONT;
   }

   sga::Traverser::TravStatus constructObbGraph::post(sga::PfTraverser* trav)
   {
      std::cout << "constructObbGraph::post: ";

      // Do the work

      // If Geode
      // - For each gset
      //   - Construct ObbTree and assign it
      // - Create encompassing BBox for geode
      // Else
      // - Create box that covers all children
      if(trav->travState()->node()->isOfType(pfGeode::getClassType()))
      {
         sga::createObbContainerForGeodeNode(static_cast<pfGeode*>(trav->travState()->node()));
      }
      else if(trav->travState()->node()->isOfType(pfGroup::getClassType()))
      {
         sga::createObbContainerForGroupNode(static_cast<pfGroup*>(trav->travState()->node()));
      }

      return sga::Traverser::CONT;
   }

}
