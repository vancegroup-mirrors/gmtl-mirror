#ifndef _GFX_TS_OBJECT_H_
#define _GFX_TS_OBJECT_H_

#include <gfxConfig.h>

namespace gfx {

//-----------------------------------------------------------------
//: Base Thread Specific object.
//
// Used so that we can have an array of heterogenous TS objects.
// (ie. We get some type safety)
// Also defines some memeber that all TS Objects need.
//-----------------------------------------------------------------
class TSBaseObject
{
public:
   virtual ~TSBaseObject()
   {;}
};

//-----------------------------------------------------------------
//: This is the object actually stored in the system.
//-----------------------------------------------------------------
template <class T>
class TSObject : public TSBaseObject
{
public:
   virtual ~TSObject()
   {;}

   //-----------------------------------------------------------------
   //: Return the address of our object
   //-----------------------------------------------------------------
   T* getObject()
   { return &mLocalObj; }

private:
   T mLocalObj;
};


}
#endif
