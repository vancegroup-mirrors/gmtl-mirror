#include <gfxConfig.h>
#include <Threads/ThreadManager.h>
//#include <Kernel/Debug.h>



namespace gfx {

SingletonImp(gfx::ThreadManager);

//-----------------------------------------------------
//: Called when a thread has been added to the system.
//
//! PRE: Manager must be locked.
//-----------------------------------------------------
void ThreadManager::addThread(Thread* thread)
{

   //vjASSERT(mThreadVectorMutex.test()==1); // Assert manager locked
   //vjASSERT(thread->getTID() >= 0);

   // Insert thread into local table
   while ((int)mThreads.size() <= thread->getTID())
      mThreads.push_back(NULL);
   mThreads[thread->getTID()] = thread;

   //debugDump();               // Dump current state

}

//-----------------------------------------------------
//: Called when a thread has been removed from the
//+ system.
//
//! PRE: Manager must be locked.
//-----------------------------------------------------
void ThreadManager::removeThread(Thread* thread)
{

   //vjASSERT(mThreadVectorMutex.test()==1); // Assert manager locked
   //vjASSERT((thread->getTID() >= 0) && (thread->getTID() < (int)mThreads.size()));
   mThreads[(unsigned int)thread->getTID()] = NULL;

}


//: Dump the state of the manager to debug
void ThreadManager::debugDump()
{

   std::cerr
      << "------- Thread Manager DUMP -------\n";
   std::cerr << "--- Thread List ----\n";

   for (unsigned int i=0;i<mThreads.size();i++)
   {
      if (mThreads[i] != NULL)
         std::cerr << i << ": ["
                                                << (void*)mThreads[i] << "] "
                                                << mThreads[i] << std::endl;
      else
         std::cerr << i << ": ["
                                                << (void*)mThreads[i]
                                                << "] No thread\n";
   }

   std::cerr << "---------------------\n";

}

}


