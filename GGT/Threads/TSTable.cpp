
#include <gfxConfig.h>
#include <Threads/TSTable.h>
//#include <Kernel/Debug.h>

namespace gfx
{

//: Delete the table
// Delete all objects in the table
TSTable::~TSTable()
{
   // For all elements in the table
   for(unsigned int i=0;i<mTSObjects.size();i++)
      if(mTSObjects[i] != NULL)        // If valid object
         delete mTSObjects[i];         // Delete them
}

//: Get the object with the spcified key
TSBaseObject* TSTable::getObject(unsigned int objectKey)
{
   //vjASSERT((objectKey >= 0) && (objectKey < mTSObjects.size()));    // Did you check to make sure the table contained it
   return mTSObjects[objectKey];
}


//-----------------------------------------------------------------
//: Set an object entry in the table.
//-----------------------------------------------------------------
void TSTable::setObject(TSBaseObject* object, long key)
{
   //vjASSERT(key >= 0);
   while((long)mTSObjects.size() <= key)
      mTSObjects.push_back(NULL);
   mTSObjects[key] = object;
}

//-----------------------------------------------------------------
//: Release the object given by key.
//
//! POST: Obj(key) is deleted, and the ptr is set to NULL.
//-----------------------------------------------------------------
void TSTable::releaseObject(unsigned long key)
{
   //ASSERT( (key>=0) && (key<mTSObjects.size()) );
   if (mTSObjects[key] != NULL)
      delete mTSObjects[key];
   mTSObjects[key] = NULL;
}

}

