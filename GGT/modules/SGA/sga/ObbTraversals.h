/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ObbTraversals.h,v $
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
#ifndef _SGA_OBB_TRAVERSALS_H_
#define _SGA_OBB_TRAVERSALS_H_

#include <SGA/Traverser.h>
#include <SGA/ObbBoundingTreeTravFuncs.h>
#include <SGA/ObbBoundingTree.h>
#include <SGA/ObbNodeContainer.h>
#include <SGA/ObbTreeContainer.h>

#include <SGA/PfNodeAdapters.h>

#include <Performer/pf/pfGroup.h>
#include <Performer/pf/pfGeode.h>
#include <Performer/pr/pfGeoSet.h>


namespace sga
{
   // Traverse the scene rooted at base_node
   // and create an obbGraph for the entire thing
   void createObbGraph(pfNode* base_node);

   // Create bounding node that covers all children.
   // ASSERT: Each child should already have a group node
   void createObbContainerForGroupNode(pfGroup* groupNode);

   // Create boundign node that covers all gset in geode
   // ASSERT: Each gset should already have an ObbTree assigned to it
   void createObbContainerForGeodeNode(pfGeode* geodeNode);

   // Create an ObbTree for the given geoset
   void createObbContainerForGset(pfGeoSet* gset);

//: Traverse through an ObbTree and call function objects on each node
// Recurse through the tree and call the function objects
// for_each.  Apply a function to every node
template <class _ObbNodeFunctionPre,
          class _ObbNodeFunctionPost >
void travObbTree(ObbBoundingNode* node,
                      _ObbNodeFunctionPre _fPre,
                      _ObbNodeFunctionPost _fPost)
{
   _fPre(node);
   if(node->mLeftNode != NULL)
   {
      travObbTree(node->mLeftNode, _fPre, _fPost);
   }
   if(node->mRightNode != NULL)
   {
      travObbTree(node->mRightNode, _fPre, _fPost);
   }
   _fPost(node);

   return;
   /*
   for ( ; __first != __last; ++__first)
    __f(*__first);
  return __f;
  */
}

};    // namespace sga

#endif
