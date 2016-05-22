#include <cstdlib>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <pthread.h>

#include <atomic>

using namespace std;
/*    
class Thread
{
private:
    pthread_t thread;

    Thread(const Thread& copy);         // copy constructor denied
    static void *thread_func(void *d)   { ((Thread *)d)->run(); return NULL; }

public:
    Thread()             {}
    virtual ~Thread()    {}
        
    virtual void run() = 0;

    int start()          { return pthread_create(&thread, NULL,
                           Thread::thread_func, (void*)this); }
    int wait ()          { return pthread_join  (thread, NULL); }
};

typedef std::auto_ptr<Thread> ThreadPtr;

int main(void)
{
    class Thread_a:public Thread
    {
    public:
        void run()
        {
            for (int i=0; i<20; i++, sleep(1))
                std::cout << "a  " << std::endl;
        }
    };

    class Thread_b:public Thread
    {
    public:
    void run()
        {
            for(int i=0; i<20; i++, sleep(1))
                std::cout << "  b" << std::endl;
        }
    };

    ThreadPtr a( new Thread_a() );
    ThreadPtr b( new Thread_b() );
    
    if (a->start() != 0 || b->start() != 0)
        return EXIT_FAILURE;

    if (a->wait() != 0 || b->wait() != 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
*/
int main(){
    const int num_mailboxes = 32;
    std::atomic<int> mailbox[num_mailboxes];
 
    // The writer threads update non-atomic shared data and then update mailbox[i] as follows
    std::atomic_store_explicit(&mailbox[0], std::memory_order_release);
 
    // Reader thread needs to check all mailbox[i], but only needs to sync with one
    for (int i = 0; i < num_mailboxes; ++i) {
        if (std::atomic_load_explicit(&mailbox[i],  std::memory_order_relaxed) == i) {
            std::atomic_thread_fence(std::memory_order_acquire); // synchronize with just one writer
            cout << i  << endl; // guaranteed to observe everything done in the writer thread before
                    // the atomic_store_explicit()
    }
 }
}