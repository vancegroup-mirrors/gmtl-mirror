/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Traverser.h,v $
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
#ifndef _SGA_TRAVERSER_H_
#define _SGA_TRAVERSER_H_

#include <Performer/pf/pfNode.h>
#include <Performer/pf/pfGroup.h>

#include <SGA/PfHelperFuncs.h>

namespace sga
{


//
// Idea: The future idea of the traverser code should be to shield the user from the "true" node types in any way
//       This may include part of the process of getting the children of the node.
//

class PfTravState
{
public:
   PfTravState() : mNodeList(0), mDepth(0), mNumChildren(0), mGroupNode(NULL)
   {;}

   // Initialize the object (clear to initial state)
   // Note: derived versions MUST call parent's init function
   virtual void init()
   {
      mNodeList.clear();
      mDepth = 0;
      mNumChildren = 0;
      mGroupNode = NULL;
   }

   // Called upon entry into traversal
   // NOTE: Derived version should ALWAYS call the base class member BEFORE
   //       they do anything.
   //  enterTrav()
   //      parent::enterTrav()
   //      doSomething()
   virtual void enterTrav() {;}

   // Called upon exit of traversal
   // NOTE: Derived version should ALWAYS call the base class member AFTER
   //       they do anything.
   //  exitTrav()
   //      doSomething()
   //      parent::exitTrav()
   virtual void exitTrav() {;}


   void pushChild(pfNode* node);
   void pop();

   unsigned numChildren();
   pfNode* getChild(const unsigned childNum);

   pfNode* node() const
   {
      if(mNodeList.empty())
         return NULL;
      else
         return mNodeList.back();
   }
   unsigned depth() const
   { return mDepth; }

protected:
   std::vector<pfNode*> mNodeList;     // List of nodes that we have
   unsigned mDepth;

private:
   unsigned mNumChildren;     // Cache the number of children (If > 0, then we have group)
   pfGroup* mGroupNode;       // Cached ptr of type pfGroup
};


class Traverser
{
public:
   enum TravStatus { CONT, TERM, PRUNE };
};

class PfTraverser : public Traverser
{
public:
   PfTraverser()
   {
      mTravState = new PfTravState; // Default to basic trav stats
   }

   PfTraverser(PfTravState* travState)
   { mTravState = travState; }

   virtual ~PfTraverser() {;}

   /*
   const PfTravState* travState()
   { return mTravState; }
   */

   PfTravState* travState()
   { return mTravState; }

   void setTravState(PfTravState* newTravState)
   {
      if(mTravState != NULL)
         delete mTravState;
      mTravState = newTravState;
   }

   //: Call to traverse the scene
   template<class _TpreFunctor,
            class _TpostFunctor>
   Traverser::TravStatus traverse(pfNode* node, _TpreFunctor preFunc, _TpostFunctor postFunc);

protected:
   PfTravState*    mTravState;
};


/*
template<class BTRAV>
class TrackPath : public BTRAV
{
public:
   inline void enterTrav();
   inline void exitTrav();

   const std::vector<pfNode*> path()
   { return mPath; }

protected:
   std::vector<pfNode*> mPath;
};
*/

//template<class BTRAV, bool PRECOMPUT_INV>
//template<class BTRAV>
class TrackXform : public PfTravState
{
public:
   TrackXform();

   virtual ~TrackXform() {;}

   // Initialize the object (clear to initial state)
   // Note: derived versions MUST call parent's init function
   virtual void init()
   {
      PfTravState::init();
      mMatrixStack.clear();
      mComputedInv = false;
   }

   virtual void enterTrav();
   virtual void exitTrav();

   const gmtl::Matrix& getXformMat();

   gmtl::Matrix getXformMatInv();

protected:     // Helpers
   void popMatrix();

   void pushMatrix(gmtl::Matrix& mat);

protected:
   std::vector<gmtl::Matrix>  mMatrixStack;
   bool         mComputedInv;    // Have we already computed the inv
};


///////////// INLINE FUNCTIONs ////////////////////////////

inline
void PfTravState::pushChild(pfNode* node)
{
   gfxASSERT(node != NULL);

   // Set the node
   //mNode = node;
   mNodeList.push_back(node);
   mNumChildren = 0;       // We don't know anything about chilren yet
   mGroupNode = NULL;
   mDepth++;

   // Call the member enterTrav() func, this should call the most derived class's version
   this->enterTrav();
}

inline
void PfTravState::pop()
{
   this->exitTrav();

   mNodeList.pop_back();

   // Fix up all the state variables
   mDepth--;
   mGroupNode = NULL;
   mNumChildren = 0;
}

inline
unsigned PfTravState::numChildren()
{
   if(mGroupNode == NULL)
   {
      if (node()->isOfType(pfGroup::getClassType()))
      {
         mGroupNode = static_cast<pfGroup*>(node());
      }
   }

   if(mGroupNode != NULL)
   {
      mNumChildren = mGroupNode->getNumChildren();
   }
   else
      mNumChildren = 0;

   return mNumChildren;
}

//  @PRE: Must call numChildren before calling this function
inline
pfNode* PfTravState::getChild(const unsigned childNum)
{
 //group_node = static_cast<pfGroup*>(node);
   // Make sure that we are actually a group node
   if(mGroupNode != NULL)
   {
      gfxASSERT(childNum < mGroupNode->getNumChildren());
      return mGroupNode->getChild(childNum);
   }
   else
      return NULL;
}


// Traverser traverse function
template<class _TpreFunctor,
         class _TpostFunctor>
Traverser::TravStatus PfTraverser::traverse(pfNode* node, _TpreFunctor preFunc, _TpostFunctor postFunc)
{
   /*
   unsigned   child;
   unsigned  numChildren(0);
   */
   Traverser::TravStatus ret = Traverser::CONT;

   //pfGroup* group_node;
   pfNode* child_node;

   // Check for NULL node
   if (node == NULL)
   {
      std::cout << "Warning: PfTraverser::traverse() Null node" << std::endl;
      return Traverser::CONT;
   }

   mTravState->pushChild(node);

   /*
   for(unsigned d=0;d<mTravState->depth();d++)
   { std::cout << "  "; }
   std::cout << mTravState->depth() << ": [" << node->getName() << "]  type: "
                                    << node->getType()->getName()
                                    << " numChild:" << mTravState->numChildren() << std::endl;
   */

   // -------- PRE FUNC ------ //
   // Call PRE-Function: pfTraverser::traverse
   ret = preFunc(this);

   // Check for early exit: pfTraverser::traverse
   if (ret == Traverser::PRUNE)
   {
      mTravState->pop();
      return Traverser::CONT;
   }
   else if (ret == Traverser::TERM)
   {
      mTravState->pop();
      return Traverser::TERM;
   }

   // ---- GO DEEPER ---- RECURSE --- //
   if(mTravState->numChildren() > 0)
   {
      unsigned numChildren = mTravState->numChildren();

      for (unsigned child = 0 ; (child < mTravState->numChildren()) && (ret == Traverser::CONT) ; child++)
      {
         gfxASSERT((child < mTravState->numChildren()) && "Trying to access out of range children in core pfTraverser::traverse");
         child_node = mTravState->getChild(child);
         if(child_node != NULL)
         {
            ret = traverse(child_node, preFunc, postFunc);
            /*
            if (numChildren > mTravState->numChildren())       // if the child is deleted
            {
               --child;
               --numChildren;
            }
            */
         }
      }
   }
   // other nodes, presume leaf
   else
   {
      //std::cout << "PfTraverser::traverse: Unknow node type..." << std::endl;
   }

   // Check early return
   if (ret == Traverser::PRUNE)
   {
      mTravState->pop();
      return Traverser::CONT;
   }
   else if (ret == Traverser::TERM)
   {
      mTravState->pop();
      return Traverser::TERM;
   }

   // ------ POST FUNCTION ------ //
   ret = postFunc(this);

   if (ret == Traverser::PRUNE)
   {
      mTravState->pop();
      return Traverser::CONT;
   }
   else if (ret == Traverser::TERM)
   {
      mTravState->pop();
      return Traverser::TERM;
   }

   // "Pop" off anything that was done
   mTravState->pop();

   return Traverser::CONT;
}

/*
    // pfSwitch
    if (pfIsOfType(node, pfGetSwitchClassType()))
   switch (trav->mode & PFUTRAV_SW_MASK)
   {
   case PFUTRAV_SW_CUR:
       val = pfGetSwitchVal((pfSwitch *)node);
       ret = travChild((pfGroup*)node, val, trav);
       break;
   case PFUTRAV_SW_ALL:
       for (i = 0 ; i < numChild && ret == PFTRAV_CONT ; i++)
       {
      ret = travChild((pfGroup*)node, i, trav);
      if(numChild > pfGetNumChildren(node))  // if the child is deleted
      {
          i--;
          numChild--;
      }
       }
       break;
   case PFUTRAV_SW_NONE:
       break;
   }
    // pfLOD
    else if (pfIsOfType(node, pfGetLODClassType()))
   switch (trav->mode & PFUTRAV_LOD_MASK)
   {
   case PFUTRAV_LOD_RANGE0:
       range0 = pfGetLODRange((pfLOD *)node, 0);
       range1 = pfGetLODRange((pfLOD *)node, 1);
       if (range0 <= 0.0f && 0.0f < range1)
      if (numChild > 0)
          ret = travChild((pfGroup*)node, 0, trav);
       break;
   case PFUTRAV_LOD_ALL:
       for (i = 0 ; i < numChild && ret == PFTRAV_CONT ; i++)
       {
      ret = travChild((pfGroup*)node, i, trav);
      if(numChild > pfGetNumChildren(node))     // if the child is deleted
      {
          i--;
          numChild--;
      }
       }
       break;
   }
    // pfSequence
    else if (pfIsOfType(node, pfGetSeqClassType()))
   switch (trav->mode & PFUTRAV_SEQ_MASK)
   {
   case PFUTRAV_SEQ_CUR:
       if ((val = pfGetSeqFrame((pfSequence *)node, NULL)) >= 0)
      ret = travChild((pfGroup*)node, val, trav);
       else
      ret = PFTRAV_PRUNE;
       break;
   case PFUTRAV_SEQ_ALL:
       for (i = 0 ; i < numChild && ret == PFTRAV_CONT ; i++)
       {
      ret = travChild((pfGroup*)node, i, trav);
      if(numChild > pfGetNumChildren(node))     // if the child is deleted
      {
          i--;
          numChild--;
      }
       }
       break;
   case PFUTRAV_SEQ_NONE:
       break;
   }
    // other pfGroups
    else if (pfIsOfType(node, pfGetGroupClassType()))
    */




};    // Namespace sga

#endif

