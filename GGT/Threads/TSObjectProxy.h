#ifndef _GFX_TS_OBJECT_PROXY_H_
#define _GFX_TS_OBJECT_PROXY_H_

#include <Threads/TSObject.h>
#include <Threads/ThreadManager.h>

namespace gfx {

//-----------------------------------------------------------------
//: This is a smart pointer to a thread specific object.
//
//  This allows users to have an object that has a seperate copy
// for each thread.
//
//! NOTE: The object used for type T must have a default constructor
//+       This class creates each instance of the real objects
//+       using this default constructor.
//-----------------------------------------------------------------
//! PUBLIC_API:

template <class T>
class TSObjectProxy
{
public:
   //-----------------------------------------------------------------
   //: Constructor for proxy.
   //-----------------------------------------------------------------
   TSObjectProxy() : mObjectKey(-1)
   {
      // Get a TS key for the object(s) that this will proxy
      mObjectKey = ThreadManager::instance()->generateNewTSKey();
   }

   //-----------------------------------------------------------------
   //: Destructor.
   //-----------------------------------------------------------------
   ~TSObjectProxy()
   {;}

   T* operator->()
   { return getSpecific(); }

   T& operator*()
   { return *getSpecific();}

private:
   //-----------------------------------------------------------------
   //: Get the correct version for current thread
   // - Find the correct table
   // - Make sure that object exists locally
   // - Get the obj pointer
   // - Attempts a dynamic cast
   //-----------------------------------------------------------------
   T* getSpecific()
   {
      TSTable* table = Thread::self()->getTSTable();

      // ---- DOES OBJECT EXIST --- //
      // If not, Create the object and add it to the table
      if(!table->containsKey(mObjectKey))
      {
         TSBaseObject* new_object = new TSObject<T>;
         table->setObject(new_object,mObjectKey);
      }

      // --- GET THE TS OBJECT --- //
      TSBaseObject* object = table->getObject(mObjectKey);                  // get the specific object
      TSObject<T>* real_object = dynamic_cast< TSObject<T>* >(object);    // try dynamic casting it

      ASSERT(real_object != NULL);      // If fails, it means that "real" object was different type than the proxy
      if(real_object == NULL)
         return NULL;
      else
         return real_object->getObject();                                   // return the ptr;
   }

   // Don't allow copy construction
   TSObjectProxy(TSObjectProxy& proxy)
   {;}

private:
   long  mObjectKey;    // The key to find the object
};

}

#endif
