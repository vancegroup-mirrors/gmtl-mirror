/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ContainerHolder.h,v $
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
#ifndef _CONTAINER_HOLDER_H_
#define _CONTAINER_HOLDER_H_

#include <gfxConfig.h>
#include <SGA/ContainerBase.h>
#include <hash_map>
#include <typeinfo>

namespace sga
{

   class ContainerHolder
   {
   public:

      template<class CONT_TYPE>
      CONT_TYPE* getContainer()
      {
         std::hash_map<ContainerType, void*>::iterator i;
         ContainerType type = CONT_TYPE::TYPE;
         i = mContainers.find(type);
#ifdef GFX_DEBUG
         if(type == sga::UNKNOWN_TYPE)
         {
            std::cout << "ERROR: Trying to use container with no TYPE defined. Container: " << typeid(CONT_TYPE).name() << std::endl;
            gfxASSERT(false);
         }
#endif
         if(i != mContainers.end())
         {
            return static_cast<CONT_TYPE*>((*i).second);
         }
         else
         {
            //gfxASSERT(false && "Tried to getContainer() when node did not have that container type yet");
            return NULL;
         }
      }

      // Automagically create the container if it does not yet exist in the holder
      // POST: If container did not exist previously, then create it
      template<class CONT_TYPE>
      CONT_TYPE* autoGetContainer()
      {
         CONT_TYPE* ret_val = getContainer<CONT_TYPE>();
         if(ret_val == NULL)
         {
            ret_val = new CONT_TYPE;
            setContainer<CONT_TYPE>(ret_val);
         }

         return ret_val;
      }

      template<class CONT_TYPE>
      void setContainer(CONT_TYPE* cont)
      {
         ContainerType type = CONT_TYPE::TYPE;
#ifdef GFX_DEBUG
         if(type == sga::UNKNOWN_TYPE)
         {
            std::cout << "ERROR: Trying to use container with no TYPE defined. Container: " << typeid(CONT_TYPE).name() << std::endl;
            gfxASSERT(false);
         }
#endif
         mContainers[type] = static_cast<void*>(cont);
      }

   private:
      // Hash to hold the containers
      std::hash_map<ContainerType, void*> mContainers;
   };
};

#endif
