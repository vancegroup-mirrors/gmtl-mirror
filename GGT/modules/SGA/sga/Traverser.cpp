/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Traverser.cpp,v $
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
#include <SGA/Traverser.h>

#include <Performer/pf/pfSCS.h>
#include <Performer/pf/pfNode.h>
#include <Performer/pf/pfGroup.h>
#include <Performer/pr/pfLinMath.h>


namespace sga
{

// ------------------------------------------------------------ //
// -------------------------- TrackXform ---------------------- //
// ------------------------------------------------------------ //
TrackXform::TrackXform()
{
   gmtl::Matrix ident;
   ident.makeIdent();
   mMatrixStack.push_back(ident);
}

void TrackXform::enterTrav()
{
   // Call base class first
   PfTravState::enterTrav();

   // Update matrix based on type of node
   if (node()->isOfType( pfSCS::getClassType()))
   {
       pfMatrix   mat;
       ((pfSCS*)node())->getMat(mat);

       gmtl::Matrix new_mat = sga::getMatrix<false>(mat);

       if(mMatrixStack.size() > 1)           // If is is not the identity
         new_mat = getXformMat() * new_mat;

       pushMatrix(new_mat);
   }
   /*
   else if (pfIsOfType(node, pfGetDoubleSCSClassType()))
   {
       pfMatrix4d    mat4d;
       pfMatrix mat;

       pfGetDoubleSCSMat((pfDoubleSCS *)trav->node, mat4d);

       PFCOPY_MAT(mat, mat4d);

       pfPushMStack(trav->mstack);
       pfPreMultMStack(trav->mstack, mat);
       needPop = 1;
   }
   */
}

void TrackXform::exitTrav()
{
   // Check for pop
   if(node()->isOfType(pfSCS::getClassType()))
   {
      popMatrix();
   }

   // Call base class
   PfTravState::enterTrav();
}

const gmtl::Matrix& TrackXform::getXformMat()
{
   //gfxASSERT(!mMatrixStack.empty());

   if(mMatrixStack.empty())
      return gmtl::Matrix::IDENT;
   else
      return mMatrixStack[mMatrixStack.size()-1];
}

gmtl::Matrix TrackXform::getXformMatInv()
{
   gmtl::Matrix mat_inv;
   gmtl::Matrix cur_mat = getXformMat();
   mat_inv.invert(cur_mat);
   return mat_inv;
}

void TrackXform::popMatrix()
{
   mMatrixStack.pop_back();
}

void TrackXform::pushMatrix(gmtl::Matrix& mat)
{
   mMatrixStack.push_back(mat);
}


};
