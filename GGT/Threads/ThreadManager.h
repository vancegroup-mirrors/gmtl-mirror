#ifndef _GFX_THREAD_MANAGER_H_
#define _GFX_THREAD_MANAGER_H_

#include <gfxConfig.h>
#include <Threads/Thread.h>
#include <Threads/Mutex.h>
#include <Threads/Guard.h>

#include <Util/Singleton.h>
#include <vector>


namespace gfx
{

//----------------------------------------------------
//: Manager that maintains data about all threads.
//
// This class holds data on: <br>
// - List of all threads in system <br>
// - Thread Specific data items
//
//-----------------------------------------------------
//!PUBLIC_API:
class ThreadManager
{
public:
   //-----------------------------------------------------
   //: Called when a thread has been added to the system.
   //
   //! PRE: Manager must be locked.
   //-----------------------------------------------------
   void addThread(Thread* thread);

   //-----------------------------------------------------
   //: Called when a thread has been removed from the
   //+ system.
   //
   //! PRE: Manager must be locked.
   //-----------------------------------------------------
   void removeThread(Thread* thread);

   //-----------------------------------------------------
   //: Lock the manager so that we have complete control
   //+ to do stuff.
   // The manager should be locked whenever there is
   // about to be a change in number of threads in the
   // system.
   //-----------------------------------------------------
   void lock()
   {
      mThreadVectorMutex.acquire();
   }

   //-----------------------------------------------------
   //: Unlock the manager to allow people to use it
   //+ again.
   //-----------------------------------------------------
   void unlock()
   {
      mThreadVectorMutex.release();
   }

   //-----------------------------------------------------
   //: Dump the state of the manager to debug.
   //-----------------------------------------------------
   void debugDump();

protected:
   void setSystemWideThreadingDefaults()
   {
      std::cout << "Setting system wide threading defaults:\n";
      // Set concurrency
      unsigned num_cpus = Thread::getNumCPUs();
      Thread::setConcurrency(num_cpus);
      std::cout << "   setConcurrency: " << num_cpus << " cpus\n";
      std::cout << std::flush;
   }

private:
   Mutex                mThreadVectorMutex;     //: Mutex to protect the threads vector
   std::vector<Thread*> mThreads;            		//: List of all threads in system

public:
   //: Generate a unique key for Thread Specific data
   // This value will be used locally by each thread in the system
   long generateNewTSKey()
   {
      Guard<Mutex> guard(mTSKeyMutex);
      return mNextTSObjectKey++;
   }

private:
   Mutex     mTSKeyMutex;          //: Mutex to protect allocate of TS keys
   long        mNextTSObjectKey;  //: The next available object key


   // ----------------------- //
   // --- SINGLETON STUFF --- //
   // ----------------------- //
protected:
   //-----------------------------------------------------
   //: Constructor.  Hidden, so no instantiation is
   //+ allowed.
   //-----------------------------------------------------
   ThreadManager() : mNextTSObjectKey(0)
   {
      setSystemWideThreadingDefaults();
   }

SingletonHeader(ThreadManager);

};

}


#endif
