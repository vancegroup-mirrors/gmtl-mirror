/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ObbNodeContainer.h,v $
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
#ifndef _OBB_NODE_CONTAINER_H_
#define _OBB_NODE_CONTAINER_H_

#include <SGA/ContainerBase.h>
#include <SGA/ContainerTypes.h>
#include <GMTL/OOBox.h>

namespace sga
{

   class ObbNodeContainer : public ContainerBase
   {
   public:
      enum { TYPE = sga::OBB_NODE_TYPE };

      ObbNodeContainer()
      {
         setType(sga::OBB_NODE_TYPE);
         mBox.ident();                 // Initialize box to identity
      }

      gmtl::OOBox& box()
      { return mBox; }

      const gmtl::OOBox& box() const
      { return mBox; }

   private:
      gmtl::OOBox mBox;
   };

};

#endif
