/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: PfNodeAdapters.h,v $
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
#ifndef _SGA_PERFORMER_NODE_ADAPTERS_H_
#define _SGA_PERFORMER_NODE_ADAPTERS_H_

#include <Performer/pf/pfNode.h>
#include <SGA/ContainerHolder.h>

namespace sga
{

   class NodeAdapter
   {
   public:
      NodeAdapter(pfObject* pf_node)
      {
         mNode = pf_node;
         findContainerHolder();
      }

      ContainerHolder& contHolder() const
      { return *mContHolder; }

   protected:
      // Makes sure that the node has a container holder
      // Assigns it to local variable for faster access
      void findContainerHolder()
      {
         if(mSgaSlotId < 0)
         {
            mSgaSlotId = pfObject::getNamedUserDataSlot("SGA_ContainerHolder");
            std::cout << "sga::NodeAdapter::mSgaSlotId: set to --> " << mSgaSlotId << std::endl;
         }
         void* user_data = mNode->getUserData(mSgaSlotId);

         if(user_data == NULL)      // XXX: I am just hoping that it inits to NULL
         {
            mContHolder = new ContainerHolder;
            mNode->setUserData(mSgaSlotId, (void*)mContHolder);
         }
         else
         {
            mContHolder = static_cast<ContainerHolder*>(user_data);
         }
      }

   protected:
      pfObject*           mNode;
      ContainerHolder*  mContHolder;

      static int        mSgaSlotId;
   };

int NodeAdapter::mSgaSlotId = -1;

};

#endif
