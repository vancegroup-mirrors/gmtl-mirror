#ifndef _GFX_THREAD_POOL_H
#define _GFX_THREAD_POOL_H

#include <gfxConfig.h>

#include <Threads/ThreadFunctor.h>
#include <Threads/Thread.h>
#include <Threads/CondVar.h>

namespace gfx {

//: Helper class for ThreadPool
//
// Thread states
//    SLEEP: Thread should be sleeping waiting for new work
//    RUN: Thread should start running (or is running) the current functor
//    EXIT: Thread should exit ASAP because I want it to die.
class OneThread
{
public:
   enum ThreadState { SLEEP, RUN, EXIT };    // The state that we want the thread in

    OneThread() : mCurState(OneThread::SLEEP), mThread(NULL), mNext(NULL), mFunctor(NULL) {
        mNext = NULL;
    }

public:
   ThreadState          mCurState;        // The current state of the thread
   Thread*              mThread;          //: Handle of the thread process
   OneThread*           mNext;            //: -> next OneThread ready to run
   BaseThreadFunctor*   mFunctor;         //: -> function thread is to call
   CondVar              mStateCondVar;    //: Condition variable that waits for thread state change
};

std::ostream& operator<< (std::ostream&, OneThread&);


//----------------------------------------------
//: A pool of threads to process user jobs
//
//
// Outline of thread pool <br>
//   |-Need to initialize all thread given a parameter to the constructor of the # to use <br>
//   |-Need a function to block until all work is done that has started <br>
//   |-Just repetiviely add work to the process <br>
//
// Author:
// Allen Bierbaum
//-----------------------------------------------
//!PUBLIC_API:
class ThreadPool
{
public:
   // -----------------------------------------------------------------------
   //: Constructor.
   //  numToStartWith - Number of threads to have in pool
   //  stackSize      - Size of the stack for each thread (0 -- system default)
   // -----------------------------------------------------------------------
   ThreadPool(int numToStartWith = 1, long stackSize=0);

   // -----------------------------------------------------------------------
   //: Give a function to the processes.  Start a function going
   //+ asynchronously.  Called by master process.
   // -----------------------------------------------------------------------
   void startFunc (THREAD_FUNC func, void* arg = NULL)
   {
      ThreadNonMemberFunctor* NonMemFunctor = new ThreadNonMemberFunctor(func, arg);
      this->startFunc(NonMemFunctor);
   }

   // -----------------------------------------------------------------------
   // -----------------------------------------------------------------------
   void startFunc( BaseThreadFunctor* theFunctor, void* argument)
   {
      theFunctor->setArg(argument);
      this->startFunc(theFunctor);
   }

   // -----------------------------------------------------------------------
   // -----------------------------------------------------------------------
   void startFunc( BaseThreadFunctor* theFunctor);

   // -----------------------------------------------------------------------
   // Add a new thread to the pool of workers
   // Returns the structure of the newly added thread
   // -----------------------------------------------------------------------
   OneThread* addThread(void);

   // -----------------------------------------------------------------------
   //: Body of a general-purpose child process. The argument, which must be
   //+ declared void* to match the func prototype, is the OneThread
   //+ structure that represents this process.   The contents of that
   //+ struct, in particular threadWait, MUST be initialized by the parent.
   // -----------------------------------------------------------------------
   void threadLoop(void* theThreadAsVoid);

   // -----------------------------------------------------------------------
   //: Wait for work to do.  Put a OneThread structure on the ready list
   //+ and sleep on it.  Called by a child process when its work is done.
   // -----------------------------------------------------------------------
   void threadSleep(OneThread* theThread);

   // -----------------------------------------------------------------------
   //: Get a process to run.  Acquire a OneThread structure from the ready
   //+ list, waiting if necessary.  Called by the master process as part of
   //+ dispatching a thread.
   // -----------------------------------------------------------------------
   OneThread* getThread(void);

   // -----------------------------------------------------------------------
   //: Waits until all threads are done doing their work.
   // -----------------------------------------------------------------------
   void
   barrier (void) {
      mFuncCountCond.acquire();
      {
         while(mOutstandingFuncCount > 0)
            mFuncCountCond.wait();
      }
      mFuncCountCond.release();
   }

   // -----------------------------------------------------------------------
   // -----------------------------------------------------------------------
   void printList(void);

private:
   CondVar        mThreadListCond;        //: Condition variable that syncs on the thread list changing state
   CondVar        mFuncCountCond;         //: Condition variable that syncs working cound
   OneThread*     mListHead;              //: -> first ready OneThread
   volatile int   mOutstandingFuncCount;  //: Number of funcs currently doing work
   long           mDefaultStackSize;      //: Default size for the stack of new threads
};

}

#endif
