#ifndef _GFX_Guard_H_
#define _GFX_Guard_H_

#include <Threads/Mutex.h>

//----------------------------------------------
// Guard
//
// Purpose:
//    Guard wrapper
//
//
// Author:
//	Allen Bierbaum
//-----------------------------------------------
namespace gfx
{

   enum GuardMethod { READ, WRITE, NORMAL };

//: Guard wrapper.
//!PUBLIC_API:

// With method
template <class LOCK, gfx::GuardMethod METHOD = NORMAL>
class Guard
{
public:
   //: Acquire the lock implicitly.
   // If block = 1 then use a blocking acquire
   Guard(LOCK &lock)
   : theLock(&lock)
   {
      acquire();
   }

   //: Release the lock
   ~Guard()
   {
      release();
   }

   //: Acquire the lock
   bool acquire()
   {
      if(METHOD == READ)
         return theLock->acquireRead();
      else if(METHOD == WRITE)
         return theLock->acquireWrite();
      else
         return theLock->acquire();
   }

   //: Explicity release the lock
   int release()
   {
      return theLock->release();
   }

private:
   LOCK* theLock;	//: The lock that we are using
};

// No method
template <gfx::GuardMethod METHOD>
class Guard<Mutex, METHOD>
{
public:
   //: Acquire the lock implicitly.
   // If block = 1 then use a blocking acquire
   Guard(Mutex &lock)
   : theLock(&lock)
   {
      acquire();
   }

   //: Release the lock
   ~Guard()
   {
      release();
   }

   //: Acquire the lock
   bool acquire()
   {
      return theLock->acquire();
   }

   //: Explicity release the lock
   int release()
   {
      return theLock->release();
   }

private:
   Mutex* theLock;	//: The lock that we are using
};



}

#endif
