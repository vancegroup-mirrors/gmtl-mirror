#include <gfxConfig.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

#ifdef HAVE_SYS_TIME_H
#   include <sys/time.h>
#endif

#ifndef VJ_OS_Win32
#   include <sys/resource.h>
#endif

#include <Threads/ThreadPool.h>
#include <Threads/Thread.h>

namespace gfx {


// XXX: There is a bug that causes a memory leak
//   - We never delete the Functors

// ---------------------------------------------------------------------------
// Constructor.
// ---------------------------------------------------------------------------
ThreadPool::ThreadPool (int numToStartWith, long stackSize)
{
   std::cerr << "vjThreadPool::vjThreadPool: Entering.\n";
   std::cerr << "\tvjThreadPool::vjThreadPool: Number threads: " << numToStartWith << std::endl;

   mDefaultStackSize = stackSize;

   mListHead = NULL;
   mOutstandingFuncCount = 0;
   //finishedLock.release();         // Initialize if to threads being done

   //-- Start the initial # of threads ---//
   for (int index=0;index < numToStartWith;index++)
   {
      addThread();
   }
}

void ThreadPool::startFunc( BaseThreadFunctor* theFunctor)
{
   OneThread* theThread = getThread();

   // Set functor and put thread in running state, then NOTIFY it fo changes
   theThread->mStateCondVar.acquire();
   {
      theThread->mFunctor = theFunctor;
      theThread->mCurState = OneThread::RUN;
      theThread->mStateCondVar.notify();
   }
   theThread->mStateCondVar.release();

   // ADD ONE TO OUTSTANDING LIST
   mFuncCountCond.acquire();
      mOutstandingFuncCount += 1;
      mFuncCountCond.notify();         // Must notify of state change
   mFuncCountCond.release();
}

// ---------------------------------------------------------------------------
// Create a thread and start it running.
// When thread gets put to sleep in controlLoop, it will get added to the list
// ---------------------------------------------------------------------------
OneThread* ThreadPool::addThread (void)
{
    OneThread* new_thread = new OneThread;
    new_thread->mNext = NULL;

    ThreadMemberFunctor<ThreadPool>* member_functor = new ThreadMemberFunctor<ThreadPool>(this, &ThreadPool::threadLoop, (void*)new_thread);

    new_thread->mThread = new Thread(member_functor, mDefaultStackSize);

    //printList();

    return new_thread;
}

// ---------------------------------------------------------------------------
// Body of a general-purpose child process. The argument, which must be
// declared void* to match the func prototype, is the vjOneThread structure
// that represents this process.   The contents of that struct, in
// particular threadWait, MUST be initialized by the parent.
// ---------------------------------------------------------------------------
void
ThreadPool::threadLoop(void* theThreadAsVoid) {
//   DebugLock.acquire();
   //std::cerr << Thread::self()
   //          << " ThreadPool::threadLoop: Entering."
   //          << std::endl;

   // --- ACQUIRE thread list lock, to make sure that addThread has exited.
   mThreadListCond.acquire();
   mThreadListCond.release();

   OneThread* myThread = (OneThread*)theThreadAsVoid;
   bool         kill_off_thread(false);                     // When set true, the thread will exit

   while(!kill_off_thread)
   {
      // --- WAIT FOR WORK --- //
      threadSleep(myThread);

      // ASSERT:  We now have work to do...

      // --- DO THE WORK --- //
      myThread->mFunctor->operator()();

      // REMOVE ONE TO OUTSTANDING LIST
      mFuncCountCond.acquire();
         mOutstandingFuncCount -= 1;
         mFuncCountCond.notify();         // Must notify of state change
      mFuncCountCond.release();
   }
}

// ---------------------------------------------------------------------------
// Wait for work to do.  Put a OneThread structure on the ready list and
// sleep on it.  Called by a child process when its work is done.
// ---------------------------------------------------------------------------
void
ThreadPool::threadSleep(OneThread* theThread) {
   // --- ADD THREAD TO LIST --- //
   mThreadListCond.acquire();       // acquire exclusive rights to threadList
      theThread->mCurState = OneThread::SLEEP;
      theThread->mNext = mListHead;   // put self on head of the list
      mListHead = theThread;

      mThreadListCond.notify();     // Notify any waiting users of the pool, that pool state has changed
   mThreadListCond.release();       // release threadList

   // --- WAIT UNTIL WE ARE PUT BACK INTO RUNNING STATE --- //
   theThread->mStateCondVar.acquire();
      while(theThread->mCurState == OneThread::SLEEP)
         theThread->mStateCondVar.wait();

   // NOW WE ARE READY TO RUN
   theThread->mStateCondVar.release();
}

// ---------------------------------------------------------------------------
// Get a process to run.  Acquire a OneThread structure from the ready list,
// waiting if necessary.  Called by the master process as part of
// dispatching a thread.
// ---------------------------------------------------------------------------
OneThread*
ThreadPool::getThread (void) {
   OneThread* theThread;

   // ThreadList condition
   mThreadListCond.acquire();
   {
      // WAIT UNTIL THREAD AVAILABLE
      while (mListHead == NULL)
         mThreadListCond.wait();

      theThread = mListHead;
      mListHead = theThread->mNext;
   }
   mThreadListCond.release();        // exit(monitor);

   return theThread;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void
ThreadPool::printList (void) {
    OneThread* curThread = mListHead;
    int counter = 0;

    std::cerr << "----- Thread List -----\n";

    while(curThread != NULL) {
        std::cerr << "Thread: " << counter++ << std::endl;
        std::cerr << "\tpid: " << *curThread << std::endl;
        curThread = curThread->mNext;
    }
}



std::ostream& operator<< (std::ostream& outfile, OneThread& thread)
{
    outfile << thread.mThread;
    return outfile;
}

}
