/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: PfTriangleListAdapter.h,v $
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
#ifndef _PF_TRIANGLE_LIST_H_
#define _PF_TRIANGLE_LIST_H_

#include <GMTL/Point3.h>
#include <GMTL/Tri.h>
#include <SGA/TriangleList.h>
#include <SGA/PfHelperFuncs.h>

#include <Performer/pr/pfGeoSet.h>

namespace sga
{

class PfTriangleListAdapter : public TriangleList
{
public:
   PfTriangleListAdapter(pfGeoSet* gset) : mGeoSet(gset)
   {;}

   inline virtual const gmtl::Tri tri(unsigned index);
   inline virtual unsigned size();
   inline void setGeoSet(pfGeoSet* gset)
   { mGeoSet = gset; }

protected:
   pfGeoSet*   mGeoSet;
};

inline unsigned PfTriangleListAdapter::size()
{
   unsigned num_pf_prims = mGeoSet->getNumPrims();
   int      pf_prim_type = mGeoSet->getPrimType();

   if(pf_prim_type == PFGS_TRIS)
   {
      return num_pf_prims;
   }
   else if(pf_prim_type == PFGS_TRISTRIPS)
   {
      unsigned total(0);
      for(unsigned i=0;i<num_pf_prims;i++)
      { total += (mGeoSet->getPrimLength(i) - 2); }
      return total;
   }
   /*
   else if(pf_prim_type == PFGS_TRIFANS)
   {
   }
   else if(pf_prim_type == PFGS_FLAT_TRISTRIPS)
   {
   }
   else if(pf_prim_type == PFGS_FLAT_TRIFANS)
   {
   }
   */
   else
   {
      std::cout << "pfTriangleListAdapter::size() trying to use unsupported prim type." << std::endl;
   }
   return 0;
}

inline const gmtl::Tri PfTriangleListAdapter::tri(unsigned index)
{
   gfxASSERT(index < size());

   //unsigned num_pf_prims = mGeoSet->getNumPrims();
   int      pf_prim_type = mGeoSet->getPrimType();
   //int*     pf_prim_lens = mGeoSet->getPrimLengths();
   //int      pf_vert_bind = mGeoSet->getAttrBind(PFGS_COORD3);
   gfxASSERT(mGeoSet->getAttrBind(PFGS_COORD3) == PFGS_PER_VERTEX);
   pfVec3*  pf_v(NULL);          // Vertices
   ushort*  pf_vi(NULL);         // Vertex indicies
   mGeoSet->getAttrLists(PFGS_COORD3, (void**)&pf_v, &pf_vi);
   pfVec3   pf_v0, pf_v1, pf_v2;

   if(pf_prim_type == PFGS_TRIS)                   // ----- SET OF TRIS ----- //
   {
      if(pf_vi == NULL)
      {
         pf_v0 = pf_v[(3*index)+0];
         pf_v1 = pf_v[(3*index)+1];
         pf_v2 = pf_v[(3*index)+2];
         return gmtl::Tri( getPoint3(pf_v0),getPoint3(pf_v1), getPoint3(pf_v2));
      }
      else
      {
         pf_v0 = pf_v[pf_vi[(3*index)+0]];
         pf_v1 = pf_v[pf_vi[(3*index)+1]];
         pf_v2 = pf_v[pf_vi[(3*index)+2]];
         return gmtl::Tri( getPoint3(pf_v0),getPoint3(pf_v1), getPoint3(pf_v2));
      }
   }
   else if(pf_prim_type == PFGS_TRISTRIPS)         // ----- TRISTRIPS ----- //
   {
      // tri_index_offset - Running triangle index offset of the head of the current strip
      //                    ie. If this is 4, then it means triangle 4 is at the head of
      //                        the current tri-strip primitive (cur_strip)
      // cur_strip   - This is the current tri strip that we are examining
      // vert_offset - This is the running index of the vertex that is at the head
      //               of the current tristrip.  ie. (vert_offset == 4) ==> cur_strip starts with vert(4)
      unsigned tri_index_offset(0);
      unsigned vert_offset(0);
      unsigned cur_strip(0);

      // WHILE: (tri_index + num tris in cur strip) <= triangleIndexWeWant
      while((tri_index_offset+(mGeoSet->getPrimLength(cur_strip) -2)) <= index)
      {
         tri_index_offset += (mGeoSet->getPrimLength(cur_strip) -2);    // Add on num tris we skipped over
         vert_offset += mGeoSet->getPrimLength(cur_strip);              // Add on num verts in that strip
         cur_strip++;                                                   // Goto next strip
      }

      // ASSERT: vert_offset points to first vert of current prim
      // ASSERT: prim_offset is the total number of previous triangles
      // ASSERT: ret_tri_index is the index of the triangle we want from this strip
      unsigned ret_tri_index = index-tri_index_offset;      // The index of the strip tri to return
      //gfxASSERT(ret_tri_index >= 0);
      unsigned v0_index = vert_offset+ret_tri_index;        // v1 = headStripVert + tri_we_want

      if(pf_vi == NULL)
      {
         pf_v0 = pf_v[v0_index+0];
         pf_v1 = pf_v[v0_index+1];
         pf_v2 = pf_v[v0_index+2];
         return gmtl::Tri( getPoint3(pf_v0),getPoint3(pf_v1), getPoint3(pf_v2));
      }
      else
      {
         pf_v0 = pf_v[pf_vi[v0_index+0]];
         pf_v1 = pf_v[pf_vi[v0_index+1]];
         pf_v2 = pf_v[pf_vi[v0_index+2]];
         return gmtl::Tri( getPoint3(pf_v0),getPoint3(pf_v1), getPoint3(pf_v2));
      }
   }
   /*
   else if(pf_prim_type == PFGS_TRIFANS)
   {
   }
   else if(pf_prim_type == PFGS_FLAT_TRISTRIPS)
   {
   }
   else if(pf_prim_type == PFGS_FLAT_TRIFANS)
   {
   }
   */
   else
   {
      std::cout << "pfTriangleListAdapter::tri() trying to use unsupported prim type." << std::endl;
   }

   return gmtl::Tri(gmtl::Vec3::ZERO, gmtl::Vec3::ZERO, gmtl::Vec3::ZERO);
}



};

#endif
