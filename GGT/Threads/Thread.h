#ifndef _GFX_THREAD_H_
#define _GFX_THREAD_H_

#include <gfxConfig.h>
#include <nspr.h>

#include <Threads/Mutex.h>
//#include <Threads/ThreadFunctor.h>
#include <Threads/TSTable.h>

#ifdef BSYS_OS_IRIX
#include <sys/types.h>
#include <sys/sysmp.h>
#endif

namespace gfx {


class BaseThreadFunctor;

// Typedefs to help with cross-platform abilities
typedef void (*THREAD_FUNC)(void *);

// Default thread implementation using NSPR
// This could be replaced in the future with system specific threads if need be
class Thread
{

public:
 //: Spawning constructor.
    // Creates and spawns the thread
   // stackSize - Number of bytes to allocate, 0 --> System default
   Thread(THREAD_FUNC func, void* arg = 0, long stackSize = 0);

    //: Spawning constructor (functor version).
    // Create and spawn thread using the given functor
    // stackSize - Number of bytes to allocate, 0 --> System default
    Thread(BaseThreadFunctor* functorPtr, long stackSize = 0);

    //: Destructor.
    //
    //! PRE: None.
    //! POST: This thread is removed from the thread table and from the local
    //+       thread hash.
    virtual ~Thread(void)
    {
       //delete mUserThreadFunctor;
    }


    // -----------------------------------------------------------------------
    //: Create a new thread that will execute functorPtr.
    //
    //! PRE: None.
    //! POST: A thread is created that begins executing functorPtr*(
    //! ARGS: functorPtr - Function to be executed by the thread.
    //
    //! RETURNS: true - Successful thread creation
    //! RETURNS: false - Error
    // -----------------------------------------------------------------------
    bool spawn(BaseThreadFunctor* functorPtr, long stackSize);

    // Called by the spawn routine to start the user thread function
    // PRE: Called ONLY by a new thread
    // POST: The new thread will have started the user thread function
    void startThread(void* null_param);


public:  // ----- Various other thread functions ------ //

    // -----------------------------------------------------------------------
    //: Get this thread's priority.
    //virtual int getPrio(int* prio);

    // -----------------------------------------------------------------------
    //: Set this thread's priority.
    // -----------------------------------------------------------------------
    //virtual int setPrio(int prio);


   // Block until thread exits
   //! RETURNS: true - Successfule
   //+          false - Either thread is non-joinable, or another thread is waiting for it, or big error
   bool join()
   {
      PRStatus ret_status;
      ret_status = PR_JoinThread(mPRThreadPtr);

      if(ret_status == PR_SUCCESS)
         return true;
      else
         return false;
   }

    // -----------------------------------------------------------------------
    //: Yield execution of the calling thread to allow a different blocked
    //+ thread to execute.
    //
    //! PRE: None.
    //! POST: The caller yields its execution control to another thread or
    //+       process.
    // -----------------------------------------------------------------------
    static void
    yield (void) {
        PR_Sleep(PR_INTERVAL_NO_WAIT);
    }

    // -----------------------------------------------------------------------
    //: Get a ptr to the thread we are in.
    //
    //! RETURNS: NULL - Thread is not in global table
    //! RETURNS: NonNull - Ptr to the thread that we are running within
    // -----------------------------------------------------------------------
    static Thread*
    self(void)
    {
       return static_cast<Thread*>(getThreadSpecific());
    }

    // -----------------------------------------------------------------------
   //: Is this a valid thread?
   //
   //! RETURNS: true - object represents a thread that has been created
   //+                 correctly.
   // -----------------------------------------------------------------------
   bool valid()
   {
      return (mThreadId != -1);
   }

   // -----------------------------------------------------------------------
   //: Ouput the state of the object.
   // -----------------------------------------------------------------------
   virtual std::ostream& outStream(std::ostream& out)
   {
      out << "t:" << mThreadId << " ";
      return out;
   }

   // -----------------------------------------------------------------------
   //: Get the "thread ID" of this BaseThread object.  This is a unique
   //+ integer value assigned when the thread was created.
   //
   //! RETURNS: -1 - Bad thread. Creation error.
   //! RETURNS: other - id of thread in Juggler
   // -----------------------------------------------------------------------
   PRInt32 getTID()
   { return mThreadId; }

public:     // STATIC HELPERS
   // return the number of CPUs in the system
   static unsigned getNumCPUs()
   {
#ifdef BSYS_OS_IRIX
      return sysmp(MP_NPROCS);
#else
      return 1;
#endif
   }

   // Set threading abstraction to be able run this many procs simultaneously
   static void setConcurrency(unsigned numCPUs)
   {
      PR_SetConcurrency(numCPUs);
   }


protected:
   // -----------------------------------------------------------------------
   //: Initialize the state of the object.
   // -----------------------------------------------------------------------
   void create_thread_id()
   {
      mThreadId = getNextThreadId();
   }

private:
   BaseThreadFunctor*   mUserThreadFunctor;     // The functor to call when the thread starts
   PRThread*            mPRThreadPtr;
   PRInt32              mThreadId;    // The local id for the thread, -1 ==> invalid thread


public:     // Thread specific data caching
   //: Get the Thread specific data table
   // NOTE: Users should NOT access the table directly
   // instead, use TSObjectProxies
   TSTable* getTSTable()
   { return &mTSTable; }

private:
   TSTable  mTSTable;      // Thread specific data for the thread

   // --- STATICS ---- //
private:
   // XXX: What happens when it rolls over after we have been running for a LONG time.
   static PRUint32 getNextThreadId()
   {
      return mNextThreadId++;
   }
   static PRUint32 mNextThreadId;   // Initialized to 0

private:  // --- Interface to set a thread specific pointer ---//
   // This class uses the functions to store a pointer in each thread
   // to the Thread* in memory
   static void* getThreadSpecific();
   static void setThreadSpecific(void* data);
   static void allocateThreadPrivateData();     // Called when we don't have the priv data yet

   static bool       mHaveAllocatedThreadPrivId;      // Initialized to false, set when we allocate
   static PRUintn    mPrivDataId;
   static Mutex      mPrivDataIdLock;                 // Lock for setting the private data

};


// Ouput operator
//std::ostream& operator<<(std::ostream& out, Thread& threadRef);

} // namespace gfx


#endif  /* _GFX_THREAD_H_ */
