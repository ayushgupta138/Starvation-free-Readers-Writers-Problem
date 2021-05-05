semaphore *in = new semaphore(1); // initializing the semaphore to 1 makes it a binary semaphore which a specialized version of mutex locks.
semaphore *out = new semaphore(1);
semaphore *write = new semaphore(0); // 0 initialization is explained later.
int start_count = 0; // represents the number of reader processes who have started reading the shared record.
int read_count = 0; // represents the number of reader processes who have completed reading the shared record.
bool wait = false;
