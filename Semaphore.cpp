struct semaphore
{
  int value;
  Queue *q = new Queue();
  
  semaphore(int n)
    {
       value=n;
    }
  
  void wait(int pid)  // assuming the process id is passed while securing the semaphore.
    {
       value--;
       if(value < 0)
         {
           q->push(pid);
           block();  // here block is assumed to be a system call which suspends the process that invlokes it.
                    // The process remains blocked unless explicitly woken up.
         } 
    }

  void signal()
    {
      value++;
      if(value <= 0)
        {
          wakeup(q->pop()); // wakeup() is a system call which resume the blocked process with a given process id.
        }
    }
};

//Queue implementation for the semaphore as mentioned above:

struct Node
{
  int data;
  Node *next;
  Node(int n)
  {
     data=n;
     next=NULL;
  }
};

struct Queue
{
   Node *front,*rear;
   Queue()
    {
       front=rear=NULL;
    }
    
   void push(int pid)
   {
      Node *temp=new Node(pid);
      if(front==NULL)
       {
          front=rear=temp;
       }
      else 
       {
         rear->next=temp;
         rear=rear->next;
       } 
   }
   
   int pop()
    {
      if(front==NULL)
       {
          return -1;
       }
      else 
       {
         Node *temp=front;
         if(front==rear)
           {
              front=rear=NULL;
           }
         else 
          {
              front=front->next;  
          }
         int pid=temp->data;
         delete(temp);
         return pid;
       }
    }
};
