/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ObbBoundingTree.cpp,v $
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
#include <gfxConfig.h>

#include <SGA/ObbBoundingTree.h>

#include <GMTL/Containment.h>
#include <GMTL/Comparitors.h>

#include <algorithm>


namespace sga
{

void ObbBoundingTree::createBoundingTree()
{
   if(mTris == NULL)
   {
      std::cerr << "ObbBoundingTree::createBoundingTree: Called with NULL triangle adapter.\n";
      gfxASSERT(false);
      return;
   }

   // Create tri index vector
   std::vector<unsigned> tri_indicies(mTris->size());
   for(unsigned i=0;i<tri_indicies.size();i++)
   {   tri_indicies[i] = i; }

   // Create triCenter vector
   std::vector<gmtl::Point3> tri_centers;
   for(unsigned i=0;i<mTris->size();i++)
   {   tri_centers.push_back(mTris->tri(i).center()); }

   mRootBV = createTree(tri_indicies, tri_centers);
}

ObbBoundingNode* ObbBoundingTree::createTree(std::vector<unsigned>& tris, const std::vector<gmtl::Point3>& triCenters)
{
   // Create the new node
   ObbBoundingNode* obb_node = new ObbBoundingNode;

   //unsigned tris_size = tris.size();
   //unsigned triCenters_size = triCenters.size();

   // Compute bound of all tris that we have
   // XXX: This should be replaced with something faster in the future
   std::vector<gmtl::Point3> tri_points;
   gmtl::Tri           cur_tri;
   unsigned    tri_to_get;
   for(unsigned t=0;t<tris.size();t++)
   {
      tri_to_get = tris[t];
      cur_tri = mTris->tri(tri_to_get);
      tri_points.push_back(cur_tri[0]); tri_points.push_back(cur_tri[1]); tri_points.push_back(cur_tri[2]);
   }

   gmtl::computeContainment(obb_node->mBound, tri_points);

   // If have only 1 triangle
   // - Return node bounding that triangle
   if(tris.size() == 1)
   {
      obb_node->mTriIndex = tris[0];
      obb_node->mLeftNode = NULL;
      obb_node->mRightNode = NULL;
      return obb_node;                       // BASE CASE: Recursive base case is 1 triangle
   }

   // Sort the points based on an axis
   // Find major axis
   float* half_lens;
   int major_axis_index(0);
   half_lens = obb_node->mBound.halfLens();

   if(half_lens[0] > half_lens[1])
   {
      if(half_lens[0] > half_lens[2])
         major_axis_index = 0;
      else
         major_axis_index = 2;
   } else {
      if(half_lens[1] > half_lens[2])
         major_axis_index = 1;
      else
         major_axis_index = 2;
   }

   unsigned midpoint_index = tris.size()/2;              // So we have 2 groups of points [0,midpoint_index) and [midpoint_index,size)
   partitionTriangles(midpoint_index, tris, triCenters, obb_node->mBound.axis(major_axis_index));

   // XXX: Should replace this with a better method in future
   //      May mean rewriting functions to use std::vector<unsigned>::iterators or something similar
   // Creates copies of tris to pass to recursive function
   std::vector<unsigned> left_tris(tris.begin(), tris.begin()+midpoint_index);
   std::vector<unsigned> right_tris(tris.begin()+midpoint_index, tris.end());

   // RECURSE: Compute left child
   obb_node->mLeftNode = createTree(left_tris,triCenters);

   // RECURSE: Compute right child
   obb_node->mRightNode = createTree(right_tris,triCenters);

   return obb_node;
}

void ObbBoundingTree::partitionTriangles(unsigned splitIndex, std::vector<unsigned>& tris, const std::vector<gmtl::Point3>& triCenters, gmtl::Vec3 sortDir)
{
   //unsigned tris_size = tris.size();
   //unsigned triCenters_size = triCenters.size();

   // Make sure that we actually have all the indices that we need to slit
   gfxASSERT((splitIndex < tris.size()) && (triCenters.size() >= tris.size()));

   gmtl::CompareIndexPointProjections  tri_sorter;
   tri_sorter.points = &triCenters;
   tri_sorter.sortDir = sortDir;

   // sort and split based on projection information
   std::nth_element(tris.begin(), tris.begin()+splitIndex, tris.end(), tri_sorter);
}

};
