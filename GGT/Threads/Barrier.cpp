//#include <vjConfig.h>
#include <Threads/Barrier.h>


// ---------------------------------------------------------------------------
// Block the caller until all <count> threads have called <wait> and then
// allow all the caller threads to continue in parallel.
// ---------------------------------------------------------------------------
int
Barrier::wait (void) {
    Guard<Mutex> guard(mutex);

    SubBarrier* curSubBarrier = this->subBarrier[currentGeneration];

    // Check for shutdown...
    if (curSubBarrier == NULL) {
        return -1;
    }

    if (curSubBarrier->runningThreads == 1)
    {
        // We're the last running thread, so swap generations and tell
        // all the threads waiting on the barrier to continue on their
        // way.

        curSubBarrier->runningThreads = this->count;

        // Swap generations.
        currentGeneration = 1 - this->currentGeneration;	    // Cycles between 0 and 1
        curSubBarrier->barrierFinished.broadcast();
    }
    else
    {
        --curSubBarrier->runningThreads;

        // Block until all the other threads wait().
        while (curSubBarrier->runningThreads != count)
            curSubBarrier->barrierFinished.wait ();
    }

    return 0;
}
