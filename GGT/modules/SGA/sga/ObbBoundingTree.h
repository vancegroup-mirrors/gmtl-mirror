/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ObbBoundingTree.h,v $
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
#ifndef _OBB_BOUNDING_TREE_H_
#define _OBB_BOUNDING_TREE_H_

#include <gfxConfig.h>
#include <SGA/TriangleList.h>
#include <GMTL/Point3.h>
#include <GMTL/OOBox.h>

namespace sga
{

/**
 * ObbBoundingNode represents a node in an ObbBoundingTree.
 *
 * It is a single node in the tree.  It may be an internal
 * node in which case it points to child nodes, or it may be a leaf node.
 *
 * If mLeftNode && mRightNode == NULL, then this node is a leaf
 */
class ObbBoundingNode
{
public:
   ObbBoundingNode() : mTriIndex(0), mLeftNode(NULL), mRightNode(NULL)
   {;}

public:
   gmtl::OOBox       mBound;        // Bounding box for the current node
   unsigned          mTriIndex;     // Tri index (if we have a triangle)
   ObbBoundingNode*  mLeftNode;     // left child
   ObbBoundingNode*  mRightNode;
};

class ObbBoundingTree
{
public:
   ObbBoundingTree() : mTris(NULL), mRootBV(NULL)
   {;}

   void createBoundingTree();

   void setTriAdapter(TriangleList* tris)
   {
      mTris = tris;
   }

   ObbBoundingNode* getTree()
   {
      return mRootBV;
   }

   // just return the encompassing box
   gmtl::OOBox treeBox()
   {
      if(mRootBV != NULL)
      { return mRootBV->mBound; }
      else
      {  gmtl::OOBox box;
         return box;
      }
   }

protected:
   // Recursively create a bounding tree using the local triangle list
   // and store the base in mRootBV
   //
   ObbBoundingNode* createTree(std::vector<unsigned>& tris, const std::vector<gmtl::Point3>& triCenters);

   /**
    * Partition the triangle
    * @post triangles [0,splitIndex) are all less than [splitIndex,size())
    *       note; This means that tris[splitIndex] belongs in upper half
    * @param splitIndex The vector index (0-based) of the element position that should be the partition point.
    * @param tris
    * @param triCenters
    * @param sortDir
    */
   void partitionTriangles(unsigned splitIndex, std::vector<unsigned>& tris,
                           const std::vector<gmtl::Point3>& triCenters, gmtl::Vec3 sortDir);

protected:
   TriangleList*     mTris;
   ObbBoundingNode*  mRootBV;

   // Cached values
};

};

#endif
