#ifndef _TS_TABLE_H_
#define _TS_TABLE_H_

#include <gfxConfig.h>
#include <Threads/TSObject.h>
//#include <Threads/Mutex.h>

namespace gfx {

//-----------------------------------------------------------------
//: This class is the actual TS Table.
//
// This class maintains a table that has ptrs to all the TS data
// in the system for a specific thread.
// Only the owning thread may actually access the table
//-----------------------------------------------------------------
class TSTable
{
public:
   TSTable()
   {;}

   //: Delete the table
   // Delete all objects in the table
   ~TSTable();

public:
   // Returns true if the table contains the given key
   // If false, then the user should setObject(...,key) before
   // attempting to access the object
   bool containsKey(long key)
   {
      return ((key>=0)&&((unsigned)key<mTSObjects.size()));
   }

   //: Get the object with the spcified key
   TSBaseObject* getObject(unsigned int objectKey);

   //-----------------------------------------------------------------
   //: Set an object entry in the table.
   //-----------------------------------------------------------------
   void setObject(TSBaseObject* object, long key);

   //-----------------------------------------------------------------
   //: Release the object given by key.
   //
   //! POST: Obj(key) is deleted, and the ptr is set to NULL.
   //-----------------------------------------------------------------
   void releaseObject(unsigned long key);

private:
   std::vector<TSBaseObject*> mTSObjects; //: Map object key to TS Object ptr
};

}
#endif
