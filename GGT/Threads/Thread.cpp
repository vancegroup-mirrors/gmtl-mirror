#include <gfxConfig.h>
#include <Threads/Thread.h>
#include <Threads/ThreadManager.h>
#include <Threads/ThreadFunctor.h>

namespace gfx
{


Thread::Thread(THREAD_FUNC func, void* arg, long stackSize) : mThreadId(-1)
{

   mUserThreadFunctor = NULL;

   // Create the thread functor to start
   mUserThreadFunctor = new ThreadNonMemberFunctor(func, arg);
   ThreadMemberFunctor<Thread>* start_functor
   = new ThreadMemberFunctor<Thread>(this,&Thread::startThread,NULL);

   // START THREAD
   // NOTE: Automagically registers thread UNLESS failure
   spawn(start_functor, stackSize);

}


//: Spawning constructor (functor version).
// Create and spawn thread using the given functor
Thread::Thread(BaseThreadFunctor* functorPtr, long stackSize) : mThreadId(-1)
{

   // Create the thread functor to start
   mUserThreadFunctor = functorPtr;
   ThreadMemberFunctor<Thread>* start_functor
   = new ThreadMemberFunctor<Thread>(this,&Thread::startThread,NULL);

   // START THREAD
   // NOTE: Automagically registers thread UNLESS failure
   spawn(start_functor, stackSize);

}

bool Thread::spawn(BaseThreadFunctor* functorPtr, long stackSize)
{
   mPRThreadPtr = PR_CreateThread(PR_USER_THREAD,
                                  gfxThreadFunctorFunction,
                                  functorPtr,
                                  PR_PRIORITY_NORMAL,
                                  PR_GLOBAL_THREAD,
                                  PR_JOINABLE_THREAD,
                                  stackSize);

   if(mPRThreadPtr != NULL)
      return true;
   else
   {
      std::cerr << "ERROR: PR_CreateThread: Failed.\n";
      return false;
   }
}

void Thread::startThread(void* null_param)
{
   // WE are a new thread... yeah!!!!
   // TELL EVERYONE THAT WE LIVE!!!!
   ThreadManager::instance()->lock();      // Lock manager
   {
      setThreadSpecific(this);       // Store the pointer to me
      create_thread_id();                          // Create our thread id
      ThreadManager::instance()->addThread(this);  // Add the thread to the table

   }
   ThreadManager::instance()->unlock();

// --- CALL USER FUNCTOR --- //
   (*mUserThreadFunctor)();
}

void* Thread::getThreadSpecific()
{
   if(!mHaveAllocatedThreadPrivId)
      allocateThreadPrivateData();

   return PR_GetThreadPrivate(mPrivDataId);
}

void Thread::setThreadSpecific(void* data)
{
   if(!mHaveAllocatedThreadPrivId)
      allocateThreadPrivateData();

   PR_SetThreadPrivate(mPrivDataId, data);
}

void Thread::allocateThreadPrivateData()
{
   mPrivDataIdLock.acquire();
   {
      if(mHaveAllocatedThreadPrivId == false)
      {
         PRStatus ret_status = PR_NewThreadPrivateIndex(&mPrivDataId,NULL);
         if(ret_status != PR_SUCCESS)
         {
            std::cerr << "Error allocating thread private id\n";
         }
         mHaveAllocatedThreadPrivId = true;
      }
   }
   mPrivDataIdLock.release();
}

PRUint32 Thread::mNextThreadId = 0;   // Initialized to 0
bool     Thread::mHaveAllocatedThreadPrivId = false;      // Initialized to false, set when we allocate
PRUintn  Thread::mPrivDataId = 0;
Mutex    Thread::mPrivDataIdLock;


}
