# Starvation free Readers-Writer Problem

The Readers-Writers problem is one of the classic Process Synchronization problems, and it has been used to test nearly every new synchronization primitive. Several variations exist for the Readers-Writers Problem. The first variation requires that no reader should be kept waiting unless a writer has already obtained permission to modify the shared record. The second variation requires that the writer performs its task as soon as it is available. Both the variations suffer from starvation. The first process may lead to writer starvation, while the second variation may lead to reader starvation.

The third variation requires that the reader and the writer get access to the shared record within a particular time-bound and prevent starvation. The solution to the third variation can be achieved using the FIFO Semaphores for process synchronization between reader and writer process.

### Semaphore implementation

The semaphore required for the purpose mentioned above requires that the processing be done in a FIFO manner, so the semaphore uses a queue to store the waiting processes. When the wait() method is invoked, instead of busy waiting, the process is blocked until the semaphore is available. This choice was made keeping in mind the better CPU utilization in comparison to busy waiting.

Semaphore code :

Semaphore implementation can be found in [Semaphore.cpp](Semaphore.cpp).

Given the complete implementation of FIFO Semaphore and its associated queue data structure, we now discuss the global data shared among all the synchronizing processes.

### Global data
 
Shared global data can be found in [Global_data.cpp](Global_data.cpp).

### Reader Code

Reader process implementation :
``` cpp
 in->wait(pid); // Assuming the process id is also passed to the reader process method.
 start_count++; // in semaphore prevents the simutaneous modification od start_counter variable.
 in->signal();
 
 // read record (This segment is the "critical section")
 
 out->wait(pid);  // secure out semaphore for read_count modification.
 read_count++;
 if(wait && read_count == start_count)
 {
    write->signal();  // release the write semaphore if all the read processes have been completed before a particular write process request.
 }
 out->signal(); // release the out semaphore.
```

### Writer Code

Writer process implementation :

``` cpp
in->wait(pid); // Secure in ensuring no other process executes while the current process executes.
 out->wait(pid); // Secure out semaphore to ensure no read process modifies read_count variable and to prevent any deadlocks;
 if(start_count == read_count)
 {
    out->signal(); // release out semaphore since all read processes have completed their task.
 }
 else
 {
   wait = true;
   out->signal();
   write->wait(pid);
   wait = false;
 }
 
 // modify the record (this is the "critical section")
 
 in->signal(); // release the in semaphore for other processes.
 ```
 
### How it works

All the read processes happen concurrently at the same time until a write process arrives. When a write process arrives, all the read processes that have previously arrived are finished. All the processes which arrive after the current write process wait in the semaphore until the current process finishes. This process repeats till all the processes are executed.

Suppose two read processes and a writer process arrive. The first two read processes happen simultaneously, except for updating the shared variables. When the writer process arrives, it indicates its presence by setting the `wait` to be true. After this, any process which arrives is not executed but is stored in the semaphore queue. After the two read processes are complete, which is indicated by the check `start_count == read_count`, the writer process begins executing. Meanwhile, any process is queued up.

This method prevents starvation by using the FIFO semaphores. This ensures that the processes are roughly executed in the order they arrive. Due to the FIFO nature, this solution to the Readers-Writers Problem is starvation-free.

### References
- [arXiv:1309.4507](https://arxiv.org/ftp/arxiv/papers/1309/1309.4507.pdf)
- Abraham Silberschatz, Peter B. Galvin, Greg Gagne - Operating System Concepts
